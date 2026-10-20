// Project 12: Overloading the Copy Assignment Operator (operator=)
// ==================================================================
// operator= MUST be a member function and should return *this by reference
// for chaining. Include a self-assignment check when dynamically allocated
// memory is involved. The compiler provides an implicit memberwise
// assignment operator if you don't define one. You can = delete it.
//
// PITFALL: Forgetting the self-assignment check when the class manages
// dynamic memory - this can delete the data you're trying to copy.

#include <iostream>
#include <cstring>   // for strlen, strcpy
#include <algorithm> // for std::copy_n
#include <cassert>

class MyString
{
private:
    char *m_data{}; // Dynamically allocated C-string
    int m_length{};

public:
    // Constructor from C-string
    MyString(const char *str = "")
        : m_length{static_cast<int>(std::strlen(str))}
    {
        m_data = new char[static_cast<std::size_t>(m_length) + 1];
        std::copy_n(str, static_cast<std::size_t>(m_length) + 1, m_data);
    }

    // Destructor - free the dynamic memory
    ~MyString()
    {
        delete[] m_data;
    }

    // --- Copy Constructor (deep copy) ---
    MyString(const MyString &source)
        : m_length{source.m_length}
    {
        m_data = new char[static_cast<std::size_t>(m_length) + 1];
        std::copy_n(source.m_data, static_cast<std::size_t>(m_length) + 1, m_data);
    }

    // --- Copy Assignment Operator (deep copy) ---
    MyString &operator=(const MyString &source)
    {
        // **SELF-ASSIGNMENT CHECK** - critical when managing dynamic memory!
        // Without this, "str = str;" would delete m_data, then try to copy from
        // the now-deleted memory - undefined behavior!
        if (this == &source)
            return *this;

        // 1. Free existing resource
        delete[] m_data;

        // 2. Deep copy from source
        m_length = source.m_length;
        m_data = new char[static_cast<std::size_t>(m_length) + 1];
        std::copy_n(source.m_data, static_cast<std::size_t>(m_length) + 1, m_data);

        // 3. Return *this by reference for chaining (a = b = c)
        return *this;
    }

    int getLength() const { return m_length; }
    const char *getString() const { return m_data; }

    friend std::ostream &operator<<(std::ostream &out, const MyString &s);
};

std::ostream &operator<<(std::ostream &out, const MyString &s)
{
    out << s.m_data;
    return out;
}

// --- Demonstrating = delete ---
class NonCopyable
{
private:
    int m_value{};

public:
    NonCopyable(int v) : m_value{v} {}

    // Delete copy assignment to prevent copying
    NonCopyable &operator=(const NonCopyable &) = delete;

    // Delete copy constructor too (Rule of Three)
    NonCopyable(const NonCopyable &) = delete;

    int getValue() const { return m_value; }
};

int main()
{
    // --- Basic copy assignment ---
    std::cout << "=== Copy Assignment ===\n";
    MyString hello{"Hello"};
    MyString world{"World"};

    std::cout << "hello = " << hello << '\n';
    std::cout << "world = " << world << '\n';

    // Assignment: world gets a deep copy of hello's data
    world = hello;
    std::cout << "After world = hello:\n";
    std::cout << "  hello = " << hello << '\n';
    std::cout << "  world = " << world << '\n';

    // --- Chaining assignment ---
    std::cout << "\n=== Chaining ===\n";
    MyString a{"Alpha"};
    MyString b{"Beta"};
    MyString c{"Gamma"};

    a = b = c; // Works because operator= returns *this by reference
    std::cout << "After a = b = c (c = \"Gamma\"):\n";
    std::cout << "  a = " << a << ", b = " << b << ", c = " << c << '\n';

    // --- Self-assignment safety ---
    std::cout << "\n=== Self-Assignment ===\n";
    MyString self{"SelfTest"};
    self = self; // Safe! The self-assignment check prevents undefined behavior.
    std::cout << "After self = self: " << self << '\n';

    // --- Deleted assignment ---
    std::cout << "\n=== Deleted operator= ===\n";
    NonCopyable nc1{42};
    // NonCopyable nc2 = nc1;    // ERROR: copy constructor is deleted
    // nc1 = nc2;                // ERROR: copy assignment is deleted
    std::cout << "NonCopyable prevents assignment (= delete)\n";

    // Key points:
    // 1. operator= must be a member function
    // 2. Return *this by reference for chaining
    // 3. Self-assignment check is CRITICAL with dynamic memory
    // 4. Use = delete to prevent assignment entirely
    // 5. If you define operator=, you likely need copy constructor and destructor too (Rule of Three)

    return 0;
}
