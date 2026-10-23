// Chapter 3 - Project 02: The Debugging Process
// ================================================
//
// KEY CONCEPT:
//   Debugging follows a six-step process:
//     1. Find the root cause of the problem.
//     2. Understand WHY the problem occurs.
//     3. Determine how to fix it.
//     4. Repair the issue.
//     5. Retest to verify the fix works.
//     6. Retest for regressions (new problems caused by the fix).
//
// This program contains a deliberate bug: it computes the average of three
// numbers but uses integer division, discarding the fractional part.
// We walk through the six-step process in the comments.
//
// EXERCISE: Follow the steps below, then apply the fix.

#include <iostream>

// This function has a semantic error: integer division truncates the result.
// Step 1 - FIND:        The average of 3, 4, 5 should be 4.0, but we get 4.
//                       For 2, 3, 8 we expect ~4.33 but get 4.
// Step 2 - UNDERSTAND:  All operands are int, so '/' performs integer division.
// Step 3 - DETERMINE:   Cast the numerator (or denominator) to double before dividing.
// Step 4 - REPAIR:      Change the return type and add a cast (see the fix below).
// Step 5 - RETEST FIX:  Verify 2+3+8 = 13 / 3 = 4.33333...
// Step 6 - REGRESSIONS: Confirm other inputs still work correctly.

// ---- BUGGY version ----
int averageBuggy(int a, int b, int c)
{
    return (a + b + c) / 3; // integer division - truncates!
}

// ---- FIXED version ----
double averageFixed(int a, int b, int c)
{
    return static_cast<double>(a + b + c) / 3; // floating-point division
}

int main()
{
    int x{2};
    int y{3};
    int z{8};

    std::cout << "=== Six-Step Debugging Process Demo ===\n\n";

    // Step 1 & 2: Observe the wrong output
    std::cout << "Buggy average of " << x << ", " << y << ", " << z
              << " = " << averageBuggy(x, y, z) << '\n';
    std::cout << "  Expected ~4.333, got 4 (integer truncation)\n\n";

    // Steps 3–5: Apply fix and retest
    std::cout << "Fixed average of " << x << ", " << y << ", " << z
              << " = " << averageFixed(x, y, z) << '\n';

    // Step 6: Regression test with a different set of inputs
    std::cout << "Fixed average of 10, 20, 30 = "
              << averageFixed(10, 20, 30) << '\n'; // should be 20.0

    return 0;
}
