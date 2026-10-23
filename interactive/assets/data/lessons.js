/* The lesson registry: the single source of truth for the site and the tools in tools/.
 *
 * Loaded BEFORE assets/app.js on every page, and run by the Node tools through the vm module, so keep this
 * file plain ES5-style JavaScript with no DOM access.
 *
 * To add a lesson: create <file> and <quiz> (and assets/data/quiz-<id>.js), then add one entry below.
 * Navigation order and the displayed number come from the position in this array, not from the file name.
 * Fields: id (lowercase letters and digits, used in saved progress), phase (1 to 8, the roadmap phase the lesson belongs to; see CT.phases), file, quiz, title, time, assess (questions drawn
 * for the level check: 2 for every lesson, so the check is even; 0 leaves the lesson out), blurb.
 */
window.CT = window.CT || {};

/* The eight phases of the C++ roadmap (docs/reading/roadmap). tools/build-checklist.mjs checks that every lesson's phase and
 * every phase's name and page match the roadmap files, so edit both together. */
CT.phases = [
  { n: 1, name: 'Core language foundations', page: 'phase-1-core-language-foundations.md' },
  { n: 2, name: 'Classes, memory and object-oriented design', page: 'phase-2-classes-memory-and-object-oriented-design.md' },
  { n: 3, name: 'The standard library and generic programming', page: 'phase-3-the-standard-library-and-generic-programming.md' },
  { n: 4, name: 'RAII, exceptions and advanced language tools', page: 'phase-4-raii-exceptions-and-advanced-language-tools.md' },
  { n: 5, name: 'Modern C++ (C++11 to C++20)', page: 'phase-5-modern-cpp.md' },
  { n: 6, name: 'Design patterns and SOLID', page: 'phase-6-design-patterns-and-solid.md' },
  { n: 7, name: 'Concurrency and the memory model', page: 'phase-7-concurrency-and-the-memory-model.md' },
  { n: 8, name: 'Performance, memory layout and binary data', page: 'phase-8-performance-memory-layout-and-binary-data.md' }
];

CT.lessons = [
  { id: 'basics', file: '01-basics.html', quiz: '01-basics-quiz.html', title: 'C++ Basics & Pointers', time: '60 min', assess: 2, phase: 1,
    blurb: 'Types, functions, memory, pointers, references, const and dynamic allocation, built up from zero.' },
  { id: 'types', file: '16-types-and-casts.html', quiz: '16-types-and-casts-quiz.html', title: 'Types, Initialization & Casts', time: '40 min', assess: 2, phase: 1,
    blurb: 'Initialization forms and brace traps, auto and decltype, implicit conversions, the named casts, const, constexpr and static.' },
  { id: 'oop', file: '02-oop.html', quiz: '02-oop-quiz.html', title: 'Object-Oriented Programming', time: '60 min', assess: 2, phase: 2,
    blurb: 'Classes, constructors, rule of 3/5/0, inheritance, virtual functions, abstract classes, operator overloading.' },
  { id: 'objmodel', file: '19-object-model.html', quiz: '19-object-model-quiz.html', title: 'The Object Model in Depth', time: '40 min', assess: 2, phase: 2,
    blurb: 'Multiple inheritance and layout, the diamond and virtual inheritance, RTTI and private inheritance.' },
  { id: 'strings', file: '08-strings-regex-time.html', quiz: '08-strings-regex-time-quiz.html', title: 'Strings, Regex & Time', time: '40 min', assess: 2, phase: 3,
    blurb: 'string versus string_view, regular expressions with a live tester, and measuring time with chrono clocks and durations.' },
  { id: 'stl', file: '04-stl.html', quiz: '04-stl-quiz.html', title: 'The STL', time: '60 min', assess: 2, phase: 3,
    blurb: 'Containers, iterators, algorithms, complexity, iterator invalidation and how to choose the right container.' },
  { id: 'lambdas', file: '15-lambdas.html', quiz: '15-lambdas-quiz.html', title: 'Lambdas & Callables', time: '35 min', assess: 2, phase: 3,
    blurb: 'Captures and their lifetime traps, init-capture, generic lambdas, and function pointer versus functor versus lambda versus std::function.' },
  { id: 'templates', file: '05-templates.html', quiz: '05-templates-quiz.html', title: 'Templates', time: '60 min', assess: 2, phase: 3,
    blurb: 'Function and class templates, specialization, forwarding references, variadic templates, type traits, if constexpr.' },
  { id: 'core', file: '03-core-language.html', quiz: '03-core-language-quiz.html', title: 'Core Language: RAII & Exceptions', time: '35 min', assess: 2, phase: 4,
    blurb: 'RAII and scope guards, stack unwinding, the exception-safety guarantees, noexcept, and exceptions versus return values.' },
  { id: 'vocab', file: '21-vocabulary-types.html', quiz: '21-vocabulary-types-quiz.html', title: 'Vocabulary Types', time: '35 min', assess: 2, phase: 5,
    blurb: 'pair and tuple, optional, variant and visit, expected, span and string_view: the small types that make interfaces honest.' },
  { id: 'moves', file: '13-move-semantics.html', quiz: '13-move-semantics-quiz.html', title: 'Move Semantics', time: '45 min', assess: 2, phase: 5,
    blurb: 'Value categories, what std::move really does, writing move operations, copy elision and the move traps.' },
  { id: 'smartptr', file: '14-smart-pointers.html', quiz: '14-smart-pointers-quiz.html', title: 'Smart Pointers & Ownership', time: '40 min', assess: 2, phase: 5,
    blurb: 'unique_ptr, shared_ptr and weak_ptr, the control block, cycles, custom deleters and how to pass ownership around.' },
  { id: 'compiletime', file: '09-compile-time.html', quiz: '09-compile-time-quiz.html', title: 'Type Traits & Compile-time C++', time: '45 min', assess: 2, phase: 5,
    blurb: 'Type traits, SFINAE, concepts and requires, if constexpr, constexpr and consteval, and classic template metaprogramming.' },
  { id: 'patterns', file: '06-design-patterns.html', quiz: '06-design-patterns-quiz.html', title: 'Design Patterns', time: '50 min', assess: 2, phase: 6,
    blurb: 'Singleton, Factory, Strategy, Observer and State in modern C++, plus the idioms you should recognise.' },
  { id: 'patterns2', file: '20-more-patterns.html', quiz: '20-more-patterns-quiz.html', title: 'More Patterns', time: '40 min', assess: 2, phase: 6,
    blurb: 'Command with undo, Decorator, Adapter, Builder, Visitor with std::variant and a protocol state machine, with real code.' },
  { id: 'threads', file: '07-multithreading.html', quiz: '07-multithreading-quiz.html', title: 'Multithreading', time: '60 min', assess: 2, phase: 7,
    blurb: 'From your first thread to data races, mutexes, deadlocks, condition variables and the other mutex types.' },
  { id: 'tasks', file: '17-tasks-parallelism.html', quiz: '17-tasks-parallelism-quiz.html', title: 'Tasks & Parallelism', time: '45 min', assess: 2, phase: 7,
    blurb: 'Futures and async, promises, thread pools and work stealing, latch, barrier, semaphore, stop_token and parallel algorithms.' },
  { id: 'atomics', file: '18-atomics-memory-model.html', quiz: '18-atomics-memory-model-quiz.html', title: 'Atomics & the Memory Model', time: '55 min', assess: 2, phase: 7,
    blurb: 'Atomic operations, compare-and-swap, memory orders and happens-before with a simulator, ordering patterns and concurrent data structures.' },
  { id: 'wire', file: '11-wire-formats.html', quiz: '11-wire-formats-quiz.html', title: 'Binary Data & Parsing', time: '60 min', assess: 2, phase: 8,
    blurb: 'Bit manipulation, struct layout and padding, endianness, aliasing and memcpy, zero-copy parsing, fixed-point numbers and sequence numbers.' },
  { id: 'latency', file: '12-low-latency.html', quiz: '12-low-latency-quiz.html', title: 'Performance & Memory', time: '60 min', assess: 2, phase: 8,
    blurb: 'Tail latency, pools and arenas, cache-friendly data, lookup structures, SPSC queues, predictable hot paths and core pinning.' }
];

/* When a section moves to another lesson, record where it went so old links keep working:
 *   'old-lesson.html#old-id': 'new-lesson.html#new-id'
 * app.js follows this when a link points at a section that is no longer on the page. */
CT.moved = {
  '05-templates.html#s7': '09-compile-time.html#s4',    // Compile-time computation: now Template metaprogramming
  '03-core-language.html#s2': '13-move-semantics.html#values',          // lesson 3 was split into five lessons
  '03-core-language.html#s3': '13-move-semantics.html#copy-move',
  '03-core-language.html#s4': '14-smart-pointers.html#ownership',
  '03-core-language.html#s5': '16-types-and-casts.html#deduction',
  '03-core-language.html#s6': '15-lambdas.html#anatomy',
  '03-core-language.html#s8': '16-types-and-casts.html#casts',
  '03-core-language.html#s9': '16-types-and-casts.html#const',
  '03-core-language.html#s10': '16-types-and-casts.html#standards',
  '08-strings-regex-time.html#s3': '08-strings-regex-time.html#s2',   // the two regex sections were merged
  '07-multithreading.html#s6': '18-atomics-memory-model.html#ops',        // the multithreading lesson was split in three
  '07-multithreading.html#s8': '17-tasks-parallelism.html#futures',
  '07-multithreading.html#s9': '17-tasks-parallelism.html#pool',
  '07-multithreading.html#s10': '12-low-latency.html#s8',
  '19-object-model.html#conversions': '02-oop.html#conversions',          // explicit, conversion operators and copy-and-swap moved to OOP
  '04-stl.html#s8': '08-strings-regex-time.html#s1'       // the STL strings section is covered by the Strings lesson
};

/* Saved progress is stored per lesson id and section id. When ids change (a lesson is split or renamed), add a
 * migration here. Each runs once per browser, in order of `to`, and MUST be idempotent (it can run again after
 * importing an older progress code).
 *   { to: 2, run: function (store) { var d = store.get('done:core', []); store.set('done:raii', d); } }
 * `store` has get(key, default) and set(key, value); keys carry no prefix. */
CT.progressMigrations = [
  /* v2: the old Core Language lesson was split into core, moves, smartptr, lambdas and types. Ticked sections move
     with their content, and weak-question entries (keyed by question text) go to the quiz that now holds the question. */
  { to: 2, run: function (store) {
    var SECS = {                                   // old section id -> [lesson, new section ids]
      s2: ['moves', ['values']], s3: ['moves', ['copy-move', 'writing', 'returning', 'traps']],
      s4: ['smartptr', ['ownership', 'unique', 'shared', 'weak', 'pitfalls']], s5: ['types', ['deduction']],
      s6: ['lambdas', ['anatomy', 'captures', 'advanced', 'callables']], s8: ['types', ['casts']],
      s9: ['types', ['const']], s10: ['types', ['standards']]
    };
    var done = store.get('done:core', []), keep = [];
    done.forEach(function (id) {
      if (!SECS[id]) { keep.push(id); return; }
      var lesson = SECS[id][0], d = store.get('done:' + lesson, []);
      SECS[id][1].forEach(function (n) { if (d.indexOf(n) < 0) d.push(n); });
      store.set('done:' + lesson, d);
    });
    store.set('done:core', keep);
    if (SECS[store.get('last:core', '')]) store.set('last:core', '');
    var li = store.get('lastinfo', null);
    if (li && li.id === 'core' && SECS[li.sec]) store.set('lastinfo', null);
    var hash = function (s) { var x = 5381, i; for (i = 0; i < s.length; i++) x = ((x * 33) ^ s.charCodeAt(i)) >>> 0; return x.toString(36); };
    var WHERE = { 'v12hn1': 'moves', '1j0lv33': 'moves', 'vjjybz': 'moves', 'bj9033': 'moves', '1joc0dk': 'moves', '1ag6nnl': 'moves',
      'mfik7c': 'smartptr', '1r8vitt': 'smartptr', 'kl74xr': 'smartptr', 'l2v1mh': 'smartptr', 'g73a6s': 'smartptr',
      '11pju37': 'lambdas', '39icpi': 'lambdas',
      '13h63if': 'types', 'inzmcy': 'types', '1yp4ovw': 'types', '1lw8fu7': 'types', '7dmsje': 'types', '116m4kb': 'types', '1wra14g': 'types' };
    var weak = store.get('weak:core', {}), stay = {};
    Object.keys(weak).forEach(function (k) {
      var to = WHERE[hash(k)];
      if (!to) { stay[k] = weak[k]; return; }
      var w = store.get('weak:' + to, {});
      w[k] = weak[k];
      store.set('weak:' + to, w);
    });
    store.set('weak:core', stay);
    store.set('mock:missed', store.get('mock:missed', []).filter(function (id) { return id.indexOf('core-') !== 0; }));   // the cheat sheets changed
  } },
  /* v3: the Multithreading lesson was split into threads, tasks and atomics (performance went to Low-Latency). */
  { to: 3, run: function (store) {
    var SECS = {                                   // old section id -> [lesson, new section ids]
      s6: ['atomics', ['ops', 'ordering']], s8: ['tasks', ['futures', 'signals']], s9: ['tasks', ['pool', 'stealing']], s10: ['latency', []]
    };
    var done = store.get('done:threads', []), keep = [];
    done.forEach(function (id) {
      if (!SECS[id]) { keep.push(id); return; }
      var lesson = SECS[id][0], d = store.get('done:' + lesson, []);
      SECS[id][1].forEach(function (n) { if (d.indexOf(n) < 0) d.push(n); });
      store.set('done:' + lesson, d);
    });
    store.set('done:threads', keep);
    if (SECS[store.get('last:threads', '')]) store.set('last:threads', '');
    var li = store.get('lastinfo', null);
    if (li && li.id === 'threads' && SECS[li.sec]) store.set('lastinfo', null);
    var hash = function (s) { var x = 5381, i; for (i = 0; i < s.length; i++) x = ((x * 33) ^ s.charCodeAt(i)) >>> 0; return x.toString(36); };
    var WHERE = { 'al18rc': 'atomics', 'ncxiq8': 'atomics', '1ht5j1o': 'atomics', '13j0ql7': 'atomics',
      '1q4movb': 'tasks', '1fyjjhv': 'tasks', '1b9ljuy': 'tasks', 'c1ji5e': 'tasks', 'gbmj0f': 'latency', '19s2m74': 'latency' };
    var weak = store.get('weak:threads', {}), stay = {};
    Object.keys(weak).forEach(function (k) {
      var to = WHERE[hash(k)];
      if (!to) { stay[k] = weak[k]; return; }
      var w = store.get('weak:' + to, {});
      w[k] = weak[k];
      store.set('weak:' + to, w);
    });
    store.set('weak:threads', stay);
    store.set('mock:missed', store.get('mock:missed', []).filter(function (id) { return id.indexOf('threads-') !== 0; }));   // the cheat sheet changed
  } },
  /* v4: the STL strings section was replaced by custom keys, and the cheat sheets of the STL and Strings lessons changed. */
  { to: 4, run: function (store) {
    store.set('done:stl', store.get('done:stl', []).filter(function (id) { return id !== 's8'; }));
    if (store.get('last:stl', '') === 's8') store.set('last:stl', '');
    var li = store.get('lastinfo', null);
    if (li && li.id === 'stl' && li.sec === 's8') store.set('lastinfo', null);
    store.set('mock:missed', store.get('mock:missed', []).filter(function (id) { return id.indexOf('stl-') !== 0 && id.indexOf('strings-') !== 0; }));
  } },
  /* v5: the generated 'Read more in the books' section was replaced by notes inside the lesson sections: forget its ticks. */
  { to: 5, run: function (store) {
    CT.lessons.forEach(function (l) {
      store.set('done:' + l.id, store.get('done:' + l.id, []).filter(function (id) { return id !== 'read-more'; }));
      if (store.get('last:' + l.id, '') === 'read-more') store.set('last:' + l.id, '');
    });
    var li = store.get('lastinfo', null);
    if (li && li.sec === 'read-more') store.set('lastinfo', null);
  } },
  /* v6: the explicit / conversion operators / copy-and-swap section moved from the Object Model lesson to OOP; the
     cheat sheets of both lessons changed. */
  { to: 6, run: function (store) {
    var done = store.get('done:objmodel', []);
    if (done.indexOf('conversions') >= 0) {
      store.set('done:objmodel', done.filter(function (id) { return id !== 'conversions'; }));
      var o = store.get('done:oop', []);
      if (o.indexOf('conversions') < 0) o.push('conversions');
      store.set('done:oop', o);
    }
    if (store.get('last:objmodel', '') === 'conversions') store.set('last:objmodel', '');
    var li = store.get('lastinfo', null);
    if (li && li.id === 'objmodel' && li.sec === 'conversions') store.set('lastinfo', null);
    var WHERE = {'1e726nt': 'oop', 'cwsz48': 'oop', '19icvtn': 'oop'};
    var hash = function (s) { var x = 5381, i; for (i = 0; i < s.length; i++) x = ((x * 33) ^ s.charCodeAt(i)) >>> 0; return x.toString(36); };
    var weak = store.get('weak:objmodel', {}), stay = {};
    Object.keys(weak).forEach(function (k) {
      var to = WHERE[hash(k)];
      if (!to) { stay[k] = weak[k]; return; }
      var w = store.get('weak:' + to, {});
      w[k] = weak[k];
      store.set('weak:' + to, w);
    });
    store.set('weak:objmodel', stay);
    store.set('mock:missed', store.get('mock:missed', []).filter(function (id) { return id.indexOf('objmodel-') !== 0 && id.indexOf('oop-') !== 0; }));
  } },
  /* v7: the Coding Rules lesson was removed (its tooling material is now a section of Basics) and many cheat sheets were reworded:
     forget the rules progress and the saved missed mock questions. */
  { to: 7, run: function (store) {
    ['done:', 'last:', 'quiz:', 'total:', 'weak:'].forEach(function (p) { store.set(p + 'rules', p === 'done:' ? [] : p === 'weak:' ? {} : p === 'last:' ? '' : null); });
    var li = store.get('lastinfo', null);
    if (li && li.id === 'rules') store.set('lastinfo', null);
    store.set('mock:missed', []);
    // the patterns2 section 'feed' became 'state-machine'
    var p2 = store.get('done:patterns2', []);
    if (p2.indexOf('feed') >= 0) store.set('done:patterns2', p2.filter(function (id) { return id !== 'feed'; }).concat(p2.indexOf('state-machine') < 0 ? ['state-machine'] : []));
    if (store.get('last:patterns2', '') === 'feed') store.set('last:patterns2', 'state-machine');
    if (li && li.id === 'patterns2' && li.sec === 'feed') li.sec = 'state-machine', store.set('lastinfo', li);
  } },
  /* v8: the two regex sections of the Strings lesson were merged (s3 into s2). */
  { to: 8, run: function (store) {
    var d = store.get('done:strings', []);
    if (d.indexOf('s3') >= 0) store.set('done:strings', d.filter(function (id) { return id !== 's3'; }).concat(d.indexOf('s2') < 0 ? ['s2'] : []));
    if (store.get('last:strings', '') === 's3') store.set('last:strings', 's2');
    var li = store.get('lastinfo', null);
    if (li && li.id === 'strings' && li.sec === 's3') { li.sec = 's2'; store.set('lastinfo', li); }
  } }
];

/* The current schema version: the highest `to`, or 1 when there are no migrations. */
CT.schemaVersion = function () {
  return CT.progressMigrations.reduce(function (v, m) { return Math.max(v, m.to); }, 1);
};

/* Brings the saved progress in `store` up to date. Returns the version it ended at. */
CT.migrate = function (store) {
  var v = store.get('schema', 1);
  CT.progressMigrations.slice().sort(function (a, b) { return a.to - b.to; }).forEach(function (m) {
    if (m.to > v) {
      try { m.run(store); v = m.to; store.set('schema', v); } catch (e) { /* leave the old version so it retries next visit */ }
    }
  });
  return v;
};

/* Where did a section go? Returns 'file#id' or null. */
CT.resolveMoved = function (file, id) {
  return CT.moved[file + '#' + id] || null;
};
