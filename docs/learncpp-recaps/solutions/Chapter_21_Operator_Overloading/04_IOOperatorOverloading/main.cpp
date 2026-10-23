// Project 04: Overloading the I/O Operators (<< and >>)
// ======================================================
// operator<< takes std::ostream& as the left operand and returns it by
// reference for chaining. operator>> takes std::istream& and a non-const
// reference. Input should be implemented TRANSACTIONALLY - extract to
// temporaries first, only update the object if ALL extractions succeed.
//
// PITFALL: Returning by value from operator<< will break chaining!
// PITFALL: Partial extraction can leave the object in an inconsistent state.

#include <iostream>
#include <string>
#include <limits>

class Point
{
private:
    double m_x{};
    double m_y{};

public:
    Point(double x = 0.0, double y = 0.0) : m_x{x}, m_y{y} {}

    double getX() const { return m_x; }
    double getY() const { return m_y; }

    // operator<< and operator>> CANNOT be member functions of Point
    // because the left operand is std::ostream/std::istream, not Point.
    friend std::ostream &operator<<(std::ostream &out, const Point &p);
    friend std::istream &operator>>(std::istream &in, Point &p);
};

// --- operator<< (output) ---
// Must return std::ostream& by REFERENCE for chaining: std::cout << a << b;
// PITFALL: If you return by value, chaining will fail to compile.
std::ostream &operator<<(std::ostream &out, const Point &p)
{
    out << "Point(" << p.m_x << ", " << p.m_y << ')';
    return out; // Return by reference for chaining!
}

// --- operator>> (input) - TRANSACTIONAL approach ---
// Extract to temporary variables first. Only update the object
// if ALL extractions succeed. This prevents partial state corruption.
std::istream &operator>>(std::istream &in, Point &p)
{
    double x{};
    double y{};

    // Try to extract both values
    in >> x >> y;

    // Only update the object if extraction succeeded
    if (in) // Check stream state
    {
        // Optionally validate semantics (e.g., reject negative coordinates)
        // For this demo, all values are valid.
        p.m_x = x;
        p.m_y = y;
    }
    // If extraction failed, p is unchanged - this is the transactional guarantee!

    return in;
}

int main()
{
    // --- Demonstrating operator<< ---
    Point p1{3.0, 4.5};
    Point p2{-1.0, 7.2};

    // Chaining works because operator<< returns std::ostream& by reference
    std::cout << "Two points: " << p1 << " and " << p2 << '\n';

    // --- Demonstrating operator>> with valid input ---
    std::cout << "\nEnter a point (two numbers separated by space, e.g. '5.0 3.0'): ";
    Point p3;
    if (std::cin >> p3)
    {
        std::cout << "You entered: " << p3 << '\n';
    }
    else
    {
        // If input failed, p3 is still in its default state (0, 0)
        // - transactional guarantee!
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! p3 remains: " << p3 << '\n';
    }

    // --- Summary of key rules ---
    // 1. operator<< and operator>> cannot be members of your class
    //    (left operand is ostream/istream)
    // 2. Always return the stream by REFERENCE for chaining
    // 3. Use transactional input: extract to temporaries, validate,
    //    then update the object only on success
    // 4. For semantically invalid input, call in.setstate(std::ios_base::failbit)

    return 0;
}
