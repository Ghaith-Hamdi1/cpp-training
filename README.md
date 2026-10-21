# cpp-training: Advanced C++ Training Index

Embedded Team Academy · Presented by Mahdi SAKKA · Doc ref TR0014_G

This repo holds two separate C++ courses that cover much of the same ground:

| Course | Where | What it is |
|---|---|---|
| **Company training** (this index) | [`docs/`](docs/) + [`examples/`](examples/) | The 4 source PDFs converted into per-topic Markdown, with matching source code. Concise, slide-style, and includes embedded topics such as multithreading, design patterns and AUTOSAR coding rules. |
| **learncpp.com recaps** | [`LearnCPP/`](LearnCPP/) | Personal chapter-by-chapter recaps of [learncpp.com](https://www.learncpp.com/) ([index](LearnCPP/Recaps/README.md)), with solved exercises under [`LearnCPP/Recaps/solutions/`](LearnCPP/Recaps/solutions/). Slower and more thorough, aimed at fundamentals. |

Use the training notes for a quick pass or the embedded-specific topics, and the recaps when you want a topic explained in depth. The table below shows where each topic appears in both.

## Interactive study pages

For hands-on learning there are ten interactive lessons, each with a quiz, in [`interactive/`](interactive/index.html). Read them online at **https://ghaith-hamdi1.github.io/cpp-training/** (published from `interactive/` by GitHub Pages), or clone the repo and open `interactive/index.html` locally (no install, works offline).

| # | Lesson | Quiz |
|---|---|---|
| 1 | [C++ Basics and Pointers](interactive/01-basics.html) | [Quiz](interactive/01-basics-quiz.html) |
| 2 | [Object-Oriented Programming](interactive/02-oop.html) | [Quiz](interactive/02-oop-quiz.html) |
| 3 | [Core Language and Modern C++](interactive/03-core-language.html) | [Quiz](interactive/03-core-language-quiz.html) |
| 4 | [The STL](interactive/04-stl.html) | [Quiz](interactive/04-stl-quiz.html) |
| 5 | [Templates](interactive/05-templates.html) | [Quiz](interactive/05-templates-quiz.html) |
| 6 | [Design Patterns](interactive/06-design-patterns.html) | [Quiz](interactive/06-design-patterns-quiz.html) |
| 7 | [Multithreading](interactive/07-multithreading.html) | [Quiz](interactive/07-multithreading-quiz.html) |
| 8 | [Strings, Regex and Time](interactive/08-strings-regex-time.html) | [Quiz](interactive/08-strings-regex-time-quiz.html) |
| 9 | [Type Traits and Compile-time C++](interactive/09-compile-time.html) | [Quiz](interactive/09-compile-time-quiz.html) |
| 10 | [Coding Rules and Safe C++](interactive/10-coding-rules.html) | [Quiz](interactive/10-coding-rules-quiz.html) |

## Where each topic is covered

| Topic | Company training | learncpp.com recap |
|---|---|---|
| Intro, variables, types, operators | [Module 1](docs/01-cpp-basics/README.md) | [Ch 0](<LearnCPP/Recaps/1) Intro + Basics/Chapter 0 - Introduction and Getting Started.md>), [Ch 1](<LearnCPP/Recaps/1) Intro + Basics/Chapter 1 - C++ Basics.md>), [Ch 4](<LearnCPP/Recaps/2) Fundamentals 1/Chapter 4 - Fundamental Data Types.md>), [Ch 6](<LearnCPP/Recaps/2) Fundamentals 1/Chapter 6 - Operators.md>) |
| Namespaces and scope | [Namespace and scope](docs/01-cpp-basics/05_namespace_and_scope.md) | [Ch 7](<LearnCPP/Recaps/2) Fundamentals 1/Chapter 7 - Scope, Duration, and Linkage.md>) |
| Functions | [Functions](docs/01-cpp-basics/06_functions.md) | [Ch 2](<LearnCPP/Recaps/1) Intro + Basics/Chapter 2 - C++ Basics Functions and Files.md>), [Ch 20](<LearnCPP/Recaps/7) Advanced 1/Chapter 20 - Functions.md>) |
| Flow control and error handling | [Flow control](docs/01-cpp-basics/07_flow_control_and_error_handling.md) | [Ch 8](<LearnCPP/Recaps/3) Fundamentals 2/Chapter 8 - Control Flow.md>), [Ch 9](<LearnCPP/Recaps/3) Fundamentals 2/Chapter 9 - Error Detection and Handling.md>) |
| Exceptions | [Exceptions](docs/01-cpp-basics/08_exceptions.md) | [Ch 27](<LearnCPP/Recaps/9) Advanced 2/Chapter 27 - Exceptions.md>) |
| Constants, typedef, type conversion | [Constants](docs/01-cpp-basics/10_constants_typedef_and_alias.md), [Type conversion](docs/01-cpp-basics/12_type_conversion.md) | [Ch 5](<LearnCPP/Recaps/2) Fundamentals 1/Chapter 5 - Constants and Strings.md>), [Ch 10](<LearnCPP/Recaps/3) Fundamentals 2/Chapter 10 - Type Conversion, Type Aliases, and Type Deduction.md>) |
| References and pointers | [References and pointers](docs/01-cpp-basics/11_references_and_pointers.md) | [Ch 12](<LearnCPP/Recaps/4) Fundamentals 3/Chapter 12 - Compound Types References and Pointers.md>) |
| Memory allocation | [Memory allocation](docs/01-cpp-basics/13_memory_allocation.md) | [Ch 19](<LearnCPP/Recaps/7) Advanced 1/Chapter 19 - Dynamic Allocation.md>) |
| Classes, OOP | [Module 2](docs/02-cpp-oop/README.md) | [Ch 14](<LearnCPP/Recaps/5) Classes/Chapter 14 - Introduction to Classes.md>), [Ch 15](<LearnCPP/Recaps/5) Classes/Chapter 15 - More on Classes.md>) |
| Operator overloading | [Operators overloading](docs/02-cpp-oop/12_operators_overloading.md) | [Ch 21](<LearnCPP/Recaps/7) Advanced 1/Chapter 21 - Operator Overloading.md>) |
| Inheritance and polymorphism | [Inheritance](docs/02-cpp-oop/08_inheritance.md), [Polymorphism](docs/02-cpp-oop/09_polymorphism.md) | [Ch 24](<LearnCPP/Recaps/8) Classes 2/Chapter 24 - Inheritance.md>), [Ch 25](<LearnCPP/Recaps/8) Classes 2/Chapter 25 - Virtual Functions.md>) |
| Object relationships | [Objects relationships](docs/02-cpp-oop/13_objects_relationships.md) | [Ch 23](<LearnCPP/Recaps/7) Advanced 1/Chapter 23 - Object Relationships.md>) |
| Containers, iterators, algorithms | [Module 3](docs/03-cpp-standard-library/README.md) | [Ch 16](<LearnCPP/Recaps/6) Arrays/Chapter 16 - Dynamic Arrays std-vector.md>), [Ch 17](<LearnCPP/Recaps/6) Arrays/Chapter 17 - Fixed-size Arrays std-array and C-style Arrays.md>), [Ch 18](<LearnCPP/Recaps/7) Advanced 1/Chapter 18 - Iterators and Algorithms.md>) |
| Smart pointers and move semantics | [Smart pointers](docs/03-cpp-standard-library/05-smart-pointers) | [Ch 22](<LearnCPP/Recaps/7) Advanced 1/Chapter 22 - Move Semantics and Smart Pointers.md>) |
| File and stream I/O | [Files management](docs/03-cpp-standard-library/13_files_management.md) | [Ch 28](<LearnCPP/Recaps/9) Advanced 2/Chapter 28 - Input and Output (IO).md>) |
| Templates | [Module 4](docs/04-templates-and-design-patterns/README.md) | [Ch 11](<LearnCPP/Recaps/4) Fundamentals 3/Chapter 11 - Function Overloading and Function Templates.md>), [Ch 26](<LearnCPP/Recaps/9) Advanced 2/Chapter 26 - Templates and Classes.md>) |
| Multithreading, regex, date and time, type traits, metaprogramming, design patterns, coding rules | In Modules 3 and 4 | Not covered by learncpp.com |

---

## [Module 1: C++ Basics](docs/01-cpp-basics/README.md)

| Topic | Examples |
|---|---|
| [Introduction to C++](docs/01-cpp-basics/01_introduction_to_cpp.md) | [Examples](examples/01-cpp-basics/01-introduction-to-cpp/) |
| [Variables and types](docs/01-cpp-basics/02_variables_and_types.md) | |
| [Variables initialization](docs/01-cpp-basics/03_variables_initialization.md) | |
| [Operations on variables](docs/01-cpp-basics/04_operations_on_variables.md) | |
| [Namespace and scope](docs/01-cpp-basics/05_namespace_and_scope.md) | [Examples](examples/01-cpp-basics/05-namespace-and-scope/) |
| [Functions](docs/01-cpp-basics/06_functions.md) | [Examples](examples/01-cpp-basics/06-functions/) |
| [Flow control and error handling](docs/01-cpp-basics/07_flow_control_and_error_handling.md) | [Examples](examples/01-cpp-basics/07-flow-control-and-error-handling/) |
| [Exceptions](docs/01-cpp-basics/08_exceptions.md) | [Examples](examples/01-cpp-basics/08-exceptions/) |
| [Operators and operations on variables](docs/01-cpp-basics/09_operators_and_operations_on_variables.md) | [Examples](examples/01-cpp-basics/09-operators-and-operations-on-variables/) |
| [Constants, typedef and alias](docs/01-cpp-basics/10_constants_typedef_and_alias.md) | [Examples](examples/01-cpp-basics/10-constants-typedef-and-alias/) |
| [References and pointers](docs/01-cpp-basics/11_references_and_pointers.md) | [Examples](examples/01-cpp-basics/11-references-and-pointers/) |
| [Type conversion](docs/01-cpp-basics/12_type_conversion.md) | [Examples](examples/01-cpp-basics/12-type-conversion/) |
| [Memory allocation](docs/01-cpp-basics/13_memory_allocation.md) | [Examples](examples/01-cpp-basics/13-memory-allocation/) |
| [Quiz](docs/01-cpp-basics/14_quiz.md) | |
| [Conversion notes](docs/01-cpp-basics/conversion-notes.md) | |

## [Module 2: C++ Object Oriented Programming](docs/02-cpp-oop/README.md)

| Topic | Examples |
|---|---|
| [Introduction to OOP](docs/02-cpp-oop/01_introduction_to_oop.md) | |
| [Classes and structures](docs/02-cpp-oop/02_classes_and_structures.md) | |
| [Access specifiers](docs/02-cpp-oop/03_access_specifiers.md) | |
| [Special methods](docs/02-cpp-oop/04_special_methods.md) (constructors, destructors, copy/move) | [Examples](examples/02-cpp-oop/04-special-methods/) |
| [Exercice](docs/02-cpp-oop/05_exercice.md) | |
| [Static and non-static member functions](docs/02-cpp-oop/06_static_and_non_static_member_functions.md) | [Examples](examples/02-cpp-oop/06-static-and-non-static-member-functions/) |
| [Friend functions and classes](docs/02-cpp-oop/07_friend_functions_and_classes.md) | [Examples](examples/02-cpp-oop/07-friend-functions-and-classes/) |
| [Inheritance](docs/02-cpp-oop/08_inheritance.md) (incl. diamond problem) | [Examples](examples/02-cpp-oop/08-inheritance/) |
| [Polymorphism](docs/02-cpp-oop/09_polymorphism.md) | [Examples](examples/02-cpp-oop/09-polymorphism/) |
| [Overloading and overriding](docs/02-cpp-oop/10_overloading_and_overriding.md) | [Examples](examples/02-cpp-oop/10-overloading-and-overriding/) |
| [Encapsulation and abstraction](docs/02-cpp-oop/11_encapsulation_and_abstraction.md) | |
| [Operators overloading](docs/02-cpp-oop/12_operators_overloading.md) | [Examples](examples/02-cpp-oop/12-operators-overloading/) |
| [Objects relationships](docs/02-cpp-oop/13_objects_relationships.md) | |
| [Quiz](docs/02-cpp-oop/14_quiz.md) | |
| [Conversion notes](docs/02-cpp-oop/conversion-notes.md) | |

## [Module 3: C++ Standard Library](docs/03-cpp-standard-library/README.md)

| Topic | Examples |
|---|---|
| [Containers overview](docs/03-cpp-standard-library/01_containers_overview.md) | |
| **Sequence Containers** ([overview](docs/03-cpp-standard-library/02-sequence-containers/README.md)) | |
| &nbsp;&nbsp;[std::array](docs/03-cpp-standard-library/02-sequence-containers/01_array.md) | [Examples](examples/03-cpp-standard-library/02-sequence-containers/29_array.cpp) |
| &nbsp;&nbsp;[std::vector](docs/03-cpp-standard-library/02-sequence-containers/02_vector.md) | [Examples](examples/03-cpp-standard-library/02-sequence-containers/30_vector.cpp) |
| &nbsp;&nbsp;[std::deque](docs/03-cpp-standard-library/02-sequence-containers/03_deque.md) | [Examples](examples/03-cpp-standard-library/02-sequence-containers/31_deque.cpp) |
| &nbsp;&nbsp;[std::list](docs/03-cpp-standard-library/02-sequence-containers/04_list.md) | [Examples](examples/03-cpp-standard-library/02-sequence-containers/32_list.cpp) |
| &nbsp;&nbsp;[std::forward_list](docs/03-cpp-standard-library/02-sequence-containers/05_forward_list.md) | [Examples](examples/03-cpp-standard-library/02-sequence-containers/33_forward_list.cpp) |
| &nbsp;&nbsp;[std::stack](docs/03-cpp-standard-library/02-sequence-containers/06_stack.md) | [Examples](examples/03-cpp-standard-library/02-sequence-containers/34_stack.cpp) |
| &nbsp;&nbsp;[std::queue](docs/03-cpp-standard-library/02-sequence-containers/07_queue.md) | [Examples](examples/03-cpp-standard-library/02-sequence-containers/35_queue.cpp) |
| &nbsp;&nbsp;[std::priority_queue](docs/03-cpp-standard-library/02-sequence-containers/08_priority_queue.md) | [Examples](examples/03-cpp-standard-library/02-sequence-containers/36_priority_queue.cpp) |
| **Associative Containers** ([overview](docs/03-cpp-standard-library/03-associative-containers/README.md)) | |
| &nbsp;&nbsp;[std::set](docs/03-cpp-standard-library/03-associative-containers/01_set.md) | [Examples](examples/03-cpp-standard-library/03-associative-containers/37_set.cpp) |
| &nbsp;&nbsp;[std::map](docs/03-cpp-standard-library/03-associative-containers/02_map.md) | [Examples](examples/03-cpp-standard-library/03-associative-containers/38_map.cpp) |
| &nbsp;&nbsp;[std::multiset](docs/03-cpp-standard-library/03-associative-containers/03_multiset.md) | [Examples](examples/03-cpp-standard-library/03-associative-containers/39_multiset.cpp) |
| &nbsp;&nbsp;[std::multimap](docs/03-cpp-standard-library/03-associative-containers/04_multimap.md) | [Examples](examples/03-cpp-standard-library/03-associative-containers/40_multimap.cpp) |
| &nbsp;&nbsp;[std::unordered_set](docs/03-cpp-standard-library/03-associative-containers/05_unordered_set.md) | [Examples](examples/03-cpp-standard-library/03-associative-containers/41_unordered_set.cpp) |
| &nbsp;&nbsp;[std::unordered_map](docs/03-cpp-standard-library/03-associative-containers/06_unordered_map.md) | [Examples](examples/03-cpp-standard-library/03-associative-containers/42_unordered_map.cpp) |
| &nbsp;&nbsp;[std::unordered_multiset](docs/03-cpp-standard-library/03-associative-containers/07_unordered_multiset.md) | [Examples](examples/03-cpp-standard-library/03-associative-containers/43_unordered_multiset.cpp) |
| &nbsp;&nbsp;[std::unordered_multimap](docs/03-cpp-standard-library/03-associative-containers/08_unordered_multimap.md) | [Examples](examples/03-cpp-standard-library/03-associative-containers/44_unordered_multimap.cpp) |
| [Iterators](docs/03-cpp-standard-library/04_iterators.md) | [Examples](examples/03-cpp-standard-library/04-iterators/45_iterators.cpp) |
| **Smart Pointers** ([overview](docs/03-cpp-standard-library/05-smart-pointers/README.md)) | |
| &nbsp;&nbsp;[std::unique_ptr\<T\>](docs/03-cpp-standard-library/05-smart-pointers/01_unique_ptr.md) | [Examples](examples/03-cpp-standard-library/05-smart-pointers/46_unique_ptr.cpp) |
| &nbsp;&nbsp;[std::shared_ptr\<T\>](docs/03-cpp-standard-library/05-smart-pointers/02_shared_ptr.md) | [Examples](examples/03-cpp-standard-library/05-smart-pointers/47_shared_ptr.cpp) |
| &nbsp;&nbsp;[std::weak_ptr\<T\>](docs/03-cpp-standard-library/05-smart-pointers/03_weak_ptr.md) | [Examples](examples/03-cpp-standard-library/05-smart-pointers/48_weak_ptr.cpp) |
| [Algorithm library overview](docs/03-cpp-standard-library/06_algorithm_library_overview.md) | |
| [Algorithm library: non-modifying](docs/03-cpp-standard-library/07_algorithm_library_non_modifying.md) | [Examples](examples/03-cpp-standard-library/07-algorithm-library-non-modifying/49_non_modifying_algorithm.cpp) |
| [Algorithm library: modifying](docs/03-cpp-standard-library/08_algorithm_library_modifying.md) | [Examples](examples/03-cpp-standard-library/08-algorithm-library-modifying/50_modifying.cpp) |
| [String](docs/03-cpp-standard-library/09_string.md) | [Examples](examples/03-cpp-standard-library/09-string/51_strings.cpp) |
| [Date and time management](docs/03-cpp-standard-library/10_date_and_time_management.md) | [Examples](examples/03-cpp-standard-library/10-date-and-time-management/52_time_management.cpp) |
| **Multi-threading and synchronization** ([overview](docs/03-cpp-standard-library/11-multithreading-and-synchronization/README.md)) | |
| &nbsp;&nbsp;[Create and manage threads](docs/03-cpp-standard-library/11-multithreading-and-synchronization/01_create_and_manage_threads.md) | [Examples](examples/03-cpp-standard-library/11-multithreading-and-synchronization/53_multithreading.cpp) |
| &nbsp;&nbsp;[Atomic variables](docs/03-cpp-standard-library/11-multithreading-and-synchronization/02_atomic_variables.md) | [Examples](examples/03-cpp-standard-library/11-multithreading-and-synchronization/54_atomic.cpp) |
| &nbsp;&nbsp;[Mutual exclusion](docs/03-cpp-standard-library/11-multithreading-and-synchronization/03_mutual_exclusion.md) | [Examples](examples/03-cpp-standard-library/11-multithreading-and-synchronization/55_mutexes.cpp) |
| &nbsp;&nbsp;[Condition variables](docs/03-cpp-standard-library/11-multithreading-and-synchronization/04_condition_variables.md) | [Examples](examples/03-cpp-standard-library/11-multithreading-and-synchronization/56_condition_variable.cpp) |
| &nbsp;&nbsp;[Futures and promises](docs/03-cpp-standard-library/11-multithreading-and-synchronization/05_futures_and_promises.md) | [Examples](examples/03-cpp-standard-library/11-multithreading-and-synchronization/57_promise_future.cpp) |
| [Back to Exceptions](docs/03-cpp-standard-library/12_back_to_exceptions.md) | |
| [Files Management](docs/03-cpp-standard-library/13_files_management.md) | [Examples](examples/03-cpp-standard-library/13-files-management/58_file_management.cpp) |
| [Regular Expressions](docs/03-cpp-standard-library/14_regular_expressions.md) | [Examples](examples/03-cpp-standard-library/14-regular-expressions/59_regex.cpp) |
| [Conversion notes](docs/03-cpp-standard-library/conversion-notes.md) | |

## [Module 4: Templates & Design Patterns](docs/04-templates-and-design-patterns/README.md)

| Topic | Examples |
|---|---|
| **Templates** ([overview](docs/04-templates-and-design-patterns/01-templates/README.md)) | |
| &nbsp;&nbsp;[Function template](docs/04-templates-and-design-patterns/01-templates/01_function_template.md) | [Examples](examples/04-templates-and-design-patterns/01-templates/60_templates_functions.cpp) |
| &nbsp;&nbsp;[Class templates](docs/04-templates-and-design-patterns/01-templates/02_class_templates.md) | [Examples](examples/04-templates-and-design-patterns/01-templates/61_templates_classes.cpp) |
| [Type traits](docs/04-templates-and-design-patterns/02_type_traits.md) | [Examples](examples/04-templates-and-design-patterns/02-type-traits/62_type_traits.cpp) |
| [Metaprogramming](docs/04-templates-and-design-patterns/03_metaprogramming.md) | [Examples](examples/04-templates-and-design-patterns/03-metaprogramming/63_metaprogramming.cpp) |
| [Variadic templates](docs/04-templates-and-design-patterns/04_variadic_templates.md) (incl. tuples) | [Examples](examples/04-templates-and-design-patterns/04-variadic-templates/) |
| [Perfect forwarding](docs/04-templates-and-design-patterns/05_perfect_forwarding.md) | [Examples](examples/04-templates-and-design-patterns/05-perfect-forwarding/67_perfect_forwarding.cpp) |
| **Design Patterns** ([overview](docs/04-templates-and-design-patterns/06-design-patterns/README.md)) | |
| &nbsp;&nbsp;[Singleton](docs/04-templates-and-design-patterns/06-design-patterns/01_singleton.md) | [Examples](examples/04-templates-and-design-patterns/06-design-patterns/68_singleton.cpp) |
| &nbsp;&nbsp;[State](docs/04-templates-and-design-patterns/06-design-patterns/02_state.md) | [Examples](examples/04-templates-and-design-patterns/06-design-patterns/69_state_dp.cpp) |
| &nbsp;&nbsp;[Strategy](docs/04-templates-and-design-patterns/06-design-patterns/03_strategy.md) | [Examples](examples/04-templates-and-design-patterns/06-design-patterns/70_strategy_dp.cpp) |
| &nbsp;&nbsp;Observer *(bonus, no dedicated slide)* | [Examples](examples/04-templates-and-design-patterns/06-design-patterns/71_observer_dp.cpp) |
| [Introduction to Coding rules](docs/04-templates-and-design-patterns/07_coding_rules.md) (AUTOSAR C++14, Code Style) | |
| [Conversion notes](docs/04-templates-and-design-patterns/conversion-notes.md) | |

---

## Further reading

- [modern-cpp-tutorial](https://github.com/changkun/modern-cpp-tutorial): book-style tutorial on C++11/14/17/20 that explains why modern features exist.
- [modern-cpp-features](https://github.com/AnthonyCalandra/modern-cpp-features): cheat sheet with a short snippet per feature, C++11 through C++23.

---

*Each module's `README.md` also has its own local table of contents. This file is the top-level entry point across all four modules. Source PDFs remain at the repo root for reference.*
