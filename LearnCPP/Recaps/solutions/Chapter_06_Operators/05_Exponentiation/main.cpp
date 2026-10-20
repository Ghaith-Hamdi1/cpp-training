// Chapter 6 - Project 05: Exponentiation
// ========================================
// Key ideas:
//   • C++ has NO built-in exponent operator (unlike Python's **).
//   • std::pow() from <cmath> works with floating-point values.
//   • For integer exponentiation, write your own function (beware overflow).
//   • std::pow() may introduce tiny rounding errors for integer bases/exponents.

#include <cmath>   // std::pow
#include <cstdint> // std::int64_t
#include <iostream>
#include <limits> // std::numeric_limits

// A simple integer power function for non-negative exponents.
// Uses repeated multiplication to avoid floating-point rounding issues.
// Returns -1 on overflow (a simplistic sentinel for demonstration).
std::int64_t intPow(std::int64_t base, int exp)
{
    // Guard: negative exponents are not meaningful for integer results
    if (exp < 0)
    {
        std::cerr << "intPow: negative exponent not supported for integers.\n";
        return 0;
    }

    std::int64_t result{1};
    for (int i{0}; i < exp; ++i)
    {
        // Simple overflow check before multiplying
        if (result != 0 && base > std::numeric_limits<std::int64_t>::max() / result)
        {
            std::cerr << "intPow: overflow detected (" << base << "^" << exp << ")\n";
            return -1; // sentinel
        }
        result *= base;
    }
    return result;
}

int main()
{
    // -----------------------------------------------------------------
    // 1. std::pow - floating-point exponentiation
    // -----------------------------------------------------------------
    std::cout << "--- std::pow (floating-point) ---\n";
    std::cout << "2.0 ^ 10 = " << std::pow(2.0, 10) << '\n';   // 1024
    std::cout << "3.0 ^ 4  = " << std::pow(3.0, 4) << '\n';    // 81
    std::cout << "2.5 ^ 3  = " << std::pow(2.5, 3) << '\n';    // 15.625
    std::cout << "9.0 ^ 0.5 = " << std::pow(9.0, 0.5) << '\n'; // 3 (square root)
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 2. Rounding pitfall with std::pow on integers
    // -----------------------------------------------------------------
    std::cout << "--- Rounding pitfall ---\n";
    // std::pow returns a double - casting to int may truncate a result like 124.9999999 to 124
    double raw{std::pow(5.0, 3.0)};
    int truncated{static_cast<int>(raw)};
    int rounded{static_cast<int>(std::round(raw))};
    std::cout << "std::pow(5.0, 3.0) = " << raw << '\n';
    std::cout << "Truncated to int   = " << truncated << '\n';
    std::cout << "Rounded to int     = " << rounded << '\n';
    std::cout << "(Always round when converting std::pow results to int)\n\n";

    // -----------------------------------------------------------------
    // 3. Integer exponentiation - custom function
    // -----------------------------------------------------------------
    std::cout << "--- intPow (integer exponentiation) ---\n";
    std::cout << "2 ^ 10 = " << intPow(2, 10) << '\n'; // 1024
    std::cout << "3 ^ 4  = " << intPow(3, 4) << '\n';  // 81
    std::cout << "7 ^ 0  = " << intPow(7, 0) << '\n';  // 1  (any number ^ 0 = 1)

    // Overflow demonstration
    std::cout << "2 ^ 63 = " << intPow(2, 63) << "  (overflow check)\n";

    return 0;
}
