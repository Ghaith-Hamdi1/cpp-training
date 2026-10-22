# Reading guide: *C++ Move Semantics: The Complete Guide* (Nicolai Josuttis)

A short reading plan for `books/Cpp-Move-Semantics-The-Complete-Guide-Josuttis.pdf` (Nicolai Josuttis, first edition, version of 2022-04-19, about 263 PDF pages, covering C++11 through C++20). It is a whole book on one topic, so it goes much deeper than the move-semantics chapter in *Effective Modern C++*: the moved-from state, value categories, writing move operations, reference qualifiers and the standard library's move support. Use the [interactive lessons](https://ghaith-hamdi1.github.io/cpp-training/) first (Lesson 4 covers move semantics, and Lesson 2 the Rule of Three, Five and Zero), then read this book for depth. The [Effective Modern C++ guide](effective-modern-cpp-reading-guide.md) has the shorter, interview-shaped treatment.

**Page numbers.** The tables give *PDF viewer* page numbers, the number shown in your PDF reader. A range covers the whole section named.

The book has 15 chapters in three parts. The summaries below come from its table of contents and the summary box at the end of each chapter. I did not read every page in full.

| Part | Chapters | PDF pages |
|---|---|---|
| I. Basic features of move semantics | 1 to 8 | 21 to 156 |
| II. Move semantics in generic code | 9 to 12 | 159 to 210 |
| III. Move semantics in the C++ standard library | 13 to 15 | 213 to 250 |
| Glossary and index | | 251 to 263 |

---

## Tier 1: read these first (about 75 pages)

| Book section | PDF pages | What it teaches | Matching lesson section |
|---|---|---|---|
| 1.2 to 1.4 Implementing move semantics; copying as a fallback; `const` objects | 36 to 41 | Move versus copy constructor. If an object cannot be moved, a move silently falls back to a copy. A `const` object cannot be moved from, so `const` return values disable moves. | 4. Move semantics |
| **Chapter 2** Core features of move semantics | 43 to 52 | Rvalue references; `std::move` is a `static_cast` to an rvalue reference; **moved-from objects** (valid but unspecified state, reusing them, moving an object to itself); overloading by different references; passing by value. | 4. Lvalues, rvalues and value categories; Move semantics |
| 3.1 and 3.1.1 to 3.1.2 Move semantics in ordinary classes | 53 to 58 | When move support is generated automatically, and when the generated move operations are broken. | 2. Copying and the Rule of 3, 5 and 0 |
| 3.3 to 3.4 Rules for special member functions; the Rule of Five or Three | 66 to 76 | The exact rules: declaring a copy operation or destructor disables moving (copy becomes the fallback); declaring a move operation disables copying; never `= delete` a move operation. | 2. Copying and the Rule of 3, 5 and 0 |
| 4.1 to 4.2 Avoid objects with names; avoid unnecessary `std::move` | 77 to 79 | Do not `std::move` a returned local, and prefer unnamed temporaries. | 4. Move semantics |
| 4.3.5 to 4.3.6 Member initialization summary; always pass by value and move? | 90 to 93 | When to take a parameter by value and move it into a member, and when not to (not for updating an existing value). | 4. Move semantics |
| **6.1 to 6.2 Moved-from states** (required and guaranteed states; destructible and assignable) | 107 to 115 | What state a moved-from object must be in (at least destructible), the states the standard guarantees, whether it can be assigned to, and broken invariants. | 4. Move semantics (the moved-from rule) |
| 7.1 and 7.4 Move constructors with and without `noexcept`; when and where to use `noexcept` | 125 to 134 and 140 to 141 | Why `noexcept` move operations matter for containers like `std::vector`, and the rule: declare move operations and `swap` `noexcept`. | 3. Exception-safety guarantees and noexcept |
| 8.1.2 to 8.1.3 and 8.4 to 8.5 Value categories since C++11 and C++17; when lvalues become rvalues and the reverse | 145 to 148 and 153 to 154 | lvalue, prvalue and xvalue, and what changed in C++17. A named rvalue reference parameter is itself an lvalue, so move semantics is not passed through. | 4. Lvalues, rvalues and value categories |
| 9.1 to 9.3 Perfect forwarding; universal versus rvalue references | 159 to 166 | Why perfect forwarding is needed, `std::forward`, and how to tell a universal reference from an ordinary rvalue reference. | 9. Forwarding references and perfect forwarding |

## Tier 2: read next if you have time (about 140 pages)

| Book section | PDF pages | What it teaches | Matching lesson section |
|---|---|---|---|
| 1.1 Motivation for move semantics | 21 to 36 | A worked example before and after C++11, with copy counts. | 4. Move semantics |
| 3.2 Implementing the special copy and move member functions | 58 to 66 | Writing the copy and move constructors and assignment operators by hand, including moving to itself. | 2. Copying and the Rule of 3, 5 and 0 |
| 4.3.1 to 4.3.4 Initializing members with move semantics | 79 to 90 | Three approaches (classical, moved by-value parameters, rvalue-reference overloads) and a comparison of their cost. | 4. Move semantics |
| 4.4 Move semantics in class hierarchies | 93 to 96 | A polymorphic base and derived class, and why not to declare a virtual destructor in a derived class. | 2. Inheritance; Polymorphism |
| **Chapter 5** Overloading on reference qualifiers | 97 to 106 | Getters that are both safe and fast for expensive members, and reference qualifiers on assignment operators. | 2. Member functions |
| 6.3 Dealing with broken invariants | 115 to 124 | How moves break invariants (moved value members, consistent members, pointer-like members) and how to cope. | 4. Move semantics |
| 7.2 to 7.3 `noexcept` details and class hierarchies | 134 to 140 | Rules for declaring `noexcept`, `noexcept` on special member functions, and checking abstract base classes. | 3. Exception-safety guarantees and noexcept |
| 8.2 to 8.3 and 8.6 Special value-category rules; binding references; checking with `decltype` | 148 to 153 and 154 to 156 | Value category of functions and data members, overload resolution with rvalue references, and using `decltype` to check categories. | 4. Lvalues, rvalues and value categories |
| 9.4 to 9.5 Overload resolution with universal references; perfect forwarding in lambdas | 167 to 170 | Why a universal reference is matched too eagerly, and how to fix it. | 9. Forwarding references and perfect forwarding |
| **Chapter 11** Perfect passing with `auto&&` | 191 to 202 | `auto&&` as a universal reference, `std::forward<decltype(ref)>`, and the range-based `for` loop. | 9. Forwarding references and perfect forwarding |
| **Chapter 12** Perfect returning with `decltype(auto)` | 203 to 210 | Returning a value or a reference exactly as given. Never put parentheses around the whole return expression. | 9. Type traits and if constexpr |
| **Chapter 13** Move-only types | 213 to 218 | Declaring and using move-only types; they cannot go in `std::initializer_list` or be iterated by value. | 5. Smart pointers |
| **Chapter 14** Moving algorithms and iterators | 219 to 228 | `std::move` and `std::move_backward` as algorithms, removing algorithms that leave moved-from elements, and move iterators. | 8. Algorithms |
| **Chapter 15** Move semantics in standard library types | 229 to 250 | Strings (moved-from is usually, but not guaranteed to be, empty), containers, `std::array`, `pair`, `optional`, smart pointers, IOStreams, threads and futures. | 8. The STL; 11. Futures and async |

## Reference: read when you need it (about 25 pages)

- **8.1.1** History of value categories (143 to 145).
- **Chapter 10** Tricky details of perfect forwarding (171 to 190): universal references and `const`, when `&&` is an ordinary rvalue reference (members of generic types, class template parameters, full specializations), how the standard specifies perfect forwarding, and "universal" versus "forwarding" reference.
- **Glossary** (251 to 254), a handy list of the terms the book uses.

## How this book relates to Effective Modern C++

| If you read this in *Effective Modern C++* | This book covers it in |
|---|---|
| Item 14 (`noexcept` and moves) | Chapter 7, including the `noexcept` rules for special member functions (125 to 142) |
| Item 17 (special member function generation) | 3.3 to 3.4 (66 to 76) |
| Item 18 (`unique_ptr`) | 15.4.2 and Chapter 13 (213 to 218; 243 to 245) |
| Item 23 (`std::move` and `std::forward`) | 2.2 (45 to 46) and 9.2 (161 to 164) |
| Item 24 (universal versus rvalue references) | 9.3 and Chapter 10 (165 to 190) |
| Item 25 (when to move, when to forward; returning locals) | 4.1 to 4.2 (77 to 79) and 9.2 |
| Items 26 and 27 (overloading on universal references) | 9.4 (167 to 168) |
| Item 29 (do not assume moves are cheap) | 15.1 to 15.2 (229 to 236) for strings and containers |
| Item 41 (pass by value) | 4.3.6 (91 to 93) |

This book adds what Meyers leaves out: **moved-from states** (Chapter 6), **value categories** with the C++17 changes (Chapter 8), step-by-step **implementation** of the special member functions (3.2), **reference qualifiers** (Chapter 5), and the **standard library's** move behavior (Chapters 13 to 15). If you read this one, you can skip most of Meyers' move chapter and keep only his short, interview-shaped Items 23, 25 and 29.

## Skip for interview preparation

- Chapter 10 unless you write generic library code.
- 15.5 IOStreams (245 to 247) and the details in 15.3 on `pair`, unless the topic comes up in your work.
- The index (255 to 263).

## Key ideas to take away

- Move semantics lets you optimize away a copy when you no longer need the value. `std::move` just marks an object as movable (it is a cast), and the destructor still runs on a moved-from object.
- **Moved-from objects must at least be destructible.** Anything more is up to the class, and generated move operations can break class invariants. Decide and document the state.
- The special member function rules: declaring a copy operation or destructor disables moving (copy is the fallback), declaring a move disables copying, and you should never `= delete` a move operation. Prefer the Rule of Zero, and declare a destructor only if you need one.
- Take a parameter by value and move it into a member only when a move is cheap, and not to update an existing value.
- Declare move operations and `swap` `noexcept`, so containers such as `std::vector` will use them.
- Every expression has a value category: lvalue (a named object), prvalue (an unnamed temporary) or xvalue (an object marked with `std::move`). A named rvalue reference parameter is an lvalue, so move semantics is not passed through automatically.
- `name&&` is an **ordinary rvalue reference** unless `name` is a function template parameter, when it is a **universal (forwarding) reference**. Use `std::forward` to forward it perfectly, and `decltype(auto)` to return perfectly.
- Do not return `const` values by value, and do not `std::move` a returned local.
- Move-only types (like `unique_ptr`) cannot be copied, cannot go in an `initializer_list`, and cannot be iterated over by value.
