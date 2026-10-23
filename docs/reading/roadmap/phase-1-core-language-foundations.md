# Phase 1: Core language foundations

[Roadmap](README.md) | Next: [Phase 2: Classes, memory and object-oriented design](phase-2-classes-memory-and-object-oriented-design.md)

*Types, expressions, control flow, functions, pointers, references, strings and vectors.*

**Time:** about **22.9 hours** (19.0 h reading, 1.7 h lessons and quizzes, 2.3 h exercises), plus 8.6 h if you also read the deepen list.

## Big topics

| Topic | What it covers |
|---|---|
| **Types and initialization** | Built-in types, literals, `auto` and `decltype`, brace initialization and why it rejects narrowing, `const` and `constexpr` basics. |
| **Expressions and conversions** | Operator precedence, integer promotion, signed versus unsigned traps, bitwise operators, the named casts. |
| **Control flow** | `if`/`switch`, loops, range-for, `try`/`catch` first look. |
| **Functions** | Declarations versus definitions, passing by value, by reference and by `const` reference, return values, default arguments, overloading and overload resolution, function pointers. |
| **Pointers, references and arrays** | Addresses, `nullptr`, pointer arithmetic, array-to-pointer decay, reference rules, `const` with pointers, dangling and null dereference. |
| **Strings and vectors** | `std::string` and `std::vector` as the default tools, iterators as a first idea, `string_view`, C strings and why to avoid them. |
| **Scope, lifetime and storage** | Stack, heap and static storage, namespaces, `static`, linkage, the compile-link process. |

## Core reading (190 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| Primer | ch. 2 Variables and Basic Types (2.1 to 2.6) | 61 to 109 | 49 | Types, `const`, compound types, `auto`/`decltype`, defining your own structs |
| Primer | ch. 3 Strings, Vectors and Arrays (3.2 to 3.6) | 113 to 161 | 49 | `string`, `vector`, iterators, built-in arrays |
| Primer | 4.2 to 4.5 Operators (short-circuit `&&`/`||`, prefix versus postfix `++`); 4.8 Bitwise operators; 4.11 Type conversions | 168 to 178; 181 to 184; 188 to 194 | 22 | Operator rules, bit operations and every implicit conversion |
| Primer | 5.3 to 5.5 Statements: `switch` fall-through, the dangling `else`, loops and jumps | 203 to 221 | 19 | Control flow rules that hide subtle bugs |
| Primer | ch. 6 Functions (6.1 to 6.7) | 231 to 281 | 51 | Argument passing, overloading, function matching, function pointers |

## Deepen (optional, 86 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| PPP | Types and initialization: 2.5; 2.8 to 2.10 | 49 to 52; 56 to 60 | 9 | A shorter second view of initialization, conversions and `auto` |
| PPP | Functions and `vector`: 3.5 to 3.6; 4.5 to 4.6 | 81 to 89; 102 to 111 | 19 | Functions, `vector`, run-time errors and exceptions |
| PPP | Declarations, scope and argument passing: 7.2 to 7.4 | 194 to 218 | 25 | Scope, storage and how arguments are passed |
| PPP | Memory, addresses and pointers: 15.3 to 15.5 | 452 to 463 | 12 | Pointers, the free store, `delete`, dangling pointers |
| PPP | Arrays, `this`, alternatives to raw pointers: 15.6 to 15.8; 16.1 to 16.4 | 464 to 473; 477 to 487 | 21 | Arrays, references versus pointers, `span` |

## Lessons and exercises

| Lesson | Time |
|---|---|
| [1. C++ Basics & Pointers](https://ghaith-hamdi1.github.io/cpp-training/01-basics.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/01-basics-quiz.html) | 60 min |
| [2. Types, Initialization & Casts](https://ghaith-hamdi1.github.io/cpp-training/16-types-and-casts.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/16-types-and-casts-quiz.html) | 40 min |

Exercises: 01 to 09 (C strings, pointers, `trim`, `parseUnsigned`).

**Recap check.** Explain from memory: what `int* const p` means, why `int{3.7}` is an error, what `v[i]` does that `v.at(i)` does not, why an array parameter is really a pointer, and what the linker error "undefined reference" means.

**Notes templates.** [Reading notes for phase 1](../notes/phase-1-core-language-foundations/README.md).

---

[Roadmap](README.md) | Next: [Phase 2: Classes, memory and object-oriented design](phase-2-classes-memory-and-object-oriented-design.md)
