# Content audit of the interactive lessons

Audit of `interactive/` (lessons 1 to 10, their quizzes, mock-interview and level-check data), done on 2026-10-22. It lists what is wrong, what is crammed together, what is duplicated and what is missing. The first part of this file is the original audit; the result of re-running it after the rewrite is in the last section, "Re-audit".

## How it was checked

- **Code:** every lesson snippet that has a stated output (5) and all 51 quiz questions that contain code were compiled with g++ 16 (`-std=c++20`) and run. Outputs and answers match what the lessons say.
- **Quiz wording:** the question text, answers and explanations of the 114 quiz questions without code in the STL, templates, patterns and multithreading quizzes were read. Nothing was wrong. The question text of the other six quizzes (basics, OOP, core language, strings, compile-time, rules) was not read.
- **Coverage:** about 70 topics were counted across the lesson text, and compared against the contents of the four books in the repo and the target role (exchange feed handlers: real time, templates, design patterns, multithreading).

## Mistakes

No factual errors were found in what could be verified. Small imprecisions:

- Lesson 3 says `[=]` captures "all by value" but does not say it also captures `this` implicitly (deprecated in C++20).
- Lesson 1 says `NULL` is "the integer 0 in disguise", which simplifies what the standard allows.
- `string_view` is explained in lessons 1, 3, 4 and 8, each time with slightly different wording.

## Crammed into one place, should span several

| Where | Problem | Suggested split |
|---|---|---|
| Lesson 3 (11 sections) | A grab-bag: RAII, move, smart pointers, lambdas, exceptions, casts, `constexpr`, language versions | RAII and exceptions; move semantics; smart pointers; lambdas and callables; types, initialization and casts |
| Move semantics | Spread over lesson 2 (Rule of 5), lesson 3 (move) and lesson 5 (forwarding) | One move-semantics lesson with value categories, `noexcept`, copy elision and forwarding |
| Lesson 5, "Deduction and forwarding references" | Type deduction, reference collapsing and perfect forwarding in one section | Deduction first (including `auto`), then forwarding |
| Lesson 7, "Atomics" | Atomic operations and the memory model mixed together | Atomics; memory ordering (happens-before, acq_rel, fences) |
| Lesson 7, "Performance and real-time concerns" | Contention, false sharing, allocation, priority inversion and lock-free in one section | A dedicated low-latency lesson |
| Lesson 8 | Strings, regex and time are three unrelated topics | Separate them |

## Duplication

- Lessons 5 and 9 both teach type traits, `if constexpr`, SFINAE and `enable_if`, concepts and template metaprogramming, with near-identical factorial examples. Merge them, or give one lesson ownership and leave a pointer in the other.
- Strings are split across lessons 1, 4 and 8 in the same way.

## Missing for this job (exchange feed handlers)

This is the largest gap. None of the following appears in the lessons:

- Parsing binary wire formats: packed structs, endianness, alignment, strict aliasing (`memcpy` and `std::bit_cast`).
- Zero-copy parsing with `string_view` and `span`, and `from_chars`.
- Order-book data structures (`map` against a sorted vector or flat map) and fixed-point prices versus `double`.
- Memory pools, `pmr` allocators, avoiding allocation after startup.
- Bounded queues with back-pressure, thread pinning, measuring tail latency.

## Missing from the books in the repo

Terms below appear zero times in the lesson text.

| Book | Missing |
|---|---|
| Effective Modern C++ | `decltype` and `decltype(auto)`; lambda init-capture (`[x = std::move(y)]`), which matters for moving into threads; the braced-init versus `initializer_list` trap; `promise<void>` as a one-shot signal; `cbegin` |
| C++ Move Semantics (Josuttis) | `std::exchange`, `std::swap` and copy-and-swap |
| C++ Concurrency in Action | `happens-before` and `synchronizes-with`; `acq_rel` and fences; `compare_exchange_weak` versus `strong`; `latch`, `barrier` and `semaphore`; `atomic_flag` spinlocks; `shared_future`; work stealing; thread-safe data structures |
| Programming: Principles and Practice | `iostream`, `fstream` and formatting; `<random>`; bit manipulation and `union` |

## Other gaps

- Multiple and virtual inheritance and the diamond problem, RTTI and `typeid`.
- Functors (`operator()` as a class), conversion operators, `explicit operator bool`.
- Placement new, `std::bind`, ranges, user-defined literals, `extern "C"`.
- Custom comparators and hash functions for `map` and `unordered_map` keys.
- Command, Decorator, Adapter, Builder and Visitor-with-`variant` have only a one-line table entry and no code.

## Suggested order of work

1. A low-latency and feed-handler lesson (closest match to the target role).
2. Split lesson 3, and merge lessons 5 and 9.
3. Split the multithreading atomics section into atomics and memory ordering, and add the missing Concurrency in Action topics.
4. Fill the smaller gaps (`decltype`, init-capture, `std::exchange`, functors, multiple inheritance).

## Re-audit (after phases 0 to 6)

Re-run on the finished rewrite. The site now has **20 lessons, 376 quiz questions, 169 interview cheat-sheet items (mock interview) and 40 step-throughs**; the level check draws 48 questions.

### Original findings

| Finding | Result |
|---|---|
| `[=]` and `this` | Fixed (Lambdas, with the C++20 deprecation). |
| `NULL` "the integer 0 in disguise" | Fixed in phase 1. |
| `string_view` explained four times | One owner: the Strings lesson; the others link to it. |
| Lesson 3 was a grab-bag | Split into five lessons: Core (RAII and exceptions), Move Semantics, Smart Pointers, Lambdas, Types and Casts. |
| Move semantics spread over three lessons | One lesson (value categories, elision, `noexcept`, sink parameters); the OOP and Templates lessons link to it. |
| "Deduction and forwarding references" in one section | Split: Template argument deduction, then Forwarding references. |
| "Atomics" mixed with the memory model | Separate lesson: Atomics and the Memory Model, with a memory-order simulator. |
| Performance and lock-free in the multithreading lesson | Moved to Low-Latency; multithreading split into three lessons. |
| Lesson 8: strings, regex and time unrelated | **Deliberately kept together** (9 sections): the strings content now has its own sections, and a split would have renumbered every lesson again. |
| Lessons 5 and 9 duplicated | Lesson 15 owns traits, SFINAE, concepts and compile-time computation. |
| Strings split over three lessons | Consolidated in lesson 14. |
| Feed-handler gaps (wire formats, zero copy, order books, pools, queues, latency) | Lessons 17 (Wire Formats and Parsing) and 18 (Low-Latency C++), with compiled programs. |
| Missing Effective Modern C++ terms | All present (`decltype(auto)`, init-capture, braced-init trap, `promise<void>`, `cbegin`). |
| Missing Josuttis terms | `std::exchange`, `swap` and copy-and-swap present. |
| Missing Concurrency in Action terms | Present: happens-before, synchronizes-with, `acq_rel`, fences, `compare_exchange_weak`/`strong`, latch, barrier, semaphore, `atomic_flag`, `shared_future`, work stealing, thread-safe data structures. |
| Missing Principles and Practice terms | Present: `fstream` and `std::format`, `<random>`, `union`, bit manipulation. |
| Other gaps (virtual inheritance, RTTI, functors, conversion operators, placement new, `std::bind`, ranges, literals, `extern "C"`, comparators and hashes, five patterns) | All present: lesson 19 (Object Model), lesson 20 (More Patterns), and short sections in Lambdas, the STL, OOP, Types and Low-Latency. |

### Deliberately dropped

- Splitting regex and `chrono` out of the strings lesson (see above).
- A full treatment of ranges: the STL lesson has a first look, which matches what an interview asks.
- Writing a lock-free pop or a work-stealing pool: explained and drawn, but not implemented, because both need memory reclamation or tuning beyond interview scope.

### Checks run

- All 40 programs in `examples/lessons` compile warning-free with `-std=c++20 -Wall -Wextra` and run with exit code 0.
- Every step-through was stepped through and every arrow was tested against cells and other arrows: no crossings in any step.
- `tools/check-links.mjs` (new): all 805 internal links, anchors included, resolve.
- All lesson pages checked at phone width (375 px): no horizontal page scroll.
- Progress: an old (schema 1) export code imported into a clean browser migrated through schema versions 2, 3 and 4 correctly; the migrations have unit tests and are idempotent.
- The offline cache contains every page, quiz and data file.
