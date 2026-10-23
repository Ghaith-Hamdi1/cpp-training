// Chapter 8 - Project 02: Common If Statement Problems
// Demonstrates dangling else, null statements, and = vs == bugs.
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>

int main()
{
    // -------------------------------------------------------
    // 1. Dangling else problem
    // -------------------------------------------------------
    // An else always pairs with the LAST unmatched if in the
    // same block - not necessarily the one you intended.

    int x{3};

    // Misleading indentation - else actually pairs with inner if
    // if (x >= 0)
    //     if (x > 5)
    //         std::cout << "x > 5\n";
    // else                              // Pairs with "if (x > 5)", NOT "if (x >= 0)"
    //     std::cout << "x is negative\n"; // WRONG - prints when x is 0..5

    // FIX: use explicit blocks to make intent clear
    if (x >= 0)
    {
        if (x > 5)
            std::cout << "x > 5\n";
    }
    else
    {
        std::cout << "x is negative\n"; // Now correctly pairs with outer if
    }

    // Since x == 3, neither message prints (x >= 0 but not > 5)
    std::cout << "x = " << x << " - dangling else demo done.\n\n";

    // -------------------------------------------------------
    // 2. Null statement after if - sneaky bug
    // -------------------------------------------------------
    // A semicolon right after if() creates a "null statement."
    // The if does nothing, and the next line always executes.

    bool isReady{false};

    // BUG (commented out to prevent confusion):
    // if (isReady);                     // <-- null statement; if does nothing
    //     std::cout << "Ready!\n";      // Always executes!

    // CORRECT:
    if (isReady)
    {
        std::cout << "Ready!\n"; // Only runs when isReady is true
    }
    std::cout << "isReady = " << std::boolalpha << isReady
              << " - null statement demo done.\n\n";

    // -------------------------------------------------------
    // 3. Using = (assignment) instead of == (comparison)
    // -------------------------------------------------------
    int y{0};

    // BUG (commented out):
    // if (y = 5)                       // Assigns 5 to y, then evaluates 5 as true!
    //     std::cout << "y is 5\n";     // Always prints because 5 is truthy

    // CORRECT:
    if (y == 5)
    {
        std::cout << "y is 5\n";
    }
    else
    {
        std::cout << "y is not 5 (y = " << y << ")\n";
    }

    // -------------------------------------------------------
    // 4. Flattening nested ifs with logical operators
    // -------------------------------------------------------
    int age{25};
    bool hasLicense{true};

    // Instead of nesting:
    // if (age >= 18)
    //     if (hasLicense)
    //         std::cout << "Can drive\n";

    // Use a logical AND:
    if (age >= 18 && hasLicense)
    {
        std::cout << "Can drive.\n";
    }

    return 0;
}
