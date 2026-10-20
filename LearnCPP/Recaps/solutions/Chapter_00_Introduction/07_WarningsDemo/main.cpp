// ============================================================================
// Chapter 0, Project 07 - Warnings Demo
// Concept: Why compiler warnings matter and how to handle them.
// ============================================================================
//
// KEY IDEAS (Section 0.11):
//   - Warnings indicate code that compiles but is probably wrong or risky.
//   - Increase warning levels to catch more issues:
//       MSVC:      /W4
//       GCC/Clang: -Wall -Wextra -Wconversion -Wsign-conversion
//   - Enable "treat warnings as errors" to force yourself to fix them:
//       MSVC:      /WX
//       GCC/Clang: -Werror
//   - Ignoring warnings lets real bugs slip through unnoticed.
//   - Fix warnings as soon as they appear - don't let them accumulate.
//
// NOTE: This file is written to compile CLEANLY with warnings enabled.
//       The commented-out sections show what WARNING-TRIGGERING code looks like.
//       Uncomment them to see the warnings your compiler produces.
//
// BUILD:  g++ -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -o WarningsDemo main.cpp
// ============================================================================

#include <iostream>

int main()
{
    std::cout << "=== Compiler Warnings Demo ===" << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------------------------
    // EXAMPLE 1: Unused variable
    // -----------------------------------------------------------------------
    // Uncommenting the next line may trigger: "warning: unused variable 'unused'"
    // int unused = 42;

    std::cout << "Example 1: Unused variables" << std::endl;
    std::cout << "  An unused variable is likely a mistake - did you forget to" << std::endl;
    std::cout << "  use it, or is it leftover code? The compiler warns you." << std::endl;
    std::cout << std::endl;

    // The FIX: only declare variables you actually use.
    int used = 42;
    std::cout << "  used = " << used << " (no warning - it's actually used!)" << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------------------------
    // EXAMPLE 2: Signed/unsigned comparison
    // -----------------------------------------------------------------------
    // Uncommenting may trigger: "warning: comparison of integer expressions
    //                           of different signedness"
    // int signedVal = -1;
    // unsigned int unsignedVal = 1;
    // if (signedVal < unsignedVal) { /* ... */ } // Risky! -1 could wrap around.

    std::cout << "Example 2: Signed/unsigned comparison" << std::endl;
    std::cout << "  Comparing signed and unsigned integers is dangerous." << std::endl;
    std::cout << "  -1 as unsigned becomes a huge positive number!" << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------------------------
    // EXAMPLE 3: Implicit narrowing conversion
    // -----------------------------------------------------------------------
    // Uncommenting may trigger: "warning: conversion from 'double' to 'int',
    //                           possible loss of data"
    // double pi = 3.14159;
    // int rounded = pi;  // Truncates 3.14159 to 3 - was this intentional?

    std::cout << "Example 3: Implicit narrowing conversion" << std::endl;
    std::cout << "  Assigning a double to an int silently drops the decimal." << std::endl;
    std::cout << "  The compiler warns so you can make the truncation explicit." << std::endl;
    std::cout << std::endl;

    // The FIX: use an explicit cast to show it's intentional.
    double pi = 3.14159;
    int rounded = static_cast<int>(pi); // explicit - no warning
    std::cout << "  pi = " << pi << ", rounded = " << rounded << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------------------------
    // SUMMARY
    // -----------------------------------------------------------------------
    std::cout << "--- Best Practices ---" << std::endl;
    std::cout << "1. Turn warning levels UP (MSVC: /W4, GCC: -Wall -Wextra)." << std::endl;
    std::cout << "2. Treat warnings as errors (MSVC: /WX, GCC: -Werror)." << std::endl;
    std::cout << "3. Fix every warning immediately - don't let them pile up." << std::endl;
    std::cout << "4. Warnings often reveal real bugs hiding in plain sight." << std::endl;

    return 0;
}
