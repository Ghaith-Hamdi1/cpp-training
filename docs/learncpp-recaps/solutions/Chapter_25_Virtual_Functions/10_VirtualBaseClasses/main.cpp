// Chapter 25 - Project 10: Virtual Base Classes
// ================================================
// The DIAMOND PROBLEM:
//   If class D inherits from B and C, and both B and C inherit from A,
//   then D gets TWO copies of A - ambiguous and wasteful.
//
// Solution: VIRTUAL INHERITANCE.
//   class B : virtual public A { };
//   class C : virtual public A { };
//   Now D has only ONE shared copy of A.
//
// Important details:
//   - The MOST-DERIVED class (D) is responsible for constructing the
//     virtual base (A).  B and C's calls to A's constructor are ignored.
//   - Virtual inheritance adds a vtable pointer even to classes that
//     wouldn't otherwise need one.

#include <iostream>
#include <string>

// ========== WITHOUT virtual inheritance - AMBIGUOUS ==========
namespace Bad
{
    class PowerSource
    {
    public:
        int watts{100};
        PowerSource() { std::cout << "  Bad::PowerSource constructed\n"; }
    };

    class USBDevice : public PowerSource // non-virtual
    {
    public:
        USBDevice() { std::cout << "  Bad::USBDevice constructed\n"; }
    };

    class NetworkDevice : public PowerSource // non-virtual
    {
    public:
        NetworkDevice() { std::cout << "  Bad::NetworkDevice constructed\n"; }
    };

    class WirelessAdapter : public USBDevice, public NetworkDevice
    {
    public:
        WirelessAdapter() { std::cout << "  Bad::WirelessAdapter constructed\n"; }

        void printWatts()
        {
            // std::cout << watts;   // ERROR: ambiguous - which PowerSource?
            // Must disambiguate:
            std::cout << "  USBDevice::watts     = " << USBDevice::watts << '\n';
            std::cout << "  NetworkDevice::watts = " << NetworkDevice::watts << '\n';
        }
    };
}

// ========== WITH virtual inheritance - ONE shared base ==========
namespace Good
{
    class PowerSource
    {
    public:
        int watts{100};
        PowerSource() { std::cout << "  Good::PowerSource constructed\n"; }
        explicit PowerSource(int w) : watts{w}
        {
            std::cout << "  Good::PowerSource(" << w << ") constructed\n";
        }
    };

    class USBDevice : virtual public PowerSource // virtual inheritance
    {
    public:
        USBDevice() { std::cout << "  Good::USBDevice constructed\n"; }
    };

    class NetworkDevice : virtual public PowerSource // virtual inheritance
    {
    public:
        NetworkDevice() { std::cout << "  Good::NetworkDevice constructed\n"; }
    };

    class WirelessAdapter : public USBDevice, public NetworkDevice
    {
    public:
        // The most-derived class constructs the virtual base.
        // USBDevice/NetworkDevice's calls to PowerSource() are SKIPPED.
        WirelessAdapter() : PowerSource{250}
        {
            std::cout << "  Good::WirelessAdapter constructed\n";
        }

        void printWatts()
        {
            // Unambiguous - only ONE PowerSource.
            std::cout << "  watts = " << watts << '\n';
        }
    };
}

// ---------- main ----------
int main()
{
    std::cout << "=== WITHOUT virtual inheritance (diamond problem) ===\n";
    Bad::WirelessAdapter badAdapter;
    std::cout << "Two copies of PowerSource - must disambiguate:\n";
    badAdapter.printWatts();
    std::cout << "sizeof(Bad::WirelessAdapter) = " << sizeof(Bad::WirelessAdapter) << '\n';

    std::cout << "\n=== WITH virtual inheritance (shared base) ===\n";
    Good::WirelessAdapter goodAdapter;
    std::cout << "One shared PowerSource - unambiguous:\n";
    goodAdapter.printWatts();
    std::cout << "sizeof(Good::WirelessAdapter) = " << sizeof(Good::WirelessAdapter) << '\n';

    std::cout << "\nVirtual base classes solve the diamond problem by keeping\n"
              << "only ONE copy of the shared base.  The most-derived class\n"
              << "is responsible for constructing it.\n";

    return 0;
}
