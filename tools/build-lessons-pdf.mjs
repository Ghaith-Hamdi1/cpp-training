// Prints every lesson page in interactive/ to its own PDF in docs/lessons-pdf/ with headless Edge or Chrome (light theme, every recap
// answer opened, and print CSS that keeps figures, code blocks, callouts, tables and widgets whole: one that does not fit at the bottom of
// a page moves to the next page; only a block taller than a page is split). Code lines wrap instead of being clipped.
// Left out of the PDFs: the "Predict" exercises, the "Step through" widgets (with the line that introduces each) and the "Cheat sheet" section.
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
`;

// Captures every CT.stepper(root, cfg) call so the "Step through" widgets can be found and removed (CT is created by assets/app.js, which assigns stepper).
const CAPTURE = `(() => {
  const CT = window.CT = window.CT || {}; window.__steppers = [];
  let real; Object.defineProperty(CT, 'stepper', { configurable: true, get: () => real && ((sel, cfg) => { window.__steppers.push([sel, cfg]); return real(sel, cfg); }), set: (f) => { real = f; } });
})()`;
// Removes the "Predict" exercises, each "Step through" widget (and the paragraph right before it that says "Step through ..."), and the "Cheat sheet" section.
const REMOVE = `(() => {
  document.querySelectorAll('details.ex').forEach((d) => { const t = d.querySelector('.ex-tag'); if (t && t.textContent.trim() === 'Predict') d.remove(); });
  for (const [sel] of window.__steppers || []) {
    const rootEl = typeof sel === 'string' ? document.querySelector(sel) : sel;
    if (!rootEl) continue;
    const prev = rootEl.previousElementSibling;
    if (prev && prev.tagName === 'P' && /step through/i.test(prev.textContent)) prev.remove();
    rootEl.remove();
  }
  document.querySelectorAll('main > section').forEach((s) => { const h = s.querySelector('h2'); if (h && /^cheat sheet/i.test(h.textContent.trim())) s.remove(); });
})()`;
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
  for (const f of readdirSync(dir)) if (f.endsWith('.pdf')) unlinkSync(join(dir, f));   // the numbering can change, so start clean
  for (const [k, l] of lessons.entries()) {
    events.length = 0;
    await send('Page.navigate', { url: pathToFileURL(join(root, l.file)).href });
    for (let i = 0; i < 100 && !events.includes('Page.loadEventFired'); i++) await sleep(100);
    const ev = await send('Runtime.evaluate', { expression: `document.documentElement.dataset.theme='light'; document.head.appendChild(Object.assign(document.createElement('style'), { textContent: ${JSON.stringify(PRINT_CSS)} })); ${REMOVE}; document.querySelectorAll('details').forEach(d => d.open = true); document.fonts.ready.then(() => 1)`, awaitPromise: true }); if (ev.exceptionDetails) console.log('JS error', l.file, JSON.stringify(ev.exceptionDetails.exception && ev.exceptionDetails.exception.description || ev.exceptionDetails.text).slice(0, 300));
    await sleep(400);
    // a block that fits on one page is never split; report any block taller than a page
    const rep = await send('Runtime.evaluate', { returnByValue: true, expression: `(() => { const H = ${PAGE_PX}; const big = [];
      document.querySelectorAll('figure, .callout, .widget, table, pre, details, p, ul, ol, svg').forEach((e) => { if (e.offsetHeight > H && !(e.closest('.widget') && e.closest('.widget').offsetHeight > H && e !== e.closest('.widget') && e.offsetHeight <= H)) big.push(e.tagName + '.' + e.className + ' ' + e.offsetHeight + ' ' + (e.textContent || '').trim().slice(0, 40)); });
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
