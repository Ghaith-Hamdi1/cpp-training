// Chapter 8 - Project 07: Goto Statements
// Demonstrates goto, statement labels, and why goto is generally avoided.
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>

int main()
{
    // -------------------------------------------------------
    // 1. Basic goto and statement labels
    // -------------------------------------------------------
    // A statement label has function scope - it's visible
    // throughout the function regardless of where it's defined.

    std::cout << "=== 1. Basic goto ===\n";
    std::cout << "Before goto\n";

    goto skipMessage; // Jump forward to the label

    // This line is skipped:
    std::cout << "This will NOT print.\n";

skipMessage: // Statement label (note: no indentation required)
    std::cout << "After goto - jumped here.\n";

    // -------------------------------------------------------
    // 2. goto cannot jump over variable initialization
    // -------------------------------------------------------
    // The following would be a compile error:
    // goto pastInit;
    // int value{ 42 };  // Error: goto skips initialization
    // pastInit:
    //     std::cout << value;

    // -------------------------------------------------------
    // 3. goto cannot jump into a different scope block
    // -------------------------------------------------------
    // The following would also be an error:
    // goto insideBlock;
    // {
    //     int x{ 5 };
    // insideBlock:       // Error: can't jump into a block from outside
    //     std::cout << x;
    // }

    // -------------------------------------------------------
    // 4. The one semi-acceptable use: breaking out of nested loops
    // -------------------------------------------------------
    std::cout << "\n=== 2. Nested loop exit with goto ===\n";

    // Find the first pair (i, j) where i * j == 12
    for (int i{1}; i <= 5; ++i)
    {
        for (int j{1}; j <= 5; ++j)
        {
            if (i * j == 12)
            {
                std::cout << "Found: " << i << " * " << j << " = 12\n";
                goto exitLoops; // break only exits the inner loop
            }
        }
    }

exitLoops:
    std::cout << "Exited nested loops.\n";

    // -------------------------------------------------------
    // 5. Better alternative - use a function with early return
    // -------------------------------------------------------
    // In practice, extract the nested loops into a function
    // and use return instead of goto. This is cleaner:
    //
    // void findProduct() {
    //     for (int i{1}; i <= 5; ++i)
    //         for (int j{1}; j <= 5; ++j)
    //             if (i * j == 12) {
    //                 std::cout << i << " * " << j << " = 12\n";
    //                 return;  // Clean exit
    //             }
    // }

    // -------------------------------------------------------
    // Key points:
    // - goto performs an unconditional jump to a statement label
    // - Statement labels have function scope
    // - goto cannot jump over variable initializations
    // - goto cannot jump into a nested scope from outside
    // - Avoid goto - use structured control flow (if/loops)
    // - The only semi-acceptable use: exiting deeply nested loops
    // - Even then, prefer extracting to a function with return
    // -------------------------------------------------------

    return 0;
}
