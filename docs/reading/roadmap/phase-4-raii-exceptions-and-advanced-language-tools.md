# Phase 4: RAII, exceptions and advanced language tools

[Roadmap](README.md) | Previous: [Phase 3: The standard library and generic programming](phase-3-the-standard-library-and-generic-programming.md) | Next: [Phase 5: Modern C++ (C++11 to C++20)](phase-5-modern-cpp.md)

*Exceptions and RAII, namespaces, unions and enums, memory control.*

**Time:** about **7.2 hours** (6.6 h reading, 0.6 h lessons and quizzes, 0.0 h exercises), plus 2.3 h if you also read the deepen list.

## Big topics

| Topic | What it covers |
|---|---|
| **Exceptions and exception safety** | Throwing, catching by reference, stack unwinding, the three safety guarantees, `noexcept`. |
| **RAII and resource management** | Tying a resource to an object, scope guards, standard wrappers (`lock_guard`, `fstream`). |
| **Namespaces and large programs** | Namespace definition and use, `using`, headers and include guards, linkage. |
| **Enums, unions and nested types** | `enum class`, `union` and `variant`, nested and local classes, pointers to members. |
| **Controlling memory allocation** | Overloading `new`/`delete`, placement `new`, custom allocators. |

## Core reading (66 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| Primer | 5.6 `try` blocks; 18.1 Exception handling; 18.2 Namespaces | 222 to 228; 801 to 830 | 37 | Exceptions end to end, `noexcept`, namespaces |
| Primer | 19.1 Controlling memory allocation; 19.3 enumerations; 19.5 nested classes; 19.6 `union` | 849 to 853; 861 to 863; 872 to 875; 876 to 880 | 17 | Placement `new`, scoped enums, nested classes, unions |
| PPP | RAII, exceptions and resource management: 18.4 to 18.5 | 542 to 553 | 12 | Why RAII replaces `try`/`finally` |

## Deepen (optional, 23 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| EMC | Item 14 `noexcept`; Item 16 `const` member functions and threads | 108 to 115; 121 to 127 | 15 | Where `noexcept` really matters and the `mutable` mutex |
| Primer | 19.4 Pointers to class members | 864 to 871 | 8 | Member function pointers, used under `std::function` and `std::invoke` |

## Lessons and exercises

| Lesson | Time |
|---|---|
| [9. Core Language: RAII & Exceptions](https://ghaith-hamdi1.github.io/cpp-training/03-core-language.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/03-core-language-quiz.html) | 35 min |

Exercises: none (use the lesson's step-throughs and quiz).

**Recap check.** Explain: what stack unwinding does, why a destructor must not throw, the difference between basic and strong guarantee and how copy-and-swap gives the strong one.

**Notes templates.** [Reading notes for phase 4](../notes/phase-4-raii-exceptions-and-advanced-language-tools/README.md).

---

[Roadmap](README.md) | Previous: [Phase 3: The standard library and generic programming](phase-3-the-standard-library-and-generic-programming.md) | Next: [Phase 5: Modern C++ (C++11 to C++20)](phase-5-modern-cpp.md)
