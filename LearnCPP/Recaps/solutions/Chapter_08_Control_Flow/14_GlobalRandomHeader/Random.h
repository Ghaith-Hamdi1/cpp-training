// Random.h - Reusable header-only random number generator
// Based on the learncpp.com Chapter 8.15 pattern.
//
// Usage:
//   #include "Random.h"
//   int value = Random::get(1, 6);  // Random int in [1, 6]

#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace Random
{
    // inline ensures only one instance across all translation units.
    // The PRNG is seeded once at program startup.
    inline std::mt19937 generate()
    {
        std::random_device rd{};

        // Use seed_seq with 8 values from random_device to reduce
        // the underseeding problem (mt19937 has 19968 bits of state).
        std::seed_seq ss{
            rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};

        return std::mt19937{ss};
    }

    // Global Mersenne Twister instance - initialized once
    inline std::mt19937 mt{generate()};

    // Returns a random int in the closed range [min, max]
    inline int get(int min, int max)
    {
        return std::uniform_int_distribution{min, max}(mt);
    }

} // namespace Random

#endif // RANDOM_H
