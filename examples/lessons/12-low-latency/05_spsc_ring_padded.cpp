// Lesson 12: a single-producer single-consumer ring buffer with a power-of-two capacity (index mask instead of %),
// padded indices (no false sharing) and a drop policy when full. Compile with -std=c++20 -pthread.
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <thread>

template <typename T, std::size_t N>
class SpscRing {
    static_assert((N & (N - 1)) == 0 && N >= 2, "capacity must be a power of two");
    static constexpr std::size_t kMask = N - 1;
    T buf_[N];
    alignas(64) std::atomic<std::size_t> head_{0};              // next slot to read: written only by the consumer
    alignas(64) std::atomic<std::size_t> tail_{0};              // next slot to write: written only by the producer
public:
    bool tryPush(const T& v)                                    // producer thread only
    {
        const auto t = tail_.load(std::memory_order_relaxed);
        if (t - head_.load(std::memory_order_acquire) == N) return false;   // full: caller decides what to do
        buf_[t & kMask] = v;                                    // free-running counters; the mask wraps the index
        tail_.store(t + 1, std::memory_order_release);
        return true;
    }
    bool tryPop(T& out)                                         // consumer thread only
    {
        const auto h = head_.load(std::memory_order_relaxed);
        if (h == tail_.load(std::memory_order_acquire)) return false;       // empty
        out = buf_[h & kMask];
        head_.store(h + 1, std::memory_order_release);
        return true;
    }
    std::size_t size() const { return tail_.load(std::memory_order_acquire) - head_.load(std::memory_order_acquire); }
};

int main()
{
    SpscRing<int, 4> ring;                                      // 4 slots: the wrap-around is easy to see
    int v = 0;
    std::cout << "push 10,20,30: " << ring.tryPush(10) << ring.tryPush(20) << ring.tryPush(30) << '\n';
    std::cout << "pop " << (ring.tryPop(v), v) << '\n';
    std::cout << "push 40,50 (wraps around): " << ring.tryPush(40) << ring.tryPush(50) << ", size " << ring.size() << '\n';
    std::cout << "push 60 when full: " << std::boolalpha << ring.tryPush(60) << " (refused; the policy decides)\n";
    std::cout << "drained:";
    while (ring.tryPop(v)) std::cout << ' ' << v;
    std::cout << '\n';

    // two real threads; the producer DROPS a message when the ring is full instead of waiting (a "drop newest" policy)
    static SpscRing<std::uint64_t, 1024> big;
    constexpr std::uint64_t kMessages = 200000;
    std::uint64_t dropped = 0, received = 0, sum = 0, sentSum = 0;     // each written by ONE thread, read after join
    std::atomic<bool> done{false};                              // the producer says: I have pushed everything
    std::thread producer([&] {
        for (std::uint64_t i = 1; i <= kMessages; ++i) {
            if (big.tryPush(i)) sentSum += i; else ++dropped;
        }
        done.store(true, std::memory_order_release);
    });
    std::thread consumer([&] {
        std::uint64_t x = 0;
        while (true) {
            if (big.tryPop(x)) { sum += x; ++received; continue; }
            if (done.load(std::memory_order_acquire)) {          // all pushes are visible now: drain what is left
                if (big.tryPop(x)) { sum += x; ++received; continue; }
                break;
            }
        }
    });
    producer.join();
    consumer.join();
    std::cout << "received + dropped = " << (received + dropped) << " of " << kMessages << ", consumer sum equals producer sum: " << (sum == sentSum) << '\n';
}
