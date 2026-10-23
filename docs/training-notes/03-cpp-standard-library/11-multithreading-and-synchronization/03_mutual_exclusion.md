# Mutual exclusion

- Mutual exclusion is satisfied by mutexes:
  - `std::mutex`
  - `std::timed_mutex`
  - `std::recursive_mutex`
  - `std::recursive_timed_mutex`
  - `std::shared_timed_mutex`

## std::mutex

- `std::mutex` offers exclusive non-recursive ownership, which means:
  - Calling thread owns the mutex since call of `lock()` or `try_lock` until calling unlock
  - `lock()` is a blocking function that returns when the mutex is owned by the calling thread
  - `try_lock()` returns immediately if the mutex is not available
  - When a thread owns the mutex, all other threads trying to own it are blocked in the `lock()` function call until the owner releases the mutex by calling `unlock()`
  - `std::mutex` is neither copyable nor movable (it can only be passed by reference or address)
- `std::lock_guard` can be used to automatically call `lock()` when declared and `unlock()` when out of scope
- `std::unique_lock` is a general purpose mutex wrapper (suits all mutex types)
- The wrappers above can be used with `std::mutex`

## std::timed_mutex

- Same as `std::mutex` but it offers timing duration to wait for the mutex ownership by `try_lock_for()` and `try_lock_until()`
- Timed mutex is neither movable nor copyable
- It is used when we sometimes need to jump the lock of the mutex after a period of time

## std::recursive_mutex

- As all mutexes, it is used to protect shared data from being accessed at the same time
- It offers exclusive and recursive ownership of the mutex, i.e. when a thread owns a `recursive_mutex`, all other threads will be blocked when calling `lock()`
- Recursivity is satisfied by the fact that `lock()` or `try_lock()` can be called many times in the owner thread, and the mutex is released when `unlock()` is called as many times as `lock()` was called

## std::recursive_timed_mutex

- A recursive mutex with try-lock duration
- Use `try_lock_for()` and `try_lock_until()` to manage lock waiting timeout
- It is neither movable nor copyable

## std::shared_timed_mutex

- A new type of mutex, introduced in C++14
- Same as other mutexes, it aims to protect shared data from being accessed simultaneously by multiple threads
- It has two levels of access:
  - **Exclusive**: only one thread can own the mutex (using `lock()`, `try_lock()`, `try_lock_for()`...)
  - **Shared**: many threads can share ownership of the mutex (using `lock_shared()`, `try_lock_shared()`, `try_lock_shared_for()`...)
- Prefer plain `std::shared_mutex` (C++17) over `std::shared_timed_mutex` unless you need `_for`/`_until` — can be cheaper
- Reader-writer style only pays off for read-heavy data (e.g. a cache); profile before choosing it over a plain `std::mutex`

## Locking doesn't remove every race condition

- A mutex only stops threads from seeing a data structure *mid-update* — it doesn't make a multi-step interface safe by itself
- Classic trap: separate `empty()` / `top()` / `pop()` calls on a shared stack, each individually locked
  - Another thread can pop the last element between your `empty()` check and your `top()` call → `top()` on empty = undefined behavior
  - Two threads can both `top()` the same value before either `pop()`s → one value processed twice, the other silently dropped
  - Fix is at the interface level: combine "read and remove" into one locked call, e.g. `pop(T& value)` returning success/failure
- Rule of thumb: never let a pointer/reference to protected data escape the lock's scope — not returned, not stored elsewhere, not passed into a callback that might stash it

## Deadlock and how to avoid it

- **Deadlock**: thread A holds mutex 1 and waits for mutex 2, thread B holds mutex 2 and waits for mutex 1 — neither can proceed
- Avoidance, roughly in order of preference:
  - **Lock multiple mutexes together in one step**: `std::lock(m1, m2, ...)` or the RAII `std::scoped_lock` (C++17, preferred) — `std::scoped_lock guard(m1, m2);` can't deadlock even if another thread locks the same two mutexes in the opposite order
  - **Avoid nested locks**: a thread holding only one lock at a time can't lock-deadlock (though it can still deadlock other ways, e.g. two threads `join()`-ing each other)
  - **Avoid calling unknown/user-supplied code while holding a lock** — it might try to acquire a lock of its own
  - If locks must be acquired separately, **always acquire them in the same fixed order** on every thread; a *lock hierarchy* (each mutex gets a level, only lock strictly-lower levels than what you already hold) enforces this and can catch violations at runtime

## Lock granularity: hold locks for the minimum necessary time

- **Granularity** = how much data (and for how long) one lock protects
  - Too coarse (one mutex for everything) → kills concurrency even for unrelated data
  - Too fine → more bookkeeping and deadlock risk
- Regardless of granularity: only hold the lock for the operations that actually need protecting
  - Do expensive work (computation, and especially file/network I/O) *outside* the locked section
- `std::unique_lock` supports mid-scope `unlock()`/`lock()` — release the mutex during slow work, re-acquire only to commit the result

## Protecting one-time initialization: std::call_once

- Naive lazy init ("check a pointer, create it if null") under a mutex serializes *every* call just to protect a check needed only once
- "Double-checked locking" (check outside the lock, check again inside) looks like a fix but is a genuine data race — the outside-the-lock read isn't synchronized with the inside-the-lock write
- `std::once_flag` + `std::call_once(flag, init_function)`: any thread can call it, initializer runs exactly once, no thread proceeds past the call until init completes
- A function-local `static` variable has the same one-time thread-safe init guarantee since C++11 — simplest option for a single global/class-level instance

```cpp
// Trimmed excerpt — full runnable example: examples/course/03-cpp-standard-library/11-multithreading-and-synchronization/55_mutexes.cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <shared_mutex>

using namespace std::chrono_literals;

class ThreadRunner
{
public:
    ThreadRunner() : counter{0} 
    {}

    void resetCounter()
    {
        counter = 0;
    }

    // manual lock()/unlock() on a plain std::mutex
    void run(int threadId)
    {
        for (int i = 0; i < 3; i++)
        {
            mtx.lock();
            std::cout << "Got mutex for id " << threadId << " counter= " << counter++ << std::endl;
            mtx.unlock();
        }
    }
    // std::lock_guard: RAII wrapper, locks on construction and unlocks on scope exit
    void run2(int threadId)
    {
        for (int i = 0; i < 3; i++)
        {
            std::lock_guard<std::mutex> lk(mtx);
            std::cout << "Got lock_guard(mutex) for id " << threadId << " counter= " << counter++ << std::endl;
        }
    }
    // std::unique_lock + try_lock(): non-blocking attempt to acquire the mutex
    void run3(int threadId)
    {
        std::unique_lock<std::mutex> lk(mtx, std::defer_lock);
        for (int i = 0; i < 4; i++)
        {
            if (lk.try_lock())
            {
                std::cout << "Got unique_lock(mutex) for id " << threadId << " counter= " << counter++ << std::endl;
                lk.unlock();
            }
            else 
            {
                std::cout << "Failed to get unique_lock(mutex) for id " << threadId << std::endl;
            }
        }
    }
    void recFun1(int i)
    {
        std::lock_guard<std::recursive_mutex> lk(rmtx);
        sharedStr = std::to_string(i) + std::string("_rec1");
        std::cout << "Shared is " << sharedStr << std::endl; 
        recFun2(i);
    }
    void recFun2(int i)
    {
        // re-locking rmtx while the same thread already holds it: fine for recursive_mutex
        std::lock_guard<std::recursive_mutex> lk(rmtx);
        sharedStr = std::to_string(i) + std::string("_rec2");
        std::cout << "Shared is " << sharedStr << std::endl; 
    }
    void runRecursive(int i)
    {
        std::lock_guard<std::recursive_mutex> lk(rmtx);
        sharedStr = std::to_string(i) + std::string("_running");
        std::cout << "Shared is now " << sharedStr << std::endl; 
        recFun1(i);
    }
private:
    std::mutex mtx;
    std::recursive_mutex rmtx;
    int counter;
    std::string sharedStr;
};


int main()
{
    std::vector<std::thread> vect;
    ThreadRunner thd;

    std::cout << "************** using mutex****************" << std::endl;
    for (int i = 0; i < 3; i++)
        vect.emplace_back(&ThreadRunner::run, &thd, i);
    for (auto& t : vect) t.join();
    vect.clear();

    std::cout << "************** using lock_guard(mutex)****************" << std::endl; 
    thd.resetCounter();
    for (int i = 0; i < 3; i++)
        vect.emplace_back(&ThreadRunner::run2, &thd, i);
    for (auto& t : vect) t.join();
    vect.clear();

    std::cout << "************** using unique_lock(mutex) with try_lock****************" << std::endl;
    thd.resetCounter();
    for (int i = 0; i < 3; i++)
        vect.emplace_back(&ThreadRunner::run3, &thd, i);
    for (auto& t : vect) t.join();
    vect.clear();

    std::cout << "########################### timed_mutex ###############################" << std::endl;
    std::timed_mutex tmtx;
    int cnt{0};
    for (int i = 0; i < 3; i++)
    {
        vect.emplace_back([&i, &tmtx, &cnt]() {
            for (int j = 0; j < 4; j++)
            {
                std::unique_lock<std::timed_mutex> lk(tmtx, std::defer_lock);
                if (lk.try_lock_for(1ms))
                {
                    std::cout << "Got unique_lock(timed_mutex) for id " << i << " counter= " << cnt++ << std::endl;
                    lk.unlock();
                }
                else 
                {
                    std::cout << "Failed to get unique_lock(timed_mutex) for id " << i << std::endl;
                }
            }
        });
    }
    for (auto& t : vect) t.join();
    vect.clear();

    std::cout << "########################### recursive_mutex ###############################" << std::endl;
    std::thread timedThd1(&ThreadRunner::runRecursive, &thd, 1);
    std::thread timedThd2(&ThreadRunner::runRecursive, &thd, 2);
    timedThd1.join();
    timedThd2.join();
    
    std::cout << "########################### shared_timed mutex ###############################" << std::endl;
    std::shared_timed_mutex stmtx;
    /// run threads in exclusive mode: only one at a time can hold the lock
    for (int i = 0; i < 3; i++)
        vect.emplace_back([i, &stmtx]() {
            stmtx.try_lock_for(2s);
            std::cout << "Exclusive mode for thread " << i << std::endl;
            std::this_thread::sleep_for(500ms);
            stmtx.unlock();
        });
    std::this_thread::sleep_for(500ms);
    // shared mode: many threads may hold the lock at once, but not while exclusive is held
    if (stmtx.try_lock_shared_for(20ms))
    {
        std::cout << "Succeeded to get shared access" << std::endl;
        std::cout << (stmtx.try_lock() ? "Succeeded to get exclusive when shared is in progress" :
                                         "Failed to get exclusive when shared is in progress") << std::endl;
        std::thread th([&stmtx]() {
            if(stmtx.try_lock_shared())
            {
                std::cout << "Shared mode from thread" << std::endl;
                std::this_thread::sleep_for(500ms);
                stmtx.unlock_shared();
            }
            else 
            {
                std::cout << "Failed to get shared mode from thread" << std::endl;
            }
        });
        th.join();
        stmtx.unlock_shared();
    }
    else 
    {
        std::cout << "Failed to get shared access due to exclusive is already in prgress" << std::endl;
    }
    for (auto& t : vect) t.join();
    vect.clear();
    return 0;
}
```

