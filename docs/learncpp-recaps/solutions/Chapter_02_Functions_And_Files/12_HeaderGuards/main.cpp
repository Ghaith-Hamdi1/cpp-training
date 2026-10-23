// Chapter 2 - Project 12: Header Guards
// Concept: Preventing duplicate inclusion with #ifndef/#define/#endif
//          and #pragma once
//
// Problem: If a header is #included more than once in the same
// translation unit (directly or indirectly), everything in it gets
// pasted multiple times - causing "duplicate definition" errors.
//
// Solution: Header guards ensure the header's contents are processed
// only ONCE per translation unit, no matter how many times it's included.
//
// Two approaches:
//   1. Traditional header guard:
//        #ifndef UNIQUE_NAME_H
//        #define UNIQUE_NAME_H
//        // ... declarations ...
//        #endif
//
//   2. #pragma once (non-standard but universally supported):
//        #pragma once
//        // ... declarations ...
//
// IMPORTANT: Header guards do NOT prevent a header from being included
// once in EACH of multiple different .cpp files - that's by design
// (each .cpp is an independent translation unit).
//
// This project demonstrates the problem and both solutions:
//   constants.h  - uses traditional #ifndef guards
//   utils.h      - uses #pragma once
//   helpers.h    - includes both constants.h and utils.h (transitive include)
//   main.cpp     - includes helpers.h AND constants.h directly
//                  (without guards, constants.h would be duplicated)
//
// Build: g++ -std=c++20 main.cpp -o main
//        (single .cpp - headers are declaration-only)
// -----------------------------------------------------------------------

#include <iostream>

// Notice: main.cpp includes helpers.h, which internally includes
// constants.h and utils.h.  We ALSO include constants.h directly.
// Without header guards, constants.h would be pasted TWICE - error!
// With header guards, the second inclusion is harmlessly skipped.
#include "helpers.h"
#include "constants.h" // Already included via helpers.h - guard protects us

int main()
{
    std::cout << "=== Project 12: Header Guards ===\n\n";

    // 1. Using constants from constants.h (traditional header guard)
    std::cout << "--- constants.h (#ifndef guard) ---\n";
    std::cout << "appName:    " << appName << '\n';
    std::cout << "appVersion: " << appVersion << '\n';

    // 2. Using the function from utils.h (#pragma once)
    std::cout << "\n--- utils.h (#pragma once) ---\n";
    std::cout << "max(10, 20) = " << maxOf(10, 20) << '\n';

    // 3. Using the function from helpers.h
    std::cout << "\n--- helpers.h (includes both headers) ---\n";
    printAppInfo();

    // Without header guards, this program would fail to compile because
    // constants.h would be included twice in this translation unit:
    //   once via #include "helpers.h" → #include "constants.h"
    //   once via #include "constants.h" directly
    // The second paste would re-define appName and appVersion → error.

    std::cout << "\nAll headers included without duplication errors!\n";

    return 0;
}
