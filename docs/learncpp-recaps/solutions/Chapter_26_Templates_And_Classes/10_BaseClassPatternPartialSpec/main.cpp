// Chapter 26 - Project 10: Base-Class Pattern to Avoid Code Duplication
// =======================================================================
// Problem: When you partially specialize a class, you must rewrite the
// ENTIRE class - even the parts that are identical to the primary template.
// This leads to duplicated code.
//
// Solution: Factor shared logic into a BASE class template, then have
// both the primary class and the partial specialization INHERIT from it.
// Only the differing parts (like print()) are overridden.
//
// Pattern:
//   1. StaticArrayBase<T, size>  - holds data and common operations
//   2. StaticArray<T, size>      - inherits base, adds generic print()
//   3. StaticArray<char, size>   - inherits base, adds char-specific print()

#include <iostream>

// ---------------------------------------------------------------------------
// Base class template - shared data and operations (NO print)
// ---------------------------------------------------------------------------
template <typename T, int size>
class StaticArrayBase
{
protected:
    T m_array[size]{};

public:
    T &operator[](int index) { return m_array[index]; }
    const T &operator[](int index) const { return m_array[index]; }

    constexpr int getLength() const { return size; }

    void fill(const T &value)
    {
        for (int i{0}; i < size; ++i)
            m_array[i] = value;
    }

    bool contains(const T &value) const
    {
        for (int i{0}; i < size; ++i)
        {
            if (m_array[i] == value)
                return true;
        }
        return false;
    }
};

// ---------------------------------------------------------------------------
// Primary class - inherits everything, adds space-separated print()
// ---------------------------------------------------------------------------
template <typename T, int size>
class StaticArray : public StaticArrayBase<T, size>
{
public:
    void print() const
    {
        for (int i{0}; i < size; ++i)
        {
            std::cout << this->m_array[i]; // 'this->' needed for dependent name
            if (i < size - 1)
                std::cout << ' ';
        }
        std::cout << '\n';
    }
};

// ---------------------------------------------------------------------------
// Partial specialization for char - inherits everything, adds string print()
// ---------------------------------------------------------------------------
template <int size>
class StaticArray<char, size> : public StaticArrayBase<char, size>
{
public:
    void print() const
    {
        // Print chars as a contiguous string (no spaces)
        for (int i{0}; i < size; ++i)
            std::cout << this->m_array[i];
        std::cout << '\n';
    }
};

// ---------------------------------------------------------------------------
int main()
{
    // --- int array (primary template) ---
    StaticArray<int, 5> intArr;
    for (int i{0}; i < 5; ++i)
        intArr[i] = (i + 1) * 10;

    std::cout << "int array:    ";
    intArr.print(); // 10 20 30 40 50

    // fill() and contains() come from the shared base class
    intArr.fill(0);
    std::cout << "after fill(0): ";
    intArr.print(); // 0 0 0 0 0

    std::cout << "contains(0)?  " << std::boolalpha
              << intArr.contains(0) << '\n'; // true
    std::cout << "contains(99)? "
              << intArr.contains(99) << '\n'; // false

    std::cout << '\n';

    // --- char array (partial specialization) ---
    StaticArray<char, 5> charArr;
    charArr[0] = 'H';
    charArr[1] = 'e';
    charArr[2] = 'l';
    charArr[3] = 'l';
    charArr[4] = 'o';

    std::cout << "char array:   ";
    charArr.print(); // Hello  (contiguous, no spaces)

    // fill() and contains() work identically - inherited from the same base
    std::cout << "contains('e')? " << charArr.contains('e') << '\n'; // true

    charArr.fill('*');
    std::cout << "after fill('*'): ";
    charArr.print(); // *****

    std::cout << '\n';

    // --- double array (primary template) ---
    StaticArray<double, 3> dblArr;
    dblArr[0] = 1.1;
    dblArr[1] = 2.2;
    dblArr[2] = 3.3;

    std::cout << "double array: ";
    dblArr.print(); // 1.1 2.2 3.3

    std::cout << "\nBenefit: fill(), contains(), operator[], getLength()\n"
              << "are written ONCE in the base class - no duplication!\n";

    return 0;
}
