// Chapter 12 - Project 14: std::optional
// =========================================
// std::optional<T> holds either a value of type T or nothing (std::nullopt).
// It replaces error sentinel values (like -1 or "") with a clean, type-safe API.
//
// Key operations:
//   • Construct:     std::optional<int> opt{ 42 };   or   std::nullopt
//   • Check:         opt.has_value()  or  if (opt)
//   • Access:        *opt,  opt.value(),  opt.value_or(default)
//   • Reset:         opt.reset()  or  opt = std::nullopt
//
// Prefer std::optional for functions that may or may not return a result.

#include <iostream>
#include <optional>
#include <string>
#include <cmath>

// Return std::optional instead of a sentinel value for "not found"
std::optional<int> findIndex(const int *arr, int size, int target)
{
    for (int i{0}; i < size; ++i)
    {
        if (arr[i] == target)
            return i; // implicitly constructs std::optional<int>{i}
    }
    return std::nullopt; // "not found" - no value
}

// Return std::optional for a computation that might fail
std::optional<double> safeSqrt(double value)
{
    if (value < 0.0)
        return std::nullopt; // can't take sqrt of negative
    return std::sqrt(value);
}

// Parse a string to int, returning nullopt on failure
std::optional<int> parseInt(const std::string &str)
{
    try
    {
        std::size_t pos{};
        int result{std::stoi(str, &pos)};
        if (pos != str.length()) // trailing characters = not a clean parse
            return std::nullopt;
        return result;
    }
    catch (...)
    {
        return std::nullopt;
    }
}

int main()
{
    // ----- Basic construction and checking -----
    std::optional<int> opt1{42};
    std::optional<int> opt2{};             // empty (std::nullopt)
    std::optional<int> opt3{std::nullopt}; // also empty

    std::cout << "opt1 has value? " << (opt1.has_value() ? "yes" : "no") << '\n'; // yes
    std::cout << "opt2 has value? " << (opt2.has_value() ? "yes" : "no") << '\n'; // no

    // ----- Accessing the value -----
    std::cout << "\n=== Accessing values ===\n";
    std::cout << "*opt1           = " << *opt1 << '\n';            // 42 (no bounds check)
    std::cout << "opt1.value()    = " << opt1.value() << '\n';     // 42 (throws if empty)
    std::cout << "opt2.value_or(0)= " << opt2.value_or(0) << '\n'; // 0 (default)

    // ----- findIndex -----
    std::cout << "\n=== findIndex ===\n";
    int arr[]{10, 20, 30, 40, 50};

    auto idx{findIndex(arr, 5, 30)};
    if (idx)
        std::cout << "Found 30 at index " << *idx << '\n';
    else
        std::cout << "30 not found.\n";

    auto idx2{findIndex(arr, 5, 99)};
    std::cout << "Index of 99: " << idx2.value_or(-1) << '\n'; // -1 (fallback)

    // ----- safeSqrt -----
    std::cout << "\n=== safeSqrt ===\n";
    auto r1{safeSqrt(25.0)};
    auto r2{safeSqrt(-4.0)};

    if (r1)
        std::cout << "sqrt(25) = " << *r1 << '\n';
    if (r2)
        std::cout << "sqrt(-4) = " << *r2 << '\n';
    else
        std::cout << "sqrt(-4) = no result (negative input)\n";

    // ----- parseInt -----
    std::cout << "\n=== parseInt ===\n";
    auto p1{parseInt("123")};
    auto p2{parseInt("abc")};
    auto p3{parseInt("42xyz")};

    std::cout << "parseInt(\"123\")   = " << p1.value_or(0) << '\n'; // 123
    std::cout << "parseInt(\"abc\")   = " << (p2 ? std::to_string(*p2) : "nullopt") << '\n';
    std::cout << "parseInt(\"42xyz\") = " << (p3 ? std::to_string(*p3) : "nullopt") << '\n';

    // ----- Resetting an optional -----
    std::cout << "\n=== Reset ===\n";
    std::optional<std::string> name{"Alice"};
    std::cout << "name = " << *name << '\n';
    name.reset(); // or name = std::nullopt
    std::cout << "After reset: has value? " << (name ? "yes" : "no") << '\n';

    // Assign a new value
    name = "Bob";
    std::cout << "After reassign: name = " << *name << '\n';

    return 0;
}
