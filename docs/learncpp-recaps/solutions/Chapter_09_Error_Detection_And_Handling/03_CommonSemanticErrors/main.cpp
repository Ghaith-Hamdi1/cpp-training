// Project 03 - Common Semantic Errors
// Chapter 9: Error Detection and Handling
//
// Semantic errors compile just fine but produce wrong behavior.
// This program demonstrates the most frequent mistakes beginners make,
// shows the BUGGY version (commented out), and then shows the FIX.
//
// Errors covered:
//   1. Using >= when you meant >   (conditional logic error)
//   2. Null statement after if     (semicolon after condition)
//   3. Using = instead of ==       (assignment in a conditional)
//   4. Integer division truncation
//   5. Forgetting parentheses when calling a function
//   6. Off-by-one error in a loop

#include <iostream>

// ============================================================================
// 1. Conditional logic error: >= vs >
// ============================================================================
void demo_conditionalLogicError()
{
    std::cout << "--- 1. Conditional logic error (>= vs >) ---\n";

    int age{18};

    // BUG: A drinking-age check that uses >= instead of >
    // if (age >= 18) std::cout << "Can drink\n";  // Wrong in many jurisdictions!

    // FIX: Use the correct comparison operator for the rule you're modeling.
    if (age > 20)
        std::cout << "  Can drink (age > 20)\n";
    else
        std::cout << "  Cannot drink (age " << age << " is not > 20)\n";

    std::cout << "  Lesson: Double-check your comparison operators!\n\n";
}

// ============================================================================
// 2. Null statement after if (semicolon trap)
// ============================================================================
void demo_nullStatement()
{
    std::cout << "--- 2. Null statement after if ---\n";

    int x{5};

    // BUG: The semicolon terminates the if - the block always executes
    // if (x == 10);            // <-- null statement!
    // {
    //     std::cout << "x is 10\n";  // This ALWAYS prints
    // }

    // FIX: Remove the stray semicolon
    if (x == 10)
    {
        std::cout << "  x is 10\n";
    }
    else
    {
        std::cout << "  x is NOT 10 (correct behavior)\n";
    }

    std::cout << "  Lesson: Never put a semicolon right after if (condition)\n\n";
}

// ============================================================================
// 3. Assignment (=) instead of equality (==)
// ============================================================================
void demo_assignmentInConditional()
{
    std::cout << "--- 3. Assignment = vs equality == ---\n";

    int y{0};

    // BUG: This assigns 5 to y (which is truthy) - always enters the branch
    // if (y = 5)
    //     std::cout << "y is 5\n";

    // FIX: Use == for comparison
    if (y == 5)
        std::cout << "  y is 5\n";
    else
        std::cout << "  y is NOT 5 (y == " << y << ")\n";

    std::cout << "  Lesson: Use == for comparison, = is assignment\n\n";
}

// ============================================================================
// 4. Integer division truncation
// ============================================================================
void demo_integerDivision()
{
    std::cout << "--- 4. Integer division truncation ---\n";

    int a{7};
    int b{2};

    // BUG: Integer / integer discards the fractional part
    // double result = a / b;   // result is 3.0, NOT 3.5

    // FIX: Cast at least one operand to double before dividing
    double result{static_cast<double>(a) / b};

    std::cout << "  7 / 2 (int)    = " << (a / b) << "  (truncated!)\n";
    std::cout << "  7 / 2 (double) = " << result << "  (correct)\n";
    std::cout << "  Lesson: Cast to double when you need a fractional result\n\n";
}

// ============================================================================
// 5. Forgetting parentheses when calling a function
// ============================================================================
int getValue()
{
    return 42;
}

void demo_forgottenParentheses()
{
    std::cout << "--- 5. Forgetting () when calling a function ---\n";

    // BUG: Without (), this evaluates the function's ADDRESS (non-zero, truthy)
    // if (getValue)          // always true - compares function pointer, not 42
    //     std::cout << "truthy\n";

    // FIX: Always include () to actually call the function
    int result{getValue()};
    std::cout << "  getValue() returned: " << result << '\n';
    std::cout << "  Lesson: getValue and getValue() are very different things\n\n";
}

// ============================================================================
// 6. Off-by-one error in a loop
// ============================================================================
void demo_offByOne()
{
    std::cout << "--- 6. Off-by-one error ---\n";

    constexpr int arraySize{5};
    int arr[arraySize]{10, 20, 30, 40, 50};

    // BUG: Using <= instead of < causes reading one element past the end
    // for (int i = 0; i <= arraySize; ++i)   // visits index 5 - UB!
    //     std::cout << arr[i] << ' ';

    // FIX: Use < (strictly less than the size)
    std::cout << "  Array elements: ";
    for (int i{0}; i < arraySize; ++i)
        std::cout << arr[i] << ' ';

    std::cout << "\n  Lesson: Use < size, not <= size, when iterating arrays\n\n";
}

// ============================================================================
// Main
// ============================================================================

int main()
{
    std::cout << "=== Common Semantic Errors Demo ===\n\n";

    demo_conditionalLogicError();
    demo_nullStatement();
    demo_assignmentInConditional();
    demo_integerDivision();
    demo_forgottenParentheses();
    demo_offByOne();

    return 0;
}
