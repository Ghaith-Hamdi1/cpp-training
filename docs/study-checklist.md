# Study checklist

A step-by-step plan through the lessons and the books, one phase at a time. The phases are the same eight as the [C++ roadmap](reading/roadmap/README.md), and lessons 1 to 20 run through them in order. Each phase lists its lessons with their sections and quizzes, the core book reading, the practice exercises and a recap check.

**Want ticks that save?** Use the interactive version: <https://ghaith-hamdi1.github.io/cpp-training/study-checklist.html> (also at [`interactive/study-checklist.html`](../interactive/study-checklist.html)). It has one tab per phase and its checkboxes remember your progress in your browser.

- Site: <https://ghaith-hamdi1.github.io/cpp-training/> (works offline after one visit)
- Or open [`interactive/index.html`](../interactive/index.html) from a clone of the repo.
- Time boxes are guides. If a block runs long, finish the quiz and move on.

**How to study every lesson:** read a section, run its visualizer or simulator, predict the output before revealing it, then tick "I understand this section" only when you could explain it aloud. End each lesson with its quiz and retry only the questions you missed.

---

## Phase 1: Core language foundations (about 22.9 hours)

Types, expressions, control flow, functions, pointers, references, strings and vectors.. Roadmap page: [phase-1-core-language-foundations.md](reading/roadmap/phase-1-core-language-foundations.md).

### Lessons and quizzes

**C++ Basics & Pointers:** [01-basics.html](../interactive/01-basics.html), quiz: [01-basics-quiz.html](../interactive/01-basics-quiz.html) (22 questions).

- [ ] How a C++ program is built
- [ ] Variables and types
- [ ] Operators and control flow
- [ ] Functions and passing arguments
- [ ] Where variables live: stack, heap, static
- [ ] Pointers from scratch
- [ ] References
- [ ] `const` and pointers
- [ ] Dynamic memory: `new` and `delete`
- [ ] Arrays, C-strings and `std::string`
- [ ] The classic memory bugs
- [ ] Tooling: warnings, sanitizers, static analysis
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Types, Initialization & Casts:** [16-types-and-casts.html](../interactive/16-types-and-casts.html), quiz: [16-types-and-casts-quiz.html](../interactive/16-types-and-casts-quiz.html) (16 questions).

- [ ] Initialization and brace traps
- [ ] `auto`, `decltype` and modern syntax
- [ ] Implicit conversions and `enum class`
- [ ] Casts and type conversion
- [ ] `const`, `constexpr` and `static`
- [ ] What C++14, 17 and 20 added
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

### Book reading (core)

- [ ] C++ Primer: ch. 2 Variables and Basic Types (2.1 to 2.6) (PDF pages 61 to 109)
- [ ] C++ Primer: ch. 3 Strings, Vectors and Arrays (3.2 to 3.6) (PDF pages 113 to 161)
- [ ] C++ Primer: 4.2 to 4.5 Operators (short-circuit `&&`/` (PDF pages )
- [ ] C++ Primer: 5.3 to 5.5 Statements: `switch` fall-through, the dangling `else`, loops and jumps (PDF pages 203 to 221)
- [ ] C++ Primer: ch. 6 Functions (6.1 to 6.7) (PDF pages 231 to 281)

### Practice

- [ ] Practice exercises: 01 to 09 (C strings, pointers, `trim`, `parseUnsigned`) ([examples/practice](../examples/practice/README.md))

### Recap

- [ ] Recap check. Explain from memory: what `int* const p` means, why `int{3.7}` is an error, what `v[i]` does that `v.at(i)` does not, why an array parameter is really a pointer, and what the linker error "undefined reference" means.

## Phase 2: Classes, memory and object-oriented design (about 24.5 hours)

Class design, copy control, operator overloading, inheritance, virtual functions, the object model.. Roadmap page: [phase-2-classes-memory-and-object-oriented-design.md](reading/roadmap/phase-2-classes-memory-and-object-oriented-design.md).

### Lessons and quizzes

**Object-Oriented Programming:** [02-oop.html](../interactive/02-oop.html), quiz: [02-oop-quiz.html](../interactive/02-oop-quiz.html) (26 questions).

- [ ] Classes and encapsulation
- [ ] Member functions: `this`, `const`, `static`, `friend`
- [ ] Constructors and destructors
- [ ] Copying and the Rule of 3, 5 and 0
- [ ] `explicit`, conversion operators and copy-and-swap
- [ ] Operator overloading
- [ ] Inheritance
- [ ] Polymorphism and virtual functions
- [ ] Abstract classes and interfaces
- [ ] Composition, relationships and design
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**The Object Model in Depth:** [19-object-model.html](../interactive/19-object-model.html), quiz: [19-object-model-quiz.html](../interactive/19-object-model-quiz.html) (11 questions).

- [ ] Multiple inheritance and object layout
- [ ] The diamond problem and virtual inheritance
- [ ] RTTI: `typeid` and `dynamic_cast`
- [ ] Private inheritance versus composition
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

### Book reading (core)

- [ ] C++ Primer: ch. 7 Classes (7.1 to 7.6) (PDF pages 283 to 335)
- [ ] C++ Primer: 12.1.2 Managing memory directly; 12.2.1 `new` and arrays (PDF pages 487 to 492; 506 to 509)
- [ ] C++ Primer: ch. 13 Copy Control (13.1 to 13.5) (PDF pages 525 to 559)
- [ ] C++ Primer: ch. 14 Overloaded Operations and Conversions (14.1 to 14.9) (PDF pages 581 to 619)
- [ ] C++ Primer: ch. 15 Object-Oriented Programming (15.1 to 15.9) (PDF pages 621 to 679)
- [ ] C++ Primer: 18.3 Multiple and virtual inheritance; 19.2 Run-time type identification (PDF pages 831 to 847; 854 to 860)

### Practice

- [ ] Practice exercises: 10 (`MyString`) and 11 (Shapes) ([examples/practice](../examples/practice/README.md))

### Recap

- [ ] Recap check. Explain aloud how `virtual` works in memory (vptr, vtable, slot), why a base destructor must be virtual, what the Rule of Zero says, and why `Animal a = dog;` slices.

## Phase 3: The standard library and generic programming (about 26.8 hours)

Streams, containers, iterators, algorithms, templates.. Roadmap page: [phase-3-the-standard-library-and-generic-programming.md](reading/roadmap/phase-3-the-standard-library-and-generic-programming.md).

### Lessons and quizzes

**Strings, Regex & Time:** [08-strings-regex-time.html](../interactive/08-strings-regex-time.html), quiz: [08-strings-regex-time-quiz.html](../interactive/08-strings-regex-time-quiz.html) (23 questions).

- [ ] `std::string` and `std::string_view`
- [ ] Inside `std::string`: SSO and capacity
- [ ] Numbers and text: `from_chars`, `to_chars`, `stoi`
- [ ] Formatting: `std::format` and streams
- [ ] String streams and files
- [ ] Regular expressions
- [ ] Time with `std::chrono`
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**The STL:** [04-stl.html](../interactive/04-stl.html), quiz: [04-stl-quiz.html](../interactive/04-stl-quiz.html) (33 questions).

- [ ] The big picture
- [ ] `vector`: the workhorse
- [ ] Iterators
- [ ] Other sequence containers
- [ ] Associative and unordered containers
- [ ] Custom keys: comparators and hashes
- [ ] Which container should I use?
- [ ] Algorithms
- [ ] Ranges and views (C++20)
- [ ] Common pitfalls
- [ ] Random numbers: `<random>`
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Lambdas & Callables:** [15-lambdas.html](../interactive/15-lambdas.html), quiz: [15-lambdas-quiz.html](../interactive/15-lambdas-quiz.html) (15 questions).

- [ ] Before lambdas: function pointers and functors
- [ ] What a lambda is
- [ ] Captures: by value and by reference (step through; dangling captures)
- [ ] `mutable`, init-capture, generic and recursive lambdas
- [ ] Function pointer, functor, lambda, `std::function`
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Templates:** [05-templates.html](../interactive/05-templates.html), quiz: [05-templates-quiz.html](../interactive/05-templates-quiz.html) (28 questions).

- [ ] Why templates, and function templates
- [ ] Template argument deduction
- [ ] Class templates
- [ ] Specialization
- [ ] Variadic templates and fold expressions (step through the recursion)
- [ ] Forwarding references and perfect forwarding (use the explorer, step through it)
- [ ] Alias templates, variable templates and more
- [ ] Type traits and `if constexpr`
- [ ] Pitfalls and good practice
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

### Book reading (core)

- [ ] C++ Primer: ch. 8 The IO Library (PDF pages 339 to 353)
- [ ] C++ Primer: ch. 9 Sequential Containers (9.1 to 9.6) (PDF pages 355 to 403)
- [ ] C++ Primer: ch. 10 Generic Algorithms (10.1 to 10.6) (PDF pages 405 to 447)
- [ ] C++ Primer: ch. 11 Associative Containers (11.1 to 11.4) (PDF pages 449 to 477)
- [ ] C++ Primer: ch. 16 Templates: 16.1 to 16.3, 16.5 (skip 16.2.5 to 16.2.7 and 16.4 until phase 5) (PDF pages 681 to 706; 707 to 718; 723 to 727; 735 to 743)
- [ ] Effective Modern C++: Items 31 to 32: lambdas (PDF pages 234 to 247)
- [ ] C++ Primer: ch. 17: 17.1 tuple; 17.3 regular expressions; 17.4 random numbers (PDF pages 747 to 751; 757 to 773; 774 to 780)

### Practice

- [ ] Practice exercises: 12 (`Stack<T>`) ([examples/practice](../examples/practice/README.md))

### Recap

- [ ] Recap check. Explain: how a lambda is compiled (a closure class with `operator()`), when `vector` invalidates iterators, why `map::operator[]` can insert, what a strict weak ordering is, how a template is instantiated, and why `std::sort` does not work on `std::list`.

## Phase 4: RAII, exceptions and advanced language tools (about 7.2 hours)

Exceptions and RAII, namespaces, unions and enums, memory control.. Roadmap page: [phase-4-raii-exceptions-and-advanced-language-tools.md](reading/roadmap/phase-4-raii-exceptions-and-advanced-language-tools.md).

### Lessons and quizzes

**Core Language: RAII & Exceptions:** [03-core-language.html](../interactive/03-core-language.html), quiz: [03-core-language-quiz.html](../interactive/03-core-language-quiz.html) (17 questions).

- [ ] RAII: the central idea
- [ ] Exceptions and stack unwinding
- [ ] RAII everywhere: guards and standard wrappers
- [ ] Exception-safety guarantees and noexcept
- [ ] Exceptions, error codes and optional
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

### Book reading (core)

- [ ] C++ Primer: 5.6 `try` blocks; 18.1 Exception handling; 18.2 Namespaces (PDF pages 222 to 228; 801 to 830)
- [ ] C++ Primer: 19.1 Controlling memory allocation; 19.3 enumerations; 19.5 nested classes; 19.6 `union` (PDF pages 849 to 853; 861 to 863; 872 to 875; 876 to 880)
- [ ] Programming: Principles and Practice: RAII, exceptions and resource management: 18.4 to 18.5 (PDF pages 542 to 553)

### Recap

- [ ] Recap check. Explain: what stack unwinding does, why a destructor must not throw, the difference between basic and strong guarantee and how copy-and-swap gives the strong one.

## Phase 5: Modern C++ (C++11 to C++20) (about 24.3 hours)

Move semantics, smart pointers, forwarding, `constexpr`, vocabulary types, concepts.. Roadmap page: [phase-5-modern-cpp.md](reading/roadmap/phase-5-modern-cpp.md).

### Lessons and quizzes

**Vocabulary Types:** [21-vocabulary-types.html](../interactive/21-vocabulary-types.html), quiz: [21-vocabulary-types-quiz.html](../interactive/21-vocabulary-types-quiz.html) (13 questions).

- [ ] Why vocabulary types
- [ ] `pair`, `tuple` and structured bindings
- [ ] `optional`: a value or nothing
- [ ] `variant` and `std::visit`
- [ ] `expected`: a value or an error
- [ ] `span` and `string_view`: non-owning views
- [ ] Which one when
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Move Semantics:** [13-move-semantics.html](../interactive/13-move-semantics.html), quiz: [13-move-semantics-quiz.html](../interactive/13-move-semantics-quiz.html) (15 questions).

- [ ] Lvalues, rvalues and value categories
- [ ] Copy versus move (step through it; what `std::move` really does)
- [ ] Writing move operations
- [ ] Returning objects: elision and `std::move`
- [ ] Sink parameters and move traps (the `const` trap)
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Smart Pointers & Ownership:** [14-smart-pointers.html](../interactive/14-smart-pointers.html), quiz: [14-smart-pointers-quiz.html](../interactive/14-smart-pointers-quiz.html) (12 questions).

- [ ] Who owns it? The three smart pointers
- [ ] `unique_ptr` in detail (deleters, arrays, zero overhead)
- [ ] `shared_ptr` and the control block (step through the count)
- [ ] Reference cycles and `weak_ptr` (step through the leak)
- [ ] Pitfalls and `enable_shared_from_this`
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Type Traits & Compile-time C++:** [09-compile-time.html](../interactive/09-compile-time.html), quiz: [09-compile-time-quiz.html](../interactive/09-compile-time-quiz.html) (18 questions).

- [ ] Type traits
- [ ] `enable_if` and SFINAE
- [ ] Concepts and `requires` (C++20)
- [ ] `constexpr`, `consteval`, `constinit`
- [ ] Template metaprogramming (TMP)
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

### Book reading (core)

- [ ] C++ Primer: 12.1 smart pointers (shared_ptr, unique_ptr, weak_ptr) (PDF pages 479 to 486; 493 to 504)
- [ ] C++ Primer: 13.6 Moving objects (PDF pages 560 to 579)
- [ ] C++ Primer: 16.2.5 to 16.2.7 deduction, `std::move`, forwarding; 16.4 variadic templates (PDF pages 716 to 722; 728 to 734)
- [ ] Effective Modern C++: Items 1, 2, 5, 7: deduction, `auto`, `()` versus `{}` (PDF pages 27 to 41; 55 to 61; 67 to 76)
- [ ] Effective Modern C++: Item 15 `constexpr` (PDF pages 115 to 121)
- [ ] Effective Modern C++: Items 18 to 22: `unique_ptr`, `shared_ptr`, `weak_ptr`, `make_*`, Pimpl (PDF pages 136 to 174)
- [ ] Effective Modern C++: Items 23, 24, 25, 28: `move`, `forward`, universal references, reference collapsing (PDF pages 176 to 195; 215 to 221)
- [ ] Effective Modern C++: Items 26 to 27, 29, 41, 42: overloading, cheap moves, pass by value, emplacement (PDF pages 195 to 215; 221 to 225; 299 to 320)

### Practice

- [ ] Practice exercises: 15 (`optional`/`variant`) and 16 (concepts) ([examples/practice](../examples/practice/README.md))

### Recap

- [ ] Recap check. Explain: what `std::move` does at run time (nothing), why `return std::move(local)` hurts, the three value categories, what a forwarding reference is, why `make_shared` needs one allocation, and what a concept replaces.

## Phase 6: Design patterns and SOLID (about 1.5 hours)

Common designs in modern C++, with real code.. Roadmap page: [phase-6-design-patterns-and-solid.md](reading/roadmap/phase-6-design-patterns-and-solid.md).

### Lessons and quizzes

**Design Patterns:** [06-design-patterns.html](../interactive/06-design-patterns.html), quiz: [06-design-patterns-quiz.html](../interactive/06-design-patterns-quiz.html) (20 questions).

- [ ] What patterns are and are not
- [ ] SOLID principles
- [ ] Singleton
- [ ] Factory
- [ ] Strategy (try the widget)
- [ ] Observer (subscribe and unsubscribe in the demo)
- [ ] State (use the turnstile demo)
- [ ] Other patterns worth recognising
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**More Patterns:** [20-more-patterns.html](../interactive/20-more-patterns.html), quiz: [20-more-patterns-quiz.html](../interactive/20-more-patterns-quiz.html) (11 questions).

- [ ] Command (with undo)
- [ ] Decorator
- [ ] Adapter
- [ ] Builder
- [ ] Visitor and `std::variant`
- [ ] A protocol state machine with `variant`
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

### Recap

- [ ] Recap check. Explain: when Strategy is just a lambda, why Singleton is a global with a nicer name, how Observer avoids dangling subscribers, and how `variant` plus `visit` replaces a Visitor class hierarchy.

## Phase 7: Concurrency and the memory model (about 14.4 hours)

Threads, mutexes, condition variables, futures and pools, atomics.. Roadmap page: [phase-7-concurrency-and-the-memory-model.md](reading/roadmap/phase-7-concurrency-and-the-memory-model.md).

### Lessons and quizzes

**Multithreading:** [07-multithreading.html](../interactive/07-multithreading.html), quiz: [07-multithreading-quiz.html](../interactive/07-multithreading-quiz.html) (28 questions).

- [ ] Why threads? The mental model
- [ ] Your first thread (including the dangling-argument trap and joining on every path)
- [ ] Shared data and data races (invariants; run the race simulator and "Run 500 random schedules")
- [ ] Mutexes: taking turns (run the mutex simulator)
- [ ] Other mutex types and `call_once` (why recursive mutexes are a smell)
- [ ] Races hidden in interfaces (step through the stack example)
- [ ] Deadlock (cause the deadlock yourself, then run the fixed version)
- [ ] Condition variables (step through the hand-over)
- [ ] Debugging and common bugs
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Tasks & Parallelism:** [17-tasks-parallelism.html](../interactive/17-tasks-parallelism.html), quiz: [17-tasks-parallelism-quiz.html](../interactive/17-tasks-parallelism-quiz.html) (15 questions).

- [ ] Futures and async
- [ ] `promise`, `shared_future` and `packaged_task`
- [ ] Thread pools and producer/consumer (step through the pool)
- [ ] Work stealing and sizing a pool
- [ ] `latch`, `barrier`, `semaphore` and `stop_token` (C++20)
- [ ] Parallel algorithms (C++17)
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Atomics & the Memory Model:** [18-atomics-memory-model.html](../interactive/18-atomics-memory-model.html), quiz: [18-atomics-memory-model-quiz.html](../interactive/18-atomics-memory-model-quiz.html) (17 questions).

- [ ] Atomic operations and `compare_exchange`
- [ ] Memory orders and happens-before (use the memory-order simulator)
- [ ] Ordering patterns that matter (publish, refcount, spinlock)
- [ ] Thread-safe data structures (fine-grained locks, lock-free push)
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

### Book reading (core)

- [ ] C++ Concurrency in Action: Why threads and launching them: 1.1, 1.2.3, 2.1, 2.2 (PDF pages 25 to 30; 32 to 33; 40 to 50)
- [ ] C++ Concurrency in Action: Sharing data and mutexes: 3.1, 3.2.1 to 3.2.3 (PDF pages 60 to 74)
- [ ] C++ Concurrency in Action: Deadlock and locking: 3.2.4 to 3.2.8, 3.3.1 (PDF pages 74 to 91)
- [ ] C++ Concurrency in Action: Waiting for events and results: 4.1, 4.2.1 to 4.2.4 (PDF pages 96 to 113)
- [ ] C++ Concurrency in Action: Thread counts and a pool: 2.4, 9.1.1 (PDF pages 54 to 57; 324 to 326)
- [ ] C++ Concurrency in Action: The memory model and data structures: 5.1, 5.3 overview, 6.1 to 6.2.2 (PDF pages 148 to 151; 165 to 170; 197 to 206)
- [ ] C++ Concurrency in Action: Performance and bugs: 8.2, 11.1 to 11.2.1 (PDF pages 283 to 289; 363 to 367)

### Practice

- [ ] Practice exercises: 13 (`SafeCounter`) and 14 (`BoundedQueue<T>`) ([examples/practice](../examples/practice/README.md))

### Recap

- [ ] Recap check. Explain: what a data race is and why it is undefined behavior, why a mutex per method is not enough, the four conditions for deadlock, why `wait` needs a predicate, what release and acquire guarantee, and what the ABA problem is.

## Phase 8: Performance, memory layout and binary data (about 3.9 hours)

Cache, allocation, struct layout, endianness, parsing, queues.. Roadmap page: [phase-8-performance-memory-layout-and-binary-data.md](reading/roadmap/phase-8-performance-memory-layout-and-binary-data.md).

### Lessons and quizzes

**Binary Data & Parsing:** [11-wire-formats.html](../interactive/11-wire-formats.html), quiz: [11-wire-formats-quiz.html](../interactive/11-wire-formats-quiz.html) (21 questions).

- [ ] From bytes to values
- [ ] Integers and bit manipulation
- [ ] Struct layout, alignment and padding
- [ ] Endianness
- [ ] Reading bytes safely: aliasing and memcpy
- [ ] Zero-copy parsing
- [ ] Money amounts: fixed-point versus double
- [ ] Sequence numbers and gaps
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Performance & Memory:** [12-low-latency.html](../interactive/12-low-latency.html), quiz: [12-low-latency-quiz.html](../interactive/12-low-latency-quiz.html) (23 questions).

- [ ] Where latency comes from
- [ ] Measuring: percentiles and tail latency
- [ ] Memory on the hot path
- [ ] Cache-friendly data
- [ ] Dense keys: an array instead of a map
- [ ] Queues between threads
- [ ] A predictable hot path
- [ ] Threads, cores and busy-polling
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

### Book reading (core)

- [ ] C++ Primer: 17.2 `bitset`; 19.8 bit-fields, `volatile`, `extern "C"` (PDF pages 752 to 756; 883 to 892)

### Practice

- [ ] Practice exercises: 17 (`BucketTable`) ([examples/practice](../examples/practice/README.md))

### Recap

- [ ] Recap check. Explain: why the average hides the tail, how an object pool works, why a struct is bigger than the sum of its members, what endianness is and the portable way to read a big-endian value, and what false sharing is.

## Final review

- [ ] Retake every quiz where you scored under 80%.
- [ ] Take the level check and revisit your weakest topics.
- [ ] Open each lesson's "Cheat sheet" and say every answer aloud before opening it.
- [ ] Try ten C++ Puzzles.
- [ ] From memory, write a thread-safe queue (mutex and condition variable).
- [ ] From memory, write a deadlock, then fix it with `std::scoped_lock`.
- [ ] Explain in your own words: data race versus race condition, `mutex` versus `atomic`, and why `wait` needs a predicate.

<!-- generated:end (tools/build-checklist.mjs writes everything above; the static part follows) -->

## Move semantics deep dive (optional)

Not needed for a first pass. When you want to master move semantics, follow the two guides below. The Josuttis book covers what Meyers leaves out: the moved-from state, value categories and writing move operations. About 75 pages of the Josuttis book plus a few Meyers items.

- [Effective Modern C++ move semantics path](reading/effective-modern-cpp-reading-guide.md#special-focus-move-semantics-and-perfect-forwarding) (`books/Effective-Modern-Cpp-Meyers.pdf`)
- [C++ Move Semantics reading guide, Tier 1](reading/move-semantics-complete-guide-reading-guide.md#tier-1-read-these-first-about-75-pages) (`books/Cpp-Move-Semantics-The-Complete-Guide-Josuttis.pdf`)

- [ ] Meyers Item 17, special member function generation (PDF pages 127 to 133)
- [ ] Meyers Items 24 and 28, universal references and reference collapsing (PDF pages 182 to 186 and 215 to 221)
- [ ] Josuttis chapter 2, core features including moved-from objects (PDF pages 43 to 52)
- [ ] Josuttis 3.1 and 3.3 to 3.4, the rules for special member functions and the Rule of Five or Three (PDF pages 53 to 58 and 66 to 76)
- [ ] Josuttis 6.1 to 6.2, moved-from states (PDF pages 107 to 115)
- [ ] Josuttis 7.1 and 7.4, `noexcept` and when to use it (PDF pages 125 to 134 and 140 to 141)
- [ ] Josuttis 8.1.2 to 8.1.3 and 8.4 to 8.5, value categories (PDF pages 145 to 148 and 153 to 154)
- [ ] Josuttis 9.1 to 9.3, perfect forwarding and universal references (PDF pages 159 to 166)
- [ ] Self-check from memory: write a class with a `noexcept` move constructor and move assignment, say what state its moved-from object is in, and explain the `const` trap and why `return std::move(local)` is a mistake

---

## Books: going deeper

For a full read, follow the [C++ roadmap](reading/roadmap/README.md): eight phases that match lessons 1 to 20 in order, each with the book chapters to read. For a single book, use its reading guide (which sections matter) or reading plan (an ordered path):

- Core language and library: [cpp-primer-reading-guide.md](reading/cpp-primer-reading-guide.md) (`books/Cpp-Primer-5th-Edition-Lippman.pdf`)
- Threading: [concurrency-in-action-reading-guide.md](reading/concurrency-in-action-reading-guide.md) (`books/Cpp-Concurrency-in-Action-2nd-Edition-Williams.pdf`; Tier 1 is about 47 pages)
- Foundations (pointers, OOP, templates, STL): [programming-principles-and-practice-reading-guide.md](reading/programming-principles-and-practice-reading-guide.md) (`books/Programming-Principles-and-Practice-Using-Cpp-3rd-Edition-Stroustrup.pdf`)
- Modern C++ items: [effective-modern-cpp-reading-guide.md](reading/effective-modern-cpp-reading-guide.md) (`books/Effective-Modern-Cpp-Meyers.pdf`; Tier 1 is about 85 pages)
- Move semantics in depth: [move-semantics-complete-guide-reading-guide.md](reading/move-semantics-complete-guide-reading-guide.md) (`books/Cpp-Move-Semantics-The-Complete-Guide-Josuttis.pdf`; Tier 1 is about 75 pages)
