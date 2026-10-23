/* Quiz questions for the 'compiletime' topic. Loaded by 09-compile-time-quiz.html. */
CT.quizData.compiletime = {
  id: 'compiletime',
  questions: [
    { sec: 's1', q: 'What is a type trait?',
      opts: ['A run-time property stored in each object', 'A template in `<type_traits>` that answers a question about a type, or transforms it, at compile time', 'A keyword that marks a class as final', 'A debugging flag'], a: 1,
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
      opts: ['None', '`static_assert` is checked at compile time and has no run-time cost; `assert` is a run-time check removed by NDEBUG', '`assert` is checked at compile time', '`static_assert` only works in headers'], a: 1,
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
      opts: ['It runs faster at run time', 'One function body, readable, and the discarded branch is not instantiated', 'It works in C++98', 'It allows run-time conditions in templates'], a: 1,
      why: 'You write one function with a compile-time branch instead of several overloads, and code in the false branch need not compile for that type.' },

    { sec: 's2', q: 'What goes wrong with an ordinary `if (std::is_integral_v<T>)` inside a template?',
      opts: ['It is a syntax error', 'Both branches must compile for every T, even the one that can never run', 'It is evaluated only at run time and so is slower', 'Nothing, it is identical to if constexpr'], a: 1,
      why: 'A plain `if` is run-time, so both branches are always compiled. Code that is invalid for some `T` breaks the build unless you use `if constexpr`.' },

    { sec: 's3', q: 'Which statement about a `constexpr` function is correct?',
      opts: ['It is always evaluated at compile time', 'It may be evaluated at compile time if its arguments are constants, and can also be called at run time', 'It can only be called from `main`', 'It cannot take parameters'], a: 1,
      why: '`constexpr` allows compile-time evaluation; it does not force it. Use a `constexpr` variable or `consteval` to guarantee it.' },

    { sec: 's3', q: 'What does `consteval` (C++20) add?',
      opts: ['A faster `constexpr`', 'Every call must be evaluated at compile time, otherwise it is an error', 'The function runs only at run time', 'It makes a variable mutable'], a: 1,
      why: 'A `consteval` function is an immediate function. A call with a non-constant argument is ill-formed.' },

    { sec: 's3', q: 'What does `constinit` guarantee?',
      opts: ['The variable is `const`', 'The variable is initialised at compile time but can still be modified later', 'The variable lives in read-only memory', 'The variable is thread-local'], a: 1,
      why: '`constinit` fixes the static-initialisation-order problem by requiring constant initialisation, without making the variable immutable.' },

    { sec: 's4', q: 'In the classic template-metaprogramming factorial, what stops the recursion?',
      code: String.raw`
template <int N> struct Fact { static constexpr int value = Fact<N-1>::value * N; };
// ???`,
      opts: ['A static_assert', 'A full specialisation `template <> struct Fact<0> { static constexpr int value = 1; };`', 'A virtual function', 'The compiler stops at 256 automatically with a valid result'], a: 1,
      why: 'The specialisation for 0 provides the base case. Without it the compiler keeps instantiating `Fact<-1>`, `Fact<-2>`... until it hits its recursion limit.' },

    { sec: 's4', q: 'Which is the modern replacement for computing a value with recursive template structs?',
      opts: ['A macro', 'A `constexpr` function', 'A virtual function', 'A global variable'], a: 1,
      why: 'Ordinary-looking `constexpr` functions are shorter, more readable and can also be used at run time.' },

    { sec: 'concepts', q: 'What is a C++20 concept?',
      opts: ['A runtime check that throws an exception', 'A named compile-time condition on template arguments', 'A kind of virtual base class', 'A macro that expands to enable_if'], a: 1,
      why: 'A concept is a compile-time boolean over types, such as `std::integral<T>`, that constrains a template. A call with a type that does not satisfy it is rejected at the call site with a readable message.' },

    { sec: 'concepts', q: 'What happens here?',
      code: String.raw`
template <std::integral T>
T twice(T v) { return v * 2; }
twice(2.5);`,
      opts: ['It returns 5.0', 'It returns 4 (the double is truncated)', 'A compile error: the constraint std::integral<double> is not satisfied', 'A run-time exception'], a: 2,
      why: 'A `double` is not integral, so the constrained template is not a candidate and the call fails to compile with a message that names the unmet constraint. Without the concept the function would happily return 5.0.' },

    { sec: 'concepts', q: 'In `requires(T a, T b) { { a + b } -> std::convertible_to<T>; }`, what does the part in braces express?',
      opts: ['That a + b must compile and its result must be convertible to T', 'That a and b must be equal', 'That + must be commutative', 'That T must be an integer type'], a: 0,
      why: 'A requires-expression lists operations that must be valid; `{ expr } -> Concept` also constrains the type of the result. It checks syntax and types only, not mathematical properties such as commutativity.' }
  ]
};
