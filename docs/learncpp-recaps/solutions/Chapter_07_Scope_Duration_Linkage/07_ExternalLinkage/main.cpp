// Chapter 7 - Project 07: External Linkage
// ===========================================
// External linkage means an identifier can be seen across translation units.
//
// Defaults:
//   - Functions:             external linkage by default
//   - Non-const global vars: external linkage by default
//
// Use 'extern' to forward-declare a variable defined in another file.
//
// PITFALL: extern int g_x;     → forward declaration (no initializer!)
//          extern int g_x{1};  → definition (with initializer) - different!
//
// PITFALL: constexpr variables CANNOT be forward declared as constexpr.
//          You can only forward declare them as const (losing constexpr-ness).
//
// Compile: cl /std:c++20 /EHsc main.cpp globals.cpp
//          g++ -std=c++20 main.cpp globals.cpp

#include <iostream>
#include "globals.h"

int main()
{
    // -------------------------------------------------
    // 1. Accessing an external non-const global
    // -------------------------------------------------
    std::cout << "1. g_x (from globals.cpp) = " << g_x << '\n';
    g_x = 99; // We can modify it - it's non-const and external
    std::cout << "   After g_x = 99: " << g_x << '\n';

    // -------------------------------------------------
    // 2. Accessing an external const global
    // -------------------------------------------------
    // In globals.cpp: extern const int g_maxScore{ 100 };
    // Forward declared in globals.h: extern const int g_maxScore;
    std::cout << "\n2. g_maxScore (extern const) = " << g_maxScore << '\n';

    // -------------------------------------------------
    // 3. Functions have external linkage by default
    // -------------------------------------------------
    // No 'extern' needed for function declarations - they're extern by default
    std::cout << "\n3. computeArea(5.0) = " << computeArea(5.0) << '\n';
    std::cout << "   getMessage()     = " << getMessage() << '\n';

    // -------------------------------------------------
    // 4. constexpr forward declaration limitation
    // -------------------------------------------------
    // g_compileTimeMax is defined as constexpr in globals.cpp,
    // but we can only forward-declare it as 'extern const' (not constexpr).
    // This means we CANNOT use it in constant expressions in this file.
    std::cout << "\n4. g_compileTimeMax (forward declared as const) = "
              << g_compileTimeMax << '\n';
    // constexpr int arr[g_compileTimeMax]; // ERROR: not a constant expression here
    std::cout << "   (Cannot use in constexpr context from another file!)\n";

    // -------------------------------------------------
    // 5. Summary of extern usage
    // -------------------------------------------------
    std::cout << "\n--- External Linkage Summary ---\n";
    std::cout << "  extern int g_x;           -> forward declaration\n";
    std::cout << "  extern int g_x{ 1 };      -> definition (has initializer)\n";
    std::cout << "  extern const int g_y;     -> forward decl of const global\n";
    std::cout << "  Functions                 -> external linkage by default\n";
    std::cout << "  constexpr vars            -> cannot forward declare as constexpr\n";

    return 0;
}
