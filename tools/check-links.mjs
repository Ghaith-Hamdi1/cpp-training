// Checks every relative link: in interactive/*.html and in the Markdown files (README.md, docs/, examples/**/README.md).
// A link must point at a file that exists, and a #anchor on a lesson page must be a section (or element) id on that page
// (or a moved section recorded in CT.moved). Links to the published site (ghaith-hamdi1.github.io/cpp-training/...) are
// checked against the local interactive/ folder too.
// Usage: node tools/check-links.mjs
import { readFileSync, readdirSync, existsSync, statSync } from 'node:fs';
import { join, resolve, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';
import { loadRegistry, sectionIds } from './lib/registry.mjs';

const repo = resolve(fileURLToPath(new URL('..', import.meta.url)));
const reg = loadRegistry();
const SITE = 'https://ghaith-hamdi1.github.io/cpp-training/';
const problems = [];
const idCache = {};
const idsOf = (file) => {
  if (!(file in idCache)) {
    const html = readFileSync(file, 'utf8').replace(/\r\n/g, '\n');
    const ids = new Set(sectionIds(html));
    for (const m of html.matchAll(/\bid="([^"]+)"/g)) ids.add(m[1]);
    idCache[file] = ids;
  }
  return idCache[file];
};

function check(from, target, label) {
  let [path, anchor] = target.split('#');
  if (target.startsWith(SITE)) path = join('interactive', target.slice(SITE.length).split('#')[0] || 'index.html');
  else if (/^(https?:|mailto:|javascript:|data:|tel:)/i.test(target)) return;
  else if (path) path = join(dirname(from), decodeURIComponent(path));
  else path = from;                                                      // a bare #anchor in the same page
  const abs = resolve(repo, path);
  if (!existsSync(abs)) { problems.push(`${from}: broken ${label} ${target}`); return; }
  if (anchor && abs.endsWith('.html') && statSync(abs).isFile()) {
    const rel = abs.slice(resolve(repo, 'interactive').length + 1).replace(/\\/g, '/');
    if (!idsOf(abs).has(decodeURIComponent(anchor)) && !reg.resolveMoved(rel, decodeURIComponent(anchor))) problems.push(`${from}: no #${anchor} in ${rel}`);
  }
}

const walk = (dir, ok) => readdirSync(dir, { withFileTypes: true }).flatMap((e) => {
  if (['node_modules', '.git', 'LearnCPP'].includes(e.name)) return [];
  const p = join(dir, e.name);
  return e.isDirectory() ? walk(p, ok) : ok(e.name) ? [p] : [];
});

let n = 0;
for (const f of walk(join(repo, 'interactive'), (x) => x.endsWith('.html'))) {
  const rel = f.slice(repo.length + 1).replace(/\\/g, '/');
  const html = readFileSync(f, 'utf8');
  for (const m of html.matchAll(/(?:href|src)="([^"]+)"/g)) { n++; check(rel, m[1], 'link'); }
}
const mds = [join(repo, 'README.md'), ...walk(join(repo, 'docs'), (x) => x.endsWith('.md')), ...walk(join(repo, 'examples'), (x) => x === 'README.md')];
for (const f of mds) {
  const rel = f.slice(repo.length + 1).replace(/\\/g, '/');
  const md = readFileSync(f, 'utf8').replace(/```[\s\S]*?```/g, '');
  for (const m of md.matchAll(/\]\((<[^>]+>|[^)\s]+)\)/g)) {
    const t = m[1].replace(/^<|>$/g, '');
    if (/^(https?:|mailto:)/i.test(t) && !t.startsWith(SITE)) continue;
    n++; check(rel, t, 'link');
  }
}
console.log(problems.length ? 'PROBLEMS:\n' + problems.join('\n') : `all ${n} links resolve`);
process.exit(problems.length ? 1 : 0);
