/* Quiz questions for the 'forwarding' topic. Loaded by 37-forwarding-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.forwarding = {
  id: 'forwarding',
  questions: [
    { sec: 'forward', q: 'What is the difference between `std::move(x)` and `std::forward<T>(x)`?',
      opts: ['They are the same: both just cast their argument to T&&', 'move always casts to an rvalue; forward does so only if the argument was one', 'forward makes a copy of its argument before passing it on', 'move works only on standard library containers and on strings'], a: 1,
      why: '`std::forward` preserves the value category of a forwarding reference argument, enabling perfect forwarding. `std::move` unconditionally says "this may be stolen from".' },

    { sec: 'forward', q: 'What is the purpose of perfect forwarding?',
      opts: ['To make a call run faster than a normal function call would', 'To pass arguments through a wrapper keeping lvalue/rvalue-ness and const', 'To forward exceptions up through the call stack to the caller', 'To call virtual functions through template code without a vtable'], a: 1,
      why: 'Without it a wrapper would treat every named parameter as an lvalue and force copies (or need many overloads). `std::make_unique` and `emplace_back` rely on it.' },

    { sec: 'problem', q: 'Inside `template<class T> void wrap(T&& a)`, what category is the expression `a`?',
      opts: ['An lvalue', 'Always an rvalue', 'Whatever the caller passed', 'A prvalue'], a: 0,
      why: 'Inside the function a is a named object. std::forward restores the caller\'s category.' },

    { sec: 'problem', q: 'What happens if a wrapper calls `target(std::move(a))` on a forwarding reference `a`?',
      opts: ['It moves from lvalues the caller still wanted', 'It copies lvalues', 'It forwards correctly', 'It does not compile'], a: 0,
      why: 'std::move always casts to an rvalue, so the caller\'s lvalue gets stolen from.' },

    { sec: 'forward', q: 'What does `std::forward<T>(a)` return when the caller passed an lvalue?',
      opts: ['An lvalue reference', 'An rvalue reference', 'A copy', 'A const pointer'], a: 0,
      why: 'T is deduced as X&, and forward<X&> returns X&.' },

    { sec: 'forward', q: 'How many times should a parameter be forwarded?',
      opts: ['At most once', 'Twice, to be safe', 'As often as needed', 'Never in a variadic template'], a: 0,
      why: 'After a forward the object may have been moved from.' },

    { sec: 'collapse', q: 'What does `T& &&` collapse to?',
      opts: ['`T&`', '`T&&`', '`T`', 'It is an error'], a: 0,
      why: 'If either side is an lvalue reference, the result is an lvalue reference.' },

    { sec: 'collapse', q: 'A function `template<class T> void f(T&& x)` is called with an lvalue string. What is `T`?',
      opts: ['`std::string&`', '`std::string`', '`std::string&&`', '`const std::string`'], a: 0,
      why: 'An lvalue argument deduces T as an lvalue reference, and T&& collapses to string&.' },

    { sec: 'limits', q: 'Why does forwarding `{1, 2}` to a template parameter `T&&` fail?',
      opts: ['A braced list has no type', 'Braced lists are always const', 'T&& cannot bind to ints', 'The list is a prvalue'], a: 0,
      why: 'Deduction does not look inside braced lists.' },

    { sec: 'practice', q: 'What does `decltype(auto)` as a wrapper\'s return type achieve?',
      opts: ['It returns exactly what the callee returns, including references', 'It always returns by value', 'It always returns a pointer', 'It forces a move'], a: 0,
      why: 'decltype(auto) keeps the value category and reference-ness of the returned expression.' }
  ]
};
