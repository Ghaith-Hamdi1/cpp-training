// Chapter 12 - Project 01: Value Categories (lvalues and rvalues)
// ================================================================
// Every expression has a type AND a value category.
//   • lvalue  - identifies a persistent object (has an address you can take)
//   • rvalue  - a temporary value (literals, return-by-value results, etc.)
// An lvalue can implicitly convert to an rvalue, but NOT vice versa.

#include <iostream>
#include <string>

int getValue() { return 42; } // returns an rvalue

int main()
{
    // ----- lvalues -----
    int x{5};               // 'x' is an lvalue - it names a persistent object
    std::string name{"Hi"}; // 'name' is also an lvalue

    std::cout << "x = " << x << '\n'; // 'x' used as an lvalue
    std::cout << "name = " << name << '\n';

    // We can take the address of an lvalue
    std::cout << "Address of x: " << &x << '\n';

    // ----- rvalues -----
    // Literals like 5, 3.14, "hello" are rvalues
    // Return-by-value results are rvalues
    std::cout << "getValue() = " << getValue() << '\n'; // getValue() produces an rvalue

    // ----- lvalue-to-rvalue conversion -----
    int y{x}; // 'x' is an lvalue, but its value is read (converted to rvalue) to initialize y
    std::cout << "y (copy of x) = " << y << '\n';

    // ----- You CANNOT take the address of an rvalue -----
    // &5;          // ERROR: can't take address of literal 5
    // &getValue(); // ERROR: can't take address of a temporary

    // ----- Assignment requires an lvalue on the left -----
    x = 10; // OK: x is a modifiable lvalue
    // 5 = x;  // ERROR: 5 is an rvalue - can't assign to it

    std::cout << "x after assignment = " << x << '\n';

    // ----- Modifiable vs non-modifiable lvalues -----
    int a{5};              // 'a' is a MODIFIABLE lvalue
    const double d{3.14};  // 'd' is a NON-MODIFIABLE lvalue (it's const)
    // Both are lvalues (they have addresses), but only 'a' can appear on the left side of =
    a = 10;       // OK: modifiable lvalue
    // d = 2.71;  // ERROR: d is const - non-modifiable lvalue

    std::cout << "a = " << a << ", d = " << d << '\n';

    // ----- Side-effect expressions -----
    int counter{0};
    ++counter;  // This expression has a side effect: it modifies counter
    std::cout << "counter after ++counter: " << counter << '\n'; // 1

    // ----- Type of an expression (auto deduction) -----
    auto v1{12 / 4};    // int / int => int (v1 is int)
    auto v2{12.0 / 4};  // double / int => double (v2 is double)
    std::cout << "v1 = " << v1 << ", v2 = " << v2 << '\n';

    return 0;
}
