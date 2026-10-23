// Chapter 6 - Project 03: Integer vs. Floating-Point Division
// ============================================================
// Key ideas:
//   • When BOTH operands are integers, C++ performs integer division (truncation).
//   • When at least ONE operand is floating-point, the result is floating-point.
//   • Use static_cast<double>() to force floating-point division from int operands.
//   • Dividing by integer 0 is UNDEFINED BEHAVIOR - always guard against it.

#include <iostream>

int main()
{
    // -----------------------------------------------------------------
    // 1. Integer division truncates the fractional part
    // -----------------------------------------------------------------
    std::cout << "--- Integer Division ---\n";
    std::cout << " 7 /  4 = " << (7 / 4) << '\n';  //  1  (not 1.75)
    std::cout << "-7 /  4 = " << (-7 / 4) << '\n'; // -1  (truncates toward zero)
    std::cout << " 7 / -4 = " << (7 / -4) << '\n'; // -1
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 2. Floating-point division preserves the fraction
    // -----------------------------------------------------------------
    std::cout << "--- Floating-Point Division ---\n";
    std::cout << "7.0 / 4.0 = " << (7.0 / 4.0) << '\n'; // 1.75
    std::cout << "7.0 / 4   = " << (7.0 / 4) << '\n';   // 1.75 (int 4 promoted to double)
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 3. Using static_cast to get floating-point division from int operands
    // -----------------------------------------------------------------
    int numerator{7};
    int denominator{4};

    // BAD - integer division
    std::cout << "int / int                    = " << (numerator / denominator) << '\n'; // 1

    // GOOD - cast one operand to double
    std::cout << "static_cast<double>(int)/int = "
              << (static_cast<double>(numerator) / denominator) << '\n'; // 1.75

    // Also works if you cast the denominator instead
    std::cout << "int/static_cast<double>(int) = "
              << (numerator / static_cast<double>(denominator)) << '\n'; // 1.75
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 4. Guarding against division by zero
    // -----------------------------------------------------------------
    int divisor{0};
    std::cout << "--- Division-by-zero guard ---\n";

    if (divisor != 0)
        std::cout << "numerator / divisor = " << (numerator / divisor) << '\n';
    else
        std::cout << "Cannot divide by zero - skipping to avoid undefined behavior.\n";

    // Floating-point division by 0.0 is defined (produces ±inf or NaN), but
    // integer division by 0 is undefined behavior and must be prevented.

    return 0;
}
