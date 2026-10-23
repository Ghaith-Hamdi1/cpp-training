// Chapter 11 - Project 06: Default Arguments
// ================================================================
// Default arguments provide fallback values for parameters the caller
// may omit.  Key rules:
//   1. Must be rightmost parameters (can't skip left/middle ones)
//   2. Should be declared in the forward declaration (header), not the definition
//   3. Can only be declared once per translation unit
//   4. Can interact with overloading to cause ambiguity

#include <iostream>
#include <string_view>

// ---------------------------------------------------------------
// Rule 1: Defaults must be rightmost
// ---------------------------------------------------------------
// void badDefault(int x = 1, int y) { }  // ERROR: y has no default but x does
// C++ does not allow skipping arguments - you can only omit from the right.

// ---------------------------------------------------------------
// Basic usage: a function with multiple default arguments
// ---------------------------------------------------------------
void openWindow(std::string_view title = "Untitled",
                int width = 800,
                int height = 600)
{
    std::cout << "Window: \"" << title << "\" "
              << width << "x" << height << '\n';
}

// ---------------------------------------------------------------
// Rule 2 & 3: Declaration vs definition placement
// ---------------------------------------------------------------
// In a multi-file project, defaults go in the forward declaration (header):
//     // window.h
//     void openWindow(std::string_view title = "Untitled",
//                     int width = 800, int height = 600);
//
//     // window.cpp
//     void openWindow(std::string_view title, int width, int height) { ... }
//
// You CANNOT put the default in both the declaration and the definition
// in the same translation unit - that would be "redeclaring" the default.

// ---------------------------------------------------------------
// Rule 4: Default arguments + overloading → potential ambiguity
// ---------------------------------------------------------------
void log(std::string_view message)
{
    std::cout << "[LOG] " << message << '\n';
}

// If we had: void log(std::string_view message, int level = 0) { ... }
// Then log("hello") would be ambiguous:
//   - log(string_view)          - exact match
//   - log(string_view, int=0)   - also a valid match (second arg defaulted)
// The compiler can't choose → compile error.

// Non-ambiguous version: only one overload, using a default
void logLevel(std::string_view message, int level = 0)
{
    std::cout << "[LEVEL " << level << "] " << message << '\n';
}

// ---------------------------------------------------------------
// Practical example: a function with sensible defaults
// ---------------------------------------------------------------
void printRepeat(std::string_view text, int times = 1, char separator = ' ')
{
    for (int i{0}; i < times; ++i)
    {
        if (i > 0)
            std::cout << separator;
        std::cout << text;
    }
    std::cout << '\n';
}

int main()
{
    std::cout << "=== Basic default arguments ===\n";
    openWindow();                    // all defaults
    openWindow("My App");            // width/height default
    openWindow("My App", 1024);      // height defaults
    openWindow("My App", 1024, 768); // no defaults used

    // You CANNOT skip an argument and set a later one:
    // openWindow("My App", , 768);           // ERROR: not valid C++ syntax

    std::cout << "\n=== Default arguments with logging ===\n";
    log("simple message");
    logLevel("info message"); // level defaults to 0
    logLevel("critical!", 3); // level explicitly set

    std::cout << "\n=== printRepeat with defaults ===\n";
    printRepeat("Hello");      // times=1, separator=' '
    printRepeat("Ha", 3);      // separator=' '
    printRepeat("Go", 4, '-'); // all args supplied

    return 0;
}
