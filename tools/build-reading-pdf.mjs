// Builds a printable PDF of the book-reading checklist (docs/reading-checklist.pdf) from the "Book reading (core)" lists in
// docs/study-checklist.md, plus the optional move-semantics deep dive. Needs Microsoft Edge or Chrome for the HTML-to-PDF step.
// Usage: node tools/build-reading-pdf.mjs   (run tools/build-checklist.mjs first if the roadmap changed)
import { readFileSync, writeFileSync, existsSync, mkdtempSync, rmSync } from 'node:fs';
import { resolve, join } from 'node:path';
import { tmpdir } from 'node:os';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { execFileSync } from 'node:child_process';

const repo = resolve(fileURLToPath(new URL('..', import.meta.url)));
const md = readFileSync(resolve(repo, 'docs/study-checklist.md'), 'utf8').replace(/\r\n/g, '\n');
const esc = (s) => s.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
const inl = (t) => esc(t).replace(/`([^`]+)`/g, '<code>$1</code>');

const items = (block) => block.split('\n').filter((l) => l.startsWith('- [ ] ')).map((l) => l.slice(6));
const phases = [];
for (const part of md.split(/^## /m).slice(1)) {
  const title = part.split('\n')[0];
  const m = /^Phase (\d+): (.*?) \(about ([\d.]+) hours\)$/.exec(title);
  if (!m) continue;
  const read = /### Book reading \(core\)\n([\s\S]*?)(?=\n### |\n## |$)/.exec(part);
  if (read) phases.push({ title: `Phase ${m[1]}: ${m[2]}`, rows: items(read[1]) });
}
const deep = /## Move semantics deep dive \(optional\)\n([\s\S]*?)\n---/.exec(md);
if (deep) phases.push({ title: 'Optional: move semantics deep dive', rows: items(deep[1]) });

const split = (row) => {
  const m = /^(C\+\+ [A-Za-z ]+?|Effective Modern C\+\+|Programming: Principles and Practice): (.*) \(PDF pages ([^)]*)\)$/.exec(row);
  return m ? { book: m[1], what: m[2], pages: m[3] } : { book: '', what: row, pages: '' };
};
const core = phases.filter((p) => !p.title.startsWith('Optional'));
const total = core.reduce((n, p) => n + p.rows.length, 0);
const html = `<!doctype html><html lang="en"><meta charset="utf-8"><title>C++ book reading checklist</title>
<style>
@page { size: A4; margin: 14mm 14mm 16mm; }
body { font: 10.5pt/1.35 "Segoe UI", Arial, sans-serif; color: #111; }
h1 { font-size: 20pt; margin: 0 0 2mm; }
.sub { color: #444; margin: 0 0 5mm; }
h2 { font-size: 12.5pt; margin: 6mm 0 1.5mm; padding-bottom: 1mm; border-bottom: 1.5px solid #111; break-after: avoid; }
table { width: 100%; border-collapse: collapse; }
tr { break-inside: avoid; }
td { padding: 1.6mm 1.5mm; border-bottom: 0.5px solid #bbb; vertical-align: top; }
td.box { width: 6mm; }
.box i { display: block; width: 4mm; height: 4mm; border: 1.3px solid #111; margin-top: 0.5mm; }
td.pg { width: 34mm; text-align: right; color: #333; font-size: 9.5pt; }
.book { font-weight: 600; }
code { font: 9.5pt Consolas, monospace; background: #eee; padding: 0 1px; }
.note { color: #555; font-size: 9pt; margin-top: 5mm; }
</style>
<h1>C++ book reading checklist</h1>
<p class="sub">${total} core reading blocks across ${core.length} phases (phase 6 has none), in study order, plus an optional move-semantics deep dive. Page numbers are PDF page numbers (the number your PDF viewer shows), not the numbers printed on the book pages. Tick a box when you have finished the block.</p>
${phases.map((p) => `<h2>${esc(p.title)}</h2><table>${p.rows.map((r) => { const x = split(r); return `<tr><td class="box"><i></i></td><td><span class="book">${esc(x.book)}</span>${x.book ? ': ' : ''}${inl(x.what)}</td><td class="pg">${x.pages ? 'PDF pp. ' + esc(x.pages) : ''}</td></tr>`; }).join('')}</table>`).join('\n')}
<p class="note">From the cpp-training study checklist. Interactive version with saved progress: https://ghaith-hamdi1.github.io/cpp-training/study-checklist.html</p>
</html>`;

const browsers = ['C:/Program Files (x86)/Microsoft/Edge/Application/msedge.exe', 'C:/Program Files/Microsoft/Edge/Application/msedge.exe', 'C:/Program Files/Google/Chrome/Application/chrome.exe', '/usr/bin/google-chrome', '/usr/bin/chromium'];
const exe = process.env.BROWSER || browsers.find(existsSync);
if (!exe) throw new Error('No Edge or Chrome found; set BROWSER to its path');
const tmp = mkdtempSync(join(tmpdir(), 'reading-pdf-'));
try {
  const page = join(tmp, 'reading-checklist.html');
  writeFileSync(page, html);
  const out = resolve(repo, 'docs/reading-checklist.pdf');
  execFileSync(exe, ['--headless', '--disable-gpu', '--no-pdf-header-footer', `--user-data-dir=${join(tmp, 'profile')}`, `--print-to-pdf=${out}`, pathToFileURL(page).href], { stdio: 'ignore' });
  console.log('wrote docs/reading-checklist.pdf (' + total + ' blocks)');
} finally { rmSync(tmp, { recursive: true, force: true }); }
