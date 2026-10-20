// Chapter 6 - Project 12: Common Pitfalls
// =========================================
// This project collects the most frequent mistakes with operators.
// Each pitfall is demonstrated with the WRONG approach (commented out
// or shown safely) and the CORRECT approach.

#include <cmath>     // std::abs, std::max
#include <algorithm> // std::max
#include <iostream>

int main()
{
    std::cout << std::boolalpha;

    // =================================================================
    // PITFALL 1: Using = instead of ==
    // =================================================================
    std::cout << "=== Pitfall 1: = vs == ===\n";
    int x{5};

    // WRONG - this ASSIGNS 0 to x, then the condition is false (0 → false):
    // if (x = 0)  { ... }

    // CORRECT - use == for comparison:
    if (x == 0)
        std::cout << "x is zero\n";
    else
        std::cout << "x is not zero (x = " << x << ")\n";
    std::cout << '\n';

    // =================================================================
    // PITFALL 2: x % 2 == 1 for odd check (fails on negatives)
    // =================================================================
    std::cout << "=== Pitfall 2: Odd Check with % ===\n";
    int neg{-5};

    // WRONG: -5 % 2 == -1 (not 1), so this says -5 is even!
    std::cout << neg << " % 2 == 1?  " << (neg % 2 == 1) << "  ← WRONG\n";

    // CORRECT: compare to != 0
    std::cout << neg << " % 2 != 0?  " << (neg % 2 != 0) << "  ← CORRECT\n";
    std::cout << '\n';

    // =================================================================
    // PITFALL 3: Integer division surprise
    // =================================================================
    std::cout << "=== Pitfall 3: Integer Division ===\n";
    int a{7};
    int b{4};
    std::cout << "7 / 4 (int)    = " << (a / b) << "  ← truncated!\n";
    std::cout << "7 / 4 (double) = " << (static_cast<double>(a) / b) << "  ← correct\n";
    std::cout << '\n';

    // =================================================================
    // PITFALL 4: Misusing ! precedence
    // =================================================================
    std::cout << "=== Pitfall 4: ! Precedence ===\n";
    int val{5};
    int y{3};

    // WRONG: !val > y  →  (!val) > y  →  false > 3  →  false
    std::cout << "!val > y   = " << (!val > y) << "  ← (!val) > y, not !(val > y)\n";

    // CORRECT:
    std::cout << "!(val > y) = " << (!(val > y)) << "  ← what you probably meant\n";
    std::cout << '\n';

    // =================================================================
    // PITFALL 5: Forgetting to parenthesise ?: with <<
    // =================================================================
    std::cout << "=== Pitfall 5: ?: Parenthesisation ===\n";
    int v{-3};

    // WRONG - << binds tighter than ?:
    // std::cout << (v < 0) ? "neg" : "pos";
    // This is parsed as: (std::cout << (v < 0)) ? "neg" : "pos";

    // CORRECT - wrap the entire ternary:
    std::cout << ((v < 0) ? "negative" : "non-negative") << '\n';
    std::cout << '\n';

    // =================================================================
    // PITFALL 6: Distributing ! incorrectly (De Morgan)
    // =================================================================
    std::cout << "=== Pitfall 6: De Morgan's Law ===\n";
    bool p{true};
    bool q{false};

    // WRONG: thinking !(p && q) == (!p && !q)
    std::cout << "!(p && q)  = " << !(p && q) << '\n';  // true
    std::cout << "!p && !q   = " << (!p && !q) << '\n'; // false  ← DIFFERENT

    // CORRECT: !(p && q) == !p || !q
    std::cout << "!p || !q   = " << (!p || !q) << '\n'; // true   ← matches
    std::cout << '\n';

    // =================================================================
    // PITFALL 7: Mixing && and || without parentheses
    // =================================================================
    std::cout << "=== Pitfall 7: && / || Precedence ===\n";
    bool r{false};
    bool s{true};
    bool t{false};

    // && is evaluated before ||
    std::cout << "r || s && t = " << (r || s && t) << "  (parsed as r || (s && t))\n";
    // If you intended (r || s) && t:
    std::cout << "(r||s) && t = " << ((r || s) && t) << "  (explicit parentheses)\n";
    std::cout << '\n';

    // =================================================================
    // PITFALL 8: Side effects in short-circuited expressions
    // =================================================================
    std::cout << "=== Pitfall 8: Short-Circuit Side Effects ===\n";
    int counter{0};

    // ++counter will NOT execute because x != 1 is true here
    x = 5;
    if (x == 1 && ++counter == 1)
    {
        // body skipped
    }
    std::cout << "counter after (x==1 && ++counter): " << counter
              << "  (++counter was skipped!)\n";
    std::cout << '\n';

    // =================================================================
    // PITFALL 9: Comparing floats with ==
    // =================================================================
    std::cout << "=== Pitfall 9: Float == Comparison ===\n";
    double f1{0.1 + 0.2};
    double f2{0.3};

    // WRONG:
    std::cout << "0.1 + 0.2 == 0.3?  " << (f1 == f2) << "  ← WRONG (rounding error)\n";

    // CORRECT - epsilon comparison:
    double diff{std::abs(f1 - f2)};
    double absEps{1e-12};
    double relEps{1e-8};
    bool approxEq{diff <= absEps || diff <= std::max(std::abs(f1), std::abs(f2)) * relEps};
    std::cout << "Approx equal?      " << approxEq << "  ← CORRECT\n";

    return 0;
}
