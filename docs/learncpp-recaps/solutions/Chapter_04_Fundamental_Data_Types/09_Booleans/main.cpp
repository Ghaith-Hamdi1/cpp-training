// Chapter 4 - Project 09: Boolean Values
// ========================================
// Key concept: bool stores true (1) or false (0).
// std::cout prints bools as 0/1 by default; use std::boolalpha for text.
// Any non-zero integer converts to true; zero converts to false.

#include <iostream>

// A function that returns a bool
bool isEven(int x)
{
    return (x % 2) == 0;
}

bool isPositive(int x)
{
    return x > 0;
}

int main()
{
    std::cout << "=== Boolean Values ===\n\n";

    // Basic booleans
    bool isHappy{true};
    bool isSad{false};

    // Default output: 0 and 1
    std::cout << "--- Default bool output ---\n";
    std::cout << "isHappy: " << isHappy << " (prints 1 for true)\n";
    std::cout << "isSad:   " << isSad << " (prints 0 for false)\n";
    std::cout << '\n';

    // Using std::boolalpha for text output
    std::cout << std::boolalpha;
    std::cout << "--- With std::boolalpha ---\n";
    std::cout << "isHappy: " << isHappy << '\n';
    std::cout << "isSad:   " << isSad << '\n';
    std::cout << '\n';

    // Turn it off again
    std::cout << std::noboolalpha;

    // Integer to bool conversion
    std::cout << "--- Integer to bool conversion ---\n";
    std::cout << std::boolalpha;
    bool fromZero{static_cast<bool>(0)};      // false
    bool fromOne{static_cast<bool>(1)};       // true
    bool fromNegative{static_cast<bool>(-5)}; // true (any non-zero = true)
    bool fromLargeNum{static_cast<bool>(42)}; // true

    std::cout << "0  -> bool: " << fromZero << '\n';
    std::cout << "1  -> bool: " << fromOne << '\n';
    std::cout << "-5 -> bool: " << fromNegative << " (any non-zero = true)\n";
    std::cout << "42 -> bool: " << fromLargeNum << '\n';
    std::cout << '\n';

    // Using bool in if statements
    std::cout << "--- Booleans in conditions ---\n";
    int num{7};
    std::cout << num << " is even: " << isEven(num) << '\n';
    std::cout << num << " is positive: " << isPositive(num) << '\n';

    num = -4;
    std::cout << num << " is even: " << isEven(num) << '\n';
    std::cout << num << " is positive: " << isPositive(num) << '\n';
    std::cout << '\n';

    // Non-boolean values in conditions
    std::cout << "--- Non-boolean values as conditions ---\n";
    int x{5};
    if (x) // Non-zero = true
        std::cout << x << " is truthy (non-zero)\n";

    int y{0};
    if (!y) // Zero = false, so !false = true
        std::cout << y << " is falsy (zero)\n";

    return 0;
}
