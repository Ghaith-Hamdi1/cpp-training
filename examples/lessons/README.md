# Runnable programs for the interactive lessons

Each file is a complete program (it has `main` and its own `#include`s) that demonstrates the main snippets of one lesson and prints what happens. Read the lesson section, then compile and run the matching file and change things to see what breaks. All of them compile cleanly with `-Wall -Wextra` on g++ 16 (MinGW-w64) with `-std=c++20`.

```bash
g++ -std=c++20 -Wall -Wextra -pthread 01-basics/01_init_and_traps.cpp -o demo && ./demo
```

Or build everything with `make` (outputs go to `build/`). The `-pthread` flag is only needed for lessons 11 to 13, but it is harmless elsewhere. Add `-fsanitize=address,undefined` to catch memory bugs; `-fsanitize=thread` finds data races on Linux or WSL (it is not available for MinGW).

The folder names follow the lesson file names (`13-move-semantics` holds the lesson file `13-move-semantics.html`); the Lesson column uses the numbers shown on the site, which follow the study order.

| Lesson | Program | What it shows |
|---|---|---|
| 1 Basics | `01_init_and_traps.cpp` | initialization forms, the signed/unsigned trap, prefix vs postfix, by value vs by reference |
| | `02_pointers_references_const.cpp` | pointers, array decay, reference re-binding, `const` placement, `new`/`delete` |
| 2 OOP | `01_ctor_order_encapsulation.cpp` | invariant protected by `private`, construction and destruction order |
| | `02_rule_of_five.cpp` | deep copy, move, and a destructor that silently turns a move into a copy |
| | `03_virtual_slicing_interfaces.cpp` | virtual vs non-virtual, slicing, abstract interface, virtual call in a constructor |
| 3 Core language, 5 Smart pointers, 6 Lambdas, 7 Types | `01_raii_move_smart_pointers.cpp` | RAII and stack unwinding, `std::move` on a const, `unique_ptr`, `shared_ptr`, `weak_ptr` and cycles |
| | `02_lambdas_exceptions_casts.cpp` | capture by value vs reference, exception handler order, casts, `constexpr`, `optional`, `variant` |
| 3 Core language | `03_raii_guards_exception_safety.cpp` | a scope guard with commit and rollback, the strong guarantee by copy and swap, `noexcept` moves in `vector` growth, `optional` instead of exceptions |
| 4 Move semantics | `01_value_categories_moves.cpp` | value categories checked with `decltype`, copy and move counts, elision and `return std::move`, sink parameters, `std::exchange`, copy-and-swap |
| 5 Smart pointers | `01_ownership_deleters.cpp` | `unique_ptr` ownership and custom deleters, `shared_ptr` counts, a cycle that leaks and the `weak_ptr` fix, `enable_shared_from_this` |
| 6 Lambdas | `01_callables.cpp` | function pointer, functor, lambda and `std::function`, captures, `mutable`, init-capture, generic and recursive lambdas, `std::function` allocation |
| 7 Types | `01_init_and_conversions.cpp` | initialization forms and brace traps, `auto` and `decltype`, conversions and promotions, casts, `enum class`, `constexpr` |
| 8 STL, 14 Strings | `01_vector_map_algorithms.cpp` | vector growth, `map::operator[]` inserting, erase-remove, algorithms, heaps |
| | `02_strings_regex_chrono.cpp` | `string_view`, `regex_match` vs `regex_search`, captures, `chrono` |
| 9 Templates, 15 Compile-time | `01_templates_specialization_forwarding.cpp` | templates, specialization, perfect forwarding, variadics, fold expressions |
| 9 Templates | `03_deduction_and_tools.cpp` | deduction by value, by reference and forwarding reference, class template argument deduction, alias and variable templates, template template parameters, `index_sequence` |
| | `02_traits_constexpr_concepts.cpp` | type traits, `if constexpr`, `enable_if`, concepts, `constexpr`, `consteval`, TMP |
| 10 Patterns | `01_singleton_factory_strategy.cpp` | Meyers Singleton, factory and registry, three kinds of Strategy |
| | `02_observer_state_crtp.cpp` | Observer that survives detaching, State with `variant`, CRTP |
| 11 Multithreading | `01_threads_basics_and_guard.cpp` | `std::thread`, `std::ref`, join guard, `jthread` |
| | `02_race_mutex_atomic.cpp` | a real lost-update race, fixed with a mutex and with an atomic |
| | `03_interface_race_and_deadlock.cpp` | `try_pop`, `scoped_lock` with opposite orders, hierarchical mutex |
| | `04_condvar_queue_and_thread_pool.cpp` | condition variable, blocking queue, thread pool |
| | `05_async_atomics_spsc.cpp` | `async`, `promise`, `packaged_task`, release/acquire, CAS, lock-free SPSC queue |
| | `06_mutex_types.cpp` | `recursive_mutex`, `timed_mutex` with `try_lock_for`, a `shared_mutex` price table, `call_once` |
| 12 Tasks | `01_futures_coordination_parallel.cpp` | a `promise<void>` start signal through a `shared_future`, `latch`, `barrier`, `counting_semaphore`, `jthread` with `stop_token`, `reduce(par)` |
| 13 Atomics | `01_atomics_ordering_patterns.cpp` | relaxed counter, release/acquire publication tested 2000 times, CAS weak versus strong, an `atomic_flag` spinlock, a reference count, a lock-free push, a two-lock queue |
| 17 Wire formats | `01_bits_layout_endian.cpp` | bit manipulation, struct padding and `offsetof`, `#pragma pack`, endianness |
| | `02_parse_message.cpp` | a binary message read with `memcpy`-style loads, a zero-copy text parser with `string_view` and `from_chars` |
| | `03_fixed_point_and_sequence.cpp` | prices as scaled integers versus `double`, sequence-number gaps with wrap-around |
| 18 Low latency | `01_pool_allocator.cpp` | an object pool with a free list and a `pmr` arena, with a counting `operator new` proving zero allocations |
| | `02_latency_percentiles.cpp` | mean versus p50, p99 and p99.9 on a synthetic sample set, and how to time with `steady_clock` |
| | `03_order_book_levels.cpp` | an order-book side as an array indexed by price tick, checked against `std::map` |
| | `04_aos_vs_soa.cpp` | array of structs versus struct of arrays, and cache-line padding |
| | `05_spsc_ring_padded.cpp` | an SPSC ring with a power-of-two mask, padded indices and a drop-newest policy |

Lesson 16 (coding rules) is about avoiding risky code, so it has no program. Some outputs vary between runs on purpose: the unsafe counter in `02_race_mutex_atomic.cpp` is a data race (undefined behavior) kept only to show lost updates.
