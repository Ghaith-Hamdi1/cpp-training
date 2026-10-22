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
| **18** Use `std::unique_ptr` for exclusive-ownership resource management | 136 to 143 | `unique_ptr` is small, fast and move-only; custom deleters; converting to `shared_ptr` is easy. | 5. Smart pointers |
| **19** Use `std::shared_ptr` for shared-ownership resource management | 143 to 152 | Twice the size of a raw pointer, a control block, atomic reference counts; custom deleters do not change the pointer's type. | 5. Smart pointers |
| **20** Use `std::weak_ptr` for `shared_ptr`-like pointers that can dangle | 152 to 157 | Caches, observer lists and breaking `shared_ptr` cycles. | 5. Smart pointers; 10. Observer |
| **23** Understand `std::move` and `std::forward` | 176 to 182 | `std::move` is an unconditional cast to an rvalue and moves nothing by itself; `std::forward` casts to an rvalue only if the argument was one. Neither does anything at run time. | 4. Move semantics; 9. Forwarding references and perfect forwarding |
| **24** Distinguish universal references from rvalue references | 182 to 186 | `T&&` with a deduced `T` (or `auto&&`) is a universal reference; anything else written `type&&` is an rvalue reference. | 9. Forwarding references and perfect forwarding |
| **25** Use `std::move` on rvalue references, `std::forward` on universal references | 186 to 195 | Apply each on the last use. Do not `std::move` a local you return (it defeats the return value optimization). | 4. Move semantics |
| **28** Understand reference collapsing | 215 to 221 | The four contexts where a reference to a reference arises, and the rule: if either is an lvalue reference the result is one. | 9. Forwarding references and perfect forwarding |
| **35** Prefer task-based programming to thread-based | 259 to 263 | `std::thread` gives no return value and terminates on an exception; `std::async` handles exhaustion, oversubscription and balancing for you. | 12. Futures and async |
| **36** Specify `std::launch::async` if asynchronicity is essential | 263 to 268 | The default launch policy may run the task synchronously or never. | 12. Futures and async |
| **37** Make `std::thread`s unjoinable on all paths | 268 to 276 | A joinable thread destroyed is a terminate; join-on-destruction and detach-on-destruction both have pitfalls; declare `std::thread` members last. | 11. Your first thread |
| **40** Use `std::atomic` for concurrency, `volatile` for special memory | 289 to 297 | `atomic` is for data shared between threads without a mutex; `volatile` is for memory where reads and writes must not be optimized away. They are different tools. | 13. Atomic operations |

## Tier 2: read next if you have time (about 160 pages)

| Item | PDF pages | What it teaches | Matching lesson section |
|---|---|---|---|
| **1** Understand template type deduction | 27 to 36 | The three cases (reference or pointer, universal reference, by value); references are ignored for deduction, `const` is dropped for by-value parameters; arrays and functions decay. | 9. Template argument deduction |
| **2** Understand `auto` type deduction | 36 to 41 | `auto` follows the template rules, except that a braced initializer deduces `std::initializer_list`. | 7. auto, decltype and modern syntax (the `auto` traps) |
| **5** Prefer `auto` to explicit type declarations | 55 to 61 | `auto` must be initialized, avoids type mismatches and eases refactoring. | 7. auto, decltype and modern syntax |
| **7** Distinguish `()` and `{}` when creating objects | 67 to 76 | Braces prevent narrowing and the most vexing parse, but prefer `initializer_list` constructors when one exists, even if another constructor looks like a better match. | 1. Variables and types |
| **12** Declare overriding functions `override` | 97 to 104 | A mismatched signature silently creates a new function without it; reference qualifiers on member functions. | 2. Polymorphism and virtual functions |
| **14** Declare functions `noexcept` if they won't emit exceptions | 108 to 115 | `noexcept` is part of the interface and enables optimization, and it matters most for move operations, `swap` and destructors. | 3. Exception-safety guarantees and noexcept; Move semantics |
| **15** Use `constexpr` whenever possible | 115 to 121 | `constexpr` objects are `const` with compile-time values; `constexpr` functions can run at compile time. | 7. `const`, `constexpr` and `static` |
| **16** Make `const` member functions thread safe | 121 to 127 | A `const` member that mutates a cached value is a data race unless protected. | 11. Mutexes (the `mutable` mutex) |
| **21** Prefer `make_unique` and `make_shared` to `new` | 157 to 165 | Less duplication, better exception safety, and smaller, faster code for `make_shared`; when not to use them. | 5. Smart pointers |
| **22** Pimpl: define special member functions in the implementation file | 165 to 174 | A `unique_ptr` Pimpl needs the special members declared in the header but defined in the `.cpp`. | 10. Other patterns |
| **26 to 27** Avoid overloading on universal references; alternatives | 195 to 215 | Universal-reference overloads and perfect-forwarding constructors are matched too eagerly. Alternatives: distinct names, pass by value, tag dispatch, `enable_if`. | 9. Type traits and if constexpr |
| **29** Assume move operations are not present, not cheap, and not used | 221 to 225 | In generic code do not assume a move is cheap. | 4. Move semantics |
| **31** Avoid default capture modes | 234 to 242 | `[&]` can dangle; `[=]` can capture `this` and suggests the lambda is self-contained. | 6. Lambdas |
| **32** Use init capture to move objects into closures | 242 to 247 | C++14 `[p = std::move(x)]`. | 6. Lambdas |
| **38** Be aware of varying thread handle destructor behavior | 276 to 280 | The last future of a non-deferred `std::async` task blocks in its destructor. | 12. Futures and async |
| **39** Consider void futures for one-shot event communication | 280 to 289 | Condition-variable, flag and promise/future designs for a single event. | 11. Condition variables |
| **41** Consider pass by value for copyable, cheap-to-move parameters that are always copied | 299 to 310 | Pass by value can be nearly as fast as by reference and simpler, but beware slicing. | 4. Move semantics |
| **42** Consider emplacement instead of insertion | 310 to 320 | When `emplace_back` really is faster than `push_back`. | 8. vector: the workhorse |

## Quick reads you probably know (about 15 minutes in total)

Short items that match things the lessons already cover: **8** prefer `nullptr` (76 to 81), **9** prefer alias declarations to `typedef` (81 to 85), **10** prefer scoped enums (85 to 92), **11** prefer deleted functions to private undefined ones (92 to 97).

## Special focus: move semantics and perfect forwarding

Move semantics is concentrated in Chapter 5 (PDF pages 175 to 232), with important pieces in other chapters. The chapter's opening makes the book's stance clear: `std::move` does not move anything, perfect forwarding is imperfect, and moves are not always cheaper than copies. Matching lessons: **4. Move Semantics** (lvalues and rvalues, `std::move`, elision), **5. Smart Pointers and Ownership** and **9. Templates** (forwarding references).

Read the items in this order. Each builds on the one before.

| Step | Item | PDF pages | What it teaches | Matching lesson section |
|---|---|---|---|---|
| 1 | **17** Understand special member function generation | 127 to 133 | Moves are generated only for a class that declares no copy operations, move operations or destructor. Adding a destructor later silently turns moves into copies, and the code still compiles and passes tests. `= default` for polymorphic bases. | 2. Copying and the Rule of 3, 5 and 0 |
| 2 | **23** Understand `std::move` and `std::forward` | 176 to 182 | Both are casts that generate no code. A sample implementation of `std::move`. **The `const` trap:** `std::move` on a `const` object silently copies, because a `const` rvalue cannot bind to the move constructor. | 4. Move semantics |
| 3 | **24** Distinguish universal references from rvalue references | 182 to 186 | `T&&` with a deduced `T` (or `auto&&`) is a universal reference. Any other form `type&&` is an rvalue reference. | 9. Forwarding references and perfect forwarding |
| 4 | **28** Understand reference collapsing | 215 to 221 | The four contexts where a reference to a reference arises, and the rule: if either is an lvalue reference, so is the result. This is the mechanism behind forwarding. | 9. Forwarding references and perfect forwarding |
| 5 | **25** Use `std::move` on rvalue references, `std::forward` on universal references | 186 to 195 | Apply each on its last use. **Returning by value:** the return value optimization (RVO) conditions, why `return std::move(local)` hinders it, and why the compiler must treat a returned local or by-value parameter as an rvalue if it does not elide the copy. | 4. Move semantics |
| 6 | **29** Assume that move operations are not present, not cheap, and not used | 221 to 225 | Types without move support gain nothing. A `std::array` move is linear, not constant. A `std::string` with the small string optimization can move no faster than it copies. Be conservative in generic code and look up the facts for known types. | 4. Move semantics |
| 7 | **14** Declare functions `noexcept` if they won't emit exceptions | 108 to 115 | Why `std::vector` growth moves its elements only when the move cannot throw (`std::move_if_noexcept`), to keep the strong exception guarantee. `noexcept` matters most for move operations, `swap` and destructors. | 3. Exception-safety guarantees and noexcept |
| 8 | **26 to 27** and **30** Overloading on universal references; perfect forwarding failure cases | 195 to 215 and 225 to 232 | Universal-reference overloads and perfect-forwarding constructors are matched too eagerly. Alternatives: distinct names, pass by value, tag dispatch, `enable_if`. Arguments that defeat perfect forwarding: braced initializers, `0` or `NULL` as a null pointer, overloaded function names, bitfields. | 9. Type traits and if constexpr |
| optional | **18** `std::unique_ptr` | 136 to 143 | A small, fast, move-only smart pointer. | 5. Smart pointers |
| optional | **22** Pimpl: define special member functions in the implementation file | 165 to 174 | A `unique_ptr` Pimpl needs the special members declared in the header but defined in the `.cpp`. | 10. Other patterns |
| optional | **32** Use init capture to move objects into closures | 242 to 247 | C++14 `[p = std::move(x)]`. | 6. Lambdas |
| optional | **41** Consider pass by value for copyable parameters that are cheap to move and always copied | 299 to 310 | Where a cheap move makes pass by value attractive, and the slicing caveat. | 4. Move semantics |

**If you only have time for part of it:** read steps 2, 5 and 6 (Items 23, 25 and 29, about 22 pages). They cover the `const` trap, the RVO rules and the performance caveats, which are the questions interviews come back to.

**What the book barely covers, so use the lesson or another book for it:**
- There is no dedicated treatment of the **moved-from state** ("valid but unspecified"); I found no mention of it.
- It does not use the terms xvalue, prvalue or glvalue.
- It does not cover `std::exchange` or use the name "Rule of Five" (Item 17 discusses the Rule of Three and when moves are generated).
- It predates C++17's guaranteed copy elision.
- It gives little on writing your own move constructor and move assignment step by step.

For those gaps, my Lesson 4 covers the moved-from rules and a worked move constructor, and the [reading guide for *C++ Move Semantics: The Complete Guide*](move-semantics-complete-guide-reading-guide.md) points to where that book treats value categories and the moved-from state in full.

**Key ideas to take away**
- `std::move` is only a cast to an rvalue, and `std::forward` is a cast that preserves the original value category. Neither does anything at run time.
- `std::move` on a `const` object copies, and `return std::move(local)` makes returning by value slower.
- Do not assume a move is cheap or even happening: it needs a move operation to exist (Item 17), to be `noexcept` where containers care (Item 14), and to beat a copy for that type (Item 29).
- `T&&` is only an rvalue reference when no type deduction is involved. Otherwise it is a universal reference.

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
