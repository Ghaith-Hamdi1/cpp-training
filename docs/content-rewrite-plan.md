# Rewrite plan for the interactive lessons

Plan for fixing everything listed in [content-audit.md](content-audit.md), in phases that can each be shipped on their own. Nothing is started. Effort figures are rough working sessions (one session is about 2 to 3 hours of focused work).

## Status

| Phase | State |
|---|---|
| 0 Foundations | done (branch `rewrite/phase-0`) |
| 1 Quick fixes and de-duplication | done (branch `rewrite/phase-1`): the three imprecisions fixed, lessons 5 and 9 de-duplicated (lesson 9 owns traits, SFINAE, concepts and compile-time computation; the old lesson 5 section moved via `CT.moved`), strings consolidated in lesson 8, and the cheap gaps added (`decltype`, init-capture, `std::exchange`, functors, `explicit operator bool`, the braced-init trap, `cbegin`) |
| 2 Low-latency and feed-handler lessons | in progress (branch `rewrite/phase-2`): lesson 11 (Wire Formats and Parsing) and lesson 12 (Low-Latency C++) written, with quizzes, step-throughs and compiled programs |
| 3 to 6 | not started |

## Ground rules for every phase

- **Each phase ends shippable.** The site works, all checks pass, and the work is committed and pushed before the next phase starts. Work on a branch per phase and merge when the exit criteria are met.
- **Concise and visual.** Short paragraphs, a diagram or step-through wherever a concept has moving parts, no walls of text. This is a standing preference.
- **Every lesson is complete when it has:** sections with stable ids, at least one diagram or step-through per major concept, an interview cheat sheet, a quiz whose questions are tagged with a `sec` id, runnable programs in `examples/lessons/`, an entry in the search index, mock bank and offline cache (all generated), and its row in the study checklist.
- **Checks that must pass:** `node tools/check-interactive.mjs`, `build-search-index.mjs --check`, `build-mock-bank.mjs --check`, `build-precache.mjs --check`, the checklist consistency check (to be moved into `tools/` in phase 0), and every program in `examples/lessons/` compiling with `-Wall -Wextra` and running.
- **Verify code, do not trust it.** Any new snippet with a claimed output is compiled and run (g++, `-std=c++20`) before it goes in.
- **Do not break saved progress or links.** See phase 0.

## Phase 0: Foundations (1 session)

**Goal:** make adding, splitting and moving lessons safe and cheap.

Tasks:
1. **Lesson registry.** Today the lesson list lives in `TOPICS` inside `app.js`, a second copy in `check-interactive.mjs` (`lessonOf`), and the level-check weights in `ASSESS_COUNTS`. Move this to one data file read by the site and the tools.
2. **Stable URLs.** Keep every existing file name. New lessons get new numbers (11 and up); navigation order comes from the registry, not the file name. Moved sections leave a `moved` map (old `lesson#id` to new `lesson#id`) so old links, the checklist and the docs keep working.
3. **Progress migration.** Saved progress is keyed by topic id (`done:`, `total:`, `quiz:`, `weak:`) and by section id. Add a one-time migration in `app.js` that remaps old ids to new ones, and extend the export/import whitelist to the new ids. Without it, learners lose ticks when a lesson is split.
4. **Move the checklist consistency script into `tools/`** (it currently lives only in a scratchpad) and add it to CI. Add a check that reading guides refer only to sections that exist.
5. **Content template.** One page documenting the section, cheat-sheet, quiz and example conventions, so later phases are uniform.

Exit: the registry drives the site, tools and CI; a dummy new lesson can be added by editing one file; migration tested with a saved-progress sample.

## Phase 1: Quick fixes and de-duplication (1 session)

**Goal:** fix what is already wrong or repeated, with no structural change.

Tasks:
1. Fix the three imprecisions: `[=]` and implicit `this` capture (lesson 3), the `NULL` wording (lesson 1), and one consistent `string_view` explanation.
2. Give lessons 5 and 9 clear ownership: lesson 9 owns type traits, SFINAE, `enable_if`, concepts, `constexpr` and template metaprogramming; lesson 5 keeps a short pointer and the template-specific uses. Remove the duplicated factorial and trait examples from lesson 5, and re-tag the affected quiz questions.
3. Strings: keep one full treatment, and turn the other mentions into one-line pointers.
4. Add the cheap one-paragraph gaps with a snippet each: `decltype`, lambda init-capture, `std::exchange`, functors, conversion operators and `explicit operator bool`, the braced-init versus `initializer_list` trap, `cbegin`.

Files: lessons 1, 3, 4, 5, 8, 9 and their quiz data and mock bank.
Exit: no concept explained twice with different wording; zero audit "imprecision" items open.

## Phase 2: Low-latency and feed-handler lesson (3 to 4 sessions)

**Goal:** close the biggest gap against the job description. Mostly additive, so it carries little risk and comes before the restructuring.

New lesson, possibly two (wire formats and data; latency and memory):
1. **Binary wire formats:** packed structs, alignment and padding, endianness, strict aliasing, `memcpy` and `std::bit_cast`, integer types and bit manipulation, `union` and its pitfalls.
2. **Zero-copy parsing:** `string_view` and `span`, `from_chars`, sequence numbers and gap detection.
3. **Data structures for market data:** order-book options (`map`, sorted vector, flat map, price-indexed arrays), hashing and ID lookup, fixed-point prices versus `double`.
4. **Memory on the hot path:** preallocation, object pools, `pmr` and arena allocators, `reserve`, avoiding allocation after startup.
5. **Concurrency on the hot path:** bounded queues with back-pressure and drop policies, the SPSC ring buffer revisited, thread pinning, busy-polling versus blocking, false sharing, cache layout (AoS versus SoA).
6. **Measuring:** `steady_clock`, percentiles and tail latency, why averages mislead, benchmarking pitfalls.

Deliverables: sections with diagrams, at least 4 step-throughs (ring buffer, order-book insert, packet parse, pool allocation), runnable programs (parse a packed message, bounded SPSC queue, pool allocator, latency histogram), 15 to 20 quiz questions, a cheat sheet, and level-check weights.
Exit: the lesson passes the checks; a reader can answer "how would you parse and queue a market-data feed without allocating or locking?"

## Phase 3: Split lesson 3 and restructure templates (3 to 4 sessions)

**Goal:** remove the grab-bag lesson and put move semantics in one place.

Target structure (new files, `core` keeps its id for the first slice):
1. RAII and exceptions (exception safety levels, `noexcept`, stack unwinding).
2. Move semantics (value categories, `std::move`, move constructor and assignment, `noexcept`, copy elision, moved-from state, `std::exchange`, copy-and-swap). This absorbs the Rule of 5 move table from lesson 2 and the forwarding half of lesson 5 through cross-links.
3. Smart pointers (`unique_ptr`, `shared_ptr` internals, `weak_ptr`, custom deleters, `enable_shared_from_this`, ownership guidelines).
4. Lambdas and callables (captures, init-capture, `mutable`, `this`, generic lambdas, `std::function` versus templates versus function pointers, functors).
5. Types, initialization and casts (`auto`, `decltype`, initialization forms, the braced-init trap, casts, `const`, `constexpr`, `static`, language versions).

Templates: split "Deduction and forwarding references" into deduction (including `auto`) and forwarding; add alias templates, variable templates, template template parameters and `std::index_sequence`.

Migration: the 24-question core quiz is divided among the new lessons; `weak:core` entries are redistributed by question text; the `moved` map keeps old `03-core-language.html#...` links alive.
Exit: no lesson over about 9 sections; every old link resolves; progress migrates.

## Phase 4: Multithreading depth (3 sessions)

**Goal:** cover the Concurrency in Action topics a feed-handler interview can reach.

Tasks:
1. Split "Atomics" into atomic operations and memory ordering.
2. Memory ordering: happens-before and synchronizes-with, `acq_rel`, fences, `compare_exchange_weak` versus `strong`, with a visual simulator for acquire/release.
3. New material: `atomic_flag` and spinlocks, `recursive_mutex` and `timed_mutex` (and why recursion is a smell), `latch`, `barrier` and `semaphore`, `shared_future`, `promise<void>` as a signal, thread-safe data structures (fine-grained locking, lookup table with `shared_mutex`), work stealing, parallel algorithms.
4. Move the performance and lock-free material out of lesson 7 into the phase 2 lesson, leaving a short pointer.

Deliverables: new sections with step-throughs, 10 to 12 new quiz questions, updated cheat sheet, new runnable programs.
Exit: lesson 7 is no longer the longest lesson; the quiz covers the memory model.

## Phase 5: Strings, OOP, STL and patterns gaps (2 to 3 sessions)

1. **Strings and time:** one strings lesson (`string`, SSO, `string_view`, `from_chars`, `format`, streams and `fstream`, formatting); regex and `chrono` split off.
2. **OOP:** multiple and virtual inheritance and the diamond problem, RTTI and `typeid`, private inheritance, `explicit` conversions, copy-and-swap.
3. **STL:** custom comparators and hash functions for keys, `try_emplace`, `multimap`, iterator adaptors (`back_inserter`), a short ranges introduction.
4. **Patterns:** real code and a diagram for Command (with undo), Decorator, Adapter and Builder, Visitor with `variant`, and the patterns that matter for feed handlers (pub/sub, object pool, state machine for a session).
5. **Smaller items:** placement new, `std::bind`, `<random>`, user-defined literals, `extern "C"`.

Exit: every row in the audit's "Other gaps" list is either covered or consciously dropped with a note.

## Phase 6: Integration and release (1 to 2 sessions)

1. Update the study checklist (both `docs/study-checklist.md` and `interactive/study-checklist.html`), the four reading guides (section numbers), the topic map, the README (lesson count, links), the home page and the level-check weights.
2. Re-tag all quiz questions with `sec`; re-balance the level check so each topic keeps at least 2 questions.
3. Full QA: every step-through (arrow check across all steps), every link, every program compiled and run, offline mode, mobile layout, export/import of progress across the migration.
4. Re-run the content audit and record the result in `content-audit.md`.

Exit: audit shows no open items except the ones deliberately dropped.

## Order, dependencies and effort

| Phase | Depends on | Effort | Why this position |
|---|---|---|---|
| 0 Foundations | none | 1 session | Everything else touches ids, links or progress. |
| 1 Quick fixes | 0 | 1 session | Cheap, and removes duplication before restructuring. |
| 2 Low-latency lesson | 0 | 3 to 4 sessions | Biggest gap against the job; additive, low risk. |
| 3 Split lesson 3, templates | 0, 1 | 3 to 4 sessions | Largest structural change; needs the migration from phase 0. |
| 4 Multithreading depth | 0, 2 | 3 sessions | Reuses the ring-buffer material from phase 2. |
| 5 Remaining gaps | 0, 1 | 2 to 3 sessions | Independent, can run in parallel with 4. |
| 6 Integration | all | 1 to 2 sessions | Final consistency pass. |

Total: roughly 14 to 18 sessions. Phases 4 and 5 can overlap; phase 2 can start as soon as phase 0 is done.

## Risks

- **Lost progress or dead links when lessons split.** Mitigated by the registry, the `moved` map and the migration in phase 0, plus tests with saved-progress samples.
- **Content bloat.** New lessons can grow the same walls of text that were trimmed earlier. Every phase is held to the "concise and visual" rule, and long sections are split rather than extended.
- **Unverified code.** Mitigated by compiling every new snippet and program.
- **Quiz and level-check drift.** Splitting lessons changes question counts and weights. The checks fail on missing `sec` tags and on stale counts in the checklist.
- **Scope creep.** The list of gaps is long. Items not tied to the job description or the audit are dropped, not added.

## Decisions needed before starting

1. One low-latency lesson or two (wire formats and data; latency and memory)?
2. Keep the current numbering in the navigation and append new lessons at the end, or renumber (which means redirects)? The plan assumes appending, with navigation order set in the registry.
3. Are lessons 8 (regex and time) and 10 (coding rules) worth keeping as separate lessons, or should they become sections of larger ones?
4. Is the target C++17 or C++20? The examples compile as C++20 today; the job description may fix this.
