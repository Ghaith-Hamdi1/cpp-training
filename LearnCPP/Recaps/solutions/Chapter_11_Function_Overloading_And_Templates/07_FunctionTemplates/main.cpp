// Chapter 11 - Project 07: Function Templates
// ================================================================
// A function template is a blueprint using type template parameters
// (e.g. `T`) as placeholders.  The compiler generates concrete functions
// ("instantiations") from it as needed.
//
// This avoids writing duplicate functions for every type (DRY principle).

#include <iostream>

// ---------------------------------------------------------------
// Without templates: repetitive code for each type
// ---------------------------------------------------------------
// int    maxInt(int x, int y)       { return (x >= y) ? x : y; }
// double maxDouble(double x, double y) { return (x >= y) ? x : y; }
// These are identical apart from the type - a perfect case for a template.

// ---------------------------------------------------------------
// With a function template
// ---------------------------------------------------------------
// `template <typename T>` declares T as a type template parameter.
// T is a placeholder that gets replaced with a real type when instantiated.
template <typename T>
T max(T x, T y)
{
    return (x >= y) ? x : y;
}

// The compiler will generate concrete functions like max<int>, max<double>, etc.
// only when they are actually used. Each instantiation is a full, real function.

// ---------------------------------------------------------------
// Another template example: swap two values
// ---------------------------------------------------------------
template <typename T>
void swapValues(T &a, T &b)
{
    T temp{a};
    a = b;
    b = temp;
}

// ---------------------------------------------------------------
// Template with multiple statements
// ---------------------------------------------------------------
template <typename T>
T clamp(T value, T low, T high)
{
    // Ensure value is within [low, high]
    if (value < low)
        return low;
    if (value > high)
        return high;
    return value;
}

int main()
{
    std::cout << "=== max template ===\n";

    // Explicit template argument syntax: max<int>(...)
    std::cout << "max<int>(3, 7)          = " << max<int>(3, 7) << '\n';
    std::cout << "max<double>(3.5, 2.1)   = " << max<double>(3.5, 2.1) << '\n';

    // Normal call syntax - the compiler deduces T from the arguments:
    std::cout << "max(10, 20)             = " << max(10, 20) << '\n';   // T = int
    std::cout << "max(1.1, 2.2)           = " << max(1.1, 2.2) << '\n'; // T = double
    std::cout << "max('a', 'z')           = " << max('a', 'z') << '\n'; // T = char

    std::cout << "\n=== swapValues template ===\n";
    int a{5}, b{10};
    std::cout << "Before swap: a=" << a << ", b=" << b << '\n';
    swapValues(a, b); // T = int (deduced)
    std::cout << "After swap:  a=" << a << ", b=" << b << '\n';

    double x{1.1}, y{9.9};
    std::cout << "Before swap: x=" << x << ", y=" << y << '\n';
    swapValues(x, y); // T = double (deduced)
    std::cout << "After swap:  x=" << x << ", y=" << y << '\n';

    std::cout << "\n=== clamp template ===\n";
    std::cout << "clamp(15, 0, 10) = " << clamp(15, 0, 10) << '\n'; // clamped to 10
    std::cout << "clamp(-5, 0, 10) = " << clamp(-5, 0, 10) << '\n'; // clamped to 0
    std::cout << "clamp(7, 0, 10)  = " << clamp(7, 0, 10) << '\n';  // unchanged

    return 0;
}
