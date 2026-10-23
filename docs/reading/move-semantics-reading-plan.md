# Reading plan: *C++ Move Semantics: The Complete Guide* (Nicolai Josuttis)

An ordered plan for reading the book in seven sessions. It is a whole book on one topic, so the plan reads the parts that explain how moving works and leaves the library reference chapters for when you need them. The reasons behind each pick are in the [reading guide](move-semantics-complete-guide-reading-guide.md).

The book is `books/Cpp-Move-Semantics-The-Complete-Guide-Josuttis.pdf` (first edition, C++11 to C++20). **All page numbers are PDF viewer pages.** Do the Move Semantics lesson (Lesson 11) and its quiz first.

## The plan at a glance

| # | Session | Book sections | PDF pages | Pages | Time |
|---|---|---|---|---|---|
| 1 | The core idea | 1.2 to 1.4; chapter 2 | 36 to 41; 43 to 52 | 14 | 2 h |
| 2 | Special member functions | 3.1; 3.3 to 3.4 | 53 to 58; 66 to 76 | 15 | 2 h |
| 3 | Passing and initializing | 4.1 to 4.2; 4.3.5 to 4.3.6 | 77 to 79; 90 to 93 | 5 | 1 h |
| 4 | Moved-from states and `noexcept` | 6.1 to 6.2; 7.1; 7.4 | 107 to 115; 125 to 134; 140 to 141 | 18 | 2.5 h |
| 5 | Value categories | 8.1.2 to 8.1.3; 8.4 to 8.5 | 145 to 148; 153 to 154 | 4 | 1 h |
| 6 | Perfect forwarding | 9.1 to 9.3 | 159 to 166 | 7 | 1 h |
| 7 | Move-only types, algorithms and the library | chapters 13 to 15 | 213 to 250 | 35 | 4 h |

About 100 pages and 14 hours at roughly 10 pages an hour plus the exercises. Optional additions are listed at the end.

## How to read each session

| Step | Do |
|---|---|
| 1. Read | Read the pages once with the code closed. |
| 2. Count | Compile the key example with a type that prints "copy" and "move" from its special members, so you see which one runs (`g++ -std=c++20 -Wall -Wextra`). |
| 3. Explain | Answer the checkpoint questions aloud. |
| 4. Reinforce | Do the "after" step. |

## Session 1: the core idea

Read 1.2 to 1.4 Implementing move semantics, copying as a fallback and `const` objects (36 to 41), then chapter 2 Core features of move semantics (43 to 52).

1. What does a move do that a copy does not, and what happens when a type has no move operation?
2. What does `std::move` do at run time?
3. What may you do with a moved-from object?

After: Lesson 11, "Lvalues, rvalues and value categories" and "Copy versus move".

## Session 2: special member functions

Read 3.1 Move semantics in ordinary classes (53 to 58) and 3.3 to 3.4 The rules for special member functions and the Rule of Five or Three (66 to 76).

1. Which declarations stop the compiler from generating moves, and which stop it from generating copies?
2. Why must you never `= delete` a move operation?
3. What does the Rule of Zero say?

After: Lesson 3, "Copying and the Rule of 3, 5 and 0"; practice exercise 10 (`MyString`).

## Session 3: passing and initializing

Read 4.1 to 4.2 Avoid objects with names and avoid unnecessary `std::move` (77 to 79) and 4.3.5 to 4.3.6 Member initialization summary, and whether to always pass by value and move (90 to 93).

1. When is "take by value, then `std::move` into the member" the right constructor, and when is it not?
2. Why is `return std::move(local)` a mistake?

After: Lesson 11, "Returning objects" and "Sink parameters and move traps".

## Session 4: moved-from states and `noexcept`

Read 6.1 to 6.2 Moved-from states (107 to 115), 7.1 Move constructors with and without `noexcept` (125 to 134) and 7.4 When and where to use `noexcept` (140 to 141).

1. What is the least a moved-from object must support, and what does the standard guarantee for its own types?
2. Why does `std::vector` copy instead of move when the move constructor can throw?
3. Which functions should you always declare `noexcept`?

After: Lesson 9 (Core, `noexcept`) and Lesson 11.

## Session 5: value categories

Read 8.1.2 to 8.1.3 Value categories since C++11 and C++17 (145 to 148) and 8.4 to 8.5 When lvalues become rvalues and the reverse (153 to 154).

1. Define lvalue, prvalue and xvalue with one example each.
2. Why is a named rvalue reference parameter an lvalue inside the function?
3. What changed for temporaries in C++17?

After: Lesson 11, "Lvalues, rvalues and value categories".

## Session 6: perfect forwarding

Read 9.1 to 9.3 Perfect forwarding and universal versus rvalue references (159 to 166).

1. Why does a wrapper need `std::forward`?
2. When is `T&&` an rvalue reference and when a universal reference?

After: Lesson 8 (Templates), "Forwarding references and perfect forwarding".

## Session 7: move-only types, algorithms and the library

Read chapter 13 Move-only types (213 to 218), chapter 14 Moving algorithms and iterators (219 to 228) and chapter 15 Move semantics in standard library types (229 to 250).

1. Why can a move-only type not be put in an `initializer_list`?
2. Why does `std::remove` leave moved-from elements at the end?
3. Is a moved-from `std::string` guaranteed to be empty?

After: Lesson 12 (Smart pointers), Lesson 6 (STL algorithms) and Lesson 17 (futures and threads are move-only).

## Optional additions

3.2 writing the copy and move members by hand (58 to 66); 4.3.1 to 4.3.4 and 4.4 (79 to 96); chapter 5 reference qualifiers (97 to 106); 6.3 broken invariants (115 to 124); 9.4 to 9.5, chapter 11 `auto&&` and chapter 12 `decltype(auto)` (167 to 170, 191 to 210). Chapter 10 only if you write generic library code. The book's relation to *Effective Modern C++* is tabulated at the end of the [reading guide](move-semantics-complete-guide-reading-guide.md).

Notes templates, one file per session: [docs/reading/notes/move-semantics-complete-guide](notes/move-semantics-complete-guide/README.md).
