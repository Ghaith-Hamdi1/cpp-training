// Chapter 11 - Project 03: Function Overload Resolution
// ================================================================
// The compiler resolves overloaded function calls in a prioritized sequence:
//
//   1. Exact match (including trivial conversions like array-to-pointer)
//   2. Numeric promotion (e.g. char/short → int, float → double)
//   3. Numeric conversion (e.g. int → double, double → int)
//   4. User-defined conversion (e.g. conversion operators, converting ctors)
//   5. Ellipsis match (...)
//
// The compiler picks the FIRST step where a unique best match exists.

#include <iostream>

// --- Step 1: Exact match ---
void step(int x) { std::cout << "step(int): " << x << '\n'; }
void step(double x) { std::cout << "step(double): " << x << '\n'; }

// --- Step 2: Numeric promotion demo ---
// char and short are promoted to int; float is promoted to double.
void promote(int x) { std::cout << "promote(int): " << x << '\n'; }
void promote(double x) { std::cout << "promote(double): " << x << '\n'; }

// --- Step 3: Numeric conversion demo ---
// Only a long long overload exists - int can convert to long long.
void convert(long long x) { std::cout << "convert(long long): " << x << '\n'; }

// --- Step 4: User-defined conversion demo ---
struct Meters
{
    double value{};
    // Allow implicit conversion from double via converting constructor
    Meters(double v) : value{v} {}
};

void measure(Meters m) { std::cout << "measure(Meters): " << m.value << " m\n"; }

// --- Step 5: Ellipsis match demo ---
// The ellipsis (...) matches anything but is the lowest priority.
void catchAll(...) { std::cout << "catchAll(...): matched via ellipsis\n"; }

int main()
{
    std::cout << "=== Step 1: Exact match ===\n";
    step(5);    // exact match: step(int)
    step(3.14); // exact match: step(double)

    std::cout << "\n=== Step 2: Numeric promotion ===\n";
    promote('A');   // char → int (promotion) → promote(int)
    promote(3.14f); // float → double (promotion) → promote(double)
    short s{10};
    promote(s); // short → int (promotion) → promote(int)

    std::cout << "\n=== Step 3: Numeric conversion ===\n";
    convert(42); // int → long long (conversion) → convert(long long)

    std::cout << "\n=== Step 4: User-defined conversion ===\n";
    measure(9.81); // double → Meters (user-defined ctor) → measure(Meters)

    std::cout << "\n=== Step 5: Ellipsis match ===\n";
    catchAll(1, 2, "hi"); // anything matches ellipsis

    // Key takeaway: the compiler tries each step in order and stops
    // as soon as it finds exactly one best match at that step.

    return 0;
}
