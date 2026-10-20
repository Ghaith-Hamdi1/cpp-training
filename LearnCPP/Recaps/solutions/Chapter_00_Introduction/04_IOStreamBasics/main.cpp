// ============================================================================
// Chapter 0, Project 04 - I/O Stream Basics
// Concept: Using <iostream> for console input and output.
// ============================================================================
//
// KEY IDEAS (Sections 0.7, 0.8):
//   - #include <iostream> is REQUIRED to use std::cout and std::cin.
//   - std::cout  - the standard character output stream (prints to console).
//   - std::cin   - the standard character input stream (reads from keyboard).
//   - std::endl  - outputs a newline character AND flushes the output buffer.
//   - '\n'       - outputs a newline without flushing (often preferred).
//   - <<         - the insertion operator (inserts data INTO the output stream).
//   - >>         - the extraction operator (extracts data FROM the input stream).
//   - You can chain multiple << or >> operators in a single statement.
//   - Everything in the standard library lives in the std:: namespace.
//
// COMMON PITFALL:
//   Forgetting #include <iostream> or forgetting the std:: prefix will cause
//   compilation errors. These are the #1 and #2 beginner mistakes!
//
// BUILD:  g++ -std=c++20 -Wall -Wextra -Werror -o IOStreamBasics main.cpp
// ============================================================================

#include <iostream> // REQUIRED - gives us std::cout, std::cin, std::endl

int main()
{
    std::cout << "=== I/O Stream Basics ===" << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------------------------
    // OUTPUT with std::cout
    // -----------------------------------------------------------------------

    // Basic output:
    std::cout << "Hello from std::cout!" << std::endl;

    // Chaining multiple items with <<
    std::cout << "You can " << "chain " << "multiple " << "items." << std::endl;

    // Outputting numbers:
    std::cout << "An integer: " << 42 << std::endl;
    std::cout << "A double:   " << 3.14159 << std::endl;

    // Using '\n' instead of std::endl (no flush - slightly faster):
    std::cout << "Using backslash-n for newline.\n";
    std::cout << '\n'; // Just a blank line

    // -----------------------------------------------------------------------
    // INPUT with std::cin
    // -----------------------------------------------------------------------

    std::cout << "What is your name? ";
    std::string name; // A variable to store the user's input
    std::cin >> name; // >> extracts input from the keyboard

    std::cout << "Hello, " << name << "!" << std::endl;
    std::cout << '\n';

    std::cout << "Enter a whole number: ";
    int number = 0;
    std::cin >> number; // Reads an integer from the keyboard

    std::cout << "You entered: " << number << std::endl;
    std::cout << "Doubled:     " << number * 2 << std::endl;
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // std::endl vs '\n'
    // -----------------------------------------------------------------------
    // std::endl = newline + flush (forces output to appear immediately).
    // '\n'     = newline only (faster, usually preferred).
    // Use std::endl when you need guaranteed immediate output (e.g. before
    // waiting for input). Use '\n' for general output.

    std::cout << "Tip: Prefer '\\n' over std::endl for performance.\n";
    std::cout << "Use std::endl when you need to flush the buffer.\n";

    return 0;
}
