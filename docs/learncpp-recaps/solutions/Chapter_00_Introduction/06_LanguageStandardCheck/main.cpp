// ============================================================================
// Chapter 0, Project 06 - Language Standard Check
// Concept: Detecting which C++ standard your compiler is using.
// ============================================================================
//
// KEY IDEAS (Sections 0.12, 0.13):
//   - C++ has many versions: C++11, C++14, C++17, C++20, C++23, etc.
//   - Compilers often default to an OLDER standard (e.g., C++14).
//   - You should explicitly set at least C++17 (or C++20 for this course).
//   - The macro __cplusplus reports the active standard as a long integer.
//   - MSVC has a bug: __cplusplus always reports 199711L unless you use
//     the /Zc:__cplusplus flag. Use _MSVC_LANG instead on MSVC.
//
//   Standard version values:
//     C++98/03  →  199711L
//     C++11     →  201103L
//     C++14     →  201402L
//     C++17     →  201703L
//     C++20     →  202002L
//     C++23     →  202302L
//
// BEST PRACTICE:
//   For personal projects, use the latest finalized standard.
//   For professional work, one or two versions back is common.
//   Always explicitly set the standard - never rely on compiler defaults.
//
// BUILD:  g++ -std=c++20 -Wall -Wextra -Werror -o LanguageStandardCheck main.cpp
// ============================================================================

#include <iostream>

int main()
{
    std::cout << "=== C++ Language Standard Check ===" << std::endl;
    std::cout << std::endl;

    // Determine the active language standard.
    // MSVC may report __cplusplus incorrectly, so check _MSVC_LANG first.
    long standard = 0;

#ifdef _MSVC_LANG
    // Microsoft Visual C++ - use _MSVC_LANG for an accurate value
    standard = _MSVC_LANG;
    std::cout << "Compiler: MSVC (Microsoft Visual C++)" << std::endl;
    std::cout << "_MSVC_LANG = " << _MSVC_LANG << std::endl;
#else
    // GCC, Clang, or other compilers - __cplusplus is reliable
    standard = __cplusplus;
    std::cout << "__cplusplus = " << __cplusplus << std::endl;
#endif

    std::cout << std::endl;

    // Decode the numeric value into a human-readable standard name
    std::cout << "Detected standard: ";
    if (standard >= 202302L)
        std::cout << "C++23 or later";
    else if (standard >= 202002L)
        std::cout << "C++20";
    else if (standard >= 201703L)
        std::cout << "C++17";
    else if (standard >= 201402L)
        std::cout << "C++14";
    else if (standard >= 201103L)
        std::cout << "C++11";
    else
        std::cout << "Pre-C++11 (C++98/03 or unknown)";
    std::cout << std::endl;

    std::cout << std::endl;

    // Provide guidance
    if (standard >= 202002L)
    {
        std::cout << "Great! You're using C++20 or newer. You're all set." << std::endl;
    }
    else if (standard >= 201703L)
    {
        std::cout << "C++17 is good, but consider upgrading to C++20." << std::endl;
    }
    else
    {
        std::cout << "WARNING: Your standard is older than C++17!" << std::endl;
        std::cout << "Update your compiler settings to use at least C++17." << std::endl;
        std::cout << std::endl;
        std::cout << "  MSVC:       /std:c++20" << std::endl;
        std::cout << "  GCC/Clang:  -std=c++20" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "--- Standard Version Reference ---" << std::endl;
    std::cout << "C++98/03 = 199711L" << std::endl;
    std::cout << "C++11    = 201103L" << std::endl;
    std::cout << "C++14    = 201402L" << std::endl;
    std::cout << "C++17    = 201703L" << std::endl;
    std::cout << "C++20    = 202002L" << std::endl;
    std::cout << "C++23    = 202302L" << std::endl;

    return 0;
}
