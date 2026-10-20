// Chapter 23 - Project 07: Dependency ("depends-on")
// =====================================================
//
// A dependency is the WEAKEST object relationship.
// One object temporarily uses another to accomplish a task.
//
// Key properties:
//   - The depended-on object is NOT a member of the class.
//   - It is passed as a parameter, or instantiated locally within a method.
//   - The relationship is always unidirectional.
//   - The dependency exists only for the duration of the call.
//
// Classic example: operator<< depends on std::ostream.

#include <iostream>
#include <string>
#include <sstream> // std::ostringstream - used as a local dependency

class Point
{
private:
    double m_x{};
    double m_y{};

public:
    Point(double x, double y) : m_x{x}, m_y{y} {}

    double getX() const { return m_x; }
    double getY() const { return m_y; }

    // Dependency: Point depends on std::ostream (passed as a parameter).
    // Point doesn't own the stream - it just uses it temporarily.
    friend std::ostream &operator<<(std::ostream &out, const Point &p)
    {
        out << '(' << p.m_x << ", " << p.m_y << ')';
        return out;
    }
};

class Logger
{
public:
    // Dependency: Logger depends on std::ostringstream (created locally).
    // The stream exists only for the duration of this call.
    static std::string formatMessage(std::string_view prefix, const Point &p)
    {
        std::ostringstream oss; // Local dependency
        oss << "[" << prefix << "] " << p;
        return oss.str();
    }
};

// A Timer that depends on a callback function (temporary usage)
class Timer
{
private:
    std::string m_label;

public:
    Timer(std::string_view label) : m_label{label} {}

    // Dependency: Timer depends on the callable passed as a parameter.
    // It doesn't own the callable - it just invokes it.
    void execute(void (*callback)()) const
    {
        std::cout << "[Timer: " << m_label << "] Starting...\n";
        callback(); // Use the dependency
        std::cout << "[Timer: " << m_label << "] Done.\n";
    }
};

void doWork()
{
    std::cout << "  Performing some work...\n";
}

int main()
{
    std::cout << "=== Dependency: Temporary Usage of Another Object ===\n\n";

    // Example 1: operator<< depends on std::ostream (parameter dependency)
    Point p{3.0, 4.5};
    std::cout << "Point: " << p << '\n'; // std::cout is the dependency

    // Example 2: Logger::formatMessage depends on std::ostringstream (local)
    std::string msg = Logger::formatMessage("INFO", p);
    std::cout << msg << '\n';

    // Example 3: Timer depends on a callback (parameter dependency)
    std::cout << '\n';
    Timer timer{"Task1"};
    timer.execute(doWork);

    std::cout << "\nIn all cases, the depended-on object is NOT a member.\n"
              << "It's either passed as a parameter or created locally.\n";

    return 0;
}
