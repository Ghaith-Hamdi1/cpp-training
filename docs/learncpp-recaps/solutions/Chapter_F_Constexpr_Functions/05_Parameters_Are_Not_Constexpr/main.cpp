// ============================================================================
// Project 05 - Parameters Are Not Constexpr (Common Pitfall)
// Chapter F: Constexpr Functions
// ============================================================================
//
// KEY CONCEPT (PITFALL):
//   Function parameters of constexpr (and even consteval) functions are
//   NEVER constexpr themselves.
//
//   Even though the compiler may know the argument's value at compile-time,
//   the C++ standard says parameters are not constant expressions.
//   This means you CANNOT:
//     • Use a parameter to initialize a constexpr variable inside the body.
//     • Use a parameter as a template non-type argument.
//     • Use a parameter in a static_assert.
//
//   This is a very common source of confusion for beginners.
// ============================================================================

#include <iostream>

// ---------------------------------------------------------------------------
// EXAMPLE 1: Correct usage - parameters used in ordinary expressions
// ---------------------------------------------------------------------------
constexpr int multiply(int a, int b)
{
    // 'a' and 'b' are NOT constexpr inside this function, but that's fine.
    // We can still use them in regular expressions and return them.
    // The result becomes a constant expression at the *call site* if
    // the arguments are constant expressions.
    return a * b;
}

// ---------------------------------------------------------------------------
// EXAMPLE 2: What you CANNOT do (commented out - would not compile)
// ---------------------------------------------------------------------------
/*
constexpr int broken(int n)
{
    // ERROR: 'n' is NOT a constant expression, even in a constexpr function
    constexpr int local{ n };         // ← compile error!

    // ERROR: template arguments require constant expressions
    // std::array<int, n> arr{};      // ← compile error!

    // ERROR: static_assert requires a constant expression
    // static_assert(n > 0);          // ← compile error!

    return local;
}
*/

// ---------------------------------------------------------------------------
// EXAMPLE 3: Even consteval doesn't make parameters constexpr
// ---------------------------------------------------------------------------
consteval int constevalExample(int n)
{
    // 'n' is still NOT constexpr inside this function body.
    // We can use it in normal expressions, but not as a constant expression.

    // constexpr int x{ n };  // ← would still be a compile error!

    // This is fine - we're just using n in a normal expression:
    int result{n * 2};
    return result;
}

// ---------------------------------------------------------------------------
// EXAMPLE 4: The workaround - use template non-type parameters
//   If you truly need a compile-time constant inside a function,
//   pass it as a template parameter instead of a function parameter.
// ---------------------------------------------------------------------------
template <int N>
constexpr int doubleValue()
{
    // N IS a constant expression - it's a template parameter, not a
    // function parameter.
    constexpr int result{N * 2};                     // ✓ OK!
    static_assert(N >= 0, "N must be non-negative"); // ✓ OK!
    return result;
}

int main()
{
    // multiply works at compile-time - the arguments are constant expressions
    // at the call site, even though the parameters aren't constexpr inside.
    constexpr int product{multiply(6, 7)};
    std::cout << "multiply(6, 7) = " << product << '\n';

    // consteval example - forced compile-time, but parameters still not constexpr
    constexpr int ce{constevalExample(21)};
    std::cout << "constevalExample(21) = " << ce << '\n';

    // Template parameter workaround - N is a true compile-time constant
    constexpr int dv{doubleValue<15>()};
    std::cout << "doubleValue<15>() = " << dv << '\n';

    // Summary
    std::cout << "\n--- Key Takeaway ---\n"
              << "Function parameters (even in constexpr/consteval functions)\n"
              << "are NEVER constexpr.  Use template parameters if you need\n"
              << "a true compile-time constant inside the function body.\n";

    return 0;
}
