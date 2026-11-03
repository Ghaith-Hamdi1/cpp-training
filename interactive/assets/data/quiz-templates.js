/* Quiz questions for the 'templates' topic. Loaded by 05-templates-quiz.html. */
CT.quizData.templates = {
  id: 'templates',
  questions: [
    { sec: 's1', q: 'What does the compiler do with a function template when you call it with a new type?',
      opts: ['Templates are resolved at run time by a hidden lookup', 'It instantiates a concrete function for those arguments and compiles it', 'It builds a virtual function table for the call to dispatch through', 'It converts the arguments to a common base type before calling'], a: 1,
      why: 'A template is only a blueprint. Each distinct set of template arguments causes a new function (or class) to be generated at compile time.' },

    { sec: 's8', q: 'Why does this fail to compile?',
      code: String.raw`
template <typename T>
T maxOf(T a, T b) { return a < b ? b : a; }

maxOf(3, 2.5);`,
      opts: ['maxOf needs a third parameter to decide which type should be compared', 'Deduction conflict: T is int from one argument and double from the other', 'A double cannot be compared with an int by the language rules', 'Templates cannot be called with literal values like 3 and 2.5'], a: 1,
      why: 'Both parameters share one `T`, but the arguments deduce `int` and `double`. Fix with `maxOf<double>(3, 2.5)` or by using two template parameters.' },

    { sec: 's8', q: 'What is the problem with `maxOf("apple", "pear")` for the same template?',
      opts: ['It does not compile: arrays cannot be arguments', 'It compiles but compares the pointers, not the text', 'It returns an empty string without comparing', 'It throws an exception for string literals'], a: 1,
      why: 'The string literals decay to `const char*`, so `a < b` compares addresses. Use `std::string` or `std::string_view`.' },

    { sec: 's4', q: 'In `template <typename T> void f(T&& x);` what is `T&&`?',
      opts: ['An rvalue reference to T, binding to temporaries and not to lvalues', 'A forwarding reference: it binds lvalues and rvalues and remembers which', 'A compile error: references to references are illegal in C++', 'A pointer to a pointer to T, spelled with reference syntax here'], a: 1,
      why: 'When `T` is deduced for that function, `T&&` is a forwarding (universal) reference. It is a real rvalue reference only for something like `void g(Widget&&)` or `std::vector<T>&&`.' },

    { sec: 's4', q: 'If `int x = 1;` and you call `f(x)` for `template <typename T> void f(T&& p);`, what is `T`?',
      opts: ['int', 'int&', 'int&&', 'const int'], a: 1,
      why: 'For an lvalue argument, `T` is deduced as `int&`. Reference collapsing then turns `int& &&` into `int&`, so `p` is an lvalue reference.' },

    { sec: 's4', q: 'What does reference collapsing do with `T&& &&`?',
      opts: ['Collapses to T&', 'Collapses to T&&', 'Is an error', 'Collapses to T'], a: 1,
      why: 'If either side is an lvalue reference the result is an lvalue reference. Only rvalue-reference-to-rvalue-reference stays an rvalue reference.' },

    { sec: 's5', q: 'What does this compute?',
      code: String.raw`
template <typename... Args>
auto f(Args... args) { return (args + ...); }

f(1, 2, 3, 4);`,
      opts: ['A tuple holding the values (1, 2, 3, 4)', '10, via a C++17 fold expression', 'A compile error because the pack is empty', '4, the number of elements in the pack'], a: 1,
      why: '`(args + ...)` is a unary right fold: `1 + (2 + (3 + 4))`. The size of the pack is `sizeof...(args)`.' },

    { sec: 's5', q: 'What does `sizeof...(Args)` return?',
      opts: ['The total size in bytes of all arguments', 'The number of elements in the parameter pack', 'The size in bytes of the first argument', 'It is not valid C++ outside of variadic function templates'], a: 1,
      why: 'It counts the elements of the pack, at compile time. It is not the same as `sizeof`.' },

    { sec: 's8', q: 'Why does a dependent type name like `T::iterator` need the `typename` keyword inside a template?',
      opts: ['It is a style convention and can be omitted', 'Until T is known, the compiler cannot tell a type from a value', 'typename speeds up name lookup inside templates', 'It lets the nested type take part in multiple inheritance'], a: 1,
      why: 'Without `typename`, `T::iterator` is assumed to be a value. Write `typename T::iterator it = c.begin();`.' },

    { sec: 's8', q: 'What is a common drawback of heavy template use?',
      opts: ['Run-time slowdown caused by virtual calls in the instantiations', 'Longer compile times, bigger binaries and hard-to-read errors', 'Memory leaks in the instantiations of a class template', 'Templates cannot be inlined by modern optimizing compilers'], a: 1,
      why: 'Each instantiation is separate code, and errors surface inside instantiations. The upside is zero runtime overhead and aggressive inlining.' },

    { sec: 's1', q: 'Which is the best description of templates compared with virtual functions?',
      opts: ['Templates are run-time polymorphism, exactly like virtual functions are', 'Templates resolve at compile time with no indirection; virtual calls at run time', 'They are the same mechanism with different syntax and different names', 'Virtual functions are faster, because compilers inline them'], a: 1,
      why: 'With templates the concrete type is resolved when compiling (so calls can be inlined), but the set of types is fixed then. Virtual dispatch decides at runtime at the cost of an indirection.' },

    { sec: 's4', q: 'Which of these declarations is a forwarding (universal) reference?',
      opts: ['`template <class T> void f(T&& x);`', '`template <class T> void f(const T&& x);`', '`template <class T> void f(std::vector<T>&& v);`', '`void f(Widget&& w);`'], a: 0,
      why: 'It must be exactly `T&&` (or `auto&&`) with the type deduced for that function. A `const` qualifier, a wrapper such as `vector<T>`, a fixed type like `Widget`, or a `T` fixed by the enclosing class all make it an ordinary rvalue reference.' },

    { sec: 'deduction', q: 'For `template <typename T> void f(T x);` called as `f(ci)` with `const int ci`, what is `T`?',
      opts: ['`const int`', '`int`', '`const int&`', '`int&`'], a: 1,
      why: 'A by-value parameter is a copy, so top-level `const` and references are dropped from the deduced type.' },

    { sec: 'deduction', q: 'For `template <typename T> void f(T& x);` called as `f(ci)` with `const int ci`, what is `T`?',
      opts: ['`int`', '`const int`', '`int&`', 'It fails to compile'], a: 1,
      why: 'A reference parameter must keep the argument\'s `const`, so `T` is `const int` and the parameter is `const int&`.' },

    { sec: 'deduction', q: 'Why does `maxOf(3, 2.5)` fail for `template <typename T> T maxOf(T a, T b)`?',
      opts: ['T is deduced as both int and double, and deduction does not convert', 'Templates cannot be instantiated with double arguments', 'The return type cannot be deduced from the two arguments', 'It compiles and silently returns 3 as an int, truncating'], a: 0,
      why: 'Each argument deduces its own `T` and they conflict. Specify `maxOf<double>(3, 2.5)` or use two template parameters.' },

    { sec: 'deduction', q: 'What does `std::vector v{1, 2, 3};` deduce (C++17)?',
      opts: ['It does not compile without the template argument spelled out', '`std::vector<int>`, by class template argument deduction', 'std::vector<std::initializer_list<int>>, holding one element', 'std::vector<long>, because the literals are widened'], a: 1,
      why: 'CTAD deduces the class\'s template arguments from the constructor call.' },

    { sec: 'deduction', q: 'An `int arr[3]` is passed to `template <typename T> void f(T x);`. What is `T`?',
      opts: ['`int[3]`', '`int*`', '`int&`', '`int(&)[3]`'], a: 1,
      why: 'By-value deduction makes arrays decay to pointers. Take `T (&x)[N]` or `T&` to keep the array type.' }
  ]
};
