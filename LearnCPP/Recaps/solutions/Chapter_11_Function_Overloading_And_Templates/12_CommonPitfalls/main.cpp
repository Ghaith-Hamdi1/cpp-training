// Chapter 11 - Project 12: Common Pitfalls
// ================================================================
// This file collects the most common mistakes when working with
// function overloading and templates, shows why they fail, and
// demonstrates the correct approach.

#include <iostream>
#include <string_view>

// =================================================================
// PITFALL 1: Differentiating overloads only by return type
// =================================================================
// int getValue()    { return 1; }
// double getValue() { return 1.0; }
// ^^^ COMPILE ERROR: return type is NOT part of overload differentiation.
//
// Fix: differ by parameters, or use a template.

template <typename T>
T getValue()
{
    if constexpr (std::is_same_v<T, int>)
        return 42;
    else if constexpr (std::is_same_v<T, double>)
        return 3.14;
    else
        return T{};
}

// =================================================================
// PITFALL 2: Type aliases do NOT create distinct overloads
// =================================================================
using Meters = double;
using Kilograms = double;

void measure(double x) { std::cout << "measure(double): " << x << '\n'; }
// void measure(Meters m) { ... }      // ERROR: Meters IS double - same overload
// void measure(Kilograms k) { ... }   // ERROR: Kilograms IS double - same overload

// =================================================================
// PITFALL 3: const on value parameters doesn't differentiate
// =================================================================
void process(int x) { std::cout << "process(int): " << x << '\n'; }
// void process(const int x)  { }  // ERROR: same overload as process(int)
// The caller can't tell the difference - both take int by value.

// =================================================================
// PITFALL 4: Mismatched types with single-type template
// =================================================================
template <typename T>
T maxSingle(T x, T y)
{
    return (x >= y) ? x : y;
}
// maxSingle(2, 3.5) → FAIL: T can't be int AND double simultaneously.

// Fix A: static_cast at the call site
// Fix B: explicit template argument: maxSingle<double>(2, 3.5)
// Fix C: use two template parameters (see Project 09)

// =================================================================
// PITFALL 5: Expecting type conversion during template deduction
// =================================================================
template <typename T>
T doubleIt(T x)
{
    return x * 2;
}
// doubleIt(3.14f) → T = float (deduced), returns float.
// If you expected double, you're wrong - deduction picks float.
// Fix: be explicit: doubleIt<double>(3.14f)

// =================================================================
// PITFALL 6: Deleted functions are NOT invisible
// =================================================================
void onlyDouble(double x)
{
    std::cout << "onlyDouble(double): " << x << '\n';
}
void onlyDouble(int) = delete; // "forbidden," NOT "nonexistent"

// onlyDouble(5) → ERROR: calls deleted function, not "no match found."
// The deleted overload IS found and IS selected - then rejected.

// =================================================================
// PITFALL 7: Skipping default arguments from the left
// =================================================================
void printFormatted(std::string_view text,
                    int width = 10,
                    char fill = '.')
{
    // Print text right-aligned in a field of `width`, padded with `fill`
    int pad = width - static_cast<int>(text.size());
    if (pad < 0)
        pad = 0;
    for (int i{0}; i < pad; ++i)
        std::cout << fill;
    std::cout << text << '\n';
}
// printFormatted("Hi", , '*')  → INVALID: can't skip middle argument
// You can only omit from the right.

// =================================================================
// PITFALL 8: Static locals NOT shared across template instantiations
// =================================================================
template <typename T>
int countCalls()
{
    static int count{0}; // each instantiation gets its OWN count
    return ++count;
}
// countCalls<int>() and countCalls<double>() are completely separate functions.

int main()
{
    std::cout << "=== Pitfall 1: Return type (fixed with template) ===\n";
    std::cout << "getValue<int>()    = " << getValue<int>() << '\n';
    std::cout << "getValue<double>() = " << getValue<double>() << '\n';

    std::cout << "\n=== Pitfall 2: Type aliases ===\n";
    Meters m{5.0};
    Kilograms k{70.0};
    measure(m); // both call the same measure(double)
    measure(k); // same function - Meters and Kilograms are just double

    std::cout << "\n=== Pitfall 3: const on value params ===\n";
    process(42);
    // Only one process(int) exists; const int version would be identical.

    std::cout << "\n=== Pitfall 4: Mismatched types with single-type template ===\n";
    // maxSingle(2, 3.5);  // Would fail
    std::cout << "maxSingle<double>(2, 3.5) = " << maxSingle<double>(2, 3.5) << '\n';
    std::cout << "maxSingle(2, static_cast<int>(3.5)) = "
              << maxSingle(2, static_cast<int>(3.5)) << '\n';

    std::cout << "\n=== Pitfall 5: No conversion during deduction ===\n";
    std::cout << "doubleIt(3.14f)           = " << doubleIt(3.14f) << '\n';         // float
    std::cout << "doubleIt<double>(3.14f)   = " << doubleIt<double>(3.14f) << '\n'; // double

    std::cout << "\n=== Pitfall 6: Deleted function still participates ===\n";
    onlyDouble(3.14);
    // onlyDouble(5);  // ERROR: calls deleted function - not "no match"

    std::cout << "\n=== Pitfall 7: Default arguments - omit from right only ===\n";
    printFormatted("Hello");          // width=10, fill='.'
    printFormatted("Hello", 15);      // fill='.'
    printFormatted("Hello", 15, '*'); // all specified
    // printFormatted("Hello", , '*');     // INVALID syntax

    std::cout << "\n=== Pitfall 8: Static locals per instantiation ===\n";
    std::cout << "countCalls<int>()    #" << countCalls<int>() << '\n';    // 1
    std::cout << "countCalls<int>()    #" << countCalls<int>() << '\n';    // 2
    std::cout << "countCalls<double>() #" << countCalls<double>() << '\n'; // 1 (separate!)
    std::cout << "countCalls<int>()    #" << countCalls<int>() << '\n';    // 3
    std::cout << "countCalls<double>() #" << countCalls<double>() << '\n'; // 2

    return 0;
}
