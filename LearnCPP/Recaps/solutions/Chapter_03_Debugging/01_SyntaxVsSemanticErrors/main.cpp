// Chapter 3 - Project 01: Syntax vs. Semantic Errors
// ====================================================
//
// KEY CONCEPT:
//   - A SYNTAX ERROR violates C++ grammar rules and is caught by the compiler.
//     Examples: missing semicolons, mismatched braces, typos in keywords.
//
//   - A SEMANTIC ERROR (logic error) is syntactically valid C++ that compiles
//     and links without problems, but produces incorrect results at runtime.
//     Examples: using '-' instead of '+', off-by-one loops, uninitialized variables.
//
// This program demonstrates a semantic error: a function that is supposed to
// add two numbers but subtracts them instead. The compiler cannot catch this
// because the code is perfectly valid C++ - only a human reviewing the output
// can spot the mistake.
//
// TRY IT: Compile and run. Notice the wrong answer. Then fix the bug.

#include <iostream>

// BUG: This function is named "add" but actually subtracts!
// This is a classic semantic error - the compiler sees valid C++ and stays silent.
int add(int x, int y)
{
    return x - y; // <-- Semantic error: should be x + y
}

int main()
{
    // --- Syntax error examples (commented out so the program compiles) ---
    // Uncomment any line below to see a compiler error:

    // std::cout << "Hello"   // Missing semicolon - syntax error
    // int 2bad = 5;          // Variable names can't start with a digit - syntax error
    // int x = (3 + 4;        // Mismatched parentheses - syntax error

    // --- Semantic error demonstration ---
    int a{8};
    int b{3};

    std::cout << "Attempting to add " << a << " + " << b << '\n';
    std::cout << "Result: " << add(a, b) << '\n'; // Prints 5 instead of 11!
    std::cout << "Expected: " << (a + b) << '\n';

    // The compiler raised zero warnings - the bug is purely logical.
    // Lesson: Always verify your program's output against expected results.

    return 0;
}
