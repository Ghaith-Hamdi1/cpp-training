# Atomic variables

- Race condition is a common issue faced on multi threading systems
- It occurs when many threads try to access the same resource at the same time
- Atomic variables are created to be protected from data races
- `std::atomic<T>` where `T` is the type of atomic variable
- Type aliases are defined in the standard library, like `std::atomic_bool` ~ `std::atomic<bool>`

## What "atomic" actually guarantees

- An atomic operation is *indivisible*: no other thread can ever observe it half-done, it's either not started or fully completed
- Plain `int counter++` is really read + increment + write; two threads can interleave those steps (both read the same old value before either writes back) and silently drop updates
- That's why, in the example below, `getCounter()` will (almost always) report a lower value than `getAtomicCounter()` after 10 threads each do 1000 increments, even though the source looks symmetric

## Key atomic operations

- `is_lock_free()` (every atomic type except `std::atomic_flag`, which is *always* lock-free): tells you whether operations compile to plain atomic CPU instructions or fall back to an internal mutex
  - If it falls back to a mutex, you've lost the main performance reason to use an atomic — profile before assuming atomics beat a mutex
- `std::atomic<T>` for a user-defined `T` requires a trivial copy-assignment operator (no virtual functions/bases, every member trivially copyable), so the library can treat it as raw bytes
  - Works for the plain `struct A { int x; void print(); }` below; would not compile for a type holding a `std::string` or `std::vector`
- `compare_exchange_weak()` / `compare_exchange_strong()`: "update this value based on its current value, only if nobody else changed it meanwhile"
  - Compares current value to `expected`; stores the new value and returns `true` if they match, otherwise refreshes `expected` and returns `false`
  - `compare_exchange_weak()` may fail *spuriously* (return `false` even on a match) — always use it in a retry loop
  - `compare_exchange_strong()` never fails spuriously, at the cost of being more expensive when a spurious retry would've been fine

## Memory ordering: the part that's easy to get wrong

Every atomic operation takes an optional `std::memory_order` — it controls not just that variable's atomicity, but what it guarantees about the visibility of *other*, ordinary reads/writes around it on other threads. Three practical models:

- **`memory_order_seq_cst`** (default): all threads agree on one global order of every sequentially-consistent atomic operation
  - Easiest to reason about — "as if" every thread's atomic ops were interleaved one at a time in a fixed order
  - Right default unless you've measured a specific reason to relax it
- **Acquire/release** (`memory_order_acquire` on loads, `memory_order_release` on stores): cheaper than full seq_cst on some architectures
  - A release-store "publishes" everything written before it; a matching acquire-load that observes it is guaranteed to see those prior writes too
  - Classic pattern: set up data → flip a `ready` flag with release; consumer spins on the flag with acquire → safely reads the data
  - This is how the standard library's own mutexes/condition variables are typically implemented under the hood
- **`memory_order_relaxed`**: only guarantees atomicity of that one variable, and that a thread never sees its own writes "go backwards"
  - No ordering guarantee relative to any other variable — two threads can disagree on which of two relaxed writes (on two different variables) happened first
  - Genuinely hard to reason about correctly — treat as an expert-level, profile-justified optimization, not a default

**Practical guidance**: reach for `std::mutex` first for anything beyond a simple counter/flag; when an atomic is the right tool, keep the default `memory_order_seq_cst` unless you've measured a real bottleneck and understand exactly which acquire/release pairing you need.

```cpp
// Trimmed excerpt (already close to minimal) — full runnable example: examples/03-cpp-standard-library/11-multithreading-and-synchronization/54_atomic.cpp
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

class Test
{
public:
    Test() : atomic_counter{0}, counter{0} 
    {
    }

    void run()
    {
        for (int i = 0; i < 1000; i++)
        {
            atomic_counter++;
            counter++;
        }
    }
    int getAtomicCounter() const
    {
        return atomic_counter;
    }

    int getCounter() const 
    {
        return counter;
    }
private:
    std::atomic_int atomic_counter;
    int counter;
};

struct A
{
    int x;
    void print()
    {
        std::cout << "Print from A" << std::endl;
    }
};

int main()
{
    std::vector<std::thread> vect;
    Test test;
    std::atomic<A> aA;

    for (int i = 0; i < 10; i++)
    {
        vect.emplace_back(&Test::run, &test);
    }

    for (int i = 0; i < 10; i++)
    {
        vect[i].join();
    }

    std::cout << "Atomic counter " << test.getAtomicCounter() << " and non atomic counter is " << test.getCounter() << std::endl;
    aA.load().print();
    return 0;
}
```

