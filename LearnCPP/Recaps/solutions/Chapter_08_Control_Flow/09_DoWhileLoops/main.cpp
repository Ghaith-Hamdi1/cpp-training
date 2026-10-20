// Chapter 8 - Project 09: Do-While Loops
// Demonstrates do-while guaranteeing at least one execution.
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>

int main()
{
    // -------------------------------------------------------
    // 1. Basic do-while - body always executes at least once
    // -------------------------------------------------------
    std::cout << "=== 1. Basic do-while ===\n";
    int i{1};
    do
    {
        std::cout << i << ' ';
        ++i;
    } while (i <= 5); // Condition checked AFTER the body
    std::cout << '\n'; // Output: 1 2 3 4 5

    // -------------------------------------------------------
    // 2. Runs once even when condition is immediately false
    // -------------------------------------------------------
    std::cout << "\n=== 2. Runs at least once ===\n";
    int x{100};
    do
    {
        std::cout << "x = " << x << " (body executed)\n";
    } while (x < 10); // false immediately, but body already ran once

    // Compare with while: this wouldn't execute the body at all
    // while (x < 10) { std::cout << "This never prints\n"; }

    // -------------------------------------------------------
    // 3. Input validation - classic do-while use case
    // -------------------------------------------------------
    std::cout << "\n=== 3. Input validation (simulated) ===\n";

    // Simulating a menu where user must pick 1, 2, or 3
    int menuChoices[]{5, 0, 2}; // Simulated inputs: invalid, invalid, valid
    int choiceIdx{0};
    int userChoice{};

    do
    {
        // In a real program: std::cin >> userChoice;
        userChoice = menuChoices[choiceIdx++];
        std::cout << "Input: " << userChoice;

        if (userChoice < 1 || userChoice > 3)
            std::cout << " - Invalid, try again.\n";

    } while (userChoice < 1 || userChoice > 3);

    std::cout << " - Valid choice: " << userChoice << '\n';

    // -------------------------------------------------------
    // 4. Countdown with do-while
    // -------------------------------------------------------
    std::cout << "\n=== 4. Countdown ===\n";
    int n{5};
    do
    {
        std::cout << n << "... ";
        --n;
    } while (n > 0);
    std::cout << "Liftoff!\n"; // 5... 4... 3... 2... 1... Liftoff!

    // -------------------------------------------------------
    // 5. When to prefer while over do-while
    // -------------------------------------------------------
    // Prefer while when:
    // - You might not want to execute the body at all
    // - The condition is more readable at the top
    //
    // Use do-while when:
    // - The body must execute at least once (input validation, menus)
    // - The condition depends on something computed in the body

    // -------------------------------------------------------
    // Key points:
    // - do-while: body runs first, then condition is checked
    // - Guarantees at least one execution
    // - Ideal for input validation / menu loops
    // - Prefer while when either loop works equally well
    // -------------------------------------------------------

    return 0;
}
