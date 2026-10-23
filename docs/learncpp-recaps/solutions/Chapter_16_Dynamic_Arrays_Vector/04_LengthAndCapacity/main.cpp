// Chapter 16 - Project 04: Length and Capacity
// ==============================================
// Demonstrates the critical difference between length and capacity:
//   - Length  = number of elements currently in use
//   - Capacity = number of elements with allocated storage
//
// Also covers:
//   - size() and std::size() for unsigned length
//   - std::ssize() (C++20) for signed length
//   - size_type - the unsigned typedef used for lengths/indices
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <vector>
#include <cstddef> // for std::size_t, std::ptrdiff_t

int main()
{
    // --- 1. size() returns the length (number of elements in use) ---
    std::vector<int> v{10, 20, 30, 40, 50};

    std::cout << "=== Length and Capacity basics ===\n";
    std::cout << "v.size()     = " << v.size() << "  (elements in use)\n";
    std::cout << "v.capacity() = " << v.capacity() << "  (allocated storage)\n";
    // Initially, capacity >= size. The exact capacity is implementation-defined.

    // --- 2. size_type - the unsigned type returned by size() ---
    // std::vector<int>::size_type is typically std::size_t (unsigned)
    std::vector<int>::size_type len = v.size();
    std::cout << "\nsize_type len = " << len << '\n';

    // --- 3. std::size() - free function version (C++17) ---
    std::cout << "std::size(v)  = " << std::size(v) << "  (free function)\n";

    // --- 4. std::ssize() - signed size (C++20) ---
    // Returns std::ptrdiff_t - a signed type. Eliminates signed/unsigned mismatch.
    auto signedLen = std::ssize(v); // type: std::ptrdiff_t
    std::cout << "std::ssize(v) = " << signedLen << "  (signed, C++20)\n";

    // --- 5. Capacity grows automatically when elements are added ---
    std::cout << "\n=== Watching capacity grow ===\n";
    std::vector<int> growing;
    std::cout << "Empty: size=" << growing.size()
              << ", capacity=" << growing.capacity() << '\n';

    for (int i{1}; i <= 10; ++i)
    {
        growing.push_back(i);
        std::cout << "After push_back(" << i << "): size="
                  << growing.size() << ", capacity=" << growing.capacity() << '\n';
    }
    // Notice: capacity roughly doubles each time it needs to grow.
    // Reallocation (copying all elements) happens each time capacity increases.

    // --- 6. Valid indices are [0, size()-1], NOT [0, capacity()-1] ---
    std::cout << "\n=== Important ===\n";
    std::cout << "Valid index range: 0 to " << (v.size() - 1) << '\n';
    std::cout << "Accessing beyond size() is undefined behavior,\n";
    std::cout << "even if index < capacity()!\n";

    return 0;
}
