// Chapter 7 - Project 04: Global Variables
// ==========================================
// Variables declared outside all functions are global variables.
// Properties:
//   - File scope:     accessible from point of declaration to end of file
//   - Static duration: created at program start, destroyed at program end
//   - Linkage:        non-const globals → external by default
//                     const/constexpr globals → internal by default
// Best practice: prefix globals with g_ for clarity.

#include <iostream>

// -------------------------------------------------
// 1. Non-const global variable (external linkage by default)
// -------------------------------------------------
// Accessible from any file (if forward-declared with extern).
// Prefix with g_ to distinguish from local variables.
int g_errorCount{0};

// -------------------------------------------------
// 2. Const global variable (internal linkage by default)
// -------------------------------------------------
// Only visible within this translation unit (this .cpp file).
const double g_pi{3.14159265358979};

// -------------------------------------------------
// 3. Constexpr global variable (internal linkage by default)
// -------------------------------------------------
// Evaluated at compile time. Internal linkage by default.
constexpr int g_maxStudents{30};

// -------------------------------------------------
// 4. Global variables are zero-initialized by default
//    (if no initializer is provided)
// -------------------------------------------------
int g_uninitialized; // Zero-initialized to 0 (unlike local variables!)

// -------------------------------------------------
// Helper functions that can access globals
// -------------------------------------------------
void recordError()
{
    ++g_errorCount; // Modifies the global directly
}

void printStatus()
{
    std::cout << "  Error count: " << g_errorCount << '\n';
    std::cout << "  Pi:          " << g_pi << '\n';
    std::cout << "  Max students:" << g_maxStudents << '\n';
}

int main()
{
    // -------------------------------------------------
    // 1. Globals are accessible everywhere after declaration
    // -------------------------------------------------
    std::cout << "1. Initial state:\n";
    printStatus();

    // -------------------------------------------------
    // 2. Any function can modify non-const globals
    // -------------------------------------------------
    std::cout << "\n2. After recording 3 errors:\n";
    recordError();
    recordError();
    recordError();
    printStatus();

    // -------------------------------------------------
    // 3. Globals have static duration - they persist
    //    for the entire program lifetime
    // -------------------------------------------------
    std::cout << "\n3. Global g_errorCount persists: " << g_errorCount << '\n';

    // -------------------------------------------------
    // 4. Zero-initialization of global variables
    // -------------------------------------------------
    std::cout << "\n4. Uninitialized global (zero-initialized): "
              << g_uninitialized << '\n'; // Guaranteed to be 0

    // -------------------------------------------------
    // 5. Const/constexpr globals cannot be modified
    // -------------------------------------------------
    // g_pi = 3.0;        // ERROR: assignment of read-only variable
    // g_maxStudents = 50; // ERROR: assignment of read-only variable
    std::cout << "\n5. Const globals are read-only:\n";
    std::cout << "  g_pi = " << g_pi << '\n';
    std::cout << "  g_maxStudents = " << g_maxStudents << '\n';

    // -------------------------------------------------
    // Summary of linkage defaults
    // -------------------------------------------------
    std::cout << "\n--- Linkage Defaults ---\n";
    std::cout << "  int g_errorCount    -> external linkage (non-const)\n";
    std::cout << "  const double g_pi   -> internal linkage (const)\n";
    std::cout << "  constexpr int g_max -> internal linkage (constexpr)\n";

    return 0;
}
