// Chapter 14 - Project 02: Member Functions
// ============================================
// Key concepts:
//   - Member functions are functions declared inside a class/struct.
//   - They are called on an object using the dot operator: obj.func()
//   - The object the function is called on is the "implicit object".
//   - Inside a member function, you can access the implicit object's
//     members directly - no prefix needed.
//   - Members can be defined in any order inside the class.
//   - Member functions can be overloaded.

#include <iostream>
#include <string>

class Rectangle
{
    double m_width{};
    double m_height{};

public:
    Rectangle(double width, double height)
        : m_width{width}, m_height{height}
    {
    }

    // Member function: accesses m_width and m_height of the implicit object
    double area() const
    {
        return m_width * m_height; // no prefix needed - uses implicit object
    }

    double perimeter() const
    {
        return 2.0 * (m_width + m_height);
    }

    // Overloaded member function - scale uniformly
    void scale(double factor)
    {
        m_width *= factor;
        m_height *= factor;
    }

    // Overloaded member function - scale each dimension independently
    void scale(double widthFactor, double heightFactor)
    {
        m_width *= widthFactor;
        m_height *= heightFactor;
    }

    void print() const
    {
        std::cout << "Rectangle(" << m_width << " x " << m_height
                  << ")  area=" << area() // calling another member function
                  << "  perimeter=" << perimeter()
                  << '\n';
    }
};

int main()
{
    Rectangle r{5.0, 3.0};

    // Calling member functions on the object using the dot operator
    r.print();

    std::cout << "Area:      " << r.area() << '\n';
    std::cout << "Perimeter: " << r.perimeter() << '\n';

    // Overloaded member functions
    r.scale(2.0); // uniform scale
    std::cout << "\nAfter scale(2.0):\n";
    r.print();

    r.scale(0.5, 3.0); // independent scale
    std::cout << "After scale(0.5, 3.0):\n";
    r.print();

    // Key insight: every call to area(), perimeter(), etc. operates on
    // the "implicit object" - the Rectangle that appears before the dot.

    return 0;
}
