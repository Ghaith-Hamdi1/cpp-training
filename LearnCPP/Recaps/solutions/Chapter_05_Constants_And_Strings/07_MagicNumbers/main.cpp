// Chapter 5 - Project 07: Magic Numbers
// ========================================
// Topics:
//   - What are magic numbers and why they're problematic
//   - Replacing magic numbers with named constexpr constants
//   - Improving code readability and maintainability
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>

int main()
{
    // -------------------------------------------------------
    // 1. The problem with magic numbers
    // -------------------------------------------------------
    // A "magic number" is a literal whose meaning is unclear
    // or that might need to change later.

    std::cout << "=== BAD: Magic Numbers ===\n";

    // What does 30 mean? What does 1.08 mean? What is 100?
    double price{49.99};
    double taxed{price * 1.08}; // What is 1.08?
    if (taxed > 100)            // Why 100?
        std::cout << "Price with tax: $" << taxed << " (high-value item)\n";

    int students{25};
    if (students > 30) // Why 30?
        std::cout << "Class is full.\n";

    std::cout << "The numbers 1.08, 100, 30 are 'magic numbers'.\n";
    std::cout << "Their meaning is unclear without context.\n";

    // -------------------------------------------------------
    // 2. The solution: named constexpr constants
    // -------------------------------------------------------
    std::cout << "\n=== GOOD: Named Constants ===\n";

    constexpr double taxRate{0.08};
    constexpr double highValueThreshold{100.0};
    constexpr int maxClassSize{30};

    double price2{49.99};
    double taxed2{price2 * (1.0 + taxRate)}; // Clear: tax rate
    if (taxed2 > highValueThreshold)         // Clear: threshold
        std::cout << "Price with tax: $" << taxed2 << " (high-value item)\n";

    int students2{25};
    if (students2 > maxClassSize) // Clear: max class size
        std::cout << "Class is full.\n";
    else
        std::cout << "Class has room (" << students2 << "/" << maxClassSize << ").\n";

    // -------------------------------------------------------
    // 3. Benefits of named constants
    // -------------------------------------------------------
    std::cout << "\n=== Benefits ===\n";
    std::cout << "1. Readability:      'maxClassSize' is self-documenting.\n";
    std::cout << "2. Maintainability:  Change ONE constant, not every occurrence.\n";
    std::cout << "3. Fewer bugs:       No risk of updating some occurrences but not others.\n";
    std::cout << "4. Debugging:        Named constants appear in the debugger.\n";

    // -------------------------------------------------------
    // 4. When literals are acceptable
    // -------------------------------------------------------
    // Not all literals are magic numbers. Some have obvious meaning:

    std::cout << "\n=== Acceptable Literals ===\n";

    int doubled = students2 * 2;     // Multiplying by 2 is self-evident
    bool isEmpty = (students2 == 0); // Comparing to 0 is clear

    std::cout << "students * 2 = " << doubled << "  (2 is not 'magic' here)\n";
    std::cout << "students == 0 is " << std::boolalpha << isEmpty
              << "  (0 is not 'magic' here)\n";

    // -------------------------------------------------------
    // 5. Practical example: geometry
    // -------------------------------------------------------
    std::cout << "\n=== Practical Example ===\n";

    // BAD:
    // double area = 3.14159 * 5.0 * 5.0;  // What is 3.14159? What is 5.0?

    // GOOD:
    constexpr double pi{3.14159265358979};
    constexpr double radius{5.0};
    double area = pi * radius * radius;

    std::cout << "Circle with radius " << radius << ":\n";
    std::cout << "  Area = " << area << '\n';

    return 0;
}
