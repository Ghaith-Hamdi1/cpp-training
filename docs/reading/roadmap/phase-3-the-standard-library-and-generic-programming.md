# Phase 3: The standard library and generic programming

[Roadmap](README.md) | Previous: [Phase 2: Classes, memory and object-oriented design](phase-2-classes-memory-and-object-oriented-design.md) | Next: [Phase 4: Advanced language tools and design](phase-4-advanced-language-tools-and-design.md)

*Streams, containers, iterators, algorithms, templates.*

**Time:** about **24.8 hours** (21.7 h reading, 2.7 h lessons and quizzes, 0.4 h exercises), plus 6.7 h if you also read the deepen list.

## Big topics

| Topic | What it covers |
|---|---|
| **I/O and streams** | Stream state, files, string streams, formatted input and output, `std::format` as the modern alternative. |
| **Sequential containers** | `vector`, `deque`, `list`, `array`; how `vector` grows; invalidation rules; `string` operations. |
| **Associative and unordered containers** | `map`/`set`, `unordered_map`, custom keys, comparators and hashes, `try_emplace`. |
| **Iterators and algorithms** | Iterator categories, the algorithm header, predicates and function objects, erase-remove, `lower_bound`. |
| **Function and class templates** | Instantiation, argument deduction, non-type parameters, template argument rules. |
| **Specialization and overloading with templates** | Full and partial specialization, function matching with templates. |
| **Specialized library facilities** | `tuple`, `bitset`, regular expressions, random numbers. |

## Core reading (217 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| Primer | ch. 8 The IO Library | 339 to 353 | 15 | Streams, files, string streams |
| Primer | ch. 9 Sequential Containers (9.1 to 9.6) | 355 to 403 | 49 | Containers, operations, how `vector` grows, string operations, adaptors |
| Primer | ch. 10 Generic Algorithms (10.1 to 10.6) | 405 to 447 | 43 | Algorithms, lambdas as predicates, iterator categories |
| Primer | ch. 11 Associative Containers (11.1 to 11.4) | 449 to 477 | 29 | `map`, `set`, unordered containers |
| Primer | ch. 16 Templates: 16.1 to 16.3, 16.5 (skip 16.2.5 to 16.2.7 and 16.4 until phase 5) | 681 to 706; 707 to 718; 723 to 727; 735 to 743 | 52 | Function and class templates, deduction, overloading, specialization |
| Primer | ch. 17: 17.1 tuple; 17.3 regular expressions; 17.4 random numbers | 747 to 751; 757 to 773; 774 to 780 | 29 | The library pieces the lessons also cover |

## Deepen (optional, 67 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| PPP | Templates and concepts: 18.1 to 18.3 | 527 to 541 | 15 | Templates from the idea down, with a first look at concepts |
| PPP | Containers and iterators: 19.1 to 19.3, 19.6; 20.1 to 20.2 | 559 to 572; 585 to 586; 591 to 598 | 24 | How the STL is designed |
| PPP | Choosing a container: 20.3 to 20.7.1 | 598 to 612 | 15 | Container overview, iterator categories, timing |
| PPP | Algorithms: 21.1, 21.2, 21.5 | 617 to 626; 633 to 635 | 13 | Standard algorithms, function objects, sorting and searching |

## Lessons and exercises

| Lesson | Time |
|---|---|
| [10. Strings, Regex and Time](https://ghaith-hamdi1.github.io/cpp-training/08-strings-regex-time.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/08-strings-regex-time-quiz.html) | 40 min |
| [11. The STL](https://ghaith-hamdi1.github.io/cpp-training/04-stl.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/04-stl-quiz.html) | 60 min |
| [12. Templates](https://ghaith-hamdi1.github.io/cpp-training/05-templates.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/05-templates-quiz.html) | 60 min |

Exercises: 12 (`Stack<T>`).

**Recap check.** Explain: when `vector` invalidates iterators, why `map::operator[]` can insert, what a strict weak ordering is, how a template is instantiated, and why `std::sort` does not work on `std::list`.

---

[Roadmap](README.md) | Previous: [Phase 2: Classes, memory and object-oriented design](phase-2-classes-memory-and-object-oriented-design.md) | Next: [Phase 4: Advanced language tools and design](phase-4-advanced-language-tools-and-design.md)
