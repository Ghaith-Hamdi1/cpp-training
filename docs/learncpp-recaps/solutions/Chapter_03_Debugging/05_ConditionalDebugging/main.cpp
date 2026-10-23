// Chapter 3 - Project 05: Conditional Debugging with #ifdef
// ===========================================================
//
// KEY CONCEPT:
//   Scattering std::cerr statements throughout your code is messy:
//   you must add them to debug and remove them when done, risking
//   accidentally leaving some behind or removing the wrong code.
//
//   A better approach: wrap all debug output in #ifdef ENABLE_DEBUG.
//   - To enable debug output:  #define ENABLE_DEBUG   (or compile with -DENABLE_DEBUG)
//   - To disable debug output: comment out / remove the #define
//
//   This way, toggling debugging is a ONE-LINE change, and the debug
//   code is compiled away entirely when disabled (zero runtime cost).
//
// EXERCISE: Comment out the #define below and recompile. All debug
//           output disappears without touching any other code.

#include <iostream>

// Toggle this single line to enable/disable ALL debug output:
#define ENABLE_DEBUG

int factorial(int n)
{
#ifdef ENABLE_DEBUG
    std::cerr << "[DEBUG] factorial(" << n << ") called\n";
#endif

    if (n <= 1)
    {
#ifdef ENABLE_DEBUG
        std::cerr << "[DEBUG] factorial base case, returning 1\n";
#endif
        return 1;
    }

    int result{n * factorial(n - 1)};

#ifdef ENABLE_DEBUG
    std::cerr << "[DEBUG] factorial(" << n << ") returning " << result << '\n';
#endif

    return result;
}

int main()
{
#ifdef ENABLE_DEBUG
    std::cerr << "[DEBUG] Debug mode is ON\n";
#endif

    std::cout << "=== Conditional Debugging Demo ===\n\n";

    int num{5};
    std::cout << num << "! = " << factorial(num) << '\n';

    // ALTERNATIVE: Instead of #define in source, you can pass the flag
    // at compile time without modifying the file:
    //   g++ -DENABLE_DEBUG -std=c++20 main.cpp -o main
    //   cl /DENABLE_DEBUG /std:c++20 main.cpp        (MSVC)
    //
    // This is the preferred approach for real projects - the source
    // file never needs to change between debug and release builds.

    // BEST PRACTICE: For larger projects, consider using a logging
    // library (e.g., plog or spdlog) instead of raw preprocessor macros.
    // Loggers support severity levels, file output, and timestamps.

    return 0;
}
