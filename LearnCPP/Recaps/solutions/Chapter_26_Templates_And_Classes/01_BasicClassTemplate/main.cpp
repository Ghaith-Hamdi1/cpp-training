// Chapter 26 - Project 1: Basic Class Template
// ================================================
// Demonstrates how to define a template class so that a single class
// definition works for any element type (int, double, std::string, …).
//
// Key ideas:
//   - `template <typename T>` before the class makes T a placeholder type.
//   - The compiler generates ("instantiates") a concrete class only when
//     you actually use it with a specific type, e.g. Array<int>.
//   - Template class code should live in headers so every translation unit
//     that uses it can see the full definition.

#include <cassert>
#include <iostream>
#include <string>

// ---------------------------------------------------------------------------
// A simple dynamic-array template class with member functions defined
// INSIDE the class body (the simplest approach).
// ---------------------------------------------------------------------------
template <typename T>
class Array
{
private:
    int m_length{};
    T* m_data{};

public:
    // Constructor - allocates storage for 'length' elements
    Array(int length) : m_length{ length }
    {
        assert(length > 0 && "Array length must be positive");
        m_data = new T[length]{};      // value-initialise every element
    }

    // Destructor - frees the dynamically allocated array
    ~Array()
    {
        delete[] m_data;
    }

    // Disable copy to keep this example simple (rule of three)
    Array(const Array&)            = delete;
    Array& operator=(const Array&) = delete;

    // Element access (with bounds checking)
    T& operator[](int index)
    {
        assert(index >= 0 && index < m_length && "Index out of bounds");
        return m_data[index];
    }

    const T& operator[](int index) const
    {
        assert(index >= 0 && index < m_length && "Index out of bounds");
        return m_data[index];
    }

    int getLength() const { return m_length; }

    // Print all elements
    void print() const
    {
        for (int i{ 0 }; i < m_length; ++i)
        {
            std::cout << m_data[i];
            if (i < m_length - 1)
                std::cout << ", ";
        }
        std::cout << '\n';
    }
};

// ---------------------------------------------------------------------------
int main()
{
    // The compiler generates Array<int> here
    Array<int> intArr(5);
    for (int i{ 0 }; i < intArr.getLength(); ++i)
        intArr[i] = (i + 1) * 10;

    std::cout << "int array:    ";
    intArr.print();   // 10, 20, 30, 40, 50

    // The compiler generates Array<double> here
    Array<double> dblArr(3);
    dblArr[0] = 1.1;
    dblArr[1] = 2.2;
    dblArr[2] = 3.3;

    std::cout << "double array: ";
    dblArr.print();   // 1.1, 2.2, 3.3

    // The compiler generates Array<std::string> here
    Array<std::string> strArr(3);
    strArr[0] = "Hello";
    strArr[1] = "Template";
    strArr[2] = "World";

    std::cout << "string array: ";
    strArr.print();   // Hello, Template, World

    // NOTE: If we never use Array<float>, the compiler never generates it.
    // Templates are only instantiated on demand.

    return 0;
}
