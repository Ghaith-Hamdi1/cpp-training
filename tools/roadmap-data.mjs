// The data behind the C++ roadmap (docs/reading/roadmap): the eight phases with their topics, book reading, lessons, exercises and
// recap, plus the topic index. tools/build-roadmap.mjs turns it into the roadmap README and one page per phase, and `--check` (run in CI)
// fails if those pages differ from it. Edit this file, then run `node tools/build-roadmap.mjs`.
//
// Page numbers are PDF viewer pages. C++ Primer's own page numbers are 29 lower, so P(a, b) takes the book's numbers and shifts them.
// After editing a page range, run `node tools/check-book-pages.mjs` to confirm each section starts on the page given.
// Lesson numbers, titles and times are NOT here: the builder reads them from the lesson registry (interactive/assets/data/lessons.js).

export const OFF = 29;
export const P = (a, b) => [a + OFF, b + OFF];
export const pagesOf = (ranges) => ranges.reduce((n, [a, b]) => n + (b - a + 1), 0);
export const fmt = (ranges) => ranges.map(([a, b]) => (a === b ? String(a) : a + ' to ' + b)).join('; ');
export const SHORT = { primer: 'Primer', ppp: 'PPP', emc: 'EMC', mv: 'Move Semantics', cia: 'Concurrency in Action' };
export const PAGE_PER_HOUR = 10;

// each row: [book, label, ranges, why]
export const phases = [
  {
    n: 1, name: 'Core language foundations', sub: 'Types, expressions, control flow, functions, pointers, references, strings and vectors',
    topics: [
      ['Types and initialization', 'Built-in types, literals, `auto` and `decltype`, brace initialization and why it rejects narrowing, `const` and `constexpr` basics.'],
      ['Expressions and conversions', 'Operator precedence, integer promotion, signed versus unsigned traps, bitwise operators, the named casts.'],
      ['Control flow', '`if`/`switch`, loops, range-for, `try`/`catch` first look.'],
      ['Functions', 'Declarations versus definitions, passing by value, by reference and by `const` reference, return values, default arguments, overloading and overload resolution, function pointers.'],
      ['Pointers, references and arrays', 'Addresses, `nullptr`, pointer arithmetic, array-to-pointer decay, reference rules, `const` with pointers, dangling and null dereference.'],
      ['Strings and vectors', '`std::string` and `std::vector` as the default tools, iterators as a first idea, `string_view`, C strings and why to avoid them.'],
      ['Scope, lifetime and storage', 'Stack, heap and static storage, namespaces, `static`, linkage, the compile-link process.'],
    ],
    core: [
      ['primer', 'ch. 2 Variables and Basic Types (2.1 to 2.6)', [P(32, 80)], 'Types, `const`, compound types, `auto`/`decltype`, defining your own structs'],
      ['primer', 'ch. 3 Strings, Vectors and Arrays (3.2 to 3.6)', [P(84, 132)], '`string`, `vector`, iterators, built-in arrays'],
      ['primer', '4.2 to 4.5 Operators (short-circuit `&&`/`||`, prefix versus postfix `++`); 4.8 Bitwise operators; 4.11 Type conversions', [P(139, 149), P(152, 155), P(159, 165)], 'Operator rules, bit operations and every implicit conversion'],
      ['primer', '5.3 to 5.5 Statements: `switch` fall-through, the dangling `else`, loops and jumps', [P(174, 192)], 'Control flow rules that hide subtle bugs'],
      ['primer', 'ch. 6 Functions (6.1 to 6.7)', [P(202, 252)], 'Argument passing, overloading, function matching, function pointers'],
    ],
    deepen: [
      ['ppp', 'Types and initialization: 2.5; 2.8 to 2.10', [[49, 52], [56, 60]], 'A shorter second view of initialization, conversions and `auto`'],
      ['ppp', 'Functions and `vector`: 3.5 to 3.6; 4.5 to 4.6', [[81, 89], [102, 111]], 'Functions, `vector`, run-time errors and exceptions'],
      ['ppp', 'Declarations, scope and argument passing: 7.2 to 7.4', [[194, 218]], 'Scope, storage and how arguments are passed'],
      ['ppp', 'Memory, addresses and pointers: 15.3 to 15.5', [[452, 463]], 'Pointers, the free store, `delete`, dangling pointers'],
      ['ppp', 'Arrays, `this`, alternatives to raw pointers: 15.6 to 15.8; 16.1 to 16.4', [[464, 473], [477, 487]], 'Arrays, references versus pointers, `span`'],
    ],
    lessons: ['basics', 'types'], practice: ['01 to 09 (C strings, pointers, `trim`, `parseUnsigned`)', 9 * 15],
    recap: 'Explain from memory: what `int* const p` means, why `int{3.7}` is an error, what `v[i]` does that `v.at(i)` does not, why an array parameter is really a pointer, and what the linker error "undefined reference" means.',
  },
  {
    n: 2, name: 'Classes, memory and object-oriented design', sub: 'Class design, copy control, operator overloading, inheritance, virtual functions, the object model',
    topics: [
      ['Class design', 'Invariants, encapsulation, constructors and the initializer list, `explicit`, `const` and `static` members, `friend`.'],
      ['Object lifetime', 'Construction and destruction order, the destructor as cleanup, temporaries.'],
      ['Copy control', 'The copy constructor and assignment, shallow versus deep copy, the Rule of Three, Five and Zero, `= default` and `= delete`, copy-and-swap.'],
      ['Dynamic memory', '`new`/`delete`, `new[]`/`delete[]`, leaks, double delete, why this is replaced by RAII in phase 4 and smart pointers in phase 5.'],
      ['Operator overloading and conversions', 'Member versus non-member operators, `<<`/`>>`, comparison, `operator()`, conversion operators and `explicit`.'],
      ['Inheritance and polymorphism', 'Public inheritance as is-a, virtual functions and `override`, virtual destructors, slicing, abstract classes and interfaces.'],
      ['The object model', 'The vtable and vptr, multiple inheritance and pointer adjustment, the diamond and virtual inheritance, RTTI and `dynamic_cast`, private inheritance.'],
    ],
    core: [
      ['primer', 'ch. 7 Classes (7.1 to 7.6)', [P(254, 306)], 'Abstract data types, constructors, `const`/`mutable`/`static` members, class scope'],
      ['primer', '12.1.2 Managing memory directly; 12.2.1 `new` and arrays', [P(458, 463), P(477, 480)], '`new`/`delete` and their pitfalls (read before copy control)'],
      ['primer', 'ch. 13 Copy Control (13.1 to 13.5)', [P(496, 530)], 'Copy constructor, assignment, destructor, Rule of Three/Five, classes that manage memory'],
      ['primer', 'ch. 14 Overloaded Operations and Conversions (14.1 to 14.9)', [P(552, 590)], 'Operator overloading and conversion operators'],
      ['primer', 'ch. 15 Object-Oriented Programming (15.1 to 15.9)', [P(592, 650)], 'Base and derived classes, virtual functions, abstract classes, copy control with inheritance'],
      ['primer', '18.3 Multiple and virtual inheritance; 19.2 Run-time type identification', [P(802, 818), P(825, 831)], 'The diamond, `dynamic_cast`, `typeid`'],
    ],
    deepen: [
      ['ppp', 'Classes as a way to keep objects valid: 8.1 to 8.7', [[235, 258]], 'Invariants and class interfaces'],
      ['ppp', 'Inheritance and virtual functions: 12.1 to 12.5', [[369, 390]], 'The vptr/vtbl layout and virtual destructors'],
      ['ppp', 'Copying, moving and `vector` growth: 17.4 to 17.9', [[501, 523]], 'Essential operations and how `vector` is built'],
      ['emc', 'Item 12 `override`; Item 17 special member generation', [[97, 104], [127, 133]], 'The two items that fix the most real bugs in class design'],
    ],
    lessons: ['oop', 'objmodel'], practice: ['10 (`MyString`) and 11 (Shapes)', 50],
    recap: 'Explain aloud how `virtual` works in memory (vptr, vtable, slot), why a base destructor must be virtual, what the Rule of Zero says, and why `Animal a = dog;` slices.',
  },
  {
    n: 3, name: 'The standard library and generic programming', sub: 'Streams, containers, iterators, algorithms, templates',
    topics: [
      ['I/O and streams', 'Stream state, files, string streams, formatted input and output, `std::format` as the modern alternative.'],
      ['Sequential containers', '`vector`, `deque`, `list`, `array`; how `vector` grows; invalidation rules; `string` operations.'],
      ['Associative and unordered containers', '`map`/`set`, `unordered_map`, custom keys, comparators and hashes, `try_emplace`.'],
      ['Iterators and algorithms', 'Iterator categories, the algorithm header, predicates and function objects, erase-remove, `lower_bound`.'],
      ['Function and class templates', 'Instantiation, argument deduction, non-type parameters, template argument rules.'],
      ['Specialization and overloading with templates', 'Full and partial specialization, function matching with templates.'],
      ['Lambdas and callables', 'Captures and their lifetime traps, `mutable`, init-capture, generic lambdas, function objects, `std::function` versus templates.'],
      ['Specialized library facilities', '`tuple`, `bitset`, regular expressions, random numbers.'],
    ],
    core: [
      ['primer', 'ch. 8 The IO Library', [P(310, 324)], 'Streams, files, string streams'],
      ['primer', 'ch. 9 Sequential Containers (9.1 to 9.6)', [P(326, 374)], 'Containers, operations, how `vector` grows, string operations, adaptors'],
      ['primer', 'ch. 10 Generic Algorithms (10.1 to 10.6)', [P(376, 418)], 'Algorithms, lambdas as predicates, iterator categories'],
      ['primer', 'ch. 11 Associative Containers (11.1 to 11.4)', [P(420, 448)], '`map`, `set`, unordered containers'],
      ['primer', 'ch. 16 Templates: 16.1 to 16.3, 16.5 (skip 16.2.5 to 16.2.7 and 16.4 until phase 5)', [P(652, 677), P(678, 689), P(694, 698), P(706, 714)], 'Function and class templates, deduction, overloading, specialization'],
      ['emc', 'Items 31 to 32: lambdas', [[234, 247]], 'Default captures, init-capture and why to avoid default captures'],
      ['primer', 'ch. 17: 17.1 tuple; 17.3 regular expressions; 17.4 random numbers', [P(718, 722), P(728, 744), P(745, 751)], 'The library pieces the lessons also cover'],
    ],
    deepen: [
      ['ppp', 'Templates and concepts: 18.1 to 18.3', [[527, 541]], 'Templates from the idea down, with a first look at concepts'],
      ['ppp', 'Containers and iterators: 19.1 to 19.3, 19.6; 20.1 to 20.2', [[559, 572], [585, 586], [591, 598]], 'How the STL is designed'],
      ['ppp', 'Choosing a container: 20.3 to 20.7.1', [[598, 612]], 'Container overview, iterator categories, timing'],
      ['ppp', 'Algorithms: 21.1, 21.2, 21.5', [[617, 626], [633, 635]], 'Standard algorithms, function objects, sorting and searching'],
    ],
    lessons: ['strings', 'stl', 'lambdas', 'templates'], practice: ['12 (`Stack<T>`)', 25],
    recap: 'Explain: how a lambda is compiled (a closure class with `operator()`), when `vector` invalidates iterators, why `map::operator[]` can insert, what a strict weak ordering is, how a template is instantiated, and why `std::sort` does not work on `std::list`.',
  },
  {
    n: 4, name: 'RAII, exceptions and advanced language tools', sub: 'Exceptions and RAII, namespaces, unions and enums, memory control',
    topics: [
      ['Exceptions and exception safety', 'Throwing, catching by reference, stack unwinding, the three safety guarantees, `noexcept`.'],
      ['RAII and resource management', 'Tying a resource to an object, scope guards, standard wrappers (`lock_guard`, `fstream`).'],
      ['Namespaces and large programs', 'Namespace definition and use, `using`, headers and include guards, linkage.'],
      ['Enums, unions and nested types', '`enum class`, `union` and `variant`, nested and local classes, pointers to members.'],
      ['Controlling memory allocation', 'Overloading `new`/`delete`, placement `new`, custom allocators.'],
    ],
    core: [
      ['primer', '5.6 `try` blocks; 18.1 Exception handling; 18.2 Namespaces', [P(193, 199), P(772, 801)], 'Exceptions end to end, `noexcept`, namespaces'],
      ['primer', '19.1 Controlling memory allocation; 19.3 enumerations; 19.5 nested classes; 19.6 `union`', [P(820, 824), P(832, 834), P(843, 846), P(847, 851)], 'Placement `new`, scoped enums, nested classes, unions'],
      ['ppp', 'RAII, exceptions and resource management: 18.4 to 18.5', [[542, 553]], 'Why RAII replaces `try`/`finally`'],
    ],
    deepen: [
      ['emc', 'Item 14 `noexcept`; Item 16 `const` member functions and threads', [[108, 115], [121, 127]], 'Where `noexcept` really matters and the `mutable` mutex'],
      ['primer', '19.4 Pointers to class members', [P(835, 842)], 'Member function pointers, used under `std::function` and `std::invoke`'],
    ],
    lessons: ['core'], practice: ['none (use the lesson\'s step-throughs and quiz)', 0],
    recap: 'Explain: what stack unwinding does, why a destructor must not throw, the difference between basic and strong guarantee and how copy-and-swap gives the strong one.',
  },
  {
    n: 5, name: 'Modern C++ (C++11 to C++20)', sub: 'Move semantics, smart pointers, forwarding, `constexpr`, vocabulary types, concepts',
    topics: [
      ['Move semantics', 'Value categories, rvalue references, what `std::move` does, writing move operations, copy elision, the move traps, `noexcept` moves.'],
      ['Smart pointers and ownership', '`unique_ptr`, `shared_ptr`, `weak_ptr`, control blocks, cycles, custom deleters, passing ownership.'],
      ['Type deduction and `auto`', 'Template deduction rules, `auto` and `decltype`, structured bindings.'],
      ['Forwarding and variadic templates', 'Forwarding references, reference collapsing, `std::forward`, parameter packs, fold expressions.'],
      ['Compile-time programming', '`constexpr`, `consteval`, type traits, `if constexpr`, SFINAE, concepts and `requires`.'],
      ['Vocabulary types', '`optional`, `variant` and `visit`, `expected`, `span`, `string_view`, `tuple`.'],
      ['Ranges and C++20', 'Views and pipelines, `std::format`, `<=>`, `jthread` (see phase 7).'],
    ],
    core: [
      ['primer', '12.1 smart pointers (shared_ptr, unique_ptr, weak_ptr)', [P(450, 457), P(464, 475)], 'The C++11 smart pointers'],
      ['primer', '13.6 Moving objects', [P(531, 550)], 'Rvalue references, move constructors, move assignment, `noexcept`'],
      ['primer', '16.2.5 to 16.2.7 deduction, `std::move`, forwarding; 16.4 variadic templates', [P(687, 693), P(699, 705)], 'Reference collapsing, perfect forwarding, parameter packs'],
      ['emc', 'Items 1, 2, 5, 7: deduction, `auto`, `()` versus `{}`', [[27, 41], [55, 61], [67, 76]], 'The deduction rules everything else uses'],
      ['emc', 'Item 15 `constexpr`', [[115, 121]], '`constexpr` objects and functions'],
      ['emc', 'Items 18 to 22: `unique_ptr`, `shared_ptr`, `weak_ptr`, `make_*`, Pimpl', [[136, 174]], 'Smart pointers in depth'],
      ['emc', 'Items 23, 24, 25, 28: `move`, `forward`, universal references, reference collapsing', [[176, 195], [215, 221]], 'The core of move semantics and forwarding'],
      ['emc', 'Items 26 to 27, 29, 41, 42: overloading, cheap moves, pass by value, emplacement', [[195, 215], [221, 225], [299, 320]], 'Moves in practice'],
    ],
    deepen: [
      ['mv', '1.2 to 1.4; chapter 2: the core idea and moved-from objects', [[36, 41], [43, 52]], 'The clearest account of what a move is'],
      ['mv', '3.1; 3.3 to 3.4: special member functions, Rule of Five', [[53, 58], [66, 76]], 'Exactly when the compiler generates or suppresses moves'],
      ['mv', '4.1 to 4.2; 4.3.5 to 4.3.6: passing and initializing', [[77, 79], [90, 93]], 'By value and `std::move`'],
      ['mv', '6.1 to 6.2; 7.1; 7.4: moved-from states and `noexcept`', [[107, 115], [125, 134], [140, 141]], 'The state a moved-from object is in; `noexcept` rules'],
      ['mv', '8.1.2 to 8.1.3; 8.4 to 8.5: value categories', [[145, 148], [153, 154]], 'lvalue, prvalue, xvalue and the C++17 changes'],
      ['mv', '9.1 to 9.3: perfect forwarding', [[159, 166]], 'Universal versus rvalue references'],
      ['mv', 'chapters 13 to 15: move-only types, algorithms, library types', [[213, 250]], 'Move semantics in the standard library'],
      ['ppp', 'Concepts: 18.1.2 to 18.1.4', [[530, 534]], 'The only concepts coverage in the five books; the lessons carry the rest'],
    ],
    lessons: ['vocab', 'moves', 'smartptr', 'compiletime'], practice: ['15 (`optional`/`variant`) and 16 (concepts)', 50],
    recap: 'Explain: what `std::move` does at run time (nothing), why `return std::move(local)` hurts, the three value categories, what a forwarding reference is, why `make_shared` needs one allocation, and what a concept replaces.',
    note: 'C++ Primer (2013) stops at C++11, so for C++14, C++17 and C++20 features (vocabulary types, `if constexpr`, concepts, ranges, structured bindings) the lessons and Effective Modern C++ are the sources. Josuttis is a deep dive: read it after Effective Modern C++ if move semantics is the part you want to master.',
  },
  {
    n: 6, name: 'Design patterns and SOLID', sub: 'Common designs in modern C++, with real code',
    topics: [
      ['What patterns are and are not', 'Patterns as names for recurring solutions, and when they are overkill.'],
      ['SOLID', 'The five principles and how they show up in C++ interfaces.'],
      ['Creational', 'Singleton, Factory, Builder.'],
      ['Behavioral', 'Strategy (often just a lambda), Observer, State, Command with undo, Visitor with `variant`.'],
      ['Structural', 'Decorator, Adapter, Pimpl.'],
    ],
    core: [],
    deepen: [
      ['emc', 'Item 22 Pimpl', [[165, 174]], 'The one design pattern Meyers covers in depth'],
    ],
    lessons: ['patterns', 'patterns2'], practice: ['none (use the lessons\' step-throughs and quizzes)', 0],
    recap: 'Explain: when Strategy is just a lambda, why Singleton is a global with a nicer name, how Observer avoids dangling subscribers, and how `variant` plus `visit` replaces a Visitor class hierarchy.',
    note: 'No book in this set covers design patterns, so the two lessons are the only source; Item 22 of Effective Modern C++ covers the Pimpl idiom.',
  },
  {
    n: 7, name: 'Concurrency and the memory model', sub: 'Threads, mutexes, condition variables, futures and pools, atomics',
    topics: [
      ['Threads and data races', 'Launching, joining, passing arguments, shared data, what a data race is.'],
      ['Mutexes and deadlock', '`lock_guard`, `unique_lock`, `scoped_lock`, interface races, deadlock and lock ordering.'],
      ['Condition variables and queues', 'Waiting with a predicate, lost wakeups, a thread-safe queue.'],
      ['Tasks, futures and pools', '`async`, `promise`, `packaged_task`, thread pools, work stealing, `latch`/`barrier`/`jthread`.'],
      ['Atomics and the memory model', '`std::atomic`, compare-and-swap, memory orders, happens-before, lock-free structures.'],
    ],
    core: [
      ['cia', 'Why threads and launching them: 1.1, 1.2.3, 2.1, 2.2', [[25, 30], [32, 33], [40, 50]], 'The model and the basic API'],
      ['cia', 'Sharing data and mutexes: 3.1, 3.2.1 to 3.2.3', [[60, 74]], 'Invariants, race conditions inherent in interfaces'],
      ['cia', 'Deadlock and locking: 3.2.4 to 3.2.8, 3.3.1', [[74, 91]], 'Lock ordering, `unique_lock`, `call_once`'],
      ['cia', 'Waiting for events and results: 4.1, 4.2.1 to 4.2.4', [[96, 113]], 'Condition variables, futures, `promise`'],
      ['cia', 'Thread counts and a pool: 2.4, 9.1.1', [[54, 57], [324, 326]], 'How many threads; the simplest pool'],
      ['cia', 'The memory model and data structures: 5.1, 5.3 overview, 6.1 to 6.2.2', [[148, 151], [165, 170], [197, 206]], 'Memory locations, orderings, a thread-safe stack and queue'],
      ['cia', 'Performance and bugs: 8.2, 11.1 to 11.2.1', [[283, 289], [363, 367]], 'False sharing, oversubscription, kinds of concurrency bug'],
    ],
    deepen: [
      ['emc', 'Items 35 to 40: tasks, launch policies, joining, futures, one-shot events, `atomic` versus `volatile`', [[259, 297]], 'A compact second opinion on the same ground'],
    ],
    lessons: ['threads', 'tasks', 'atomics'], practice: ['13 (`SafeCounter`) and 14 (`BoundedQueue<T>`)', 50],
    recap: 'Explain: what a data race is and why it is undefined behavior, why a mutex per method is not enough, the four conditions for deadlock, why `wait` needs a predicate, what release and acquire guarantee, and what the ABA problem is.',
    note: 'C++ Primer and Programming: Principles and Practice have no chapters on threads. Concurrency in Action is the main book; Effective Modern C++ items 35 to 40 are the short version.',
  },
  {
    n: 8, name: 'Performance, memory layout and binary data', sub: 'Cache, allocation, struct layout, endianness, parsing, queues',
    topics: [
      ['Where latency comes from', 'Tail latency, percentiles, measuring correctly, the cost of allocation, exceptions, system calls.'],
      ['Memory on the hot path', 'Preallocation, object pools, arenas, placement `new`.'],
      ['Cache-friendly data', 'Contiguous versus linked, array of structs versus struct of arrays, false sharing, dense keys instead of maps.'],
      ['Binary data and parsing', 'Bit manipulation, struct padding and alignment, endianness, aliasing and `memcpy`, zero-copy parsing, fixed-point numbers, sequence numbers.'],
      ['Queues and pipelines', 'SPSC ring buffers, bounded queues and drop policies, busy-polling and thread pinning.'],
    ],
    core: [
      ['primer', '17.2 `bitset`; 19.8 bit-fields, `volatile`, `extern "C"`', [P(723, 727), P(854, 863)], 'The only low-level chapters in the five books; the rest is in the lessons'],
    ],
    deepen: [
      ['cia', '8.2 Factors affecting the performance of concurrent code (also in phase 7)', [[283, 289]], 'Cache ping-pong and false sharing'],
    ],
    lessons: ['wire', 'latency'], practice: ['17 (`BucketTable`)', 25],
    recap: 'Explain: why the average hides the tail, how an object pool works, why a struct is bigger than the sum of its members, what endianness is and the portable way to read a big-endian value, and what false sharing is.',
    note: 'None of the five books covers this phase, so the two lessons are the main source. The C++ Primer sections are a small supplement.',
  },
];

export const topicIndex = [
  ['Types, initialization, `auto`', 'types', `Primer 2.1 to 2.5 (${fmt([P(32, 71)])})`],
  ['Expressions and conversions', 'types', `Primer 4.11 (${fmt([P(159, 165)])})`],
  ['Functions and argument passing', 'basics', `Primer ch. 6 (${fmt([P(202, 252)])})`],
  ['Pointers, references, `const`', 'basics', `Primer 2.3 to 2.4 (${fmt([P(50, 66)])}); PPP 15.3 to 15.5 (452 to 463)`],
  ['Strings, vectors, arrays', 'basics', `Primer ch. 3 (${fmt([P(84, 132)])})`],
  ['Vocabulary types (`optional`, `variant`, `span`)', 'vocab', `Primer 17.1 tuple (${fmt([P(718, 722)])}); EMC Item 5 (55 to 61)`],
  ['Classes and invariants', 'oop', `Primer ch. 7 (${fmt([P(254, 306)])}); PPP 8.1 to 8.7 (235 to 258)`],
  ['Copy control, Rule of 3/5/0', 'oop', `Primer 13.1 to 13.5 (${fmt([P(496, 530)])}); Move Semantics 3.3 to 3.4 (66 to 76)`],
  ['Operator overloading, conversions', 'oop', `Primer ch. 14 (${fmt([P(552, 590)])})`],
  ['Inheritance, virtual functions', 'oop', `Primer ch. 15 (${fmt([P(592, 650)])}); PPP 12.3 (380 to 387)`],
  ['Object model, multiple inheritance, RTTI', 'objmodel', `Primer 18.3, 19.2 (${fmt([P(802, 818), P(825, 831)])})`],
  ['RAII and exceptions', 'core', `Primer 18.1 (${fmt([P(772, 784)])}); PPP 18.4 to 18.5 (542 to 553)`],
  ['Move semantics and value categories', 'moves', `Primer 13.6 (${fmt([P(531, 550)])}); EMC Items 23, 25 (176 to 195); Move Semantics ch. 2 (43 to 52)`],
  ['Smart pointers', 'smartptr', `Primer 12.1 (${fmt([P(450, 475)])}); EMC Items 18 to 22 (136 to 174)`],
  ['Lambdas and callables', 'lambdas', `Primer 10.3, 14.8 (${fmt([P(385, 400), P(571, 578)])}); EMC Items 31 to 32 (234 to 247)`],
  ['Strings, regex, time', 'strings', `Primer 9.5, 17.3 (${fmt([P(360, 367), P(728, 744)])})`],
  ['The STL: containers, iterators, algorithms', 'stl', `Primer ch. 9 to 11 (${fmt([P(326, 448)])}); PPP 19 to 21 (559 to 635)`],
  ['Templates', 'templates', `Primer ch. 16 (${fmt([P(652, 714)])}); EMC Item 1 (27 to 36)`],
  ['Forwarding and variadics', 'templates', `Primer 16.2.5 to 16.4 (${fmt([P(687, 705)])}); EMC Item 28 (215 to 221)`],
  ['Type traits, `constexpr`, concepts', 'compiletime', `EMC Item 15 (115 to 121); PPP 18.1.2 to 18.1.4 (530 to 534)`],
  ['Design patterns, SOLID', 'patterns', 'lessons only; EMC Item 22 Pimpl (165 to 174)'],
  ['Threads, mutexes, deadlock', 'threads', 'Concurrency in Action ch. 2 to 4 (40 to 113)'],
  ['Futures, pools, tasks', 'tasks', 'Concurrency in Action 4.2, 9.1.1 (105 to 113; 324 to 326); EMC Items 35 to 39 (259 to 289)'],
  ['Atomics and the memory model', 'atomics', 'Concurrency in Action 5.1, 5.3 (148 to 151; 165 to 170); EMC Item 40 (289 to 297)'],
  ['Binary data, endianness, aliasing', 'wire', `Primer 17.2, 19.8 (${fmt([P(723, 727), P(854, 863)])}); lessons mainly`],
  ['Performance, cache, pools', 'latency', 'Concurrency in Action 8.2 (283 to 289); lessons mainly'],
];
