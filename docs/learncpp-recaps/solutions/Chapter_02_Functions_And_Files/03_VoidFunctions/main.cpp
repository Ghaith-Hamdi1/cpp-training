// Chapter 2 - Project 03: Void Functions
// Concept: Non-value-returning functions (void return type)
//
// A function with return type `void` performs an action but does NOT
// return a value to the caller.
//
// Key rules:
//   • A void function does not need a return statement.
//   • Putting `return;` at the very end of a void function is legal but
//     redundant - avoid it.
//   • You CANNOT use a void function where a value is expected
//     (e.g., std::cout << someVoidFunction();  // ERROR)
//   • An early `return;` IS useful to exit a void function before the end.
// -----------------------------------------------------------------------

#include <iostream>

// A simple void function - it does something but returns nothing.
void printStars()
{
    std::cout << "**********\n";
    // No return statement needed (and no trailing `return;` - it's redundant)
}

// A void function that takes a parameter.
void printValue(int value)
{
    std::cout << "The value is: " << value << '\n';
}

// Demonstrates early return in a void function (guard clause pattern).
void printPositive(int number)
{
    if (number <= 0)
    {
        std::cout << number << " is not positive - skipping.\n";
        return; // Early return - useful here to avoid deeper nesting
    }

    std::cout << number << " is positive!\n";
}

// A void function that calls other void functions - chaining actions.
void printReport(int a, int b)
{
    printStars();
    printValue(a);
    printValue(b);
    printStars();
}

int main()
{
    std::cout << "=== Project 03: Void Functions ===\n\n";

    // 1. Calling a basic void function
    std::cout << "--- printStars() ---\n";
    printStars();

    // 2. Void function with a parameter
    std::cout << "\n--- printValue(99) ---\n";
    printValue(99);

    // 3. Early return from a void function
    std::cout << "\n--- printPositive() with various inputs ---\n";
    printPositive(5);
    printPositive(-3);
    printPositive(0);

    // 4. Void function calling other void functions
    std::cout << "\n--- printReport(10, 20) ---\n";
    printReport(10, 20);

    // 5. Compile error demonstration (commented out):
    // std::cout << printStars();  // ERROR: cannot use void function as a value
    // int x = printStars();       // ERROR: cannot assign void to int

    return 0;
}
