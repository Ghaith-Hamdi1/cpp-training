// Chapter 10 - Project 01: Implicit Type Conversion (Coercion)
//
// Implicit conversions happen automatically when the compiler needs a
// different type than what is supplied. This occurs during:
//   - Initialization and assignment
//   - Return statements
//   - Binary operations with mismatched types
//   - Function calls (argument to parameter)
//
// The compiler converts the value to a temporary of the target type.
// The original value is NEVER modified.

#include <iostream>

void printDouble(double d)
{
    std::cout << "printDouble received: " << d << '\n';
}

int main()
{
    // -------------------------------------------------------
    // 1. Implicit conversion during initialization
    // -------------------------------------------------------
    // The int value 5 is implicitly converted to double 5.0
    double d{5}; // int -> double (safe, value-preserving)
    std::cout << "double d from int 5: " << d << '\n';

    // -------------------------------------------------------
    // 2. Implicit conversion during assignment
    // -------------------------------------------------------
    int i{};
    i = 3.9; // double -> int (truncation! 3.9 becomes 3)
    std::cout << "int i from double 3.9: " << i << '\n';

    // -------------------------------------------------------
    // 3. Implicit conversion in a return statement
    // -------------------------------------------------------
    // (See printDouble below for the function-call case)

    // -------------------------------------------------------
    // 4. Implicit conversion in a function call
    // -------------------------------------------------------
    // int 42 is implicitly converted to double 42.0 to match the parameter
    printDouble(42);

    // -------------------------------------------------------
    // 5. Implicit conversion in a binary operation
    // -------------------------------------------------------
    // 5 (int) is promoted to double so the addition can proceed
    double result{3.2 + 5};
    std::cout << "3.2 + 5 = " << result << '\n';

    // -------------------------------------------------------
    // 6. Bool conversions
    // -------------------------------------------------------
    // Non-zero integers convert to true; 0 converts to false
    bool b1{0}; // false
    bool b2{1}; // true (any non-zero via direct init won't compile with brace, but 1 is fine)
    std::cout << std::boolalpha;
    std::cout << "bool from 0: " << b1 << '\n';
    std::cout << "bool from 1: " << b2 << '\n';

    // Key takeaway: conversions produce a TEMPORARY value of the target type.
    // The original value is never modified.
    int original{7};
    double converted{original}; // original is still int 7
    std::cout << "original (still int): " << original << '\n';
    std::cout << "converted (double):   " << converted << '\n';

    return 0;
}
