// Project 05 - The Protected Access Specifier
// ==============================================
// `protected` members are accessible by:
//   - The class itself
//   - Friend functions/classes
//   - Derived classes
// But NOT by the general public (outside code).
//
// Best practice: favor private members; use protected only when
// derived classes genuinely need direct access and the cost of
// providing an interface (getters/setters) is too high.

#include <iostream>
#include <string>
#include <string_view>

class Base
{
public:
    int m_public{1}; // accessible everywhere

protected:
    int m_protected{2}; // accessible in Base, friends, and derived classes

private:
    int m_private{3}; // accessible only in Base and friends

public:
    Base() = default;

    void printAll() const
    {
        // Base can access everything
        std::cout << "Base sees:  public=" << m_public
                  << "  protected=" << m_protected
                  << "  private=" << m_private << '\n';
    }
};

class Derived : public Base
{
public:
    void printAccess() const
    {
        std::cout << "Derived sees:\n";
        std::cout << "  m_public    = " << m_public << "  (OK - public)\n";
        std::cout << "  m_protected = " << m_protected << "  (OK - protected)\n";

        // The following would NOT compile:
        // std::cout << m_private;
        // ERROR: m_private is private in Base and inaccessible to Derived
        // Even though m_private EXISTS in the Derived object's memory,
        // the compiler prevents access.
        std::cout << "  m_private   = (inaccessible - private in Base)\n";
    }
};

int main()
{
    Base b{};
    b.printAll();

    std::cout << '\n';

    Derived d{};
    d.printAccess();

    std::cout << '\n';

    // From outside (main), only public members are accessible:
    std::cout << "main() sees: d.m_public = " << d.m_public << '\n';
    // d.m_protected;  // ERROR: protected
    // d.m_private;    // ERROR: private

    return 0;
}
