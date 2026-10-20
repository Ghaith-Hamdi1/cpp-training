// Project 07 - Adding New Functionality to a Derived Class
// ==========================================================
// Derived classes can define new member functions that don't
// exist in the base class. This extends the base without modifying it.
// Base class objects CANNOT access derived-class-only functions.

#include <iostream>
#include <string>
#include <string_view>

class Shape
{
private:
    std::string m_color{};

public:
    Shape(std::string_view color)
        : m_color{color}
    {
    }

    const std::string &getColor() const { return m_color; }

    void describe() const
    {
        std::cout << "A " << m_color << " shape\n";
    }
};

// Circle inherits Shape and adds radius-related functionality
class Circle : public Shape
{
private:
    double m_radius{};

public:
    Circle(std::string_view color, double radius)
        : Shape{color}, m_radius{radius}
    {
    }

    // New functionality - not present in Shape
    double getRadius() const { return m_radius; }

    double getArea() const
    {
        return 3.14159265 * m_radius * m_radius;
    }

    double getCircumference() const
    {
        return 2.0 * 3.14159265 * m_radius;
    }

    void printDetails() const
    {
        std::cout << "Circle: color=" << getColor()
                  << ", radius=" << m_radius
                  << ", area=" << getArea()
                  << ", circumference=" << getCircumference() << '\n';
    }
};

// Rectangle inherits Shape and adds width/height functionality
class Rectangle : public Shape
{
private:
    double m_width{};
    double m_height{};

public:
    Rectangle(std::string_view color, double width, double height)
        : Shape{color}, m_width{width}, m_height{height}
    {
    }

    double getArea() const { return m_width * m_height; }
    double getPerimeter() const { return 2.0 * (m_width + m_height); }

    void printDetails() const
    {
        std::cout << "Rectangle: color=" << getColor()
                  << ", " << m_width << "x" << m_height
                  << ", area=" << getArea()
                  << ", perimeter=" << getPerimeter() << '\n';
    }
};

int main()
{
    Shape s{"red"};
    s.describe();
    // s.getArea();  // ERROR: Shape has no getArea()

    std::cout << '\n';

    Circle c{"blue", 5.0};
    c.describe();     // inherited from Shape
    c.printDetails(); // new in Circle

    std::cout << '\n';

    Rectangle r{"green", 4.0, 6.0};
    r.describe();     // inherited from Shape
    r.printDetails(); // new in Rectangle

    return 0;
}
