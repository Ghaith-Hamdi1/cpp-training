// Chapter 22 - Project 04: Move Assignment Operator
// The move assignment operator transfers resources from an r-value
// source into an already-existing object, freeing any resource the
// destination previously held.
//
// Key differences from move constructor:
//   - The destination object already exists and may own a resource.
//   - Must free the destination's OLD resource before stealing the source's.
//   - Must handle self-assignment (a = std::move(a)).
//   - Should be marked noexcept.

#include <iostream>
#include <cstring>
#include <utility>

class Buffer
{
    int *m_data{};
    std::size_t m_size{};

public:
    // Parameterized constructor
    explicit Buffer(std::size_t size)
        : m_data{new int[size]{}}, m_size{size}
    {
        std::cout << "  [Constructed] Buffer of size " << m_size << '\n';
    }

    // Copy constructor (deep copy)
    Buffer(const Buffer &src)
        : m_data{new int[src.m_size]}, m_size{src.m_size}
    {
        std::memcpy(m_data, src.m_data, m_size * sizeof(int));
        std::cout << "  [Copy ctor]   Buffer of size " << m_size << '\n';
    }

    // Move constructor
    Buffer(Buffer &&src) noexcept
        : m_data{src.m_data}, m_size{src.m_size}
    {
        src.m_data = nullptr;
        src.m_size = 0;
        std::cout << "  [Move ctor]   Buffer of size " << m_size << '\n';
    }

    // -------------------------------------------------------------------
    // Copy assignment (deep copy)
    // -------------------------------------------------------------------
    Buffer &operator=(const Buffer &src)
    {
        std::cout << "  [Copy assign] ";
        if (this == &src) // Self-assignment check
            return *this;

        delete[] m_data; // Free old resource

        m_size = src.m_size;
        m_data = new int[m_size];
        std::memcpy(m_data, src.m_data, m_size * sizeof(int));

        std::cout << "Buffer of size " << m_size << '\n';
        return *this;
    }

    // -------------------------------------------------------------------
    // MOVE assignment operator
    // -------------------------------------------------------------------
    Buffer &operator=(Buffer &&src) noexcept
    {
        std::cout << "  [Move assign] ";

        // 1. Self-assignment guard (rare but possible: a = std::move(a))
        if (this == &src)
            return *this;

        // 2. Free destination's existing resource
        delete[] m_data;

        // 3. Steal from source
        m_data = src.m_data;
        m_size = src.m_size;

        // 4. Leave source in a valid empty state
        src.m_data = nullptr;
        src.m_size = 0;

        std::cout << "Buffer of size " << m_size << '\n';
        return *this;
    }

    // Destructor
    ~Buffer()
    {
        std::cout << "  [Destroyed]   Buffer of size " << m_size
                  << (m_data ? "" : " (empty)") << '\n';
        delete[] m_data;
    }

    // Utility
    std::size_t size() const { return m_size; }

    void fill(int value)
    {
        for (std::size_t i = 0; i < m_size; ++i)
            m_data[i] = value;
    }

    void print() const
    {
        std::cout << "  [";
        for (std::size_t i = 0; i < m_size; ++i)
        {
            if (i)
                std::cout << ", ";
            std::cout << m_data[i];
        }
        std::cout << "]\n";
    }
};

// -----------------------------------------------------------------------
int main()
{
    std::cout << "=== 1. Copy assignment ===\n";
    {
        Buffer a(3);
        a.fill(1);
        Buffer b(5);
        b.fill(9);

        std::cout << "  Before copy assign:\n";
        std::cout << "  a: ";
        a.print();
        std::cout << "  b: ";
        b.print();

        b = a; // Copy assignment - a is an l-value

        std::cout << "  After copy assign:\n";
        std::cout << "  a: ";
        a.print();
        std::cout << "  b: ";
        b.print();
    }

    std::cout << "\n=== 2. Move assignment ===\n";
    {
        Buffer a(3);
        a.fill(7);
        Buffer b(5);
        b.fill(2);

        std::cout << "  Before move assign:\n";
        std::cout << "  a: ";
        a.print();
        std::cout << "  b: ";
        b.print();

        b = std::move(a); // Move assignment - std::move casts a to r-value

        std::cout << "  After move assign:\n";
        std::cout << "  a size = " << a.size() << " (moved-from)\n";
        std::cout << "  b: ";
        b.print();
    }

    std::cout << "\n=== 3. Move from temporary ===\n";
    {
        Buffer c(2);
        c.fill(0);
        c = Buffer(4); // Temporary (r-value) triggers move assignment
        std::cout << "  c size = " << c.size() << '\n';
    }

    std::cout << "\nDone.\n";
    return 0;
}
