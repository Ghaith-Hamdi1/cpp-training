// Chapter 14 - Project 09: Default Constructors
// ================================================
// Key concepts:
//   - A default constructor takes no arguments (or all arguments have defaults).
//   - If NO constructors are user-declared, the compiler generates an
//     implicit default constructor.
//   - Once you declare ANY constructor, the implicit default constructor
//     is no longer generated.
//   - Use '= default' to explicitly request a compiler-generated default
//     constructor.
//   - Only provide a default constructor when default-initialized objects
//     make sense semantically.

#include <iostream>
#include <string>

// -----------------------------------------------------------------------
// Case 1: No user-declared constructors → implicit default constructor
// -----------------------------------------------------------------------
class Implicit
{
public:
    // No constructors declared at all.
    // The compiler generates a default constructor that value-initializes
    // members using their default member initializers.

    void print() const
    {
        std::cout << "Implicit { m_value=" << m_value << " }\n";
    }

private:
    int m_value{42}; // default member initializer
};

// -----------------------------------------------------------------------
// Case 2: User-declared constructor → NO implicit default constructor
// -----------------------------------------------------------------------
class NoDefault
{
public:
    NoDefault(int value) // user-declared constructor
        : m_value{value}
    {
    }

    void print() const
    {
        std::cout << "NoDefault { m_value=" << m_value << " }\n";
    }

private:
    int m_value{};
};

// -----------------------------------------------------------------------
// Case 3: Bringing back the default constructor with '= default'
// -----------------------------------------------------------------------
class WithDefault
{
public:
    WithDefault() = default; // explicitly request compiler-generated default

    WithDefault(int value)
        : m_value{value}
    {
    }

    void print() const
    {
        std::cout << "WithDefault { m_value=" << m_value << " }\n";
    }

private:
    int m_value{0}; // default member initializer used by = default
};

// -----------------------------------------------------------------------
// Case 4: When a default constructor DOESN'T make sense
// -----------------------------------------------------------------------
class Employee
{
public:
    // An Employee without a name is semantically invalid.
    // So we intentionally do NOT provide a default constructor.
    Employee(std::string_view name, int id)
        : m_name{name}, m_id{id}
    {
    }

    void print() const
    {
        std::cout << "Employee { \"" << m_name << "\", id=" << m_id << " }\n";
    }

private:
    std::string m_name;
    int m_id{};
};

int main()
{
    // Case 1: Implicit default constructor works
    Implicit imp{};
    imp.print(); // m_value = 42 (from default member initializer)

    // Case 2: No default constructor - must provide an argument
    // NoDefault nd{};    // ERROR - no default constructor
    NoDefault nd{10};
    nd.print();

    // Case 3: Explicit = default brings the default constructor back
    WithDefault wd1{};  // uses = default constructor → m_value = 0
    WithDefault wd2{7}; // uses parameterized constructor → m_value = 7
    wd1.print();
    wd2.print();

    // Case 4: No default constructor by design
    // Employee e{};      // ERROR - Employee always needs a name
    Employee e{"Alice", 101};
    e.print();

    std::cout << "\n-- Takeaway --\n"
              << "Use '= default' to explicitly request a default constructor.\n"
              << "Don't provide one if default-constructed objects are invalid.\n";

    return 0;
}
