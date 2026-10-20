// Chapter 6 - Project 11: Logical Operators and Short-Circuit Evaluation
// =======================================================================
// Key ideas:
//   • ! (NOT), && (AND), || (OR) - produce bool results.
//   • && has HIGHER precedence than || - always parenthesise when mixing.
//   • Short-circuit evaluation: && and || skip the right operand when the
//     left operand alone determines the result.
//   • De Morgan's laws:
//       !(x && y) ≡ !x || !y
//       !(x || y) ≡ !x && !y
//   • C++ has no logical XOR, but (a != b) on bools achieves the same effect.

#include <iostream>

int main()
{
    std::cout << std::boolalpha;

    // -----------------------------------------------------------------
    // 1. Logical NOT (!)
    // -----------------------------------------------------------------
    std::cout << "--- Logical NOT ---\n";
    bool t{true};
    bool f{false};
    std::cout << "!true  = " << !t << '\n'; // false
    std::cout << "!false = " << !f << '\n'; // true
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 2. Logical AND (&&) and OR (||)
    // -----------------------------------------------------------------
    std::cout << "--- AND / OR ---\n";
    std::cout << "true  && true  = " << (true && true) << '\n';   // true
    std::cout << "true  && false = " << (true && false) << '\n';  // false
    std::cout << "false || true  = " << (false || true) << '\n';  // true
    std::cout << "false || false = " << (false || false) << '\n'; // false
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 3. Precedence of && vs || - parenthesise when mixing!
    // -----------------------------------------------------------------
    std::cout << "--- Precedence: && binds tighter than || ---\n";
    bool a{true};
    bool b{false};
    bool c{true};

    // Without explicit parentheses:
    bool r1{a || b && c}; // parsed as a || (b && c)  →  true || false  →  true
    // What a reader might THINK without parentheses:
    bool r2{(a || b) && c}; // (true || false) && true  →  true && true  →  true

    std::cout << "a||b&&c           = " << r1 << "  (parsed as a||(b&&c))\n";
    std::cout << "(a||b)&&c         = " << r2 << "  (explicit grouping)\n";

    // Subtle case where the difference matters:
    bool x{false};
    bool y{true};
    bool z{false};
    std::cout << "x||y&&z           = " << (x || y && z) << "  →  false||(true&&false) = false\n";
    std::cout << "(x||y)&&z         = " << ((x || y) && z) << "  →  (false||true)&&false = false\n";
    std::cout << "Best practice: always parenthesise when mixing && and ||.\n\n";

    // -----------------------------------------------------------------
    // 4. Short-circuit evaluation
    // -----------------------------------------------------------------
    std::cout << "--- Short-Circuit Evaluation ---\n";

    int counter{0};

    // || short-circuits: left is true → right is never evaluated
    if (true || ++counter == 1)
    {
        std::cout << "counter after (true || ++counter): " << counter << "  (not incremented!)\n";
    }

    // && short-circuits: left is false → right is never evaluated
    if (false && ++counter == 1)
    {
        // this block is skipped
    }
    std::cout << "counter after (false && ++counter): " << counter << "  (still not incremented!)\n";

    // Side-effect warning:
    // Don't rely on side effects in the right operand - they may be skipped!
    std::cout << "Warning: don't put important side effects on the right side of && or ||.\n\n";

    // -----------------------------------------------------------------
    // 5. De Morgan's Laws
    // -----------------------------------------------------------------
    std::cout << "--- De Morgan's Laws ---\n";
    bool p{true};
    bool q{false};

    // !(p && q) ≡ !p || !q
    std::cout << "!(p && q) = " << !(p && q) << '\n';  // true
    std::cout << "!p || !q  = " << (!p || !q) << '\n'; // true  (same!)

    // !(p || q) ≡ !p && !q
    std::cout << "!(p || q) = " << !(p || q) << '\n';  // false
    std::cout << "!p && !q  = " << (!p && !q) << '\n'; // false (same!)

    // Common mistake: !(p && q) is NOT !p && !q
    std::cout << "\nCommon mistake: !(p && q) != (!p && !q)\n";
    std::cout << "  !(true && false) = " << !(p && q) << '\n';  // true
    std::cout << "  !true && !false  = " << (!p && !q) << '\n'; // false - different!
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 6. Logical XOR using !=
    // -----------------------------------------------------------------
    std::cout << "--- Logical XOR (using !=) ---\n";
    std::cout << "true  XOR true  = " << (true != true) << '\n';   // false
    std::cout << "true  XOR false = " << (true != false) << '\n';  // true
    std::cout << "false XOR true  = " << (false != true) << '\n';  // true
    std::cout << "false XOR false = " << (false != false) << '\n'; // false

    return 0;
}
