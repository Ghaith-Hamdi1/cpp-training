// Checks the page numbers in the reading guides, plans and roadmap against the book PDFs.
// For every table row that gives a section number and an "N to M" PDF page range, the start page must contain a heading line that
// begins with that section number (or "Item N" for Effective Modern C++, "Chapter N" for a whole chapter). It needs `pdftotext`
// (poppler) on the PATH and the PDFs in books/, so it needs poppler-utils (CI installs it); you can also run it by hand after editing page ranges.
// Usage: node tools/check-book-pages.mjs [--verbose]
import { readFileSync, readdirSync, existsSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { join, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';

const repo = resolve(fileURLToPath(new URL('..', import.meta.url)));
const verbose = process.argv.includes('--verbose');
const BOOKS = {
  primer: { pdf: 'Cpp-Primer-5th-Edition-Lippman.pdf', style: 'num' },
  ppp: { pdf: 'Programming-Principles-and-Practice-Using-Cpp-3rd-Edition-Stroustrup.pdf', style: 'num' },
  emc: { pdf: 'Effective-Modern-Cpp-Meyers.pdf', style: 'item' },
  mv: { pdf: 'Cpp-Move-Semantics-The-Complete-Guide-Josuttis.pdf', style: 'num' },
  cia: { pdf: 'Cpp-Concurrency-in-Action-2nd-Edition-Williams.pdf', style: 'num' }
};
const bookOfFile = (f) => /primer/i.test(f) ? 'primer' : /programming-principles/i.test(f) ? 'ppp' : /effective-modern/i.test(f) ? 'emc' : /move-semantics/i.test(f) ? 'mv' : /concurrency/i.test(f) ? 'cia' : null;
const bookOfName = (n) => /primer/i.test(n) ? 'primer' : /^PPP|Programming/i.test(n) ? 'ppp' : /^EMC|Effective/i.test(n) ? 'emc' : /Move Semantics/i.test(n) ? 'mv' : /Concurrency/i.test(n) ? 'cia' : null;

const cache = {};
const pagesFor = (book) => {
  if (book in cache) return cache[book];
  const pdf = join(repo, 'books', BOOKS[book].pdf);
  if (!existsSync(pdf)) return (cache[book] = null);
  const txt = execFileSync('pdftotext', ['-layout', pdf, '-'], { encoding: 'utf8', maxBuffer: 1 << 28 });
  return (cache[book] = txt.split('\f').map((p) => p.split('\n').map((l) => l.trim()).filter(Boolean)));
};

const problems = [];
let checked = 0;
const rangeRe = /(\d+) to (\d+)/g;
const hasHeading = (lines, book, id) => {
  if (/^\d+$/.test(id)) {
    if (BOOKS[book].style === 'item') return lines.some((l) => new RegExp('^Item ' + id + '\\b').test(l));
    return lines.some((l) => new RegExp('^(Chapter )?' + id + '\\s+[A-Z]').test(l) || new RegExp('^Chapter ' + id + '\\b', 'i').test(l));
  }
  const esc = id.replace(/\./g, '\\.');
  return lines.some((l) => new RegExp('^' + esc + '(\\s|\\.\\s)+\\S').test(l));
};
const firstId = (piece) => {
  const t = piece.replace(/\*\*/g, '').replace(/`/g, '');
  const dotted = /(?:^|[\s(])(\d+\.\d+(?:\.\d+)*)(?=[\s,.):]|$)/.exec(t);
  if (dotted) return dotted[1];
  const m = /^(?:Items? |ch\. )?(\d+)(?=[\s:,.]|$)/.exec(t);
  return m ? m[1] : null;
};

const files = [];
const dir = join(repo, 'docs', 'reading');
for (const n of readdirSync(dir)) if (/-reading-(guide|plan)\.md$/.test(n)) files.push(join(dir, n));
for (const n of readdirSync(join(dir, 'roadmap'))) if (/^phase-/.test(n)) files.push(join(dir, 'roadmap', n));

for (const f of files) {
  const fileBook = /phase-/.test(f) ? null : bookOfFile(f);
  const lines = readFileSync(f, 'utf8').replace(/\r\n/g, '\n').split('\n');
  let hdr = null;
  lines.forEach((line, li) => {
    if (!/^\|/.test(line)) { hdr = null; return; }
    const cells = line.split('|').slice(1, -1).map((c) => c.trim());
    if (/^\|[\s:|-]+\|\s*$/.test(line)) { hdr = lines[li - 1].split('|').slice(1, -1).map((c) => c.trim()); return; }
    if (!hdr) return;
    const pageCol = hdr.findIndex((h) => /pdf pages/i.test(h));
    const secCol = hdr.findIndex((h) => /^(read|book section|section|item|chapters? and sections|chapters)/i.test(h) && !/session|matching|lesson/i.test(h));
    const bookCol = hdr.findIndex((h) => /^book$/i.test(h));
    if (pageCol < 0 || secCol < 0) return;
    const book = fileBook || (bookCol >= 0 ? bookOfName(cells[bookCol] || '') : null);
    const secCell = cells[secCol];
    const pageCell = (cells[pageCol] || '').replace(/\*\*/g, '');
    if (!book || !secCell || !/\d+ to \d+/.test(pageCell)) return;
    const ranges = [...pageCell.matchAll(rangeRe)].map((m) => [+m[1], +m[2]]);
    const pg = pagesFor(book);
    if (!pg) return;
    const pieces = secCell.split(';').map((p) => p.trim()).filter(Boolean);
    const pair = pieces.length === ranges.length ? pieces.map((p, i) => [p, ranges[i]]) : [[pieces[0], ranges[0]]];
    for (const [piece, [a, b]] of pair) {
      const id = firstId(piece);
      if (!id) continue;
      checked++;
      const rel = f.slice(repo.length + 1).replace(/\\/g, '/') + ':' + (li + 1);
      if (a < 1 || b > pg.length || a > b) { problems.push(`${rel}: ${book} pages ${a} to ${b} are outside the book (${pg.length} pages)`); continue; }
      if (hasHeading(pg[a - 1], book, id) || (/^\d+$/.test(id) && /^ch\./.test(piece) && hasHeading(pg[a - 1], book, id + '.1'))) { if (verbose) console.log('ok  ', rel, book, id, a); continue; }
      const near = [a - 1, a + 1].filter((p) => p >= 1 && p <= pg.length && hasHeading(pg[p - 1], book, id));
      problems.push(`${rel}: ${book} "${id}" is not on page ${a}` + (near.length ? ` (found on page ${near.join(' or ')})` : ' (not on a neighbouring page either)') + `  [${piece.slice(0, 50)}]`);
    }
  });
}
console.log(problems.length ? 'PROBLEMS:\n' + problems.join('\n') : 'all section starts are on the pages given');
console.log(`checked ${checked} section starts`);
process.exit(problems.length ? 1 : 0);
