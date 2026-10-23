# Phase 6: Design patterns and SOLID

[Roadmap](README.md) | Previous: [Phase 5: Modern C++ (C++11 to C++20)](phase-5-modern-cpp.md) | Next: [Phase 7: Concurrency and the memory model](phase-7-concurrency-and-the-memory-model.md)

*Common designs in modern C++, with real code.*

**Time:** about **1.5 hours** (0.0 h reading, 1.5 h lessons and quizzes, 0.0 h exercises), plus 1.0 h if you also read the deepen list.

## Big topics

| Topic | What it covers |
|---|---|
| **What patterns are and are not** | Patterns as names for recurring solutions, and when they are overkill. |
| **SOLID** | The five principles and how they show up in C++ interfaces. |
| **Creational** | Singleton, Factory, Builder. |
| **Behavioral** | Strategy (often just a lambda), Observer, State, Command with undo, Visitor with `variant`. |
| **Structural** | Decorator, Adapter, Pimpl. |

## Core reading

No book in this set covers this phase; the lessons are the core.

## Deepen (optional, 10 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| EMC | Item 22 Pimpl | 165 to 174 | 10 | The one design pattern Meyers covers in depth |

## Lessons and exercises

| Lesson | Time |
|---|---|
| [14. Design Patterns](https://ghaith-hamdi1.github.io/cpp-training/06-design-patterns.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/06-design-patterns-quiz.html) | 50 min |
| [15. More Patterns](https://ghaith-hamdi1.github.io/cpp-training/20-more-patterns.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/20-more-patterns-quiz.html) | 40 min |

Exercises: none (use the lessons' step-throughs and quizzes).

> No book in this set covers design patterns, so the two lessons are the only source; Item 22 of Effective Modern C++ covers the Pimpl idiom.

**Recap check.** Explain: when Strategy is just a lambda, why Singleton is a global with a nicer name, how Observer avoids dangling subscribers, and how `variant` plus `visit` replaces a Visitor class hierarchy.

---

[Roadmap](README.md) | Previous: [Phase 5: Modern C++ (C++11 to C++20)](phase-5-modern-cpp.md) | Next: [Phase 7: Concurrency and the memory model](phase-7-concurrency-and-the-memory-model.md)
