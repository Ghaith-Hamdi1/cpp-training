# Futures and promises

- Futures and promises provide a facility to provide data from a thread to another (or to the caller) that can be acquired later asynchronously
- Future and promise are linked together: promise is used to set the data that will be passed, and a future generated from the promise is used to get that data (in the future :D)
- The data held by promise is called the "shared state"
- So, promise is used to set the shared state and generate a future that will be used to get the shared state
- `std::promise<T>` where `T` is the type of shared state (can be `void` as well)
  - `set_value()` used to set the shared state value
  - `set_exception()` used to set the shared state as an exception
  - `get_future()` returns the associated future
  - Important: a promise is intended to be used only once
- `std::future<T>` where `T` is the type of the shared state, must be the same as the type of the promise
  - It can be retrieved from `std::promise`, `std::async` or `std::packaged_task`
  - Its shared state has to be in a valid state before use (or undefined behavior)
  - A valid shared state means that the future is associated to a promise, or the `get()` function has not been called to retrieve the shared state value
  - Can use wait functions to wait for the shared state to have a value (set by the promise)
  - `get()` function waits until the shared state is ready before returning
  - `valid()` checks if the shared state is valid
- `std::shared_future<T>` is the same as `std::future`, however it can be shared by many threads (unlike future, which is not copyable but only movable)
  - All `shared_future` instances point to the same shared state
- `std::async`: runs a function asynchronously (like threads) and returns `std::future` having the type of the return value of the function
  - It can be launched immediately with `std::launch::async`
  - It can be launched when the result is claimed (waiting for future result) using `std::launch::deferred`
  - By default, launch is immediate
- `std::packaged_task` is a wrapper of a callable target (function, lambdas, function object/functor, bind expression)
  - The call of `operator()` of `packaged_task` is blocking, but it can be converted to `std::thread` to be run asynchronously (by moving the packaged task as per the thread function)
  - The use of `packaged_task` is mostly to handle threads with return value (retrieved by `get_future()` before moving the packaged task to a thread)

## Choosing between async, packaged_task and promise

All three produce a `std::future`, but fit different situations:
- **`std::async`**: "run this callable somewhere, give me its result (or exception) later" — no manual thread management needed
- **`std::packaged_task`**: ties a future to a callable without deciding *how/when* it runs — you invoke it yourself (directly, on a `std::thread`, or via a task queue/thread pool). Right tool when you control the execution mechanism, e.g. queuing work for one dedicated worker thread instead of spawning a thread per task
- **`std::promise`**: lowest-level of the three — set the value/exception explicitly from wherever it becomes available. Needed when the result doesn't come from one self-contained function call, e.g. arriving via a callback, I/O completion, or network event

## std::async launch policies

`std::async` takes an optional `std::launch` policy as its first argument:
- `std::launch::async` — forces the callable onto its own new thread immediately
- `std::launch::deferred` — postpones the call until `.wait()`/`.get()` is called on the future; if neither is ever called, it may never run
- `std::launch::async | std::launch::deferred` (default) — implementation picks either strategy; convenient, but you can't rely on actual concurrency unless you explicitly request `std::launch::async`

## What happens if a promise is never fulfilled

- If a `std::promise`/`std::packaged_task` is destroyed without `set_value()`/`set_exception()` (or the task never invoked) while its future is still unconsumed, the library stores a `std::future_error` (`std::future_errc::broken_promise`) into the shared state
- A thread waiting on `get()` then fails with an exception instead of blocking forever
- Treat this as a safety net, not a design crutch: always set a value or exception on every code path, including error paths

```cpp
// Trimmed excerpt — full runnable example: examples/03-cpp-standard-library/11-multithreading-and-synchronization/57_promise_future.cpp
#include <iostream>
#include <future>
#include <thread>
#include <functional>

using namespace std::placeholders;

class Test
{
public:
    void operator()(int x, int y)
    {
        std::cout << "Operator() X=" << x << " Y=" << y << std::endl;
    }
};

int main()
{
    // basic promise/future: get_future(), valid(), wait(), get(), set_value()
    std::promise<int> i_promise;
    std::future<int> i_future;
    std::cout << "Not assigned future is " << (i_future.valid() ? "valid" : "invalid") << std::endl;
    i_future = i_promise.get_future();
    std::cout << "Future is now " << (i_future.valid() ? "valid" : "invalid") << std::endl;
    std::thread th1([&i_promise]()
                    {
        std::cout << "Thread th1 launched" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        i_promise.set_value(0); });

    i_future.wait(); // blocking call
    std::cout << "Future is ready and the retrieved value is " << i_future.get() << " and after get the shared state is now "
              << (i_future.valid() ? "valid" : "invalid") << std::endl;

    // a promise/future pair is single-use: setting/getting a second time throws
    try
    {
        i_promise.set_value(2);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception raised for promise set: " << e.what() << std::endl;
    }
    try
    {
        i_future.get();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception raised for future get: " << e.what() << std::endl;
    }
    th1.join();

    // std::future cannot be waited on from many threads; std::shared_future can, and is copyable
    std::promise<int> v_promise;
    std::shared_future<int> vs_future1 = v_promise.get_future();
    std::shared_future<int> vs_future2{vs_future1}; // a copy of the shared_future itself

    std::thread th2([&vs_future1]()
                    {
        std::cout << "Th2 is launched" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "Th2 finished " << vs_future1.valid() 
            << " value " << vs_future1.get() << std::endl; });
    std::thread th3([&vs_future2]()
                    {
        std::cout << "Th3 is launched" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        std::cout << "Th3 finished " << vs_future2.valid() 
        << " value " << vs_future2.get() << std::endl; });
    std::cout << "Set promise for shared futures" << std::endl;
    v_promise.set_value(51);

    th2.join();
    th3.join();

    // propagating an exception from a thread through promise/future via set_exception()
    std::promise<int> e_pr;
    std::future<int> e_ft = e_pr.get_future();

    std::thread eTh([&e_pr]() {
        try
        {
            // some processing that throws an exception
            throw std::runtime_error("This is an exception");
        }
        catch (...)
        {
            e_pr.set_exception(std::current_exception()); // std::exception_ptr
    } });

    try
    {
        e_ft.wait();
        int value = e_ft.get();
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception thrown from thread " << e.what() << std::endl;
    }
    eTh.join();

    std::cout << std::endl
              << "############### std::async #################" << std::endl;
    std::promise<void> launch_pr;
    std::future<void> launch_ft = launch_pr.get_future();
    std::future<int> async_ret_future = std::async([&launch_pr]()
                                                   {
        int x{0};
        launch_pr.set_value();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        return x; });
    // wait for the thread to be launched (default/std::launch::async runs it immediately)
    launch_ft.get();
    std::cout << "Thread is launched" << std::endl;
    std::cout << "Thread returned value " << async_ret_future.get() << std::endl;

    // std::launch::deferred: the callable only runs once the future is waited on/gotten
    std::promise<void> launch_pr_d;
    std::future<void> launch_ft_d = launch_pr_d.get_future();
    std::future<int> async_ret_future_d = std::async(std::launch::deferred, [&launch_pr_d]()
                                                     {
        int x{10};
        launch_pr_d.set_value();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        return x; });
    // wait for the thread to be launched, won't happen since the result is not claimed
    std::cout << "Wait for deferred thread to be launched" << std::endl;
    std::future_status sts = launch_ft_d.wait_for(std::chrono::milliseconds(300));
    if (sts != std::future_status::ready)
    {
        std::cout << "Wait for deferred thread start, result is " << (sts == std::future_status::deferred ? " deferred" : " timed out") << std::endl;
    }
    // claiming the result is what actually starts the deferred call
    int res = async_ret_future_d.get();
    std::cout << "Wait for deferred thread start, result is " << res << std::endl;

    std::cout << std::endl
              << "############### std::packaged_task #################" << std::endl;
    auto lambda = []()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "Packaged task returned" << std::endl;
        return 1;
    };

    // calling operator() on a packaged_task is a blocking, synchronous call
    std::packaged_task<void(void)> ptsk(lambda);
    ptsk();

    // converting a packaged_task to a std::thread runs it asynchronously;
    // get_future() must be called before the task is moved into the thread
    std::packaged_task<int(void)> ptsk2(lambda);
    auto ft2 = ptsk2.get_future();
    std::thread pkg_thread(std::move(ptsk2));
    pkg_thread.join();
    std::cout << "Thread result is " << ft2.get() << std::endl;

    // packaged_task can also wrap a bind expression: std::bind(Test(), 2, _1) becomes operator()(2, y)
    std::packaged_task<void(int)> ptsk3(std::bind(Test(), 2, _1));
    ptsk3(10);

    return 0;
}
```

---

