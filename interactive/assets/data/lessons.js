/* The lesson registry: the single source of truth for the site and the tools in tools/.
 *
 * Loaded BEFORE assets/app.js on every page, and run by the Node tools through the vm module, so keep this
 * file plain ES5-style JavaScript with no DOM access.
 *
 * To add a lesson: create <file> and <quiz> (and assets/data/quiz-<id>.js), then add one entry below.
 * Navigation order and the displayed number come from the position in this array, not from the file name.
 * Fields: id (lowercase letters and digits, used in saved progress), phase (1 to 6, the roadmap phase the lesson belongs to; see CT.phases), file, quiz, title, time, assess (questions drawn
 * for the level check: 2 for every lesson, so the check is even; 0 leaves the lesson out), blurb.
 */
window.CT = window.CT || {};

/* The six phases of the C++ roadmap (docs/reading/roadmap). tools/build-checklist.mjs checks that every lesson's phase and
 * every phase's name and page match the roadmap files, so edit both together. */
CT.phases = [
  { n: 1, name: 'Core language foundations', page: 'phase-1-core-language-foundations.md' },
  { n: 2, name: 'Classes, memory and object-oriented design', page: 'phase-2-classes-memory-and-object-oriented-design.md' },
  { n: 3, name: 'The standard library and generic programming', page: 'phase-3-the-standard-library-and-generic-programming.md' },
  { n: 4, name: 'RAII, exceptions and advanced language tools', page: 'phase-4-raii-exceptions-and-advanced-language-tools.md' },
  { n: 5, name: 'Modern C++ (C++11 to C++20)', page: 'phase-5-modern-cpp.md' },
  { n: 6, name: 'Concurrency and the memory model', page: 'phase-6-concurrency-and-the-memory-model.md' }
];

CT.lessons = [
  { id: 'basics', file: '01-basics.html', quiz: '01-basics-quiz.html', title: 'C++ Basics', time: '40 min', assess: 2, phase: 1,
    blurb: 'How a program is built, types and variables, operators, control flow, functions and passing arguments, and the tools that catch mistakes.' },
  { id: 'pointers', file: '22-pointers.html', quiz: '22-pointers-quiz.html', title: 'Pointers and References', time: '50 min', assess: 2, phase: 1,
    blurb: 'Where variables live, what an address is, pointers, arrays and decay, references, const with pointers, new and delete, and the classic memory bugs, in pictures.' },
  { id: 'types', file: '16-types-and-casts.html', quiz: '16-types-and-casts-quiz.html', title: 'Types, Initialization & Constants', time: '30 min', assess: 2, phase: 1,
    blurb: 'Initialization forms and brace traps, auto and decltype, const, constexpr and static, and what C++14, 17 and 20 added.' },
  { id: 'casts', file: '25-casts.html', quiz: '25-casts-quiz.html', title: 'Casts and Type Conversions', time: '45 min', assess: 2, phase: 1,
    blurb: 'What the compiler converts silently, narrowing and braces, why the C-style cast is a trap, and static_cast, dynamic_cast, const_cast, reinterpret_cast and bit_cast.' },
  { id: 'oop', file: '02-oop.html', quiz: '02-oop-quiz.html', title: 'Classes and Objects', time: '40 min', assess: 2, phase: 2,
    blurb: 'Encapsulation and invariants, member functions and this, const and static members, constructors, destructors and object lifetime.' },
  { id: 'copying', file: '26-copying.html', quiz: '26-copying-quiz.html', title: 'Copy Control and Operators', time: '45 min', assess: 2, phase: 2,
    blurb: 'Shallow and deep copies, the Rule of 3, 5 and 0, explicit and conversion operators, copy-and-swap, and operator overloading.' },
  { id: 'inherit', file: '27-inherit.html', quiz: '27-inherit-quiz.html', title: 'Inheritance, Virtual Functions and the Object Model', time: '60 min', assess: 2, phase: 2,
    blurb: 'Is-a inheritance, how virtual calls work with the vtable and vptr, abstract classes, composition, multiple and virtual inheritance, RTTI and private inheritance.' },
  { id: 'strings', file: '08-strings-regex-time.html', quiz: '08-strings-regex-time-quiz.html', title: 'Strings, Regex & Time', time: '40 min', assess: 2, phase: 3,
    blurb: 'string versus string_view, regular expressions with a live tester, and measuring time with chrono clocks and durations.' },
  { id: 'callables', file: '23-callables.html', quiz: '23-callables-quiz.html', title: 'Function Pointers and Functors', time: '35 min', assess: 2, phase: 3,
    blurb: 'Function pointers, functors, std::function and std::invoke: the things you can call, what each can hold, and when to use which.' },
  { id: 'lambdas', file: '15-lambdas.html', quiz: '15-lambdas-quiz.html', title: 'Lambdas', time: '35 min', assess: 2, phase: 3,
    blurb: 'What a lambda is, captures and their lifetime traps, init-capture, generic lambdas and where lambdas are used.' },
  { id: 'stl', file: '04-stl.html', quiz: '04-stl-quiz.html', title: 'STL Containers', time: '35 min', assess: 2, phase: 3,
    blurb: 'vector, array, deque, list and the container adaptors: memory layout, operation costs, growth, and how to choose the right container.' },
  { id: 'assoc', file: '31-assoc.html', quiz: '31-assoc-quiz.html', title: 'Maps, Sets and Hashing', time: '40 min', assess: 2, phase: 3,
    blurb: 'map, set and the unordered containers: trees and hash tables, operator[] versus find, try_emplace, multimap, custom comparators and hashes, pair and tuple.' },
  { id: 'iterators', file: '28-iterators.html', quiz: '28-iterators-quiz.html', title: 'Iterators', time: '35 min', assess: 2, phase: 3,
    blurb: 'Iterators as generalised pointers, the half-open range, iterator categories, inserters, invalidation, and span and string_view as non-owning views.' },
  { id: 'algorithms', file: '29-algorithms.html', quiz: '29-algorithms-quiz.html', title: 'Algorithms and Ranges', time: '40 min', assess: 2, phase: 3,
    blurb: 'sort, find, transform and accumulate with lambdas, the erase-remove idiom, binary search, C++20 ranges and views, and random numbers.' },
  { id: 'templates', file: '05-templates.html', quiz: '05-templates-quiz.html', title: 'Function Templates', time: '45 min', assess: 2, phase: 3,
    blurb: 'Instantiation, argument deduction, variadic templates and fold expressions, and forwarding references.' },
  { id: 'classtemplates', file: '30-classtemplates.html', quiz: '30-classtemplates-quiz.html', title: 'Class Templates', time: '40 min', assess: 2, phase: 3,
    blurb: 'Class templates and non-type parameters, class template argument deduction, full and partial specialization, alias and variable templates.' },
  { id: 'compiletime', file: '09-compile-time.html', quiz: '09-compile-time-quiz.html', title: 'Type Traits, Concepts and Compile-time C++', time: '50 min', assess: 2, phase: 3,
    blurb: 'Type traits, if constexpr, SFINAE and enable_if, concepts and requires, constexpr and consteval, and classic template metaprogramming.' },
  { id: 'core', file: '03-core-language.html', quiz: '03-core-language-quiz.html', title: 'RAII and Exceptions', time: '30 min', assess: 2, phase: 4,
    blurb: 'RAII and scope guards, stack unwinding, the exception-safety guarantees and noexcept.' },
  { id: 'vocab', file: '21-vocabulary-types.html', quiz: '21-vocabulary-types-quiz.html', title: 'Values or Errors: optional, variant and expected', time: '30 min', assess: 2, phase: 5,
    blurb: 'Exceptions versus return values, and optional, variant and visit, and expected: saying no value or failed in the type.' },
  { id: 'moves', file: '13-move-semantics.html', quiz: '13-move-semantics-quiz.html', title: 'Lvalues and Rvalues', time: '30 min', assess: 2, phase: 5,
    blurb: 'Names versus temporaries, the value categories, and which references bind to what.' },
  { id: 'copymove', file: '33-copymove.html', quiz: '33-copymove-quiz.html', title: 'Copy versus Move, and std::move', time: '35 min', assess: 2, phase: 5,
    blurb: 'What a copy costs, what std::move really does, how a move steals, and what state a moved-from object is left in.' },
  { id: 'writemoves', file: '34-writemoves.html', quiz: '34-writemoves-quiz.html', title: 'Writing Move Operations', time: '35 min', assess: 2, phase: 5,
    blurb: 'The move constructor and move assignment step by step, copy-and-swap, why moves must be noexcept, and the Rule of Zero.' },
  { id: 'elision', file: '35-elision.html', quiz: '35-elision-quiz.html', title: 'Returning Objects and Copy Elision', time: '30 min', assess: 2, phase: 5,
    blurb: 'Why you return locals plainly: RVO, NRVO, guaranteed elision in C++17, and the few cases where std::move on a return is right.' },
  { id: 'sinks', file: '36-sinks.html', quiz: '36-sinks-quiz.html', title: 'Sink Parameters and Move Traps', time: '30 min', assess: 2, phase: 5,
    blurb: 'Taking a parameter you will store: by value and move versus overloads, the move traps, and push_back versus emplace_back.' },
  { id: 'forwarding', file: '37-forwarding.html', quiz: '37-forwarding-quiz.html', title: 'Perfect Forwarding', time: '35 min', assess: 2, phase: 5,
    blurb: 'Why a wrapper loses lvalue-ness, how std::forward restores it, reference collapsing and the cases where forwarding fails.' },
  { id: 'uniqueptr', file: '24-uniqueptr.html', quiz: '24-uniqueptr-quiz.html', title: 'unique_ptr: Exclusive Ownership', time: '35 min', assess: 2, phase: 5,
    blurb: 'Ownership in the type: how unique_ptr frees its object, why it is move-only, passing and returning it, deleters, arrays and the usual mistakes.' },
  { id: 'smartptr', file: '14-smart-pointers.html', quiz: '14-smart-pointers-quiz.html', title: 'shared_ptr: Shared Ownership', time: '35 min', assess: 2, phase: 5,
    blurb: 'When ownership is shared, the control block, make_shared, thread safety and the pitfalls.' },
  { id: 'weakptr', file: '32-weakptr.html', quiz: '32-weakptr-quiz.html', title: 'weak_ptr and Reference Cycles', time: '35 min', assess: 2, phase: 5,
    blurb: 'Why shared_ptr cycles leak, weak_ptr and lock(), and the three places weak_ptr belongs: parent links, caches and observers.' },
  { id: 'threads', file: '07-multithreading.html', quiz: '07-multithreading-quiz.html', title: 'Multithreading', time: '60 min', assess: 2, phase: 6,
    blurb: 'From your first thread to data races, mutexes, deadlocks, condition variables and the other mutex types.' },
  { id: 'tasks', file: '17-tasks-parallelism.html', quiz: '17-tasks-parallelism-quiz.html', title: 'Tasks & Parallelism', time: '45 min', assess: 2, phase: 6,
    blurb: 'Futures and async, promises, thread pools and work stealing, latch, barrier, semaphore, stop_token and parallel algorithms.' },
  { id: 'atomics', file: '18-atomics-memory-model.html', quiz: '18-atomics-memory-model-quiz.html', title: 'Atomics & the Memory Model', time: '55 min', assess: 2, phase: 6,
    blurb: 'Atomic operations, compare-and-swap, memory orders and happens-before with a simulator, ordering patterns and concurrent data structures.' },
];

/* When a section moves to another lesson, record where it went so old links keep working:
 *   'old-lesson.html#old-id': 'new-lesson.html#new-id'
 * app.js follows this when a link points at a section that is no longer on the page. */
CT.moved = {
  '05-templates.html#s7': '09-compile-time.html#s4',    // Compile-time computation: now Template metaprogramming
  '03-core-language.html#s2': '13-move-semantics.html#values',          // lesson 3 was split into five lessons
  '03-core-language.html#s3': '33-copymove.html#stdmove',
  '03-core-language.html#s4': '24-uniqueptr.html#owner',
  '03-core-language.html#s5': '16-types-and-casts.html#deduction',
  '03-core-language.html#s6': '15-lambdas.html#anatomy',
  '03-core-language.html#s8': '25-casts.html#static',
  '03-core-language.html#s9': '16-types-and-casts.html#const',
  '03-core-language.html#s10': '16-types-and-casts.html#standards',
  '08-strings-regex-time.html#s3': '08-strings-regex-time.html#s2',   // the two regex sections were merged
  '07-multithreading.html#s6': '18-atomics-memory-model.html#ops',        // the multithreading lesson was split in three
  '07-multithreading.html#s8': '17-tasks-parallelism.html#futures',
  '07-multithreading.html#s9': '17-tasks-parallelism.html#pool',
  '02-oop.html#s3': '26-copying.html#copy',                       // the OOP lesson was split in three: classes, copy control, inheritance
  '02-oop.html#conversions': '26-copying.html#conversions',
  '02-oop.html#s8': '26-copying.html#operators',
  '02-oop.html#s5': '27-inherit.html#inheritance',
  '02-oop.html#s6': '27-inherit.html#virtual',
  '02-oop.html#s7': '27-inherit.html#abstract',
  '02-oop.html#s9': '27-inherit.html#design',
  '16-types-and-casts.html#conversions': '25-casts.html#implicit',         // the conversions and casts sections became their own lesson
  '16-types-and-casts.html#casts': '25-casts.html#static',
  '14-smart-pointers.html#ownership': '24-uniqueptr.html#owner',      // the first two Smart Pointers sections became the unique_ptr lesson
  '14-smart-pointers.html#unique': '24-uniqueptr.html#basics',
  '15-lambdas.html#before': '23-callables.html#fnptr',          // the callable sections of Lambdas became their own lesson
  '15-lambdas.html#callables': '23-callables.html#choose',
  '01-basics.html#s5': '22-pointers.html#regions',            // the pointer sections of Basics became the Pointers lesson
  '01-basics.html#s6': '22-pointers.html#pointers',
  '01-basics.html#s7': '22-pointers.html#references',
  '01-basics.html#s8': '22-pointers.html#constptr',
  '01-basics.html#s9': '22-pointers.html#dynamic',
  '01-basics.html#s10': '22-pointers.html#arrays',
  '01-basics.html#s11': '22-pointers.html#bugs',
  '04-stl.html#s4': '31-assoc.html#s4',                        // associative containers, custom keys and pair/tuple became their own lesson
  '04-stl.html#keys': '31-assoc.html#keys',
  '04-stl.html#s6': '28-iterators.html#s6',                   // the STL lesson was split in three: containers, iterators, algorithms
  '04-stl.html#s7': '29-algorithms.html#s7',
  '04-stl.html#ranges': '29-algorithms.html#ranges',
  '04-stl.html#random': '29-algorithms.html#random',
  '04-stl.html#s9': '04-stl.html#pitfalls',
  '04-stl.html#s10': '04-stl.html#cheat',
  '21-vocabulary-types.html#pairs': '31-assoc.html#pairs',      // pair and tuple went to containers, span and string_view to iterators
  '21-vocabulary-types.html#views': '28-iterators.html#views',
  '05-templates.html#s2': '30-classtemplates.html#s2',        // the Templates lesson was split into function templates and class templates
  '05-templates.html#s3': '30-classtemplates.html#s3',
  '05-templates.html#tools': '30-classtemplates.html#tools',
  '05-templates.html#s6': '09-compile-time.html#ifconstexpr',
  '05-templates.html#s9': '05-templates.html#cheat',
  '13-move-semantics.html#copy-move': '33-copymove.html#stdmove',     // Move Semantics was split into six lessons
  '13-move-semantics.html#writing': '34-writemoves.html#ctor',
  '13-move-semantics.html#returning': '35-elision.html#whenmove',
  '13-move-semantics.html#traps': '36-sinks.html#traps',
  '13-move-semantics.html#forwarding': '37-forwarding.html#forward',
  '14-smart-pointers.html#weak': '32-weakptr.html#weak',             // shared_ptr and weak_ptr became two lessons
  '03-core-language.html#errors': '21-vocabulary-types.html#errors',  // exceptions versus return values went to the values-or-errors lesson
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
  } },
  /* v9: the lessons Design Patterns, More Patterns, Binary Data and Performance & Memory were removed. Forget their progress. */
  { to: 9, run: function (store) {
    var GONE = ['patterns', 'patterns2', 'wire', 'latency'];
    GONE.forEach(function (id) {
      ['done:', 'last:', 'quiz:', 'total:', 'weak:'].forEach(function (p) { store.set(p + id, p === 'done:' ? [] : p === 'weak:' ? {} : p === 'last:' ? '' : null); });
    });
    var li = store.get('lastinfo', null);
    if (li && GONE.indexOf(li.id) >= 0) store.set('lastinfo', null);
    store.set('mock:missed', store.get('mock:missed', []).filter(function (id) { return !GONE.some(function (g) { return id.indexOf(g + '-') === 0; }); }));
  } },
  /* v10: the pointer sections of the Basics lesson became the lesson Pointers and References. Ticks, the saved position, weak
     questions and cheat-sheet ids move with them. */
  { to: 10, run: function (store) {
    var SECS = { s5: 'regions', s6: 'pointers', s7: 'references', s8: 'constptr', s9: 'dynamic', s10: 'arrays', s11: 'bugs' };   // old basics section id -> pointers section id
    var done = store.get('done:basics', []), keep = [], moved = store.get('done:pointers', []);
    done.forEach(function (id) {
      if (!SECS[id]) { keep.push(id); return; }
      if (moved.indexOf(SECS[id]) < 0) moved.push(SECS[id]);
    });
    store.set('done:basics', keep);
    if (moved.length) store.set('done:pointers', moved);
    if (SECS[store.get('last:basics', '')]) store.set('last:basics', '');
    var li = store.get('lastinfo', null);
    if (li && li.id === 'basics' && SECS[li.sec]) store.set('lastinfo', null);
    var hash = function (s) { var x = 5381, i; for (i = 0; i < s.length; i++) x = ((x * 33) ^ s.charCodeAt(i)) >>> 0; return x.toString(36); };
    var WHERE = { '12rk0wq': 'pointers', '140heij': 'pointers', '1695ukm': 'pointers', '16dq4u': 'pointers', '1gjko1s': 'pointers', '1wy7ajg': 'pointers', '4glhig': 'pointers', '5ddfga': 'pointers', 'c4xhtz': 'pointers', 'kcotr5': 'pointers', 'rzuk2j': 'pointers', 'uxe5i5': 'pointers', 'yrsevc': 'pointers', 'yvgttd': 'pointers' };
    var weak = store.get('weak:basics', {}), stay = {};
    Object.keys(weak).forEach(function (k) {
      if (!WHERE[hash(k)]) { stay[k] = weak[k]; return; }
      var w = store.get('weak:pointers', {});
      w[k] = weak[k];
      store.set('weak:pointers', w);
    });
    store.set('weak:basics', stay);
    store.set('mock:missed', store.get('mock:missed', []).filter(function (id) { return id.indexOf('basics-') !== 0; }));   // the cheat sheet changed
  } },
  /* v11: the Lambdas lesson lost its two callable sections to the new lesson Function Pointers and Functors. */
  { to: 11, run: function (store) {
    var SECS = { before: ['fnptr', 'functor'], callables: ['stdfunction', 'choose'] };          // old lambdas section -> new callables sections
    var done = store.get('done:lambdas', []), keep = [], moved = store.get('done:callables', []);
    done.forEach(function (id) {
      if (!SECS[id]) { keep.push(id); return; }
      SECS[id].forEach(function (n) { if (moved.indexOf(n) < 0) moved.push(n); });
    });
    store.set('done:lambdas', keep);
    if (moved.length) store.set('done:callables', moved);
    if (SECS[store.get('last:lambdas', '')]) store.set('last:lambdas', '');
    var li = store.get('lastinfo', null);
    if (li && li.id === 'lambdas' && SECS[li.sec]) store.set('lastinfo', null);
    var hash = function (s) { var x = 5381, i; for (i = 0; i < s.length; i++) x = ((x * 33) ^ s.charCodeAt(i)) >>> 0; return x.toString(36); };
    var WHERE = { '1n3e8s0': 'callables', '1ny5xz': 'callables', '1o4szts': 'callables', '6h4nsm': 'callables', 'cnzgl8': 'callables' };
    var weak = store.get('weak:lambdas', {}), stay = {};
    Object.keys(weak).forEach(function (k) {
      if (!WHERE[hash(k)]) { stay[k] = weak[k]; return; }
      var w = store.get('weak:callables', {});
      w[k] = weak[k];
      store.set('weak:callables', w);
    });
    store.set('weak:lambdas', stay);
    store.set('mock:missed', store.get('mock:missed', []).filter(function (id) { return id.indexOf('lambdas-') !== 0; }));   // the cheat sheet changed
  } },
  /* v12: the first two sections of the Smart Pointers lesson became the lesson unique_ptr: Exclusive Ownership. */
  { to: 12, run: function (store) {
    var SECS = { ownership: ['owner', 'pass'], unique: ['basics', 'move', 'details'] };         // old smartptr section -> new uniqueptr sections
    var done = store.get('done:smartptr', []), keep = [], moved = store.get('done:uniqueptr', []);
    done.forEach(function (id) {
      if (!SECS[id]) { keep.push(id); return; }
      SECS[id].forEach(function (n) { if (moved.indexOf(n) < 0) moved.push(n); });
    });
    store.set('done:smartptr', keep);
    if (moved.length) store.set('done:uniqueptr', moved);
    if (SECS[store.get('last:smartptr', '')]) store.set('last:smartptr', '');
    var li = store.get('lastinfo', null);
    if (li && li.id === 'smartptr' && SECS[li.sec]) store.set('lastinfo', null);
    var hash = function (s) { var x = 5381, i; for (i = 0; i < s.length; i++) x = ((x * 33) ^ s.charCodeAt(i)) >>> 0; return x.toString(36); };
    var WHERE = { '1cbs40b': 'uniqueptr', '1lnknas': 'uniqueptr', '2xwsc1': 'uniqueptr', 'l2v1mh': 'uniqueptr', 'mhbz02': 'uniqueptr', 'v9cdh9': 'uniqueptr' };
    var weak = store.get('weak:smartptr', {}), stay = {};
    Object.keys(weak).forEach(function (k) {
      if (!WHERE[hash(k)]) { stay[k] = weak[k]; return; }
      var w = store.get('weak:uniqueptr', {});
      w[k] = weak[k];
      store.set('weak:uniqueptr', w);
    });
    store.set('weak:smartptr', stay);
    store.set('mock:missed', store.get('mock:missed', []).filter(function (id) { return id.indexOf('smartptr-') !== 0; }));   // the cheat sheet changed
  } },
  /* v13: the conversions and casts sections of the Types lesson became the lesson Casts and Type Conversions (the enum class
     section was dropped). */
  { to: 13, run: function (store) {
    var SECS = { conversions: ['implicit', 'narrowing'], casts: ['cstyle', 'static', 'dynamic', 'constcast', 'choose'] };   // old types section -> new casts sections
    var done = store.get('done:types', []), keep = [], moved = store.get('done:casts', []);
    done.forEach(function (id) {
      if (!SECS[id]) { keep.push(id); return; }
      SECS[id].forEach(function (n) { if (moved.indexOf(n) < 0) moved.push(n); });
    });
    store.set('done:types', keep);
    if (moved.length) store.set('done:casts', moved);
    if (SECS[store.get('last:types', '')]) store.set('last:types', '');
    var li = store.get('lastinfo', null);
    if (li && li.id === 'types' && SECS[li.sec]) store.set('lastinfo', null);
    var hash = function (s) { var x = 5381, i; for (i = 0; i < s.length; i++) x = ((x * 33) ^ s.charCodeAt(i)) >>> 0; return x.toString(36); };
    var WHERE = { '10df3o5': 'casts', '13h63if': 'casts', '1ggqdb0': 'casts', 'inzmcy': 'casts', 'kcswmp': 'casts' };
    var GONE = { '8eaw0v': 1 };                                   // the enum class question
    var weak = store.get('weak:types', {}), stay = {};
    Object.keys(weak).forEach(function (k) {
      var h = hash(k);
      if (GONE[h]) return;
      if (!WHERE[h]) { stay[k] = weak[k]; return; }
      var w = store.get('weak:casts', {});
      w[k] = weak[k];
      store.set('weak:casts', w);
    });
    store.set('weak:types', stay);
    store.set('mock:missed', store.get('mock:missed', []).filter(function (id) { return id.indexOf('types-') !== 0; }));   // the cheat sheet changed
  } },
  /* v14: the OOP lesson was split into Classes and Objects, Copy Control and Operators, and Inheritance, Virtual Functions and the
     Object Model; the Object Model in Depth lesson was merged into the last one. */
  { to: 14, run: function (store) {
    var SECS = { s3: ['copying', 'copy'], conversions: ['copying', 'conversions'], s8: ['copying', 'operators'],
      s5: ['inherit', 'inheritance'], s6: ['inherit', 'virtual'], s7: ['inherit', 'abstract'], s9: ['inherit', 'design'] };   // old oop section -> [new lesson, new section]
    var done = store.get('done:oop', []), keep = [];
    done.forEach(function (id) {
      if (!SECS[id]) { keep.push(id); return; }
      var d = store.get('done:' + SECS[id][0], []);
      if (d.indexOf(SECS[id][1]) < 0) d.push(SECS[id][1]);
      store.set('done:' + SECS[id][0], d);
    });
    store.set('done:oop', keep);
    var om = store.get('done:objmodel', []);
    if (om.length) {
      var d2 = store.get('done:inherit', []);
      om.forEach(function (id) { if (d2.indexOf(id) < 0) d2.push(id); });
      store.set('done:inherit', d2);
    }
    if (SECS[store.get('last:oop', '')]) store.set('last:oop', '');
    var li = store.get('lastinfo', null);
    if (li && li.id === 'objmodel') store.set('lastinfo', null);
    if (li && li.id === 'oop' && SECS[li.sec]) store.set('lastinfo', null);
    var hash = function (s) { var x = 5381, i; for (i = 0; i < s.length; i++) x = ((x * 33) ^ s.charCodeAt(i)) >>> 0; return x.toString(36); };
    var WHERE = {'1lci8e8': 'copying', '1iuz060': 'copying', '12rk0wq': 'inherit', '1w60i7u': 'inherit', '73xv3e': 'inherit', '18nvff': 'inherit', '1kgmqwi': 'inherit', 'f5vycw': 'copying', '9xii7h': 'inherit', 'qna1n': 'copying', '6bxs1o': 'inherit', 'uxe5i5': 'copying', 'labf5h': 'copying', '1e726nt': 'copying', 'cwsz48': 'copying', '19icvtn': 'copying'};
    var moveWeak = function (from, always) {
      var weak = store.get('weak:' + from, {}), stay = {};
      Object.keys(weak).forEach(function (k) {
        var to = always || WHERE[hash(k)];
        if (!to) { stay[k] = weak[k]; return; }
        var w = store.get('weak:' + to, {});
        w[k] = weak[k];
        store.set('weak:' + to, w);
      });
      store.set('weak:' + from, stay);
    };
    moveWeak('oop');
    moveWeak('objmodel', 'inherit');
    ['done:', 'last:', 'quiz:', 'total:', 'weak:'].forEach(function (p) { store.set(p + 'objmodel', p === 'done:' ? [] : p === 'weak:' ? {} : p === 'last:' ? '' : null); });
    store.set('mock:missed', store.get('mock:missed', []).filter(function (id) { return id.indexOf('oop-') !== 0 && id.indexOf('objmodel-') !== 0; }));   // the cheat sheets changed
  } },
  /* v15: the STL lesson became STL Containers, Iterators, and Algorithms and Ranges; pair/tuple and span/string_view moved out of the
     vocabulary-types lesson; the Templates lesson became Function Templates and Class Templates, and its traits section joined the
     compile-time lesson. */
  { to: 15, run: function (store) {
    var SECS = {
      stl: { s4: ['assoc', ['s4']], keys: ['assoc', ['keys']], s6: ['iterators', ['s6', 'adaptors', 'invalidation']], s7: ['algorithms', ['s7']], ranges: ['algorithms', ['ranges']], random: ['algorithms', ['random']], s9: ['stl', ['pitfalls']], s10: ['stl', ['cheat']] },
      vocab: { pairs: ['assoc', ['pairs']], views: ['iterators', ['views']] },
      templates: { s2: ['classtemplates', ['s2']], s3: ['classtemplates', ['s3']], tools: ['classtemplates', ['tools']], s6: ['compiletime', ['ifconstexpr']], s9: ['templates', ['cheat']] }
    };   // old lesson -> old section -> [new lesson, new section ids]
    var hash = function (s) { var x = 5381, i; for (i = 0; i < s.length; i++) x = ((x * 33) ^ s.charCodeAt(i)) >>> 0; return x.toString(36); };
    var WHERE = { stl: {'12rk0wq': 'algorithms', 'jlcsy': 'iterators', 'nu1uji': 'assoc', '1pw8gum': 'iterators', 'b1zvow': 'assoc', '13ikhrm': 'algorithms', '49g3nb': 'algorithms', '88ygc5': 'assoc', 'x7h99w': 'iterators', '17hn921': 'assoc', 'hsrt9i': 'assoc', '1ki4g6j': 'assoc', '1e7nyhw': 'assoc', 'ko6xpa': 'assoc', '1qsn1a2': 'assoc', '1u7mfqk': 'assoc', 'vv9780': 'iterators', '799bam': 'algorithms', '1xkqtt4': 'algorithms', 'n6mxl4': 'algorithms', '1c4l6xi': 'algorithms', 'p4q63z': 'algorithms'}, vocab: {'xar4d9': 'assoc', '24zj67': 'assoc', 'x55o0f': 'iterators', '1qwpi8j': 'iterators'}, templates: {'1fft48l': 'classtemplates', '2momso': 'classtemplates', 'dsv88v': 'classtemplates', '1fb048j': 'compiletime', 'sef9pz': 'compiletime', '1si2x4g': 'classtemplates', '1t8z3jb': 'classtemplates', '1xfrar0': 'classtemplates', 'q6m83n': 'classtemplates'} };
    Object.keys(SECS).forEach(function (from) {
      var done = store.get('done:' + from, []), keep = [];
      done.forEach(function (id) {
        var t = SECS[from][id];
        if (!t) { keep.push(id); return; }
        var d = store.get('done:' + t[0], []);
        t[1].forEach(function (n) { if (d.indexOf(n) < 0) d.push(n); });
        store.set('done:' + t[0], d);
        if (t[0] === from) keep.push.apply(keep, t[1]);
      });
      store.set('done:' + from, keep.filter(function (id, i) { return keep.indexOf(id) === i; }));
      if (SECS[from][store.get('last:' + from, '')]) store.set('last:' + from, '');
      var li = store.get('lastinfo', null);
      if (li && li.id === from && SECS[from][li.sec]) store.set('lastinfo', null);
      var weak = store.get('weak:' + from, {}), stay = {};
      Object.keys(weak).forEach(function (k) {
        var to = WHERE[from][hash(k)];
        if (!to) { stay[k] = weak[k]; return; }
        var w = store.get('weak:' + to, {});
        w[k] = weak[k];
        store.set('weak:' + to, w);
      });
      store.set('weak:' + from, stay);
    });
    var gone = ['stl-', 'vocab-', 'templates-', 'compiletime-'];   // 'assoc-' ids only exist from now on
    store.set('mock:missed', store.get('mock:missed', []).filter(function (id) { return !gone.some(function (g) { return id.indexOf(g) === 0; }); }));   // the cheat sheets changed
  } },
  /* v16: Move Semantics became six lessons, shared_ptr and weak_ptr two, and the exceptions-versus-return-values section of the core
     lesson moved to the values-or-errors lesson. */
  { to: 16, run: function (store) {
    var SECS = {
      moves: { values: ['moves', ['values', 'binding', 'named']], 'copy-move': ['copymove', ['cost', 'stdmove', 'movedfrom']], writing: ['writemoves', ['ctor', 'assign', 'noexcept', 'zero']],
        returning: ['elision', ['rvo', 'whenmove']], traps: ['sinks', ['sink', 'choose', 'traps', 'emplace']], forwarding: ['forwarding', ['problem', 'forward', 'collapse']] },
      smartptr: { weak: ['weakptr', ['cycle', 'weak']] },
      core: { errors: ['vocab', ['errors']] }
    };   // old lesson -> old section -> [new lesson, new section ids]
    var hash = function (s) { var x = 5381, i; for (i = 0; i < s.length; i++) x = ((x * 33) ^ s.charCodeAt(i)) >>> 0; return x.toString(36); };
    var WHERE = { moves: {'v12hn1': 'copymove', '1j0lv33': 'copymove', 'vjjybz': 'elision', 'bj9033': 'writemoves', '1hybzdt': 'sinks', 'n27cgk': 'writemoves', 'a0tij4': 'writemoves', '1f2arp9': 'elision', 'pr9mmj': 'elision', '1hqv4g8': 'sinks', '1f28stg': 'sinks', 'e401ix': 'forwarding', '131k7yk': 'forwarding'}, smartptr: {'kl74xr': 'weakptr', '1g8ufty': 'weakptr', '153zkxg': 'weakptr', '1w0lydz': 'weakptr'}, core: {'oiyex4': 'vocab', '1u6vy2y': 'vocab'} };
    Object.keys(SECS).forEach(function (from) {
      var done = store.get('done:' + from, []), keep = [];
      done.forEach(function (id) {
        var t = SECS[from][id];
        if (!t) { keep.push(id); return; }
        var d = store.get('done:' + t[0], []);
        t[1].forEach(function (n) { if (d.indexOf(n) < 0) d.push(n); });
        store.set('done:' + t[0], d);
        if (t[0] === from) keep.push.apply(keep, t[1]);
      });
      store.set('done:' + from, keep.filter(function (id, i) { return keep.indexOf(id) === i; }));
      if (SECS[from][store.get('last:' + from, '')]) store.set('last:' + from, '');
      var li = store.get('lastinfo', null);
      if (li && li.id === from && SECS[from][li.sec]) store.set('lastinfo', null);
      var weak = store.get('weak:' + from, {}), stay = {};
      Object.keys(weak).forEach(function (k) {
        var to = WHERE[from][hash(k)];
        if (!to) { stay[k] = weak[k]; return; }
        var w = store.get('weak:' + to, {});
        w[k] = weak[k];
        store.set('weak:' + to, w);
      });
      store.set('weak:' + from, stay);
    });
    var gone = ['moves-', 'smartptr-', 'core-', 'vocab-'];
    store.set('mock:missed', store.get('mock:missed', []).filter(function (id) { return !gone.some(function (g) { return id.indexOf(g) === 0; }); }));   // the cheat sheets changed
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
