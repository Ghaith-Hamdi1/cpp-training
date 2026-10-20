// ============================================================================
// Project 01 - Constexpr Function Basics
// Chapter F: Constexpr Functions
// ============================================================================
//
// KEY CONCEPT:
//   A function marked `constexpr` is *allowed* to be evaluated at compile-time.
//   - When called in a context that REQUIRES a constant expression (e.g.,
//     initializing a constexpr variable), the call is guaranteed to be
//     evaluated at compile-time.
//   - When called in a non-required context (e.g., initializing a non-const
//     variable), the compiler MAY still evaluate it at compile-time, but
//     is NOT obligated to. The function behaves like a normal function.
//
//   A constexpr function is also implicitly inline.
// ============================================================================

#include <iostream>

// A simple constexpr function: computes the square of an integer.
// Because it is a *pure function* (no side effects, same input → same output),
// it is an ideal candidate for constexpr.
constexpr int square(int n)
{
    return n * n;
}

// Another constexpr function: computes the sum of integers from 1 to n.
constexpr int triangular(int n)
{
    int sum{0};
    for (int i{1}; i <= n; ++i)
        sum += i;
    return sum;
}

int main()
{
    // -----------------------------------------------------------------------
    // 1) Compile-time evaluation (GUARANTEED)
    //    The result is used to initialize a constexpr variable, so the
    //    compiler MUST evaluate square(5) at compile-time.
    // -----------------------------------------------------------------------
    constexpr int sq{square(5)};
    std::cout << "square(5)  = " << sq << "  [compile-time]\n";

    // -----------------------------------------------------------------------
    // 2) Compile-time evaluation in another required context:
    //    static_assert requires a constant expression.
    // -----------------------------------------------------------------------
    static_assert(square(4) == 16, "square(4) must be 16");
    std::cout << "static_assert(square(4) == 16) passed!\n";

    // -----------------------------------------------------------------------
    // 3) Runtime evaluation
    //    Reading from std::cin gives us a non-constant value, so the
    //    compiler cannot evaluate square() at compile-time here.
    // -----------------------------------------------------------------------
    std::cout << "\nEnter an integer: ";
    int userInput{};
    std::cin >> userInput;

    // square() is called at runtime - it works just like a normal function.
    int result{square(userInput)};
    std::cout << "square(" << userInput << ") = " << result << "  [runtime]\n";

    // -----------------------------------------------------------------------
    // 4) Constexpr function with a loop (triangular numbers)
    //    Constexpr functions can contain loops, local variables, etc.
    // -----------------------------------------------------------------------
    constexpr int t10{triangular(10)};
    std::cout << "\ntriangular(10) = " << t10 << "  [compile-time]\n";

    return 0;
}
