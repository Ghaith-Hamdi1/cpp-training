// Chapter 6 - Project 06: Increment / Decrement Operators
// ========================================================
// Key ideas:
//   • Prefix  (++x / --x): modifies the variable, then returns the NEW value.
//   • Postfix (x++ / x--): copies the old value, modifies the variable, returns the OLD copy.
//   • Prefer prefix - it avoids creating an unnecessary temporary copy.
//   • Never use a variable with a side-effect more than once in the same expression.

#include <iostream>

int main()
{
    // -----------------------------------------------------------------
    // 1. Prefix increment / decrement
    // -----------------------------------------------------------------
    std::cout << "--- Prefix ---\n";
    int a{5};
    std::cout << "a starts at " << a << '\n'; // 5
    std::cout << "++a = " << ++a << '\n';     // 6  (a is now 6)
    std::cout << "a is now " << a << '\n';    // 6
    std::cout << "--a = " << --a << '\n';     // 5  (a is now 5)
    std::cout << "a is now " << a << '\n';    // 5
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 2. Postfix increment / decrement
    // -----------------------------------------------------------------
    std::cout << "--- Postfix ---\n";
    int b{5};
    std::cout << "b starts at " << b << '\n'; // 5
    std::cout << "b++ = " << b++ << '\n';     // 5  (returns OLD value; b becomes 6)
    std::cout << "b is now " << b << '\n';    // 6
    std::cout << "b-- = " << b-- << '\n';     // 6  (returns OLD value; b becomes 5)
    std::cout << "b is now " << b << '\n';    // 5
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 3. Prefix vs. postfix in a loop - prefer prefix
    // -----------------------------------------------------------------
    std::cout << "--- In a for-loop (prefix recommended) ---\n";
    for (int i{0}; i < 5; ++i) // ++i preferred over i++
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    // For built-in types the compiler optimizes away the difference,
    // but for user-defined iterators, prefix genuinely avoids a copy.
    std::cout << '\n';

    // -----------------------------------------------------------------
    // 4. Practical example: prefix is used when you need the new value
    // -----------------------------------------------------------------
    std::cout << "--- When the return value matters ---\n";
    int counter{0};

    // Prefix: we want the already-incremented value
    if (++counter == 1)
        std::cout << "Prefix: counter incremented to 1 before the check.\n";

    counter = 0;

    // Postfix: we want the original value, then increment happens
    if (counter++ == 0)
        std::cout << "Postfix: counter was 0 during the check, now it is "
                  << counter << ".\n";

    // -----------------------------------------------------------------
    // 5. WARNING - don't use a side-effecting variable twice in one expression
    // -----------------------------------------------------------------
    // int x{ 5 };
    // int y{ x + ++x };   // UNDEFINED BEHAVIOR - don't do this!
    // The order in which x and ++x are evaluated is unspecified.
    std::cout << "\n(See comments for the undefined-behavior warning.)\n";

    return 0;
}
