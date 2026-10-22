# Runnable programs for the interactive lessons

Each file is a complete program (it has `main` and its own `#include`s) that demonstrates the main snippets of one lesson and prints what happens. Read the lesson section, then compile and run the matching file and change things to see what breaks. All of them compile cleanly with `-Wall -Wextra` on g++ 16 (MinGW-w64) with `-std=c++20`.

```bash
g++ -std=c++20 -Wall -Wextra -pthread 01-basics/01_init_and_traps.cpp -o demo && ./demo
```

Or build everything with `make` (outputs go to `build/`). The `-pthread` flag is only needed for lesson 7, but it is harmless elsewhere. Add `-fsanitize=address,undefined` to catch memory bugs; `-fsanitize=thread` finds data races on Linux or WSL (it is not available for MinGW).

| Lesson | Program | What it shows |
|---|---|---|
| 1 Basics | `01_init_and_traps.cpp` | initialization forms, the signed/unsigned trap, prefix vs postfix, by value vs by reference |
| | `02_pointers_references_const.cpp` | pointers, array decay, reference re-binding, `const` placement, `new`/`delete` |
| 2 OOP | `01_ctor_order_encapsulation.cpp` | invariant protected by `private`, construction and destruction order |
| | `02_rule_of_five.cpp` | deep copy, move, and a destructor that silently turns a move into a copy |
| | `03_virtual_slicing_interfaces.cpp` | virtual vs non-virtual, slicing, abstract interface, virtual call in a constructor |
| 3 Core language | `01_raii_move_smart_pointers.cpp` | RAII and stack unwinding, `std::move` on a const, `unique_ptr`, `shared_ptr`, `weak_ptr` and cycles |
| | `02_lambdas_exceptions_casts.cpp` | capture by value vs reference, exception handler order, casts, `constexpr`, `optional`, `variant` |
| 4 STL, 8 Strings | `01_vector_map_algorithms.cpp` | vector growth, `map::operator[]` inserting, erase-remove, algorithms, heaps |
| | `02_strings_regex_chrono.cpp` | `string_view`, `regex_match` vs `regex_search`, captures, `chrono` |
| 5 Templates, 9 Compile-time | `01_templates_specialization_forwarding.cpp` | templates, specialization, perfect forwarding, variadics, fold expressions |
| | `02_traits_constexpr_concepts.cpp` | type traits, `if constexpr`, `enable_if`, concepts, `constexpr`, `consteval`, TMP |
| 6 Patterns | `01_singleton_factory_strategy.cpp` | Meyers Singleton, factory and registry, three kinds of Strategy |
| | `02_observer_state_crtp.cpp` | Observer that survives detaching, State with `variant`, CRTP |
| 7 Multithreading | `01_threads_basics_and_guard.cpp` | `std::thread`, `std::ref`, join guard, `jthread` |
| | `02_race_mutex_atomic.cpp` | a real lost-update race, fixed with a mutex and with an atomic |
| | `03_interface_race_and_deadlock.cpp` | `try_pop`, `scoped_lock` with opposite orders, hierarchical mutex |
| | `04_condvar_queue_and_thread_pool.cpp` | condition variable, blocking queue, thread pool |
| | `05_async_atomics_spsc.cpp` | `async`, `promise`, `packaged_task`, release/acquire, CAS, lock-free SPSC queue |
| 11 Wire formats | `01_bits_layout_endian.cpp` | bit manipulation, struct padding and `offsetof`, `#pragma pack`, endianness |
| | `02_parse_message.cpp` | a binary message read with `memcpy`-style loads, a zero-copy text parser with `string_view` and `from_chars` |
| | `03_fixed_point_and_sequence.cpp` | prices as scaled integers versus `double`, sequence-number gaps with wrap-around |

Lesson 10 (coding rules) is about avoiding risky code, so it has no program. Some outputs vary between runs on purpose: the unsafe counter in `02_race_mutex_atomic.cpp` is a data race (undefined behavior) kept only to show lost updates.
