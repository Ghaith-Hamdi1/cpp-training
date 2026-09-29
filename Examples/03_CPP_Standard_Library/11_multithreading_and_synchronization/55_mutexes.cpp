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
    
    void run(int threadId)
    {
        for (int i = 0; i < 10; i++)
        {
            mtx.lock();
            std::cout << "Got mutex for id " << threadId << " counter= " << counter++ << std::endl;
            mtx.unlock();
        }
    }
    void run2(int threadId)
    {
        for (int i = 0; i < 10; i++)
        {
            std::lock_guard<std::mutex> lk(mtx);
            std::cout << "Got lock_guard(mutex) for id " << threadId << " counter= " << counter++ << std::endl;
        }
    }
    void run3(int threadId)
    {
        std::unique_lock<std::mutex> lk(mtx, std::defer_lock);
        for (int i = 0; i < 10; i++)
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
        std::this_thread::sleep_for(500ms);
    }
    void recFun2(int i)
    {
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
    for (int i = 0; i < 10; i++)
    {
        vect.emplace_back(&ThreadRunner::run, &thd, i);
    }

    for (int i = 0; i < 10; i++)
    {
        vect[i].join();
    }
    vect.clear();
    
    std::cout << "************** using lock_guard(mutex)****************" << std::endl; 
    thd.resetCounter();
    for (int i = 0; i < 10; i++)
    {
        vect.emplace_back(&ThreadRunner::run2, &thd, i);
    }

    for (int i = 0; i < 10; i++)
    {
        vect[i].join();
    }
    vect.clear();
    std::cout << "************** using unique_lock(mutex)****************" << std::endl;
    thd.resetCounter();
    for (int i = 0; i < 3; i++)
    {
        vect.emplace_back(&ThreadRunner::run3, &thd, i);
    }

    for (int i = 0; i < vect.size(); i++)
    {
        vect[i].join();
    }
    vect.clear();

    std::cout << "########################### timed_mutex ###############################" << std::endl;
    std::timed_mutex tmtx;
    int cnt{0};
    for (int i = 0; i < 3; i++)
    {
        vect.emplace_back([&i, &tmtx, &cnt]() {
            for (int j = 0; j < 10; j++)
            {
                std::unique_lock<std::timed_mutex> lk(tmtx, std::defer_lock);
                if (lk.try_lock_for(1ms))
                {
                    std::cout << "Got unique_lock(timed_mutex) for id " << i << " counter= " << cnt++ << std::endl;
                    lk.unlock();
                }
                else 
                {
                    std::cout << "Failed to get unique_lock(timed_mutex) for id " << i << " counter= " << cnt++ << std::endl;
                }
            }
        });
    }

    for (int i = 0; i < 3; i++)
    {
        vect[i].join();
    }
    vect.clear();

    std::cout << "########################### recursive_mutex ###############################" << std::endl;
    std::thread timedThd1(&ThreadRunner::runRecursive, &thd, 1);
    std::thread timedThd2(&ThreadRunner::runRecursive, &thd, 2);
    timedThd1.join();
    timedThd2.join();
    
    std::cout << "########################### shared_timed mutex ###############################" << std::endl;
    std::shared_timed_mutex stmtx;
    /// run threads in exclusive mode
    for (int i = 0; i < 3; i++)
    {
        vect.emplace_back([i, &stmtx]() {
            stmtx.try_lock_for(2s);
            std::cout << "Exclusive mode for thread " << i << std::endl;
            std::this_thread::sleep_for(500ms);
            stmtx.unlock();
        });
    }
    std::this_thread::sleep_for(500ms);
    // try to get access using shared mode
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
    for (int i = 0; i < vect.size(); i++)
    {
        vect[i].join();
    }
    vect.clear();
    return 0;
}