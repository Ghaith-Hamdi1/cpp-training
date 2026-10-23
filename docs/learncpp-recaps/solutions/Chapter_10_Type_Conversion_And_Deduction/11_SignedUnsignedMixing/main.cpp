// Chapter 10 - Project 11: Pitfall - Signed/Unsigned Mixing
//
// Mixing signed and unsigned integers in expressions is one of the
// most common sources of bugs in C++.
//
// What happens: when a binary operator has one signed and one unsigned
// operand of the same rank, the SIGNED value is converted to UNSIGNED.
//
// This means negative numbers get converted to large positive numbers,
// causing comparisons and arithmetic to produce wrong results.
//
// BEST PRACTICE: Avoid unsigned integers in arithmetic.
// Use signed types (int, long, etc.) for quantities that could be negative.

#include <iostream>

int main()
{
    // =============================================================
    // 1. Subtraction wrapping
    // =============================================================
    std::cout << "=== Subtraction wrapping ===\n";

    // 5u - 10 should be -5, but unsigned can't be negative
    // It wraps around to a huge number
    unsigned int a{5u};
    unsigned int b{10u};
    unsigned int result{a - b}; // wraps!
    std::cout << "  5u - 10u = " << result << " (expected -5, got huge number!)\n";

    // =============================================================
    // 2. Comparison surprises
    // =============================================================
    std::cout << "\n=== Comparison surprises ===\n";

    int signedVal{-1};
    unsigned int unsignedVal{1u};

    // -1 < 1 should be true, but...
    // -1 is converted to unsigned first -> becomes a huge positive number
    if (signedVal < static_cast<int>(unsignedVal))
        std::cout << "  -1 < 1 (with cast): TRUE (correct!)\n";

    // Without the cast, this comparison is WRONG:
    // The compiler converts -1 to unsigned, making it ~4 billion
    // So the comparison becomes: 4294967295 < 1 -> false!
    if (static_cast<unsigned int>(signedVal) < unsignedVal)
        std::cout << "  (unsigned)-1 < 1u: This branch won't execute!\n";
    else
        std::cout << "  (unsigned)-1 < 1u: FALSE (wrong! -1 became "
                  << static_cast<unsigned int>(signedVal) << ")\n";

    // =============================================================
    // 3. Loop counter problems
    // =============================================================
    std::cout << "\n=== Loop counter problems ===\n";

    // Counting down with unsigned - this is an infinite loop!
    // When i reaches 0 and decrements, it wraps to max unsigned value
    std::cout << "  Counting down (signed, safe): ";
    for (int i{5}; i >= 0; --i)
        std::cout << i << ' ';
    std::cout << '\n';

    // This would be infinite with unsigned:
    // for (unsigned int i{ 5 }; i >= 0; --i)  // i >= 0 is ALWAYS true!
    //     std::cout << i << ' ';               // Infinite loop!

    std::cout << "  'for (unsigned i=5; i>=0; --i)' would be INFINITE!\n";
    std::cout << "  (unsigned is always >= 0, so the condition is always true)\n";

    // =============================================================
    // 4. Arithmetic mixing
    // =============================================================
    std::cout << "\n=== Arithmetic mixing ===\n";

    int x{-3};
    unsigned int y{10u};

    // x + y: x (-3) is converted to unsigned, becomes ~4 billion
    // then added to 10 -> gives wrong result
    auto mixedSum{x + y}; // unsigned arithmetic!
    std::cout << "  -3 + 10u = " << mixedSum
              << " (type is unsigned, wrong if negative result expected!)\n";

    // Fix: cast to signed first
    int correctSum{x + static_cast<int>(y)};
    std::cout << "  -3 + static_cast<int>(10u) = " << correctSum << " (correct!)\n";

    // =============================================================
    // 5. How to avoid these problems
    // =============================================================
    std::cout << "\n=== Prevention strategies ===\n";
    std::cout << "  1. Use signed types (int, long) for arithmetic\n";
    std::cout << "  2. Only use unsigned for bit manipulation or when required by API\n";
    std::cout << "  3. If you must mix, use static_cast to make intent explicit\n";
    std::cout << "  4. Enable compiler warnings (-Wsign-compare, -Wsign-conversion)\n";
    std::cout << "  5. Avoid unsigned loop counters that count down\n";

    return 0;
}
