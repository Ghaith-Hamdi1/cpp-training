// Builds the phase part of the study checklist (docs/study-checklist.md and interactive/study-checklist.html), one tab per phase of the
// roadmap in docs/reading/roadmap/phase-N-*.md. Each phase lists its lessons (sections and quiz, from the lesson registry and the lesson
// pages), its core book reading, its practice exercises and its recap check, so both files always list the same items. Everything after the line
// "<!-- generated:end" in each file (the move-semantics deep dive and the book list) is hand-written and left alone.
// Hints such as "(step through it)" come from tools/checklist-hints.json (key "lessonId:sectionId").
// Usage: node tools/build-checklist.mjs [--check]
import { readFileSync, writeFileSync, readdirSync } from 'node:fs';
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

// the phases come from docs/reading/roadmap/phase-N-*.md, so the checklist and the roadmap cannot drift apart
const ROAD = 'docs/reading/roadmap';
const BOOKS = { 'Primer': 'C++ Primer', 'PPP': 'Programming: Principles and Practice', 'EMC': 'Effective Modern C++', 'Move Semantics': 'C++ Move Semantics', 'Concurrency in Action': 'C++ Concurrency in Action' };
const inl = (t) => esc(t).replace(/\*\*([^*]+)\*\*/g, '<b>$1</b>').replace(/`([^`]+)`/g, '<code>$1</code>');
const unmd = (t) => t.replace(/\*\*/g, '');
const PHASES = readdirSync(resolve(repo, ROAD)).filter((n) => /^phase-\d+-.*\.md$/.test(n)).sort((x, y) => parseInt(x.slice(6)) - parseInt(y.slice(6))).map((file) => {
  const lines = rd(ROAD + '/' + file).split('\n');
  const n = +/^# Phase (\d+):/.exec(lines[0])[1];
  const name = lines[0].replace(/^# Phase \d+: /, '');
  const sub = (lines.find((l) => /^\*[^*].*\*$/.test(l)) || '').replace(/^\*|\*$/g, '');
  const time = /\*\*Time:\*\* about \*\*([\d.]+) hours?\*\*/.exec(lines.join('\n'))[1];
  const at = (re) => lines.findIndex((l) => re.test(l));
  const rows = (start) => { const out = []; for (let i = start; i < lines.length && !/^## /.test(lines[i]); i++) if (/^\| /.test(lines[i]) && !/^\| (Book|---)/.test(lines[i]) && !/^\|---/.test(lines[i])) out.push(lines[i].split('|').slice(1, -1).map((c) => c.trim())); return out; };
  const core = at(/^## Core reading/) >= 0 ? rows(at(/^## Core reading/) + 1).map(([book, sec, pages]) => ({ book, sec, pages })) : [];
  const lessonFiles = [...lines.slice(at(/^## Lessons and exercises/)).join('\n').matchAll(/cpp-training\/([\w-]+\.html)\)/g)].map((m) => m[1]).filter((x) => !/-quiz\.html$/.test(x));
  const ex = (lines.find((l) => /^Exercises: /.test(l)) || '').replace(/^Exercises: /, '').replace(/\.$/, '');
  const recap = (lines.find((l) => /^\*\*Recap check\.\*\* /.test(l)) || '').replace(/^\*\*Recap check\.\*\* /, '');
  return { n, name, sub, time, file, core, lessonFiles, ex, recap };
});

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
const idOfFile = Object.fromEntries(reg.lessons.map((l) => [l.file, l.id]));
for (const p of PHASES) p.ids = p.lessonFiles.map((fl) => { if (!idOfFile[fl]) throw new Error('roadmap phase ' + p.n + ' names an unknown lesson file ' + fl); return idOfFile[fl]; });
const used = PHASES.flatMap((p) => p.ids);
for (const l of reg.lessons) if (!used.includes(l.id)) throw new Error('lesson ' + l.id + ' is not in any phase of the roadmap');

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

// extra per-phase items: book reading, practice, recap
const extraItems = (p) => {
  const out = { read: [], practice: [], recap: [] };
  p.core.forEach((r, i) => out.read.push({ key: 'read-' + p.n + '-' + (i + 1), html: '<b>' + esc(BOOKS[r.book] || r.book) + ':</b> ' + inl(r.sec) + ' (PDF pages ' + esc(r.pages) + ')', md: (BOOKS[r.book] || r.book) + ': ' + unmd(r.sec) + ' (PDF pages ' + r.pages + ')' }));
  if (p.ex && !/^none/i.test(p.ex)) out.practice.push({ key: 'ex-' + p.n, html: 'Practice exercises: ' + inl(p.ex) + ' <a href="https://github.com/Ghaith-Hamdi1/cpp-training/blob/main/examples/practice/README.md">open</a>', md: 'Practice exercises: ' + p.ex + ' ([examples/practice](../examples/practice/README.md))' });
  if (p.recap) out.recap.push({ key: 'recap-' + p.n, html: 'Recap check. ' + inl(p.recap), md: 'Recap check. ' + unmd(p.recap) });
  return out;
};

// ---- markdown ----
let md = `# Study checklist

A step-by-step plan through the lessons and the books, one phase at a time. The phases are the same eight as the [C++ roadmap](reading/roadmap/README.md), and lessons 1 to 20 run through them in order. Each phase lists its lessons with their sections and quizzes, the core book reading, the practice exercises and a recap check.

**Want ticks that save?** Use the interactive version: <https://ghaith-hamdi1.github.io/cpp-training/study-checklist.html> (also at [\`interactive/study-checklist.html\`](../interactive/study-checklist.html)). It has one tab per phase and its checkboxes remember your progress in your browser.

- Site: <https://ghaith-hamdi1.github.io/cpp-training/> (works offline after one visit)
- Or open [\`interactive/index.html\`](../interactive/index.html) from a clone of the repo.
- Time boxes are guides. If a block runs long, finish the quiz and move on.

**How to study every lesson:** read a section, run its visualizer or simulator, predict the output before revealing it, then tick "I understand this section" only when you could explain it aloud. End each lesson with its quiz and retry only the questions you missed.

---

`;
PHASES.forEach((p) => {
  const x = extraItems(p);
  md += `## Phase ${p.n}: ${p.name} (about ${p.time} hours)\n\n${p.sub}. Roadmap page: [${p.file}](reading/roadmap/${p.file}).\n\n`;
  md += '### Lessons and quizzes\n\n';
  for (const id of p.ids) {
    const { l, n } = info[id];
    md += `**${l.title}:** [${l.file}](../interactive/${l.file}), quiz: [${l.quiz}](../interactive/${l.quiz}) (${n} questions).\n\n`;
    md += sectionItems(id).map((it) => `- [ ] ${it.md}`).join('\n') + '\n\n';
  }
  if (x.read.length) md += '### Book reading (core)\n\n' + x.read.map((it) => `- [ ] ${it.md}`).join('\n') + '\n\n';
  if (x.practice.length) md += '### Practice\n\n' + x.practice.map((it) => `- [ ] ${it.md}`).join('\n') + '\n\n';
  if (x.recap.length) md += '### Recap\n\n' + x.recap.map((it) => `- [ ] ${it.md}`).join('\n') + '\n\n';
});
md += `## Final review\n\n` + FINAL.map(([, t]) => `- [ ] ${mdText(t.replace(/<a href="[^"]*">([^<]*)<\/a>/g, '$1'))}.`).join('\n') + '\n\n';
md += '<!-- generated:end (tools/build-checklist.mjs writes everything above; the static part follows) -->\n';

// ---- html: one tab (a section) per phase, then the final review ----
const ROADMAP_URL = 'https://github.com/Ghaith-Hamdi1/cpp-training/blob/main/docs/reading/roadmap/';
let hh = '<div class="ck-tabs" role="tablist" aria-label="Phases">\n' +
  PHASES.map((p) => `<button type="button" role="tab" class="ck-tab" data-tab="phase-${p.n}" title="${esc(p.name)}">Phase ${p.n} <span class="ck-tab-count"></span></button>`).join('\n') +
  '\n<button type="button" role="tab" class="ck-tab" data-tab="final">Final <span class="ck-tab-count"></span></button>\n<button type="button" role="tab" class="ck-tab" data-tab="moves-deep" title="Move semantics deep dive (optional)">Move deep dive <span class="ck-tab-count"></span></button>\n</div>\n\n';
PHASES.forEach((p) => {
  const x = extraItems(p);
  const list = (items) => '<ul class="ck-list">\n' + items.map((it) => `<li><label><input type="checkbox" data-ck="${it.key}"><span class="t">${it.html}</span></label></li>`).join('\n') + '\n</ul>\n';
  hh += `<section class="ck-section" data-ck-section id="phase-${p.n}" role="tabpanel">\n<h2>Phase ${p.n}: ${esc(p.name)} (about ${p.time} hours) <span class="ck-count"></span></h2>\n<p class="ck-note">${esc(p.sub)}. <a href="${ROADMAP_URL}${p.file}">Roadmap page for this phase</a>.</p>\n<h3 class="ck-sub">Lessons and quizzes</h3>\n`;
  for (const id of p.ids) {
    const { l, n } = info[id];
    hh += `<h4>${esc(l.title)}</h4>\n<p class="ck-note"><a href="${l.file}">Lesson</a> <span class="badge" data-lesson="${id}"></span> and <a href="${l.quiz}">quiz</a> (${n} questions) <span class="badge" data-quiz="${id}"></span></p>\n<ul class="ck-list">\n`;
    hh += sectionItems(id).map((it) => `<li><label><input type="checkbox" data-ck="${it.key}"><span class="t">${it.html} <a href="${it.href}">open</a></span></label></li>`).join('\n') + '\n</ul>\n';
  }
  if (x.read.length) hh += '<h3 class="ck-sub">Book reading (core)</h3>\n' + list(x.read);
  if (x.practice.length) hh += '<h3 class="ck-sub">Practice</h3>\n' + list(x.practice);
  if (x.recap.length) hh += '<h3 class="ck-sub">Recap</h3>\n' + list(x.recap);
  hh += '</section>\n\n';
});
hh += `<section class="ck-section" data-ck-section id="final" role="tabpanel">\n<h2>Final review <span class="ck-count"></span></h2>\n<ul class="ck-list">\n` +
  FINAL.map(([k, t]) => `<li><label><input type="checkbox" data-ck="${k}"><span class="t">${t}</span></label></li>`).join('\n') + '\n</ul>\n</section>\n\n';

// ---- write, keeping each file's hand-written tail ----
const END = '<!-- generated:end';
const mdOld = rd('docs/study-checklist.md');
const mdNew = md.replace(/\n$/, '') + mdOld.slice(mdOld.indexOf('\n', mdOld.indexOf(END)));
const hOld = rd('interactive/study-checklist.html');
const starts = ['<div class="ck-tabs"', '<section class="ck-section"'].map((m) => hOld.indexOf(m)).filter((i) => i >= 0);
const cut = starts.length ? Math.min(...starts) : -1;
const endIdx = hOld.indexOf(END);
const headEnd = cut >= 0 && cut < endIdx ? cut : endIdx;
const hNew = hOld.slice(0, headEnd) + hh + hOld.slice(endIdx);
const headFixed = hNew.replace(/<p class="lead">[\s\S]*?<\/p>/, '<p class="lead">A step-by-step plan, one tab per phase of the roadmap. Each phase has its lessons, quizzes, core book reading, practice and a recap check. Tick each item when you finish it. Your ticks are saved on this device, and the lesson and quiz badges show your progress from the lessons themselves.</p>');

let stale = false;
for (const [p, s] of [['docs/study-checklist.md', mdNew], ['interactive/study-checklist.html', headFixed]]) {
  if (rd(p) === s) continue;
  if (check) { console.error(p + ' is out of date: run node tools/build-checklist.mjs'); stale = true; } else writeFileSync(resolve(repo, p), s);
}
if (check) { if (stale) process.exit(1); console.log('study checklist is up to date'); } else console.log('wrote the study checklist');
