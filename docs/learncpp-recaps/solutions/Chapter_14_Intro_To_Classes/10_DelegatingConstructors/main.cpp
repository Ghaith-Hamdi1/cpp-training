// Chapter 14 - Project 10: Delegating Constructors
// ===================================================
// Key concepts:
//   - One constructor can delegate to another via the member initializer list
//     to reduce code duplication.
//   - A delegating constructor CANNOT also directly initialize members
//     (the entire member initializer list must be just the delegation).
//   - Alternative: use default arguments to reduce the number of constructors.
//
// Pitfalls:
//   - Calling a constructor from another constructor's BODY creates a
//     temporary object - it does NOT continue initializing the current object.
//   - Avoid infinite delegation chains (A delegates to B, B delegates to A).

#include <iostream>
#include <string>

class Circle
{
public:
    // "Main" constructor - does all the real work
    Circle(double radius, double x, double y)
        : m_radius{radius}, m_x{x}, m_y{y}
    {
        std::cout << "  [Main constructor called]\n";
    }

    // Delegating constructor: circle at origin
    Circle(double radius)
        : Circle{radius, 0.0, 0.0} // delegates to the 3-parameter constructor
    {
        // Can do additional work here, but NOT initialize more members.
        std::cout << "  [Delegating constructor (radius only) called]\n";
    }

    // Delegating constructor: unit circle at origin
    Circle()
        : Circle{1.0} // delegates to the 1-parameter constructor
    {
        std::cout << "  [Default delegating constructor called]\n";
    }

    void print() const
    {
        std::cout << "Circle { r=" << m_radius
                  << ", center=(" << m_x << ", " << m_y << ") }\n";
    }

private:
    double m_radius{};
    double m_x{};
    double m_y{};
};

// -----------------------------------------------------------------------
// Alternative approach: default arguments reduce constructor count
// -----------------------------------------------------------------------
class Square
{
public:
    // Single constructor with default arguments replaces multiple constructors
    Square(double side = 1.0, double x = 0.0, double y = 0.0)
        : m_side{side}, m_x{x}, m_y{y}
    {
    }

    void print() const
    {
        std::cout << "Square { side=" << m_side
                  << ", pos=(" << m_x << ", " << m_y << ") }\n";
    }

private:
    double m_side{};
    double m_x{};
    double m_y{};
};

int main()
{
    // Delegating constructors in action - note the call chain
    std::cout << "--- Circle c1{ 5.0, 1.0, 2.0 } ---\n";
    Circle c1{5.0, 1.0, 2.0};
    c1.print();

    std::cout << "\n--- Circle c2{ 3.0 } ---\n";
    Circle c2{3.0}; // delegates to Circle(3.0, 0.0, 0.0)
    c2.print();

    std::cout << "\n--- Circle c3{} ---\n";
    Circle c3{}; // delegates to Circle(1.0) → Circle(1.0, 0.0, 0.0)
    c3.print();

    // Alternative: default arguments
    std::cout << "\n--- Squares with default arguments ---\n";
    Square s1{};    // side=1, pos=(0,0)
    Square s2{4.0}; // side=4, pos=(0,0)
    Square s3{2.0, 3.0, 4.0};
    s1.print();
    s2.print();
    s3.print();

    // PITFALL: calling constructor from body creates a TEMPORARY
    // Circle(double radius) {
    //     Circle{ radius, 0.0, 0.0 };  // WRONG - creates a temporary, doesn't delegate
    // }

    std::cout << "\n-- Takeaway --\n"
              << "Use delegating constructors or default arguments to reduce duplication.\n"
              << "Never call a constructor from a constructor body.\n";

    return 0;
}
