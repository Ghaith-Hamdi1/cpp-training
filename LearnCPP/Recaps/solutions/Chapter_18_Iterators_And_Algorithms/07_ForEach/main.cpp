// Chapter 18 - Project 7: std::for_each
// ========================================
// std::for_each applies a function to every element in a range.
//
// Advantages over range-based for-loops:
//   - Guarantees sequential, single-access traversal
//   - Avoids common mistakes like wrong type deduction, missing
//     reference, or accidentally using the wrong variable name
//   - Makes intent explicit: "do this to each element"
//
// std::for_each(begin, end, callable)
//   - callable can be a function pointer, lambda, or functor
//   - Returns the callable (useful with stateful functors)

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// A regular function can serve as the callable
void doubleAndPrint(int &val)
{
    val *= 2;
    std::cout << val << ' ';
}

int main()
{
    // --- 1) Basic std::for_each with a lambda ---
    std::cout << "=== for_each with a lambda (print) ===\n";

    std::vector<int> nums{1, 2, 3, 4, 5};

    std::for_each(nums.begin(), nums.end(),
                  [](int val)
                  { std::cout << val << ' '; });
    std::cout << '\n';

    // --- 2) for_each with a function pointer ---
    std::cout << "\n=== for_each with function pointer (double and print) ===\n";

    std::for_each(nums.begin(), nums.end(), doubleAndPrint);
    std::cout << '\n';

    // nums is now { 2, 4, 6, 8, 10 } - for_each modified elements via reference

    // --- 3) for_each with a stateful lambda ---
    std::cout << "\n=== for_each with stateful lambda (compute sum) ===\n";

    int total{0};
    std::for_each(nums.begin(), nums.end(),
                  [&total](int val)
                  { total += val; });

    std::cout << "Sum of doubled values: " << total << '\n';

    // --- 4) for_each on a subset of elements ---
    std::cout << "\n=== for_each on a subset (first 3 elements) ===\n";

    std::vector<std::string> words{"hello", "world", "foo", "bar", "baz"};

    std::for_each(words.begin(), words.begin() + 3,
                  [](const std::string &w)
                  { std::cout << w << ' '; });
    std::cout << '\n';

    // --- 5) Comparing for_each vs range-based for-loop pitfalls ---
    std::cout << "\n=== Pitfall: missing & in range-based for ===\n";

    std::vector<int> values{1, 2, 3};

    // BUG (if intent is to modify): val is a COPY, not a reference
    for (auto val : values) // Should be `auto& val`
        val *= 10;          // Modifies the copy, NOT the vector

    std::cout << "After 'auto val' loop (unchanged): ";
    for (int v : values)
        std::cout << v << ' ';
    std::cout << '\n';

    // CORRECT: use auto& to modify elements
    for (auto &val : values)
        val *= 10;

    std::cout << "After 'auto& val' loop (modified): ";
    for (int v : values)
        std::cout << v << ' ';
    std::cout << '\n';

    // for_each avoids this by making you explicitly write the parameter type
    std::cout << "\nfor_each always makes intent clear via the callable signature.\n";

    return 0;
}
