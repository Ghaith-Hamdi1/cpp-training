// Project 06: Overloading Unary Operators (+, -, !)
// ===================================================
// Unary operators operate on a single operand and are typically overloaded
// as member functions with no parameters (the operand is *this).
// operator- returns the negated object by value.
// operator! typically returns true if the object is in a "zero" or default state.

#include <iostream>

class Vector2D
{
private:
    double m_x{};
    double m_y{};

public:
    Vector2D(double x = 0.0, double y = 0.0) : m_x{x}, m_y{y} {}

    double getX() const { return m_x; }
    double getY() const { return m_y; }

    // --- Unary operator- (negation) ---
    // Returns a NEW negated object by value. Does NOT modify *this.
    Vector2D operator-() const
    {
        return Vector2D{-m_x, -m_y};
    }

    // --- Unary operator+ (identity) ---
    // Typically returns the object as-is. Included for completeness.
    Vector2D operator+() const
    {
        return *this; // Return a copy of the object unchanged
    }

    // --- Unary operator! (logical negation) ---
    // Returns true if the vector is the zero vector (both components are 0).
    bool operator!() const
    {
        return (m_x == 0.0 && m_y == 0.0);
    }

    // Friend for output
    friend std::ostream &operator<<(std::ostream &out, const Vector2D &v);
};

std::ostream &operator<<(std::ostream &out, const Vector2D &v)
{
    out << "Vector2D(" << v.m_x << ", " << v.m_y << ')';
    return out;
}

int main()
{
    Vector2D v1{3.0, -4.0};
    Vector2D zero{}; // Default: (0, 0)

    std::cout << "v1       = " << v1 << '\n';

    // --- Unary minus: negates both components ---
    Vector2D neg = -v1;
    std::cout << "-v1      = " << neg << '\n';

    // --- Unary plus: returns the object as-is ---
    Vector2D pos = +v1;
    std::cout << "+v1      = " << pos << '\n';

    // --- Unary NOT: checks if vector is zero ---
    std::cout << "\n!v1      = " << std::boolalpha << !v1 << '\n'; // false (non-zero)
    std::cout << "!zero    = " << std::boolalpha << !zero << '\n'; // true  (zero vector)

    // Double negation
    Vector2D doubleNeg = -(-v1);
    std::cout << "\n-(-v1)   = " << doubleNeg << '\n'; // Back to original

    // Key points:
    // 1. Unary operators are best as member functions (single operand = *this)
    // 2. operator- returns a NEW object by value (does not modify *this)
    // 3. operator! returns bool - true when the object is in a "zero" state
    // 4. These take no parameters (the operand is the implicit *this)

    return 0;
}
