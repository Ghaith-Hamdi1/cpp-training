# C++ recap and roadmap: seven phases, five books

A map of every big C++ topic, grouped into seven phases from solid fundamentals to advanced tools to modern C++, with the exact book chapters (PDF pages) to read in each phase, the lessons and exercises that go with them, and a time estimate. Use it as a **reading guide** when you want to study a phase properly, and as a **recap** when you want to check that you can still explain the topics. The [topic index](#topic-index-where-to-look) at the end is the quick reminder.

All page numbers are **PDF viewer pages** (the number your PDF reader shows). The books are in [`books/`](../../books).

## The five books

| Book | Covers | Best used for |
|---|---|---|
| *C++ Primer*, 5th ed. (Lippman, Lajoie, Moo), [PDF](../../books/Cpp-Primer-5th-Edition-Lippman.pdf), [reading guide](cpp-primer-reading-guide.md), [reading plan](cpp-primer-reading-plan.md) | C++11, the whole language and library, 970 pages | The **systematic base**: phases 1 to 4 and the C++11 parts of phase 5. It is a textbook in the order a language should be learned, with exercises |
| *Programming: Principles and Practice Using C++*, 3rd ed. (Stroustrup), [reading guide](programming-principles-and-practice-reading-guide.md) | C++20 | A **second explanation** from the language's creator, strongest on class design, memory and the STL. [Reading plan](programming-principles-and-practice-reading-plan.md) |
| *Effective Modern C++* (Meyers), [reading guide](effective-modern-cpp-reading-guide.md) | C++11/14 | **Modern C++** in short, self-contained items: deduction, smart pointers, move and forwarding, lambdas. [Reading plan](effective-modern-cpp-reading-plan.md) |
| *C++ Move Semantics: The Complete Guide* (Josuttis), [reading guide](move-semantics-complete-guide-reading-guide.md) | C++11 to C++20 | A **deep dive** on one topic: moved-from states, value categories, special member rules. [Reading plan](move-semantics-reading-plan.md) |
| *C++ Concurrency in Action*, 2nd ed. (Williams), [reading guide](concurrency-in-action-reading-guide.md) | C++17 | **Concurrency**: the only book here with real depth on threads and the memory model. [Reading plan](concurrency-in-action-reading-plan.md) |

The books overlap on purpose. For each phase the **core** list is the shortest path that covers the phase; the **deepen** list is a second explanation of the same ground from another author, to read when a topic is still unclear or you want more depth. Do not read both lists in full unless you have the time.

## The plan at a glance

Time = core reading at about 10 pages an hour (pages with code you type in and run), plus the lessons and quizzes of the phase, plus the practice exercises. The deepen reading is extra and shown separately.

| Phase | Theme | Core reading | Lessons and quizzes | Exercises | **Core total** | Deepen reading (optional) |
|---|---|---|---|---|---|---|
| [1](#phase-1-core-language-foundations) | Core language foundations | 160 pages, 16.0 h | 1.7 h | 2.3 h | **19.9 h** | 86 pages, 8.6 h |
| [2](#phase-2-classes-memory-and-object-oriented-design) | Classes, memory and object-oriented design | 220 pages, 22.0 h | 1.7 h | 0.8 h | **24.5 h** | 84 pages, 8.4 h |
| [3](#phase-3-the-standard-library-and-generic-programming) | The standard library and generic programming | 217 pages, 21.7 h | 2.7 h | 0.4 h | **24.8 h** | 67 pages, 6.7 h |
| [4](#phase-4-advanced-language-tools-and-design) | Advanced language tools and design | 66 pages, 6.6 h | 2.1 h | 0.0 h | **8.7 h** | 33 pages, 3.3 h |
| [5](#phase-5-modern-c-c-11-to-c-20) | Modern C++ (C++11 to C++20) | 229 pages, 22.9 h | 3.3 h | 0.8 h | **27.1 h** | 118 pages, 11.8 h |
| [6](#phase-6-concurrency-and-the-memory-model) | Concurrency and the memory model | 109 pages, 10.9 h | 2.7 h | 0.8 h | **14.4 h** | 39 pages, 3.9 h |
| [7](#phase-7-performance-memory-layout-and-binary-data) | Performance, memory layout and binary data | 15 pages, 1.5 h | 2.0 h | 0.4 h | **3.9 h** | 7 pages, 0.7 h |
| | **Total** | 1016 pages | | | **123.3 h** | 434 pages, 43.4 h |

The core path is about **123 hours**: roughly 21 weeks at 6 hours a week, or 10 weeks at 12. Adding every deepen list brings it to about **167 hours**. If you only want a refresher on what you already know, skim the "core reading" at 25 pages an hour and spend your time on the lessons, quizzes and recap questions.

Suggested order: phases 1 to 5 in sequence, because each builds on the one before. Phase 6 (concurrency) needs phases 1 to 5 and especially move semantics, lambdas and RAII. Phase 7 needs phases 1 to 3 and the cache and threads ideas from phase 6; it can be read last or interleaved with phase 6.

## How to study a phase

| Step | Do |
|---|---|
| 1. Skim the topic list | Mark each topic you could not explain aloud right now. |
| 2. Do the lessons | Work through the phase's lessons on the [site](https://ghaith-hamdi1.github.io/cpp-training/), running the step-throughs, then take each quiz. |
| 3. Read | Read the core reading in the order listed, with the code closed first, then typed in. Read the deepen list only for topics you marked. |
| 4. Practise | Do the phase's exercises from [`examples/practice/`](../../examples/practice/README.md) without looking things up. |
| 5. Recap | Answer the phase's recap question aloud, and retake any quiz below 80%. |

## Phase 1: Core language foundations

*Types, expressions, control flow, functions, pointers, references, strings and vectors.*

**Time:** about **19.9 hours** (16.0 h reading, 1.7 h lessons and quizzes, 2.3 h exercises), plus 8.6 h if you also read the deepen list.

### Big topics

| Topic | What it covers |
|---|---|
| **Types and initialization** | Built-in types, literals, `auto` and `decltype`, brace initialization and why it rejects narrowing, `const` and `constexpr` basics. |
| **Expressions and conversions** | Operator precedence, integer promotion, signed versus unsigned traps, bitwise operators, the named casts. |
| **Control flow** | `if`/`switch`, loops, range-for, `try`/`catch` first look. |
| **Functions** | Declarations versus definitions, passing by value, by reference and by `const` reference, return values, default arguments, overloading and overload resolution, function pointers. |
| **Pointers, references and arrays** | Addresses, `nullptr`, pointer arithmetic, array-to-pointer decay, reference rules, `const` with pointers, dangling and null dereference. |
| **Strings and vectors** | `std::string` and `std::vector` as the default tools, iterators as a first idea, `string_view`, C strings and why to avoid them. |
| **Scope, lifetime and storage** | Stack, heap and static storage, namespaces, `static`, linkage, the compile-link process. |

### Core reading (160 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| Primer | ch. 2 Variables and Basic Types (2.1 to 2.6) | 61 to 109 | 49 | Types, `const`, compound types, `auto`/`decltype`, defining your own structs |
| Primer | ch. 3 Strings, Vectors and Arrays (3.2 to 3.6) | 113 to 161 | 49 | `string`, `vector`, iterators, built-in arrays |
| Primer | 4.8 Bitwise operators; 4.11 Type conversions | 181 to 184; 188 to 194 | 11 | Bit operations and every implicit conversion |
| Primer | ch. 6 Functions (6.1 to 6.7) | 231 to 281 | 51 | Argument passing, overloading, function matching, function pointers |

### Deepen (optional, 86 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| PPP | Types and initialization: 2.5; 2.8 to 2.10 | 49 to 52; 56 to 60 | 9 | A shorter second view of initialization, conversions and `auto` |
| PPP | Functions and `vector`: 3.5 to 3.6; 4.5 to 4.6 | 81 to 89; 102 to 111 | 19 | Functions, `vector`, run-time errors and exceptions |
| PPP | Declarations, scope and argument passing: 7.2 to 7.4 | 194 to 218 | 25 | Scope, storage and how arguments are passed |
| PPP | Memory, addresses and pointers: 15.3 to 15.5 | 452 to 463 | 12 | Pointers, the free store, `delete`, dangling pointers |
| PPP | Arrays, `this`, alternatives to raw pointers: 15.6 to 15.8; 16.1 to 16.4 | 464 to 473; 477 to 487 | 21 | Arrays, references versus pointers, `span` |

### Lessons and exercises

| Lesson | Time |
|---|---|
| [1. Basics and Pointers](https://ghaith-hamdi1.github.io/cpp-training/01-basics.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/01-basics-quiz.html) | 60 min |
| [2. Types, Initialization and Casts](https://ghaith-hamdi1.github.io/cpp-training/16-types-and-casts.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/16-types-and-casts-quiz.html) | 40 min |

Exercises: 01 to 09 (C strings, pointers, `trim`, `parseUnsigned`).

**Recap check.** Explain from memory: what `int* const p` means, why `int{3.7}` is an error, what `v[i]` does that `v.at(i)` does not, why an array parameter is really a pointer, and what the linker error "undefined reference" means.

## Phase 2: Classes, memory and object-oriented design

*Class design, copy control, operator overloading, inheritance, virtual functions, the object model.*

**Time:** about **24.5 hours** (22.0 h reading, 1.7 h lessons and quizzes, 0.8 h exercises), plus 8.4 h if you also read the deepen list.

### Big topics

| Topic | What it covers |
|---|---|
| **Class design** | Invariants, encapsulation, constructors and the initializer list, `explicit`, `const` and `static` members, `friend`. |
| **Object lifetime** | Construction and destruction order, the destructor as cleanup, temporaries. |
| **Copy control** | The copy constructor and assignment, shallow versus deep copy, the Rule of Three, Five and Zero, `= default` and `= delete`, copy-and-swap. |
| **Dynamic memory** | `new`/`delete`, `new[]`/`delete[]`, leaks, double delete, why this is replaced by RAII in phase 4 and smart pointers in phase 5. |
| **Operator overloading and conversions** | Member versus non-member operators, `<<`/`>>`, comparison, `operator()`, conversion operators and `explicit`. |
| **Inheritance and polymorphism** | Public inheritance as is-a, virtual functions and `override`, virtual destructors, slicing, abstract classes and interfaces. |
| **The object model** | The vtable and vptr, multiple inheritance and pointer adjustment, the diamond and virtual inheritance, RTTI and `dynamic_cast`, private inheritance. |

### Core reading (220 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| Primer | ch. 7 Classes (7.1 to 7.6) | 283 to 335 | 53 | Abstract data types, constructors, `const`/`mutable`/`static` members, class scope |
| Primer | 12.1.2 Managing memory directly; 12.2.1 `new` and arrays | 487 to 492; 506 to 509 | 10 | `new`/`delete` and their pitfalls (read before copy control) |
| Primer | ch. 13 Copy Control (13.1 to 13.5) | 525 to 559 | 35 | Copy constructor, assignment, destructor, Rule of Three/Five, classes that manage memory |
| Primer | ch. 14 Overloaded Operations and Conversions (14.1 to 14.9) | 581 to 619 | 39 | Operator overloading and conversion operators |
| Primer | ch. 15 Object-Oriented Programming (15.1 to 15.9) | 621 to 679 | 59 | Base and derived classes, virtual functions, abstract classes, copy control with inheritance |
| Primer | 18.3 Multiple and virtual inheritance; 19.2 Run-time type identification | 831 to 847; 854 to 860 | 24 | The diamond, `dynamic_cast`, `typeid` |

### Deepen (optional, 84 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| PPP | Classes as a way to keep objects valid: 8.1 to 8.7 | 235 to 258 | 24 | Invariants and class interfaces |
| PPP | Inheritance and virtual functions: 12.1 to 12.5 | 369 to 390 | 22 | The vptr/vtbl layout and virtual destructors |
| PPP | Copying, moving and `vector` growth: 17.4 to 17.9 | 501 to 523 | 23 | Essential operations and how `vector` is built |
| EMC | Item 12 `override`; Item 17 special member generation | 97 to 104; 127 to 133 | 15 | The two items that fix the most real bugs in class design |

### Lessons and exercises

| Lesson | Time |
|---|---|
| [4. Object-Oriented Programming](https://ghaith-hamdi1.github.io/cpp-training/02-oop.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/02-oop-quiz.html) | 60 min |
| [5. The Object Model in Depth](https://ghaith-hamdi1.github.io/cpp-training/19-object-model.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/19-object-model-quiz.html) | 40 min |

Exercises: 10 (`MyString`) and 11 (Shapes).

**Recap check.** Explain aloud how `virtual` works in memory (vptr, vtable, slot), why a base destructor must be virtual, what the Rule of Zero says, and why `Animal a = dog;` slices.

## Phase 3: The standard library and generic programming

*Streams, containers, iterators, algorithms, templates.*

**Time:** about **24.8 hours** (21.7 h reading, 2.7 h lessons and quizzes, 0.4 h exercises), plus 6.7 h if you also read the deepen list.

### Big topics

| Topic | What it covers |
|---|---|
| **I/O and streams** | Stream state, files, string streams, formatted input and output, `std::format` as the modern alternative. |
| **Sequential containers** | `vector`, `deque`, `list`, `array`; how `vector` grows; invalidation rules; `string` operations. |
| **Associative and unordered containers** | `map`/`set`, `unordered_map`, custom keys, comparators and hashes, `try_emplace`. |
| **Iterators and algorithms** | Iterator categories, the algorithm header, predicates and function objects, erase-remove, `lower_bound`. |
| **Function and class templates** | Instantiation, argument deduction, non-type parameters, template argument rules. |
| **Specialization and overloading with templates** | Full and partial specialization, function matching with templates. |
| **Specialized library facilities** | `tuple`, `bitset`, regular expressions, random numbers. |

### Core reading (217 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| Primer | ch. 8 The IO Library | 339 to 353 | 15 | Streams, files, string streams |
| Primer | ch. 9 Sequential Containers (9.1 to 9.6) | 355 to 403 | 49 | Containers, operations, how `vector` grows, string operations, adaptors |
| Primer | ch. 10 Generic Algorithms (10.1 to 10.6) | 405 to 447 | 43 | Algorithms, lambdas as predicates, iterator categories |
| Primer | ch. 11 Associative Containers (11.1 to 11.4) | 449 to 477 | 29 | `map`, `set`, unordered containers |
| Primer | ch. 16 Templates: 16.1 to 16.3, 16.5 (skip 16.2.5 to 16.2.7 and 16.4 until phase 5) | 681 to 706; 707 to 718; 723 to 727; 735 to 743 | 52 | Function and class templates, deduction, overloading, specialization |
| Primer | ch. 17: 17.1 tuple; 17.3 regular expressions; 17.4 random numbers | 747 to 751; 757 to 773; 774 to 780 | 29 | The library pieces the lessons also cover |

### Deepen (optional, 67 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| PPP | Templates and concepts: 18.1 to 18.3 | 527 to 541 | 15 | Templates from the idea down, with a first look at concepts |
| PPP | Containers and iterators: 19.1 to 19.3, 19.6; 20.1 to 20.2 | 559 to 572; 585 to 586; 591 to 598 | 24 | How the STL is designed |
| PPP | Choosing a container: 20.3 to 20.7.1 | 598 to 612 | 15 | Container overview, iterator categories, timing |
| PPP | Algorithms: 21.1, 21.2, 21.5 | 617 to 626; 633 to 635 | 13 | Standard algorithms, function objects, sorting and searching |

### Lessons and exercises

| Lesson | Time |
|---|---|
| [10. Strings, Regex and Time](https://ghaith-hamdi1.github.io/cpp-training/08-strings-regex-time.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/08-strings-regex-time-quiz.html) | 40 min |
| [11. The STL](https://ghaith-hamdi1.github.io/cpp-training/04-stl.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/04-stl-quiz.html) | 60 min |
| [12. Templates](https://ghaith-hamdi1.github.io/cpp-training/05-templates.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/05-templates-quiz.html) | 60 min |

Exercises: 12 (`Stack<T>`).

**Recap check.** Explain: when `vector` invalidates iterators, why `map::operator[]` can insert, what a strict weak ordering is, how a template is instantiated, and why `std::sort` does not work on `std::list`.

## Phase 4: Advanced language tools and design

*Exceptions and RAII, namespaces, unions and enums, memory control, design patterns.*

**Time:** about **8.7 hours** (6.6 h reading, 2.1 h lessons and quizzes, 0.0 h exercises), plus 3.3 h if you also read the deepen list.

### Big topics

| Topic | What it covers |
|---|---|
| **Exceptions and exception safety** | Throwing, catching by reference, stack unwinding, the three safety guarantees, `noexcept`. |
| **RAII and resource management** | Tying a resource to an object, scope guards, standard wrappers (`lock_guard`, `fstream`). |
| **Namespaces and large programs** | Namespace definition and use, `using`, headers and include guards, linkage. |
| **Enums, unions and nested types** | `enum class`, `union` and `variant`, nested and local classes, pointers to members. |
| **Controlling memory allocation** | Overloading `new`/`delete`, placement `new`, custom allocators. |
| **Design patterns and SOLID** | Singleton, Factory, Strategy, Observer, State, Command, Decorator, Adapter, Builder, Visitor, and the five principles. |

### Core reading (66 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| Primer | 5.6 `try` blocks; 18.1 Exception handling; 18.2 Namespaces | 222 to 228; 801 to 830 | 37 | Exceptions end to end, `noexcept`, namespaces |
| Primer | 19.1 Controlling memory allocation; 19.3 enumerations; 19.5 nested classes; 19.6 `union` | 849 to 853; 861 to 863; 872 to 875; 876 to 880 | 17 | Placement `new`, scoped enums, nested classes, unions |
| PPP | RAII, exceptions and resource management: 18.4 to 18.5 | 542 to 553 | 12 | Why RAII replaces `try`/`finally` |

### Deepen (optional, 33 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| EMC | Item 14 `noexcept`; Item 16 `const` member functions and threads | 108 to 115; 121 to 127 | 15 | Where `noexcept` really matters and the `mutable` mutex |
| EMC | Item 22 Pimpl | 165 to 174 | 10 | The one design pattern Meyers covers in depth |
| Primer | 19.4 Pointers to class members | 864 to 871 | 8 | Member function pointers, used under `std::function` and `std::invoke` |

### Lessons and exercises

| Lesson | Time |
|---|---|
| [6. Core Language: RAII and Exceptions](https://ghaith-hamdi1.github.io/cpp-training/03-core-language.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/03-core-language-quiz.html) | 35 min |
| [14. Design Patterns](https://ghaith-hamdi1.github.io/cpp-training/06-design-patterns.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/06-design-patterns-quiz.html) | 50 min |
| [15. More Patterns](https://ghaith-hamdi1.github.io/cpp-training/20-more-patterns.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/20-more-patterns-quiz.html) | 40 min |

Exercises: none (design patterns have no exercise; use the lessons' step-throughs).

> The design-pattern lessons have no matching book chapters in this set; the five books cover the language, not design. Use the lessons, and Item 22 of Effective Modern C++ for Pimpl.

**Recap check.** Explain: what stack unwinding does, why a destructor must not throw, the difference between basic and strong guarantee and how copy-and-swap gives the strong one, and when Strategy is just a lambda.

## Phase 5: Modern C++ (C++11 to C++20)

*Move semantics, smart pointers, lambdas, forwarding, `constexpr`, vocabulary types, concepts.*

**Time:** about **27.1 hours** (22.9 h reading, 3.3 h lessons and quizzes, 0.8 h exercises), plus 11.8 h if you also read the deepen list.

### Big topics

| Topic | What it covers |
|---|---|
| **Move semantics** | Value categories, rvalue references, what `std::move` does, writing move operations, copy elision, the move traps, `noexcept` moves. |
| **Smart pointers and ownership** | `unique_ptr`, `shared_ptr`, `weak_ptr`, control blocks, cycles, custom deleters, passing ownership. |
| **Lambdas and callables** | Captures and their lifetime traps, `mutable`, init-capture, generic lambdas, `std::function` versus templates. |
| **Type deduction and `auto`** | Template deduction rules, `auto` and `decltype`, structured bindings. |
| **Forwarding and variadic templates** | Forwarding references, reference collapsing, `std::forward`, parameter packs, fold expressions. |
| **Compile-time programming** | `constexpr`, `consteval`, type traits, `if constexpr`, SFINAE, concepts and `requires`. |
| **Vocabulary types** | `optional`, `variant` and `visit`, `expected`, `span`, `string_view`, `tuple`. |
| **Ranges and C++20** | Views and pipelines, `std::format`, `<=>`, `jthread` (see phase 6). |

### Core reading (229 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| Primer | 12.1 smart pointers (shared_ptr, unique_ptr, weak_ptr) | 479 to 486; 493 to 504 | 20 | The C++11 smart pointers |
| Primer | 13.6 Moving objects; 14.8 Function-call operator and `function` | 560 to 579; 600 to 607 | 28 | Rvalue references, move constructors; lambdas as function objects |
| Primer | 16.2.5 to 16.2.7 deduction, `std::move`, forwarding; 16.4 variadic templates | 716 to 722; 728 to 734 | 14 | Reference collapsing, perfect forwarding, parameter packs |
| EMC | Items 1, 2, 5, 7: deduction, `auto`, `()` versus `{}` | 27 to 41; 55 to 61; 67 to 76 | 32 | The deduction rules everything else uses |
| EMC | Item 15 `constexpr` | 115 to 121 | 7 | `constexpr` objects and functions |
| EMC | Items 18 to 22: `unique_ptr`, `shared_ptr`, `weak_ptr`, `make_*`, Pimpl | 136 to 174 | 39 | Smart pointers in depth |
| EMC | Items 23, 24, 25, 28: `move`, `forward`, universal references, reference collapsing | 176 to 195; 215 to 221 | 27 | The core of move semantics and forwarding |
| EMC | Items 26 to 27, 29, 41, 42: overloading, cheap moves, pass by value, emplacement | 195 to 215; 221 to 225; 299 to 320 | 48 | Moves in practice |
| EMC | Items 31, 32: lambdas | 234 to 247 | 14 | Default captures and init-capture |

### Deepen (optional, 118 pages)

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

### Lessons and exercises

| Lesson | Time |
|---|---|
| [3. Vocabulary Types](https://ghaith-hamdi1.github.io/cpp-training/21-vocabulary-types.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/21-vocabulary-types-quiz.html) | 35 min |
| [7. Move Semantics](https://ghaith-hamdi1.github.io/cpp-training/13-move-semantics.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/13-move-semantics-quiz.html) | 45 min |
| [8. Smart Pointers and Ownership](https://ghaith-hamdi1.github.io/cpp-training/14-smart-pointers.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/14-smart-pointers-quiz.html) | 40 min |
| [9. Lambdas and Callables](https://ghaith-hamdi1.github.io/cpp-training/15-lambdas.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/15-lambdas-quiz.html) | 35 min |
| [13. Type Traits and Compile-time C++](https://ghaith-hamdi1.github.io/cpp-training/09-compile-time.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/09-compile-time-quiz.html) | 45 min |

Exercises: 15 (`optional`/`variant`) and 16 (concepts).

> C++ Primer (2013) stops at C++11, so for C++14, C++17 and C++20 features (vocabulary types, `if constexpr`, concepts, ranges, structured bindings) the lessons and Effective Modern C++ are the sources. Josuttis is a deep dive: read it after Effective Modern C++ if move semantics is the part you want to master.

**Recap check.** Explain: what `std::move` does at run time (nothing), why `return std::move(local)` hurts, the three value categories, what a forwarding reference is, why `make_shared` needs one allocation, how a lambda is compiled, and what a concept replaces.

## Phase 6: Concurrency and the memory model

*Threads, mutexes, condition variables, futures and pools, atomics.*

**Time:** about **14.4 hours** (10.9 h reading, 2.7 h lessons and quizzes, 0.8 h exercises), plus 3.9 h if you also read the deepen list.

### Big topics

| Topic | What it covers |
|---|---|
| **Threads and data races** | Launching, joining, passing arguments, shared data, what a data race is. |
| **Mutexes and deadlock** | `lock_guard`, `unique_lock`, `scoped_lock`, interface races, deadlock and lock ordering. |
| **Condition variables and queues** | Waiting with a predicate, lost wakeups, a thread-safe queue. |
| **Tasks, futures and pools** | `async`, `promise`, `packaged_task`, thread pools, work stealing, `latch`/`barrier`/`jthread`. |
| **Atomics and the memory model** | `std::atomic`, compare-and-swap, memory orders, happens-before, lock-free structures. |

### Core reading (109 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| Concurrency in Action | Why threads and launching them: 1.1, 1.2.3, 2.1, 2.2 | 25 to 30; 32 to 33; 40 to 50 | 19 | The model and the basic API |
| Concurrency in Action | Sharing data and mutexes: 3.1, 3.2.1 to 3.2.3 | 60 to 74 | 15 | Invariants, race conditions inherent in interfaces |
| Concurrency in Action | Deadlock and locking: 3.2.4 to 3.2.8, 3.3.1 | 74 to 91 | 18 | Lock ordering, `unique_lock`, `call_once` |
| Concurrency in Action | Waiting for events and results: 4.1, 4.2.1 to 4.2.4 | 96 to 113 | 18 | Condition variables, futures, `promise` |
| Concurrency in Action | Thread counts and a pool: 2.4, 9.1.1 | 54 to 57; 324 to 326 | 7 | How many threads; the simplest pool |
| Concurrency in Action | The memory model and data structures: 5.1, 5.3 overview, 6.1 to 6.2.2 | 148 to 151; 165 to 170; 197 to 206 | 20 | Memory locations, orderings, a thread-safe stack and queue |
| Concurrency in Action | Performance and bugs: 8.2, 11.1 to 11.2.1 | 283 to 289; 363 to 367 | 12 | False sharing, oversubscription, kinds of concurrency bug |

### Deepen (optional, 39 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| EMC | Items 35 to 40: tasks, launch policies, joining, futures, one-shot events, `atomic` versus `volatile` | 259 to 297 | 39 | A compact second opinion on the same ground |

### Lessons and exercises

| Lesson | Time |
|---|---|
| [16. Multithreading](https://ghaith-hamdi1.github.io/cpp-training/07-multithreading.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/07-multithreading-quiz.html) | 60 min |
| [17. Tasks and Parallelism](https://ghaith-hamdi1.github.io/cpp-training/17-tasks-parallelism.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/17-tasks-parallelism-quiz.html) | 45 min |
| [18. Atomics and the Memory Model](https://ghaith-hamdi1.github.io/cpp-training/18-atomics-memory-model.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/18-atomics-memory-model-quiz.html) | 55 min |

Exercises: 13 (`SafeCounter`) and 14 (`BoundedQueue<T>`).

> C++ Primer and Programming: Principles and Practice have no chapters on threads. Concurrency in Action is the main book; Effective Modern C++ items 35 to 40 are the short version.

**Recap check.** Explain: what a data race is and why it is undefined behavior, why a mutex per method is not enough, the four conditions for deadlock, why `wait` needs a predicate, what release and acquire guarantee, and what the ABA problem is.

## Phase 7: Performance, memory layout and binary data

*Cache, allocation, struct layout, endianness, parsing, queues.*

**Time:** about **3.9 hours** (1.5 h reading, 2.0 h lessons and quizzes, 0.4 h exercises), plus 0.7 h if you also read the deepen list.

### Big topics

| Topic | What it covers |
|---|---|
| **Where latency comes from** | Tail latency, percentiles, measuring correctly, the cost of allocation, exceptions, system calls. |
| **Memory on the hot path** | Preallocation, object pools, arenas, placement `new`. |
| **Cache-friendly data** | Contiguous versus linked, array of structs versus struct of arrays, false sharing, dense keys instead of maps. |
| **Binary data and parsing** | Bit manipulation, struct padding and alignment, endianness, aliasing and `memcpy`, zero-copy parsing, fixed-point numbers, sequence numbers. |
| **Queues and pipelines** | SPSC ring buffers, bounded queues and drop policies, busy-polling and thread pinning. |

### Core reading (15 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| Primer | 17.2 `bitset`; 19.8 bit-fields, `volatile`, `extern "C"` | 752 to 756; 883 to 892 | 15 | The only low-level chapters in the five books; the rest is in the lessons |

### Deepen (optional, 7 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| Concurrency in Action | 8.2 Factors affecting the performance of concurrent code (also in phase 6) | 283 to 289 | 7 | Cache ping-pong and false sharing |

### Lessons and exercises

| Lesson | Time |
|---|---|
| [19. Binary Data and Parsing](https://ghaith-hamdi1.github.io/cpp-training/11-wire-formats.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/11-wire-formats-quiz.html) | 60 min |
| [20. Performance and Memory](https://ghaith-hamdi1.github.io/cpp-training/12-low-latency.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/12-low-latency-quiz.html) | 60 min |

Exercises: 17 (`BucketTable`).

> None of the five books covers this phase, so the two lessons are the main source. The C++ Primer sections are a small supplement.

**Recap check.** Explain: why the average hides the tail, how an object pool works, why a struct is bigger than the sum of its members, what endianness is and the portable way to read a big-endian value, and what false sharing is.

## Topic index: where to look

A one-page reminder: every big topic, the lesson that teaches it and the book chapter that explains it best (PDF pages).

| Topic | Lesson | Best book chapter |
|---|---|---|
| Types, initialization, `auto` | [2. Types, Initialization and Casts](https://ghaith-hamdi1.github.io/cpp-training/16-types-and-casts.html) | Primer 2.1 to 2.5 (61 to 100) |
| Expressions and conversions | [2. Types, Initialization and Casts](https://ghaith-hamdi1.github.io/cpp-training/16-types-and-casts.html) | Primer 4.11 (188 to 194) |
| Functions and argument passing | [1. Basics and Pointers](https://ghaith-hamdi1.github.io/cpp-training/01-basics.html) | Primer ch. 6 (231 to 281) |
| Pointers, references, `const` | [1. Basics and Pointers](https://ghaith-hamdi1.github.io/cpp-training/01-basics.html) | Primer 2.3 to 2.4 (79 to 95); PPP 15.3 to 15.5 (452 to 463) |
| Strings, vectors, arrays | [1. Basics and Pointers](https://ghaith-hamdi1.github.io/cpp-training/01-basics.html) | Primer ch. 3 (113 to 161) |
| Vocabulary types (`optional`, `variant`, `span`) | [3. Vocabulary Types](https://ghaith-hamdi1.github.io/cpp-training/21-vocabulary-types.html) | Primer 17.1 tuple (747 to 751); EMC Item 5 (55 to 61) |
| Classes and invariants | [4. Object-Oriented Programming](https://ghaith-hamdi1.github.io/cpp-training/02-oop.html) | Primer ch. 7 (283 to 335); PPP 8.1 to 8.7 (235 to 258) |
| Copy control, Rule of 3/5/0 | [4. Object-Oriented Programming](https://ghaith-hamdi1.github.io/cpp-training/02-oop.html) | Primer 13.1 to 13.5 (525 to 559); Move Semantics 3.3 to 3.4 (66 to 76) |
| Operator overloading, conversions | [4. Object-Oriented Programming](https://ghaith-hamdi1.github.io/cpp-training/02-oop.html) | Primer ch. 14 (581 to 619) |
| Inheritance, virtual functions | [4. Object-Oriented Programming](https://ghaith-hamdi1.github.io/cpp-training/02-oop.html) | Primer ch. 15 (621 to 679); PPP 12.3 (380 to 387) |
| Object model, multiple inheritance, RTTI | [5. The Object Model in Depth](https://ghaith-hamdi1.github.io/cpp-training/19-object-model.html) | Primer 18.3, 19.2 (831 to 847; 854 to 860) |
| RAII and exceptions | [6. Core Language: RAII and Exceptions](https://ghaith-hamdi1.github.io/cpp-training/03-core-language.html) | Primer 18.1 (801 to 813); PPP 18.4 to 18.5 (542 to 553) |
| Move semantics and value categories | [7. Move Semantics](https://ghaith-hamdi1.github.io/cpp-training/13-move-semantics.html) | Primer 13.6 (560 to 579); EMC Items 23, 25 (176 to 195); Move Semantics ch. 2 (43 to 52) |
| Smart pointers | [8. Smart Pointers and Ownership](https://ghaith-hamdi1.github.io/cpp-training/14-smart-pointers.html) | Primer 12.1 (479 to 504); EMC Items 18 to 22 (136 to 174) |
| Lambdas and callables | [9. Lambdas and Callables](https://ghaith-hamdi1.github.io/cpp-training/15-lambdas.html) | Primer 10.3, 14.8 (414 to 429; 600 to 607); EMC Items 31 to 32 (234 to 247) |
| Strings, regex, time | [10. Strings, Regex and Time](https://ghaith-hamdi1.github.io/cpp-training/08-strings-regex-time.html) | Primer 9.5, 17.3 (389 to 396; 757 to 773) |
| The STL: containers, iterators, algorithms | [11. The STL](https://ghaith-hamdi1.github.io/cpp-training/04-stl.html) | Primer ch. 9 to 11 (355 to 477); PPP 19 to 21 (559 to 635) |
| Templates | [12. Templates](https://ghaith-hamdi1.github.io/cpp-training/05-templates.html) | Primer ch. 16 (681 to 743); EMC Item 1 (27 to 36) |
| Forwarding and variadics | [12. Templates](https://ghaith-hamdi1.github.io/cpp-training/05-templates.html) | Primer 16.2.5 to 16.4 (716 to 734); EMC Item 28 (215 to 221) |
| Type traits, `constexpr`, concepts | [13. Type Traits and Compile-time C++](https://ghaith-hamdi1.github.io/cpp-training/09-compile-time.html) | EMC Item 15 (115 to 121); PPP 18.1.2 to 18.1.4 (530 to 534) |
| Design patterns, SOLID | [14. Design Patterns](https://ghaith-hamdi1.github.io/cpp-training/06-design-patterns.html) | lessons only; EMC Item 22 Pimpl (165 to 174) |
| Threads, mutexes, deadlock | [16. Multithreading](https://ghaith-hamdi1.github.io/cpp-training/07-multithreading.html) | Concurrency in Action ch. 2 to 4 (40 to 113) |
| Futures, pools, tasks | [17. Tasks and Parallelism](https://ghaith-hamdi1.github.io/cpp-training/17-tasks-parallelism.html) | Concurrency in Action 4.2, 9.1.1 (105 to 113; 324 to 326); EMC Items 35 to 39 (259 to 289) |
| Atomics and the memory model | [18. Atomics and the Memory Model](https://ghaith-hamdi1.github.io/cpp-training/18-atomics-memory-model.html) | Concurrency in Action 5.1, 5.3 (148 to 151; 165 to 170); EMC Item 40 (289 to 297) |
| Binary data, endianness, aliasing | [19. Binary Data and Parsing](https://ghaith-hamdi1.github.io/cpp-training/11-wire-formats.html) | Primer 17.2, 19.8 (752 to 756; 883 to 892); lessons mainly |
| Performance, cache, pools | [20. Performance and Memory](https://ghaith-hamdi1.github.io/cpp-training/12-low-latency.html) | Concurrency in Action 8.2 (283 to 289); lessons mainly |

## Notes on the books

- **C++ Primer is a C++11 book.** It does not cover structured bindings, `if constexpr`, `std::optional`/`variant`/`string_view`, concepts, ranges or the C++14 to C++20 library. Phase 5 therefore leans on Effective Modern C++, Move Semantics and the lessons for those.
- **Programming: Principles and Practice** teaches C++20 style from the start (it uses `span`, concepts and `std::format`), but stays introductory on templates and has no threading chapter.
- **Skip on a first pass:** Primer chapters 1, 4 (except 4.8 and 4.11), 5 and the Text-Query case studies in 12.3, 15.9 and 15.8; the Primer appendix; PPP chapters on graphics and the calculator (10 to 14, 6 to 7); Concurrency in Action chapter 7 (lock-free data structures) until phase 6 is solid.
- Each phase's book sections come from the reading guides and plans next to this file, which were checked against the PDFs. The C++ Primer sections use printed page numbers shifted by 29 to PDF pages, checked at chapter openings.
- **Notes templates** for the Primer-style sessions live in [`notes/`](notes).
