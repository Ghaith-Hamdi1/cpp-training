// Scaffolds a new lesson: the lesson page, the quiz page and its data file, the registry entry, and the quiz <script> tags in
// interactive/assess.html and interactive/review.html (the only hand edits a new lesson needs outside its own files).
// The new quiz starts with no questions and `assess: 0`; write the questions, then set `assess: 2` in the registry.
// Usage: node tools/new-lesson.mjs <id> "<Title>" --phase <1-6> [--after <lesson id>] [--time "40 min"] [--blurb "..."] [--lead "..."]
//   <id>        lowercase letters and digits, used in saved progress (for example `pointers`)
//   --after     put the lesson right after this one in the study order (default: at the end)
// The file names are NN-<id>.html and NN-<id>-quiz.html, with NN the next unused number (the site numbers lessons by registry position).
import { readFileSync, writeFileSync, readdirSync, existsSync } from 'node:fs';
import { join, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';

const root = resolve(fileURLToPath(new URL('..', import.meta.url)), 'interactive');
const argv = process.argv.slice(2);
const opt = (name, dflt) => { const i = argv.indexOf('--' + name); return i >= 0 ? argv[i + 1] : dflt; };
const [id, title] = argv.filter((a, i) => !a.startsWith('--') && !(i > 0 && argv[i - 1].startsWith('--')));
if (!id || !title || !/^[a-z0-9]+$/.test(id)) {
  console.error('Usage: node tools/new-lesson.mjs <id> "<Title>" --phase <1-6> [--after <id>] [--time "40 min"] [--blurb "..."] [--lead "..."]');
  process.exit(1);
}
const phase = +opt('phase', 0);
if (!(phase >= 1)) { console.error('--phase is required'); process.exit(1); }
const time = opt('time', '40 min');
const blurb = opt('blurb', 'TODO: one sentence for the lesson card.');
const lead = opt('lead', 'TODO: one or two sentences that say what this lesson covers and what it assumes.');
const after = opt('after', null);

const lessonsJs = join(root, 'assets', 'data', 'lessons.js');
const reg = readFileSync(lessonsJs, 'utf8');
if (new RegExp(`id: '${id}'`).test(reg)) { console.error(`A lesson with id '${id}' already exists.`); process.exit(1); }
const prefixes = readdirSync(root).map((f) => /^(\d+)-/.exec(f)).filter(Boolean).map((m) => +m[1]);
const nn = String(Math.max(0, ...prefixes) + 1).padStart(2, '0');
const file = `${nn}-${id}.html`, quiz = `${nn}-${id}-quiz.html`;
for (const f of [file, quiz]) if (existsSync(join(root, f))) { console.error(f + ' already exists'); process.exit(1); }

const head = (t) => `<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>${t}</title>
<script>try{var t=JSON.parse(localStorage.getItem('cpptrain:theme'));if(t)document.documentElement.dataset.theme=t}catch(e){}</script>
<link rel="stylesheet" href="assets/style.css">
</head>
`;
const esc = (s) => s.replace(/&/g, '&amp;').replace(/</g, '&lt;');

writeFileSync(join(root, file), head(esc(title)) + `<body data-topic="${id}" data-kind="lesson">
<main>
<h1>${esc(title)}</h1>
<p class="lead">${esc(lead)}</p>

<section id="intro" data-title="TODO: first idea">
<h2>TODO: first idea</h2>
<p>Say it in plain words first. Then show it in a picture (see docs/maintaining/visual-kit.md), then in about ten lines of code.</p>
<figure class="fig"><svg viewBox="0 0 640 120" role="img" aria-label="TODO: what the picture shows"><text class="t" x="10" y="24">TODO</text></svg><figcaption>TODO</figcaption></figure>
<script type="text/x-cpp">
// about ten lines, one idea
</script>
</section>

<section id="cheat" data-title="Cheat sheet">
<h2>Cheat sheet</h2>
<p>Answer aloud, then open.</p>
<details class="ex"><summary>TODO: a question you could be asked in an interview?</summary><div><p>TODO: the short answer.</p></div></details>
</section>

</main>

<script src="assets/data/lessons.js"></script>
<script src="assets/app.js"></script>
</body>
</html>
`);

writeFileSync(join(root, quiz), head('Quiz: ' + esc(title)) + `<body data-topic="${id}" data-kind="quiz">
<main>
<h1>Quiz: ${esc(title)}</h1>
<p class="lead">TODO: one line.</p>
<div id="quiz"></div>
</main>
<script src="assets/data/lessons.js"></script>
<script src="assets/app.js"></script>
<script src="assets/data/quiz-${id}.js"></script>
<script>CT.quiz('#quiz', CT.quizData.${id});</script>
</body>
</html>
`);

writeFileSync(join(root, 'assets', 'data', `quiz-${id}.js`), `/* Quiz questions for the '${id}' topic. Loaded by ${quiz}.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.${id} = {
  id: '${id}',
  questions: [
  ]
};
`);

// registry entry
const entry = `  { id: '${id}', file: '${file}', quiz: '${quiz}', title: '${title.replace(/'/g, "\\'")}', time: '${time}', assess: 0, phase: ${phase},
    blurb: '${blurb.replace(/'/g, "\\'")}' }`;
let nl = reg.includes('\r\n') ? '\r\n' : '\n';
let src = reg.replace(/\r\n/g, '\n');
if (after) {
  const m = new RegExp(`  \\{ id: '${after}'.*?\\n    blurb: .*?\\}(,?)\\n`, 's').exec(src);
  if (!m) { console.error(`No lesson '${after}' in the registry`); process.exit(1); }
  const here = m[0].replace(/\},?\n$/, '},\n');
  src = src.slice(0, m.index) + here + entry + (m[1] ? ',' : '') + '\n' + src.slice(m.index + m[0].length);
} else {
  const m = /(\n    blurb: [^\n]*?)\s*\}\n\];\n/.exec(src);                      // the end of CT.lessons
  if (!m) { console.error('Could not find the end of CT.lessons'); process.exit(1); }
  src = src.slice(0, m.index) + m[1] + ' },\n' + entry + '\n];\n' + src.slice(m.index + m[0].length);
}
writeFileSync(lessonsJs, src.replace(/\n/g, nl));

// quiz script tags in assess.html and review.html, after the last quiz tag
for (const page of ['assess.html', 'review.html']) {
  const p = join(root, page);
  const t = readFileSync(p, 'utf8'); nl = t.includes('\r\n') ? '\r\n' : '\n';
  const lines = t.replace(/\r\n/g, '\n').split('\n');
  const last = lines.map((l, i) => (/assets\/data\/quiz-[a-z0-9]+\.js/.test(l) ? i : -1)).filter((i) => i >= 0).pop();
  lines.splice(last + 1, 0, `<script src="assets/data/quiz-${id}.js"></script>`);
  writeFileSync(p, lines.join('\n').replace(/\n/g, nl));
}
console.log(`created ${file}, ${quiz}, quiz-${id}.js, a registry entry (assess: 0) and the tags in assess.html and review.html`);
console.log('Next: write the lesson, the examples under examples/lessons/, the quiz; then node tools/build-search-index.mjs, build-mock-bank.mjs, build-precache.mjs, build-read-more.mjs, build-checklist.mjs');
