# Phase 5: Modern C++ (C++11 to C++20)

[Roadmap](README.md) | Previous: [Phase 4: RAII, exceptions and advanced language tools](phase-4-raii-exceptions-and-advanced-language-tools.md) | Next: [Phase 6: Design patterns and SOLID](phase-6-design-patterns-and-solid.md)

*Move semantics, smart pointers, forwarding, `constexpr`, vocabulary types, concepts.*

**Time:** about **24.3 hours** (20.7 h reading, 2.8 h lessons and quizzes, 0.8 h exercises), plus 11.8 h if you also read the deepen list.

## Big topics

| Topic | What it covers |
|---|---|
| **Move semantics** | Value categories, rvalue references, what `std::move` does, writing move operations, copy elision, the move traps, `noexcept` moves. |
| **Smart pointers and ownership** | `unique_ptr`, `shared_ptr`, `weak_ptr`, control blocks, cycles, custom deleters, passing ownership. |
| **Type deduction and `auto`** | Template deduction rules, `auto` and `decltype`, structured bindings. |
| **Forwarding and variadic templates** | Forwarding references, reference collapsing, `std::forward`, parameter packs, fold expressions. |
| **Compile-time programming** | `constexpr`, `consteval`, type traits, `if constexpr`, SFINAE, concepts and `requires`. |
| **Vocabulary types** | `optional`, `variant` and `visit`, `expected`, `span`, `string_view`, `tuple`. |
| **Ranges and C++20** | Views and pipelines, `std::format`, `<=>`, `jthread` (see phase 7). |

## Core reading (207 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| Primer | 12.1 smart pointers (shared_ptr, unique_ptr, weak_ptr) | 479 to 486; 493 to 504 | 20 | The C++11 smart pointers |
| Primer | 13.6 Moving objects | 560 to 579 | 20 | Rvalue references, move constructors, move assignment, `noexcept` |
| Primer | 16.2.5 to 16.2.7 deduction, `std::move`, forwarding; 16.4 variadic templates | 716 to 722; 728 to 734 | 14 | Reference collapsing, perfect forwarding, parameter packs |
| EMC | Items 1, 2, 5, 7: deduction, `auto`, `()` versus `{}` | 27 to 41; 55 to 61; 67 to 76 | 32 | The deduction rules everything else uses |
| EMC | Item 15 `constexpr` | 115 to 121 | 7 | `constexpr` objects and functions |
| EMC | Items 18 to 22: `unique_ptr`, `shared_ptr`, `weak_ptr`, `make_*`, Pimpl | 136 to 174 | 39 | Smart pointers in depth |
| EMC | Items 23, 24, 25, 28: `move`, `forward`, universal references, reference collapsing | 176 to 195; 215 to 221 | 27 | The core of move semantics and forwarding |
| EMC | Items 26 to 27, 29, 41, 42: overloading, cheap moves, pass by value, emplacement | 195 to 215; 221 to 225; 299 to 320 | 48 | Moves in practice |

## Deepen (optional, 118 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| Move Semantics | 1.2 to 1.4; chapter 2: the core idea and moved-from objects | 36 to 41; 43 to 52 | 16 | The clearest account of what a move is |
| Move Semantics | 3.1; 3.3 to 3.4: special member functions, Rule of Five | 53 to 58; 66 to 76 | 17 | Exactly when the compiler generates or suppresses moves |
| Move Semantics | 4.1 to 4.2; 4.3.5 to 4.3.6: passing and initializing | 77 to 79; 90 to 93 | 7 | By value and `std::move` |
| Move Semantics | 6.1 to 6.2; 7.1; 7.4: moved-from states and `noexcept` | 107 to 115; 125 to 134; 140 to 141 | 21 | The state a moved-from object is in; `noexcept` rules |
| Move Semantics | 8.1.2 to 8.1.3; 8.4 to 8.5: value categories | 145 to 148; 153 to 154 | 6 | lvalue, prvalue, xvalue and the C++17 changes |
| Move Semantics | 9.1 to 9.3: perfect forwarding | 159 to 166 | 8 | Universal versus rvalue references |
| Move Semantics | chapters 13 to 15: move-only types, algorithms, library types | 213 to 250 | 38 | Move semantics in the standard library |
| PPP | Concepts: 18.1.2 to 18.1.4 | 530 to 534 | 5 | The only concepts coverage in the five books; the lessons carry the rest |

## Lessons and exercises

| Lesson | Time |
|---|---|
| [10. Vocabulary Types](https://ghaith-hamdi1.github.io/cpp-training/21-vocabulary-types.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/21-vocabulary-types-quiz.html) | 35 min |
| [11. Move Semantics](https://ghaith-hamdi1.github.io/cpp-training/13-move-semantics.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/13-move-semantics-quiz.html) | 45 min |
| [12. Smart Pointers and Ownership](https://ghaith-hamdi1.github.io/cpp-training/14-smart-pointers.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/14-smart-pointers-quiz.html) | 40 min |
| [13. Type Traits and Compile-time C++](https://ghaith-hamdi1.github.io/cpp-training/09-compile-time.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/09-compile-time-quiz.html) | 45 min |

Exercises: 15 (`optional`/`variant`) and 16 (concepts).

> C++ Primer (2013) stops at C++11, so for C++14, C++17 and C++20 features (vocabulary types, `if constexpr`, concepts, ranges, structured bindings) the lessons and Effective Modern C++ are the sources. Josuttis is a deep dive: read it after Effective Modern C++ if move semantics is the part you want to master.

**Recap check.** Explain: what `std::move` does at run time (nothing), why `return std::move(local)` hurts, the three value categories, what a forwarding reference is, why `make_shared` needs one allocation, and what a concept replaces.

**Notes templates.** [Reading notes for phase 5](../notes/phase-5-modern-cpp/README.md).

---

[Roadmap](README.md) | Previous: [Phase 4: RAII, exceptions and advanced language tools](phase-4-raii-exceptions-and-advanced-language-tools.md) | Next: [Phase 6: Design patterns and SOLID](phase-6-design-patterns-and-solid.md)
