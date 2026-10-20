// Chapter 1 - Project 10: Expressions
// =======================================
//
// KEY CONCEPTS:
//   - An **expression** is a combination of literals, variables, operators,
//     and function calls that evaluates to a single value.
//   - A **subexpression** is an expression used as an operand within a larger expression.
//   - A **full expression** is one that is NOT a subexpression of anything else.
//   - An **expression statement** is an expression followed by a semicolon.
//   - Wherever C++ expects a value, you can use ANY value-producing expression.
//
// BEST PRACTICE:
//   - Prefer using expressions inline rather than creating unnecessary
//     intermediate variables.

#include <iostream>

int main()
{
    // =====================================================================
    // BASIC EXPRESSIONS
    // =====================================================================

    std::cout << "--- Basic Expressions ---\n";

    // A literal by itself is an expression:
    // 5            -> evaluates to 5

    // A variable by itself is an expression:
    int x{10};
    // x            -> evaluates to 10

    // An operation is an expression:
    // x + 5        -> evaluates to 15

    std::cout << "x = " << x << '\n';
    std::cout << "x + 5 = " << (x + 5) << '\n';

    // =====================================================================
    // SUBEXPRESSIONS
    // =====================================================================

    std::cout << "\n--- Subexpressions ---\n";

    // In the expression: (x + 5) * 2
    //   - x       is a subexpression (evaluates to 10)
    //   - 5       is a subexpression (evaluates to 5)
    //   - (x + 5) is a subexpression (evaluates to 15)
    //   - 2       is a subexpression (evaluates to 2)
    //   - (x + 5) * 2 is the full expression (evaluates to 30)

    int result{(x + 5) * 2};
    std::cout << "(x + 5) * 2 = (" << x << " + 5) * 2 = " << result << '\n';

    // Breaking it down:
    std::cout << "  Subexpression x       = " << x << '\n';
    std::cout << "  Subexpression 5       = 5\n";
    std::cout << "  Subexpression (x + 5) = " << (x + 5) << '\n';
    std::cout << "  Subexpression 2       = 2\n";
    std::cout << "  Full expression       = " << result << '\n';

    // =====================================================================
    // EXPRESSION STATEMENTS
    // =====================================================================

    std::cout << "\n--- Expression Statements ---\n";

    // An expression statement = expression + semicolon.
    // The expression is evaluated, the return value is discarded,
    // but any side effects take place.

    x = 20; // Expression statement. The = operator assigns 20 to x (side effect).
            // The return value (20) is discarded.
    std::cout << "After 'x = 20;', x = " << x << '\n';

    // std::cout << x is also an expression (returns the stream).
    // Adding ; makes it an expression statement.

    // Even a standalone literal can be an expression statement (though useless):
    42; // Valid but pointless: evaluates to 42, result is discarded, no side effect.

    // =====================================================================
    // USING EXPRESSIONS INLINE (BEST PRACTICE)
    // =====================================================================

    std::cout << "\n--- Inline Expressions (Best Practice) ---\n";

    int num{7};

    // UNNECESSARY intermediate variable:
    int doubled{num * 2};
    std::cout << "Intermediate var: " << doubled << '\n';

    // BETTER: use the expression directly where the value is needed:
    std::cout << "Inline expression: " << (num * 2) << '\n';
    // Same result, less code, no extra variable cluttering the scope.

    // Another example - computing and displaying in one statement:
    int a{3};
    int b{4};
    std::cout << a << " + " << b << " = " << (a + b) << '\n';
    std::cout << a << " * " << b << " = " << (a * b) << '\n';

    // =====================================================================
    // EXPRESSIONS CAN GO ANYWHERE A VALUE IS EXPECTED
    // =====================================================================

    std::cout << "\n--- Expressions as Values ---\n";

    // Initializing with an expression:
    int area{5 * 10}; // The expression 5 * 10 provides the initial value
    std::cout << "area = 5 * 10 = " << area << '\n';

    // Using an expression as a function argument:
    // std::cout << (area + 100) passes the expression result to <<
    std::cout << "area + 100 = " << (area + 100) << '\n';

    return 0;
}
