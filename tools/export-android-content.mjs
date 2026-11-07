// Exports the lessons, quiz questions and recap cards of the site as one JSON file for the Android app
// (android-quiz/app/src/main/assets/content.json), so a fix to a quiz on the site also reaches the app.
//
// Chapters follow the themes of lessons-pdf/ (the roadmap phases, with the strings lesson as the optional last chapter).
// Every lesson becomes one or more path nodes of 5 to 8 items: its quiz questions in order, with its recap cards as
// the info slides in front. A chapter is "ready" when the app should show it; the others appear as "coming soon".
// Usage: node tools/export-android-content.mjs [--check]
import { mkdirSync, readFileSync, readdirSync, writeFileSync, existsSync } from 'node:fs';
import { join, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';
import { loadRegistry, root as interactive } from './lib/registry.mjs';

const repo = resolve(fileURLToPath(new URL('..', import.meta.url)));
const out = join(repo, 'android-quiz', 'app', 'src', 'main', 'assets', 'content.json');
const check = process.argv.includes('--check');

const CHAPTERS = [
  { id: 'core', title: '1. Core language foundations', lessons: ['basics', 'pointers', 'types', 'casts'], ready: true },
  { id: 'classes', title: '2. Classes, memory and OOP', lessons: ['oop', 'copying', 'inherit'], ready: true },
  { id: 'library', title: '3. Standard library and generic programming', lessons: ['callables', 'lambdas', 'stl', 'assoc', 'iterators', 'algorithms', 'templates', 'classtemplates', 'compiletime'], ready: false },
  { id: 'raii', title: '4. RAII, exceptions and advanced tools', lessons: ['core'], ready: false },
  { id: 'modern', title: '5. Modern C++', lessons: ['vocab', 'moves', 'copymove', 'writemoves', 'elision', 'sinks', 'forwarding', 'uniqueptr', 'smartptr', 'weakptr'], ready: false },
  { id: 'concurrency', title: '6. Concurrency and the memory model', lessons: ['threads', 'races', 'mutexes', 'deadlock', 'condvars', 'tasks', 'pools', 'atomics', 'memmodel'], ready: false },
  { id: 'further', title: '7. Further reading', lessons: ['strings'], ready: false },
];

const dataDir = join(interactive, 'assets', 'data');
const ctx = {};
ctx.window = ctx;
vm.createContext(ctx);
const run = (f) => vm.runInContext(readFileSync(join(dataDir, f), 'utf8'), ctx, { filename: f });
run('lessons.js');
ctx.CT.quizData = {};
for (const f of readdirSync(dataDir).filter((f) => /^quiz-.*\.js$/.test(f))) run(f);
run('mock-bank.js');
const CT = ctx.CT;
const lessonById = new Map(CT.lessons.map((l) => [l.id, l]));

const decode = (s) => s.replace(/&lt;/g, '<').replace(/&gt;/g, '>').replace(/&quot;/g, '"').replace(/&amp;/g, '&');
/** The recap HTML uses only div, p, code, i and b; the app understands **bold** and `code`. */
function htmlToMarkup(html) {
  return decode(
    html
      .replace(/<\/p>\s*<p>/g, '\n\n')
      .replace(/<code>(.*?)<\/code>/gs, '`$1`')
      .replace(/<b>(.*?)<\/b>/gs, '**$1**')
      .replace(/<\/?(div|p|i)>/g, '')
  ).trim();
}

function questionType(q) {
  const text = q.q;
  if (q.code) {
    if (/print|output|result|what is|value|display|prints|outputs/i.test(text)) return 'OUTPUT';
    if (/wrong|bug|mistake|fix|problem|fails|compil/i.test(text)) return 'BUG';
    return 'CONCEPT';
  }
  if (q.opts.length === 2 && /^true$/i.test(q.opts[0]) && /^false$/i.test(q.opts[1])) return 'TRUE_FALSE';
  return 'CONCEPT';
}

const problems = [];
const questions = [];
const chapters = [];
const counts = { lessons: 0, questions: 0, cards: 0 };

for (const ch of CHAPTERS) {
  const nodes = [];
  for (const lessonId of ch.lessons) {
    const lesson = lessonById.get(lessonId);
    const quiz = CT.quizData[lessonId];
    if (!lesson || !quiz) { problems.push(`lesson ${lessonId}: missing registry entry or quiz`); continue; }
    counts.lessons++;

    const ids = quiz.questions.map((q, i) => {
      const id = `${lessonId}:${i}`;
      if (q.opts.length < 2 || q.a < 0 || q.a >= q.opts.length) problems.push(`${id}: bad options or answer index`);
      questions.push({
        id,
        type: questionType(q),
        topic: lesson.title,
        prompt: q.q.trim(),
        code: q.code ? q.code.replace(/^\n/, '').replace(/\s+$/, '') : undefined,
        options: q.opts.map((o) => o.trim()),
        answer: q.a,
        explanation: (q.why || '').trim(),
      });
      counts.questions++;
      return id;
    });

    // 5 to 8 items per node: split a lesson into ceil(n / 8) nodes of near-equal size.
    const parts = Math.max(1, Math.ceil(ids.length / 8));
    const cards = CT.mockBank.filter((c) => c.topic === lessonId)
      .map((c) => `**${htmlToMarkup(c.q)}**\n\n${htmlToMarkup(c.a)}`);
    counts.cards += cards.length;
    let qi = 0;
    let ci = 0;
    for (let p = 0; p < parts; p++) {
      const take = Math.floor(ids.length / parts) + (p < ids.length % parts ? 1 : 0);
      const cardTake = Math.floor(cards.length / parts) + (p < cards.length % parts ? 1 : 0);
      nodes.push({
        id: `${lessonId}:n${p}`,
        title: parts > 1 ? `${lesson.title} (${p + 1}/${parts})` : lesson.title,
        intro: cards.slice(ci, ci + cardTake),
        items: ids.slice(qi, qi + take),
      });
      qi += take;
      ci += cardTake;
    }
  }
  chapters.push({ id: ch.id, title: ch.title, ready: ch.ready, nodes });
}

// Lint: long code lines and leftovers the app cannot show.
for (const q of questions) {
  if (q.code) {
    const longest = Math.max(...q.code.split('\n').map((l) => l.length));
    if (longest > 60) problems.push(`${q.id}: code line of ${longest} characters (the app shrinks the font to fit)`);
  }
  for (const t of [q.prompt, q.explanation, ...q.options]) {
    if (/<(p|div|code|b|i)>/.test(t)) problems.push(`${q.id}: HTML left in text`);
  }
}

const json = JSON.stringify({ chapters, questions }, null, 1) + '\n';
const nodeCount = chapters.reduce((n, c) => n + c.nodes.length, 0);
console.log(`${counts.lessons} lessons, ${nodeCount} nodes, ${counts.questions} questions, ${counts.cards} recap cards`);
const fatal = problems.filter((p) => !/the app shrinks the font/.test(p));
for (const p of problems) console.log((fatal.includes(p) ? 'ERROR ' : 'note  ') + p);
if (fatal.length) process.exit(1);

if (check) {
  const same = existsSync(out) && readFileSync(out, 'utf8').replace(/
/g, '
') === json;
  if (!same) { console.log('content.json is out of date: run node tools/export-android-content.mjs'); process.exit(1); }
  console.log('content.json is up to date');
} else {
  mkdirSync(join(repo, 'android-quiz', 'app', 'src', 'main', 'assets'), { recursive: true });
  writeFileSync(out, json);
  console.log('wrote ' + out);
}
