// Chapter 4 - Project 03: Object Sizes and the sizeof Operator
// =============================================================
// Key concept: sizeof returns the size of a type or variable in bytes.
// The C++ standard only guarantees MINIMUM sizes for types:
//   - short:     at least 16 bits (2 bytes)
//   - int:       at least 16 bits (2 bytes), usually 32 bits
//   - long:      at least 32 bits (4 bytes)
//   - long long: at least 64 bits (8 bytes)
//
// Pitfall: Never assume int is always 32 bits - the standard only
// guarantees a minimum of 16 bits.

#include <iostream>

int main()
{
    std::cout << "=== sizeof Operator ===\n\n";

    // sizeof with types
    std::cout << "--- Sizes of fundamental types (in bytes) ---\n";
    std::cout << "bool:        " << sizeof(bool) << " byte(s)\n";
    std::cout << "char:        " << sizeof(char) << " byte(s)\n"; // Always 1
    std::cout << "short:       " << sizeof(short) << " byte(s)\n";
    std::cout << "int:         " << sizeof(int) << " byte(s)\n";
    std::cout << "long:        " << sizeof(long) << " byte(s)\n";
    std::cout << "long long:   " << sizeof(long long) << " byte(s)\n";
    std::cout << "float:       " << sizeof(float) << " byte(s)\n";
    std::cout << "double:      " << sizeof(double) << " byte(s)\n";
    std::cout << "long double: " << sizeof(long double) << " byte(s)\n";

    std::cout << '\n';

    // sizeof with variables
    int x{42};
    double y{3.14};
    char c{'A'};

    std::cout << "--- sizeof with variables ---\n";
    std::cout << "sizeof(x) [int]:    " << sizeof(x) << " byte(s)\n";
    std::cout << "sizeof(y) [double]: " << sizeof(y) << " byte(s)\n";
    std::cout << "sizeof(c) [char]:   " << sizeof(c) << " byte(s)\n";

    std::cout << '\n';

    // sizeof is a compile-time operation - it does NOT evaluate the expression
    int a{5};
    std::cout << "--- sizeof does NOT evaluate its operand ---\n";
    std::cout << "a before sizeof: " << a << '\n';
    std::cout << "sizeof(++a):     " << sizeof(++a) << '\n';
    std::cout << "a after sizeof:  " << a << " (unchanged! sizeof doesn't evaluate)\n";

    return 0;
}
