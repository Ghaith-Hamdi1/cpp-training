# Reading plan: *C++ Primer* (5th Edition)

An ordered plan for reading the book to learn the language and library properly, in 33 sessions. It follows the book's own order, because each part builds on the one before it, and it skips what the lessons already cover or what is only reference. The book is `books/Cpp-Primer-5th-Edition-Lippman.pdf`. **All page numbers are PDF viewer pages** (the number your PDF reader shows), taken from the [reading guide](cpp-primer-reading-guide.md).

## The plan at a glance

| # | Session | Read (book sections) | PDF pages | Pages | Time |
|---|---|---|---|---|---|
| 1 | Types and variables | 2.1; **2.2** | 61 to 69; 70 to 78 | 18 | 3 h |
| 2 | Compound types, const and auto | **2.3**; **2.4**; 2.5 | 79 to 87; 88 to 95; 96 to 100 | 22 | 3 h |
| 3 | Structs, strings and vectors | 2.6; 3.1; **3.2**; **3.3** | 101 to 109; 111 to 112; 113 to 124; 125 to 134 | 33 | 4 h |
| 4 | Iterators and arrays | **3.4**; **3.5**; 3.6 | 135 to 141; 142 to 153; 154 to 161 | 27 | 4 h |
| 5 | Expressions and conversions | **4.1**; 4.4 to 4.5; 4.8; **4.11** | 163 to 167; 173 to 178; 181 to 184; 188 to 194 | 22 | 3 h |
| 6 | Statements and a first look at exceptions | 5.3 to 5.4; **5.6** | 203 to 218; 222 to 229 | 24 | 3 h |
| 7 | Functions: arguments and returns | 6.1; **6.2**; **6.3** | 231 to 236; 237 to 250; 251 to 258 | 28 | 4 h |
| 8 | Functions: overloading and function pointers | **6.4**; 6.5; 6.6; **6.7** | 259 to 264; 265 to 270; 271 to 275; 276 to 281 | 23 | 3 h |
| 9 | Classes: abstract data types | **7.1**; **7.2**; 7.3 | 283 to 296; 297 to 299; 300 to 310 | 28 | 4 h |
| 10 | Classes: scope, constructors, static members | 7.4; **7.5**; 7.6 | 311 to 316; 317 to 328; 329 to 334 | 24 | 3 h |
| 11 | The IO library | 8.1 to 8.3 | 339 to 353 | 15 | 3 h |
| 12 | Sequential containers | 9.1 to 9.2; **9.3** | 355 to 369; 370 to 383 | 29 | 4 h |
| 13 | How vector grows, string operations, adaptors | **9.4**; 9.5; 9.6 | 384 to 388; 389 to 396; 397 to 402 | 19 | 3 h |
| 14 | Generic algorithms and lambdas | **10.1 to 10.2**; **10.3** | 405 to 413; 414 to 429 | 25 | 4 h |
| 15 | Iterators revisited, algorithm structure | 10.4; **10.5**; 10.6 | 430 to 438; 439 to 443; 444 to 447 | 18 | 3 h |
| 16 | Associative and unordered containers | 11.1 to 11.2; **11.3**; **11.4** | 449 to 456; 457 to 471; 472 to 477 | 29 | 4 h |
| 17 | Dynamic memory and smart pointers | **12.1** | 479 to 504 | 26 | 4 h |
| 18 | Dynamic arrays and a worked program | **12.2**; 12.3 | 505 to 512; 513 to 521 | 17 | 3 h |
| 19 | Copy control | **13.1**; **13.2**; 13.3 | 525 to 538; 539 to 544; 545 to 547 | 23 | 3 h |
| 20 | A class that manages memory | 13.4; **13.5** | 548 to 552; 553 to 559 | 12 | 2 h |
| 21 | Moving objects | **13.6** | 560 to 579 | 20 | 3 h |
| 22 | Overloaded operators and function objects | 14.1 to 14.7; **14.8** | 581 to 599; 600 to 607 | 27 | 4 h |
| 23 | Conversions, base and derived classes | **14.9**; **15.1 to 15.2** | 608 to 619; 621 to 631 | 23 | 3 h |
| 24 | Virtual functions, abstract classes, access | **15.3**; **15.4**; 15.5; **15.6** | 632 to 636; 637 to 639; 640 to 645; 646 to 650 | 19 | 3 h |
| 25 | Constructors, copy control and containers under inheritance | **15.7**; **15.8** | 651 to 658; 659 to 662 | 12 | 2 h |
| 26 | Defining templates | **16.1** | 681 to 706 | 26 | 4 h |
| 27 | Template argument deduction and overloading | **16.2**; 16.3 | 707 to 722; 723 to 727 | 21 | 3 h |
| 28 | Variadic templates and specialization | **16.4**; 16.5 | 728 to 734; 735 to 743 | 16 | 3 h |
| 29 | tuple, regular expressions and random numbers | 17.1; **17.3**; **17.4** | 747 to 751; 757 to 773; 774 to 780 | 29 | 4 h |
| 30 | Exception handling and namespaces | **18.1**; 18.2 | 801 to 813; 814 to 830 | 30 | 4 h |
| 31 | Multiple inheritance and RTTI | **18.3**; **19.2** | 831 to 847; 854 to 860 | 24 | 3 h |
| 32 | Memory control, enums, unions, nested classes | 19.1; 19.3; 19.4; 19.5 to 19.6 | 849 to 853; 861 to 863; 864 to 871; 872 to 880 | 25 | 4 h |
| 33 | Optional extras | 17.2; 19.7 to 19.8 | 752 to 756; 881 to 893 | 18 | 3 h |

Bold sections are the ones to read most carefully. In all it is about 110 hours across roughly 752 pages (107 hours for sessions 1 to 32, without the optional extras), which is 11 to 16 weeks at two or three sessions a week. Time estimates assume about 10 pages an hour plus the exercises and checkpoint work; they are guidelines.

## How to read each session

| Step | Do |
|---|---|
| 1. Read | Read the pages once with the code closed. Note every sentence that surprises you. |
| 2. Write | Close the book and write the small program the pages teach (a class with a constructor, a `Stack`, a lambda with a capture). Compile with `g++ -std=c++20 -Wall -Wextra`. Open the book only to compare. |
| 3. Exercise | Do two or three of the exercises at the end of each section you read (they are numbered by section). Skip the ones that only repeat code. |
| 4. Explain | Answer the checkpoint questions aloud. If you cannot answer one in two sentences, reread that part. |
| 5. Reinforce | Do the "after" step: the repo lesson, quiz or practice exercise named for the session. |

## Part A: the language basics (sessions 1 to 10)

Chapters 2 to 7. After this you can write ordinary C++ programs and design a simple class.

| # | Checkpoint questions | After |
|---|---|---|
| 1 | Why does `int x{3.7};` not compile while `int x = 3.7;` does?<br>What is the difference between a declaration and a definition?<br>What happens when you mix a signed and an unsigned integer in a comparison?<br>What value does an uninitialized local `int` have, and why is that dangerous? | Lesson 2 (Types, Initialization and Casts), section 1; practice 07 (`parseUnsigned`) |
| 2 | What does a reference give you that a pointer does not, and the other way round?<br>Read `const int* const p` aloud.<br>Why can a `const int&` bind to a temporary but an `int&` cannot?<br>What does `auto` drop when it deduces a type, and how do you keep it? | Lesson 1 (Pointers from scratch, References, const and pointers) and its quiz; practice 09 (`pointer-basics`) |
| 3 | Why does a header file never contain `using namespace std;`?<br>What is the difference between `vector<int> v(10)` and `vector<int> v{10}`?<br>Why does `v[5] = 1` on an empty vector not add an element, and what happens instead?<br>How do you loop over a string and change each character in place? | Lesson 11 (The STL), section 2 (vector); practice 06 (`count-words`) and 08 (`trim`) |
| 4 | What does the range `[begin, end)` mean, and why is `end` one past the last element?<br>Why does an array passed to a function lose its size?<br>What is pointer arithmetic, and why is `p + 1` not "add one byte"?<br>Why do C-style strings need a terminating `\0`, and what breaks without it? | Lesson 1, section 10 (Arrays, C-strings and std::string) and the classic memory bugs; practice 01 to 05 |
| 5 | Which of `i = i++ + 1` and `a[i] = i++` are undefined behavior, and why?<br>What is an lvalue and what is an rvalue, in your own words?<br>What does `static_cast` do that a C-style cast hides?<br>Why does `-1 < 1u` evaluate to false? | Lesson 2, sections 3 and 4 (conversions and casts) and its quiz |
| 6 | What happens when a `switch` case has no `break`?<br>What does a `throw` do to the functions between it and the `catch`?<br>Why catch exceptions by reference?<br>Which destructors run during unwinding? | Lesson 6 (Core Language: RAII and Exceptions), sections 1 and 2 |
| 7 | When do you pass by value, by reference and by `const` reference?<br>Why is returning a reference to a local variable a bug?<br>What does an array parameter really receive?<br>What does `static` mean on a local variable? | Lesson 1, section 4 (passing-arguments step-through) and its quiz; practice 02 and 03 |
| 8 | Why do two functions that differ only in return type not overload?<br>What makes an overloaded call ambiguous?<br>Write a function parameter that accepts a function pointer.<br>What does `inline` really permit? | Lesson 9 (Lambdas), section 1; practice 04 (`join-all`) |
| 9 | What does `const` after a member function promise, and what does `this` become inside it?<br>What is the only difference between `struct` and `class`?<br>What is an invariant, and which function should establish it?<br>When is `mutable` justified? | Lesson 4 (OOP), sections 1 and 2; practice 10 up to its constructor |
| 10 | Why is the initializer list better than assigning in the constructor body?<br>In what order are members initialized, and why does the list order not matter?<br>What does `explicit` prevent?<br>Where is a `static` data member defined? | Lesson 4, sections 3 and 5 and its quiz |

## Part B: the library (sessions 11 to 18)

Chapters 8 to 12. The containers, algorithms and smart pointers you will use every day.

| # | Checkpoint questions | After |
|---|---|---|
| 11 | How do you test whether a read succeeded, and what are the stream state bits?<br>What does flushing do, and when does it happen on its own?<br>How do you parse a line of text into fields with a string stream? | Lesson 10 (Strings, Regex and Time), sections 4 and 5 |
| 12 | Why is `vector` the default sequential container?<br>Which operations invalidate iterators in a `vector`, and which in a `deque` and `list`?<br>What does `emplace_back` do that `push_back` does not?<br>Why is erasing in a loop a classic bug? | Lesson 11 (The STL), sections 2 to 4 and 10; its quiz |
| 13 | What is the difference between `size` and `capacity`, and what does `reserve` change?<br>Why does `push_back` take amortized constant time?<br>What does `find` return when it does not find the character?<br>What container does a `stack` use underneath? | Lesson 11, sections 2 and 4; lesson 10, section 2 (SSO and capacity); practice 12 (`Stack<T>`) so far |
| 14 | What is a predicate, and what does a lambda save you from writing?<br>What is the erase-remove idiom, and why is `remove` alone not enough?<br>What is the difference between capturing by value and by reference, and when is the reference version dangerous?<br>Why do algorithms take iterators, not containers? | Lesson 9 (Lambdas), sections 2 to 4; lesson 11, section 8 (Algorithms) |
| 15 | Name the iterator categories and one container for each.<br>Why does `std::sort` not work on a `list`?<br>What does `back_inserter` do? | Lesson 11, section 3 (Iterators) and its quiz |
| 16 | What does `m[key]` do when the key is missing, and why can that surprise you?<br>What ordering must a key type provide in a `map`, and what in an `unordered_map`?<br>When would you choose `unordered_map` over `map`?<br>How do you give your own struct a hash? | Lesson 11, sections 5 and 6; practice 06 and 17 (`BucketTable`) |
| 17 | Who owns the object when you write `new` and who deletes it?<br>How is `unique_ptr` different from `shared_ptr`, and which is the default choice?<br>What is a reference cycle, and which pointer breaks it?<br>Why prefer `make_shared` and `make_unique` over `new`? | Lesson 8 (Smart Pointers and Ownership) and its quiz |
| 18 | What goes wrong if you `delete` memory that was `new[]`-allocated?<br>Why separate allocation from construction in a container like `vector`?<br>Read 12.3 and sketch the classes before you read the code. Which owns which? | Practice 12 (`Stack<T>`) with a raw array; lesson 1, section 9 |

## Part C: tools for class authors (sessions 19 to 28)

Chapters 13 to 16. Copy control, move semantics, operators, inheritance and templates: what separates a user of C++ from a writer of classes. Do not skip these.

| # | Checkpoint questions | After |
|---|---|---|
| 19 | What are the three (five) special members and what does the Rule of Three say?<br>What is a shallow copy and why does it cause a double free?<br>Why must assignment handle `a = a`?<br>How does copy-and-swap give both safety and simplicity? | Lesson 4, sections 4 and 5; practice 10 (`MyString`) |
| 20 | What does `StrVec::reallocate` do when it runs out of capacity?<br>Why does `StrVec` use `allocator` and not `new[]`?<br>What must the destructor do for the elements before it frees the storage? | Practice 10 (`MyString`) and 12 (`Stack<T>`), writing the Rule-of-Five version |
| 21 | What does `std::move` actually do at run time?<br>Why should move operations be `noexcept`?<br>What state may a moved-from object be in?<br>What does the compiler stop generating when you declare a copy constructor? | Lesson 7 (Move Semantics) and its quiz; read Effective Modern C++ items 23 to 25 next |
| 22 | Why is `operator<<` a non-member?<br>Which operators must be members?<br>What is a function object and why is it faster than a function pointer?<br>How is a lambda translated into a class? | Lesson 4, section 6 (Operator overloading); lesson 9, section 5 |
| 23 | Why is `explicit operator bool` the standard idiom?<br>What does a derived-to-base conversion do to the object?<br>What is the meaning of "is-a" in public inheritance? | Lesson 4, sections 5 and 7 |
| 24 | What makes a call dynamically bound, and why do value parameters never do that?<br>What does `override` catch for you?<br>What is hiding, and how can a derived function hide an inherited overload set?<br>What does a class with a pure virtual function let you do? | Lesson 4, sections 7 to 9; practice 11 (polymorphism) |
| 25 | Why must a polymorphic base class have a virtual destructor?<br>What is slicing, and how do you avoid it in a container?<br>In what order do constructors and destructors run in a hierarchy?<br>What does `clone()` solve? | Lesson 4 quiz; lesson 5, section 1 |
| 26 | What is instantiation and when does it happen?<br>Why must template definitions be visible in the header?<br>What is a non-type template parameter, and where would you use one?<br>What is the difference between a class template and a template class? | Lesson 12 (Templates), sections 1 and 3; practice 12 (`Stack<T>`) |
| 27 | What does the compiler deduce for `template<class T> void f(T x)` called with a `const int&`?<br>What is a forwarding reference and how is it different from an rvalue reference?<br>What does reference collapsing say about `T& &&`?<br>What does `std::forward` do that `std::move` does not? | Lesson 12, sections 2 and 6; read Effective Modern C++ item 1 and 28 next |
| 28 | What is a parameter pack and how do you expand it?<br>Why does a recursive variadic function need a base case?<br>What is the difference between full and partial specialization?<br>Which of them can a function template have? | Lesson 12, sections 4 and 5; lesson 13 (compile-time C++) |

## Part D: advanced topics (sessions 29 to 32)

Chapters 17 to 19. Specialized tools; read the parts you need.

| # | Checkpoint questions | After |
|---|---|---|
| 29 | What is the difference between `regex_match` and `regex_search`?<br>Why do you create the engine once, outside the loop?<br>How do you return several values without defining a struct? | Lesson 3, section 2; lesson 10, section 6; lesson 11, section 11; practice 15 (`parse-value`) |
| 30 | What are the three exception-safety guarantees?<br>Why must a destructor not throw?<br>What is argument-dependent lookup, and why does `operator<<` for your type just work?<br>What does `noexcept` promise and what happens if you break it? | Lesson 6, sections 2 to 5 and its quiz |
| 31 | What is the diamond problem and how does a virtual base solve it?<br>When does `dynamic_cast` return null and when does it throw?<br>Why is a chain of `dynamic_cast` often a design smell? | Lesson 5 (The Object Model in Depth) and its quiz |
| 32 | What does placement `new` do and when would you use it?<br>Why is `enum class` better than a plain `enum`?<br>How does a discriminated union avoid reading the wrong member? | Lesson 3, section 4; lesson 20, section 3 |

## Part E: optional extras (session 33)

Optional.

| # | Read | After |
|---|---|---|
| 33 | 17.2 The bitset type; 19.7 to 19.8 Local classes and nonportable features | Lesson 19 (Binary Data and Parsing), sections 1 to 3 |

## What to skip

| Skip | Why |
|---|---|
| Chapter 1 | The first program, the bookstore program and flow of control; Lesson 1 covers the build process. |
| 4.2, 4.3, 4.6, 4.7, 4.9, 4.10, 4.12 | Operators you already know, the precedence table (look it up). |
| 5.1, 5.2, 5.5 | Simple statements, statement scope, `break`/`continue`/`goto`. |
| 17.5 | IO revisited (formatted and unformatted IO, random access); look up when needed. |
| Appendix A | A reference list of the library; use it as a lookup. |

## What this book will not teach you

| Topic | Where to learn it |
|---|---|
| Threads, mutexes, atomics | *C++ Concurrency in Action* in `books/`; lessons 16 to 18 |
| C++14 to C++20 (`optional`, `variant`, `string_view`, concepts, ranges) | lessons 2, 3, 9, 11 and 13 |
| Move semantics and forwarding in depth | *C++ Move Semantics* and *Effective Modern C++* in `books/` |
| Design patterns | lessons 14 and 15 |
| Binary data, memory layout and performance | lessons 19 and 20 |

## Notes on the edition

The code is C++11. Where the book writes `for (auto it = v.begin(); ...)` or a `bind` call, the lessons use range-for and lambdas; both are valid, and you should be able to read each. To compile the examples, use `g++ -std=c++20 -Wall -Wextra`.

For the notes on each session, see the [notes templates](notes/cpp-primer/README.md).
