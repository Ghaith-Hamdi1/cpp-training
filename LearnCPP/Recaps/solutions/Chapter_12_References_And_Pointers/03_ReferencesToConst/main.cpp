// Chapter 12 - Project 03: Lvalue References to Const
// =====================================================
// A const lvalue reference (const int& ref) can bind to:
//   1. Modifiable lvalues
//   2. Non-modifiable (const) lvalues
//   3. Rvalues (temporaries) - the compiler creates a temporary object
//      whose lifetime is extended to match the reference
//
// Rule: Favor const& over non-const& unless you need to modify the object.

#include <iostream>

int getNumber() { return 42; }

int main()
{
    // 1. Binding to a modifiable lvalue
    int x{10};
    const int &ref1{x};
    std::cout << "ref1 (bound to modifiable lvalue x): " << ref1 << '\n';
    // ref1 = 20;  // ERROR: can't modify through a const reference

    // We can still modify x directly - ref1 sees the change
    x = 20;
    std::cout << "After x = 20, ref1 = " << ref1 << '\n'; // 20

    // 2. Binding to a const lvalue
    const int y{30};
    const int &ref2{y};
    std::cout << "ref2 (bound to const lvalue y): " << ref2 << '\n';

    // 3. Binding to an rvalue - lifetime extension!
    const int &ref3{50};          // temporary '50' lives as long as ref3
    const int &ref4{getNumber()}; // temporary from getNumber() lives as long as ref4

    std::cout << "ref3 (bound to rvalue 50):           " << ref3 << '\n';
    std::cout << "ref4 (bound to rvalue getNumber()):   " << ref4 << '\n';

    // Non-const references CANNOT bind to rvalues or const lvalues:
    // int& bad1{ 5 };    // ERROR: non-const ref can't bind to rvalue
    // int& bad2{ y };    // ERROR: non-const ref can't bind to const lvalue

    // ----- Practical example: const reference extends temporary lifetime -----
    const std::string &greeting{std::string{"Hello, World!"}};
    std::cout << "greeting: " << greeting << '\n'; // valid - temporary lives on

    return 0;
}
