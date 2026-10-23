// Builds the lesson part of the study checklist (docs/study-checklist.md and interactive/study-checklist.html) from the lesson registry
// and the section titles of each lesson, so both files always list the same sections and quiz sizes. Everything after the line
// "<!-- generated:end" in each file (the move-semantics deep dive and the book list) is hand-written and left alone.
// Hints such as "(step through it)" come from tools/checklist-hints.json (key "lessonId:sectionId").
// Usage: node tools/build-checklist.mjs [--check]
import { readFileSync, writeFileSync } from 'node:fs';
import { join, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';
import { loadRegistry, root as interactive } from './lib/registry.mjs';

const repo = resolve(fileURLToPath(new URL('..', import.meta.url)));
const check = process.argv.includes('--check');
const rd = (p) => readFileSync(resolve(repo, p), 'utf8').replace(/\r\n/g, '\n');
const reg = loadRegistry();
const hints = JSON.parse(rd('tools/checklist-hints.json'));
const esc = (s) => s.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
const mdText = (s) => s.replace(/<code>([^<]*)<\/code>/g, '`$1`').replace(/&amp;/g, '&').replace(/&lt;/g, '<').replace(/&gt;/g, '>');

// the same eight phases as docs/reading/roadmap, so lessons 1 to 20 read top to bottom
const STAGES = [
  ['Core language foundations', ['basics', 'types'], 'Types, memory, pointers, references, initialization and conversions.'],
  ['Classes and object-oriented design', ['oop', 'objmodel'], 'Classes, copy control, inheritance, virtual functions, and how objects are laid out in memory.'],
  ['The library and generic programming', ['strings', 'stl', 'lambdas', 'templates'], 'Strings, containers, iterators, algorithms, lambdas and templates.'],
  ['RAII and exceptions', ['core'], 'Tying resources to objects, exceptions, and the exception-safety guarantees.'],
  ['Modern C++', ['vocab', 'moves', 'smartptr', 'compiletime'], 'Vocabulary types, moving instead of copying, who owns an object, and compile-time programming.'],
  ['Design patterns', ['patterns', 'patterns2'], 'Common patterns in modern C++, with real code.'],
  ['Concurrency', ['threads', 'tasks', 'atomics'], 'Threads, locks, futures, atomics and the memory model.'],
  ['Performance', ['wire', 'latency'], 'Binary formats and parsing, and predictable, fast code.']
];

const info = {};
for (const l of reg.lessons) {
  const html = rd('interactive/' + l.file);
  const main = (html.match(/<main[^>]*>([\s\S]*)<\/main>/) || [, ''])[1];
  const secs = [...main.matchAll(/<section([^>]*)>\s*<h2>([\s\S]*?)<\/h2>/g)].map((m, i) => ({
    id: (m[1].match(/\sid="([^"]+)"/) || [, 's' + (i + 1)])[1], title: m[2].replace(/\s+/g, ' ').trim()
  }));
  const ctx = { CT: { quizData: {} } };
  vm.runInNewContext(rd('interactive/assets/data/quiz-' + l.id + '.js'), ctx);
  info[l.id] = { l, secs, n: ctx.CT.quizData[l.id].questions.length, mins: parseInt(l.time, 10) || 0 };
}
const hours = (ids) => { const m = ids.reduce((t, id) => t + info[id].mins, 0); const h = Math.round(m / 30) / 2; return h === 1 ? 'about 1 hour' : `about ${h} hours`; };
const used = STAGES.flatMap((s) => s[1]);
for (const l of reg.lessons) if (!used.includes(l.id)) throw new Error('lesson ' + l.id + ' is not in any stage of build-checklist.mjs');

const sectionItems = (id) => {
  const { secs } = info[id];
  return secs.map((s) => {
    const cheat = /^cheat sheet$/i.test(s.title.replace(/<[^>]+>/g, ''));
    const hint = cheat ? 'say each answer aloud' : hints[id + ':' + s.id];
    return { key: id + '-' + s.id, html: s.title + (hint ? ' (' + hint + ')' : ''), md: mdText(s.title + (hint ? ' (' + hint + ')' : '')), href: info[id].l.file + '#' + s.id };
  }).concat([{ key: id + '-quiz', html: 'Take the quiz, then retry the missed questions', md: 'Take the quiz, then retry the missed questions', href: info[id].l.quiz }]);
};

// ---- the final review ----
const FINAL = [
  ['final-retake', 'Retake every quiz where you scored under 80%'],
  ['final-level', 'Take the <a href="assess.html">level check</a> and revisit your weakest topics'],
  ['final-cheat', 'Open each lesson\'s "Cheat sheet" and say every answer aloud before opening it'],
  ['final-puzzles', 'Try ten <a href="puzzles.html">C++ Puzzles</a>'],
  ['final-queue', 'From memory, write a thread-safe queue (mutex and condition variable)'],
  ['final-deadlock', 'From memory, write a deadlock, then fix it with <code>std::scoped_lock</code>'],
  ['final-explain', 'Explain in your own words: data race versus race condition, <code>mutex</code> versus <code>atomic</code>, and why <code>wait</code> needs a predicate']
];

// ---- markdown ----
let md = `# Study checklist

A step-by-step plan through the lessons, in the order they build on each other. Each stage lists its lessons with their sections and quizzes.

**Want ticks that save?** Use the interactive version: <https://ghaith-hamdi1.github.io/cpp-training/study-checklist.html> (also at [\`interactive/study-checklist.html\`](../interactive/study-checklist.html)). Its checkboxes are clickable, remember your progress on your device, show a progress bar, and work offline. The boxes below are for reading on GitHub or for editing the file yourself.

- Site: <https://ghaith-hamdi1.github.io/cpp-training/> (works offline after one visit)
- Or open [\`interactive/index.html\`](../interactive/index.html) from a clone of the repo.
- Time boxes are guides. If a block runs long, finish the quiz and move on.

**How to study every lesson:** read a section, run its visualizer or simulator, predict the output before revealing it, then tick "I understand this section" only when you could explain it aloud. End each lesson with its quiz and retry only the questions you missed. Use the search box in the header when a term comes up. Run code snippets with the "Try in Compiler Explorer" button (add \`-pthread\` for thread code).

---

`;
STAGES.forEach(([name, ids, what], si) => {
  md += `## Stage ${si + 1}: ${name} (${hours(ids)})\n\n${what}\n\n`;
  for (const id of ids) {
    const { l, n } = info[id];
    md += `**${l.title}:** [${l.file}](../interactive/${l.file}), quiz: [${l.quiz}](../interactive/${l.quiz}) (${n} questions).\n\n`;
    md += sectionItems(id).map((it) => `- [ ] ${it.md}`).join('\n') + '\n\n';
  }
});
md += `## Final review\n\n` + FINAL.map(([, t]) => `- [ ] ${mdText(t.replace(/<a href="[^"]*">([^<]*)<\/a>/g, '$1'))}.`).join('\n') + '\n\n';
md += '<!-- generated:end (tools/build-checklist.mjs writes everything above; the static part follows) -->\n';

// ---- html ----
let hh = '';
STAGES.forEach(([name, ids, what], si) => {
  hh += `<section class="ck-section" data-ck-section>\n<h2>Stage ${si + 1}: ${esc(name)} (${hours(ids)}) <span class="ck-count"></span></h2>\n<p class="ck-note">${esc(what)}</p>\n`;
  for (const id of ids) {
    const { l, n } = info[id];
    hh += `<h3>${esc(l.title)}</h3>\n<p class="ck-note"><a href="${l.file}">Lesson</a> <span class="badge" data-lesson="${id}"></span> and <a href="${l.quiz}">quiz</a> (${n} questions) <span class="badge" data-quiz="${id}"></span></p>\n<ul class="ck-list">\n`;
    hh += sectionItems(id).map((it) => `<li><label><input type="checkbox" data-ck="${it.key}"><span class="t">${it.html} <a href="${it.href}">open</a></span></label></li>`).join('\n') + '\n</ul>\n';
  }
  hh += '</section>\n\n';
});
hh += `<section class="ck-section" data-ck-section>\n<h2>Final review <span class="ck-count"></span></h2>\n<ul class="ck-list">\n` +
  FINAL.map(([k, t]) => `<li><label><input type="checkbox" data-ck="${k}"><span class="t">${t}</span></label></li>`).join('\n') + '\n</ul>\n</section>\n\n';

// ---- write, keeping each file's hand-written tail ----
const END = '<!-- generated:end';
const mdOld = rd('docs/study-checklist.md');
const mdNew = md.replace(/\n$/, '') + mdOld.slice(mdOld.indexOf('\n', mdOld.indexOf(END)));
const hOld = rd('interactive/study-checklist.html');
const cut = hOld.indexOf('<section class="ck-section" data-ck-section>');
const endIdx = hOld.indexOf(END);
const headEnd = cut >= 0 && cut < endIdx ? cut : endIdx;
const hNew = hOld.slice(0, headEnd) + hh + hOld.slice(endIdx);
const headFixed = hNew.replace(/<p class="lead">[\s\S]*?<\/p>/, '<p class="lead">A step-by-step plan through the lessons, in the order they build on each other. Tick each item when you finish it. Your ticks are saved on this device, and the lesson and quiz badges show your progress from the lessons themselves.</p>');

let stale = false;
for (const [p, s] of [['docs/study-checklist.md', mdNew], ['interactive/study-checklist.html', headFixed]]) {
  if (rd(p) === s) continue;
  if (check) { console.error(p + ' is out of date: run node tools/build-checklist.mjs'); stale = true; } else writeFileSync(resolve(repo, p), s);
}
if (check) { if (stale) process.exit(1); console.log('study checklist is up to date'); } else console.log('wrote the study checklist');
