// Chapter 23 - Project 10: Common Pitfalls
// ===========================================
//
// This project demonstrates three common pitfalls related to
// object relationships and container classes:
//
//   1. Shallow copying: Without proper deep-copy, copying a container
//      with dynamic memory creates dangling pointers and UB.
//
//   2. {} vs () after adding an initializer_list constructor:
//      Adding a list constructor can silently change existing code
//      behavior - MyClass{5} calls the list ctor, not the int ctor.
//
//   3. Forgetting self-assignment check in operator=:
//      Without it, `a = a` deletes data before copying, causing UB.

#include <iostream>
#include <string>

// ================================================================
// PITFALL 1: Shallow Copy
// ================================================================
// This class deliberately omits deep-copy to show what goes wrong.
class BrokenArray
{
private:
    int *m_data{};
    int m_length{};

public:
    BrokenArray(int length)
        : m_data{new int[static_cast<std::size_t>(length)]{}}, m_length{length}
    {
    }

    ~BrokenArray()
    {
        delete[] m_data;
    }

    // No copy constructor or assignment operator defined!
    // The compiler generates shallow copies (copies the pointer, not the data).

    int &operator[](int index) { return m_data[index]; }
    int getLength() const { return m_length; }

    void print(std::string_view label) const
    {
        std::cout << label << ": [ ";
        for (int i{0}; i < m_length; ++i)
        {
            std::cout << m_data[i];
            if (i < m_length - 1)
                std::cout << ", ";
        }
        std::cout << " ]\n";
    }
};

void demonstrateShallowCopyProblem()
{
    std::cout << "=== PITFALL 1: Shallow Copy ===\n\n";

    std::cout << "BrokenArray has no deep-copy constructor.\n";
    std::cout << "If we copy it, both copies share the same pointer.\n";
    std::cout << "When the first is destroyed, the second has a dangling pointer.\n";
    std::cout << "(We demonstrate the concept without triggering actual UB.)\n\n";

    // SAFE demonstration: show the concept without actual UB
    // We create one array and explain what WOULD happen if copied.
    BrokenArray original(3);
    original[0] = 10;
    original[1] = 20;
    original[2] = 30;
    original.print("original");

    std::cout << "\n// BrokenArray copy = original;  // <-- DON'T DO THIS!\n";
    std::cout << "// Shallow copy: copy.m_data == original.m_data (same pointer!)\n";
    std::cout << "// When 'original' is destroyed, copy.m_data is dangling.\n";
    std::cout << "// Accessing copy[0] after that = UNDEFINED BEHAVIOR.\n";
    std::cout << "// Both destructors will delete[] the same memory = DOUBLE FREE.\n\n";

    std::cout << "FIX: Always implement a deep-copy constructor and assignment\n";
    std::cout << "operator for classes with dynamically allocated memory.\n";
}

// ================================================================
// PITFALL 2: {} vs () with initializer_list constructor
// ================================================================
class Widget
{
private:
    int m_size{};
    int *m_data{};

public:
    // Constructor 1: create widget of given size
    explicit Widget(int size)
        : m_size{size}, m_data{new int[static_cast<std::size_t>(size)]{}}
    {
        std::cout << "  Widget(int) called - created widget of size " << size << '\n';
    }

    // Constructor 2: initializer_list
    Widget(std::initializer_list<int> list)
        : m_size{static_cast<int>(list.size())}, m_data{new int[list.size()]}
    {
        std::cout << "  Widget(initializer_list) called - " << m_size << " elements: { ";
        int i{0};
        for (int val : list)
        {
            m_data[i++] = val;
            std::cout << val;
            if (i < m_size)
                std::cout << ", ";
        }
        std::cout << " }\n";
    }

    ~Widget() { delete[] m_data; }

    Widget(const Widget &) = delete;
    Widget &operator=(const Widget &) = delete;
};

void demonstrateBracesVsParens()
{
    std::cout << "=== PITFALL 2: {} vs () with initializer_list ===\n\n";

    std::cout << "Widget w1(5);   // Calls Widget(int) - size 5\n";
    Widget w1(5);

    std::cout << "\nWidget w2{5};   // Calls Widget(initializer_list) - one element: 5\n";
    Widget w2{5};

    std::cout << "\nWidget w3{1, 2, 3}; // Calls Widget(initializer_list) - three elements\n";
    Widget w3{1, 2, 3};

    std::cout << "\nDANGER: If you originally had Widget w{5} (calling the int ctor)\n";
    std::cout << "and then added an initializer_list constructor, the meaning of\n";
    std::cout << "Widget w{5} SILENTLY CHANGES. This is a frequent source of bugs!\n";
    std::cout << "\nFIX: Use () when you want the non-list constructor.\n";
}

// ================================================================
// PITFALL 3: Self-Assignment in operator=
// ================================================================
class SafeArray
{
private:
    int *m_data{};
    int m_length{};

public:
    SafeArray(int length)
        : m_data{new int[static_cast<std::size_t>(length)]{}}, m_length{length}
    {
    }

    SafeArray(const SafeArray &other)
        : m_data{new int[static_cast<std::size_t>(other.m_length)]}, m_length{other.m_length}
    {
        for (int i{0}; i < m_length; ++i)
            m_data[i] = other.m_data[i];
    }

    ~SafeArray() { delete[] m_data; }

    // CORRECT: has self-assignment check
    SafeArray &operator=(const SafeArray &other)
    {
        // Without this check, `a = a` would:
        // 1. delete[] m_data   (destroys our own data!)
        // 2. Try to copy from other.m_data (which is the same, now deleted!)
        // Result: Undefined Behavior
        if (this == &other)
        {
            std::cout << "  Self-assignment detected - skipping.\n";
            return *this;
        }

        delete[] m_data;
        m_length = other.m_length;
        m_data = new int[static_cast<std::size_t>(m_length)];
        for (int i{0}; i < m_length; ++i)
            m_data[i] = other.m_data[i];

        return *this;
    }

    int &operator[](int index) { return m_data[index]; }
    int getLength() const { return m_length; }

    void print() const
    {
        std::cout << "  [ ";
        for (int i{0}; i < m_length; ++i)
        {
            std::cout << m_data[i];
            if (i < m_length - 1)
                std::cout << ", ";
        }
        std::cout << " ]\n";
    }
};

void demonstrateSelfAssignment()
{
    std::cout << "=== PITFALL 3: Self-Assignment Check ===\n\n";

    SafeArray arr(3);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    std::cout << "Before self-assignment:\n";
    arr.print();

    std::cout << "\narr = arr; // Self-assignment\n";
    arr = arr;

    std::cout << "\nAfter self-assignment (data is preserved):\n";
    arr.print();

    std::cout << "\nWithout the self-assignment check, this would be UB -\n";
    std::cout << "the data would be deleted before being copied.\n";
}

int main()
{
    demonstrateShallowCopyProblem();
    std::cout << "\n"
              << std::string(60, '=') << "\n\n";

    demonstrateBracesVsParens();
    std::cout << "\n"
              << std::string(60, '=') << "\n\n";

    demonstrateSelfAssignment();

    return 0;
}
