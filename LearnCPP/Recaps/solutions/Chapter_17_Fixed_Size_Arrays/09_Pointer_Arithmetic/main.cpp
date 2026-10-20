// Chapter 17 - Project 09: Pointer Arithmetic and Subscripting
// Topics: ptr[n] == *(ptr+n), whole-object movement, pointer iteration
// Compile: g++ -std=c++20 -Wall -Wextra -o program main.cpp

#include <iostream>
#include <iterator> // std::begin, std::end

int main()
{
    int data[]{10, 20, 30, 40, 50};

    // -----------------------------------------------------------------------
    // 1. Pointer arithmetic moves by WHOLE OBJECTS, not bytes
    //    If ptr points to an int (4 bytes), ptr+1 moves 4 bytes forward
    //    to point to the next int in memory.
    // -----------------------------------------------------------------------
    std::cout << "--- 1. Pointer arithmetic ---\n";

    int *ptr{data};                                   // points to data[0]
    std::cout << "ptr     -> " << *ptr << '\n';       // 10
    std::cout << "ptr + 1 -> " << *(ptr + 1) << '\n'; // 20
    std::cout << "ptr + 2 -> " << *(ptr + 2) << '\n'; // 30
    std::cout << "ptr + 4 -> " << *(ptr + 4) << '\n'; // 50

    // -----------------------------------------------------------------------
    // 2. Subscript operator equivalence:  ptr[n] == *(ptr + n)
    //    This is why arrays are 0-based: arr[0] == *(arr + 0) == *arr
    // -----------------------------------------------------------------------
    std::cout << "\n--- 2. ptr[n] == *(ptr + n) ---\n";

    for (int i{0}; i < 5; ++i)
    {
        std::cout << "ptr[" << i << "] = " << ptr[i]
                  << "   *(ptr+" << i << ") = " << *(ptr + i) << '\n';
    }

    // -----------------------------------------------------------------------
    // 3. Increment / decrement operators
    // -----------------------------------------------------------------------
    std::cout << "\n--- 3. ++ptr and --ptr ---\n";

    int *p{data};
    std::cout << "*p   = " << *p << '\n'; // 10
    ++p;
    std::cout << "++p  => *p = " << *p << '\n'; // 20
    ++p;
    std::cout << "++p  => *p = " << *p << '\n'; // 30
    --p;
    std::cout << "--p  => *p = " << *p << '\n'; // 20

    // -----------------------------------------------------------------------
    // 4. Pointer difference - subtracting two pointers gives the number
    //    of elements between them (not bytes).
    // -----------------------------------------------------------------------
    std::cout << "\n--- 4. Pointer difference ---\n";

    int *first{&data[0]};
    int *last{&data[4]};
    std::cout << "last - first = " << (last - first) << " elements\n"; // 4

    // -----------------------------------------------------------------------
    // 5. Pointer-based iteration (begin/end pattern)
    //    This is what range-based for loops do under the hood.
    // -----------------------------------------------------------------------
    std::cout << "\n--- 5. Pointer iteration ---\n";

    // Manual begin/end
    for (int *it{data}; it != data + 5; ++it)
        std::cout << *it << ' ';
    std::cout << '\n';

    // Using std::begin / std::end (safer, no hardcoded length)
    for (int *it{std::begin(data)}; it != std::end(data); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 6. Why zero-based indexing?
    //    arr[i] == *(arr + i)
    //    The first element has offset 0 from the start => arr[0]
    //    This falls naturally out of pointer arithmetic.
    // -----------------------------------------------------------------------
    std::cout << "\n--- 6. Zero-based indexing rationale ---\n";
    std::cout << "arr[0] == *(arr + 0) == *arr  (no offset = first element)\n";

    // -----------------------------------------------------------------------
    // 7. Negative indices (valid only when pointer doesn't point to element 0)
    // -----------------------------------------------------------------------
    std::cout << "\n--- 7. Negative indexing ---\n";

    int *mid{&data[2]};                           // points to 30
    std::cout << "mid[-1] = " << mid[-1] << '\n'; // 20
    std::cout << "mid[-2] = " << mid[-2] << '\n'; // 10
    std::cout << "mid[0]  = " << mid[0] << '\n';  // 30
    std::cout << "mid[1]  = " << mid[1] << '\n';  // 40

    // -----------------------------------------------------------------------
    // KEY TAKEAWAY:
    //   ptr[n] is syntactic sugar for *(ptr + n).
    //   Pointer arithmetic moves by whole objects, not bytes.
    //   This is the foundation of array indexing and iteration in C/C++.
    // -----------------------------------------------------------------------

    return 0;
}
