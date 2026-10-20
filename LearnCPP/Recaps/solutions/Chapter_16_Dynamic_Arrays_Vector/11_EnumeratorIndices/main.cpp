// Chapter 16 - Project 11: Array Indexing with Enumerators
// =========================================================
// Demonstrates:
//   - Using unscoped enumerators as meaningful array indices
//   - A count enumerator at the end for automatic size tracking
//   - Assertions to validate array size matches enum count
//   - Scoped enum (enum class) with helper for indexing
//
// This makes array indexing self-documenting:
//   scores[Students::alice] instead of scores[0]
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

// --- 1. Unscoped enum for meaningful indices ---
// The enumerator names document what each index means.
namespace Students
{
    enum Names : unsigned
    {
        alice,       // 0
        bob,         // 1
        charlie,     // 2
        diana,       // 3
        max_students // 4 - equals the count of students above
    };
}

// --- 2. Scoped enum (enum class) - requires a cast or helper ---
enum class Color
{
    red,
    green,
    blue,
    max_colors
};

// Helper: convert a scoped enum to its underlying type for indexing
constexpr auto toIndex(Color c)
{
    return static_cast<std::underlying_type_t<Color>>(c);
}

int main()
{
    // --- 1. Using unscoped enum as indices ---
    std::cout << "=== Unscoped enum indices ===\n";

    // Create a vector with exactly the right number of elements
    std::vector<int> scores(Students::max_students);
    assert(scores.size() == Students::max_students); // validate size

    // Self-documenting access
    scores[Students::alice] = 95;
    scores[Students::bob] = 87;
    scores[Students::charlie] = 72;
    scores[Students::diana] = 91;

    // The names make the code readable
    std::cout << "Alice's score:   " << scores[Students::alice] << '\n';
    std::cout << "Bob's score:     " << scores[Students::bob] << '\n';
    std::cout << "Charlie's score: " << scores[Students::charlie] << '\n';
    std::cout << "Diana's score:   " << scores[Students::diana] << '\n';

    // --- 2. Iterating with enum ---
    std::cout << "\n=== Iterating with enum ===\n";
    const char *studentNames[]{"Alice", "Bob", "Charlie", "Diana"};
    for (unsigned i{0}; i < Students::max_students; ++i)
        std::cout << studentNames[i] << ": " << scores[i] << '\n';

    // --- 3. Scoped enum with helper function ---
    std::cout << "\n=== Scoped enum (enum class) ===\n";
    std::vector<std::string> colorNames(toIndex(Color::max_colors));

    colorNames[toIndex(Color::red)] = "Red";
    colorNames[toIndex(Color::green)] = "Green";
    colorNames[toIndex(Color::blue)] = "Blue";

    for (std::size_t i{0}; i < colorNames.size(); ++i)
        std::cout << "Color " << i << ": " << colorNames[i] << '\n';

    // --- 4. Why this pattern is useful ---
    std::cout << "\n=== Benefits ===\n";
    std::cout << "- scores[Students::alice] is self-documenting\n";
    std::cout << "- scores[0] tells you nothing about what index 0 means\n";
    std::cout << "- max_students automatically stays correct if you add/remove names\n";
    std::cout << "- assert() catches size mismatches at runtime in debug builds\n";

    return 0;
}
