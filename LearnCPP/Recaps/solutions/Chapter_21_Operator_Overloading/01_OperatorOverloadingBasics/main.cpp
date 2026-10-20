// Project 01: Introduction to Operator Overloading
// ==================================================
// Operators in C++ are implemented as functions. You can overload them
// to work with your own types, as long as at least one operand is a
// program-defined type. You CANNOT:
//   - Create new operators
//   - Change the number of operands an operator takes
//   - Change the precedence or associativity of an operator
// Keep overloaded operators intuitive and consistent with their original meaning.

#include <iostream>

// A simple class representing a monetary amount in cents.
class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents) : m_cents{cents} {}

    int getCents() const { return m_cents; }

    // --- Overloading operator+ as a friend function ---
    // This allows us to write: Cents a{5}; Cents b{10}; Cents c = a + b;
    // At least one operand (Cents) is a program-defined type, so this is valid.
    friend Cents operator+(const Cents &c1, const Cents &c2);

    // --- Overloading operator== as a friend function ---
    friend bool operator==(const Cents &c1, const Cents &c2);
};

// operator+ returns a NEW Cents object (by value) - it does not modify either operand.
Cents operator+(const Cents &c1, const Cents &c2)
{
    return Cents{c1.m_cents + c2.m_cents};
}

bool operator==(const Cents &c1, const Cents &c2)
{
    return c1.m_cents == c2.m_cents;
}

int main()
{
    Cents cents1{6};
    Cents cents2{8};

    // Using the overloaded operator+
    Cents sum{cents1 + cents2};
    std::cout << "cents1 (6) + cents2 (8) = " << sum.getCents() << " cents\n";

    // Using the overloaded operator==
    Cents cents3{14};
    std::cout << "sum == Cents{14}? " << std::boolalpha << (sum == cents3) << '\n';
    std::cout << "sum == cents1?    " << std::boolalpha << (sum == cents1) << '\n';

    // Key rule: at least one operand must be a program-defined type.
    // You CANNOT overload operator+ for two ints - that's already defined by the language.

    // Key rule: keep meaning intuitive.
    // operator+ on Cents clearly means "add the cent values together" - intuitive!
    // Don't overload ^ for exponentiation - its precedence is wrong for that purpose.

    return 0;
}
