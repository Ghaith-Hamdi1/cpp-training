/* Quiz questions for the 'patterns2' topic. Loaded by 20-more-patterns-quiz.html. */
CT.quizData.patterns2 = {
  id: 'patterns2',
  questions: [
    { sec: 'command', q: 'What does the Command pattern make possible?',
      opts: ['Faster function calls', 'Storing, queuing, logging, replaying and undoing actions, because each action is an object', 'Removing virtual functions', 'Sharing one instance'], a: 1,
      why: 'A request becomes an object with `execute` (and `undo`), so it can be treated as data.' },

    { sec: 'command', q: 'How is undo usually implemented with commands?',
      opts: ['By copying the whole document every time', 'The invoker keeps executed commands on a stack; undo pops the last one and calls its `undo`', 'With `goto`', 'It cannot be done'], a: 1,
      why: 'Each command knows how to reverse itself, so the history of commands is the undo stack.' },

    { sec: 'decorator', q: 'What is the defining property of the Decorator pattern?',
      opts: ['It changes the interface of an object', 'It wraps an object with the same interface and adds behaviour; wrappers can be stacked', 'It creates objects without naming their class', 'It guarantees one instance'], a: 1,
      why: 'Each decorator holds an object of the same interface and calls it (compiled: Bracket around Upper around Plain turned "feed" into "[FEED]").' },

    { sec: 'decorator', q: 'Why prefer decorators to a subclass for every combination of features?',
      opts: ['They are faster', 'Combinations are chosen and stacked at run time instead of multiplying classes', 'They avoid virtual functions', 'They are required by the standard'], a: 1,
      why: 'With inheritance, n independent features can need 2^n classes. Decorators compose.' },

    { sec: 'adapter', q: 'What does an Adapter do?',
      opts: ['Adds behaviour while keeping the interface', 'Makes an existing interface fit the interface the client expects', 'Hides a subsystem behind a simpler interface', 'Creates objects step by step'], a: 1,
      why: 'It implements the expected interface and translates calls to the adaptee. A decorator keeps the interface; a facade simplifies a subsystem.' },

    { sec: 'builder', q: 'When is a Builder appropriate?',
      opts: ['For any class', 'When an object has many optional or related parts and must be validated before use, so a long constructor would be unreadable', 'To guarantee one instance', 'To avoid templates'], a: 1,
      why: 'Named steps read clearly and `build()` can reject an incomplete object.' },

    { sec: 'builder', q: 'Why does each builder setter return `*this` (a reference to the builder)?',
      opts: ['To make it thread-safe', 'So calls can be chained: `b.url("x").timeout(5).retries(3)`', 'To avoid copies of the product', 'It is required by the compiler'], a: 1,
      why: 'That is the fluent interface style.' },

    { sec: 'visitor', q: 'What is the advantage of `std::variant` with `std::visit` over virtual functions for a closed set of message types?',
      opts: ['It is shorter to write', 'Adding an operation is one new visitor, values are stored inline without allocation or virtual calls, and a missing alternative is a compile error', 'It supports an unlimited set of types', 'It needs no header'], a: 1,
      why: 'When the set of types is closed and operations keep growing, the variant fits better. With an open set of types, virtual functions fit better.' },

    { sec: 'visitor', q: 'You add a new alternative to a `std::variant` used with `std::visit`. What happens to a visitor that does not handle it?',
      opts: ['It silently ignores it', 'It fails to compile', 'It throws at run time', 'It calls the first overload'], a: 1,
      why: '`std::visit` requires the visitor to be callable with every alternative, so the compiler lists the ones you forgot.' },

    { sec: 'state-machine', q: 'In the session state machine, why does `LoggedOn` hold `nextSeq` instead of a global variable?',
      opts: ['It is faster', 'The data lives in the state that needs it, so it cannot be misused when disconnected or stopped', 'Globals are not allowed', 'It saves memory'], a: 1,
      why: 'Each state carries only its own data, so invalid combinations are unrepresentable.' },

    { sec: 'state-machine', q: 'What does a `variant` of state structs plus `std::visit` give a state machine over an enum plus shared fields?',
      opts: ['It is always faster', 'Each state holds only its own data, and the compiler checks that every state is handled', 'It allows unlimited states at run time', 'It removes the need for events'], a: 1,
      why: 'With an enum and shared fields, a field such as the sequence number exists (and can be misused) in every state. With a variant, each state struct carries only what it needs, and a visitor that misses a state does not compile.' }
  ]
};
