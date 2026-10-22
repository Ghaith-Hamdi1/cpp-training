// Exercise 13: make a counter safe to use from several threads. Compile with -pthread.
//
// SafeCounter is used by four threads at once. The version below loses updates.
// Make increment(), add() and get() thread-safe with a std::mutex, using RAII locking
// (std::lock_guard), and make get() work on a const object (hint: `mutable`).
// Then think about the alternative: when would std::atomic<long> be enough instead?
#include <mutex>
#include <thread>
#include <vector>
#include "../check.h"

class SafeCounter {
    long value_ = 0;                                   // TODO: protect this
public:
    void increment() { ++value_; }
    void add(long n) { value_ += n; }
    long get() const { return value_; }
};

int main()
{
    SafeCounter c;
    std::vector<std::thread> threads;
    for (int t = 0; t < 4; ++t)
        threads.emplace_back([&c] {
            for (int i = 0; i < 100000; ++i) c.increment();
            c.add(10);
        });
    for (auto& t : threads) t.join();
    CHECK(c.get() == 4 * 100000 + 4 * 10);

    const SafeCounter& cc = c;
    CHECK(cc.get() == 400040);                         // get() must be callable on a const object
    return finish("13 SafeCounter");
}
