/* Quiz questions for the 'casts' topic. Loaded by 25-casts-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.casts = {
  id: 'casts',
  questions: [
    { sec: 'dynamic', q: 'What does `dynamic_cast<Dog*>(animalPtr)` return when the object is not a Dog?',
      opts: ['The same pointer', 'nullptr', 'It throws std::bad_cast', 'Undefined behavior'], a: 1,
      why: 'The pointer form returns null on failure; the reference form throws `std::bad_cast`. It requires the base class to be polymorphic (have a virtual function).' },

    { sec: 'constcast', q: 'Which cast is the most dangerous and rarely correct?',
      opts: ['static_cast', 'dynamic_cast', 'reinterpret_cast', 'They are equally safe'], a: 2,
      why: '`reinterpret_cast` reinterprets raw bits between unrelated types and bypasses the type system. Prefer `static_cast`, and avoid C-style casts, which can silently act as any of them.' },

    { sec: 'implicit', q: 'What is the value of `-1 < 1u`?',
      opts: ['`true`', '`false`', 'Compile error', 'Undefined'], a: 1,
      why: 'The signed -1 is converted to unsigned, becoming a huge number, so the comparison is false. This is why `-Wsign-compare` exists.' },

    { sec: 'implicit', q: 'For `std::uint8_t a = 200, b = 100;`, what is the type and value of `a + b`?',
      opts: ['`uint8_t`, 44', '`int`, 300', '`uint8_t`, runtime error', '`unsigned`, 300'], a: 1,
      why: 'Types smaller than `int` are promoted to `int` before arithmetic, so the sum is 300. Only storing it back into a `uint8_t` wraps it to 44.' },

    { sec: 'static', q: 'What is `static_cast<int>(-3.9)`?',
      opts: ['-4', '-3', '-3.9', '4'], a: 1,
      why: 'Converting a floating-point value to an integer truncates toward zero.' },

    { sec: 'implicit', q: 'What does `7 / 2` give when both operands are `int`, and how do you get 3.5?',
      opts: ['3, and `7 / 2.0` gives 3.5', '3.5, because C++ promotes the result', '4, because it rounds', 'A compile error without a cast'], a: 0,
      why: 'Integer division drops the fraction. Making one operand a floating-point type, for example `static_cast<double>(7) / 2` or `7 / 2.0`, converts the other operand and gives 3.5.' },

    { sec: 'narrowing', q: 'Which of these is a compile error?',
      opts: ['int a = 3.7;', 'int b{3.7};', 'double c = 3;', 'unsigned char d{200};'], a: 1,
      why: 'Braces reject narrowing: a double to an int inside braces is an error. The `=` form compiles and truncates, and the last line is a constant that fits.' },

    { sec: 'narrowing', q: 'Why can `unsigned char c{300};` not compile?',
      opts: ['char cannot be initialized with braces', '300 does not fit in an unsigned char, which is a narrowing conversion', '300 is an odd number', 'Braces only work with int'], a: 1,
      why: 'A constant that does not fit the target type is a narrowing conversion, and list-initialization forbids it.' },

    { sec: 'cstyle', q: 'What does the C-style cast `(T)x` do?',
      opts: ['It always behaves like static_cast', 'It tries static_cast, then static_cast with const_cast, then reinterpret_cast, and uses the first that compiles', 'It behaves like dynamic_cast when it can', 'It checks the types at run time'], a: 1,
      why: 'That fallback chain is the danger: a small mistake can silently turn into a const removal or a reinterpretation of raw bytes. A C-style cast never becomes a dynamic_cast.' },

    { sec: 'static', q: 'A `Base*` points to an object that is not a `Derived`. What does `static_cast<Derived*>(b)` do?',
      opts: ['Returns nullptr', 'Throws bad_cast', 'Gives a pointer and the behavior is undefined when you use it', 'Does not compile'], a: 2,
      why: 'A static downcast is unchecked: it just changes the pointer type. It is your promise that the object really is a Derived.' },

    { sec: 'dynamic', q: 'What does `dynamic_cast<Derived&>(base)` do when `base` is not a Derived?',
      opts: ['Returns a null reference', 'Throws std::bad_cast', 'Ignores the cast', 'Terminates the program immediately'], a: 1,
      why: 'A reference cannot be null, so a failed reference cast throws `std::bad_cast`. The pointer form returns `nullptr` instead.' },

    { sec: 'dynamic', q: 'What does `dynamic_cast` require of the base class?',
      opts: ['A virtual function', 'A copy constructor', 'No data members', 'A template parameter'], a: 0,
      why: 'Run-time type information lives with the vtable, so the base must be polymorphic: at least one virtual function.' },

    { sec: 'constcast', q: 'What is the problem with writing through a pointer produced by `const_cast` from a `const int` variable?',
      opts: ['Nothing: const_cast makes the object writable', 'It is undefined behavior: the object itself is const', 'It copies the object first', 'It only works for pointers to classes'], a: 1,
      why: '`const_cast` changes the type seen by the compiler, not the object. Modifying an object that was defined `const` is undefined behavior.' },

    { sec: 'constcast', q: 'Which is the safe way to reinterpret the bits of a `float` as a `uint32_t`?',
      opts: ['reinterpret_cast on the pointer, then read it', 'std::memcpy or std::bit_cast', 'A C-style cast of the value', 'static_cast<std::uint32_t>(f)'], a: 1,
      why: '`static_cast` converts the number (1.0f becomes 1). Reading through a reinterpret_cast pointer breaks the aliasing rules. memcpy and bit_cast copy the bytes.' },

    { sec: 'choose', q: 'A function takes `char*` but only reads, and you hold a `const char*`. Which cast fits?',
      opts: ['reinterpret_cast', 'dynamic_cast', 'const_cast', 'static_cast'], a: 2,
      why: 'Removing `const` for an API that does not write is the legitimate use of `const_cast`. Prefer fixing the API\'s signature if you own it.' }
  ]
};
