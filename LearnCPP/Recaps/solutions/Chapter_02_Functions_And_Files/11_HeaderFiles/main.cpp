// Chapter 2 - Project 11: Header Files
// Concept: .h files for forward declarations, #include rules, paired headers
//
// Header files (.h) hold forward declarations so they can be shared
// across multiple source files via #include.
//
// Key rules:
//   • Use angle brackets < > for system/library headers:   #include <iostream>
//   • Use double quotes " " for your own headers:          #include "myheader.h"
//   • A source file should #include its paired header FIRST - this lets
//     the compiler verify that declarations match definitions immediately.
//   • Do NOT put function/variable definitions in headers (for now) - it
//     leads to ODR violations when included in multiple .cpp files.
//   • NEVER #include a .cpp file - add .cpp files to your build instead.
//
// This project has:
//   main.cpp       - entry point
//   geometry.h     - declarations for geometry functions
//   geometry.cpp   - definitions for geometry functions
//   greeting.h     - declarations for greeting functions
//   greeting.cpp   - definitions for greeting functions
//
// Build: g++ -std=c++20 main.cpp geometry.cpp greeting.cpp -o main
// -----------------------------------------------------------------------

#include <iostream>

// Include our project headers - these provide the forward declarations.
// Source files use double quotes " " for project-local headers.
#include "geometry.h"
#include "greeting.h"

int main()
{
    std::cout << "=== Project 11: Header Files ===\n\n";

    // 1. Using functions from geometry.h / geometry.cpp
    std::cout << "--- Geometry functions (from geometry.h) ---\n";
    double r{5.0};
    std::cout << "Circle radius:        " << r << '\n';
    std::cout << "Circle area:          " << circleArea(r) << '\n';
    std::cout << "Circle circumference: " << circleCircumference(r) << '\n';

    // 2. Using functions from greeting.h / greeting.cpp
    std::cout << "\n--- Greeting functions (from greeting.h) ---\n";
    sayHello("Alice");
    sayGoodbye("Bob");

    // Key lessons:
    // • We only #include the .h files, NOT the .cpp files.
    // • Each .cpp file is compiled independently.
    // • The linker connects the object files so main.cpp can call
    //   functions defined in geometry.cpp and greeting.cpp.

    return 0;
}
