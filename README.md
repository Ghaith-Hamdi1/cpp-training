# cpp-training

Study material for learning C++ and preparing for C++ interviews, in three parts: **Lessons** (interactive, with quizzes), **Training notes** (from a company course) and **Recaps** (of [learncpp.com](https://www.learncpp.com/)), plus reading guides for two reference books.

## Start here

| If you want to... | Go to |
|---|---|
| **Learn C++ step by step** | [Lesson 1: basics and pointers](https://ghaith-hamdi1.github.io/cpp-training/01-basics.html), then [OOP](https://ghaith-hamdi1.github.io/cpp-training/02-oop.html) and [core language](https://ghaith-hamdi1.github.io/cpp-training/03-core-language.html) |
| **Prepare for an interview** | The [study checklist](https://ghaith-hamdi1.github.io/cpp-training/study-checklist.html), with clickable boxes that remember your progress |
| **Find one topic** | The [topic map](docs/topic-map.md): where each topic appears in the notes, the recaps and the lessons |
| **Read the source notes** | The [training notes index](docs/README.md) |
| **Go deeper with the books** | The reading guides for [C++ Concurrency in Action](docs/concurrency-in-action-reading-guide.md) and [Programming: Principles and Practice](docs/programming-principles-and-practice-reading-guide.md) |

The lessons work offline after one visit. From a clone you can also open [`interactive/index.html`](interactive/index.html) directly; no install is needed.

## What is in this repo

| Path | What it is |
|---|---|
| [`interactive/`](interactive/index.html) | The **Lessons**: ten interactive lessons with quizzes, published with GitHub Pages. Plain HTML, CSS and JavaScript, with no build step. |
| [`docs/`](docs/README.md) and [`examples/`](examples/) | The **Training notes**: a company course as concise, slide-style Markdown (four modules) with matching source code. The docs folder also holds the topic map, the reading guides and the study checklist. |
| [`LearnCPP/`](LearnCPP/Recaps/README.md) | The **Recaps**: personal recaps of the learncpp.com chapters, with solved exercises under [`LearnCPP/Recaps/solutions/`](LearnCPP/Recaps/solutions/). Slower and more thorough than the training notes. |
| [`tools/`](tools/) | Scripts that check the interactive site: links, quiz data, the search index and the offline cache list. |
| `thread.pdf`, `P_P_P.pdf` | Two reference books: *C++ Concurrency in Action* (Anthony Williams) and *Programming: Principles and Practice Using C++* (Bjarne Stroustrup). |

## The lessons

Each lesson has step-through memory visualizers or simulators, predict-the-output exercises, an interview cheat sheet and a quiz. Start at [`interactive/index.html`](interactive/index.html).

| # | Lesson | Quiz |
|---|---|---|
| 1 | [C++ Basics and Pointers](https://ghaith-hamdi1.github.io/cpp-training/01-basics.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/01-basics-quiz.html) |
| 2 | [Object-Oriented Programming](https://ghaith-hamdi1.github.io/cpp-training/02-oop.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/02-oop-quiz.html) |
| 3 | [Core Language and Modern C++](https://ghaith-hamdi1.github.io/cpp-training/03-core-language.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/03-core-language-quiz.html) |
| 4 | [The STL](https://ghaith-hamdi1.github.io/cpp-training/04-stl.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/04-stl-quiz.html) |
| 5 | [Templates](https://ghaith-hamdi1.github.io/cpp-training/05-templates.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/05-templates-quiz.html) |
| 6 | [Design Patterns](https://ghaith-hamdi1.github.io/cpp-training/06-design-patterns.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/06-design-patterns-quiz.html) |
| 7 | [Multithreading](https://ghaith-hamdi1.github.io/cpp-training/07-multithreading.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/07-multithreading-quiz.html) |
| 8 | [Strings, Regex and Time](https://ghaith-hamdi1.github.io/cpp-training/08-strings-regex-time.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/08-strings-regex-time-quiz.html) |
| 9 | [Type Traits and Compile-time C++](https://ghaith-hamdi1.github.io/cpp-training/09-compile-time.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/09-compile-time-quiz.html) |
| 10 | [Coding Rules and Safe C++](https://ghaith-hamdi1.github.io/cpp-training/10-coding-rules.html) | [Quiz](https://ghaith-hamdi1.github.io/cpp-training/10-coding-rules-quiz.html) |

**Working on the site.** After you change anything in `interactive/`, regenerate the derived files and run the checks (the same checks run in CI):

```bash
node tools/build-search-index.mjs   # rebuilds the lesson search index
node tools/build-precache.mjs       # rebuilds the offline cache list in sw.js
node tools/check-interactive.mjs    # checks links and quiz data
```

## Further reading

- [modern-cpp-tutorial](https://github.com/changkun/modern-cpp-tutorial): book-style tutorial on C++11/14/17/20 that explains why modern features exist.
- [modern-cpp-features](https://github.com/AnthonyCalandra/modern-cpp-features): cheat sheet with a short snippet per feature, C++11 through C++23.
