# cpp-training

Study material for learning C++ and revising it, in three parts: **Lessons** (interactive, with quizzes), **Training notes** (from a company course) and **Recaps** (of [learncpp.com](https://www.learncpp.com/)), plus reading guides for two reference books.

## Start here

| If you want to... | Go to |
|---|---|
| **Learn C++ step by step** | [Lesson 1: basics and pointers](https://ghaith-hamdi1.github.io/cpp-training/01-basics.html), then [types and casts](https://ghaith-hamdi1.github.io/cpp-training/16-types-and-casts.html), [OOP](https://ghaith-hamdi1.github.io/cpp-training/02-oop.html) and [the object model](https://ghaith-hamdi1.github.io/cpp-training/19-object-model.html) |
| **Follow a plan** | The [study checklist](https://ghaith-hamdi1.github.io/cpp-training/study-checklist.html), with clickable boxes that remember your progress |
| **Find one topic** | The [topic map](docs/topic-map.md): where each topic appears in the notes, the recaps and the lessons |
| **Read the source notes** | The [training notes index](docs/training-notes/README.md) |
| **Go deeper with the books** | The [C++ roadmap](docs/reading/roadmap/README.md): eight phases across all five books with exact chapters and time estimates. The reading guides for [C++ Primer](docs/reading/cpp-primer-reading-guide.md), [C++ Concurrency in Action](docs/reading/concurrency-in-action-reading-guide.md), [Programming: Principles and Practice](docs/reading/programming-principles-and-practice-reading-guide.md), [Effective Modern C++](docs/reading/effective-modern-cpp-reading-guide.md) and [C++ Move Semantics](docs/reading/move-semantics-complete-guide-reading-guide.md). For an ordered path through each book, session by session: the reading plans for [C++ Primer](docs/reading/cpp-primer-reading-plan.md), [Programming: Principles and Practice](docs/reading/programming-principles-and-practice-reading-plan.md), [Effective Modern C++](docs/reading/effective-modern-cpp-reading-plan.md), [C++ Concurrency in Action](docs/reading/concurrency-in-action-reading-plan.md) and [C++ Move Semantics](docs/reading/move-semantics-reading-plan.md) |

The lessons work offline after one visit. From a clone you can also open [`interactive/index.html`](interactive/index.html) directly; no install is needed.

## What is in this repo

| Path | What it is |
|---|---|
| [`interactive/`](interactive/index.html) | The **Lessons**: interactive lessons with quizzes, published with GitHub Pages. Plain HTML, CSS and JavaScript, with no build step. |
| [`docs/`](docs/README.md) | Everything written: the [roadmap and reading guides](docs/reading/roadmap/README.md), the [training notes](docs/training-notes/README.md) (a company course in four modules), the [learncpp.com recaps](docs/learncpp-recaps/README.md), the topic map, the study checklist and the [maintainer docs](docs/maintaining). |
| [`examples/lessons/`](examples/lessons/README.md) | **Runnable programs** for the main lesson snippets: complete, compiled and checked with g++ (`make` builds them all). |
| [`examples/course/`](examples/course) | The **course code**: the programs that go with the four training-notes modules. |
| [`examples/practice/`](examples/practice/README.md) | **Practice set**: 17 write-it-yourself coding exercises (C strings, pointers, a String class, templates, threads, vocabulary types, concepts) with tests and verified solutions, plus model answers to the questions they raise. |
| [`tools/`](tools) | Scripts that check the interactive site: links, quiz data, the search index and the offline cache list. |
| [`books/`](books) | Five reference books as PDFs, named by title: *C++ Primer*, 5th ed. (Lippman, Lajoie and Moo), *C++ Concurrency in Action* (Williams), *Programming: Principles and Practice Using C++* (Stroustrup), *Effective Modern C++* (Meyers) and *C++ Move Semantics: The Complete Guide* (Josuttis). Each has a reading guide and a reading plan in `docs/reading/`. |

## The lessons

Each lesson has step-through memory visualizers or simulators, predict-the-output exercises, a cheat sheet and a quiz. Start at [`interactive/index.html`](interactive/index.html).

| # | Lesson | Quiz |
|---|---|---|
| 1 | [C++ Basics and Pointers](https://ghaith-hamdi1.github.io/cpp-training/01-basics.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/01-basics-quiz.html) |
| 2 | [Types, Initialization and Casts](https://ghaith-hamdi1.github.io/cpp-training/16-types-and-casts.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/16-types-and-casts-quiz.html) |
| 3 | [Vocabulary Types](https://ghaith-hamdi1.github.io/cpp-training/21-vocabulary-types.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/21-vocabulary-types-quiz.html) |
| 4 | [Object-Oriented Programming](https://ghaith-hamdi1.github.io/cpp-training/02-oop.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/02-oop-quiz.html) |
| 5 | [The Object Model in Depth](https://ghaith-hamdi1.github.io/cpp-training/19-object-model.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/19-object-model-quiz.html) |
| 6 | [Core Language: RAII and Exceptions](https://ghaith-hamdi1.github.io/cpp-training/03-core-language.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/03-core-language-quiz.html) |
| 7 | [Move Semantics](https://ghaith-hamdi1.github.io/cpp-training/13-move-semantics.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/13-move-semantics-quiz.html) |
| 8 | [Smart Pointers and Ownership](https://ghaith-hamdi1.github.io/cpp-training/14-smart-pointers.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/14-smart-pointers-quiz.html) |
| 9 | [Lambdas and Callables](https://ghaith-hamdi1.github.io/cpp-training/15-lambdas.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/15-lambdas-quiz.html) |
| 10 | [Strings, Regex and Time](https://ghaith-hamdi1.github.io/cpp-training/08-strings-regex-time.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/08-strings-regex-time-quiz.html) |
| 11 | [The STL](https://ghaith-hamdi1.github.io/cpp-training/04-stl.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/04-stl-quiz.html) |
| 12 | [Templates](https://ghaith-hamdi1.github.io/cpp-training/05-templates.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/05-templates-quiz.html) |
| 13 | [Type Traits and Compile-time C++](https://ghaith-hamdi1.github.io/cpp-training/09-compile-time.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/09-compile-time-quiz.html) |
| 14 | [Design Patterns](https://ghaith-hamdi1.github.io/cpp-training/06-design-patterns.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/06-design-patterns-quiz.html) |
| 15 | [More Patterns](https://ghaith-hamdi1.github.io/cpp-training/20-more-patterns.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/20-more-patterns-quiz.html) |
| 16 | [Multithreading](https://ghaith-hamdi1.github.io/cpp-training/07-multithreading.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/07-multithreading-quiz.html) |
| 17 | [Tasks and Parallelism](https://ghaith-hamdi1.github.io/cpp-training/17-tasks-parallelism.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/17-tasks-parallelism-quiz.html) |
| 18 | [Atomics and the Memory Model](https://ghaith-hamdi1.github.io/cpp-training/18-atomics-memory-model.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/18-atomics-memory-model-quiz.html) |
| 19 | [Binary Data and Parsing](https://ghaith-hamdi1.github.io/cpp-training/11-wire-formats.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/11-wire-formats-quiz.html) |
| 20 | [Performance and Memory](https://ghaith-hamdi1.github.io/cpp-training/12-low-latency.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/12-low-latency-quiz.html) |

Besides the lessons, the site has a [C++ Puzzles](https://ghaith-hamdi1.github.io/cpp-training/puzzles.html) page: 163 "what does this program print?" questions from CppQuiz.org, each with an explanation that quotes the standard (see [third-party content](#third-party-content)).

**Working on the site.** After you change anything in `interactive/`, regenerate the derived files and run the checks (the same checks run in CI):

```bash
node tools/build-search-index.mjs   # rebuilds the lesson search index
node tools/build-mock-bank.mjs      # rebuilds the mock questions
node tools/build-precache.mjs       # rebuilds the offline cache list in sw.js
node tools/check-interactive.mjs    # registry, quiz data and section tags
node tools/check-links.mjs          # every internal link and anchor
node tools/check-quiz-balance.mjs   # no quiz can be answered by option length
node tools/build-read-more.mjs      # rebuilds the "Read more" notes in the lessons from the reading guides
node tools/build-checklist.mjs     # rebuilds the study checklist from the lesson sections
node tools/verify-checklist.mjs     # study checklist against the lessons
node tools/check-guides.mjs         # reading guides against the lessons
node tools/test-registry.mjs        # progress migrations
```

## Further reading

### Books to read next

After the two books in this repo (see their reading guides above), these are the ones I would read next, in this order, for a C++ role that involves modern C++, templates, design patterns and multithreaded or low-latency code. They are copyrighted, so none are included here. Check current editions before buying.

| # | Book | Why read it | Lessons |
|---|---|---|---|
| 1 | **Effective Modern C++**, Scott Meyers ([reading guide](docs/reading/effective-modern-cpp-reading-guide.md)) | Short, self-contained items on move semantics, smart pointers, lambdas, `auto`, forwarding references and a concurrency chapter (C++11/14). The most practical book on the list. | 2, 6 to 9, 12, 16, 17 |
| 2 | **[C++ Move Semantics: The Complete Guide](https://leanpub.com/cppmove)**, Nicolai Josuttis ([reading guide](docs/reading/move-semantics-complete-guide-reading-guide.md)) | A whole book on one topic (about 260 pages, 2020): `std::move`, rvalue references, moved-from states, value categories, `std::forward`, forwarding references and `decltype(auto)`. The deepest treatment of move semantics. | 4, 7, 8, 12 |
| 3 | **A Tour of C++**, Bjarne Stroustrup | A short whole-language overview by the language's creator, including the C++20 features (concepts, ranges, modules, coroutines). | 2, 7, 9, 11, 12 |
| 4 | **C++ Templates: The Complete Guide**, Vandevoorde, Josuttis and Gregor | The definitive templates book: variadic templates, forwarding, type traits, SFINAE and `if constexpr`. Large, so use it as a reference. | 12, 13 |
| 5 | **Hands-On Design Patterns with C++**, Fedor Pikus | Design patterns in modern C++, including templates, concurrency and performance. | 14, 15 |
| 6 | **C++ High Performance**, Björn Andrist and Viktor Sehr | Performance, STL algorithms, memory and concurrency, relevant to real-time and low-latency work. | 11, 16, 18, 20 |
| 7 | **The Art of Multiprocessor Programming**, Maurice Herlihy and Nir Shavit | The theory behind locks, lock-free structures and memory models. Heavy and academic; read it only if lock-free work interests you. | 18 |

"Lessons" refers to the [lessons](#the-lessons) above.

### Online

- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines): the rules from Stroustrup and Sutter, a good companion to the lessons on OOP, RAII and resource management.
- [cppreference.com](https://en.cppreference.com/): the standard reference for language and library details.
- [modern-cpp-tutorial](https://github.com/changkun/modern-cpp-tutorial): book-style tutorial on C++11/14/17/20 that explains why modern features exist.
- [modern-cpp-features](https://github.com/AnthonyCalandra/modern-cpp-features): cheat sheet with a short snippet per feature, C++11 through C++23.

## Third-party content

The questions on the C++ Puzzles page (`interactive/assets/data/puzzles.js`) come from [CppQuiz.org](https://cppquiz.org) by Anders Schau Knatten and contributors, and are licensed under [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/). The text is unchanged; it was reformatted into one data file by `tools/import-cppquiz.mjs` from the public [cppquiz23](https://github.com/knatten/cppquiz23) repository. That data file stays under CC BY-SA 4.0 and carries its own attribution header.
