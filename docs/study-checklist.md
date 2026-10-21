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

The topic you knew least, and the one the job description names. Lesson: [07-multithreading.html](../interactive/07-multithreading.html), quiz: [07-multithreading-quiz.html](../interactive/07-multithreading-quiz.html) (32 questions).

- [ ] Section 1: Why threads? The mental model
- [ ] Section 2: Your first thread
- [ ] Section 3: Shared data and data races (run the race simulator and "Run 500 random schedules")
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

RAII, move semantics, smart pointers, lambdas, exceptions. Lesson: [03-core-language.html](../interactive/03-core-language.html), quiz: [03-core-language-quiz.html](../interactive/03-core-language-quiz.html) (21 questions).

- [ ] RAII: the central idea (step through the stack unwinding)
- [ ] Lvalues, rvalues and references
- [ ] Move semantics (step through copy versus move)
- [ ] Smart pointers (step through the `shared_ptr` count)
- [ ] Modern syntax tour, then Lambdas
- [ ] Exceptions and exception safety
- [ ] Casts, `const`/`constexpr`/`static`, and what C++14/17/20 added
- [ ] Interview cheat sheet (say each answer aloud)
- [ ] Take the quiz, then retry the missed questions

## Step 3: templates and design patterns (about 1.5 hours)

Both are named in the job description.

**Templates:** [05-templates.html](../interactive/05-templates.html), quiz: [05-templates-quiz.html](../interactive/05-templates-quiz.html) (20 questions).

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
- [ ] Basics and pointers: [lesson](../interactive/01-basics.html), [quiz](../interactive/01-basics-quiz.html) (20 questions)
- [ ] OOP: [lesson](../interactive/02-oop.html), [quiz](../interactive/02-oop-quiz.html) (20 questions)

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

---

## Books: only to fill gaps

Do not read either book front to back. Use the reading guides to find the few sections you need:

- Threading: [concurrency-in-action-reading-guide.md](concurrency-in-action-reading-guide.md) (`thread.pdf`; Tier 1 is about 47 pages)
- Foundations (pointers, OOP, templates, STL): [programming-principles-and-practice-reading-guide.md](programming-principles-and-practice-reading-guide.md) (`P_P_P.pdf`)

## Optional extras, only if you finish early

- [ ] [08-strings-regex-time.html](../interactive/08-strings-regex-time.html) and [quiz](../interactive/08-strings-regex-time-quiz.html) (15 questions)
- [ ] [09-compile-time.html](../interactive/09-compile-time.html) and [quiz](../interactive/09-compile-time-quiz.html) (15 questions)
- [ ] [10-coding-rules.html](../interactive/10-coding-rules.html) and [quiz](../interactive/10-coding-rules-quiz.html) (14 questions)
