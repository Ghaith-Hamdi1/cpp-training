# Study checklist: C++ interview (Thursday, 4 PM)

A step-by-step plan from Wednesday to the interview.

**Want ticks that save?** Use the interactive version: <https://ghaith-hamdi1.github.io/cpp-training/study-checklist.html> (also at [`interactive/study-checklist.html`](../interactive/study-checklist.html)). Its checkboxes are clickable, remember your progress on your device, show a progress bar, and work offline. The boxes below are for reading on GitHub or for editing the file yourself.

- Site: <https://ghaith-hamdi1.github.io/cpp-training/> (works offline after one visit)
- Or open [`interactive/index.html`](../interactive/index.html) from a clone of the repo.
- Time boxes are guides. If a block runs long, finish the quiz and move on.

**How to study every lesson:** read a section, run its visualizer or simulator, predict the output before revealing it, then tick "I understand this section" only when you could explain it aloud. End each lesson with its quiz and retry only the questions you missed. Use the search box in the header when a term comes up. Run code snippets with the "Try in Compiler Explorer" button (add `-pthread` for thread code).

---

## Step 0: set up (2 minutes)

- [ ] Open the site and check that the lessons load.
- [ ] Open **Lesson 11, Multithreading**.

## Step 1: multithreading (about 3 hours)

The topic you knew least, and the one the job description names. Three lessons: the basics, tasks and parallelism, and atomics with the memory model.

**Multithreading:** [07-multithreading.html](../interactive/07-multithreading.html), quiz: [07-multithreading-quiz.html](../interactive/07-multithreading-quiz.html) (28 questions).

- [ ] Why threads? The mental model
- [ ] Your first thread (including the dangling-argument trap and joining on every path)
- [ ] Shared data and data races (invariants; run the race simulator and "Run 500 random schedules")
- [ ] Mutexes: taking turns (run the mutex simulator)
- [ ] Other mutex types and `call_once` (why recursive mutexes are a smell)
- [ ] Races hidden in interfaces (step through the stack example)
- [ ] Deadlock (cause the deadlock yourself, then run the fixed version)
- [ ] Condition variables (step through the hand-over)
- [ ] Optional: debugging and common bugs
- [ ] Take the quiz, then retry the missed questions

**Tasks and parallelism:** [17-tasks-parallelism.html](../interactive/17-tasks-parallelism.html), quiz: [17-tasks-parallelism-quiz.html](../interactive/17-tasks-parallelism-quiz.html) (15 questions).

- [ ] Futures and async
- [ ] `promise`, `shared_future` and `packaged_task`
- [ ] Thread pools and producer/consumer (step through the pool)
- [ ] Work stealing and sizing a pool
- [ ] `latch`, `barrier`, `semaphore` and `stop_token`
- [ ] Parallel algorithms
- [ ] Take the quiz, then retry the missed questions

**Atomics and the memory model:** [18-atomics-memory-model.html](../interactive/18-atomics-memory-model.html), quiz: [18-atomics-memory-model-quiz.html](../interactive/18-atomics-memory-model-quiz.html) (17 questions).

- [ ] Atomic operations and `compare_exchange` (run the atomic simulator)
- [ ] Memory orders and happens-before (use the memory-order simulator)
- [ ] Ordering patterns that matter (publish, refcount, spinlock)
- [ ] Thread-safe data structures (fine-grained locks, lock-free push)
- [ ] Take the quiz, then retry the missed questions

## Step 2: core language and modern C++ (about 3 hours)

Five lessons, each short: RAII and exceptions, move semantics, smart pointers, lambdas, types and casts.

**RAII and exceptions:** [03-core-language.html](../interactive/03-core-language.html), quiz: [03-core-language-quiz.html](../interactive/03-core-language-quiz.html) (17 questions).

- [ ] RAII: the central idea (step through the stack unwinding)
- [ ] RAII everywhere: scope guards and the standard wrappers
- [ ] Exceptions and stack unwinding
- [ ] Exception-safety guarantees and `noexcept`
- [ ] Exceptions, error codes and `optional`
- [ ] Interview cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Move semantics:** [13-move-semantics.html](../interactive/13-move-semantics.html), quiz: [13-move-semantics-quiz.html](../interactive/13-move-semantics-quiz.html) (15 questions).

- [ ] Lvalues, rvalues and the three value categories
- [ ] Copy versus move (step through it; what `std::move` really does)
- [ ] Optional, book: *Effective Modern C++* Items 23, 25 and 29 on `std::move`, `std::forward` and when moves are not cheap (PDF pages 176 to 182, 186 to 195 and 221 to 225, about 22 pages). See the [move semantics path](effective-modern-cpp-reading-guide.md#special-focus-move-semantics-and-perfect-forwarding)
- [ ] Writing move operations: `std::exchange`, `noexcept`, copy-and-swap
- [ ] Returning objects: elision, and why not `return std::move(local)`
- [ ] Sink parameters and the move traps (the `const` trap)
- [ ] Interview cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Smart pointers:** [14-smart-pointers.html](../interactive/14-smart-pointers.html), quiz: [14-smart-pointers-quiz.html](../interactive/14-smart-pointers-quiz.html) (12 questions).

- [ ] Who owns it? The three smart pointers and how to pass them
- [ ] `unique_ptr` in detail (deleters, arrays, zero overhead)
- [ ] `shared_ptr` and the control block (step through the count)
- [ ] Reference cycles and `weak_ptr` (step through the leak)
- [ ] Pitfalls: one control block per object, `enable_shared_from_this`
- [ ] Interview cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Lambdas:** [15-lambdas.html](../interactive/15-lambdas.html), quiz: [15-lambdas-quiz.html](../interactive/15-lambdas-quiz.html) (13 questions).

- [ ] What a lambda is
- [ ] Captures: by value and by reference (step through; dangling captures)
- [ ] `mutable`, init-capture, generic and recursive lambdas
- [ ] Function pointer, functor, lambda, `std::function`
- [ ] Interview cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Types, initialization and casts:** [16-types-and-casts.html](../interactive/16-types-and-casts.html), quiz: [16-types-and-casts-quiz.html](../interactive/16-types-and-casts-quiz.html) (16 questions).

- [ ] Initialization forms and the brace traps
- [ ] `auto`, `decltype` and the modern syntax tour
- [ ] Implicit conversions and `enum class`
- [ ] Casts, `const`/`constexpr`/`static`, and what C++14/17/20 added
- [ ] Interview cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

## Step 3: templates and design patterns (about 1.5 hours)

Both are named in the job description.

**Templates:** [05-templates.html](../interactive/05-templates.html), quiz: [05-templates-quiz.html](../interactive/05-templates-quiz.html) (28 questions).

- [ ] Function templates and class templates
- [ ] Template argument deduction (by value, by reference) and class template argument deduction
- [ ] Forwarding references and perfect forwarding (use the explorer, step through it)
- [ ] Variadic templates and fold expressions (step through the recursion)
- [ ] Type traits, `if constexpr` and concepts
- [ ] Alias templates, variable templates, template template parameters and `std::index_sequence`
- [ ] Interview cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

**Design patterns:** [06-design-patterns.html](../interactive/06-design-patterns.html), quiz: [06-design-patterns-quiz.html](../interactive/06-design-patterns-quiz.html) (20 questions).

- [ ] Singleton (thread-safe version and its drawbacks)
- [ ] Factory
- [ ] Strategy (try the widget)
- [ ] Observer (subscribe and unsubscribe in the demo)
- [ ] State (use the turnstile demo)
- [ ] SOLID principles and the interview cheat sheet
- [ ] Take the quiz, then retry the missed questions

## Step 4: the rest (about 1 hour)

Take each quiz **first**. Only read the lesson sections for questions you miss.

- [ ] STL: [lesson](../interactive/04-stl.html), [quiz](../interactive/04-stl-quiz.html) (29 questions)
- [ ] Basics and pointers: [lesson](../interactive/01-basics.html), [quiz](../interactive/01-basics-quiz.html) (22 questions)
- [ ] OOP: [lesson](../interactive/02-oop.html), [quiz](../interactive/02-oop-quiz.html) (23 questions)

## Step 5: Thursday morning, before the interview

- [ ] Retake every quiz where you scored under 80%.
- [ ] Open each lesson's "Interview cheat sheet" and say every answer aloud before opening it.
- [ ] From memory, write a thread-safe queue (mutex and condition variable).
- [ ] From memory, write a deadlock, then fix it with `std::scoped_lock`.
- [ ] Explain in your own words: data race versus race condition, `mutex` versus `atomic`, why `wait` needs a predicate.
- [ ] **Stop studying about two hours before the interview.** Rest helps more than another cram session.

## Talking points to prepare (about 15 minutes)

The job description mentions production bugs, unit tests and mentoring. Have one short example ready for each from your own experience, in the form situation, what you did, result.

- [ ] A bug you investigated and debugged (what you looked at, the root cause, the fix)
- [ ] How you write unit tests and keep code testable
- [ ] A time you helped or guided a teammate
- [ ] A question or two to ask the interviewers (for example how they test changes, and how the teams across sites collaborate)

## Move semantics deep dive (after the interview)

Not needed for Thursday. When you want to master move semantics, follow the two guides below. The Josuttis book covers what Meyers leaves out: the moved-from state, value categories and writing move operations. About 75 pages of the Josuttis book plus a few Meyers items.

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

## Optional extras, only if you finish early

- [ ] [08-strings-regex-time.html](../interactive/08-strings-regex-time.html) and [quiz](../interactive/08-strings-regex-time-quiz.html) (23 questions)
- [ ] [09-compile-time.html](../interactive/09-compile-time.html) and [quiz](../interactive/09-compile-time-quiz.html) (15 questions)
- [ ] [10-coding-rules.html](../interactive/10-coding-rules.html) and [quiz](../interactive/10-coding-rules-quiz.html) (14 questions)
- [ ] [11-wire-formats.html](../interactive/11-wire-formats.html) and [quiz](../interactive/11-wire-formats-quiz.html) (21 questions)
- [ ] [12-low-latency.html](../interactive/12-low-latency.html) and [quiz](../interactive/12-low-latency-quiz.html) (23 questions)
- [ ] [19-object-model.html](../interactive/19-object-model.html) and [quiz](../interactive/19-object-model-quiz.html) (14 questions): multiple and virtual inheritance, RTTI, private inheritance, copy-and-swap
- [ ] [20-more-patterns.html](../interactive/20-more-patterns.html) and [quiz](../interactive/20-more-patterns-quiz.html) (11 questions): Command, Decorator, Adapter, Builder, Visitor, session state machine
