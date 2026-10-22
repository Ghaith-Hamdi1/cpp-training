// Exercise 14: a bounded blocking queue (producer/consumer with back-pressure). Compile with -pthread.
//
// BoundedQueue<T> holds at most `capacity` items.
//   void push(T value)   blocks while the queue is FULL, then adds the value
//   T pop()              blocks while the queue is EMPTY, then removes and returns the oldest value
//   std::size_t size()   the current number of items
// Use one mutex and TWO condition variables (notFull, notEmpty). Wait with a predicate, change the
// queue only while holding the lock, and notify after releasing it.
// Why bounded? A feed handler that cannot keep up must slow the producer down (or drop data)
// instead of letting memory grow without limit.
#include <cstddef>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include "../check.h"

template <typename T>
class BoundedQueue {
    std::queue<T> q_;
public:
    explicit BoundedQueue(std::size_t capacity) { (void)capacity; }
    void push(T value) { q_.push(std::move(value)); }          // TODO: block while full
    T pop()                                                    // TODO: block while empty
    {
        if (q_.empty()) return T{};
        T v = std::move(q_.front());
        q_.pop();
        return v;
    }
    std::size_t size() const { return q_.size(); }
};

int main()
{
    BoundedQueue<int> q(4);
    constexpr int N = 2000;
    long long sum = 0;
    bool inOrder = true;
    std::size_t maxSeen = 0;

    std::thread producer([&] {
        for (int i = 1; i <= N; ++i) {
            q.push(i);                                 // blocks when 4 items are already waiting
            const std::size_t s = q.size();
            if (s > maxSeen) maxSeen = s;
        }
    });
    std::thread consumer([&] {
        int prev = 0;
        for (int i = 1; i <= N; ++i) {
            const int v = q.pop();                     // blocks when the queue is empty
            if (v != prev + 1) inOrder = false;
            prev = v;
            sum += v;
        }
    });
    producer.join();
    consumer.join();

    CHECK(sum == static_cast<long long>(N) * (N + 1) / 2);   // every item arrived exactly once
    CHECK(inOrder);                                    // and in order (FIFO)
    CHECK(maxSeen <= 4);                               // the bound was respected
    CHECK(q.size() == 0);
    return finish("14 BoundedQueue");
}
