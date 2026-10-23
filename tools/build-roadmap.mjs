// Builds the C++ roadmap pages (docs/reading/roadmap/README.md and one phase-N-*.md per phase) from tools/roadmap-data.mjs and the
// lesson registry (lesson numbers, titles and times come from interactive/assets/data/lessons.js).
// Usage: node tools/build-roadmap.mjs [--check]     (--check fails if the pages differ from what the data produces)
import { readFileSync, writeFileSync, mkdirSync, existsSync } from 'node:fs';
import { join, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import { loadRegistry } from './lib/registry.mjs';
import { phases, topicIndex, pagesOf, fmt, SHORT, PAGE_PER_HOUR } from './roadmap-data.mjs';

const repo = resolve(fileURLToPath(new URL('..', import.meta.url)));
const outDir = join(repo, 'docs', 'reading', 'roadmap');
const check = process.argv.includes('--check');
const SITE = 'https://ghaith-hamdi1.github.io/cpp-training/';

// ---- lessons, from the registry ----
const reg = loadRegistry();
const lesson = {};
reg.lessons.forEach((l, i) => { lesson[l.id] = { no: i + 1, name: l.title, file: l.file.replace(/\.html$/, ''), min: parseInt(l.time, 10) }; });
const lessonLink = (id) => `[${lesson[id].no}. ${lesson[id].name}](${SITE}${lesson[id].file}.html)`;
for (const p of phases) for (const id of p.lessons) if (!lesson[id]) throw new Error('phase ' + p.n + ' names an unknown lesson ' + id);

// ---- totals ----
const hrs = (m) => (Math.round(m / 6) / 10).toFixed(1);   // minutes -> hours with one decimal
const coreP = (p) => p.core.reduce((n, r) => n + pagesOf(r[2]), 0);
const deepP = (p) => p.deepen.reduce((n, r) => n + pagesOf(r[2]), 0);
const readMin = (pages) => Math.round(pages / PAGE_PER_HOUR * 60);
let totCoreMin = 0, totDeepMin = 0, totCoreP = 0, totDeepP = 0;
for (const p of phases) {
  p.lm = p.lessons.reduce((t, id) => t + lesson[id].min, 0);
  p.cm = readMin(coreP(p)); p.pm = p.practice[1]; p.dm = readMin(deepP(p));
  p.total = p.cm + p.lm + p.pm;
  totCoreMin += p.total; totDeepMin += p.dm; totCoreP += coreP(p); totDeepP += deepP(p);
  const slug = p.name.startsWith('Modern C++') ? 'modern-cpp' : p.name.toLowerCase().replace(/[^a-z0-9]+/g, '-').replace(/^-|-$/g, '');
  p.slug = slug;
  p.file = `phase-${p.n}-${slug}.md`;
  p.title = `Phase ${p.n}: ${p.name}`;
}

// ---- one phase page ----
function phasePage(p, k) {
  let o = '';
  const w = (s = '') => { o += s + '\n'; };
  w(`*${p.sub}.*`);
  w();
  w(`**Time:** about **${hrs(p.total)} hours** (${hrs(p.cm)} h reading, ${hrs(p.lm)} h lessons and quizzes, ${hrs(p.pm)} h exercises)` + (p.deepen.length ? `, plus ${hrs(p.dm)} h if you also read the deepen list.` : '.'));
  w();
  w('## Big topics');
  w();
  w('| Topic | What it covers |');
  w('|---|---|');
  for (const [t, d] of p.topics) w(`| **${t}** | ${d} |`);
  const table = (rows) => {
    w('| Book | Chapters and sections | PDF pages | Pages | What it gives you |');
    w('|---|---|---|---|---|');
    for (const [b, label, ranges, why] of rows) w(`| ${SHORT[b]} | ${label} | ${fmt(ranges)} | ${pagesOf(ranges)} | ${why} |`);
  };
  w();
  if (p.core.length) { w(`## Core reading (${coreP(p)} pages)`); w(); table(p.core); } else { w('## Core reading'); w(); w('No book in this set covers this phase; the lessons are the core.'); }
  if (p.deepen.length) { w(); w(`## Deepen (optional, ${deepP(p)} pages)`); w(); table(p.deepen); }
  w();
  w('## Lessons and exercises');
  w();
  w('| Lesson | Time |');
  w('|---|---|');
  for (const id of p.lessons) w(`| ${lessonLink(id)} and its [quiz](${SITE}${lesson[id].file}-quiz.html) | ${lesson[id].min} min |`);
  w();
  w(`Exercises: ${p.practice[0]}.`);
  if (p.note) { w(); w(`> ${p.note}`); }
  w();
  w(`**Recap check.** ${p.recap}`);
  w();
  w(`**Notes templates.** [Reading notes for phase ${p.n}](../notes/phase-${p.n}-${p.slug}/README.md).`);
  const prev = phases[k - 1], next = phases[k + 1];
  const nav = `[Roadmap](README.md)` + (prev ? ` | Previous: [${prev.title}](${prev.file})` : '') + (next ? ` | Next: [${next.title}](${next.file})` : '');
  return `# ${p.title}\n\n${nav}\n\n${o.trim()}\n\n---\n\n${nav}\n`;
}

// ---- the README ----
function readme() {
  let o = '';
  const w = (s = '') => { o += s + '\n'; };
  w('# C++ recap and roadmap: eight phases, five books');
  w();
  w('A map of every big C++ topic, grouped into eight phases from solid fundamentals to advanced tools to modern C++, with the exact book chapters (PDF pages) to read in each phase, the lessons and exercises that go with them, and a time estimate. Use it as a **reading guide** when you want to study a phase properly, and as a **recap** when you want to check that you can still explain the topics. The [topic index](#topic-index-where-to-look) at the end is the quick reminder.');
  w();
  w('All page numbers are **PDF viewer pages** (the number your PDF reader shows). The books are in [`books/`](../../../books).');
  w();
  w('## The five books');
  w();
  w('| Book | Covers | Best used for |');
  w('|---|---|---|');
  w('| *C++ Primer*, 5th ed. (Lippman, Lajoie, Moo), [PDF](../../../books/Cpp-Primer-5th-Edition-Lippman.pdf), [reading guide](../cpp-primer-reading-guide.md), [reading plan](../cpp-primer-reading-plan.md) | C++11, the whole language and library, 970 pages | The **systematic base**: phases 1 to 4 and the C++11 parts of phase 5. It is a textbook in the order a language should be learned, with exercises |');
  w('| *Programming: Principles and Practice Using C++*, 3rd ed. (Stroustrup), [reading guide](../programming-principles-and-practice-reading-guide.md) | C++20 | A **second explanation** from the language\'s creator, strongest on class design, memory and the STL. [Reading plan](../programming-principles-and-practice-reading-plan.md) |');
  w('| *Effective Modern C++* (Meyers), [reading guide](../effective-modern-cpp-reading-guide.md) | C++11/14 | **Modern C++** in short, self-contained items: deduction, smart pointers, move and forwarding, lambdas. [Reading plan](../effective-modern-cpp-reading-plan.md) |');
  w('| *C++ Move Semantics: The Complete Guide* (Josuttis), [reading guide](../move-semantics-complete-guide-reading-guide.md) | C++11 to C++20 | A **deep dive** on one topic: moved-from states, value categories, special member rules. [Reading plan](../move-semantics-reading-plan.md) |');
  w('| *C++ Concurrency in Action*, 2nd ed. (Williams), [reading guide](../concurrency-in-action-reading-guide.md) | C++17 | **Concurrency**: the only book here with real depth on threads and the memory model. [Reading plan](../concurrency-in-action-reading-plan.md) |');
  w();
  w('The books overlap on purpose. For each phase the **core** list is the shortest path that covers the phase; the **deepen** list is a second explanation of the same ground from another author, to read when a topic is still unclear or you want more depth. Do not read both lists in full unless you have the time.');
  w();
  w('## The plan at a glance');
  w();
  w('Time = core reading at about 10 pages an hour (pages with code you type in and run), plus the lessons and quizzes of the phase, plus the practice exercises. The deepen reading is extra and shown separately.');
  w();
  w('| Phase | Theme | Core reading | Lessons and quizzes | Exercises | **Core total** | Deepen reading (optional) |');
  w('|---|---|---|---|---|---|---|');
  for (const p of phases) w(`| [${p.n}](${p.file}) | ${p.name} | ${coreP(p)} pages, ${hrs(p.cm)} h | ${hrs(p.lm)} h | ${hrs(p.pm)} h | **${hrs(p.total)} h** | ${deepP(p)} pages, ${hrs(p.dm)} h |`);
  w(`| | **Total** | ${totCoreP} pages | | | **${hrs(totCoreMin)} h** | ${totDeepP} pages, ${hrs(totDeepMin)} h |`);
  w();
  w(`The core path is about **${Math.round(totCoreMin / 60)} hours**: roughly ${Math.round(totCoreMin / 60 / 6)} weeks at 6 hours a week, or ${Math.round(totCoreMin / 60 / 12)} weeks at 12. Adding every deepen list brings it to about **${Math.round((totCoreMin + totDeepMin) / 60)} hours**. If you only want a refresher on what you already know, skim the "core reading" at 25 pages an hour and spend your time on the lessons, quizzes and recap questions.`);
  w();
  w('Do the phases in order, because each builds on the one before. The lesson numbers on the site follow the same order, so lessons 1 to 20 are exactly phases 1 to 8 read top to bottom. Phase 6 (design patterns) uses `unique_ptr`, lambdas and `variant` from phases 3 and 5. Phase 7 (concurrency) needs move semantics, lambdas and RAII. Phase 8 needs phases 1 to 3 and the cache and threads ideas from phase 7; it can be read last or interleaved with phase 7.');
  w();
  w('## How to study a phase');
  w();
  w('| Step | Do |');
  w('|---|---|');
  w('| 1. Skim the topic list | Mark each topic you could not explain aloud right now. |');
  w(`| 2. Do the lessons | Work through the phase's lessons on the [site](${SITE}), running the step-throughs, then take each quiz. |`);
  w('| 3. Read | Read the core reading in the order listed, with the code closed first, then typed in. Read the deepen list only for topics you marked. |');
  w('| 4. Practise | Do the phase\'s exercises from [`examples/practice/`](../../../examples/practice/README.md) without looking things up. |');
  w('| 5. Recap | Answer the phase\'s recap question aloud, and retake any quiz below 80%. |');
  w();
  w('## Topic index: where to look');
  w();
  w('A one-page reminder: every big topic, the lesson that teaches it and the book chapter that explains it best (PDF pages).');
  w();
  w('| Topic | Lesson | Best book chapter |');
  w('|---|---|---|');
  for (const [t, id, b] of topicIndex) { if (!lesson[id]) throw new Error('topic index names an unknown lesson ' + id); w(`| ${t} | ${lessonLink(id)} | ${b} |`); }
  w();
  w('## Notes on the books');
  w();
  w('- **C++ Primer is a C++11 book.** It does not cover structured bindings, `if constexpr`, `std::optional`/`variant`/`string_view`, concepts, ranges or the C++14 to C++20 library. Phase 5 therefore leans on Effective Modern C++, Move Semantics and the lessons for those.');
  w('- **Programming: Principles and Practice** teaches C++20 style from the start (it uses `span`, concepts and `std::format`), but stays introductory on templates and has no threading chapter.');
  w('- **Skip on a first pass:** Primer chapter 1, the operator sections that only repeat what you know (4.6, 4.7, 4.9, 4.10, 4.12), 5.1, 5.2 and the Text-Query case studies in 12.3, 15.9 and 15.8; the Primer appendix; PPP chapters on graphics and the calculator (10 to 14, 6 to 7); Concurrency in Action chapter 7 (lock-free data structures) until phase 7 is solid.');
  w('- Each phase\'s book sections come from the reading guides and plans next to this file. `node tools/check-book-pages.mjs` checks that every section starts on the PDF page given.');
  w('- **Notes templates** live in [`notes/`](../notes/README.md), sorted by phase and then by book.');
  return o;
}

// ---- write, or check ----
const files = [['README.md', readme()], ...phases.map((p, k) => [p.file, phasePage(p, k)])];
let stale = 0;
for (const [name, text] of files) {
  const p = join(outDir, name);
  const old = existsSync(p) ? readFileSync(p, 'utf8').replace(/\r\n/g, '\n') : null;
  if (old === text) continue;
  if (check) { console.error(`docs/reading/roadmap/${name} is out of date: run node tools/build-roadmap.mjs`); stale++; }
  else { mkdirSync(outDir, { recursive: true }); writeFileSync(p, text); }
}
if (check) { if (stale) process.exit(1); console.log('roadmap pages are up to date'); } else console.log(`wrote ${files.length} roadmap pages`);
