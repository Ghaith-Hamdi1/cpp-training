# Reading notes

One template file per reading session, filled in as you read. The folders follow the [C++ roadmap](../roadmap/README.md): first by **phase**, then by **book** within each phase. Each book's sessions keep their order and numbers from its reading plan, so a phase folder can hold sessions from several books.

## By phase

| Phase | Books and sessions |
|---|---|
| [1. Core language foundations](phase-1-core-language-foundations/README.md) | C++ Primer, 5th ed.: 8; Programming: Principles and Practice, 3rd ed.: 5 |
| [2. Classes, memory and object-oriented design](phase-2-classes-memory-and-object-oriented-design/README.md) | C++ Primer, 5th ed.: 10; Programming: Principles and Practice, 3rd ed.: 3 |
| [3. The standard library and generic programming](phase-3-the-standard-library-and-generic-programming/README.md) | C++ Primer, 5th ed.: 10; Programming: Principles and Practice, 3rd ed.: 5; Effective Modern C++: 1 |
| [4. RAII, exceptions and advanced language tools](phase-4-raii-exceptions-and-advanced-language-tools/README.md) | C++ Primer, 5th ed.: 2; Programming: Principles and Practice, 3rd ed.: 1; Effective Modern C++: 1 |
| [5. Modern C++ (C++11 to C++20)](phase-5-modern-cpp/README.md) | C++ Primer, 5th ed.: 2; Effective Modern C++: 4; C++ Move Semantics: The Complete Guide: 7 |
| [6. Design patterns and SOLID](phase-6-design-patterns-and-solid/README.md) | lessons only |
| [7. Concurrency and the memory model](phase-7-concurrency-and-the-memory-model/README.md) | Effective Modern C++: 1; C++ Concurrency in Action, 2nd ed.: 7 |
| [8. Performance, memory layout and binary data](phase-8-performance-memory-layout-and-binary-data/README.md) | C++ Primer, 5th ed.: 1 |

## By book

The reading plans give the order to read each book in. Every session below links to its notes file.

### C++ Primer, 5th ed.

Plan: [cpp-primer-reading-plan.md](../cpp-primer-reading-plan.md).

| # | Session | Phase | Notes file |
|---|---|---|---|
| 1 | Types and variables | 1 | [01-types-and-variables.md](phase-1-core-language-foundations/cpp-primer/01-types-and-variables.md) |
| 2 | Compound types, const and auto | 1 | [02-compound-types-and-const.md](phase-1-core-language-foundations/cpp-primer/02-compound-types-and-const.md) |
| 3 | Structs, strings and vectors | 1 | [03-structs-strings-and-vectors.md](phase-1-core-language-foundations/cpp-primer/03-structs-strings-and-vectors.md) |
| 4 | Iterators and arrays | 1 | [04-iterators-and-arrays.md](phase-1-core-language-foundations/cpp-primer/04-iterators-and-arrays.md) |
| 5 | Expressions and conversions | 1 | [05-expressions.md](phase-1-core-language-foundations/cpp-primer/05-expressions.md) |
| 6 | Statements and a first look at exceptions | 1 | [06-statements-and-exceptions.md](phase-1-core-language-foundations/cpp-primer/06-statements-and-exceptions.md) |
| 7 | Functions: arguments and returns | 1 | [07-functions-arguments-and-returns.md](phase-1-core-language-foundations/cpp-primer/07-functions-arguments-and-returns.md) |
| 8 | Functions: overloading and function pointers | 1 | [08-functions-overloading-and-pointers.md](phase-1-core-language-foundations/cpp-primer/08-functions-overloading-and-pointers.md) |
| 9 | Classes: abstract data types | 2 | [09-classes-abstract-data-types.md](phase-2-classes-memory-and-object-oriented-design/cpp-primer/09-classes-abstract-data-types.md) |
| 10 | Classes: scope, constructors, static members | 2 | [10-classes-scope-and-constructors.md](phase-2-classes-memory-and-object-oriented-design/cpp-primer/10-classes-scope-and-constructors.md) |
| 11 | The IO library | 3 | [11-io-library.md](phase-3-the-standard-library-and-generic-programming/cpp-primer/11-io-library.md) |
| 12 | Sequential containers | 3 | [12-sequential-containers.md](phase-3-the-standard-library-and-generic-programming/cpp-primer/12-sequential-containers.md) |
| 13 | How vector grows, string operations, adaptors | 3 | [13-vector-growth-strings-adaptors.md](phase-3-the-standard-library-and-generic-programming/cpp-primer/13-vector-growth-strings-adaptors.md) |
| 14 | Generic algorithms and lambdas | 3 | [14-generic-algorithms.md](phase-3-the-standard-library-and-generic-programming/cpp-primer/14-generic-algorithms.md) |
| 15 | Iterators revisited, algorithm structure | 3 | [15-iterators-revisited.md](phase-3-the-standard-library-and-generic-programming/cpp-primer/15-iterators-revisited.md) |
| 16 | Associative and unordered containers | 3 | [16-associative-containers.md](phase-3-the-standard-library-and-generic-programming/cpp-primer/16-associative-containers.md) |
| 17 | Dynamic memory and smart pointers | 5 | [17-dynamic-memory-and-smart-pointers.md](phase-5-modern-cpp/cpp-primer/17-dynamic-memory-and-smart-pointers.md) |
| 18 | Dynamic arrays and a worked program | 2 | [18-dynamic-arrays-and-text-query.md](phase-2-classes-memory-and-object-oriented-design/cpp-primer/18-dynamic-arrays-and-text-query.md) |
| 19 | Copy control | 2 | [19-copy-control.md](phase-2-classes-memory-and-object-oriented-design/cpp-primer/19-copy-control.md) |
| 20 | A class that manages memory | 2 | [20-copy-control-in-practice.md](phase-2-classes-memory-and-object-oriented-design/cpp-primer/20-copy-control-in-practice.md) |
| 21 | Moving objects | 5 | [21-moving-objects.md](phase-5-modern-cpp/cpp-primer/21-moving-objects.md) |
| 22 | Overloaded operators and function objects | 2 | [22-overloaded-operators.md](phase-2-classes-memory-and-object-oriented-design/cpp-primer/22-overloaded-operators.md) |
| 23 | Conversions, base and derived classes | 2 | [23-conversions-and-inheritance-basics.md](phase-2-classes-memory-and-object-oriented-design/cpp-primer/23-conversions-and-inheritance-basics.md) |
| 24 | Virtual functions, abstract classes, access | 2 | [24-virtual-functions-and-access.md](phase-2-classes-memory-and-object-oriented-design/cpp-primer/24-virtual-functions-and-access.md) |
| 25 | Constructors, copy control and containers under inheritance | 2 | [25-inheritance-and-copy-control.md](phase-2-classes-memory-and-object-oriented-design/cpp-primer/25-inheritance-and-copy-control.md) |
| 26 | Defining templates | 3 | [26-defining-templates.md](phase-3-the-standard-library-and-generic-programming/cpp-primer/26-defining-templates.md) |
| 27 | Template argument deduction and overloading | 3 | [27-deduction-and-overloading.md](phase-3-the-standard-library-and-generic-programming/cpp-primer/27-deduction-and-overloading.md) |
| 28 | Variadic templates and specialization | 3 | [28-variadic-templates-and-specialization.md](phase-3-the-standard-library-and-generic-programming/cpp-primer/28-variadic-templates-and-specialization.md) |
| 29 | tuple, regular expressions and random numbers | 3 | [29-specialized-library-facilities.md](phase-3-the-standard-library-and-generic-programming/cpp-primer/29-specialized-library-facilities.md) |
| 30 | Exception handling and namespaces | 4 | [30-exceptions-and-namespaces.md](phase-4-raii-exceptions-and-advanced-language-tools/cpp-primer/30-exceptions-and-namespaces.md) |
| 31 | Multiple inheritance and RTTI | 2 | [31-multiple-inheritance-and-rtti.md](phase-2-classes-memory-and-object-oriented-design/cpp-primer/31-multiple-inheritance-and-rtti.md) |
| 32 | Memory control, enums, unions, nested classes | 4 | [32-specialized-tools.md](phase-4-raii-exceptions-and-advanced-language-tools/cpp-primer/32-specialized-tools.md) |
| 33 | Optional extras | 8 | [33-optional-extras.md](phase-8-performance-memory-layout-and-binary-data/cpp-primer/33-optional-extras.md) |

### Programming: Principles and Practice, 3rd ed.

Plan: [programming-principles-and-practice-reading-plan.md](../programming-principles-and-practice-reading-plan.md).

| # | Session | Phase | Notes file |
|---|---|---|---|
| 1 | Types, initialization and auto | 1 | [01-types-initialization-auto.md](phase-1-core-language-foundations/programming-principles-and-practice/01-types-initialization-auto.md) |
| 2 | Functions, vector and errors | 1 | [02-functions-vector-errors.md](phase-1-core-language-foundations/programming-principles-and-practice/02-functions-vector-errors.md) |
| 3 | Declarations, scope and passing arguments | 1 | [03-declarations-scope-arguments.md](phase-1-core-language-foundations/programming-principles-and-practice/03-declarations-scope-arguments.md) |
| 4 | Classes as a way to keep objects valid | 2 | [04-classes-and-invariants.md](phase-2-classes-memory-and-object-oriented-design/programming-principles-and-practice/04-classes-and-invariants.md) |
| 5 | Inheritance and virtual functions | 2 | [05-inheritance-and-virtual-functions.md](phase-2-classes-memory-and-object-oriented-design/programming-principles-and-practice/05-inheritance-and-virtual-functions.md) |
| 6 | Memory, addresses and pointers | 1 | [06-memory-addresses-pointers.md](phase-1-core-language-foundations/programming-principles-and-practice/06-memory-addresses-pointers.md) |
| 7 | Arrays, this and the alternatives to raw pointers | 1 | [07-arrays-this-alternatives-to-raw-pointers.md](phase-1-core-language-foundations/programming-principles-and-practice/07-arrays-this-alternatives-to-raw-pointers.md) |
| 8 | Copying, moving and vector growth | 2 | [08-copying-moving-vector-growth.md](phase-2-classes-memory-and-object-oriented-design/programming-principles-and-practice/08-copying-moving-vector-growth.md) |
| 9 | Templates and concepts | 3 | [09-templates-and-concepts.md](phase-3-the-standard-library-and-generic-programming/programming-principles-and-practice/09-templates-and-concepts.md) |
| 10 | RAII, exceptions and smart pointers | 4 | [10-raii-exceptions-smart-pointers.md](phase-4-raii-exceptions-and-advanced-language-tools/programming-principles-and-practice/10-raii-exceptions-smart-pointers.md) |
| 11 | Containers and iterators | 3 | [11-containers-and-iterators.md](phase-3-the-standard-library-and-generic-programming/programming-principles-and-practice/11-containers-and-iterators.md) |
| 12 | Choosing a container | 3 | [12-choosing-a-container.md](phase-3-the-standard-library-and-generic-programming/programming-principles-and-practice/12-choosing-a-container.md) |
| 13 | Algorithms | 3 | [13-algorithms.md](phase-3-the-standard-library-and-generic-programming/programming-principles-and-practice/13-algorithms.md) |
| 14 | Streams and finishing touches (optional) | 3 | [14-streams-and-finishing-touches.md](phase-3-the-standard-library-and-generic-programming/programming-principles-and-practice/14-streams-and-finishing-touches.md) |

### Effective Modern C++

Plan: [effective-modern-cpp-reading-plan.md](../effective-modern-cpp-reading-plan.md).

| # | Session | Phase | Notes file |
|---|---|---|---|
| 1 | Deduction, auto and initialization | 5 | [01-deduction-auto-initialization.md](phase-5-modern-cpp/effective-modern-cpp/01-deduction-auto-initialization.md) |
| 2 | Interfaces that say what they mean | 4 | [02-interfaces-that-say-what-they-mean.md](phase-4-raii-exceptions-and-advanced-language-tools/effective-modern-cpp/02-interfaces-that-say-what-they-mean.md) |
| 3 | Special members and smart pointers | 5 | [03-special-members-and-smart-pointers.md](phase-5-modern-cpp/effective-modern-cpp/03-special-members-and-smart-pointers.md) |
| 4 | std::move, std::forward and universal references | 5 | [04-move-forward-universal-references.md](phase-5-modern-cpp/effective-modern-cpp/04-move-forward-universal-references.md) |
| 5 | Overloading and moves in practice | 5 | [05-overloading-and-moves-in-practice.md](phase-5-modern-cpp/effective-modern-cpp/05-overloading-and-moves-in-practice.md) |
| 6 | Lambdas | 3 | [06-lambdas.md](phase-3-the-standard-library-and-generic-programming/effective-modern-cpp/06-lambdas.md) |
| 7 | Concurrency | 7 | [07-concurrency.md](phase-7-concurrency-and-the-memory-model/effective-modern-cpp/07-concurrency.md) |

### C++ Move Semantics: The Complete Guide

Plan: [move-semantics-reading-plan.md](../move-semantics-reading-plan.md).

| # | Session | Phase | Notes file |
|---|---|---|---|
| 1 | The core idea | 5 | [01-the-core-idea.md](phase-5-modern-cpp/move-semantics-complete-guide/01-the-core-idea.md) |
| 2 | Special member functions | 5 | [02-special-member-functions.md](phase-5-modern-cpp/move-semantics-complete-guide/02-special-member-functions.md) |
| 3 | Passing and initializing | 5 | [03-passing-and-initializing.md](phase-5-modern-cpp/move-semantics-complete-guide/03-passing-and-initializing.md) |
| 4 | Moved-from states and noexcept | 5 | [04-moved-from-states-and-noexcept.md](phase-5-modern-cpp/move-semantics-complete-guide/04-moved-from-states-and-noexcept.md) |
| 5 | Value categories | 5 | [05-value-categories.md](phase-5-modern-cpp/move-semantics-complete-guide/05-value-categories.md) |
| 6 | Perfect forwarding | 5 | [06-perfect-forwarding.md](phase-5-modern-cpp/move-semantics-complete-guide/06-perfect-forwarding.md) |
| 7 | Move-only types, algorithms and the library | 5 | [07-move-only-types-algorithms-library.md](phase-5-modern-cpp/move-semantics-complete-guide/07-move-only-types-algorithms-library.md) |

### C++ Concurrency in Action, 2nd ed.

Plan: [concurrency-in-action-reading-plan.md](../concurrency-in-action-reading-plan.md).

| # | Session | Phase | Notes file |
|---|---|---|---|
| 1 | Why threads, and launching them | 7 | [01-why-threads-and-launching.md](phase-7-concurrency-and-the-memory-model/concurrency-in-action/01-why-threads-and-launching.md) |
| 2 | Sharing data and mutexes | 7 | [02-sharing-data-and-mutexes.md](phase-7-concurrency-and-the-memory-model/concurrency-in-action/02-sharing-data-and-mutexes.md) |
| 3 | Deadlock and locking | 7 | [03-deadlock-and-locking.md](phase-7-concurrency-and-the-memory-model/concurrency-in-action/03-deadlock-and-locking.md) |
| 4 | Waiting for events and results | 7 | [04-waiting-for-events-and-results.md](phase-7-concurrency-and-the-memory-model/concurrency-in-action/04-waiting-for-events-and-results.md) |
| 5 | How many threads, and a thread pool | 7 | [05-thread-counts-and-pools.md](phase-7-concurrency-and-the-memory-model/concurrency-in-action/05-thread-counts-and-pools.md) |
| 6 | The memory model and data structures | 7 | [06-memory-model-and-data-structures.md](phase-7-concurrency-and-the-memory-model/concurrency-in-action/06-memory-model-and-data-structures.md) |
| 7 | Performance and bugs | 7 | [07-performance-and-bugs.md](phase-7-concurrency-and-the-memory-model/concurrency-in-action/07-performance-and-bugs.md) |
