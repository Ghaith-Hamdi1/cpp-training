// Chapter 17 - Project 06: std::array and Enumerations
// Topics: enum-to-string mapping, static_assert validation, iterating enums
// Compile: g++ -std=c++20 -Wall -Wextra -o program main.cpp

#include <array>
#include <iostream>
#include <string_view>
#include <cstddef> // std::size_t

// -----------------------------------------------------------------------
// Define an enum class with a "count" enumerator at the end.
// This lets us validate that our parallel array has the correct size.
// -----------------------------------------------------------------------
enum class Color
{
    red,
    green,
    blue,
    yellow,
    max_colors // must be last - gives the count of actual colors
};

// -----------------------------------------------------------------------
// 1. Enum-to-string mapping using a constexpr array
//    The array index matches the enumerator's underlying value.
//    static_assert ensures we update the array when adding new colors.
// -----------------------------------------------------------------------
constexpr std::array colorNames{
    std::string_view{"Red"},
    std::string_view{"Green"},
    std::string_view{"Blue"},
    std::string_view{"Yellow"}};

// Validate that the array has exactly the right number of entries
static_assert(colorNames.size() == static_cast<std::size_t>(Color::max_colors),
              "colorNames array size must match Color::max_colors");

// Helper to convert Color -> string_view
constexpr std::string_view getColorName(Color c)
{
    return colorNames[static_cast<std::size_t>(c)];
}

// -----------------------------------------------------------------------
// 2. A constexpr array of enumerator VALUES for range-based for loops
//    Enums don't natively support iteration, so we list them explicitly.
// -----------------------------------------------------------------------
constexpr std::array allColors{
    Color::red,
    Color::green,
    Color::blue,
    Color::yellow};

static_assert(allColors.size() == static_cast<std::size_t>(Color::max_colors));

// -----------------------------------------------------------------------
// Another enum example: Days of the week
// -----------------------------------------------------------------------
enum class Day
{
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday,
    max_days
};

constexpr std::array dayNames{
    std::string_view{"Monday"},
    std::string_view{"Tuesday"},
    std::string_view{"Wednesday"},
    std::string_view{"Thursday"},
    std::string_view{"Friday"},
    std::string_view{"Saturday"},
    std::string_view{"Sunday"}};

static_assert(dayNames.size() == static_cast<std::size_t>(Day::max_days),
              "dayNames size must match Day::max_days");

constexpr std::array allDays{
    Day::monday, Day::tuesday, Day::wednesday,
    Day::thursday, Day::friday, Day::saturday, Day::sunday};

static_assert(allDays.size() == static_cast<std::size_t>(Day::max_days));

int main()
{
    // --- 1. Convert enum to string ---
    std::cout << "--- 1. Enum to string ---\n";
    std::cout << "Color::blue  => " << getColorName(Color::blue) << '\n';
    std::cout << "Color::red   => " << getColorName(Color::red) << '\n';

    // --- 2. Iterate over all colors ---
    std::cout << "\n--- 2. Iterate all colors ---\n";
    for (Color c : allColors)
        std::cout << "  " << getColorName(c) << '\n';

    // --- 3. Iterate over days ---
    std::cout << "\n--- 3. Iterate all days ---\n";
    for (Day d : allDays)
        std::cout << "  " << dayNames[static_cast<std::size_t>(d)] << '\n';

    // --- 4. Using enum as array index directly ---
    std::cout << "\n--- 4. Enum as array index ---\n";

    // Scores per color
    std::array<int, static_cast<std::size_t>(Color::max_colors)> scores{};
    scores[static_cast<std::size_t>(Color::red)] = 100;
    scores[static_cast<std::size_t>(Color::green)] = 85;
    scores[static_cast<std::size_t>(Color::blue)] = 92;
    scores[static_cast<std::size_t>(Color::yellow)] = 77;

    for (Color c : allColors)
    {
        auto idx = static_cast<std::size_t>(c);
        std::cout << "  " << getColorName(c) << ": " << scores[idx] << '\n';
    }

    // -----------------------------------------------------------------------
    // KEY TAKEAWAY:
    //   Pair constexpr arrays with enums for clean mappings.
    //   Use static_assert to ensure array sizes match enum counts.
    //   A constexpr array of enumerators enables range-based for over enums.
    // -----------------------------------------------------------------------

    return 0;
}
