// Chapter 1 - Project 04: Initialization Forms
// ===============================================
//
// KEY CONCEPTS:
//   C++ offers several ways to initialize a variable:
//
//   1. Default initialization:   int x;       - leaves x uninitialized (garbage value!)
//   2. Copy initialization:      int x = 5;   - copies 5 into x
//   3. Direct initialization:    int x(5);    - directly initializes x with 5
//   4. Direct-list-init (brace): int x{5};    - initializes x with 5 (PREFERRED)
//   5. Value initialization:     int x{};     - zero-initializes x (x becomes 0)
//
// WHY PREFER LIST INITIALIZATION (braces)?
//   - It disallows **narrowing conversions** (e.g., double -> int loses data).
//   - Copy and direct initialization silently allow narrowing - dangerous!
//
// PITFALL:
//   - int a, b = 5;  - only b is initialized! a is still uninitialized.

#include <iostream>

int main()
{
    // --- 1. Default initialization ---
    // int uninit;  // DANGEROUS: contains a garbage value. Using it is UB.
    // We won't use this - just know it exists and avoid it.

    // --- 2. Copy initialization ---
    // Uses the = sign. Inherited from C.
    int copyInit = 10;
    std::cout << "Copy initialization:        copyInit = " << copyInit << '\n';

    // --- 3. Direct initialization ---
    // Uses parentheses. Introduced in early C++.
    int directInit(20);
    std::cout << "Direct initialization:      directInit = " << directInit << '\n';

    // --- 4. Direct-list-initialization (brace initialization) - PREFERRED ---
    // Uses curly braces. Introduced in C++11.
    int listInit{30};
    std::cout << "List initialization:        listInit = " << listInit << '\n';

    // --- 5. Value initialization ---
    // Braces with nothing inside → zero-initializes the variable.
    int valueInit{};
    std::cout << "Value initialization:       valueInit = " << valueInit << '\n';

    // =====================================================================
    // NARROWING CONVERSION DEMO
    // =====================================================================

    // Copy initialization ALLOWS narrowing (silent data loss):
    int fromDouble = 3.9; // Compiles! But truncates to 3. Data lost silently.
    std::cout << "\nNarrowing (copy init):      int fromDouble = 3.9 -> " << fromDouble << '\n';

    // Direct initialization ALSO allows narrowing:
    int fromDouble2(4.7); // Compiles! Truncates to 4.
    std::cout << "Narrowing (direct init):    int fromDouble2(4.7) -> " << fromDouble2 << '\n';

    // List initialization DISALLOWS narrowing - compile error if uncommented:
    // int fromDouble3{ 5.5 };  // ERROR: narrowing conversion from double to int
    std::cout << "Narrowing (list init):      int fromDouble3{5.5} -> COMPILE ERROR (blocked!)\n";

    // This is why list initialization is the safest and preferred form.

    // =====================================================================
    // PITFALL: Multiple variables, one initializer
    // =====================================================================
    // int a, b = 5;  // Only b gets 5. a is UNINITIALIZED. Don't do this!

    // CORRECT: initialize each variable separately.
    int a{5};
    int b{5};
    std::cout << "\nSeparate init: a=" << a << " b=" << b << '\n';

    // =====================================================================
    // SUMMARY
    // =====================================================================
    std::cout << "\n--- Summary ---\n";
    std::cout << "int x;      -> Default (uninitialized - avoid!)\n";
    std::cout << "int x = 5;  -> Copy (allows narrowing)\n";
    std::cout << "int x(5);   -> Direct (allows narrowing)\n";
    std::cout << "int x{5};   -> List/Brace (PREFERRED - blocks narrowing)\n";
    std::cout << "int x{};    -> Value (zero-initializes)\n";

    return 0;
}
