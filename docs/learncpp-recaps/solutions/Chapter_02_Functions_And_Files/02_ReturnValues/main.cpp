// Chapter 2 - Project 02: Function Return Values
// Concept: Return types, return by value, status codes, undefined behavior
//
// A value-returning function specifies a non-void return type and uses a
// `return` statement to copy a value back to the caller ("return by value").
//
// Key rules:
//   • main() should return 0 on success (the status code).
//   • main() implicitly returns 0 if you omit the return statement - it is
//     the ONLY function with this special rule.
//   • Every other value-returning function MUST return a value on every
//     code path, or the result is undefined behavior.
//   • The returned value is a COPY - the caller gets its own copy of the
//     result.
// -----------------------------------------------------------------------

#include <iostream>

// A function that returns an int value.
int getNumber()
{
    return 42; // The value 42 is copied back to the caller
}

// A function that returns the sum of two hardcoded numbers.
int calculateSum()
{
    int a{10};
    int b{25};
    return a + b; // Expression is evaluated, result is returned
}

// Demonstrates that return immediately exits the function.
int earlyReturn(bool condition)
{
    if (condition)
    {
        return 1; // Function exits here if condition is true
    }
    // Otherwise, execution continues to this return
    return 0;
}

// A function whose return value can be used as an argument to another call.
int doubleValue(int x)
{
    return x * 2;
}

int main()
{
    std::cout << "=== Project 02: Function Return Values ===\n\n";

    // 1. Using a return value directly
    std::cout << "getNumber() returned: " << getNumber() << '\n';

    // 2. Storing a return value in a variable
    int sum{calculateSum()};
    std::cout << "calculateSum() returned: " << sum << '\n';

    // 3. Using the return value in an expression
    std::cout << "getNumber() + 8 = " << getNumber() + 8 << '\n';

    // 4. Nested function calls - the inner call's return value feeds the outer
    std::cout << "doubleValue(getNumber()) = " << doubleValue(getNumber()) << '\n';

    // 5. Return value controlling program flow
    std::cout << "earlyReturn(true)  = " << earlyReturn(true) << '\n';
    std::cout << "earlyReturn(false) = " << earlyReturn(false) << '\n';

    // 6. main()'s return value is the program's exit/status code.
    //    0 means success.  Non-zero values indicate errors.
    //    The OS receives this value when the program exits.
    std::cout << "\nmain() will return 0 (success).\n";

    return 0;
}

// NOTE - Undefined Behavior example (DO NOT uncomment in production):
// int broken()
// {
//     // Missing return statement!  The caller gets garbage - UB.
// }
// The compiler may warn but NOT error, so always check your warnings!
