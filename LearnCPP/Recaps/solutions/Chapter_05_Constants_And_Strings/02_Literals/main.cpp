// Chapter 5 - Project 02: Literals
// =================================
// Topics:
//   - Every literal has a default type
//   - Type suffixes (f, L, u, etc.)
//   - C-style string literals
//   - Float/double narrowing pitfall with suffixes
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>

int main()
{
    // -------------------------------------------------------
    // 1. Default types of literals
    // -------------------------------------------------------
    // Integer literals default to int:
    std::cout << "=== Default Literal Types ===\n";
    std::cout << "5       is an int\n";
    std::cout << "3.14    is a double (NOT float!)\n";
    std::cout << "'a'     is a char\n";
    std::cout << "true    is a bool\n";
    std::cout << "\"hello\" is a const char[6] (C-style string)\n\n";

    // -------------------------------------------------------
    // 2. Suffixes change the literal's type
    // -------------------------------------------------------
    // Use suffixes to specify a different type than the default.

    auto intLiteral = 5;        // int (default)
    auto unsignedLit = 5u;      // unsigned int
    auto longLit = 5L;          // long
    auto longLongLit = 5LL;     // long long
    auto floatLit = 3.14f;      // float  (without 'f', it would be double)
    auto longDoubleLit = 3.14L; // long double

    std::cout << "=== Suffix Examples ===\n";
    std::cout << "5u   -> unsigned int:  " << unsignedLit << '\n';
    std::cout << "5L   -> long:          " << longLit << '\n';
    std::cout << "5LL  -> long long:     " << longLongLit << '\n';
    std::cout << "3.14f -> float:        " << floatLit << '\n';
    std::cout << "3.14L -> long double:  " << longDoubleLit << '\n';

    // -------------------------------------------------------
    // 3. The float narrowing pitfall
    // -------------------------------------------------------
    // float f { 4.1 };  // WARNING: 4.1 is double, narrowing to float
    float f{4.1f}; // OK: 4.1f is already a float - no narrowing

    std::cout << "\n=== Float Suffix ===\n";
    std::cout << "float f{ 4.1f } = " << f << "  (use 'f' suffix to avoid warnings)\n";

    // -------------------------------------------------------
    // 4. C-style string literals
    // -------------------------------------------------------
    // "hello" creates a const char[6] - 5 characters + null terminator '\0'
    // C-style string literals exist for the entire lifetime of the program.
    const char *greeting = "Hello, World!";
    std::cout << "\n=== C-Style String Literal ===\n";
    std::cout << greeting << '\n';

    // -------------------------------------------------------
    // 5. Boolean and character literals
    // -------------------------------------------------------
    bool isTrue = true;   // bool literal
    bool isFalse = false; // bool literal
    char letter = 'Z';    // char literal

    std::cout << "\n=== Bool & Char Literals ===\n";
    std::cout << std::boolalpha;
    std::cout << "true:  " << isTrue << '\n';
    std::cout << "false: " << isFalse << '\n';
    std::cout << "char:  " << letter << '\n';

    return 0;
}
