// Prints every lesson page in interactive/ to its own PDF in docs/lessons-pdf/ with headless Edge or Chrome (light theme, every recap
// answer opened, and print CSS that keeps figures, code blocks, callouts, tables and widgets whole: one that does not fit at the bottom of
// a page moves to the next page; only a block taller than a page is split). Code lines wrap instead of being clipped.
// Left out of the PDFs: the "Predict" exercises, the "Cheat sheet" section, terminal-command blocks (g++ ..., ./main) and every interactive widget (step-through walk-throughs,
// simulators, testers, advisors), together with the sentence that introduces each. Three simulators and the container advisor are replaced by
// a short static table. The "Read more" book notes of a lesson are collected into one "Further reading" box at the end of the lesson, and
// a few sections are moved within their lesson where that reads better on paper (see ORDER in pdfPrep).
// The "Read more" book notes are taken out of the sections and listed per section (book, chapter and PDF pages) on a last page of their own.
// The files are numbered in study order (lesson 1 upwards, as in the registry), not by the page's own file name, and sit in one folder per theme
// (the roadmap phase: 01-core-language-foundations, 02-classes-..., plus 07-further-reading for the optional lesson).
// A lesson with `optional: true` in the registry is printed as NN-further-reading-<name>.pdf.
// Needs Edge or Chrome. Usage: node tools/build-lessons-pdf.mjs
import { existsSync, mkdirSync, mkdtempSync, readdirSync, rmSync, unlinkSync, writeFileSync } from 'node:fs';
import { resolve, join } from 'node:path';
import { tmpdir } from 'node:os';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { spawn } from 'node:child_process';
import { loadRegistry, root } from './lib/registry.mjs';

const repo = resolve(fileURLToPath(new URL('..', import.meta.url)));
const registry = loadRegistry();
const lessons = registry.lessons;
const slug = (t) => t.replace(/\(.*?\)/g, '').toLowerCase().replace(/c\+\+/g, 'cpp').replace(/&/g, 'and').replace(/[^a-z0-9]+/g, '-').replace(/^-|-$/g, '');
/** The theme folder of a lesson: its roadmap phase (01-core-language-foundations ...), or 07-further-reading for the optional lesson. */
const folderOf = (l) => { if (l.optional) return '07-further-reading'; const ph = registry.phases.find((p) => p.n === l.phase); return String(ph.n).padStart(2, '0') + '-' + slug(ph.name); };
const exe = process.env.BROWSER || ['C:/Program Files (x86)/Microsoft/Edge/Application/msedge.exe', 'C:/Program Files/Microsoft/Edge/Application/msedge.exe', 'C:/Program Files/Google/Chrome/Application/chrome.exe', '/usr/bin/google-chrome', '/usr/bin/chromium'].find(existsSync);
if (!exe) throw new Error('No Edge or Chrome found; set BROWSER to its path');

const PAGE_PX = 1005;   // printable page height in CSS px (A4 11.69in less 0.4in and 0.45in margins), with a little slack
// Blocks are kept whole on one page, except a code block taller than SPLIT_CODE_PX or a list taller than SPLIT_LIST_PX, which may continue on the
// next page (at a line or an item) so that a long block does not leave half a page empty. 0 keeps everything whole.
const SPLIT_CODE_PX = +(process.env.SPLIT_CODE_PX ?? 400);
const SPLIT_LIST_PX = +(process.env.SPLIT_LIST_PX ?? 150);
const PRINT_CSS = `
  h1, h2, h3, h4, summary { break-after: avoid; }
  figure, figure.code, .fig, .callout, .widget, .card, details, table, table tr, pre, svg, blockquote, .sim, .stepper, .ex { break-inside: avoid; }
  table { overflow: visible !important; }
  figure.code, figure.code *, pre { overflow: visible !important; max-width: 100% !important; }
  pre, pre code, figure.code code { white-space: pre-wrap !important; overflow-wrap: anywhere; }
  svg, img, table { max-width: 100% !important; }
  p, li, dd, dt, h1, h2, h3, h4, h5, summary, figcaption, .lead, thead, tr { break-inside: avoid; }
  ul, ol { break-inside: avoid-page; }
  p, li { orphans: 3; widows: 3; }
  section > p:has(+ figure), section > p:has(+ .widget), section > p:has(+ table), section > p:has(+ details) { break-after: avoid; }
  figure.code.may-split, figure.code.may-split pre { break-inside: auto; }
  figure.code.may-split pre { orphans: 4; widows: 4; }
  ul.may-split, ol.may-split { break-inside: auto; }
  .further-page { break-before: page; }
  .further-page table { display: table; width: 100%; break-inside: auto; font-size: 0.82rem; }
  .further-page thead { display: table-header-group; }
  .further-page td, .further-page th { padding: 0.28em 0.6em; line-height: 1.35; }
  .further-page td.pg { white-space: nowrap; }
  .further-page tr.grp td { border-top: 2px solid #999; }
`;

// Runs inside the lesson page (serialized with toString) before it is printed. Only touches the DOM, so it must not use anything from this file.
function pdfPrep(file, splitCodePx, splitListPx) {
  const $$ = (sel, scope = document) => [...scope.querySelectorAll(sel)];
  const esc = (t) => String(t).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
  const norm = (t) => t.replace(/\s+/g, ' ').trim();
  const table = (head, rows, widths, style) => '<table' + (style ? ' style="' + style + '"' : '') + '><tr>' + head.map((h, i) => '<th' + (widths ? ' style="width:' + widths[i] + '"' : '') + '>' + h + '</th>').join('') + '</tr>' + rows.map((r) => '<tr>' + r.map((c) => '<td>' + c + '</td>').join('') + '</tr>').join('') + '</table>';

  // "Predict" exercises (the other collapsible recap questions stay)
  $$('details.ex').forEach((d) => { const t = d.querySelector('.ex-tag'); if (t && t.textContent.trim() === 'Predict') d.remove(); });

  // The cheat sheet at the end of every lesson
  $$('main > section').forEach((s) => { const h = s.querySelector('h2'); if (h && /^cheat sheet/i.test(h.textContent.trim())) s.remove(); });

  // Terminal commands: code blocks whose first line is a shell command (compile and run lines)
  const SHELL = /^(\$ |g\+\+|clang\+\+|gcc |cmake|make\b|ninja|\.\/|valgrind|gdb|lldb|perf |taskset)/;
  $$('figure.code').forEach((f) => {
    const first = ((f.querySelector('pre') || f).textContent.split('\n').find((l) => l.trim()) || '').trim();
    if (SHELL.test(first)) f.remove();
  });

  // Static stand-ins for the widgets whose idea matters on paper, keyed by widget id
  const STATIC = {
    'sim-race': table(['Step', 'Thread', 'What runs', 'r in that thread', 'counter afterwards'], [
      ['1', 'A', '<code>r = counter</code>', '0', '0'],
      ['2', 'B', 'first increment: <code>r = counter</code>, <code>r = r + 1</code>, <code>counter = r</code>', '1', '1'],
      ['3', 'B', 'second increment, the same three lines', '2', '2'],
      ['4', 'A', '<code>r = r + 1</code> (still working from the old value 0)', '1', '2'],
      ['5', 'A', '<code>counter = r</code> overwrites both of B\'s increments', '1', '1'],
      ['6', 'A', 'second increment: <code>r = counter</code>, <code>r = r + 1</code>, <code>counter = r</code>', '2', '2']
    ]) + '<p>One bad schedule: the final value is <b>2</b>, not 4. Two increments were lost.</p>',
    'sim-deadlock': table(['Step', 'Thread', 'Runs', 'State afterwards'], [
      ['1', 'A', '<code>a.lock()</code>', 'A holds a'],
      ['2', 'B', '<code>b.lock()</code>', 'B holds b'],
      ['3', 'A', '<code>b.lock()</code>', 'A waits for b, which B holds'],
      ['4', 'B', '<code>a.lock()</code>', 'B waits for a, which A holds: <b>deadlock</b>, neither can ever continue']
    ]),
    'ms-publish': table(['<code>ready.store(true, ...)</code>', '<code>ready.load(...)</code>', 'What the consumer prints'], [
      ['<code>release</code> (or <code>seq_cst</code>)', '<code>acquire</code> (or <code>seq_cst</code>)', 'always <b>42</b>'],
      ['<code>relaxed</code>', '<code>acquire</code>', 'may print <b>0</b>: the flag can become visible before the data'],
      ['<code>release</code>', '<code>relaxed</code>', 'may print <b>0</b>: nothing guarantees the data is visible after the load'],
      ['<code>relaxed</code>', '<code>relaxed</code>', 'may print <b>0</b>']
    ]),
    'w-choose': table(['I need to...', 'Use', 'Why'], [
      ['iterate over items, access by index, mostly append at the end', '<code>std::vector</code>', 'Contiguous memory: fastest iteration and indexing, amortised O(1) <code>push_back</code>. This is the default choice.'],
      ['hold a fixed number of items known at compile time', '<code>std::array</code>', 'Lives inline (no heap), knows its size, zero overhead over a C array.'],
      ['push and pop at both ends (a deque of work)', '<code>std::deque</code>', 'O(1) push/pop at front and back while still allowing indexing.'],
      ['insert/erase often in the middle while holding iterators that must stay valid', '<code>std::list</code>', 'O(1) splice/insert/erase at a known position and stable iterators. Costs: a heap allocation per node and poor cache locality. Measure before choosing it.'],
      ['look up values by key; order does not matter', '<code>std::unordered_map</code>', 'Hash table: average O(1) find/insert/erase. Needs a hash and <code>operator==</code>.'],
      ['look up by key AND iterate in sorted order, or find the nearest key', '<code>std::map</code>', 'Balanced tree: O(log n), sorted iteration, <code>lower_bound</code>/<code>upper_bound</code> for range queries.'],
      ['check membership / remove duplicates (no values attached)', '<code>std::unordered_set</code>', 'Hash set: average O(1) contains. Use <code>std::set</code> if you also need the elements sorted.'],
      ['count how often each word occurs', '<code>std::unordered_map&lt;std::string, int&gt;</code>', '<code>counts[word]++</code> inserts a zero on first sight and increments in one expression.'],
      ['last-in first-out (undo, DFS, matching brackets)', '<code>std::stack</code>', 'Adaptor over deque/vector exposing only push, pop and top.'],
      ['first-in first-out (task queue, BFS)', '<code>std::queue</code>', 'Adaptor over deque exposing push, pop, front and back.'],
      ['always process the largest (or smallest) item next', '<code>std::priority_queue</code>', 'A binary heap: O(log n) push/pop, O(1) top. Largest first by default; pass <code>std::greater</code> for smallest first.']
    ], ['34%', '24%', '42%'], 'font-size:0.78rem')
  };

  // Every interactive widget goes, with the sentence that introduces it
  const PROMPT_START = /^(try\b|pick\b|explore|watch|play\b|send events)/i;
  const TRAIL = /\s*(Try it|Explore|Send events|Play the scheduler with .*?|Play A and B .*?|Step A once, B once, then try to go on)\s*:\s*$/i;
  $$('.widget').forEach((w) => {
    const prev = w.previousElementSibling, next = w.nextElementSibling;
    if (prev && prev.tagName === 'P') {
      const txt = norm(prev.textContent);
      if (w.id === 'ms-publish') prev.innerHTML = 'What the consumer can print in the publish-with-a-flag example above, for each pair of memory orders:';
      else if (/^Try patterns \(/.test(txt)) prev.innerHTML = '<code>std::regex</code> uses the ECMAScript grammar.';
      else if (/^step through/i.test(txt) || (txt.length <= 100 && PROMPT_START.test(txt))) prev.remove();
      else if (TRAIL.test(prev.innerHTML)) prev.innerHTML = prev.innerHTML.replace(TRAIL, '');
      else if (/:$/.test(txt) && !(next && /^(UL|OL)$/.test(next.tagName))) prev.innerHTML = prev.innerHTML.replace(/:\s*$/, '.');
    }
    if (STATIC[w.id]) w.insertAdjacentHTML('afterend', STATIC[w.id]);
    w.remove();
  });

  // Sentences that referred to a widget (replacement null: drop the paragraph)
  const FIXES = [
    ['07-multithreading.html', /^Hint: A loads, B runs fully, A finishes\. Or press <b>Run 500 random schedules<\/b>\.$/, null],
    ['07-multithreading.html', /^Run 500 random schedules: <b>always 4<\/b>\.$/, 'With the lock, the result is <b>always 4</b>.'],
    ['07-multithreading.html', /^"Run 500 random schedules": many end in deadlock\.\s*/, ''],
    ['07-multithreading.html', /The simulator switches far more often than a real OS\.\s*A real race/, 'A real race'],
    ['18-atomics-memory-model.html', /The simulator above shows/, 'The table of outcomes above shows'],
    ['18-atomics-memory-model.html', / with a simulator,/, ','],
    ['08-strings-regex-time.html', /\s*but not in the tester/, ''],
    ['01-basics.html', /\s*\(see the step-through above\)/, ''],
    // sentences that only point at the website or at the repo (nothing to click on paper)
    ['02-oop.html', /^Related notes in your repo:/, null],
    ['04-stl.html', /^Notes: <a[^>]*>Module 3<\/a>\.$/, null],
    ['05-templates.html', /^Notes: <a[^>]*>Module 4<\/a>; <a[^>]*>modern-cpp-features<\/a>\.$/, null],
    ['16-types-and-casts.html', /\s*Full lists: <a[^>]*>modern-cpp-features<\/a>, <a[^>]*>modern-cpp-tutorial<\/a>\. Your notes: <a[^>]*>Module 3<\/a>\./, ''],
    ['07-multithreading.html', /^<span class="label">Where next<\/span>/, null],
    ['07-multithreading.html', /^Further reading: your notes in /, null],
    // wording that depended on the original section order
    ['08-strings-regex-time.html', /then <code>&lt;regex&gt;<\/code> and <code>&lt;chrono&gt;<\/code>/, 'then <code>&lt;chrono&gt;</code> and <code>&lt;regex&gt;</code>']
  ];
  for (const [f, re, rep] of FIXES) {
    if (f !== file) continue;
    $$('main p, main td, main li, main .callout').forEach((el) => {
      if (!re.test(el.innerHTML)) return;
      if (rep === null) el.remove(); else el.innerHTML = el.innerHTML.replace(re, rep);
    });
  }

  // The "Phase N of 8 ... checklist, book reading" line above the title: keep the phase and lesson number, drop the two website links
  $$('main > *').forEach((e) => {
    if (/Phase \d+ of \d+/.test(e.textContent) && /book reading/.test(e.textContent)) e.innerHTML = e.innerHTML.replace(/\s*(?:·|&middot;)\s*<a[^>]*>checklist<\/a>\s*(?:·|&middot;)\s*<a[^>]*>book reading<\/a>/, '');
  });

  // "Read more" notes: taken out of the sections and listed per section on a page of their own at the end of the lesson
  const notes = $$('.callout').filter((c) => { const lb = c.querySelector(':scope > .label'); return lb && /^read more$/i.test(lb.textContent.trim()); });
  const reading = new Map();   // section element -> Map(book title -> Map(entry text -> entry html))
  for (const n of notes) {
    const section = n.closest('section');
    if (!section) { n.remove(); continue; }
    const books = reading.get(section) || new Map();
    let title = '';
    for (const el of n.children) {
      if (el.tagName === 'P') title = norm(el.textContent);
      else if (el.tagName === 'UL') {
        const items = books.get(title) || new Map();
        for (const li of el.children) { const key = norm(li.textContent); if (!items.has(key)) items.set(key, li.innerHTML); }
        books.set(title, items);
      }
    }
    reading.set(section, books);
    n.remove();
  }

  // Sections moved within their lesson (the lessons themselves keep their order)
  const ORDER = {
    '01-basics.html': [['Where variables live: stack, heap, static', 'before', 'Dynamic memory: new and delete']],
    '02-oop.html': [['explicit, conversion operators and copy-and-swap', 'before', 'Composition, relationships and design'], ['Operator overloading', 'before', 'Composition, relationships and design']],
    '08-strings-regex-time.html': [['Inside std::string: SSO and capacity', 'before', 'String streams and files'], ['Regular expressions', 'after', 'Time with std::chrono']],
    '04-stl.html': [['Which container should I use?', 'before', 'Custom keys: comparators and hashes']],
    '09-compile-time.html': [['constexpr, consteval, constinit', 'before', 'enable_if and SFINAE']],
  };
  const sec = (title) => $$('main > section').find((s) => s.dataset.title === title);
  for (const [t, where, anchor] of ORDER[file] || []) {
    const s = sec(t), a = sec(anchor);
    if (!s || !a) { console.log('ORDER: section not found in ' + file + ': ' + (s ? anchor : t)); continue; }
    if (where === 'before') a.before(s); else a.after(s);
  }
  if (reading.size) {
    const page = document.createElement('section');
    page.className = 'further-page';
    const rows = [];
    for (const s of $$('main > section').filter((x) => reading.has(x))) {
      const title = esc(s.dataset.title || norm(s.querySelector('h2').textContent));
      let first = true;
      for (const [book, items] of reading.get(s)) {
        const shortBook = book.replace(/\s*\([^)]*\)\s*$/, '');   // drop the authors
        for (const h of items.values()) {
          const m = h.match(/^([\s\S]*?)\s*\(PDF pages? ([^()]*)\)\s*$/);
          rows.push('<tr' + (first ? ' class="grp"' : '') + '><td>' + (first ? '<b>' + title + '</b>' : '') + '</td><td>' + esc(shortBook) + '</td><td>' + (m ? m[1] : h) + '</td><td class="pg">' + (m ? esc(m[2]) : '') + '</td></tr>');
          first = false;
        }
      }
    }
    page.innerHTML = '<h2>Further reading by section</h2><p>Where each section of this lesson is explained in more depth. Pages are PDF viewer pages (the number your PDF reader shows).</p>' +
      '<table><thead><tr><th style="width:22%">Section</th><th style="width:26%">Book</th><th style="width:40%">Part of the book</th><th style="width:12%">PDF pages</th></tr></thead><tbody>' + rows.join('') + '</tbody></table>';
    $$('main > section').pop().after(page);
  }
  // A trailing comment that would wrap onto the next line (and start at the left margin, looking like code) goes on a line of its own above
  // the code line it belongs to, wrapped to the line width and indented like the code
  $$('pre').forEach((pre) => {
    const box = pre.querySelector(':scope > code') || pre;
    const style = getComputedStyle(pre);
    const probe = document.createElement('span');
    probe.style.cssText = 'visibility:hidden;white-space:pre';
    probe.textContent = 'x'.repeat(100);
    box.appendChild(probe);
    const charWidth = probe.getBoundingClientRect().width / 100;
    probe.remove();
    const limit = Math.floor((pre.clientWidth - parseFloat(style.paddingLeft) - parseFloat(style.paddingRight)) / charWidth) - 1;   // characters per printed line
    if (!(limit > 20)) return;
    const wrapComment = (text, indent) => {
      const pad = ' '.repeat(indent);
      const lines = [];
      let cur = '';
      for (const w of text.replace(/^\/\/\s?/, '').split(/\s+/).filter(Boolean)) {
        if (cur && pad.length + 3 + cur.length + 1 + w.length > limit) { lines.push(cur); cur = w; } else cur = cur ? cur + ' ' + w : w;
      }
      if (cur) lines.push(cur);
      return lines.map((l) => pad + '// ' + l).join('\n');
    };
    let col = 0, indent = 0, hasCode = false, inIndent = true, line = 0;
    let last = null;   // the trailing comment of the previous line: { line, span, text, indent } when it was moved above its code, else { line }
    let lineStart = { node: box.firstChild, offset: 0 };
    const step = (ch) => {
      if (inIndent && (ch === ' ' || ch === '\t')) indent++; else { inIndent = false; if (ch !== ' ' && ch !== '\t') hasCode = true; }
      col++;
    };
    for (const node of [...box.childNodes]) {
      if (node.nodeType === 3) {
        const t = node.nodeValue;
        for (let i = 0; i < t.length; i++) {
          if (t[i] === '\n') { col = 0; indent = 0; hasCode = false; inIndent = true; line++; lineStart = { node, offset: i + 1 }; } else step(t[i]);
        }
      } else if (node.nodeType === 1) {
        const t = node.textContent;
        const lineComment = node.classList.contains('tk-cm') && /^\/\//.test(t) && !t.includes('\n');
        if (lineComment && col + t.length > limit) {
          if (hasCode) {
            const prev = node.previousSibling;
            if (prev && prev.nodeType === 3) prev.nodeValue = prev.nodeValue.replace(/[ \t]+$/, '');
            const moved = document.createElement('span');
            moved.className = 'tk-cm';
            moved.textContent = wrapComment(t, indent) + '\n';
            if (lineStart.node.nodeType === 3) lineStart.node.splitText(lineStart.offset).before(moved); else lineStart.node.before(moved);
            node.remove();
            last = { line, span: moved, text: t, indent };
          } else if (indent >= 20 && last && last.line === line - 1) {
            // a comment that continues the previous line's comment, aligned to the comment column
            if (last.span) {
              last.text += ' ' + t.replace(/^\/\/\s?/, '');
              last.span.textContent = wrapComment(last.text, last.indent) + '\n';
              const prev = node.previousSibling;
              if (prev && prev.nodeType === 3) prev.nodeValue = prev.nodeValue.replace(/\n[ \t]*$/, '');
              node.remove();
              last.line = line;
            }
          } else node.textContent = wrapComment(t, indent);
        } else {
          if (lineComment && hasCode) last = { line };
          for (const ch of t) step(ch);
        }
      }
    }
  });

  // Long code blocks and lists may continue on the next page; everything else stays whole
  if (splitCodePx) $$('figure.code').forEach((f) => { if (f.offsetHeight > splitCodePx) f.classList.add('may-split'); });
  if (splitListPx) $$('main ul, main ol').forEach((l) => { if (l.offsetHeight > splitListPx) l.classList.add('may-split'); });
  return $$('.widget, .threadsim, select').length;   // anything left over is reported by the caller
}

const tmp = mkdtempSync(join(tmpdir(), 'lessons-pdf-'));
const port = 9333;
const browser = spawn(exe, ['--headless', '--disable-gpu', `--remote-debugging-port=${port}`, `--user-data-dir=${join(tmp, 'profile')}`, 'about:blank'], { stdio: 'ignore' });
const sleep = (ms) => new Promise((r) => setTimeout(r, ms));
try {
  let target;
  for (let i = 0; i < 50 && !target; i++) { await sleep(200); try { target = (await (await fetch(`http://127.0.0.1:${port}/json`)).json()).find((t) => t.type === 'page'); } catch { /* not up yet */ } }
  if (!target) throw new Error('browser did not start');
  const ws = new WebSocket(target.webSocketDebuggerUrl);
  await new Promise((r) => (ws.onopen = r));
  let id = 0; const pending = new Map(); const events = [];
  ws.onmessage = (m) => { const d = JSON.parse(m.data); if (d.id && pending.has(d.id)) { pending.get(d.id)(d); pending.delete(d.id); } else events.push(d.method); };
  const send = (method, params = {}) => new Promise((res, rej) => { const i = ++id; pending.set(i, (d) => (d.error ? rej(new Error(method + ': ' + d.error.message)) : res(d.result))); ws.send(JSON.stringify({ id: i, method, params })); });
  await send('Page.enable');
  await send('Emulation.setDeviceMetricsOverride', { width: 698, height: 1000, deviceScaleFactor: 1, mobile: false });
  await send('Emulation.setEmulatedMedia', { media: 'print' });

  const dir = resolve(repo, 'docs/lessons-pdf');
  mkdirSync(dir, { recursive: true });
  for (const f of readdirSync(dir, { withFileTypes: true })) {                    // the numbering can change, so start clean (only what this tool names)
    if (f.isFile() && /^\d\d-.*\.pdf$/.test(f.name)) unlinkSync(join(dir, f.name));
    else if (f.isDirectory() && /^\d\d-/.test(f.name)) rmSync(join(dir, f.name), { recursive: true, force: true });
  }
  for (const [k, l] of lessons.entries()) {
    events.length = 0;
    await send('Page.navigate', { url: pathToFileURL(join(root, l.file)).href });
    for (let i = 0; i < 100 && !events.includes('Page.loadEventFired'); i++) await sleep(100);
    const ev = await send('Runtime.evaluate', { returnByValue: true, expression: `document.documentElement.dataset.theme='light'; document.head.appendChild(Object.assign(document.createElement('style'), { textContent: ${JSON.stringify(PRINT_CSS)} })); document.querySelectorAll('details').forEach(d => d.open = true); document.fonts.ready.then(() => (${pdfPrep.toString()})(${JSON.stringify(l.file)}, ${SPLIT_CODE_PX}, ${SPLIT_LIST_PX}))`, awaitPromise: true });
    if (ev.exceptionDetails) console.log('JS error', l.file, JSON.stringify(ev.exceptionDetails.exception && ev.exceptionDetails.exception.description || ev.exceptionDetails.text).slice(0, 300));
    else if (ev.result.value) console.log('widgets left in', l.file, ev.result.value);
    await sleep(400);
    // a block that fits on one page is never split; report any block taller than a page
    const rep = await send('Runtime.evaluate', { returnByValue: true, expression: `(() => { const H = ${PAGE_PX}; const big = [];
      document.querySelectorAll('figure, .callout, .widget, table, pre, details, p, ul, ol, svg').forEach((e) => { if (e.offsetHeight > H && !e.closest('.further-page') && !(e.closest('.widget') && e.closest('.widget').offsetHeight > H && e !== e.closest('.widget') && e.offsetHeight <= H)) big.push(e.tagName + '.' + e.className + ' ' + e.offsetHeight + ' ' + (e.textContent || '').trim().slice(0, 40)); });
      return big; })()` });
    if (rep.result.value && rep.result.value.length) console.log('taller than a page in', l.file, JSON.stringify(rep.result.value));
    const { data } = await send('Page.printToPDF', { printBackground: true, preferCSSPageSize: false, paperWidth: 8.27, paperHeight: 11.69, marginTop: 0.4, marginBottom: 0.45, marginLeft: 0.5, marginRight: 0.5 });
    const name = String(k + 1).padStart(2, '0') + '-' + (l.optional ? 'further-reading-' : '') + l.file.replace(/^\d+-/, '').replace(/\.html$/, '') + '.pdf';
    const sub = join(dir, folderOf(l)); mkdirSync(sub, { recursive: true });
    writeFileSync(join(sub, name), Buffer.from(data, 'base64'));
    console.log('printed', folderOf(l) + '/' + name);
  }
  ws.close();

  console.log('wrote ' + lessons.length + ' PDFs to docs/lessons-pdf/');
} finally { browser.kill(); await sleep(500); rmSync(tmp, { recursive: true, force: true, maxRetries: 5 }); }
