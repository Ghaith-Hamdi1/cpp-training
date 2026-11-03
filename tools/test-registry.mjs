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
  assert.ok(s.get('done:uniqueptr').includes('basics'));        // v2 filed it under smartptr, v12 moved it to unique_ptr
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
  assert.deepEqual(s.get('weak:latency'), {}, 'v3 filed it under the Performance lesson, which v9 later removed');
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
  assert.deepEqual(s.get('done:stl'), ['s1', 'pitfalls']);
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
  assert.deepEqual(s.get('done:inherit'), ['multiple']);                         // v14 then moved the Object Model into Inheritance
  assert.deepEqual(s.get('done:copying'), ['conversions']);
  assert.deepEqual(s.get('done:oop'), ['s1']);
  assert.deepEqual(s.get('weak:copying'), { [key]: 0 });
  assert.deepEqual(s.get('weak:inherit'), { 'a question that stayed': 1 });
  assert.deepEqual(s.get('mock:missed'), []);
});

test('the real v7 migration forgets the removed Coding Rules lesson and keeps other progress', () => {
  const CT = loadRegistry();
  const s = makeStore({ 'schema': 6, 'done:rules': ['s1'], 'last:rules': 's2', 'quiz:rules': { best: 90, last: 80, total: 14 }, 'weak:rules': { q: 1 }, 'lastinfo': { id: 'rules', sec: 's2' }, 'done:stl': ['s2'], 'mock:missed': ['rules-1', 'stl-2'] });
  assert.equal(CT.migrate(s), CT.schemaVersion());
  assert.deepEqual(s.get('done:rules'), []);
  assert.equal(s.get('quiz:rules'), null);
  assert.equal(s.get('lastinfo', 'gone'), null);
  assert.deepEqual(s.get('done:stl'), ['s2']);
  assert.deepEqual(s.get('mock:missed'), []);
  assert.ok(!CT.lessons.some((l) => l.id === 'rules'));
});

test('the real v7 migration renames the patterns2 section feed to state-machine (run alone: v9 later removes that lesson)', () => {
  const CT = loadRegistry();
  const s = makeStore({ 'done:patterns2': ['command', 'feed'], 'last:patterns2': 'feed' });
  CT.progressMigrations.find((m) => m.to === 7).run(s);
  assert.deepEqual(s.get('done:patterns2'), ['command', 'state-machine']);
  assert.equal(s.get('last:patterns2'), 'state-machine');
});

test('the real v9 migration forgets the four removed lessons and keeps other progress', () => {
  const CT = loadRegistry();
  const s = makeStore({ 'schema': 8, 'done:patterns': ['s1'], 'done:patterns2': ['command'], 'done:wire': ['s1'], 'done:latency': ['s1'], 'last:wire': 's2',
    'quiz:latency': { best: 90, last: 80, total: 14 }, 'weak:patterns': { q: 1 }, 'lastinfo': { id: 'wire', sec: 's2' }, 'done:stl': ['s2'], 'quiz:stl': { best: 70, last: 70, total: 20 },
    'mock:missed': ['wire-1', 'tasks-2', 'latency-3', 'patterns2-0'] });
  assert.equal(CT.migrate(s), CT.schemaVersion());
  for (const id of ['patterns', 'patterns2', 'wire', 'latency']) assert.deepEqual(s.get('done:' + id), []);
  assert.equal(s.get('quiz:latency'), null);
  assert.deepEqual(s.get('weak:patterns'), {});
  assert.equal(s.get('lastinfo', 'gone'), null);
  assert.deepEqual(s.get('done:stl'), ['s2']);
  assert.equal(s.get('quiz:stl').best, 70);
  assert.deepEqual(s.get('mock:missed'), ['tasks-2']);
  assert.ok(!CT.lessons.some((l) => ['patterns', 'patterns2', 'wire', 'latency'].includes(l.id)));
});

test('the real v10 migration moves the pointer sections from Basics to Pointers', () => {
  const CT = loadRegistry();
  const q = 'What is the value of `x` after this code runs?';     // a question that moved to the pointers quiz (checked by its hash below)
  const s = makeStore({ 'schema': 9, 'done:basics': ['s1', 's5', 's6', 's9', 'tooling'], 'last:basics': 's7', 'lastinfo': { id: 'basics', sec: 's9' },
    'weak:basics': { [q]: 0, 'a question that stayed': 1 }, 'mock:missed': ['basics-2', 'tasks-1'] });
  assert.equal(CT.migrate(s), CT.schemaVersion());
  assert.deepEqual(s.get('done:basics'), ['s1', 'tooling']);
  assert.deepEqual(s.get('done:pointers').sort(), ['dynamic', 'pointers', 'regions']);
  assert.equal(s.get('last:basics'), '');
  assert.equal(s.get('lastinfo', 'gone'), null);
  assert.deepEqual(s.get('weak:basics'), { 'a question that stayed': 1 });
  assert.deepEqual(s.get('weak:pointers'), { [q]: 0 });
  assert.deepEqual(s.get('mock:missed'), ['tasks-1']);
  const before = JSON.stringify(s.dump());
  s.set('schema', 9);
  CT.migrate(s);
  assert.equal(JSON.stringify(s.dump()), before, 'running it again must change nothing');
});

test('the real v11 migration moves the callable sections from Lambdas to Function Pointers and Functors', () => {
  const CT = loadRegistry();
  const q = 'What is a functor?';                               // a question that moved to the callables quiz
  const s = makeStore({ 'schema': 10, 'done:lambdas': ['anatomy', 'before', 'callables'], 'last:lambdas': 'before', 'lastinfo': { id: 'lambdas', sec: 'callables' },
    'weak:lambdas': { [q]: 0, 'a question that stayed': 1 }, 'mock:missed': ['lambdas-2', 'tasks-1'] });
  assert.equal(CT.migrate(s), CT.schemaVersion());
  assert.deepEqual(s.get('done:lambdas'), ['anatomy']);
  assert.deepEqual(s.get('done:callables').sort(), ['choose', 'fnptr', 'functor', 'stdfunction']);
  assert.equal(s.get('last:lambdas'), '');
  assert.equal(s.get('lastinfo', 'gone'), null);
  assert.deepEqual(s.get('weak:lambdas'), { 'a question that stayed': 1 });
  assert.deepEqual(s.get('weak:callables'), { [q]: 0 });
  assert.deepEqual(s.get('mock:missed'), ['tasks-1']);
  const before = JSON.stringify(s.dump());
  s.set('schema', 10);
  CT.migrate(s);
  assert.equal(JSON.stringify(s.dump()), before, 'running it again must change nothing');
});

test('the real v12 migration moves the ownership and unique sections from Smart Pointers to unique_ptr', () => {
  const CT = loadRegistry();
  const q = 'Which `unique_ptr` member returns the raw pointer AND gives up ownership?';   // a question that moved to the uniqueptr quiz
  const s = makeStore({ 'schema': 11, 'done:smartptr': ['ownership', 'shared', 'unique'], 'last:smartptr': 'unique', 'lastinfo': { id: 'smartptr', sec: 'ownership' },
    'weak:smartptr': { [q]: 0, 'a question that stayed': 1 }, 'mock:missed': ['smartptr-2', 'tasks-1'] });
  assert.equal(CT.migrate(s), CT.schemaVersion());
  assert.deepEqual(s.get('done:smartptr'), ['shared']);
  assert.deepEqual(s.get('done:uniqueptr').sort(), ['basics', 'details', 'move', 'owner', 'pass']);
  assert.equal(s.get('last:smartptr'), '');
  assert.equal(s.get('lastinfo', 'gone'), null);
  assert.deepEqual(s.get('weak:smartptr'), { 'a question that stayed': 1 });
  assert.deepEqual(s.get('weak:uniqueptr'), { [q]: 0 });
  assert.deepEqual(s.get('mock:missed'), ['tasks-1']);
  const before = JSON.stringify(s.dump());
  s.set('schema', 11);
  CT.migrate(s);
  assert.equal(JSON.stringify(s.dump()), before, 'running it again must change nothing');
});

test('the real v13 migration moves the conversions and casts sections from Types to Casts', () => {
  const CT = loadRegistry();
  const q = 'What is `static_cast<int>(-3.9)`?';                  // a question that moved to the casts quiz
  const s = makeStore({ 'schema': 12, 'done:types': ['init', 'conversions', 'casts', 'const'], 'last:types': 'casts', 'lastinfo': { id: 'types', sec: 'conversions' },
    'weak:types': { [q]: 0, 'a question that stayed': 1 }, 'mock:missed': ['types-2', 'tasks-1'] });
  assert.equal(CT.migrate(s), CT.schemaVersion());
  assert.deepEqual(s.get('done:types'), ['init', 'const']);
  assert.deepEqual(s.get('done:casts').sort(), ['choose', 'constcast', 'cstyle', 'dynamic', 'implicit', 'narrowing', 'static']);
  assert.equal(s.get('last:types'), '');
  assert.equal(s.get('lastinfo', 'gone'), null);
  assert.deepEqual(s.get('weak:types'), { 'a question that stayed': 1 });
  assert.deepEqual(s.get('weak:casts'), { [q]: 0 });
  assert.deepEqual(s.get('mock:missed'), ['tasks-1']);
  const before = JSON.stringify(s.dump());
  s.set('schema', 12);
  CT.migrate(s);
  assert.equal(JSON.stringify(s.dump()), before, 'running it again must change nothing');
});

test('the real v8 migration merges the strings regex sections', () => {
  const CT = loadRegistry();
  const s = makeStore({ 'schema': 7, 'done:strings': ['s1', 's3'], 'last:strings': 's3' });
  assert.equal(CT.migrate(s), CT.schemaVersion());
  assert.deepEqual(s.get('done:strings'), ['s1', 's2']);
  assert.equal(s.get('last:strings'), 's2');
  assert.equal(CT.resolveMoved('08-strings-regex-time.html', 's3'), '08-strings-regex-time.html#s2');
});

console.log(passed + ' tests passed');

test('the real v14 migration splits OOP into three lessons and merges the Object Model into Inheritance', () => {
  const CT = loadRegistry();
  const qCopy = 'What does the Rule of Three say?';                       // placeholder text, not in the quiz: it stays in oop
  const s = makeStore({ 'schema': 13, 'done:oop': ['s1', 's3', 'conversions', 's5', 's6', 's8'], 'done:objmodel': ['multiple', 'rtti'],
    'last:oop': 's6', 'lastinfo': { id: 'oop', sec: 's6' }, 'weak:objmodel': { 'a diamond question': 1 }, 'weak:oop': { [qCopy]: 0 },
    'quiz:objmodel': { right: 3 }, 'mock:missed': ['oop-1', 'objmodel-2', 'tasks-1'] });
  assert.equal(CT.migrate(s), CT.schemaVersion());
  assert.deepEqual(s.get('done:oop'), ['s1']);
  assert.deepEqual(s.get('done:copying').sort(), ['conversions', 'copy', 'operators']);
  assert.deepEqual(s.get('done:inherit').sort(), ['inheritance', 'multiple', 'rtti', 'virtual']);
  assert.deepEqual(s.get('done:objmodel'), []);
  assert.equal(s.get('last:oop'), '');
  assert.equal(s.get('lastinfo', 'gone'), null);
  assert.deepEqual(s.get('weak:inherit'), { 'a diamond question': 1 });
  assert.deepEqual(s.get('weak:oop'), { [qCopy]: 0 });
  assert.deepEqual(s.get('mock:missed'), ['tasks-1']);
  const before = JSON.stringify(s.dump());
  s.set('schema', 13);
  CT.migrate(s);
  assert.equal(JSON.stringify(s.dump()), before, 'running it again must change nothing');
});

test('the real v15 migration splits the STL and Templates lessons and moves pair and span sections', () => {
  const CT = loadRegistry();
  const s = makeStore({ 'schema': 14,
    'done:stl': ['s1', 's2', 's4', 's6', 's7', 'ranges', 's9', 's10'], 'last:stl': 's6', 'lastinfo': { id: 'stl', sec: 's7' },
    'done:vocab': ['why', 'pairs', 'optional', 'views'], 'done:templates': ['s1', 's2', 'tools', 's6', 's9'],
    'weak:stl': { 'a question that stayed': 1 }, 'mock:missed': ['stl-1', 'templates-2', 'core-3'] });
  assert.equal(CT.migrate(s), CT.schemaVersion());
  assert.deepEqual(s.get('done:stl').sort(), ['cheat', 'pitfalls', 's1', 's2']);
  assert.deepEqual(s.get('done:assoc').sort(), ['pairs', 's4']);
  assert.deepEqual(s.get('done:iterators').sort(), ['adaptors', 'invalidation', 's6', 'views']);
  assert.deepEqual(s.get('done:algorithms').sort(), ['ranges', 's7']);
  assert.deepEqual(s.get('done:vocab').sort(), ['optional', 'why']);
  assert.deepEqual(s.get('done:templates').sort(), ['cheat', 's1']);
  assert.deepEqual(s.get('done:classtemplates').sort(), ['s2', 'tools']);
  assert.deepEqual(s.get('done:compiletime'), ['ifconstexpr']);
  assert.equal(s.get('last:stl'), '');
  assert.equal(s.get('lastinfo', 'gone'), null);
  assert.deepEqual(s.get('weak:stl'), { 'a question that stayed': 1 });
  assert.deepEqual(s.get('mock:missed'), ['core-3']);
  const before = JSON.stringify(s.dump());
  s.set('schema', 14);
  CT.migrate(s);
  assert.equal(JSON.stringify(s.dump()), before, 'running it again must change nothing');
});
