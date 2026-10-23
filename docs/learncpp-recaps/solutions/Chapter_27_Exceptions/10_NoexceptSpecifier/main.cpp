// Chapter 27 - Project 10: noexcept Specifier and Operator
// ==========================================================
// noexcept specifier:
//   - Marks a function as non-throwing
//   - If an exception escapes a noexcept function, std::terminate is called
//     (the stack may NOT be unwound - implementation-defined)
//   - Enables compiler optimizations (no need for unwinding tables)
//
// noexcept operator:
//   - Compile-time check: noexcept(expr) returns true if expr can't throw
//   - Used in templates and conditional noexcept: noexcept(noexcept(expr))
//
// What to mark noexcept:
//   - Move constructors, move assignment operators, swap functions
//   - Destructors (implicitly noexcept already)
//   - Simple getters, trivial operations that clearly can't throw

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

// --- A function marked noexcept ---
int add(int a, int b) noexcept
{
    return a + b; // clearly can't throw
}

// --- Conditional noexcept ---
// This function is noexcept only if T's copy constructor is noexcept
template <typename T>
T duplicate(const T &value) noexcept(std::is_nothrow_copy_constructible_v<T>)
{
    return value;
}

// --- A well-designed class with noexcept move operations ---
class Buffer
{
    int *m_data{};
    std::size_t m_size{};

public:
    Buffer() = default;

    explicit Buffer(std::size_t size)
        : m_data{new int[size]{}}, m_size{size}
    {
        std::cout << "  Buffer(" << m_size << ") constructed\n";
    }

    // Destructor is implicitly noexcept
    ~Buffer()
    {
        delete[] m_data;
        if (m_size > 0)
            std::cout << "  Buffer(" << m_size << ") destroyed\n";
    }

    // Copy constructor (may throw - allocates memory)
    Buffer(const Buffer &other)
        : m_data{new int[other.m_size]}, m_size{other.m_size}
    {
        std::copy(other.m_data, other.m_data + m_size, m_data);
        std::cout << "  Buffer(" << m_size << ") copied\n";
    }

    // Move constructor - marked noexcept! This is critical.
    // Without noexcept, std::vector won't use move during reallocation.
    Buffer(Buffer &&other) noexcept
        : m_data{other.m_data}, m_size{other.m_size}
    {
        other.m_data = nullptr;
        other.m_size = 0;
        std::cout << "  Buffer moved\n";
    }

    // Move assignment - also noexcept
    Buffer &operator=(Buffer &&other) noexcept
    {
        if (this != &other)
        {
            delete[] m_data;
            m_data = other.m_data;
            m_size = other.m_size;
            other.m_data = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    // Swap - noexcept
    friend void swap(Buffer &a, Buffer &b) noexcept
    {
        std::swap(a.m_data, b.m_data);
        std::swap(a.m_size, b.m_size);
    }

    std::size_t size() const noexcept { return m_size; }
};

int main()
{
    // --- noexcept operator: compile-time check ---
    std::cout << "=== noexcept operator (compile-time checks) ===\n";
    std::cout << std::boolalpha;
    std::cout << "add(1,2) is noexcept: " << noexcept(add(1, 2)) << '\n';
    std::cout << "duplicate(42) is noexcept: " << noexcept(duplicate(42)) << '\n';

    // std::string copy may throw (allocates memory), so duplicate<string> is not noexcept
    std::string s{"hello"};
    std::cout << "duplicate(string) is noexcept: " << noexcept(duplicate(s)) << '\n';

    // --- noexcept move constructor enables std::vector optimization ---
    std::cout << "\n=== noexcept move constructor with std::vector ===\n";
    std::cout << "Because Buffer's move constructor is noexcept,\n";
    std::cout << "std::vector will MOVE (not copy) during reallocation:\n\n";

    std::vector<Buffer> buffers;
    buffers.reserve(2); // room for 2

    buffers.emplace_back(100);
    buffers.emplace_back(200);
    std::cout << "\n-- Adding 3rd element triggers reallocation --\n";
    buffers.emplace_back(300); // reallocation: existing elements are MOVED (not copied)

    // --- Check traits ---
    std::cout << "\n=== Type traits for Buffer ===\n";
    std::cout << "is_nothrow_move_constructible: "
              << std::is_nothrow_move_constructible_v<Buffer> << '\n';
    std::cout << "is_nothrow_move_assignable: "
              << std::is_nothrow_move_assignable_v<Buffer> << '\n';
    std::cout << "is_nothrow_destructible: "
              << std::is_nothrow_destructible_v<Buffer> << '\n';

    // Note: if a noexcept function DOES throw, std::terminate is called.
    // We won't demonstrate that here because it kills the program!
    std::cout << "\n(If a noexcept function throws, std::terminate is called.)\n";

    return 0;
}
