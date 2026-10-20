// ============================================================================
// Project 07 - Testing Constexpr Functions in a Constant Context
// Chapter F: Constexpr Functions
// ============================================================================
//
// KEY CONCEPT (PITFALL):
//   A constexpr function may compile and run perfectly fine at *runtime*,
//   yet FAIL when actually forced to evaluate at compile-time.
//
//   This can happen if:
//     • The function internally calls a non-constexpr function.
//     • The function does something not allowed at compile-time
//       (e.g., dynamic allocation that persists, I/O, etc.).
//
//   BEST PRACTICE:
//     Always test every constexpr function by assigning its result to a
//     constexpr variable (or using static_assert).  This forces the compiler
//     to evaluate it at compile-time and catches hidden issues early.
//
//   This project demonstrates a CORRECT constexpr function and shows
//   (via comments) what a broken one looks like.
// ============================================================================

#include <iostream>
#include <cmath> // for std::sqrt (NOT constexpr in most implementations)

// ---------------------------------------------------------------------------
// A correctly written constexpr function - works at compile-time AND runtime.
// ---------------------------------------------------------------------------
constexpr int clamp(int value, int lo, int hi)
{
    if (value < lo)
        return lo;
    if (value > hi)
        return hi;
    return value;
}

// ---------------------------------------------------------------------------
// A "sneaky" function that compiles for runtime but FAILS at compile-time.
// (Uncomment to see the error.)
//
// constexpr double hypotenuse(double a, double b)
// {
//     // std::sqrt is NOT constexpr in most standard library implementations.
//     // This function compiles fine if called at runtime, but fails when
//     // used in a constexpr context.
//     return std::sqrt(a * a + b * b);
// }
//
// If you call:
//     double h = hypotenuse(3.0, 4.0);       // ✓ compiles (runtime)
//     constexpr double h = hypotenuse(3.0, 4.0); // ✗ compile error!
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Our own constexpr-safe integer square root (Newton's method).
// This version works at compile-time because it uses no non-constexpr calls.
// ---------------------------------------------------------------------------
constexpr int isqrt(int n)
{
    if (n < 0)
        return -1; // error indicator
    if (n < 2)
        return n;

    int guess{n / 2};
    while (true)
    {
        int next{(guess + n / guess) / 2};
        if (next >= guess)
            return guess;
        guess = next;
    }
}

int main()
{
    // -----------------------------------------------------------------------
    // 1) TEST in a constant context - forces compile-time evaluation.
    //    If clamp() had a hidden non-constexpr call, this would fail.
    // -----------------------------------------------------------------------
    constexpr int c1{clamp(15, 0, 10)}; // should be 10
    constexpr int c2{clamp(-5, 0, 10)}; // should be 0
    constexpr int c3{clamp(7, 0, 10)};  // should be 7

    static_assert(c1 == 10, "clamp upper bound failed");
    static_assert(c2 == 0, "clamp lower bound failed");
    static_assert(c3 == 7, "clamp passthrough failed");

    std::cout << "clamp(15, 0, 10) = " << c1 << '\n';
    std::cout << "clamp(-5, 0, 10) = " << c2 << '\n';
    std::cout << "clamp( 7, 0, 10) = " << c3 << '\n';

    // -----------------------------------------------------------------------
    // 2) TEST isqrt in a constant context.
    // -----------------------------------------------------------------------
    constexpr int sq{isqrt(144)}; // should be 12
    static_assert(sq == 12, "isqrt(144) should be 12");
    std::cout << "\nisqrt(144)       = " << sq << '\n';

    constexpr int sq2{isqrt(50)}; // should be 7 (integer sqrt)
    static_assert(sq2 == 7, "isqrt(50) should be 7");
    std::cout << "isqrt(50)        = " << sq2 << '\n';

    // -----------------------------------------------------------------------
    // 3) Runtime usage of the same functions still works fine.
    // -----------------------------------------------------------------------
    int val{};
    std::cout << "\nEnter a value to clamp (0-10): ";
    std::cin >> val;
    std::cout << "clamp(" << val << ", 0, 10) = " << clamp(val, 0, 10) << '\n';

    std::cout << "\n--- Best Practice ---\n"
              << "Always test constexpr functions with:\n"
              << "  constexpr auto result{ myFunc(args) };\n"
              << "This catches hidden non-constexpr calls at compile-time.\n";

    return 0;
}
