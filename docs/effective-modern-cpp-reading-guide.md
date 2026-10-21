# Reading guide: *Effective Modern C++* (Scott Meyers)

A short reading plan for `effective.pdf` (Scott Meyers, 42 items on C++11 and C++14, about 335 PDF pages). Unlike the other two books in this repo, this one is built from short, self-contained **items**, and each item ends with a "Things to Remember" box. That makes it easy to read selectively and a good source of interview answers. Use the [interactive lessons](https://ghaith-hamdi1.github.io/cpp-training/) first, then read the items below for the topics where you want the longer explanation.

**Page numbers.** The tables give *PDF viewer* page numbers, the number shown in your PDF reader. Items run on from one to the next, so each range includes the page where the next item begins; the first lines of that page may belong to the next item.

The items and their summaries come from the book's table of contents and its "Things to Remember" boxes. I did not read every page in full.

---

## Tier 1: read these first (about 85 pages)

The items on move semantics, smart pointers and concurrency are the ones interviews come back to most often.

| Item | PDF pages | What it teaches | Matching lesson section |
|---|---|---|---|
| **17** Understand special member function generation | 127 to 133 | Which of the default constructor, destructor, copy and move operations the compiler generates, and when it silently does not (for example, declaring a destructor or a copy operation suppresses the move operations). | 2. Copying and the Rule of 3, 5 and 0 |
| **18** Use `std::unique_ptr` for exclusive-ownership resource management | 136 to 143 | `unique_ptr` is small, fast and move-only; custom deleters; converting to `shared_ptr` is easy. | 3. Smart pointers |
| **19** Use `std::shared_ptr` for shared-ownership resource management | 143 to 152 | Twice the size of a raw pointer, a control block, atomic reference counts; custom deleters do not change the pointer's type. | 3. Smart pointers |
| **20** Use `std::weak_ptr` for `shared_ptr`-like pointers that can dangle | 152 to 157 | Caches, observer lists and breaking `shared_ptr` cycles. | 3. Smart pointers; 6. Observer |
| **23** Understand `std::move` and `std::forward` | 176 to 182 | `std::move` is an unconditional cast to an rvalue and moves nothing by itself; `std::forward` casts to an rvalue only if the argument was one. Neither does anything at run time. | 3. Move semantics; 5. Deduction and forwarding references |
| **24** Distinguish universal references from rvalue references | 182 to 186 | `T&&` with a deduced `T` (or `auto&&`) is a universal reference; anything else written `type&&` is an rvalue reference. | 5. Deduction and forwarding references |
| **25** Use `std::move` on rvalue references, `std::forward` on universal references | 186 to 195 | Apply each on the last use. Do not `std::move` a local you return (it defeats the return value optimization). | 3. Move semantics |
| **28** Understand reference collapsing | 215 to 221 | The four contexts where a reference to a reference arises, and the rule: if either is an lvalue reference the result is one. | 5. Deduction and forwarding references |
| **35** Prefer task-based programming to thread-based | 259 to 263 | `std::thread` gives no return value and terminates on an exception; `std::async` handles exhaustion, oversubscription and balancing for you. | 7. Futures and async |
| **36** Specify `std::launch::async` if asynchronicity is essential | 263 to 268 | The default launch policy may run the task synchronously or never. | 7. Futures and async |
| **37** Make `std::thread`s unjoinable on all paths | 268 to 276 | A joinable thread destroyed is a terminate; join-on-destruction and detach-on-destruction both have pitfalls; declare `std::thread` members last. | 7. Your first thread |
| **40** Use `std::atomic` for concurrency, `volatile` for special memory | 289 to 297 | `atomic` is for data shared between threads without a mutex; `volatile` is for memory where reads and writes must not be optimized away. They are different tools. | 7. Atomics |

## Tier 2: read next if you have time (about 160 pages)

| Item | PDF pages | What it teaches | Matching lesson section |
|---|---|---|---|
| **1** Understand template type deduction | 27 to 36 | The three cases (reference or pointer, universal reference, by value); references are ignored for deduction, `const` is dropped for by-value parameters; arrays and functions decay. | 5. Deduction and forwarding references |
| **2** Understand `auto` type deduction | 36 to 41 | `auto` follows the template rules, except that a braced initializer deduces `std::initializer_list`. | 3. Modern syntax tour (the `auto` traps) |
| **5** Prefer `auto` to explicit type declarations | 55 to 61 | `auto` must be initialized, avoids type mismatches and eases refactoring. | 3. Modern syntax tour |
| **7** Distinguish `()` and `{}` when creating objects | 67 to 76 | Braces prevent narrowing and the most vexing parse, but prefer `initializer_list` constructors when one exists, even if another constructor looks like a better match. | 1. Variables and types |
| **12** Declare overriding functions `override` | 97 to 104 | A mismatched signature silently creates a new function without it; reference qualifiers on member functions. | 2. Polymorphism and virtual functions |
| **14** Declare functions `noexcept` if they won't emit exceptions | 108 to 115 | `noexcept` is part of the interface and enables optimization, and it matters most for move operations, `swap` and destructors. | 3. Exceptions and exception safety; Move semantics |
| **15** Use `constexpr` whenever possible | 115 to 121 | `constexpr` objects are `const` with compile-time values; `constexpr` functions can run at compile time. | 3. `const`, `constexpr` and `static` |
| **16** Make `const` member functions thread safe | 121 to 127 | A `const` member that mutates a cached value is a data race unless protected. | 7. Mutexes (the `mutable` mutex) |
| **21** Prefer `make_unique` and `make_shared` to `new` | 157 to 165 | Less duplication, better exception safety, and smaller, faster code for `make_shared`; when not to use them. | 3. Smart pointers |
| **22** Pimpl: define special member functions in the implementation file | 165 to 174 | A `unique_ptr` Pimpl needs the special members declared in the header but defined in the `.cpp`. | 6. Other patterns |
| **26 to 27** Avoid overloading on universal references; alternatives | 195 to 215 | Universal-reference overloads and perfect-forwarding constructors are matched too eagerly. Alternatives: distinct names, pass by value, tag dispatch, `enable_if`. | 5. Type traits and if constexpr |
| **29** Assume move operations are not present, not cheap, and not used | 221 to 225 | In generic code do not assume a move is cheap. | 3. Move semantics |
| **31** Avoid default capture modes | 234 to 242 | `[&]` can dangle; `[=]` can capture `this` and suggests the lambda is self-contained. | 3. Lambdas |
| **32** Use init capture to move objects into closures | 242 to 247 | C++14 `[p = std::move(x)]`. | 3. Lambdas |
| **38** Be aware of varying thread handle destructor behavior | 276 to 280 | The last future of a non-deferred `std::async` task blocks in its destructor. | 7. Futures and async |
| **39** Consider void futures for one-shot event communication | 280 to 289 | Condition-variable, flag and promise/future designs for a single event. | 7. Condition variables |
| **41** Consider pass by value for copyable, cheap-to-move parameters that are always copied | 299 to 310 | Pass by value can be nearly as fast as by reference and simpler, but beware slicing. | 3. Move semantics |
| **42** Consider emplacement instead of insertion | 310 to 320 | When `emplace_back` really is faster than `push_back`. | 4. vector: the workhorse |

## Quick reads you probably know (about 15 minutes in total)

Short items that match things the lessons already cover: **8** prefer `nullptr` (76 to 81), **9** prefer alias declarations to `typedef` (81 to 85), **10** prefer scoped enums (85 to 92), **11** prefer deleted functions to private undefined ones (92 to 97).

## Special focus: move semantics and perfect forwarding

If this is the topic you want to master, read the items in this order. Each builds on the one before.

1. **Item 17** (127 to 133): which move operations the compiler generates.
2. **Item 23** (176 to 182): what `std::move` and `std::forward` really are.
3. **Item 24** (182 to 186): universal references versus rvalue references.
4. **Item 28** (215 to 221): reference collapsing, the mechanism behind forwarding.
5. **Item 25** (186 to 195): when to apply `std::move` and when `std::forward`.
6. **Item 29** (221 to 225): do not assume moves are cheap.
7. **Items 26 and 27** (195 to 215) and **Item 30** (225 to 232): where perfect forwarding goes wrong.

## Special focus: concurrency

Items 35 to 40 (PDF pages 259 to 297) are the book's short concurrency chapter: tasks versus threads, launch policies, joining threads on every path, what future destructors do, one-shot events, and `atomic` versus `volatile`. It is a compact complement to `thread.pdf`, whose reading guide is [here](concurrency-in-action-reading-guide.md). The Meyers items give you the rules and pitfalls; Williams gives you the full machinery.

## Skip for interview preparation

- Item 3 (`decltype`), Item 4 (viewing deduced types), Item 6 (proxy types and `auto`): useful for template authors, rarely asked.
- Item 13 (`const_iterator`), Item 30 if you skip the forwarding focus above, Item 33 (`decltype` on `auto&&` parameters) and Item 34 (lambdas versus `std::bind`).
- The index (PDF pages 321 to the end).

## Notes on the edition

This book covers **C++11 and C++14**. Some advice has since moved on:
- **C++17** guarantees copy elision for temporaries, but the advice not to `std::move` a returned local object still holds.
- **C++20 concepts** and `requires` are now the cleaner way to constrain templates in place of the `enable_if` techniques in Items 26 and 27.
- **C++20 `std::jthread`** joins automatically in its destructor, which removes most of the problem Item 37 describes.
- The book does not cover `std::scoped_lock`, `std::variant`, `std::optional` or structured bindings, which arrived in C++17.
