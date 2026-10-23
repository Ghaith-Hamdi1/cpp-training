// physics.cpp - Uses the same inline constexpr constants from another file

#include <iostream>
#include <array>
#include "constants.h"

void physicsDemo()
{
    // Same constants, same values, same addresses as in main.cpp
    constexpr double fallDistance{0.5 * Constants::gravity * 3.0 * 3.0};
    std::cout << "   Free-fall distance after 3s = " << fallDistance << " m\n";

    // Compile-time array - proves constexpr works across files
    std::array<int, Constants::defaultLives> lives{};
    std::cout << "   Default lives array size    = " << lives.size() << '\n';

    // Verify same address (single instance due to 'inline')
    std::cout << "   Address of Constants::pi in physics.cpp: " << &Constants::pi << '\n';
}
