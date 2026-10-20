// Chapter 4 - Project 04: Signed Integers
// =========================================
// Key concept: C++ has 4 signed integer types with minimum sizes:
//   short     - at least 16 bits (-32,768 to 32,767)
//   int       - at least 16 bits (usually 32 bits on modern systems)
//   long      - at least 32 bits
//   long long - at least 64 bits
//
// CRITICAL: Signed integer overflow is UNDEFINED BEHAVIOR.
// Integer division truncates (drops the fractional part, does NOT round).

#include <climits> // For INT_MIN, INT_MAX, etc.
#include <iostream>

int main()
{
    std::cout << "=== Signed Integers ===\n\n";

    // Ranges of signed integer types (from <climits>)
    std::cout << "--- Ranges of signed integer types ---\n";
    std::cout << "short:     " << SHRT_MIN << " to " << SHRT_MAX << '\n';
    std::cout << "int:       " << INT_MIN << " to " << INT_MAX << '\n';
    std::cout << "long:      " << LONG_MIN << " to " << LONG_MAX << '\n';
    std::cout << "long long: " << LLONG_MIN << " to " << LLONG_MAX << '\n';

    std::cout << '\n';

    // Integer division truncates - it drops the fractional part
    std::cout << "--- Integer division truncation ---\n";
    std::cout << "7  / 4  = " << (7 / 4) << " (expected 1.75, got 1 - truncated)\n";
    std::cout << "-7 / 4  = " << (-7 / 4) << " (expected -1.75, got -1 - truncated toward zero)\n";
    std::cout << "5  / 3  = " << (5 / 3) << " (expected 1.67, got 1)\n";
    std::cout << "1  / 2  = " << (1 / 2) << " (expected 0.5, got 0)\n";

    std::cout << '\n';

    // Demonstrating that both operands must be integers for integer division
    std::cout << "--- Getting fractional results ---\n";
    std::cout << "7.0 / 4  = " << (7.0 / 4) << " (one operand is double -> double division)\n";
    std::cout << "static_cast<double>(7) / 4 = " << (static_cast<double>(7) / 4) << '\n';

    std::cout << '\n';

    // Signed integer overflow is UNDEFINED BEHAVIOR
    std::cout << "--- Signed integer overflow (UNDEFINED BEHAVIOR) ---\n";
    std::cout << "INT_MAX = " << INT_MAX << '\n';
    // Uncomment the following to see undefined behavior (DON'T rely on the result):
    // int overflow = INT_MAX + 1; // UB! Might wrap, crash, or do anything
    // std::cout << "INT_MAX + 1 = " << overflow << " (UNDEFINED - unreliable!)\n";
    std::cout << "Adding 1 to INT_MAX is undefined behavior - the program may\n";
    std::cout << "crash, produce garbage, or appear to work. Never rely on it.\n";

    return 0;
}
