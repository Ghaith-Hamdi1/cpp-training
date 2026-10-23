// Chapter 26 - Project 7: Partial Template Specialization
// ==========================================================
// Partial specialization lets you fix SOME template parameters while
// keeping others generic. Only classes can be partially specialized -
// functions cannot.
//
// Example: StaticArray<T, size> is the primary template.
//          We partially specialize it for T = char (any size) to add
//          a custom print() that outputs the chars as a contiguous string.
//
// To partially specialize a member function, you must partially specialize
// the ENTIRE class - you can't partially specialize just one function.

#include <iostream>

// ---------------------------------------------------------------------------
// Primary template
// ---------------------------------------------------------------------------
template <typename T, int size>
class StaticArray
{
private:
    T m_array[size]{};

public:
    T &operator[](int index) { return m_array[index]; }
    const T &operator[](int index) const { return m_array[index]; }

    void print() const
    {
        // Generic print: separate elements with spaces
        for (int i{0}; i < size; ++i)
        {
            std::cout << m_array[i];
            if (i < size - 1)
                std::cout << ' ';
        }
        std::cout << '\n';
    }
};

// ---------------------------------------------------------------------------
// Partial specialization: T is fixed to char, size remains generic
// ---------------------------------------------------------------------------
// We fix T = char but keep 'size' as a template parameter.
// This specialization applies to StaticArray<char, N> for ANY N.
template <int size>           // only 'size' is still a parameter
class StaticArray<char, size> // T is fixed to char
{
private:
    char m_array[size]{};

public:
    char &operator[](int index) { return m_array[index]; }
    const char &operator[](int index) const { return m_array[index]; }

    void print() const
    {
        // Char-specific print: output as a contiguous string
        for (int i{0}; i < size; ++i)
            std::cout << m_array[i];
        std::cout << '\n';
    }
};

// ---------------------------------------------------------------------------
int main()
{
    // Uses the primary template - elements separated by spaces
    StaticArray<int, 4> intArr;
    intArr[0] = 10;
    intArr[1] = 20;
    intArr[2] = 30;
    intArr[3] = 40;

    std::cout << "StaticArray<int, 4>:  ";
    intArr.print(); // 10 20 30 40

    // Uses the partial specialization for char - printed as a string
    StaticArray<char, 6> charArr;
    charArr[0] = 'H';
    charArr[1] = 'e';
    charArr[2] = 'l';
    charArr[3] = 'l';
    charArr[4] = 'o';
    charArr[5] = '!';

    std::cout << "StaticArray<char, 6>: ";
    charArr.print(); // Hello!

    // Another char array with a different size - same partial specialization
    StaticArray<char, 3> tinyArr;
    tinyArr[0] = 'C';
    tinyArr[1] = '+';
    tinyArr[2] = '+';

    std::cout << "StaticArray<char, 3>: ";
    tinyArr.print(); // C++

    // Uses the primary template - double, spaces between elements
    StaticArray<double, 3> dblArr;
    dblArr[0] = 1.1;
    dblArr[1] = 2.2;
    dblArr[2] = 3.3;

    std::cout << "StaticArray<dbl, 3>:  ";
    dblArr.print(); // 1.1 2.2 3.3

    return 0;
}
