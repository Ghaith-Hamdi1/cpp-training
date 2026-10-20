// Project 08 - Overriding Behavior (Function Redefinition)
// ==========================================================
// When a derived class defines a function with the same name and
// signature as one in the base class, the derived version is
// used for derived objects.
//
// CRITICAL: to call the base version from inside the override,
// use the scope resolution operator: Base::functionName().
// Without it, you get INFINITE RECURSION.

#include <iostream>
#include <string>
#include <string_view>

class Base
{
private:
    int m_id{};

public:
    Base(int id) : m_id{id} {}

    int getId() const { return m_id; }

    void print() const
    {
        std::cout << "Base [id=" << m_id << "]";
    }
};

class Derived : public Base
{
private:
    double m_value{};

public:
    Derived(int id, double value)
        : Base{id}, m_value{value}
    {
    }

    // Override print() - provides a new version for Derived objects
    void print() const
    {
        // CORRECT: call the base version using scope resolution
        Base::print();
        // Then add derived-specific information
        std::cout << " + Derived [value=" << m_value << "]";
    }

    // BAD example (commented out) - causes infinite recursion:
    // void print() const
    // {
    //     print();  // Oops! Calls Derived::print() again - infinite recursion!
    // }
};

class MostDerived : public Derived
{
private:
    std::string m_tag{};

public:
    MostDerived(int id, double value, std::string_view tag)
        : Derived{id, value}, m_tag{tag}
    {
    }

    // Override again at a deeper level
    void print() const
    {
        Derived::print(); // calls Derived::print, which calls Base::print
        std::cout << " + MostDerived [tag=" << m_tag << "]";
    }
};

int main()
{
    Base b{1};
    std::cout << "b.print():  ";
    b.print();
    std::cout << "\n\n";

    Derived d{2, 3.14};
    std::cout << "d.print():  ";
    d.print();
    std::cout << "\n\n";

    MostDerived md{3, 2.72, "gamma"};
    std::cout << "md.print(): ";
    md.print();
    std::cout << "\n\n";

    // You can also explicitly call the base version on a derived object:
    std::cout << "md via Base::print(): ";
    md.Base::print();
    std::cout << '\n';

    return 0;
}
