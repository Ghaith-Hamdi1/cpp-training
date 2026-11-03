/* Quiz questions for the 'moves' topic. Loaded by 13-move-semantics-quiz.html. */
CT.quizData.moves = {
  id: 'moves',
  questions: [
    { sec: 'values', q: 'What is the value category of the expression `std::move(x)`?',
      opts: ['lvalue', 'prvalue', 'xvalue', 'It is not an expression'], a: 2,
      why: 'An xvalue is an object marked as movable, and `std::move` produces one. A prvalue is an unnamed temporary like `5` or `a + b`. "Rvalue" means a prvalue or an xvalue.' },

    { sec: 'values', q: 'Which expression is a prvalue?',
      opts: ['`x` (a named variable)', '`std::move(x)`', '`x + 1`', '`v[0]`'], a: 2,
      why: '`x + 1` is an unnamed temporary: a prvalue. `x` and `v[0]` are lvalues; `std::move(x)` is an xvalue.' },

    { sec: 'values', q: 'Which overload is called?',
      code: String.raw`
void h(const std::string&);
void h(std::string&&);
void g(std::string&& s) { h(s); }`,
      opts: ['h(const std::string&), because s is an lvalue inside g', 'h(std::string&&), because s has an rvalue reference type', 'Neither: the call is ambiguous between the two', 'The code does not compile'], a: 0,
      why: 'A name is always an lvalue, whatever its declared type. To pass it on as an rvalue you need `std::move(s)`.' },

    { sec: 'values', q: 'What can bind to an rvalue reference parameter `T&&`?',
      opts: ['Any lvalue of type T', 'Only rvalues: temporaries and std::move(x)', 'Only const objects of type T', 'Anything, including lvalues, just like const T&'], a: 1,
      why: 'An rvalue reference binds to rvalues, which is how overload resolution sends temporaries to move operations. An lvalue needs `std::move` first.' },

    { sec: 'names', q: 'Which of these is an lvalue?',
      opts: ['`v[0]`', '`5`', '`a + b` for two ints', '`std::string("x")`'], a: 0,
      why: 'An element of a vector has a name path and an address. The others are temporaries.' },

    { sec: 'names', q: 'Why does `int* p = &5;` not compile?',
      opts: ['5 is a temporary and has no address', '5 is a constant that lives in read-only memory', 'Pointers cannot point to ints', '& can only be applied to variables of type int'], a: 0,
      why: 'An rvalue has no stored location you can name. Only lvalues have addresses.' },

    { sec: 'binding', q: 'A function has overloads `f(const std::string&)` and `f(std::string&&)`. Which is called for `f(std::string("b"))`?',
      opts: ['The `&&` overload', 'The `const&` overload, because it accepts everything', 'Neither: the call is ambiguous', 'Both, one after the other'], a: 0,
      why: 'An rvalue prefers the rvalue-reference overload when both are viable.' },

    { sec: 'binding', q: 'Which reference type can bind to both lvalues and rvalues?',
      opts: ['`const T&`', '`T&`', '`T&&` on a non-template parameter', '`volatile T&`'], a: 0,
      why: 'A const lvalue reference accepts temporaries. T& rejects them and a plain T&& rejects lvalues.' },

    { sec: 'named', q: 'Inside `void g(std::string&& s)`, what is the value category of the expression `s`?',
      opts: ['An lvalue', 'An rvalue, because of its type', 'An xvalue', 'A prvalue'], a: 0,
      why: 'A name is always an lvalue, whatever its type. Write std::move(s) to treat it as an rvalue again.' },

    { sec: 'named', q: 'What does `f(s)` call inside `void g(std::string&& s)` when f has `const&` and `&&` overloads?',
      opts: ['The `const&` overload', 'The `&&` overload', 'Neither', 'It does not compile'], a: 0,
      why: 's is an lvalue inside g, so the lvalue overload is chosen.' },

    { sec: 'values', q: 'What is the type of `decltype((std::move(x)))` for an int x?',
      opts: ['`int&&`', '`int&`', '`int`', '`const int&`'], a: 0,
      why: 'std::move gives an xvalue, which decltype with double parentheses reports as T&&.' },

    { sec: 'signature', q: 'What does a parameter of type `const T&&` usually indicate?',
      opts: ['Almost nothing useful: a const object cannot be moved from', 'A forwarding reference', 'A function that steals the argument', 'A parameter that must be an lvalue'], a: 0,
      why: 'You cannot steal from a const object, so a const rvalue reference is rarely right.' }
  ]
};
