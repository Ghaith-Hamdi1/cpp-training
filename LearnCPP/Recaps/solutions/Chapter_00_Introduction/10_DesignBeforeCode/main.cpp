// ============================================================================
// Chapter 0, Project 10 - Design Before Code
// Concept: Planning your solution before writing code.
// ============================================================================
//
// KEY IDEAS (Section 0.4):
//   The software development cycle:
//     1. Define the problem
//     2. Design the solution
//     3. Write the code
//     4. Compile
//     5. Link
//     6. Test
//     7. Debug (fix issues, go back to step 3)
//
//   Good programming practices:
//     - Plan BEFORE you code - jumping straight in leads to fragile solutions.
//     - Keep code straightforward and well-documented.
//     - Make programs modular (break big problems into smaller pieces).
//     - Handle errors gracefully.
//     - Test with different inputs, including edge cases.
//     - Maintenance takes 60-90% of total development time!
//
// This program demonstrates a small, well-planned solution:
//   Problem:  Convert temperatures between Celsius and Fahrenheit.
//   Design:   - Ask the user for a temperature and its unit.
//             - Convert and display the result.
//             - Handle invalid input gracefully.
//
// BUILD:  g++ -std=c++20 -Wall -Wextra -Werror -o DesignBeforeCode main.cpp
// ============================================================================

#include <iostream>

// -----------------------------------------------------------------------
// STEP 2 (Design): We planned these helper functions before writing code.
//   - Each function does ONE thing (modularity).
//   - Names clearly describe what they do (readability).
//   - Conversion formulas are isolated (easy to test and fix).
// -----------------------------------------------------------------------

// Convert Celsius to Fahrenheit: F = C * 9/5 + 32
double celsiusToFahrenheit(double celsius)
{
    return celsius * 9.0 / 5.0 + 32.0;
}

// Convert Fahrenheit to Celsius: C = (F - 32) * 5/9
double fahrenheitToCelsius(double fahrenheit)
{
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

int main()
{
    std::cout << "=== Design Before Code: Temperature Converter ===" << std::endl;
    std::cout << std::endl;

    // STEP 1 was done on paper: "Convert temperatures between C and F."

    // STEP 3: Write the code (following our design)

    std::cout << "This program converts between Celsius and Fahrenheit." << std::endl;
    std::cout << std::endl;

    // Get the temperature value
    std::cout << "Enter a temperature value: ";
    double temperature = 0.0;
    std::cin >> temperature;

    // Get the unit
    std::cout << "Is this (C)elsius or (F)ahrenheit? Enter C or F: ";
    char unit = ' ';
    std::cin >> unit;

    std::cout << std::endl;

    // Perform the conversion based on the unit
    if (unit == 'C' || unit == 'c')
    {
        double result = celsiusToFahrenheit(temperature);
        std::cout << temperature << " C = " << result << " F" << std::endl;
    }
    else if (unit == 'F' || unit == 'f')
    {
        double result = fahrenheitToCelsius(temperature);
        std::cout << temperature << " F = " << result << " C" << std::endl;
    }
    else
    {
        // Handle errors gracefully - don't just crash or give wrong output
        std::cout << "Error: '" << unit << "' is not a valid unit." << std::endl;
        std::cout << "Please enter 'C' for Celsius or 'F' for Fahrenheit." << std::endl;
    }

    std::cout << std::endl;

    // STEP 6 & 7: Test with different inputs!
    // Try these test cases:
    //   100 C  → should give 212 F   (boiling point of water)
    //   32 F   → should give 0 C     (freezing point of water)
    //   0 C    → should give 32 F
    //   -40 C  → should give -40 F   (the point where C and F are equal!)
    //   X      → should show an error message

    std::cout << "--- Development Cycle Recap ---" << std::endl;
    std::cout << "1. Define the problem  (what to solve)" << std::endl;
    std::cout << "2. Design the solution (plan before coding)" << std::endl;
    std::cout << "3. Write the code      (follow the plan)" << std::endl;
    std::cout << "4. Compile             (fix syntax errors)" << std::endl;
    std::cout << "5. Link                (fix missing references)" << std::endl;
    std::cout << "6. Test                (try different inputs)" << std::endl;
    std::cout << "7. Debug               (fix logic errors, repeat)" << std::endl;

    return 0;
}
