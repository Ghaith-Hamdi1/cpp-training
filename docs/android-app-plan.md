# Android app: full curriculum plan

The Android app (`android-quiz/`, Kotlin and Jetpack Compose) started as one chapter on `virtual`. This plan turns it into a Mimo-style course that covers all of C++ as the repo teaches it, basics first.

## Where it stands

| Done | |
|---|---|
| Learn tab | Zigzag path of lesson nodes, sticky chapter header, locked "Coming soon" chapters |
| Lesson flow | Info slides, quiz questions, tap-to-build code exercises, feedback card, quit sheet, retry of missed questions, lesson-complete and chapter-complete screens |
| Practice tab | Daily review from missed questions, replay of finished lessons, stats |
| Profile tab | XP, streak, lessons done, reset |
| Content | One chapter: "OOP: virtual functions", 5 lessons, 35 hand-written questions and 5 build exercises, written for the app |

The questions and lessons are hand-written Kotlin (`Questions.kt`, `Content.kt`, `Builds.kt`). That does not scale to 37 lessons, so the first job is to feed the app from the repo's existing content.

## What the repo already has

| Asset | Size | Where |
|---|---|---|
| Lessons, in study order | 37 | `interactive/assets/data/lessons.js` (id, phase, title, time) |
| Multiple-choice questions | 509 (59 with code) | `quiz-<id>.js`, each with `sec` (lesson section), options, answer, `why` |
| Recap flashcards (the cheat sheets) | 198 across the 37 lessons | `mock-bank.js` |
| "Read more" book pointers | one per section | `read-more.js` |
| Level-check questions | 2 per lesson | `assess` field in `lessons.js` |
| Puzzles (guess the output) | 163 | `puzzles.js`, from CppQuiz.org, **CC BY-SA 4.0** |

## Chapter structure

One chapter per theme, in the repo's study order. This is also the basics-first order.

| # | Chapter | Repo lessons | Quiz questions |
|---|---|---|---|
| 1 | Core language foundations | 1 basics, 2 pointers, 3 types, 4 casts | 59 |
| 2 | Classes, memory and OOP | 5 classes, 6 copy control, 7 inheritance and virtual | 44, plus the 35 hand-written virtual questions |
| 3 | Standard library and generic programming | 8 callables, 9 lambdas, 10 STL, 11 maps and sets, 12 iterators, 13 algorithms, 14 function templates, 15 class templates, 16 compile-time C++ | 129 |
| 4 | RAII, exceptions and advanced tools | 17 RAII and exceptions | 15 (thin, see risks) |
| 5 | Modern C++ | 18 optional/variant/expected, 19 to 24 move semantics and forwarding, 25 to 27 smart pointers | 116 |
| 6 | Concurrency and the memory model | 28 to 36 threads, races, mutexes, deadlock, condition variables, futures, pools, atomics, memory model | 123 |
| 7 | Further reading (optional) | 37 strings, regex, time | 23 |

The 509 questions add up from the per-lesson counts above.

### From repo lessons to path nodes

- A path node holds 5 to 8 items, like Mimo. A lesson with 14 or more questions splits into two nodes by its `sec` values, so about 60 nodes in total.
- Each node starts with 1 or 2 info slides built from that section's recap cards, then its questions, then a build exercise where the topic suits one.
- The end of each chapter gets a "boss" node of 5 puzzles, picked by difficulty from the CppQuiz set.
- Chapter 2 keeps the hand-written virtual deep-dive as its last five nodes. The repo's inheritance quiz is used in the node before it, with overlapping questions dropped.
- Chapters unlock in order. Lessons inside a chapter unlock in order. A placement test (below) can unlock ahead.

## Content pipeline

The repo stays the single source of truth. The app reads generated files, so a quiz fix on the website also fixes the app.

1. **`tools/export-android-content.mjs`** runs the same `vm` loading the other tools use, and writes `android-quiz/app/src/main/assets/content/*.json`: chapters, lessons, nodes, questions, cards, puzzles, read-more.
2. **Question ids** become stable strings, `<lessonId>:<index>`, so saved progress survives edits to other lessons. Build exercises use `<lessonId>:b<index>`.
3. **Mapping:** a question with `code` becomes a "guess the output" question, one without becomes a concept question. `opts` and `a` carry over. `why` becomes the explanation. Recap card answers are HTML, so the exporter converts them to the app's small markup (bold and inline code) and drops anything it cannot express.
4. **Lint in the exporter:** fail the export when a code line is longer than about 34 characters (the app has no sideways scroll), when HTML is left over, or when the right answer is the longest option (reuse `tools/check-quiz-balance.mjs`).
5. The app parses the JSON with `org.json` at start-up. About 500 questions is a few hundred KB, so there is no database and no new dependency.
6. The hand-written `Questions.kt`, `Content.kt` and `Builds.kt` move into a `virtual-deep-dive.json` file in the same format, so there is one code path.

## New question types to author

The imported questions are mostly concept multiple-choice (450 of 509). The `virtual` chapter works because it mixes types, so each chapter gets the same mix.

| Type | Source | Target per chapter |
|---|---|---|
| Concept multiple choice | Imported | All 509 |
| Guess the output | Imported code questions, plus CppQuiz puzzles tagged to the chapter | 6 to 10 |
| Spot the bug | New, written by hand | 3 to 5 |
| True / False | New, short | 4 to 6 |
| Tap-to-build code | New | 1 per node, about 60 in total |

That is roughly 20 new questions per chapter, about 140 in total, and about 55 more build exercises. Authoring is the largest cost in the plan. Write them in the same file format as the imports, so they are reviewable in the repo.

## App features still to build

| Feature | What it is | Size |
|---|---|---|
| Data-driven path | Many chapters with the sticky header per chapter, locked states, progress per node, store keyed by lesson id (migrates the current "lessons done" set) | M |
| Placement test | 2 questions per lesson from the `assess` field (74 total), unlock chapters up to what you already know | M |
| Spaced-repetition review | Daily review of recap cards in Leitner boxes (1, 3, 7, 14, 30 days) like the website's `today.html`, mixed with missed questions | M |
| Go-deeper cards | After a lesson, point to the book chapters for the sections you missed (from `read-more.js`) | S |
| Chapter boss | 5 puzzles by difficulty at the end of each chapter | S |
| Daily goal and streak ring | A goal such as one lesson per day, shown on the Learn tab | S |
| Hints | A hint on hard output questions that reveals one line of reasoning | S |
| Interview mode | Mock-interview cards: read the question, answer aloud, self-grade | M |
| Reminder notification | Optional daily reminder | S |
| Attribution screen | Required for the CppQuiz puzzles (see licensing) | S |

Skipped on purpose: leaderboard and leagues (nothing to rank against without a backend) and a code playground (needs a compiler service).

## Milestones

Each milestone ends with an installable APK and a working app. The order follows the chapters.

| # | Milestone | Contents |
|---|---|---|
| M1 | Pipeline and chapters 1 and 2 | Exporter and lint, data-driven path, store migration, chapter 1 and 2 nodes, the virtual deep-dive in the new format |
| M2 | Chapter 3 | The largest chapter (129 questions), plus build exercises for templates and lambdas, and the spaced-repetition review |
| M3 | Chapters 4 and 5 | Author new RAII and exceptions content, move semantics and smart pointer nodes, go-deeper cards |
| M4 | Chapters 6 and 7 | Concurrency nodes, boss nodes for every chapter, attribution screen |
| M5 | Polish | Placement test, daily goal and streak ring, hints, interview mode, reminder |

## Risks and decisions

- **Chapter 4 is thin.** One lesson and 15 questions cover RAII and exceptions. It needs new material (exception safety, `noexcept`, stack unwinding, scope guards) or it should merge into chapter 2 or 5.
- **Licensing.** The puzzle file stays under CC BY-SA 4.0. The app has to show attribution, and anything derived from those puzzles has to carry the same licence. Keep the puzzles in their own JSON file so the licence boundary is clear.
- **HTML to markup.** The recap answers contain rich HTML (lists, tables, figures). Plain text slides lose some of that, so the exporter should drop complex answers rather than show broken text.
- **Code width.** The earlier fix (short lines, wrapped text) holds only if the lint enforces it for 500 imported questions.
- **Question quality.** Imported questions were written for a website with the lesson open beside them. Some may need rewording to stand alone on a phone.
- **Progress migration.** Today's store keeps lesson numbers as a set of indexes. The data-driven path needs lesson ids, so M1 must convert existing progress once.
- **Testing.** Unit-test the exporter (counts per lesson must match the 509, 198 and 163 above), and check every chapter on a narrow phone before each APK.

## Open decisions

- Whether chapter 4 gets new lessons or merges into another chapter.
- Whether chapters should stay locked until the previous one is finished, or only warn.
- Whether the placement test is offered at first launch or only from the Profile tab.
