// Project 05: Overloading Operators Using Member Functions
// =========================================================
// As a member function, the left operand becomes the implicit *this object,
// and only the right operand is an explicit parameter.
//
// MUST be member functions: =, [], (), ->
// BEST as members: unary operators, compound assignment (+=, -=, etc.)
// BEST as non-members: binary operators that don't modify left operand (+, ==, <<)

#include <iostream>

class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents = 0) : m_cents{cents} {}

    int getCents() const { return m_cents; }

    // --- Compound assignment operators as MEMBER functions ---
    // These modify the left operand (*this), so they're best as members.
    // They return *this by reference for chaining: (a += b) += c;

    Cents &operator+=(const Cents &rhs)
    {
        // *this is the left operand; rhs is the right operand
        m_cents += rhs.m_cents;
        return *this; // Return by reference for chaining
    }

    Cents &operator-=(const Cents &rhs)
    {
        m_cents -= rhs.m_cents;
        return *this;
    }

    Cents &operator*=(int value)
    {
        m_cents *= value;
        return *this;
    }

    // --- Implementing operator+ in terms of operator+= ---
    // This is a common pattern. operator+ creates a copy, applies +=, returns the copy.
    // Note: operator+ could also be a non-member friend/normal function.
    // Here we show it as a member for demonstration.
    Cents operator+(const Cents &rhs) const
    {
        // 'copy' is a copy of *this (left operand)
        Cents copy{*this};
        copy += rhs; // Reuse operator+=
        return copy; // Return by value (new object)
    }
};

// operator<< as a non-member (cannot be a member of Cents)
std::ostream &operator<<(std::ostream &out, const Cents &c)
{
    out << c.getCents() << " cents";
    return out;
}

int main()
{
    Cents a{10};
    Cents b{5};

    // --- Compound assignment (member functions) ---
    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';

    a += b;
    std::cout << "After a += b: a = " << a << '\n';

    a -= Cents{3};
    std::cout << "After a -= 3: a = " << a << '\n';

    a *= 2;
    std::cout << "After a *= 2: a = " << a << '\n';

    // --- Chaining compound assignment ---
    Cents c{100};
    (c += Cents{10}) += Cents{5};
    std::cout << "\nChained: (100 += 10) += 5 = " << c << '\n';

    // --- operator+ implemented in terms of += ---
    Cents d{20};
    Cents e{30};
    Cents sum = d + e;
    std::cout << "\n20 + 30 = " << sum << '\n';

    // --- Rules summary ---
    // Member functions: left operand = *this, only right operand is a parameter
    // MUST be members: =, [], (), ->
    // Compound assignments (+=, -=, etc.) best as members (they modify *this)
    // operator+ best as non-member (doesn't modify either operand)

    return 0;
}
