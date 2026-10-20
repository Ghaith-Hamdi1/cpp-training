// Chapter 1 - Project 12: Common Pitfalls
// ==========================================
//
// This project demonstrates the most common mistakes beginners make in C++,
// with correct alternatives alongside each pitfall.
//
// PITFALLS COVERED:
//   1. Forgetting a semicolon
//   2. Using = (assignment) instead of == (equality)
//   3. Mixing up << and >> with cout/cin
//   4. Leaving variables uninitialized
//   5. Nesting multi-line comments
//   6. Multiple variables, one initializer
//   7. Using '/n' instead of '\n'
//   8. Assuming separate cout statements print on separate lines
//   9. Naming variables with keywords or starting with a digit

#include <iostream>

int main()
{
    std::cout << "=== Common C++ Pitfalls ===\n\n";

    // =====================================================================
    // PITFALL 1: Forgetting a semicolon
    // =====================================================================
    // WRONG:
    //   std::cout << "Hello"    // Missing semicolon!
    //   std::cout << "World";   // Compiler error points HERE, not the line above!
    //
    // CORRECT:
    std::cout << "Pitfall 1: Missing semicolons\n";
    std::cout << "  The error often points to the NEXT line, not the actual problem.\n";
    std::cout << "  Always check the line ABOVE the error too.\n\n";

    // =====================================================================
    // PITFALL 2: = (assignment) vs == (equality)
    // =====================================================================
    int score{100};

    // WRONG (compiles but does something unexpected):
    //   if (score = 50)   // This ASSIGNS 50 to score, then checks if 50 is true!
    //
    // CORRECT:
    if (score == 100) // This COMPARES score to 100
    {
        std::cout << "Pitfall 2: = vs ==\n";
        std::cout << "  = assigns a value.  == compares values.\n";
        std::cout << "  'if (score = 50)' assigns, not compares!\n\n";
    }

    // =====================================================================
    // PITFALL 3: Mixing up << and >> with cout/cin
    // =====================================================================
    // WRONG:
    //   std::cin << x;     // << is insertion (for cout), not cin!
    //   std::cout >> x;    // >> is extraction (for cin), not cout!
    //
    // CORRECT:
    //   std::cin  >> x;    // Extraction: data comes OUT OF the stream into x
    //   std::cout << x;    // Insertion: data goes INTO the stream from x
    std::cout << "Pitfall 3: << vs >>\n";
    std::cout << "  std::cout << value;    (data goes INTO the output stream)\n";
    std::cout << "  std::cin  >> variable; (data comes OUT OF the input stream)\n";
    std::cout << "  Remember: arrows point in the direction of data flow.\n\n";

    // =====================================================================
    // PITFALL 4: Uninitialized variables
    // =====================================================================
    // WRONG:
    //   int x;                      // Uninitialized - garbage value
    //   std::cout << x;             // UNDEFINED BEHAVIOR!
    //
    // CORRECT:
    int x{0}; // or int x{};   - always initialize!
    std::cout << "Pitfall 4: Uninitialized variables\n";
    std::cout << "  'int x;' leaves x with garbage. Use 'int x{};' instead.\n";
    std::cout << "  x (properly initialized) = " << x << "\n\n";

    // =====================================================================
    // PITFALL 5: Nesting multi-line comments
    // =====================================================================
    // WRONG:
    //   /* outer comment
    //      /* inner comment */    <-- first */ ends OUTER comment here
    //      still code, not comment
    //   */                        <-- stray */ causes compile error
    //
    // CORRECT: Use // to comment out blocks that contain /* */ comments.
    std::cout << "Pitfall 5: Nested /* */ comments\n";
    std::cout << "  /* */ comments CANNOT nest.\n";
    std::cout << "  The first */ ends ALL comments, leaving stray code.\n";
    std::cout << "  Use // for each line when commenting out blocks.\n\n";

    // =====================================================================
    // PITFALL 6: Multiple variables, one initializer
    // =====================================================================
    // WRONG:
    //   int a, b = 5;   // Only b is initialized! a is uninitialized!
    //
    // CORRECT:
    int a{5};
    int b{5};
    std::cout << "Pitfall 6: 'int a, b = 5;' only initializes b!\n";
    std::cout << "  Initialize each variable separately: int a{5}; int b{5};\n";
    std::cout << "  a = " << a << ", b = " << b << "\n\n";

    // =====================================================================
    // PITFALL 7: '/n' (forward slash) vs '\n' (backslash)
    // =====================================================================
    // WRONG:
    //   std::cout << "Hello" << '/n';   // Prints a number (multi-char literal), not a newline!
    //
    // CORRECT:
    //   std::cout << "Hello" << '\n';   // Prints a newline character
    std::cout << "Pitfall 7: '/n' vs '\\n'\n";
    std::cout << "  '/n' (forward slash) is NOT a newline - it's a multi-char literal.\n";
    std::cout << "  '\\n' (backslash) IS the newline escape character.\n";
    // Show the actual difference:
    std::cout << "  Correct newline: Hello";
    std::cout << '\n'; // Correct: moves to next line
    std::cout << "  Wrong '/n' would print: Hello" << "/n (no newline!)\n\n";

    // =====================================================================
    // PITFALL 8: Assuming cout prints on separate lines
    // =====================================================================
    // WRONG assumption:
    //   std::cout << "Hello";
    //   std::cout << "World";
    //   // These print "HelloWorld" on the SAME line!
    //
    // CORRECT: Explicitly add '\n' to move to the next line.
    std::cout << "Pitfall 8: cout does NOT auto-add newlines\n";
    std::cout << "  Without '\\n': ";
    std::cout << "Hello";
    std::cout << "World";
    std::cout << " (same line!)\n";
    std::cout << "  With '\\n':    ";
    std::cout << "Hello\n";
    std::cout << "  World (separate lines)\n\n";

    // =====================================================================
    // PITFALL 9: Invalid identifiers
    // =====================================================================
    // WRONG:
    //   int void{};      // 'void' is a keyword
    //   int 2ndPlace{};  // starts with a digit
    //
    // CORRECT:
    //   int result{};
    //   int secondPlace{};
    std::cout << "Pitfall 9: Invalid variable names\n";
    std::cout << "  Can't use keywords: int void{};   -> compile error\n";
    std::cout << "  Can't start with digit: int 2x{}; -> compile error\n";
    std::cout << "  Use: int result{}; int secondPlace{};\n";

    return 0;
}
