# Reading plan: *Programming: Principles and Practice Using C++* (3rd Edition)

An ordered plan for reading the book to understand C++ deeply, in 14 sessions. It follows the book's own order, because each part builds on the one before it, but it leaves out the parts that do not help (the calculator parser, the graphics library). For a quick interview-focused pass instead, use the tiers in the [reading guide](programming-principles-and-practice-reading-guide.md).

The book is `books/Programming-Principles-and-Practice-Using-Cpp-3rd-Edition-Stroustrup.pdf`. **All page numbers are PDF viewer pages** (the number your PDF reader shows), taken from the reading guide.

## The plan at a glance

| # | Session | Read (book sections) | PDF pages | Pages | Time |
|---|---|---|---|---|---|
| 1 | Types, initialization, `auto` | 2.5; 2.8 to 2.10 | 49 to 52; 56 to 60 | 9 | 2 h |
| 2 | Functions, `vector`, errors | 3.5 to 3.6; 4.5 to 4.6 | 81 to 89; 102 to 111 | 18 | 3 h |
| 3 | Declarations, scope, arguments | 7.2 to 7.3; **7.4** | 194 to 202; 203 to 218 | 25 | 3 h |
| 4 | Classes and invariants | 8.1 to 8.3; 8.4 to 8.6; **8.7** | 235 to 238; 238 to 249; 250 to 258 | 24 | 3 h |
| 5 | Inheritance and virtual functions | 12.1 to 12.2; **12.3**; 12.4 to 12.5 | 369 to 379; 380 to 387; 388 to 390 | 22 | 3 h |
| 6 | Memory, addresses, pointers | **15.3**; **15.4**; **15.5** | 452 to 454; 455 to 459; 460 to 463 | 12 | 2 h |
| 7 | Arrays, `this`, alternatives to raw pointers | 15.6 to 15.8; 16.1 to 16.4 | 464 to 473; 477 to 487 | 20 | 2 h |
| 8 | Copying, moving, `vector` growth | **17.4 to 17.5**; 17.6 to 17.9 | 501 to 512; 513 to 523 | 22 | 3 h |
| 9 | Templates and concepts | 18.1 to 18.3 (focus on 18.1.2 to 18.1.4) | 527 to 541 | 15 | 2 h |
| 10 | RAII, exceptions, smart pointers | 18.4 to 18.5 | 542 to 553 | 12 | 3 h |
| 11 | Containers and iterators | 19.1 to 19.3, 19.6; 20.1 to 20.2 | 559 to 572, 585 to 586; 591 to 598 | 28 | 3 h |
| 12 | Choosing a container | 20.3 to 20.5; **20.6 to 20.7.1** | 598 to 604; 604 to 612 | 20 | 2 h |
| 13 | Algorithms | **21.1**; 21.2; 21.5 | 617 to 622; 623 to 626; 633 to 635 | 16 | 2 h |
| 14 | Optional extras | 9.11; 19.4; 21.3 to 21.4 | 296 to 297; 573 to 578; 627 to 632 | 14 | 2 h |

Bold sections are the ones to read most carefully. In all it is about 35 hours across roughly 255 pages, which is 4 to 6 weeks at one session every two or three days. Time estimates assume about 10 pages an hour plus the writing and checkpoint work; they are guides, not deadlines.

## How to read each session

| Step | Do |
|---|---|
| 1. Read | Read the pages once with the code closed. Note every sentence that surprises you. |
| 2. Write | Close the book and write the small program the pages teach (a `Vector`, a class with an invariant, a copy constructor). Compile with `g++ -std=c++20 -Wall -Wextra`. Open the book only to compare. |
| 3. Explain | Answer the checkpoint questions aloud. If you cannot answer one in two sentences, reread that part. |
| 4. Reinforce | Do the "after" step: the repo lesson, quiz or practice exercise named for the session. |

## Part A: the language basics (sessions 1 to 3)

| # | Checkpoint questions | After |
|---|---|---|
| 1 | Why is `int x{7.5};` an error while `int x = 7.5;` compiles?<br>What does `auto` deduce, and what does it drop?<br>Which conversions can lose information? | Lesson 2 (Types, Initialization and Casts); practice 09 |
| 2 | When should a function report an error by exception and when by return value?<br>What is the difference between a logic error and a run-time error? | Lesson 5 (exceptions) and its quiz |
| 3 | Pass by value, by reference and by `const` reference: when do you use each?<br>What does a declaration promise that a definition delivers?<br>Where does each kind of variable live (stack, static data, free store)? | Lesson 1 (passing-arguments step-through) and its quiz |

## Part B: classes and object-oriented design (sessions 4 and 5)

| # | Checkpoint questions | After |
|---|---|---|
| 4 | What is an **invariant**, and how does a constructor enforce it?<br>Why does the book keep the representation private?<br>What belongs in a class's interface ("as small as possible, but no smaller")?<br>Why mark a member function `const`? | Lesson 3 (OOP), sections 1 to 4; practice 10 up to its constructor (`MyString`) |
| 5 | How is a derived object laid out in memory, and what is the vptr?<br>Why does the base class need a virtual destructor?<br>Why does the book delete the copy operations of a base class?<br>Interface inheritance versus implementation inheritance? | Lesson 3 (polymorphism) and lesson 4 (The Object Model in Depth); practice 11 (Shapes) |

Session 5 answers "how does `virtual` work in memory". Explain the vptr and vtable aloud before moving on.

## Part C: memory, pointers, templates and ownership (sessions 6 to 10)

These sessions are the heart of the book. Do not skip them.

| # | Checkpoint questions | After |
|---|---|---|
| 6 | Why does a pointer not know how many elements it points to?<br>`delete` versus `delete[]`: what goes wrong if you mix them?<br>What are the four ways a raw pointer causes a crash (uninitialized, out of range, dangling, double delete)?<br>What does a destructor release, and in what order are members destroyed? | Lesson 1 (pointers); practice 01, 02, 03. Do 01 (`buildExecutionId`) from memory with a timer |
| 7 | When do you pass a pointer and when a reference?<br>What replaces a (pointer, count) pair (`span`) and a possibly-null pointer (`not_null`)?<br>How does a reference differ from a pointer in reassignment? | Practice 05, 06, 07, 08, 09; quiz for lesson 1 |
| 8 | What is a shallow copy, and why is it a bug for a class that owns memory?<br>What are the "essential operations", the rule of zero and the rule of all?<br>How does `vector` grow: what do `reserve`, `resize` and `push_back` each do?<br>What state is a moved-from object in? | Lesson 6 (Move Semantics); practice 10 (`MyString`, Rule of Five), written fully from memory |
| 9 | Templates versus virtual functions: what is resolved at compile time and what at run time?<br>What is a concept, and what does it improve (errors at the call site)?<br>Why is `vector<Circle>` not a `vector<Shape>`? | Lesson 11 (Templates), first three sections; practice 12 (`Stack<T>`) |
| 10 | What is RAII, and how does it remove the need for `try`/`finally`?<br>Why return a moved object instead of a free-store pointer ("who deletes it?")?<br>What are `unique_ptr` and `shared_ptr` for, and which is the default? | Lesson 5 (RAII) and lesson 7 (Smart Pointers and Ownership) |

The book stops at introductory templates. Variadic templates, forwarding references, specialization and type traits are not in it; use lessons 11 and 12.

## Part D: the standard library (sessions 11 to 13)

| # | Checkpoint questions | After |
|---|---|---|
| 11 | How does generalizing a loop over an array lead to iterators and `[first, last)` ranges?<br>What does `++words[s]` do when `s` is not yet a key? | Lesson 10 (The STL), sections 1 to 4; its quiz |
| 12 | Why is `vector` the default container?<br>Name the six iterator categories and which container gives which.<br>Why measure before claiming something is faster, and how do you stop the optimizer deleting your test? | Lesson 10, "Which container should I use?"; time `find` in a `vector` against a `map` with `<chrono>` |
| 13 | How do algorithms report "not found"?<br>Why do `binary_search` and `equal_range` need a sorted sequence?<br>How does a lambda differ from a function object? | Lessons 10 (Algorithms) and 8 (Lambdas); quiz for lesson 10 |

## Part E: optional extras (session 14)

| # | Read | After |
|---|---|---|
| 14 | Any of: 9.11 String streams; 19.4 Generalizing `Vector` again; 21.3 to 21.4 Numerical algorithms and copying | Lesson 9 (Strings, Regex and Time) |

## What to skip

| Skip | Why |
|---|---|
| Chapter 1 | hello world and the build process |
| Chapters 5 and 6 | building a calculator parser |
| Chapter 9, except 9.11 | stream I/O details |
| Chapters 10 to 14, except 12.1 to 12.5 | about 150 pages on a graphics and GUI library |
| 20.7 beyond iterator categories, and the index | not needed |

## What this book will not teach you

| Topic | Where to learn it |
|---|---|
| Threads, mutexes, atomics | the Williams book in `books/`; lessons 15 to 17 |
| Design patterns | lessons 13 and 14 |
| The memory model and low-latency C++ | lessons 17 and 19 |
| Variadic templates, forwarding references, SFINAE | lessons 11 and 12 |
| Interview-style depth | the lessons' quizzes and cheat sheets |

## Notes on the edition

The book's examples start with `import std;` and `using namespace std;` (C++20 modules), and its section 0.4 recommends `#include "PPP.h"`. That header gives range-checked `vector` subscripting and a convenient `error()` function; the author's support files are on the book's website. To compile the examples with plain g++, replace the support line with the ordinary `#include` lines for the standard headers you use.
