/* The lesson registry: the single source of truth for the site and the tools in tools/.
 *
 * Loaded BEFORE assets/app.js on every page, and run by the Node tools through the vm module, so keep this
 * file plain ES5-style JavaScript with no DOM access.
 *
 * To add a lesson: create <file> and <quiz> (and assets/data/quiz-<id>.js), then add one entry below.
 * Navigation order and the displayed number come from the position in this array, not from the file name.
 * Fields: id (lowercase letters and digits, used in saved progress), file, quiz, title, time, hot (named in the
 * job description), assess (questions drawn for the level check, 0 to leave the lesson out), blurb.
 */
window.CT = window.CT || {};

CT.lessons = [
  { id: 'basics', file: '01-basics.html', quiz: '01-basics-quiz.html', title: 'C++ Basics & Pointers', time: '60 min', hot: false, assess: 2,
    blurb: 'Types, functions, memory, pointers, references, const and dynamic allocation, built up from zero.' },
  { id: 'oop', file: '02-oop.html', quiz: '02-oop-quiz.html', title: 'Object-Oriented Programming', time: '60 min', hot: false, assess: 3,
    blurb: 'Classes, constructors, rule of 3/5/0, inheritance, virtual functions, abstract classes, operator overloading.' },
  { id: 'core', file: '03-core-language.html', quiz: '03-core-language-quiz.html', title: 'Core Language: RAII & Exceptions', time: '35 min', hot: true, assess: 1,
    blurb: 'RAII and scope guards, stack unwinding, the exception-safety guarantees, noexcept, and exceptions versus return values.' },
  { id: 'moves', file: '13-move-semantics.html', quiz: '13-move-semantics-quiz.html', title: 'Move Semantics', time: '45 min', hot: true, assess: 2,
    blurb: 'Value categories, what std::move really does, writing move operations, copy elision and the move traps.' },
  { id: 'smartptr', file: '14-smart-pointers.html', quiz: '14-smart-pointers-quiz.html', title: 'Smart Pointers & Ownership', time: '40 min', hot: true, assess: 2,
    blurb: 'unique_ptr, shared_ptr and weak_ptr, the control block, cycles, custom deleters and how to pass ownership around.' },
  { id: 'lambdas', file: '15-lambdas.html', quiz: '15-lambdas-quiz.html', title: 'Lambdas & Callables', time: '35 min', hot: true, assess: 1,
    blurb: 'Captures and their lifetime traps, init-capture, generic lambdas, and function pointer versus functor versus lambda versus std::function.' },
  { id: 'types', file: '16-types-and-casts.html', quiz: '16-types-and-casts-quiz.html', title: 'Types, Initialization & Casts', time: '40 min', hot: false, assess: 1,
    blurb: 'Initialization forms and brace traps, auto and decltype, implicit conversions, the named casts, const, constexpr and static.' },
  { id: 'stl', file: '04-stl.html', quiz: '04-stl-quiz.html', title: 'The STL', time: '60 min', hot: false, assess: 3,
    blurb: 'Containers, iterators, algorithms, complexity, iterator invalidation and how to choose the right container.' },
  { id: 'templates', file: '05-templates.html', quiz: '05-templates-quiz.html', title: 'Templates', time: '60 min', hot: true, assess: 4,
    blurb: 'Function and class templates, specialization, forwarding references, variadic templates, type traits, if constexpr.' },
  { id: 'patterns', file: '06-design-patterns.html', quiz: '06-design-patterns-quiz.html', title: 'Design Patterns', time: '50 min', hot: true, assess: 3,
    blurb: 'Singleton, Factory, Strategy, Observer and State in modern C++, plus the idioms you should recognise.' },
  { id: 'threads', file: '07-multithreading.html', quiz: '07-multithreading-quiz.html', title: 'Multithreading', time: '60 min', hot: true, assess: 3,
    blurb: 'From your first thread to data races, mutexes, deadlocks, condition variables and the other mutex types.' },
  { id: 'tasks', file: '17-tasks-parallelism.html', quiz: '17-tasks-parallelism-quiz.html', title: 'Tasks & Parallelism', time: '45 min', hot: true, assess: 1,
    blurb: 'Futures and async, promises, thread pools and work stealing, latch, barrier, semaphore, stop_token and parallel algorithms.' },
  { id: 'atomics', file: '18-atomics-memory-model.html', quiz: '18-atomics-memory-model-quiz.html', title: 'Atomics & the Memory Model', time: '55 min', hot: true, assess: 2,
    blurb: 'Atomic operations, compare-and-swap, memory orders and happens-before with a simulator, ordering patterns and concurrent data structures.' },
  { id: 'strings', file: '08-strings-regex-time.html', quiz: '08-strings-regex-time-quiz.html', title: 'Strings, Regex & Time', time: '40 min', hot: false, assess: 2,
    blurb: 'string versus string_view, regular expressions with a live tester, and measuring time with chrono clocks and durations.' },
  { id: 'compiletime', file: '09-compile-time.html', quiz: '09-compile-time-quiz.html', title: 'Type Traits & Compile-time C++', time: '45 min', hot: true, assess: 2,
    blurb: 'Type traits, SFINAE, if constexpr, constexpr and consteval, and classic template metaprogramming.' },
  { id: 'rules', file: '10-coding-rules.html', quiz: '10-coding-rules-quiz.html', title: 'Coding Rules & Safe C++', time: '30 min', hot: true, assess: 2,
    blurb: 'MISRA and AUTOSAR C++14, typical safety rules and why they exist, and static analysis in practice.' },
  { id: 'wire', file: '11-wire-formats.html', quiz: '11-wire-formats-quiz.html', title: 'Wire Formats & Parsing', time: '60 min', hot: true, assess: 3,
    blurb: 'Bit manipulation, struct layout and padding, endianness, aliasing and memcpy, zero-copy parsing, fixed-point prices and sequence numbers.' },
  { id: 'latency', file: '12-low-latency.html', quiz: '12-low-latency-quiz.html', title: 'Low-Latency C++', time: '60 min', hot: true, assess: 3,
    blurb: 'Tail latency, pools and arenas, cache-friendly data, order-book structures, SPSC queues, predictable hot paths and core pinning.' },
  { id: 'objmodel', file: '19-object-model.html', quiz: '19-object-model-quiz.html', title: 'The Object Model in Depth', time: '40 min', hot: false, assess: 2,
    blurb: 'Multiple inheritance and layout, the diamond and virtual inheritance, RTTI, private inheritance, explicit conversions and copy-and-swap.' },
  { id: 'patterns2', file: '20-more-patterns.html', quiz: '20-more-patterns-quiz.html', title: 'More Patterns & Feed-Handler Designs', time: '40 min', hot: true, assess: 2,
    blurb: 'Command with undo, Decorator, Adapter, Builder, Visitor with std::variant and a session state machine, with real code.' }
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
  '07-multithreading.html#s6': '18-atomics-memory-model.html#ops',        // the multithreading lesson was split in three
  '07-multithreading.html#s8': '17-tasks-parallelism.html#futures',
  '07-multithreading.html#s9': '17-tasks-parallelism.html#pool',
  '07-multithreading.html#s10': '12-low-latency.html#s8',
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
