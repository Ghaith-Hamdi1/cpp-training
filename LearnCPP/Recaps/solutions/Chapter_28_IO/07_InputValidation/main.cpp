// Chapter 28 - Project 07: Input Validation
// ---------------------------------------------
// Key concepts:
//   1. After a failed extraction, you MUST:
//      a) Call cin.clear()  - to reset failbit (otherwise all future reads fail)
//      b) Call cin.ignore() - to discard the leftover bad characters
//   2. Numeric validation: attempt extraction, check fail(), clear + ignore on failure
//   3. String validation:  read as string, then check each character
//   4. Range validation:   check if the value is within acceptable bounds
//
// Common pitfall:
//   Forgetting step (b) - clear() resets the flags, but the bad input
//   is still sitting in the buffer.  The next >> will fail immediately.

#include <algorithm> // std::ranges::all_of (C++20)
#include <cctype>    // std::isalpha, std::isdigit
#include <iostream>
#include <limits> // std::numeric_limits
#include <string>

// -------------------------------------------------------
// Helper: get a valid integer from the user
// Re-prompts until a valid integer is entered.
// -------------------------------------------------------
int getValidInt(const std::string &prompt)
{
    while (true)
    {
        std::cout << prompt;
        int value{};
        std::cin >> value;

        if (std::cin.fail())
        {
            // Step 1: clear the error flags
            std::cin.clear();
            // Step 2: discard bad input up to and including '\n'
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "  [Error] That's not a valid integer. Try again.\n";
        }
        else
        {
            // Discard any trailing characters (e.g., "42abc" - discard "abc\n")
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// -------------------------------------------------------
// Helper: get an integer within a range
// -------------------------------------------------------
int getIntInRange(const std::string &prompt, int low, int high)
{
    while (true)
    {
        int value{getValidInt(prompt)};
        if (value >= low && value <= high)
            return value;
        std::cout << "  [Error] Value must be between "
                  << low << " and " << high << ". Try again.\n";
    }
}

// -------------------------------------------------------
// Helper: get a name (alphabetic characters only)
// Uses C++20 std::ranges::all_of for clean validation.
// -------------------------------------------------------
std::string getAlphaName(const std::string &prompt)
{
    while (true)
    {
        std::cout << prompt;
        std::string name{};
        std::getline(std::cin, name);

        if (name.empty())
        {
            std::cout << "  [Error] Name cannot be empty.\n";
            continue;
        }

        // Check that every character is alphabetic or a space
        bool valid = std::ranges::all_of(name, [](char c)
                                         { return std::isalpha(static_cast<unsigned char>(c)) || c == ' '; });

        if (valid)
            return name;

        std::cout << "  [Error] Name must contain only letters and spaces.\n";
    }
}

int main()
{
    std::cout << "=== Input Validation Demo ===\n\n";

    // ----- Numeric validation -----
    int age{getIntInRange("Enter your age (0-120): ", 0, 120)};
    std::cout << "Your age: " << age << "\n\n";

    // ----- String validation -----
    std::string name{getAlphaName("Enter your name (letters only): ")};
    std::cout << "Your name: " << name << "\n\n";

    // ----- Grade (A-F) validation -----
    char grade{};
    while (true)
    {
        std::cout << "Enter a letter grade (A-F): ";
        std::cin >> grade;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        grade = static_cast<char>(std::toupper(static_cast<unsigned char>(grade)));
        if (grade >= 'A' && grade <= 'F')
            break;
        std::cout << "  [Error] Must be A through F.\n";
    }
    std::cout << "Your grade: " << grade << "\n\n";

    std::cout << "All inputs validated successfully!\n";
    return 0;
}
