# Study checklist

A step-by-step plan through the lessons and the books, one phase at a time. The phases are the same six as the [C++ roadmap](reading/roadmap/README.md), and the lessons run through them in order. Each phase lists its lessons with their sections and quizzes, the core book reading, the practice exercises and a recap check.

**Want ticks that save?** Use the interactive version: <https://ghaith-hamdi1.github.io/cpp-training/study-checklist.html> (also at [`interactive/study-checklist.html`](../interactive/study-checklist.html)). It has one tab per phase and its checkboxes remember your progress in your browser.

- Site: <https://ghaith-hamdi1.github.io/cpp-training/> (works offline after one visit)
- Or open [`interactive/index.html`](../interactive/index.html) from a clone of the repo.
- Time boxes are guides. If a block runs long, finish the quiz and move on.

**How to study every lesson:** read a section, run its visualizer or simulator, predict the output before revealing it, then tick "I understand this section" only when you could explain it aloud. End each lesson with its quiz and retry only the questions you missed.

---

## Phase 1: Core language foundations (about 24.0 hours)

Types, expressions, control flow, functions, pointers, references, strings and vectors.. Roadmap page: [phase-1-core-language-foundations.md](reading/roadmap/phase-1-core-language-foundations.md).

### Lessons and quizzes

**C++ Basics:** [01-basics.html](../interactive/01-basics.html), quiz: [01-basics-quiz.html](../interactive/01-basics-quiz.html) (13 questions).

- [ ] How a C++ program is built
- [ ] Variables and types
- [ ] Operators and control flow
- [ ] Functions and passing arguments
- [ ] Tooling: warnings, sanitizers, static analysis
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Pointers and References:** [22-pointers.html](../interactive/22-pointers.html), quiz: [22-pointers-quiz.html](../interactive/22-pointers-quiz.html) (18 questions).

- [ ] Memory is a row of numbered boxes
- [ ] Where variables live: stack, heap, static
- [ ] Pointers from scratch
- [ ] Pointers and arrays
- [ ] References
- [ ] `const` and pointers
- [ ] Dynamic memory: `new` and `delete`
- [ ] The classic memory bugs
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Types, Initialization & Constants:** [16-types-and-casts.html](../interactive/16-types-and-casts.html), quiz: [16-types-and-casts-quiz.html](../interactive/16-types-and-casts-quiz.html) (13 questions).

- [ ] Initialization and brace traps
- [ ] `auto`, `decltype` and modern syntax
- [ ] `const`, `constexpr` and `static`
- [ ] What C++14, 17 and 20 added
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Casts and Type Conversions:** [25-casts.html](../interactive/25-casts.html), quiz: [25-casts-quiz.html](../interactive/25-casts-quiz.html) (15 questions).

- [ ] What the compiler converts for you
- [ ] Narrowing and braces
- [ ] The C-style cast and why to avoid it
- [ ] `static_cast`: the everyday cast
- [ ] `dynamic_cast`: checked downcasts
- [ ] `const_cast`, `reinterpret_cast` and `bit_cast`
- [ ] Which cast, if any?
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

### Book reading (core)

- [ ] C++ Primer: ch. 2 Variables and Basic Types (2.1 to 2.6) (PDF pages 61 to 109)
- [ ] C++ Primer: ch. 3 Strings, Vectors and Arrays (3.2 to 3.6) (PDF pages 113 to 161)
- [ ] C++ Primer: 4.2 to 4.5 Operators (short-circuit `&&`/`||`, prefix versus postfix `++`); 4.8 Bitwise operators; 4.11 Type conversions (PDF pages 168 to 178; 181 to 184; 188 to 194)
- [ ] C++ Primer: 5.3 to 5.5 Statements: `switch` fall-through, the dangling `else`, loops and jumps (PDF pages 203 to 221)
- [ ] C++ Primer: ch. 6 Functions (6.1 to 6.7) (PDF pages 231 to 281)

### Practice

- [ ] Practice exercises: 01 to 09 (C strings, pointers, `trim`, `parseUnsigned`) ([examples/practice](../examples/practice/README.md))

### Recap

- [ ] Recap check. Explain from memory: what `int* const p` means, why `int{3.7}` is an error, what `v[i]` does that `v.at(i)` does not, why an array parameter is really a pointer, and what the linker error "undefined reference" means.

## Phase 2: Classes, memory and object-oriented design (about 25.3 hours)

Class design, copy control, operator overloading, inheritance, virtual functions, the object model.. Roadmap page: [phase-2-classes-memory-and-object-oriented-design.md](reading/roadmap/phase-2-classes-memory-and-object-oriented-design.md).

### Lessons and quizzes

**Classes and Objects:** [02-oop.html](../interactive/02-oop.html), quiz: [02-oop-quiz.html](../interactive/02-oop-quiz.html) (13 questions).

- [ ] Classes and encapsulation
- [ ] Member functions: `this`, `const`, `static`, `friend`
- [ ] Constructors and destructors
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Copy Control and Operators:** [26-copying.html](../interactive/26-copying.html), quiz: [26-copying-quiz.html](../interactive/26-copying-quiz.html) (12 questions).

- [ ] Copying and the Rule of 3, 5 and 0
- [ ] `explicit`, conversion operators and copy-and-swap
- [ ] Operator overloading
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Inheritance, Virtual Functions and the Object Model:** [27-inherit.html](../interactive/27-inherit.html), quiz: [27-inherit-quiz.html](../interactive/27-inherit-quiz.html) (19 questions).

- [ ] Inheritance
- [ ] Polymorphism and virtual functions
- [ ] Abstract classes and interfaces
- [ ] Composition, relationships and design
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

## Phase 3: The standard library and generic programming (about 30.1 hours)

Streams, containers, iterators, algorithms, templates.. Roadmap page: [phase-3-the-standard-library-and-generic-programming.md](reading/roadmap/phase-3-the-standard-library-and-generic-programming.md).

### Lessons and quizzes

**Function Pointers and Functors:** [23-callables.html](../interactive/23-callables.html), quiz: [23-callables-quiz.html](../interactive/23-callables-quiz.html) (13 questions).

- [ ] Something you can call
- [ ] Function pointers
- [ ] Functors: objects you can call
- [ ] `std::function` and `std::invoke`
- [ ] Which one when
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Lambdas:** [15-lambdas.html](../interactive/15-lambdas.html), quiz: [15-lambdas-quiz.html](../interactive/15-lambdas-quiz.html) (13 questions).

- [ ] What a lambda is
- [ ] Captures: by value and by reference (step through; dangling captures)
- [ ] Capture lifetime: dangling references
- [ ] `mutable`, init-capture, generic and recursive lambdas
- [ ] Where lambdas are used
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**STL Containers:** [04-stl.html](../interactive/04-stl.html), quiz: [04-stl-quiz.html](../interactive/04-stl-quiz.html) (13 questions).

- [ ] The big picture
- [ ] `vector`: the workhorse
- [ ] Other sequence containers
- [ ] Container adaptors
- [ ] Which container should I use?
- [ ] Common pitfalls
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Maps, Sets and Hashing:** [31-assoc.html](../interactive/31-assoc.html), quiz: [31-assoc-quiz.html](../interactive/31-assoc-quiz.html) (13 questions).

- [ ] Associative and unordered containers
- [ ] Custom keys: comparators and hashes
- [ ] `pair`, `tuple` and structured bindings
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Iterators:** [28-iterators.html](../interactive/28-iterators.html), quiz: [28-iterators-quiz.html](../interactive/28-iterators-quiz.html) (12 questions).

- [ ] Iterators
- [ ] Inserters and iterator adaptors
- [ ] Iterator invalidation
- [ ] `span` and `string_view`: non-owning views
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Algorithms and Ranges:** [29-algorithms.html](../interactive/29-algorithms.html), quiz: [29-algorithms-quiz.html](../interactive/29-algorithms-quiz.html) (16 questions).

- [ ] Algorithms
- [ ] Which algorithm do I need?
- [ ] Ranges and views (C++20)
- [ ] Common algorithm pitfalls
- [ ] Random numbers: `<random>`
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Function Templates:** [05-templates.html](../interactive/05-templates.html), quiz: [05-templates-quiz.html](../interactive/05-templates-quiz.html) (17 questions).

- [ ] Why templates, and function templates
- [ ] Template argument deduction
- [ ] Variadic templates and fold expressions (step through the recursion)
- [ ] Forwarding references (use the explorer, step through it)
- [ ] Pitfalls and good practice
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Class Templates:** [30-classtemplates.html](../interactive/30-classtemplates.html), quiz: [30-classtemplates-quiz.html](../interactive/30-classtemplates-quiz.html) (12 questions).

- [ ] Class templates
- [ ] Class template argument deduction (C++17)
- [ ] Specialization
- [ ] Alias templates, variable templates and more
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Type Traits, Concepts and Compile-time C++:** [09-compile-time.html](../interactive/09-compile-time.html), quiz: [09-compile-time-quiz.html](../interactive/09-compile-time-quiz.html) (20 questions).

- [ ] Type traits
- [ ] Type traits and `if constexpr`
- [ ] `enable_if` and SFINAE
- [ ] Concepts and `requires` (C++20)
- [ ] `constexpr`, `consteval`, `constinit`
- [ ] Template metaprogramming (TMP)
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

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

## Phase 4: RAII, exceptions and advanced language tools (about 7.1 hours)

Exceptions and RAII, namespaces, unions and enums, memory control.. Roadmap page: [phase-4-raii-exceptions-and-advanced-language-tools.md](reading/roadmap/phase-4-raii-exceptions-and-advanced-language-tools.md).

### Lessons and quizzes

**RAII and Exceptions:** [03-core-language.html](../interactive/03-core-language.html), quiz: [03-core-language-quiz.html](../interactive/03-core-language-quiz.html) (15 questions).

- [ ] RAII: the central idea
- [ ] Exceptions and stack unwinding
- [ ] RAII everywhere: guards and standard wrappers
- [ ] Exception-safety guarantees and noexcept
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

### Book reading (core)

- [ ] C++ Primer: 5.6 `try` blocks; 18.1 Exception handling; 18.2 Namespaces (PDF pages 222 to 228; 801 to 830)
- [ ] C++ Primer: 19.1 Controlling memory allocation; 19.3 enumerations; 19.5 nested classes; 19.6 `union` (PDF pages 849 to 853; 861 to 863; 872 to 875; 876 to 880)
- [ ] Programming: Principles and Practice: RAII, exceptions and resource management: 18.4 to 18.5 (PDF pages 542 to 553)

### Recap

- [ ] Recap check. Explain: what stack unwinding does, why a destructor must not throw, the difference between basic and strong guarantee and how copy-and-swap gives the strong one.

## Phase 5: Modern C++ (C++11 to C++20) (about 27.0 hours)

Move semantics, smart pointers, forwarding, `constexpr`, vocabulary types, concepts.. Roadmap page: [phase-5-modern-cpp.md](reading/roadmap/phase-5-modern-cpp.md).

### Lessons and quizzes

**Values or Errors: optional, variant and expected:** [21-vocabulary-types.html](../interactive/21-vocabulary-types.html), quiz: [21-vocabulary-types-quiz.html](../interactive/21-vocabulary-types-quiz.html) (11 questions).

- [ ] Why vocabulary types
- [ ] Exceptions, error codes and optional
- [ ] `optional`: a value or nothing
- [ ] `variant` and `std::visit`
- [ ] `expected`: a value or an error
- [ ] Which one when
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Lvalues and Rvalues:** [13-move-semantics.html](../interactive/13-move-semantics.html), quiz: [13-move-semantics-quiz.html](../interactive/13-move-semantics-quiz.html) (12 questions).

- [ ] Names and temporaries
- [ ] Lvalues, rvalues and value categories
- [ ] Which reference binds to what
- [ ] A name is always an lvalue
- [ ] What a parameter type promises
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Copy versus Move, and std::move:** [33-copymove.html](../interactive/33-copymove.html), quiz: [33-copymove-quiz.html](../interactive/33-copymove-quiz.html) (10 questions).

- [ ] What a copy costs
- [ ] What `std::move` really does
- [ ] Moved-from objects
- [ ] When `std::move` copies anyway
- [ ] Which standard types are cheap to move
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Writing Move Operations:** [34-writemoves.html](../interactive/34-writemoves.html), quiz: [34-writemoves-quiz.html](../interactive/34-writemoves-quiz.html) (11 questions).

- [ ] The move constructor, step by step
- [ ] Move assignment and copy-and-swap
- [ ] Why moves must be `noexcept`
- [ ] Rule of Zero first
- [ ] Testing your move operations
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Returning Objects and Copy Elision:** [35-elision.html](../interactive/35-elision.html), quiz: [35-elision-quiz.html](../interactive/35-elision-quiz.html) (11 questions).

- [ ] Returning a local: the compiler does the work
- [ ] Guaranteed elision in C++17
- [ ] When `std::move` on a return is right and wrong
- [ ] When elision does not happen
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Sink Parameters and Move Traps:** [36-sinks.html](../interactive/36-sinks.html), quiz: [36-sinks-quiz.html](../interactive/36-sinks-quiz.html) (11 questions).

- [ ] Taking a parameter you will store
- [ ] By value, overloads or const reference?
- [ ] Move traps
- [ ] `push_back`, `emplace_back` and moving into containers
- [ ] Move-only sinks
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Perfect Forwarding:** [37-forwarding.html](../interactive/37-forwarding.html), quiz: [37-forwarding-quiz.html](../interactive/37-forwarding-quiz.html) (10 questions).

- [ ] Why a wrapper loses the category
- [ ] `std::forward` restores it
- [ ] Reference collapsing
- [ ] Where forwarding fails
- [ ] Forwarding in practice
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**unique_ptr: Exclusive Ownership:** [24-uniqueptr.html](../interactive/24-uniqueptr.html), quiz: [24-uniqueptr-quiz.html](../interactive/24-uniqueptr-quiz.html) (16 questions).

- [ ] Ownership: who frees it?
- [ ] Creating a `unique_ptr`
- [ ] Move-only: handing over ownership
- [ ] Passing and returning
- [ ] Deleters, arrays, polymorphism and the member functions
- [ ] Common mistakes
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**shared_ptr: Shared Ownership:** [14-smart-pointers.html](../interactive/14-smart-pointers.html), quiz: [14-smart-pointers-quiz.html](../interactive/14-smart-pointers-quiz.html) (12 questions).

- [ ] When ownership is shared
- [ ] `shared_ptr` and the control block (step through the count)
- [ ] `make_shared` and the cost of a copy
- [ ] `shared_ptr` and threads
- [ ] Pitfalls and `enable_shared_from_this`
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**weak_ptr and Reference Cycles:** [32-weakptr.html](../interactive/32-weakptr.html), quiz: [32-weakptr-quiz.html](../interactive/32-weakptr-quiz.html) (12 questions).

- [ ] The cycle problem
- [ ] `weak_ptr` and `lock()`
- [ ] Where weak_ptr belongs
- [ ] What a weak_ptr keeps alive
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

## Phase 6: Concurrency and the memory model (about 17.7 hours)

Threads, mutexes, condition variables, futures and pools, atomics.. Roadmap page: [phase-6-concurrency-and-the-memory-model.md](reading/roadmap/phase-6-concurrency-and-the-memory-model.md).

### Lessons and quizzes

**Threads: The Mental Model and Your First Thread:** [07-multithreading.html](../interactive/07-multithreading.html), quiz: [07-multithreading-quiz.html](../interactive/07-multithreading-quiz.html) (12 questions).

- [ ] Why threads? The mental model
- [ ] Concurrency, parallelism and the cost of a thread
- [ ] Your first thread (including the dangling-argument trap and joining on every path)
- [ ] Arguments, ownership and detach bugs
- [ ] Join on every path
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Shared Data and Data Races:** [38-races.html](../interactive/38-races.html), quiz: [38-races-quiz.html](../interactive/38-races-quiz.html) (11 questions).

- [ ] Shared data and data races
- [ ] Races break invariants
- [ ] Three ways to be safe
- [ ] The three strategies in code
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Mutexes and Locking:** [39-mutexes.html](../interactive/39-mutexes.html), quiz: [39-mutexes-quiz.html](../interactive/39-mutexes-quiz.html) (15 questions).

- [ ] Mutexes: taking turns
- [ ] Use RAII locks, never raw `lock()`/`unlock()`
- [ ] Protecting a class
- [ ] How long to hold a lock
- [ ] Other mutex types and `call_once`
- [ ] `recursive_mutex` is a design smell
- [ ] Reader-writer lock
- [ ] `std::call_once`
- [ ] Races hidden in interfaces
- [ ] Fix: offer whole operations
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Deadlock:** [40-deadlock.html](../interactive/40-deadlock.html), quiz: [40-deadlock-quiz.html](../interactive/40-deadlock-quiz.html) (13 questions).

- [ ] Deadlock
- [ ] Fix: one global lock order
- [ ] Four guidelines, one idea
- [ ] Livelock, starvation and lost wakeups
- [ ] Finding a deadlock
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Condition Variables and Debugging:** [41-condvars.html](../interactive/41-condvars.html), quiz: [41-condvars-quiz.html](../interactive/41-condvars-quiz.html) (13 questions).

- [ ] Condition variables
- [ ] The predicate is the truth
- [ ] Three rules to follow
- [ ] A reusable thread-safe queue
- [ ] Debugging and common bugs
- [ ] Vocabulary
- [ ] A producer and consumer timeline
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Futures, async and Promises:** [17-tasks-parallelism.html](../interactive/17-tasks-parallelism.html), quiz: [17-tasks-parallelism-quiz.html](../interactive/17-tasks-parallelism-quiz.html) (13 questions).

- [ ] Why tasks instead of raw threads
- [ ] `std::async` and `std::future`
- [ ] The future that waits in its destructor
- [ ] Exceptions travel with the result
- [ ] `promise`: the writing end
- [ ] `shared_future` and `packaged_task`
- [ ] Waiting with a time limit
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Thread Pools, Coordination and Parallel Algorithms:** [42-pools.html](../interactive/42-pools.html), quiz: [42-pools-quiz.html](../interactive/42-pools-quiz.html) (14 questions).

- [ ] Thread pools and the task queue
- [ ] Sizing a pool and the pool deadlock
- [ ] Work stealing
- [ ] `latch`, `barrier` and `semaphore` (C++20)
- [ ] Cooperative cancellation: `jthread` and `stop_token`
- [ ] Parallel algorithms (C++17)
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Atomics and Compare-and-Swap:** [18-atomics-memory-model.html](../interactive/18-atomics-memory-model.html), quiz: [18-atomics-memory-model-quiz.html](../interactive/18-atomics-memory-model-quiz.html) (14 questions).

- [ ] What an atomic is
- [ ] Compare-and-swap
- [ ] `atomic_flag` and a spinlock
- [ ] The ABA problem
- [ ] Atomics in everyday code
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**The Memory Model: Orders and Happens-Before:** [43-memmodel.html](../interactive/43-memmodel.html), quiz: [43-memmodel-quiz.html](../interactive/43-memmodel-quiz.html) (18 questions).

- [ ] Why the order matters
- [ ] Release and acquire: the one rule to learn
- [ ] The five memory orders
- [ ] Happens-before
- [ ] Ordering patterns that matter
- [ ] Double-checked locking: the classic trap
- [ ] Thread-safe data structures
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
