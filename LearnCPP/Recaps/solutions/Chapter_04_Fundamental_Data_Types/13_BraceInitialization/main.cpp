// Chapter 4 - Project 13: Brace Initialization and Narrowing Conversions
// ========================================================================
// Key concept: Brace initialization {} prevents narrowing conversions
// - conversions that would lose data - by generating a compiler error.
//
// This is one of the key reasons to prefer brace initialization over
// copy (=) or direct (()) initialization.

#include <iostream>

int main()
{
    std::cout << "=== Brace Initialization ===\n\n";

    // --- Three forms of initialization ---
    std::cout << "--- Three forms of initialization ---\n";

    int a = 5; // Copy initialization
    int b(5);  // Direct initialization
    int c{5};  // Brace (list/uniform) initialization - PREFERRED

    std::cout << "Copy init:   int a = 5  -> " << a << '\n';
    std::cout << "Direct init: int b(5)   -> " << b << '\n';
    std::cout << "Brace init:  int c{5}   -> " << c << '\n';
    std::cout << '\n';

    // --- Brace init prevents narrowing ---
    std::cout << "--- Narrowing conversions ---\n";

    // These COMPILE (copy/direct allow narrowing silently):
    int fromDouble1 = 3.9; // Silently truncates to 3 - no error!
    int fromDouble2(3.9);  // Also silently truncates to 3

    std::cout << "int x = 3.9;   -> " << fromDouble1 << " (silently truncated, no warning!)\n";
    std::cout << "int x(3.9);    -> " << fromDouble2 << " (also silently truncated)\n";

    // This would NOT compile (brace init catches narrowing):
    // int fromDouble3{ 3.9 };  // ERROR: narrowing conversion from double to int
    std::cout << "int x{3.9};    -> COMPILER ERROR (narrowing conversion detected!)\n";
    std::cout << '\n';

    // --- Safe brace initializations ---
    std::cout << "--- Safe brace initializations ---\n";

    int safe1{42};      // OK: 42 fits in int
    double safe2{3.14}; // OK: literal is double
    char safe3{'Z'};    // OK: char literal
    bool safe4{true};   // OK: bool literal

    std::cout << "int{42}:      " << safe1 << '\n';
    std::cout << "double{3.14}: " << safe2 << '\n';
    std::cout << "char{'Z'}:    " << safe3 << '\n';
    std::cout << "bool{true}:   " << std::boolalpha << safe4 << '\n';
    std::cout << '\n';

    // --- Value initialization (zero-init) with empty braces ---
    std::cout << "--- Value initialization with {} ---\n";

    int zero1{};    // Initialized to 0
    double zero2{}; // Initialized to 0.0
    bool zero3{};   // Initialized to false
    char zero4{};   // Initialized to '\0' (null character)

    std::cout << "int{}:    " << zero1 << '\n';
    std::cout << "double{}: " << zero2 << '\n';
    std::cout << "bool{}:   " << zero3 << '\n';
    std::cout << "char{}:   " << static_cast<int>(zero4) << " (null character = 0)\n";
    std::cout << '\n';

    // --- Why brace init is preferred ---
    std::cout << "--- Summary: Why prefer brace initialization ---\n";
    std::cout << "1. Prevents narrowing conversions (catches bugs at compile time).\n";
    std::cout << "2. Works consistently across all types.\n";
    std::cout << "3. Empty braces {} zero-initialize the variable.\n";
    std::cout << "4. Avoids the 'most vexing parse' problem of direct init.\n";

    return 0;
}
