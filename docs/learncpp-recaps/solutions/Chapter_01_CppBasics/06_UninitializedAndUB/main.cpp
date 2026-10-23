// Chapter 1 - Project 06: Uninitialized Variables and Undefined Behavior
// ========================================================================
//
// KEY CONCEPTS:
//   - A variable that hasn't received a known value is **uninitialized**.
//   - It contains whatever garbage bits were already in that memory location.
//   - Using an uninitialized variable is **undefined behavior (UB)**.
//   - UB means the C++ standard does not define what happens - the program
//     may crash, produce wrong results, or appear to work correctly.
//
// THREE CATEGORIES OF NON-PORTABLE BEHAVIOR:
//   1. **Undefined behavior (UB)** - no rules at all; anything can happen.
//   2. **Implementation-defined** - compiler-specific but documented.
//   3. **Unspecified behavior** - compiler-specific but NOT documented.
//
// BEST PRACTICE:
//   - ALWAYS initialize your variables.
//   - Prefer value initialization: int x{};  (zero-initializes)

#include <iostream>

int main()
{
    // =====================================================================
    // SAFE: Initialized variables
    // =====================================================================

    int initialized{42}; // List-initialized to 42 - safe and predictable
    std::cout << "Initialized variable: " << initialized << '\n';

    int valueInit{}; // Value-initialized to 0 - also safe
    std::cout << "Value-initialized variable: " << valueInit << '\n';

    // =====================================================================
    // DANGEROUS: Uninitialized variable (DO NOT DO THIS)
    // =====================================================================

    // Uncomment the next two lines to see undefined behavior in action.
    // The result is unpredictable - you might get 0, a random number, or a crash.
    //
    // int garbage;                        // Default-initialized: NO value assigned!
    // std::cout << "Garbage value: " << garbage << '\n';  // UB! Don't do this!

    // We simulate the concept for demonstration without actual UB:
    std::cout << "\n--- What happens with uninitialized variables? ---\n";
    std::cout << "int x;              // x gets whatever bits were in memory\n";
    std::cout << "std::cout << x;     // UNDEFINED BEHAVIOR!\n";
    std::cout << "Could print 0, 42, -858993460, or crash entirely.\n";

    // =====================================================================
    // WHY is UB dangerous?
    // =====================================================================

    std::cout << "\n--- Why is undefined behavior dangerous? ---\n";
    std::cout << "1. Your program might APPEAR to work during testing\n";
    std::cout << "   but fail in production with different data.\n";
    std::cout << "2. Different compilers may produce different results.\n";
    std::cout << "3. The compiler can optimize assuming UB never happens,\n";
    std::cout << "   which can cause surprising code elimination.\n";

    // =====================================================================
    // BEST PRACTICE: Always initialize
    // =====================================================================

    std::cout << "\n--- Best practices ---\n";
    std::cout << "int x{};   // Value-init: guaranteed to be 0\n";
    std::cout << "int x{5};  // List-init: guaranteed to be 5\n";
    std::cout << "NEVER use: int x;  // Leaves x uninitialized (UB if read)\n";

    // =====================================================================
    // Implementation-defined vs. Unspecified vs. Undefined
    // =====================================================================

    std::cout << "\n--- Behavior categories ---\n";
    std::cout << "Implementation-defined: sizeof(int) may be 4 or 2 (documented per compiler)\n";
    std::cout << "Unspecified:            Order of function argument evaluation\n";
    std::cout << "Undefined:              Using an uninitialized variable (anything can happen)\n";

    // Example of implementation-defined behavior:
    std::cout << "\nsizeof(int) on this system: " << sizeof(int) << " bytes\n";

    return 0;
}
