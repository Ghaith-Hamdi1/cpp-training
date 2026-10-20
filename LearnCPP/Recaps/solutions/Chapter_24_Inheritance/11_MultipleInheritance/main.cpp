// Project 11 - Multiple Inheritance
// ====================================
// A class can inherit from more than one base class:
//   class T : public A, public B { ... };
//
// Risks:
//   - Ambiguous function calls when bases share function names
//   - The diamond problem (next project)
//
// Resolution: use explicit scope (obj.Base::func()) to resolve ambiguity.
// Best practice: avoid multiple inheritance unless alternatives are more complex.

#include <iostream>
#include <string>
#include <string_view>

// Mixin-style class: adds serialization capability
class Serializable
{
public:
    void serialize() const
    {
        std::cout << "[Serializable] serializing object...\n";
    }

    void info() const
    {
        std::cout << "[Serializable] I can be serialized\n";
    }
};

// Mixin-style class: adds logging capability
class Loggable
{
public:
    void log(std::string_view message) const
    {
        std::cout << "[Loggable] LOG: " << message << '\n';
    }

    void info() const
    {
        std::cout << "[Loggable] I can be logged\n";
    }
};

// Document inherits from both Serializable and Loggable
class Document : public Serializable, public Loggable
{
private:
    std::string m_title{};

public:
    Document(std::string_view title)
        : m_title{title}
    {
    }

    void print() const
    {
        std::cout << "Document: " << m_title << '\n';
    }
};

int main()
{
    Document doc{"Design Notes"};
    doc.print();

    // Functions with unique names work fine:
    doc.serialize();    // from Serializable
    doc.log("created"); // from Loggable

    std::cout << '\n';

    // PROBLEM: both bases have info() - this is ambiguous
    // doc.info();           // ERROR: ambiguous - which info()?

    // Resolution: use explicit scope
    std::cout << "Resolving ambiguity:\n";
    doc.Serializable::info();
    doc.Loggable::info();

    return 0;
}
