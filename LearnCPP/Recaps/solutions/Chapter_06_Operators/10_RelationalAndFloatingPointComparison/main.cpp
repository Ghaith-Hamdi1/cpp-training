// Chapter 6 - Project 10: Relational Operators and Floating-Point Comparison
// ============================================================================
// Key ideas:
//   • Six relational operators: >, <, >=, <=, ==, != - all return bool.
//   • NEVER use == or != on calculated floating-point values (rounding errors).
//   • Use an epsilon-based comparison for approximate equality:
//       – Absolute epsilon: good for values near zero.
//       – Relative epsilon (Knuth's algorithm): scales with magnitude.
//       – Best practice: combine both.

#include <algorithm> // std::max
#include <cmath>     // std::abs
#include <iostream>

// -----------------------------------------------------------------
// Approximate equality using combined absolute + relative epsilon
// -----------------------------------------------------------------
// absEpsilon handles values near zero (where relative comparison breaks).
// relEpsilon is a percentage tolerance for larger values.
bool approximatelyEqual(double a, double b,
                        double absEpsilon = 1e-12,
                        double relEpsilon = 1e-8)
{
    // If the difference is within the absolute tolerance, they're "equal"
    double diff{std::abs(a - b)};
    if (diff <= absEpsilon)
        return true;

    // Otherwise scale the tolerance by the larger magnitude (Knuth)
    return diff <= std::max(std::abs(a), std::abs(b)) * relEpsilon;
}

int main()
{
    // -----------------------------------------------------------------
    // 1. Basic relational operators
    // -----------------------------------------------------------------
    std::cout << std::boolalpha;
    std::cout << "--- Relational Operators ---\n";
    std::cout << "5 >  3  = " << (5 > 3) << '\n';  // true
    std::cout << "5 <  3  = " << (5 < 3) << '\n';  // false
    std::cout << "5 >= 5  = " << (5 >= 5) << '\n'; // true
    std::cout << "5 <= 4  = " << (5 <= 4) << '\n'; // false
    std::cout << "5 == 5  = " << (5 == 5) << '\n'; // true
    std::cout << "5 != 5  = " << (5 != 5) << '\n'; // false
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 2. The floating-point equality problem
    // -----------------------------------------------------------------
    std::cout << "--- Floating-Point Equality Problem ---\n";
    double a{0.1 + 0.2};
    double b{0.3};
    std::cout << "0.1 + 0.2 == 0.3  →  " << (a == b) << '\n'; // false!
    std::cout << "  Because 0.1 + 0.2 = " << a << " (tiny rounding error)\n\n";

    // -----------------------------------------------------------------
    // 3. Epsilon-based comparison - correct approach
    // -----------------------------------------------------------------
    std::cout << "--- Epsilon-Based Comparison ---\n";
    std::cout << "approximatelyEqual(0.1+0.2, 0.3) = "
              << approximatelyEqual(a, b) << '\n'; // true

    // Works for larger magnitudes too
    double big1{100000000.0};
    double big2{100000000.00000001};
    std::cout << "approximatelyEqual(1e8, 1e8+1e-8) = "
              << approximatelyEqual(big1, big2) << '\n'; // true
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 4. Why absolute epsilon alone is insufficient
    // -----------------------------------------------------------------
    std::cout << "--- Absolute vs. Relative Epsilon ---\n";
    double x{1e10};
    double y{x + 1.0}; // differ by 1.0 - large absolute diff, tiny relative diff
    double tinyAbs{1e-12};
    std::cout << "abs diff = " << std::abs(x - y) << '\n';
    std::cout << "Within absEpsilon(1e-12)? " << (std::abs(x - y) <= tinyAbs) << '\n'; // false
    std::cout << "approximatelyEqual?       " << approximatelyEqual(x, y, tinyAbs, 1e-8) << '\n';
    std::cout << "Relative epsilon handles large-magnitude values correctly.\n";

    return 0;
}
