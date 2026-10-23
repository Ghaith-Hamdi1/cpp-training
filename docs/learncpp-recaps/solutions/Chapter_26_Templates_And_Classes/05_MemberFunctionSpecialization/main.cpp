// Chapter 26 - Project 5: Specializing a Single Member Function
// ================================================================
// You can specialize ONE member function of a class template without
// rewriting the entire class. This lets you keep the primary template
// for most types and override only the behavior that differs.
//
// Syntax:
//   template <>
//   void ClassName<SpecificType>::memberFunction() { ... }
//
// The rest of the class (data members, other functions) comes from the
// primary template - you only replace the one function.

#include <iostream>
#include <string>

// ---------------------------------------------------------------------------
// Primary template
// ---------------------------------------------------------------------------
template <typename T>
class Storage
{
private:
    T m_value{};

public:
    Storage(const T &value) : m_value{value} {}

    void print() const
    {
        std::cout << "Storage<T>::print() → " << m_value << '\n';
    }

    const T &getValue() const { return m_value; }
};

// ---------------------------------------------------------------------------
// Specialize ONLY the print() member for T = double
// ---------------------------------------------------------------------------
// We don't rewrite the class - only this one function gets custom behavior.
template <>
void Storage<double>::print() const
{
    std::cout << "Storage<double>::print() → "
              << std::scientific << m_value << std::defaultfloat << '\n';
}

// ---------------------------------------------------------------------------
// Specialize ONLY the print() member for T = bool
// ---------------------------------------------------------------------------
template <>
void Storage<bool>::print() const
{
    std::cout << "Storage<bool>::print() → "
              << (m_value ? "true" : "false") << '\n';
}

// ---------------------------------------------------------------------------
int main()
{
    Storage<int> si(42);
    si.print();
    // Output: Storage<T>::print() → 42
    // Uses the primary template's print().

    Storage<double> sd(3.14159);
    sd.print();
    // Output: Storage<double>::print() → 3.141590e+00
    // Uses our specialized print() that formats in scientific notation.

    Storage<bool> sb(true);
    sb.print();
    // Output: Storage<bool>::print() → true
    // Uses our specialized print() that shows "true"/"false".

    Storage<std::string> ss("hello");
    ss.print();
    // Output: Storage<T>::print() → hello
    // No specialization for std::string - falls back to primary.

    // All other members (getValue, constructor, etc.) are still provided
    // by the primary template for every type, including double and bool.
    std::cout << "\ngetValue() still works from primary template:\n";
    std::cout << "  si: " << si.getValue() << '\n';
    std::cout << "  sd: " << sd.getValue() << '\n';
    std::cout << "  sb: " << sb.getValue() << '\n';

    return 0;
}
