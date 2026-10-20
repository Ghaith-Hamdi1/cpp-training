// Chapter 8 - Project 06: Switch Fallthrough and Scoping
// Demonstrates fallthrough behavior, [[fallthrough]], and variable scoping.
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>

int main()
{
    // -------------------------------------------------------
    // 1. Unintentional fallthrough - the BUG
    // -------------------------------------------------------
    std::cout << "=== 1. Unintentional fallthrough ===\n";
    int choice{2};

    // Without break, execution "falls through" into subsequent cases.
    // BUG example (commented out - would print cases 2, 3, default):
    // switch (choice)
    // {
    // case 1:
    //     std::cout << "Case 1\n";
    // case 2:
    //     std::cout << "Case 2\n";   // Matches, starts here
    // case 3:
    //     std::cout << "Case 3\n";   // Falls through!
    // default:
    //     std::cout << "Default\n";  // Falls through!
    // }

    // CORRECT - use break
    switch (choice)
    {
    case 1:
        std::cout << "Case 1\n";
        break;
    case 2:
        std::cout << "Case 2\n";
        break;
    case 3:
        std::cout << "Case 3\n";
        break;
    default:
        std::cout << "Default\n";
        break;
    }

    // -------------------------------------------------------
    // 2. Intentional fallthrough with [[fallthrough]]
    // -------------------------------------------------------
    std::cout << "\n=== 2. Intentional fallthrough ===\n";
    int month{2}; // February

    int daysInMonth{};
    switch (month)
    {
    case 2:
        daysInMonth = 28; // (ignoring leap years for simplicity)
        break;

    // Months with 30 days - stacked labels share one body
    case 4:
    case 6:
    case 9:
    case 11:
        daysInMonth = 30;
        break;

    // Months with 31 days
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        daysInMonth = 31;
        break;

    default:
        daysInMonth = -1; // Invalid month
        break;
    }
    std::cout << "Month " << month << " has " << daysInMonth << " days.\n";

    // -------------------------------------------------------
    // 3. [[fallthrough]] attribute - marking it intentional
    // -------------------------------------------------------
    std::cout << "\n=== 3. [[fallthrough]] attribute ===\n";
    int level{3};

    std::cout << "Permissions for level " << level << ": ";
    switch (level)
    {
    case 3:
        std::cout << "[admin] ";
        [[fallthrough]]; // Tells compiler: this fallthrough is intentional
    case 2:
        std::cout << "[write] ";
        [[fallthrough]];
    case 1:
        std::cout << "[read] ";
        break;
    default:
        std::cout << "[none]";
        break;
    }
    std::cout << '\n';

    // -------------------------------------------------------
    // 4. Variable scoping inside switch
    // -------------------------------------------------------
    std::cout << "\n=== 4. Variable scoping ===\n";
    int action{1};

    switch (action)
    {
        // WRONG - declaring and initializing a variable here
        // without a block would cause a compile error if another
        // case follows, because execution could jump past the init.
        // int x{ 5 }; // ERROR if case 2 exists below

    case 1:
    {
        // FIX: wrap the case body in its own block
        int x{10};
        std::cout << "Action 1: x = " << x << '\n';
        break;
    }

    case 2:
    {
        int x{20}; // Different scope - no conflict
        std::cout << "Action 2: x = " << x << '\n';
        break;
    }

    default:
        std::cout << "Unknown action\n";
        break;
    }

    // -------------------------------------------------------
    // Key points:
    // - Without break/return, execution falls through to the next case
    // - Stacked case labels (no code between them) are NOT fallthrough
    // - Use [[fallthrough]]; to silence warnings for intentional fallthrough
    // - Variables inside switch cases must be in their own block {}
    // -------------------------------------------------------

    return 0;
}
