// Guards against a quiz being answerable by option length: the correct answer must not usually be the longest one.
// A question is "tell-tale" when its correct option is at least 15% longer than the longest wrong one (or 25% longer than their average).
// Fails when more than 15% of all questions, or more than 40% of one quiz, are tell-tale (the quizzes shuffle option order, so length is the only cue left).
// Usage: node tools/check-quiz-balance.mjs
import { readFileSync } from 'node:fs';
import { join } from 'node:path';
import vm from 'node:vm';
import { loadRegistry, root } from './lib/registry.mjs';

const reg = loadRegistry();
let total = 0, tell = 0;
const problems = [];
for (const l of reg.lessons) {
  const ctx = { CT: { quizData: {} } };
  vm.runInNewContext(readFileSync(join(root, 'assets', 'data', 'quiz-' + l.id + '.js'), 'utf8'), ctx);
  const qs = ctx.CT.quizData[l.id].questions;
  let n = 0;
  for (const q of qs) {
    const lens = q.opts.map((o) => o.length), c = lens[q.a];
    const others = lens.filter((_, k) => k !== q.a), longest = Math.max(...others), avg = others.reduce((a, b) => a + b, 0) / others.length;
    if (c > longest && (c >= 1.15 * longest || c >= 1.25 * avg)) n++;
  }
  total += qs.length; tell += n;
  if (n / qs.length > 0.4) problems.push(`${l.id}: ${n} of ${qs.length} questions give the answer away by length`);
}
if (tell / total > 0.15) problems.push(`overall: ${tell} of ${total} questions give the answer away by length`);
if (problems.length) { console.error(problems.join('\n')); process.exit(1); }
console.log(`quiz balance: ${tell} of ${total} questions have a noticeably longest correct answer`);
