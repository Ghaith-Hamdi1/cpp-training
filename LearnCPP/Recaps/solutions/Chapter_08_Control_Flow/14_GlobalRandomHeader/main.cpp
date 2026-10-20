// Chapter 8 - Project 14: Global Random Header (Random.h pattern)
// Demonstrates a reusable header-only Random namespace for project-wide RNG.
// Compile: g++ -std=c++20 -o main main.cpp
//
// This project includes two files:
//   Random.h  - the reusable header
//   main.cpp  - demo program using Random::get()

// =====================================================================
// NOTE: Random.h is in this same folder. See Random.h for implementation.
// =====================================================================

#include "Random.h" // Our reusable random header
#include <iostream>

int main()
{
    // -------------------------------------------------------
    // 1. Simple usage - no setup required
    // -------------------------------------------------------
    std::cout << "=== 1. Random::get(min, max) ===\n";
    std::cout << "Random d6 rolls: ";
    for (int i{0}; i < 10; ++i)
    {
        std::cout << Random::get(1, 6) << ' ';
    }
    std::cout << '\n';

    // -------------------------------------------------------
    // 2. Different ranges
    // -------------------------------------------------------
    std::cout << "\n=== 2. Various ranges ===\n";
    std::cout << "Coin (0-1): " << Random::get(0, 1) << '\n';
    std::cout << "d20:        " << Random::get(1, 20) << '\n';
    std::cout << "Percentage: " << Random::get(1, 100) << '\n';
    std::cout << "Big range:  " << Random::get(1000, 9999) << '\n';

    // -------------------------------------------------------
    // 3. Using in a game-like scenario
    // -------------------------------------------------------
    std::cout << "\n=== 3. Simple game simulation ===\n";

    int playerHP{100};
    int turns{0};

    while (playerHP > 0)
    {
        int damage{Random::get(5, 25)};
        playerHP -= damage;
        ++turns;
        std::cout << "Turn " << turns << ": took " << damage
                  << " damage, HP = " << (playerHP > 0 ? playerHP : 0) << '\n';
    }
    std::cout << "Player defeated after " << turns << " turns.\n";

    // -------------------------------------------------------
    // 4. Advantages of the Random.h approach
    // -------------------------------------------------------
    // - No setup: just #include "Random.h" and call Random::get()
    // - Single PRNG instance: avoids per-function re-seeding
    // - Properly seeded: uses seed_seq with multiple random_device values
    // - Thread-safe initialization (inline variable, initialized once)
    // - No need to pass mt19937 around as a parameter

    // -------------------------------------------------------
    // Key points:
    // - Wrap a global inline std::mt19937 in a namespace
    // - Self-seed once with std::seed_seq + std::random_device
    // - Provide a simple get(min, max) API
    // - Any file can #include "Random.h" and generate random numbers
    // -------------------------------------------------------

    return 0;
}
