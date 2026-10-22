// Lesson 16: shared_future, promise<void> as a signal, std::latch, std::barrier, counting_semaphore, jthread with a
// stop_token, and a parallel algorithm. Compile with -std=c++20 -pthread.
#include <atomic>
#include <barrier>
#include <chrono>
#include <execution>
#include <future>
#include <iostream>
#include <latch>
#include <numeric>
#include <semaphore>
#include <thread>
#include <vector>

int main()
{
    // promise<void>: a one-shot "go" signal to several waiters through a shared_future
    std::promise<void> go;
    std::shared_future<void> start = go.get_future().share();             // copyable: every worker gets its own handle
    std::atomic<int> started{0};
    std::vector<std::thread> ws;
    for (int i = 0; i < 4; ++i) ws.emplace_back([&] { start.wait(); ++started; });
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    std::cout << "before the signal, workers started: " << started << '\n';
    go.set_value();
    for (auto& w : ws) w.join();
    std::cout << "after set_value, workers started: " << started << '\n';

    // latch: a one-shot countdown ("wait until N things are done")
    std::latch done(3);
    std::atomic<int> work{0};
    std::vector<std::thread> ls;
    for (int i = 0; i < 3; ++i) ls.emplace_back([&] { ++work; done.count_down(); });
    done.wait();
    std::cout << "latch released after " << work << " tasks counted down\n";
    for (auto& l : ls) l.join();

    // barrier: reusable, all threads wait at the end of each phase
    std::atomic<int> phase1{0};
    bool ok = true;
    {
        std::barrier sync(3);
        std::vector<std::thread> bs;
        for (int i = 0; i < 3; ++i) bs.emplace_back([&] {
            ++phase1;
            sync.arrive_and_wait();                                       // nobody starts phase 2 until all finished phase 1
            if (phase1 != 3) ok = false;
        });
        for (auto& b : bs) b.join();
    }
    std::cout << "barrier: every thread saw all 3 phase-1 results before phase 2: " << std::boolalpha << ok << '\n';

    // counting_semaphore: at most 2 threads inside at once
    std::counting_semaphore<4> slots(2);
    std::atomic<int> inside{0}, peak{0};
    std::vector<std::thread> ss;
    for (int i = 0; i < 6; ++i) ss.emplace_back([&] {
        slots.acquire();
        int n = ++inside;
        int p = peak.load();
        while (n > p && !peak.compare_exchange_weak(p, n)) {}
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        --inside;
        slots.release();
    });
    for (auto& s : ss) s.join();
    std::cout << "semaphore(2): at most " << peak << " threads were inside at once\n";

    // jthread + stop_token: cooperative cancellation, joins on destruction
    std::atomic<int> ticks{0};
    {
        std::jthread j([&](std::stop_token st) { while (!st.stop_requested()) { ++ticks; std::this_thread::sleep_for(std::chrono::milliseconds(2)); } });
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }                                                                     // destructor: request_stop() then join()
    std::cout << "jthread stopped by its destructor after " << (ticks > 0 ? "some" : "no") << " ticks\n";

    // a parallel algorithm (runs serially if the standard library has no parallel backend)
    std::vector<int> v(1000);
    std::iota(v.begin(), v.end(), 1);
    long long sum = std::reduce(std::execution::par, v.begin(), v.end(), 0LL);
    std::cout << "reduce(par) of 1..1000 = " << sum << '\n';
}
