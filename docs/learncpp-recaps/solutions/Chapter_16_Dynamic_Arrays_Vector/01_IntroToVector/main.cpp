// Chapter 16 - Project 01: Introduction to std::vector
// =====================================================
// Demonstrates basic std::vector declaration, initialization,
// element access, and Class Template Argument Deduction (CTAD).
//
// Key points:
//   - std::vector is a dynamic array defined in <vector>
//   - Elements are stored contiguously in memory
//   - List initialization uses { } to provide initial values
//   - CTAD (C++17) lets the compiler deduce the element type
//   - operator[] accesses elements by zero-based index
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <vector>
#include <string>

int main()
{
    // --- 1. Explicit type declaration with list initialization ---
    std::vector<int> primes{2, 3, 5, 7, 11};

    std::cout << "=== Explicit type: std::vector<int> ===\n";
    std::cout << "First prime : " << primes[0] << '\n'; // 2
    std::cout << "Third prime : " << primes[2] << '\n'; // 5
    std::cout << "Number of primes: " << primes.size() << '\n';

    // --- 2. CTAD - compiler deduces std::vector<double> ---
    std::vector temperatures{36.5, 37.0, 38.2, 39.1};

    std::cout << "\n=== CTAD: deduced std::vector<double> ===\n";
    for (std::size_t i{0}; i < temperatures.size(); ++i)
        std::cout << "  temp[" << i << "] = " << temperatures[i] << '\n';

    // --- 3. Vector of strings ---
    std::vector<std::string> colors{"red", "green", "blue"};

    std::cout << "\n=== std::vector<std::string> ===\n";
    for (std::size_t i{0}; i < colors.size(); ++i)
        std::cout << "  colors[" << i << "] = " << colors[i] << '\n';

    // --- 4. Modifying elements through operator[] ---
    colors[1] = "yellow"; // change "green" to "yellow"
    std::cout << "\nAfter modifying colors[1]:\n";
    std::cout << "  colors[1] = " << colors[1] << '\n';

    // --- 5. Empty vector -  starts with size 0 ---
    std::vector<int> empty{};
    std::cout << "\nEmpty vector size: " << empty.size() << '\n';

    return 0;
}
