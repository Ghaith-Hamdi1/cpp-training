// Lesson 19: a fixed-size object pool with a free list, and a pmr arena. A counting operator new proves that the
// hot path allocates nothing. Compile with -std=c++20.
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory_resource>
#include <new>
#include <vector>

// ---- count every heap allocation in the program -------------------------------------------------------------------
static std::size_t g_allocations = 0;
void* operator new(std::size_t n) { ++g_allocations; if (void* p = std::malloc(n)) return p; throw std::bad_alloc(); }
void operator delete(void* p) noexcept { std::free(p); }
void operator delete(void* p, std::size_t) noexcept { std::free(p); }

// ---- the pool: all storage is reserved up front; allocate/deallocate are a few instructions ----------------------
template <typename T, std::size_t N>
class Pool {
    union Slot {
        alignas(T) unsigned char storage[sizeof(T)];            // holds a T while in use
        std::size_t nextFree;                                   // holds the free-list link while free
    };
    std::array<Slot, N> slots_;
    std::size_t freeHead_ = 0;                                  // index of the first free slot (N means "none")
    std::size_t inUse_ = 0;
public:
    Pool() { for (std::size_t i = 0; i < N; ++i) slots_[i].nextFree = i + 1; }

    template <typename... Args>
    T* allocate(Args&&... args)
    {
        if (freeHead_ == N) return nullptr;                     // pool exhausted: the caller decides (drop, wait, count)
        Slot& s = slots_[freeHead_];
        freeHead_ = s.nextFree;                                 // pop the free list
        ++inUse_;
        return new (s.storage) T(std::forward<Args>(args)...);  // placement new: construct in the slot, no heap
    }

    void deallocate(T* p)
    {
        p->~T();
        Slot* s = reinterpret_cast<Slot*>(p);                   // the T lives at the start of its slot
        s->nextFree = freeHead_;                                // push the slot back on the free list
        freeHead_ = static_cast<std::size_t>(s - slots_.data());
        --inUse_;
    }

    std::size_t inUse() const { return inUse_; }
    std::size_t indexOf(const T* p) const { return static_cast<std::size_t>(reinterpret_cast<const Slot*>(p) - slots_.data()); }
};

struct Order {
    std::uint64_t id;
    std::int64_t  priceTicks;
    std::uint32_t qty;
    Order(std::uint64_t i, std::int64_t p, std::uint32_t q) : id(i), priceTicks(p), qty(q) {}
};

int main()
{
    static Pool<Order, 4> pool;                                 // static: built once, never on the hot path

    const std::size_t before = g_allocations;
    Order* a = pool.allocate(1, 1012500, 300);
    Order* b = pool.allocate(2, 1012600, 100);
    std::cout << "a in slot " << pool.indexOf(a) << ", b in slot " << pool.indexOf(b) << ", in use " << pool.inUse() << '\n';
    pool.deallocate(a);
    Order* c = pool.allocate(3, 1012700, 50);
    std::cout << "after freeing a, c reuses slot " << pool.indexOf(c) << " (same address as a: " << std::boolalpha << (c == a) << ")\n";

    Order* d = pool.allocate(4, 1, 1);
    Order* e = pool.allocate(5, 1, 1);
    Order* f = pool.allocate(6, 1, 1);                          // the pool has 4 slots: b, c, d, e are in use
    std::cout << "5th allocation: " << (f == nullptr ? "refused (pool exhausted)" : "granted") << '\n';
    pool.deallocate(b); pool.deallocate(c); pool.deallocate(d); pool.deallocate(e);
    std::cout << "heap allocations on this path: " << (g_allocations - before) << '\n';

    // a pmr arena: a std::pmr::vector takes its memory from a buffer we provide
    alignas(std::max_align_t) static unsigned char buffer[4096];
    std::pmr::monotonic_buffer_resource arena(buffer, sizeof buffer, std::pmr::null_memory_resource());
    const std::size_t before2 = g_allocations;
    std::pmr::vector<int> v(&arena);
    v.reserve(100);
    for (int i = 0; i < 100; ++i) v.push_back(i);
    std::cout << "pmr vector of " << v.size() << " ints, heap allocations: " << (g_allocations - before2) << '\n';

    const std::size_t before3 = g_allocations;
    std::vector<int> plain;
    for (int i = 0; i < 100; ++i) plain.push_back(i);           // grows by reallocating: several heap allocations
    std::cout << "plain vector without reserve, heap allocations: " << (g_allocations - before3 > 1 ? "several" : "one") << '\n';
    const std::size_t before4 = g_allocations;
    std::vector<int> reserved;
    reserved.reserve(100);
    for (int i = 0; i < 100; ++i) reserved.push_back(i);
    std::cout << "vector with reserve(100), heap allocations: " << (g_allocations - before4) << '\n';
}
