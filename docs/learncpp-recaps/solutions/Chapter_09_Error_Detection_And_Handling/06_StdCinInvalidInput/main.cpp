// Project 06 - std::cin and Handling Invalid Input
// Chapter 9: Error Detection and Handling
//
// Four categories of bad text input:
//   1. Meaningless but extractable   (e.g., entering -5 for age)
//   2. Extraneous input after valid  (e.g., "42abc" or "42 abc")
//   3. Extraction failure            (e.g., typing "hello" for an int)
//   4. Numeric overflow              (e.g., a number too large for int)
//
// Recovery recipe after extraction failure:
//   1. std::cin.clear()  - reset the error flags
//   2. std::cin.ignore() - discard the bad characters from the buffer
//   3. Re-prompt the user
//
// IMPORTANT: You must call clear() BEFORE ignore(). If the stream is still
// in a fail state, ignore() silently does nothing.
//
// This program demonstrates a robust input loop that handles all four cases.

#include <iostream>
#include <limits> // std::numeric_limits

// ============================================================================
// Robust integer input function
// ============================================================================

// Prompts the user until a valid integer in [min, max] is entered.
int getIntInRange(const char *prompt, int min, int max)
{
    while (true) // Loop forever until we get valid input
    {
        std::cout << prompt;

        int value{};
        std::cin >> value;

        // --- Category 3 & 4: extraction failure or overflow ---
        if (std::cin.fail())
        {
            // Step 1: clear the error state so we can use cin again
            std::cin.clear();

            // Step 2: discard everything remaining in the input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cerr << "  Invalid input. Please enter a whole number.\n";
            continue; // Re-prompt
        }

        // --- Category 2: extraneous input after the number ---
        // Discard any remaining characters up to (and including) '\n'
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // --- Category 1: meaningless but extractable value ---
        if (value < min || value > max)
        {
            std::cerr << "  Value must be between " << min
                      << " and " << max << ". Try again.\n";
            continue; // Re-prompt
        }

        return value; // All checks passed - valid input!
    }
}

// ============================================================================
// Robust double input function
// ============================================================================

double getPositiveDouble(const char *prompt)
{
    while (true)
    {
        std::cout << prompt;

        double value{};
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "  Invalid input. Please enter a number.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (value <= 0.0)
        {
            std::cerr << "  Value must be positive. Try again.\n";
            continue;
        }

        return value;
    }
}

// ============================================================================
// Robust yes/no input function
// ============================================================================

bool getYesNo(const char *prompt)
{
    while (true)
    {
        std::cout << prompt << " (y/n): ";

        char ch{};
        std::cin >> ch;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (ch == 'y' || ch == 'Y')
            return true;
        if (ch == 'n' || ch == 'N')
            return false;

        std::cerr << "  Please enter 'y' or 'n'.\n";
    }
}

// ============================================================================
// Main - interactive demo
// ============================================================================

int main()
{
    std::cout << "=== std::cin Invalid Input Handling Demo ===\n\n";
    std::cout << "This program demonstrates robust input validation.\n";
    std::cout << "Try entering bad input (letters, huge numbers, extra chars).\n\n";

    // Get a valid age (1..150)
    int age{getIntInRange("Enter your age (1-150): ", 1, 150)};
    std::cout << "  You entered age: " << age << "\n\n";

    // Get a valid weight
    double weight{getPositiveDouble("Enter your weight in kg: ")};
    std::cout << "  You entered weight: " << weight << " kg\n\n";

    // Get a yes/no answer
    bool again{getYesNo("Would you like to continue?")};
    std::cout << "  You answered: " << (again ? "yes" : "no") << "\n\n";

    std::cout << "Key takeaway: Always call clear() BEFORE ignore() after a failed extraction.\n";
    return 0;
}
