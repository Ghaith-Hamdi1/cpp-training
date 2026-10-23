// ============================================================================
// Chapter 0, Project 08 - Common Mistakes
// Concept: Frequent beginner pitfalls and how to avoid them.
// ============================================================================
//
// KEY IDEAS (Section 0.8):
//   - Forgetting #include <iostream> → compilation error.
//   - Omitting std:: before cout/cin/endl → compilation error.
//   - Confusing similar characters: l vs 1, O vs 0.
//   - Creating a Windows GUI project instead of a console project → linker
//     error about missing WinMain.
//   - Leaving precompiled headers enabled in Visual Studio → mysterious
//     #include "pch.h" errors.
//
// This file compiles cleanly - the mistakes are shown in comments so you
// can understand them without breaking the build.
//
// BUILD:  g++ -std=c++20 -Wall -Wextra -Werror -o CommonMistakes main.cpp
// ============================================================================

#include <iostream> // Mistake #1 fix: always include this for I/O

int main()
{
    std::cout << "=== Common C++ Beginner Mistakes ===" << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------------------------
    // MISTAKE #1: Forgetting #include <iostream>
    // -----------------------------------------------------------------------
    std::cout << "Mistake #1: Forgetting #include <iostream>" << std::endl;
    std::cout << "  Without it, std::cout and std::cin are undefined." << std::endl;
    std::cout << "  Error: 'cout' is not a member of 'std'" << std::endl;
    std::cout << "  Fix:   Add #include <iostream> at the top of your file." << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------------------------
    // MISTAKE #2: Omitting std:: prefix
    // -----------------------------------------------------------------------
    // WRONG:  cout << "Hello";       // Error: 'cout' was not declared
    // RIGHT:  std::cout << "Hello";  // Works!

    std::cout << "Mistake #2: Omitting the std:: prefix" << std::endl;
    std::cout << "  cout, cin, endl all live in the std namespace." << std::endl;
    std::cout << "  WRONG:  cout << \"Hello\";" << std::endl;
    std::cout << "  RIGHT:  std::cout << \"Hello\";" << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------------------------
    // MISTAKE #3: Confusing similar-looking characters
    // -----------------------------------------------------------------------
    std::cout << "Mistake #3: Confusing similar characters" << std::endl;
    std::cout << "  l (lowercase L) vs 1 (one)" << std::endl;
    std::cout << "  O (uppercase O) vs 0 (zero)" << std::endl;
    std::cout << "  Use a monospace programming font to tell them apart!" << std::endl;
    std::cout << std::endl;

    // Let's demonstrate the difference:
    int val1 = 1;  // This is the number one
    int val_l = 2; // This variable has a lowercase L
    std::cout << "  val1 (with digit 1) = " << val1 << std::endl;
    std::cout << "  val_l (with letter l) = " << val_l << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------------------------
    // MISTAKE #4: Missing semicolons
    // -----------------------------------------------------------------------
    // WRONG:  std::cout << "Hello"     // Error: expected ';'
    // RIGHT:  std::cout << "Hello";    // Every statement needs a semicolon!

    std::cout << "Mistake #4: Forgetting the semicolon at end of statements" << std::endl;
    std::cout << "  Every C++ statement must end with a semicolon (;)." << std::endl;
    std::cout << "  The error message may point to the NEXT line, not the" << std::endl;
    std::cout << "  line where the semicolon is actually missing." << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------------------------
    // MISTAKE #5: Wrong project type (Windows GUI vs Console)
    // -----------------------------------------------------------------------
    std::cout << "Mistake #5: Creating a Windows GUI project by accident" << std::endl;
    std::cout << "  Symptom: linker error about missing WinMain." << std::endl;
    std::cout << "  Fix:     Create a Console Application project instead." << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------------------------
    // MISTAKE #6: Precompiled header errors (Visual Studio)
    // -----------------------------------------------------------------------
    std::cout << "Mistake #6: Precompiled header errors in Visual Studio" << std::endl;
    std::cout << "  Symptom: error about missing 'pch.h' or 'stdafx.h'." << std::endl;
    std::cout << "  Fix:     Disable precompiled headers in project settings," << std::endl;
    std::cout << "           or create an Empty Project from the start." << std::endl;
    std::cout << std::endl;

    std::cout << "--- Summary ---" << std::endl;
    std::cout << "Most beginner errors are simple typos or missing boilerplate." << std::endl;
    std::cout << "Read error messages carefully - they usually tell you exactly" << std::endl;
    std::cout << "what's wrong and on which line." << std::endl;

    return 0;
}
