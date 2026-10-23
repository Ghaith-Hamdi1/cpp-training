// internal.cpp - Demonstrates internal linkage from another translation unit
// This file has its OWN copies of internally-linked identifiers.

#include <iostream>
#include "internal.h"

// -------------------------------------------------
// 1. static global - internal linkage
// -------------------------------------------------
// This is a DIFFERENT variable from main.cpp's s_count.
// Both files can have their own 'static int s_count' without conflict.
static int s_count{777};

// -------------------------------------------------
// 2. const global - also internal linkage by default
// -------------------------------------------------
// This is a different 'g_gravity' from main.cpp's - no conflict.
const double g_gravity{1.62}; // Moon gravity, separate copy

// -------------------------------------------------
// 3. Unnamed namespace - modern alternative to 'static'
// -------------------------------------------------
// Everything inside an unnamed namespace has internal linkage.
// Preferred over 'static' in modern C++ because it also works for
// types, enums, and other identifiers (not just variables/functions).
namespace
{
    int secretValue{12345};

    void secretHelper()
    {
        std::cout << "  secretHelper() - only visible in internal.cpp\n";
        std::cout << "  secretValue = " << secretValue << '\n';
    }
}

// -------------------------------------------------
// Externally-visible functions (so main.cpp can observe)
// -------------------------------------------------
int getInternalCount()
{
    return s_count; // Returns internal.cpp's s_count (777)
}

void printUnnamedDemo()
{
    std::cout << "  Calling secretHelper() from unnamed namespace:\n";
    secretHelper();
    std::cout << "  internal.cpp's g_gravity (Moon) = " << g_gravity << '\n';
}
