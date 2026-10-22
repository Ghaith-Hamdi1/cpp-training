# How to write a lesson

The conventions every lesson, quiz and example follows, so that the site, the tools and saved progress keep working. Read this before adding or splitting a lesson.

## 1. Files and registry

A lesson is three files plus one registry entry:

| File | Purpose |
|---|---|
| `interactive/NN-name.html` | the lesson |
| `interactive/NN-name-quiz.html` | its quiz page (copy an existing one, change the topic and data file) |
| `interactive/assets/data/quiz-<id>.js` | the quiz questions |

Then add one entry to `CT.lessons` in `interactive/assets/data/lessons.js`:

```js
{ id: 'moves', file: '11-move-semantics.html', quiz: '11-move-semantics-quiz.html', title: 'Move Semantics',
  time: '60 min', assess: 2, blurb: 'One sentence shown on the home page card.' }
```

- `id`: lowercase letters and digits. It is stored in saved progress, so **never rename it** without a migration.
- The number shown on screen and the navigation order come from the **position in the array**, not from the file name. New lessons get the next free file number and go at the end, or wherever they belong in the order.
- `assess`: how many questions the level check draws from this lesson. Use 2 for every lesson so the check is even (0 leaves the lesson out; it cannot exceed the quiz size).

The search index, mock-interview bank, offline cache, home page, menus, pager and level check all pick the lesson up from the registry. Run the generators after editing (see section 8).

## 2. Page skeleton

```html
<body data-topic="moves" data-kind="lesson">
<main>
<h1>Move Semantics</h1>
<p class="lead">One or two sentences: what the reader will be able to do afterwards.</p>

<section data-title="Value categories">
<h2>Value categories</h2>
...
</section>
...
<section data-title="Interview cheat sheet">
<h2>Interview cheat sheet</h2>
<details class="ex"><summary>The question</summary><div><p>A short answer to say out loud.</p></div></details>
</section>
</main>
<script src="assets/data/lessons.js"></script>
<script src="assets/app.js"></script>
<script> /* CT.stepper(...), CT.threadsim(...) calls */ </script>
```

- `data-topic` must equal the registry `id`. The registry script goes **before** `app.js`.
- Each `<section>` is one page on screen. Keep sections short: one idea, ideally under about 250 words of prose plus code.
- Section ids are `s1`, `s2`... by position unless you give one explicitly (`<section id="interface-races">`). Anything that links to a section by id (quiz tags, checklist links, reading guides, other lessons) depends on it. **Moving or renumbering sections breaks those links**, so pin an explicit `id` on a section before inserting sections ahead of it.
- "Read more" notes (the book chapters and PDF pages that deepen a section) are generated at the end of lesson sections from the reading guides by `node tools/build-read-more.mjs`. Do not edit them by hand; add rows to the guides, or to EXTRA or HINTS in the tool.
- The last section must be titled exactly `Interview cheat sheet`; the mock interview is built from its `<details>` elements.

## 3. Writing style

- Concise and visual. A diagram or step-through for every concept with moving parts; no walls of text.
- Every claimed output is compiled and run before it goes in (g++ 16, `-std=c++20`).
- Interview angle: say what the interviewer wants to hear, and when not to use something.

## 4. Visuals

- **Diagram:** an inline `<figure class="fig"><svg viewBox="...">` using the classes in `style.css` (`.box`, `.acc`, `.gd`, `.bd`, `.wn`, `.ln`, `.ar`, `.t`, `.m`). Keep text inside the viewBox and clear of boxes.
- **Step-through:** `<div id="st-name"></div>` plus `CT.stepper('#st-name', { title, code, steps })`. Each step is `{ line, mem: [...], out, note }`. A memory entry is `{ n, t, v, p, k, dead, to, fam }`: `n` name (put `@0x...` in a heap name and the address in the pointer's `v`, and an arrow is drawn), `t` type, `v` value, `p` caption, `k` region (`stack`, `heap`, `static`, `call`, `inst`, `queue`, `threads`), `dead` freed, `to` explicit arrow target, `fam` colour family (cells with the same family share a colour).
- **Simulator:** `CT.threadsim` for interleavings.

## 5. Quiz data

`CT.quizData.<id> = { id, questions: [...] }` with each question `{ sec, q, code?, opts, a, why }`:

- `sec` is required and must be a section id of the lesson (checked by the tools). The level check and the "Re-read this" links use it.
- Two to four options, a single correct index `a`, no duplicate options, and a `why` that teaches.
- About 15 to 25 questions per lesson, a mix of recall and "what does this print / what is wrong".

## 6. Runnable examples and the study checklist

- Add programs to `examples/lessons/<NN>-<name>/` (complete, compile with `-Wall -Wextra`, output checked) and list them in `examples/lessons/README.md`.
- Add the lesson to `docs/study-checklist.md` and `interactive/study-checklist.html` (same items in both, with the quiz question count). `node tools/verify-checklist.mjs` enforces it.
- If a reading guide maps a book section to this lesson, use the exact section title (`node tools/check-guides.mjs` enforces it).

## 7. Moving or renaming things safely

- **Moving a section to another lesson:** add `'old-file.html#old-id': 'new-file.html#new-id'` to `CT.moved` so old links redirect. The tools fail if the old id still exists on the old page or the target does not exist.
- **Changing a lesson id or splitting a lesson:** add a migration to `CT.progressMigrations` (`{ to: N, run(store) {...} }`, versions start at 2). It copies saved ticks, quiz scores and weak-question lists to the new ids. Migrations run once per browser and must be idempotent, because an older exported progress code can be imported later. `tools/test-registry.mjs` shows the pattern.

## 8. Checks and generators

Run these before committing (CI runs the same):

```bash
node tools/build-search-index.mjs
node tools/build-mock-bank.mjs
node tools/build-precache.mjs
node tools/check-interactive.mjs
node tools/check-links.mjs
node tools/build-read-more.mjs
node tools/verify-checklist.mjs
node tools/check-guides.mjs
node tools/test-registry.mjs
```

The first three rewrite generated files (`search-index.js`, `mock-bank.js`, `sw.js`); the rest only check. Add `--check` to a generator to verify without writing.

## 9. Definition of done for a lesson

- [ ] Registry entry, three files, `data-topic` matches
- [ ] Sections short, ids stable, a diagram or step-through for each major concept
- [ ] Cheat sheet, quiz (every question has `sec`), `assess` set
- [ ] Runnable examples compiled and checked
- [ ] Checklist (both files) and any reading guide updated
- [ ] All checks above pass; generated files rebuilt
- [ ] Opened in the browser: pager, menu, search, quiz, level check, mock interview, offline reload
