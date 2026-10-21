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

if (errors.length) { console.error(errors.join('\n')); process.exit(1); }
console.log('interactive/: all checks passed');
