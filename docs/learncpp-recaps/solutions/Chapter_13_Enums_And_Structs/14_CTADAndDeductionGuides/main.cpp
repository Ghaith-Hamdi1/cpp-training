// Chapter 13 - Project 14: CTAD and Deduction Guides
// Demonstrates: Class Template Argument Deduction (C++17), deduction guides,
//               C++20 aggregate CTAD, and cases where CTAD doesn't work.
//
// Requires: C++20 or later

#include <iostream>
#include <string>
#include <utility> // std::pair

// ============================================================================
// 1. A simple class template
// ============================================================================
template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

// ============================================================================
// 2. Deduction guide (needed in C++17 for aggregate templates)
// ============================================================================
// In C++17, aggregate class templates cannot auto-deduce types.
// A deduction guide tells the compiler how to deduce T and U:
//
//   template <typename T, typename U>
//   Pair(T, U) -> Pair<T, U>;
//
// In C++20, this deduction guide is auto-generated for aggregates,
// so you don't need to write it yourself. We include it here for
// backward compatibility and to demonstrate the concept.

// Explicit deduction guide (C++17 requirement, optional in C++20):
template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;

// ============================================================================
// 3. Another template to demonstrate CTAD
// ============================================================================
template <typename T>
struct Wrapper
{
    T value{};
};

// Deduction guide for Wrapper
template <typename T>
Wrapper(T) -> Wrapper<T>;

// ============================================================================
// 4. Print helpers
// ============================================================================
template <typename T, typename U>
void printPair(const Pair<T, U> &p)
{
    std::cout << '(' << p.first << ", " << p.second << ')';
}

template <typename T>
void printWrapper(const Wrapper<T> &w)
{
    std::cout << '[' << w.value << ']';
}

int main()
{
    // ========================================================================
    // CTAD in action - compiler deduces template arguments from initializers
    // ========================================================================
    std::cout << "=== CTAD: Pair ===\n";

    // Without CTAD, you'd have to write: Pair<int, double> p1{ 1, 2.5 };
    // With CTAD, the compiler deduces <int, double> from the initializers:
    Pair p1{1, 2.5}; // deduced as Pair<int, double>
    printPair(p1);
    std::cout << '\n';

    Pair p2{3.14, std::string{"hello"}}; // Pair<double, std::string>
    printPair(p2);
    std::cout << '\n';

    // ========================================================================
    // CTAD with Wrapper
    // ========================================================================
    std::cout << "\n=== CTAD: Wrapper ===\n";
    Wrapper w1{42};                  // Wrapper<int>
    Wrapper w2{3.14};                // Wrapper<double>
    Wrapper w3{std::string{"text"}}; // Wrapper<std::string>

    printWrapper(w1);
    std::cout << '\n';
    printWrapper(w2);
    std::cout << '\n';
    printWrapper(w3);
    std::cout << '\n';

    // ========================================================================
    // CTAD with std::pair (standard library)
    // ========================================================================
    std::cout << "\n=== CTAD: std::pair ===\n";
    std::pair sp{"Alice", 95}; // std::pair<const char*, int>
    std::cout << sp.first << ": " << sp.second << '\n';

    // ========================================================================
    // Where CTAD does NOT work
    // ========================================================================
    std::cout << "\n=== CTAD Limitations ===\n";

    // 1) CTAD doesn't work with non-static member initialization:
    //    struct Foo { Pair member{ 1, 2 }; }; // ERROR: can't deduce Pair<?,?>
    //    Fix: specify types explicitly: Pair<int,int> member{ 1, 2 };

    // 2) CTAD doesn't work in function parameters:
    //    void func(Pair p);  // ERROR: can't deduce Pair<?,?>
    //    Fix: make the function a template, or specify types explicitly.

    // 3) CTAD needs initializers - you can't write: Pair p; (no deduction info)

    std::cout << "CTAD doesn't work for:\n";
    std::cout << "  - Non-static data member initialization\n";
    std::cout << "  - Function parameter types\n";
    std::cout << "  - Declarations without initializers\n";

    // ========================================================================
    // Explicit template arguments still work as always
    // ========================================================================
    std::cout << "\n=== Explicit Template Arguments (fallback) ===\n";
    Pair<int, int> explicit1{10, 20};
    printPair(explicit1);
    std::cout << '\n';

    return 0;
}
