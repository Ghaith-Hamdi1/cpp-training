// Chapter 14 - Project 14: Converting Constructors and the explicit Keyword
// ===========================================================================
// Key concepts:
//   - Any constructor that can be called with a single argument is a
//     "converting constructor" by default - it allows IMPLICIT conversions.
//   - Only ONE user-defined conversion is applied per implicit conversion.
//   - The 'explicit' keyword prevents a constructor from being used
//     for implicit conversions.
//
// Best practice:
//   Make single-argument constructors 'explicit' by default to prevent
//   surprising silent conversions.
//
// Pitfall:
//   Forgetting 'explicit' allows the compiler to silently convert
//   unrelated types into your class, leading to confusing behavior.

#include <iostream>
#include <string>
#include <string_view>

// -----------------------------------------------------------------------
// BAD: Implicit converting constructor - allows silent conversion
// -----------------------------------------------------------------------
class Inches
{
public:
    // This constructor is NOT explicit - it's a converting constructor.
    // The compiler can silently convert an int to Inches.
    Inches(double value) : m_value{value} {}

    double getValue() const { return m_value; }

    void print() const
    {
        std::cout << m_value << " inches";
    }

private:
    double m_value{};
};

void printLength(Inches length)
{
    std::cout << "Length: ";
    length.print();
    std::cout << '\n';
}

// -----------------------------------------------------------------------
// GOOD: Explicit constructor - prevents silent conversion
// -----------------------------------------------------------------------
class Centimeters
{
public:
    // 'explicit' prevents this constructor from being used for implicit conversions
    explicit Centimeters(double value) : m_value{value} {}

    double getValue() const { return m_value; }

    void print() const
    {
        std::cout << m_value << " cm";
    }

private:
    double m_value{};
};

void printMetricLength(Centimeters length)
{
    std::cout << "Length: ";
    length.print();
    std::cout << '\n';
}

// -----------------------------------------------------------------------
// GOOD: explicit with std::string_view constructor
// -----------------------------------------------------------------------
class Username
{
public:
    explicit Username(std::string_view name) : m_name{name} {}

    void print() const
    {
        std::cout << "Username: " << m_name << '\n';
    }

private:
    std::string m_name{};
};

int main()
{
    // --- Implicit conversion (BAD - Inches is not explicit) ---
    std::cout << "=== Without explicit (Inches) ===\n";

    Inches i1{5.0}; // direct init - always works
    printLength(i1);

    printLength(10.0); // IMPLICIT conversion: double → Inches
    //   ^ The compiler silently calls Inches{10.0} - this may be unintended!

    Inches i2 = 7.5; // copy initialization with implicit conversion
    i2.print();
    std::cout << '\n';

    // --- Explicit constructor (GOOD - Centimeters prevents silent conversion) ---
    std::cout << "\n=== With explicit (Centimeters) ===\n";

    Centimeters c1{25.0}; // direct init - always works
    printMetricLength(c1);

    // printMetricLength(25.0);  // ERROR - implicit conversion blocked by 'explicit'
    // Centimeters c2 = 25.0;   // ERROR - copy init with conversion blocked

    // You must be EXPLICIT about the conversion:
    printMetricLength(Centimeters{30.0});              // OK - explicit construction
    printMetricLength(static_cast<Centimeters>(40.0)); // OK - explicit cast

    // --- Explicit with string_view ---
    std::cout << "\n=== Explicit Username ===\n";
    Username user{"Alice"};
    user.print();

    // Username u2 = "Bob";     // ERROR - implicit conversion blocked
    // The user must explicitly construct:
    Username u3{"Charlie"};
    u3.print();

    std::cout << "\n-- Takeaway --\n"
              << "Make single-argument constructors 'explicit' by default.\n"
              << "This prevents the compiler from silently converting types.\n";

    return 0;
}
