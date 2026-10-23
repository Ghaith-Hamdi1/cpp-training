// Project 05 - Bouncer Pattern (Preconditions, Invariants, Postconditions)
// Chapter 9: Error Detection and Handling
//
// The "bouncer pattern" checks preconditions at the TOP of a function
// and returns early (or asserts) if they are violated - just like a
// bouncer who checks your ID before letting you into the club.
//
// Terminology:
//   - Precondition  - a condition that must be true BEFORE the function runs
//   - Invariant     - a condition that must remain true DURING execution
//   - Postcondition - a condition that must be true AFTER the function completes
//
// Benefits:
//   - Keeps the main logic un-indented and easy to read
//   - Makes assumptions explicit and documented
//   - Fails fast with a clear message

#include <cassert>
#include <iostream>
#include <string>

// ============================================================================
// Example 1 - Bouncer pattern with early return
// ============================================================================

// Calculates the area of a rectangle.
// Preconditions: width > 0, height > 0
double rectangleArea(double width, double height)
{
    // --- Bouncer: validate preconditions, return early on failure ---
    if (width <= 0.0)
    {
        std::cerr << "  [Error] rectangleArea: width must be > 0 (got "
                  << width << ")\n";
        return 0.0;
    }
    if (height <= 0.0)
    {
        std::cerr << "  [Error] rectangleArea: height must be > 0 (got "
                  << height << ")\n";
        return 0.0;
    }

    // --- Main logic (only reached if preconditions are satisfied) ---
    return width * height;
}

// ============================================================================
// Example 2 - Bouncer pattern with assert (programmer errors)
// ============================================================================

// Returns the element at 'index' in a fixed-size array.
// Precondition: 0 <= index < size   (violated only by programmer bugs)
int getElement(const int *arr, int size, int index)
{
    // This should NEVER happen if the code is correct - use assert.
    assert(arr != nullptr && "getElement: arr must not be null");
    assert(index >= 0 && "getElement: index must be >= 0");
    assert(index < size && "getElement: index must be < size");

    return arr[index];
}

// ============================================================================
// Example 3 - Combining error handling AND assert
// ============================================================================

// Divides numerator by denominator.
// In debug builds, asserts that denominator != 0 (catches programmer bugs).
// In release builds, still checks and returns a safe default.
double safeDivide(double numerator, double denominator)
{
    // Assert catches the bug during development
    assert(denominator != 0.0 && "safeDivide: denominator must not be zero");

    // Error handling protects the release build
    if (denominator == 0.0)
    {
        std::cerr << "  [Error] safeDivide: division by zero\n";
        return 0.0;
    }

    return numerator / denominator;
}

// ============================================================================
// Example 4 - Postcondition check
// ============================================================================

// Computes the letter grade and verifies the postcondition that
// the result is one of the expected characters.
char computeGrade(int score)
{
    // Precondition
    assert(score >= 0 && score <= 100 && "computeGrade: score out of range");

    char grade{};
    if (score >= 90)
        grade = 'A';
    else if (score >= 80)
        grade = 'B';
    else if (score >= 70)
        grade = 'C';
    else if (score >= 60)
        grade = 'D';
    else
        grade = 'F';

    // Postcondition: result must be a valid grade letter
    assert((grade == 'A' || grade == 'B' || grade == 'C' ||
            grade == 'D' || grade == 'F') &&
           "computeGrade: invalid grade produced");

    return grade;
}

// ============================================================================
// Main
// ============================================================================

int main()
{
    std::cout << "=== Bouncer Pattern Demo ===\n\n";

    // --- Example 1: early return ---
    std::cout << "Example 1 - Early return on bad input:\n";
    std::cout << "  rectangleArea(5, 3)  = " << rectangleArea(5.0, 3.0) << '\n';
    std::cout << "  rectangleArea(-1, 3) = " << rectangleArea(-1.0, 3.0) << '\n';
    std::cout << "  rectangleArea(5, 0)  = " << rectangleArea(5.0, 0.0) << '\n';
    std::cout << '\n';

    // --- Example 2: assert-guarded access ---
    std::cout << "Example 2 - Assert-guarded array access:\n";
    int nums[]{10, 20, 30, 40, 50};
    std::cout << "  getElement(nums, 5, 2) = " << getElement(nums, 5, 2) << '\n';
    // Uncommenting the next line would trigger an assert in debug mode:
    // getElement(nums, 5, 10);  // index out of range!
    std::cout << '\n';

    // --- Example 3: assert + error handling ---
    std::cout << "Example 3 - Assert + error handling combined:\n";
    std::cout << "  safeDivide(10, 3) = " << safeDivide(10.0, 3.0) << '\n';
    std::cout << '\n';

    // --- Example 4: postcondition ---
    std::cout << "Example 4 - Postcondition checks:\n";
    for (int score : {95, 82, 74, 65, 50})
        std::cout << "  Score " << score << " -> Grade " << computeGrade(score) << '\n';
    std::cout << '\n';

    std::cout << "Key takeaway: Check preconditions at the top, return early on failure.\n";
    return 0;
}
