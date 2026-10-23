/* Quiz questions for the 'compiletime' topic. Loaded by 09-compile-time-quiz.html. */
CT.quizData.compiletime = {
  id: 'compiletime',
  questions: [
    { sec: 's1', q: 'What is a type trait?',
      opts: ['A run-time property that is stored in each object of the type', 'A template in <type_traits> that queries or transforms a type at compile time', 'A keyword that marks a class as final, so it cannot be a base class', 'A debugging flag that records the names of all types at run time'], a: 1,
      why: 'Traits like `std::is_integral<T>` and `std::remove_reference<T>` are evaluated entirely by the compiler.' },

    { sec: 's1', q: 'What is the C++17 shorthand for `std::is_integral<T>::value`?',
      opts: ['`std::is_integral<T>()`', '`std::is_integral_t<T>`', '`std::is_integral_v<T>`', '`std::integral<T>`'], a: 2,
      why: '`_v` is the variable template for `::value`. `_t` is the alias for `::type` on transformation traits like `remove_reference_t`.' },

    { sec: 's1', q: 'What does `std::is_same_v<int, const int>` evaluate to?',
      opts: ['true', 'false', 'A compile error', 'It depends on the compiler'], a: 1,
      why: 'Top-level `const` is part of the type, so `int` and `const int` are different types.' },

    { sec: 's1', q: 'What does `std::is_integral_v<const int>` evaluate to?',
      opts: ['true', 'false', 'A compile error', 'Only true in C++20'], a: 0,
      why: '`is_integral` ignores cv-qualifiers, so `const int` is still an integral type.' },

    { sec: 's1', q: 'What does `std::is_integral_v<int&>` evaluate to?',
      opts: ['true', 'false', 'A compile error', 'true, because a reference to int behaves like int'], a: 1,
      why: 'A reference type is a different kind of type from the integral type it refers to. Use `std::remove_reference_t` (or `remove_cvref_t`) first.' },

    { sec: 's1', q: 'What is the difference between `static_assert` and `assert`?',
      opts: ['They are the same check, apart from the spelling', 'static_assert is checked at compile time; assert runs at run time unless NDEBUG', 'assert is checked at compile time, while static_assert runs at run time', 'static_assert works inside header files, assert in sources'], a: 1,
      why: '`static_assert` needs a constant expression and fails the build; `assert` checks while the program runs.' },

    { sec: 's2', q: 'What does SFINAE stand for?',
      opts: ['Safe Function Inlining And Naming Extension', 'Substitution Failure Is Not An Error', 'Static Function Instantiation And Name Elaboration', 'Selective Failure In Namespace Evaluation'], a: 1,
      why: 'If substituting template arguments into a candidate produces an invalid type, that candidate is quietly dropped from overload resolution.' },

    { sec: 's2', q: 'In this code, which overload does `print(2.5)` call?',
      code: String.raw`
template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
void print(T) { /* (1) */ }

template <typename T, std::enable_if_t<!std::is_integral_v<T>, bool> = true>
void print(T) { /* (2) */ }`,
      opts: ['(1)', '(2)', 'Ambiguous: compile error', 'Neither'], a: 1,
      why: 'For `double` the condition of (1) is false, so `enable_if_t` has no `::type` and that overload is discarded by SFINAE. Only (2) remains.' },

    { sec: 's2', q: 'Why is `if constexpr` often better than `enable_if` for choosing code by type?',
      opts: ['It runs faster than enable_if at run time, since it skips overloads', 'One readable function body, and the discarded branch is not instantiated', 'It works in C++98 compilers as well as in newer ones', 'It allows run-time conditions inside templates, unlike enable_if'], a: 1,
      why: 'You write one function with a compile-time branch instead of several overloads, and code in the false branch need not compile for that type.' },

    { sec: 's2', q: 'What goes wrong with an ordinary `if (std::is_integral_v<T>)` inside a template?',
      opts: ['It is a syntax error inside a template body', 'Both branches must compile for every T, even the one that never runs', 'It is evaluated at run time, so it is slower than if constexpr', 'It behaves exactly like if constexpr in a template'], a: 1,
      why: 'A plain `if` is run-time, so both branches are always compiled. Code that is invalid for some `T` breaks the build unless you use `if constexpr`.' },

    { sec: 's3', q: 'Which statement about a `constexpr` function is correct?',
      opts: ['It is evaluated at compile time, whatever its arguments', 'It may run at compile time for constant arguments, and also at run time', 'It can be called from main and from other constexpr functions', 'It cannot take parameters, since it must be a constant'], a: 1,
      why: '`constexpr` allows compile-time evaluation; it does not force it. Use a `constexpr` variable or `consteval` to guarantee it.' },

    { sec: 's3', q: 'What does `consteval` (C++20) add?',
      opts: ['A faster version of constexpr that skips some checks', 'Every call must be evaluated at compile time, or it is an error', 'The function runs at run time and not in constants', 'It makes a variable mutable inside constant expressions'], a: 1,
      why: 'A `consteval` function is an immediate function. A call with a non-constant argument is ill-formed.' },

    { sec: 's3', q: 'What does `constinit` guarantee?',
      opts: ['The variable is const and can never be modified', 'The variable is initialised at compile time but can change later', 'The variable lives in read-only memory and cannot be changed', 'The variable is thread-local, with one copy for each thread'], a: 1,
      why: '`constinit` fixes the static-initialisation-order problem by requiring constant initialisation, without making the variable immutable.' },

    { sec: 's4', q: 'In the classic template-metaprogramming factorial, what stops the recursion?',
      code: String.raw`
template <int N> struct Fact { static constexpr int value = Fact<N-1>::value * N; };
// ???`,
      opts: ['A static_assert inside the struct that stops at a limit', 'A full specialisation template <> struct Fact<0> with value = 1', 'A virtual function that returns early when N reaches 0', 'The compiler stops at 256 levels and gives a valid result'], a: 1,
      why: 'The specialisation for 0 provides the base case. Without it the compiler keeps instantiating `Fact<-1>`, `Fact<-2>`... until it hits its recursion limit.' },

    { sec: 's4', q: 'Which is the modern replacement for computing a value with recursive template structs?',
      opts: ['A preprocessor macro with arguments', 'A constexpr function', 'A virtual function in a base class', 'A global lookup table built at start-up'], a: 1,
      why: 'Ordinary-looking `constexpr` functions are shorter, more readable and can also be used at run time.' },

    { sec: 'concepts', q: 'What is a C++20 concept?',
      opts: ['A run-time check that throws an exception when it fails', 'A named compile-time condition on template arguments', 'A kind of virtual base class used for interfaces', 'A macro that expands to an enable_if expression'], a: 1,
      why: 'A concept is a compile-time boolean over types, such as `std::integral<T>`, that constrains a template. A call with a type that does not satisfy it is rejected at the call site with a readable message.' },

    { sec: 'concepts', q: 'What happens here?',
      code: String.raw`
template <std::integral T>
T twice(T v) { return v * 2; }
twice(2.5);`,
      opts: ['It returns 5.0, since the double is simply doubled', 'It returns 4, the double truncated to an integer', 'A compile error: std::integral<double> is not satisfied', 'A run-time exception thrown from inside the function'], a: 2,
      why: 'A `double` is not integral, so the constrained template is not a candidate and the call fails to compile with a message that names the unmet constraint. Without the concept the function would happily return 5.0.' },

    { sec: 'concepts', q: 'In `requires(T a, T b) { { a + b } -> std::convertible_to<T>; }`, what does the part in braces express?',
      opts: ['That a + b must compile and give a result convertible to T', 'That a and b must be equal for the expression to compile', 'That + must be commutative for all pairs of values', 'That T must be an integer type, not a class type'], a: 0,
      why: 'A requires-expression lists operations that must be valid; `{ expr } -> Concept` also constrains the type of the result. It checks syntax and types only, not mathematical properties such as commutativity.' }
  ]
};
