# Condition variables

- A condition variable is a synchronization primitive used with `std::mutex` to block one or many threads until another one modifies a shared variable and notifies one or all of them to continue (allow them to continue)
- Even if the shared variable can be atomic, it must be modified while owning the mutex to correctly publish the modification to waiting threads
- If no shared variable needs to be modified, `condition_variable` can be used as a synchronization tool between threads (some threads are waiting for a processing to be done, signaled when calling `notify_one` or `notify_all`)
- Steps for the thread that wants to modify the shared variable:
  - Acquire a mutex (get ownership)
  - Modify shared variable
  - Call `notify_one()` or `notify_all()`
- Steps for threads that intend to wait on the condition variable:
  - Acquire `unique_lock` of mutex (same one used to protect shared variable)
  - Call `wait()`, `wait_for()` or `wait_until()`
  - Check if notified (in case of timeout) and continue processing

## Why not just poll a flag?

- Naive alternative: loop that locks a mutex, checks a flag, unlocks, sleeps a bit, repeats
  - Sleep too little → waiting thread burns CPU and keeps contending for the mutex, getting in the way of the thread trying to set the flag
  - Sleep too long → needless latency after the condition actually becomes true
- `condition_variable::wait()` is a well-implemented version of that same loop, handled by the library/OS scheduler instead of a hand-rolled sleep — zero CPU while blocked, woken close to immediately on `notify_one()`/`notify_all()`

## Why `wait()` needs a `unique_lock`, not a `lock_guard`

- `wait()` must unlock the mutex before blocking (otherwise no other thread could lock it to modify the shared state and notify), then re-lock it before returning
- `std::lock_guard` only locks once (construction) and unlocks once (destruction) — can't do that
- `std::unique_lock` can lock/unlock mid-scope, which is why `wait()` requires it

## Spurious wakeups and why you always pass a predicate

- A thread can wake from `wait()` even when nobody called `notify_one()`/`notify_all()` — a **spurious wakeup**, explicitly permitted by the standard (a conforming `wait()` can legally be just a relock-and-recheck loop)
- The predicate form `cv.wait(lk, []{ return condition; })` re-checks the real condition on *every* wake (real notification, spurious wakeup, or another thread beating you to it) and only returns once it actually holds — always prefer it over the bare `cv.wait(lk)`
- The predicate can be evaluated any number of times — avoid side effects in it

## notify_one vs notify_all, and std::condition_variable_any

- `notify_one()`: wakes at most one waiting thread — for interchangeable workers pulling from the same queue, where it doesn't matter which one goes next
- `notify_all()`: wakes every waiting thread, each re-checking its own predicate — for a shared state change (e.g. "setup is ready") that *all* waiters need to react to
- `std::condition_variable` only works with `std::mutex`/`std::unique_lock<std::mutex>`
- `std::condition_variable_any` is a more general, slightly more expensive version for any lock type meeting the basic mutex requirements — only reach for it if you need that flexibility

A very common real use: a thread-safe producer/consumer queue — producers lock, push, `notify_one()`; consumers lock and `wait()` on `!queue.empty()`, blocking at zero CPU cost until there's something to process.

```cpp
// Trimmed excerpt — full runnable example: examples/03-cpp-standard-library/11-multithreading-and-synchronization/56_condition_variable.cpp
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>

int main()
{
    std::vector<std::thread> threads;
    std::mutex mtx;
    std::condition_variable cv;

    // threads blocked on a bare wait() (no predicate), used here as a pure signal
    for (int i = 0; i < 3; i++)
    {
        threads.emplace_back([&cv, &mtx, i]() {
            std::cout << "Thread " << i << " waiting" << std::endl;
            std::unique_lock<std::mutex> lk(mtx);
            cv.wait(lk);
            std::cout << "Thread " << i << " exited" << std::endl;
        });
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    cv.notify_one(); // wakes only one waiting thread
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    cv.notify_all(); // wakes every remaining waiting thread
    for (int i = 0; i < 3; i++)
    {
        threads[i].join();
    }


    /// sample with shared variable and predicate-based wait
    std::condition_variable cond_var;
    std::mutex smtx;

    std::string shared_data{"Initial state"};
    bool launched{false};
    bool processed{false};

    std::thread worker([&launched, &shared_data, &smtx, &cond_var, &processed](){
        // lock mutex to update shared data
        std::unique_lock<std::mutex> lk(smtx);
        std::cout << "Worker launched" << std::endl;
        lk.unlock();
        cond_var.notify_one(); // early notify: 'launched' is still false, so main's predicate keeps it waiting
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        lk.lock();
        launched = true;
        lk.unlock();
        cond_var.notify_one(); // this time the predicate is satisfied

        std::unique_lock<std::mutex> lk2(smtx);
        // predicate form of wait_for: re-checks 'processed' on every wake, immune to spurious wakeups
        cond_var.wait_for(lk2, std::chrono::milliseconds(200), [&processed]() {
            return processed;
        });
        std::cout << "Shared data state " << shared_data << std::endl;
    });

    std::unique_lock<std::mutex> lk(smtx);
    // wait for the worker to be launched
    cond_var.wait(lk, [&launched]{ return launched; });
    std::cout << "Main resumed" << std::endl;
    shared_data += " processed";
    processed = true;
    lk.unlock();
    cond_var.notify_one();

    worker.join();
    
    return 0;
}
```

