/* Quiz questions for the 'lambdas' topic. Loaded by 15-lambdas-quiz.html. */
CT.quizData.lambdas = {
  id: 'lambdas',
  questions: [
    { sec: 'captures', q: 'What does this print?',
      code: String.raw`
int x = 1;
auto byVal = [x]  { return x; };
auto byRef = [&x] { return x; };
x = 2;
std::cout << byVal() << byRef();`,
      opts: ['11', '12', '21', '22'], a: 1,
      why: 'The by-value capture is a snapshot taken when the lambda was created (1). The by-reference capture reads the live variable (2).' },

    { sec: 'advanced', q: 'How do you move a `std::unique_ptr` into a lambda (C++14)?',
      opts: ['`[p]`: capture by value', '`[p = std::move(p)]`: an init-capture', '`[&p]`: capture by reference', 'It is not possible: lambdas cannot hold move-only objects'], a: 1,
      why: 'A unique_ptr cannot be copied, so `[p]` does not compile. An init-capture creates the lambda\'s own member initialised with `std::move(p)`. A lambda that owns a unique_ptr is itself move-only.' },

    { sec: 'anatomy', q: 'What does the compiler generate for a lambda expression?',
      opts: ['A function pointer', 'An unnamed class with a call operator and a member for each capture', 'A `std::function` object', 'A macro'], a: 1,
      why: 'Every lambda has its own closure type: captures become members and the body becomes `operator()`. That is why calls can be inlined.' },

    { sec: 'anatomy', q: 'Which lambda converts to a plain function pointer?',
      opts: ['`[](int a) { return a * 2; }`', '`[factor](int a) { return a * factor; }`', '`[&](int a) { return a * k; }`', 'None: lambdas never convert'], a: 0,
      why: 'Only a lambda with no captures has a conversion to a function pointer, because it needs no state to call.' },

    { sec: 'captures', q: 'What is printed?',
      code: String.raw`
int n = 5;
auto f = [n]() mutable { return ++n; };
std::cout << f() << f() << n;`,
      opts: ['675', '677', '666', '565'], a: 0,
      why: '`f` has its own copy of `n`, so `++n` returns 6 then 7. The outer `n` is never touched and stays 5.' },

    { sec: 'captures', q: 'Which lambda is safe to return from a function that has a local `int x`?',
      opts: ['`[&x] { return x; }`', '`[x] { return x; }`', '`[&] { return x; }`', 'All of them'], a: 1,
      why: 'Capturing by value copies `x` into the lambda. The reference captures would dangle once the function returns.' },

    { sec: 'captures', q: 'In a member function, what does the capture `[=]` capture (and why is relying on it deprecated in C++20)?',
      opts: ['A copy of the whole object', 'The `this` pointer (not a copy of the object), so it dangles if the object dies', 'Nothing', 'A reference to a copy of the object'], a: 1,
      why: '`[=]` implicitly captures `this` by pointer. C++20 deprecates that: write `[=, this]` to be explicit, or `[*this]` to copy the object.' },

    { sec: 'advanced', q: 'What does `mutable` allow on a lambda?',
      opts: ['Modifying variables captured by reference', 'Modifying the lambda\'s own by-value copies of captured variables', 'Capturing non-copyable types', 'Calling the lambda from several threads'], a: 1,
      why: 'By-value captures are `const` inside the call operator unless the lambda is `mutable`. The changes affect the lambda\'s copy, not the original.' },

    { sec: 'advanced', q: 'What do three successive calls of `[n = 0]() mutable { return ++n; }` return (the same lambda object)?',
      opts: ['0 0 0', '1 2 3', '1 1 1', 'It does not compile'], a: 1,
      why: 'The init-capture creates a member `n` initialized to 0 once; `mutable` lets each call increment it, so the state persists between calls.' },

    { sec: 'advanced', q: 'What makes `[](const auto& a, const auto& b) { return a < b; }` a generic lambda?',
      opts: ['The `const` qualifiers', 'The `auto` parameters turn `operator()` into a template', 'The empty capture list', 'Nothing: it is invalid'], a: 1,
      why: 'A C++14 generic lambda has a templated call operator, so it works for any pair of types that support `<`.' },

    { sec: 'callables', q: 'Why is `std::sort` with a lambda comparator usually faster than with a `std::function` comparator?',
      opts: ['`std::function` is not allowed in sort', 'The lambda\'s exact type is known at compile time, so the call can be inlined; `std::function` needs an indirect call', 'Lambdas run on the GPU', 'There is no difference'], a: 1,
      why: 'A template parameter keeps the closure type, so the comparison is inlined into the sort loop. Type erasure costs an indirect call per comparison.' },

    { sec: 'callables', q: 'When do you genuinely need `std::function` rather than a template parameter?',
      opts: ['Whenever you pass a lambda', 'To store callables of different types with the same signature in one container or member', 'To call a function faster', 'To capture by reference'], a: 1,
      why: 'A member or container needs one concrete type. `std::function` erases the different closure types behind a single signature.' },

    { sec: 'callables', q: 'When may constructing a `std::function` allocate on the heap?',
      opts: ['Never', 'When the stored callable is too large for its small internal buffer', 'Only for function pointers', 'Always'], a: 1,
      why: 'Implementations keep small callables inline and heap-allocate bigger ones. The threshold is implementation-defined (compiled with libstdc++: a 64-byte capture allocated).' },

    { sec: 'before', q: 'Why can a plain function pointer not carry a "limit" value for a comparison?',
      opts: ['Function pointers cannot be passed to algorithms', 'A function pointer is only an address: the function has no state beyond its arguments and globals', 'Because functions cannot take int parameters', 'Because the limit would have to be const'], a: 1,
      why: 'A function pointer holds just the address of code. To bring in state you need a global variable, an extra argument, or a function object (a functor or a lambda) that stores it in a member.' },

    { sec: 'before', q: 'What is a functor?',
      opts: ['A function that returns a function', 'A class with an `operator()`, so its objects can be called like functions and can hold state', 'Another name for a function pointer', 'A macro that expands to a lambda'], a: 1,
      why: 'A functor is a function object: an instance of a class with `operator()`. A lambda is a functor the compiler writes for you, with the captured variables as members.' }
  ]
};
