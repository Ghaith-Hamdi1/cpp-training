// Chapter 1 - Project 11: Incremental Development (First Program)
// ==================================================================
//
// KEY CONCEPTS:
//   - Build programs **incrementally**: write a few lines, compile, test, repeat.
//   - Don't try to write the entire program at once.
//   - Start with the simplest version that compiles, then add features one at a time.
//   - Prefer using expressions inline (e.g., num * 2 directly in cout)
//     over creating unnecessary intermediate variables.
//   - Once the code works, clean it up (remove debug output, improve names, etc.).
//   - Don't overwrite input variables - use expressions or new variables for results.
//
// This program demonstrates the process by building a "double a number" program
// step by step. Each "step" is labeled so you can see the progression.

#include <iostream>

int main()
{
    // =====================================================================
    // STEP 1: Start with the skeleton - just make it compile
    // =====================================================================
    // At first, you'd have just:
    //   int main() { return 0; }
    // Compile and run - it does nothing, but it proves your setup works.

    std::cout << "=== Double-a-Number Program ===\n\n";

    // =====================================================================
    // STEP 2: Add input
    // =====================================================================
    // Next, add the ability to get a number from the user.

    std::cout << "Enter a number: ";
    int num{};
    std::cin >> num;

    // At this point you'd compile and test - make sure input works.
    // You might add a debug print:
    // std::cout << "DEBUG: num = " << num << '\n';

    // =====================================================================
    // STEP 3: Add the computation and output
    // =====================================================================
    // Now add the core logic: double the number and display it.

    // APPROACH A (not ideal): storing in an intermediate variable
    // int doubled{ num * 2 };
    // std::cout << num << " doubled is " << doubled << '\n';

    // APPROACH B (better): use the expression inline - no extra variable needed
    std::cout << num << " doubled is " << (num * 2) << '\n';

    // =====================================================================
    // STEP 4: Clean up
    // =====================================================================
    // Remove any debug prints, ensure variable names are clear,
    // add comments where needed. The program is complete.

    // =====================================================================
    // BONUS: Don't overwrite input variables
    // =====================================================================
    // A common mistake is to do:
    //   num = num * 2;               // Overwrites the original input!
    //   std::cout << num << '\n';    // We lost what the user typed.
    //
    // Better: use the expression directly, or store in a NEW variable.

    std::cout << "\n--- Extra: Triple and Quadruple ---\n";
    std::cout << num << " tripled is " << (num * 3) << '\n';
    std::cout << num << " quadrupled is " << (num * 4) << '\n';
    // Notice: 'num' still holds the original value because we never overwrote it.

    // =====================================================================
    // SUMMARY: The incremental development process
    // =====================================================================
    std::cout << "\n--- Development Process ---\n";
    std::cout << "1. Write the minimal skeleton (main + return 0)\n";
    std::cout << "2. Add one feature at a time\n";
    std::cout << "3. Compile and test after each addition\n";
    std::cout << "4. Use debug prints to verify intermediate values\n";
    std::cout << "5. Clean up: remove debug output, improve names\n";
    std::cout << "6. Done!\n";

    return 0;
}
