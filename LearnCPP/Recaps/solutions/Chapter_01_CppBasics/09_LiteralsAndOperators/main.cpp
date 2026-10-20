// Chapter 1 - Project 09: Literals and Operators
// ==================================================
//
// KEY CONCEPTS:
//   - A **literal** is a fixed value embedded directly in source code.
//     Examples: 5, 3.14, 'A', "Hello", true
//   - An **operator** is a symbol that performs an operation on operands.
//   - Operators are classified by **arity** (number of operands):
//       * Unary:   1 operand   (e.g., -x, !flag)
//       * Binary:  2 operands  (e.g., x + y, a = b)
//       * Ternary: 3 operands  (e.g., condition ? a : b)
//       * Nullary: 0 operands  (e.g., throw)
//   - A **side effect** is any observable effect beyond the return value.
//     Examples: = changes a variable, << prints to console.
//   - Arithmetic follows standard precedence (PEMDAS/BODMAS).

#include <iostream>

int main()
{
    // =====================================================================
    // LITERALS
    // =====================================================================

    std::cout << "--- Literals ---\n";

    // Integer literal
    int count{42};
    std::cout << "Integer literal:  42  -> count = " << count << '\n';

    // Floating-point literal
    double pi{3.14159};
    std::cout << "Double literal:   3.14159 -> pi = " << pi << '\n';

    // Character literal (single quotes)
    char letter{'Z'};
    std::cout << "Char literal:     'Z' -> letter = " << letter << '\n';

    // String literal (double quotes) - used directly with cout
    std::cout << "String literal:   \"Hello, C++!\"\n";

    // Boolean literal
    bool flag{true};
    std::cout << "Bool literal:     true -> flag = " << flag << '\n';

    // =====================================================================
    // OPERATORS AND ARITY
    // =====================================================================

    std::cout << "\n--- Operators by Arity ---\n";

    // UNARY operators - 1 operand
    int value{10};
    int negated{-value}; // Unary minus: negates the value
    std::cout << "Unary -:    -" << value << " = " << negated << '\n';

    bool condition{true};
    bool flipped{!condition}; // Logical NOT: flips true/false
    std::cout << "Unary !:    !" << condition << " = " << flipped << '\n';

    // BINARY operators - 2 operands
    int sum{10 + 20};      // Addition
    int diff{20 - 10};     // Subtraction
    int product{5 * 6};    // Multiplication
    int quotient{15 / 4};  // Integer division (truncates!)
    int remainder{15 % 4}; // Modulus (remainder)

    std::cout << "\nBinary +: 10 + 20  = " << sum << '\n';
    std::cout << "Binary -: 20 - 10  = " << diff << '\n';
    std::cout << "Binary *: 5 * 6    = " << product << '\n';
    std::cout << "Binary /: 15 / 4   = " << quotient << "  (integer division truncates!)\n";
    std::cout << "Binary %: 15 % 4   = " << remainder << "  (remainder)\n";

    // TERNARY operator - 3 operands (the only one in C++)
    int age{20};
    const char *status{(age >= 18) ? "adult" : "minor"};
    std::cout << "\nTernary ?: age=" << age << " -> " << status << '\n';

    // =====================================================================
    // SIDE EFFECTS
    // =====================================================================

    std::cout << "\n--- Side Effects ---\n";

    // The = operator has a side effect: it changes the variable's value.
    int x{0};
    x = 99; // Side effect: x is modified. Return value: 99.
    std::cout << "Assignment side effect: x is now " << x << '\n';

    // The << operator has a side effect: it sends data to the console.
    // Its return value is the stream itself (allowing chaining).

    // =====================================================================
    // OPERATOR PRECEDENCE (PEMDAS)
    // =====================================================================

    std::cout << "\n--- Precedence ---\n";

    // Multiplication before addition:
    int result1{2 + 3 * 4}; // 2 + 12 = 14 (not 20)
    std::cout << "2 + 3 * 4  = " << result1 << "  (* before +)\n";

    // Use parentheses to override:
    int result2{(2 + 3) * 4}; // 5 * 4 = 20
    std::cout << "(2 + 3) * 4 = " << result2 << "  (parentheses override)\n";

    // Integer division truncates toward zero:
    std::cout << "7 / 2      = " << (7 / 2) << "  (integer division: truncates to 3)\n";
    std::cout << "7.0 / 2.0  = " << (7.0 / 2.0) << "  (floating-point: keeps 3.5)\n";

    return 0;
}
