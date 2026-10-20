// Chapter 5 - Project 01: Const Variables (Named Constants)
// =========================================================
// Topics:
//   - Declaring variables with the 'const' keyword
//   - const variables must be initialized at declaration
//   - const prevents reassignment
//   - Why const is preferred over #define macros
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>

int main()
{
    // -------------------------------------------------------
    // 1. Declaring const variables
    // -------------------------------------------------------
    // A const variable's value cannot be changed after initialization.
    const int daysInWeek{7};
    const double pi{3.14159265358979};

    std::cout << "Days in a week: " << daysInWeek << '\n';
    std::cout << "Pi: " << pi << '\n';

    // Uncommenting the next line would cause a compiler error:
    // daysInWeek = 8;  // ERROR: assignment of read-only variable

    // -------------------------------------------------------
    // 2. const variables MUST be initialized
    // -------------------------------------------------------
    // Uncommenting the next line would cause a compiler error:
    // const int uninitializedConst;  // ERROR: uninitialized const

    // -------------------------------------------------------
    // 3. Runtime const - value determined at runtime
    // -------------------------------------------------------
    // const does NOT mean "compile-time constant". It means
    // "cannot be modified after initialization."
    // A const variable can be initialized with a runtime value.
    std::cout << "\nEnter your age: ";
    int inputAge{};
    std::cin >> inputAge;

    const int userAge{inputAge}; // runtime const - perfectly valid
    std::cout << "Your age (const): " << userAge << '\n';

    // userAge = 30;  // ERROR: still cannot reassign a const variable

    // -------------------------------------------------------
    // 4. Why const is better than #define
    // -------------------------------------------------------
    // Bad (macro):
    //   #define MAX_STUDENTS 30
    //
    // Good (const variable):
    const int maxStudents{30};

    // Advantages of const over #define:
    //   - const respects scope (block, function, namespace)
    //   - const is visible to the debugger
    //   - const has a proper type, so the compiler can type-check
    //   - #define is a text substitution - can cause confusing errors

    std::cout << "\nMax students (const): " << maxStudents << '\n';

    // -------------------------------------------------------
    // 5. Don't use const on by-value parameters or return types
    // -------------------------------------------------------
    // The following is legal but unnecessary and misleading:
    //   void printValue(const int value) { ... }
    // The caller doesn't care whether the function's copy is const.
    // Best practice: omit const for by-value parameters.

    std::cout << "\nKey takeaway: Use 'const' for any variable whose value\n"
              << "should not change after initialization.\n";

    return 0;
}
