// ============================================================================
// Chapter 0, Project 02 - Program Structure
// Concept: The basic anatomy of a C++ program.
// ============================================================================
//
// KEY IDEAS (Sections 0.4, 0.7):
//   - A C++ program is a sequence of statements executed in order.
//   - Every statement ends with a semicolon (;).
//   - The main() function is the entry point - every program must have one.
//   - main() returns an int: 0 means success, non-zero means failure.
//   - The return value of main() is sent back to the operating system.
//   - Curly braces { } define the body (scope) of a function.
//   - Preprocessor directives like #include are processed before compilation.
//
// BUILD:  g++ -std=c++20 -Wall -Wextra -Werror -o ProgramStructure main.cpp
// ============================================================================

#include <iostream> // Preprocessor directive: includes the I/O library

// The main() function - every C++ program must have exactly one.
// The return type is 'int' (integer).
int main()
{
    // --- Statements ---
    // Each line ending in ';' is a statement.
    // Statements execute sequentially from top to bottom.

    std::cout << "=== C++ Program Structure ===" << std::endl;
    std::cout << std::endl;

    // A declaration statement: creates a variable
    int exitCode = 0;

    // An expression statement: performs an action
    std::cout << "1. This program has a main() function." << std::endl;
    std::cout << "2. It includes <iostream> for console I/O." << std::endl;
    std::cout << "3. Statements execute top-to-bottom." << std::endl;
    std::cout << "4. Each statement ends with a semicolon." << std::endl;
    std::cout << "5. main() returns an int to the OS." << std::endl;
    std::cout << std::endl;

    std::cout << "Returning exit code: " << exitCode << std::endl;

    // The return statement: sends a status code to the operating system.
    // 0 = success, non-zero = some kind of error.
    return exitCode;
}
