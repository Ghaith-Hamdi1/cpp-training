# C++ recap and roadmap: six phases, five books

A map of every big C++ topic, grouped into six phases from solid fundamentals to advanced tools to modern C++, with the exact book chapters (PDF pages) to read in each phase, the lessons and exercises that go with them, and a time estimate. Use it as a **reading guide** when you want to study a phase properly, and as a **recap** when you want to check that you can still explain the topics. The [topic index](#topic-index-where-to-look) at the end is the quick reminder.

All page numbers are **PDF viewer pages** (the number your PDF reader shows). The books are in [`books/`](../../../books).

## The five books

| Book | Covers | Best used for |
|---|---|---|
| *C++ Primer*, 5th ed. (Lippman, Lajoie, Moo), [PDF](../../../books/Cpp-Primer-5th-Edition-Lippman.pdf), [reading guide](../cpp-primer-reading-guide.md), [reading plan](../cpp-primer-reading-plan.md) | C++11, the whole language and library, 970 pages | The **systematic base**: phases 1 to 4 and the C++11 parts of phase 5. It is a textbook in the order a language should be learned, with exercises |
| *Programming: Principles and Practice Using C++*, 3rd ed. (Stroustrup), [reading guide](../programming-principles-and-practice-reading-guide.md) | C++20 | A **second explanation** from the language's creator, strongest on class design, memory and the STL. [Reading plan](../programming-principles-and-practice-reading-plan.md) |
| *Effective Modern C++* (Meyers), [reading guide](../effective-modern-cpp-reading-guide.md) | C++11/14 | **Modern C++** in short, self-contained items: deduction, smart pointers, move and forwarding, lambdas. [Reading plan](../effective-modern-cpp-reading-plan.md) |
| *C++ Move Semantics: The Complete Guide* (Josuttis), [reading guide](../move-semantics-complete-guide-reading-guide.md) | C++11 to C++20 | A **deep dive** on one topic: moved-from states, value categories, special member rules. [Reading plan](../move-semantics-reading-plan.md) |
| *C++ Concurrency in Action*, 2nd ed. (Williams), [reading guide](../concurrency-in-action-reading-guide.md) | C++17 | **Concurrency**: the only book here with real depth on threads and the memory model. [Reading plan](../concurrency-in-action-reading-plan.md) |

The books overlap on purpose. For each phase the **core** list is the shortest path that covers the phase; the **deepen** list is a second explanation of the same ground from another author, to read when a topic is still unclear or you want more depth. Do not read both lists in full unless you have the time.

## The plan at a glance

Time = core reading at about 10 pages an hour (pages with code you type in and run), plus the lessons and quizzes of the phase, plus the practice exercises. The deepen reading is extra and shown separately.

| Phase | Theme | Core reading | Lessons and quizzes | Exercises | **Core total** | Deepen reading (optional) |
|---|---|---|---|---|---|---|
| [1](phase-1-core-language-foundations.md) | Core language foundations | 190 pages, 19.0 h | 2.8 h | 2.3 h | **24.0 h** | 86 pages, 8.6 h |
| [2](phase-2-classes-memory-and-object-oriented-design.md) | Classes, memory and object-oriented design | 220 pages, 22.0 h | 2.4 h | 0.8 h | **25.3 h** | 84 pages, 8.4 h |
| [3](phase-3-the-standard-library-and-generic-programming.md) | The standard library and generic programming | 231 pages, 23.1 h | 6.6 h | 0.4 h | **30.1 h** | 67 pages, 6.7 h |
| [4](phase-4-raii-exceptions-and-advanced-language-tools.md) | RAII, exceptions and advanced language tools | 66 pages, 6.6 h | 0.5 h | 0.0 h | **7.1 h** | 23 pages, 2.3 h |
| [5](phase-5-modern-cpp.md) | Modern C++ (C++11 to C++20) | 207 pages, 20.7 h | 5.5 h | 0.8 h | **27.0 h** | 118 pages, 11.8 h |
| [6](phase-6-concurrency-and-the-memory-model.md) | Concurrency and the memory model | 109 pages, 10.9 h | 5.9 h | 0.8 h | **17.7 h** | 39 pages, 3.9 h |
| | **Total** | 1023 pages | | | **131.1 h** | 417 pages, 41.7 h |

The core path is about **131 hours**: roughly 22 weeks at 6 hours a week, or 11 weeks at 12. Adding every deepen list brings it to about **173 hours**. If you only want a refresher on what you already know, skim the "core reading" at 25 pages an hour and spend your time on the lessons, quizzes and recap questions.

Do the phases in order, because each builds on the one before. Phase 6 (concurrency) needs move semantics, lambdas and RAII from the earlier phases.

## How to study a phase

| Step | Do |
|---|---|
| 1. Skim the topic list | Mark each topic you could not explain aloud right now. |
| 2. Do the lessons | Work through the phase's lessons on the [site](https://ghaith-hamdi1.github.io/cpp-training/), running the step-throughs, then take each quiz. |
| 3. Read | Read the core reading in the order listed, with the code closed first, then typed in. Read the deepen list only for topics you marked. |
| 4. Practise | Do the phase's exercises from [`examples/practice/`](../../../examples/practice/README.md) without looking things up. |
| 5. Recap | Answer the phase's recap question aloud, and retake any quiz below 80%. |

## Topic index: where to look

A one-page reminder: every big topic, the lesson that teaches it and the book chapter that explains it best (PDF pages).

| Topic | Lesson | Best book chapter |
|---|---|---|
| Types, initialization, `auto` | [3. Types, Initialization & Constants](https://ghaith-hamdi1.github.io/cpp-training/16-types-and-casts.html) | Primer 2.1 to 2.5 (61 to 100) |
| Expressions and conversions | [3. Types, Initialization & Constants](https://ghaith-hamdi1.github.io/cpp-training/16-types-and-casts.html) | Primer 4.11 (188 to 194) |
| Functions and argument passing | [1. C++ Basics](https://ghaith-hamdi1.github.io/cpp-training/01-basics.html) | Primer ch. 6 (231 to 281) |
| Pointers, references, `const` | [1. C++ Basics](https://ghaith-hamdi1.github.io/cpp-training/01-basics.html) | Primer 2.3 to 2.4 (79 to 95); PPP 15.3 to 15.5 (452 to 463) |
| Strings, vectors, arrays | [1. C++ Basics](https://ghaith-hamdi1.github.io/cpp-training/01-basics.html) | Primer ch. 3 (113 to 161) |
| Vocabulary types (`optional`, `variant`, `span`) | [19. Values or Errors: optional, variant and expected](https://ghaith-hamdi1.github.io/cpp-training/21-vocabulary-types.html) | Primer 17.1 tuple (747 to 751); EMC Item 5 (55 to 61) |
| Classes and invariants | [5. Classes and Objects](https://ghaith-hamdi1.github.io/cpp-training/02-oop.html) | Primer ch. 7 (283 to 335); PPP 8.1 to 8.7 (235 to 258) |
| Copy control, Rule of 3/5/0 | [6. Copy Control and Operators](https://ghaith-hamdi1.github.io/cpp-training/26-copying.html) | Primer 13.1 to 13.5 (525 to 559); Move Semantics 3.3 to 3.4 (66 to 76) |
| Operator overloading, conversions | [6. Copy Control and Operators](https://ghaith-hamdi1.github.io/cpp-training/26-copying.html) | Primer ch. 14 (581 to 619) |
| Inheritance, virtual functions | [7. Inheritance, Virtual Functions and the Object Model](https://ghaith-hamdi1.github.io/cpp-training/27-inherit.html) | Primer ch. 15 (621 to 679); PPP 12.3 (380 to 387) |
| Object model, multiple inheritance, RTTI | [7. Inheritance, Virtual Functions and the Object Model](https://ghaith-hamdi1.github.io/cpp-training/27-inherit.html) | Primer 18.3, 19.2 (831 to 847; 854 to 860) |
| RAII and exceptions | [18. RAII and Exceptions](https://ghaith-hamdi1.github.io/cpp-training/03-core-language.html) | Primer 18.1 (801 to 813); PPP 18.4 to 18.5 (542 to 553) |
| Value categories | [20. Lvalues and Rvalues](https://ghaith-hamdi1.github.io/cpp-training/13-move-semantics.html) | Primer 4.1 (163 to 167); Move Semantics ch. 8 (145 to 156) |
| Move semantics and std::move | [21. Copy versus Move, and std::move](https://ghaith-hamdi1.github.io/cpp-training/33-copymove.html) | Primer 13.6 (560 to 579); EMC Item 23 (176 to 182); Move Semantics ch. 2 (43 to 52) |
| Writing move operations | [22. Writing Move Operations](https://ghaith-hamdi1.github.io/cpp-training/34-writemoves.html) | Primer 13.6 (560 to 579); EMC Item 14 (108 to 115) |
| Perfect forwarding | [25. Perfect Forwarding](https://ghaith-hamdi1.github.io/cpp-training/37-forwarding.html) | EMC Items 23, 25 (176 to 195); Move Semantics ch. 9 (159 to 170) |
| Smart pointers: shared_ptr | [27. shared_ptr: Shared Ownership](https://ghaith-hamdi1.github.io/cpp-training/14-smart-pointers.html) | Primer 12.1 (479 to 504); EMC Items 19, 21 (143 to 165) |
| weak_ptr and cycles | [28. weak_ptr and Reference Cycles](https://ghaith-hamdi1.github.io/cpp-training/32-weakptr.html) | EMC Item 20 (152 to 157) |
| Lambdas and callables | [10. Lambdas](https://ghaith-hamdi1.github.io/cpp-training/15-lambdas.html) | Primer 10.3, 14.8 (414 to 429; 600 to 607); EMC Items 31 to 32 (234 to 247) |
| Strings, regex, time | [8. Strings, Regex & Time](https://ghaith-hamdi1.github.io/cpp-training/08-strings-regex-time.html) | Primer 9.5, 17.3 (389 to 396; 757 to 773) |
| STL containers | [11. STL Containers](https://ghaith-hamdi1.github.io/cpp-training/04-stl.html) | Primer ch. 9 (355 to 388); PPP 20 (591 to 609) |
| Maps, sets and hashing | [12. Maps, Sets and Hashing](https://ghaith-hamdi1.github.io/cpp-training/31-assoc.html) | Primer ch. 11 (449 to 477); PPP 20 (591 to 609) |
| Iterators | [13. Iterators](https://ghaith-hamdi1.github.io/cpp-training/28-iterators.html) | Primer 3.4 and 10.4 (135 to 141; 430 to 438); PPP 19 (559 to 586) |
| Algorithms and ranges | [14. Algorithms and Ranges](https://ghaith-hamdi1.github.io/cpp-training/29-algorithms.html) | Primer ch. 10 (405 to 447); PPP 21 (617 to 635) |
| Function templates | [15. Function Templates](https://ghaith-hamdi1.github.io/cpp-training/05-templates.html) | Primer 16.1 to 16.2 (681 to 722); EMC Item 1 (27 to 36) |
| Class templates and specialization | [16. Class Templates](https://ghaith-hamdi1.github.io/cpp-training/30-classtemplates.html) | Primer 16.1, 16.5 (681 to 706; 735 to 743); PPP 18.1 to 18.3 (527 to 541) |
| Forwarding and variadics | [15. Function Templates](https://ghaith-hamdi1.github.io/cpp-training/05-templates.html) | Primer 16.2.5 to 16.4 (716 to 734); EMC Item 28 (215 to 221) |
| Type traits, `constexpr`, concepts | [17. Type Traits, Concepts and Compile-time C++](https://ghaith-hamdi1.github.io/cpp-training/09-compile-time.html) | EMC Item 15 (115 to 121); PPP 18.1.2 to 18.1.4 (530 to 534) |
| Threads | [29. Threads: The Mental Model and Your First Thread](https://ghaith-hamdi1.github.io/cpp-training/07-multithreading.html) | Concurrency in Action ch. 2 (40 to 59) |
| Data races and mutexes | [31. Mutexes and Locking](https://ghaith-hamdi1.github.io/cpp-training/39-mutexes.html) | Concurrency in Action ch. 3 (60 to 95) |
| Deadlock | [32. Deadlock](https://ghaith-hamdi1.github.io/cpp-training/40-deadlock.html) | Concurrency in Action 3.2.4 to 3.2.5 (74 to 82) |
| Condition variables | [33. Condition Variables and Debugging](https://ghaith-hamdi1.github.io/cpp-training/41-condvars.html) | Concurrency in Action 4.1 (96 to 103) |
| Futures and promises | [34. Futures, async and Promises](https://ghaith-hamdi1.github.io/cpp-training/17-tasks-parallelism.html) | Concurrency in Action 4.2 (104 to 115); EMC Items 35 to 38 (259 to 280) |
| Thread pools | [35. Thread Pools, Coordination and Parallel Algorithms](https://ghaith-hamdi1.github.io/cpp-training/42-pools.html) | Concurrency in Action 9.1, 10.1 (324 to 337; 350 to 362) |
| Atomics and compare-and-swap | [36. Atomics and Compare-and-Swap](https://ghaith-hamdi1.github.io/cpp-training/18-atomics-memory-model.html) | Concurrency in Action 5.2 (151 to 164); EMC Item 40 (289 to 297) |
| The memory model | [37. The Memory Model: Orders and Happens-Before](https://ghaith-hamdi1.github.io/cpp-training/43-memmodel.html) | Concurrency in Action 5.1, 5.3 (148 to 151; 165 to 196) |

## Notes on the books

- **C++ Primer is a C++11 book.** It does not cover structured bindings, `if constexpr`, `std::optional`/`variant`/`string_view`, concepts, ranges or the C++14 to C++20 library. Phase 5 therefore leans on Effective Modern C++, Move Semantics and the lessons for those.
- **Programming: Principles and Practice** teaches C++20 style from the start (it uses `span`, concepts and `std::format`), but stays introductory on templates and has no threading chapter.
- **Skip on a first pass:** Primer chapter 1, the operator sections that only repeat what you know (4.6, 4.7, 4.9, 4.10, 4.12), 5.1, 5.2 and the Text-Query case studies in 12.3, 15.9 and 15.8; the Primer appendix; PPP chapters on graphics and the calculator (10 to 14, 6 to 7); Concurrency in Action chapter 7 (lock-free data structures) until phase 7 is solid.
- Each phase's book sections come from the reading guides and plans next to this file. `node tools/check-book-pages.mjs` checks that every section starts on the PDF page given.
- **Notes templates** live in [`notes/`](../notes/README.md), sorted by phase and then by book.
