// Chapter 11 - Project 11: Abbreviated Function Templates (C++20)
// ================================================================
// C++20 lets you use `auto` in a function's parameter list to implicitly
// create a function template.  Each `auto` parameter becomes an independent
// template type parameter - equivalent to writing template <typename T, ...>.
//
// Syntax:   auto funcName(auto x, auto y) { ... }
// Equivalent to: template <typename T, typename U> auto funcName(T x, U y) { ... }

#include <iostream>
#include <string>

// ---------------------------------------------------------------
// Traditional template
// ---------------------------------------------------------------
template <typename T, typename U>
auto traditionalMax(T x, U y)
{
    return (x >= y) ? x : y;
}

// ---------------------------------------------------------------
// C++20 abbreviated equivalent - much shorter!
// ---------------------------------------------------------------
auto abbreviatedMax(auto x, auto y)
{
    // Each `auto` is an independent type (like T and U).
    return (x >= y) ? x : y;
}

// ---------------------------------------------------------------
// Single auto parameter (like template <typename T>)
// ---------------------------------------------------------------
void printAnything(auto value)
{
    // This works with any printable type.
    std::cout << value << '\n';
}

// ---------------------------------------------------------------
// auto with constrained logic
// ---------------------------------------------------------------
auto add(auto x, auto y)
{
    return x + y;
}

// ---------------------------------------------------------------
// Mixing auto with a concrete type
// ---------------------------------------------------------------
void printNTimes(auto value, int n)
{
    // `value` is a template parameter, `n` is always int.
    for (int i{0}; i < n; ++i)
        std::cout << value << ' ';
    std::cout << '\n';
}

// ---------------------------------------------------------------
// Important: each `auto` is independent
// ---------------------------------------------------------------
// If you write:  auto func(auto x, auto y)
// x and y CAN be different types (like template<typename T, typename U>).
//
// If you NEED both parameters to be the same type, you must use
// the traditional syntax:  template <typename T> auto func(T x, T y)
// There is no abbreviated syntax for "same type" constraint.

// ---------------------------------------------------------------
// Comparison: traditional vs abbreviated
// ---------------------------------------------------------------
// Traditional:
template <typename T>
T square(T x)
{
    return x * x;
}

// Abbreviated equivalent - but note that the return type is `auto`,
// not guaranteed to be the same as the input:
auto squareAbbrev(auto x)
{
    return x * x;
}

int main()
{
    std::cout << "=== traditionalMax vs abbreviatedMax ===\n";
    std::cout << "traditionalMax(3, 7.5)  = " << traditionalMax(3, 7.5) << '\n';
    std::cout << "abbreviatedMax(3, 7.5)  = " << abbreviatedMax(3, 7.5) << '\n';
    std::cout << "abbreviatedMax(10, 20)  = " << abbreviatedMax(10, 20) << '\n';

    std::cout << "\n=== printAnything ===\n";
    printAnything(42);
    printAnything(3.14);
    printAnything("Hello, C++20!");
    printAnything('Z');

    std::cout << "\n=== add with mixed types ===\n";
    std::cout << "add(3, 4.5)     = " << add(3, 4.5) << '\n';     // int + double → double
    std::cout << "add(1.5f, 2.5f) = " << add(1.5f, 2.5f) << '\n'; // float + float → float

    // String concatenation also works!
    std::string s1{"Hello"};
    std::string s2{" World"};
    std::cout << "add(s1, s2)     = " << add(s1, s2) << '\n';

    std::cout << "\n=== printNTimes (mixed auto + concrete) ===\n";
    printNTimes("Go!", 3);
    printNTimes(42, 5);

    std::cout << "\n=== square: traditional vs abbreviated ===\n";
    std::cout << "square(5)           = " << square(5) << '\n';
    std::cout << "squareAbbrev(5)     = " << squareAbbrev(5) << '\n';
    std::cout << "squareAbbrev(2.5)   = " << squareAbbrev(2.5) << '\n';

    // Key takeaway: abbreviated function templates are a concise C++20
    // shorthand.  Each `auto` parameter is an INDEPENDENT type.
    // Use traditional syntax when you need to constrain multiple params
    // to the SAME type.

    return 0;
}
