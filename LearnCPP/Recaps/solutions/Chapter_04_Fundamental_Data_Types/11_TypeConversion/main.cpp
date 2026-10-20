// Chapter 4 - Project 11: Type Conversion and static_cast
// =========================================================
// Key concept: Type conversion changes a value from one type to another.
//   Implicit conversion: done automatically by the compiler.
//   Explicit conversion: done by the programmer using static_cast.
//
// Unsafe implicit conversions (e.g., double→int) generate warnings
// and silently drop data.
//
// Best practice: Use static_cast<new_type>(expression) for explicit,
// warning-free, intentional conversions.

#include <iostream>

// This function takes a double, showing implicit conversion from int
void printDouble(double d)
{
    std::cout << "printDouble received: " << d << '\n';
}

int main()
{
    std::cout << "=== Type Conversion and static_cast ===\n\n";

    // --- Implicit (safe) conversions ---
    std::cout << "--- Safe implicit conversions ---\n";

    int i{5};
    double d{i}; // int -> double: safe, no data loss
    std::cout << "int 5 -> double: " << d << '\n';

    printDouble(42); // int 42 implicitly converted to double 42.0
    std::cout << '\n';

    // --- Implicit (unsafe) conversions ---
    std::cout << "--- Unsafe implicit conversions ---\n";

    double pi{3.14159};
    int truncated = pi; // double -> int: UNSAFE, drops fractional part
    // Warning: possible loss of data
    std::cout << "double 3.14159 -> int: " << truncated << " (fractional part LOST)\n";

    int big{1000};
    char narrow = big; // int -> char: UNSAFE if value doesn't fit
    std::cout << "int 1000 -> char: value may be wrong (depends on char range)\n";
    std::cout << "  result: " << static_cast<int>(narrow) << '\n';
    std::cout << '\n';

    // --- Explicit conversion with static_cast ---
    std::cout << "--- static_cast (explicit conversion) ---\n";

    double val{9.7};
    int intVal{static_cast<int>(val)}; // No warning - conversion is intentional
    std::cout << "static_cast<int>(9.7) = " << intVal << " (truncates, no warning)\n";

    // static_cast to convert char to its numeric value
    char ch{'A'};
    std::cout << "static_cast<int>('A') = " << static_cast<int>(ch) << " (ASCII value)\n";

    // static_cast for integer division workaround
    int a{7};
    int b{2};
    std::cout << "7 / 2 (int division):                    " << (a / b) << '\n';
    std::cout << "static_cast<double>(7) / 2 (real result): " << (static_cast<double>(a) / b) << '\n';
    std::cout << '\n';

    // --- Bool conversions ---
    std::cout << "--- Bool conversions ---\n";
    std::cout << std::boolalpha;
    bool fromInt{static_cast<bool>(5)};   // Non-zero -> true
    bool fromZero{static_cast<bool>(0)};  // Zero -> false
    int fromBool{static_cast<int>(true)}; // true -> 1

    std::cout << "static_cast<bool>(5):    " << fromInt << '\n';
    std::cout << "static_cast<bool>(0):    " << fromZero << '\n';
    std::cout << "static_cast<int>(true):  " << fromBool << '\n';

    return 0;
}
