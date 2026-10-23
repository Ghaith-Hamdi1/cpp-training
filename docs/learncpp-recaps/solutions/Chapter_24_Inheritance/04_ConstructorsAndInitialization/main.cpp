// Project 04 - Constructors and Initialization of Derived Classes
// =================================================================
// Key rules:
//   1) Inherited members CANNOT be initialized in the derived class's
//      member initializer list - delegate to the base constructor.
//   2) Assigning inherited members in the derived constructor body
//      fails for const/reference members and is less efficient.
//   3) Destructors run in reverse order of construction.

#include <iostream>
#include <string>
#include <string_view>

class Base
{
private:
    int m_id{};
    std::string m_label{};

public:
    Base(int id, std::string_view label)
        : m_id{id}, m_label{label}
    {
        std::cout << "Base constructed: id=" << m_id
                  << ", label=" << m_label << '\n';
    }

    ~Base()
    {
        std::cout << "Base destructed: id=" << m_id << '\n';
    }

    int getId() const { return m_id; }
    const std::string &getLabel() const { return m_label; }
};

class Derived : public Base
{
private:
    double m_value{};

public:
    // CORRECT: delegate inherited member initialization to Base
    Derived(int id, std::string_view label, double value)
        : Base{id, label} // ← initializes m_id and m_label via Base
          ,
          m_value{value} // ← initializes own member
    {
        std::cout << "Derived constructed: value=" << m_value << '\n';

        // WRONG approach (commented out for illustration):
        // m_id = id;       // ERROR: m_id is private in Base
        // m_label = label; // ERROR: m_label is private in Base
        // Even if they were protected, assignment in the body
        // would fail for const/reference members.
    }

    ~Derived()
    {
        std::cout << "Derived destructed: value=" << m_value << '\n';
    }

    void print() const
    {
        std::cout << "Derived [id=" << getId()
                  << ", label=" << getLabel()
                  << ", value=" << m_value << "]\n";
    }
};

int main()
{
    std::cout << "--- Creating Derived object ---\n";
    {
        Derived obj{42, "Alpha", 3.14};
        obj.print();
    }
    std::cout << "--- Derived object destroyed ---\n";

    // Output shows:
    //   Base constructor runs first  (most-base → most-derived)
    //   Derived destructor runs first (most-derived → most-base)

    return 0;
}
