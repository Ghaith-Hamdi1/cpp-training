// A tiny static server for trying the site locally (the service worker and the web manifest need http, not file://).
// Usage: node tools/serve.mjs [port]      then open http://localhost:8123/ (the default port)
import http from 'node:http';
import { readFile } from 'node:fs';
import { extname, join, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';

const root = resolve(fileURLToPath(new URL('../interactive', import.meta.url)));
const port = +process.argv[2] || 8123;
const types = {
  '.html': 'text/html; charset=utf-8', '.js': 'text/javascript; charset=utf-8', '.css': 'text/css; charset=utf-8', '.json': 'application/json',
  '.webmanifest': 'application/manifest+json', '.svg': 'image/svg+xml', '.md': 'text/plain; charset=utf-8'
};
http.createServer((req, res) => {
  let p = decodeURIComponent(req.url.split('?')[0]);
  if (p.endsWith('/')) p += 'index.html';
  const f = join(root, p);
  if (!f.startsWith(root)) { res.writeHead(403); return res.end(); }
  readFile(f, (e, d) => {
    if (e) { res.writeHead(404); return res.end('not found'); }
    res.writeHead(200, { 'Content-Type': types[extname(f)] || 'application/octet-stream' });
    res.end(d);
  });
}).listen(port, () => console.log(`serving ${root} on http://localhost:${port}/`));
