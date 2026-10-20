// Chapter 2 - Project 06: Effective Functions (DRY, Single-Task, I/O Separation)
// Concept: Why functions are useful and how to use them well
//
// Functions aid:
//   • Organization - group related code into named units
//   • Reusability  - call the same function many times
//   • Testing      - test each function independently
//   • Extensibility- add features by adding/modifying functions
//   • Abstraction  - hide implementation details behind a clear name
//
// Best practices:
//   • Each function should perform ONE task.
//   • Separate calculation from output (I/O separation).
//   • Follow DRY (Don't Repeat Yourself) - extract repeated code into
//     a function.
//   • Use a parameter when the caller supplies the value; use a local
//     variable otherwise.
// -----------------------------------------------------------------------

#include <iostream>

// -----------------------------------------------------------------------
// BAD EXAMPLE (DRY violation) - commented out to show what NOT to do.
// Imagine you want to print a formatted price in three places:
//
//   std::cout << "Item A: $" << (priceA * 1.10) << '\n';
//   std::cout << "Item B: $" << (priceB * 1.10) << '\n';
//   std::cout << "Item C: $" << (priceC * 1.10) << '\n';
//
// The tax calculation (price * 1.10) is duplicated - if the tax rate
// changes you must update it everywhere.  Extract it into a function!
// -----------------------------------------------------------------------

// GOOD: A single function for the repeated calculation.
double applyTax(double price)
{
    constexpr double taxRate{1.10}; // 10% tax
    return price * taxRate;
}

// -----------------------------------------------------------------------
// I/O SEPARATION - separate calculation from output.
// Instead of one function that calculates AND prints, split into two.
// -----------------------------------------------------------------------

// Calculation-only function (no I/O).
int computeArea(int width, int height)
{
    return width * height;
}

// Output-only function - receives the data to display.
void printArea(int width, int height, int area)
{
    std::cout << "Rectangle " << width << " x " << height
              << " = " << area << " sq. units\n";
}

// -----------------------------------------------------------------------
// SINGLE-TASK FUNCTIONS - each does one thing.
// -----------------------------------------------------------------------

bool isEven(int value)
{
    return (value % 2) == 0;
}

void reportEvenOdd(int value)
{
    if (isEven(value))
        std::cout << value << " is even.\n";
    else
        std::cout << value << " is odd.\n";
}

// -----------------------------------------------------------------------
// ABSTRACTION - the caller doesn't need to know HOW the function works,
// only WHAT it does.
// -----------------------------------------------------------------------

int factorial(int n)
{
    int result{1};
    for (int i{2}; i <= n; ++i)
        result *= i;
    return result;
}

int main()
{
    std::cout << "=== Project 06: Effective Functions ===\n\n";

    // 1. DRY - use applyTax() instead of repeating the formula
    std::cout << "--- DRY: applyTax() ---\n";
    double priceA{10.00};
    double priceB{25.50};
    double priceC{7.99};
    std::cout << "Item A after tax: $" << applyTax(priceA) << '\n';
    std::cout << "Item B after tax: $" << applyTax(priceB) << '\n';
    std::cout << "Item C after tax: $" << applyTax(priceC) << '\n';

    // 2. I/O separation - calculate, then display
    std::cout << "\n--- I/O Separation: computeArea() + printArea() ---\n";
    int w1{5}, h1{3};
    int area1{computeArea(w1, h1)};
    printArea(w1, h1, area1);

    int w2{10}, h2{7};
    int area2{computeArea(w2, h2)};
    printArea(w2, h2, area2);

    // 3. Single-task functions - isEven checks, reportEvenOdd prints
    std::cout << "\n--- Single-task functions ---\n";
    reportEvenOdd(4);
    reportEvenOdd(7);

    // 4. Abstraction - we call factorial() without knowing its internals
    std::cout << "\n--- Abstraction: factorial() ---\n";
    std::cout << "5! = " << factorial(5) << '\n';
    std::cout << "8! = " << factorial(8) << '\n';

    return 0;
}
