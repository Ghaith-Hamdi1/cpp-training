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

```cpp
// Source: Examples/03_CPP_Standard_Library/11_multithreading_and_synchronization/56_condition_variable.cpp
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

    // waiting threads without shared variable
    for (int i = 0; i < 10; i++)
    {
        threads.emplace_back([&cv, &mtx, i]() {
            std::cout << "Thread " << i << " waiting" << std::endl;
            std::unique_lock<std::mutex> lk(mtx);
            std::cout << "Thread " << i << " aquired mutex" << std::endl;
            cv.wait(lk);

            std::cout << "Thread " << i << " exited" << std::endl;
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));
    cv.notify_one();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cv.notify_one();
    std::this_thread::sleep_for(std::chrono::seconds(2));

    cv.notify_all();
    for (int i = 0; i < 10; i++)
    {
        threads[i].join();
    }


    /// sample with shared variable
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
        cond_var.notify_one();
        std::this_thread::sleep_for(std::chrono::seconds(10));
        lk.lock();
        launched = true;
        lk.unlock();
        cond_var.notify_one();

        std::unique_lock<std::mutex> lk2(smtx);
        cond_var.wait_for(lk2, std::chrono::milliseconds(200), [&processed]() {
            return processed;
        });
        std::cout << "Shared data state " << shared_data << std::endl;
    });

    std::unique_lock<std::mutex> lk(smtx);
    // wait thread to be launched
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

