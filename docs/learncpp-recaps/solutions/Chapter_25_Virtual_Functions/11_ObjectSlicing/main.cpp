// Chapter 25 - Project 11: Object Slicing
// ==========================================
// OBJECT SLICING occurs when you assign/copy a derived object into a
// base object BY VALUE.  The derived portion is "sliced off" - lost.
//
// Common traps:
//   1. Passing a derived object to a function taking Base by value.
//   2. Storing derived objects in std::vector<Base> (copies by value).
//   3. Assigning a Derived to a Base variable.
//
// FRANKENOBJECT: assigning one Derived to another through a Base reference
// can produce an object with mixed state (the base part is overwritten but
// the derived part stays from the original).
//
// Prevention: pass polymorphic objects by reference or pointer, never by value.
// For containers, use vector<Base*>, vector<unique_ptr<Base>>, or
// vector<reference_wrapper<Base>>.

#include <iostream>
#include <string_view>
#include <vector>
#include <functional> // std::reference_wrapper

class Base
{
public:
    virtual std::string_view getName() const { return "Base"; }
    virtual ~Base() = default;
};

class Derived : public Base
{
    int m_value{42};

public:
    explicit Derived(int v = 42) : m_value{v} {}
    std::string_view getName() const override { return "Derived"; }
    int getValue() const { return m_value; }
};

// ========== Slicing trap 1: pass by value ==========
void printByValue(Base b) // <-- takes Base BY VALUE → slicing!
{
    std::cout << "  printByValue: " << b.getName() << '\n';
}

void printByRef(const Base &b) // <-- takes Base by reference → safe
{
    std::cout << "  printByRef:   " << b.getName() << '\n';
}

// ---------- main ----------
int main()
{
    Derived d{100};

    // --- Trap 1: Pass by value ---
    std::cout << "=== Trap 1: Pass by value ===\n";
    printByValue(d); // Sliced! Prints "Base"
    printByRef(d);   // Safe!   Prints "Derived"

    // --- Trap 2: Assignment to base variable ---
    std::cout << "\n=== Trap 2: Assignment to base variable ===\n";
    Base base = d;                                                // Sliced! Only Base portion is copied.
    std::cout << "  base.getName() = " << base.getName() << '\n'; // "Base"

    // --- Trap 3: std::vector<Base> ---
    std::cout << "\n=== Trap 3: vector<Base> (slicing!) ===\n";
    std::vector<Base> badVec;
    badVec.push_back(d);                                                    // Sliced on push_back!
    std::cout << "  badVec[0].getName() = " << badVec[0].getName() << '\n'; // "Base"

    // --- Solution: vector of pointers ---
    std::cout << "\n=== Solution: vector<Base*> (no slicing) ===\n";
    Derived d1{10}, d2{20};
    std::vector<Base *> goodVec = {&d1, &d2};
    for (const auto *p : goodVec)
        std::cout << "  " << p->getName() << '\n'; // "Derived", "Derived"

    // --- Solution: vector of reference_wrapper ---
    std::cout << "\n=== Solution: vector<reference_wrapper<Base>> ===\n";
    std::vector<std::reference_wrapper<Base>> refVec = {d1, d2};
    for (const Base &ref : refVec)
        std::cout << "  " << ref.getName() << '\n'; // "Derived", "Derived"

    // --- Frankenobject ---
    std::cout << "\n=== Frankenobject ===\n";
    Derived derived1{111};
    Derived derived2{222};
    Base &ref = derived1;
    ref = derived2; // Calls Base::operator= - only copies the Base portion!
    // derived1 now has Base data from derived2 but its own Derived data (111).
    std::cout << "  derived1.getName()  = " << derived1.getName() << '\n';  // "Derived"
    std::cout << "  derived1.getValue() = " << derived1.getValue() << '\n'; // 111 (not 222!)
    std::cout << "  ^ The derived part was NOT overwritten - Frankenobject!\n";

    std::cout << "\nAlways pass polymorphic objects by reference/pointer, never by value.\n";

    return 0;
}
