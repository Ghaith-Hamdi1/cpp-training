// Chapter 1 - Project 07: Keywords and Naming Identifiers
// ==========================================================
//
// KEY CONCEPTS:
//   - C++ reserves 92+ **keywords** (as of C++23) that cannot be used as identifiers.
//     Examples: int, double, return, if, else, while, for, class, void, etc.
//   - An **identifier** is the name you give to a variable, function, type, etc.
//
// IDENTIFIER NAMING RULES:
//   1. Cannot be a keyword (e.g., you can't name a variable "int" or "void").
//   2. Can only contain letters (a-z, A-Z), digits (0-9), and underscores (_).
//   3. Must begin with a letter or underscore (NOT a digit).
//   4. C++ is case-sensitive: myVar, MyVar, and MYVAR are all different.
//
// BEST PRACTICES:
//   - Start variable/function names with a lowercase letter.
//   - Use camelCase or snake_case consistently (pick one style).
//   - Make names descriptive; length should be proportional to scope.
//   - Avoid starting with an underscore (reserved for compiler/OS internals).

#include <iostream>

int main()
{
    // =====================================================================
    // VALID identifiers
    // =====================================================================

    int age{25};           // Starts with lowercase letter - good
    int studentCount{30};  // camelCase - good
    int student_count{30}; // snake_case - also good
    int numberOfItems{10}; // Descriptive name - good
    int x{1};              // Short name - OK for small scopes (e.g., loop vars)
    int _internal{0};      // Starts with underscore - technically valid but discouraged

    std::cout << "Valid identifiers:\n";
    std::cout << "  age = " << age << '\n';
    std::cout << "  studentCount = " << studentCount << '\n';
    std::cout << "  student_count = " << student_count << '\n';
    std::cout << "  numberOfItems = " << numberOfItems << '\n';
    std::cout << "  x = " << x << '\n';
    std::cout << "  _internal = " << _internal << '\n';

    // =====================================================================
    // INVALID identifiers (would cause compile errors if uncommented)
    // =====================================================================

    std::cout << "\nInvalid identifiers (would not compile):\n";

    // int void{};       // ERROR: 'void' is a keyword
    std::cout << "  int void{};       // 'void' is a keyword\n";

    // int 2ndPlace{};   // ERROR: starts with a digit
    std::cout << "  int 2ndPlace{};   // starts with a digit\n";

    // int my-var{};     // ERROR: hyphens are not allowed
    std::cout << "  int my-var{};     // hyphens not allowed\n";

    // int my var{};     // ERROR: spaces are not allowed
    std::cout << "  int my var{};     // spaces not allowed\n";

    // int class{};      // ERROR: 'class' is a keyword
    std::cout << "  int class{};      // 'class' is a keyword\n";

    // =====================================================================
    // Case sensitivity
    // =====================================================================

    int myValue{10};
    int MyValue{20}; // Different variable! C++ is case-sensitive.
    int MYVALUE{30}; // Yet another different variable.

    std::cout << "\nCase sensitivity:\n";
    std::cout << "  myValue = " << myValue << '\n';
    std::cout << "  MyValue = " << MyValue << '\n';
    std::cout << "  MYVALUE = " << MYVALUE << '\n';

    // =====================================================================
    // Naming best practices
    // =====================================================================

    std::cout << "\n--- Naming Best Practices ---\n";
    std::cout << "1. Start with lowercase: userAge, totalScore\n";
    std::cout << "2. Be descriptive: 'numberOfStudents' > 'n'\n";
    std::cout << "3. Pick camelCase OR snake_case - be consistent\n";
    std::cout << "4. Longer names for wider scope, short names for tight loops\n";
    std::cout << "5. Avoid starting with _ (reserved for implementation)\n";

    return 0;
}
