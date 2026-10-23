// Lesson 16: check-then-act race fixed by a whole-operation interface (try_pop), and deadlock avoidance:
// scoped_lock with opposite lock order.
#include <iostream>
#include <mutex>
#include <optional>
#include <stack>
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
}
