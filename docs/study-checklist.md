# Study checklist

A step-by-step plan through the lessons, in the order they build on each other. Each stage lists its lessons with their sections and quizzes.

**Want ticks that save?** Use the interactive version: <https://ghaith-hamdi1.github.io/cpp-training/study-checklist.html> (also at [`interactive/study-checklist.html`](../interactive/study-checklist.html)). Its checkboxes are clickable, remember your progress on your device, show a progress bar, and work offline. The boxes below are for reading on GitHub or for editing the file yourself.

- Site: <https://ghaith-hamdi1.github.io/cpp-training/> (works offline after one visit)
- Or open [`interactive/index.html`](../interactive/index.html) from a clone of the repo.
- Time boxes are guides. If a block runs long, finish the quiz and move on.

**How to study every lesson:** read a section, run its visualizer or simulator, predict the output before revealing it, then tick "I understand this section" only when you could explain it aloud. End each lesson with its quiz and retry only the questions you missed. Use the search box in the header when a term comes up. Run code snippets with the "Try in Compiler Explorer" button (add `-pthread` for thread code).

---

## Stage 1: Foundations (about 2.5 hours)

Types, memory, pointers, references, initialization, conversions, and the small types that make interfaces honest.

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

## Stage 2: Objects (about 1.5 hours)

Classes, inheritance, virtual functions, and how objects are laid out in memory.

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

## Stage 3: Ownership and modern C++ (about 2.5 hours)

RAII, exceptions, moving instead of copying, who owns an object, and callables.

**Core Language: RAII & Exceptions:** [03-core-language.html](../interactive/03-core-language.html), quiz: [03-core-language-quiz.html](../interactive/03-core-language-quiz.html) (17 questions).

- [ ] RAII: the central idea
- [ ] Exceptions and stack unwinding
- [ ] RAII everywhere: guards and standard wrappers
- [ ] Exception-safety guarantees and noexcept
- [ ] Exceptions, error codes and optional
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

**Lambdas & Callables:** [15-lambdas.html](../interactive/15-lambdas.html), quiz: [15-lambdas-quiz.html](../interactive/15-lambdas-quiz.html) (13 questions).

- [ ] What a lambda is
- [ ] Captures: by value and by reference (step through; dangling captures)
- [ ] `mutable`, init-capture, generic and recursive lambdas
- [ ] Function pointer, functor, lambda, `std::function`
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

## Stage 4: The library and generic code (about 3.5 hours)

Strings, containers, iterators, algorithms, templates, type traits and concepts, and compile-time computation.

**Strings, Regex & Time:** [08-strings-regex-time.html](../interactive/08-strings-regex-time.html), quiz: [08-strings-regex-time-quiz.html](../interactive/08-strings-regex-time-quiz.html) (23 questions).

- [ ] `std::string` and `std::string_view`
- [ ] Inside `std::string`: SSO and capacity
- [ ] Numbers and text: `from_chars`, `to_chars`, `stoi`
- [ ] Formatting: `std::format` and streams
- [ ] String streams and files
- [ ] Regular expressions: the basics
- [ ] Captures, replace and iterating matches
- [ ] Time with `std::chrono`
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**The STL:** [04-stl.html](../interactive/04-stl.html), quiz: [04-stl-quiz.html](../interactive/04-stl-quiz.html) (29 questions).

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

**Type Traits & Compile-time C++:** [09-compile-time.html](../interactive/09-compile-time.html), quiz: [09-compile-time-quiz.html](../interactive/09-compile-time-quiz.html) (18 questions).

- [ ] Type traits
- [ ] `enable_if` and SFINAE
- [ ] Concepts and `requires` (C++20)
- [ ] `constexpr`, `consteval`, `constinit`
- [ ] Template metaprogramming (TMP)
- [ ] Cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

## Stage 5: Design (about 1.5 hours)

Common patterns in modern C++, with real code.

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

## Stage 6: Concurrency (about 2.5 hours)

Threads, locks, futures, atomics and the memory model.

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

## Stage 7: Performance (about 2 hours)

Binary formats and parsing, and predictable, fast code.

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

- [Effective Modern C++ move semantics path](effective-modern-cpp-reading-guide.md#special-focus-move-semantics-and-perfect-forwarding) (`books/Effective-Modern-Cpp-Meyers.pdf`)
- [C++ Move Semantics reading guide, Tier 1](move-semantics-complete-guide-reading-guide.md#tier-1-read-these-first-about-75-pages) (`books/Cpp-Move-Semantics-The-Complete-Guide-Josuttis.pdf`)

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

## Books: only to fill gaps

Do not read any of these books front to back. Use the reading guides to find the few sections you need:

- Threading: [concurrency-in-action-reading-guide.md](concurrency-in-action-reading-guide.md) (`books/Cpp-Concurrency-in-Action-2nd-Edition-Williams.pdf`; Tier 1 is about 47 pages)
- Foundations (pointers, OOP, templates, STL): [programming-principles-and-practice-reading-guide.md](programming-principles-and-practice-reading-guide.md) (`books/Programming-Principles-and-Practice-Using-Cpp-3rd-Edition-Stroustrup.pdf`)
- Modern C++ items: [effective-modern-cpp-reading-guide.md](effective-modern-cpp-reading-guide.md) (`books/Effective-Modern-Cpp-Meyers.pdf`; Tier 1 is about 85 pages)
- Move semantics in depth: [move-semantics-complete-guide-reading-guide.md](move-semantics-complete-guide-reading-guide.md) (`books/Cpp-Move-Semantics-The-Complete-Guide-Josuttis.pdf`; Tier 1 is about 75 pages)
