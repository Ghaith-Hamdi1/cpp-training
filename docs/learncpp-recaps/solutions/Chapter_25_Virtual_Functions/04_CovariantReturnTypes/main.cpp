// Chapter 25 - Project 04: Covariant Return Types
// ==================================================
// Normally an override must have the EXACT same return type as the base.
// Exception: if the base returns Base* or Base&, the override may return
// Derived* or Derived& - a pointer/reference to a MORE-derived type.
// This is called a COVARIANT return type.
//
// This is useful in clone() / factory patterns where the derived class
// wants to return its own type for convenience.

#include <iostream>
#include <string_view>

// ---------- hierarchy ----------
class Base
{
public:
    virtual std::string_view getName() const { return "Base"; }

    // Returns Base* - derived classes may return Derived*.
    virtual Base *clone() const
    {
        std::cout << "  [Base::clone called]\n";
        return new Base(*this);
    }

    virtual ~Base() = default;
};

class Derived : public Base
{
public:
    std::string_view getName() const override { return "Derived"; }

    // Covariant return type: returns Derived* instead of Base*.
    // This is legal because Derived IS-A Base.
    Derived *clone() const override
    {
        std::cout << "  [Derived::clone called]\n";
        return new Derived(*this);
    }
};

class MostDerived : public Derived
{
public:
    std::string_view getName() const override { return "MostDerived"; }

    // Covariant again: MostDerived* instead of Base*.
    MostDerived *clone() const override
    {
        std::cout << "  [MostDerived::clone called]\n";
        return new MostDerived(*this);
    }
};

// ---------- main ----------
int main()
{
    std::cout << "=== Covariant return types ===\n\n";

    MostDerived md;

    // Through a Base* - clone() still returns the correct dynamic type,
    // but the STATIC return type is Base*.
    Base *basePtr = &md;
    std::cout << "Cloning through Base*:\n";
    Base *cloned1 = basePtr->clone(); // calls MostDerived::clone
    std::cout << "  cloned1->getName() = " << cloned1->getName() << "\n\n";

    // Through a Derived* - clone() returns Derived* (covariant).
    Derived *derivedPtr = &md;
    std::cout << "Cloning through Derived*:\n";
    Derived *cloned2 = derivedPtr->clone(); // calls MostDerived::clone
    std::cout << "  cloned2->getName() = " << cloned2->getName() << "\n\n";

    // Directly on the MostDerived object - returns MostDerived*.
    std::cout << "Cloning directly on MostDerived:\n";
    MostDerived *cloned3 = md.clone(); // returns MostDerived*
    std::cout << "  cloned3->getName() = " << cloned3->getName() << "\n\n";

    // Clean up (in real code, use smart pointers).
    delete cloned1;
    delete cloned2;
    delete cloned3;

    std::cout << "Covariant return types let clone()/factory methods return\n"
              << "the most-specific type when called through a derived pointer.\n";

    return 0;
}
