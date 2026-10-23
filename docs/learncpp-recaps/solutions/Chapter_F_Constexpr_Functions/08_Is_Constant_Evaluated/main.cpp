// ============================================================================
// Project 08 - std::is_constant_evaluated() and if consteval
// Chapter F: Constexpr Functions
// ============================================================================
//
// KEY CONCEPT:
//   Sometimes a constexpr function needs to behave differently depending
//   on whether it is being evaluated at compile-time or runtime.
//
//   C++20:  std::is_constant_evaluated()
//     Returns true  - in a *required* constant-expression context.
//     Returns false - when called at runtime.
//     CAUTION: It does NOT simply mean "running at compile-time."
//              In an *optional* compile-time context (e.g., the compiler
//              choosing to optimize), it may still return false.
//
//   C++23:  if consteval { ... } else { ... }
//     A cleaner syntax that replaces the somewhat confusing
//     std::is_constant_evaluated().  The 'if consteval' branch is taken
//     only in a *manifestly constant-evaluated* context.
//
//   Both utilities let you provide a fast compile-time path and a
//   potentially different runtime path (e.g., using non-constexpr library
//   functions at runtime).
// ============================================================================

#include <iostream>
#include <type_traits> // for std::is_constant_evaluated (C++20)

// ---------------------------------------------------------------------------
// Example using std::is_constant_evaluated() (C++20)
// ---------------------------------------------------------------------------
constexpr int smartAbs(int n)
{
    if (std::is_constant_evaluated())
    {
        // Compile-time path: pure manual implementation
        return (n < 0) ? -n : n;
    }
    else
    {
        // Runtime path: could use a library function or platform intrinsic.
        // Here we just do the same thing, but you could imagine a more
        // efficient runtime implementation.
        return (n < 0) ? -n : n;
    }
}

// ---------------------------------------------------------------------------
// Example: different algorithm for compile-time vs runtime.
// At compile-time we use a simple loop; at runtime we could use a
// more optimized approach (here simplified for demonstration).
// ---------------------------------------------------------------------------
constexpr int smartPower(int base, int exp)
{
    if (std::is_constant_evaluated())
    {
        // Compile-time: straightforward loop (simplicity)
        int result{1};
        for (int i{0}; i < exp; ++i)
            result *= base;
        return result;
    }
    else
    {
        // Runtime: exponentiation by squaring (efficiency)
        int result{1};
        int b{base};
        int e{exp};
        while (e > 0)
        {
            if (e % 2 == 1)
                result *= b;
            b *= b;
            e /= 2;
        }
        return result;
    }
}

// ---------------------------------------------------------------------------
// Example using "if consteval" (C++23)
// Uncomment if your compiler supports C++23.
// ---------------------------------------------------------------------------
/*
constexpr int smartAbsC23(int n)
{
    if consteval
    {
        // Manifestly constant-evaluated context
        return (n < 0) ? -n : n;
    }
    else
    {
        // Runtime context
        return (n < 0) ? -n : n;
    }
}
*/

int main()
{
    // -----------------------------------------------------------------------
    // 1) Required constant context → is_constant_evaluated() returns true
    // -----------------------------------------------------------------------
    constexpr int a1{smartAbs(-10)};
    std::cout << "smartAbs(-10) [compile-time] = " << a1 << '\n';
    static_assert(a1 == 10);

    constexpr int p1{smartPower(2, 8)};
    std::cout << "smartPower(2,8) [compile-time] = " << p1 << '\n';
    static_assert(p1 == 256);

    // -----------------------------------------------------------------------
    // 2) Runtime context → is_constant_evaluated() returns false
    // -----------------------------------------------------------------------
    int x{};
    std::cout << "\nEnter an integer: ";
    std::cin >> x;

    int a2{smartAbs(x)};
    std::cout << "smartAbs(" << x << ") [runtime] = " << a2 << '\n';

    int p2{smartPower(x, 3)};
    std::cout << "smartPower(" << x << ", 3) [runtime] = " << p2 << '\n';

    // -----------------------------------------------------------------------
    // 3) Important subtlety:
    //    In a non-required context (plain int, not constexpr), even if the
    //    compiler decides to evaluate at compile-time as an optimization,
    //    is_constant_evaluated() returns false.
    //
    //    int val{ smartAbs(-5) };
    //    The compiler *might* compute this at compile-time, but
    //    is_constant_evaluated() will still return false because it's
    //    not a REQUIRED constant context.
    // -----------------------------------------------------------------------
    std::cout << "\n--- Key Subtlety ---\n"
              << "std::is_constant_evaluated() returns true ONLY in a\n"
              << "*required* constant context (constexpr init, static_assert,\n"
              << "template arg, etc.), NOT whenever the compiler *happens*\n"
              << "to optimize a call to compile-time.\n";

    return 0;
}
