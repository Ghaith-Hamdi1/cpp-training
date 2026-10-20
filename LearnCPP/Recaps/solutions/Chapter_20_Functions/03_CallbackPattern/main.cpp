// Chapter 20 - Project 03: The Callback Pattern
// ===============================================
// Demonstrates: passing a function (as a pointer or std::function)
// to another function so the caller can customize behavior.
//
// Key points:
//   - Callbacks let you inject behavior into a general-purpose function.
//   - The standard library uses this pattern heavily (e.g., std::sort comparator).
//   - std::function is preferred for callback parameters because it accepts
//     function pointers, lambdas, and functors alike.

#include <algorithm>  // std::sort
#include <functional> // std::function
#include <iostream>
#include <vector>

// -------------------------------------------------------
// 1. A function that accepts a callback
// -------------------------------------------------------
// 'predicate' decides which elements to print.
void printIf(const std::vector<int> &v,
             const std::function<bool(int)> &predicate,
             std::string_view label)
{
    std::cout << label << ": ";
    for (int val : v)
    {
        if (predicate(val))
            std::cout << val << ' ';
    }
    std::cout << '\n';
}

// -------------------------------------------------------
// 2. Some named predicates (plain functions)
// -------------------------------------------------------
bool isEven(int n) { return n % 2 == 0; }
bool isPositive(int n) { return n > 0; }

int main()
{
    std::vector<int> data{7, -3, 12, 0, -8, 5, 2, -1, 9, 4};

    // Pass a named function as callback
    printIf(data, isEven, "Even numbers     ");
    printIf(data, isPositive, "Positive numbers ");

    // Pass a lambda as callback
    printIf(data, [](int n)
            { return n < 0; }, "Negative numbers ");

    // -------------------------------------------------------
    // 3. std::sort with a custom comparator callback
    // -------------------------------------------------------
    // Sort descending using a lambda comparator
    std::sort(data.begin(), data.end(), [](int a, int b)
              { return a > b; });

    std::cout << "\nSorted descending: ";
    for (int val : data)
        std::cout << val << ' ';
    std::cout << '\n';

    // Sort ascending by absolute value using a lambda
    std::sort(data.begin(), data.end(),
              [](int a, int b)
              { return std::abs(a) < std::abs(b); });

    std::cout << "Sorted by |value|: ";
    for (int val : data)
        std::cout << val << ' ';
    std::cout << '\n';

    return 0;
}
