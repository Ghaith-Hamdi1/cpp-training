// Chapter 8 - Project 05: Switch Statement Basics
// Demonstrates switch/case/default for integral and enum testing.
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <string_view>

// -------------------------------------------------------
// 1. Enum with switch - the ideal use case
// -------------------------------------------------------
enum class Color
{
    red,
    green,
    blue,
    yellow
};

std::string_view colorToString(Color c)
{
    switch (c)
    {
    case Color::red:
        return "Red";
    case Color::green:
        return "Green";
    case Color::blue:
        return "Blue";
    case Color::yellow:
        return "Yellow";
    default:
        return "Unknown";
    }
}

// -------------------------------------------------------
// 2. Integer switch - day of the week
// -------------------------------------------------------
std::string_view dayName(int day)
{
    switch (day)
    {
    case 1:
        return "Monday";
    case 2:
        return "Tuesday";
    case 3:
        return "Wednesday";
    case 4:
        return "Thursday";
    case 5:
        return "Friday";
    case 6:
        return "Saturday";
    case 7:
        return "Sunday";
    default:
        return "Invalid day";
    }
}

int main()
{
    // -------------------------------------------------------
    // 3. Basic switch with user-chosen value
    // -------------------------------------------------------
    std::cout << "=== Simple calculator ===\n";
    int a{20};
    int b{4};
    char op{'/'};

    std::cout << a << ' ' << op << ' ' << b << " = ";

    switch (op) // switch evaluates op ONCE
    {
    case '+':
        std::cout << (a + b);
        break; // Each case MUST end with break (or return)

    case '-':
        std::cout << (a - b);
        break;

    case '*':
        std::cout << (a * b);
        break;

    case '/':
        if (b != 0)
            std::cout << (a / b);
        else
            std::cout << "Error: division by zero";
        break;

    default: // Handles any value not matched above
        std::cout << "Unknown operator";
        break; // Best practice: break even in default
    }
    std::cout << '\n';

    // -------------------------------------------------------
    // 4. Enum switch
    // -------------------------------------------------------
    std::cout << "\n=== Enum switch ===\n";
    Color c{Color::blue};
    std::cout << "Color: " << colorToString(c) << '\n';

    // -------------------------------------------------------
    // 5. Day name switch
    // -------------------------------------------------------
    std::cout << "\n=== Day name switch ===\n";
    for (int d{1}; d <= 7; ++d)
    {
        std::cout << "Day " << d << " = " << dayName(d) << '\n';
    }

    // -------------------------------------------------------
    // Key points:
    // - switch only works with integral/enum types
    // - Case labels must be compile-time constants
    // - Always include a default case
    // - Every case should end with break or return
    // - switch is cleaner than long if-else chains for equality
    // -------------------------------------------------------

    return 0;
}
