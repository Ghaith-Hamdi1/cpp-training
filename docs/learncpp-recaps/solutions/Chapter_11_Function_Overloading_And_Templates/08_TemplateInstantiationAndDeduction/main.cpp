// Chapter 11 - Project 08: Template Instantiation and Argument Deduction
// ================================================================
// When a template is used, the compiler INSTANTIATES a concrete function
// by replacing template parameters with actual types.
//
// Key points:
//   - Template argument deduction lets the compiler infer T from arguments
//   - Deduction does NOT perform type conversions
//   - Normal call syntax is preferred over explicit template arguments
//   - Each unique instantiation is a separate function (own static locals)
//   - Non-template functions are preferred over equally viable template ones

#include <iostream>

// ---------------------------------------------------------------
// A simple template
// ---------------------------------------------------------------
template <typename T>
T add(T x, T y)
{
    // Each instantiation gets its own copy of any static local
    static int callCount{0};
    ++callCount;
    std::cout << "  [add<" << typeid(T).name() << "> call #" << callCount << "] ";
    return x + y;
}

// ---------------------------------------------------------------
// Non-template overload - preferred over template when equally viable
// ---------------------------------------------------------------
int add(int x, int y)
{
    std::cout << "  [add(int,int) non-template] ";
    return x + y;
}

// ---------------------------------------------------------------
// Demonstrating deduction failure with mismatched types
// ---------------------------------------------------------------
template <typename T>
T multiply(T x, T y)
{
    return x * y;
}
// multiply(2, 3.0)  would FAIL:
//   T can't be both int and double
//   Deduction does NOT convert - it requires exact matches.

int main()
{
    std::cout << "=== Template argument deduction ===\n";

    // Explicit template argument:
    std::cout << "add<double>(1.5, 2.5) = " << add<double>(1.5, 2.5) << '\n';

    // Deduced from arguments:
    std::cout << "add(1.5, 2.5)         = " << add(1.5, 2.5) << '\n'; // T = double

    std::cout << "\n=== Non-template preferred over template ===\n";
    // Both add(int,int) non-template and add<int>(int,int) template match.
    // The non-template version wins:
    std::cout << "add(3, 4) = " << add(3, 4) << '\n'; // calls non-template

    // We can force the template version with explicit syntax:
    std::cout << "add<int>(3, 4) = " << add<int>(3, 4) << '\n'; // calls template

    std::cout << "\n=== Each instantiation has its own static locals ===\n";
    // add<double> and add<int> each have separate callCount variables.
    std::cout << "add(10.0, 20.0) = " << add(10.0, 20.0) << '\n';   // add<double> call #2
    std::cout << "add<int>(10, 20) = " << add<int>(10, 20) << '\n'; // add<int> call #2

    std::cout << "\n=== Deduction does NOT convert types ===\n";
    // multiply(2, 3.0);  // Would fail: T can't be int AND double

    // Fix 1: use static_cast so both args are the same type
    std::cout << "multiply(2, static_cast<int>(3.0)) = "
              << multiply(2, static_cast<int>(3.0)) << '\n';

    // Fix 2: explicitly specify T, then the second arg converts
    std::cout << "multiply<double>(2, 3.0) = "
              << multiply<double>(2, 3.0) << '\n';

    return 0;
}
