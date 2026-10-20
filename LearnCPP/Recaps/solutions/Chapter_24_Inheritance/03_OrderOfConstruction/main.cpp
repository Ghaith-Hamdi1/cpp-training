// Project 03 - Order of Construction and Destruction
// =====================================================
// Key rule:
//   Construction: most-base → most-derived
//   Destruction:  most-derived → most-base
//
// This guarantees that base members are fully initialized
// before the derived constructor runs, and derived members
// are cleaned up before the base destructor runs.

#include <iostream>

class Base
{
public:
    Base()
    {
        std::cout << "  Base constructor called\n";
    }

    ~Base()
    {
        std::cout << "  Base destructor called\n";
    }
};

class Derived : public Base
{
public:
    Derived()
    // Base() is constructed BEFORE this body executes
    {
        std::cout << "  Derived constructor called\n";
    }

    ~Derived()
    {
        std::cout << "  Derived destructor called\n";
        // After this body completes, ~Base() runs automatically
    }
};

class MostDerived : public Derived
{
public:
    MostDerived()
    {
        std::cout << "  MostDerived constructor called\n";
    }

    ~MostDerived()
    {
        std::cout << "  MostDerived destructor called\n";
    }
};

int main()
{
    std::cout << "--- Creating a Derived object ---\n";
    {
        Derived d{};
        // Construction: Base → Derived
    }
    // Destruction: Derived → Base
    std::cout << "--- Derived object destroyed ---\n\n";

    std::cout << "--- Creating a MostDerived object ---\n";
    {
        MostDerived md{};
        // Construction: Base → Derived → MostDerived
    }
    // Destruction: MostDerived → Derived → Base
    std::cout << "--- MostDerived object destroyed ---\n";

    return 0;
}
