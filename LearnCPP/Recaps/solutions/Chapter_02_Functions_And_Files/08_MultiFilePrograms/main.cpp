// Chapter 2 - Project 08: Multi-File Programs
// Concept: Splitting code across multiple .cpp files
//
// In real projects, code is spread across many source files.  Each .cpp
// file is compiled independently into an object file.  The compiler does
// NOT know about other .cpp files - it only sees the current one.
//
// To call a function defined in another file, you need a forward
// declaration (or an #include of a header that provides one).
//
// The LINKER then connects the object files together, resolving all the
// cross-file function calls.
//
// This project has three files:
//   main.cpp   - the entry point; calls functions from other files
//   math.cpp   - defines add() and multiply()
//   math.h     - header with forward declarations for math.cpp
//
// Build all .cpp files together:
//   g++ -std=c++20 main.cpp math.cpp -o main
//   (or add both .cpp files to your IDE project)
//
// IMPORTANT: Do NOT #include "math.cpp".  Instead, compile it alongside
// main.cpp and let the linker connect them.
// -----------------------------------------------------------------------

#include <iostream>
#include "math.h" // Provides forward declarations for add() and multiply()

int main()
{
    std::cout << "=== Project 08: Multi-File Programs ===\n\n";

    // These functions are DEFINED in math.cpp.
    // We can call them because math.h provides forward declarations.
    std::cout << "add(3, 4)      = " << add(3, 4) << '\n';
    std::cout << "multiply(5, 6) = " << multiply(5, 6) << '\n';
    std::cout << "add(10, 20)    = " << add(10, 20) << '\n';

    // If we forgot to compile math.cpp, or forgot to add it to the
    // project, we'd get a linker error:
    //   "unresolved external symbol: add"
    // The compiler would be happy (it saw the declaration), but the
    // linker can't find the definition.

    return 0;
}
