// Chapter 5 - Project 06: Constexpr Variables
// ==============================================
// Topics:
//   - constexpr guarantees a compile-time constant
//   - constexpr works with non-integral types (double, float)
//   - constexpr variables are implicitly const
//   - constexpr vs const - when to use which
//   - Function parameters cannot be constexpr
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>

int main()
{
    // -------------------------------------------------------
    // 1. constexpr = compile-time constant guarantee
    // -------------------------------------------------------
    // constexpr tells the compiler: "This variable's initializer
    // MUST be a constant expression. If it's not, give me an error."

    constexpr int maxItems{50};
    constexpr int doubleMax{maxItems * 2}; // OK: maxItems is constexpr

    std::cout << "=== constexpr Variables ===\n";
    std::cout << "constexpr int maxItems   = " << maxItems << '\n';
    std::cout << "constexpr int doubleMax  = " << doubleMax << '\n';

    // -------------------------------------------------------
    // 2. constexpr works with non-integral types
    // -------------------------------------------------------
    // Unlike const, constexpr makes non-integral types (double, float)
    // true compile-time constants.

    constexpr double pi{3.14159265358979};
    constexpr float gravity{9.81f};
    constexpr double circleArea{pi * 5.0 * 5.0}; // Computed at compile-time!

    std::cout << "\n=== constexpr with Non-Integral Types ===\n";
    std::cout << "constexpr double pi     = " << pi << '\n';
    std::cout << "constexpr float gravity = " << gravity << '\n';
    std::cout << "constexpr double area   = " << circleArea
              << " (pi * 5 * 5, computed at compile-time)\n";

    // Compare with const:
    // const double e = 2.71828;  // NOT a constant expression (const non-integral)
    // constexpr double e = 2.71828;  // IS a constant expression (constexpr)

    // -------------------------------------------------------
    // 3. constexpr variables are implicitly const
    // -------------------------------------------------------
    // You don't need to write 'const constexpr' - constexpr implies const.

    // constexpr int x{ 10 };
    // x = 20;  // ERROR: constexpr is implicitly const - cannot reassign

    std::cout << "\n=== constexpr is Implicitly const ===\n";
    std::cout << "constexpr int x{ 10 }; means x is also const.\n";
    std::cout << "Writing 'const constexpr' is redundant.\n";

    // -------------------------------------------------------
    // 4. constexpr requires a constant expression initializer
    // -------------------------------------------------------
    // If the initializer is not a constant expression, the compiler errors.

    // int runtimeValue{};
    // std::cin >> runtimeValue;
    // constexpr int bad{ runtimeValue };  // ERROR: initializer is not a constant expression

    std::cout << "\n=== constexpr Rejects Runtime Initializers ===\n";
    std::cout << "constexpr int bad{ runtimeValue };  // COMPILE ERROR\n";
    std::cout << "The compiler enforces that constexpr = compile-time known.\n";

    // -------------------------------------------------------
    // 5. When to use constexpr vs const
    // -------------------------------------------------------
    std::cout << "\n=== constexpr vs const ===\n";
    std::cout << "  constexpr: value is known at compile-time -> use constexpr\n";
    std::cout << "  const:     value is determined at runtime  -> use const\n\n";

    // Example:
    constexpr int compiletimeConst{42}; // Known at compile-time -> constexpr
    // const int runtimeConst{ getUserInput() };  // Known only at runtime -> const

    std::cout << "constexpr int compiletimeConst{ 42 };  // Best practice\n";
    std::cout << "const int runtimeConst{ input };        // const for runtime values\n";

    // -------------------------------------------------------
    // 6. Function parameters cannot be constexpr
    // -------------------------------------------------------
    std::cout << "\n=== No constexpr Parameters ===\n";
    std::cout << "void foo(constexpr int x);  // COMPILE ERROR\n";
    std::cout << "Function arguments are determined at runtime,\n";
    std::cout << "so they can't be constexpr.\n";

    return 0;
}
