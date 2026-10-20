// Chapter 5 - Project 13: Common Pitfalls
// ==========================================
// Topics:
//   - float/double narrowing warning
//   - Accidental octal with leading 0
//   - Assuming const double is a constant expression
//   - Forgetting to initialize const
//   - Using #define instead of const/constexpr
//   - Passing std::string by value instead of string_view
//   - Forgetting std::ws with std::getline
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <string>
#include <string_view>

// -------------------------------------------------------
// PITFALL 5 DEMO: Passing std::string by value (expensive)
// -------------------------------------------------------
// BAD: copies the entire string
void printBad(std::string text)
{
    std::cout << "  [by value]       " << text << '\n';
}

// GOOD: no copy, accepts string, string_view, and C-style strings
void printGood(std::string_view text)
{
    std::cout << "  [by string_view] " << text << '\n';
}

int main()
{
    std::cout << "=== Chapter 5: Common Pitfalls ===\n\n";

    // -------------------------------------------------------
    // PITFALL 1: float/double narrowing
    // -------------------------------------------------------
    std::cout << "--- Pitfall 1: float/double narrowing ---\n";

    // BAD: 4.1 is a double literal - narrowing to float!
    // float bad { 4.1 };  // WARNING: narrowing conversion from double to float

    // GOOD: use 'f' suffix to make it a float literal
    float good{4.1f}; // No warning - 4.1f is already float
    std::cout << "  float good{ 4.1f } = " << good << "  // use 'f' suffix!\n";

    // ALSO GOOD: just use double
    double alsoGood{4.1}; // No narrowing - 4.1 is already double
    std::cout << "  double alsoGood{ 4.1 } = " << alsoGood << "  // or use double\n\n";

    // -------------------------------------------------------
    // PITFALL 2: Accidental octal
    // -------------------------------------------------------
    std::cout << "--- Pitfall 2: Accidental octal ---\n";

    int notTen = 010; // This is OCTAL 10 = DECIMAL 8!
    int ten = 10;     // This is decimal 10.

    std::cout << "  010 (octal) = " << notTen << " (decimal) - NOT 10!\n";
    std::cout << "  10  (decimal) = " << ten << "\n";
    std::cout << "  Lesson: A leading 0 makes the number octal.\n\n";

    // -------------------------------------------------------
    // PITFALL 3: const double is NOT a constant expression
    // -------------------------------------------------------
    std::cout << "--- Pitfall 3: const double != constant expression ---\n";

    const int constInt = 42;      // IS a constant expression (const integral)
    const double constDbl = 3.14; // NOT a constant expression (non-integral)

    // constInt can be used in contexts requiring a constant expression:
    int arr[constInt]{}; // OK

    // constDbl CANNOT reliably be used where constant expressions are required.
    // For double constants, use constexpr:
    constexpr double constexprDbl = 3.14; // IS a constant expression

    std::cout << "  const int = " << constInt << "       -> constant expression (integral)\n";
    std::cout << "  const double = " << constDbl << "   -> NOT a constant expression\n";
    std::cout << "  constexpr double = " << constexprDbl << " -> IS a constant expression\n";
    std::cout << "  Fix: use constexpr for non-integral compile-time constants.\n\n";

    // -------------------------------------------------------
    // PITFALL 4: Forgetting to initialize const
    // -------------------------------------------------------
    std::cout << "--- Pitfall 4: Uninitialized const ---\n";

    // const int x;  // COMPILE ERROR: const must be initialized
    std::cout << "  const int x;  // ERROR: const variables MUST be initialized.\n";
    std::cout << "  const int x{ 5 };  // Correct.\n\n";

    // -------------------------------------------------------
    // PITFALL 5: Passing std::string by value
    // -------------------------------------------------------
    std::cout << "--- Pitfall 5: std::string by value vs string_view ---\n";

    std::string message{"Hello from a long string"};

    printBad(message);  // Makes an expensive copy
    printGood(message); // No copy - just a view

    std::cout << "  Use std::string_view for read-only string parameters.\n\n";

    // -------------------------------------------------------
    // PITFALL 6: Using #define for constants
    // -------------------------------------------------------
    std::cout << "--- Pitfall 6: #define vs const/constexpr ---\n";

    // BAD:
    // #define MAX_SIZE 100
    // - No type checking
    // - No scoping
    // - Invisible to debugger
    // - Text substitution can cause subtle bugs

    // GOOD:
    constexpr int maxSize{100};

    std::cout << "  #define MAX_SIZE 100    // BAD: no type, no scope\n";
    std::cout << "  constexpr int maxSize{ 100 };  // GOOD: typed, scoped, debuggable\n";
    std::cout << "  maxSize = " << maxSize << '\n';

    // -------------------------------------------------------
    // PITFALL 7: Forgetting std::ws with std::getline
    // -------------------------------------------------------
    std::cout << "\n--- Pitfall 7: std::ws with std::getline ---\n";

    std::cout << "  After std::cin >>, a leftover '\\n' stays in the buffer.\n";
    std::cout << "  std::getline() picks it up and returns an empty string.\n";
    std::cout << "  Fix: std::getline(std::cin >> std::ws, str);\n";
    std::cout << "  std::ws discards leading whitespace including the '\\n'.\n";

    // -------------------------------------------------------
    // Summary
    // -------------------------------------------------------
    std::cout << "\n=== Summary of Pitfalls ===\n";
    std::cout << "1. Use 'f' suffix for float literals: 4.1f\n";
    std::cout << "2. Don't prefix decimal numbers with 0 (octal).\n";
    std::cout << "3. Use constexpr (not const) for non-integral compile-time constants.\n";
    std::cout << "4. Always initialize const/constexpr variables.\n";
    std::cout << "5. Pass std::string_view, not std::string, for read-only params.\n";
    std::cout << "6. Use const/constexpr, not #define, for named constants.\n";
    std::cout << "7. Use std::getline(std::cin >> std::ws, str) for line input.\n";

    return 0;
}
