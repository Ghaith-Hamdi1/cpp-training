/* Quiz questions for the 'templates' topic. Loaded by 05-templates-quiz.html. */
CT.quizData.templates = {
  id: 'templates',
  questions: [
    { sec: 's1', q: 'What does the compiler do with a function template when you call it with a new type?',
      opts: ['Nothing: templates are resolved at runtime', 'It instantiates a separate concrete function for those template arguments and compiles it', 'It creates a virtual function table', 'It converts every argument to a common base type'], a: 1,
      why: 'A template is only a blueprint. Each distinct set of template arguments causes a new function (or class) to be generated at compile time.' },

    { sec: 's8', q: 'Why does this fail to compile?',
      code: String.raw`
template <typename T>
T maxOf(T a, T b) { return a < b ? b : a; }

maxOf(3, 2.5);`,
      opts: ['maxOf needs three parameters', 'Deduction conflict: T would be int from one argument and double from the other', 'double cannot be compared with int', 'Templates cannot take literals'], a: 1,
      why: 'Both parameters share one `T`, but the arguments deduce `int` and `double`. Fix with `maxOf<double>(3, 2.5)` or by using two template parameters.' },

    { sec: 's8', q: 'What is the problem with `maxOf("apple", "pear")` for the same template?',
      opts: ['It does not compile', 'It compiles but compares the pointers (addresses), not the text', 'It returns an empty string', 'It throws'], a: 1,
      why: 'The string literals decay to `const char*`, so `a < b` compares addresses. Use `std::string` or `std::string_view`.' },

    { sec: 's2', q: 'Where should the full definition of a function template normally go?',
      opts: ['In a .cpp file only', 'In the header, so every translation unit that instantiates it can see the body', 'In a separate .o file', 'Anywhere, it makes no difference'], a: 1,
      why: 'The compiler needs the body at the point of instantiation. A body hidden in a .cpp file leads to linker errors (unless you use explicit instantiation there).' },

    { sec: 's2', q: 'What is a non-type template parameter?',
      code: String.raw`
template <typename T, std::size_t N>
struct Buffer { T data[N]; };`,
      opts: ['A parameter that is not a class', 'A compile-time constant value such as N, used as a template argument', 'A parameter that cannot be deduced', 'A reference parameter'], a: 1,
      why: '`N` is a value known at compile time, which is how `std::array<int, 5>` encodes its size in its type.' },

    { sec: 's3', q: 'Which statement about partial specialization is true?',
      opts: ['It is allowed for function templates', 'It is allowed for class templates but not for function templates (use overloading instead)', 'It is not allowed at all', 'It is only allowed for non-type parameters'], a: 1,
      why: 'Class templates can be partially specialized (for example `Foo<T*>`). Function templates cannot, so you overload them.' },

    { sec: 's4', q: 'In `template <typename T> void f(T&& x);` what is `T&&`?',
      opts: ['Always an rvalue reference', 'A forwarding reference: binds to lvalues and rvalues and remembers which', 'A compile error', 'A pointer to a pointer'], a: 1,
      why: 'When `T` is deduced for that function, `T&&` is a forwarding (universal) reference. It is a real rvalue reference only for something like `void g(Widget&&)` or `std::vector<T>&&`.' },

    { sec: 's4', q: 'If `int x = 1;` and you call `f(x)` for `template <typename T> void f(T&& p);`, what is `T`?',
      opts: ['int', 'int&', 'int&&', 'const int'], a: 1,
      why: 'For an lvalue argument, `T` is deduced as `int&`. Reference collapsing then turns `int& &&` into `int&`, so `p` is an lvalue reference.' },

    { sec: 's4', q: 'What does reference collapsing do with `T&& &&`?',
      opts: ['Collapses to T&', 'Collapses to T&&', 'Is an error', 'Collapses to T'], a: 1,
      why: 'If either side is an lvalue reference the result is an lvalue reference. Only rvalue-reference-to-rvalue-reference stays an rvalue reference.' },

    { sec: 's4', q: 'What is the difference between `std::move(x)` and `std::forward<T>(x)`?',
      opts: ['No difference', '`move` always casts to an rvalue; `forward` casts to an rvalue only if the original argument was an rvalue', '`forward` always copies', '`move` only works on containers'], a: 1,
      why: '`std::forward` preserves the value category of a forwarding reference argument, enabling perfect forwarding. `std::move` unconditionally says "this may be stolen from".' },

    { sec: 's4', q: 'What is the purpose of perfect forwarding?',
      opts: ['To make a function run faster than a normal call', 'To pass arguments through a wrapper while preserving lvalue/rvalue-ness and const, so the callee can copy or move correctly', 'To forward exceptions', 'To call virtual functions through templates'], a: 1,
      why: 'Without it a wrapper would treat every named parameter as an lvalue and force copies (or need many overloads). `std::make_unique` and `emplace_back` rely on it.' },

    { sec: 's5', q: 'What does this compute?',
      code: String.raw`
template <typename... Args>
auto f(Args... args) { return (args + ...); }

f(1, 2, 3, 4);`,
      opts: ['A tuple (1,2,3,4)', '10, using a C++17 fold expression', 'A compile error', '4, the pack size'], a: 1,
      why: '`(args + ...)` is a unary right fold: `1 + (2 + (3 + 4))`. The size of the pack is `sizeof...(args)`.' },

    { sec: 's5', q: 'What does `sizeof...(Args)` return?',
      opts: ['The total byte size of all arguments', 'The number of elements in the parameter pack', 'The size of the first argument', 'It is not valid C++'], a: 1,
      why: 'It counts the elements of the pack, at compile time. It is not the same as `sizeof`.' },

    { sec: 's6', q: 'What is special about `if constexpr`?',
      opts: ['It runs the condition at runtime but faster', 'The condition is evaluated at compile time and the untaken branch is discarded (not even compiled for that instantiation)', 'It can only be used outside templates', 'It always executes both branches'], a: 1,
      why: 'That is what lets one template body use operations that are valid for some types only, with a different branch chosen for each instantiation.' },

    { sec: 's6', q: 'What is the main advantage of C++20 concepts over `enable_if`?',
      opts: ['They make code run faster', 'They state requirements directly and give clear, early error messages', 'They remove the need for templates', 'They work at runtime'], a: 1,
      why: '`template <std::integral T>` documents the constraint in the signature and produces "constraint not satisfied" instead of a wall of instantiation errors.' },

    { sec: 's8', q: 'Why does a dependent type name like `T::iterator` need the `typename` keyword inside a template?',
      opts: ['It is optional style', 'The compiler cannot know whether `T::iterator` is a type or a value until T is known, so you must say it is a type', 'typename makes it faster', 'To allow multiple inheritance'], a: 1,
      why: 'Without `typename`, `T::iterator` is assumed to be a value. Write `typename T::iterator it = c.begin();`.' },

    { sec: 's8', q: 'What is a common drawback of heavy template use?',
      opts: ['Runtime slowdown from virtual calls', 'Longer compile times, larger binaries (code bloat) and hard-to-read error messages', 'Memory leaks', 'Templates cannot be inlined'], a: 1,
      why: 'Each instantiation is separate code, and errors surface inside instantiations. The upside is zero runtime overhead and aggressive inlining.' },

    { sec: 's1', q: 'Which is the best description of templates compared with virtual functions?',
      opts: ['Templates are runtime polymorphism', 'Templates give compile-time (static) polymorphism with no runtime indirection; virtual functions give runtime polymorphism via a vtable', 'They are the same', 'Virtual functions are faster because they are inlined'], a: 1,
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
      opts: ['`T` is deduced as `int` from one argument and `double` from the other, and no conversion is applied during deduction', 'Templates cannot take doubles', 'The return type cannot be deduced', 'It compiles and returns 3'], a: 0,
      why: 'Each argument deduces its own `T` and they conflict. Specify `maxOf<double>(3, 2.5)` or use two template parameters.' },

    { sec: 'deduction', q: 'What does `std::vector v{1, 2, 3};` deduce (C++17)?',
      opts: ['It does not compile without the template argument', '`std::vector<int>`, by class template argument deduction', '`std::vector<std::initializer_list<int>>`', '`std::vector<long>`'], a: 1,
      why: 'CTAD deduces the class\'s template arguments from the constructor call.' },

    { sec: 'deduction', q: 'An `int arr[3]` is passed to `template <typename T> void f(T x);`. What is `T`?',
      opts: ['`int[3]`', '`int*`', '`int&`', '`int(&)[3]`'], a: 1,
      why: 'By-value deduction makes arrays decay to pointers. Take `T (&x)[N]` or `T&` to keep the array type.' },

    { sec: 'tools', q: 'What can an alias template do that a `typedef` cannot?',
      opts: ['Nothing', 'Take template parameters of its own', 'Create a new type', 'Be used in headers'], a: 1,
      why: '`template <typename T> using Vec = std::vector<T>;` is a family of aliases. A `typedef` names one concrete type.' },

    { sec: 'tools', q: 'What is `std::make_index_sequence<3>` used for?',
      opts: ['Creating an array of three integers at run time', 'Generating the compile-time pack 0, 1, 2, so an expression can be expanded once per index (for example over a tuple)', 'Shuffling three indices', 'Counting threads'], a: 1,
      why: 'It produces `std::index_sequence<0, 1, 2>`; a function template deduces the pack `I...` and expands `get<I>(t)...`.' },

    { sec: 'tools', q: 'Which of these is a variable template?',
      opts: ['`template <typename T> constexpr T zero = T{};`', '`template <typename T> using Zero = T;`', '`template <typename T> T zero();`', '`constexpr int zero = 0;`'], a: 0,
      why: 'A variable template gives one variable per `T` (`zero<int>`, `zero<double>`). The standard\'s `std::is_integral_v<T>` is defined this way.' },

    { sec: 'tools', q: 'In `template <template <typename...> class C, typename T> C<T> make(T a, T b);`, what do you pass for `C`?',
      opts: ['A concrete type such as `std::vector<int>`', 'A template such as `std::vector` (without arguments)', 'A function pointer', 'An integer'], a: 1,
      why: 'A template template parameter takes a template: `make<std::vector>(3, 4)` builds a `std::vector<int>`.' }
  ]
};
