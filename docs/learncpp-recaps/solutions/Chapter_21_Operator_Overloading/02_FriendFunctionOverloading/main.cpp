// Project 02: Overloading Arithmetic Operators Using Friend Functions
// ====================================================================
// Binary arithmetic operators (+, -, *, /) can be overloaded as friend
// functions that take two parameters. When operands are different types
// (e.g. Cents + int vs int + Cents), you need separate overloads for
// each ordering. One overload can call the other to reduce redundancy.

#include <iostream>

class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents) : m_cents{cents} {}

    int getCents() const { return m_cents; }

    // --- Friend overloads for all four arithmetic operators ---
    friend Cents operator+(const Cents &c1, const Cents &c2);
    friend Cents operator-(const Cents &c1, const Cents &c2);
    friend Cents operator*(const Cents &c1, const Cents &c2);
    friend Cents operator/(const Cents &c1, const Cents &c2);

    // --- Mixed-type overloads: Cents + int and int + Cents ---
    // These handle cases where one operand is an int.
    friend Cents operator+(const Cents &c, int value);
    friend Cents operator+(int value, const Cents &c);

    // --- Overload operator* for Cents * int and int * Cents ---
    friend Cents operator*(const Cents &c, int value);
    friend Cents operator*(int value, const Cents &c);
};

// --- Same-type arithmetic ---
Cents operator+(const Cents &c1, const Cents &c2)
{
    return Cents{c1.m_cents + c2.m_cents};
}

Cents operator-(const Cents &c1, const Cents &c2)
{
    return Cents{c1.m_cents - c2.m_cents};
}

Cents operator*(const Cents &c1, const Cents &c2)
{
    return Cents{c1.m_cents * c2.m_cents};
}

Cents operator/(const Cents &c1, const Cents &c2)
{
    return Cents{c1.m_cents / c2.m_cents};
}

// --- Mixed-type: Cents + int ---
Cents operator+(const Cents &c, int value)
{
    return Cents{c.m_cents + value};
}

// --- Mixed-type: int + Cents ---
// Reuse the Cents + int overload to avoid code duplication!
Cents operator+(int value, const Cents &c)
{
    return c + value; // Calls operator+(const Cents&, int)
}

// --- Mixed-type: Cents * int ---
Cents operator*(const Cents &c, int value)
{
    return Cents{c.m_cents * value};
}

// --- Mixed-type: int * Cents ---
// Again, reuse the other overload to reduce redundancy.
Cents operator*(int value, const Cents &c)
{
    return c * value; // Calls operator*(const Cents&, int)
}

int main()
{
    Cents cents1{6};
    Cents cents2{14};

    // Same-type operations
    std::cout << "6 + 14 = " << (cents1 + cents2).getCents() << " cents\n";
    std::cout << "14 - 6 = " << (cents2 - cents1).getCents() << " cents\n";
    std::cout << "6 * 14 = " << (cents1 * cents2).getCents() << " cents\n";
    std::cout << "14 / 6 = " << (cents2 / cents1).getCents() << " cents\n";

    // Mixed-type operations - both orderings work
    std::cout << "\nMixed-type operations:\n";
    std::cout << "Cents{6} + 10   = " << (cents1 + 10).getCents() << " cents\n";
    std::cout << "10 + Cents{6}   = " << (10 + cents1).getCents() << " cents\n";
    std::cout << "Cents{6} * 3    = " << (cents1 * 3).getCents() << " cents\n";
    std::cout << "3 * Cents{6}    = " << (3 * cents1).getCents() << " cents\n";

    // Key takeaway: if you need Cents + int AND int + Cents,
    // implement one and have the other call it - DRY principle!

    return 0;
}
