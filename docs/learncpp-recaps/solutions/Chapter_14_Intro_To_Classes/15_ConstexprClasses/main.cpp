// Chapter 14 - Project 15: Constexpr Classes
// =============================================
// Key concepts:
//   - Constructors and member functions can be marked 'constexpr',
//     enabling objects to be created and used at COMPILE TIME.
//   - A class needs a constexpr constructor to have constexpr objects.
//   - As of C++14, constexpr member functions are NOT implicitly const.
//   - Constexpr non-const member functions CAN modify data members
//     of non-const constexpr objects at compile time.
//   - If a constexpr function is called at runtime, it works like
//     a normal function.

#include <iostream>
#include <cassert>

class Vec2
{
public:
    // Constexpr constructor - allows compile-time creation
    constexpr Vec2(double x, double y)
        : m_x{x}, m_y{y}
    {
    }

    // Constexpr default constructor
    constexpr Vec2() = default;

    // Constexpr const member functions - can be evaluated at compile time
    constexpr double x() const { return m_x; }
    constexpr double y() const { return m_y; }

    constexpr double dot(const Vec2 &other) const
    {
        return m_x * other.m_x + m_y * other.m_y;
    }

    constexpr Vec2 operator+(const Vec2 &other) const
    {
        return Vec2{m_x + other.m_x, m_y + other.m_y};
    }

    // Constexpr NON-const member function - can modify members at compile time
    // (since C++14, constexpr does NOT imply const)
    constexpr void scale(double factor)
    {
        m_x *= factor;
        m_y *= factor;
    }

    void print() const
    {
        std::cout << "Vec2(" << m_x << ", " << m_y << ")\n";
    }

private:
    double m_x{0.0};
    double m_y{0.0};
};

// A constexpr function that uses the constexpr class
constexpr Vec2 computeMidpoint(const Vec2 &a, const Vec2 &b)
{
    return Vec2{
        (a.x() + b.x()) / 2.0,
        (a.y() + b.y()) / 2.0};
}

// A consteval function that MUST be evaluated at compile time
consteval double computeDot(const Vec2 &a, const Vec2 &b)
{
    return a.dot(b);
}

int main()
{
    // --- Compile-time object creation ---
    constexpr Vec2 origin{};
    constexpr Vec2 unitX{1.0, 0.0};
    constexpr Vec2 unitY{0.0, 1.0};

    // --- Compile-time computation ---
    constexpr Vec2 sum = unitX + unitY;
    static_assert(sum.x() == 1.0 && sum.y() == 1.0); // verified at compile time!

    constexpr double dotProduct = unitX.dot(unitY);
    static_assert(dotProduct == 0.0); // perpendicular vectors - dot product is 0

    constexpr Vec2 midpoint = computeMidpoint(Vec2{2.0, 4.0}, Vec2{6.0, 8.0});
    static_assert(midpoint.x() == 4.0 && midpoint.y() == 6.0);

    // Consteval - guaranteed compile-time evaluation
    constexpr double d = computeDot(Vec2{3.0, 4.0}, Vec2{1.0, 0.0});
    static_assert(d == 3.0);

    // --- Constexpr non-const member function modifying at compile time ---
    constexpr auto scaled = []()
    {
        Vec2 v{3.0, 4.0}; // non-const constexpr local
        v.scale(2.0);     // modifies v at compile time
        return v;
    }();
    static_assert(scaled.x() == 6.0 && scaled.y() == 8.0);

    // --- Runtime usage still works ---
    std::cout << "=== Runtime output ===\n";
    std::cout << "Origin:   ";
    origin.print();
    std::cout << "UnitX:    ";
    unitX.print();
    std::cout << "UnitY:    ";
    unitY.print();
    std::cout << "Sum:      ";
    sum.print();
    std::cout << "Midpoint: ";
    midpoint.print();
    std::cout << "Scaled:   ";
    scaled.print();
    std::cout << "Dot(X,Y): " << dotProduct << '\n';

    // Non-constexpr usage - works like normal at runtime
    Vec2 runtime{10.0, 20.0};
    runtime.scale(0.5);
    std::cout << "Runtime:  ";
    runtime.print();

    std::cout << "\n-- Takeaway --\n"
              << "constexpr constructors + member functions = compile-time objects.\n"
              << "constexpr does NOT imply const (since C++14).\n"
              << "static_assert verifies everything at compile time.\n";

    return 0;
}
