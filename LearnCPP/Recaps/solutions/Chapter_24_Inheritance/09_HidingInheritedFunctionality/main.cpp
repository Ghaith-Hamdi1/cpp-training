// Project 09 - Hiding Inherited Functionality
// ==============================================
// A derived class can:
//   1) Change an inherited member's access level using a `using` declaration
//      under a different access specifier.
//   2) Delete an inherited function (`= delete`) to prevent its use.
//
// CAVEAT: hidden/private members can still be accessed by casting
// to a base reference - this is not true encapsulation.

#include <iostream>

class Base
{
public:
    int m_value{10};

    void publicFunc() const
    {
        std::cout << "Base::publicFunc() called, m_value = " << m_value << '\n';
    }

    void anotherFunc() const
    {
        std::cout << "Base::anotherFunc() called\n";
    }
};

// --- Example 1: Changing access level with a using declaration ---
class RestrictedDerived : public Base
{
private:
    // Pull Base::m_value into the private section
    // This makes it inaccessible from outside RestrictedDerived
    using Base::m_value;

    // Pull publicFunc into private as well
    using Base::publicFunc;

public:
    void show() const
    {
        // Inside the class, we can still access them
        std::cout << "RestrictedDerived::show(): m_value = " << m_value << '\n';
        publicFunc();
    }
};

// --- Example 2: Deleting an inherited function ---
class LimitedDerived : public Base
{
public:
    // Delete anotherFunc so it can't be called on LimitedDerived objects
    void anotherFunc() const = delete;
};

int main()
{
    std::cout << "=== Changing access level ===\n";
    RestrictedDerived rd;
    rd.show(); // OK - show() is public
    // rd.m_value;            // ERROR: m_value is now private
    // rd.publicFunc();       // ERROR: publicFunc is now private
    rd.anotherFunc(); // OK - not restricted

    std::cout << '\n';

    // CAVEAT: We can bypass the restriction by casting to Base&
    Base &baseRef = rd;
    std::cout << "Bypass via Base&: m_value = " << baseRef.m_value << '\n';
    baseRef.publicFunc(); // Works - access is checked against Base

    std::cout << "\n=== Deleting inherited function ===\n";
    LimitedDerived ld;
    ld.publicFunc(); // OK - not deleted
    // ld.anotherFunc();      // ERROR: explicitly deleted

    // CAVEAT: can still call via Base&
    Base &ldRef = ld;
    ldRef.anotherFunc(); // Works - deletion only applies to LimitedDerived

    return 0;
}
