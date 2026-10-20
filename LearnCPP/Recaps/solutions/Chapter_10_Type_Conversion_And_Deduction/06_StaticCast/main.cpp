// Chapter 10 - Project 06: Explicit Type Conversion with static_cast
//
// C++ provides five cast types:
//   static_cast   - compile-time checked, safe, most commonly used
//   dynamic_cast  - runtime checked, for polymorphic types
//   const_cast    - removes/adds const (avoid unless absolutely necessary)
//   reinterpret_cast - reinterprets bit patterns (dangerous, rarely needed)
//   C-style cast  - (type)value - avoid! can silently do dangerous things
//
// BEST PRACTICE: Use static_cast for all explicit type conversions.
// It performs compile-time type checking and makes intent clear.

#include <iostream>

int main()
{
    // =============================================================
    // 1. static_cast for numeric conversions
    // =============================================================
    std::cout << "=== static_cast for numeric conversions ===\n";

    // double -> int (intentional truncation)
    double pi{3.14159};
    int intPi{static_cast<int>(pi)};
    std::cout << "  static_cast<int>(3.14159) = " << intPi << '\n';

    // int -> double (for floating-point division)
    int a{7};
    int b{2};
    double divResult{static_cast<double>(a) / b};
    std::cout << "  static_cast<double>(7) / 2 = " << divResult << '\n';

    // int -> char
    int charCode{65};
    char ch{static_cast<char>(charCode)};
    std::cout << "  static_cast<char>(65) = '" << ch << "'\n";

    // =============================================================
    // 2. static_cast to suppress narrowing warnings
    // =============================================================
    std::cout << "\n=== Suppressing narrowing warnings ===\n";

    double largeVal{99.7};
    // Without static_cast, assigning double to int would warn
    int truncated{static_cast<int>(largeVal)};
    std::cout << "  Intentional truncation: " << truncated << '\n';

    // =============================================================
    // 3. static_cast with char/int conversions
    // =============================================================
    std::cout << "\n=== char <-> int conversions ===\n";

    char letter{'A'};
    // Print the numeric value of a char
    std::cout << "  'A' as int: " << static_cast<int>(letter) << '\n';

    // Convert int back to char
    int code{90};
    std::cout << "  90 as char: '" << static_cast<char>(code) << "'\n";

    // Get a char from user input and show its numeric value
    std::cout << "  All uppercase letters:\n  ";
    for (char c{'A'}; c <= 'Z'; ++c)
    {
        std::cout << c << '(' << static_cast<int>(c) << ") ";
    }
    std::cout << '\n';

    // =============================================================
    // 4. static_cast for unsigned/signed conversions
    // =============================================================
    std::cout << "\n=== Unsigned <-> signed conversions ===\n";

    unsigned int u{4000000000u};
    // Make the conversion explicit so it's clear this is intentional
    int s{static_cast<int>(u)};
    std::cout << "  unsigned 4000000000 -> signed: " << s << '\n';

    int neg{-42};
    unsigned int uNeg{static_cast<unsigned int>(neg)};
    std::cout << "  signed -42 -> unsigned: " << uNeg << '\n';

    // =============================================================
    // 5. static_cast catches invalid conversions at compile time
    // =============================================================
    std::cout << "\n=== static_cast provides compile-time safety ===\n";

    // These would be compile errors (unlike C-style casts which may succeed):
    // int* ptr{ static_cast<int*>("hello") };     // Error: can't convert string to int*
    // int x{ static_cast<int>(ptr) };              // Error: can't convert pointer to int

    std::cout << "  static_cast prevents dangerous conversions at compile time.\n";
    std::cout << "  C-style casts might silently allow them!\n";

    return 0;
}
