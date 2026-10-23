// Project 08 - Floating-Point Comparison Pitfalls
// Chapter 9: Error Detection and Handling
//
// Why == fails for floating-point numbers:
//   Most decimal fractions (like 0.1) cannot be represented exactly in
//   binary floating-point. Repeated arithmetic accumulates tiny rounding
//   errors, so two values that "should" be equal often differ by a tiny
//   amount (e.g., 1e-16).
//
// Solutions:
//   1. Epsilon comparison:  std::abs(a - b) < epsilon
//   2. Relative comparison: std::abs(a - b) <= epsilon * std::max(|a|, |b|)
//      (handles both small and large magnitudes)
//
// This is a common semantic error listed in Chapter 9.

#include <algorithm> // std::max
#include <cmath>     // std::abs
#include <iomanip>   // std::setprecision
#include <iostream>

// ============================================================================
// Comparison functions
// ============================================================================

// Absolute epsilon comparison - good when values are near zero or small.
bool almostEqualAbs(double a, double b, double epsilon = 1e-9)
{
    return std::abs(a - b) < epsilon;
}

// Relative epsilon comparison - handles both small and large magnitudes.
// Falls back to absolute comparison when both values are near zero.
bool almostEqualRel(double a, double b, double relEpsilon = 1e-9,
                    double absEpsilon = 1e-12)
{
    double diff{std::abs(a - b)};

    // If the difference is very small in absolute terms, they're equal
    if (diff <= absEpsilon)
        return true;

    // Otherwise, compare relative to the larger magnitude
    double largest{std::max(std::abs(a), std::abs(b))};
    return diff <= largest * relEpsilon;
}

// ============================================================================
// Demonstrations
// ============================================================================

void demo_equalityFails()
{
    std::cout << "--- Why == fails for doubles ---\n";

    double sum{0.0};
    for (int i{0}; i < 10; ++i)
        sum += 0.1;

    std::cout << std::setprecision(17);
    std::cout << "  0.1 added 10 times = " << sum << '\n';
    std::cout << "  1.0                = " << 1.0 << '\n';
    std::cout << "  (sum == 1.0)       = " << std::boolalpha << (sum == 1.0) << '\n';
    std::cout << "  Difference         = " << std::abs(sum - 1.0) << '\n';
    std::cout << '\n';
}

void demo_absoluteEpsilon()
{
    std::cout << "--- Absolute epsilon comparison ---\n";

    double sum{0.0};
    for (int i{0}; i < 10; ++i)
        sum += 0.1;

    bool result{almostEqualAbs(sum, 1.0)};
    std::cout << "  almostEqualAbs(sum, 1.0) = " << std::boolalpha << result << '\n';

    // Works well for small values
    std::cout << "  almostEqualAbs(0.0, 1e-10) = "
              << almostEqualAbs(0.0, 1e-10) << " (within epsilon)\n";
    std::cout << '\n';
}

void demo_relativeEpsilon()
{
    std::cout << "--- Relative epsilon comparison ---\n";

    // Large values: absolute epsilon would be too strict
    double a{1000000.1};
    double b{1000000.1000000001}; // Differs by ~1e-10 relative to magnitude

    std::cout << std::setprecision(17);
    std::cout << "  a = " << a << '\n';
    std::cout << "  b = " << b << '\n';
    std::cout << "  (a == b)              = " << (a == b) << '\n';
    std::cout << "  almostEqualRel(a, b)  = " << almostEqualRel(a, b) << '\n';

    // Small values near zero
    double c{0.0};
    double d{1e-15};
    std::cout << "  almostEqualRel(0.0, 1e-15) = "
              << almostEqualRel(c, d) << " (near-zero fallback)\n";
    std::cout << '\n';
}

void demo_commonMistakes()
{
    std::cout << "--- Common floating-point mistakes ---\n";

    // Mistake 1: Using == in a loop termination condition
    std::cout << "  Mistake: using == with doubles in a loop condition\n";
    // BAD:  for (double d = 0.0; d != 1.0; d += 0.1)  // May never terminate!
    // GOOD: for (double d = 0.0; d < 1.0; d += 0.1)   // Use < instead
    int count{0};
    for (double d{0.0}; d < 1.0; d += 0.1)
        ++count;
    std::cout << "  Loop ran " << count << " times using < (correct)\n";

    // Mistake 2: Checking exact equality after arithmetic
    double third{1.0 / 3.0};
    double reconstructed{third * 3.0};
    std::cout << "\n  1.0/3.0 * 3.0 = " << std::setprecision(17) << reconstructed << '\n';
    std::cout << "  == 1.0?  " << (reconstructed == 1.0) << '\n';
    std::cout << "  almostEqualAbs?  " << almostEqualAbs(reconstructed, 1.0) << '\n';
    std::cout << '\n';
}

// ============================================================================
// Main
// ============================================================================

int main()
{
    std::cout << "=== Floating-Point Comparison Pitfalls Demo ===\n\n";

    demo_equalityFails();
    demo_absoluteEpsilon();
    demo_relativeEpsilon();
    demo_commonMistakes();

    std::cout << "Key takeaway: Never use == to compare floating-point results.\n";
    std::cout << "Use an epsilon-based comparison instead.\n";
    return 0;
}
