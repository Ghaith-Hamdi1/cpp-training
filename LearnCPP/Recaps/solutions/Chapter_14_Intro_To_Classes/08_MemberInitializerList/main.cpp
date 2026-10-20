// Chapter 14 - Project 08: Member Initializer Lists
// ====================================================
// Key concepts:
//   - The member initializer list (: m_x{val}, m_y{val}) is the CORRECT
//     way to initialize data members in a constructor.
//   - Assignment in the constructor body is NOT initialization - it's
//     assignment after default initialization already happened.
//   - const members and references MUST be initialized via the member
//     initializer list (they cannot be assigned).
//
// Pitfall:
//   Members are ALWAYS initialized in DECLARATION ORDER, regardless
//   of their order in the initializer list. This can cause subtle bugs.

#include <iostream>
#include <string>

// -----------------------------------------------------------------------
// Demo 1: Initializer list vs. constructor body assignment
// -----------------------------------------------------------------------
class Good
{
public:
    Good(int x, double y, std::string_view name)
        : m_x{x} // initialization (preferred)
          ,
          m_y{y} // initialization (preferred)
          ,
          m_name{name} // initialization (preferred)
    {
        // Constructor body is empty - nothing else to do
    }

    void print() const
    {
        std::cout << "Good { " << m_x << ", " << m_y
                  << ", \"" << m_name << "\" }\n";
    }

private:
    int m_x{};
    double m_y{};
    std::string m_name{};
};

class Bad
{
public:
    Bad(int x, double y, std::string_view name)
    // No member initializer list!
    {
        // These are ASSIGNMENTS, not initializations.
        // m_x, m_y, m_name were already default-initialized before we got here.
        m_x = x;
        m_y = y;
        m_name = name;
        // This works but is less efficient (double initialization).
    }

    void print() const
    {
        std::cout << "Bad  { " << m_x << ", " << m_y
                  << ", \"" << m_name << "\" }\n";
    }

private:
    int m_x{};
    double m_y{};
    std::string m_name{};
};

// -----------------------------------------------------------------------
// Demo 2: Const members MUST use the initializer list
// -----------------------------------------------------------------------
class Config
{
public:
    Config(int maxRetries)
        : m_maxRetries{maxRetries} // REQUIRED - const member
    {
        // m_maxRetries = maxRetries; // ERROR - can't assign to const
    }

    int getMaxRetries() const { return m_maxRetries; }

private:
    const int m_maxRetries; // const - can only be initialized, not assigned
};

// -----------------------------------------------------------------------
// Demo 3: Initialization order pitfall
// -----------------------------------------------------------------------
class OrderDemo
{
public:
    // WARNING: m_a and m_b are listed out of declaration order
    OrderDemo(int value)
        : m_b{value} // m_b is initialized SECOND (declared second)
          ,
          m_a{value * 2} // m_a is initialized FIRST (declared first)
    {
        // Even though m_b appears first in the initializer list,
        // m_a is initialized first because it's declared first.
    }

    void print() const
    {
        std::cout << "OrderDemo { m_a=" << m_a << ", m_b=" << m_b << " }\n";
    }

private:
    int m_a{}; // declared FIRST - initialized FIRST
    int m_b{}; // declared SECOND - initialized SECOND
};

int main()
{
    // Demo 1: Both work, but initializer list is preferred
    Good g{1, 2.5, "hello"};
    g.print();

    Bad b{1, 2.5, "hello"};
    b.print();

    // Demo 2: Const members require the initializer list
    Config cfg{3};
    std::cout << "Max retries: " << cfg.getMaxRetries() << '\n';

    // Demo 3: Initialization order = declaration order
    OrderDemo od{5};
    od.print();
    // m_a = 10, m_b = 5  (NOT the order listed in the initializer list)

    std::cout << "\n-- Takeaway --\n"
              << "Always use the member initializer list.\n"
              << "List members in the SAME ORDER as they are declared.\n";

    return 0;
}
