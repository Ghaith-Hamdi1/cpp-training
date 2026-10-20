// Chapter 6 - Project 01: Operator Precedence and Associativity
// =============================================================
// Key ideas:
//   • Precedence determines which operator groups with its operands first.
//   • Associativity (L→R or R→L) breaks ties among same-precedence operators.
//   • Precedence/associativity control GROUPING, NOT the order operands are evaluated.
//   • Best practice: use parentheses to make intent explicit.

#include <iostream>

int main()
{
    // -----------------------------------------------------------------
    // 1. Precedence: multiplication before addition
    // -----------------------------------------------------------------
    int a{2 + 3 * 4};   // grouped as 2 + (3 * 4) = 14
    int b{(2 + 3) * 4}; // parentheses override: (5) * 4 = 20
    std::cout << "2 + 3 * 4   = " << a << "  (multiplication first)\n";
    std::cout << "(2 + 3) * 4 = " << b << "  (parentheses override)\n\n";

    // -----------------------------------------------------------------
    // 2. Associativity: left-to-right for subtraction
    // -----------------------------------------------------------------
    int c{20 - 5 - 3};   // left-to-right: (20 - 5) - 3 = 12
    int d{20 - (5 - 3)}; // right grouping changes meaning: 20 - 2 = 18
    std::cout << "20 - 5 - 3   = " << c << "  (L→R associativity)\n";
    std::cout << "20 - (5 - 3) = " << d << "  (explicit right grouping)\n\n";

    // -----------------------------------------------------------------
    // 3. Right-to-left associativity: assignment
    // -----------------------------------------------------------------
    int x{};
    int y{};
    int z{};
    x = y = z = 5; // R→L: x = (y = (z = 5))  - all become 5
    std::cout << "x = y = z = 5  →  x=" << x << ", y=" << y << ", z=" << z << '\n';
    std::cout << "  (assignment is right-to-left associative)\n\n";

    // -----------------------------------------------------------------
    // 4. Mixed precedence - parenthesise for clarity
    // -----------------------------------------------------------------
    int val{6};
    // Without parentheses the reader must recall that * binds tighter than +
    int unclear{val + val * val}; // 6 + 36 = 42
    int clear{val + (val * val)}; // same, but intent is obvious
    std::cout << "val + val * val     = " << unclear << '\n';
    std::cout << "val + (val * val)   = " << clear << "  (prefer this form)\n\n";

    // -----------------------------------------------------------------
    // 5. Compound example with several precedence levels
    // -----------------------------------------------------------------
    // Precedence (high→low): unary -, *, +, <
    int p{3};
    int q{4};
    int r{2};
    bool result{p + q * r > -p + q};
    // Grouping: (p + (q * r)) > ((-p) + q)  →  (3+8) > (-3+4)  →  11 > 1  →  true
    std::cout << "p + q * r > -p + q  →  " << std::boolalpha << result << '\n';
    std::cout << "  Grouped as: (p + (q*r)) > ((-p) + q)\n";

    return 0;
}
