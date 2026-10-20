// Chapter 8 - Project 11: Break and Continue
// Demonstrates break, continue, early returns, and common pitfalls.
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>

// -------------------------------------------------------
// Helper: demonstrates early return (function-level break)
// -------------------------------------------------------
bool isPrime(int n)
{
    if (n <= 1)
        return false;

    for (int i{2}; i * i <= n; ++i)
    {
        if (n % i == 0)
            return false; // Early return - no need to check further
    }
    return true;
}

int main()
{
    // -------------------------------------------------------
    // 1. break - exits the innermost loop immediately
    // -------------------------------------------------------
    std::cout << "=== 1. break ===\n";
    std::cout << "Searching for first multiple of 7 in 1..50: ";

    for (int i{1}; i <= 50; ++i)
    {
        if (i % 7 == 0)
        {
            std::cout << i << " found!\n";
            break; // Stop as soon as we find one
        }
    }

    // -------------------------------------------------------
    // 2. continue - skips the rest of the current iteration
    // -------------------------------------------------------
    std::cout << "\n=== 2. continue ===\n";
    std::cout << "Odd numbers 1..10: ";

    for (int i{1}; i <= 10; ++i)
    {
        if (i % 2 == 0)
            continue; // Skip even numbers

        std::cout << i << ' ';
    }
    std::cout << '\n'; // 1 3 5 7 9

    // -------------------------------------------------------
    // 3. break only exits the innermost loop
    // -------------------------------------------------------
    std::cout << "\n=== 3. break with nested loops ===\n";

    for (int i{1}; i <= 3; ++i)
    {
        for (int j{1}; j <= 5; ++j)
        {
            if (j == 3)
                break; // Only breaks inner loop

            std::cout << '(' << i << ',' << j << ") ";
        }
        std::cout << '\n';
    }
    // Inner loop stops at j==3 each time, but outer loop continues

    // -------------------------------------------------------
    // 4. continue in a for loop - end-expression still runs
    // -------------------------------------------------------
    std::cout << "\n=== 4. continue in for loop (safe) ===\n";
    std::cout << "Non-multiples of 3 in 1..10: ";

    for (int i{1}; i <= 10; ++i) // ++i runs even after continue
    {
        if (i % 3 == 0)
            continue;

        std::cout << i << ' ';
    }
    std::cout << '\n'; // 1 2 4 5 7 8 10

    // -------------------------------------------------------
    // 5. PITFALL: continue in while loop can skip the counter
    // -------------------------------------------------------
    std::cout << "\n=== 5. continue pitfall in while ===\n";

    // BUG (would be infinite loop - commented out):
    // int count{ 0 };
    // while (count < 10)
    // {
    //     if (count == 5)
    //         continue;    // Skips ++count below → infinite loop!
    //     std::cout << count << ' ';
    //     ++count;         // Never reached when count == 5
    // }

    // FIX: increment BEFORE continue
    int count{0};
    std::cout << "Fixed while+continue: ";
    while (count < 10)
    {
        ++count; // Increment first to avoid infinite loop
        if (count == 5)
            continue; // Safe - counter already incremented

        std::cout << count << ' ';
    }
    std::cout << '\n'; // 1 2 3 4 6 7 8 9 10 (5 is skipped)

    // -------------------------------------------------------
    // 6. Early return - function-level equivalent of break
    // -------------------------------------------------------
    std::cout << "\n=== 6. Early return (isPrime) ===\n";
    for (int n{2}; n <= 20; ++n)
    {
        if (isPrime(n))
            std::cout << n << ' ';
    }
    std::cout << '\n'; // 2 3 5 7 11 13 17 19

    // -------------------------------------------------------
    // Key points:
    // - break: exits the innermost enclosing loop or switch
    // - continue: skips to the next iteration
    // - In for loops, continue still runs the end-expression
    // - In while/do-while, continue can skip counter updates → infinite loop
    // - Early return is the function-level equivalent of break
    // -------------------------------------------------------

    return 0;
}
