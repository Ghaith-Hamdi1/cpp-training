# Reading guide: *Programming: Principles and Practice Using C++* (3rd Edition)

A short reading plan for `P_P_P.pdf` in the repo root (Bjarne Stroustrup, 2024, 654 pages, C++20 plus a little C++23). It is a beginner-oriented textbook that teaches *why* C++ is designed the way it is, so it is the right book for the **foundations** (types, memory, classes, ownership, templates, containers) and the wrong book for multithreading or design patterns. For those, use the [interactive lessons](../interactive/index.html) and the [concurrency book guide](concurrency-in-action-reading-guide.md).

**Page numbers.** The tables give *PDF viewer* page numbers, the number shown in your PDF reader.

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

| Book section | PDF pages | Matching lesson |
|---|---|---|
| 2.8 to 2.10 Type safety, conversions, type deduction with `auto` | 56 to 60 | 1. Variables and types; 3. Modern syntax tour (auto traps) |
| 7.4 Function call and return (pass by value, by reference, by `const` reference) | 203 to 218 | 1. Functions and passing arguments |
| 8.2, 8.3 Classes and members, interface and implementation | 236 to 238 | 2. Classes and encapsulation |
| 8.7 Class interfaces | 250 to 258 | 2. Classes and encapsulation |
| 15.3 to 15.5 Memory, addresses and pointers; free store; destructors | 452 to 463 | 1. Pointers, Dynamic memory; 2. Constructors and destructors |
| 16.1 to 16.2 Arrays, pointers and references | 477 to 483 | 1. Arrays, Pointers, References |
| 17.4 to 17.5 Copying and moving; essential operations | 501 to 512 | 2. Rule of 3, 5 and 0; 3. Move semantics |
| 18.4 to 18.5 Resources and exceptions; resource-management pointers (RAII, `unique_ptr`) | 542 to 553 | 3. RAII, Smart pointers, Exceptions |

## Tier 2: read next if you have time (about 130 pages)

| Book section | PDF pages | Matching lesson |
|---|---|---|
| 2.5 Assignment and initialization | 49 to 52 | 1. Variables and types |
| 3.5 to 3.6 Functions; `vector` introduced | 81 to 89 | 1. Functions; 4. `vector` |
| 4.5 to 4.6 Run-time errors and exceptions | 102 to 111 | 3. Exceptions |
| 7.2 to 7.3 Declarations and definitions; scope | 194 to 202 | 1. Functions; where variables live |
| 8.4 to 8.6 Evolving a class (`Date`), enumerations, operator overloading | 238 to 249 | 2. Operator overloading; 3. `enum class` |
| 12.3, 12.5 Base and derived classes; benefits of object-oriented programming | 380 to 387 and 389 to 390 | 2. Inheritance, Polymorphism |
| 15.6 to 15.8 Element access, an example list, the `this` pointer | 464 to 473 | 2. Member functions: `this` |
| 16.3 to 16.4 C-style strings; alternatives to pointer use | 484 to 487 | 1. Arrays, C-strings and `std::string` |
| 17.6 to 17.9 Other operations, remaining `Vector` problems, changing size | 513 to 523 | 3. Move semantics; 4. How `vector` grows |
| 18.1 to 18.3 Templates, generalizing `Vector`, range checking and exceptions | 527 to 541 | 5. Function and class templates |
| 19.1 to 19.3, 19.6 Containers, sequences and iterators, linked lists, `vector`/`list`/`string` | 559 to 572 and 585 to 586 | 4. Iterators, Sequence containers |
| 20.1 to 20.6 `map`, `unordered_map`, `set`, container overview | 591 to 609 | 4. Associative containers; Which container? |
| 21.1 to 21.2, 21.5 Standard algorithms, function objects, sorting and searching | 617 to 626 and 633 to 635 | 4. Algorithms; 3. Lambdas |
| 9.11 String streams | 296 to 297 | 8. Strings, regex and time |

## Special focus: pointers

Pointers run through Part III of the book. It introduces them to explain how `vector` works underneath, then steers you toward safer alternatives. Most of these sections are already in the tiers above. This is the same material in the order that builds the pointer story, with what each part teaches. Matching lesson: **1. C++ Basics and Pointers** (Pointers from scratch, References, `const` and pointers, Dynamic memory) and **3. Core Language** (RAII, Smart pointers).

| Step | Book section | PDF pages | What it teaches |
|---|---|---|---|
| 1 | 15.3 Memory, addresses and pointers | 452 to 454 | Memory is numbered bytes. A pointer holds an address; `&` takes it and `*` dereferences it. A pointer is not an integer, and pointers to different types cannot be assigned to each other, because that would silently corrupt memory. `sizeof` and why `sizeof(vector)` does not count the elements (15.3.1, up to page 442). |
| 2 | 15.4 Free store and pointers | 455 to 459 | The memory layout (code, static data, stack, free store). `new` returns a pointer to the first element, and **a pointer does not know how many elements it points to**. Indexing with `p[i]` is unchecked. Always initialize pointers; `new` leaves built-in types uninitialized. `nullptr` and `if (p)`. `delete` versus `delete[]`, memory leaks, and deleting twice. |
| 3 | 15.5 Destructors | 460 to 463 | A constructor acquires a resource and the destructor releases it. Generated destructors call the members' destructors. **Virtual destructors**, with the rule that a class with a virtual function needs one. |
| 4 | 16.1 Arrays and pointer arithmetic | 477 to 480 | Arrays on the stack, in static storage and on the free store. A pointer to an array points only to its first element. `p += 2`, negative subscripts, and that out-of-range access is not detected. The book prefers `vector` throughout. |
| 5 | 16.2 Pointers and references | 481 to 483 | A side-by-side comparison. A reference cannot be re-bound, so `r = x2` assigns a value. Parameter rules: return small results by value, use a pointer only when `nullptr` is a valid argument, otherwise use a reference. Do not pass a (pointer, count) pair; pass a `span`. |
| 6 | 16.3 to 16.4 C-style strings and alternatives to pointers | 484 to 487 | Zero-terminated strings. The "don't use raw pointers" list: containers, `string`, `unique_ptr` and `shared_ptr` for ownership, **`span`** for a non-owned sequence, **`not_null`** for pointer arguments that must not be null. |
| 7 | 18.5 Resource-management pointers | 550 to 553 | Return by moving instead of returning a free-store pointer ("who deletes it?"), then `unique_ptr` and `shared_ptr`. |
| optional | 15.8 The `this` pointer | 469 to 473 | Turning a linked list's free functions into member functions. |

**If you only have time for part of it:** read steps 2, 3 and 5. They give the clearest explanations in the book of why raw pointers are error-prone and how pointers differ from references.

**Key ideas to take away**
- A pointer is a value (an address) plus a type. It carries no length and no ownership information.
- Raw pointers cause most "mysterious crash" bugs: uninitialized pointers, going out of range, dangling pointers after `delete`, and double `delete`.
- The modern answer is to match the tool to the job: `vector`/`string` for collections, `unique_ptr`/`shared_ptr` for owning, `span` for viewing a sequence, a reference when "no object" is not allowed, and a pointer only when `nullptr` is a meaningful value.

## Special focus: object-oriented programming

OOP in this book is spread over chapters 8, 12 and 17, with pieces in 15 and 18. Chapter 8 teaches classes as a way to keep objects valid. Chapter 12 teaches inheritance and virtual functions through one graphics hierarchy (`Shape`, `Circle` and so on). Matching lesson: **2. Object-Oriented Programming**.

| Step | Book section | PDF pages | What it teaches | Matching lesson section |
|---|---|---|---|---|
| 1 | 8.1 to 8.3 User-defined types, classes and members, interface and implementation | 235 to 237 | Types exist to represent ideas, with both data and operations. A class has a public interface and a private implementation. | Classes and encapsulation |
| 2 | 8.4.3 Keep details private | 241 to 242 | Why a public representation invites invalid objects ("time bombs"). Constructors that only create valid objects. The **invariant** (the rule for validity); if you cannot state one, use a `struct`. | Classes and encapsulation |
| 3 | 8.7 Class interfaces (argument types, copying, default constructors, `const` member functions, helper functions) | 250 to 257 | Interface rules: complete but minimal ("as small as possible, but no smaller"), provide constructors, support copying or prohibit it, mark non-modifying functions `const`, free resources in the destructor. Why every object should be initialized. | Constructors and destructors; Member functions |
| 4 | 12.1 to 12.2 Design principles; `Shape`: an abstract class and access control | 369 to 379 | Represent application concepts directly in code. A `protected` constructor stops you creating a general `Shape`, since a shape must be a specific one. Data stays private. | Abstract classes and interfaces |
| 5 | **12.3 Base and derived classes** | 380 to 387 | The three mechanisms behind OOP: derivation, virtual functions (run-time dispatch) and encapsulation. **Object layout**: derived members follow the base's, and each object has a hidden vptr to a vtbl. **Overriding** and `override` (a mismatched signature silently creates a new function). Pure virtual functions (`= 0`), abstract versus concrete classes. | Inheritance; Polymorphism and virtual functions; Abstract classes |
| 6 | 12.4 to 12.5 Copying a hierarchy; benefits of OOP | 388 to 390 | Hierarchies do not mix with default copying, so delete the copy operations of a base class. **Interface inheritance** versus **implementation inheritance**. A derived class that cannot stand in for its base is a flawed design. Adding new types without changing existing code. | Inheritance; Composition and design |
| 7 | 15.5.2 Virtual destructors | 462 to 463 | Why `delete` through a base pointer needs a virtual destructor, with the rule that a class with a virtual function needs one. | Polymorphism and virtual functions |
| 8 | 17.4 to 17.5 Copying and moving; essential operations | 501 to 512 | The "rule of zero" (define none of the essential operations if you can) and the "rule of all" (if you define one, define them all). | Copying and the Rule of 3, 5 and 0 |
| optional | 8.5 to 8.6 Enumerations and operator overloading | 246 to 249 | `enum class`, and overloading `++` for a `Month` type. | Operator overloading |

**If you only have time for part of it:** read steps 5, 6 and 7 (the inheritance and virtual-function core) and the rules in step 3.

**What the book does not cover, so use the lesson for it:** composition versus inheritance as a design choice, the SOLID principles and Liskov substitution, `dynamic_cast` (one passing mention only), multiple inheritance and design patterns. Nearly all its OOP examples come from the one graphics hierarchy, so the ideas are consistent but the examples are less varied than the lesson's.

**Key ideas to take away**
- A class exists to keep its objects valid. Hide the representation, make constructors create only valid values, and state the invariant.
- Keep interfaces small, and use `const` for functions that do not modify the object.
- Inheritance means "can stand in for its base" (interface inheritance). Code that uses the base type should keep working when given a derived object.
- Virtual functions dispatch at run time through a per-class table. Always use `override`, and give a polymorphic base a virtual destructor and no copying.
- Define none of the copy, move and destructor operations if you can (rule of zero); if you define any, define them all.

## Special focus: templates

The book introduces templates as the tool for building `vector` and the standard library, and it stays at an introductory level. Most of the material is in section 18.1, with a little more in 18.2, 19.4 and chapters 19 to 21. Matching lessons: **5. Templates** and **9. Type Traits and Compile-time C++**.

| Step | Book section | PDF pages | What it teaches | Matching lesson section |
|---|---|---|---|---|
| 1 | 18.1.1 Types as template parameters | 527 to 530 | Turning the book's `Vector` of doubles into `template<typename T> class Vector`. A class template is a "type generator", and instantiation happens at compile time. The compiler writes `Vector<string>::push_back` when you use it. `class` and `typename` mean the same here. | Why templates, and function templates; Class templates |
| 2 | **18.1.2 Generic programming** | 530 to 531 | Generic programming means code that works for any type meeting stated requirements. **Templates versus virtual functions:** compile-time versus run-time resolution. The book calls the first "parametric" and the second "ad hoc" polymorphism, which is its own terminology. When to use templates (performance, flexibility) and how they combine with OOP. | Why templates (the interview note on templates versus virtual functions) |
| 3 | **18.1.3 Concepts** | 531 to 533 | A **concept** is a named set of requirements on template arguments, a compile-time type predicate. The syntax `template<Element T>` and `requires`. A list of standard concepts: `range`, the iterator kinds, `equality_comparable`, `totally_ordered`, `integral`, `copyable`, `regular` and `sortable`. | Type traits and `if constexpr` (the "Concepts (C++20)" part) |
| 4 | **18.1.4 Containers and inheritance** | 533 to 534 | "D is a B" does **not** imply `vector<D>` is a `vector<B>`. This is deliberate: it protects against slicing and against putting a `Rectangle*` into a vector of `Circle*`. Not covered in the lesson. | Not in the lessons |
| 5 | 18.1.5 Value template parameters | 534 to 535 | One example: `template<typename T, int sz> class Buffer`, useful when you do not want the free store. | Class templates (non-type parameters) |
| 6 | 18.2 Generalizing `Vector` | 535 to 538 | What changes when `T` can be any type: types with no default value (`resize(n, T def = T{})`), copy operations that throw, and destroying elements properly. | Pitfalls and good practice |
| optional | 19.4 and 21.1 Generalizing `Vector` again; standard algorithms | 573 to 578 and 617 to 622 | The standard algorithms shown as function templates constrained by concepts, for example `template<input_iterator In, equality_comparable<...> T>` for `find`. A look at concepts in real use. | Type traits and `if constexpr` |

**If you only have time for part of it:** read steps 2, 3 and 4 (about 4 pages, PDF pages 530 to 534). They give the clearest comparison of templates with virtual functions, and the concepts idea.

**What the book does not cover, so use the lessons for it.** None of these appear anywhere in the book:
- variadic templates and fold expressions;
- forwarding references, `std::forward` and perfect forwarding;
- explicit and partial specialization (the book uses the word "specialization" only to mean instantiation);
- type traits, `is_same`, SFINAE and `enable_if`;
- `if constexpr`, `static_assert` and `decltype`;
- dependent names and the rule that templates normally live in headers.

Those topics make up most of what interviews ask, so the lessons are the main source.

**Key ideas to take away**
- A template is a blueprint; the compiler generates a separate real class or function for each set of template arguments, at compile time.
- Generic programming (templates) resolves at compile time, which is faster and more regular. Object-oriented programming (virtual functions) resolves at run time, which is more flexible.
- A **concept** states what a template requires of its arguments, so mistakes are reported clearly at the call site instead of deep inside the template.
- Inheritance does not carry through templates: `vector<Circle>` is not a `vector<Shape>`.
- A general-purpose template must cope with types that have no default value, throwing copies and destructors.

## Special focus: the STL

The STL is Part III of the book (chapters 19 to 21). It is taught from the idea down rather than as a reference. It starts with a worked example that generalizes a loop until iterators appear, then covers containers, then algorithms. Matching lesson: **4. The STL**.

| Step | Book section | PDF pages | What it teaches | Matching lesson section |
|---|---|---|---|---|
| 1 | **19.1 Storing and processing data, STL ideals** (19.1.3) | 559 to 564 | The motivation. Two loops that find the highest value, one for an array and one for a vector, are generalized with pointers, which leads to iterators and `[first, last)` ranges. The STL is defined as the containers plus the generic algorithms. | The big picture |
| 2 | 19.2 Sequences and iterators | 565 to 567 | An iterator is a generalized pointer; sequences are traversed from `begin()` to `end()`. | Iterators |
| 3 | **20.7.1 Iterator categories** | 610 to 612 | The six categories (input, output, forward, bidirectional, random-access, contiguous) and which container provides which. Range versions such as `ranges::find`. | Iterators |
| 4 | 17.8 Changing size | 517 to 522 | How a `vector` grows: `reserve`, `resize` and `push_back` on a hand-built `Vector`. | vector: the workhorse |
| 5 | **20.6 Container overview** | 604 to 610 | One-line advice per container: `vector` is "the default container", `list` for inserts and deletes without moving elements, `forward_list` for mostly-empty lists, `deque` "don't use until you have expert-level knowledge", and the ordered versus hash-based associative containers. The informal definition of an STL container and its operations, and the "almost containers" (`string`, built-in arrays, I/O streams). | Other sequence containers; Which container should I use? |
| 6 | 20.1 to 20.2 Associative containers and `map` | 591 to 598 | The word-count example (`++words[s]`), where a missing key is inserted with a default value, and structured bindings. | Associative and unordered containers |
| 7 | 20.3 and 20.5 `unordered_map` and `set` | 598 to 599 and 602 to 604 | Hash tables, and sets for tracking individual values. | Associative and unordered containers |
| 8 | 20.4 Timing | 599 to 602 | Measuring a linear `find` in a `vector` against a `map` lookup with `<chrono>`. Make no efficiency claim without measuring, and use the result so the optimizer cannot delete the code. | Which container should I use? |
| 9 | **21.1 Standard algorithms** | 617 to 622 | About 125 algorithms; a summary table (`find`, `find_if`, `count`, `count_if`, `sort`, `copy`, `merge`, `equal_range`, `accumulate`, `max_element`, `iota`). Input sequences are iterator pairs, and failure is reported by returning `end()`. | Algorithms |
| 10 | 21.2 Function objects and lambdas | 623 to 626 | Function objects, predicates on class members, lambda expressions. | Algorithms; Core Language: Lambdas |
| 11 | 21.5 Sorting and searching | 633 to 635 | `sort` with a custom comparator. `binary_search` and `equal_range`, which require a sorted sequence and are much faster than `find` on long ones. | Algorithms |
| optional | 19.3, 19.4, 19.6 Linked lists, making `Vector` act like an STL container, `vector`/`list`/`string` | 568 to 572, 573 to 578 and 585 to 586 | Building a list and a container that fits the STL. | Other sequence containers |
| optional | 21.3 to 21.4 Numerical algorithms and copying | 627 to 632 | `accumulate`, `inner_product`, `copy` and `copy_if`. | Algorithms |

**If you only have time for part of it:** read steps 3, 5 and 9 (about 16 pages, PDF pages 604 to 612 and 617 to 622). They give the container advice, the iterator categories and the algorithm model.

**What the book barely covers or omits, so use the lesson for it:**
- `stack`, `queue` and `priority_queue` are absent, and `deque` appears only in the advice above.
- Iterator invalidation gets only a brief mention.
- There is no erase-remove idiom, and `transform` appears in only a few places.
- There is no `string_view`.
- Complexity is limited to a brief big-O section (20.3) and the timing experiment, with no table of operation costs.

**Key ideas to take away**
- The STL is three parts that fit together: containers hold data, iterators walk it, and algorithms work on iterator ranges without knowing the container.
- Default to `vector`; pick another container only for a reason you can state.
- A `map`'s `operator[]` inserts a default value for a missing key. A `map` is ordered, and hash containers are the "optimized version" for large lookups.
- Binary search needs a sorted sequence. Algorithms report "not found" by returning `end()`.
- Measure before you claim something is faster.

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
