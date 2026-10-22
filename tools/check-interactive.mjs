// Sanity checks for interactive/: local links and scripts resolve, quiz data is well formed.
// Run with: node tools/check-interactive.mjs
import { readFileSync, readdirSync, existsSync } from 'node:fs';
import { join, dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';
import { loadRegistry, sectionIds } from './lib/registry.mjs';

const root = resolve(fileURLToPath(new URL('../interactive', import.meta.url)));
const errors = [];
const err = (m) => errors.push(m);

for (const f of readdirSync(root).filter((n) => n.endsWith('.html'))) {
  const html = readFileSync(join(root, f), 'utf8');
  for (const m of html.matchAll(/(?:href|src)="([^"#?]+)(?:#[^"]*)?"/g)) {
    const t = m[1];
    if (/^(https?:|mailto:|data:)/.test(t)) continue;
    if (t.startsWith('../')) { err(`${f}: ${t} leaves interactive/, which GitHub Pages does not publish: use a github.com/.../blob/main/ URL`); continue; }
    if (!existsSync(resolve(dirname(join(root, f)), t))) err(`${f}: missing local target ${t}`);
  }
}

const dataDir = join(root, 'assets', 'data');
for (const f of readdirSync(dataDir).filter((n) => n.startsWith('quiz-'))) {
  const ctx = { CT: { quizData: {} } };
  vm.runInNewContext(readFileSync(join(dataDir, f), 'utf8'), ctx, { filename: f });
  const quizzes = Object.values(ctx.CT.quizData);
  if (quizzes.length !== 1) { err(`${f}: expected exactly one quiz`); continue; }
  const seen = new Set();
  quizzes[0].questions.forEach((q, i) => {
    const where = `${f} #${i + 1}`;
    if (!q.q || !q.why) err(`${where}: missing q or why`);
    if (!Array.isArray(q.opts) || q.opts.length < 2) err(`${where}: needs at least 2 options`);
    else {
      if (!Number.isInteger(q.a) || q.a < 0 || q.a >= q.opts.length) err(`${where}: answer index out of range`);
      if (new Set(q.opts).size !== q.opts.length) err(`${where}: duplicate options`);
    }
    const id = q.q + (q.code ? '\n' + q.code.trim() : '');
    if (seen.has(id)) err(`${where}: duplicate question (same text and code)`);
    seen.add(id);
  });
}


// Registry checks (assets/data/lessons.js): every lesson has its pages and quiz data, ids are unique,
// moved sections point at real places, and every quiz question's sec is a section of its lesson.
const reg = loadRegistry();
const seenIds = new Set(), seenFiles = new Set();
const sections = {};
reg.lessons.forEach((l, k) => {
  const where = 'lessons.js #' + (k + 1) + ' (' + l.id + ')';
  for (const f of ['id', 'file', 'quiz', 'title', 'time', 'blurb']) if (typeof l[f] !== 'string' || !l[f]) err(where + ': missing ' + f);
  if (!/^[a-z][a-z0-9]*$/.test(l.id || '')) err(where + ': id must be lowercase letters and digits');
  if (seenIds.has(l.id)) err(where + ': duplicate id');
  seenIds.add(l.id);
  for (const f of [l.file, l.quiz]) {
    if (seenFiles.has(f)) err(where + ': ' + f + ' is used twice');
    seenFiles.add(f);
    if (!existsSync(join(root, f))) err(where + ': ' + f + ' does not exist');
  }
  if (!Number.isInteger(l.assess) || l.assess < 0) err(where + ': assess must be a whole number');
  if (existsSync(join(root, l.file))) {
    const html = readFileSync(join(root, l.file), 'utf8');
    if (!new RegExp('data-topic="' + l.id + '"').test(html)) err(where + ': ' + l.file + ' needs data-topic="' + l.id + '"');
    sections[l.file] = new Set(sectionIds(html));
  }
  const dataFile = join(dataDir, 'quiz-' + l.id + '.js');
  if (!existsSync(dataFile)) { err(where + ': assets/data/quiz-' + l.id + '.js does not exist'); return; }
  const ctx = { CT: { quizData: {} } };
  vm.runInNewContext(readFileSync(dataFile, 'utf8'), ctx);
  const qs = (ctx.CT.quizData[l.id] || {}).questions || [];
  if (l.assess > qs.length) err(where + ': assess is ' + l.assess + ' but the quiz has only ' + qs.length + ' questions');
  qs.forEach((q, i) => {
    if (!q.sec) err('quiz-' + l.id + '.js #' + (i + 1) + ': missing sec');
    else if (sections[l.file] && !sections[l.file].has(q.sec)) err('quiz-' + l.id + '.js #' + (i + 1) + ': sec "' + q.sec + '" is not a section of ' + l.file);
  });
});
for (const f of readdirSync(root).filter((n) => /^\d\d-.*\.html$/.test(n))) {
  if (!seenFiles.has(f)) err(f + ' looks like a lesson or quiz page but is not listed in lessons.js');
}
Object.entries(reg.moved).forEach(([from, to]) => {
  const [ff, fid] = from.split('#'), [tf, tid] = to.split('#');
  if (!reg.lessons.some((l) => l.file === ff)) err('moved: ' + from + ' is not a lesson page');
  else if (sections[ff] && sections[ff].has(fid)) err('moved: ' + from + ' still exists on its old page, so it never redirects');
  if (!sections[tf] || !sections[tf].has(tid)) err('moved: ' + from + ' points at ' + to + ', which does not exist');
});
const versions = reg.progressMigrations.map((m) => m.to);
if (new Set(versions).size !== versions.length || versions.some((v) => !Number.isInteger(v) || v < 2)) err('lessons.js: progressMigrations need distinct whole-number versions, starting at 2');

// the C++ Puzzles data (assets/data/puzzles.js, from CppQuiz.org): ids are unique and every puzzle has code, a result and an explanation
{
  const ctx = { CT: {} };
  vm.runInNewContext(readFileSync(join(dataDir, 'puzzles.js'), 'utf8'), ctx, { filename: 'puzzles.js' });
  const seen = new Set();
  for (const q of ctx.CT.puzzleData || []) {
    if (seen.has(q.id)) err('puzzles.js: duplicate id ' + q.id);
    seen.add(q.id);
    if (!['OK', 'CE', 'UD', 'US'].includes(q.r)) err('puzzles.js: puzzle ' + q.id + ' has the result ' + q.r);
    if (!q.code || !q.ex) err('puzzles.js: puzzle ' + q.id + ' lacks code or an explanation');
    if (q.r === 'OK' && typeof q.a !== 'string') err('puzzles.js: puzzle ' + q.id + ' has no answer text');
  }
  if (!seen.size) err('puzzles.js: no puzzles');
}

if (errors.length) { console.error(errors.join('\n')); process.exit(1); }
console.log('interactive/: all checks passed');
