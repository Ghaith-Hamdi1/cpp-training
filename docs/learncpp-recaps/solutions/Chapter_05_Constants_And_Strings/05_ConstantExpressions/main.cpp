// Chapter 5 - Project 05: Constant Expressions
// ===============================================
// Topics:
//   - What qualifies as a constant expression
//   - const integral types with constant-expression initializers
//   - const non-integral types do NOT qualify as constant expressions
//   - Where constant expressions are required
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>

int main()
{
    // -------------------------------------------------------
    // 1. What is a constant expression?
    // -------------------------------------------------------
    // A constant expression is an expression that can be fully
    // evaluated at compile-time. Every operand must be known
    // at compile-time.

    std::cout << "=== Constant Expressions ===\n";

    // These are constant expressions (all parts are compile-time known):
    // 5
    // 2 + 3
    // 1 + 2 * 3

    std::cout << "5, 2+3, 1+2*3 are all constant expressions.\n";

    // -------------------------------------------------------
    // 2. const integral variables CAN be constant expressions
    // -------------------------------------------------------
    // A const variable of integral type (int, char, bool, etc.)
    // initialized with a constant expression is itself usable
    // as a constant expression.

    const int maxSize = 100;         // const int + constant expression initializer
    const int doubled = maxSize * 2; // Also a constant expression

    // Can be used where a constant expression is required:
    int arr1[maxSize]{}; // Array size must be a constant expression - OK
    int arr2[doubled]{}; // Also OK

    std::cout << "\nconst int maxSize = 100;  // usable as constant expression\n";
    std::cout << "const int doubled = maxSize * 2;  // also constant expression\n";
    std::cout << "int arr1[maxSize] - compiles because maxSize is a constant expression.\n";

    // -------------------------------------------------------
    // 3. const non-integral types are NOT constant expressions
    // -------------------------------------------------------
    // IMPORTANT: const double, const float, etc. do NOT qualify
    // as constant expressions, even with a literal initializer.

    const double pi = 3.14159; // NOT a constant expression (non-integral type)

    // This would NOT compile if a constant expression were required:
    // int arr3[static_cast<int>(pi)]{};  // May or may not compile depending on context

    std::cout << "\nconst double pi = 3.14;  // NOT a constant expression!\n";
    std::cout << "Only const INTEGRAL types qualify. For non-integral, use constexpr.\n";

    // -------------------------------------------------------
    // 4. Non-const variables are never constant expressions
    // -------------------------------------------------------
    int x = 5;
    // Even though 5 is a constant expression, x is not const,
    // so x itself is not a constant expression.

    // int arr4[x]{};  // ERROR on strict compilers: x is not a constant expression

    std::cout << "\nint x = 5;  // x is NOT a constant expression (not const)\n";

    // -------------------------------------------------------
    // 5. Runtime values cannot form constant expressions
    // -------------------------------------------------------
    std::cout << "\nEnter a number: ";
    int input{};
    std::cin >> input;

    const int runtimeConst = input; // const, but initialized with runtime value
    // runtimeConst is NOT a constant expression because 'input' is unknown at compile-time.

    // int arr5[runtimeConst]{};  // ERROR: runtimeConst is not a constant expression

    std::cout << "const int runtimeConst = " << runtimeConst << ";\n";
    std::cout << "This is const but NOT a constant expression (runtime initializer).\n";

    // -------------------------------------------------------
    // Summary
    // -------------------------------------------------------
    std::cout << "\n=== Summary ===\n";
    std::cout << "Constant expression = every part is compile-time evaluable.\n";
    std::cout << "const int with const-expr initializer  -> IS a constant expression.\n";
    std::cout << "const double with literal initializer   -> NOT a constant expression.\n";
    std::cout << "const int with runtime initializer      -> NOT a constant expression.\n";
    std::cout << "For guaranteed compile-time constants, use constexpr (next project).\n";

    return 0;
}
