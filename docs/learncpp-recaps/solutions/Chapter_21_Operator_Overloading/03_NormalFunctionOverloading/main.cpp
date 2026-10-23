// Project 03: Overloading Operators Using Normal (Non-Friend) Functions
// ======================================================================
// If a class provides sufficient public access functions (getters/setters),
// operators can be overloaded as normal (non-friend, non-member) functions.
// This is PREFERRED because it minimizes the number of functions that
// touch private members, improving encapsulation.

#include <iostream>

class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents) : m_cents{cents} {}

    // Public getter - this is all the normal function needs
    int getCents() const { return m_cents; }
};

// --- Normal function overloads (NOT friends) ---
// These rely entirely on the public interface (getCents()).
// No "friend" declaration needed inside the class.

Cents operator+(const Cents &c1, const Cents &c2)
{
    // Using the public getter instead of accessing m_cents directly
    return Cents{c1.getCents() + c2.getCents()};
}

Cents operator-(const Cents &c1, const Cents &c2)
{
    return Cents{c1.getCents() - c2.getCents()};
}

bool operator==(const Cents &c1, const Cents &c2)
{
    return c1.getCents() == c2.getCents();
}

bool operator!=(const Cents &c1, const Cents &c2)
{
    // Implement in terms of operator== to reduce redundancy
    return !(c1 == c2);
}

// Overloading operator<< as a normal function (not friend)
// This works because we only need getCents(), which is public.
std::ostream &operator<<(std::ostream &out, const Cents &c)
{
    out << c.getCents() << " cents";
    return out;
}

int main()
{
    Cents nickle{5};
    Cents dime{10};

    // Using normal function overloads
    Cents sum{nickle + dime};
    Cents diff{dime - nickle};

    std::cout << "Nickle:      " << nickle << '\n';
    std::cout << "Dime:        " << dime << '\n';
    std::cout << "Sum:         " << sum << '\n';
    std::cout << "Difference:  " << diff << '\n';

    std::cout << "\nEquality checks:\n";
    std::cout << "nickle == dime? " << std::boolalpha << (nickle == dime) << '\n';
    std::cout << "nickle != dime? " << std::boolalpha << (nickle != dime) << '\n';
    std::cout << "sum == Cents{15}? " << std::boolalpha << (sum == Cents{15}) << '\n';

    // KEY INSIGHT:
    // Normal function overloads are preferred over friend overloads when possible.
    // They don't need access to private members - just the public interface.
    // This keeps the class's "trust boundary" small.

    // When to use friend instead:
    // - When the class doesn't expose the data you need through public functions
    // - When adding a getter just for the operator would break encapsulation worse

    return 0;
}
