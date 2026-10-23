// Chapter 8 - Project 01: If Statements and Blocks
// Demonstrates if/else syntax and why blocks {} are essential.
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>

int main()
{
    // -------------------------------------------------------
    // 1. Basic if statement
    // -------------------------------------------------------
    int x{10};

    if (x > 5)
        std::cout << "x is greater than 5\n"; // Only this line is conditional

    // -------------------------------------------------------
    // 2. if/else
    // -------------------------------------------------------
    int temperature{30};

    if (temperature > 25)
        std::cout << "It's warm outside.\n";
    else
        std::cout << "It's cool outside.\n";

    // -------------------------------------------------------
    // 3. Why blocks matter - BUG without braces
    // -------------------------------------------------------
    // Without a block, only the FIRST statement after if/else
    // is conditional. The rest execute unconditionally.

    bool loggedIn{false};

    // WRONG - "Welcome back!" prints regardless of loggedIn
    // if (loggedIn)
    //     std::cout << "Logged in.\n";
    //     std::cout << "Welcome back!\n";  // Always runs!

    // CORRECT - use a block
    if (loggedIn)
    {
        std::cout << "Logged in.\n";
        std::cout << "Welcome back!\n";
    }
    else
    {
        std::cout << "Please log in first.\n";
    }

    // -------------------------------------------------------
    // 4. if vs if-else: independent vs exclusive conditions
    // -------------------------------------------------------
    int score{85};

    // Independent checks - both can print
    if (score >= 50)
        std::cout << "You passed.\n";
    if (score >= 80)
        std::cout << "Great job!\n";

    // Exclusive check - only one branch runs
    if (score >= 90)
        std::cout << "Grade: A\n";
    else if (score >= 80)
        std::cout << "Grade: B\n";
    else if (score >= 70)
        std::cout << "Grade: C\n";
    else
        std::cout << "Grade: below C\n";

    // -------------------------------------------------------
    // 5. Single-line if is fine for truly simple cases
    // -------------------------------------------------------
    int value{42};
    if (value == 42)
        std::cout << "The answer to life, the universe, and everything.\n";

    // Best practice: always use blocks to prevent future bugs
    // when adding more statements to a branch.

    return 0;
}
