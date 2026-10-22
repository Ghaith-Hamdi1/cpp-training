# Reading plan: *Programming: Principles and Practice Using C++* (3rd Edition)

An ordered plan for reading the book to understand C++ deeply, in 14 sessions. It follows the book's own order, because each part builds on the one before it, but it leaves out the parts that do not help (the calculator parser, the graphics library). For a quick interview-focused pass instead, use the tiers in the [reading guide](programming-principles-and-practice-reading-guide.md).

The book is `books/Programming-Principles-and-Practice-Using-Cpp-3rd-Edition-Stroustrup.pdf`. **All page numbers are PDF viewer pages** (the number your PDF reader shows), taken from the reading guide.

## How to read each session

1. **Read first, with the code closed.** Read the pages once without typing anything. Note every sentence that surprises you.
2. **Close the book and write it from memory.** Write the small program the pages teach (a `Vector`, a class with an invariant, a copy constructor) and compile it with `g++ -std=c++20 -Wall -Wextra`. Open the book only to compare.
3. **Answer the checkpoint questions aloud.** If you cannot answer one in two sentences, reread that part.
4. **Do the "after" step.** Each session names the repo lesson, quiz and practice exercise that reinforce it.

Time estimates assume about 10 pages an hour for reading plus the writing and checkpoint work. They are guides, not deadlines.

## Part A: the language basics (sessions 1 to 3)

### Session 1: types, initialization and `auto` (about 2 hours)
- **Read:** 2.5 Assignment and initialization (pp. 49 to 52) and 2.8 to 2.10 Type safety, conversions, type deduction with `auto` (pp. 56 to 60). About 9 pages.
- **Checkpoint questions:**
  - Why is `int x{7.5};` an error while `int x = 7.5;` compiles?
  - What does `auto` deduce, and what does it drop?
  - Which conversions can lose information?
- **After:** lesson 7 (Types, Initialization and Casts); the practice exercise 09 (pointers and arrays warm-up).

### Session 2: functions, `vector` and errors (about 3 hours)
- **Read:** 3.5 to 3.6 Functions and `vector` introduced (pp. 81 to 89), and 4.5 to 4.6 Run-time errors and exceptions (pp. 102 to 111). About 18 pages.
- **Checkpoint questions:**
  - When should a function report an error by exception, and when by return value?
  - What is the difference between a logic error and a run-time error?
- **After:** lesson 3 (Core Language: exceptions); quiz for lesson 3.

### Session 3: declarations, scope, passing arguments (about 3 hours)
- **Read:** 7.2 to 7.3 Declarations and definitions, scope (pp. 194 to 202) and **7.4 Function call and return** (pp. 203 to 218). About 25 pages.
- **Checkpoint questions:**
  - What is the difference between pass by value, by reference and by `const` reference, and when do you use each?
  - What does a declaration promise that a definition delivers?
  - Where does each kind of variable live (stack, static data, free store)?
- **After:** lesson 1 (Basics and Pointers), the passing-arguments step-through; quiz for lesson 1.

## Part B: classes and object-oriented design (sessions 4 and 5)

### Session 4: classes as a way to keep objects valid (about 3 hours)
- **Read:** 8.1 to 8.3 User-defined types, classes, interface and implementation (pp. 235 to 238); 8.4 to 8.6 evolving the `Date` class, enumerations, operator overloading (pp. 238 to 249); **8.7 Class interfaces** (pp. 250 to 258). About 24 pages.
- **Checkpoint questions:**
  - What is an **invariant**, and how does a constructor enforce it?
  - Why does the book keep the representation private?
  - What belongs in a class's interface and what does not ("as small as possible, but no smaller")?
  - Why mark a member function `const`?
- **After:** lesson 2 (OOP), sections 1 to 4; practice exercise 10 up to its constructor (`MyString`).

### Session 5: inheritance and virtual functions (about 3 hours)
- **Read:** 12.1 to 12.2 Design principles, `Shape` abstract class (pp. 369 to 379) and **12.3 Base and derived classes** (pp. 380 to 387), 12.4 to 12.5 Copying a hierarchy, benefits of OOP (pp. 388 to 390). About 22 pages.
- **Checkpoint questions:**
  - How is a derived object laid out in memory, and what is the vptr?
  - Why does the base class need a virtual destructor?
  - Why does the book delete the copy operations of a base class?
  - What is the difference between interface inheritance and implementation inheritance?
- **After:** lesson 2 (polymorphism) and lesson 19 (The Object Model in Depth); practice exercise 11 (Shapes). This session answers "how does `virtual` work in memory", so explain the vptr and vtable aloud before moving on.

## Part C: memory, pointers, templates and ownership (sessions 6 to 10)

These sessions are the heart of the book. Do not skip them.

### Session 6: memory, addresses and pointers (about 2 hours)
- **Read:** **15.3 Memory, addresses and pointers** (pp. 452 to 454), **15.4 Free store and pointers** (pp. 455 to 459), **15.5 Destructors** (pp. 460 to 463). About 12 pages.
- **Checkpoint questions:**
  - Why does a pointer not know how many elements it points to?
  - What are the differences between `delete` and `delete[]`, and what goes wrong if you mix them?
  - What are the four ways a raw pointer causes a crash (uninitialized, out of range, dangling, double delete)?
  - What does a destructor release, and in what order are members destroyed?
- **After:** lesson 1 (pointers); practice exercises 01, 02, 03 (C strings). Do 01 (`buildExecutionId`) from memory with a timer.

### Session 7: arrays, `this` and the alternatives to raw pointers (about 2 hours)
- **Read:** 15.6 to 15.8 Element access, an example list, the `this` pointer (pp. 464 to 473) and 16.1 to 16.4 Arrays, pointers and references, C-style strings, alternatives to pointers (pp. 477 to 487). About 20 pages.
- **Checkpoint questions:**
  - When do you pass a pointer, and when a reference?
  - What replaces a (pointer, count) pair in modern code (`span`) and a possibly-null pointer (`not_null`)?
  - What is the difference between a reference and a pointer in how they can be reassigned?
- **After:** practice exercises 05, 06, 07, 08, 09 (pointer walking and parsing); quiz for lesson 1.

### Session 8: copying, moving and `vector` that grows (about 3 hours)
- **Read:** **17.4 to 17.5 Copying and moving; essential operations** (pp. 501 to 512) and 17.6 to 17.9 Other operations, remaining `Vector` problems, changing size (pp. 513 to 523). About 22 pages.
- **Checkpoint questions:**
  - What is a shallow copy and why is it a bug for a class that owns memory?
  - What are the "essential operations", and what are the rule of zero and the rule of all?
  - How does `vector` grow, and what do `reserve`, `resize` and `push_back` each do?
  - What state is a moved-from object in?
- **After:** lesson 4 (Move Semantics); practice exercise 10 (`MyString`, Rule of Five). Write it fully from memory.

### Session 9: templates and concepts (about 2 hours)
- **Read:** 18.1 to 18.3 Templates, generalizing `Vector`, range checking and exceptions (pp. 527 to 541). About 15 pages. Pay most attention to **18.1.2 Generic programming** (pp. 530 to 531), **18.1.3 Concepts** (pp. 531 to 533) and **18.1.4 Containers and inheritance** (pp. 533 to 534).
- **Checkpoint questions:**
  - Templates versus virtual functions: what is resolved at compile time and what at run time?
  - What is a concept, and what does it improve (error messages at the call site)?
  - Why is `vector<Circle>` not a `vector<Shape>`?
- **After:** lesson 9 (Templates), the first three sections; practice exercise 12 (`Stack<T>`).
- **Note:** the book stops here. Variadic templates, forwarding references, specialization and type traits are not in it; use lessons 9 and 15 for those.

### Session 10: RAII, exceptions and smart pointers (about 3 hours)
- **Read:** 18.4 to 18.5 Resources and exceptions, resource-management pointers (pp. 542 to 553). About 12 pages.
- **Checkpoint questions:**
  - What is RAII, and how does it remove the need for `try`/`finally`?
  - Why return a moved object instead of a free-store pointer ("who deletes it?")?
  - What are `unique_ptr` and `shared_ptr` for, and which is the default?
- **After:** lesson 3 (RAII) and lesson 5 (Smart Pointers and Ownership).

## Part D: the standard library (sessions 11 to 13)

### Session 11: containers and iterators (about 3 hours)
- **Read:** 19.1 to 19.3 and 19.6 Containers, sequences and iterators, linked lists, `vector`/`list`/`string` (pp. 559 to 572 and 585 to 586), then 20.1 to 20.2 `map` (pp. 591 to 598). About 28 pages.
- **Checkpoint questions:**
  - How does generalizing a loop over an array lead to iterators and `[first, last)` ranges?
  - What does `++words[s]` do when `s` is not yet a key?
- **After:** lesson 8 (The STL), sections 1 to 4; quiz for lesson 8.

### Session 12: choosing a container (about 2 hours)
- **Read:** 20.3 and 20.5 `unordered_map` and `set` (pp. 598 to 599 and 602 to 604), 20.4 Timing (pp. 599 to 602) and **20.6 to 20.7.1 Container overview and iterator categories** (pp. 604 to 612). About 20 pages.
- **Checkpoint questions:**
  - Why is `vector` the default container?
  - Name the six iterator categories and which container gives which.
  - Why must you measure before claiming something is faster, and how do you stop the optimizer deleting your test?
- **After:** lesson 8, "Which container should I use?"; practice by timing `find` in a `vector` against a `map` with `<chrono>`.

### Session 13: algorithms (about 2 hours)
- **Read:** **21.1 Standard algorithms** (pp. 617 to 622), 21.2 Function objects and lambdas (pp. 623 to 626), 21.5 Sorting and searching (pp. 633 to 635). About 16 pages.
- **Checkpoint questions:**
  - How do algorithms report "not found"?
  - Why do `binary_search` and `equal_range` need a sorted sequence?
  - How does a lambda differ from a function object?
- **After:** lesson 8 (Algorithms) and lesson 6 (Lambdas); quiz for lesson 8.

## Part E: optional extras (session 14)

### Session 14: streams and finishing touches (about 2 hours)
- **Read, any of:** 9.11 String streams (pp. 296 to 297); 19.4 Generalizing `Vector` again (pp. 573 to 578); 21.3 to 21.4 Numerical algorithms and copying (pp. 627 to 632).
- **After:** lesson 14 (Strings, Regex and Time).

## What to skip

- Chapter 1 (hello world and the build process), chapters 5 and 6 (the calculator parser).
- Chapter 9 except 9.11.
- Chapters 10 to 14 (the graphics and GUI library). Chapter 12.1 to 12.5 above is the only part of that range worth reading.
- 20.7 beyond iterator categories, and the index.

## Total

About 35 hours of reading and writing across the 14 sessions, covering roughly 255 pages. At one session every two or three days this is a 4 to 6 week plan.

## What this book will not teach you

Use the repo's lessons, or the other books in `books/`, for these topics: threads, mutexes and atomics (the Williams book); design patterns (lessons 6 and 20); the memory model and low-latency C++ (lessons 13 and 18); variadic templates, forwarding references and SFINAE (lessons 9 and 15); and interview-style depth (the lessons' quizzes and cheat sheets).

## Notes on the edition

The book's examples start with `import std;` and `using namespace std;` (C++20 modules), and its section 0.4 recommends `#include "PPP.h"`. That header gives range-checked `vector` subscripting and a convenient `error()` function; the author's support files are on the book's website. To compile the examples with plain g++, replace the support line with the ordinary `#include` lines for the standard headers you use.
