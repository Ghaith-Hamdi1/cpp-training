# Runnable programs for the interactive lessons

Each file is a complete program (it has `main` and its own `#include`s) that demonstrates the main snippets of one lesson and prints what happens. Read the lesson section, then compile and run the matching file and change things to see what breaks. All of them compile cleanly with `-Wall -Wextra` on g++ 16 (MinGW-w64) with `-std=c++20`.

```bash
g++ -std=c++23 -Wall -Wextra -pthread 01-basics/01_init_and_traps.cpp -o demo && ./demo
```

Or build everything with `make` (outputs go to `build/`). The `-pthread` flag is only needed for lessons 29 to 36, but it is harmless elsewhere. Add `-fsanitize=address,undefined` to catch memory bugs; `-fsanitize=thread` finds data races on Linux or WSL (it is not available for MinGW).

The folder names follow the lesson file names (`13-move-semantics` holds the lesson file `13-move-semantics.html`); the Lesson column uses the numbers shown on the site, which follow the study order.

| Lesson | Program | What it shows |
|---|---|---|
| 1 Basics | `01_init_and_traps.cpp` | initialization forms, the signed/unsigned trap, prefix vs postfix, by value vs by reference |
| 2 Pointers | `22-pointers/01_pointers_references_const.cpp` | pointers, array decay, reference re-binding, `const` placement, `new`/`delete` |
| 3 Types | `01_init_and_conversions.cpp` | initialization forms and brace traps, `auto` and `decltype`, conversions and promotions, casts, `enum class`, `constexpr` |
| 3 Types | `16-types-and-casts/02_small_items.cpp` | `std::bind`, user-defined literals, `<random>`, `extern "C"` and placement new |
| 4 Casts | `25-casts/01_casts.cpp` | silent conversions and narrowing, a C-style cast removing `const`, `static_cast`, `dynamic_cast` on a pointer and a reference, `const_cast`, `reinterpret_cast` and `std::bit_cast` |
| 5 Classes | `02-oop/01_ctor_order_encapsulation.cpp` | invariant protected by `private`, construction and destruction order |
| 6 Copy control | `26-copying/01_rule_of_five.cpp` | deep copy, move, and a destructor that silently turns a move into a copy |
| 7 Inheritance | `27-inherit/01_virtual_slicing_interfaces.cpp` | virtual vs non-virtual, slicing, abstract interface, virtual call in a constructor |
| 7 Inheritance | `27-inherit/02_multiple_inheritance_rtti_conversions.cpp` | multiple inheritance, the diamond and virtual inheritance, object layout, RTTI, private inheritance |
| 8 Strings | `01_sso_numbers_format_streams.cpp` | small string optimisation and capacity, `from_chars`, `to_chars`, `stoi`, `std::format`, string and file streams |
| 11 to 13 STL | `04-stl/01_vector_map_algorithms.cpp` | vector growth, `map::operator[]` inserting, erase-remove, algorithms, heaps |
|  | `04-stl/02_strings_regex_chrono.cpp` | `string_view`, `regex_match` vs `regex_search`, captures, `chrono` |
|  | `04-stl/03_keys_adaptors_ranges.cpp` | a case-insensitive comparator, a custom hash, transparent lookup, `try_emplace`, `multimap`, inserters, `erase_if`, ranges and views |
| 9 Callables | `23-callables/01_function_pointers_functors.cpp` | a function pointer, a functor, `std::function` holding each, `std::invoke` on a member function, `std::bind` next to the lambda that replaces it, when `std::function` allocates |
| 10 Lambdas | `01_callables.cpp` | function pointer, functor, lambda and `std::function`, captures, `mutable`, init-capture, generic and recursive lambdas, `std::function` allocation |
| 15 and 15 Templates | `05-templates/01_templates_specialization_forwarding.cpp` | templates, specialization, perfect forwarding, variadics, fold expressions |
|  | `05-templates/03_deduction_and_tools.cpp` | deduction by value, by reference and forwarding reference, class template argument deduction, alias and variable templates, template template parameters, `index_sequence` |
| 17 Compile-time | `05-templates/02_traits_constexpr_concepts.cpp` | type traits, `if constexpr`, `enable_if`, concepts, `constexpr`, `consteval`, TMP |
| 18 RAII and exceptions | `03-core-language/01_raii_move_smart_pointers.cpp` | RAII and stack unwinding, `std::move` on a const, `unique_ptr`, `shared_ptr`, `weak_ptr` and cycles |
|  | `03-core-language/02_lambdas_exceptions_casts.cpp` | capture by value vs reference, exception handler order, casts, `constexpr`, `optional`, `variant` |
|  | `03-core-language/03_raii_guards_exception_safety.cpp` | a scope guard with commit and rollback, the strong guarantee by copy and swap, `noexcept` moves in `vector` growth, `optional` instead of exceptions |
| 19 Values or errors | `21-vocabulary-types/01_optional_variant_expected_span.cpp` | `pair`/`tuple`, `optional`, `variant` with `visit`, `expected` (C++23), `span` |
| 20 to 25 Move semantics | `13-move-semantics/01_value_categories_moves.cpp` | value categories checked with `decltype`, copy and move counts, elision and `return std::move`, sink parameters, `std::exchange`, copy-and-swap |
| 26 unique_ptr | `24-uniqueptr/01_unique_ptr.cpp` | the object freed at the closing brace, ownership that moves but never copies, passing and returning, a vector of `unique_ptr`, `unique_ptr<Base>`, sizes with different deleters, `release` and `reset` |
| 27 and 28 shared_ptr, weak_ptr | `14-smart-pointers/01_ownership_deleters.cpp` | ownership and custom deleters, `shared_ptr` counts, a cycle that leaks and the `weak_ptr` fix, `enable_shared_from_this` |
| 29 to 33 Threads | `07-multithreading/01_threads_basics_and_guard.cpp` | `std::thread`, `std::ref`, join guard, `jthread` |
|  | `07-multithreading/02_race_mutex_atomic.cpp` | a real lost-update race, fixed with a mutex and with an atomic |
|  | `03_interface_race_and_deadlock.cpp` | `try_pop`, `scoped_lock` with opposite orders |
|  | `04_condvar_queue_and_thread_pool.cpp` | condition variable, blocking queue, thread pool |
|  | `05_async_atomics_spsc.cpp` | `async`, `promise`, `packaged_task`, release/acquire, CAS, lock-free SPSC queue |
|  | `06_mutex_types.cpp` | `recursive_mutex`, `timed_mutex` with `try_lock_for`, a `shared_mutex` price table, `call_once` |
| 34 and 35 Tasks | `17-tasks-parallelism/01_futures_coordination_parallel.cpp` | a `promise<void>` start signal through a `shared_future`, `latch`, `barrier`, `counting_semaphore`, `jthread` with `stop_token`, `reduce(par)` |
| 36 and 37 Atomics | `18-atomics-memory-model/01_atomics_ordering_patterns.cpp` | relaxed counter, release/acquire publication tested 2000 times, CAS weak versus strong, an `atomic_flag` spinlock, a reference count, a lock-free push, a two-lock queue |

Some outputs vary between runs on purpose: the unsafe counter in `02_race_mutex_atomic.cpp` is a data race (undefined behavior) kept only to show lost updates.
