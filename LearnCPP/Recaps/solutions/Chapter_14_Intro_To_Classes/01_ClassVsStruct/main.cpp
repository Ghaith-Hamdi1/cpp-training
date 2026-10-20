// Chapter 14 - Project 01: Class vs Struct
// ==========================================
// Key concept: The only difference between 'class' and 'struct' in C++ is the
// DEFAULT access level of their members.
//   - struct members default to PUBLIC
//   - class  members default to PRIVATE
//
// Best practice:
//   - Use 'struct' for simple aggregates (plain data, no invariants).
//   - Use 'class' when you need private data or must enforce invariants.

#include <iostream>
#include <string>

// -----------------------------------------------------------------------
// A struct - members are public by default.
// Use structs for simple "bundles of data" that don't need invariants.
// -----------------------------------------------------------------------
struct Point
{
    double x{}; // public by default
    double y{}; // public by default

    // Structs CAN have member functions, but should avoid constructors
    // (to remain aggregates and keep aggregate initialization).
    void print() const
    {
        std::cout << "Point(" << x << ", " << y << ")\n";
    }
};

// -----------------------------------------------------------------------
// A class - members are private by default.
// Use classes when you need to enforce invariants or hide data.
// -----------------------------------------------------------------------
class Employee
{
    // These are PRIVATE by default (no access specifier needed).
    std::string m_name{};
    int m_id{};

public:
    // Public constructor - the controlled way to create an Employee
    Employee(std::string_view name, int id)
        : m_name{name}, m_id{id}
    {
    }

    // Public interface - users interact with Employee through these functions
    void print() const
    {
        std::cout << "Employee { name: \"" << m_name
                  << "\", id: " << m_id << " }\n";
    }
};

int main()
{
    // --- Struct usage: aggregate initialization, direct member access ---
    Point p1{3.5, 7.2}; // aggregate initialization works
    p1.x = 10.0;        // direct access OK - members are public
    p1.print();

    Point p2{}; // zero-initialized
    p2.print();

    // --- Class usage: must go through constructor and public interface ---
    Employee emp{"Alice", 1001};
    emp.print();

    // emp.m_name = "Bob";    // ERROR - m_name is PRIVATE (class default)
    // This is the key difference: the class protects its data.

    std::cout << "\n-- Takeaway --\n"
              << "struct = public by default  -> use for plain data\n"
              << "class  = private by default -> use when you need encapsulation\n";

    return 0;
}
