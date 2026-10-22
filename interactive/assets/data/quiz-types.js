/* Quiz questions for the 'types' topic. Loaded by 16-types-and-casts-quiz.html. */
CT.quizData.types = {
  id: 'types',
  questions: [
    { sec: 'casts', q: 'What does `dynamic_cast<Dog*>(animalPtr)` return when the object is not a Dog?',
      opts: ['The same pointer', 'nullptr', 'It throws std::bad_cast', 'Undefined behavior'], a: 1,
      why: 'The pointer form returns null on failure; the reference form throws `std::bad_cast`. It requires the base class to be polymorphic (have a virtual function).' },

    { sec: 'casts', q: 'Which cast is the most dangerous and rarely correct?',
      opts: ['static_cast', 'dynamic_cast', 'reinterpret_cast', 'They are equally safe'], a: 2,
      why: '`reinterpret_cast` reinterprets raw bits between unrelated types and bypasses the type system. Prefer `static_cast`, and avoid C-style casts, which can silently act as any of them.' },

    { sec: 'deduction', q: 'What does `auto x = {1, 2, 3};` deduce?',
      opts: ['std::vector<int>', 'int[3]', 'std::initializer_list<int>', 'It does not compile'], a: 2,
      why: 'A braced list with `auto =` deduces `std::initializer_list`. It is a famous gotcha: write the type explicitly if you want a vector.' },

    { sec: 'deduction', q: 'What is the problem with `for (auto [key, value] : myMap)` for a `std::map<std::string, BigObject>`?',
      opts: ['It does not compile', 'It copies each pair every iteration; use `const auto&` to avoid it', 'It modifies the map', 'It skips the first element'], a: 1,
      why: '`auto` deduces a value type, so each element is copied. Write `for (const auto& [key, value] : myMap)`.' },

    { sec: 'const', q: 'What is the difference between `const` and `constexpr`?',
      opts: ['None', '`constexpr` guarantees the value can be computed at compile time; `const` only means read-only after initialization', '`const` is for functions, `constexpr` for variables', '`constexpr` values live on the heap'], a: 1,
      why: 'A `const int` may be initialized at runtime. A `constexpr` variable must be a compile-time constant, usable in template arguments and array sizes.' },

    { sec: 'standards', q: 'Which of these was introduced in C++17?',
      opts: ['Move semantics', '`std::optional` and structured bindings', 'Lambdas', 'Concepts'], a: 1,
      why: 'Move semantics, lambdas and smart pointers came in C++11; `optional`, `variant`, `string_view`, structured bindings and `if constexpr` in C++17; concepts and ranges in C++20.' },

    { sec: 'const', q: 'What are the three meanings of `static` in C++?',
      opts: ['Constant, shared, and fast', 'Persistent local variable, internal linkage at file scope, and class-level member', 'Heap allocation, stack allocation, and global', 'Only one: shared across threads'], a: 1,
      why: 'Inside a function it persists across calls; at namespace scope it hides the name in the translation unit; on a class member it is shared by all instances.' },

    { sec: 'init', q: 'What does `int a; std::cout << a;` do inside a function?',
      opts: ['Prints 0', 'Prints some defined garbage value', 'Reading the uninitialized local is undefined behaviour', 'Does not compile'], a: 2,
      why: 'A default-initialized local `int` has an indeterminate value; reading it is undefined behaviour. Initialize with `int a{};` or a value.' },

    { sec: 'init', q: 'How many elements does `std::vector<int> v{3, 7};` contain?',
      opts: ['3 elements, each 7', '2 elements: 3 and 7', '7 elements', 'It does not compile'], a: 1,
      why: 'Braces prefer the `initializer_list` constructor. `std::vector<int> v(3, 7)` with parentheses gives three 7s.' },

    { sec: 'init', q: 'What happens with `int x{3.7};`?',
      opts: ['`x` is 3', '`x` is 4', 'Compile error: narrowing conversion in braces', 'Undefined behaviour at runtime'], a: 2,
      why: 'List-initialization rejects narrowing conversions. `int x = 3.7;` would compile and silently truncate.' },

    { sec: 'deduction', q: 'Given `const int ci = 9;`, what are the types of `auto a = ci;` and `decltype(ci) b = 10;`?',
      opts: ['`int` and `const int`', 'both `const int`', 'both `int`', '`const int` and `int`'], a: 0,
      why: '`auto` drops top-level `const` and references; `decltype` reports the declared type exactly.' },

    { sec: 'conversions', q: 'What is the value of `-1 < 1u`?',
      opts: ['`true`', '`false`', 'Compile error', 'Undefined'], a: 1,
      why: 'The signed -1 is converted to unsigned, becoming a huge number, so the comparison is false. This is why `-Wsign-compare` exists.' },

    { sec: 'conversions', q: 'For `std::uint8_t a = 200, b = 100;`, what is the type and value of `a + b`?',
      opts: ['`uint8_t`, 44', '`int`, 300', '`uint8_t`, runtime error', '`unsigned`, 300'], a: 1,
      why: 'Types smaller than `int` are promoted to `int` before arithmetic, so the sum is 300. Only storing it back into a `uint8_t` wraps it to 44.' },

    { sec: 'conversions', q: 'Why does `int m = Level::Error;` fail when `Level` is an `enum class`?',
      opts: ['Scoped enums have no integer values', 'A scoped enum does not convert implicitly: you need `static_cast<int>`', '`Error` is a reserved word', 'Enums cannot be assigned to `int`'], a: 1,
      why: 'That is a feature of `enum class`: no silent conversion to integers and no names leaking into the enclosing scope.' },

    { sec: 'casts', q: 'What is `static_cast<int>(-3.9)`?',
      opts: ['-4', '-3', '-3.9', '4'], a: 1,
      why: 'Converting a floating-point value to an integer truncates toward zero.' },

    { sec: 'standards', q: 'Which of these needs C++20?',
      opts: ['`std::optional`', 'Structured bindings', 'Concepts', '`std::string_view`'], a: 2,
      why: '`optional`, structured bindings and `string_view` arrived in C++17. Concepts, ranges, `std::span`, coroutines and `operator<=>` are C++20.' }
  ]
};
