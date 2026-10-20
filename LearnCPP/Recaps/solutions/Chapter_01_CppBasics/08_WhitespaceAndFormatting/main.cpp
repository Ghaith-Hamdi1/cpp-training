// Chapter 1 - Project 08: Whitespace and Basic Formatting
// ==========================================================
//
// KEY CONCEPTS:
//   - **Whitespace** = spaces, tabs, and newlines.
//   - The compiler generally ignores whitespace (except inside quoted strings).
//   - Whitespace IS required to separate certain tokens (e.g., "int x" not "intx").
//   - Inside string literals, whitespace is preserved exactly as written.
//
// FORMATTING BEST PRACTICES:
//   1. Indent with 4 spaces (or 1 tab) per level.
//   2. Keep lines ≤ 80 characters.
//   3. When breaking a long line, put the operator at the START of the next line.
//   4. Use consistent brace style.
//   5. Use your IDE's auto-format feature (e.g., Ctrl+K, Ctrl+F in VS Code).

#include <iostream>

int main()
{
    // =====================================================================
    // Whitespace is mostly ignored by the compiler
    // =====================================================================

    // All three of these statements are identical to the compiler:
    int a{5};
    int b{5};
    int c{
        5};

    std::cout << "a=" << a << " b=" << b << " c=" << c << '\n';
    // All produce the same result - but the first form is the most readable.

    // =====================================================================
    // Whitespace IS significant inside string literals
    // =====================================================================

    std::cout << "Hello, World!\n";   // Normal spacing
    std::cout << "Hello,   World!\n"; // Extra spaces are preserved in the output
    std::cout << "Hello,\tWorld!\n";  // Tab character is preserved

    // =====================================================================
    // Whitespace IS required to separate tokens
    // =====================================================================

    // int x{5};   - correct: "int" and "x" are separated by a space
    // intx{5};    - ERROR: compiler sees "intx" as a single identifier

    // =====================================================================
    // Good formatting example
    // =====================================================================

    std::cout << "\n--- Good Formatting ---\n";

    int width{10};
    int height{20};
    int area{width * height};

    std::cout << "Width:  " << width << '\n';
    std::cout << "Height: " << height << '\n';
    std::cout << "Area:   " << area << '\n';

    // =====================================================================
    // Breaking long lines
    // =====================================================================

    // BEST PRACTICE: If a line is too long, break it and put the operator
    // at the START of the continuation line. This makes it easier to see
    // that the line is a continuation.

    std::cout << "\n--- Long Line Example ---\n";

    int result{1 + 2 + 3 + 4 + 5 + 6}; // Operator at start of continuation line

    std::cout << "1+2+3+4+5+6 = " << result << '\n';

    // Similarly for chained output:
    std::cout << "This is a very long output "
              << "that has been split across "
              << "multiple lines for readability.\n";

    // =====================================================================
    // Summary
    // =====================================================================

    std::cout << "\n--- Formatting Summary ---\n";
    std::cout << "1. Indent 4 spaces per level\n";
    std::cout << "2. Keep lines <= 80 chars\n";
    std::cout << "3. Operators at START of continuation lines\n";
    std::cout << "4. Consistent brace style\n";
    std::cout << "5. Use auto-format in your IDE\n";

    return 0;
}
