// Chapter 4 - Project 12: Integer Division Truncation
// =====================================================
// Key concept: When both operands of / are integers, C++ performs
// integer division, which TRUNCATES (drops the fractional part).
// It does NOT round - it always drops toward zero.
//
// To get a fractional result, at least one operand must be
// a floating-point type. Use static_cast<double>() to convert.

#include <iostream>

int main()
{
    std::cout << "=== Integer Division Truncation ===\n\n";

    // Basic integer division - truncation in action
    std::cout << "--- Integer division results ---\n";
    std::cout << " 7 / 2  = " << (7 / 2) << " (expected 3.5,  got 3)\n";
    std::cout << " 1 / 3  = " << (1 / 3) << " (expected 0.33, got 0)\n";
    std::cout << "10 / 3  = " << (10 / 3) << " (expected 3.33, got 3)\n";
    std::cout << " 5 / 10 = " << (5 / 10) << " (expected 0.5,  got 0)\n";
    std::cout << " 3 / 4  = " << (3 / 4) << " (expected 0.75, got 0)\n";
    std::cout << '\n';

    // Negative integer division - truncates toward zero (NOT floor)
    std::cout << "--- Negative integer division ---\n";
    std::cout << "-7 / 2  = " << (-7 / 2) << " (truncates toward 0, not -4)\n";
    std::cout << " 7 / -2 = " << (7 / -2) << " (also -3, not -4)\n";
    std::cout << "-7 / -2 = " << (-7 / -2) << " (positive 3)\n";
    std::cout << '\n';

    // --- Getting fractional results ---
    std::cout << "--- How to get fractional results ---\n";

    int a{7};
    int b{2};

    // Method 1: Use a floating-point literal
    std::cout << "7.0 / 2   = " << (7.0 / 2) << " (one operand is double)\n";
    std::cout << "7   / 2.0 = " << (7 / 2.0) << " (one operand is double)\n";

    // Method 2: Use static_cast (best for variables)
    double result{static_cast<double>(a) / b};
    std::cout << "static_cast<double>(a) / b = " << result << '\n';
    std::cout << '\n';

    // Common mistake: casting AFTER division
    std::cout << "--- Common mistake ---\n";
    double wrong{static_cast<double>(a / b)}; // Division happens first as int!
    double right{static_cast<double>(a) / b}; // Cast first, then divide
    std::cout << "static_cast<double>(7 / 2) = " << wrong << " (WRONG: int division happens first)\n";
    std::cout << "static_cast<double>(7) / 2 = " << right << " (RIGHT: cast before division)\n";
    std::cout << '\n';

    // Practical example: computing an average
    std::cout << "--- Practical example: Average ---\n";
    int score1{85};
    int score2{90};
    int score3{78};
    int total{score1 + score2 + score3};

    // Wrong way:
    int wrongAvg{total / 3};
    // Right way:
    double rightAvg{static_cast<double>(total) / 3};

    std::cout << "Scores: " << score1 << ", " << score2 << ", " << score3 << '\n';
    std::cout << "Total:  " << total << '\n';
    std::cout << "Average (int division):    " << wrongAvg << " (truncated!)\n";
    std::cout << "Average (double division): " << rightAvg << " (correct)\n";

    return 0;
}
