// constants.h - Demonstrates TRADITIONAL header guards (#ifndef)
//
// Convention: the guard macro is typically the filename in UPPER_CASE
// with dots replaced by underscores.
//
// The first time this header is processed, CONSTANTS_H is not defined,
// so the preprocessor enters the #ifndef block and defines it.
// On any subsequent inclusion in the SAME translation unit, CONSTANTS_H
// is already defined, so the #ifndef check fails and the entire block
// is skipped.

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string_view>

// Using inline constexpr so these can safely appear in a header
// included by multiple .cpp files (they have internal linkage or
// are implicitly inline with constexpr at namespace scope).
constexpr std::string_view appName{"HeaderGuard Demo"};
constexpr int appVersion{1};

#endif // CONSTANTS_H
