// Chapter 18 - Project 10: Common Pitfalls
// ==========================================
// This file demonstrates all major pitfalls from the chapter, each
// clearly labeled with the WRONG way (commented out) and the RIGHT way.

#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    // =========================================================
    // PITFALL 1: Off-by-one in selection sort outer loop
    // =========================================================
    // The outer loop should stop at (length - 1), not length.
    // When only one element remains unsorted, it's already in place.
    std::cout << "=== Pitfall 1: Off-by-one in sorting loops ===\n";

    std::vector<int> arr{5, 3, 1, 4, 2};
    int length{static_cast<int>(arr.size())};

    // WRONG: for (int i = 0; i < length; ++i)     // wastes one iteration
    // RIGHT: for (int i = 0; i < length - 1; ++i) // correct
    for (int i{0}; i < length - 1; ++i)
    {
        int smallest{i};
        for (int j{i + 1}; j < length; ++j)
        {
            if (arr[j] < arr[smallest])
                smallest = j;
        }
        std::swap(arr[i], arr[smallest]);
    }

    std::cout << "Sorted: ";
    for (int v : arr)
        std::cout << v << ' ';
    std::cout << "\n\n";

    // =========================================================
    // PITFALL 2: Benchmarking in debug mode
    // =========================================================
    std::cout << "=== Pitfall 2: Benchmarking in debug mode ===\n";
    std::cout << "Debug builds disable optimizations, making results\n";
    std::cout << "misleadingly slow (sometimes 30x+ slower).\n";
    std::cout << "ALWAYS benchmark with Release/optimized builds:\n";
    std::cout << "  MSVC:  cl /O2 main.cpp\n";
    std::cout << "  GCC:   g++ -O2 main.cpp\n\n";

    // =========================================================
    // PITFALL 3: Forgetting & in range-based for-loop
    // =========================================================
    std::cout << "=== Pitfall 3: Missing & in range-based for ===\n";

    std::vector<int> values{1, 2, 3};

    // WRONG: auto val (copies, doesn't modify the vector)
    for (auto val : values)
        val *= 10; // Modifies the copy, not the vector!

    std::cout << "After 'auto val' (bug - unchanged): ";
    for (int v : values)
        std::cout << v << ' ';
    std::cout << '\n';

    // RIGHT: auto& val (reference, modifies the vector)
    for (auto &val : values)
        val *= 10;

    std::cout << "After 'auto& val' (correct - modified): ";
    for (int v : values)
        std::cout << v << ' ';
    std::cout << "\n\n";

    // =========================================================
    // PITFALL 4: Accessing one-past-the-end element
    // =========================================================
    std::cout << "=== Pitfall 4: Accessing one-past-the-end ===\n";

    int cArr[]{10, 20, 30};

    // WRONG: cArr[std::size(cArr)]  - undefined behavior!
    // This accesses the element AFTER the last one.
    // std::cout << cArr[std::size(cArr)]; // UB!

    // RIGHT: Use pointer arithmetic for the one-past-the-end address
    // (but never dereference it!)
    int *pastEnd = cArr + std::size(cArr); // Valid pointer, but don't dereference
    std::cout << "One-past-the-end pointer is valid for comparison, not dereferencing.\n";
    std::cout << "cArr + size(cArr) == end iterator:  "
              << (pastEnd == std::end(cArr) ? "true" : "false") << "\n\n";

    // =========================================================
    // PITFALL 5: Using operator< with iterators
    // =========================================================
    std::cout << "=== Pitfall 5: Using < instead of != with iterators ===\n";

    std::vector<int> vec{1, 2, 3, 4, 5};

    // WRONG (may not compile for non-random-access iterators):
    // for (auto it = container.begin(); it < container.end(); ++it) { ... }

    // RIGHT (works with ALL iterator categories):
    std::cout << "Using != : ";
    for (auto it{vec.begin()}; it != vec.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';

    std::cout << "Note: operator< only works with random-access iterators.\n";
    std::cout << "      operator!= works with ALL iterator types.\n\n";

    // =========================================================
    // PITFALL 6: Assuming execution order for all algorithms
    // =========================================================
    std::cout << "=== Pitfall 6: Assuming execution order ===\n";
    std::cout << "Only some algorithms guarantee sequential order:\n";
    std::cout << "  - std::for_each:  YES, guaranteed sequential\n";
    std::cout << "  - std::copy:      YES, guaranteed sequential\n";
    std::cout << "  - std::sort:      NO, may process in any order\n";
    std::cout << "  - std::transform: NO specific order guaranteed\n";
    std::cout << "Use std::for_each when order matters.\n\n";

    // =========================================================
    // Summary
    // =========================================================
    std::cout << "=== Summary of Best Practices ===\n";
    std::cout << "1. Use != (not <) to compare iterators\n";
    std::cout << "2. Use auto& (not auto) when modifying in range-for\n";
    std::cout << "3. Never access arr[std::size(arr)] - it's UB\n";
    std::cout << "4. Never modify a container while iterating over it\n";
    std::cout << "5. Benchmark in Release mode, not Debug\n";
    std::cout << "6. Prefer std::sort over hand-written sorts\n";
    std::cout << "7. Use C++20 ranges for cleaner algorithm calls\n";

    return 0;
}
