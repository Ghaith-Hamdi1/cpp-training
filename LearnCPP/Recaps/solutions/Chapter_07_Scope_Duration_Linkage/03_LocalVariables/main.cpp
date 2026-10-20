// Chapter 7 - Project 03: Local Variables
// =========================================
// Local variables have:
//   - Block scope:        accessible only within their enclosing { }
//   - Automatic duration: created at definition, destroyed at end of block
//   - No linkage:         each declaration is independent
// Best practice: define variables in the most limited scope possible.

#include <iostream>

void demonstrateAutomatic()
{
    // 'counter' is created each time this function is called
    // and destroyed when the function returns (automatic duration)
    int counter{0};
    ++counter;
    std::cout << "  counter = " << counter << '\n'; // Always prints 1
}

int main()
{
    // -------------------------------------------------
    // 1. Block scope - variables live from definition to }
    // -------------------------------------------------
    {
        int x{10};
        std::cout << "1. Inside block: x = " << x << '\n';
    }
    // std::cout << x; // ERROR: x is out of scope here

    // -------------------------------------------------
    // 2. Automatic storage duration - variables are
    //    created and destroyed each time the block runs
    // -------------------------------------------------
    std::cout << "\n2. Automatic duration (3 calls):\n";
    demonstrateAutomatic(); // counter starts at 0 each call
    demonstrateAutomatic();
    demonstrateAutomatic();

    // -------------------------------------------------
    // 3. No linkage - each local variable is independent
    // -------------------------------------------------
    {
        int value{100};
        std::cout << "\n3a. Outer block value = " << value << '\n';

        {
            // This is a DIFFERENT 'value' - no linkage to the outer one
            int value{200};
            std::cout << "3b. Inner block value = " << value << '\n';
        }

        std::cout << "3c. Outer block value still = " << value << '\n';
    }

    // -------------------------------------------------
    // 4. Best practice: define in the most limited scope
    // -------------------------------------------------
    // BAD: defining 'result' far from where it's used
    // int result;
    // ... 50 lines of code ...
    // result = someCalculation();

    // GOOD: define right where you need it
    bool condition{true};
    if (condition)
    {
        int result{42}; // Only exists when needed
        std::cout << "\n4. result = " << result << '\n';
    }

    // -------------------------------------------------
    // 5. Loop variables have block scope of the loop
    // -------------------------------------------------
    std::cout << "\n5. Loop variables:\n";
    for (int i{0}; i < 3; ++i)
    {
        int doubled{i * 2}; // New variable each iteration
        std::cout << "  i=" << i << ", doubled=" << doubled << '\n';
    }
    // 'i' and 'doubled' are both out of scope here

    // -------------------------------------------------
    // 6. Function parameters are also local variables
    // -------------------------------------------------
    // The parameters of a function behave just like local variables:
    // block scope, automatic duration, no linkage.
    // (demonstrateAutomatic's implicit 'this' or explicit params would work the same)

    std::cout << "\n6. Parameters are locals - see demonstrateAutomatic() above.\n";

    return 0;
}
