# cpp-training

Study material for learning C++ and preparing for C++ interviews, in three parts: **Lessons** (interactive, with quizzes), **Training notes** (from a company course) and **Recaps** (of [learncpp.com](https://www.learncpp.com/)), plus reading guides for two reference books.

## Start here

| If you want to... | Go to |
|---|---|
| **Learn C++ step by step** | [Lesson 1: basics and pointers](https://ghaith-hamdi1.github.io/cpp-training/01-basics.html), then [OOP](https://ghaith-hamdi1.github.io/cpp-training/02-oop.html), [core language](https://ghaith-hamdi1.github.io/cpp-training/03-core-language.html) and [move semantics](https://ghaith-hamdi1.github.io/cpp-training/13-move-semantics.html) |
| **Prepare for an interview** | The [study checklist](https://ghaith-hamdi1.github.io/cpp-training/study-checklist.html), with clickable boxes that remember your progress |
| **Find one topic** | The [topic map](docs/topic-map.md): where each topic appears in the notes, the recaps and the lessons |
| **Read the source notes** | The [training notes index](docs/README.md) |
| **Go deeper with the books** | The reading guides for [C++ Concurrency in Action](docs/concurrency-in-action-reading-guide.md), [Programming: Principles and Practice](docs/programming-principles-and-practice-reading-guide.md), [Effective Modern C++](docs/effective-modern-cpp-reading-guide.md) and [C++ Move Semantics](docs/move-semantics-complete-guide-reading-guide.md) |

The lessons work offline after one visit. From a clone you can also open [`interactive/index.html`](interactive/index.html) directly; no install is needed.

## What is in this repo

| Path | What it is |
|---|---|
| [`interactive/`](interactive/index.html) | The **Lessons**: interactive lessons with quizzes, published with GitHub Pages. Plain HTML, CSS and JavaScript, with no build step. |
| [`docs/`](docs/README.md) and [`examples/`](examples/) | The **Training notes**: a company course as concise, slide-style Markdown (four modules) with matching source code. The docs folder also holds the topic map, the reading guides and the study checklist. |
| [`examples/lessons/`](examples/lessons/README.md) | **Runnable programs** for the main lesson snippets: complete, compiled and checked with g++ (`make` builds them all). |
| [`LearnCPP/`](LearnCPP/Recaps/README.md) | The **Recaps**: personal recaps of the learncpp.com chapters, with solved exercises under [`LearnCPP/Recaps/solutions/`](LearnCPP/Recaps/solutions/). Slower and more thorough than the training notes. |
| [`tools/`](tools/) | Scripts that check the interactive site: links, quiz data, the search index and the offline cache list. |
| `thread.pdf`, `P_P_P.pdf` | Two reference books: *C++ Concurrency in Action* (Anthony Williams) and *Programming: Principles and Practice Using C++* (Bjarne Stroustrup). |

## The lessons

Each lesson has step-through memory visualizers or simulators, predict-the-output exercises, an interview cheat sheet and a quiz. Start at [`interactive/index.html`](interactive/index.html).

| # | Lesson | Quiz |
|---|---|---|
| 1 | [C++ Basics and Pointers](https://ghaith-hamdi1.github.io/cpp-training/01-basics.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/01-basics-quiz.html) |
| 2 | [Object-Oriented Programming](https://ghaith-hamdi1.github.io/cpp-training/02-oop.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/02-oop-quiz.html) |
| 3 | [Core Language: RAII and Exceptions](https://ghaith-hamdi1.github.io/cpp-training/03-core-language.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/03-core-language-quiz.html) |
| 4 | [Move Semantics](https://ghaith-hamdi1.github.io/cpp-training/13-move-semantics.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/13-move-semantics-quiz.html) |
| 5 | [Smart Pointers and Ownership](https://ghaith-hamdi1.github.io/cpp-training/14-smart-pointers.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/14-smart-pointers-quiz.html) |
| 6 | [Lambdas and Callables](https://ghaith-hamdi1.github.io/cpp-training/15-lambdas.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/15-lambdas-quiz.html) |
| 7 | [Types, Initialization and Casts](https://ghaith-hamdi1.github.io/cpp-training/16-types-and-casts.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/16-types-and-casts-quiz.html) |
| 8 | [The STL](https://ghaith-hamdi1.github.io/cpp-training/04-stl.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/04-stl-quiz.html) |
| 9 | [Templates](https://ghaith-hamdi1.github.io/cpp-training/05-templates.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/05-templates-quiz.html) |
| 10 | [Design Patterns](https://ghaith-hamdi1.github.io/cpp-training/06-design-patterns.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/06-design-patterns-quiz.html) |
| 11 | [Multithreading](https://ghaith-hamdi1.github.io/cpp-training/07-multithreading.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/07-multithreading-quiz.html) |
| 12 | [Tasks and Parallelism](https://ghaith-hamdi1.github.io/cpp-training/17-tasks-parallelism.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/17-tasks-parallelism-quiz.html) |
| 13 | [Atomics and the Memory Model](https://ghaith-hamdi1.github.io/cpp-training/18-atomics-memory-model.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/18-atomics-memory-model-quiz.html) |
| 14 | [Strings, Regex and Time](https://ghaith-hamdi1.github.io/cpp-training/08-strings-regex-time.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/08-strings-regex-time-quiz.html) |
| 15 | [Type Traits and Compile-time C++](https://ghaith-hamdi1.github.io/cpp-training/09-compile-time.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/09-compile-time-quiz.html) |
| 16 | [Coding Rules and Safe C++](https://ghaith-hamdi1.github.io/cpp-training/10-coding-rules.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/10-coding-rules-quiz.html) |
| 17 | [Wire Formats and Parsing](https://ghaith-hamdi1.github.io/cpp-training/11-wire-formats.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/11-wire-formats-quiz.html) |
| 18 | [Low-Latency C++](https://ghaith-hamdi1.github.io/cpp-training/12-low-latency.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/12-low-latency-quiz.html) |

**Working on the site.** After you change anything in `interactive/`, regenerate the derived files and run the checks (the same checks run in CI):

```bash
node tools/build-search-index.mjs   # rebuilds the lesson search index
node tools/build-precache.mjs       # rebuilds the offline cache list in sw.js
node tools/check-interactive.mjs    # checks links and quiz data
```

## Further reading

### Books to read next

After the two books in this repo (see their reading guides above), these are the ones I would read next, in this order, for a C++ role that involves modern C++, templates, design patterns and multithreaded or low-latency code. They are copyrighted, so none are included here. Check current editions before buying.

| # | Book | Why read it | Lessons |
|---|---|---|---|
| 1 | **Effective Modern C++**, Scott Meyers ([reading guide](docs/effective-modern-cpp-reading-guide.md)) | Short, self-contained items on move semantics, smart pointers, lambdas, `auto`, forwarding references and a concurrency chapter (C++11/14). The best interview-style book on the list. | 3, 5, 7 |
| 2 | **[C++ Move Semantics: The Complete Guide](https://leanpub.com/cppmove)**, Nicolai Josuttis ([reading guide](docs/move-semantics-complete-guide-reading-guide.md)) | A whole book on one topic (about 260 pages, 2020): `std::move`, rvalue references, moved-from states, value categories, `std::forward`, forwarding references and `decltype(auto)`. The deepest treatment of move semantics. | 2, 3, 5 |
| 3 | **A Tour of C++**, Bjarne Stroustrup | A short whole-language overview by the language's creator, including the C++20 features (concepts, ranges, modules, coroutines). | 3, 4, 5 |
| 4 | **C++ Templates: The Complete Guide**, Vandevoorde, Josuttis and Gregor | The definitive templates book: variadic templates, forwarding, type traits, SFINAE and `if constexpr`. Large, so use it as a reference. | 5, 9 |
| 5 | **Hands-On Design Patterns with C++**, Fedor Pikus | Design patterns in modern C++, including templates, concurrency and performance. | 6 |
| 6 | **C++ High Performance**, Björn Andrist and Viktor Sehr | Performance, STL algorithms, memory and concurrency, relevant to real-time and low-latency work. | 4, 7 |
| 7 | **The Art of Multiprocessor Programming**, Maurice Herlihy and Nir Shavit | The theory behind locks, lock-free structures and memory models. Heavy and academic; read it only if lock-free work interests you. | 7 |

"Lessons" refers to the [lessons](#the-lessons) above.

### Online

- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines): the rules from Stroustrup and Sutter, a good companion to lesson 16 on coding rules.
- [cppreference.com](https://en.cppreference.com/): the standard reference for language and library details.
- [modern-cpp-tutorial](https://github.com/changkun/modern-cpp-tutorial): book-style tutorial on C++11/14/17/20 that explains why modern features exist.
- [modern-cpp-features](https://github.com/AnthonyCalandra/modern-cpp-features): cheat sheet with a short snippet per feature, C++11 through C++23.
