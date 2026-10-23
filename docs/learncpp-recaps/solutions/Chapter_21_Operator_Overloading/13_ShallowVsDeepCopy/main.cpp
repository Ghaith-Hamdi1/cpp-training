// Project 13: Shallow vs. Deep Copying and the Rule of Three
// =============================================================
// The compiler's default copy constructor and assignment operator perform
// SHALLOW (memberwise) copies. For classes with dynamically allocated memory,
// shallow copies cause multiple objects to share the same memory, leading to
// dangling pointers and double-deletes.
//
// DEEP copying allocates new memory and copies the actual data.
//
// Rule of Three: If you need a custom destructor, copy constructor, or
// copy assignment operator, you likely need ALL THREE.
//
// Best practice: Prefer std::string, std::vector over manual memory management.

#include <iostream>
#include <cstring>
#include <algorithm>

// ======================================================================
// BAD EXAMPLE: Shallow copy with raw pointers - demonstrates the problem
// ======================================================================
class ShallowString
{
private:
    char *m_data{};
    int m_length{};

public:
    ShallowString(const char *str = "")
        : m_length{static_cast<int>(std::strlen(str))}
    {
        m_data = new char[static_cast<std::size_t>(m_length) + 1];
        std::copy_n(str, static_cast<std::size_t>(m_length) + 1, m_data);
        std::cout << "  [Constructed: \"" << m_data << "\"]\n";
    }

    ~ShallowString()
    {
        std::cout << "  [Destructor called";
        if (m_data)
            std::cout << " for data at " << static_cast<void *>(m_data);
        std::cout << "]\n";
        delete[] m_data;
        // NOTE: No custom copy constructor/assignment - compiler does SHALLOW copy.
        // Two objects will point to the SAME m_data. When one is destroyed,
        // the other has a dangling pointer. Double-delete = undefined behavior!
    }

    const char *getString() const { return m_data; }
    void setChar(int index, char ch) { m_data[index] = ch; }
};

// ======================================================================
// GOOD EXAMPLE: Deep copy - each object owns its own memory
// ======================================================================
class DeepString
{
private:
    char *m_data{};
    int m_length{};

public:
    DeepString(const char *str = "")
        : m_length{static_cast<int>(std::strlen(str))}
    {
        m_data = new char[static_cast<std::size_t>(m_length) + 1];
        std::copy_n(str, static_cast<std::size_t>(m_length) + 1, m_data);
    }

    // --- Rule of Three: 1. Destructor ---
    ~DeepString()
    {
        delete[] m_data;
    }

    // --- Rule of Three: 2. Copy Constructor (deep copy) ---
    DeepString(const DeepString &source)
        : m_length{source.m_length}
    {
        // Allocate NEW memory - don't share the source's pointer
        m_data = new char[static_cast<std::size_t>(m_length) + 1];
        std::copy_n(source.m_data, static_cast<std::size_t>(m_length) + 1, m_data);
    }

    // --- Rule of Three: 3. Copy Assignment Operator (deep copy) ---
    DeepString &operator=(const DeepString &source)
    {
        if (this == &source) // Self-assignment guard
            return *this;

        delete[] m_data; // Free old data

        m_length = source.m_length;
        m_data = new char[static_cast<std::size_t>(m_length) + 1];
        std::copy_n(source.m_data, static_cast<std::size_t>(m_length) + 1, m_data);

        return *this;
    }

    const char *getString() const { return m_data; }
    void setChar(int index, char ch) { m_data[index] = ch; }

    friend std::ostream &operator<<(std::ostream &out, const DeepString &s)
    {
        out << s.m_data;
        return out;
    }
};

int main()
{
    // ======================================================================
    // Demonstrating the SHALLOW COPY PROBLEM
    // (We'll describe the problem without actually causing a crash)
    // ======================================================================
    std::cout << "=== Shallow Copy Problem (Illustration) ===\n";
    std::cout << "If we had:\n";
    std::cout << "  ShallowString a{\"Hello\"};\n";
    std::cout << "  ShallowString b{a};  // Shallow copy - b.m_data == a.m_data!\n";
    std::cout << "Both a and b point to the SAME memory.\n";
    std::cout << "When b is destroyed, it deletes the shared memory.\n";
    std::cout << "Then a has a DANGLING POINTER. When a is destroyed → double-delete!\n\n";

    // Show that modification of one affects the other (shared pointer)
    {
        std::cout << "Demonstrating shared-pointer mutation:\n";
        ShallowString original{"Hello"};
        // We won't copy it to avoid double-delete, but the concept is:
        // If ShallowString copy{original};  then copy.m_data == original.m_data
        // Modifying one modifies both, because they share the memory.
    }

    // ======================================================================
    // Demonstrating DEEP COPY - the correct approach
    // ======================================================================
    std::cout << "\n=== Deep Copy (Correct) ===\n";
    DeepString str1{"Hello"};
    DeepString str2{str1}; // Deep copy constructor - allocates new memory

    std::cout << "str1 = " << str1 << '\n';
    std::cout << "str2 = " << str2 << " (deep copy of str1)\n";

    // Modifying str2 does NOT affect str1 - they have separate memory
    str2.setChar(0, 'J');
    std::cout << "\nAfter str2[0] = 'J':\n";
    std::cout << "str1 = " << str1 << " (unchanged!)\n";
    std::cout << "str2 = " << str2 << " (modified independently)\n";

    // Deep copy assignment
    DeepString str3{"World"};
    str3 = str1; // Deep copy assignment
    std::cout << "\nAfter str3 = str1:\n";
    std::cout << "str3 = " << str3 << " (independent deep copy)\n";

    str3.setChar(4, '!');
    std::cout << "After str3[4] = '!':\n";
    std::cout << "str1 = " << str1 << " (still unchanged)\n";
    std::cout << "str3 = " << str3 << '\n';

    // ======================================================================
    // Summary
    // ======================================================================
    std::cout << "\n=== Key Takeaways ===\n";
    std::cout << "1. Shallow copy: copies pointer addresses → shared memory → bugs\n";
    std::cout << "2. Deep copy: allocates new memory → each object owns its data\n";
    std::cout << "3. Rule of Three: custom destructor + copy ctor + copy assignment\n";
    std::cout << "4. Best practice: use std::string/std::vector instead of raw pointers\n";

    return 0;
}
