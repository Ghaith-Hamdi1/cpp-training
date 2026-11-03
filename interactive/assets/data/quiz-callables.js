/* Quiz questions for the 'callables' topic. Loaded by 23-callables-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.callables = {
  id: 'callables',
  questions: [
    { sec: 'choose', q: 'Why is `std::sort` with a lambda comparator usually faster than with a `std::function` comparator?',
      opts: ['std::function cannot be used as a sort comparator at all', 'The lambda\'s type is known at compile time, so the call inlines', 'Lambdas are compiled to run on the graphics card instead', 'Both comparators run at exactly the same speed'], a: 1,
      why: 'A template parameter keeps the closure type, so the comparison is inlined into the sort loop. Type erasure costs an indirect call per comparison.' },

    { sec: 'choose', q: 'When do you genuinely need `std::function` rather than a template parameter?',
      opts: ['Whenever you pass a lambda to a function template', 'To store callables of different types with one signature together', 'To make a call faster than the equivalent template would be', 'To capture variables by reference instead of by value'], a: 1,
      why: 'A member or container needs one concrete type. `std::function` erases the different closure types behind a single signature.' },

    { sec: 'stdfunction', q: 'When may constructing a `std::function` allocate on the heap?',
      opts: ['It stores the callable inline in the object, up to any size', 'When the callable is too big for its small internal buffer', 'Only when it wraps a plain function pointer or a lambda', 'Each std::function allocates on the heap when constructed'], a: 1,
      why: 'Implementations keep small callables inline and heap-allocate bigger ones. The threshold is implementation-defined (compiled with libstdc++: a 64-byte capture allocated).' },

    { sec: 'fnptr', q: 'Why can a plain function pointer not carry a "limit" value for a comparison?',
      opts: ['Function pointers cannot be passed to standard algorithms such as sort', 'It is only an address: the function has no state besides arguments and globals', 'Functions cannot take int parameters, only pointers to them', 'The limit would have to be declared as a const variable first'], a: 1,
      why: 'A function pointer holds just the address of code. To bring in state you need a global variable, an extra argument, or a function object (a functor or a lambda) that stores it in a member.' },

    { sec: 'functor', q: 'What is a functor?',
      opts: ['A function that returns another function when it is called later', 'A class with an operator(), so objects are callable and can hold state', 'Another name for a function pointer in older C++ code bases', 'A macro that expands to a lambda expression at compile time'], a: 1,
      why: 'A functor is a function object: an instance of a class with `operator()`. A lambda is a functor the compiler writes for you, with the captured variables as members.' },

    { sec: 'fnptr', q: 'What does `int (*f)(int);` declare?',
      opts: ['A function that returns a pointer to an int value', 'A pointer to a function: int in, int out', 'A pointer to an int that is named f here', 'An array of functions that take an int'], a: 1,
      why: 'The parentheses around `*f` make f a pointer; the rest is the function type it points to: takes an `int`, returns an `int`.' },

    { sec: 'fnptr', q: 'Which statement about a plain function pointer is true?',
      opts: ['It can hold state in its own member variables', 'It is only an address, so it carries no state', 'It is always inlined by the compiler here', 'It can only point to member functions of classes'], a: 1,
      why: 'A function pointer holds only the address of code. State must come from the arguments or from globals, which is why functors and lambdas exist.' },

    { sec: 'functor', q: 'What makes `std::sort(v.begin(), v.end(), std::greater<>{})` cheap to run?',
      opts: ['The comparator is copied once and then cached', 'The comparator\'s type is known, so the call inlines', 'std::greater is implemented as a function pointer', 'The sort skips the comparator entirely for ints'], a: 1,
      why: '`std::greater<>` is a functor with its own type. The template knows exactly which `operator()` it calls, so the compiler can inline it.' },

    { sec: 'stdfunction', q: 'Which callable can NOT be stored in a `std::function<int(int)>`?',
      opts: ['A function `int twice(int)`', 'A lambda `[](int x) { return x + 1; }`', 'A functor with `int operator()(int) const`', 'A function `int add(int, int)`'], a: 3,
      why: 'The stored callable must be callable with the signature of the `std::function`. `add` needs two arguments, so it does not fit `int(int)`.' },

    { sec: 'stdfunction', q: 'What does `std::invoke(&Account::balance, acct)` do?',
      opts: ['Reads the data member balance of acct', 'Calls the member function acct.balance()', 'Creates a new Account named balance', 'Takes the address of acct'], a: 1,
      why: '`std::invoke` calls any callable. With a pointer to a member function and an object, it calls that member function on the object.' },

    { sec: 'choose', q: 'You need a vector that holds a mix of function pointers, functors and lambdas that all take an `int` and return an `int`. What type does the vector hold?',
      opts: ['std::vector<auto> with C++20 deduction', 'std::vector<std::function<int(int)>>', 'std::vector<int(*)(int)> with a typedef', 'std::vector<decltype(some_lambda)>'], a: 1,
      why: 'Different callable types need one common type. `std::function<int(int)>` erases the difference. A function pointer cannot hold a lambda with captures.' },

    { sec: 'callable', q: 'Which of these can all be called with the syntax `f(x)`?',
      opts: ['Only plain functions that have a name', 'Pointers, functors, lambdas and std::function', 'Only lambdas and functors, nothing else', 'Everything that has a name in the program'], a: 1,
      why: 'Anything with a call operator, or that converts to one, can be called with `f(x)`: functions through pointers, functors, lambdas and `std::function`.' },

    { sec: 'fnptr', q: 'Given `int (*f)(int) = twice;`, which expressions call `twice` with 21?',
      opts: ['f(21) only', '(*f)(21) only', 'Both f(21) and (*f)(21)', 'Neither: you must write twice(21)'], a: 2,
      why: 'A function pointer can be called directly or after dereferencing; both run the same function.' }
  ]
};
