// Chapter 16 - Project 07: Arrays and Index-Based Loops
// ======================================================
// Demonstrates:
//   - Traversing vectors with index-based for loops
//   - Common tasks: search, sum, min/max, transform
//   - Off-by-one errors: index < size(), NOT index <= size()
//   - The signed/unsigned indexing problem and workarounds
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <vector>
#include <cstddef> // std::size_t

int main()
{
    std::vector<int> data{42, 17, 93, 56, 8, 74, 31};

    // --- 1. Basic traversal with index ---
    std::cout << "=== Basic index-based traversal ===\n";
    for (std::size_t i{0}; i < data.size(); ++i)
        std::cout << "data[" << i << "] = " << data[i] << '\n';

    // --- 2. Summing elements ---
    std::cout << "\n=== Summing elements ===\n";
    int sum{0};
    for (std::size_t i{0}; i < data.size(); ++i)
        sum += data[i];
    std::cout << "Sum = " << sum << '\n';

    // --- 3. Finding the maximum element ---
    std::cout << "\n=== Finding max ===\n";
    int maxVal{data[0]};
    for (std::size_t i{1}; i < data.size(); ++i)
    {
        if (data[i] > maxVal)
            maxVal = data[i];
    }
    std::cout << "Max = " << maxVal << '\n';

    // --- 4. Searching for an element ---
    std::cout << "\n=== Searching for value 56 ===\n";
    bool found{false};
    for (std::size_t i{0}; i < data.size(); ++i)
    {
        if (data[i] == 56)
        {
            std::cout << "Found 56 at index " << i << '\n';
            found = true;
            break;
        }
    }
    if (!found)
        std::cout << "56 not found\n";

    // --- 5. OFF-BY-ONE ERROR PITFALL ---
    std::cout << "\n=== Off-by-one pitfall ===\n";
    std::cout << "CORRECT: for (i = 0; i < size(); ++i)   - last index = size()-1\n";
    std::cout << "WRONG:   for (i = 0; i <= size(); ++i)  - accesses one past the end!\n";
    std::cout << "The last valid index is size()-1 = " << (data.size() - 1) << '\n';

    // --- 6. Signed indexing with std::ssize() (C++20) ---
    std::cout << "\n=== Using std::ssize() for signed indexing (C++20) ===\n";
    for (auto i{0}; i < std::ssize(data); ++i) // i is int, ssize returns ptrdiff_t
        std::cout << "data[" << i << "] = " << data[static_cast<std::size_t>(i)] << '\n';

    // --- 7. PITFALL: Reverse loop with unsigned index ---
    std::cout << "\n=== Pitfall: reverse loop with unsigned index ===\n";
    std::cout << "// DANGEROUS - i wraps to huge value when it goes below 0:\n";
    std::cout << "// for (std::size_t i = v.size()-1; i >= 0; --i)  // INFINITE LOOP!\n";
    std::cout << "// Because std::size_t is unsigned, i >= 0 is ALWAYS true.\n\n";

    // Safe reverse loop using signed index:
    std::cout << "Safe reverse loop (signed index):\n";
    for (auto i{std::ssize(data) - 1}; i >= 0; --i)
        std::cout << "data[" << i << "] = " << data[static_cast<std::size_t>(i)] << '\n';

    return 0;
}
