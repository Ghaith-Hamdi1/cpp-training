// Chapter 20 - Project 08: Lambda Basics
// =======================================
// Demonstrates: lambda expression syntax, storing lambdas, and
// using them with standard library algorithms.
//
// Key points:
//   - Syntax: [captures](params) -> returnType { body; }
//   - Return type can usually be omitted (auto-deduced).
//   - Store a lambda in a variable using 'auto' (preferred) or std::function.
//   - A captureless lambda can also decay to a function pointer.
//   - Lambdas are ideal for short, one-off functions passed to algorithms.
//   - <functional> provides ready-made function objects like std::greater.

#include <algorithm>  // std::sort, std::find_if, std::for_each, std::count_if
#include <functional> // std::greater
#include <iostream>
#include <string>
#include <vector>

int main()
{
    // -------------------------------------------------------
    // 1. Basic lambda - stored in auto variable
    // -------------------------------------------------------
    auto greet = [](std::string_view name)
    {
        std::cout << "Hello, " << name << "!\n";
    };
    greet("World");
    greet("C++20");

    // -------------------------------------------------------
    // 2. Lambda with explicit return type
    // -------------------------------------------------------
    auto divide = [](double a, double b) -> double
    {
        if (b == 0.0)
            return 0.0; // avoid division by zero
        return a / b;
    };
    std::cout << "\n10.0 / 3.0 = " << divide(10.0, 3.0) << '\n';

    // -------------------------------------------------------
    // 3. Using lambdas with standard algorithms
    // -------------------------------------------------------
    std::vector<int> nums{5, 3, 8, 1, 9, 2, 7, 4, 6};

    // std::sort with a lambda comparator (descending)
    std::sort(nums.begin(), nums.end(), [](int a, int b)
              { return a > b; });

    std::cout << "\nSorted descending: ";
    std::for_each(nums.begin(), nums.end(), [](int n)
                  { std::cout << n << ' '; });
    std::cout << '\n';

    // std::find_if - find first element > 6
    auto it = std::find_if(nums.begin(), nums.end(), [](int n)
                           { return n > 6; });
    if (it != nums.end())
        std::cout << "First element > 6: " << *it << '\n';

    // std::count_if - count even numbers
    auto evenCount = std::count_if(nums.begin(), nums.end(),
                                   [](int n)
                                   { return n % 2 == 0; });
    std::cout << "Even numbers: " << evenCount << '\n';

    // -------------------------------------------------------
    // 4. Using std::greater from <functional> instead of a lambda
    // -------------------------------------------------------
    std::sort(nums.begin(), nums.end(), std::greater<int>{});
    std::cout << "\nSorted with std::greater: ";
    for (int n : nums)
        std::cout << n << ' ';
    std::cout << '\n';

    // -------------------------------------------------------
    // 5. Captureless lambda → function pointer decay
    // -------------------------------------------------------
    // A lambda with no captures can implicitly convert to a function pointer.
    int (*fnPtr)(int, int) = [](int a, int b)
    { return a + b; };
    std::cout << "\nCaptureless lambda as function pointer: " << fnPtr(10, 20) << '\n';

    return 0;
}
