// ============================================================================
// Chapter 19 - Project 02: Dynamically Allocating Arrays
// ============================================================================
// Demonstrates new[] and delete[] for allocating arrays whose size is
// determined at runtime.
//
// Key points:
//   - Use 'new type[size]' to allocate a dynamic array.
//   - Use 'delete[]' (NOT 'delete') to free it - mismatching is UB.
//   - Dynamic arrays have no built-in size tracking.
//   - Since C++11, dynamic arrays can use initializer lists.
//   - C++ has no built-in array resizing - prefer std::vector.
// ============================================================================

#include <iostream>

int main()
{
    // -----------------------------------------------------------------
    // 1. Basic dynamic array allocation
    // -----------------------------------------------------------------
    std::cout << "How many scores to enter? ";
    int count{};
    std::cin >> count;

    // Allocate array of 'count' ints on the heap
    // Value-initialized to 0 with empty braces
    int *scores{new int[count]{}};

    // Fill the array
    for (int i{0}; i < count; ++i)
    {
        std::cout << "  Score " << (i + 1) << ": ";
        std::cin >> scores[i];
    }

    // Print them back
    std::cout << "\nYou entered:\n";
    for (int i{0}; i < count; ++i)
        std::cout << "  scores[" << i << "] = " << scores[i] << '\n';

    // Free the dynamic array - MUST use delete[] (not delete)
    delete[] scores;
    scores = nullptr;

    // -----------------------------------------------------------------
    // 2. Initializer list with new[] (C++11)
    // -----------------------------------------------------------------
    // You can initialize a dynamic array with a brace-enclosed list.
    int *primes{new int[5]{2, 3, 5, 7, 11}};

    std::cout << "\nFirst 5 primes (dynamic array):\n";
    for (int i{0}; i < 5; ++i)
        std::cout << "  " << primes[i] << '\n';

    delete[] primes;
    primes = nullptr;

    // -----------------------------------------------------------------
    // 3. Dynamic array of doubles
    // -----------------------------------------------------------------
    constexpr int size{4};
    double *temperatures{new double[size]{72.5, 68.3, 75.1, 80.0}};

    double sum{0.0};
    for (int i{0}; i < size; ++i)
        sum += temperatures[i];

    std::cout << "\nAverage temperature: " << (sum / size) << '\n';

    delete[] temperatures;
    temperatures = nullptr;

    // -----------------------------------------------------------------
    // 4. Why std::vector is preferred
    // -----------------------------------------------------------------
    // Dynamic arrays don't track their own size, can't be resized,
    // and require manual delete[]. std::vector handles all of this.
    // (We demonstrate vector elsewhere - this project focuses on raw arrays.)

    std::cout << "\nAll dynamic arrays properly deallocated.\n";
    return 0;
}
