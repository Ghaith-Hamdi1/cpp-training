// Chapter 10 - Project 10: Type Deduction for Functions
//
// In C++14+, 'auto' can be used as a function return type,
// letting the compiler deduce it from return statements.
//
// Rules and limitations:
//   1. All return statements must return the SAME type
//   2. The function must be fully DEFINED before use
//      (forward declarations with auto return type don't work)
//   3. Prefer explicit return types for normal functions
//
// Trailing return syntax: auto func() -> ReturnType
//   - An alternative way to write the return type
//   - Useful when the return type depends on parameters
//   - Puts the return type AFTER the parameter list

#include <iostream>
#include <string>

// =============================================================
// 1. Auto return type deduction (C++14)
// =============================================================

// The compiler deduces the return type from the return statement
auto add(int x, int y)
{
    return x + y; // returns int, so the function returns int
}

auto multiply(double x, double y)
{
    return x * y; // returns double, so the function returns double
}

// =============================================================
// 2. All return statements must return the same type
// =============================================================

// This would NOT compile:
// auto badFunc(bool flag)
// {
//     if (flag)
//         return 1;       // int
//     else
//         return 2.5;     // double - different type! ERROR
// }

// This is fine - both branches return int
auto safeFunc(bool flag)
{
    if (flag)
        return 1;
    else
        return 2; // same type as above (int)
}

// =============================================================
// 3. Trailing return type syntax
// =============================================================

// Traditional syntax:
int traditionalAdd(int x, int y)
{
    return x + y;
}

// Trailing return syntax (equivalent):
auto trailingAdd(int x, int y) -> int
{
    return x + y;
}

// Trailing return is useful when the return type is complex
// or depends on the parameter types
auto divide(double x, double y) -> double
{
    if (y == 0.0)
        return 0.0;
    return x / y;
}

// =============================================================
// 4. Forward declaration limitation
// =============================================================

// auto forwardDeclared(int x); // Forward declaration with auto is NOT usable
//                               // until the function is defined

// You CAN forward-declare with trailing return type:
auto forwardWithTrailing(int x) -> int; // This works (type is known)

int main()
{
    std::cout << "=== Auto return type deduction ===\n";

    std::cout << "  add(3, 4) = " << add(3, 4) << '\n';
    std::cout << "  multiply(2.5, 3.0) = " << multiply(2.5, 3.0) << '\n';
    std::cout << "  safeFunc(true) = " << safeFunc(true) << '\n';
    std::cout << "  safeFunc(false) = " << safeFunc(false) << '\n';

    std::cout << "\n=== Trailing return type ===\n";

    std::cout << "  trailingAdd(10, 20) = " << trailingAdd(10, 20) << '\n';
    std::cout << "  divide(10.0, 3.0) = " << divide(10.0, 3.0) << '\n';
    std::cout << "  divide(10.0, 0.0) = " << divide(10.0, 0.0)
              << " (division by zero handled)\n";

    std::cout << "\n=== Forward declaration with trailing return ===\n";
    std::cout << "  forwardWithTrailing(5) = " << forwardWithTrailing(5) << '\n';

    std::cout << "\n=== Best practices ===\n";
    std::cout << "  - Prefer explicit return types for normal functions\n";
    std::cout << "  - auto return types hide the type from the reader\n";
    std::cout << "  - Trailing return syntax is useful for complex return types\n";
    std::cout << "  - auto return cannot be forward-declared and used\n";

    return 0;
}

// Definition of the forward-declared function (with trailing return type)
auto forwardWithTrailing(int x) -> int
{
    return x * x;
}
