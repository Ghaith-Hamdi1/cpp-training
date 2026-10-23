// Chapter 17 - Project 03: Passing and Returning std::array
// Topics: pass by const ref, function templates, returning arrays
// Compile: g++ -std=c++20 -Wall -Wextra -o program main.cpp

#include <array>
#include <iostream>
#include <cstddef> // std::size_t

// -----------------------------------------------------------------------
// 1. Passing by const reference (specific type + length)
//    Problem: this only works for std::array<int, 4>
// -----------------------------------------------------------------------
void printFixed(const std::array<int, 4> &arr)
{
    for (int v : arr)
        std::cout << v << ' ';
    std::cout << '\n';
}

// -----------------------------------------------------------------------
// 2. Function template - works for ANY element type and ANY length
//    This is the preferred approach for generic array functions.
// -----------------------------------------------------------------------
template <typename T, std::size_t N>
void printArray(const std::array<T, N> &arr)
{
    std::cout << "[ ";
    for (const auto &elem : arr)
        std::cout << elem << ' ';
    std::cout << "] (size=" << N << ")\n";
}

// -----------------------------------------------------------------------
// 3. Returning std::array by value
//    NOTE: std::array is NOT move-capable - this always copies.
//    For small arrays this is fine; for large arrays, consider an
//    out parameter or use std::vector instead.
// -----------------------------------------------------------------------
template <std::size_t N>
std::array<int, N> makeSequence()
{
    std::array<int, N> result{};
    for (std::size_t i{0}; i < N; ++i)
        result[i] = static_cast<int>(i + 1);
    return result;
}

// -----------------------------------------------------------------------
// 4. Using an "out parameter" to avoid the copy
// -----------------------------------------------------------------------
template <typename T, std::size_t N>
void fillWithValue(std::array<T, N> &arr, T value)
{
    for (auto &elem : arr)
        elem = value;
}

int main()
{
    // --- 1. Passing a specific array ---
    std::cout << "--- 1. Pass specific type ---\n";
    std::array<int, 4> a{1, 2, 3, 4};
    printFixed(a);

    // --- 2. Generic template function ---
    std::cout << "\n--- 2. Generic template ---\n";
    std::array<double, 3> dArr{1.1, 2.2, 3.3};
    std::array<int, 6> iArr{10, 20, 30, 40, 50, 60};
    printArray(dArr); // deduces T=double, N=3
    printArray(iArr); // deduces T=int,    N=6

    // --- 3. Returning by value ---
    std::cout << "\n--- 3. Return by value ---\n";
    auto seq = makeSequence<5>(); // returns std::array<int, 5>{1,2,3,4,5}
    printArray(seq);

    // --- 4. Out parameter ---
    std::cout << "\n--- 4. Out parameter ---\n";
    std::array<int, 4> filled{};
    fillWithValue(filled, 42);
    printArray(filled);

    // -----------------------------------------------------------------------
    // KEY TAKEAWAY:
    //   Pass std::array by const& to avoid copies.
    //   Use function templates (T, N) for generic array functions.
    //   Returning by value is OK for small arrays; beware copies for large ones.
    // -----------------------------------------------------------------------

    return 0;
}
