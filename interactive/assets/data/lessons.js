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
  { id: 'core', file: '03-core-language.html', quiz: '03-core-language-quiz.html', title: 'Core Language & Modern C++', time: '75 min', hot: true, assess: 4,
    blurb: 'RAII, move semantics, smart pointers, lambdas, exceptions, casts and the C++11/14/17 features interviewers ask about.' },
  { id: 'stl', file: '04-stl.html', quiz: '04-stl-quiz.html', title: 'The STL', time: '60 min', hot: false, assess: 3,
    blurb: 'Containers, iterators, algorithms, complexity, iterator invalidation and how to choose the right container.' },
  { id: 'templates', file: '05-templates.html', quiz: '05-templates-quiz.html', title: 'Templates', time: '60 min', hot: true, assess: 4,
    blurb: 'Function and class templates, specialization, forwarding references, variadic templates, type traits, if constexpr.' },
  { id: 'patterns', file: '06-design-patterns.html', quiz: '06-design-patterns-quiz.html', title: 'Design Patterns', time: '50 min', hot: true, assess: 3,
    blurb: 'Singleton, Factory, Strategy, Observer and State in modern C++, plus the idioms you should recognise.' },
  { id: 'threads', file: '07-multithreading.html', quiz: '07-multithreading-quiz.html', title: 'Multithreading', time: '90 min', hot: true, assess: 5,
    blurb: 'From your first thread to mutexes, deadlocks, atomics, condition variables, futures and thread pools.' },
  { id: 'strings', file: '08-strings-regex-time.html', quiz: '08-strings-regex-time-quiz.html', title: 'Strings, Regex & Time', time: '40 min', hot: false, assess: 2,
    blurb: 'string versus string_view, regular expressions with a live tester, and measuring time with chrono clocks and durations.' },
  { id: 'compiletime', file: '09-compile-time.html', quiz: '09-compile-time-quiz.html', title: 'Type Traits & Compile-time C++', time: '45 min', hot: true, assess: 2,
    blurb: 'Type traits, SFINAE, if constexpr, constexpr and consteval, and classic template metaprogramming.' },
  { id: 'rules', file: '10-coding-rules.html', quiz: '10-coding-rules-quiz.html', title: 'Coding Rules & Safe C++', time: '30 min', hot: true, assess: 2,
    blurb: 'MISRA and AUTOSAR C++14, typical safety rules and why they exist, and static analysis in practice.' }
];

/* When a section moves to another lesson, record where it went so old links keep working:
 *   'old-lesson.html#old-id': 'new-lesson.html#new-id'
 * app.js follows this when a link points at a section that is no longer on the page. */
CT.moved = {
  '05-templates.html#s7': '09-compile-time.html#s4'     // Compile-time computation: now Template metaprogramming
};

/* Saved progress is stored per lesson id and section id. When ids change (a lesson is split or renamed), add a
 * migration here. Each runs once per browser, in order of `to`, and MUST be idempotent (it can run again after
 * importing an older progress code).
 *   { to: 2, run: function (store) { var d = store.get('done:core', []); store.set('done:raii', d); } }
 * `store` has get(key, default) and set(key, value); keys carry no prefix. */
CT.progressMigrations = [];

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
