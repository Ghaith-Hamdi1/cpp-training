// Lesson 18: atomic operations, compare_exchange (weak versus strong), release/acquire publication, a spinlock built on
// atomic_flag, a reference count with the right orders, a lock-free stack push, and a fine-grained queue.
// Compile with -std=c++20 -pthread.
#include <atomic>
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <thread>
#include <vector>

struct Spinlock {                                                    // acquire on lock, release on unlock
    std::atomic_flag f = ATOMIC_FLAG_INIT;
    void lock() { while (f.test_and_set(std::memory_order_acquire)) { /* spin */ } }
    void unlock() { f.clear(std::memory_order_release); }
};

struct Counted {                                                     // intrusive reference count, like shared_ptr's
    std::atomic<int> refs{1};
    static inline std::atomic<int> destroyed{0};
    void addRef() { refs.fetch_add(1, std::memory_order_relaxed); }  // no ordering needed to just count
    void release() {
        if (refs.fetch_sub(1, std::memory_order_acq_rel) == 1) { ++destroyed; delete this; }   // the last one sees everyone's writes, then deletes
    }
};

struct Node { int value; Node* next; };
std::atomic<Node*> head{nullptr};
void push(int v) {                                                   // lock-free push: retry until the head did not change under us
    Node* n = new Node{v, head.load(std::memory_order_relaxed)};
    while (!head.compare_exchange_weak(n->next, n, std::memory_order_release, std::memory_order_relaxed)) {}
}

template <typename T>
class TwoLockQueue {                                                 // fine-grained locking: producers and consumers use different mutexes
    struct N { std::shared_ptr<T> data; std::unique_ptr<N> next; };
    std::mutex headM_, tailM_;
    std::unique_ptr<N> head_;
    N* tail_;
    N* getTail() { std::lock_guard<std::mutex> lk(tailM_); return tail_; }
public:
    TwoLockQueue() : head_(new N), tail_(head_.get()) {}              // one dummy node: head and tail never touch the same node when non-empty
    void push(T v) {
        auto data = std::make_shared<T>(std::move(v));
        std::unique_ptr<N> dummy(new N);
        std::lock_guard<std::mutex> lk(tailM_);
        tail_->data = data;
        N* newTail = dummy.get();
        tail_->next = std::move(dummy);
        tail_ = newTail;
    }
    std::optional<T> tryPop() {
        std::lock_guard<std::mutex> lk(headM_);
        if (head_.get() == getTail()) return std::nullopt;            // empty
        std::shared_ptr<T> d = head_->data;
        head_ = std::move(head_->next);
        return *d;
    }
};

int main()
{
    // 1. plain atomic counter, relaxed is enough for a statistic
    std::atomic<long> hits{0};
    std::vector<std::thread> ts;
    for (int i = 0; i < 4; ++i) ts.emplace_back([&] { for (int k = 0; k < 100000; ++k) hits.fetch_add(1, std::memory_order_relaxed); });
    for (auto& t : ts) t.join();
    std::cout << "4 threads x 100000 relaxed fetch_add -> " << hits << '\n';

    // 2. publish data with release/acquire, many rounds
    int bad = 0;
    for (int round = 0; round < 2000; ++round) {
        int data = 0;
        std::atomic<bool> ready{false};
        std::thread prod([&] { data = 42; ready.store(true, std::memory_order_release); });
        std::thread cons([&] { while (!ready.load(std::memory_order_acquire)) {} if (data != 42) ++bad; });
        prod.join(); cons.join();
    }
    std::cout << "release/acquire publish: 2000 rounds, wrong reads " << bad << '\n';

    // 3. compare_exchange: double a value atomically, retry on interference
    std::atomic<int> x{3};
    int expected = x.load();
    while (!x.compare_exchange_weak(expected, expected * 2)) {}       // weak may fail spuriously, so it lives in a loop
    int e2 = 6;
    bool okStrong = x.compare_exchange_strong(e2, 99);                // strong: fails only if the value really differs
    std::cout << "CAS: 3 doubled to " << expected * 2 << ", strong(6 -> 99) " << std::boolalpha << okStrong << ", x = " << x << '\n';
    int stale = 5;
    bool okStale = x.compare_exchange_strong(stale, 7);               // expected is wrong: fails and refreshes `stale`
    std::cout << "CAS with a stale expected value: " << okStale << ", expected was refreshed to " << stale << '\n';

    // 4. spinlock protects a plain counter
    Spinlock sl;
    long guarded = 0;
    ts.clear();
    for (int i = 0; i < 4; ++i) ts.emplace_back([&] { for (int k = 0; k < 50000; ++k) { sl.lock(); ++guarded; sl.unlock(); } });
    for (auto& t : ts) t.join();
    std::cout << "spinlock (atomic_flag), 4 x 50000 increments -> " << guarded << '\n';

    // 5. reference count with relaxed increments and acq_rel decrement
    auto* obj = new Counted;
    ts.clear();
    for (int i = 0; i < 4; ++i) { obj->addRef(); ts.emplace_back([obj] { obj->release(); }); }
    for (auto& t : ts) t.join();
    obj->release();
    std::cout << "refcount: objects destroyed exactly once -> " << Counted::destroyed << '\n';

    // 6. lock-free push from several threads
    ts.clear();
    for (int i = 0; i < 4; ++i) ts.emplace_back([i] { for (int k = 0; k < 1000; ++k) push(i * 1000 + k); });
    for (auto& t : ts) t.join();
    int n = 0;
    for (Node* p = head.load(); p;) { Node* nx = p->next; delete p; p = nx; ++n; }
    std::cout << "lock-free stack: 4 x 1000 pushes -> " << n << " nodes\n";

    // 7. fine-grained queue: one producer, one consumer
    TwoLockQueue<int> q;
    long sum = 0;
    std::thread prod([&] { for (int i = 1; i <= 1000; ++i) q.push(i); });
    std::thread cons([&] { int got = 0; while (got < 1000) if (auto v = q.tryPop()) { sum += *v; ++got; } });
    prod.join(); cons.join();
    std::cout << "two-lock queue: sum of 1..1000 popped by the consumer = " << sum << '\n';
}
