# Training notes index

Embedded Team Academy · Doc ref TR0014_G

The 4 source PDFs of the training, converted into per-topic Markdown, with matching source code under [`examples/`](../examples/). Each module's `README.md` also has its own local table of contents. Back to the [main README](../README.md).

## Other files in this folder

- [Topic map](topic-map.md): where each topic appears in the training notes, the recaps and the lessons.
- [Study checklist](study-checklist.md): a step-by-step plan, also available with clickable boxes on the [site](https://ghaith-hamdi1.github.io/cpp-training/study-checklist.html).
- Reading guides: [C++ Concurrency in Action](concurrency-in-action-reading-guide.md) and [Programming: Principles and Practice Using C++](programming-principles-and-practice-reading-guide.md).

## [Module 1: C++ Basics](01-cpp-basics/README.md)

| Topic | Examples |
|---|---|
| [Introduction to C++](01-cpp-basics/01_introduction_to_cpp.md) | [Examples](../examples/01-cpp-basics/01-introduction-to-cpp/) |
| [Variables and types](01-cpp-basics/02_variables_and_types.md) | |
| [Variables initialization](01-cpp-basics/03_variables_initialization.md) | |
| [Operations on variables](01-cpp-basics/04_operations_on_variables.md) | |
| [Namespace and scope](01-cpp-basics/05_namespace_and_scope.md) | [Examples](../examples/01-cpp-basics/05-namespace-and-scope/) |
| [Functions](01-cpp-basics/06_functions.md) | [Examples](../examples/01-cpp-basics/06-functions/) |
| [Flow control and error handling](01-cpp-basics/07_flow_control_and_error_handling.md) | [Examples](../examples/01-cpp-basics/07-flow-control-and-error-handling/) |
| [Exceptions](01-cpp-basics/08_exceptions.md) | [Examples](../examples/01-cpp-basics/08-exceptions/) |
| [Operators and operations on variables](01-cpp-basics/09_operators_and_operations_on_variables.md) | [Examples](../examples/01-cpp-basics/09-operators-and-operations-on-variables/) |
| [Constants, typedef and alias](01-cpp-basics/10_constants_typedef_and_alias.md) | [Examples](../examples/01-cpp-basics/10-constants-typedef-and-alias/) |
| [References and pointers](01-cpp-basics/11_references_and_pointers.md) | [Examples](../examples/01-cpp-basics/11-references-and-pointers/) |
| [Type conversion](01-cpp-basics/12_type_conversion.md) | [Examples](../examples/01-cpp-basics/12-type-conversion/) |
| [Memory allocation](01-cpp-basics/13_memory_allocation.md) | [Examples](../examples/01-cpp-basics/13-memory-allocation/) |
| [Quiz](01-cpp-basics/14_quiz.md) | |
| [Conversion notes](01-cpp-basics/conversion-notes.md) | |

## [Module 2: C++ Object Oriented Programming](02-cpp-oop/README.md)

| Topic | Examples |
|---|---|
| [Introduction to OOP](02-cpp-oop/01_introduction_to_oop.md) | |
| [Classes and structures](02-cpp-oop/02_classes_and_structures.md) | |
| [Access specifiers](02-cpp-oop/03_access_specifiers.md) | |
| [Special methods](02-cpp-oop/04_special_methods.md) (constructors, destructors, copy/move) | [Examples](../examples/02-cpp-oop/04-special-methods/) |
| [Exercice](02-cpp-oop/05_exercice.md) | |
| [Static and non-static member functions](02-cpp-oop/06_static_and_non_static_member_functions.md) | [Examples](../examples/02-cpp-oop/06-static-and-non-static-member-functions/) |
| [Friend functions and classes](02-cpp-oop/07_friend_functions_and_classes.md) | [Examples](../examples/02-cpp-oop/07-friend-functions-and-classes/) |
| [Inheritance](02-cpp-oop/08_inheritance.md) (incl. diamond problem) | [Examples](../examples/02-cpp-oop/08-inheritance/) |
| [Polymorphism](02-cpp-oop/09_polymorphism.md) | [Examples](../examples/02-cpp-oop/09-polymorphism/) |
| [Overloading and overriding](02-cpp-oop/10_overloading_and_overriding.md) | [Examples](../examples/02-cpp-oop/10-overloading-and-overriding/) |
| [Encapsulation and abstraction](02-cpp-oop/11_encapsulation_and_abstraction.md) | |
| [Operators overloading](02-cpp-oop/12_operators_overloading.md) | [Examples](../examples/02-cpp-oop/12-operators-overloading/) |
| [Objects relationships](02-cpp-oop/13_objects_relationships.md) | |
| [Quiz](02-cpp-oop/14_quiz.md) | |
| [Conversion notes](02-cpp-oop/conversion-notes.md) | |

## [Module 3: C++ Standard Library](03-cpp-standard-library/README.md)

| Topic | Examples |
|---|---|
| [Containers overview](03-cpp-standard-library/01_containers_overview.md) | |
| **Sequence Containers** ([overview](03-cpp-standard-library/02-sequence-containers/README.md)) | |
| &nbsp;&nbsp;[std::array](03-cpp-standard-library/02-sequence-containers/01_array.md) | [Examples](../examples/03-cpp-standard-library/02-sequence-containers/29_array.cpp) |
| &nbsp;&nbsp;[std::vector](03-cpp-standard-library/02-sequence-containers/02_vector.md) | [Examples](../examples/03-cpp-standard-library/02-sequence-containers/30_vector.cpp) |
| &nbsp;&nbsp;[std::deque](03-cpp-standard-library/02-sequence-containers/03_deque.md) | [Examples](../examples/03-cpp-standard-library/02-sequence-containers/31_deque.cpp) |
| &nbsp;&nbsp;[std::list](03-cpp-standard-library/02-sequence-containers/04_list.md) | [Examples](../examples/03-cpp-standard-library/02-sequence-containers/32_list.cpp) |
| &nbsp;&nbsp;[std::forward_list](03-cpp-standard-library/02-sequence-containers/05_forward_list.md) | [Examples](../examples/03-cpp-standard-library/02-sequence-containers/33_forward_list.cpp) |
| &nbsp;&nbsp;[std::stack](03-cpp-standard-library/02-sequence-containers/06_stack.md) | [Examples](../examples/03-cpp-standard-library/02-sequence-containers/34_stack.cpp) |
| &nbsp;&nbsp;[std::queue](03-cpp-standard-library/02-sequence-containers/07_queue.md) | [Examples](../examples/03-cpp-standard-library/02-sequence-containers/35_queue.cpp) |
| &nbsp;&nbsp;[std::priority_queue](03-cpp-standard-library/02-sequence-containers/08_priority_queue.md) | [Examples](../examples/03-cpp-standard-library/02-sequence-containers/36_priority_queue.cpp) |
| **Associative Containers** ([overview](03-cpp-standard-library/03-associative-containers/README.md)) | |
| &nbsp;&nbsp;[std::set](03-cpp-standard-library/03-associative-containers/01_set.md) | [Examples](../examples/03-cpp-standard-library/03-associative-containers/37_set.cpp) |
| &nbsp;&nbsp;[std::map](03-cpp-standard-library/03-associative-containers/02_map.md) | [Examples](../examples/03-cpp-standard-library/03-associative-containers/38_map.cpp) |
| &nbsp;&nbsp;[std::multiset](03-cpp-standard-library/03-associative-containers/03_multiset.md) | [Examples](../examples/03-cpp-standard-library/03-associative-containers/39_multiset.cpp) |
| &nbsp;&nbsp;[std::multimap](03-cpp-standard-library/03-associative-containers/04_multimap.md) | [Examples](../examples/03-cpp-standard-library/03-associative-containers/40_multimap.cpp) |
| &nbsp;&nbsp;[std::unordered_set](03-cpp-standard-library/03-associative-containers/05_unordered_set.md) | [Examples](../examples/03-cpp-standard-library/03-associative-containers/41_unordered_set.cpp) |
| &nbsp;&nbsp;[std::unordered_map](03-cpp-standard-library/03-associative-containers/06_unordered_map.md) | [Examples](../examples/03-cpp-standard-library/03-associative-containers/42_unordered_map.cpp) |
| &nbsp;&nbsp;[std::unordered_multiset](03-cpp-standard-library/03-associative-containers/07_unordered_multiset.md) | [Examples](../examples/03-cpp-standard-library/03-associative-containers/43_unordered_multiset.cpp) |
| &nbsp;&nbsp;[std::unordered_multimap](03-cpp-standard-library/03-associative-containers/08_unordered_multimap.md) | [Examples](../examples/03-cpp-standard-library/03-associative-containers/44_unordered_multimap.cpp) |
| [Iterators](03-cpp-standard-library/04_iterators.md) | [Examples](../examples/03-cpp-standard-library/04-iterators/45_iterators.cpp) |
| **Smart Pointers** ([overview](03-cpp-standard-library/05-smart-pointers/README.md)) | |
| &nbsp;&nbsp;[std::unique_ptr\<T\>](03-cpp-standard-library/05-smart-pointers/01_unique_ptr.md) | [Examples](../examples/03-cpp-standard-library/05-smart-pointers/46_unique_ptr.cpp) |
| &nbsp;&nbsp;[std::shared_ptr\<T\>](03-cpp-standard-library/05-smart-pointers/02_shared_ptr.md) | [Examples](../examples/03-cpp-standard-library/05-smart-pointers/47_shared_ptr.cpp) |
| &nbsp;&nbsp;[std::weak_ptr\<T\>](03-cpp-standard-library/05-smart-pointers/03_weak_ptr.md) | [Examples](../examples/03-cpp-standard-library/05-smart-pointers/48_weak_ptr.cpp) |
| [Algorithm library overview](03-cpp-standard-library/06_algorithm_library_overview.md) | |
| [Algorithm library: non-modifying](03-cpp-standard-library/07_algorithm_library_non_modifying.md) | [Examples](../examples/03-cpp-standard-library/07-algorithm-library-non-modifying/49_non_modifying_algorithm.cpp) |
| [Algorithm library: modifying](03-cpp-standard-library/08_algorithm_library_modifying.md) | [Examples](../examples/03-cpp-standard-library/08-algorithm-library-modifying/50_modifying.cpp) |
| [String](03-cpp-standard-library/09_string.md) | [Examples](../examples/03-cpp-standard-library/09-string/51_strings.cpp) |
| [Date and time management](03-cpp-standard-library/10_date_and_time_management.md) | [Examples](../examples/03-cpp-standard-library/10-date-and-time-management/52_time_management.cpp) |
| **Multi-threading and synchronization** ([overview](03-cpp-standard-library/11-multithreading-and-synchronization/README.md)) | |
| &nbsp;&nbsp;[Create and manage threads](03-cpp-standard-library/11-multithreading-and-synchronization/01_create_and_manage_threads.md) | [Examples](../examples/03-cpp-standard-library/11-multithreading-and-synchronization/53_multithreading.cpp) |
| &nbsp;&nbsp;[Atomic variables](03-cpp-standard-library/11-multithreading-and-synchronization/02_atomic_variables.md) | [Examples](../examples/03-cpp-standard-library/11-multithreading-and-synchronization/54_atomic.cpp) |
| &nbsp;&nbsp;[Mutual exclusion](03-cpp-standard-library/11-multithreading-and-synchronization/03_mutual_exclusion.md) | [Examples](../examples/03-cpp-standard-library/11-multithreading-and-synchronization/55_mutexes.cpp) |
| &nbsp;&nbsp;[Condition variables](03-cpp-standard-library/11-multithreading-and-synchronization/04_condition_variables.md) | [Examples](../examples/03-cpp-standard-library/11-multithreading-and-synchronization/56_condition_variable.cpp) |
| &nbsp;&nbsp;[Futures and promises](03-cpp-standard-library/11-multithreading-and-synchronization/05_futures_and_promises.md) | [Examples](../examples/03-cpp-standard-library/11-multithreading-and-synchronization/57_promise_future.cpp) |
| [Back to Exceptions](03-cpp-standard-library/12_back_to_exceptions.md) | |
| [Files Management](03-cpp-standard-library/13_files_management.md) | [Examples](../examples/03-cpp-standard-library/13-files-management/58_file_management.cpp) |
| [Regular Expressions](03-cpp-standard-library/14_regular_expressions.md) | [Examples](../examples/03-cpp-standard-library/14-regular-expressions/59_regex.cpp) |
| [Conversion notes](03-cpp-standard-library/conversion-notes.md) | |

## [Module 4: Templates & Design Patterns](04-templates-and-design-patterns/README.md)

| Topic | Examples |
|---|---|
| **Templates** ([overview](04-templates-and-design-patterns/01-templates/README.md)) | |
| &nbsp;&nbsp;[Function template](04-templates-and-design-patterns/01-templates/01_function_template.md) | [Examples](../examples/04-templates-and-design-patterns/01-templates/60_templates_functions.cpp) |
| &nbsp;&nbsp;[Class templates](04-templates-and-design-patterns/01-templates/02_class_templates.md) | [Examples](../examples/04-templates-and-design-patterns/01-templates/61_templates_classes.cpp) |
| [Type traits](04-templates-and-design-patterns/02_type_traits.md) | [Examples](../examples/04-templates-and-design-patterns/02-type-traits/62_type_traits.cpp) |
| [Metaprogramming](04-templates-and-design-patterns/03_metaprogramming.md) | [Examples](../examples/04-templates-and-design-patterns/03-metaprogramming/63_metaprogramming.cpp) |
| [Variadic templates](04-templates-and-design-patterns/04_variadic_templates.md) (incl. tuples) | [Examples](../examples/04-templates-and-design-patterns/04-variadic-templates/) |
| [Perfect forwarding](04-templates-and-design-patterns/05_perfect_forwarding.md) | [Examples](../examples/04-templates-and-design-patterns/05-perfect-forwarding/67_perfect_forwarding.cpp) |
| **Design Patterns** ([overview](04-templates-and-design-patterns/06-design-patterns/README.md)) | |
| &nbsp;&nbsp;[Singleton](04-templates-and-design-patterns/06-design-patterns/01_singleton.md) | [Examples](../examples/04-templates-and-design-patterns/06-design-patterns/68_singleton.cpp) |
| &nbsp;&nbsp;[State](04-templates-and-design-patterns/06-design-patterns/02_state.md) | [Examples](../examples/04-templates-and-design-patterns/06-design-patterns/69_state_dp.cpp) |
| &nbsp;&nbsp;[Strategy](04-templates-and-design-patterns/06-design-patterns/03_strategy.md) | [Examples](../examples/04-templates-and-design-patterns/06-design-patterns/70_strategy_dp.cpp) |
| &nbsp;&nbsp;Observer *(bonus, no dedicated slide)* | [Examples](../examples/04-templates-and-design-patterns/06-design-patterns/71_observer_dp.cpp) |
| [Introduction to Coding rules](04-templates-and-design-patterns/07_coding_rules.md) (AUTOSAR C++14, Code Style) | |
| [Conversion notes](04-templates-and-design-patterns/conversion-notes.md) | |
