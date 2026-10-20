// Chapter 10 - Project 03: Numeric Conversions
//
// Numeric conversions are all fundamental type conversions that are NOT
// promotions. They fall into three safety categories:
//
//   1. Value-preserving: always safe, destination can hold all source values
//      Example: int -> long, int -> double
//
//   2. Reinterpretive: value may change meaning but no data is lost
//      Example: signed int -> unsigned int (bit pattern reinterpreted)
//
//   3. Lossy: data may be permanently lost
//      Example: double -> int (fractional part truncated)
//              double -> float (precision may be lost)

#include <iostream>
#include <iomanip>

int main()
{
    std::cout << std::fixed << std::setprecision(6);

    // =============================================================
    // 1. VALUE-PRESERVING conversions (always safe)
    // =============================================================
    std::cout << "=== Value-preserving conversions ===\n";

    int i{42};
    long l{i}; // int -> long: safe, all int values fit in long
    std::cout << "  int " << i << " -> long " << l << '\n';

    int i2{100};
    double d{i2}; // int -> double: safe (for reasonable int values)
    std::cout << "  int " << i2 << " -> double " << d << '\n';

    // =============================================================
    // 2. REINTERPRETIVE conversions (value may change)
    // =============================================================
    std::cout << "\n=== Reinterpretive conversions ===\n";

    // Signed -> unsigned: the bit pattern is preserved, but the
    // interpretation changes. Negative values wrap around.
    int negative{-1};
    unsigned int u{static_cast<unsigned int>(negative)};
    std::cout << "  signed int " << negative << " -> unsigned int " << u << '\n';
    // -1 wraps to the maximum unsigned int value (4294967295 on 32-bit)

    unsigned int big{4000000000u};
    int s{static_cast<int>(big)}; // unsigned -> signed: may wrap
    std::cout << "  unsigned " << big << " -> signed int " << s << '\n';

    // =============================================================
    // 3. LOSSY conversions (data may be permanently lost)
    // =============================================================
    std::cout << "\n=== Lossy conversions ===\n";

    // double -> int: fractional part is TRUNCATED (not rounded)
    double pi{3.14159};
    int truncated{static_cast<int>(pi)};
    std::cout << "  double " << pi << " -> int " << truncated
              << " (fractional part lost!)\n";

    // double -> float: precision may be lost
    double precise{1.23456789012345};
    float lessAccurate{static_cast<float>(precise)};
    std::cout << "  double " << precise << " -> float "
              << lessAccurate << " (precision lost)\n";

    // Large int -> float: not all large integers are representable in float
    int largeInt{16777217}; // 2^24 + 1, not exactly representable as float
    float fLarge{static_cast<float>(largeInt)};
    std::cout << "  int " << largeInt << " -> float " << fLarge
              << " (value changed due to precision)\n";

    // =============================================================
    // Anything -> bool
    // =============================================================
    std::cout << "\n=== Conversions to bool ===\n";
    std::cout << std::boolalpha;

    // Zero values convert to false, non-zero to true
    std::cout << "  int 0 -> bool: " << static_cast<bool>(0) << '\n';
    std::cout << "  int 5 -> bool: " << static_cast<bool>(5) << '\n';
    std::cout << "  double 0.0 -> bool: " << static_cast<bool>(0.0) << '\n';
    std::cout << "  double 0.1 -> bool: " << static_cast<bool>(0.1) << '\n';

    return 0;
}
