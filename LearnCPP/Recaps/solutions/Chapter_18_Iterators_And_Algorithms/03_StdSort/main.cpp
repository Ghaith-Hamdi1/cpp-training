// Chapter 18 - Project 3: std::sort
// ====================================
// std::sort (from <algorithm>) is the standard library's highly optimized
// sorting function. It typically uses introsort (quicksort + heapsort +
// insertion sort hybrid) and is vastly faster than hand-written sorts.
//
// Key ideas:
//   - Default: sorts in ascending order using operator<
//   - Custom comparator: pass a callable (function, lambda, or functor)
//   - std::greater{}: built-in functor for descending order
//   - Works with any random-access iterators (arrays, vectors, deques)

#include <algorithm>  // std::sort
#include <functional> // std::greater
#include <iostream>
#include <string>
#include <vector>

void printVector(const std::string &label, const std::vector<int> &v)
{
    std::cout << label;
    for (int val : v)
        std::cout << val << ' ';
    std::cout << '\n';
}

int main()
{
    // --- 1) Default ascending sort ---
    std::vector<int> nums{30, 10, 50, 20, 40};
    printVector("Original:   ", nums);

    std::sort(nums.begin(), nums.end());
    printVector("Ascending:  ", nums);

    // --- 2) Descending sort with std::greater ---
    std::sort(nums.begin(), nums.end(), std::greater{});
    printVector("Descending: ", nums);

    // --- 3) Custom comparator: sort by absolute distance from 30 ---
    std::vector<int> vals{5, 35, 28, 50, 31, 10, 29};
    printVector("\nOriginal:        ", vals);

    std::sort(vals.begin(), vals.end(),
              [](int a, int b)
              {
                  // Sort by distance from 30 (ascending)
                  return std::abs(a - 30) < std::abs(b - 30);
              });
    printVector("Closest to 30:   ", vals);

    // --- 4) Sorting strings ---
    std::vector<std::string> names{"Charlie", "Alice", "Eve", "Bob", "Dave"};

    std::cout << "\nNames before: ";
    for (const auto &n : names)
        std::cout << n << ' ';
    std::cout << '\n';

    std::sort(names.begin(), names.end()); // Lexicographic ascending
    std::cout << "Names after:  ";
    for (const auto &n : names)
        std::cout << n << ' ';
    std::cout << '\n';

    // --- 5) Partial sort of a C-style array ---
    int arr[]{9, 1, 7, 3, 5};
    std::sort(std::begin(arr), std::end(arr));

    std::cout << "\nSorted C-array: ";
    for (int val : arr)
        std::cout << val << ' ';
    std::cout << '\n';

    return 0;
}
