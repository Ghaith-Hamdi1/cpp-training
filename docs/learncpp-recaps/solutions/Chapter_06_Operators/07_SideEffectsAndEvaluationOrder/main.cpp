// Chapter 6 - Project 07: Side Effects and Evaluation Order
// ===========================================================
// Key ideas:
//   • A side effect is any observable change beyond producing a return value
//     (e.g., modifying a variable, performing I/O).
//   • The order in which operands/arguments are evaluated is UNSPECIFIED in C++.
//   • Using a variable that has a side effect more than once in the same
//     expression/statement is UNDEFINED BEHAVIOR.
//   • Rule: each variable with a side effect should appear at most once per statement.

#include <iostream>

int add(int a, int b)
{
    return a + b;
}

int main()
{
    // -----------------------------------------------------------------
    // 1. Side effects - common examples
    // -----------------------------------------------------------------
    std::cout << "--- Common Side Effects ---\n";

    int x{5};
    x = 10; // assignment is a side effect (x is modified)
    std::cout << "After x = 10: x = " << x << '\n';

    ++x; // increment is a side effect (x is modified)
    std::cout << "After ++x:    x = " << x << '\n';

    // std::cout << ... is also a side effect (console output is observable state)
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 2. Unspecified evaluation order of function arguments
    // -----------------------------------------------------------------
    std::cout << "--- Unspecified Argument Evaluation Order ---\n";

    // The following is SAFE - each call to add() has no side effects on shared state:
    int a{1};
    int b{2};
    std::cout << "add(a, b) = " << add(a, b) << '\n'; // 3

    // DANGEROUS pattern (don't do this):
    // int c{ 1 };
    // int result = add(c, ++c);  // UNDEFINED BEHAVIOR
    // We don't know whether c or ++c is evaluated first.
    // One compiler might give add(1, 2) = 3, another might give add(2, 2) = 4.
    std::cout << "(See comments for the dangerous pattern with add(c, ++c).)\n\n";

    // -----------------------------------------------------------------
    // 3. Safe alternative: use separate statements
    // -----------------------------------------------------------------
    std::cout << "--- Safe Alternative ---\n";
    int c{1};
    ++c;                   // side effect in its own statement
    int result{add(c, c)}; // now c is consistently 2
    std::cout << "After ++c in a separate statement: add(c, c) = " << result << '\n';
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 4. Order of evaluation of << operands
    // -----------------------------------------------------------------
    std::cout << "--- << Operand Order ---\n";
    // This is ALSO unspecified:
    // int d{ 1 };
    // std::cout << d << ' ' << ++d;   // could print "1 2" or "2 2"
    // Safe version:
    int d{1};
    std::cout << d << ' ';
    ++d;
    std::cout << d << '\n'; // Always prints "1 2"

    // -----------------------------------------------------------------
    // 5. General rule
    // -----------------------------------------------------------------
    std::cout << "\nRule: A variable with a side effect should appear at most\n"
              << "      once in a given statement. Split into separate statements.\n";

    return 0;
}
