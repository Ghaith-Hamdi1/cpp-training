// Project 10 - Using Declarations to Bring Base Overloads into Scope
// ====================================================================
// When a derived class defines a function with the same name as one
// in the base class, ALL base class overloads of that name are HIDDEN
// - even if the signatures differ.
//
// A `using Base::func;` declaration in the derived class brings all
// base overloads back into the derived class's overload set.
//
// NOTE: A using declaration changes access for ALL overloads of a
// name - you cannot selectively change one overload.

#include <iostream>
#include <string_view>

class Base
{
public:
    // Two overloads of print()
    void print(int x) const
    {
        std::cout << "Base::print(int): " << x << '\n';
    }

    void print(double x) const
    {
        std::cout << "Base::print(double): " << x << '\n';
    }
};

// --- Without using declaration: base overloads are hidden ---
class DerivedHidden : public Base
{
public:
    // This hides BOTH Base::print(int) and Base::print(double)
    void print(std::string_view s) const
    {
        std::cout << "DerivedHidden::print(string_view): " << s << '\n';
    }
};

// --- With using declaration: base overloads are visible ---
class DerivedVisible : public Base
{
public:
    // Bring all Base::print overloads into scope
    using Base::print;

    // Add a new overload alongside the inherited ones
    void print(std::string_view s) const
    {
        std::cout << "DerivedVisible::print(string_view): " << s << '\n';
    }
};

int main()
{
    std::cout << "=== DerivedHidden (no using declaration) ===\n";
    DerivedHidden dh;
    dh.print("hello"); // OK - DerivedHidden::print(string_view)
    // dh.print(42);       // ERROR: Base::print(int) is hidden!
    // dh.print(3.14);     // ERROR: Base::print(double) is hidden!

    // You can still call the base version explicitly:
    dh.Base::print(42); // OK - explicit scope resolution

    std::cout << "\n=== DerivedVisible (with using declaration) ===\n";
    DerivedVisible dv;
    dv.print("hello"); // DerivedVisible::print(string_view)
    dv.print(42);      // Base::print(int) - now visible!
    dv.print(3.14);    // Base::print(double) - now visible!

    return 0;
}
