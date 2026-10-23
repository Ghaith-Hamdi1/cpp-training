// Chapter 8 - Project 10: For Loops
// Demonstrates for loop syntax, off-by-one errors, and best practices.
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>

int main()
{
    // -------------------------------------------------------
    // 1. Basic for loop anatomy
    // -------------------------------------------------------
    // for (init; condition; end-expression) { body }
    //   init:          runs once before the loop starts
    //   condition:     checked before each iteration (false → stop)
    //   end-expression: runs after each iteration (before next check)

    std::cout << "=== 1. Basic for loop ===\n";
    for (int i{0}; i < 5; ++i)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n'; // 0 1 2 3 4

    // -------------------------------------------------------
    // 2. Counting backward
    // -------------------------------------------------------
    std::cout << "\n=== 2. Counting backward ===\n";
    for (int i{5}; i > 0; --i)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n'; // 5 4 3 2 1

    // -------------------------------------------------------
    // 3. Custom step size
    // -------------------------------------------------------
    std::cout << "\n=== 3. Step by 2 (even numbers) ===\n";
    for (int i{0}; i <= 10; i += 2)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n'; // 0 2 4 6 8 10

    // -------------------------------------------------------
    // 4. Off-by-one error examples
    // -------------------------------------------------------
    std::cout << "\n=== 4. Off-by-one errors ===\n";

    // Printing numbers 1 through 5:
    // WRONG: starts at 0 → prints 0,1,2,3,4
    // for (int i{0}; i < 5; ++i) - gives 0..4

    // CORRECT approaches:
    // A) Start at 1, use <=
    std::cout << "1..5: ";
    for (int i{1}; i <= 5; ++i)
        std::cout << i << ' ';
    std::cout << '\n';

    // B) Start at 0, use < count (idiomatic for 0-based indexing)
    std::cout << "0..4 (indices): ";
    for (int i{0}; i < 5; ++i)
        std::cout << i << ' ';
    std::cout << '\n';

    // -------------------------------------------------------
    // 5. Prefer < over != - safety against skipping past target
    // -------------------------------------------------------
    // DANGEROUS: if i somehow skips 10, loop never terminates
    // for (int i{0}; i != 10; i += 3) // 0, 3, 6, 9, 12, 15... (misses 10!)

    // SAFE: < will catch it
    std::cout << "\n=== 5. < vs != ===\n";
    std::cout << "Step by 3 (< 10): ";
    for (int i{0}; i < 10; i += 3)
        std::cout << i << ' ';
    std::cout << '\n'; // 0 3 6 9

    // -------------------------------------------------------
    // 6. Nested for loops - pattern printing
    // -------------------------------------------------------
    std::cout << "\n=== 6. Nested loops - right triangle ===\n";
    for (int row{1}; row <= 5; ++row)
    {
        for (int col{1}; col <= row; ++col)
        {
            std::cout << "* ";
        }
        std::cout << '\n';
    }

    // -------------------------------------------------------
    // 7. Omitting for-loop components
    // -------------------------------------------------------
    std::cout << "\n=== 7. Omitted components ===\n";

    // All three parts are optional:
    int j{0};
    for (; j < 3;) // init and end-expression omitted
    {
        std::cout << j << ' ';
        ++j; // increment manually in the body
    }
    std::cout << '\n';

    // Infinite for loop:
    // for (;;) { /* ... break when done ... */ }

    // -------------------------------------------------------
    // 8. Declare loop variable inside for - limits scope
    // -------------------------------------------------------
    for (int k{0}; k < 3; ++k)
    {
        std::cout << k << ' ';
    }
    // std::cout << k; // Error: k is out of scope here
    std::cout << '\n';

    // -------------------------------------------------------
    // Key points:
    // - for loops are ideal when a counter variable exists
    // - Prefer < or <= over != to avoid off-by-one / infinite loops
    // - Declare loop variables inside the for-statement
    // - Use signed integers for loop counters
    // -------------------------------------------------------

    return 0;
}
