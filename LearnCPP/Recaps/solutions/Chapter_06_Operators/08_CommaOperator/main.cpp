// Chapter 6 - Project 08: The Comma Operator
// =============================================
// Key ideas:
//   • The comma operator evaluates the left operand, discards the result,
//     then evaluates and returns the right operand.
//   • It has the LOWEST precedence of all C++ operators.
//   • It is most commonly (and idiomatically) used in for-loop headers.
//   • Avoid using it elsewhere - it hurts readability.
//   • The comma in function calls / variable declarations is NOT the comma operator.

#include <iostream>

int main()
{
    // -----------------------------------------------------------------
    // 1. Basic comma operator behavior
    // -----------------------------------------------------------------
    std::cout << "--- Basic Comma Operator ---\n";

    int x{(1, 2)}; // evaluates 1 (discarded), then 2 → x = 2
    std::cout << "x = (1, 2)  →  x = " << x << '\n';

    int y{(3 + 4, 5 + 6)}; // evaluates 7 (discarded), then 11 → y = 11
    std::cout << "y = (3+4, 5+6)  →  y = " << y << '\n';
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 2. Comma operator in a for-loop (idiomatic usage)
    // -----------------------------------------------------------------
    std::cout << "--- In a for-loop ---\n";
    // Two variables updated each iteration using the comma operator
    for (int i{0}, j{10}; i < 5; ++i, --j) // ++i, --j uses comma operator
    {
        std::cout << "i=" << i << ", j=" << j << '\n';
    }
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 3. Lowest precedence - parentheses often needed
    // -----------------------------------------------------------------
    std::cout << "--- Precedence ---\n";

    int z{};
    z = 1, 2; // parsed as (z = 1), 2  - z gets 1, the 2 is discarded
    std::cout << "z = 1, 2    →  z = " << z << "  (assignment binds tighter)\n";

    z = (1, 2); // parentheses force comma operator first: z gets 2
    std::cout << "z = (1, 2)  →  z = " << z << "  (parentheses change grouping)\n";
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 4. Comma in function calls is NOT the comma operator
    // -----------------------------------------------------------------
    std::cout << "--- NOT the comma operator ---\n";
    // add(1, 2);  ← this comma separates function arguments
    // int a{1}, b{2};  ← this comma separates variable declarations
    std::cout << "Commas in function calls and declarations are separators,\n"
              << "not the comma operator.\n";

    return 0;
}
