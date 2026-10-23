// Chapter 25 - Project 03: override and final Specifiers
// ========================================================
// 'override' - placed after a derived function's parameter list.
//   Tells the compiler: "I intend this to override a base virtual function."
//   If the signature doesn't match, the compiler emits an ERROR instead of
//   silently creating a brand-new (non-overriding) function.
//
// 'final' - two uses:
//   1. On a virtual function: prevents derived classes from overriding it further.
//   2. On a class: prevents ANY class from inheriting from it.
//
// Best practice: always use 'override' on derived-class overrides; never
// write 'virtual' on them (override already implies it).

#include <iostream>
#include <string_view>

// ========== Demonstrating override ==========

class Base
{
public:
    virtual std::string_view getName() const { return "Base"; }
    virtual int getValue() const { return 0; }
    virtual ~Base() = default;
};

class Derived : public Base
{
public:
    // Correct override - signature matches exactly.
    std::string_view getName() const override { return "Derived"; }

    // ---- Common mistakes (uncomment to see compile errors) ----

    // WRONG: missing 'const' - different signature!
    // std::string_view getName() override { return "Derived"; }
    //   error: 'getName' marked override but does not override any member function

    // WRONG: wrong return type
    // int getName() const override { return 0; }
    //   error: ...

    int getValue() const override { return 42; }
};

// ========== Demonstrating final on a function ==========

class A
{
public:
    virtual void doSomething() const { std::cout << "A::doSomething\n"; }
    virtual ~A() = default;
};

class B : public A
{
public:
    // Mark override as final - no class derived from B may override this.
    void doSomething() const final { std::cout << "B::doSomething\n"; }
};

// Uncomment to see the compile error:
// class C : public B
// {
// public:
//     void doSomething() const override { std::cout << "C::doSomething\n"; }
//     // error: cannot override 'final' function 'B::doSomething'
// };

// ========== Demonstrating final on a class ==========

class Immutable final // No class may inherit from Immutable.
{
public:
    int value{};
};

// Uncomment to see the compile error:
// class Mutable : public Immutable { };
//   error: cannot derive from 'final' base 'Immutable'

// ---------- main ----------
int main()
{
    Derived d;
    Base &ref = d;

    std::cout << "=== override specifier demo ===\n";
    std::cout << "ref.getName()  = " << ref.getName() << '\n';  // Derived
    std::cout << "ref.getValue() = " << ref.getValue() << '\n'; // 42

    std::cout << "\n=== final function demo ===\n";
    B b;
    A &aRef = b;
    aRef.doSomething(); // B::doSomething (resolved at runtime via vtable)

    std::cout << "\n=== final class demo ===\n";
    Immutable obj{99};
    std::cout << "Immutable value: " << obj.value << '\n';
    // Immutable cannot be inherited from - enforced at compile time.

    std::cout << "\nTakeaway: always use 'override' on derived overrides.\n";
    std::cout << "Use 'final' when you intentionally want to stop further overriding.\n";

    return 0;
}
