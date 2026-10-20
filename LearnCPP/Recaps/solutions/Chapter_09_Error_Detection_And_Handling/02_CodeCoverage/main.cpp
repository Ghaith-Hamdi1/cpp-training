// Project 02 - Code Coverage
// Chapter 9: Error Detection and Handling
//
// Key idea: Code coverage measures how much of your source code is exercised
// by your tests. Three levels of coverage are discussed:
//
//   1. Statement coverage  - has every statement been executed?
//   2. Branch coverage      - has every true AND false branch of every
//                             conditional been tested?  Aim for 100%.
//   3. Loop coverage (0-1-2 test) - does the loop work correctly when
//                             it executes 0, 1, and 2+ iterations?
//
// This program demonstrates writing tests that achieve full branch and
// loop coverage for a simple function.

#include <iostream>
#include <string>

// ============================================================================
// Function under test
// ============================================================================

// Returns a letter grade for a numeric score.
// Requires: 0 <= score <= 100
std::string letterGrade(int score)
{
    if (score >= 90) // Branch A (true / false)
        return "A";
    else if (score >= 80) // Branch B
        return "B";
    else if (score >= 70) // Branch C
        return "C";
    else if (score >= 60) // Branch D
        return "D";
    else
        return "F"; // Branch E (else)
}

// Sums the first 'count' positive integers: 1 + 2 + ... + count
// Returns 0 when count <= 0.
int sumFirstN(int count)
{
    int total{0};
    for (int i{1}; i <= count; ++i) // Loop to test with 0, 1, 2 rule
        total += i;
    return total;
}

// ============================================================================
// Test helpers
// ============================================================================

int g_totalTests{0};
int g_passedTests{0};

void check(bool condition, const char *testName)
{
    ++g_totalTests;
    if (condition)
    {
        ++g_passedTests;
        std::cout << "[PASS] " << testName << '\n';
    }
    else
    {
        std::cout << "[FAIL] " << testName << '\n';
    }
}

// ============================================================================
// Tests - Branch coverage for letterGrade()
// ============================================================================

void testLetterGrade()
{
    std::cout << "--- letterGrade() branch coverage ---\n";

    // Branch A true: score >= 90
    check(letterGrade(95) == "A", "95  -> A");
    check(letterGrade(90) == "A", "90  -> A (boundary)");

    // Branch A false, B true: 80 <= score < 90
    check(letterGrade(85) == "B", "85  -> B");
    check(letterGrade(80) == "B", "80  -> B (boundary)");

    // Branch B false, C true: 70 <= score < 80
    check(letterGrade(75) == "C", "75  -> C");
    check(letterGrade(70) == "C", "70  -> C (boundary)");

    // Branch C false, D true: 60 <= score < 70
    check(letterGrade(65) == "D", "65  -> D");
    check(letterGrade(60) == "D", "60  -> D (boundary)");

    // Branch D false -> else (F): score < 60
    check(letterGrade(55) == "F", "55  -> F");
    check(letterGrade(0) == "F", " 0  -> F (boundary)");
}

// ============================================================================
// Tests - Loop coverage for sumFirstN() using the 0-1-2 test
// ============================================================================

void testSumFirstN()
{
    std::cout << "\n--- sumFirstN() loop coverage (0, 1, 2 test) ---\n";

    // 0 iterations: count <= 0 means the loop body never runs
    check(sumFirstN(0) == 0, "sumFirstN(0)  == 0   (0 iterations)");
    check(sumFirstN(-5) == 0, "sumFirstN(-5) == 0   (0 iterations, negative)");

    // 1 iteration
    check(sumFirstN(1) == 1, "sumFirstN(1)  == 1   (1 iteration)");

    // 2+ iterations
    check(sumFirstN(2) == 3, "sumFirstN(2)  == 3   (2 iterations)");
    check(sumFirstN(5) == 15, "sumFirstN(5)  == 15  (5 iterations)");
    check(sumFirstN(10) == 55, "sumFirstN(10) == 55  (10 iterations)");
}

// ============================================================================
// Main
// ============================================================================

int main()
{
    std::cout << "=== Code Coverage Demo ===\n\n";

    testLetterGrade();
    testSumFirstN();

    std::cout << "\nResults: " << g_passedTests << " / " << g_totalTests << " passed.\n";
    return 0;
}
