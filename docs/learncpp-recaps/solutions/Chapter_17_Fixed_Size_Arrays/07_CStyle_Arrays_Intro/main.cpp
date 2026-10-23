// Chapter 17 - Project 07: Introduction to C-style Arrays
// Topics: declaration, initialization, limitations, no assignment
// Compile: g++ -std=c++20 -Wall -Wextra -o program main.cpp

#include <iostream>
#include <iterator> // std::size, std::ssize (C++17/20)

int main()
{
    // -----------------------------------------------------------------------
    // 1. Declaration - uses bracket syntax: type name[length]
    //    Length MUST be a compile-time constant expression.
    // -----------------------------------------------------------------------
    std::cout << "--- 1. Declaration ---\n";

    int nums[5]{}; // value-initialized: all zeros
    for (int n : nums)
        std::cout << n << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 2. Aggregate initialization - same as std::array
    // -----------------------------------------------------------------------
    std::cout << "\n--- 2. Aggregate init ---\n";

    int primes[5]{2, 3, 5, 7, 11};
    for (int p : primes)
        std::cout << p << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 3. Partial initialization - remaining elements are zero
    // -----------------------------------------------------------------------
    std::cout << "\n--- 3. Partial init ---\n";

    int partial[5]{10, 20}; // {10, 20, 0, 0, 0}
    for (int v : partial)
        std::cout << v << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 4. Omitting the length - compiler deduces it from the initializer
    // -----------------------------------------------------------------------
    std::cout << "\n--- 4. Omit length ---\n";

    int deduced[]{100, 200, 300}; // length = 3
    std::cout << "Length: " << std::size(deduced) << '\n';
    for (int d : deduced)
        std::cout << d << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 5. Getting the length
    //    std::size()  (C++17) - returns std::size_t (unsigned)
    //    std::ssize() (C++20) - returns signed type
    //    sizeof trick: sizeof(arr) / sizeof(arr[0]) - old C idiom
    // -----------------------------------------------------------------------
    std::cout << "\n--- 5. Length queries ---\n";
    std::cout << "std::size(primes)  = " << std::size(primes) << '\n';
    std::cout << "std::ssize(primes) = " << std::ssize(primes) << '\n';
    std::cout << "sizeof trick       = " << sizeof(primes) / sizeof(primes[0]) << '\n';

    // -----------------------------------------------------------------------
    // 6. Indexing - both signed and unsigned indices are accepted
    // -----------------------------------------------------------------------
    std::cout << "\n--- 6. Indexing ---\n";
    std::cout << "primes[0] = " << primes[0] << '\n';
    std::cout << "primes[4] = " << primes[4] << '\n';

    // -----------------------------------------------------------------------
    // 7. PITFALL: C-style arrays do NOT support assignment after declaration
    //    int a[3] = {1,2,3};
    //    a = {4,5,6};        // ERROR: won't compile
    //
    //    You must assign element-by-element or use std::copy.
    // -----------------------------------------------------------------------
    std::cout << "\n--- 7. No assignment (element-by-element only) ---\n";

    int arr[3]{1, 2, 3};
    // arr = {4, 5, 6};  // ERROR
    arr[0] = 4;
    arr[1] = 5;
    arr[2] = 6; // OK
    for (int v : arr)
        std::cout << v << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 8. PITFALL: length must be a constant expression
    //    int n = 5;
    //    int vla[n];  // Not valid standard C++ (some compilers allow as extension)
    //
    //    Use constexpr or a literal for the length.
    // -----------------------------------------------------------------------
    constexpr int len{4};
    int fixed[len]{1, 2, 3, 4}; // OK - len is constexpr
    for (int v : fixed)
        std::cout << v << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // KEY TAKEAWAY:
    //   C-style arrays are built into the language (no #include needed).
    //   They lack safety features - no bounds checking, no assignment,
    //   and they decay to pointers when passed to functions.
    //   Prefer std::array or std::vector in modern C++.
    // -----------------------------------------------------------------------

    return 0;
}
