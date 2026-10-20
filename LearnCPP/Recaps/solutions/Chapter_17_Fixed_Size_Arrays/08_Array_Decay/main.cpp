// Chapter 17 - Project 08: C-style Array Decay
// Topics: decay to pointer, sizeof pitfalls, lost length info
// Compile: g++ -std=c++20 -Wall -Wextra -o program main.cpp

#include <iostream>
#include <iterator> // std::size

// -----------------------------------------------------------------------
// When a C-style array is passed to a function, it DECAYS to a pointer
// to its first element. The function receives a pointer, NOT an array.
// ALL length information is lost.
// -----------------------------------------------------------------------

// This function signature looks like it takes an array, but it actually
// receives a pointer (int*). The [5] is ignored by the compiler.
void printDecayed(int arr[], [[maybe_unused]] int length)
{
    // sizeof(arr) here gives the size of a POINTER (4 or 8 bytes)
    // NOT the size of the original array!
    std::cout << "sizeof(arr) inside function: " << sizeof(arr) << " bytes\n";
    std::cout << "(This is the pointer size, not the array size!)\n";

    // std::size(arr);  // Won't compile - arr is a pointer, not an array

    // We must rely on an explicitly passed length
    for (int i{0}; i < length; ++i)
        std::cout << arr[i] << ' ';
    std::cout << '\n';
}

// Same thing - int* is the actual type received
void printDecayed2(int *arr, int length)
{
    for (int i{0}; i < length; ++i)
        std::cout << arr[i] << ' ';
    std::cout << '\n';
}

int main()
{
    int data[5]{10, 20, 30, 40, 50};

    // -----------------------------------------------------------------------
    // 1. sizeof on the ACTUAL array (before decay) gives the full size
    // -----------------------------------------------------------------------
    std::cout << "--- 1. sizeof before decay ---\n";
    std::cout << "sizeof(data) in main: " << sizeof(data)
              << " bytes (" << sizeof(data) / sizeof(data[0]) << " elements)\n";
    std::cout << "std::size(data):      " << std::size(data) << '\n';

    // -----------------------------------------------------------------------
    // 2. Passing to function - array decays to pointer
    // -----------------------------------------------------------------------
    std::cout << "\n--- 2. After decay (inside function) ---\n";
    printDecayed(data, 5);

    // -----------------------------------------------------------------------
    // 3. Implicit conversion to pointer
    // -----------------------------------------------------------------------
    std::cout << "\n--- 3. Implicit decay to pointer ---\n";

    int *ptr{data};                                                // data decays to &data[0]
    std::cout << "ptr points to: " << *ptr << '\n';                // 10
    std::cout << "ptr == &data[0]: " << (ptr == &data[0]) << '\n'; // 1 (true)

    // -----------------------------------------------------------------------
    // 4. PITFALL: sizeof on a decayed pointer
    // -----------------------------------------------------------------------
    std::cout << "\n--- 4. sizeof pitfall ---\n";
    std::cout << "sizeof(ptr):  " << sizeof(ptr) << " bytes (pointer size)\n";
    std::cout << "sizeof(data): " << sizeof(data) << " bytes (full array size)\n";
    std::cout << "These are DIFFERENT!\n";

    // -----------------------------------------------------------------------
    // 5. Demonstrating that both function signatures receive a pointer
    // -----------------------------------------------------------------------
    std::cout << "\n--- 5. Both signatures are the same ---\n";
    printDecayed2(data, 5); // data decays, matches int* parameter

    // -----------------------------------------------------------------------
    // 6. Why this matters - std::array does NOT decay
    // -----------------------------------------------------------------------
    std::cout << "\n--- 6. std::array does NOT decay ---\n";
    std::cout << "std::array preserves its type and length when passed to functions.\n";
    std::cout << "Use std::array or std::vector to avoid decay bugs.\n";

    // -----------------------------------------------------------------------
    // KEY TAKEAWAY:
    //   C-style arrays silently decay to pointers in most contexts,
    //   losing all length information. sizeof() and std::size() become
    //   unreliable. Always pass the length separately, or better yet,
    //   use std::array / std::vector.
    // -----------------------------------------------------------------------

    return 0;
}
