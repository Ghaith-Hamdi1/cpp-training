// Chapter 26 - Project 9: static_assert with Type Traits
// =========================================================
// Instead of partially specializing a class to handle (or reject) pointer
// types, you can use `static_assert` with type traits to produce a clear
// compile-time error when someone tries to instantiate the template with
// an unwanted type.
//
// This is often simpler and more explicit than partial specialization.
//
// Key type traits used here:
//   std::is_pointer_v<T>      - true if T is a pointer type
//   std::is_arithmetic_v<T>   - true if T is int, double, char, etc.
//   std::is_class_v<T>        - true if T is a class/struct

#include <iostream>
#include <string>
#include <type_traits>

// ---------------------------------------------------------------------------
// A Storage class that REFUSES pointer types at compile time
// ---------------------------------------------------------------------------
template <typename T>
class SafeStorage
{
    // This fires at instantiation time if T is a pointer
    static_assert(!std::is_pointer_v<T>,
                  "SafeStorage cannot be instantiated with pointer types. "
                  "Pass the value directly instead.");

private:
    T m_value;

public:
    SafeStorage(const T &value) : m_value{value} {}

    const T &getValue() const { return m_value; }

    void print() const
    {
        std::cout << "SafeStorage: " << m_value << '\n';
    }
};

// ---------------------------------------------------------------------------
// A numeric-only container that requires arithmetic types
// ---------------------------------------------------------------------------
template <typename T>
class NumericBox
{
    static_assert(std::is_arithmetic_v<T>,
                  "NumericBox requires an arithmetic type (int, float, double, char, etc.).");

private:
    T m_value;

public:
    NumericBox(T value) : m_value{value} {}

    T doubled() const { return m_value * 2; }

    void print() const
    {
        std::cout << "NumericBox: " << m_value
                  << "  (doubled = " << doubled() << ")\n";
    }
};

// ---------------------------------------------------------------------------
// Demonstrate multiple static_assert conditions
// ---------------------------------------------------------------------------
template <typename T>
class NonPointerNonBool
{
    static_assert(!std::is_pointer_v<T>, "No pointers allowed.");
    static_assert(!std::is_same_v<T, bool>, "No bools allowed.");

private:
    T m_value;

public:
    NonPointerNonBool(const T &value) : m_value{value} {}

    void print() const
    {
        std::cout << "NonPointerNonBool: " << m_value << '\n';
    }
};

// ---------------------------------------------------------------------------
int main()
{
    // Valid uses
    SafeStorage<int> si(42);
    si.print(); // SafeStorage: 42

    SafeStorage<std::string> ss("hello");
    ss.print(); // SafeStorage: hello

    NumericBox<int> ni(21);
    ni.print(); // NumericBox: 21  (doubled = 42)

    NumericBox<double> nd(1.5);
    nd.print(); // NumericBox: 1.5  (doubled = 3)

    NonPointerNonBool<int> npi(7);
    npi.print(); // NonPointerNonBool: 7

    // -----------------------------------------------------------------------
    // BLOCKED uses (uncomment any to see the compile-time error):
    //
    //   SafeStorage<int*> bad1(nullptr);
    //   // error: "SafeStorage cannot be instantiated with pointer types."
    //
    //   NumericBox<std::string> bad2("hi");
    //   // error: "NumericBox requires an arithmetic type."
    //
    //   NonPointerNonBool<bool> bad3(true);
    //   // error: "No bools allowed."
    //
    //   NonPointerNonBool<double*> bad4(nullptr);
    //   // error: "No pointers allowed."
    // -----------------------------------------------------------------------

    std::cout << "\nAll static_assert checks passed for valid types.\n";

    return 0;
}
