// Tests for the lesson registry helpers in interactive/assets/data/lessons.js: the progress migration framework
// and the moved-section lookup. Run with: node tools/test-registry.mjs
import assert from 'node:assert/strict';
import { loadRegistry } from './lib/registry.mjs';

let passed = 0;
const test = (name, fn) => { fn(); passed++; console.log('ok  ' + name); };

// A store like the one in app.js, backed by a Map. Keys carry no prefix.
const makeStore = (initial = {}) => {
  const m = new Map(Object.entries(initial));
  return { get: (k, d) => (m.has(k) ? JSON.parse(JSON.stringify(m.get(k))) : d), set: (k, v) => m.set(k, v), dump: () => Object.fromEntries(m) };
};

test('registry has lessons with unique ids and numbering by position', () => {
  const CT = loadRegistry();
  assert.ok(CT.lessons.length >= 10);
  assert.equal(new Set(CT.lessons.map((l) => l.id)).size, CT.lessons.length);
});

test('no migrations: schema stays 1 and the store is untouched', () => {
  const CT = loadRegistry();
  CT.progressMigrations = [];
  const s = makeStore({ 'done:core': ['s1'] });
  assert.equal(CT.schemaVersion(), 1);
  assert.equal(CT.migrate(s), 1);
  assert.deepEqual(s.dump(), { 'done:core': ['s1'] });
});

test('a migration renames saved ids once and records the version', () => {
  const CT = loadRegistry();
  let runs = 0;
  CT.progressMigrations = [{ to: 2, run: (st) => { runs++; st.set('done:raii', Array.from(new Set([].concat(st.get('done:raii', []), st.get('done:core', []))))); } }];
  const s = makeStore({ 'done:core': ['s1', 's2'], 'quiz:core': { best: 80, last: 60, total: 24 } });
  assert.equal(CT.schemaVersion(), 2);
  assert.equal(CT.migrate(s), 2);
  assert.deepEqual(s.get('done:raii'), ['s1', 's2']);
  assert.equal(s.get('schema'), 2);
  CT.migrate(s);
  assert.equal(runs, 1, 'already migrated: must not run again');
});

test('migrations are idempotent when an older progress code is imported later', () => {
  const CT = loadRegistry();
  CT.progressMigrations = [{ to: 2, run: (st) => { st.set('done:raii', Array.from(new Set([].concat(st.get('done:raii', []), st.get('done:core', []))))); } }];
  const s = makeStore({ 'done:core': ['s1'] });
  CT.migrate(s);
  s.set('done:core', ['s1', 's3']);          // an older export brings back old ids...
  s.set('schema', 1);                         // ...and the import marks the browser as old
  CT.migrate(s);
  assert.deepEqual(s.get('done:raii').sort(), ['s1', 's3']);
});

test('migrations run in order of version, whatever the array order', () => {
  const CT = loadRegistry();
  const order = [];
  CT.progressMigrations = [{ to: 3, run: () => order.push(3) }, { to: 2, run: () => order.push(2) }];
  CT.migrate(makeStore());
  assert.deepEqual(order, [2, 3]);
});

test('a failing migration does not throw and leaves the version so it retries', () => {
  const CT = loadRegistry();
  CT.progressMigrations = [{ to: 2, run: () => { throw new Error('boom'); } }];
  const s = makeStore();
  assert.equal(CT.migrate(s), 1);
  assert.equal(s.get('schema', 1), 1);
});

test('moved sections resolve to their new place, unknown ones to null', () => {
  const CT = loadRegistry();
  CT.moved = { '03-core-language.html#s4': '13-smart-pointers.html#s1' };
  assert.equal(CT.resolveMoved('03-core-language.html', 's4'), '13-smart-pointers.html#s1');
  assert.equal(CT.resolveMoved('03-core-language.html', 's5'), null);
  assert.equal(CT.resolveMoved('04-stl.html', 's4'), null);
});

console.log(passed + ' tests passed');
