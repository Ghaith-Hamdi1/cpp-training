// Project 06 - Public, Protected, and Private Inheritance
// =========================================================
// The inheritance access specifier controls how base class members
// are exposed through the derived class:
//
//   Base member  | public inh. | protected inh. | private inh.
//   -------------|-------------|----------------|-------------
//   public       | public      | protected      | private
//   protected    | protected   | protected      | private
//   private      | inaccessible| inaccessible   | inaccessible
//
// Best practice: use public inheritance unless you have a specific
// reason for the other forms (they are rarely used).

#include <iostream>

class Base
{
public:
    int m_public{1};

protected:
    int m_protected{2};

private:
    int m_private{3}; // always inaccessible to derived classes
};

// --- Public inheritance ---
// public → public, protected → protected
class PubDerived : public Base
{
public:
    void test()
    {
        std::cout << "[PubDerived] m_public = " << m_public << " (public)\n";
        std::cout << "[PubDerived] m_protected = " << m_protected << " (protected)\n";
        // m_private is inaccessible
    }
};

// --- Protected inheritance ---
// public → protected, protected → protected
class ProtDerived : protected Base
{
public:
    void test()
    {
        // Both are accessible inside the class, but as protected
        std::cout << "[ProtDerived] m_public = " << m_public << " (now protected)\n";
        std::cout << "[ProtDerived] m_protected = " << m_protected << " (still protected)\n";
    }
};

// --- Private inheritance ---
// public → private, protected → private
class PrivDerived : private Base
{
public:
    void test()
    {
        // Both are accessible inside the class, but as private
        std::cout << "[PrivDerived] m_public = " << m_public << " (now private)\n";
        std::cout << "[PrivDerived] m_protected = " << m_protected << " (now private)\n";
    }
};

// Further derivation illustrates the cascading effect
class GrandChild : public PrivDerived
{
public:
    void test()
    {
        // Because PrivDerived inherited privately, m_public and m_protected
        // became private in PrivDerived → inaccessible here
        // m_public;     // ERROR
        // m_protected;  // ERROR
        std::cout << "[GrandChild] Cannot access Base members through private inheritance\n";
    }
};

int main()
{
    PubDerived pub;
    pub.test();
    std::cout << "main: pub.m_public = " << pub.m_public << " (still public)\n";
    // pub.m_protected;  // ERROR: protected

    std::cout << '\n';

    ProtDerived prot;
    prot.test();
    // prot.m_public;  // ERROR: now protected due to protected inheritance

    std::cout << '\n';

    PrivDerived priv;
    priv.test();
    // priv.m_public;  // ERROR: now private due to private inheritance

    std::cout << '\n';

    GrandChild gc;
    gc.test();

    return 0;
}
