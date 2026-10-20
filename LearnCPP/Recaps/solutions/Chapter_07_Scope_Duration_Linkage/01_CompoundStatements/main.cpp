// Chapter 7 - Project 01: Compound Statements (Blocks)
// =====================================================
// A block (compound statement) is a group of statements enclosed in { }.
// Blocks let you use multiple statements wherever C++ expects a single statement.
// Blocks can be nested, but keep nesting to 3 levels or fewer for readability.

#include <iostream>

int main()
{
    // -------------------------------------------------
    // 1. A basic block - groups statements together
    // -------------------------------------------------
    {
        int x{5};
        std::cout << "Inside block: x = " << x << '\n';
    }
    // x is not accessible here - it went out of scope at the closing }

    // -------------------------------------------------
    // 2. Blocks as the body of an if-statement
    // -------------------------------------------------
    // Without braces, only ONE statement is conditional.
    // PITFALL: forgetting braces on multi-statement if bodies.
    int temperature{30};

    if (temperature > 25)
    {
        std::cout << "It's warm outside.\n";
        std::cout << "Remember to stay hydrated!\n"; // Both lines conditional
    }

    // Common bug without braces:
    // if (temperature > 25)
    //     std::cout << "It's warm outside.\n";
    //     std::cout << "Remember to stay hydrated!\n"; // ALWAYS executes!

    // -------------------------------------------------
    // 3. Nested blocks - variables defined inside are
    //    limited to that block's scope
    // -------------------------------------------------
    {
        int outer{10};
        std::cout << "\nOuter block: outer = " << outer << '\n';

        {
            int inner{20};
            std::cout << "  Inner block: outer = " << outer
                      << ", inner = " << inner << '\n';
        }
        // 'inner' is destroyed here - no longer accessible
    }
    // 'outer' is also destroyed here

    // -------------------------------------------------
    // 4. Best practice: keep nesting ≤ 3 levels
    // -------------------------------------------------
    // Deeply nested code is hard to read. Refactor into functions instead.
    // Example of acceptable nesting (3 levels):
    int value{42};

    if (value > 0) // Level 1
    {
        if (value < 100) // Level 2
        {
            if (value % 2 == 0) // Level 3
            {
                std::cout << "\n"
                          << value << " is a small positive even number.\n";
            }
        }
    }

    // -------------------------------------------------
    // 5. Blocks define variable lifetime
    // -------------------------------------------------
    for (int i{0}; i < 3; ++i)
    {
        int loopVar{i * 10}; // Created each iteration, destroyed at }
        std::cout << "Iteration " << i << ": loopVar = " << loopVar << '\n';
    }
    // Neither 'i' nor 'loopVar' exists here

    return 0;
}
