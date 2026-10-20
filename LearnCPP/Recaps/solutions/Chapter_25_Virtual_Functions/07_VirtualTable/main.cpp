// Chapter 25 - Project 07: The Virtual Table (vtable)
// =====================================================
// How virtual dispatch actually works under the hood:
//
// 1. Every class with at least one virtual function gets a compiler-generated
//    VIRTUAL TABLE (vtable) - a static array of function pointers.
//
// 2. Each object of such a class gets a hidden member called __vptr (or
//    similar), pointing to the vtable of its ACTUAL dynamic type.
//
// 3. When a virtual function is called through a pointer/reference:
//      a. Follow __vptr to the vtable.
//      b. Look up the function pointer at the correct index.
//      c. Call through that function pointer (late binding).
//
// Cost:
//   - One extra pointer per object (__vptr) - typically 4 or 8 bytes.
//   - Each virtual call involves an extra indirection (vtable lookup).
//   - The vtable itself is per-class (not per-object), so it's shared.
//
// This program demonstrates the concept and shows the size overhead.

#include <iostream>

// ---------- No virtual functions ----------
class Plain
{
    int x{}; // 4 bytes (typically)
public:
    void doStuff() {} // non-virtual - no vtable needed
};

// ---------- With virtual functions ----------
class WithVirtual
{
    int x{}; // 4 bytes
public:
    virtual void doStuff() {} // virtual - vtable + __vptr
    virtual ~WithVirtual() = default;
};

// ---------- Hierarchy to visualize vtable entries ----------
class Base
{
public:
    virtual void func1() { std::cout << "Base::func1\n"; }
    virtual void func2() { std::cout << "Base::func2\n"; }
    virtual void func3() { std::cout << "Base::func3\n"; }
    virtual ~Base() = default;
};

class Derived : public Base
{
public:
    // Overrides func1 - its vtable entry for func1 points to Derived::func1.
    void func1() override { std::cout << "Derived::func1\n"; }
    // func2 not overridden - Derived's vtable still points to Base::func2.
    // func3 not overridden - Derived's vtable still points to Base::func3.
};

class MostDerived : public Derived
{
public:
    // Overrides func2 - its vtable entry for func2 points to MostDerived::func2.
    void func2() override { std::cout << "MostDerived::func2\n"; }
    // func1 not overridden - MostDerived's vtable points to Derived::func1.
    // func3 not overridden - MostDerived's vtable points to Base::func3.
};

// ---------- main ----------
int main()
{
    // --- Size overhead ---
    std::cout << "=== Size overhead of __vptr ===\n";
    std::cout << "sizeof(Plain)       = " << sizeof(Plain) << " bytes\n";
    std::cout << "sizeof(WithVirtual) = " << sizeof(WithVirtual) << " bytes\n";
    std::cout << "(Difference includes __vptr + possible padding)\n";

    // --- vtable dispatch visualization ---
    // Conceptual vtable layout:
    //
    //  Base vtable:        [Base::func1,        Base::func2,        Base::func3,       ...]
    //  Derived vtable:     [Derived::func1,     Base::func2,        Base::func3,       ...]
    //  MostDerived vtable: [Derived::func1,     MostDerived::func2, Base::func3,       ...]

    std::cout << "\n=== vtable dispatch demo ===\n";
    Base b;
    Derived d;
    MostDerived md;

    // Array of base pointers - each object's __vptr points to its class's vtable.
    Base *objects[] = {&b, &d, &md};
    const char *labels[] = {"Base", "Derived", "MostDerived"};

    for (int i = 0; i < 3; ++i)
    {
        std::cout << "\n--- " << labels[i] << " ---\n";
        objects[i]->func1(); // vtable[0]
        objects[i]->func2(); // vtable[1]
        objects[i]->func3(); // vtable[2]
    }

    std::cout << "\nEach object carries a __vptr (hidden pointer to its class vtable).\n"
              << "Virtual calls: follow __vptr → look up index → call function pointer.\n";

    return 0;
}
