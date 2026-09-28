#include <iostream>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <array>
#include <atomic>

int main()
{
   std::array<std::thread, 10> threads;
   std::condition_variable cv;
   std::condition_variable cv_sync;
   std::mutex mtx;
   std::mutex mtx_sync;
   std::atomic_int current_tread{0};

    for (int i = 0; i < threads.size(); i++)
    {
        threads[i] = std::thread([&](int threadId){
            std::unique_lock<std::mutex> lk(mtx);
            cv.wait(lk, [threadId, &current_tread]{
                return (threadId == current_tread);
            });
            std::cout << "Run thread " << threadId << std::endl;
            std::this_thread::sleep_for(std::chrono::microseconds(500));
            cv_sync.notify_one();
        }, i);
    }
    // manage the current thread
    for (int i = 0; i < threads.size(); i++)
    {
        cv.notify_all();
        std::unique_lock<std::mutex> lk(mtx_sync);
        cv_sync.wait(lk);
        std::cout << "Increment current thread " << current_tread << std::endl;
        current_tread++;
    }
    for (int i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }


    return 0;
}