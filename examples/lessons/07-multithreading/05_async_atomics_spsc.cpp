// Lesson 15: futures and async (results and exceptions), promise, packaged_task, release/acquire publishing,
// compare_exchange, a single-producer single-consumer lock-free ring buffer. Compile with -pthread.
#include <atomic>
#include <chrono>
#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>

int slowSquare(int n) { std::this_thread::sleep_for(std::chrono::milliseconds(50)); return n * n; }
int failing() { throw std::runtime_error("task failed"); }

template <typename T, std::size_t N>
class SpscQueue {
    T buf_[N];
    std::atomic<std::size_t> head_{0};                  // next slot to read: written ONLY by the consumer
    std::atomic<std::size_t> tail_{0};                  // next slot to write: written ONLY by the producer
public:
    bool push(const T& v) {                             // producer thread only
        auto t = tail_.load(std::memory_order_relaxed);
        auto next = (t + 1) % N;
        if (next == head_.load(std::memory_order_acquire)) return false;   // full
        buf_[t] = v;                                    // write the data...
        tail_.store(next, std::memory_order_release);   // ...then publish it
        return true;
    }
    bool pop(T& out) {                                  // consumer thread only
        auto h = head_.load(std::memory_order_relaxed);
        if (h == tail_.load(std::memory_order_acquire)) return false;      // empty
        out = buf_[h];
        head_.store((h + 1) % N, std::memory_order_release);               // free the slot
        return true;
    }
};

int main() {
    std::future<int> f = std::async(std::launch::async, slowSquare, 7);   // runs on another thread
    std::cout << "main keeps working while the task runs\n";
    std::cout << "result: " << f.get() << '\n';                           // waits if needed

    std::future<int> bad = std::async(std::launch::async, failing);
    try { bad.get(); } catch (const std::exception& e) { std::cout << "exception travelled with the result: " << e.what() << '\n'; }

    std::promise<int> p;                                // a one-shot channel between two threads
    std::future<int> pf = p.get_future();
    std::thread t([&p] { p.set_value(42); });
    std::cout << "promise delivered " << pf.get() << '\n';
    t.join();

    std::packaged_task<int(int)> task(slowSquare);      // how thread pools hand results back
    std::future<int> tf = task.get_future();
    std::thread t2(std::move(task), 9);
    std::cout << "packaged_task result " << tf.get() << '\n';
    t2.join();

    int data = 0;
    std::atomic<bool> ready{false};
    std::thread producer([&] { data = 42; ready.store(true, std::memory_order_release); });
    while (!ready.load(std::memory_order_acquire)) {}   // acquire pairs with the release store
    std::cout << "published data = " << data << " (guaranteed 42)\n";
    producer.join();

    std::atomic<int> counter{3};
    int expected = counter.load();
    while (!counter.compare_exchange_weak(expected, expected * 2)) {}   // retry if someone changed it
    std::cout << "compare_exchange doubled it to " << counter.load() << '\n';

    SpscQueue<int, 1024> q;
    long long sum = 0;
    std::thread prod([&] { for (int i = 1; i <= 100000; ++i) while (!q.push(i)) {} });   // spin while full
    std::thread cons([&] { int v; for (int n = 0; n < 100000; ) if (q.pop(v)) { sum += v; ++n; } });
    prod.join(); cons.join();
    std::cout << "SPSC queue delivered sum " << sum << " (expected 5000050000)\n";
}
