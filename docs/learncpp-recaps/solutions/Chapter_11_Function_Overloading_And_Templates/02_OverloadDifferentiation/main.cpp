// Chapter 11 - Project 02: Function Overload Differentiation
// ================================================================
// Overloads are differentiated by the NUMBER and TYPE of parameters.
// The following do NOT create distinct overloads:
//   - Return type alone
//   - Type aliases (typedef / using)
//   - const on value parameters
//
// This file demonstrates what counts and what doesn't.

#include <iostream>

// ---------------------------------------------------------------
// 1) Different parameter count → valid differentiation
// ---------------------------------------------------------------
void greet()
{
    std::cout << "Hello!\n";
}

void greet(std::string_view name)
{
    std::cout << "Hello, " << name << "!\n";
}

// ---------------------------------------------------------------
// 2) Different parameter types → valid differentiation
// ---------------------------------------------------------------
void display(int value)
{
    std::cout << "int: " << value << '\n';
}

void display(double value)
{
    std::cout << "double: " << value << '\n';
}

void display(char value)
{
    std::cout << "char: " << value << '\n';
}

// ---------------------------------------------------------------
// 3) Return type ALONE does NOT differentiate
//    Uncommenting the following would cause a compile error:
// ---------------------------------------------------------------
// int getValue() { return 1; }
// double getValue() { return 1.0; }  // ERROR: same parameters (none)

// ---------------------------------------------------------------
// 4) Type aliases do NOT create distinct overloads
// ---------------------------------------------------------------
using Height = int;
// void display(Height h) { ... }  // ERROR: Height is just int - same as display(int)

// ---------------------------------------------------------------
// 5) const on a value parameter does NOT differentiate
// ---------------------------------------------------------------
// void process(int x) { }
// void process(const int x) { }  // ERROR: same as process(int)
// The compiler considers them the same overload because the caller
// can't tell the difference - both take an int by value.

// ---------------------------------------------------------------
// 6) Reference and pointer parameters CAN differentiate
//    (const reference vs non-const reference are distinct)
// ---------------------------------------------------------------
void examine(int &ref)
{
    std::cout << "non-const int&: " << ref << '\n';
}

void examine(const int &ref)
{
    std::cout << "const int&: " << ref << '\n';
}

int main()
{
    std::cout << "=== Parameter count differentiation ===\n";
    greet();
    greet("Alice");

    std::cout << "\n=== Parameter type differentiation ===\n";
    display(42);
    display(3.14);
    display('A');

    std::cout << "\n=== Reference const-qualification differentiation ===\n";
    int x{10};
    const int cx{20};
    examine(x);  // calls examine(int&)      - x is a non-const lvalue
    examine(cx); // calls examine(const int&) - cx is const
    examine(30); // calls examine(const int&) - 30 is an rvalue, binds to const ref

    // Summary:
    // ✓ Number of parameters       → differentiates
    // ✓ Types of parameters         → differentiates
    // ✓ const/non-const references  → differentiates
    // ✗ Return type                 → does NOT differentiate
    // ✗ Type aliases                → does NOT differentiate
    // ✗ const on value parameters   → does NOT differentiate

    return 0;
}
