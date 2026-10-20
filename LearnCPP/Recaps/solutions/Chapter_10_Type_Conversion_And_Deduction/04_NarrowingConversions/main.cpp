// Chapter 10 - Project 04: Narrowing Conversions and Brace Initialization
//
// A narrowing conversion is one where the destination type may not be able
// to hold all values of the source type.
//
// KEY RULE: Brace initialization {} DISALLOWS narrowing conversions,
// producing a compile error. This is a major reason to prefer brace init.
//
// EXCEPTION: If the source value is constexpr and fits in the destination,
// the conversion is NOT considered narrowing (except float-to-int, which
// is ALWAYS narrowing even with constexpr).
//
// To make an intentional narrowing conversion explicit, use static_cast.

#include <iostream>

int main()
{
    // =============================================================
    // 1. Brace init catches narrowing - compile errors if uncommented
    // =============================================================
    std::cout << "=== Brace init catches narrowing conversions ===\n";

    // ERROR: double -> int is narrowing (fractional part may be lost)
    // int a{ 3.5 };             // Won't compile!

    // ERROR: int -> char might lose data (int range > char range)
    // char c{ 500 };            // Won't compile! 500 doesn't fit in char

    // ERROR: double -> float might lose precision
    // float f{ 1.23456789012345 }; // Won't compile!

    std::cout << "  (Uncomment the lines above to see compile errors)\n";

    // =============================================================
    // 2. Constexpr exemption: value known at compile time and fits
    // =============================================================
    std::cout << "\n=== Constexpr exemption ===\n";

    // constexpr int fits in char (65 is within char range) - OK
    constexpr int letterA{65};
    char c2{letterA}; // OK: constexpr value fits in char
    std::cout << "  constexpr int 65 -> char: '" << c2 << "'\n";

    // constexpr double with no fractional part -> float - OK
    constexpr double exactVal{2.5};
    float f2{exactVal}; // OK: 2.5 is exactly representable as float
    std::cout << "  constexpr double 2.5 -> float: " << f2 << '\n';

    // constexpr int -> short, value fits - OK
    constexpr int small{100};
    short s{small}; // OK: 100 fits in short
    std::cout << "  constexpr int 100 -> short: " << s << '\n';

    // =============================================================
    // 3. Float-to-int is ALWAYS narrowing, even with constexpr
    // =============================================================
    std::cout << "\n=== Float-to-int is always narrowing ===\n";

    // Even though 3.0 has no fractional part, float-to-int is always narrowing
    // int bad{ 3.0 };           // Won't compile! float-to-int always narrowing

    // Use static_cast to make the intent explicit
    int fromDouble{static_cast<int>(3.0)};
    std::cout << "  static_cast<int>(3.0) = " << fromDouble << '\n';

    // =============================================================
    // 4. Using static_cast for intentional narrowing
    // =============================================================
    std::cout << "\n=== Intentional narrowing with static_cast ===\n";

    double pi{3.14159};

    // This would be an error with brace init:
    // int iPi{ pi };            // Won't compile!

    // Use static_cast to explicitly request the conversion
    int iPi{static_cast<int>(pi)};
    std::cout << "  static_cast<int>(3.14159) = " << iPi << '\n';

    int bigVal{1000};
    // char is too small for 1000, but we explicitly want the conversion
    char truncated{static_cast<char>(bigVal)};
    std::cout << "  static_cast<char>(1000) = " << static_cast<int>(truncated)
              << " (truncated/wrapped)\n";

    // =============================================================
    // 5. Copy init does NOT catch narrowing (another reason to avoid it)
    // =============================================================
    std::cout << "\n=== Copy init allows narrowing (dangerous!) ===\n";

    int dangerous = 3.9; // Compiles! Silently truncates to 3
    std::cout << "  int dangerous = 3.9 -> " << dangerous << " (silently truncated!)\n";

    return 0;
}
