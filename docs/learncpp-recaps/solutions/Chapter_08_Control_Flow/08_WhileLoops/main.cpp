// Chapter 8 - Project 08: While Loops
// Demonstrates while loops, infinite loops, nested loops, and pitfalls.
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>

int main()
{
    // -------------------------------------------------------
    // 1. Basic while loop - condition checked BEFORE each iteration
    // -------------------------------------------------------
    std::cout << "=== 1. Basic while loop ===\n";
    int count{1};
    while (count <= 5)
    {
        std::cout << count << ' ';
        ++count;
    }
    std::cout << '\n'; // Output: 1 2 3 4 5

    // -------------------------------------------------------
    // 2. while loop with a sentinel value
    // -------------------------------------------------------
    std::cout << "\n=== 2. Summing until zero ===\n";
    int values[]{3, 7, 2, 5, 0}; // 0 is the sentinel
    int idx{0};
    int sum{0};

    while (values[idx] != 0)
    {
        sum += values[idx];
        ++idx;
    }
    std::cout << "Sum = " << sum << '\n'; // 17

    // -------------------------------------------------------
    // 3. Intentional infinite loop with while(true)
    // -------------------------------------------------------
    std::cout << "\n=== 3. Infinite loop with exit condition ===\n";

    int attempts{0};
    while (true) // Intentional infinite loop
    {
        ++attempts;
        std::cout << "Attempt " << attempts << '\n';

        if (attempts >= 3)
        {
            std::cout << "Done after " << attempts << " attempts.\n";
            break; // Exit the infinite loop
        }
    }

    // -------------------------------------------------------
    // 4. Nested while loops - multiplication table
    // -------------------------------------------------------
    std::cout << "\n=== 4. Nested loops - 3x3 multiplication table ===\n";
    int row{1};
    while (row <= 3)
    {
        int col{1};
        while (col <= 3)
        {
            std::cout << (row * col) << '\t';
            ++col;
        }
        std::cout << '\n';
        ++row;
    }

    // -------------------------------------------------------
    // 5. Pitfall: unsigned loop variable
    // -------------------------------------------------------
    // DANGER: unsigned variables wrap around past zero!
    // unsigned int u{ 5 };
    // while (u >= 0) // ALWAYS true for unsigned - infinite loop!
    // {
    //     std::cout << u << ' ';
    //     --u;
    // }

    // FIX: use signed integers for loop counters
    std::cout << "\n=== 5. Counting down (signed) ===\n";
    int n{5};
    while (n >= 0)
    {
        std::cout << n << ' ';
        --n;
    }
    std::cout << '\n'; // Output: 5 4 3 2 1 0

    // -------------------------------------------------------
    // 6. Pitfall: accidental semicolon after while
    // -------------------------------------------------------
    // while (count < 10);  // <- null statement! Infinite loop
    //     ++count;         // Never reached inside the loop

    // -------------------------------------------------------
    // Key points:
    // - while checks condition BEFORE each iteration
    // - Use while(true) for intentional infinite loops (with break)
    // - Always use SIGNED integers for loop counters
    // - Watch out for semicolons after while()
    // -------------------------------------------------------

    return 0;
}
