// Chapter 20 - Project 11: Generic Lambdas
// ==========================================
// Demonstrates: auto parameters in lambdas, constexpr lambdas,
// and standard library functors from <functional>.
//
// Key points:
//   - Using 'auto' for lambda parameters creates a generic (templated) lambda.
//   - Each distinct argument type causes a separate instantiation.
//   - In C++17+, lambdas are implicitly constexpr when possible.
//   - C++20 adds explicit template parameter lists for lambdas.
//   - <functional> provides pre-built functors: std::plus, std::greater, etc.

#include <algorithm>
#include <functional> // std::plus, std::greater, std::multiplies
#include <iostream>
#include <numeric> // std::accumulate
#include <string>
#include <vector>

int main()
{
    // -------------------------------------------------------
    // 1. Generic lambda with 'auto' parameters
    // -------------------------------------------------------
    // Works with any types that support operator+
    auto add = [](auto a, auto b)
    {
        return a + b;
    };

    std::cout << "=== Generic lambda (auto params) ===\n";
    std::cout << "add(3, 4)       = " << add(3, 4) << '\n';     // int
    std::cout << "add(1.5, 2.7)   = " << add(1.5, 2.7) << '\n'; // double
    std::cout << "add(\"Hi\"s, \" there\"s) = "
              << add(std::string("Hi"), std::string(" there")) << '\n'; // string

    // -------------------------------------------------------
    // 2. Generic lambda for printing any container
    // -------------------------------------------------------
    auto printContainer = [](const auto &container, std::string_view label)
    {
        std::cout << label << ": ";
        for (const auto &elem : container)
            std::cout << elem << ' ';
        std::cout << '\n';
    };

    std::vector<int> ints{5, 3, 1, 4, 2};
    std::vector<std::string> words{"hello", "world", "cpp"};

    printContainer(ints, "ints");
    printContainer(words, "words");

    // -------------------------------------------------------
    // 3. C++20 explicit template parameter lambda
    // -------------------------------------------------------
    // Allows constraining or naming the template parameter.
    auto typedMax = []<typename T>(T a, T b) -> T
    {
        return (a > b) ? a : b;
    };

    std::cout << "\n=== C++20 template lambda ===\n";
    std::cout << "max(10, 20)   = " << typedMax(10, 20) << '\n';
    std::cout << "max(3.14, 2.71) = " << typedMax(3.14, 2.71) << '\n';

    // -------------------------------------------------------
    // 4. constexpr lambda (C++17+)
    // -------------------------------------------------------
    // Lambdas are implicitly constexpr when the body qualifies.
    constexpr auto square = [](int n)
    { return n * n; };
    static_assert(square(5) == 25, "compile-time check");

    std::cout << "\nconstexpr square(7) = " << square(7) << '\n';

    // -------------------------------------------------------
    // 5. Standard library functors from <functional>
    // -------------------------------------------------------
    std::cout << "\n=== Standard functors ===\n";

    // std::sort with std::greater - no need to write a lambda
    std::sort(ints.begin(), ints.end(), std::greater<int>{});
    printContainer(ints, "sorted desc");

    // std::accumulate with std::multiplies
    int product = std::accumulate(ints.begin(), ints.end(), 1, std::multiplies<int>{});
    std::cout << "product of ints: " << product << '\n';

    // std::plus used directly
    std::plus<int> adder;
    std::cout << "std::plus(10, 20) = " << adder(10, 20) << '\n';

    return 0;
}
