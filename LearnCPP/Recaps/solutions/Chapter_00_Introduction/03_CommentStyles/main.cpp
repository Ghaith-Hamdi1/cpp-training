// ============================================================================
// Chapter 0, Project 03 - Comment Styles
// Concept: Single-line and multi-line comments in C++.
// ============================================================================
//
// KEY IDEAS:
//   - Comments are notes for humans - the compiler ignores them entirely.
//   - Single-line comment:  //  (everything after // on that line is a comment)
//   - Multi-line comment:   /* ... */  (everything between the markers)
//   - Good comments explain WHY, not WHAT (the code should explain what).
//   - Comments help future-you (and teammates) understand your reasoning.
//   - Don't over-comment obvious code; don't under-comment tricky code.
//
// BUILD:  g++ -std=c++20 -Wall -Wextra -Werror -o CommentStyles main.cpp
// ============================================================================

#include <iostream>

int main()
{
    std::cout << "=== C++ Comment Styles ===" << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------------------------
    // STYLE 1: Single-line comments (using //)
    // -----------------------------------------------------------------------
    // Everything after // on a line is ignored by the compiler.
    // Use these for brief explanations on one line.

    std::cout << "1. Single-line comments use //" << std::endl;

    int x = 42; // You can also put a comment after code on the same line

    // -----------------------------------------------------------------------
    // STYLE 2: Multi-line comments (using /* ... */)
    // -----------------------------------------------------------------------
    /*
        Multi-line comments can span
        multiple lines. They start with
        slash-star and end with star-slash.

        Use these for longer explanations,
        function documentation, or temporarily
        disabling blocks of code.
    */

    std::cout << "2. Multi-line comments use /* ... */" << std::endl;

    // -----------------------------------------------------------------------
    // STYLE 3: Using comments to disable code (commenting out)
    // -----------------------------------------------------------------------
    // You can "comment out" code to temporarily disable it:

    // std::cout << "This line will NOT execute." << std::endl;

    /* You can also comment out multiple lines at once:
    std::cout << "Line A" << std::endl;
    std::cout << "Line B" << std::endl;
    */

    std::cout << "3. Comments can disable code temporarily." << std::endl;

    // -----------------------------------------------------------------------
    // GOOD vs BAD comments
    // -----------------------------------------------------------------------

    // BAD: restating what the code already says
    // int y = 10; // set y to 10          <-- don't do this

    // GOOD: explaining WHY
    int maxRetries = 3; // Limited to 3 to avoid overwhelming the server

    std::cout << std::endl;
    std::cout << "x = " << x << std::endl;
    std::cout << "maxRetries = " << maxRetries << std::endl;
    std::cout << std::endl;
    std::cout << "Remember: comments are for humans, not the compiler!" << std::endl;

    return 0;
}
