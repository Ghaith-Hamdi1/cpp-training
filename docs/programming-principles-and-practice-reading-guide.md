# Reading guide: *Programming: Principles and Practice Using C++* (3rd Edition)

A short reading plan for `P_P_P.pdf` in the repo root (Bjarne Stroustrup, 2024, 654 pages, C++20 plus a little C++23). It is a beginner-oriented textbook that teaches *why* C++ is designed the way it is, so it is the right book for the **foundations** (types, memory, classes, ownership, templates, containers) and the wrong book for multithreading or design patterns. For those, use the [interactive lessons](../interactive/index.html) and the [concurrency book guide](concurrency-in-action-reading-guide.md).

**Page numbers.** The tables give the book's *printed* page numbers and the matching *PDF viewer* page numbers. The PDF page is the printed page plus 13 (printed page 439 is PDF page 452).

The sections were chosen from the book's table of contents. Chapter end pages come from where each chapter's exercises begin. The table of contents lists only where each section starts, so a range ends just before the next section.

---

## What the book does and does not cover

| Covers well | Barely or not at all |
|---|---|
| Types, initialization, conversions, `auto` (ch. 2) | Threads, mutexes, atomics, concurrency (essentially absent; it points to the Williams book) |
| Functions, scope, passing arguments (ch. 3, 7) | Design patterns |
| Classes, interfaces, operator overloading (ch. 8, 12) | `<regex>` and `<chrono>` |
| Pointers, free store, destructors, arrays (ch. 15, 16) | Variadic templates, forwarding references, type traits |
| Copying, moving, essential operations, rule of zero (ch. 17) | Interview-style depth: it is a gentle, thorough textbook |
| Templates, concepts, exceptions, RAII, resource-management pointers (ch. 18) | |
| Containers, iterators, maps, sets, algorithms (ch. 19 to 21) | |

---

## Tier 1: read these for a solid foundation (about 77 pages)

These are the ownership and memory chapters that every other C++ topic builds on.

| Book section | Printed pages | PDF pages | Matching lesson |
|---|---|---|---|
| 2.8 to 2.10 Type safety, conversions, type deduction with `auto` | 43 to 47 | 56 to 60 | 1. Variables and types; 3. Modern syntax tour (auto traps) |
| 7.4 Function call and return (pass by value, by reference, by `const` reference) | 190 to 205 | 203 to 218 | 1. Functions and passing arguments |
| 8.2, 8.3 Classes and members, interface and implementation | 223 to 225 | 236 to 238 | 2. Classes and encapsulation |
| 8.7 Class interfaces | 237 to 245 | 250 to 258 | 2. Classes and encapsulation |
| 15.3 to 15.5 Memory, addresses and pointers; free store; destructors | 439 to 450 | 452 to 463 | 1. Pointers, Dynamic memory; 2. Constructors and destructors |
| 16.1 to 16.2 Arrays, pointers and references | 464 to 470 | 477 to 483 | 1. Arrays, Pointers, References |
| 17.4 to 17.5 Copying and moving; essential operations | 488 to 499 | 501 to 512 | 2. Rule of 3, 5 and 0; 3. Move semantics |
| 18.4 to 18.5 Resources and exceptions; resource-management pointers (RAII, `unique_ptr`) | 529 to 540 | 542 to 553 | 3. RAII, Smart pointers, Exceptions |

## Tier 2: read next if you have time (about 130 pages)

| Book section | Printed pages | PDF pages | Matching lesson |
|---|---|---|---|
| 2.5 Assignment and initialization | 36 to 39 | 49 to 52 | 1. Variables and types |
| 3.5 to 3.6 Functions; `vector` introduced | 68 to 76 | 81 to 89 | 1. Functions; 4. `vector` |
| 4.5 to 4.6 Run-time errors and exceptions | 89 to 98 | 102 to 111 | 3. Exceptions |
| 7.2 to 7.3 Declarations and definitions; scope | 181 to 189 | 194 to 202 | 1. Functions; where variables live |
| 8.4 to 8.6 Evolving a class (`Date`), enumerations, operator overloading | 225 to 236 | 238 to 249 | 2. Operator overloading; 3. `enum class` |
| 12.3, 12.5 Base and derived classes; benefits of object-oriented programming | 367 to 374 and 376 to 377 | 380 to 387 and 389 to 390 | 2. Inheritance, Polymorphism |
| 15.6 to 15.8 Element access, an example list, the `this` pointer | 451 to 460 | 464 to 473 | 2. Member functions: `this` |
| 16.3 to 16.4 C-style strings; alternatives to pointer use | 471 to 474 | 484 to 487 | 1. Arrays, C-strings and `std::string` |
| 17.6 to 17.9 Other operations, remaining `Vector` problems, changing size | 500 to 510 | 513 to 523 | 3. Move semantics; 4. How `vector` grows |
| 18.1 to 18.3 Templates, generalizing `Vector`, range checking and exceptions | 514 to 528 | 527 to 541 | 5. Function and class templates |
| 19.1 to 19.3, 19.6 Containers, sequences and iterators, linked lists, `vector`/`list`/`string` | 546 to 559 and 572 to 573 | 559 to 572 and 585 to 586 | 4. Iterators, Sequence containers |
| 20.1 to 20.6 `map`, `unordered_map`, `set`, container overview | 578 to 596 | 591 to 609 | 4. Associative containers; Which container? |
| 21.1 to 21.2, 21.5 Standard algorithms, function objects, sorting and searching | 604 to 613 and 620 to 622 | 617 to 626 and 633 to 635 | 4. Algorithms; 3. Lambdas |
| 9.11 String streams | 283 to 284 | 296 to 297 | 8. Strings, regex and time |

## Special focus: pointers

Pointers run through Part III of the book. It introduces them to explain how `vector` works underneath, then steers you toward safer alternatives. Most of these sections are already in the tiers above. This is the same material in the order that builds the pointer story, with what each part teaches. Matching lesson: **1. C++ Basics and Pointers** (Pointers from scratch, References, `const` and pointers, Dynamic memory) and **3. Core Language** (RAII, Smart pointers).

| Step | Book section | Printed pages | PDF pages | What it teaches |
|---|---|---|---|---|
| 1 | 15.3 Memory, addresses and pointers | 439 to 441 | 452 to 454 | Memory is numbered bytes. A pointer holds an address; `&` takes it and `*` dereferences it. A pointer is not an integer, and pointers to different types cannot be assigned to each other, because that would silently corrupt memory. `sizeof` and why `sizeof(vector)` does not count the elements (15.3.1, up to page 442). |
| 2 | 15.4 Free store and pointers | 442 to 446 | 455 to 459 | The memory layout (code, static data, stack, free store). `new` returns a pointer to the first element, and **a pointer does not know how many elements it points to**. Indexing with `p[i]` is unchecked. Always initialize pointers; `new` leaves built-in types uninitialized. `nullptr` and `if (p)`. `delete` versus `delete[]`, memory leaks, and deleting twice. |
| 3 | 15.5 Destructors | 447 to 450 | 460 to 463 | A constructor acquires a resource and the destructor releases it. Generated destructors call the members' destructors. **Virtual destructors**, with the rule that a class with a virtual function needs one. |
| 4 | 16.1 Arrays and pointer arithmetic | 464 to 467 | 477 to 480 | Arrays on the stack, in static storage and on the free store. A pointer to an array points only to its first element. `p += 2`, negative subscripts, and that out-of-range access is not detected. The book prefers `vector` throughout. |
| 5 | 16.2 Pointers and references | 468 to 470 | 481 to 483 | A side-by-side comparison. A reference cannot be re-bound, so `r = x2` assigns a value. Parameter rules: return small results by value, use a pointer only when `nullptr` is a valid argument, otherwise use a reference. Do not pass a (pointer, count) pair; pass a `span`. |
| 6 | 16.3 to 16.4 C-style strings and alternatives to pointers | 471 to 474 | 484 to 487 | Zero-terminated strings. The "don't use raw pointers" list: containers, `string`, `unique_ptr` and `shared_ptr` for ownership, **`span`** for a non-owned sequence, **`not_null`** for pointer arguments that must not be null. |
| 7 | 18.5 Resource-management pointers | 537 to 540 | 550 to 553 | Return by moving instead of returning a free-store pointer ("who deletes it?"), then `unique_ptr` and `shared_ptr`. |
| optional | 15.8 The `this` pointer | 456 to 460 | 469 to 473 | Turning a linked list's free functions into member functions. |

**If you only have time for part of it:** read steps 2, 3 and 5. They give the clearest explanations in the book of why raw pointers are error-prone and how pointers differ from references.

**Key ideas to take away**
- A pointer is a value (an address) plus a type. It carries no length and no ownership information.
- Raw pointers cause most "mysterious crash" bugs: uninitialized pointers, going out of range, dangling pointers after `delete`, and double `delete`.
- The modern answer is to match the tool to the job: `vector`/`string` for collections, `unique_ptr`/`shared_ptr` for owning, `span` for viewing a sequence, a reference when "no object" is not allowed, and a pointer only when `nullptr` is a meaningful value.

## Special focus: object-oriented programming

OOP in this book is spread over chapters 8, 12 and 17, with pieces in 15 and 18. Chapter 8 teaches classes as a way to keep objects valid. Chapter 12 teaches inheritance and virtual functions through one graphics hierarchy (`Shape`, `Circle` and so on). Matching lesson: **2. Object-Oriented Programming**.

| Step | Book section | Printed pages | PDF pages | What it teaches | Matching lesson section |
|---|---|---|---|---|---|
| 1 | 8.1 to 8.3 User-defined types, classes and members, interface and implementation | 222 to 224 | 235 to 237 | Types exist to represent ideas, with both data and operations. A class has a public interface and a private implementation. | Classes and encapsulation |
| 2 | 8.4.3 Keep details private | 228 to 229 | 241 to 242 | Why a public representation invites invalid objects ("time bombs"). Constructors that only create valid objects. The **invariant** (the rule for validity); if you cannot state one, use a `struct`. | Classes and encapsulation |
| 3 | 8.7 Class interfaces (argument types, copying, default constructors, `const` member functions, helper functions) | 237 to 244 | 250 to 257 | Interface rules: complete but minimal ("as small as possible, but no smaller"), provide constructors, support copying or prohibit it, mark non-modifying functions `const`, free resources in the destructor. Why every object should be initialized. | Constructors and destructors; Member functions |
| 4 | 12.1 to 12.2 Design principles; `Shape`: an abstract class and access control | 356 to 366 | 369 to 379 | Represent application concepts directly in code. A `protected` constructor stops you creating a general `Shape`, since a shape must be a specific one. Data stays private. | Abstract classes and interfaces |
| 5 | **12.3 Base and derived classes** | 367 to 374 | 380 to 387 | The three mechanisms behind OOP: derivation, virtual functions (run-time dispatch) and encapsulation. **Object layout**: derived members follow the base's, and each object has a hidden vptr to a vtbl. **Overriding** and `override` (a mismatched signature silently creates a new function). Pure virtual functions (`= 0`), abstract versus concrete classes. | Inheritance; Polymorphism and virtual functions; Abstract classes |
| 6 | 12.4 to 12.5 Copying a hierarchy; benefits of OOP | 375 to 377 | 388 to 390 | Hierarchies do not mix with default copying, so delete the copy operations of a base class. **Interface inheritance** versus **implementation inheritance**. A derived class that cannot stand in for its base is a flawed design. Adding new types without changing existing code. | Inheritance; Composition and design |
| 7 | 15.5.2 Virtual destructors | 449 to 450 | 462 to 463 | Why `delete` through a base pointer needs a virtual destructor, with the rule that a class with a virtual function needs one. | Polymorphism and virtual functions |
| 8 | 17.4 to 17.5 Copying and moving; essential operations | 488 to 499 | 501 to 512 | The "rule of zero" (define none of the essential operations if you can) and the "rule of all" (if you define one, define them all). | Copying and the Rule of 3, 5 and 0 |
| optional | 8.5 to 8.6 Enumerations and operator overloading | 233 to 236 | 246 to 249 | `enum class`, and overloading `++` for a `Month` type. | Operator overloading |

**If you only have time for part of it:** read steps 5, 6 and 7 (the inheritance and virtual-function core) and the rules in step 3.

**What the book does not cover, so use the lesson for it:** composition versus inheritance as a design choice, the SOLID principles and Liskov substitution, `dynamic_cast` (one passing mention only), multiple inheritance and design patterns. Nearly all its OOP examples come from the one graphics hierarchy, so the ideas are consistent but the examples are less varied than the lesson's.

**Key ideas to take away**
- A class exists to keep its objects valid. Hide the representation, make constructors create only valid values, and state the invariant.
- Keep interfaces small, and use `const` for functions that do not modify the object.
- Inheritance means "can stand in for its base" (interface inheritance). Code that uses the base type should keep working when given a derived object.
- Virtual functions dispatch at run time through a per-class table. Always use `override`, and give a polymorphic base a virtual destructor and no copying.
- Define none of the copy, move and destructor operations if you can (rule of zero); if you define any, define them all.

## Skip for interview preparation

- Chapter 1 (hello world and the build process, which the first lesson summarises) and chapters 5 and 6 (building a calculator parser).
- Chapter 9 except 9.11 (stream I/O details).
- Chapters 10 to 14 (graphics and GUI library): about 150 pages on drawing shapes and windows, not on interview material.
- 20.7 (ranges and iterators), 21.3 and 21.4 (numerical algorithms, copying), and the index.

## How to use this guide

1. Do the lesson and quiz for a topic first (for example, Lesson 1 for pointers).
2. If a quiz question surprises you, read the matching Tier 1 section here for the longer, gentler explanation.
3. Read Tier 2 as a longer-term path, not before the interview.

## Notes on the edition

- The book's examples start with `import std;` and `using namespace std;` (C++20 modules), and its section 0.4 recommends `#include "PPP.h"` instead. That header is the authors' small `PPP_support` module: it gives range-checked `vector` subscripting, a convenient `error()` function and a simplified interface to random numbers. If your compiler lacks good module support, the book supplies `"PPPheaders.h"` as a fallback.
- The support files are downloaded from the author's website (see section 0.4), so to compile the book's examples as written you need them. For plain study you can read the code without compiling it, or replace the support line with the ordinary `#include` lines for the standard headers you use.
