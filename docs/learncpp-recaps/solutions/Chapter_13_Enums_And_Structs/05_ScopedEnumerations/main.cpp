// Chapter 13 - Project 05: Scoped Enumerations (enum class)
// Demonstrates: enum class syntax, scope resolution, no implicit int
//               conversion, static_cast, using enum (C++20), and
//               specifying underlying type.

#include <iostream>
#include <string_view>
#include <type_traits> // std::to_underlying (C++23) - shown as static_cast fallback

// ============================================================================
// 1. Scoped enum basics
// ============================================================================
// 'enum class' keeps enumerators inside the enum's own scope.
// No implicit conversion to int - much safer than unscoped enums.
enum class Color
{
    red,
    green,
    blue,
};

// Because enumerators are scoped, we can reuse the same names:
enum class TrafficLight
{
    red,
    yellow,
    green,
};
// No collision! Color::red and TrafficLight::red are completely separate.

// ============================================================================
// 2. Specifying an underlying type
// ============================================================================
// By default the underlying type is int, but you can change it:
enum class SmallEnum : std::uint8_t
{
    a,
    b,
    c,
};

// ============================================================================
// 3. Enum-to-string helper
// ============================================================================
constexpr std::string_view colorToString(Color c)
{
    switch (c)
    {
    case Color::red:
        return "red";
    case Color::green:
        return "green";
    case Color::blue:
        return "blue";
    default:
        return "unknown";
    }
}

// operator<< overload for Color
std::ostream &operator<<(std::ostream &out, Color c)
{
    out << colorToString(c);
    return out;
}

// ============================================================================
// 4. Using 'using enum' (C++20) to reduce prefix verbosity
// ============================================================================
constexpr std::string_view lightToString(TrafficLight tl)
{
    using enum TrafficLight; // C++20: import all enumerators into this scope
    switch (tl)
    {
    case red:
        return "red"; // no TrafficLight:: prefix needed
    case yellow:
        return "yellow";
    case green:
        return "green";
    default:
        return "unknown";
    }
}

int main()
{
    // --- Scoped access ---
    std::cout << "=== Scoped Enumerations ===\n";
    Color c{Color::blue};
    // std::cout << c;  // would fail without operator<< overload
    std::cout << "Color: " << c << '\n'; // uses our overload

    // --- No implicit int conversion ---
    std::cout << "\n=== No Implicit Int Conversion ===\n";
    // int val = c;                // ERROR: no implicit conversion
    int val = static_cast<int>(c);                      // OK: explicit cast
    std::cout << "Color::blue as int: " << val << '\n'; // 2

    // C++23 offers std::to_underlying() for the same purpose:
    // auto val2 = std::to_underlying(c); // returns the underlying int value

    // --- No naming collisions ---
    std::cout << "\n=== No Naming Collisions ===\n";
    TrafficLight tl{TrafficLight::red};
    std::cout << "Traffic light: " << lightToString(tl) << '\n';
    std::cout << "Color: " << Color::red << '\n'; // different type, same name

    // --- Underlying type ---
    std::cout << "\n=== Custom Underlying Type ===\n";
    std::cout << "sizeof(Color):     " << sizeof(Color) << " bytes\n";
    std::cout << "sizeof(SmallEnum): " << sizeof(SmallEnum) << " byte\n";

    // --- using enum in a local scope ---
    std::cout << "\n=== 'using enum' (C++20) ===\n";
    {
        using enum Color; // import Color enumerators into this block
        Color c2{green};  // no Color:: prefix needed
        std::cout << "c2 = " << c2 << '\n';
    }
    // 'green' is no longer accessible without Color:: prefix here.

    return 0;
}
