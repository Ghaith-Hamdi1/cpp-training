// Sanity checks for interactive/: local links and scripts resolve, quiz data is well formed.
// Run with: node tools/check-interactive.mjs
import { readFileSync, readdirSync, existsSync } from 'node:fs';
import { join, dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';

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


// Every quiz question's sec must be a section id that exists in its lesson (the assessment links to it).
const lessonOf = { basics: '01-basics', oop: '02-oop', core: '03-core-language', stl: '04-stl', templates: '05-templates', patterns: '06-design-patterns', threads: '07-multithreading', strings: '08-strings-regex-time', compiletime: '09-compile-time', rules: '10-coding-rules' };
for (const [topic, lesson] of Object.entries(lessonOf)) {
  const html = readFileSync(join(root, lesson + '.html'), 'utf8');
  const main = (html.match(/<main[^>]*>([\s\S]*)<\/main>/) || [, ''])[1];
  const ids = new Set([...main.matchAll(/<section([^>]*)>/g)].map((m, i) => (m[1].match(/\sid="([^"]+)"/) || [, 's' + (i + 1)])[1]));
  const ctx = { CT: { quizData: {} } };
  vm.runInNewContext(readFileSync(join(dataDir, 'quiz-' + topic + '.js'), 'utf8'), ctx);
  ctx.CT.quizData[topic].questions.forEach((q, i) => {
    if (!q.sec) err('quiz-' + topic + '.js #' + (i + 1) + ': missing sec');
    else if (!ids.has(q.sec)) err('quiz-' + topic + '.js #' + (i + 1) + ': sec "' + q.sec + '" is not a section of ' + lesson + '.html');
  });
}

if (errors.length) { console.error(errors.join('\n')); process.exit(1); }
console.log('interactive/: all checks passed');
