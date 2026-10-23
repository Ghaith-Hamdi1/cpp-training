// Chapter 18 - Project 4: Introduction to Iterators
// ====================================================
// An iterator is an object that abstracts traversal of a container.
//   - operator* (dereference) - access the current element
//   - operator++ (advance) - move to the next element
//   - operator!= - compare against another iterator (use != not <)
//
// Key ideas:
//   - Pointers are the simplest form of iterators
//   - Containers provide begin() and end() member functions
//   - Free functions std::begin() / std::end() work with C-arrays too
//   - Range-based for-loops work by using iterators behind the scenes
//   - Always compare iterators with != (not <), since not all iterator
//     types support relational operators

#include <array>
#include <iostream>
#include <vector>

int main()
{
    // --- 1) Pointer as an iterator over a C-array ---
    int arr[]{10, 20, 30, 40, 50};

    std::cout << "=== Pointer iterator over C-array ===\n";
    // std::begin and std::end work with C-arrays
    for (auto it{std::begin(arr)}; it != std::end(arr); ++it)
    {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    // --- 2) Using iterators with std::vector ---
    std::vector<int> vec{1, 2, 3, 4, 5};

    std::cout << "\n=== std::vector iterator ===\n";
    for (auto it{vec.begin()}; it != vec.end(); ++it)
    {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    // --- 3) Using iterators with std::array ---
    std::array<double, 4> stdArr{1.1, 2.2, 3.3, 4.4};

    std::cout << "\n=== std::array iterator ===\n";
    for (auto it{stdArr.begin()}; it != stdArr.end(); ++it)
    {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    // --- 4) Range-based for uses iterators internally ---
    // The compiler translates:
    //     for (auto elem : vec) { ... }
    // Into something like:
    //     auto __begin = vec.begin();
    //     auto __end   = vec.end();
    //     for (; __begin != __end; ++__begin) { auto elem = *__begin; ... }

    std::cout << "\n=== Range-based for (uses iterators internally) ===\n";
    for (int val : vec)
    {
        std::cout << val << ' ';
    }
    std::cout << '\n';

    // --- 5) Reverse iterators ---
    std::cout << "\n=== Reverse iterators ===\n";
    for (auto rit{vec.rbegin()}; rit != vec.rend(); ++rit)
    {
        std::cout << *rit << ' ';
    }
    std::cout << '\n';

    // --- 6) Const iterators - read-only access ---
    std::cout << "\n=== Const iterators (cbegin / cend) ===\n";
    for (auto cit{vec.cbegin()}; cit != vec.cend(); ++cit)
    {
        std::cout << *cit << ' ';
        // *cit = 99; // ERROR: can't modify through a const_iterator
    }
    std::cout << '\n';

    // --- 7) Why use != instead of < ---
    // Some iterators (e.g., for std::list, std::set) are bidirectional
    // or forward iterators that do NOT support operator<.
    // Using != works universally with all iterator categories.
    std::cout << "\n=== Always use != to compare iterators ===\n";
    std::cout << "  it != end()  -->  correct (works with all iterators)\n";
    std::cout << "  it <  end()  -->  only works with random-access iterators\n";

    return 0;
}
