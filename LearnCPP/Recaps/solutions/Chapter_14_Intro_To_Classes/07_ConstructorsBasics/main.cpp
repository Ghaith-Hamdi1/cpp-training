// Chapter 14 - Project 07: Introduction to Constructors
// =======================================================
// Key concepts:
//   - A constructor is a special member function used to initialize
//     non-aggregate class objects. It has:
//       * The same name as the class
//       * No return type (not even void)
//       * Must NOT be const
//   - If no matching constructor exists → compilation error.
//   - Constructors don't CREATE objects - they initialize already-allocated
//     memory.
//   - Best practice for a failing constructor: throw an exception.

#include <iostream>
#include <string>
#include <stdexcept>

class Date
{
public:
    // Constructor - validates inputs and initializes the object
    Date(int year, int month, int day)
        : m_year{year}, m_month{month}, m_day{day}
    {
        // Enforce invariants: throw if the date is obviously invalid
        if (month < 1 || month > 12)
            throw std::invalid_argument("Month must be 1-12");
        if (day < 1 || day > 31)
            throw std::invalid_argument("Day must be 1-31");
    }

    // Note: the constructor is NOT const, even though it doesn't "modify"
    //       the object after initialization. This is by design.

    void print() const
    {
        std::cout << m_year << '-'
                  << (m_month < 10 ? "0" : "") << m_month << '-'
                  << (m_day < 10 ? "0" : "") << m_day << '\n';
    }

private:
    int m_year{};
    int m_month{};
    int m_day{};
};

int main()
{
    // Normal construction
    Date birthday{2000, 6, 15};
    std::cout << "Birthday: ";
    birthday.print();

    Date today{2026, 3, 17};
    std::cout << "Today:    ";
    today.print();

    // Construction failure - the constructor throws
    try
    {
        Date bad{2026, 13, 1}; // month 13 is invalid
        bad.print();           // won't reach this
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Caught exception: " << e.what() << '\n';
    }

    // Without a matching constructor, this wouldn't compile:
    // Date d;               // ERROR - no default constructor
    // Date d{ "hello" };    // ERROR - no constructor taking a string

    std::cout << "\n-- Takeaway --\n"
              << "Constructors initialize objects. Name matches the class, no return type.\n"
              << "Throw an exception if initialization fails.\n";

    return 0;
}
