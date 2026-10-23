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

    { sec: 's2', q: 'Where should the full definition of a function template normally go?',
      opts: ['In a .cpp file, to keep the header small and compile faster', 'In the header, so each translation unit that instantiates it sees the body', 'In a separate .o file that is linked in at a later stage', 'Anywhere, since the compiler and linker treat all placements alike'], a: 1,
      why: 'The compiler needs the body at the point of instantiation. A body hidden in a .cpp file leads to linker errors (unless you use explicit instantiation there).' },

    { sec: 's2', q: 'What is a non-type template parameter?',
      code: String.raw`
template <typename T, std::size_t N>
struct Buffer { T data[N]; };`,
      opts: ['A parameter that is not allowed to be a class template', 'A compile-time constant value such as N used as a template argument', 'A parameter that cannot be deduced by the compiler from the call', 'A parameter passed by reference to the template instead of by value'], a: 1,
      why: '`N` is a value known at compile time, which is how `std::array<int, 5>` encodes its size in its type.' },

    { sec: 's3', q: 'Which statement about partial specialization is true?',
      opts: ['It is allowed for function templates as well as for class templates', 'It is allowed for class templates, not function templates (overload instead)', 'It is not allowed for templates in standard C++ code', 'It is allowed only when every template parameter is a non-type parameter'], a: 1,
      why: 'Class templates can be partially specialized (for example `Foo<T*>`). Function templates cannot, so you overload them.' },

    { sec: 's4', q: 'In `template <typename T> void f(T&& x);` what is `T&&`?',
      opts: ['An rvalue reference to T, binding to temporaries and not to lvalues', 'A forwarding reference: it binds lvalues and rvalues and remembers which', 'A compile error: references to references are illegal in C++', 'A pointer to a pointer to T, spelled with reference syntax here'], a: 1,
      why: 'When `T` is deduced for that function, `T&&` is a forwarding (universal) reference. It is a real rvalue reference only for something like `void g(Widget&&)` or `std::vector<T>&&`.' },

    { sec: 's4', q: 'If `int x = 1;` and you call `f(x)` for `template <typename T> void f(T&& p);`, what is `T`?',
      opts: ['int', 'int&', 'int&&', 'const int'], a: 1,
      why: 'For an lvalue argument, `T` is deduced as `int&`. Reference collapsing then turns `int& &&` into `int&`, so `p` is an lvalue reference.' },

    { sec: 's4', q: 'What does reference collapsing do with `T&& &&`?',
      opts: ['Collapses to T&', 'Collapses to T&&', 'Is an error', 'Collapses to T'], a: 1,
      why: 'If either side is an lvalue reference the result is an lvalue reference. Only rvalue-reference-to-rvalue-reference stays an rvalue reference.' },

    { sec: 's4', q: 'What is the difference between `std::move(x)` and `std::forward<T>(x)`?',
      opts: ['They are the same: both just cast their argument to T&&', 'move always casts to an rvalue; forward does so only if the argument was one', 'forward makes a copy of its argument before passing it on', 'move works only on standard library containers and on strings'], a: 1,
      why: '`std::forward` preserves the value category of a forwarding reference argument, enabling perfect forwarding. `std::move` unconditionally says "this may be stolen from".' },

    { sec: 's4', q: 'What is the purpose of perfect forwarding?',
      opts: ['To make a call run faster than a normal function call would', 'To pass arguments through a wrapper keeping lvalue/rvalue-ness and const', 'To forward exceptions up through the call stack to the caller', 'To call virtual functions through template code without a vtable'], a: 1,
      why: 'Without it a wrapper would treat every named parameter as an lvalue and force copies (or need many overloads). `std::make_unique` and `emplace_back` rely on it.' },

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

    { sec: 's6', q: 'What is special about `if constexpr`?',
      opts: ['It evaluates its condition at run time, only a little faster than if', 'The condition is evaluated at compile time and the other branch is discarded', 'It can only be used outside of templates, in ordinary functions', 'It compiles and executes both branches in the order written'], a: 1,
      why: 'That is what lets one template body use operations that are valid for some types only, with a different branch chosen for each instantiation.' },

    { sec: 's6', q: 'What is the main advantage of C++20 concepts over `enable_if`?',
      opts: ['They make the generated code run faster than enable_if code', 'They state requirements directly and give clear, early error messages', 'They remove the need for templates altogether in generic code', 'They are evaluated at run time, not at compile time'], a: 1,
      why: '`template <std::integral T>` documents the constraint in the signature and produces "constraint not satisfied" instead of a wall of instantiation errors.' },

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
      why: 'By-value deduction makes arrays decay to pointers. Take `T (&x)[N]` or `T&` to keep the array type.' },

    { sec: 'tools', q: 'What can an alias template do that a `typedef` cannot?',
      opts: ['They are two spellings of the same feature', 'Take template parameters of its own', 'Create a brand new distinct type', 'Be used in header files without a definition'], a: 1,
      why: '`template <typename T> using Vec = std::vector<T>;` is a family of aliases. A `typedef` names one concrete type.' },

    { sec: 'tools', q: 'What is `std::make_index_sequence<3>` used for?',
      opts: ['Creating an array of three integers filled at run time', 'Generating the pack 0, 1, 2 at compile time to expand per index', 'Shuffling three indices into a random order at run time', 'Counting how many worker threads are currently running'], a: 1,
      why: 'It produces `std::index_sequence<0, 1, 2>`; a function template deduces the pack `I...` and expands `get<I>(t)...`.' },

    { sec: 'tools', q: 'Which of these is a variable template?',
      opts: ['`template <typename T> constexpr T zero = T{};`', '`template <typename T> using Zero = T;` an alias template', '`template <typename T> T zero();` a function template', '`constexpr int zero = 0;` an ordinary variable'], a: 0,
      why: 'A variable template gives one variable per `T` (`zero<int>`, `zero<double>`). The standard\'s `std::is_integral_v<T>` is defined this way.' },

    { sec: 'tools', q: 'In `template <template <typename...> class C, typename T> C<T> make(T a, T b);`, what do you pass for `C`?',
      opts: ['A concrete type such as std::vector<int>, with its argument', 'A template such as std::vector, without arguments', 'A function pointer to a factory function that builds C', 'An integer that selects which container kind to build'], a: 1,
      why: 'A template template parameter takes a template: `make<std::vector>(3, 4)` builds a `std::vector<int>`.' }
  ]
};
