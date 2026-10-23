// Chapter 25 - Project 12: dynamic_cast
// ========================================
// dynamic_cast performs a SAFE RUNTIME downcast from a base pointer/reference
// to a derived type.  It uses RTTI (Run-Time Type Information) - which
// requires at least one virtual function in the hierarchy.
//
// Behavior:
//   - Pointer form: returns nullptr on failure.
//   - Reference form: throws std::bad_cast on failure.
//
// Performance: has a runtime cost - prefer virtual functions when possible.
// Use dynamic_cast only when virtual functions aren't practical (e.g., you
// need access to a derived-specific member that has no base virtual equivalent).
//
// ALWAYS check the result for nullptr before dereferencing!

#include <iostream>
#include <string>
#include <string_view>

class Base
{
public:
    virtual std::string_view getType() const { return "Base"; }
    virtual ~Base() = default;
};

class Derived : public Base
{
    int m_value{};

public:
    explicit Derived(int v) : m_value{v} {}
    std::string_view getType() const override { return "Derived"; }

    // Derived-specific member - no virtual equivalent in Base.
    int getValue() const { return m_value; }
};

class AnotherDerived : public Base
{
    std::string m_label;

public:
    explicit AnotherDerived(std::string_view label) : m_label{label} {}
    std::string_view getType() const override { return "AnotherDerived"; }

    const std::string &getLabel() const { return m_label; }
};

// ---------- Functions demonstrating dynamic_cast ----------

// Pointer form: returns nullptr on failure.
void tryDowncastPointer(Base *base)
{
    std::cout << "  Attempting dynamic_cast<Derived*>...\n";
    Derived *d = dynamic_cast<Derived *>(base);

    if (d) // ALWAYS check for nullptr!
    {
        std::cout << "    Success! getValue() = " << d->getValue() << '\n';
    }
    else
    {
        std::cout << "    Failed - returned nullptr (object is " << base->getType() << ")\n";
    }
}

// Reference form: throws std::bad_cast on failure.
void tryDowncastReference(Base &base)
{
    std::cout << "  Attempting dynamic_cast<Derived&>...\n";
    try
    {
        Derived &d = dynamic_cast<Derived &>(base);
        std::cout << "    Success! getValue() = " << d.getValue() << '\n';
    }
    catch (const std::bad_cast &e)
    {
        std::cout << "    Failed - caught std::bad_cast: " << e.what() << '\n';
    }
}

// ---------- Sideways cast ----------
// dynamic_cast can also cast between sibling types in a hierarchy.
void trySidewaysCast(Base *base)
{
    std::cout << "  Attempting dynamic_cast<AnotherDerived*>...\n";
    AnotherDerived *ad = dynamic_cast<AnotherDerived *>(base);
    if (ad)
        std::cout << "    Success! getLabel() = " << ad->getLabel() << '\n';
    else
        std::cout << "    Failed - not an AnotherDerived\n";
}

// ---------- main ----------
int main()
{
    Derived derived{42};
    AnotherDerived another{"hello"};
    Base base;

    std::cout << "=== dynamic_cast with pointers ===\n\n";

    // Cast to Derived* - should succeed for 'derived', fail for 'another' and 'base'.
    std::cout << "From Derived object:\n";
    tryDowncastPointer(&derived); // Success

    std::cout << "\nFrom AnotherDerived object:\n";
    tryDowncastPointer(&another); // Fail

    std::cout << "\nFrom Base object:\n";
    tryDowncastPointer(&base); // Fail

    std::cout << "\n=== dynamic_cast with references ===\n\n";

    std::cout << "From Derived object:\n";
    tryDowncastReference(derived); // Success

    std::cout << "\nFrom Base object:\n";
    tryDowncastReference(base); // throws std::bad_cast

    std::cout << "\n=== Sideways cast ===\n\n";

    std::cout << "Derived → AnotherDerived:\n";
    trySidewaysCast(&derived); // Fail

    std::cout << "\nAnotherDerived → AnotherDerived:\n";
    trySidewaysCast(&another); // Success

    std::cout << "\n--- Best Practices ---\n"
              << "- Prefer virtual functions over dynamic_cast.\n"
              << "- Always check for nullptr (pointer form).\n"
              << "- Catch std::bad_cast (reference form).\n"
              << "- dynamic_cast requires at least one virtual function.\n";

    return 0;
}
