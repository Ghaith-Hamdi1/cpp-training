# Phase 2: Classes, memory and object-oriented design

[Roadmap](README.md) | Previous: [Phase 1: Core language foundations](phase-1-core-language-foundations.md) | Next: [Phase 3: The standard library and generic programming](phase-3-the-standard-library-and-generic-programming.md)

*Class design, copy control, operator overloading, inheritance, virtual functions, the object model.*

**Time:** about **24.5 hours** (22.0 h reading, 1.7 h lessons and quizzes, 0.8 h exercises), plus 8.4 h if you also read the deepen list.

## Big topics

| Topic | What it covers |
|---|---|
| **Class design** | Invariants, encapsulation, constructors and the initializer list, `explicit`, `const` and `static` members, `friend`. |
| **Object lifetime** | Construction and destruction order, the destructor as cleanup, temporaries. |
| **Copy control** | The copy constructor and assignment, shallow versus deep copy, the Rule of Three, Five and Zero, `= default` and `= delete`, copy-and-swap. |
| **Dynamic memory** | `new`/`delete`, `new[]`/`delete[]`, leaks, double delete, why this is replaced by RAII in phase 4 and smart pointers in phase 5. |
| **Operator overloading and conversions** | Member versus non-member operators, `<<`/`>>`, comparison, `operator()`, conversion operators and `explicit`. |
| **Inheritance and polymorphism** | Public inheritance as is-a, virtual functions and `override`, virtual destructors, slicing, abstract classes and interfaces. |
| **The object model** | The vtable and vptr, multiple inheritance and pointer adjustment, the diamond and virtual inheritance, RTTI and `dynamic_cast`, private inheritance. |

## Core reading (220 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| Primer | ch. 7 Classes (7.1 to 7.6) | 283 to 335 | 53 | Abstract data types, constructors, `const`/`mutable`/`static` members, class scope |
| Primer | 12.1.2 Managing memory directly; 12.2.1 `new` and arrays | 487 to 492; 506 to 509 | 10 | `new`/`delete` and their pitfalls (read before copy control) |
| Primer | ch. 13 Copy Control (13.1 to 13.5) | 525 to 559 | 35 | Copy constructor, assignment, destructor, Rule of Three/Five, classes that manage memory |
| Primer | ch. 14 Overloaded Operations and Conversions (14.1 to 14.9) | 581 to 619 | 39 | Operator overloading and conversion operators |
| Primer | ch. 15 Object-Oriented Programming (15.1 to 15.9) | 621 to 679 | 59 | Base and derived classes, virtual functions, abstract classes, copy control with inheritance |
| Primer | 18.3 Multiple and virtual inheritance; 19.2 Run-time type identification | 831 to 847; 854 to 860 | 24 | The diamond, `dynamic_cast`, `typeid` |

## Deepen (optional, 84 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| PPP | Classes as a way to keep objects valid: 8.1 to 8.7 | 235 to 258 | 24 | Invariants and class interfaces |
| PPP | Inheritance and virtual functions: 12.1 to 12.5 | 369 to 390 | 22 | The vptr/vtbl layout and virtual destructors |
| PPP | Copying, moving and `vector` growth: 17.4 to 17.9 | 501 to 523 | 23 | Essential operations and how `vector` is built |
| EMC | Item 12 `override`; Item 17 special member generation | 97 to 104; 127 to 133 | 15 | The two items that fix the most real bugs in class design |

## Lessons and exercises

| Lesson | Time |
|---|---|
| [4. Object-Oriented Programming](https://ghaith-hamdi1.github.io/cpp-training/02-oop.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/02-oop-quiz.html) | 60 min |
| [5. The Object Model in Depth](https://ghaith-hamdi1.github.io/cpp-training/19-object-model.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/19-object-model-quiz.html) | 40 min |

Exercises: 10 (`MyString`) and 11 (Shapes).

**Recap check.** Explain aloud how `virtual` works in memory (vptr, vtable, slot), why a base destructor must be virtual, what the Rule of Zero says, and why `Animal a = dog;` slices.

---

[Roadmap](README.md) | Previous: [Phase 1: Core language foundations](phase-1-core-language-foundations.md) | Next: [Phase 3: The standard library and generic programming](phase-3-the-standard-library-and-generic-programming.md)
