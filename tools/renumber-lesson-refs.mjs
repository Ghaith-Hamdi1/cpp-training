// Rewrites the lesson numbers that are written by hand in docs, tool data and examples after lessons were removed, added or reordered.
// The number of a lesson is its position in interactive/assets/data/lessons.js. This tool compares the registry at a git ref (default HEAD,
// the state before your edits) with the working copy and rewrites, by lesson id, every number it finds in:
//   - docs/reading/*-reading-guide.md: the "N." in the "Matching lesson" column and the "Matching lessons: **N. ...**" lines
//   - tools/primer-data.mjs: the lesson cell of every I(...) row
//   - "Lesson N", "lessons N and M", "lessons N to M" in prose (docs/reading, tools/primer-data.mjs, tools/build-primer.mjs, README.md, examples)
//   - the lesson table and the "Lessons" column of the reading list in README.md, and the Lesson column of examples/lessons/README.md
// A reference to a lesson that no longer exists is dropped from a list; a lone reference is left alone and printed as MANUAL.
// For a lesson that was split, list its new ids in SPLITS: a plain "Lesson N" then points at the first one, and references that name a
// section of the old lesson are printed as MANUAL because they need a human to pick the right new lesson.
// Run it ONCE per change, before committing: running it twice would renumber twice.
// Usage: node tools/renumber-lesson-refs.mjs [--ref HEAD | --base-file <lessons.js>] [--write]
import { readFileSync, writeFileSync, readdirSync, statSync } from 'node:fs';
import { join, resolve, relative } from 'node:path';
import { fileURLToPath } from 'node:url';
import { execFileSync } from 'node:child_process';
import vm from 'node:vm';
import { loadRegistry } from './lib/registry.mjs';

const repo = resolve(fileURLToPath(new URL('..', import.meta.url)));
const args = process.argv.slice(2);
const ref = args.includes('--ref') ? args[args.indexOf('--ref') + 1] : 'HEAD';
const write = args.includes('--write');

// old lesson id -> its new ids (first one is where a plain "Lesson N" now points). Edit when a lesson is split.
export const SPLITS = {};

const baseFile = args.includes('--base-file') ? args[args.indexOf('--base-file') + 1] : null;       // a lessons.js to compare with instead of a git ref
const oldSource = baseFile ? readFileSync(baseFile, 'utf8') : execFileSync('git', ['show', `${ref}:interactive/assets/data/lessons.js`], { cwd: repo, encoding: 'utf8' });
const sandbox = {}; sandbox.window = sandbox; vm.createContext(sandbox); vm.runInContext(oldSource, sandbox);
const oldIds = sandbox.CT.lessons.map((l) => l.id);
const newReg = loadRegistry();
const newIds = newReg.lessons.map((l) => l.id);

/** New number for an old number, or null when the lesson is gone. */
function mapNum(n) {
  const id = oldIds[n - 1];
  if (!id) return n;                                   // not a lesson number we know: leave it
  const target = SPLITS[id] ? SPLITS[id][0] : id;
  const i = newIds.indexOf(target);
  return i < 0 ? null : i + 1;
}
const survivorAtOrAfter = (n) => { for (let k = n; k <= oldIds.length; k++) { const m = mapNum(k); if (m) return m; } return null; };
const survivorAtOrBefore = (n) => { for (let k = Math.min(n, oldIds.length); k >= 1; k--) { const m = mapNum(k); if (m) return m; } return null; };

const manual = [];
const note = (file, line, text) => manual.push(`${relative(repo, file)}:${line}: ${text}`);

/** Rewrites one run such as "7", "2, 10, 7 and 13" or "16 to 18". Returns the new text, or null if nothing survives. */
function mapRun(run) {
  const parts = run.split(/(,\s*|\s+and\s+|\s+to\s+)/);          // numbers at even indexes, separators at odd ones
  const out = [];
  for (let i = 0; i < parts.length; i += 2) {
    const n = +parts[i], sep = parts[i - 1];
    if (sep && /\sto\s/.test(sep)) {                           // a range: map both ends to survivors
      const a = +parts[i - 2], b = n;
      const na = survivorAtOrAfter(a), nb = survivorAtOrBefore(b);
      if (na && nb && na <= nb) { out.pop(); out.push([na, nb]); }
      continue;
    }
    const m = mapNum(n);
    if (m) out.push(m);
  }
  if (!out.length) return null;
  const txt = (x) => (Array.isArray(x) ? (x[0] === x[1] ? String(x[0]) : `${x[0]} to ${x[1]}`) : String(x));
  if (out.length === 1) return txt(out[0]);
  return out.slice(0, -1).map(txt).join(', ') + ' and ' + txt(out[out.length - 1]);
}

function walk(dir, test, acc = []) {
  for (const name of readdirSync(dir)) {
    const p = join(dir, name);
    if (statSync(p).isDirectory()) { if (name !== 'node_modules' && name !== '.git') walk(p, test, acc); } else if (test(p)) acc.push(p);
  }
  return acc;
}
const posix = (p) => relative(repo, p).replace(/\\/g, '/');
const GENERATED = /^docs\/(reading\/roadmap\/|study-checklist)/;

/** "Lesson N" and friends in prose. */
function prose(text, file) {
  const rx = /\b(Lessons?|lessons?)(\s+)(\d+(?:(?:,\s*|\s+and\s+|\s+to\s+)\d+)*)/g;
  return text.split('\n').map((line, i) => line.replace(rx, (all, word, sp, run) => {
    const ids = run.split(/\D+/).filter(Boolean).map(Number);
    if (ids.some((n) => SPLITS[oldIds[n - 1]]) && /section/i.test(line)) note(file, i + 1, 'names a section of a split lesson: ' + all);
    const m = mapRun(run);
    if (m === null) { note(file, i + 1, 'refers only to removed lessons: ' + all); return all; }
    return word + sp + m;
  })).join('\n');
}

/** The "N." prefixes of a "Matching lesson" cell: "11. Move semantics; Perfect forwarding" or "16. A; 17. B". */
function cell(cellText) {
  let cur = null; const kept = [];
  for (const piece of cellText.split(';')) {
    const m = /^(\s*)(\d+)\.(\s*)(.*)$/.exec(piece);
    if (m) cur = +m[2];
    const nn = cur === null ? null : mapNum(cur);
    if (cur !== null && nn === null) continue;                 // a removed lesson (and the unnumbered pieces that inherit it)
    kept.push(m ? `${m[1]}${nn}.${m[3]}${m[4]}` : piece);
  }
  if (!kept.length) return null;
  return kept.map((p, i) => (i === 0 ? p : ' ' + p.trimStart())).join(';');
}

function guide(text) {
  const lines = text.split('\n'); let check = false;
  return lines.map((line, i) => {
    if (!/^\|/.test(line)) { check = false; return line.replace(/(Matching lessons?:)(.*)$/, (all, a, rest) => a + rest.replace(/\*\*(\d+)\.([^*]*)\*\*/g, (x, n, t) => { const m = mapNum(+n); return m ? `**${m}.${t}**` : ''; })); }
    if (/^\|[\s:|-]+\|\s*$/.test(line)) { const hdr = lines[i - 1].split('|').slice(1, -1).map((c) => c.trim()); check = /^matching lesson/i.test(hdr[hdr.length - 1] || ''); return line; }
    if (!check) return line;
    const cells = line.split('|');                              // ['', c1, ..., cn, '']
    const last = cells[cells.length - 2];
    if (/^\s*not in the lessons/i.test(last) || !/\d+\./.test(last)) return line;
    const next = cell(last.replace(/^\s+|\s+$/g, ''));
    cells[cells.length - 2] = ' ' + (next === null ? 'Not in the lessons' : next) + ' ';
    return cells.join('|');
  }).join('\n');
}

function primerData(text) {
  return text.split('\n').map((line) => {
    if (!/^\s*I\(/.test(line)) return line;
    return line.replace(/'((?:[^'\\]|\\.)*)'(\)\s*,?)\s*$/, (all, c, tail) => {
      if (!/\d+\./.test(c)) return all;
      const next = cell(c);
      return next === null ? `NL${tail}` : `'${next}'${tail}`;
    });
  }).join('\n');
}

function readme(text) {
  const BASE = 'https://ghaith-hamdi1.github.io/cpp-training/';
  const rows = newReg.lessons.map((l, i) => `| ${i + 1} | [${l.title.replace(/&/g, 'and')}](${BASE}${l.file}) | [Quiz](${BASE}${l.quiz}) |`);
  text = text.replace(/(\| # \| Lesson \| Quiz \|\n\|[-| ]+\|\n)(?:\|[^\n]*\n)+/, (all, head) => head + rows.join('\n') + '\n');
  // the "Lessons" column of the reading list: | n | **Book** | why | 2, 7, 9 |
  return text.split('\n').map((line) => {
    const m = /^(\| \d+ \| \*\*.*\| )((?:\d+)(?:, \d+)*)( \|)$/.exec(line);
    if (!m) return line;
    const nums = m[2].split(', ').map(Number).map(mapNum).filter(Boolean);
    return m[1] + (nums.length ? nums.join(', ') : 'none') + m[3];
  }).join('\n');
}

function examplesReadme(text) {
  let drop = false;
  return text.split('\n').filter((line) => {
    const m = /^\| (\d+) ([^|]*)\|/.exec(line);
    if (m) { drop = mapNum(+m[1]) === null; return !drop; }
    if (/^\|\s{1,2}\|/.test(line) && drop) return false;      // continuation row of a removed lesson
    if (/^\|/.test(line) && !/^\|\s*\|/.test(line)) drop = false;
    return true;
  }).map((line) => line.replace(/^\| (\d+) /, (all, n) => `| ${mapNum(+n)} `)).join('\n');
}

const files = [
  ...walk(join(repo, 'docs', 'reading'), (p) => p.endsWith('.md') && !GENERATED.test(posix(p))),
  join(repo, 'tools', 'primer-data.mjs'), join(repo, 'tools', 'build-primer.mjs'), join(repo, 'README.md'),
  join(repo, 'examples', 'lessons', 'README.md'),
  ...walk(join(repo, 'examples', 'lessons'), (p) => p.endsWith('.cpp')),
];
let changed = 0;
for (const f of files) {
  const rel = posix(f);
  const raw = readFileSync(f, 'utf8'); const crlf = raw.includes('\r\n');
  let text = raw.replace(/\r\n/g, '\n');
  const before = text;
  if (/reading-guide\.md$/.test(rel)) text = guide(text);
  if (rel === 'tools/primer-data.mjs') text = primerData(text);
  if (rel === 'README.md') text = readme(text);
  if (rel === 'examples/lessons/README.md') text = examplesReadme(text);
  if (rel.endsWith('.cpp')) { const head = text.split('\n').slice(0, 3).join('\n'); text = prose(head, f) + text.slice(head.length); }
  else text = prose(text, f);
  if (text !== before) {
    changed++;
    if (write) writeFileSync(f, crlf ? text.replace(/\n/g, '\r\n') : text);
  }
}
console.log(`${write ? 'rewrote' : 'would rewrite'} ${changed} file(s); ${oldIds.length} lessons at ${ref}, ${newIds.length} now`);
for (const m of manual) console.log('MANUAL ' + m);
