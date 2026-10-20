// Chapter 6 - Project 02: Arithmetic Operators
// ==============================================
// Key ideas:
//   • Unary operators: +x (identity), -x (negation)
//   • Binary operators: +, -, *, /, %
//   • Arithmetic assignment shorthand: +=, -=, *=, /=, %=
//   • Integer division truncates; floating-point division preserves the fraction.

#include <iostream>

int main()
{
    // -----------------------------------------------------------------
    // 1. Unary plus and minus
    // -----------------------------------------------------------------
    int a{7};
    std::cout << "+a = " << +a << '\n'; // unary plus  (identity - rarely used)
    std::cout << "-a = " << -a << '\n'; // unary minus (negation)
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 2. Binary arithmetic operators
    // -----------------------------------------------------------------
    int x{15};
    int y{4};
    std::cout << "x + y = " << (x + y) << '\n'; // 19
    std::cout << "x - y = " << (x - y) << '\n'; // 11
    std::cout << "x * y = " << (x * y) << '\n'; // 60
    std::cout << "x / y = " << (x / y) << '\n'; // 3  (integer division - truncated!)
    std::cout << "x % y = " << (x % y) << '\n'; // 3  (remainder)
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 3. Floating-point arithmetic
    // -----------------------------------------------------------------
    double d1{15.0};
    double d2{4.0};
    std::cout << "15.0 / 4.0 = " << (d1 / d2) << '\n'; // 3.75 - no truncation
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 4. Arithmetic assignment operators (shorthand)
    // -----------------------------------------------------------------
    int val{10};
    std::cout << "val starts at " << val << '\n';

    val += 5;                                    // val = val + 5
    std::cout << "val += 5  →  " << val << '\n'; // 15

    val -= 3;                                    // val = val - 3
    std::cout << "val -= 3  →  " << val << '\n'; // 12

    val *= 2;                                    // val = val * 2
    std::cout << "val *= 2  →  " << val << '\n'; // 24

    val /= 4;                                    // val = val / 4
    std::cout << "val /= 4  →  " << val << '\n'; // 6

    val %= 4;                                    // val = val % 4
    std::cout << "val %= 4  →  " << val << '\n'; // 2

    return 0;
}
