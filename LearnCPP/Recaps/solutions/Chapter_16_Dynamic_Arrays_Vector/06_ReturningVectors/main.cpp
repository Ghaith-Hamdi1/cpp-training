// Chapter 16 - Project 06: Returning std::vector and Move Semantics
// ==================================================================
// Demonstrates:
//   - Returning std::vector by value is efficient (move semantics)
//   - Move vs copy: copy duplicates data, move transfers ownership
//   - The compiler uses move (or NRVO) automatically for returns
//
// Key rule: Pass by const reference, return by VALUE.
// DO NOT return by reference (dangling reference to local variable!).
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <vector>
#include <string>

// --- 1. Return by value - efficient thanks to move semantics ---
// The local vector is an rvalue at the return site, so its data
// ownership is MOVED (not copied) into the caller's variable.
std::vector<int> generateSquares(int count)
{
    std::vector<int> result;
    result.reserve(count); // pre-allocate to avoid reallocations

    for (int i{1}; i <= count; ++i)
        result.push_back(i * i);

    return result; // moved (or NRVO-elided), NOT copied
}

// --- 2. Another example: returning a filtered vector ---
std::vector<int> filterEvens(const std::vector<int> &input)
{
    std::vector<int> evens;
    for (const auto &val : input)
    {
        if (val % 2 == 0)
            evens.push_back(val);
    }
    return evens; // moved to the caller
}

// --- 3. Returning a vector of strings ---
std::vector<std::string> getDaysOfWeek()
{
    return {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    // Directly returns an initializer list - constructs in place
}

// *** BAD EXAMPLE - DO NOT DO THIS ***
// Returning by reference to a local variable creates a dangling reference!
// const std::vector<int>& badReturn()
// {
//     std::vector<int> local{ 1, 2, 3 };
//     return local;  // ERROR: local is destroyed, reference dangles
// }

int main()
{
    // Receive the returned vector - move semantics kicks in
    std::cout << "=== Return by value (move semantics) ===\n";
    std::vector<int> squares = generateSquares(6);
    std::cout << "Squares: ";
    for (const auto &s : squares)
        std::cout << s << ' ';
    std::cout << '\n';

    // Filter example
    std::cout << "\n=== Returning filtered vector ===\n";
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> evens = filterEvens(numbers);
    std::cout << "Even numbers: ";
    for (const auto &e : evens)
        std::cout << e << ' ';
    std::cout << '\n';

    // Direct use of returned vector
    std::cout << "\n=== Direct use of returned vector ===\n";
    std::cout << "Days: ";
    for (const auto &day : getDaysOfWeek())
        std::cout << day << ' ';
    std::cout << '\n';

    // --- Summary ---
    std::cout << "\n=== Summary ===\n";
    std::cout << "- Return std::vector by VALUE (move/NRVO makes it cheap)\n";
    std::cout << "- NEVER return by reference to a local vector\n";
    std::cout << "- Move transfers ownership: no data is copied\n";

    return 0;
}
