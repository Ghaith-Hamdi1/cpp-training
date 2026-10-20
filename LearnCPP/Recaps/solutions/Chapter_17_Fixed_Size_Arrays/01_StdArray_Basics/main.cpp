// Chapter 17 - Project 01: std::array Basics
// Topics: declaration, aggregate initialization, value-init, constexpr, CTAD
// Compile: g++ -std=c++20 -Wall -Wextra -o program main.cpp

#include <array>
#include <iostream>

int main()
{
    // -----------------------------------------------------------------------
    // 1. Basic declaration - element type and compile-time length are required
    // -----------------------------------------------------------------------
    std::array<int, 5> nums{10, 20, 30, 40, 50};

    std::cout << "--- 1. Basic declaration ---\n";
    for (int n : nums)
        std::cout << n << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 2. Value-initialization with {} - all elements become zero / default
    //    PITFALL: omitting {} leaves elements uninitialized (undefined values)
    // -----------------------------------------------------------------------
    std::array<int, 4> zeros{};       // all elements are 0
    std::array<double, 3> dblZeros{}; // all elements are 0.0

    std::cout << "\n--- 2. Value-init (all zeros) ---\n";
    for (int z : zeros)
        std::cout << z << ' ';
    std::cout << '\n';
    for (double d : dblZeros)
        std::cout << d << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 3. Partial initialization - remaining elements are value-initialized
    // -----------------------------------------------------------------------
    std::array<int, 5> partial{1, 2}; // {1, 2, 0, 0, 0}

    std::cout << "\n--- 3. Partial init ---\n";
    for (int p : partial)
        std::cout << p << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 4. constexpr arrays - fully usable at compile time
    // -----------------------------------------------------------------------
    constexpr std::array<int, 3> primes{2, 3, 5};

    static_assert(primes[0] == 2, "First prime must be 2");
    static_assert(primes.size() == 3, "Must have 3 primes");

    std::cout << "\n--- 4. constexpr array ---\n";
    for (int p : primes)
        std::cout << p << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 5. CTAD (C++17) - compiler deduces type and length from initializers
    //    std::array  arr{ 1, 2, 3 };  =>  std::array<int, 3>
    // -----------------------------------------------------------------------
    std::array doubles{1.1, 2.2, 3.3}; // deduced as std::array<double, 3>

    std::cout << "\n--- 5. CTAD ---\n";
    std::cout << "Size deduced: " << doubles.size() << '\n';
    for (double d : doubles)
        std::cout << d << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 6. const vs constexpr
    //    - const: elements cannot be modified after initialization (runtime OK)
    //    - constexpr: value must be known at compile time
    // -----------------------------------------------------------------------
    const std::array<int, 3> constArr{4, 5, 6};
    // constArr[0] = 99;  // ERROR: const array

    std::cout << "\n--- 6. const array ---\n";
    for (int c : constArr)
        std::cout << c << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // KEY TAKEAWAY:
    //   Use std::array for fixed-size, compile-time-known arrays.
    //   Always value-initialize with {} when not providing explicit values.
    //   Use CTAD to reduce verbosity.
    // -----------------------------------------------------------------------

    return 0;
}
