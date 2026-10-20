// Chapter 8 - Project 13: Mersenne Twister Random Number Generation
// Demonstrates std::mt19937, std::uniform_int_distribution, and proper seeding.
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <random> // std::mt19937, std::random_device, std::uniform_int_distribution, std::seed_seq
#include <chrono> // For clock-based seeding example

int main()
{
    // -------------------------------------------------------
    // 1. Basic Mersenne Twister with std::random_device seed
    // -------------------------------------------------------
    std::cout << "=== 1. Basic mt19937 with random_device ===\n";

    // std::random_device provides non-deterministic random data
    // from the OS (hardware RNG, /dev/urandom, etc.)
    std::random_device rd;

    // Seed the Mersenne Twister PRNG - do this ONCE
    std::mt19937 mt{rd()};

    // Create a distribution to map raw output into [1, 6]
    std::uniform_int_distribution die6{1, 6};

    std::cout << "Rolling a d6 ten times: ";
    for (int i{0}; i < 10; ++i)
    {
        std::cout << die6(mt) << ' ';
    }
    std::cout << '\n';

    // -------------------------------------------------------
    // 2. Why seed only once?
    // -------------------------------------------------------
    // BAD - re-seeding every call produces correlated sequences:
    // for (...) {
    //     std::mt19937 mt{ rd() };  // Re-creating = re-seeding = BAD
    //     std::cout << die6(mt);
    // }
    //
    // GOOD - create mt19937 once, reuse it (as above)

    // -------------------------------------------------------
    // 3. Using std::seed_seq to reduce underseeding
    // -------------------------------------------------------
    std::cout << "\n=== 2. Better seeding with seed_seq ===\n";

    // mt19937 has 624 × 32 = 19968 bits of state, but rd() gives
    // only 32 bits. Using std::seed_seq with multiple rd() values
    // provides more entropy, reducing the underseeding problem.
    std::seed_seq ss{
        rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
    std::mt19937 betterMt{ss};

    std::uniform_int_distribution d100{1, 100};
    std::cout << "Random 1-100 (better seeded): ";
    for (int i{0}; i < 10; ++i)
    {
        std::cout << d100(betterMt) << ' ';
    }
    std::cout << '\n';

    // -------------------------------------------------------
    // 4. Different distribution ranges
    // -------------------------------------------------------
    std::cout << "\n=== 3. Different ranges ===\n";

    std::uniform_int_distribution coinFlip{0, 1};
    std::cout << "Coin flips (0=T, 1=H): ";
    for (int i{0}; i < 10; ++i)
    {
        std::cout << coinFlip(betterMt) << ' ';
    }
    std::cout << '\n';

    std::uniform_int_distribution bigRange{1000, 9999};
    std::cout << "4-digit codes: ";
    for (int i{0}; i < 5; ++i)
    {
        std::cout << bigRange(betterMt) << ' ';
    }
    std::cout << '\n';

    // -------------------------------------------------------
    // 5. Alternative: seeding from system clock (deterministic fallback)
    // -------------------------------------------------------
    std::cout << "\n=== 4. Clock-based seeding (fallback) ===\n";

    // Use this only if std::random_device is not truly random
    // on your platform (some older MinGW implementations).
    auto seed = static_cast<std::mt19937::result_type>(
        std::chrono::steady_clock::now().time_since_epoch().count());
    std::mt19937 clockMt{seed};

    std::cout << "Clock-seeded d6: ";
    for (int i{0}; i < 10; ++i)
    {
        std::cout << die6(clockMt) << ' ';
    }
    std::cout << '\n';

    // -------------------------------------------------------
    // 6. Deterministic seed for debugging / reproducibility
    // -------------------------------------------------------
    std::cout << "\n=== 5. Fixed seed (reproducible) ===\n";

    std::mt19937 debugMt{42}; // Same seed → same sequence every run
    std::cout << "Fixed-seed d6: ";
    for (int i{0}; i < 10; ++i)
    {
        std::cout << die6(debugMt) << ' ';
    }
    std::cout << '\n';

    // -------------------------------------------------------
    // Key points:
    // - Use std::mt19937 as your PRNG (good quality, fast)
    // - Seed it ONCE with std::random_device (or seed_seq for better coverage)
    // - Use std::uniform_int_distribution to get numbers in a range
    // - Never re-create/re-seed the PRNG every call
    // - Use a fixed seed when you need reproducible results
    // -------------------------------------------------------

    return 0;
}
