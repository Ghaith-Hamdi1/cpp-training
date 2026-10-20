// Chapter 10 - Project 05: Usual Arithmetic Conversions
//
// When a binary operator has operands of different types, the compiler
// applies the "usual arithmetic conversions" to find a common type.
//
// Rule: the operand with the LOWER-ranked type is converted to the
// HIGHER-ranked type.
//
// Type ranking (low to high):
//   int < long < long long < float < double < long double
//
// WARNING: Mixing signed and unsigned types is dangerous!
// The signed value is converted to unsigned, which can cause
// unexpected wrapping for negative numbers.

#include <iostream>

int main()
{
    // =============================================================
    // 1. Basic arithmetic conversions
    // =============================================================
    std::cout << "=== Basic arithmetic conversions ===\n";

    // int + double -> both become double
    int i{5};
    double d{2.5};
    auto result1{i + d}; // i promoted to double, result is double
    std::cout << "  int 5 + double 2.5 = " << result1 << " (double)\n";

    // int + float -> both become float
    float f{1.5f};
    auto result2{i + f}; // i converted to float, result is float
    std::cout << "  int 5 + float 1.5 = " << result2 << " (float)\n";

    // int + long -> both become long
    long l{100L};
    auto result3{i + l}; // i converted to long, result is long
    std::cout << "  int 5 + long 100 = " << result3 << " (long)\n";

    // float + double -> both become double
    auto result4{f + d}; // f promoted to double, result is double
    std::cout << "  float 1.5 + double 2.5 = " << result4 << " (double)\n";

    // =============================================================
    // 2. Integer division vs floating-point division
    // =============================================================
    std::cout << "\n=== Integer vs floating-point division ===\n";

    // Both operands are int -> integer division (truncates)
    std::cout << "  10 / 4 = " << (10 / 4) << " (integer division!)\n";

    // If either operand is floating-point -> floating-point division
    std::cout << "  10.0 / 4 = " << (10.0 / 4) << " (double division)\n";
    std::cout << "  10 / 4.0 = " << (10 / 4.0) << " (double division)\n";

    // Using static_cast to force floating-point division
    int a{10};
    int b{4};
    double correctDiv{static_cast<double>(a) / b};
    std::cout << "  static_cast<double>(10) / 4 = " << correctDiv << '\n';

    // =============================================================
    // 3. Signed/unsigned mixing - DANGER ZONE
    // =============================================================
    std::cout << "\n=== Signed/unsigned mixing (DANGER!) ===\n";

    // When signed and unsigned are mixed, the signed value is
    // converted to unsigned. This causes problems with negative numbers.

    unsigned int u{5u};
    int s{-3};

    // -3 is converted to unsigned (wraps to a huge number), then compared
    // This comparison gives the WRONG result!
    if (s < static_cast<int>(u))
        std::cout << "  -3 < 5 is TRUE (correct, using static_cast)\n";

    // Demonstrate the wrapping
    unsigned int wrapped{static_cast<unsigned int>(s)};
    std::cout << "  -3 as unsigned int = " << wrapped << " (wrapped!)\n";

    // 5u - 10 wraps around because the result would be negative
    // but unsigned can't be negative
    unsigned int sub{5u - 10u};
    std::cout << "  5u - 10u = " << sub << " (unsigned wrap-around!)\n";

    // =============================================================
    // 4. Same-rank signed/unsigned resolution
    // =============================================================
    std::cout << "\n=== Same-rank signed/unsigned ===\n";

    // When signed and unsigned have the same rank, signed -> unsigned
    int si{-1};
    unsigned int ui{1u};
    // si is converted to unsigned before comparison!
    // -1 becomes 4294967295 (on 32-bit), which is > 1
    std::cout << "  -1 converted to unsigned: "
              << static_cast<unsigned int>(si) << '\n';
    std::cout << "  Lesson: avoid mixing signed and unsigned in arithmetic!\n";

    return 0;
}
