// Chapter 2 - Project 13: Program Design (Top-Down Approach)
// Concept: Breaking problems into functions, incremental implementation
//
// Good program design follows these steps:
//   1. Define the goal ("What should the program do?")
//   2. Define requirements (inputs, outputs, constraints)
//   3. Break the problem into smaller sub-problems → each becomes a function
//   4. Determine the sequence of events
//   5. Implement incrementally - write and test one function at a time
//
// This project demonstrates the process by building a simple "Unit
// Converter" that converts temperatures between Celsius and Fahrenheit.
// We design it top-down, keeping functions small, single-purpose, and
// testable.
// -----------------------------------------------------------------------

#include <iostream>

// -----------------------------------------------------------------------
// Step 3: Identify sub-problems and create a function for each.
// -----------------------------------------------------------------------

// Sub-problem 1: Get user input (which conversion direction?)
int getConversionChoice()
{
    std::cout << "Choose conversion:\n";
    std::cout << "  1) Celsius  -> Fahrenheit\n";
    std::cout << "  2) Fahrenheit -> Celsius\n";
    std::cout << "Enter choice (1 or 2): ";

    int choice{};
    std::cin >> choice;
    return choice;
}

// Sub-problem 2: Get the temperature value from the user.
double getTemperature()
{
    std::cout << "Enter temperature value: ";
    double temp{};
    std::cin >> temp;
    return temp;
}

// Sub-problem 3: Convert Celsius to Fahrenheit (pure calculation).
double celsiusToFahrenheit(double celsius)
{
    return (celsius * 9.0 / 5.0) + 32.0;
}

// Sub-problem 4: Convert Fahrenheit to Celsius (pure calculation).
double fahrenheitToCelsius(double fahrenheit)
{
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

// Sub-problem 5: Display the result (I/O only - no calculation).
void printResult(double inputTemp, const char *fromUnit,
                 double outputTemp, const char *toUnit)
{
    std::cout << inputTemp << " " << fromUnit
              << " = " << outputTemp << " " << toUnit << '\n';
}

// -----------------------------------------------------------------------
// Step 4: Sequence - main() orchestrates the sub-problems.
// -----------------------------------------------------------------------
int main()
{
    std::cout << "=== Project 13: Program Design (Temperature Converter) ===\n\n";

    // Get the user's choice
    int choice{getConversionChoice()};

    // Get the temperature
    double temp{getTemperature()};

    // Perform the conversion and display the result
    if (choice == 1)
    {
        double result{celsiusToFahrenheit(temp)};
        printResult(temp, "C", result, "F");
    }
    else if (choice == 2)
    {
        double result{fahrenheitToCelsius(temp)};
        printResult(temp, "F", result, "C");
    }
    else
    {
        std::cout << "Invalid choice.\n";
    }

    // Design summary:
    // • Each function does ONE thing (single responsibility).
    // • Calculation functions (celsiusToFahrenheit, fahrenheitToCelsius)
    //   are pure - no I/O.  Easy to test independently.
    // • I/O functions (getConversionChoice, getTemperature, printResult)
    //   handle user interaction.
    // • main() orchestrates the flow without doing heavy logic itself.
    // • We could add more conversions later by just adding new functions
    //   and extending the menu - extensibility!

    return 0;
}
