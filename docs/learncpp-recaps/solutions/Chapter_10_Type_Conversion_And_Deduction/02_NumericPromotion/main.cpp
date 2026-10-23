// Chapter 10 - Project 02: Numeric Promotion
//
// Numeric promotions are VALUE-PRESERVING conversions of narrow types
// to wider types so the CPU can operate on them efficiently.
//
// Two categories:
//   1. Floating-point promotion: float -> double
//   2. Integral promotion: bool, char, short (and variants) -> int (or unsigned int)
//
// IMPORTANT: Not all widenings are promotions!
//   - float -> double  IS a promotion
//   - int -> long       is a numeric CONVERSION, not a promotion
// This distinction matters for function overload resolution.

#include <iostream>

void printInt(int value)
{
    std::cout << "  printInt: " << value << '\n';
}

void printDouble(double value)
{
    std::cout << "  printDouble: " << value << '\n';
}

int main()
{
    std::cout << "=== Floating-point promotion ===\n";

    // float is promoted to double when passed to a function expecting double
    float f{3.14f};
    printDouble(f); // float -> double (promotion, value-preserving)

    // float is promoted to double in arithmetic with a double operand
    double d{1.0};
    double result{d + f}; // f promoted to double before addition
    std::cout << "  1.0 + 3.14f = " << result << '\n';

    std::cout << "\n=== Integral promotion ===\n";

    // bool -> int: false=0, true=1
    bool b{true};
    printInt(b); // bool -> int (promotion)

    // char -> int
    char c{'A'};
    printInt(c); // char -> int (promotion), prints 65

    // short -> int
    short s{100};
    printInt(s); // short -> int (promotion)

    // unsigned char -> int
    unsigned char uc{200};
    printInt(uc); // unsigned char -> int (promotion)

    std::cout << "\n=== Promotion in expressions ===\n";

    // In expressions, narrow types are promoted BEFORE the operation
    char c1{10};
    char c2{20};
    // c1 and c2 are both promoted to int, then added as ints
    // The result is an int, not a char
    auto sum{c1 + c2}; // sum is int, not char
    std::cout << "  char 10 + char 20 = " << sum
              << " (type is int, not char)\n";

    std::cout << "\n=== NOT a promotion (numeric conversion) ===\n";

    // int -> long is a numeric conversion, NOT a promotion
    int i{42};
    long l{i}; // This is a numeric conversion (widening, but not a promotion)
    std::cout << "  int -> long: " << l << " (conversion, not promotion)\n";

    // int -> double is also a numeric conversion, not a promotion
    double d2{i};
    std::cout << "  int -> double: " << d2 << " (conversion, not promotion)\n";

    return 0;
}
