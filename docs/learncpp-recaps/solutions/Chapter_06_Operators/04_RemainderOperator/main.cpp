// Chapter 6 - Project 04: Remainder Operator (%)
// ================================================
// Key ideas:
//   • % returns the remainder of integer division; it only works on integers.
//   • The sign of the result follows the sign of the FIRST (left) operand.
//   • To check divisibility, compare the remainder to 0 (not 1).
//   • x % 2 == 1 fails for negative odd numbers - use x % 2 != 0 instead.

#include <iostream>

int main()
{
    // -----------------------------------------------------------------
    // 1. Basic remainder
    // -----------------------------------------------------------------
    std::cout << "--- Basic Remainder ---\n";
    std::cout << "11 % 3 = " << (11 % 3) << '\n'; // 2
    std::cout << "12 % 3 = " << (12 % 3) << '\n'; // 0  (perfectly divisible)
    std::cout << " 1 % 3 = " << (1 % 3) << '\n';  // 1
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 2. Sign follows the first operand
    // -----------------------------------------------------------------
    std::cout << "--- Sign Behavior ---\n";
    std::cout << " 7 %  4 = " << (7 % 4) << '\n';   //  3
    std::cout << "-7 %  4 = " << (-7 % 4) << '\n';  // -3  (sign of first operand)
    std::cout << " 7 % -4 = " << (7 % -4) << '\n';  //  3  (sign of first operand)
    std::cout << "-7 % -4 = " << (-7 % -4) << '\n'; // -3
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 3. Checking even / odd - the correct way
    // -----------------------------------------------------------------
    std::cout << "--- Even / Odd Check ---\n";

    auto isOdd = [](int n)
    { return (n % 2 != 0); }; // correct: compare to 0

    // Demonstration with positive and negative numbers
    for (int n : {4, 5, -4, -5})
    {
        std::cout << n << " is " << (isOdd(n) ? "odd" : "even") << '\n';
    }
    std::cout << '\n';

    // Why x % 2 == 1 is WRONG for negative numbers:
    //   -5 % 2 == -1  (not 1), so the test would say -5 is even - incorrect!
    std::cout << "-5 % 2 = " << (-5 % 2) << "  (not 1, so '== 1' test would fail)\n";

    // -----------------------------------------------------------------
    // 4. Divisibility check
    // -----------------------------------------------------------------
    std::cout << "\n--- Divisibility ---\n";
    int value{24};
    for (int d : {2, 3, 5, 6, 7})
    {
        if (value % d == 0)
            std::cout << value << " is divisible by " << d << '\n';
        else
            std::cout << value << " is NOT divisible by " << d << '\n';
    }

    return 0;
}
