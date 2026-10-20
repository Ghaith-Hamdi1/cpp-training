// Chapter 13 - Project 03: Converting an Enumeration To and From a String
// Demonstrates: enum-to-string via switch, string-to-enum with std::optional,
//               and using std::string_view for zero-cost string returns.

#include <iostream>
#include <optional>    // std::optional
#include <string>      // std::string
#include <string_view> // std::string_view

enum Color
{
    red,
    green,
    blue,
    maxColors, // handy for knowing the count of enumerators
};

// ============================================================================
// 1. Enum -> String (using switch + string_view)
// ============================================================================
// Returns a string_view (no allocation) corresponding to the enumerator.
// Best practice: return std::string_view from enum-to-string functions.
constexpr std::string_view colorToString(Color c)
{
    switch (c)
    {
    case red:
        return "red";
    case green:
        return "green";
    case blue:
        return "blue";
    default:
        return "unknown";
    }
}

// ============================================================================
// 2. String -> Enum (returning std::optional for safety)
// ============================================================================
// std::optional lets us signal "no valid conversion" without using a sentinel
// value or throwing an exception.
std::optional<Color> stringToColor(std::string_view str)
{
    if (str == "red")
        return red;
    if (str == "green")
        return green;
    if (str == "blue")
        return blue;
    return std::nullopt; // no matching enumerator
}

int main()
{
    // --- Enum to string ---
    std::cout << "=== Enum to String ===\n";
    Color c{green};
    std::cout << "Color value " << c << " is \"" << colorToString(c) << "\"\n";

    for (int i{0}; i < maxColors; ++i)
    {
        Color col{static_cast<Color>(i)};
        std::cout << "  " << i << " -> " << colorToString(col) << '\n';
    }

    // --- String to enum ---
    std::cout << "\n=== String to Enum ===\n";

    auto tryConvert = [](std::string_view name)
    {
        std::optional<Color> result{stringToColor(name)};
        if (result)
            std::cout << "  \"" << name << "\" -> " << colorToString(*result)
                      << " (value " << *result << ")\n";
        else
            std::cout << "  \"" << name << "\" -> invalid color!\n";
    };

    tryConvert("red");
    tryConvert("blue");
    tryConvert("purple"); // not a valid color

    return 0;
}
