// Chapter 2 - Project 10: The Preprocessor
// Concept: Preprocessor directives - #include, #define, #ifdef, #if 0
//
// Before the compiler sees your code, the PREPROCESSOR runs.  It processes
// lines that begin with '#' (directives).  These are NOT C++ statements -
// they don't end with semicolons and are resolved line by line.
//
// Key directives:
//   #include <file>    - pastes the contents of a system/library header
//   #include "file"    - pastes the contents of a user header
//   #define MACRO       - defines a preprocessor macro (object-like)
//   #define MACRO(x)    - defines a function-like macro (avoid in modern C++)
//   #ifdef / #ifndef    - conditional compilation (is macro defined?)
//   #if / #elif / #else / #endif - conditional compilation (expression)
//   #if 0 ... #endif    - quick way to "comment out" a block of code
//
// Directives are file-scoped and resolved top-to-bottom.
// In modern C++, prefer constexpr variables over #define for constants,
// and inline/constexpr functions over function-like macros.
// -----------------------------------------------------------------------

#include <iostream> // Preprocessor pastes the entire <iostream> header here

// -----------------------------------------------------------------------
// #define - object-like macro (acts as a text substitution)
// Prefer constexpr in modern C++, but this shows how it works.
// -----------------------------------------------------------------------
#define APP_VERSION "2.0.1"

// -----------------------------------------------------------------------
// Conditional compilation with #ifdef / #ifndef
// -----------------------------------------------------------------------
#define DEBUG_MODE // Comment this line out to disable debug output

// -----------------------------------------------------------------------
// Platform detection example (simulated)
// -----------------------------------------------------------------------
// #define PLATFORM_LINUX   // Uncomment to simulate Linux build
#define PLATFORM_WINDOWS // Simulate Windows build

int main()
{
    std::cout << "=== Project 10: The Preprocessor ===\n\n";

    // 1. #define - text substitution
    std::cout << "--- #define macro ---\n";
    std::cout << "App version: " << APP_VERSION << '\n';

    // 2. Conditional compilation with #ifdef
    std::cout << "\n--- #ifdef DEBUG_MODE ---\n";
#ifdef DEBUG_MODE
    std::cout << "DEBUG_MODE is defined - debug output is ON.\n";
    std::cout << "[DEBUG] Detailed diagnostic information here.\n";
#else
    std::cout << "DEBUG_MODE is NOT defined - debug output is OFF.\n";
#endif

    // 3. Conditional compilation with #ifndef (opposite of #ifdef)
    std::cout << "\n--- #ifndef RELEASE_MODE ---\n";
#ifndef RELEASE_MODE
    std::cout << "RELEASE_MODE is NOT defined (we're in development).\n";
#else
    std::cout << "RELEASE_MODE IS defined (production build).\n";
#endif

    // 4. Platform-specific code with #if defined()
    std::cout << "\n--- Platform-specific code ---\n";
#if defined(PLATFORM_WINDOWS)
    std::cout << "Compiling for Windows.\n";
#elif defined(PLATFORM_LINUX)
    std::cout << "Compiling for Linux.\n";
#else
    std::cout << "Unknown platform.\n";
#endif

    // 5. #if 0 - used to disable a block of code (like a multi-line comment)
    std::cout << "\n--- #if 0 (disabled code) ---\n";
    std::cout << "The code below is disabled by #if 0 and will NOT execute.\n";
#if 0
    std::cout << "THIS LINE WILL NEVER COMPILE OR RUN.\n";
    std::cout << "Useful for temporarily disabling code during development.\n";
    // Unlike /* */ comments, #if 0 can nest and won't break on embedded comments.
#endif

    // 6. Why #define macros are discouraged in modern C++
    std::cout << "\n--- Modern C++ alternatives ---\n";
    // Instead of:  #define MAX_SIZE 100
    // Prefer:
    constexpr int maxSize{100};
    std::cout << "constexpr maxSize = " << maxSize << " (preferred over #define)\n";

    return 0;
}
