// Checks docs/study-checklist.md and interactive/study-checklist.html against each other and the lessons:
// same sections and item counts, quiz sizes that match the data, links and lesson anchors that exist.
// Usage: node tools/verify-checklist.mjs
import { readFileSync, existsSync } from 'node:fs';
import { resolve, join } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';
import { loadRegistry, sectionIds, root as interactive } from './lib/registry.mjs';

const repo = resolve(fileURLToPath(new URL('..', import.meta.url)));
const rd = (p) => readFileSync(resolve(repo, p), 'utf8').replace(/\r\n/g, '\n');
const problems = [];
const bad = (m) => problems.push(m);
const reg = loadRegistry();

const md = rd('docs/study-checklist.md');
const html = rd('interactive/study-checklist.html');

// 1. the quiz sizes quoted in both files match the quiz data
for (const l of reg.lessons) {
  const ctx = { CT: { quizData: {} } };
  vm.runInNewContext(rd('interactive/assets/data/quiz-' + l.id + '.js'), ctx);
  const size = ctx.CT.quizData[l.id].questions.length;
  const esc = l.quiz.replace('.', '\\.');
  const m1 = md.match(new RegExp('\\(\\.\\./interactive/' + esc + '\\)\\)? \\((\\d+) questions\\)'));
  const m2 = html.match(new RegExp('href="' + esc + '">quiz</a>\\)? \\((\\d+) questions\\)'));
  if (!m1) bad(`md: no question count found for ${l.quiz}`); else if (+m1[1] !== size) bad(`md: ${l.quiz} says ${m1[1]}, data has ${size}`);
  if (!m2) bad(`html: no question count found for ${l.quiz}`); else if (+m2[1] !== size) bad(`html: ${l.quiz} says ${m2[1]}, data has ${size}`);
}

// 2. per-section item counts, md versus html
const mdSections = [];
let cur = null;
for (const line of md.split('\n')) {
  if (/^## /.test(line)) { cur = { title: line.slice(3).trim(), n: 0 }; mdSections.push(cur); }
  else if (/^- \[ \] /.test(line) && cur) cur.n++;
}
const htmlSections = [...html.matchAll(/<section class="ck-section"[^>]*>([\s\S]*?)<\/section>/g)].map((m) => ({
  title: (m[1].match(/<h2>([\s\S]*?)<span/) || [, ''])[1].trim(), n: (m[1].match(/data-ck=/g) || []).length
}));
const mdCheck = mdSections.filter((s) => s.n > 0);
if (mdCheck.length !== htmlSections.length) bad(`section count differs: md ${mdCheck.length}, html ${htmlSections.length}`);
const norm = (t) => t.replace(/\s*\(.*?\)\s*/g, ' ').replace(/[^a-z0-9 ]/gi, '').trim().toLowerCase();
mdCheck.forEach((s, i) => {
  const h = htmlSections[i];
  if (!h) return;
  if (s.n !== h.n) bad(`items differ in "${s.title}": md ${s.n}, html ${h.n}`);
  if (norm(s.title).slice(0, 18) !== norm(h.title).slice(0, 18)) bad(`section titles differ: "${s.title}" vs "${h.title}"`);
});
const total = (a) => a.reduce((x, s) => x + s.n, 0);
console.log(`items: md ${total(mdCheck)}, html ${total(htmlSections)}; sections: md ${mdCheck.length}, html ${htmlSections.length}`);

// 3. relative links in the md exist, and lesson anchors in the html exist
for (const m of md.matchAll(/\]\((?!https?:)([^)#\s]+)(#[^)]*)?\)/g)) {
  if (!existsSync(resolve(repo, 'docs', m[1]))) bad(`md: broken link ${m[1]}`);
}
const cache = {};
for (const m of html.matchAll(/href="(\d\d-[a-z0-9-]+\.html)#([^"]+)"/g)) {
  cache[m[1]] = cache[m[1]] || (existsSync(join(interactive, m[1])) ? new Set(sectionIds(readFileSync(join(interactive, m[1]), 'utf8'))) : new Set());
  if (!cache[m[1]].has(m[2]) && !reg.resolveMoved(m[1], m[2])) bad(`html: anchor #${m[2]} not found in ${m[1]}`);
}
for (const m of html.matchAll(/href="(\d\d-[a-z0-9-]+\.html)"/g)) {
  if (!existsSync(join(interactive, m[1]))) bad(`html: missing page ${m[1]}`);
}
if (/printed/i.test(md + html)) bad('the word "printed" appears in the checklist');

console.log(problems.length ? 'PROBLEMS:\n' + problems.join('\n') : 'study checklist is consistent with the repo');
process.exit(problems.length ? 1 : 0);
