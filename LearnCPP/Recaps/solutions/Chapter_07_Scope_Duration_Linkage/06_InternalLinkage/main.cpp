// Chapter 7 - Project 06: Internal Linkage
// ===========================================
// Internal linkage means an identifier is only visible within its
// own translation unit (the .cpp file after preprocessing).
//
// How to get internal linkage:
//   - const/constexpr global variables have it BY DEFAULT
//   - Use the 'static' keyword on non-const globals or functions
//   - Use an unnamed namespace (modern C++ preferred approach)
//
// This file is the main driver. Compile with internal.cpp:
//   cl /std:c++20 /EHsc main.cpp internal.cpp
//   g++ -std=c++20 main.cpp internal.cpp

#include <iostream>
#include "internal.h"

// -------------------------------------------------
// 1. 'static' global variable - internal linkage
// -------------------------------------------------
// This variable is ONLY visible in main.cpp.
// If internal.cpp also defines 'static int s_count', it's a DIFFERENT variable.
static int s_count{0};

// -------------------------------------------------
// 2. const global - internal linkage by default
// -------------------------------------------------
const double g_gravity{9.81}; // Internal linkage (no 'static' needed)

// -------------------------------------------------
// 3. constexpr global - internal linkage by default
// -------------------------------------------------
constexpr int g_maxItems{100}; // Internal linkage (no 'static' needed)

// -------------------------------------------------
// 4. 'static' function - internal linkage
// -------------------------------------------------
// This helper function is only callable from main.cpp.
static void localHelper()
{
    std::cout << "  localHelper() in main.cpp called.\n";
}

int main()
{
    // 1. static global variable
    std::cout << "1. static global s_count (main.cpp): " << s_count << '\n';
    s_count = 42;
    std::cout << "   After assignment: s_count = " << s_count << '\n';

    // The other file has its OWN s_count (they don't interfere)
    std::cout << "   internal.cpp's s_count: " << getInternalCount() << '\n';

    // 2. const global (internal linkage by default)
    std::cout << "\n2. const global g_gravity = " << g_gravity << '\n';

    // 3. constexpr global (internal linkage by default)
    std::cout << "3. constexpr global g_maxItems = " << g_maxItems << '\n';

    // 4. static function - only visible in this file
    std::cout << "\n4. Calling static function:\n";
    localHelper(); // Works - defined in this file

    // 5. Unnamed namespace (demonstrated in internal.cpp)
    std::cout << "\n5. Unnamed namespace (in internal.cpp):\n";
    printUnnamedDemo();

    // 6. Summary
    std::cout << "\n--- Internal Linkage Summary ---\n";
    std::cout << "  'static' on globals/functions   -> internal linkage\n";
    std::cout << "  'const' globals                 -> internal linkage (default)\n";
    std::cout << "  'constexpr' globals             -> internal linkage (default)\n";
    std::cout << "  Unnamed namespaces              -> internal linkage (modern)\n";

    return 0;
}
