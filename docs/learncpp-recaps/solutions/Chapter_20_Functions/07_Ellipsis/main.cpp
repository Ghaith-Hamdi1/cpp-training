// Chapter 20 - Project 07: Ellipsis (and Why to Avoid Them)
// =========================================================
// Demonstrates: C-style variadic functions using <cstdarg>,
// and why modern C++ alternatives are superior.
//
// Key points:
//   - Ellipsis (...) lets a function accept a variable number of arguments.
//   - Uses va_list, va_start, va_arg, va_end macros.
//   - The function has NO way to know the types or count of arguments -
//     the caller must communicate this (e.g., via a count parameter).
//   - Passing the wrong types causes garbage results - no compiler warning.
//   - Modern alternatives: variadic templates, fold expressions, std::initializer_list.
//   - Rule: AVOID ellipsis in new code.

#include <cstdarg> // va_list, va_start, va_arg, va_end
#include <iostream>
#include <numeric> // std::accumulate
#include <vector>

// -------------------------------------------------------
// 1. C-style variadic function (AVOID in real code)
// -------------------------------------------------------
// 'count' tells us how many extra arguments follow.
// We ASSUME they are all double - if the caller passes an int, garbage results!
double unsafeAverage(int count, ...)
{
    va_list args;
    va_start(args, count); // initialize the argument list after 'count'

    double sum{0.0};
    for (int i{0}; i < count; ++i)
    {
        sum += va_arg(args, double); // extract next argument as double
    }

    va_end(args); // clean up
    return (count > 0) ? sum / count : 0.0;
}

// -------------------------------------------------------
// 2. Modern alternative: std::initializer_list (safe)
// -------------------------------------------------------
double safeAverage(std::initializer_list<double> values)
{
    if (values.size() == 0)
        return 0.0;

    double sum{0.0};
    for (double v : values)
        sum += v;
    return sum / static_cast<double>(values.size());
}

// -------------------------------------------------------
// 3. Modern alternative: variadic template with fold expression (C++17)
// -------------------------------------------------------
template <typename... Args>
auto templateSum(Args... args)
{
    return (args + ...); // fold expression: adds all arguments
}

int main()
{
    // C-style ellipsis - works IF you pass the right types
    std::cout << "=== C-style ellipsis (unsafe) ===\n";
    std::cout << "average(3, 1.0, 2.0, 3.0) = " << unsafeAverage(3, 1.0, 2.0, 3.0) << '\n';
    std::cout << "average(4, 10.0, 20.0, 30.0, 40.0) = "
              << unsafeAverage(4, 10.0, 20.0, 30.0, 40.0) << '\n';

    // What if we pass ints by mistake?  The function expects doubles.
    // This may produce garbage results because int and double have different sizes.
    // Uncomment to see:
    // std::cout << "average(2, 1, 2) = " << unsafeAverage(2, 1, 2) << '\n'; // BUG!

    // std::initializer_list - type-safe, readable
    std::cout << "\n=== std::initializer_list (safe) ===\n";
    std::cout << "average({1.0, 2.0, 3.0}) = " << safeAverage({1.0, 2.0, 3.0}) << '\n';
    std::cout << "average({10.0, 20.0, 30.0, 40.0}) = "
              << safeAverage({10.0, 20.0, 30.0, 40.0}) << '\n';

    // Variadic template - fully type-safe, compile-time checked
    std::cout << "\n=== Variadic template fold expression (safe) ===\n";
    std::cout << "sum(1, 2, 3, 4, 5) = " << templateSum(1, 2, 3, 4, 5) << '\n';
    std::cout << "sum(1.5, 2.5, 3.0) = " << templateSum(1.5, 2.5, 3.0) << '\n';

    return 0;
}
