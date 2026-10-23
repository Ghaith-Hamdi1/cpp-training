// ============================================================================
// Project 06 - Constexpr Local Variables and Mutation
// Chapter F: Constexpr Functions
// ============================================================================
//
// KEY CONCEPT:
//   Constexpr (and consteval) functions CAN:
//     • Declare non-const local variables.
//     • Mutate those local variables (including with loops).
//     • Call other constexpr functions (even if the callee's parameters
//       aren't constexpr - the compiler resolves everything at compile-time
//       when the outermost call is in a required constant context).
//
//   The only restriction is that the function must be evaluable with the
//   given arguments at compile-time.  Side effects that persist beyond
//   the function (like I/O) are not allowed during compile-time evaluation.
// ============================================================================

#include <iostream>

// ---------------------------------------------------------------------------
// A constexpr function that uses local mutable variables and a loop.
// ---------------------------------------------------------------------------
constexpr int sumOfSquares(int n)
{
    int total{0}; // non-const local - perfectly fine
    for (int i{1}; i <= n; ++i)
    {
        total += i * i; // mutation - perfectly fine
    }
    return total;
}

// ---------------------------------------------------------------------------
// A constexpr helper called by another constexpr function.
// Even though 'base' and 'exp' are not constexpr inside this body,
// the compiler can still resolve the call at compile-time when
// the *caller* is being evaluated at compile-time.
// ---------------------------------------------------------------------------
constexpr int power(int base, int exp)
{
    int result{1};
    for (int i{0}; i < exp; ++i)
        result *= base;
    return result;
}

// ---------------------------------------------------------------------------
// This constexpr function calls power() - a constexpr-to-constexpr chain.
// When volume() is evaluated at compile-time, power() is also evaluated
// at compile-time, even though its parameters aren't constexpr.
// ---------------------------------------------------------------------------
constexpr int volume(int side)
{
    return power(side, 3); // side^3
}

// ---------------------------------------------------------------------------
// A constexpr function with conditional logic and an accumulator.
// ---------------------------------------------------------------------------
constexpr int countEvenDigits(int n)
{
    if (n < 0)
        n = -n; // mutate parameter - allowed!
    if (n == 0)
        return 1; // 0 is even

    int count{0};
    while (n > 0)
    {
        if ((n % 10) % 2 == 0)
            ++count;
        n /= 10; // mutating parameter again - fine
    }
    return count;
}

int main()
{
    // -----------------------------------------------------------------------
    // All of these are evaluated at compile-time (constexpr initialization).
    // -----------------------------------------------------------------------
    constexpr int ss5{sumOfSquares(5)};        // 1+4+9+16+25 = 55
    constexpr int p{power(2, 10)};             // 1024
    constexpr int v{volume(4)};                // 64
    constexpr int ed{countEvenDigits(123456)}; // digits 2,4,6 → 3

    std::cout << "sumOfSquares(5)       = " << ss5 << '\n';
    std::cout << "power(2, 10)          = " << p << '\n';
    std::cout << "volume(4)             = " << v << '\n';
    std::cout << "countEvenDigits(123456) = " << ed << '\n';

    // Compile-time verification
    static_assert(sumOfSquares(5) == 55);
    static_assert(power(2, 10) == 1024);
    static_assert(volume(4) == 64);
    static_assert(countEvenDigits(123456) == 3);

    std::cout << "\nAll static_asserts passed - compile-time evaluation works\n"
              << "even with mutable locals, loops, and nested constexpr calls!\n";

    return 0;
}
