// Checks that the lesson sections named in docs/*-reading-guide.md still exist.
// A reference is the last cell of a table row, such as "3. Smart pointers" or "Inheritance; Polymorphism and virtual functions".
// A leading "N." is accepted when N is the lesson's number (most guides) or the section's position inside its lesson
// (the concurrency guide, which only refers to the multithreading lesson). A title may be shortened to its first words.
// Usage: node tools/check-guides.mjs
import { readFileSync, readdirSync } from 'node:fs';
import { join, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import { loadRegistry, root as interactive } from './lib/registry.mjs';

const repo = resolve(fileURLToPath(new URL('..', import.meta.url)));
const norm = (t) => t.replace(/\([^)]*\)/g, ' ').replace(/<[^>]+>/g, '').toLowerCase().replace(/[^a-z0-9]+/g, ' ').trim();

const reg = loadRegistry();
const titles = [];                                       // { lessonNo, n, title }: every section, plus each lesson itself (n = 0)
reg.lessons.forEach((l, li) => {
  titles.push({ lessonNo: li + 1, n: 0, title: norm(l.title) });
  const html = readFileSync(join(interactive, l.file), 'utf8').replace(/\r\n/g, '\n');
  const main = (html.match(/<main[^>]*>([\s\S]*)<\/main>/) || [, ''])[1];
  [...main.matchAll(/<section([^>]*)>/g)].forEach((m, i) => {
    titles.push({ lessonNo: li + 1, n: i + 1, title: norm((m[1].match(/data-title="([^"]+)"/) || [, ''])[1]) });
  });
});

const pieceOk = (raw) => {
  const m = /^(\d+)\.\s*(.+)$/.exec(raw.trim());
  const want = norm(m ? m[2] : raw);
  if (!want) return true;
  const hits = titles.filter((t) => t.title.includes(want) || want.includes(t.title));
  if (!hits.length) return false;
  return !m || hits.some((t) => t.lessonNo === +m[1] || t.n === +m[1]);
};
const refOk = (cell) => {
  if (pieceOk(cell)) return true;                        // the whole cell is one title
  for (const sep of [/;/, /[;,]/]) {
    const parts = cell.split(sep).map((x) => x.trim()).filter(Boolean);
    if (parts.length > 1 && parts.every(pieceOk)) return true;
  }
  return false;
};

const problems = [];
let checked = 0;
for (const f of readdirSync(join(repo, 'docs')).filter((n) => n.endsWith('-reading-guide.md'))) {
  const lines = readFileSync(join(repo, 'docs', f), 'utf8').replace(/\r\n/g, '\n').split('\n');
  let check = false;                                     // only tables whose last column is "Matching lesson ..."
  lines.forEach((line, i) => {
    if (!/^\|/.test(line)) { check = false; return; }
    const cells = line.split('|').slice(1, -1).map((c) => c.trim());
    if (/^\|[\s:|-]+\|\s*$/.test(line)) {                // the separator row: the row above is the header
      const hdr = lines[i - 1].split('|').slice(1, -1).map((c) => c.trim());
      check = /^matching lesson/i.test(hdr[hdr.length - 1] || '');
      return;
    }
    if (!check || cells.length < 3) return;
    const last = cells[cells.length - 1].replace(/`/g, '');
    if (!last || /^not in the lessons/i.test(last)) return;
    checked++;
    if (!refOk(last)) problems.push(`${f}:${i + 1}: cannot match "${last}" to lesson sections`);
  });
}
console.log(problems.length ? 'PROBLEMS:\n' + problems.join('\n') : `reading guides are consistent with the lessons (${checked} references checked)`);
process.exit(problems.length ? 1 : 0);
