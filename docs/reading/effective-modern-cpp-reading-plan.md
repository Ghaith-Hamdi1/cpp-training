# Reading plan: *Effective Modern C++* (Scott Meyers)

An ordered plan for reading the book in seven sessions, picking the items that deepen the lessons and skipping the rest. The book is made of short, self-contained items, so each session is a handful of items on one theme. For the tiers and the reasons behind each pick, see the [reading guide](effective-modern-cpp-reading-guide.md).

The book is `books/Effective-Modern-Cpp-Meyers.pdf` (C++11 and C++14). **All page numbers are PDF viewer pages.** Items run on from one to the next, so each range includes the page where the next item begins.

## The plan at a glance

| # | Session | Items | PDF pages | Pages | Time |
|---|---|---|---|---|---|
| 1 | Deduction, `auto`, initialization | 1, 2, 5, 7 | 27 to 41; 55 to 61; 67 to 76 | 29 | 3 h |
| 2 | Interfaces that say what they mean | 12, 14, 15, 16 | 97 to 127 | 26 | 3 h |
| 3 | Special members and smart pointers | 17, 18, 19, 20, 21, 22 | 127 to 174 | 44 | 4 h |
| 4 | `std::move`, `std::forward`, universal references | 23, 24, 25, 28 | 176 to 195; 215 to 221 | 25 | 3 h |
| 5 | Overloading and moves in practice | 26 to 27, 29, 41, 42 | 195 to 215; 221 to 225; 299 to 320 | 45 | 4 h |
| 6 | Lambdas | 31, 32 | 234 to 247 | 13 | 1.5 h |
| 7 | Concurrency | 35 to 40 | 259 to 297 | 38 | 4 h |

About 220 pages and 22 hours, at roughly 10 pages an hour plus the checkpoint work. If you have time, the four quick items 8 to 11 (`nullptr`, alias declarations, scoped enums, deleted functions; PDF pages 76 to 97) fit before session 2.

## How to read each session

| Step | Do |
|---|---|
| 1. Read | Read each item, then its "Things to Remember" box, with the code closed. |
| 2. Reproduce | Compile the book's key example yourself and change it until the behaviour surprises you (`g++ -std=c++20 -Wall -Wextra`). |
| 3. Explain | Answer the checkpoint questions aloud in two sentences each. |
| 4. Reinforce | Do the "after" step: the lesson section and quiz named for the session. |

## Session 1: deduction, `auto` and initialization

| Read | PDF pages |
|---|---|
| Item 1, template type deduction | 27 to 36 |
| Item 2, `auto` type deduction | 36 to 41 |
| Item 5, prefer `auto` to explicit types | 55 to 61 |
| Item 7, `()` versus `{}` when creating objects | 67 to 76 |

1. What are the three cases of template deduction, and what happens to references and `const` in each?
2. How does `auto` differ from template deduction for a braced initializer?
3. Why can `{}` pick an `initializer_list` constructor you did not expect?

After: Lesson 8 (Templates, argument deduction), Lesson 2 (Types, `auto` and braces) and their quizzes.

## Session 2: interfaces that say what they mean

| Read | PDF pages |
|---|---|
| Item 12, declare overriding functions `override` | 97 to 104 |
| Item 14, `noexcept` | 108 to 115 |
| Item 15, `constexpr` | 115 to 121 |
| Item 16, make `const` member functions thread safe | 121 to 127 |

1. What does `override` catch that a plain redeclaration does not?
2. Why does `std::vector` move its elements on growth only if the move is `noexcept`?
3. When is a `const` member function a data race, and what does `mutable` have to do with it?

After: Lesson 3 (OOP, polymorphism), Lesson 9 (Core, `noexcept`), Lesson 13 (`constexpr`) and Lesson 16 (Multithreading, mutexes).

## Session 3: special members and smart pointers

| Read | PDF pages |
|---|---|
| Item 17, special member function generation | 127 to 133 |
| Items 18 to 20, `unique_ptr`, `shared_ptr`, `weak_ptr` | 136 to 157 |
| Item 21, prefer `make_unique` and `make_shared` | 157 to 165 |
| Item 22, Pimpl: special members in the `.cpp` | 165 to 174 |

1. Which special members does a declared destructor suppress, and what does the compiler do instead?
2. What is in a `shared_ptr`'s control block, and why is a custom deleter not part of its type?
3. When should you not use `make_shared`?

After: Lesson 3 (Rule of 3, 5, 0), Lesson 12 (Smart pointers) and Lesson 14 (Pimpl under other patterns).

## Session 4: `std::move`, `std::forward` and universal references

| Read | PDF pages |
|---|---|
| Item 23, `std::move` and `std::forward` | 176 to 182 |
| Item 24, universal references versus rvalue references | 182 to 186 |
| Item 25, `move` on rvalue references, `forward` on universal ones | 186 to 195 |
| Item 28, reference collapsing | 215 to 221 |

1. Why does `std::move` on a `const` object copy?
2. How do you tell a universal reference from an rvalue reference?
3. Why does `return std::move(local)` hurt?

After: Lesson 11 (Move semantics) and Lesson 8 (forwarding references).

## Session 5: overloading and moves in practice

| Read | PDF pages |
|---|---|
| Items 26 to 27, universal-reference overloads and their alternatives | 195 to 215 |
| Item 29, assume moves are not present, not cheap, not used | 221 to 225 |
| Item 41, pass by value for cheap-to-move, always-copied parameters | 299 to 310 |
| Item 42, emplacement instead of insertion | 310 to 320 |

1. Why does a forwarding constructor hijack calls you meant for the copy constructor?
2. Name two ways to avoid overloading on universal references.
3. When is `emplace_back` really faster than `push_back`?

After: Lesson 11, Lesson 13 (tag dispatch, `enable_if`, concepts) and Lesson 6 (vector).

## Session 6: lambdas

| Read | PDF pages |
|---|---|
| Item 31, avoid default capture modes | 234 to 242 |
| Item 32, init capture to move objects into closures | 242 to 247 |

1. Why is `[=]` inside a member function not self-contained?
2. How do you move a `unique_ptr` into a lambda?

After: Lesson 7 (Lambdas) and its quiz.

## Session 7: concurrency

| Read | PDF pages |
|---|---|
| Item 35, prefer tasks to threads | 259 to 263 |
| Item 36, specify `std::launch::async` if it matters | 263 to 268 |
| Item 37, make threads unjoinable on all paths | 268 to 276 |
| Item 38, thread handle destructor behaviour | 276 to 280 |
| Item 39, void futures for one-shot events | 280 to 289 |
| Item 40, `std::atomic` versus `volatile` | 289 to 297 |

1. What does the default launch policy risk, and what does a future from `async` do in its destructor?
2. Why is a joinable `std::thread` destroyed a `std::terminate`?
3. What is `volatile` for, and why is it not a synchronization tool?

After: Lessons 16 to 18 (Multithreading, Tasks, Atomics) and their quizzes.

## Skip, and a note on the edition

Skip Items 3, 4, 6, 13, 30, 33 and 34, and the index. The book covers C++11 and C++14: C++17 guarantees copy elision for temporaries, C++20 concepts replace the `enable_if` tricks in Items 26 and 27, and `std::jthread` removes most of the problem in Item 37.

Notes templates, one file per session: [docs/reading/notes/effective-modern-cpp](notes/effective-modern-cpp/README.md).
