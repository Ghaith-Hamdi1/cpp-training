// Chapter 10 - Project 12: Common Pitfalls Roundup
//
// This project collects several common pitfalls from Chapter 10
// in one place for quick reference:
//
//   1. Integer division surprise
//   2. Forgetting const with auto
//   3. String literal type with auto
//   4. Assuming all widenings are promotions
//   5. Narrowing in brace init without noticing
//   6. Auto return types with forward declarations
//   7. Thinking type aliases create new types

#include <iostream>
#include <string>
#include <string_view>
#include <typeinfo>

using namespace std::string_literals;

// For pitfall 6: auto return type can't be forward-declared
// auto forwardDeclaredAutoReturn(int x);  // Can't use before definition!

// Must define fully before calling:
auto computeSquare(int x)
{
    return x * x;
}

int main()
{
    // =============================================================
    // PITFALL 1: Integer division surprise
    // =============================================================
    std::cout << "=== Pitfall 1: Integer division ===\n";

    // 10 / 4 is 2, not 2.5 - both operands are int!
    std::cout << "  10 / 4 = " << (10 / 4) << " (not 2.5!)\n";

    // Fix: cast one operand to double
    std::cout << "  static_cast<double>(10) / 4 = "
              << (static_cast<double>(10) / 4) << " (correct!)\n";

    // Another fix: make one operand a literal double
    std::cout << "  10.0 / 4 = " << (10.0 / 4) << " (correct!)\n";

    // =============================================================
    // PITFALL 2: auto drops const
    // =============================================================
    std::cout << "\n=== Pitfall 2: auto drops const ===\n";

    const int maxSize{100};
    auto copy{maxSize}; // deduces to int, NOT const int!
    copy = 999;         // compiles! copy is mutable
    std::cout << "  const int maxSize{100};\n";
    std::cout << "  auto copy{maxSize}; // type is int, not const int\n";
    std::cout << "  copy = 999; // compiles! copy is now " << copy << '\n';

    // Fix: use const auto
    const auto safeCopy{maxSize};
    // safeCopy = 999;        // won't compile - safeCopy is const
    std::cout << "  const auto safeCopy{maxSize}; // correctly const\n";

    // =============================================================
    // PITFALL 3: String literal deduces to const char*
    // =============================================================
    std::cout << "\n=== Pitfall 3: String literal type ===\n";

    auto s1{"hello"};  // const char* - NOT std::string!
    auto s2{"hello"s}; // std::string (using s suffix)

    // s1 is const char* - can't use string methods directly
    std::cout << "  auto{\"hello\"} -> type: const char*\n";
    std::cout << "  auto{\"hello\"s} -> type: std::string\n";
    std::cout << "  Use \"...\"s suffix for std::string deduction\n";

    // =============================================================
    // PITFALL 4: Not all widenings are promotions
    // =============================================================
    std::cout << "\n=== Pitfall 4: Widenings vs promotions ===\n";

    // Promotions (to int or double):
    //   char -> int     ✓ promotion
    //   short -> int    ✓ promotion
    //   float -> double ✓ promotion
    //
    // NOT promotions (numeric conversions):
    //   int -> long     ✗ widening conversion, NOT a promotion
    //   int -> double   ✗ widening conversion, NOT a promotion

    std::cout << "  char -> int:    PROMOTION (value-preserving)\n";
    std::cout << "  int -> long:    CONVERSION (widening, but not a promotion)\n";
    std::cout << "  int -> double:  CONVERSION (widening, but not a promotion)\n";
    std::cout << "  This distinction matters for function overload resolution!\n";

    // =============================================================
    // PITFALL 5: Narrowing in brace init
    // =============================================================
    std::cout << "\n=== Pitfall 5: Narrowing in brace init ===\n";

    // int x{ 3.5 };   // ERROR! Brace init catches this
    // int y{ 3.0 };   // ERROR! float-to-int is ALWAYS narrowing

    // Non-brace init silently truncates:
    int silent = 3.9; // Compiles with = (silently becomes 3)
    std::cout << "  int x = 3.9; // silently truncates to " << silent << '\n';
    std::cout << "  int x{ 3.9 }; // compile error! (brace init catches it)\n";

    // Fix: use static_cast when narrowing is intentional
    int intentional{static_cast<int>(3.9)};
    std::cout << "  int x{ static_cast<int>(3.9) }; // explicit: " << intentional << '\n';

    // =============================================================
    // PITFALL 6: auto return type forward declaration
    // =============================================================
    std::cout << "\n=== Pitfall 6: auto return + forward declaration ===\n";

    // A function with auto return type must be DEFINED before it's called
    // Forward declarations don't provide enough info for the compiler
    std::cout << "  computeSquare(7) = " << computeSquare(7) << '\n';
    std::cout << "  (Function must be defined before use, can't just forward-declare)\n";

    // =============================================================
    // PITFALL 7: Type aliases don't create new types
    // =============================================================
    std::cout << "\n=== Pitfall 7: Type aliases are not distinct types ===\n";

    using Meters = double;
    using Seconds = double;
    using Speed = double;

    Meters distance{100.0};
    Seconds time{10.0};
    Speed velocity{distance / time};

    // But we can assign anything to anything - no type safety!
    distance = velocity; // Meters = Speed compiles fine!
    time = distance;     // Seconds = Meters compiles fine!

    std::cout << "  using Meters = double; using Seconds = double;\n";
    std::cout << "  Meters = Speed; // compiles! No type checking.\n";
    std::cout << "  Type aliases are just convenient names, not new types.\n";

    return 0;
}
