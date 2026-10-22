// Loads the lesson registry (interactive/assets/data/lessons.js) so every tool uses the same lesson list as the site.
import { readFileSync } from 'node:fs';
import { join, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';

export const root = resolve(fileURLToPath(new URL('../../interactive', import.meta.url)));

/** Runs lessons.js in a sandbox and returns the CT object it defines: { lessons, moved, progressMigrations, migrate, ... }. */
export function loadRegistry() {
  const sandbox = {};
  sandbox.window = sandbox;                      // lessons.js assigns window.CT, which becomes the global CT
  vm.createContext(sandbox);
  vm.runInContext(readFileSync(join(root, 'assets', 'data', 'lessons.js'), 'utf8'), sandbox, { filename: 'lessons.js' });
  return sandbox.CT;
}

/** The ids of the sections of a lesson page, exactly as app.js assigns them (explicit id, else s<position>). */
export function sectionIds(html) {
  const main = (html.replace(/\r\n/g, '\n').match(/<main[^>]*>([\s\S]*)<\/main>/) || [, ''])[1];
  return [...main.matchAll(/<section([^>]*)>/g)].map((m, i) => (m[1].match(/\sid="([^"]+)"/) || [, 's' + (i + 1)])[1]);
}
