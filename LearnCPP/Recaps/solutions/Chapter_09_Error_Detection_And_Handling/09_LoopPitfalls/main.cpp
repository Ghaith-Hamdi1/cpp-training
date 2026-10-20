// Project 09 - Loop Pitfalls
// Chapter 9: Error Detection and Handling
//
// Common loop-related mistakes that compile but produce wrong behavior:
//   1. Unsigned integer countdown to 0 (always-true condition)
//   2. Off-by-one errors  (< vs <=)
//   3. Forgetting to update the loop variable (infinite loop)
//   4. Modifying the loop variable incorrectly
//
// Each section shows the BUGGY pattern (commented out) and the correct FIX.

#include <iostream>

// ============================================================================
// 1. Unsigned integer countdown - always-true condition
// ============================================================================

void demo_unsignedCountdown()
{
    std::cout << "--- 1. Unsigned countdown pitfall ---\n";

    // BUG: An unsigned int is ALWAYS >= 0, so (count >= 0) is always true.
    //      When count reaches 0 and is decremented, it wraps to a huge value.
    //
    // unsigned int count { 5 };
    // while (count >= 0)   // INFINITE LOOP - unsigned is always >= 0!
    // {
    //     std::cout << count << ' ';
    //     --count;
    // }

    // FIX 1: Use a signed integer for countdown loops
    std::cout << "  FIX 1 (signed int): ";
    for (int i{5}; i >= 0; --i)
        std::cout << i << ' ';
    std::cout << '\n';

    // FIX 2: If you must use unsigned, check > 0 and handle 0 separately
    std::cout << "  FIX 2 (unsigned, adjusted condition): ";
    for (unsigned int i{5}; i > 0; --i)
        std::cout << i << ' ';
    std::cout << "0\n"; // Handle zero manually

    std::cout << "  Lesson: Avoid unsigned types in countdown loops.\n\n";
}

// ============================================================================
// 2. Off-by-one errors
// ============================================================================

void demo_offByOne()
{
    std::cout << "--- 2. Off-by-one errors ---\n";

    constexpr int size{5};

    // BUG: Using <= size iterates one time too many (0..5 = 6 iterations)
    // for (int i = 0; i <= size; ++i)   // visits index 5 - out of bounds!

    // FIX: Use < size for zero-based indexing
    std::cout << "  Correct (< size): indices ";
    for (int i{0}; i < size; ++i)
        std::cout << i << ' ';
    std::cout << '\n';

    // Common variant: printing numbers 1 through N
    // BUG: for (int i = 0; i < 5; ++i) prints 0..4 instead of 1..5
    // FIX: Start from 1 and use <=
    std::cout << "  Numbers 1-5 (start at 1, use <=): ";
    for (int i{1}; i <= 5; ++i)
        std::cout << i << ' ';
    std::cout << '\n';

    std::cout << "  Lesson: Carefully choose < vs <= based on your intent.\n\n";
}

// ============================================================================
// 3. Forgetting to update the loop variable
// ============================================================================

void demo_forgottenUpdate()
{
    std::cout << "--- 3. Forgetting to update the loop variable ---\n";

    // BUG: Missing ++i causes an infinite loop
    // int i { 0 };
    // while (i < 5)
    // {
    //     std::cout << i << ' ';
    //     // Oops - forgot ++i here!
    // }

    // FIX: Always ensure the loop variable progresses toward termination
    int i{0};
    std::cout << "  Correct: ";
    while (i < 5)
    {
        std::cout << i << ' ';
        ++i; // Don't forget this!
    }
    std::cout << '\n';

    // TIP: Prefer for-loops when the update is straightforward,
    // because the init/condition/update are all visible in one line.
    std::cout << "  Better: use a for-loop: ";
    for (int j{0}; j < 5; ++j)
        std::cout << j << ' ';
    std::cout << '\n';

    std::cout << "  Lesson: Prefer for-loops to avoid forgetting the update.\n\n";
}

// ============================================================================
// 4. Modifying the loop variable incorrectly
// ============================================================================

void demo_incorrectModification()
{
    std::cout << "--- 4. Incorrect loop variable modification ---\n";

    // BUG: Using the wrong operator (= instead of +=) resets the variable
    // for (int i = 0; i < 10; i = 2)   // i alternates between 0 and 2 forever

    // FIX: Use += to increment properly
    std::cout << "  Even numbers (i += 2): ";
    for (int i{0}; i < 10; i += 2)
        std::cout << i << ' ';
    std::cout << '\n';

    // BUG: Decrementing when you meant to increment (or vice versa)
    // for (int i = 0; i < 10; --i)   // i goes to -1, -2, ... (infinite)

    // FIX: Make sure the update moves TOWARD the termination condition
    std::cout << "  Countdown (--i):       ";
    for (int i{5}; i > 0; --i)
        std::cout << i << ' ';
    std::cout << '\n';

    std::cout << "  Lesson: Verify the update moves toward termination.\n\n";
}

// ============================================================================
// 5. Summary: the 0-1-2 test for loops
// ============================================================================

// A function we'll test with the 0-1-2 rule.
int sumArray(const int *arr, int count)
{
    int total{0};
    for (int i{0}; i < count; ++i)
        total += arr[i];
    return total;
}

void demo_012test()
{
    std::cout << "--- 5. The 0-1-2 test ---\n";

    // 0 iterations: count = 0
    int empty[]{};
    std::cout << "  sumArray(empty, 0) = " << sumArray(empty, 0) << " (0 iterations)\n";

    // 1 iteration: count = 1
    int one[]{42};
    std::cout << "  sumArray({42}, 1)  = " << sumArray(one, 1) << " (1 iteration)\n";

    // 2+ iterations: count = 3
    int three[]{10, 20, 30};
    std::cout << "  sumArray({10,20,30}, 3) = " << sumArray(three, 3) << " (3 iterations)\n";

    std::cout << "  Lesson: Always test loops with 0, 1, and 2+ iterations.\n\n";
}

// ============================================================================
// Main
// ============================================================================

int main()
{
    std::cout << "=== Loop Pitfalls Demo ===\n\n";

    demo_unsignedCountdown();
    demo_offByOne();
    demo_forgottenUpdate();
    demo_incorrectModification();
    demo_012test();

    std::cout << "Key takeaway: Use signed types for countdown loops, prefer\n";
    std::cout << "for-loops over while-loops, and always test with the 0-1-2 rule.\n";
    return 0;
}
