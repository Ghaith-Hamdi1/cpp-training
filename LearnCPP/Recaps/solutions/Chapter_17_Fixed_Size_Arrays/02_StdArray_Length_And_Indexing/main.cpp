// Chapter 17 - Project 02: std::array Length and Indexing
// Topics: size(), std::size(), ssize(), operator[], at(), std::get<>()
// Compile: g++ -std=c++20 -Wall -Wextra -o program main.cpp

#include <array>
#include <iostream>
#include <cstddef> // std::size_t, std::ptrdiff_t

int main()
{
    constexpr std::array data{10, 20, 30, 40, 50};

    // -----------------------------------------------------------------------
    // 1. Getting the length
    //    .size()        - member function, returns std::size_t (unsigned)
    //    std::size()    - free function (C++17), also returns std::size_t
    //    std::ssize()   - free function (C++20), returns signed type
    // -----------------------------------------------------------------------
    std::cout << "--- 1. Length queries ---\n";
    std::cout << "data.size()      = " << data.size() << '\n';
    std::cout << "std::size(data)  = " << std::size(data) << '\n';
    std::cout << "std::ssize(data) = " << std::ssize(data) << '\n';

    // All return constexpr values, so they work in static_assert
    static_assert(data.size() == 5);

    // -----------------------------------------------------------------------
    // 2. operator[] - fast, NO bounds checking (UB if out of range)
    // -----------------------------------------------------------------------
    std::cout << "\n--- 2. operator[] ---\n";
    std::cout << "data[0] = " << data[0] << '\n';
    std::cout << "data[4] = " << data[4] << '\n';
    // data[5] - undefined behavior! No error, no exception, just UB.

    // -----------------------------------------------------------------------
    // 3. at() - runtime bounds checking, throws std::out_of_range
    // -----------------------------------------------------------------------
    std::cout << "\n--- 3. at() with bounds check ---\n";
    std::cout << "data.at(2) = " << data.at(2) << '\n';

    try
    {
        [[maybe_unused]] int bad = data.at(99); // throws
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Caught out_of_range: " << e.what() << '\n';
    }

    // -----------------------------------------------------------------------
    // 4. std::get<>() - compile-time bounds check (index must be constexpr)
    //    Preferred when the index is a compile-time constant.
    // -----------------------------------------------------------------------
    std::cout << "\n--- 4. std::get<>() ---\n";
    std::cout << "std::get<0>(data) = " << std::get<0>(data) << '\n';
    std::cout << "std::get<4>(data) = " << std::get<4>(data) << '\n';
    // std::get<5>(data); // Compile error - index out of range

    // -----------------------------------------------------------------------
    // 5. Iterating with index using signed loop variable (best practice)
    // -----------------------------------------------------------------------
    std::cout << "\n--- 5. Index-based loop (signed) ---\n";
    for (auto i{0}; i < std::ssize(data); ++i)
        std::cout << "data[" << i << "] = " << data[static_cast<std::size_t>(i)] << '\n';

    // -----------------------------------------------------------------------
    // KEY TAKEAWAY:
    //   Prefer std::get<>() when the index is constexpr.
    //   Use at() when you need runtime safety.
    //   Use ssize() for signed-length comparisons.
    // -----------------------------------------------------------------------

    return 0;
}
