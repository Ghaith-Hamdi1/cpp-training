// Project 04: Class Template Argument Deduction (CTAD)
// =====================================================
// Appendix A.4 - CTAD (C++17 and later)
//
// CTAD lets the compiler deduce template arguments from the initializer,
// so you don't have to spell them out explicitly.
//
// Before C++17:    std::pair<int, double> p(1, 2.5);
// With CTAD:       std::pair p(1, 2.5);        // deduced as pair<int,double>
//
// Requirements:
//   - Compile with at least C++17 (or C++20).
//   - Works with standard library types (pair, tuple, vector, array,
//     optional, etc.) and user-defined class templates.
//   - User-defined types can provide *deduction guides* to help the
//     compiler deduce template arguments from constructor parameters.

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <tuple>
#include <optional>
#include <utility> // std::pair

// -----------------------------------------------------------------------
// User-defined class template with CTAD
// -----------------------------------------------------------------------
template <typename T>
class Wrapper
{
    T m_value;

public:
    explicit Wrapper(const T &value) : m_value{value} {}

    const T &get() const { return m_value; }
};

// A deduction guide: when constructed from a const char*, deduce as std::string
Wrapper(const char *) -> Wrapper<std::string>;

// -----------------------------------------------------------------------
// Another example: a Pair template
// -----------------------------------------------------------------------
template <typename T1, typename T2>
struct MyPair
{
    T1 first;
    T2 second;

    MyPair(T1 f, T2 s) : first{f}, second{s} {}
};

// No explicit deduction guide needed here - the compiler generates one
// from the constructor parameters (implicit deduction guide).

int main()
{
    std::cout << "=== Class Template Argument Deduction (CTAD) ===\n\n";

    // --- std::pair --------------------------------------------------------
    // Before CTAD: std::pair<int, double> p1(42, 3.14);
    std::pair p1(42, 3.14); // CTAD: deduced as pair<int, double>
    std::cout << "pair: (" << p1.first << ", " << p1.second << ")\n";

    // --- std::tuple -------------------------------------------------------
    std::tuple t1(1, 2.5, std::string{"hello"}); // tuple<int, double, string>
    std::cout << "tuple: (" << std::get<0>(t1)
              << ", " << std::get<1>(t1)
              << ", " << std::get<2>(t1) << ")\n";

    // --- std::vector ------------------------------------------------------
    std::vector v1{10, 20, 30, 40}; // CTAD: deduced as vector<int>
    std::cout << "vector<int>: ";
    for (int n : v1)
        std::cout << n << ' ';
    std::cout << '\n';

    // --- std::array (C++17 CTAD) ------------------------------------------
    std::array a1{1.1, 2.2, 3.3}; // CTAD: deduced as array<double, 3>
    std::cout << "array<double,3>: ";
    for (double d : a1)
        std::cout << d << ' ';
    std::cout << '\n';

    // --- std::optional ----------------------------------------------------
    std::optional opt1{99}; // CTAD: deduced as optional<int>
    if (opt1.has_value())
        std::cout << "optional<int>: " << opt1.value() << '\n';

    // --- User-defined: Wrapper with deduction guide -----------------------
    std::cout << "\n--- User-defined CTAD ---\n";

    Wrapper w1{42}; // Wrapper<int>
    std::cout << "Wrapper<int>:    " << w1.get() << '\n';

    Wrapper w2{3.14}; // Wrapper<double>
    std::cout << "Wrapper<double>: " << w2.get() << '\n';

    Wrapper w3{"hello"}; // Deduction guide → Wrapper<std::string>
    std::cout << "Wrapper<string>: " << w3.get() << '\n';

    // --- User-defined: MyPair (implicit deduction guide) ------------------
    MyPair mp{10, std::string{"world"}}; // MyPair<int, std::string>
    std::cout << "MyPair: (" << mp.first << ", " << mp.second << ")\n";

    // --- Summary ----------------------------------------------------------
    std::cout << "\n--- Summary ---\n";
    std::cout << "CTAD (C++17) lets the compiler deduce template args from initializers.\n";
    std::cout << "Works with standard library types and user-defined templates.\n";
    std::cout << "Deduction guides help when constructor args don't match the desired type.\n";
    std::cout << "Requires compiling with at least -std=c++17.\n";

    return 0;
}
