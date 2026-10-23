// constants.h - Global constants using inline constexpr (C++17+ best practice)
// ==============================================================================
// 'inline constexpr' in a header gives you the best of both worlds:
//   - Single copy in the program (inline → linker deduplicates)
//   - Usable in constant expressions in every file that includes this header

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string_view>

namespace Constants
{
    inline constexpr double pi{3.14159265358979};
    inline constexpr double gravity{9.81};               // m/s^2
    inline constexpr double speedOfLight{299'792'458.0}; // m/s
    inline constexpr int maxPlayers{4};
    inline constexpr int defaultLives{3};

    // string_view is already constexpr-friendly
    inline constexpr std::string_view appName{"PhysicsEngine v1.0"};
}

#endif
