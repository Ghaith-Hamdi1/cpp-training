// utils.h - Demonstrates #pragma once (modern, non-standard but universal)
//
// #pragma once tells the preprocessor: "only include this file once
// per translation unit."  It is simpler than traditional guards and
// avoids the risk of naming collisions in guard macros.
//
// Virtually all modern compilers support it (MSVC, GCC, Clang).

#pragma once

// An inline function in a header - safe because inline allows
// multiple identical definitions across translation units.
inline int maxOf(int a, int b)
{
    return (a > b) ? a : b;
}
