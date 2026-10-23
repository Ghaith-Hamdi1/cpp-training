# Reading guide: *C++ Primer* (5th Edition)

A reading plan for `books/Cpp-Primer-5th-Edition-Lippman.pdf` (Stanley Lippman, Josée Lajoie and Barbara Moo, 2012, about 970 pages, C++11). It is the most complete textbook of the five books: it teaches the whole language and the library in the order a beginner should meet them, with exercises after almost every section. That makes it the **systematic base** for lessons 1 to 12; it is a good partner to the lessons because it explains every rule in full, and they show what happens in memory.

**Page numbers.** The tables give *PDF viewer* page numbers, the number your PDF reader shows. The book's own printed page numbers are 29 lower (printed page 50 is PDF page 79); the plan and notes use PDF pages only.

The sections and their summaries come from the book's table of contents and chapter openings. I did not read every page in full.

---

## What the book does and does not cover

| Covers well | Does not cover |
|---|---|
| Types, expressions, statements, functions, classes | Threads, mutexes, atomics (use *C++ Concurrency in Action* and lessons 16 to 18) |
| The whole standard library of C++11: strings, containers, algorithms, IO, smart pointers | C++14, C++17 and C++20: `optional`, `variant`, `string_view`, structured bindings, `if constexpr`, concepts, ranges, `std::format` (lessons 2, 3, 9, 11, 13) |
| Copy control, move semantics, operator overloading | Deep move semantics and forwarding (*Effective Modern C++* and *C++ Move Semantics*) |
| Inheritance and virtual functions, templates, exceptions | Design patterns, performance and memory layout (lessons 14, 15, 19 and 20) |

## Tier 1: read these first (about 467 pages)

The sections that teach what the lessons rely on: types and `const`, strings and vectors, argument passing, classes, copy control, the library containers, smart pointers, inheritance, templates and exceptions.

| Section | PDF pages | What it teaches | Matching lesson section |
|---|---|---|---|
| **2.2** Variables | 70 to 78 | Initialization versus assignment, list initialization and narrowing, declaration versus definition, scope. | 2. Initialization and brace traps |
| **2.3** Compound types | 79 to 87 | References, pointers, null pointers, `void*`, pointers to pointers and references to pointers. | 1. Pointers from scratch; References |
| **2.4** const qualifier | 88 to 95 | Top-level versus low-level `const`, `const` references, `constexpr`. | 1. const and pointers |
| **3.2** Library string type | 113 to 124 | Initializing and reading strings, `getline`, range-for, character functions. | 1. Arrays, C-strings and std::string |
| **3.3** Library vector type | 125 to 134 | `vector` as the default container, `push_back`, subscript does not add elements. | 11. vector: the workhorse |
| **3.4** Introducing iterators | 135 to 141 | `begin`/`end`, dereferencing, iterator arithmetic, invalidation. | 11. Iterators |
| **3.5** Arrays | 142 to 153 | Built-in arrays, decay to pointers, pointer arithmetic, C-style strings; why to prefer `vector` and `string`. | 1. Arrays, C-strings and std::string |
| **4.1** Fundamentals | 163 to 167 | Lvalues and rvalues, precedence, evaluation order and what is unspecified. | 7. Lvalues, rvalues and value categories |
| **4.11** Type conversions | 188 to 194 | Every implicit conversion, the usual arithmetic conversions, and the named casts. | 2. Implicit conversions and enum class; Casts and type conversion |
| **5.6** try blocks and exception handling | 222 to 229 | `throw`, `try`/`catch`, the standard exception classes, stack unwinding. | 6. Exceptions and stack unwinding |
| **6.2** Argument passing | 237 to 250 | By value, by reference, by `const` reference, array parameters, `initializer_list`. | 1. Functions and passing arguments |
| **6.3** Return types and the return statement | 251 to 258 | Returning references (never to a local), returning lists, `decltype` and trailing return types. | 1. Functions and passing arguments |
| **6.4** Overloaded functions | 259 to 264 | What counts as a different signature, `const` and overloading, scope and overloading. | 1. Functions and passing arguments |
| **6.7** Pointers to functions | 276 to 281 | Declaring, passing and returning function pointers. | 9. Before lambdas: function pointers and functors |
| **7.1** Defining abstract data types | 283 to 296 | Member functions, `this`, `const` member functions, constructors, `= default`, non-member helpers. | 4. Classes and encapsulation; Member functions: this, const, static, friend |
| **7.2** Access control and encapsulation | 297 to 299 | `class` versus `struct`, `private`, `friend`. | 4. Classes and encapsulation |
| **7.5** Constructors revisited | 317 to 328 | The initializer list (and why order matters), delegating constructors, implicit conversions, `explicit`, aggregate classes. | 4. Constructors and destructors; explicit, conversion operators and copy-and-swap |
| **9.3** Sequential container operations | 370 to 383 | Insert, erase, `emplace`, access, resizing and which operations invalidate iterators. | 11. vector: the workhorse; Common pitfalls |
| **9.4** How a vector grows | 384 to 388 | `size` versus `capacity`, `reserve`, `shrink_to_fit`, amortized growth. | 11. vector: the workhorse |
| **10.1 to 10.2** Overview and a first look | 405 to 413 | Read, write and reordering algorithms, `sort`, `unique`, the erase-remove idiom. | 11. Algorithms |
| **10.3** Customizing operations | 414 to 429 | Predicates, lambda expressions, captures, `bind`. | 9. What a lambda is; Captures: by value and by reference |
| **10.5** Structure of generic algorithms | 439 to 443 | The five iterator categories and which algorithms need which. | 11. Iterators |
| **11.3** Operations on associative containers | 457 to 471 | Insert, erase, access, `operator[]` inserting a default value, the strict weak ordering rule. | 11. Associative and unordered containers; Custom keys: comparators and hashes |
| **11.4** The unordered containers | 472 to 477 | Hash tables, buckets and how to give your own type a hash. | 11. Custom keys: comparators and hashes |
| **12.1** Dynamic memory and smart pointers | 479 to 504 | `shared_ptr`, `new` and `delete` and why raw `new` is dangerous, `unique_ptr`, `weak_ptr`, custom deleters. | 8. Who owns it? The three smart pointers; unique_ptr in detail; shared_ptr and the control block; Reference cycles and weak_ptr |
| **12.2** Dynamic arrays | 505 to 512 | `new[]`/`delete[]`, `unique_ptr<T[]>`, the `allocator` class. | 1. Dynamic memory: new and delete |
| **13.1** Copy, assign and destroy | 525 to 538 | The copy constructor, copy assignment, destructor, `= default` and `= delete`, the Rule of Three. | 4. Copying and the Rule of 3, 5 and 0 |
| **13.2** Copy control and resource management | 539 to 544 | Value-like versus pointer-like classes. | 4. Copying and the Rule of 3, 5 and 0 |
| **13.5** Classes that manage dynamic memory | 553 to 559 | A `StrVec` built by hand with `allocator`: the model for `vector`. | 4. Copying and the Rule of 3, 5 and 0 |
| **13.6** Moving objects | 560 to 579 | Rvalue references, `std::move`, move constructor and assignment, `noexcept`, reference qualifiers. | 7. Lvalues, rvalues and value categories; Copy versus move; Writing move operations |
| **14.8** The function-call operator | 600 to 607 | Function objects, lambdas as function objects, library functors, `std::function`. | 9. Function pointer, functor, lambda, std::function |
| **14.9** Overloading, conversions and operators | 608 to 619 | Conversion operators, `explicit` conversions, ambiguity. | 4. explicit, conversion operators and copy-and-swap |
| **15.1 to 15.2** OOP overview, defining base and derived classes | 621 to 631 | Inheritance, `virtual`, derived-to-base conversion, how a derived object is laid out. | 4. Inheritance |
| **15.3** Virtual functions | 632 to 636 | Dynamic binding, `override` and `final`, calling a virtual function through a reference or pointer. | 4. Polymorphism and virtual functions |
| **15.4** Abstract base classes | 637 to 639 | Pure virtual functions and interfaces. | 4. Abstract classes and interfaces |
| **15.6** Class scope under inheritance | 646 to 650 | Name lookup and hiding. | 4. Polymorphism and virtual functions |
| **15.7** Constructors and copy control | 651 to 658 | Virtual destructors, derived-class constructors, synthesized copy control and deleted copy operations. | 4. Constructors and destructors; Copying and the Rule of 3, 5 and 0 |
| **15.8** Containers and inheritance | 659 to 662 | Containers of pointers instead of objects, slicing, the virtual-copy (`clone`) idiom. | 4. Polymorphism and virtual functions |
| **16.1** Defining a template | 681 to 706 | Function and class templates, template parameters, member templates, instantiation, why templates live in headers. | 12. Why templates, and function templates; Class templates |
| **16.2** Template argument deduction | 707 to 722 | Conversions allowed during deduction, explicit arguments, trailing returns, `std::move` and forwarding references, reference collapsing. | 12. Template argument deduction; Forwarding references and perfect forwarding |
| **16.4** Variadic templates | 728 to 734 | Parameter packs, `sizeof...`, pack expansion and recursion. | 12. Variadic templates and fold expressions |
| **17.3** Regular expressions | 757 to 773 | `regex`, `regex_search`, `regex_match`, `sregex_iterator`, match results. | 10. Regular expressions |
| **17.4** Random numbers | 774 to 780 | Engines, distributions and why `rand()` is not good enough. | 11. Random numbers |
| **18.1** Exception handling | 801 to 813 | Stack unwinding, destructors and exceptions, `noexcept`, exception class hierarchies, RAII for exception safety. | 6. Exceptions and stack unwinding; Exception-safety guarantees and noexcept |
| **18.3** Multiple and virtual inheritance | 831 to 847 | Constructing multiple bases, name ambiguity, the diamond, `virtual` base classes. | 5. Multiple inheritance and object layout; The diamond problem and virtual inheritance |
| **19.2** Run-time type identification | 854 to 860 | `dynamic_cast`, `typeid`, `type_info`. | 5. RTTI: typeid and dynamic_cast |

## Tier 2: read next if you have time (about 285 pages)

| Section | PDF pages | What it teaches | Matching lesson section |
|---|---|---|---|
| **2.1** Primitive built-in types | 61 to 69 | Integer sizes, signed versus unsigned and the traps of mixing them, floating point, literals. | 2. Implicit conversions and enum class |
| **2.5** Dealing with types | 96 to 100 | Type aliases, `auto` and `decltype`. | 2. auto, decltype and modern syntax |
| **2.6** Defining our own data structures | 101 to 109 | Structs, in-class initializers, headers and include guards. | 1. How a C++ program is built |
| **3.1** Namespace using declarations | 111 to 112 | Why headers should not contain `using` declarations. | 1. How a C++ program is built |
| **3.6** Multidimensional arrays | 154 to 161 | Arrays of arrays and pointers into them. | 1. Arrays, C-strings and std::string |
| **4.4 to 4.5** Assignment, increment and decrement | 173 to 178 | Assignment returns an lvalue; prefer prefix `++`. | 1. Operators and control flow |
| **4.8** The bitwise operators | 181 to 184 | Shifts, masks and `bitset`. | 19. Integers and bit manipulation |
| **5.3 to 5.4** Conditional and iterative statements | 203 to 218 | `switch` and fall-through, the dangling `else`, range-for, `do`-`while`. | 1. Operators and control flow |
| **6.1** Function basics | 231 to 236 | Parameters, local and `static` objects, separate compilation. | 1. Functions and passing arguments |
| **6.5** Features for specialized uses | 265 to 270 | Default arguments, `inline`, `constexpr` functions, `assert` and `NDEBUG`. | 2. const, constexpr and static |
| **6.6** Function matching | 271 to 275 | How the compiler picks an overload and when it is ambiguous. | 1. Functions and passing arguments |
| **7.3** Additional class features | 300 to 310 | `mutable`, in-class initializers, returning `*this`, incomplete types. | 4. Member functions: this, const, static, friend |
| **7.4** Class scope | 311 to 316 | Name lookup inside member functions and definitions outside the class. | 4. Classes and encapsulation |
| **7.6** static class members | 329 to 334 | Shared members and where they are defined. | 4. Member functions: this, const, static, friend |
| **8.1 to 8.3** IO classes, file IO and string streams | 339 to 353 | Stream state and error flags, buffering and flushing, `ifstream`/`ofstream`, `istringstream`/`ostringstream`. | 10. String streams and files |
| **9.1 to 9.2** Overview and the container library | 355 to 369 | Which container to choose, the common members, `array` and `forward_list`, assignment and `swap`. | 11. Other sequence containers |
| **9.5** Additional string operations | 389 to 396 | `substr`, `find`, `replace`, numeric conversions. | 10. std::string and std::string_view |
| **9.6** Container adaptors | 397 to 402 | `stack`, `queue`, `priority_queue`. | 11. Other sequence containers |
| **10.4** Revisiting iterators | 430 to 438 | Insert, stream, reverse and move iterators. | 11. Iterators |
| **10.6** Container-specific algorithms | 444 to 447 | `list::sort` and `merge`. | 11. Other sequence containers |
| **11.1 to 11.2** Using an associative container, overview | 449 to 456 | `map`, `set`, their `multi` variants, key requirements. | 11. Associative and unordered containers |
| **12.3** Using the library: a text-query program | 513 to 521 | A complete program that combines `vector`, `map`, `set` and `shared_ptr` (optional). | Not in the lessons |
| **13.3** Swap | 545 to 547 | A custom `swap` and copy-and-swap assignment. | 4. explicit, conversion operators and copy-and-swap |
| **13.4** A copy-control example | 548 to 552 | Two classes that cooperate via a shared object (optional). | Not in the lessons |
| **14.1 to 14.7** Basic concepts through member access | 581 to 599 | Which operators to overload, `<<` and `>>`, `==` and `<`, assignment, `[]`, `++`, `->`. | 4. Operator overloading |
| **15.5** Access control and inheritance | 640 to 645 | `protected`, `public`/`private` inheritance, `using` declarations. | 4. Inheritance |
| **16.3** Overloading and templates | 723 to 727 | How templates take part in overload resolution. | 12. Template argument deduction |
| **16.5** Template specializations | 735 to 743 | Full and partial specialization. | 12. Specialization |
| **17.1** The tuple type | 747 to 751 | `tuple`, `get`, `tie` and returning several values. | 3. pair, tuple and structured bindings |
| **18.2** Namespaces | 814 to 830 | Definitions, aliases, `using` directives, argument-dependent lookup, overloading. | 1. How a C++ program is built |
| **19.1** Controlling memory allocation | 849 to 853 | Overloading `operator new`, placement `new`. | 20. Memory on the hot path |
| **19.3** Enumerations | 861 to 863 | Scoped `enum class` and the underlying type. | 2. Implicit conversions and enum class |
| **19.4** Pointer to class member | 864 to 871 | Pointers to data and function members, and how `std::function` and `std::invoke` handle them. | Not in the lessons |
| **19.5 to 19.6** Nested classes and unions | 872 to 880 | Nested classes, `union`, discriminated unions (the idea behind `variant`). | 3. variant and std::visit |
| **17.2** The bitset type | 752 to 756 | Fixed-size bit sets. | 19. Integers and bit manipulation |
| **19.7 to 19.8** Local classes and nonportable features | 881 to 893 | Bit-fields, `volatile`, `extern "C"`. | Not in the lessons |

## Skip on a first read

| Skip | Why |
|---|---|
| Chapter 1 | The first program, the bookstore program and flow of control; Lesson 1 covers the build process. |
| 4.2, 4.3, 4.6, 4.7, 4.9, 4.10, 4.12 | Operators you already know, the precedence table (look it up). |
| 5.1, 5.2, 5.5 | Simple statements, statement scope, `break`/`continue`/`goto`. |
| 17.5 | IO revisited (formatted and unformatted IO, random access); look up when needed. |
| Appendix A | A reference list of the library; use it as a lookup. |

## How to use this guide

1. Do the lesson and quiz for a topic first (for example, lesson 1 for pointers).
2. If a quiz question surprises you, read the matching Tier 1 section here for the longer explanation.
3. Do the exercises at the end of each section you read: the book has hundreds, so pick two or three per section.
4. For an ordered path through the whole book, session by session, follow the [reading plan](cpp-primer-reading-plan.md); to keep your own notes, copy the [session templates](notes/cpp-primer/README.md).

## Notes on the edition

- The book is written for C++11. Code such as `auto`, range-for, lambdas and `nullptr` is covered, but the C++14 to C++20 features in the lessons are not, so do not treat the book as the last word on modern style (see the other four books for that).
- The book's own exercises are numbered by section (Exercise 3.2.1 is the first exercise of section 3.2). Solutions are not in the book.
- Chapter 1 and the bookstore case study are an introduction; start at chapter 2.
