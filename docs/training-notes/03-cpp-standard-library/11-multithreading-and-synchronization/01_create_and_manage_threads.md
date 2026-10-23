# Create and manage threads

- `std::thread` used to create standard threads. It allows running multiple functions concurrently
- Threads begin immediately upon construction
- If an exception is thrown within a thread, `std::terminate` is called
- Promise and Future mechanism is used to communicate with the caller (return value or handled exceptions)
- Mutexes and atomic variables are used to manage concurrent access for shared data
- Important: a thread must be joined by calling `join()` (blocking until processing is finished) OR detached using `detach()` so that the thread remains running separately until self destruction (thread function exits)
- If a thread is detached, the thread handle is no longer valid

## Why join-or-detach is mandatory

- `std::thread` owns a real OS resource — a running thread of execution
- If its `std::thread` object is destroyed while still joinable (neither `join()` nor `detach()` called), the destructor calls `std::terminate()` and the program aborts — a deliberate hard failure, not a silent leak
- The decision doesn't have to happen immediately — the thread can finish long before you actually call `join()` — but it must have *happened* before the `std::thread` object's own destructor runs
- `detach()` hands the thread to the C++ runtime as a background ("daemon") thread: no more waiting on it, observing completion, or joining it later — `joinable()` becomes `false` right after

## The dangling-reference trap with detached threads

- A detached thread capturing a reference/pointer to a local variable is dangerous if the enclosing function can return first:

```cpp
void oops() {
    int some_local_state = 0;
    std::thread t([&some_local_state]() {
        // if oops() has already returned by the time this runs,
        // some_local_state no longer exists: undefined behavior
        do_something(some_local_state);
    });
    t.detach();
} // some_local_state is destroyed here, but the thread may still be running
```

- Same "don't return a reference to a local" rule as single-threaded code — but timing-dependent, so much easier to trigger by accident
- Avoid it by:
  - Copying data into the thread instead of referencing it (pass by value, or `std::move` ownership of something like a `std::unique_ptr`)
  - `join()`-ing before the enclosing scope exits, instead of `detach()`-ing, if the thread must reference local state

## RAII thread guard: never forget to join

- An exception thrown between starting a thread and its planned `join()` skips the `join()` → `std::terminate()`
- Common fix: wrap the thread in a small RAII guard that joins in its destructor, same idea as `std::lock_guard` for mutexes:

```cpp
class thread_guard {
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_) : t(t_) {}
    ~thread_guard() {
        if (t.joinable()) t.join();
    }
    thread_guard(const thread_guard&) = delete;
    thread_guard& operator=(const thread_guard&) = delete;
};
```

- Copying is deleted — a copy could outlive the thread it's meant to join
- Joins whether the function returns normally or via an exception
- C++20 standardizes essentially this idea as `std::jthread` (auto-joins, plus cooperative cancellation)

## Passing arguments: values are copied, not referenced, by default

- `std::thread` arguments are copied into internal storage and passed to the callable as temporaries — even if the target expects a reference
- That's why the code below wraps `a` in `std::ref(a)`:
  - Without it, `operator()(const A&)` would still compile (a const ref can bind to the copy), but silently operate on a *copy*
  - A non-const reference parameter meant to mutate the caller's object simply wouldn't compile without `std::ref`
- Same reason `std::ref(x)` is used for `ths1`/`ths2` below — it's what makes both threads see and decrement the *same* `x` rather than independent copies
- Still need a mutex/atomic on top of that if more than one thread can mutate the same shared variable concurrently

## Choosing how many threads to use

- `std::thread::hardware_concurrency()` hints at how many threads can truly run in parallel (often the core count); may return `0` if unknown — fall back to a sensible default (e.g. `2`)
- Running far more threads than this ("oversubscription") adds context-switching overhead, not real parallelism
- Use it as an upper bound when splitting work, not as "one thread per data item"

## Identifying threads

- `std::thread::id`: from `get_id()` on the thread object, or `std::this_thread::get_id()` from inside the running thread
- Comparable, orderable, hashable — usable as map keys, or to let a thread recognize "am I the one that started this work?"
- The value itself has no meaning beyond equality/ordering — don't treat it as an index or count

```cpp
// Trimmed excerpt — full runnable example: examples/course/03-cpp-standard-library/11-multithreading-and-synchronization/53_multithreading.cpp
#include <iostream>
#include <thread>
#include <chrono>

/// !!! Need to be executed using compile flag -lpthread (to link threads library of linux)

using namespace std::chrono_literals;

class A
{
public:
    explicit A(int x) : m_x{x} {}

    A(const A& a) : m_x{a.m_x}
    {
        std::cout << "Copy Constructor" << std::endl;
    }
    virtual ~A() = default;
    int getX() const
    {
        return m_x;
    }
private:
    int m_x;
};

class ThreadHandler
{
public:
    void run()
    {
        std::cout << "Run thread from class member function" << std::endl;
    }

    void operator()(int x)
    {
        while (x >= 0)
        {
            std::cout << "Running thread with counter " << x << std::endl;
            x--;
            std::this_thread::sleep_for(100ms);
        }
    }
    void operator()(int &x, int id)
    {
        while (x >= 0)
        {
            std::cout << "Running thread id=" << id << " with counter " << x << std::endl;
            x--;
            std::this_thread::sleep_for(100ms);
        }
    }

    void operator()(const A& a)
    {
        int x = a.getX();
        while (x >= 0)
        {
            std::cout << "Running thread with A reference " << x << std::endl;
            x--;
            std::this_thread::sleep_for(100ms);
        }
    }
};

int main()
{
    int capture{10};
    std::thread th1; // not a thread, just declared
    std::cout << "th1 is " << (th1.joinable() ? "joinable" : "not joinable") << std::endl;
    th1 = std::thread([&capture]() { // use lambda and move assignment operator
        std::cout << "Running thread from lambda with capture value " << capture << std::endl;
        capture = 20;
    });
    std::cout << "th1 is now " << (th1.joinable() ? "joinable" : "not joinable") << " with id=0x" << std::hex << th1.get_id() << std::dec << std::endl;
    if (th1.joinable())
    {
        th1.join();
    }

    std::thread th2(ThreadHandler(), 3); // thread created and launched, argument passed by value
    A a(10);
    // std::ref(a) is required: thread arguments are copied by default, and operator()(const A&)
    // would otherwise silently run on a COPY of a (no "Copy Constructor" print without std::ref)
    std::thread th3(ThreadHandler(), std::ref(a));
    if (th2.joinable())
    {
        th2.join();
    }
    if (th3.joinable())
    {
        th3.join();
    }

    ThreadHandler threadHandler;
    std::thread th4(&ThreadHandler::run, &threadHandler); // running a thread on a member function
    th4.detach(); // no problem since run will exit (no infinite loop)

    // two threads sharing the same variable via std::ref, so both see/decrement the same x
    int x = 3;
    std::thread ths1(ThreadHandler(), std::ref(x), 1);
    std::thread ths2(ThreadHandler(), std::ref(x), 2);
    if (ths1.joinable())
    {
        ths1.join();
    }
    if (ths2.joinable())
    {
        ths2.join();
    }

    // an uncaught exception inside a thread function calls std::terminate
    std::thread thex([]() { throw std::runtime_error("RUNTIME ERROR!");});
    if (thex.joinable())
    {
        thex.join();
    }
    return 0;
}
```

