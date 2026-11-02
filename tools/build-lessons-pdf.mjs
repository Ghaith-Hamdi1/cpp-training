// Prints every lesson page in interactive/ to its own PDF in docs/lessons-pdf/ with headless Edge or Chrome (light theme, every recap
// answer opened, and print CSS that keeps figures, code blocks, callouts, tables and widgets whole: one that does not fit at the bottom of
// a page moves to the next page; only a block taller than a page is split). Code lines wrap instead of being clipped.
// Left out of the PDFs: the "Predict" exercises, the "Cheat sheet" section and every interactive widget (step-through walk-throughs,
// simulators, testers, advisors), together with the sentence that introduces each. Three simulators and the container advisor are replaced by
// a short static table. The "Read more" book notes of a lesson are collected into one "Further reading" box at the end of the lesson, and
// a few sections are moved within their lesson where that reads better on paper (see ORDER in pdfPrep).
// The files are numbered in study order (lesson 1 to 20, as in the registry), not by the page's own file name.
// Needs Edge or Chrome. Usage: node tools/build-lessons-pdf.mjs
import { existsSync, mkdirSync, mkdtempSync, readdirSync, rmSync, unlinkSync, writeFileSync } from 'node:fs';
import { resolve, join } from 'node:path';
import { tmpdir } from 'node:os';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { spawn } from 'node:child_process';
import { loadRegistry, root } from './lib/registry.mjs';

const repo = resolve(fileURLToPath(new URL('..', import.meta.url)));
const lessons = loadRegistry().lessons;
const exe = process.env.BROWSER || ['C:/Program Files (x86)/Microsoft/Edge/Application/msedge.exe', 'C:/Program Files/Microsoft/Edge/Application/msedge.exe', 'C:/Program Files/Google/Chrome/Application/chrome.exe', '/usr/bin/google-chrome', '/usr/bin/chromium'].find(existsSync);
if (!exe) throw new Error('No Edge or Chrome found; set BROWSER to its path');

const PAGE_PX = 1005;   // printable page height in CSS px (A4 11.69in less 0.4in and 0.45in margins), with a little slack
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
  .callout.further, .callout.further ul { break-inside: auto; }
`;

// Runs inside the lesson page (serialized with toString) before it is printed. Only touches the DOM, so it must not use anything from this file.
function pdfPrep(file) {
  const $$ = (sel, scope = document) => [...scope.querySelectorAll(sel)];
  const esc = (t) => String(t).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
  const norm = (t) => t.replace(/\s+/g, ' ').trim();
  const table = (head, rows, widths, style) => '<table' + (style ? ' style="' + style + '"' : '') + '><tr>' + head.map((h, i) => '<th' + (widths ? ' style="width:' + widths[i] + '"' : '') + '>' + h + '</th>').join('') + '</tr>' + rows.map((r) => '<tr>' + r.map((c) => '<td>' + c + '</td>').join('') + '</tr>').join('') + '</table>';

  // "Predict" exercises (the other collapsible recap questions stay)
  $$('details.ex').forEach((d) => { const t = d.querySelector('.ex-tag'); if (t && t.textContent.trim() === 'Predict') d.remove(); });

  // The cheat sheet at the end of every lesson
  $$('main > section').forEach((s) => { const h = s.querySelector('h2'); if (h && /^cheat sheet/i.test(h.textContent.trim())) s.remove(); });

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
    ['01-basics.html', /\s*\(see the step-through above\)/, '']
  ];
  for (const [f, re, rep] of FIXES) {
    if (f !== file) continue;
    $$('main p, main td, main li, main .callout').forEach((el) => {
      if (!re.test(el.innerHTML)) return;
      if (rep === null) el.remove(); else el.innerHTML = el.innerHTML.replace(re, rep);
    });
  }

  // "Read more" notes: one "Further reading" box at the end of the lesson, repeated entries listed once
  const notes = $$('.callout').filter((c) => { const lb = c.querySelector(':scope > .label'); return lb && /^read more$/i.test(lb.textContent.trim()); });
  const books = new Map();
  for (const n of notes) {
    let title = '';
    for (const el of n.children) {
      if (el.tagName === 'P') title = norm(el.textContent);
      else if (el.tagName === 'UL') {
        const items = books.get(title) || new Map();
        for (const li of el.children) { const key = norm(li.textContent); if (!items.has(key)) items.set(key, li.innerHTML); }
        books.set(title, items);
      }
    }
    n.remove();
  }

  // Sections moved within their lesson (the lessons themselves keep their order)
  const ORDER = {
    '01-basics.html': [['Where variables live: stack, heap, static', 'before', 'Dynamic memory: new and delete']],
    '02-oop.html': [['explicit, conversion operators and copy-and-swap', 'before', 'Composition, relationships and design'], ['Operator overloading', 'before', 'Composition, relationships and design']],
    '08-strings-regex-time.html': [['Inside std::string: SSO and capacity', 'before', 'String streams and files'], ['Regular expressions', 'after', 'Time with std::chrono']],
    '04-stl.html': [['Which container should I use?', 'before', 'Custom keys: comparators and hashes']],
    '09-compile-time.html': [['constexpr, consteval, constinit', 'before', 'enable_if and SFINAE']],
    '06-design-patterns.html': [['SOLID principles', 'before', 'Other patterns worth recognising']]
  };
  const sec = (title) => $$('main > section').find((s) => s.dataset.title === title);
  for (const [t, where, anchor] of ORDER[file] || []) {
    const s = sec(t), a = sec(anchor);
    if (!s || !a) { console.log('ORDER: section not found in ' + file + ': ' + (s ? anchor : t)); continue; }
    if (where === 'before') a.before(s); else a.after(s);
  }
  if (books.size) {
    const box = document.createElement('div');
    box.className = 'callout tip further';
    box.innerHTML = '<span class="label">Further reading</span>' + [...books].map(([t, items]) => '<p><b>' + esc(t) + '</b></p><ul>' + [...items.values()].map((h) => '<li>' + h + '</li>').join('') + '</ul>').join('');
    $$('main > section').pop().appendChild(box);
  }
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
  for (const f of readdirSync(dir)) if (f.endsWith('.pdf')) unlinkSync(join(dir, f));   // the numbering can change, so start clean
  for (const [k, l] of lessons.entries()) {
    events.length = 0;
    await send('Page.navigate', { url: pathToFileURL(join(root, l.file)).href });
    for (let i = 0; i < 100 && !events.includes('Page.loadEventFired'); i++) await sleep(100);
    const ev = await send('Runtime.evaluate', { returnByValue: true, expression: `document.documentElement.dataset.theme='light'; document.head.appendChild(Object.assign(document.createElement('style'), { textContent: ${JSON.stringify(PRINT_CSS)} })); document.querySelectorAll('details').forEach(d => d.open = true); document.fonts.ready.then(() => (${pdfPrep.toString()})(${JSON.stringify(l.file)}))`, awaitPromise: true });
    if (ev.exceptionDetails) console.log('JS error', l.file, JSON.stringify(ev.exceptionDetails.exception && ev.exceptionDetails.exception.description || ev.exceptionDetails.text).slice(0, 300));
    else if (ev.result.value) console.log('widgets left in', l.file, ev.result.value);
    await sleep(400);
    // a block that fits on one page is never split; report any block taller than a page
    const rep = await send('Runtime.evaluate', { returnByValue: true, expression: `(() => { const H = ${PAGE_PX}; const big = [];
      document.querySelectorAll('figure, .callout, .widget, table, pre, details, p, ul, ol, svg').forEach((e) => { if (e.offsetHeight > H && !e.classList.contains('further') && !(e.closest('.widget') && e.closest('.widget').offsetHeight > H && e !== e.closest('.widget') && e.offsetHeight <= H)) big.push(e.tagName + '.' + e.className + ' ' + e.offsetHeight + ' ' + (e.textContent || '').trim().slice(0, 40)); });
      return big; })()` });
    if (rep.result.value && rep.result.value.length) console.log('taller than a page in', l.file, JSON.stringify(rep.result.value));
    const { data } = await send('Page.printToPDF', { printBackground: true, preferCSSPageSize: false, paperWidth: 8.27, paperHeight: 11.69, marginTop: 0.4, marginBottom: 0.45, marginLeft: 0.5, marginRight: 0.5 });
    const name = String(k + 1).padStart(2, '0') + '-' + l.file.replace(/^\d+-/, '').replace(/\.html$/, '') + '.pdf';
    writeFileSync(join(dir, name), Buffer.from(data, 'base64'));
    console.log('printed', name);
  }
  ws.close();

  console.log('wrote ' + lessons.length + ' PDFs to docs/lessons-pdf/');
} finally { browser.kill(); await sleep(500); rmSync(tmp, { recursive: true, force: true, maxRetries: 5 }); }
