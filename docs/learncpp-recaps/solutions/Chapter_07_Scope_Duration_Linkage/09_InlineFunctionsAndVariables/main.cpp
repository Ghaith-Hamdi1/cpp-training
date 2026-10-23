// Chapter 7 - Project 09: Inline Functions and Variables
// ========================================================
// In modern C++, 'inline' does NOT mean "please inline this function."
// It means: "multiple identical definitions across translation units are allowed."
// The linker will deduplicate them.
//
// This enables defining functions and variables in HEADER files without
// violating the One Definition Rule (ODR).
//
// Compile: cl /std:c++20 /EHsc main.cpp other.cpp
//          g++ -std=c++20 main.cpp other.cpp

#include <iostream>
#include "mathutils.h"

// Forward declaration
void otherFileDemo();

int main()
{
    // -------------------------------------------------
    // 1. Inline function defined in a header
    // -------------------------------------------------
    // Both main.cpp and other.cpp include mathutils.h, which defines
    // an inline function. Without 'inline', this would cause a linker
    // error (multiple definitions). With 'inline', the linker keeps one copy.
    std::cout << "1. Inline function from header:\n";
    std::cout << "   square(7)    = " << MathUtils::square(7) << '\n';
    std::cout << "   cube(3)      = " << MathUtils::cube(3) << '\n';

    // -------------------------------------------------
    // 2. Inline variable defined in a header
    // -------------------------------------------------
    // Same idea: the variable is defined in the header, and both .cpp files
    // see the same single instance (not copies).
    std::cout << "\n2. Inline variable from header:\n";
    std::cout << "   MathUtils::pi = " << MathUtils::pi << '\n';

    // Verify both files see the SAME variable (same address)
    std::cout << "   Address in main.cpp:  " << &MathUtils::pi << '\n';

    // -------------------------------------------------
    // 3. Verify from other.cpp
    // -------------------------------------------------
    std::cout << "\n3. Same inline function/variable used in other.cpp:\n";
    otherFileDemo();

    // -------------------------------------------------
    // 4. Key insight: inline ≠ optimization hint
    // -------------------------------------------------
    std::cout << "\n4. 'inline' does NOT mean:\n";
    std::cout << "   - 'Please replace call with function body'\n";
    std::cout << "   - 'This function is small/fast'\n";
    std::cout << "   It DOES mean:\n";
    std::cout << "   - 'Multiple definitions are OK - linker, deduplicate them'\n";
    std::cout << "   The compiler decides what to actually inline for optimization.\n";

    return 0;
}
