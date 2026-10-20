// Chapter 16 - Project 08: Range-Based For Loops (for-each)
// ==========================================================
// Demonstrates:
//   - for (auto e : arr)       - copies each element (cheap types)
//   - for (auto& e : arr)      - mutable reference (can modify)
//   - for (const auto& e : arr) - read-only reference (best default)
//   - Reverse traversal with std::views::reverse (C++20)
//
// Key takeaway: Prefer range-based for loops over index-based loops
// when you don't need the index. They eliminate off-by-one errors
// and signed/unsigned mismatch problems entirely.
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <vector>
#include <string>
#include <ranges> // for std::views::reverse (C++20)

int main()
{
    // --- 1. auto (by value) - copies each element ---
    // Use for cheap-to-copy types (int, double, char, etc.)
    std::vector<int> numbers{10, 20, 30, 40, 50};

    std::cout << "=== auto (copy) - good for cheap types ===\n";
    for (auto n : numbers) // n is a COPY of each element
    {
        n *= 2; // modifying n does NOT affect the vector
        std::cout << n << ' ';
    }
    std::cout << '\n';
    std::cout << "Original unchanged: ";
    for (auto n : numbers)
        std::cout << n << ' ';
    std::cout << '\n';

    // --- 2. auto& (by reference) - can modify elements ---
    std::cout << "\n=== auto& (reference) - modifies elements ===\n";
    for (auto &n : numbers) // n is a REFERENCE to each element
        n *= 2;             // modifying n CHANGES the vector

    std::cout << "After doubling: ";
    for (auto n : numbers)
        std::cout << n << ' ';
    std::cout << '\n';

    // --- 3. const auto& (const reference) - read-only, no copy ---
    // Best default for expensive types (string, vector, custom classes)
    std::vector<std::string> names{"Alice", "Bob", "Charlie", "Diana"};

    std::cout << "\n=== const auto& - read-only reference ===\n";
    for (const auto &name : names) // no copy, no modification allowed
        std::cout << "Hello, " << name << "!\n";

    // --- 4. Reverse traversal with std::views::reverse (C++20) ---
    std::cout << "\n=== Reverse traversal (C++20) ===\n";
    std::cout << "Names in reverse: ";
    for (const auto &name : std::views::reverse(names))
        std::cout << name << ' ';
    std::cout << '\n';

    std::cout << "Numbers in reverse: ";
    for (const auto &n : std::views::reverse(numbers))
        std::cout << n << ' ';
    std::cout << '\n';

    // --- 5. Works with initializer lists too ---
    std::cout << "\n=== With initializer list ===\n";
    for (auto x : {1, 1, 2, 3, 5, 8, 13})
        std::cout << x << ' ';
    std::cout << " (Fibonacci)\n";

    // --- Summary ---
    std::cout << "\n=== Which auto form to use? ===\n";
    std::cout << "auto        - copies element (use for int, double, char)\n";
    std::cout << "auto&       - mutable reference (use when modifying)\n";
    std::cout << "const auto& - read-only reference (best default for strings, etc.)\n";

    return 0;
}
