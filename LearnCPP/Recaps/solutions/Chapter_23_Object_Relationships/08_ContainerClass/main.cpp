// Chapter 23 - Project 08: Container Class (IntArray)
// =====================================================
//
// A container class holds and organizes multiple instances of another type.
//   - Value container (composition): stores copies of elements.
//   - Reference container (aggregation): stores pointers/references.
//
// This example builds a VALUE container (IntArray) with:
//   - Dynamic allocation (new/delete)
//   - Deep-copy constructor and assignment operator
//   - Self-assignment check in operator=
//   - Insert, remove, and resize operations
//
// Best practice: Prefer std::vector over writing your own container,
// but understanding how containers work internally is valuable.

#include <cassert>
#include <iostream>

class IntArray
{
private:
    int *m_data{};
    int m_length{};

public:
    // Default constructor
    IntArray() = default;

    // Constructor: allocate array of given size
    explicit IntArray(int length)
        : m_data{new int[static_cast<std::size_t>(length)]{}}, m_length{length}
    {
    }

    // Deep-copy constructor - prevents shallow copy bugs
    IntArray(const IntArray &other)
        : m_data{new int[static_cast<std::size_t>(other.m_length)]}, m_length{other.m_length}
    {
        for (int i{0}; i < m_length; ++i)
            m_data[i] = other.m_data[i];
    }

    // Destructor - free dynamically allocated memory
    ~IntArray()
    {
        delete[] m_data;
    }

    // Deep-copy assignment operator with self-assignment check
    IntArray &operator=(const IntArray &other)
    {
        // Self-assignment guard - critical for correctness!
        // Without this, we'd delete our own data before copying.
        if (this == &other)
            return *this;

        // Deallocate old data
        delete[] m_data;

        // Deep copy
        m_length = other.m_length;
        if (m_length > 0)
        {
            m_data = new int[static_cast<std::size_t>(m_length)];
            for (int i{0}; i < m_length; ++i)
                m_data[i] = other.m_data[i];
        }
        else
        {
            m_data = nullptr;
        }

        return *this;
    }

    // Element access with bounds checking
    int &operator[](int index)
    {
        assert(index >= 0 && index < m_length && "Index out of bounds");
        return m_data[index];
    }

    const int &operator[](int index) const
    {
        assert(index >= 0 && index < m_length && "Index out of bounds");
        return m_data[index];
    }

    int getLength() const { return m_length; }

    // Insert a value before the element at the given index
    void insertBefore(int value, int index)
    {
        assert(index >= 0 && index <= m_length && "Insert index out of bounds");

        int *newData{new int[static_cast<std::size_t>(m_length + 1)]};

        // Copy elements before index
        for (int i{0}; i < index; ++i)
            newData[i] = m_data[i];

        // Insert new value
        newData[index] = value;

        // Copy elements after index
        for (int i{index}; i < m_length; ++i)
            newData[i + 1] = m_data[i];

        delete[] m_data;
        m_data = newData;
        ++m_length;
    }

    // Remove the element at the given index
    void remove(int index)
    {
        assert(index >= 0 && index < m_length && "Remove index out of bounds");

        if (m_length == 1)
        {
            delete[] m_data;
            m_data = nullptr;
            m_length = 0;
            return;
        }

        int *newData{new int[static_cast<std::size_t>(m_length - 1)]};

        for (int i{0}; i < index; ++i)
            newData[i] = m_data[i];

        for (int i{index + 1}; i < m_length; ++i)
            newData[i - 1] = m_data[i];

        delete[] m_data;
        m_data = newData;
        --m_length;
    }

    // Print all elements
    void print() const
    {
        std::cout << "[ ";
        for (int i{0}; i < m_length; ++i)
        {
            std::cout << m_data[i];
            if (i < m_length - 1)
                std::cout << ", ";
        }
        std::cout << " ] (length: " << m_length << ")\n";
    }
};

int main()
{
    std::cout << "=== Container Class: IntArray ===\n\n";

    // Create and populate
    IntArray arr(5);
    for (int i{0}; i < arr.getLength(); ++i)
        arr[i] = (i + 1) * 10;

    std::cout << "Original: ";
    arr.print();

    // Insert
    arr.insertBefore(25, 2); // Insert 25 before index 2
    std::cout << "After insert 25 at index 2: ";
    arr.print();

    // Remove
    arr.remove(0); // Remove first element
    std::cout << "After remove index 0: ";
    arr.print();

    // Deep copy constructor
    IntArray copy{arr};
    copy[0] = 999;
    std::cout << "\nDeep copy (modified): ";
    copy.print();
    std::cout << "Original (unchanged): ";
    arr.print();

    // Deep copy assignment
    IntArray assigned;
    assigned = arr;
    assigned[1] = 777;
    std::cout << "\nAssigned copy (modified): ";
    assigned.print();
    std::cout << "Original (unchanged): ";
    arr.print();

    // Self-assignment (should be a no-op)
    arr = arr;
    std::cout << "\nAfter self-assignment: ";
    arr.print();

    return 0;
}
