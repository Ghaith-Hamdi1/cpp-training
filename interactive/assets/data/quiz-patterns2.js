/* Quiz questions for the 'patterns2' topic. Loaded by 20-more-patterns-quiz.html. */
CT.quizData.patterns2 = {
  id: 'patterns2',
  questions: [
    { sec: 'command', q: 'What does the Command pattern make possible?',
      opts: ['Faster function calls through direct dispatch to the target', 'Storing, queuing, replaying and undoing actions as objects', 'Removing virtual functions from a design that has them', 'Sharing a single instance across the whole program, safely'], a: 1,
      why: 'A request becomes an object with `execute` (and `undo`), so it can be treated as data.' },

    { sec: 'command', q: 'How is undo usually implemented with commands?',
      opts: ['By copying the whole document before each change that is made', 'The invoker keeps commands on a stack; undo pops one and calls undo', 'With goto statements that jump back to an earlier program state', 'It cannot be done without storing the states in a database'], a: 1,
      why: 'Each command knows how to reverse itself, so the history of commands is the undo stack.' },

    { sec: 'decorator', q: 'What is the defining property of the Decorator pattern?',
      opts: ['It changes the interface of the object that it wraps', 'It wraps an object with the same interface and adds behaviour', 'It creates objects without naming the concrete class', 'It guarantees that exactly one instance of a class exists'], a: 1,
      why: 'Each decorator holds an object of the same interface and calls it (compiled: Bracket around Upper around Plain turned "feed" into "[FEED]").' },

    { sec: 'decorator', q: 'Why prefer decorators to a subclass for every combination of features?',
      opts: ['They are faster than inheritance when the program is running', 'Combinations are chosen at run time, not multiplied as subclasses', 'They avoid the use of virtual functions entirely in the design', 'They are required by the C++ standard for stream classes'], a: 1,
      why: 'With inheritance, n independent features can need 2^n classes. Decorators compose.' },

    { sec: 'adapter', q: 'What does an Adapter do?',
      opts: ['Adds behaviour to an object while keeping its interface', 'Makes an existing interface fit the one the client expects', 'Hides a whole subsystem behind a simpler interface', 'Creates complex objects step by step with named setters'], a: 1,
      why: 'It implements the expected interface and translates calls to the adaptee. A decorator keeps the interface; a facade simplifies a subsystem.' },

    { sec: 'builder', q: 'When is a Builder appropriate?',
      opts: ['For a class that happens to have a constructor', 'When an object has many optional parts and needs validation', 'To guarantee that one instance of a class exists', 'To avoid using templates anywhere in the design'], a: 1,
      why: 'Named steps read clearly and `build()` can reject an incomplete object.' },

    { sec: 'builder', q: 'Why does each builder setter return `*this` (a reference to the builder)?',
      opts: ['To make the builder safe to use from several threads', 'So calls can be chained: b.url(x).timeout(5).retries(3)', 'To avoid copying the product object while it is built', 'The compiler requires setters to return *this'], a: 1,
      why: 'That is the fluent interface style.' },

    { sec: 'visitor', q: 'What is the advantage of `std::variant` with `std::visit` over virtual functions for a closed set of message types?',
      opts: ['It is shorter to write than an equivalent class hierarchy', 'New operations are one visitor; storage is inline; a missed case fails to build', 'It supports an unlimited, open set of types from many libraries', 'It needs no header and no extra include anywhere in the program'], a: 1,
      why: 'When the set of types is closed and operations keep growing, the variant fits better. With an open set of types, virtual functions fit better.' },

    { sec: 'visitor', q: 'You add a new alternative to a `std::variant` used with `std::visit`. What happens to a visitor that does not handle it?',
      opts: ['It silently ignores it', 'It fails to compile', 'It throws at run time', 'It calls the first overload'], a: 1,
      why: '`std::visit` requires the visitor to be callable with every alternative, so the compiler lists the ones you forgot.' },

    { sec: 'state-machine', q: 'In the session state machine, why does `LoggedOn` hold `nextSeq` instead of a global variable?',
      opts: ['It is faster than reading a global variable would be at run time', 'The data lives in the state that needs it, so other states cannot misuse it', 'Globals are not allowed in C++ state machines', 'It saves memory in the states of the machine'], a: 1,
      why: 'Each state carries only its own data, so invalid combinations are unrepresentable.' },

    { sec: 'state-machine', q: 'What does a `variant` of state structs plus `std::visit` give a state machine over an enum plus shared fields?',
      opts: ['It is faster than an enum with a switch statement', 'Each state holds only its own data, and every state must be handled', 'It allows an unlimited number of states to be added at run time', 'It removes the need for events in the state machine design'], a: 1,
      why: 'With an enum and shared fields, a field such as the sequence number exists (and can be misused) in every state. With a variant, each state struct carries only what it needs, and a visitor that misses a state does not compile.' }
  ]
};
