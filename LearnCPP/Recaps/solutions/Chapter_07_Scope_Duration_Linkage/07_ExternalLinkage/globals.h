// globals.h - Forward declarations for externally-linked identifiers
// These allow main.cpp to access variables/functions defined in globals.cpp.

#ifndef GLOBALS_H
#define GLOBALS_H

#include <string_view>

// Forward declaration of a non-const global variable.
// 'extern' without an initializer = forward declaration (not a definition).
extern int g_x;

// Forward declaration of an extern const global variable.
// The 'extern' is required here because const globals default to internal linkage.
extern const int g_maxScore;

// Forward declaration of a constexpr variable - but as const, NOT constexpr.
// PITFALL: constexpr cannot be forward declared as constexpr in another file!
extern const int g_compileTimeMax;

// Function declarations (extern by default - the 'extern' keyword is optional here)
double computeArea(double radius);
std::string_view getMessage();

#endif
