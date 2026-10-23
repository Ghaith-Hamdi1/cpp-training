// globals.cpp - Definitions of externally-linked variables and functions
// These are the actual definitions; other files use forward declarations to access them.

#include "globals.h"
#include <string_view>

// -------------------------------------------------
// 1. Non-const global - external linkage by default
// -------------------------------------------------
// No 'extern' needed on the definition (it's external by default for non-const).
int g_x{42};

// -------------------------------------------------
// 2. const global with EXTERNAL linkage
// -------------------------------------------------
// Normally const globals have internal linkage. Adding 'extern' on the
// DEFINITION makes it external, creating a single shared copy across files.
extern const int g_maxScore{100};

// -------------------------------------------------
// 3. constexpr global - defined here, but other files can only
//    forward-declare it as 'const' (not constexpr)
// -------------------------------------------------
// In the defining file, it IS constexpr. But in other files (via extern const),
// the compiler can't guarantee the value is known at compile time.
extern constexpr int g_compileTimeMax{256};

// -------------------------------------------------
// 4. Functions - external linkage by default
// -------------------------------------------------
double computeArea(double radius)
{
    constexpr double pi{3.14159265358979};
    return pi * radius * radius;
}

std::string_view getMessage()
{
    return "Hello from globals.cpp!";
}
