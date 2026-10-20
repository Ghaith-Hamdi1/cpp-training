// Chapter 6 - Project 09: The Conditional (Ternary) Operator
// ============================================================
// Key ideas:
//   • Syntax:  condition ? exprTrue : exprFalse
//   • It is an EXPRESSION (produces a value), unlike if-else which is a statement.
//   • Ideal for initialization, assignment, or return values.
//   • ALWAYS parenthesise the entire ternary when embedded in a larger expression.
//   • Parenthesise the condition itself if it contains operators, for clarity.
//   • The types of exprTrue and exprFalse must match or be implicitly convertible.

#include <iostream>
#include <string>

int main()
{
    // -----------------------------------------------------------------
    // 1. Basic usage - compact if-else
    // -----------------------------------------------------------------
    std::cout << "--- Basic Ternary ---\n";
    int x{7};
    const char *result{(x > 0) ? "positive" : "non-positive"};
    std::cout << x << " is " << result << '\n';
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 2. Ternary for initialization (constexpr-friendly)
    // -----------------------------------------------------------------
    std::cout << "--- Initialization ---\n";
    constexpr int a{10};
    constexpr int b{20};
    constexpr int larger{(a > b) ? a : b}; // determined at compile time
    std::cout << "The larger of " << a << " and " << b << " is " << larger << '\n';
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 3. Ternary inside std::cout - MUST parenthesise!
    // -----------------------------------------------------------------
    std::cout << "--- Parenthesisation pitfall ---\n";
    int value{-3};

    // CORRECT - entire ternary parenthesised:
    std::cout << value << " is " << ((value < 0) ? "negative" : "non-negative") << '\n';

    // WRONG (would compile but behaves unexpectedly):
    // std::cout << (value < 0) ? "negative" : "non-negative";
    // ↑ This is parsed as:  (std::cout << (value < 0))  ? "negative" : "non-negative";
    //   because << has higher precedence than ?:
    std::cout << "(See comments for why missing parentheses breaks this.)\n\n";

    // -----------------------------------------------------------------
    // 4. Nested ternary - use sparingly, prefer if-else for clarity
    // -----------------------------------------------------------------
    std::cout << "--- Nested Ternary (use sparingly) ---\n";
    int score{75};
    // grade: A >= 90, B >= 80, C >= 70, D >= 60, F otherwise
    char grade{(score >= 90)   ? 'A'
               : (score >= 80) ? 'B'
               : (score >= 70) ? 'C'
               : (score >= 60) ? 'D'
                               : 'F'};
    std::cout << "Score " << score << " → Grade " << grade << '\n';
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 5. Type matching
    // -----------------------------------------------------------------
    std::cout << "--- Type Matching ---\n";
    int intVal{5};
    // Both branches must yield compatible types:
    double d{(intVal > 0) ? 1.5 : 2.5}; // both double - OK
    std::cout << "d = " << d << '\n';

    // Mixed types get implicitly converted to a common type:
    auto mixed{(intVal > 0) ? intVal : 3.14}; // int promoted to double
    std::cout << "mixed (int vs double) = " << mixed << '\n';

    return 0;
}
