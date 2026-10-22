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
- [ ] Open **Lesson 7, Multithreading**.

## Step 1: multithreading (about 2 hours)

The topic you knew least, and the one the job description names. Lesson: [07-multithreading.html](../interactive/07-multithreading.html), quiz: [07-multithreading-quiz.html](../interactive/07-multithreading-quiz.html) (34 questions).

- [ ] Section 1: Why threads? The mental model
- [ ] Section 2: Your first thread (including the dangling-argument trap and joining on every path)
- [ ] Section 3: Shared data and data races (invariants; run the race simulator and "Run 500 random schedules")
- [ ] Section 4: Mutexes: taking turns (run the mutex simulator)
- [ ] Section 5: Races hidden in interfaces (step through the stack example)
- [ ] Section 6: Deadlock (cause the deadlock yourself, then run the fixed version)
- [ ] Section 7: Atomics
- [ ] Section 8: Condition variables (step through the hand-over)
- [ ] Section 9: Futures and async
- [ ] Section 10: Thread pools and producer/consumer
- [ ] Optional: sections 11 and 12 (performance, debugging and common bugs)
- [ ] Take the quiz, then retry the missed questions

## Step 2: core language (about 1.5 hours)

RAII, move semantics, smart pointers, lambdas, exceptions. Lesson: [03-core-language.html](../interactive/03-core-language.html), quiz: [03-core-language-quiz.html](../interactive/03-core-language-quiz.html) (24 questions).

- [ ] RAII: the central idea (step through the stack unwinding)
- [ ] Lvalues, rvalues and references (including the three value categories)
- [ ] Move semantics (step through copy versus move; the `const` trap and the by-value-then-move idiom)
- [ ] Optional, book: *Effective Modern C++* Items 23, 25 and 29 on `std::move`, `std::forward` and when moves are not cheap (PDF pages 176 to 182, 186 to 195 and 221 to 225, about 22 pages). See the [move semantics path](effective-modern-cpp-reading-guide.md#special-focus-move-semantics-and-perfect-forwarding)
- [ ] Smart pointers (step through the `shared_ptr` count; one control block per object)
- [ ] Modern syntax tour, then Lambdas
- [ ] Exceptions and exception safety
- [ ] Casts, `const`/`constexpr`/`static`, and what C++14/17/20 added
- [ ] Interview cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

## Step 3: templates and design patterns (about 1.5 hours)

Both are named in the job description.

**Templates:** [05-templates.html](../interactive/05-templates.html), quiz: [05-templates-quiz.html](../interactive/05-templates-quiz.html) (19 questions).

- [ ] Function templates and class templates
- [ ] Deduction and forwarding references (use the explorer), then perfect forwarding
- [ ] Variadic templates and fold expressions (step through the recursion)
- [ ] Type traits, `if constexpr` and concepts
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

- [ ] STL: [lesson](../interactive/04-stl.html), [quiz](../interactive/04-stl-quiz.html) (21 questions)
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

- [Effective Modern C++ move semantics path](effective-modern-cpp-reading-guide.md#special-focus-move-semantics-and-perfect-forwarding) (`effective.pdf`)
- [C++ Move Semantics reading guide, Tier 1](move-semantics-complete-guide-reading-guide.md#tier-1-read-these-first-about-75-pages) (`semant.pdf`)

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

- Threading: [concurrency-in-action-reading-guide.md](concurrency-in-action-reading-guide.md) (`thread.pdf`; Tier 1 is about 47 pages)
- Foundations (pointers, OOP, templates, STL): [programming-principles-and-practice-reading-guide.md](programming-principles-and-practice-reading-guide.md) (`P_P_P.pdf`)
- Modern C++ items: [effective-modern-cpp-reading-guide.md](effective-modern-cpp-reading-guide.md) (`effective.pdf`; Tier 1 is about 85 pages)
- Move semantics in depth: [move-semantics-complete-guide-reading-guide.md](move-semantics-complete-guide-reading-guide.md) (`semant.pdf`; Tier 1 is about 75 pages)

## Optional extras, only if you finish early

- [ ] [08-strings-regex-time.html](../interactive/08-strings-regex-time.html) and [quiz](../interactive/08-strings-regex-time-quiz.html) (15 questions)
- [ ] [09-compile-time.html](../interactive/09-compile-time.html) and [quiz](../interactive/09-compile-time-quiz.html) (15 questions)
- [ ] [10-coding-rules.html](../interactive/10-coding-rules.html) and [quiz](../interactive/10-coding-rules-quiz.html) (14 questions)
- [ ] [11-wire-formats.html](../interactive/11-wire-formats.html) and [quiz](../interactive/11-wire-formats-quiz.html) (21 questions)
- [ ] [12-low-latency.html](../interactive/12-low-latency.html) and [quiz](../interactive/12-low-latency-quiz.html) (23 questions)
