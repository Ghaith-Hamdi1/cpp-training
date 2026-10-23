// Chapter 7 - Project 10: Sharing Global Constants Across Files
// ===============================================================
// Three approaches to share constants across translation units:
//
// (1) constexpr in header (pre-C++17): each TU gets its own copy → wasteful
// (2) extern const in .cpp + forward declarations: single copy, but loses
//     constexpr-ness in other files (can't use in constant expressions)
// (3) inline constexpr in header (C++17+): BEST - single copy, usable in
//     constant expressions everywhere
//
// This project demonstrates approach (3) - the recommended modern way.
//
// Compile: cl /std:c++20 /EHsc main.cpp physics.cpp
//          g++ -std=c++20 main.cpp physics.cpp

#include <iostream>
#include <array>
#include "constants.h"

// Forward declaration
void physicsDemo();

int main()
{
    // -------------------------------------------------
    // 1. Using inline constexpr constants from the header
    // -------------------------------------------------
    std::cout << "1. Constants from constants.h:\n";
    std::cout << "   pi         = " << Constants::pi << '\n';
    std::cout << "   gravity    = " << Constants::gravity << '\n';
    std::cout << "   maxPlayers = " << Constants::maxPlayers << '\n';
    std::cout << "   appName    = " << Constants::appName << '\n';

    // -------------------------------------------------
    // 2. Key advantage: usable in constant expressions!
    // -------------------------------------------------
    // Because they're inline constexpr, the compiler knows their values
    // at compile time - even in other translation units.
    constexpr double circumference{2.0 * Constants::pi * 5.0}; // Compile-time!
    std::cout << "\n2. constexpr calculation: circumference of r=5 = "
              << circumference << '\n';

    // Can be used as array sizes (requires compile-time value)
    std::array<int, Constants::maxPlayers> scores{};
    std::cout << "   Array size (constexpr): " << scores.size() << '\n';

    // Can be used in static_assert
    static_assert(Constants::maxPlayers > 0, "Must have at least one player");
    static_assert(Constants::pi > 3.0, "Pi should be greater than 3");
    std::cout << "   static_assert checks passed!\n";

    // -------------------------------------------------
    // 3. Single instance - same address across files
    // -------------------------------------------------
    std::cout << "\n3. Address of Constants::pi in main.cpp:    " << &Constants::pi << '\n';

    // -------------------------------------------------
    // 4. Used from another file (physics.cpp)
    // -------------------------------------------------
    std::cout << "\n4. Using same constants in physics.cpp:\n";
    physicsDemo();

    // -------------------------------------------------
    // 5. Comparison of the three approaches
    // -------------------------------------------------
    std::cout << "\n--- Three Approaches Compared ---\n";
    std::cout << "  (1) constexpr in header (pre-C++17):\n";
    std::cout << "      + Works, compile-time values\n";
    std::cout << "      - Each .cpp gets its own COPY (wastes memory)\n\n";

    std::cout << "  (2) extern const in .cpp + forward declarations:\n";
    std::cout << "      + Single copy in memory\n";
    std::cout << "      - NOT constexpr in other files (can't use in const expressions)\n\n";

    std::cout << "  (3) inline constexpr in header (C++17+): << BEST >>\n";
    std::cout << "      + Single copy (inline deduplication)\n";
    std::cout << "      + Constexpr everywhere (full compile-time evaluation)\n";

    return 0;
}
