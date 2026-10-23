// Chapter 4 - Project 07: Floating-Point Basics
// ================================================
// Key concept: C++ has three floating-point types:
//   float       - 4 bytes, ~7 digits of precision
//   double      - 8 bytes, ~15-16 digits of precision
//   long double - 8, 12, or 16 bytes (platform-dependent)
//
// Floating-point literals are double by default. Use 'f' suffix for float.
// Scientific notation: 1.23e4 means 1.23 × 10^4 = 12300.0
//
// Best practice: Favor double over float - floats lack precision.
// Pitfall: Forgetting the 'f' suffix - 5.0 is double, 5.0f is float.

#include <iomanip> // For std::setprecision
#include <iostream>

int main()
{
    std::cout << "=== Floating-Point Basics ===\n\n";

    // Sizes of floating-point types
    std::cout << "--- Type sizes ---\n";
    std::cout << "float:       " << sizeof(float) << " bytes\n";
    std::cout << "double:      " << sizeof(double) << " bytes\n";
    std::cout << "long double: " << sizeof(long double) << " bytes\n";
    std::cout << '\n';

    // Literal types
    float f{5.0f};        // 'f' suffix makes it a float literal
    double d{5.0};        // No suffix = double (default)
    long double ld{5.0L}; // 'L' suffix for long double

    std::cout << "--- Literal suffixes ---\n";
    std::cout << "5.0f (float):       " << f << '\n';
    std::cout << "5.0  (double):      " << d << '\n';
    std::cout << "5.0L (long double): " << ld << '\n';
    std::cout << '\n';

    // Scientific notation in C++
    std::cout << "--- Scientific notation ---\n";
    double avogadro{6.02e23}; // 6.02 × 10^23
    double electron{1.6e-19}; // 1.6 × 10^-19
    double simple{1.23e4};    // 1.23 × 10^4 = 12300

    std::cout << "6.02e23  = " << avogadro << '\n';
    std::cout << "1.6e-19  = " << electron << '\n';
    std::cout << "1.23e4   = " << simple << '\n';
    std::cout << '\n';

    // Precision of different types
    std::cout << "--- Precision comparison ---\n";
    std::cout << std::setprecision(17); // Show up to 17 digits

    float fPi{3.14159265358979323846f}; // float can only store ~7 digits
    double dPi{3.14159265358979323846}; // double stores ~16 digits

    std::cout << "float  pi: " << fPi << " (only ~7 digits accurate)\n";
    std::cout << "double pi: " << dPi << " (about ~16 digits accurate)\n";
    std::cout << '\n';

    // Reset precision
    std::cout << std::setprecision(6); // default

    // Pitfall: forgetting the 'f' suffix
    std::cout << "--- Pitfall: Missing 'f' suffix ---\n";
    // float x = 5.0;  // 5.0 is a double literal being converted to float
    // float x = 5.0f; // Correct: 5.0f is already a float literal
    std::cout << "5.0  is type double (8 bytes)\n";
    std::cout << "5.0f is type float  (4 bytes)\n";
    std::cout << "Always use 'f' suffix when assigning to float variables.\n";

    return 0;
}
