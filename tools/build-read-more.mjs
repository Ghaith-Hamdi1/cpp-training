// Builds the "Read more in the books" section of every lesson from the reading guides (docs/*-reading-guide.md).
// Each row of a guide's tables that ends in a "Matching lesson section" column names a book section, its PDF pages and the
// lesson sections it deepens. This tool groups those rows by lesson and writes one table into each lesson page, just
// before the interview cheat sheet. A few rows the guides do not carry are listed in EXTRA below.
// Usage: node tools/build-read-more.mjs [--check]
import { readFileSync, writeFileSync } from 'node:fs';
import { join, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import { loadRegistry, root as interactive } from './lib/registry.mjs';

const repo = resolve(fileURLToPath(new URL('..', import.meta.url)));
const GH = 'https://github.com/Ghaith-Hamdi1/cpp-training/blob/main/';
const BOOKS = {
  ppp: { order: 0, title: 'Programming: Principles and Practice Using C++, 3rd ed. (Stroustrup)', file: 'Programming-Principles-and-Practice-Using-Cpp-3rd-Edition-Stroustrup.pdf', guide: 'programming-principles-and-practice-reading-guide.md' },
  emc: { order: 1, title: 'Effective Modern C++ (Meyers)', file: 'Effective-Modern-Cpp-Meyers.pdf', guide: 'effective-modern-cpp-reading-guide.md' },
  mv: { order: 2, title: 'C++ Move Semantics: The Complete Guide (Josuttis)', file: 'Cpp-Move-Semantics-The-Complete-Guide-Josuttis.pdf', guide: 'move-semantics-complete-guide-reading-guide.md' },
  cia: { order: 3, title: 'C++ Concurrency in Action, 2nd ed. (Williams)', file: 'Cpp-Concurrency-in-Action-2nd-Edition-Williams.pdf', guide: 'concurrency-in-action-reading-guide.md' }
};
const clean = (s) => s.replace(/\*\*/g, '').replace(/`/g, '').trim();
const esc = (s) => s.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');

/* rows the guides do not carry: lesson id -> [{ book, label, pages, deepens }] */
const EXTRA = {
  objmodel: [
    { book: 'ppp', label: '12.3 Base and derived classes (object layout, the vptr and vtbl, overriding)', pages: '380 to 387', deepens: ['Multiple inheritance and object layout (single-inheritance layout)'] },
    { book: 'ppp', label: '15.5 Destructors, including 15.5.2 Virtual destructors', pages: '460 to 463', deepens: ['The diamond problem and virtual inheritance (why a polymorphic base needs a virtual destructor)'] }
  ],
  threads: [
    { book: 'cia', label: '2.3 Transferring ownership of a thread; 2.5 Identifying threads', pages: '50 to 53 and 57 to 59', deepens: ['Your first thread'] },
    { book: 'cia', label: '3.3.2 to 3.3.3 Protecting rarely updated data (reader-writer lock); recursive locking', pages: '91 to 95', deepens: ['Other mutex types and call_once'] }
  ],
  tasks: [
    { book: 'cia', label: '2.4 Choosing the number of threads at runtime', pages: '54 to 56', deepens: ['Work stealing and sizing a pool'] },
    { book: 'cia', label: '4.2 Waiting for one-off events with futures (std::async, packaged_task, promise, shared_future)', pages: '104 to 115', deepens: ['Futures and async', 'promise, shared_future and packaged_task'] },
    { book: 'cia', label: '4.3 Waiting with a time limit', pages: '116 to 121', deepens: ['Futures and async'] },
    { book: 'cia', label: '4.4.7 to 4.4.10 Latches and barriers (the Concurrency TS versions of C++20 std::latch and std::barrier)', pages: '141 to 147', deepens: ['latch, barrier, semaphore and stop_token (C++20)'] },
    { book: 'cia', label: '8.1 Techniques for dividing work between threads', pages: '275 to 282', deepens: ['Work stealing and sizing a pool'] },
    { book: 'cia', label: '9.1 Thread pools (a simple pool, waiting for tasks, work stealing in 9.1.5)', pages: '324 to 337', deepens: ['Thread pools and producer/consumer', 'Work stealing and sizing a pool'] },
    { book: 'cia', label: '9.2 Interrupting threads (the idea behind std::stop_token)', pages: '338 to 349', deepens: ['latch, barrier, semaphore and stop_token (C++20)'] },
    { book: 'cia', label: '10.1 to 10.3 Parallel algorithms: execution policies and the parallel standard algorithms', pages: '350 to 362', deepens: ['Parallel algorithms'] }
  ],
  atomics: [
    { book: 'cia', label: '5.1 Memory model basics (objects, memory locations, modification orders)', pages: '148 to 150', deepens: ['Memory orders and happens-before'] },
    { book: 'cia', label: '5.2 Atomic operations and types in C++ (atomic_flag, atomic<bool>, pointers, integers, free functions)', pages: '151 to 164', deepens: ['Atomic operations and compare_exchange'] },
    { book: 'cia', label: '5.3 Synchronizing operations and enforcing ordering (synchronizes-with, happens-before, the memory orders, release sequences, fences)', pages: '165 to 196', deepens: ['Memory orders and happens-before', 'Ordering patterns that matter'] },
    { book: 'cia', label: '6.2 Lock-based concurrent data structures (a thread-safe stack and queue, fine-grained locks)', pages: '199 to 216', deepens: ['Thread-safe data structures'] },
    { book: 'cia', label: '7.1 to 7.3 Lock-free data structures: definitions, a lock-free stack, memory reclamation, the ABA problem', pages: '229 to 274', deepens: ['Thread-safe data structures', 'Atomic operations and compare_exchange'] }
  ],
  latency: [
    { book: 'cia', label: '8.3 Designing data structures for multithreaded performance', pages: '289 to 292', deepens: ['Threads, cores and busy-polling'] }
  ],
  compiletime: [
    { book: 'emc', label: 'Item 15 Use constexpr whenever possible', pages: '115 to 121', deepens: ['constexpr, consteval, constinit'] },
    { book: 'emc', label: 'Items 26 to 27 Overloading on universal references and its alternatives (tag dispatch, enable_if)', pages: '195 to 215', deepens: ['enable_if and SFINAE'] }
  ]
};
/* lessons whose guide rows for a book are replaced by the fuller list in EXTRA (the guides pick interview essentials, these lessons go deeper) */
const REPLACE = { tasks: ['cia'], atomics: ['cia'] };

const NONE = {
  patterns: 'The books in <code>books/</code> touch patterns only in passing (the rows above). For a full treatment in modern C++, <i>C++ Software Design</i> by Klaus Iglberger covers Strategy, Observer, Decorator, Visitor and more; it is not in <code>books/</code>, so there are no page numbers here.',
  patterns2: 'None of the four books in <code>books/</code> covers these patterns. <i>C++ Software Design</i> by Klaus Iglberger covers Command, Decorator, Adapter, Visitor and type erasure in modern C++; it is not in <code>books/</code>, so there are no page numbers here.',
  wire: 'None of the four books in <code>books/</code> covers binary wire formats, endianness or zero-copy parsing in depth. The lesson and its programs are the main source.',
  rules: 'None of the four books in <code>books/</code> covers MISRA, AUTOSAR or static-analysis practice. The lesson is the main source; the rules themselves are published by the MISRA and AUTOSAR bodies.'
};

const REG = loadRegistry();
const normName = (s) => s.replace(/\([^)]*\)/g, ' ').replace(/<[^>]+>/g, '').toLowerCase().replace(/[^a-z0-9]+/g, ' ').trim();
const titleCache = {};
function hasSection(no, name) {                                                  // does lesson number `no` have a section (or title) like `name`?
  const l = REG.lessons[no - 1];
  if (!l) return false;
  if (!titleCache[no]) titleCache[no] = [...readFileSync(join(interactive, l.file), 'utf8').matchAll(/data-title="([^"]+)"/g)].map((m) => normName(m[1])).concat(normName(l.title));
  const n = normName(name);
  return !!n && titleCache[no].some((x) => x.includes(n) || n.includes(x));
}

function parseGuides(lessonNo, id) {
  const rows = [];
  for (const [key, b] of Object.entries(BOOKS)) {
    if ((REPLACE[id] || []).includes(key)) continue;
    const lines = readFileSync(join(repo, 'docs', b.guide), 'utf8').replace(/\r\n/g, '\n').split('\n');
    let check = false;
    let defaults = [];                                                           // lessons named by the latest "Matching lesson(s): **N. ...**" line
    lines.forEach((line, i) => {
      if (!/^\|/.test(line)) { check = false; if (/Matching lessons?:/.test(line)) defaults = [...line.matchAll(/\*\*(\d+)\./g)].map((x) => +x[1]); return; }
      if (/^\|[\s:|-]+\|\s*$/.test(line)) { const hdr = lines[i - 1].split('|').slice(1, -1).map((c) => c.trim()); check = /^matching lesson/i.test(hdr[hdr.length - 1] || ''); return; }
      if (!check) return;
      let cells = line.split('|').slice(1, -1).map((c) => c.trim());
      if (/^(\d+|optional)$/i.test(cells[0])) cells = cells.slice(1);
      const refs = cells[cells.length - 1];
      if (!refs || /^not in the lessons/i.test(refs)) return;
      const pi = cells.findIndex((c, k) => k > 0 && /^\d+( to \d+)?( and \d+( to \d+)?)*(, \d+ to \d+)*$/.test(c));
      if (pi < 1) return;
      const per = {}; let cur = null;                                         // lesson number -> section names, carrying the prefix forward
      for (const piece of refs.split(';')) {
        const m = /^\s*(\d+)\.\s*(.+)$/.exec(piece);
        if (m) cur = +m[1];
        if (cur === null) {                                                      // an unnumbered cell: find which default lesson has a section of that name
          const n = defaults.find((d) => hasSection(d, clean(piece)));
          if (n === undefined) continue;
          (per[n] = per[n] || []).push(clean(piece));
          continue;
        }
        (per[cur] = per[cur] || []).push(clean(m ? m[2] : piece));
      }
      if (per[lessonNo]) rows.push({ book: key, label: clean(cells[pi - 1]), pages: cells[pi], deepens: per[lessonNo] });
    });
  }
  return rows;
}

const firstPage = (p) => +(/\d+/.exec(p) || [0])[0];
function sectionFor(lessonNo, id) {
  const rows = [...parseGuides(lessonNo, id), ...(EXTRA[id] || [])];
  const merged = new Map();                                                    // the same book pages listed twice become one row
  for (const r of rows) {
    const k = r.book + '|' + r.pages;
    if (!merged.has(k)) merged.set(k, { ...r, deepens: [...r.deepens] });
    else for (const d of r.deepens) if (!merged.get(k).deepens.includes(d)) merged.get(k).deepens.push(d);
  }
  const bounds = (p) => { const n = (p.match(/\d+/g) || []).map(Number); return [Math.min(...n), Math.max(...n)]; };
  let rowsLeft = [...merged.values()];
  rowsLeft = rowsLeft.filter((a) => {                                        // a row whose pages lie inside a bigger row of the same book is folded into it
    const [as, ae] = bounds(a.pages);
    const big = rowsLeft.find((b) => b !== a && b.book === a.book && bounds(b.pages)[0] <= as && bounds(b.pages)[1] >= ae && (bounds(b.pages)[1] - bounds(b.pages)[0] > ae - as));
    if (!big) return true;
    for (const d of a.deepens) if (!big.deepens.includes(d)) big.deepens.push(d);
    return false;
  });
  const list = rowsLeft.sort((a, b) => BOOKS[a.book].order - BOOKS[b.book].order || firstPage(a.pages) - firstPage(b.pages));
  let body;
  if (!list.length) body = `<p>${NONE[id] || 'None of the four books in <code>books/</code> covers this topic in depth. The lesson and its programs are the main source.'}</p>`;
  else {
    const trs = list.map((r) => `<tr><td><a href="${GH}docs/${BOOKS[r.book].guide}">${esc(BOOKS[r.book].title)}</a></td><td>${esc(r.label)}</td><td>${esc(r.pages)}</td><td>${r.deepens.map(esc).join('; ')}</td></tr>`).join('\n');
    body = `<table>\n<tr><th>Book</th><th>Chapter or section</th><th>PDF pages</th><th>Deepens</th></tr>\n${trs}\n</table>` + (NONE[id] ? `\n<p>${NONE[id]}</p>` : '');
  }
  return `<section id="read-more" data-title="Read more in the books">
<h2>Read more in the books</h2>
<p>These book sections explain the same ideas in more depth. Page numbers are <b>PDF pages</b>, the number your PDF reader shows, in the files under <code>books/</code>. Each book's reading guide in <code>docs/</code> has its full plan.</p>
${body}
</section>`;
}

/* every "Deepens" name must be a real section of the lesson (loosely, as in check-guides) */
const norm = (s) => s.replace(/\([^)]*\)/g, ' ').replace(/<[^>]+>/g, '').toLowerCase().replace(/[^a-z0-9]+/g, ' ').trim();
function checkNames(l, html, block) {
  const titles = [...html.matchAll(/data-title="([^"]+)"/g)].map((m) => norm(m[1])).concat(norm(l.title));
  for (const m of block.matchAll(/<td>([^<]*)<\/td><\/tr>/g)) {
    for (const plain of m[1].replace(/&amp;/g, '&').replace(/&lt;/g, '<').replace(/&gt;/g, '>').split('; ')) {
      const name = plain;
      const hit = (s) => { const n = norm(s); return !n || titles.some((x) => x.includes(n) || n.includes(x)); };
      if (!hit(plain) && !plain.split(',').every(hit)) throw new Error(l.file + ': "Deepens" names no section: ' + name);
    }
  }
}

const check = process.argv.includes('--check');
const reg = loadRegistry();
let changed = 0;
reg.lessons.forEach((l, i) => {
  const path = join(interactive, l.file);
  const raw = readFileSync(path, 'utf8'); const crlf = raw.includes('\r\n');
  let html = raw.replace(/\r\n/g, '\n');
  const block = sectionFor(i + 1, l.id);
  checkNames(l, html, block);
  const old = html.match(/<section id="read-more"[\s\S]*?<\/section>\n\n?/);
  if (old) html = html.replace(old[0], block + '\n\n');
  else {
    const m = /<section([^>]*)data-title="Interview cheat sheet">/.exec(html);
    if (!m) throw new Error(l.file + ': no cheat sheet section');
    let cheat = m[0];
    if (!/\sid="/.test(m[1])) {                                                // keep the cheat sheet's positional id (s<position>) stable
      const pos = (html.slice(0, m.index).match(/<section[\s>]/g) || []).length + 1;
      cheat = cheat.replace('<section', `<section id="s${pos}"`);
    }
    html = html.slice(0, m.index) + block + '\n\n' + cheat + html.slice(m.index + m[0].length);
  }
  if (html !== raw.replace(/\r\n/g, '\n')) {
    changed++;
    if (!check) writeFileSync(path, crlf ? html.replace(/\n/g, '\r\n') : html);
  }
});
if (check) { console.log(changed ? `read-more sections are out of date in ${changed} lesson(s): run node tools/build-read-more.mjs` : 'read-more sections are up to date'); process.exit(changed ? 1 : 0); }
console.log(`updated ${changed} lesson page(s)`);
