// Chapter 18 - Project 8: C++20 Ranges
// =======================================
// C++20 ranges let you pass containers directly to algorithms,
// removing the boilerplate of begin()/end() pairs.
//
// Instead of:   std::sort(vec.begin(), vec.end());
// You write:    std::ranges::sort(vec);
//
// Ranges live in the <algorithm> and <ranges> headers under the
// std::ranges namespace. They work with any range (container, view,
// or anything with begin() and end()).
//
// Compile with C++20: /std:c++20 (MSVC) or -std=c++20 (GCC/Clang)

#include <algorithm>  // std::ranges::sort, find, count, for_each, etc.
#include <functional> // std::greater
#include <iostream>
#include <string>
#include <vector>

void printVec(const std::string &label, const std::vector<int> &v)
{
    std::cout << label;
    for (int val : v)
        std::cout << val << ' ';
    std::cout << '\n';
}

int main()
{
    // --- 1) std::ranges::sort - pass the container directly ---
    std::cout << "=== std::ranges::sort ===\n";

    std::vector<int> nums{50, 10, 40, 20, 30};
    printVec("Before: ", nums);

    std::ranges::sort(nums); // Ascending (default)
    printVec("Ascending:  ", nums);

    std::ranges::sort(nums, std::greater{}); // Descending
    printVec("Descending: ", nums);

    // --- 2) std::ranges::find ---
    std::cout << "\n=== std::ranges::find ===\n";

    auto it{std::ranges::find(nums, 30)};
    if (it != nums.end())
        std::cout << "Found 30\n";

    // --- 3) std::ranges::find_if ---
    std::cout << "\n=== std::ranges::find_if ===\n";

    auto gt35{std::ranges::find_if(nums, [](int n)
                                   { return n > 35; })};
    if (gt35 != nums.end())
        std::cout << "First element > 35: " << *gt35 << '\n';

    // --- 4) std::ranges::count / count_if ---
    std::cout << "\n=== std::ranges::count / count_if ===\n";

    std::vector<int> data{1, 2, 3, 2, 4, 2, 5};
    auto twos{std::ranges::count(data, 2)};
    std::cout << "Count of 2: " << twos << '\n';

    auto evens{std::ranges::count_if(data, [](int n)
                                     { return n % 2 == 0; })};
    std::cout << "Count of evens: " << evens << '\n';

    // --- 5) std::ranges::for_each ---
    std::cout << "\n=== std::ranges::for_each ===\n";
    std::cout << "Doubled: ";
    std::ranges::for_each(data, [](int &n)
                          { n *= 2; });
    for (int val : data)
        std::cout << val << ' ';
    std::cout << '\n';

    // --- 6) Comparison: traditional vs ranges ---
    std::cout << "\n=== Side-by-side comparison ===\n";

    std::vector<int> v{5, 3, 1, 4, 2};

    // Traditional:
    // std::sort(v.begin(), v.end());
    // auto it = std::find(v.begin(), v.end(), 3);
    // auto c  = std::count(v.begin(), v.end(), 3);

    // Ranges (cleaner):
    std::ranges::sort(v);
    auto found = std::ranges::find(v, 3);
    auto countVal = std::ranges::count(v, 3);

    std::cout << "Sorted: ";
    for (int val : v)
        std::cout << val << ' ';
    std::cout << '\n';
    std::cout << "Found 3: " << (found != v.end() ? "yes" : "no") << '\n';
    std::cout << "Count of 3: " << countVal << '\n';

    return 0;
}
