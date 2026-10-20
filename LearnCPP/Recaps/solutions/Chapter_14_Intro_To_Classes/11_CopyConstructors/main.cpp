// Chapter 14 - Project 11: Copy Constructors
// =============================================
// Key concepts:
//   - The copy constructor initializes a NEW object as a copy of an
//     existing object of the same type.
//   - The implicit (compiler-generated) copy constructor does
//     memberwise initialization (copies each member).
//   - The parameter MUST be a const lvalue reference (to avoid infinite
//     recursion - if it took by value, it would need to copy, which
//     calls the copy constructor, which copies...).
//   - Copy constructors should have NO side effects beyond copying.
//   - Use '= default' to explicitly request the compiler-generated copy.
//   - Use '= delete' to prevent copying entirely.

#include <iostream>
#include <string>

// -----------------------------------------------------------------------
// Class with an implicit copy constructor (compiler-generated)
// -----------------------------------------------------------------------
class Point
{
public:
    Point(double x, double y) : m_x{x}, m_y{y} {}

    // No copy constructor declared - compiler generates one automatically.
    // It does memberwise initialization: copy m_x, copy m_y.

    void print() const
    {
        std::cout << "Point(" << m_x << ", " << m_y << ")\n";
    }

private:
    double m_x{};
    double m_y{};
};

// -----------------------------------------------------------------------
// Class with an explicit copy constructor (for demonstration)
// -----------------------------------------------------------------------
class Fraction
{
public:
    Fraction(int num, int den)
        : m_num{num}, m_den{den}
    {
    }

    // Explicit copy constructor
    // Parameter MUST be const lvalue reference
    Fraction(const Fraction &other)
        : m_num{other.m_num}, m_den{other.m_den}
    {
        // In real code, avoid side effects here.
        std::cout << "  [Fraction copy constructor called]\n";
    }

    void print() const
    {
        std::cout << m_num << "/" << m_den << '\n';
    }

private:
    int m_num{};
    int m_den{};
};

// -----------------------------------------------------------------------
// Class where copying is DELETED
// -----------------------------------------------------------------------
class UniqueResource
{
public:
    UniqueResource(int id) : m_id{id}
    {
        std::cout << "  [UniqueResource " << m_id << " created]\n";
    }

    // Delete the copy constructor - this object cannot be copied
    UniqueResource(const UniqueResource &) = delete;

    int getId() const { return m_id; }

private:
    int m_id{};
};

// A function that takes by value - requires a copy
void printFraction(Fraction f)
{
    std::cout << "Fraction value: ";
    f.print();
}

int main()
{
    // --- Implicit copy constructor ---
    Point p1{3.0, 4.0};
    Point p2{p1}; // copy constructor called (implicit)
    std::cout << "p1: ";
    p1.print();
    std::cout << "p2: ";
    p2.print();

    // --- Explicit copy constructor ---
    std::cout << "\n--- Fraction copies ---\n";
    Fraction half{1, 2};

    Fraction halfCopy{half}; // direct copy initialization
    std::cout << "halfCopy: ";
    halfCopy.print();

    Fraction halfCopy2 = half; // copy initialization (= syntax)
    std::cout << "halfCopy2: ";
    halfCopy2.print();

    // Passing by value triggers a copy
    std::cout << "\nPassing by value:\n";
    printFraction(half);

    // --- Deleted copy constructor ---
    std::cout << "\n--- UniqueResource ---\n";
    UniqueResource res{42};
    // UniqueResource resCopy{ res };  // ERROR - copy constructor is deleted
    std::cout << "Resource ID: " << res.getId() << '\n';

    std::cout << "\n-- Takeaway --\n"
              << "Copy constructor param must be const lvalue ref.\n"
              << "Use = default or = delete to control copying.\n";

    return 0;
}
