// Chapter 16 - Project 03: Subscript Operator and Bounds Checking
// ================================================================
// Demonstrates:
//   - operator[] for fast, unchecked element access (zero-based)
//   - at() for bounds-checked access (throws std::out_of_range)
//   - Why out-of-bounds access with [] is undefined behavior
//
// Key takeaway: operator[] does NO bounds checking.
//   Out-of-bounds access silently causes UB. Use at() when
//   you need safety, or prefer range-based for loops.
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <vector>
#include <stdexcept> // for std::out_of_range

int main()
{
    std::vector scores{85, 92, 78, 95, 88};

    // --- 1. Normal access with operator[] (zero-based) ---
    std::cout << "=== operator[] access ===\n";
    std::cout << "scores[0] = " << scores[0] << '\n'; // 85  (first element)
    std::cout << "scores[4] = " << scores[4] << '\n'; // 88  (last element)
    // scores[5] would be UNDEFINED BEHAVIOR - no error, no exception, just UB!

    // --- 2. Modifying elements via operator[] ---
    scores[2] = 100; // change 78 → 100
    std::cout << "\nAfter scores[2] = 100:\n";
    std::cout << "scores[2] = " << scores[2] << '\n';

    // --- 3. Bounds-checked access with at() ---
    std::cout << "\n=== at() with bounds checking ===\n";
    std::cout << "scores.at(0) = " << scores.at(0) << '\n';
    std::cout << "scores.at(4) = " << scores.at(4) << '\n';

    // --- 4. at() throws std::out_of_range on invalid index ---
    std::cout << "\n=== Attempting scores.at(10) ===\n";
    try
    {
        int val = scores.at(10); // index 10 is way out of bounds
        std::cout << "This won't print: " << val << '\n';
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Caught exception: " << e.what() << '\n';
        std::cout << "at() correctly detected an out-of-bounds index!\n";
    }

    // --- 5. Why operator[] is preferred for performance ---
    // at() has a small overhead because it checks bounds every call.
    // In performance-critical loops where you know the index is valid,
    // operator[] is faster. But at() is safer during development/debugging.
    std::cout << "\n=== Summary ===\n";
    std::cout << "operator[]: fast, no bounds check, UB if out of range\n";
    std::cout << "at():       slower, bounds check, throws on error\n";
    std::cout << "Best practice: use range-based for loops to avoid both issues!\n";

    return 0;
}
