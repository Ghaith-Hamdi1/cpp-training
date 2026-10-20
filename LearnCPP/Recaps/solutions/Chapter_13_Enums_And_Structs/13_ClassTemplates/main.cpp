// Chapter 13 - Project 13: Class Templates
// Demonstrates: template <typename T> struct, instantiation with different
//               types, std::pair, and putting templates in headers.

#include <iostream>
#include <string>
#include <utility> // std::pair

// ============================================================================
// 1. Defining a class template
// ============================================================================
// A class template is a blueprint for generating struct/class types.
// 'T' is a type template parameter - it will be replaced by a real type
// when we instantiate the template.
template <typename T>
struct Pair
{
    T first{};
    T second{};
};

// ============================================================================
// 2. Class template with multiple type parameters
// ============================================================================
template <typename T, typename U>
struct MixedPair
{
    T first{};
    U second{};
};

// ============================================================================
// 3. Function templates that use class templates
// ============================================================================
template <typename T>
T larger(const Pair<T> &p)
{
    return (p.first > p.second) ? p.first : p.second;
}

template <typename T>
void printPair(const Pair<T> &p)
{
    std::cout << '(' << p.first << ", " << p.second << ')';
}

template <typename T, typename U>
void printMixedPair(const MixedPair<T, U> &p)
{
    std::cout << '(' << p.first << ", " << p.second << ')';
}

int main()
{
    // ========================================================================
    // Using Pair with different types
    // ========================================================================
    std::cout << "=== Pair<int> ===\n";
    Pair<int> intPair{3, 7};
    printPair(intPair);
    std::cout << " - larger: " << larger(intPair) << '\n';

    std::cout << "\n=== Pair<double> ===\n";
    Pair<double> dblPair{2.5, 1.8};
    printPair(dblPair);
    std::cout << " - larger: " << larger(dblPair) << '\n';

    std::cout << "\n=== Pair<std::string> ===\n";
    Pair<std::string> strPair{"apple", "banana"};
    printPair(strPair);
    std::cout << " - larger: " << larger(strPair) << '\n';

    // ========================================================================
    // MixedPair with two different types
    // ========================================================================
    std::cout << "\n=== MixedPair<int, double> ===\n";
    MixedPair<int, double> mixed{42, 3.14};
    printMixedPair(mixed);
    std::cout << '\n';

    std::cout << "\n=== MixedPair<std::string, int> ===\n";
    MixedPair<std::string, int> namedAge{"Alice", 30};
    printMixedPair(namedAge);
    std::cout << '\n';

    // ========================================================================
    // std::pair - the standard library's pair template
    // ========================================================================
    // Best practice: use std::pair (from <utility>) instead of your own.
    std::cout << "\n=== std::pair ===\n";
    std::pair<std::string, int> student{"Bob", 95};
    std::cout << student.first << " scored " << student.second << '\n';

    // std::pair supports make_pair for convenience:
    auto item{std::make_pair("Widget", 9.99)};
    std::cout << item.first << " costs $" << item.second << '\n';

    // ========================================================================
    // Templates belong in header files
    // ========================================================================
    // Unlike regular functions, template definitions must be visible at the
    // point of instantiation. That's why class templates are placed in
    // header files (.h), not source files (.cpp).

    return 0;
}
