// Chapter 22 - Project 03: Move Constructor
// A move constructor transfers ownership of resources from a temporary
// (r-value) source object, avoiding an expensive deep copy.
//
// The pattern:
//   1. Shallow-copy the source's resource pointer into *this.
//   2. Null out the source's pointer so its destructor won't free the resource.
//   3. Mark the constructor noexcept - required for std::vector optimizations.

#include <iostream>
#include <cstring> // std::strlen, std::strcpy
#include <utility> // std::move

// -----------------------------------------------------------------------
// A simple string-like class that owns a heap-allocated char buffer.
// -----------------------------------------------------------------------
class MyString
{
    char *m_data{};
    std::size_t m_length{};

public:
    // Default constructor
    MyString() = default;

    // Parameterized constructor - deep allocates
    explicit MyString(const char *str)
        : m_length{std::strlen(str)}
    {
        m_data = new char[m_length + 1];
        std::strcpy(m_data, str);
        std::cout << "  [Constructed] \"" << m_data << "\"\n";
    }

    // ---------------------------------------------------------------
    // Copy constructor - deep copy (expensive)
    // ---------------------------------------------------------------
    MyString(const MyString &src)
        : m_length{src.m_length}
    {
        m_data = new char[m_length + 1];
        std::strcpy(m_data, src.m_data);
        std::cout << "  [Copy ctor]   \"" << m_data << "\" (deep copy)\n";
    }

    // ---------------------------------------------------------------
    // MOVE constructor - cheap transfer of ownership
    // ---------------------------------------------------------------
    MyString(MyString &&src) noexcept // <-- takes r-value ref
        : m_data{src.m_data}          // 1. Steal the pointer
          ,
          m_length{src.m_length}
    {
        src.m_data = nullptr; // 2. Null out source
        src.m_length = 0;
        std::cout << "  [Move ctor]   \"" << m_data << "\" (ownership transferred)\n";
    }

    // Destructor
    ~MyString()
    {
        if (m_data)
            std::cout << "  [Destroyed]   \"" << m_data << "\"\n";
        else
            std::cout << "  [Destroyed]   (empty / moved-from)\n";
        delete[] m_data;
    }

    // Accessors
    const char *c_str() const { return m_data ? m_data : ""; }
    std::size_t length() const { return m_length; }
    bool empty() const { return m_length == 0; }
};

// -----------------------------------------------------------------------
// A factory function that returns a MyString by value.
// The compiler may elide the copy/move (RVO), but conceptually
// a move constructor is allowed here.
// -----------------------------------------------------------------------
MyString createGreeting()
{
    MyString s("Hello from factory!");
    return s; // Eligible for NRVO / move
}

// -----------------------------------------------------------------------
int main()
{
    std::cout << "=== 1. Copy constructor ===\n";
    {
        MyString a("Alpha");
        MyString b(a); // Calls COPY ctor (a is an l-value)
        std::cout << "  a = \"" << a.c_str() << "\", b = \"" << b.c_str() << "\"\n";
    }

    std::cout << "\n=== 2. Move constructor (explicit std::move) ===\n";
    {
        MyString a("Beta");
        MyString b(std::move(a)); // Calls MOVE ctor (std::move casts a to r-value)
        std::cout << "  a empty? " << std::boolalpha << a.empty() << '\n';
        std::cout << "  b = \"" << b.c_str() << "\"\n";
    }

    std::cout << "\n=== 3. Move from temporary ===\n";
    {
        MyString c(MyString("Gamma")); // May be elided, but move ctor would apply
        std::cout << "  c = \"" << c.c_str() << "\"\n";
    }

    std::cout << "\n=== 4. Move from factory function ===\n";
    {
        MyString d = createGreeting(); // NRVO / move
        std::cout << "  d = \"" << d.c_str() << "\"\n";
    }

    std::cout << "\nDone.\n";
    return 0;
}
