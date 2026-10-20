// Chapter 5 - Project 04: The As-If Rule and Compile-Time Optimization
// =====================================================================
// Topics:
//   - The as-if rule: compiler can transform code if observable behavior is unchanged
//   - Constant folding: evaluating literal expressions at compile-time
//   - Constant propagation: replacing known-constant variables with values
//   - Dead code elimination: removing unreachable / unused code
//   - How 'const' helps the compiler optimize
//
// Compile: g++ -std=c++20 -O2 -o main main.cpp

#include <iostream>

int main()
{
    // -------------------------------------------------------
    // 1. Constant Folding
    // -------------------------------------------------------
    // The compiler can evaluate expressions made of literals at compile-time.
    // Instead of computing 3 * 4 at runtime, the compiler replaces it with 12.

    std::cout << "=== Constant Folding ===\n";

    int result = 3 * 4; // Compiler replaces this with: int result = 12;
    std::cout << "3 * 4 = " << result << '\n';

    // More complex constant folding:
    int complex = (10 + 20) * 3 - 5; // Compiler computes 85 at compile-time
    std::cout << "(10 + 20) * 3 - 5 = " << complex << '\n';

    // -------------------------------------------------------
    // 2. Constant Propagation
    // -------------------------------------------------------
    // When the compiler knows a variable always holds a specific value,
    // it can replace uses of that variable with the value itself.

    std::cout << "\n=== Constant Propagation ===\n";

    const int width = 10; // Compiler knows width is always 10
    const int height = 5; // Compiler knows height is always 5

    // The compiler may replace this with: int area = 50;
    int area = width * height;
    std::cout << "width(10) * height(5) = " << area << '\n';

    // Making variables const helps the compiler be certain their values
    // won't change, enabling more aggressive optimization.

    // -------------------------------------------------------
    // 3. Dead Code Elimination
    // -------------------------------------------------------
    // The compiler removes code that can never execute or whose results
    // are never used.

    std::cout << "\n=== Dead Code Elimination ===\n";

    const bool debugMode = false;

    // The compiler knows debugMode is always false, so this entire block
    // may be removed from the compiled program:
    if (debugMode)
    {
        std::cout << "This debug message will be optimized away.\n";
    }

    // Similarly, unused variables may be eliminated:
    // const int unusedValue = 42;  // Compiler may remove this entirely

    std::cout << "debugMode is false - the if-block was likely eliminated.\n";

    // -------------------------------------------------------
    // 4. How const enables optimization
    // -------------------------------------------------------
    std::cout << "\n=== How const Helps ===\n";

    // Without const, the compiler must assume 'x' could change:
    int x = 10;
    // ... the compiler cannot be sure no one modifies x ...

    // With const, the compiler is guaranteed 'y' never changes:
    const int y = 10;
    // The compiler can safely propagate '10' everywhere 'y' is used.

    std::cout << "x (non-const) = " << x << '\n';
    std::cout << "y (const)     = " << y << '\n';
    std::cout << "The compiler can optimize 'y' more aggressively than 'x'.\n";

    // -------------------------------------------------------
    // 5. The as-if rule in action
    // -------------------------------------------------------
    std::cout << "\n=== The As-If Rule ===\n";
    std::cout << "The compiler may reorder, merge, or eliminate operations\n";
    std::cout << "as long as the program's observable output doesn't change.\n";
    std::cout << "Observable behavior = output, file writes, volatile accesses.\n";

    // Example: the compiler may reorder these assignments because
    // neither affects the other:
    int a = 1;
    int b = 2;
    // The compiler could compute b before a - it doesn't matter.

    std::cout << "a = " << a << ", b = " << b << '\n';

    return 0;
}
