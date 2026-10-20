// Chapter 1 - Project 13: The [[maybe_unused]] Attribute
// ==========================================================
//
// KEY CONCEPTS:
//   - When you define a variable but don't use it, the compiler may warn you.
//   - Sometimes you intentionally have unused variables (e.g., for future use,
//     platform-specific code, or function parameters you don't need yet).
//   - The [[maybe_unused]] attribute (C++17) tells the compiler:
//     "I know this variable might not be used - don't warn me about it."
//   - This is cleaner than commenting out the variable or using (void)var tricks.
//
// NOTE: Compile with -std=c++17 or later (e.g., g++ -std=c++20 main.cpp)

#include <iostream>

int main()
{
    std::cout << "=== [[maybe_unused]] Attribute ===\n\n";

    // =====================================================================
    // WITHOUT [[maybe_unused]] - compiler may warn
    // =====================================================================

    // int unusedVar{ 42 };
    // ^ If you compile with -Wall, you'll get:
    //   "warning: unused variable 'unusedVar'"

    // =====================================================================
    // WITH [[maybe_unused]] - no warning
    // =====================================================================

    [[maybe_unused]] int reservedForLater{42};
    // No warning! The compiler knows we intentionally left it unused.

    [[maybe_unused]] double piApprox{3.14159};
    // Same here - marked as intentionally (possibly) unused.

    // =====================================================================
    // PRACTICAL USE CASE: Platform-specific code
    // =====================================================================

    [[maybe_unused]] int debugLevel{3};
    // debugLevel might only be used in debug builds:
    //
    // #ifdef _DEBUG
    //     std::cout << "Debug level: " << debugLevel << '\n';
    // #endif
    //
    // In release builds, it's unused - [[maybe_unused]] prevents the warning.

    // =====================================================================
    // USING a [[maybe_unused]] variable is perfectly fine
    // =====================================================================

    [[maybe_unused]] int value{100};
    // The attribute says "this MIGHT be unused" - using it is still allowed.
    std::cout << "value = " << value << '\n';

    // =====================================================================
    // ALTERNATIVE: the (void) cast trick (older style)
    // =====================================================================

    int oldStyle{99};
    (void)oldStyle; // Suppresses the warning by "using" the variable
    // This works but [[maybe_unused]] is cleaner and more expressive.

    // =====================================================================
    // SUMMARY
    // =====================================================================

    std::cout << "\n--- Summary ---\n";
    std::cout << "[[maybe_unused]] int x{5};  // No warning if x is unused\n";
    std::cout << "Available since C++17.\n";
    std::cout << "Use it for variables that may be unused in some configurations.\n";
    std::cout << "Cleaner than (void)x or commenting out the variable.\n";

    return 0;
}
