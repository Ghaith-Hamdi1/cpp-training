// Chapter 12 - Project 02: Lvalue References
// =============================================
// An lvalue reference (int& ref) is an alias for an existing lvalue.
// Key rules:
//   • Must be initialized at declaration
//   • Cannot be reseated (made to refer to a different object)
//   • Modifying the reference modifies the original object
//   • A non-const lvalue reference can only bind to a modifiable lvalue

#include <iostream>

int main()
{
    int x{5};
    int &ref{x}; // 'ref' is an alias for 'x'

    std::cout << "x   = " << x << '\n';   // 5
    std::cout << "ref = " << ref << '\n'; // 5 - same object

    // Modifying through the reference changes the original
    ref = 10;
    std::cout << "After ref = 10:\n";
    std::cout << "  x   = " << x << '\n';   // 10
    std::cout << "  ref = " << ref << '\n'; // 10

    // Modifying the original is visible through the reference
    x = 20;
    std::cout << "After x = 20:\n";
    std::cout << "  ref = " << ref << '\n'; // 20

    // Both share the same address
    std::cout << "Address of x:   " << &x << '\n';
    std::cout << "Address of ref: " << &ref << '\n'; // same address

    // ----- References cannot be reseated -----
    int y{99};
    ref = y; // This does NOT reseat ref to y!
             // It ASSIGNS the value of y (99) to x (through ref).
    std::cout << "After ref = y:\n";
    std::cout << "  x = " << x << '\n'; // 99 (x was modified, not reseated)
    std::cout << "  y = " << y << '\n'; // 99 (unchanged)

    // ----- Non-const ref cannot bind to rvalue -----
    // int& bad{ 5 };        // ERROR: can't bind non-const ref to rvalue literal
    // int& bad2{ x + 1 };   // ERROR: x + 1 is an rvalue

    // ----- References must be initialized at declaration -----
    // int& invalidRef;     // ERROR: references must be initialized

    // ----- Type must match (no narrowing conversions) -----
    double d{6.0};
    // int& refToD{ d };    // ERROR: can't bind int& to double

    // ----- Scope and lifetime -----
    // A reference can go out of scope while the referent lives on:
    {
        int& innerRef{x};
        std::cout << "innerRef inside block = " << innerRef << '\n';
    } // innerRef dies here, but x lives on
    std::cout << "x after innerRef died = " << x << '\n'; // still valid

    // ----- References are not objects -----
    int& ref2{ref}; // ref2 does NOT reference 'ref' - it binds to the SAME object (x)
    ref2 = 42;
    std::cout << "After ref2 = 42: x = " << x << '\n'; // 42 - all aliases point to x

    return 0;
}
