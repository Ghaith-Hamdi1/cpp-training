// Chapter 26 - Project 3: Non-Type Template Parameters
// ======================================================
// A template parameter can be a constexpr VALUE, not just a type.
// This enables compile-time-sized arrays that live on the stack -
// exactly the pattern used by std::array.
//
// Key rules:
//   - The non-type argument must be constexpr (compile-time constant).
//   - Passing a runtime variable is a compile error.
//   - Each distinct value creates a separate class instantiation:
//     StaticArray<int,5> and StaticArray<int,10> are completely
//     different types (you can't assign one to the other).

#include <iostream>

// ---------------------------------------------------------------------------
// StaticArray<T, size>  -  stack-allocated fixed-size array
// T    = element type          (type parameter)
// size = number of elements    (non-type parameter, must be constexpr)
// ---------------------------------------------------------------------------
template <typename T, int size>
class StaticArray
{
private:
    T m_array[size]{}; // array size is known at compile time

public:
    T &operator[](int index)
    {
        return m_array[index];
    }

    const T &operator[](int index) const
    {
        return m_array[index];
    }

    // Return the compile-time size
    constexpr int getLength() const { return size; }

    void print() const
    {
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
int main()
{
    // size = 5, known at compile time
    StaticArray<int, 5> intArr;
    for (int i{0}; i < intArr.getLength(); ++i)
        intArr[i] = (i + 1) * 100;

    std::cout << "StaticArray<int, 5>:    ";
    intArr.print(); // 100 200 300 400 500

    // size = 3, a completely different type from the one above
    StaticArray<double, 3> dblArr;
    dblArr[0] = 1.5;
    dblArr[1] = 2.5;
    dblArr[2] = 3.5;

    std::cout << "StaticArray<double, 3>: ";
    dblArr.print(); // 1.5 2.5 3.5

    // Using constexpr variable as the non-type argument - valid
    constexpr int len{4};
    StaticArray<char, len> charArr;
    charArr[0] = 'A';
    charArr[1] = 'B';
    charArr[2] = 'C';
    charArr[3] = 'D';

    std::cout << "StaticArray<char, 4>:   ";
    charArr.print(); // A B C D

    // PITFALL (commented out - would not compile):
    //
    //   int runtimeLen{ 10 };
    //   StaticArray<int, runtimeLen> bad;   // ERROR: runtimeLen is not constexpr
    //
    // Non-type template arguments MUST be compile-time constants.

    return 0;
}
