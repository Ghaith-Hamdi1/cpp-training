// Adds a "Read more" note at the end of the lesson sections that a book explains in more depth.
// Each row of a reading guide's tables (docs/*-reading-guide.md) that ends in a "Matching lesson section" column names a
// book section, its PDF pages and the lesson sections it deepens. This tool groups those rows by lesson section and writes
// one note per section, between <!-- read-more:start --> and <!-- read-more:end --> markers. Rows the guides do not carry
// are listed in EXTRA below. Sections no book covers get no note.
// Usage: node tools/build-read-more.mjs [--check]
import { readFileSync, writeFileSync } from 'node:fs';
import { join, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import { loadRegistry, root as interactive } from './lib/registry.mjs';

const repo = resolve(fileURLToPath(new URL('..', import.meta.url)));
const BOOKS = {
  ppp: { order: 0, title: 'Programming: Principles and Practice (Stroustrup)', guide: 'programming-principles-and-practice-reading-guide.md' },
  emc: { order: 1, title: 'Effective Modern C++ (Meyers)', guide: 'effective-modern-cpp-reading-guide.md' },
  mv: { order: 2, title: 'C++ Move Semantics (Josuttis)', guide: 'move-semantics-complete-guide-reading-guide.md' },
  cia: { order: 3, title: 'C++ Concurrency in Action (Williams)', guide: 'concurrency-in-action-reading-guide.md' }
};
const clean = (s) => s.replace(/\*\*/g, '').replace(/`/g, '').trim();
const esc = (s) => s.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
const norm = (s) => s.replace(/\([^)]*\)/g, ' ').replace(/<[^>]+>/g, '').toLowerCase().replace(/[^a-z0-9]+/g, ' ').trim();

/* rows the guides do not carry: lesson id -> [{ book, label, pages, deepens }] */
const EXTRA = {
  objmodel: [
    { book: 'ppp', label: '12.3 Base and derived classes (object layout, the vptr and vtbl, overriding)', pages: '380 to 387', deepens: ['Multiple inheritance and object layout'] },
    { book: 'ppp', label: '15.5 Destructors, including 15.5.2 Virtual destructors', pages: '460 to 463', deepens: ['The diamond problem and virtual inheritance'] }
  ],
  threads: [
    { book: 'cia', label: '2.3 Transferring ownership of a thread; 2.5 Identifying threads', pages: '50 to 53 and 57 to 59', deepens: ['Your first thread'] },
    { book: 'cia', label: '3.3.2 to 3.3.3 Protecting rarely updated data (reader-writer lock); recursive locking', pages: '91 to 95', deepens: ['Other mutex types and call_once'] }
  ],
  tasks: [
    { book: 'cia', label: '2.4 Choosing the number of threads at runtime', pages: '54 to 56', deepens: ['Work stealing and sizing a pool'] },
    { book: 'cia', label: '4.2 Waiting for one-off events with futures (std::async, packaged_task, promise, shared_future)', pages: '104 to 115', deepens: ['Futures and async', 'promise, shared_future and packaged_task'] },
    { book: 'cia', label: '4.3 Waiting with a time limit', pages: '116 to 121', deepens: ['Futures and async'] },
    { book: 'cia', label: '4.4.7 to 4.4.10 Latches and barriers (the Concurrency TS versions of C++20 std::latch and std::barrier)', pages: '141 to 147', deepens: ['latch, barrier, semaphore and stop_token'] },
    { book: 'cia', label: '8.1 Techniques for dividing work between threads', pages: '275 to 282', deepens: ['Work stealing and sizing a pool'] },
    { book: 'cia', label: '9.1 Thread pools (a simple pool, waiting for tasks, work stealing in 9.1.5)', pages: '324 to 337', deepens: ['Thread pools and producer/consumer', 'Work stealing and sizing a pool'] },
    { book: 'cia', label: '9.2 Interrupting threads (the idea behind std::stop_token)', pages: '338 to 349', deepens: ['latch, barrier, semaphore and stop_token'] },
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

/* guide rows that name a whole lesson ("Move semantics", "Smart pointers") are placed by a hint on the row's book and label:
   lesson id -> [[regex over "<book> <label>", text of the section title]] */
const HINTS = {
  moves: [
    [/^emc 14 /, 'writing move operations'], [/^emc 23 /, 'copy versus move'], [/^emc 25 /, 'returning objects'], [/^emc (29|41) /, 'sink parameters'],
    [/^mv (1\.|Chapter 2)/, 'copy versus move'], [/^mv 4\./, 'sink parameters'], [/^mv 6\.1/, 'copy versus move'], [/^mv 6\.3/, 'writing move operations'], [/^ppp 17\./, 'writing move operations']
  ],
  smartptr: [
    [/^emc (18|21|22) /, 'unique ptr in detail'], [/^emc 19 /, 'shared ptr and the control block'], [/^emc 20 /, 'reference cycles'], [/^ppp 18\.4/, 'who owns it']
  ],
  strings: [[/^ppp 9\.11/, 'string streams and files']],
  stl: [[/^mv Chapter 15/, 'vector the workhorse']]
};

const REG = loadRegistry();
const titleCache = {};
const sectionTitles = (no) => {
  const l = REG.lessons[no - 1];
  if (!l) return [];
  if (!titleCache[no]) titleCache[no] = [...readFileSync(join(interactive, l.file), 'utf8').matchAll(/data-title="([^"]+)"/g)].map((m) => norm(m[1])).concat(norm(l.title));
  return titleCache[no];
};
const hasSection = (no, name) => { const n = norm(name); return !!n && sectionTitles(no).some((x) => x.includes(n) || n.includes(x)); };

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
      const per = {}; let cur = null;                                             // lesson number -> section names, carrying the prefix forward
      for (const piece of refs.split(';')) {
        const m = /^\s*(\d+)\.\s*(.+)$/.exec(piece);
        if (m) cur = +m[1];
        if (cur === null) {                                                       // an unnumbered cell: find which default lesson has a section of that name
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

const bounds = (p) => { const n = (p.match(/\d+/g) || []).map(Number); return [Math.min(...n), Math.max(...n)]; };
function rowsFor(lessonNo, id) {
  const merged = new Map();                                                       // the same book pages listed twice become one row
  for (const r of [...parseGuides(lessonNo, id), ...(EXTRA[id] || [])]) {
    const k = r.book + '|' + r.pages;
    if (!merged.has(k)) merged.set(k, { ...r, deepens: [...r.deepens] });
    else for (const d of r.deepens) if (!merged.get(k).deepens.includes(d)) merged.get(k).deepens.push(d);
  }
  let rows = [...merged.values()];
  rows = rows.filter((a) => {                                                     // a row whose pages lie inside a bigger row of the same book is folded into it
    const [as, ae] = bounds(a.pages);
    const big = rows.find((b) => b !== a && b.book === a.book && bounds(b.pages)[0] <= as && bounds(b.pages)[1] >= ae && bounds(b.pages)[1] - bounds(b.pages)[0] > ae - as);
    if (!big) return true;
    for (const d of a.deepens) if (!big.deepens.includes(d)) big.deepens.push(d);
    return false;
  });
  return rows.sort((a, b) => BOOKS[a.book].order - BOOKS[b.book].order || bounds(a.pages)[0] - bounds(b.pages)[0]);
}

function label(r) {                                                               // Effective Modern C++ rows start with the item number
  let l = r.label;
  if (r.book === 'emc') l = l.replace(/^(\d+) to (\d+)\s+/, 'Items $1 to $2, ').replace(/^(\d+)\s+/, 'Item $1, ').replace(/^Item (\d+) /, 'Item $1, ').replace(/^(Items? [\d to]+) ([A-Z])/, '$1, $2');
  return l;
}
function note(rows) {
  const items = rows.map((r) => `<li><i>${esc(BOOKS[r.book].title)}</i>: ${esc(label(r))}, PDF pages ${esc(r.pages)}.</li>`).join('\n');
  return `<!-- read-more:start -->\n<div class="callout tip"><span class="label">Read more</span>This section goes deeper in:\n<ul>\n${items}\n</ul></div>\n<!-- read-more:end -->\n`;
}

function build(l, lessonNo, source) {
  let html = source.replace(/<section id="read-more"[\s\S]*?<\/section>\n\n?/, '').replace(/<!-- read-more:start -->[\s\S]*?<!-- read-more:end -->\n/g, '');
  const secs = [...html.matchAll(/<section[^>]*data-title="([^"]+)"[^>]*>/g)].map((m) => ({ start: m.index, title: norm(m[1]), raw: m[1] }));
  secs.forEach((s) => { s.end = html.indexOf('</section>', s.start); });
  const byIdx = new Map();
  for (const r of rowsFor(lessonNo, l.id)) {
    const targets = new Set();
    const hint = (HINTS[l.id] || []).find(([re]) => re.test(r.book + ' ' + r.label));
    if (hint) {
      const hi = secs.findIndex((s) => s.title.includes(norm(hint[1])));
      if (hi < 0) throw new Error(`${l.file}: no section for the hint "${hint[1]}"`);
      targets.add(hi);
    } else for (const name of r.deepens) {
      const parts = hasSection(lessonNo, name) ? [name] : name.split(',');
      for (const p of parts) {
        const n = norm(p);
        let i = secs.findIndex((s) => n && (s.title.includes(n) || n.includes(s.title)) && s.title !== 'interview cheat sheet');
        if (i < 0) i = 0;                                                         // a lesson-level name: the note goes under the first section
        targets.add(i);
      }
    }
    for (const i of targets) { if (!byIdx.has(i)) byIdx.set(i, []); if (!byIdx.get(i).includes(r)) byIdx.get(i).push(r); }
  }
  for (const i of [...byIdx.keys()].sort((a, b) => b - a)) {
    const end = secs[i].end;
    html = html.slice(0, end) + note(byIdx.get(i)) + html.slice(end);
  }
  return html;
}

const check = process.argv.includes('--check');
let changed = 0;
REG.lessons.forEach((l, i) => {
  const path = join(interactive, l.file);
  const raw = readFileSync(path, 'utf8'); const crlf = raw.includes('\r\n');
  const before = raw.replace(/\r\n/g, '\n');
  const html = build(l, i + 1, before);
  if (html !== before) {
    changed++;
    if (!check) writeFileSync(path, crlf ? html.replace(/\n/g, '\r\n') : html);
  }
});
if (check) { console.log(changed ? `read-more notes are out of date in ${changed} lesson(s): run node tools/build-read-more.mjs` : 'read-more notes are up to date'); process.exit(changed ? 1 : 0); }
console.log(`updated ${changed} lesson page(s)`);
