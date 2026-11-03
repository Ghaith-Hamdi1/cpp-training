/* Quiz questions for the 'types' topic. Loaded by 16-types-and-casts-quiz.html. */
CT.quizData.types = {
  id: 'types',
  questions: [
    { sec: 'deduction', q: 'What does `auto x = {1, 2, 3};` deduce?',
      opts: ['std::vector<int>, because braces build a vector', 'int[3], a built-in array of three ints', 'std::initializer_list<int>, not a vector', 'A compile error, since auto cannot take a braced list'], a: 2,
      why: 'A braced list with `auto =` deduces `std::initializer_list`. It is a famous gotcha: write the type explicitly if you want a vector.' },

    { sec: 'deduction', q: 'What is the problem with `for (auto [key, value] : myMap)` for a `std::map<std::string, BigObject>`?',
      opts: ['It does not compile, because structured bindings need a const map', 'It copies each pair every iteration; use const auto& instead', 'It modifies the map\'s keys while iterating over them', 'It skips the first element of the map'], a: 1,
      why: '`auto` deduces a value type, so each element is copied. Write `for (const auto& [key, value] : myMap)`.' },

    { sec: 'const', q: 'What is the difference between `const` and `constexpr`?',
      opts: ['They are the same keyword, spelled differently in C++11 and later', 'constexpr can be evaluated at compile time; const is only read-only', 'const is for functions only, constexpr is for variables only', 'constexpr values always live on the heap, so they are slower to read'], a: 1,
      why: 'A `const int` may be initialized at runtime. A `constexpr` variable must be a compile-time constant, usable in template arguments and array sizes.' },

    { sec: 'standards', q: 'Which of these was introduced in C++17?',
      opts: ['Move semantics and rvalue references', 'std::optional and structured bindings', 'Lambda expressions and generic auto parameters', 'Concepts, ranges and coroutines together'], a: 1,
      why: 'Move semantics, lambdas and smart pointers came in C++11; `optional`, `variant`, `string_view`, structured bindings and `if constexpr` in C++17; concepts and ranges in C++20.' },

    { sec: 'const', q: 'What are the three meanings of `static` in C++?',
      opts: ['Constant, shared and fast, depending on where the keyword is written', 'A persistent local, internal linkage at file scope, a class-level member', 'Heap allocation, stack allocation and global storage, depending on the context', 'A synonym for volatile, a synonym for const, and a synonym for global'], a: 1,
      why: 'Inside a function it persists across calls; at namespace scope it hides the name in the translation unit; on a class member it is shared by all instances.' },

    { sec: 'init', q: 'What does `int a; std::cout << a;` do inside a function?',
      opts: ['Prints 0, since locals start zeroed', 'Prints some leftover value, but the program is still valid', 'Undefined behavior: reading an uninitialized local', 'Does not compile, because a has no initializer'], a: 2,
      why: 'A default-initialized local `int` has an indeterminate value; reading it is undefined behaviour. Initialize with `int a{};` or a value.' },

    { sec: 'init', q: 'How many elements does `std::vector<int> v{3, 7};` contain?',
      opts: ['3 elements, each 7', '2 elements: 3 and 7', '7 elements', 'It does not compile'], a: 1,
      why: 'Braces prefer the `initializer_list` constructor. `std::vector<int> v(3, 7)` with parentheses gives three 7s.' },

    { sec: 'init', q: 'What happens with `int x{3.7};`?',
      opts: ['x is 3, truncated just as a C-style cast would do it', 'x is 4, because the value is rounded to the nearest int', 'Compile error: narrowing conversion inside braces', 'Undefined behavior at run time, because 3.7 does not fit'], a: 2,
      why: 'List-initialization rejects narrowing conversions. `int x = 3.7;` would compile and silently truncate.' },

    { sec: 'deduction', q: 'Given `const int ci = 9;`, what are the types of `auto a = ci;` and `decltype(ci) b = 10;`?',
      opts: ['`int` and `const int`', 'both `const int`', 'both `int`', '`const int` and `int`'], a: 0,
      why: '`auto` drops top-level `const` and references; `decltype` reports the declared type exactly.' },

    { sec: 'standards', q: 'Which of these needs C++20?',
      opts: ['`std::optional`', 'Structured bindings', 'Concepts', '`std::string_view`'], a: 2,
      why: '`optional`, structured bindings and `string_view` arrived in C++17. Concepts, ranges, `std::span`, coroutines and `operator<=>` are C++20.' },

    { sec: 'init', q: 'Which declaration leaves a local variable with an undefined value?',
      opts: ['int a{};', 'int a = 0;', 'int a;', 'int a{0};'], a: 2,
      why: 'A local variable of a built-in type with no initializer is not set to zero: its value is indeterminate, and reading it is undefined behavior. The other three give it a value.' },

    { sec: 'deduction', q: 'Given `const int& r = x;`, what is the type of `auto a = r;`?',
      opts: ['const int&', 'const int', 'int&', 'int'], a: 3,
      why: '`auto` drops top-level const and references, so `a` is a plain `int` holding a copy. Write `const auto&` to keep a reference.' },

    { sec: 'const', q: 'Which line is a compile-time constant that can be used as an array size?',
      opts: ['const int n = std::rand();', 'int n = 4;', 'constexpr int n = 4;', 'static int n = std::rand();'], a: 2,
      why: '`constexpr` requires a value the compiler can compute. A `const` initialized at run time, or a plain variable, cannot size an array.' }
  ]
};
