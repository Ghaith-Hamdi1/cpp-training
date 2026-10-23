// Builds the C++ Primer reading guide and reading plan (docs/reading/cpp-primer-reading-{guide,plan}.md) from tools/primer-data.mjs.
// Usage: node tools/build-primer.mjs [--check]     (--check fails if the two files differ from what the data produces)
// The notes templates (docs/reading/notes/**/cpp-primer/) are NOT generated: they are yours to fill in, so a rebuild must never touch them.
import fs from 'node:fs';
import { resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import { parts, sessions, skip, PDF } from './primer-data.mjs';

const REPO = resolve(fileURLToPath(new URL('..', import.meta.url))) + '/';
const check = process.argv.includes('--check');
let stale = 0;
const W = (rel, text) => {
  const p = REPO + rel;
  const old = fs.existsSync(p) ? fs.readFileSync(p, 'utf8').replace(/\r\n/g, '\n') : null;
  if (old === text) return;
  if (check) { console.error(rel + ' is out of date: run node tools/build-primer.mjs'); stale++; } else fs.writeFileSync(p, text);
};
const pp = (a, b) => `${a + PDF} to ${b + PDF}`;
const pages = (a, b) => b - a + 1;
const sesPages = (s) => s.items.reduce((n, i) => n + pages(i.a, i.b), 0);
const hours = (s) => Math.max(2, Math.round(sesPages(s) / 10) + 1);
const num = (i) => String(i + 1).padStart(2, '0');
const rangeStr = (s) => s.items.map((i) => pp(i.a, i.b)).join('; ');
const secStr = (s) => s.items.map((i) => (i.bold ? `**${i.sec}**` : i.sec)).join('; ');
const sesName = (i) => `${num(i)}-${sessions[i].slug}`;
const ALLP = sessions.reduce((n, s) => n + sesPages(s), 0);
const ALLH = sessions.reduce((n, s) => n + hours(s), 0);
const coreSessions = sessions.filter((s) => s.part !== 'E');
const CORE_H = coreSessions.reduce((n, s) => n + hours(s), 0);

// ---------- guide ----------
const rows = sessions.flatMap((s) => s.items);
const tier = (bold) => rows.filter((i) => i.bold === bold);
const tp = (bold) => tier(bold).reduce((n, i) => n + pages(i.a, i.b), 0);
const row = (i) => `| **${i.sec}** ${i.title} | ${pp(i.a, i.b)} | ${i.teaches} | ${i.lesson} |`;
let g = '';
g += `# Reading guide: *C++ Primer* (5th Edition)

A reading plan for \`books/Cpp-Primer-5th-Edition-Lippman.pdf\` (Stanley Lippman, Josée Lajoie and Barbara Moo, 2012, about 970 pages, C++11). It is the most complete textbook of the five books: it teaches the whole language and the library in the order a beginner should meet them, with exercises after almost every section. That makes it the **systematic base** for lessons 1 to 9, 11 and 12; it is a good partner to the lessons because it explains every rule in full, and they show what happens in memory.

**Page numbers.** The tables give *PDF viewer* page numbers, the number your PDF reader shows. The plan and the notes use PDF pages only.

The sections and their summaries come from the book's table of contents and chapter openings. I did not read every page in full.

---

## What the book does and does not cover

| Covers well | Does not cover |
|---|---|
| Types, expressions, statements, functions, classes | Threads, mutexes, atomics (use *C++ Concurrency in Action* and lessons 16 to 18) |
| The whole standard library of C++11: strings, containers, algorithms, IO, smart pointers | C++14, C++17 and C++20: \`optional\`, \`variant\`, \`string_view\`, structured bindings, \`if constexpr\`, concepts, ranges, \`std::format\` (lessons 2, 10, 7, 6, 13) |
| Copy control, move semantics, operator overloading | Deep move semantics and forwarding (*Effective Modern C++* and *C++ Move Semantics*) |
| Inheritance and virtual functions, templates, exceptions | Design patterns, performance and memory layout (lessons 14, 15, 19 and 20) |

## Tier 1: read these first (about ${tp(true)} pages)

The sections that teach what the lessons rely on: types and \`const\`, strings and vectors, argument passing, classes, copy control, the library containers, smart pointers, inheritance, templates and exceptions.

| Section | PDF pages | What it teaches | Matching lesson section |
|---|---|---|---|
${tier(true).map(row).join('\n')}

## Tier 2: read next if you have time (about ${tp(false)} pages)

| Section | PDF pages | What it teaches | Matching lesson section |
|---|---|---|---|
${tier(false).map(row).join('\n')}

## Skip on a first read

| Skip | Why |
|---|---|
${skip.map(([a, b]) => `| ${a} | ${b} |`).join('\n')}

## How to use this guide

1. Do the lesson and quiz for a topic first (for example, lesson 1 for pointers).
2. If a quiz question surprises you, read the matching Tier 1 section here for the longer explanation.
3. Do the exercises at the end of each section you read: the book has hundreds, so pick two or three per section.
4. For an ordered path through the whole book, session by session, follow the [reading plan](cpp-primer-reading-plan.md); to keep your own notes, copy the [session templates](notes/README.md#c-primer-5th-ed).

## Notes on the edition

- The book is written for C++11. Code such as \`auto\`, range-for, lambdas and \`nullptr\` is covered, but the C++14 to C++20 features in the lessons are not, so do not treat the book as the last word on modern style (see the other four books for that).
- The book's own exercises are numbered by section (Exercise 3.2.1 is the first exercise of section 3.2). Solutions are not in the book.
- Chapter 1 and the bookstore case study are an introduction; start at chapter 2.
`;
W('docs/reading/cpp-primer-reading-guide.md', g);

// ---------- plan ----------
const partOf = (letter) => sessions.map((s, i) => [s, i]).filter(([s]) => s.part === letter);
const idxRows = sessions.map((s, i) => `| ${i + 1} | ${s.title} | ${secStr(s)} | ${rangeStr(s)} | ${sesPages(s)} | ${hours(s)} h |`).join('\n');
const partRange = (L) => { const r = partOf(L).map(([, i]) => i + 1); return r.length > 1 ? `sessions ${r[0]} to ${r[r.length - 1]}` : `session ${r[0]}`; };
let p = '';
p += `# Reading plan: *C++ Primer* (5th Edition)

An ordered plan for reading the book to learn the language and library properly, in ${sessions.length} sessions. It follows the book's own order, because each part builds on the one before it, and it skips what the lessons already cover or what is only reference. The book is \`books/Cpp-Primer-5th-Edition-Lippman.pdf\`. **All page numbers are PDF viewer pages** (the number your PDF reader shows), taken from the [reading guide](cpp-primer-reading-guide.md).

## The plan at a glance

| # | Session | Read (book sections) | PDF pages | Pages | Time |
|---|---|---|---|---|---|
${idxRows}

Bold sections are the ones to read most carefully. In all it is about ${ALLH} hours across roughly ${ALLP} pages (${CORE_H} hours for sessions 1 to ${coreSessions.length}, without the optional extras), which is 11 to 16 weeks at two or three sessions a week. Time estimates assume about 10 pages an hour plus the exercises and checkpoint work; they are guidelines.

## How to read each session

| Step | Do |
|---|---|
| 1. Read | Read the pages once with the code closed. Note every sentence that surprises you. |
| 2. Write | Close the book and write the small program the pages teach (a class with a constructor, a \`Stack\`, a lambda with a capture). Compile with \`g++ -std=c++20 -Wall -Wextra\`. Open the book only to compare. |
| 3. Exercise | Do two or three of the exercises at the end of each section you read (they are numbered by section). Skip the ones that only repeat code. |
| 4. Explain | Answer the checkpoint questions aloud. If you cannot answer one in two sentences, reread that part. |
| 5. Reinforce | Do the "after" step: the repo lesson, quiz or practice exercise named for the session. |

`;
const partIntro = {
  A: 'Chapters 2 to 7. After this you can write ordinary C++ programs and design a simple class.',
  B: 'Chapters 8 to 12. The containers, algorithms and smart pointers you will use every day.',
  C: 'Chapters 13 to 16. Copy control, move semantics, operators, inheritance and templates: what separates a user of C++ from a writer of classes. Do not skip these.',
  D: 'Chapters 17 to 19. Specialized tools; read the parts you need.',
  E: 'Optional.',
};
for (const L of ['A', 'B', 'C', 'D', 'E']) {
  const list = partOf(L);
  p += `## Part ${L}: ${parts[L].toLowerCase()} (${partRange(L)})\n\n${partIntro[L]}\n\n`;
  if (L === 'E') {
    p += '| # | Read | After |\n|---|---|---|\n';
    for (const [s, i] of list) p += `| ${i + 1} | ${s.items.map((x) => x.sec + ' ' + x.title).join('; ')} | ${s.after} |\n`;
  } else {
    p += '| # | Checkpoint questions | After |\n|---|---|---|\n';
    for (const [s, i] of list) p += `| ${i + 1} | ${s.q.join('<br>')} | ${s.after} |\n`;
  }
  p += '\n';
}
p += `## What to skip

| Skip | Why |
|---|---|
${skip.map(([a, b]) => `| ${a} | ${b} |`).join('\n')}

## What this book will not teach you

| Topic | Where to learn it |
|---|---|
| Threads, mutexes, atomics | *C++ Concurrency in Action* in \`books/\`; lessons 16 to 18 |
| C++14 to C++20 (\`optional\`, \`variant\`, \`string_view\`, concepts, ranges) | lessons 2, 10, 7, 6 and 13 |
| Move semantics and forwarding in depth | *C++ Move Semantics* and *Effective Modern C++* in \`books/\` |
| Design patterns | lessons 14 and 15 |
| Binary data, memory layout and performance | lessons 19 and 20 |

## Notes on the edition

The code is C++11. Where the book writes \`for (auto it = v.begin(); ...)\` or a \`bind\` call, the lessons use range-for and lambdas; both are valid, and you should be able to read each. To compile the examples, use \`g++ -std=c++20 -Wall -Wextra\`.

For the notes on each session, see the [notes templates](notes/README.md#c-primer-5th-ed).
`;
W('docs/reading/cpp-primer-reading-plan.md', p);


if (check) { if (stale) process.exit(1); console.log('Primer guide and plan are up to date'); } else console.log('wrote the Primer guide and plan');
