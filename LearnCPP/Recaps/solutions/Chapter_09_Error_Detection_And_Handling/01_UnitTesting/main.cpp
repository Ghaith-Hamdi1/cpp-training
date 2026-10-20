// Project 01 - Unit Testing
// Chapter 9: Error Detection and Handling
//
// Key idea: Test small units of code (individual functions) in isolation.
// Write test functions that compare actual results against expected results
// and print PASS/FAIL. This catches bugs early and makes refactoring safer.
//
// Concepts demonstrated:
//   - Writing informal unit tests for pure functions
//   - Testing the "happy path" (normal inputs)
//   - Testing the "sad path" (edge cases, boundary values)
//   - Automating pass/fail checks instead of eyeballing output

#include <cmath> // std::abs
#include <iostream>

// ============================================================================
// Functions under test
// ============================================================================

// Returns true if 'value' is even.
bool isEven(int value)
{
    return (value % 2) == 0;
}

// Returns the absolute value of an integer.
int myAbs(int value)
{
    return (value < 0) ? -value : value;
}

// Clamps 'value' into the range [low, high].
int clamp(int value, int low, int high)
{
    if (value < low)
        return low;
    if (value > high)
        return high;
    return value;
}

// ============================================================================
// Test helpers
// ============================================================================

int g_totalTests{0};
int g_passedTests{0};

// A tiny assertion helper that prints PASS or FAIL.
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
// Unit tests
// ============================================================================

void testIsEven()
{
    // Happy-path tests
    check(isEven(0), "isEven(0)  == true");
    check(isEven(2), "isEven(2)  == true");
    check(isEven(-4), "isEven(-4) == true");

    // Sad-path tests (odd numbers should return false)
    check(!isEven(1), "isEven(1)  == false");
    check(!isEven(-3), "isEven(-3) == false");
}

void testMyAbs()
{
    check(myAbs(0) == 0, "myAbs(0)  == 0");
    check(myAbs(5) == 5, "myAbs(5)  == 5");
    check(myAbs(-7) == 7, "myAbs(-7) == 7");
}

void testClamp()
{
    // Value inside range - should be unchanged
    check(clamp(5, 0, 10) == 5, "clamp(5, 0, 10) == 5");

    // Value below range - should be clamped to low
    check(clamp(-3, 0, 10) == 0, "clamp(-3, 0, 10) == 0");

    // Value above range - should be clamped to high
    check(clamp(15, 0, 10) == 10, "clamp(15, 0, 10) == 10");

    // Edge: value equals boundary
    check(clamp(0, 0, 10) == 0, "clamp(0, 0, 10)  == 0");
    check(clamp(10, 0, 10) == 10, "clamp(10, 0, 10) == 10");
}

// ============================================================================
// Main
// ============================================================================

int main()
{
    std::cout << "=== Unit Testing Demo ===\n\n";

    testIsEven();
    testMyAbs();
    testClamp();

    std::cout << "\nResults: " << g_passedTests << " / " << g_totalTests << " passed.\n";

    // A real project would return EXIT_FAILURE if any test failed.
    return 0;
}
