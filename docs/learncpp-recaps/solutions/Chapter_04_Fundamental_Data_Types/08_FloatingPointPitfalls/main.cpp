// Chapter 4 - Project 08: Floating-Point Pitfalls
// ==================================================
// Key concept: Floating-point types can only store a limited number of
// significant digits. Values like 0.1 cannot be represented exactly in
// binary, leading to rounding errors that accumulate with operations.
//
// CRITICAL: Never compare floating-point values with == directly.
//
// IEEE 754 defines special values: Inf, -Inf, NaN, and signed zero.

#include <cmath> // For std::abs, std::isnan, std::isinf
#include <iomanip>
#include <iostream>

// A helper function to compare floats within a tolerance (epsilon)
bool approximatelyEqual(double a, double b, double epsilon = 1e-9)
{
    return std::abs(a - b) < epsilon;
}

int main()
{
    std::cout << "=== Floating-Point Pitfalls ===\n\n";

    // --- Rounding errors ---
    std::cout << "--- Rounding errors ---\n";
    std::cout << std::setprecision(17);

    double d1{0.1};
    std::cout << "0.1 stored as double: " << d1 << '\n';
    // 0.1 cannot be represented exactly in binary floating point!

    double sum{0.0};
    for (int i{0}; i < 10; ++i)
        sum += 0.1;

    std::cout << "0.1 added 10 times:   " << sum << '\n';
    std::cout << "Expected:             " << 1.0 << '\n';
    std::cout << '\n';

    // --- Why == fails ---
    std::cout << "--- Why == fails for floats ---\n";
    if (sum == 1.0)
        std::cout << "sum == 1.0: TRUE\n";
    else
        std::cout << "sum == 1.0: FALSE (rounding errors made sum != 1.0 exactly)\n";

    // Better: use an epsilon comparison
    if (approximatelyEqual(sum, 1.0))
        std::cout << "approximatelyEqual(sum, 1.0): TRUE (correct approach)\n";
    std::cout << '\n';

    // --- Precision loss with large and small numbers ---
    std::cout << std::setprecision(17);
    std::cout << "--- Precision loss ---\n";
    float f1{1.23456789012345f}; // float only has ~7 digits
    std::cout << "float  1.23456789012345: " << f1 << " (only ~7 digits reliable)\n";

    double d2{1.23456789012345}; // double has ~16 digits
    std::cout << "double 1.23456789012345: " << d2 << " (~16 digits reliable)\n";
    std::cout << '\n';

    // --- Special IEEE 754 values ---
    std::cout << std::setprecision(6);
    std::cout << "--- Special IEEE 754 values ---\n";

    double inf{1.0 / 0.0};     // Positive infinity
    double negInf{-1.0 / 0.0}; // Negative infinity
    double nan{0.0 / 0.0};     // Not a Number

    std::cout << " 1.0 / 0.0  = " << inf << '\n';
    std::cout << "-1.0 / 0.0  = " << negInf << '\n';
    std::cout << " 0.0 / 0.0  = " << nan << '\n';

    // NaN is special: it's not equal to anything, including itself
    std::cout << "NaN == NaN?  " << std::boolalpha << (nan == nan) << " (always false!)\n";
    std::cout << "std::isnan:  " << std::isnan(nan) << " (correct way to check)\n";
    std::cout << "std::isinf:  " << std::isinf(inf) << '\n';
    std::cout << '\n';

    // Summary
    std::cout << "--- Best Practices ---\n";
    std::cout << "1. Favor double over float for better precision.\n";
    std::cout << "2. Never compare floats with == directly.\n";
    std::cout << "3. Use epsilon-based comparison for float equality.\n";
    std::cout << "4. Be aware that rounding errors accumulate.\n";

    return 0;
}
