// ============================================================================
// Project 03 - Consteval (Immediate Functions)  [C++20]
// Chapter F: Constexpr Functions
// ============================================================================
//
// KEY CONCEPT:
//   `consteval` declares an *immediate function* - one that MUST be evaluated
//   at compile-time. If a consteval function is called with arguments that
//   are not constant expressions, the program is ill-formed (compile error).
//
//   Use consteval when the function's purpose only makes sense at compile-time
//   and a runtime call would be a bug.
//
//   Like constexpr, consteval functions are implicitly inline.
// ============================================================================

#include <iostream>

// consteval: this function MUST be evaluated at compile-time.
// If you try to call it with a runtime value, you get a compile error.
consteval int compileTimeSquare(int n)
{
    return n * n;
}

// Another consteval example: compile-time absolute value.
consteval int compileTimeAbs(int n)
{
    return (n < 0) ? -n : n;
}

// A consteval function that computes the N-th Fibonacci number.
// Since it must run at compile-time, N must be a constant expression.
consteval int fibonacci(int n)
{
    if (n <= 1)
        return n;

    int a{0};
    int b{1};
    for (int i{2}; i <= n; ++i)
    {
        int temp{a + b};
        a = b;
        b = temp;
    }
    return b;
}

int main()
{
    // -----------------------------------------------------------------------
    // Valid: arguments are constant expressions → compile-time evaluation.
    // -----------------------------------------------------------------------
    constexpr int sq{compileTimeSquare(8)};
    std::cout << "compileTimeSquare(8)  = " << sq << '\n';

    constexpr int absVal{compileTimeAbs(-42)};
    std::cout << "compileTimeAbs(-42)   = " << absVal << '\n';

    constexpr int fib10{fibonacci(10)};
    std::cout << "fibonacci(10)         = " << fib10 << '\n';

    // Even assigning to a non-constexpr variable is fine, as long as the
    // argument itself is a constant expression.
    int x{compileTimeSquare(3)}; // OK - argument 3 is a constant
    std::cout << "compileTimeSquare(3)  = " << x << '\n';

    // -----------------------------------------------------------------------
    // INVALID (would not compile):
    //   int n{};
    //   std::cin >> n;
    //   int result{ compileTimeSquare(n) };   // ERROR! n is not a constant
    //
    // Uncomment the lines above to see the compiler error.
    // -----------------------------------------------------------------------

    // -----------------------------------------------------------------------
    // consteval in static_assert - perfectly valid.
    // -----------------------------------------------------------------------
    static_assert(fibonacci(7) == 13, "fibonacci(7) should be 13");

    std::cout << "\nAll consteval calls succeeded at compile-time!\n";

    return 0;
}
