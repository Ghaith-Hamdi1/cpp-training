// Lesson 16: condition variable, a blocking SafeQueue, and a thread pool built from them. Compile with -pthread.
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

template <typename T>
class SafeQueue {
    std::queue<T> q_;
    std::mutex m_;
    std::condition_variable cv_;
public:
    void push(T v) {
        { std::lock_guard<std::mutex> lk(m_); q_.push(std::move(v)); }
        cv_.notify_one();                               // notify AFTER releasing the lock
    }
    T pop() {                                           // blocks until an item exists
        std::unique_lock<std::mutex> lk(m_);
        cv_.wait(lk, [this] { return !q_.empty(); });   // always wait with a predicate (spurious wakeups)
        T v = std::move(q_.front());
        q_.pop();
        return v;
    }
};

class ThreadPool {
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex m_;
    std::condition_variable cv_;
    bool stop_ = false;
public:
    explicit ThreadPool(std::size_t n) {
        for (std::size_t i = 0; i < n; ++i)
            workers_.emplace_back([this] {
                for (;;) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lk(m_);
                        cv_.wait(lk, [this] { return stop_ || !tasks_.empty(); });
                        if (stop_ && tasks_.empty()) return;     // finish remaining tasks, then exit
                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }                                            // lock released BEFORE running the task
                    task();
                }
            });
    }
    void submit(std::function<void()> f) {
        { std::lock_guard<std::mutex> lk(m_); tasks_.push(std::move(f)); }
        cv_.notify_one();
    }
    ~ThreadPool() {
        { std::lock_guard<std::mutex> lk(m_); stop_ = true; }    // request shutdown under the lock
        cv_.notify_all();                                        // wake every sleeping worker
        for (auto& w : workers_) w.join();
    }
};

int main() {
    SafeQueue<int> q;
    std::thread consumer([&] {
        for (;;) {
            int v = q.pop();
            if (v < 0) break;                           // negative value = shutdown signal
            std::cout << "consumed " << v << '\n';
        }
    });
    for (int i = 1; i <= 3; ++i) q.push(i);
    q.push(-1);
    consumer.join();

    std::mutex outM;
    int total = 0;
    {
        ThreadPool pool(4);
        for (int i = 1; i <= 100; ++i)
            pool.submit([&, i] { std::lock_guard<std::mutex> lk(outM); total += i; });
    }                                                   // destructor drains the queue and joins the workers
    std::cout << "pool summed 1..100 = " << total << '\n';
}
