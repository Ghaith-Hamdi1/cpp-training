// Chapter 20 - Project 02: std::function and Type Aliases
// ========================================================
// Demonstrates: cleaning up ugly function-pointer syntax using
//   - type aliases (using / typedef)
//   - std::function from <functional>
//
// Key points:
//   - Raw function-pointer declarations are hard to read.
//   - A type alias gives the pointer type a readable name.
//   - std::function<ReturnType(ParamTypes...)> is a general-purpose
//     polymorphic wrapper that can hold any callable with a matching signature:
//     function pointers, lambdas, functors, etc.
//   - Prefer std::function over raw function pointer syntax for clarity.

#include <functional> // std::function
#include <iostream>

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

int main()
{
    // -------------------------------------------------------
    // 1. Raw function pointer (ugly but valid)
    // -------------------------------------------------------
    int (*rawPtr)(int, int){&add};
    std::cout << "Raw pointer - add(5, 3):      " << rawPtr(5, 3) << '\n';

    // -------------------------------------------------------
    // 2. Type alias with 'using' (much cleaner)
    // -------------------------------------------------------
    using BinaryOp = int (*)(int, int);

    BinaryOp op{&subtract};
    std::cout << "Type alias  - subtract(5, 3): " << op(5, 3) << '\n';

    // -------------------------------------------------------
    // 3. std::function (most flexible and readable)
    // -------------------------------------------------------
    // std::function can wrap ANY callable with this signature.
    std::function<int(int, int)> func{&multiply};
    std::cout << "std::function - multiply(5,3): " << func(5, 3) << '\n';

    // Reassign to a lambda - std::function handles this seamlessly
    func = [](int a, int b)
    { return a * a + b * b; };
    std::cout << "std::function - lambda(5,3):   " << func(5, 3) << '\n';

    // -------------------------------------------------------
    // 4. Storing callables in an array / container
    // -------------------------------------------------------
    std::function<int(int, int)> operations[]{&add, &subtract, &multiply};
    const char *names[]{"add", "subtract", "multiply"};

    std::cout << "\nAll operations on (10, 4):\n";
    for (int i{0}; i < 3; ++i)
        std::cout << "  " << names[i] << ": " << operations[i](10, 4) << '\n';

    return 0;
}
