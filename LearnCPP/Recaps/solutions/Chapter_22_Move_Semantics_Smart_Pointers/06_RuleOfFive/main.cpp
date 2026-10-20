// Chapter 22 - Project 06: The Rule of Five
// If you define or delete ANY of these five special member functions,
// you should explicitly define or delete ALL five:
//
//   1. Destructor
//   2. Copy constructor
//   3. Copy assignment operator
//   4. Move constructor
//   5. Move assignment operator
//
// This ensures consistent, predictable behavior for resource-owning classes.

#include <iostream>
#include <cstring>
#include <utility>
#include <algorithm> // std::copy

// -----------------------------------------------------------------------
// A dynamic-array class that correctly implements all five.
// -----------------------------------------------------------------------
class DynArray
{
    int *m_data{};
    std::size_t m_size{};

    void log(const char *action) const
    {
        std::cout << "  [" << action << "] DynArray size=" << m_size
                  << " @" << m_data << '\n';
    }

public:
    // Constructor
    explicit DynArray(std::size_t size = 0)
        : m_data{size ? new int[size]{} : nullptr}, m_size{size}
    {
        log("Ctor");
    }

    // ---------------------------------------------------------------
    // 1. DESTRUCTOR
    // ---------------------------------------------------------------
    ~DynArray()
    {
        log("Dtor");
        delete[] m_data;
    }

    // ---------------------------------------------------------------
    // 2. COPY CONSTRUCTOR - deep copy
    // ---------------------------------------------------------------
    DynArray(const DynArray &src)
        : m_data{src.m_size ? new int[src.m_size] : nullptr}, m_size{src.m_size}
    {
        if (m_data)
            std::copy(src.m_data, src.m_data + m_size, m_data);
        log("Copy ctor");
    }

    // ---------------------------------------------------------------
    // 3. COPY ASSIGNMENT - deep copy with self-assignment check
    // ---------------------------------------------------------------
    DynArray &operator=(const DynArray &src)
    {
        if (this != &src)
        {
            delete[] m_data;

            m_size = src.m_size;
            m_data = m_size ? new int[m_size] : nullptr;
            if (m_data)
                std::copy(src.m_data, src.m_data + m_size, m_data);
        }
        log("Copy assign");
        return *this;
    }

    // ---------------------------------------------------------------
    // 4. MOVE CONSTRUCTOR - steal resources
    // ---------------------------------------------------------------
    DynArray(DynArray &&src) noexcept
        : m_data{src.m_data}, m_size{src.m_size}
    {
        src.m_data = nullptr;
        src.m_size = 0;
        log("Move ctor");
    }

    // ---------------------------------------------------------------
    // 5. MOVE ASSIGNMENT - free old, steal new
    // ---------------------------------------------------------------
    DynArray &operator=(DynArray &&src) noexcept
    {
        if (this != &src)
        {
            delete[] m_data;

            m_data = src.m_data;
            m_size = src.m_size;

            src.m_data = nullptr;
            src.m_size = 0;
        }
        log("Move assign");
        return *this;
    }

    // Accessors
    std::size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }

    int &operator[](std::size_t i) { return m_data[i]; }
    int operator[](std::size_t i) const { return m_data[i]; }

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
    std::cout << "=== 1. Construct ===\n";
    DynArray a(4);
    a[0] = 10;
    a[1] = 20;
    a[2] = 30;
    a[3] = 40;
    a.print();

    std::cout << "\n=== 2. Copy construct ===\n";
    DynArray b(a); // copy ctor
    b.print();

    std::cout << "\n=== 3. Copy assign ===\n";
    DynArray c(2);
    c = a; // copy assign
    c.print();

    std::cout << "\n=== 4. Move construct ===\n";
    DynArray d(std::move(a)); // move ctor - a is now empty
    d.print();
    std::cout << "  a.empty() = " << std::boolalpha << a.empty() << '\n';

    std::cout << "\n=== 5. Move assign ===\n";
    DynArray e(1);
    e = std::move(b); // move assign - b is now empty
    e.print();
    std::cout << "  b.empty() = " << std::boolalpha << b.empty() << '\n';

    std::cout << "\n=== Destructors follow ===\n";
    return 0;
}
