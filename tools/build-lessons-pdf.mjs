// Prints every lesson page in interactive/ to its own PDF in docs/lessons-pdf/ with headless Edge or Chrome (light theme, every "Predict"
// answer opened, and print CSS that keeps figures, code blocks, callouts, tables and widgets whole: one that does not fit at the bottom of a
// page moves to the next page; only a block taller than a page is split). Code lines wrap instead of being clipped.
// Each "Step through" widget is replaced by a static walk-through: the code once, then a table with one row per step (line, what happens,
// memory after it), taken from the same step data the widget uses.
// Needs Edge or Chrome. Usage: node tools/build-lessons-pdf.mjs
import { existsSync, mkdirSync, mkdtempSync, rmSync, writeFileSync } from 'node:fs';
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
  figure, figure.code, .st-static tr, .fig, .callout, .widget, .card, details, table tr, pre, svg, blockquote, .sim, .stepper, .ex { break-inside: avoid; }
  figure.code, figure.code *, pre { overflow: visible !important; max-width: 100% !important; }
  pre, pre code, figure.code code { white-space: pre-wrap !important; overflow-wrap: anywhere; }
  svg, img, table { max-width: 100% !important; }
  p, li, dd, dt, h1, h2, h3, h4, h5, summary, figcaption, .lead, thead, tr { break-inside: avoid; }
  ul, ol { break-inside: avoid-page; }
  p, li { orphans: 3; widows: 3; }
  section > p:has(+ figure), section > p:has(+ .widget), section > p:has(+ table), section > p:has(+ details) { break-after: avoid; }
`;

// Captures every CT.stepper(root, cfg) call so its steps can be printed as a table (CT is created by assets/app.js, which assigns stepper).
const CAPTURE = `(() => {
  const CT = window.CT = window.CT || {}; window.__steppers = [];
  let real; Object.defineProperty(CT, 'stepper', { configurable: true, get: () => real && ((sel, cfg) => { window.__steppers.push([sel, cfg]); return real(sel, cfg); }), set: (f) => { real = f; } });
})()`;
const STATIC = `(() => {
  const esc = (t) => String(t).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
  for (const [sel, cfg] of window.__steppers || []) {
    const root = typeof sel === 'string' ? document.querySelector(sel) : sel;
    if (!root) continue;
    const code = cfg.code.replace(/^\\n/, '').replace(/\\s+$/, '').split('\\n');
    const cut = Math.min(...code.filter((l) => l.trim()).map((l) => l.match(/^ */)[0].length));
    const lines = code.map((l) => l.slice(cut));
    const lineTxt = (n) => [].concat(n).map((k) => '<code>' + esc((lines[k - 1] || '').trim()) + '</code>').join(' ');
    const rows = cfg.steps.map((st, i) => {
      const prev = i ? cfg.steps[i - 1].mem || [] : [];
      const mem = (st.mem || []).map((e) => {
        const b = prev.find((x) => x.n === e.n);
        const changed = !b || b.v !== e.v || !!b.dead !== !!e.dead;
        const name = esc(e.n.replace(/\\s*@\\S+/, ''));
        return '<li class="' + (changed ? 'chg' : '') + (e.dead ? ' dead' : '') + '">' + name + ' = ' + esc(e.v) + (e.k === 'heap' ? ' (heap)' : '') + '</li>';
      }).join('');
      return '<tr><td class="n">' + (i + 1) + '</td><td class="l">' + (st.line ? '<span class="ln">line ' + [].concat(st.line).join(', ') + '</span>' + lineTxt(st.line) : '') + '</td><td>' + st.note + (st.out ? '<div class="o">prints: <code>' + esc(st.out.replace(/\\n/g, '\\\\n')) + '</code></div>' : '') + '</td><td><ul class="m">' + mem + '</ul></td></tr>';
    }).join('');
    root.className = 'widget st-static';
    root.removeAttribute('tabindex');
    root.innerHTML = '<div class="w-head"><span class="tag">Step through</span>' + esc(cfg.title || '') + '</div><div class="st-sbody">' +
      '<pre class="scode">' + lines.map((l, i) => '<span class="sl"><i>' + (i + 1) + '</i>' + (esc(l) || ' ') + '</span>').join('\\n') + '</pre>' +
      (cfg.intro ? '<p>' + cfg.intro + '</p>' : '') +
      '<table class="steps"><thead><tr><th>Step</th><th>Runs</th><th>What happens</th><th>Memory after (changed in bold)</th></tr></thead><tbody>' + rows + '</tbody></table></div>';
  }
})()`;
const STATIC_CSS = `
  .widget.st-static { break-inside: auto; }
  .widget.st-static.fits { break-inside: avoid !important; }
  .st-static thead { display: table-header-group; }
  .st-static table.steps { table-layout: fixed; }
  .st-static .steps th:nth-child(2) { width: 27%; } .st-static .steps th:nth-child(3) { width: 40%; } .st-static .steps th:nth-child(1) { width: 3.2em; }
  .st-static .l code { white-space: pre-wrap; overflow-wrap: anywhere; }
  .st-static .st-sbody { padding: 10px 14px 14px; }
  .st-static pre.scode { font: 0.85rem/1.5 Consolas, monospace; background: #f3f3f1; border: 1px solid #ccc; border-radius: 8px; padding: 8px 12px; margin: 0 0 10px; white-space: pre-wrap; }
  .st-static .sl i { display: inline-block; width: 2em; color: #888; font-style: normal; }
  .st-static table.steps { width: 100%; border-collapse: collapse; font-size: 0.88rem; }
  .st-static .steps th { text-align: left; font-size: 0.75rem; text-transform: uppercase; color: #555; border-bottom: 1.5px solid #999; padding: 4px 6px; }
  .st-static .steps td { vertical-align: top; padding: 4px 6px; line-height: 1.35; border-bottom: 1px solid #ddd; }
  .st-static .steps td.n { font-weight: 700; width: 2.2em; }
  .st-static .ln { display: block; color: #666; font-size: 0.75rem; }
  .st-static ul.m { margin: 0; padding: 0; list-style: none; font: 0.78rem/1.4 Consolas, monospace; }
  .st-static ul.m li { display: inline; } .st-static ul.m li + li::before { content: '  |  '; color: #aaa; font-weight: 400; text-decoration: none; }
  .st-static ul.m li.chg { font-weight: 700; } .st-static ul.m li.dead { text-decoration: line-through; color: #777; }
  .st-static .o { margin-top: 4px; color: #444; }
`;
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
  await send('Page.addScriptToEvaluateOnNewDocument', { source: CAPTURE });
  await send('Emulation.setDeviceMetricsOverride', { width: 698, height: 1000, deviceScaleFactor: 1, mobile: false });
  await send('Emulation.setEmulatedMedia', { media: 'print' });

  const dir = resolve(repo, 'docs/lessons-pdf');
  mkdirSync(dir, { recursive: true });
  for (const [k, l] of lessons.entries()) {
    events.length = 0;
    await send('Page.navigate', { url: pathToFileURL(join(root, l.file)).href });
    for (let i = 0; i < 100 && !events.includes('Page.loadEventFired'); i++) await sleep(100);
    const ev = await send('Runtime.evaluate', { expression: `document.documentElement.dataset.theme='light'; document.head.appendChild(Object.assign(document.createElement('style'), { textContent: ${JSON.stringify(PRINT_CSS + STATIC_CSS)} })); ${STATIC}; document.querySelectorAll('details').forEach(d => d.open = true); document.fonts.ready.then(() => 1)`, awaitPromise: true }); if (ev.exceptionDetails) console.log('JS error', l.file, JSON.stringify(ev.exceptionDetails.exception && ev.exceptionDetails.exception.description || ev.exceptionDetails.text).slice(0, 300));
    await sleep(400);
    // a block that fits on one page must never be split: shrink a walk-through that is taller than a page until it fits (down to 66%), mark the fitting ones, and report any block taller than a page
    const rep = await send('Runtime.evaluate', { returnByValue: true, expression: `(() => { const H = ${PAGE_PX}; const big = [];
      document.querySelectorAll('.widget.st-static').forEach((w) => { for (let k = 0; k < 6 && w.offsetHeight > H && (+w.style.zoom || 1) > 0.75; k++) w.style.zoom = Math.max(0.75, (+w.style.zoom || 1) * H / w.offsetHeight * 0.98); if (w.offsetHeight <= H) w.classList.add('fits'); });
      document.querySelectorAll('figure, .callout, .widget, table, pre, details, p, ul, ol, svg').forEach((e) => { if (e.offsetHeight > H && !(e.classList.contains('st-static') || e.closest('.st-static') || e.closest('.widget') && e.closest('.widget').offsetHeight > H && e !== e.closest('.widget') && e.offsetHeight <= H)) big.push(e.tagName + '.' + e.className + ' ' + e.offsetHeight + ' ' + (e.textContent || '').trim().slice(0, 40)); });
      return big; })()` });
    if (rep.result.value && rep.result.value.length) console.log('taller than a page in', l.file, JSON.stringify(rep.result.value));
    const { data } = await send('Page.printToPDF', { printBackground: true, preferCSSPageSize: false, paperWidth: 8.27, paperHeight: 11.69, marginTop: 0.4, marginBottom: 0.45, marginLeft: 0.5, marginRight: 0.5 });
    const file = join(dir, l.file.replace(/\.html$/, '.pdf'));
    writeFileSync(file, Buffer.from(data, 'base64'));
    console.log('printed', l.file);
  }
  ws.close();

  console.log('wrote ' + lessons.length + ' PDFs to docs/lessons-pdf/');
} finally { browser.kill(); await sleep(500); rmSync(tmp, { recursive: true, force: true, maxRetries: 5 }); }
