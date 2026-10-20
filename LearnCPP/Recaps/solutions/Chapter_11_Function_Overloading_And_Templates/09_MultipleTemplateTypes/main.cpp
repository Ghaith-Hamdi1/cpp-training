// Chapter 11 - Project 09: Multiple Template Type Parameters
// ================================================================
// A single template type T forces all T-typed parameters to be the same type.
// To support mixed types, use multiple template parameters (T and U).
// Use `auto` return type to let the compiler deduce the correct result type.

#include <iostream>
#include <type_traits> // for std::common_type_t

// ---------------------------------------------------------------
// Problem: single-type template can't handle mixed types
// ---------------------------------------------------------------
// template <typename T>
// T max(T x, T y) { return (x >= y) ? x : y; }
// max(2, 3.5) → FAIL: T can't be both int and double

// ---------------------------------------------------------------
// Solution 1: Multiple template parameters + auto return type
// ---------------------------------------------------------------
template <typename T, typename U>
auto maxVal(T x, U y)
{
    // auto return type deduced from the ternary expression.
    // If T=int and U=double, the return type is double (common type).
    return (x >= y) ? x : y;
}

// ---------------------------------------------------------------
// Solution 2: Use std::common_type_t for an explicit return type
// ---------------------------------------------------------------
template <typename T, typename U>
std::common_type_t<T, U> addVal(T x, U y)
{
    // std::common_type_t<int, double> is double
    return x + y;
}

// ---------------------------------------------------------------
// Multi-type template with three parameters
// ---------------------------------------------------------------
template <typename T, typename U, typename V>
auto clampVal(T value, U low, V high)
{
    if (value < low)
        return static_cast<std::common_type_t<T, U, V>>(low);
    if (value > high)
        return static_cast<std::common_type_t<T, U, V>>(high);
    return static_cast<std::common_type_t<T, U, V>>(value);
}

int main()
{
    std::cout << "=== maxVal with mixed types ===\n";
    std::cout << "maxVal(3, 7.5)   = " << maxVal(3, 7.5) << '\n'; // T=int, U=double → returns double
    std::cout << "maxVal(9.1, 4)   = " << maxVal(9.1, 4) << '\n'; // T=double, U=int → returns double
    std::cout << "maxVal(10, 20)   = " << maxVal(10, 20) << '\n'; // T=int, U=int → returns int

    std::cout << "\n=== addVal with mixed types ===\n";
    std::cout << "addVal(3, 4.5)   = " << addVal(3, 4.5) << '\n';  // int + double → double
    std::cout << "addVal(1.5f, 2)  = " << addVal(1.5f, 2) << '\n'; // float + int → float

    std::cout << "\n=== clampVal with mixed types ===\n";
    std::cout << "clampVal(3.5, 0, 10)    = " << clampVal(3.5, 0, 10) << '\n';
    std::cout << "clampVal(-1, 0.0, 10.0) = " << clampVal(-1, 0.0, 10.0) << '\n';
    std::cout << "clampVal(99, 0, 10)     = " << clampVal(99, 0, 10) << '\n';

    // Key insight: with auto return, the compiler picks the type that
    // avoids narrowing conversions - much safer than manually choosing T or U.

    return 0;
}
