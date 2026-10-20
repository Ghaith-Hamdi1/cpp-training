// Project 12 - The Diamond Problem
// ====================================
// The diamond problem occurs when two base classes share a common
// ancestor, leading to ambiguity and duplicate sub-objects.
//
//        PoweredDevice
//        /           \.
//    Scanner       Printer
//        \           /
//         Copier
//
// Without virtual inheritance, Copier contains TWO copies of
// PoweredDevice. With virtual inheritance, only ONE copy exists.

#include <iostream>

// --- Part 1: The problem WITHOUT virtual inheritance ---

namespace NoVirtual
{
    class PoweredDevice
    {
    public:
        int m_power{};

        PoweredDevice(int power) : m_power{power}
        {
            std::cout << "  [NoVirtual] PoweredDevice constructed (power=" << power << ")\n";
        }
    };

    class Scanner : public PoweredDevice
    {
    public:
        Scanner(int power) : PoweredDevice{power}
        {
            std::cout << "  [NoVirtual] Scanner constructed\n";
        }
    };

    class Printer : public PoweredDevice
    {
    public:
        Printer(int power) : PoweredDevice{power}
        {
            std::cout << "  [NoVirtual] Printer constructed\n";
        }
    };

    class Copier : public Scanner, public Printer
    {
    public:
        Copier(int scanPower, int printPower)
            : Scanner{scanPower}, Printer{printPower}
        {
            std::cout << "  [NoVirtual] Copier constructed\n";
        }

        void showPower() const
        {
            // copier.m_power is AMBIGUOUS - two copies exist!
            // Must disambiguate:
            std::cout << "  Scanner power: " << Scanner::m_power << '\n';
            std::cout << "  Printer power: " << Printer::m_power << '\n';
        }
    };
}

// --- Part 2: The solution WITH virtual inheritance ---

namespace WithVirtual
{
    class PoweredDevice
    {
    public:
        int m_power{};

        PoweredDevice(int power) : m_power{power}
        {
            std::cout << "  [WithVirtual] PoweredDevice constructed (power=" << power << ")\n";
        }
    };

    // Virtual inheritance: Scanner and Printer share ONE PoweredDevice
    class Scanner : virtual public PoweredDevice
    {
    public:
        Scanner(int power) : PoweredDevice{power}
        {
            std::cout << "  [WithVirtual] Scanner constructed\n";
        }
    };

    class Printer : virtual public PoweredDevice
    {
    public:
        Printer(int power) : PoweredDevice{power}
        {
            std::cout << "  [WithVirtual] Printer constructed\n";
        }
    };

    class Copier : public Scanner, public Printer
    {
    public:
        // With virtual inheritance, the MOST-DERIVED class must
        // directly initialize the virtual base class
        Copier(int power)
            : PoweredDevice{power} // ← most-derived initializes the shared base
              ,
              Scanner{power}, Printer{power}
        {
            std::cout << "  [WithVirtual] Copier constructed\n";
        }

        void showPower() const
        {
            // No ambiguity - only ONE PoweredDevice sub-object
            std::cout << "  Shared power: " << m_power << '\n';
        }
    };
}

int main()
{
    std::cout << "=== Diamond Problem WITHOUT virtual inheritance ===\n";
    {
        NoVirtual::Copier c{100, 200};
        c.showPower();
        // Notice: PoweredDevice is constructed TWICE
    }

    std::cout << "\n=== Diamond Problem WITH virtual inheritance ===\n";
    {
        WithVirtual::Copier c{150};
        c.showPower();
        // Notice: PoweredDevice is constructed only ONCE
    }

    return 0;
}
