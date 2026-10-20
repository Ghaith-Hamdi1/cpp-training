// Chapter 7 - Project 05: Variable Shadowing (Name Hiding)
// ==========================================================
// When a variable in an inner scope has the same name as one in an
// outer scope, the inner variable "shadows" (hides) the outer one.
// The outer variable still exists - it's just inaccessible by name
// within the inner scope.
//
// Shadowed GLOBAL variables can still be accessed via :: (scope resolution).
// Best practice: AVOID shadowing - it leads to subtle, hard-to-find bugs.

#include <iostream>

// A global variable that will be shadowed
int value{1000};

int main()
{
    // -------------------------------------------------
    // 1. Local variable shadows a global variable
    // -------------------------------------------------
    int value{5}; // Shadows the global 'value'

    std::cout << "1. Local 'value'  = " << value << '\n';   // 5
    std::cout << "   Global 'value' = " << ::value << '\n'; // 1000 (via ::)

    // -------------------------------------------------
    // 2. Nested block shadows an outer local variable
    // -------------------------------------------------
    {
        int value{99};                                          // Shadows the local 'value' from main()
        std::cout << "\n2. Inner 'value'  = " << value << '\n'; // 99
        std::cout << "   Global 'value' = " << ::value << '\n'; // 1000
        // Note: the outer local 'value' (5) is completely inaccessible here!
    }
    // Inner 'value' is destroyed; outer local 'value' is visible again
    std::cout << "   After inner block: value = " << value << '\n'; // 5

    // -------------------------------------------------
    // 3. Loop variable shadowing
    // -------------------------------------------------
    int i{100};
    std::cout << "\n3. Before loop: i = " << i << '\n'; // 100

    for (int i{0}; i < 3; ++i) // 'i' here shadows the outer 'i'
    {
        std::cout << "   Loop i = " << i << '\n'; // 0, 1, 2
    }

    std::cout << "   After loop: i = " << i << '\n'; // 100 (outer i unchanged)

    // -------------------------------------------------
    // 4. Function parameter shadowing
    // -------------------------------------------------
    // If a function parameter had the same name as a global,
    // the parameter would shadow it within the function body.
    // (Demonstrated conceptually - see the lambda below)
    auto printValue = [](int value)
    {
        // 'value' here is the parameter, not the global or local
        std::cout << "\n4. Lambda param 'value' = " << value << '\n';
        std::cout << "   Global 'value'       = " << ::value << '\n';
    };
    printValue(42);

    // -------------------------------------------------
    // 5. Why shadowing is dangerous - a subtle bug
    // -------------------------------------------------
    std::cout << "\n5. Shadowing bug example:\n";
    int total{0};

    for (int j{0}; j < 5; ++j)
    {
        // BUG: accidentally declaring a NEW 'total' instead of using the outer one
        // int total{ 0 };  // <-- This would shadow the outer 'total'!
        // total += j;      // <-- Would modify the INNER total, not the outer one

        // CORRECT: use the outer 'total' directly
        total += j;
    }
    std::cout << "   Sum 0..4 = " << total << '\n'; // 10 (correct)
    // If we had shadowed, outer 'total' would still be 0 (bug!)

    // -------------------------------------------------
    // 6. Best practice: AVOID shadowing entirely
    // -------------------------------------------------
    // Use distinct, descriptive variable names to prevent confusion.
    // Most compilers can warn about shadowing:
    //   GCC/Clang: -Wshadow
    //   MSVC: /W4 catches some cases
    std::cout << "\n6. Tip: Compile with -Wshadow (GCC/Clang) to detect shadowing.\n";

    return 0;
}
