// Chapter 2 - Project 14: Common Pitfalls
// Concept: Frequent mistakes with functions, headers, and scope
//
// This file collects the most common errors from Chapter 2 and shows
// both the WRONG way (commented out) and the CORRECT way.  Each section
// is self-contained so you can study them independently.
// -----------------------------------------------------------------------

#include <iostream>

// -----------------------------------------------------------------------
// PITFALL 1: Forgetting parentheses on a function call
// -----------------------------------------------------------------------
void doPrint()
{
    std::cout << "doPrint() was called!\n";
}

// -----------------------------------------------------------------------
// PITFALL 2: Forgetting to return a value from a non-void function
// -----------------------------------------------------------------------
int getValueCorrect()
{
    return 42; // CORRECT: always return a value from a non-void function
}

// WRONG (undefined behavior - DO NOT use):
// int getValueBroken()
// {
//     // No return statement!  The caller receives garbage.  The compiler
//     // may warn but will NOT always error.
// }

// -----------------------------------------------------------------------
// PITFALL 3: Trying to use a void function's "return value"
// -----------------------------------------------------------------------
void printHi()
{
    std::cout << "Hi!\n";
}
// WRONG:  std::cout << printHi();  // ERROR: void cannot be sent to cout

// -----------------------------------------------------------------------
// PITFALL 5: Mismatched forward declaration and definition
// -----------------------------------------------------------------------
// Forward declaration says two ints:
int computeSum(int a, int b);

// Definition must match - same return type and parameter list.
int computeSum(int a, int b)
{
    return a + b;
}

// WRONG - if the forward declaration said:
//   double computeSum(int a);  // Different return type AND parameter count
// The compiler/linker would emit errors because the signatures don't match.

// -----------------------------------------------------------------------
// PITFALL 12: Assuming a parameter change affects the caller
// -----------------------------------------------------------------------
void tryToChange(int value)
{
    value = 999; // Modifies the LOCAL copy only - the caller's variable is unaffected
    std::cout << "  Inside tryToChange: value = " << value << '\n';
}

int main()
{
    std::cout << "=== Project 14: Common Pitfalls ===\n\n";

    // ----- Pitfall 1: Forgetting parentheses -----
    std::cout << "--- Pitfall 1: Forgetting parentheses ---\n";
    // WRONG:
    //   doPrint;      // This does NOT call the function!
    //                 // It evaluates to a function pointer and is discarded.
    //                 // No output, no error in some compilers.
    // CORRECT:
    doPrint(); // Parentheses required to actually call the function.

    // ----- Pitfall 2: Missing return value -----
    std::cout << "\n--- Pitfall 2: Missing return value ---\n";
    std::cout << "getValueCorrect() = " << getValueCorrect() << '\n';
    // If we called getValueBroken(), the returned value would be garbage (UB).

    // ----- Pitfall 3: Using void function as a value -----
    std::cout << "\n--- Pitfall 3: Void function as a value ---\n";
    // WRONG:  std::cout << printHi();   // Won't compile
    // CORRECT: call it as a statement:
    printHi();

    // ----- Pitfall 4: Calling before declaration -----
    std::cout << "\n--- Pitfall 4: Calling before declaration ---\n";
    // If you move a function call ABOVE its definition (and there's no
    // forward declaration), the compiler will say "identifier not found".
    // Solution: provide a forward declaration, or reorder your functions.
    std::cout << "computeSum(3, 4) = " << computeSum(3, 4) << '\n';

    // ----- Pitfall 5: Nested function definitions -----
    std::cout << "\n--- Pitfall 5: Nested function definitions ---\n";
    // WRONG (will not compile in standard C++):
    //   void outer()
    //   {
    //       void inner() { }  // ERROR: cannot define a function inside another
    //   }
    // CORRECT: define all functions at namespace scope (outside other functions).
    std::cout << "C++ does not allow defining functions inside other functions.\n";

    // ----- Pitfall 6: Definitions in headers (ODR violation) -----
    std::cout << "\n--- Pitfall 6: Definitions in headers ---\n";
    // If you put a non-inline function definition in a .h file and
    // #include it in two .cpp files, the linker sees two definitions
    // of the same function → ODR violation → linker error.
    // CORRECT: put declarations in headers, definitions in .cpp files.
    std::cout << "Put declarations in .h, definitions in .cpp files.\n";

    // ----- Pitfall 7: Forgetting header guards -----
    std::cout << "\n--- Pitfall 7: Forgetting header guards ---\n";
    // Without #ifndef/#define/#endif (or #pragma once), a header
    // included multiple times in the same translation unit will cause
    // duplicate-definition errors.
    std::cout << "Always use #ifndef/#define/#endif or #pragma once.\n";

    // ----- Pitfall 8: using namespace std; -----
    std::cout << "\n--- Pitfall 8: using namespace std; ---\n";
    // WRONG:  using namespace std;
    // This dumps ALL std names into the global scope.  If you define
    // a 'count', 'min', 'max', 'size', etc., it may collide with std::.
    // CORRECT: always write std::cout, std::cin, etc.
    std::cout << "Always use std:: prefix.  Avoid 'using namespace std;'.\n";

    // ----- Pitfall 9: Pass by value surprise -----
    std::cout << "\n--- Pitfall 9: Pass by value surprise ---\n";
    int myVar{42};
    std::cout << "Before: myVar = " << myVar << '\n';
    tryToChange(myVar);
    std::cout << "After:  myVar = " << myVar << " (unchanged - pass by value!)\n";

    // ----- Pitfall 10: #include "file.cpp" -----
    std::cout << "\n--- Pitfall 10: #include \"file.cpp\" ---\n";
    // WRONG:  #include "math.cpp"
    // This pastes the entire .cpp file's contents, leading to
    // duplicate definitions and other problems.
    // CORRECT: add the .cpp file to your project/build and use a header.
    std::cout << "Never #include .cpp files.  Compile them separately.\n";

    // ----- Pitfall 11: Forgetting to add .cpp to the build -----
    std::cout << "\n--- Pitfall 11: Missing .cpp in build ---\n";
    // If you declare a function (via header) but forget to compile its
    // .cpp file, the linker says: "unresolved external symbol".
    // Fix: make sure ALL .cpp files are included in your build/project.
    std::cout << "Always add every .cpp file to your build/project.\n";

    std::cout << "\nAll pitfalls demonstrated successfully.\n";
    return 0;
}
