// Lesson 15: check-then-act race fixed by a whole-operation interface (try_pop), and deadlock avoidance:
// scoped_lock with opposite lock order, and a hierarchical mutex that catches a wrong order immediately.
#include <climits>
#include <iostream>
#include <mutex>
#include <optional>
#include <stack>
#include <stdexcept>
#include <thread>
#include <vector>

template <typename T>
class SafeStack {
    std::stack<T> s_;
    mutable std::mutex m_;
public:
    void push(T v) { std::lock_guard<std::mutex> lk(m_); s_.push(std::move(v)); }
    std::optional<T> try_pop() {                        // check + read + remove as ONE atomic operation
        std::lock_guard<std::mutex> lk(m_);
        if (s_.empty()) return std::nullopt;
        T v = std::move(s_.top());
        s_.pop();
        return v;
    }
};

std::mutex a, b;
int shared = 0;
void thread1() { std::scoped_lock lk(a, b); ++shared; }   // locks both with a deadlock-avoidance algorithm
void thread2() { std::scoped_lock lk(b, a); ++shared; }   // opposite order, still safe

class HierarchicalMutex {
    std::mutex m_;
    const unsigned level_;
    unsigned previous_ = 0;
    static thread_local unsigned current_;              // lowest level this thread currently holds
public:
    explicit HierarchicalMutex(unsigned level) : level_(level) {}
    void lock() {
        if (current_ <= level_) throw std::logic_error("lock order violated");   // must go strictly downward
        m_.lock();
        previous_ = current_;
        current_ = level_;
    }
    void unlock() {
        if (current_ != level_) throw std::logic_error("unlock out of order");
        current_ = previous_;
        m_.unlock();
    }
};
thread_local unsigned HierarchicalMutex::current_ = UINT_MAX;

int main() {
    SafeStack<int> stack;
    for (int i = 0; i < 1000; ++i) stack.push(i);
    std::mutex outM;
    long taken = 0;
    std::vector<std::thread> ts;
    for (int t = 0; t < 4; ++t)
        ts.emplace_back([&] {
            long mine = 0;
            while (auto v = stack.try_pop()) ++mine;    // no window between the check and the removal
            std::lock_guard<std::mutex> lk(outM);
            taken += mine;
        });
    for (auto& t : ts) t.join();
    std::cout << "4 threads popped " << taken << " items in total (each exactly once)\n";

    std::thread x([] { for (int i = 0; i < 10000; ++i) thread1(); });
    std::thread y([] { for (int i = 0; i < 10000; ++i) thread2(); });
    x.join(); y.join();
    std::cout << "opposite lock orders with scoped_lock: no deadlock, shared = " << shared << '\n';

    HierarchicalMutex high(10000), low(5000);
    {
        std::lock_guard<HierarchicalMutex> l1(high);
        std::lock_guard<HierarchicalMutex> l2(low);     // OK: 10000 then 5000
        std::cout << "high then low: fine\n";
    }
    try {
        std::lock_guard<HierarchicalMutex> l1(low);
        std::lock_guard<HierarchicalMutex> l2(high);    // throws at once
    } catch (const std::logic_error& e) {
        std::cout << "low then high: " << e.what() << '\n';
    }
}
