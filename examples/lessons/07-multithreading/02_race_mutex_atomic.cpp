// Lesson 16: a data race (lost updates), fixed with a mutex and with an atomic. Compile with -pthread.
// The UNSAFE version is undefined behavior; it is here to show lost updates. Its result differs from run to run
// (it may even be correct by luck). Never ship code like it.
#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

constexpr int kThreads = 4;
constexpr int kIncrements = 200000;

template <typename F>
void runThreads(F work) {
    std::vector<std::thread> ts;
    for (int i = 0; i < kThreads; ++i) ts.emplace_back(work);
    for (auto& t : ts) t.join();
}

int unsafeCounter = 0;
void unsafeWork() { for (int i = 0; i < kIncrements; ++i) ++unsafeCounter; }   // load, add, store: three steps

std::mutex m;
int lockedCounter = 0;
void lockedWork() {
    for (int i = 0; i < kIncrements; ++i) {
        std::lock_guard<std::mutex> lock(m);            // unlocks automatically at the end of the block
        ++lockedCounter;
    }
}

std::atomic<int> atomicCounter{0};
void atomicWork() { for (int i = 0; i < kIncrements; ++i) atomicCounter.fetch_add(1); }   // one indivisible step

class SafeCounter {
    mutable std::mutex m_;                              // mutable: so const getters can still lock it
    int value_ = 0;
public:
    void increment() { std::lock_guard<std::mutex> lk(m_); ++value_; }
    int get() const { std::lock_guard<std::mutex> lk(m_); return value_; }
};

int main() {
    const int expected = kThreads * kIncrements;
    runThreads(unsafeWork);
    std::cout << "unsafe : " << unsafeCounter << " (expected " << expected << ", usually less: lost updates)\n";
    runThreads(lockedWork);
    std::cout << "mutex  : " << lockedCounter << '\n';
    runThreads(atomicWork);
    std::cout << "atomic : " << atomicCounter.load() << '\n';

    SafeCounter sc;
    runThreads([&] { for (int i = 0; i < 1000; ++i) sc.increment(); });
    std::cout << "class  : " << sc.get() << '\n';
}
