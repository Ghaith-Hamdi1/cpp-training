// Chapter 15 - Project 10: Ref Qualifiers
// =========================================
//
// Ref qualifiers (`&` and `&&` after the parameter list) let you
// overload a member function based on whether the implicit object
// (`*this`) is an lvalue or an rvalue.
//
// Common use case: a getter that returns by reference for lvalues
// (efficient, no copy) and by value for rvalues (safe, no dangling ref).
//
// Syntax:
//     const std::string& getName() const &  { return m_name; }   // lvalue version
//     std::string        getName() const && { return m_name; }   // rvalue version
//
// Note: If ANY overload has a ref qualifier, ALL overloads of that
// function must also have ref qualifiers.
//
// This feature adds complexity and is rarely used in practice.
// The simpler alternative: just avoid saving references returned
// from rvalue objects.

#include <iostream>
#include <string>

// -------------------------------------------------------
// Example 1: Getter with ref qualifiers
// -------------------------------------------------------
class Employee
{
private:
    std::string m_name{};
    int m_id{};

public:
    Employee(const std::string &name, int id)
        : m_name{name}, m_id{id}
    {
    }

    // lvalue version - returns by const reference (efficient, no copy)
    const std::string &getName() const &
    {
        std::cout << "  [lvalue getName called]\n";
        return m_name;
    }

    // rvalue version - returns by value (safe - no dangling reference)
    std::string getName() const &&
    {
        std::cout << "  [rvalue getName called]\n";
        return m_name;
    }

    int getId() const { return m_id; }
};

// Factory function that returns a temporary Employee (rvalue)
Employee createEmployee()
{
    return Employee{"Temporary", 999};
}

// -------------------------------------------------------
// Example 2: Demonstrating why ref qualifiers matter
// -------------------------------------------------------
class Data
{
private:
    std::string m_payload{"important data"};

public:
    // Without ref qualifiers, this could return a reference to a
    // temporary object's member - which would be a dangling reference!

    // With ref qualifiers, the rvalue overload returns by value:
    const std::string &getPayload() const & { return m_payload; }
    std::string getPayload() const && { return m_payload; }
};

Data createData()
{
    return Data{};
}

int main()
{
    // --- Example 1: ref qualifiers on getName ---
    std::cout << "=== Ref Qualifiers ===\n\n";

    Employee alice{"Alice", 1};

    // `alice` is an lvalue → calls the `&` overload (returns const ref)
    std::cout << "Lvalue object:\n";
    const std::string &nameRef = alice.getName();
    std::cout << "  Name: " << nameRef << "\n\n";

    // `createEmployee()` returns an rvalue → calls the `&&` overload (returns by value)
    std::cout << "Rvalue object:\n";
    std::string nameCopy = createEmployee().getName();
    std::cout << "  Name: " << nameCopy << "\n\n";

    // --- Example 2: Safety with temporaries ---
    std::cout << "=== Safety with Temporaries ===\n\n";

    Data d{};
    // Lvalue - safe reference
    const std::string &ref = d.getPayload();
    std::cout << "From lvalue: " << ref << '\n';

    // Rvalue - returns by value, so we get a safe copy
    std::string val = createData().getPayload();
    std::cout << "From rvalue: " << val << '\n';

    // Without ref qualifiers, the following WOULD create a dangling reference:
    //   const std::string& danglingRef = createData().getPayload(); // BAD!
    // With the `&&` overload, it returns by value, so even if you write:
    //   auto safe = createData().getPayload();
    // you get a copy, not a dangling reference.

    return 0;
}
