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

test('the real v2 migration splits the old core lesson progress and is idempotent', () => {
  const CT = loadRegistry();
  const s = makeStore({
    'done:core': ['s1', 's3', 's4', 's7', 's9'], 'last:core': 's6', 'lastinfo': { id: 'core', sec: 's6' },
    'weak:core': { 'What does `std::move(x)` do?': 0, 'a question that stayed in core': 1 }, 'mock:missed': ['core-2', 'wire-1'], 'quiz:core': { best: 80, last: 70, total: 24 }
  });
  assert.equal(CT.migrate(s), CT.schemaVersion());
  assert.deepEqual(s.get('done:core'), ['s1', 's7']);
  assert.deepEqual(s.get('done:moves').sort(), ['copy-move', 'returning', 'traps', 'writing']);
  assert.ok(s.get('done:smartptr').includes('unique'));
  assert.deepEqual(s.get('done:types'), ['const']);
  assert.equal(s.get('last:core'), '');
  assert.equal(s.get('lastinfo', 'gone'), null);
  assert.deepEqual(s.get('weak:moves'), { 'What does `std::move(x)` do?': 0 });
  assert.deepEqual(s.get('weak:core'), { 'a question that stayed in core': 1 });
  assert.deepEqual(s.get('mock:missed'), []);   // v7 clears the saved missed mock questions
  assert.deepEqual(s.get('quiz:core'), { best: 80, last: 70, total: 24 });
  const before = JSON.stringify(s.dump());
  s.set('schema', 1);                          // an older export is imported
  CT.migrate(s);
  assert.equal(JSON.stringify(s.dump()), before, 'running it again must change nothing');
});

test('the real v3 migration splits the multithreading progress and is idempotent', () => {
  const CT = loadRegistry();
  const s = makeStore({
    'schema': 2, 'done:threads': ['s1', 's6', 's8', 's9', 's10', 's11'], 'last:threads': 's8', 'lastinfo': { id: 'threads', sec: 's9' },
    'weak:threads': { 'What is false sharing?': 0, 'a question that stayed': 1 }, 'mock:missed': ['threads-3', 'wire-1']
  });
  assert.equal(CT.migrate(s), CT.schemaVersion());
  assert.deepEqual(s.get('done:threads'), ['s1', 's11']);
  assert.deepEqual(s.get('done:atomics'), ['ops', 'ordering']);
  assert.deepEqual(s.get('done:tasks').sort(), ['futures', 'pool', 'signals', 'stealing']);
  assert.equal(s.get('last:threads'), '');
  assert.equal(s.get('lastinfo', 'gone'), null);
  assert.deepEqual(s.get('weak:latency'), { 'What is false sharing?': 0 });
  assert.deepEqual(s.get('weak:threads'), { 'a question that stayed': 1 });
  assert.deepEqual(s.get('mock:missed'), []);
  const before = JSON.stringify(s.dump());
  s.set('schema', 2);
  CT.migrate(s);
  assert.equal(JSON.stringify(s.dump()), before, 'running it again must change nothing');
});

test('the real v4 migration drops the replaced STL strings tick and stale cheat-sheet ids', () => {
  const CT = loadRegistry();
  const s = makeStore({ 'schema': 3, 'done:stl': ['s1', 's8', 's9'], 'last:stl': 's8', 'mock:missed': ['stl-2', 'strings-1', 'wire-1'] });
  assert.equal(CT.migrate(s), CT.schemaVersion());
  assert.deepEqual(s.get('done:stl'), ['s1', 's9']);
  assert.equal(s.get('last:stl'), '');
  assert.deepEqual(s.get('mock:missed'), []);
});

test('the real v5 migration forgets the removed read-more section ticks', () => {
  const CT = loadRegistry();
  const s = makeStore({ 'schema': 4, 'done:core': ['s1', 'read-more'], 'done:stl': ['s2'], 'last:core': 'read-more', 'lastinfo': { id: 'core', sec: 'read-more' } });
  assert.equal(CT.migrate(s), CT.schemaVersion());
  assert.deepEqual(s.get('done:core'), ['s1']);
  assert.deepEqual(s.get('done:stl'), ['s2']);
  assert.equal(s.get('last:core'), '');
  assert.equal(s.get('lastinfo', 'gone'), null);
});

test('the real v6 migration moves the conversions tick and weak question from the object model to OOP', () => {
  const CT = loadRegistry();
  const key = "What does `explicit` on a single-argument constructor prevent?";
  const s = makeStore({ 'schema': 5, 'done:objmodel': ['multiple', 'conversions'], 'done:oop': ['s1'], 'weak:objmodel': { [key]: 0, 'a question that stayed': 1 }, 'mock:missed': ['objmodel-1', 'oop-2', 'wire-1'] });
  assert.equal(CT.migrate(s), CT.schemaVersion());
  assert.deepEqual(s.get('done:objmodel'), ['multiple']);
  assert.deepEqual(s.get('done:oop'), ['s1', 'conversions']);
  assert.deepEqual(s.get('weak:oop'), { [key]: 0 });
  assert.deepEqual(s.get('weak:objmodel'), { 'a question that stayed': 1 });
  assert.deepEqual(s.get('mock:missed'), []);
});

test('the real v7 migration forgets the removed Coding Rules lesson and keeps other progress', () => {
  const CT = loadRegistry();
  const s = makeStore({ 'schema': 6, 'done:rules': ['s1'], 'last:rules': 's2', 'quiz:rules': { best: 90, last: 80, total: 14 }, 'weak:rules': { q: 1 }, 'lastinfo': { id: 'rules', sec: 's2' }, 'done:stl': ['s2'], 'mock:missed': ['rules-1', 'stl-2'] });
  assert.equal(CT.migrate(s), 7);
  assert.deepEqual(s.get('done:rules'), []);
  assert.equal(s.get('quiz:rules'), null);
  assert.equal(s.get('lastinfo', 'gone'), null);
  assert.deepEqual(s.get('done:stl'), ['s2']);
  assert.deepEqual(s.get('mock:missed'), []);
  assert.ok(!CT.lessons.some((l) => l.id === 'rules'));
});

test('the real v7 migration renames the patterns2 section feed to state-machine', () => {
  const CT = loadRegistry();
  const s = makeStore({ 'schema': 6, 'done:patterns2': ['command', 'feed'], 'last:patterns2': 'feed' });
  assert.equal(CT.migrate(s), 7);
  assert.deepEqual(s.get('done:patterns2'), ['command', 'state-machine']);
  assert.equal(s.get('last:patterns2'), 'state-machine');
});

console.log(passed + ' tests passed');
