// Chapter 23 - Project 09: std::initializer_list
// ==================================================
//
// std::initializer_list<T> (from <initializer_list>) lets custom
// classes accept brace-enclosed initializer lists: { 1, 2, 3 }.
//
// Key points:
//   - std::initializer_list is lightweight - pass by value.
//   - Elements are accessed via iterators or range-for.
//   - List initialization PREFERS list constructors over non-list ones.
//   - If you provide a list constructor, also provide a list assignment
//     operator to avoid shallow-copy bugs.
//   - Use () for direct init when you want the non-list constructor,
//     and {} when you want the list constructor.

#include <cassert>
#include <initializer_list>
#include <iostream>

class IntArray
{
private:
    int *m_data{};
    int m_length{};

public:
    // Regular constructor: creates array of a given size
    explicit IntArray(int length)
        : m_data{new int[static_cast<std::size_t>(length)]{}}, m_length{length}
    {
        std::cout << "[int constructor] Created array of size " << length << '\n';
    }

    // List constructor: accepts { 1, 2, 3, ... }
    IntArray(std::initializer_list<int> list)
        : m_data{new int[list.size()]}, m_length{static_cast<int>(list.size())}
    {
        std::cout << "[initializer_list constructor] Created array with "
                  << m_length << " elements\n";

        int index{0};
        for (int val : list)
            m_data[index++] = val;
    }

    // Deep-copy constructor
    IntArray(const IntArray &other)
        : m_data{new int[static_cast<std::size_t>(other.m_length)]}, m_length{other.m_length}
    {
        for (int i{0}; i < m_length; ++i)
            m_data[i] = other.m_data[i];
    }

    ~IntArray()
    {
        delete[] m_data;
    }

    // List assignment operator - IMPORTANT when you have a list constructor!
    // Without this, assigning an initializer_list would create a temporary
    // IntArray via the list constructor, then shallow-copy it via the
    // default copy assignment - leading to dangling pointers.
    IntArray &operator=(std::initializer_list<int> list)
    {
        std::cout << "[initializer_list operator=] Assigning " << list.size()
                  << " elements\n";

        delete[] m_data;

        m_length = static_cast<int>(list.size());
        m_data = new int[list.size()];

        int index{0};
        for (int val : list)
            m_data[index++] = val;

        return *this;
    }

    // Deep-copy assignment for IntArray-to-IntArray assignment
    IntArray &operator=(const IntArray &other)
    {
        if (this == &other)
            return *this;

        delete[] m_data;
        m_length = other.m_length;
        m_data = new int[static_cast<std::size_t>(m_length)];
        for (int i{0}; i < m_length; ++i)
            m_data[i] = other.m_data[i];

        return *this;
    }

    int &operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    int getLength() const { return m_length; }

    void print() const
    {
        std::cout << "  -> [ ";
        for (int i{0}; i < m_length; ++i)
        {
            std::cout << m_data[i];
            if (i < m_length - 1)
                std::cout << ", ";
        }
        std::cout << " ]\n";
    }
};

int main()
{
    std::cout << "=== std::initializer_list ===\n\n";

    // Using the list constructor
    std::cout << "IntArray a{ 10, 20, 30, 40, 50 };\n";
    IntArray a{10, 20, 30, 40, 50};
    a.print();

    // Using the int constructor (direct initialization with parentheses)
    std::cout << "\nIntArray b(5);  // int constructor, NOT list\n";
    IntArray b(5);
    b.print();

    // CRITICAL DISTINCTION: {} vs ()
    // IntArray{5} calls the LIST constructor (one element: 5)
    // IntArray(5) calls the INT constructor (array of size 5)
    std::cout << "\n--- {} vs () distinction ---\n";

    std::cout << "IntArray c{5};  // list constructor: one element of value 5\n";
    IntArray c{5};
    c.print();

    std::cout << "\nIntArray d(5);  // int constructor: array of size 5\n";
    IntArray d(5);
    d.print();

    // List assignment operator
    std::cout << "\n--- List assignment ---\n";
    std::cout << "d = { 100, 200, 300 };\n";
    d = {100, 200, 300};
    d.print();

    return 0;
}
