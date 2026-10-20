// Project 05: Undefined Behavior (UB)
// ====================================
// Appendix A.4 - Undefined behavior and why you must never rely on it
//
// Undefined behavior (UB) means the C++ standard imposes NO requirements
// on the program's behavior.  The compiler is free to:
//   - produce the "expected" result (making you think the bug is harmless)
//   - produce a wrong result silently
//   - crash immediately or at some later point
//   - optimise away the UB path entirely (time travel)
//   - do literally anything else
//
// UB is especially dangerous because it may "work" on your machine,
// your compiler version, your optimisation level, and your OS -
// then break catastrophically when ANY of those change.
//
// This program shows SAFE demonstrations of common UB patterns
// (we show the problematic patterns in comments and then show the
// correct alternatives in running code).

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <limits>

// -----------------------------------------------------------------------
// Helper to print section headers
// -----------------------------------------------------------------------
void printSection(const std::string &title)
{
    std::cout << "\n--- " << title << " ---\n";
}

int main()
{
    std::cout << "=== Undefined Behavior (UB) Demonstration ===\n";

    // ===================================================================
    // 1. Signed integer overflow - UB
    // ===================================================================
    printSection("1. Signed Integer Overflow");

    // BAD (UB):
    //   int x = std::numeric_limits<int>::max();
    //   x = x + 1;   // UB! Signed overflow is undefined.

    // SAFE: check before performing the operation
    int maxVal = std::numeric_limits<int>::max();
    std::cout << "INT_MAX = " << maxVal << '\n';
    std::cout << "Adding 1 to INT_MAX is undefined behavior (signed overflow).\n";
    std::cout << "SAFE: always check before arithmetic on values near limits.\n";

    // ===================================================================
    // 2. Accessing an array out of bounds - UB
    // ===================================================================
    printSection("2. Out-of-Bounds Access");

    // BAD (UB):
    //   int arr[5] = {1,2,3,4,5};
    //   int val = arr[10];   // UB! Reading past the end.

    // SAFE: use bounds-checked access
    std::vector<int> arr{1, 2, 3, 4, 5};
    std::cout << "arr.at(2) = " << arr.at(2) << "   (bounds-checked)\n";
    try
    {
        [[maybe_unused]] int val = arr.at(10); // throws std::out_of_range
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "arr.at(10) threw: " << e.what() << '\n';
    }

    // ===================================================================
    // 3. Using an uninitialised variable - UB
    // ===================================================================
    printSection("3. Uninitialised Variables");

    // BAD (UB):
    //   int x;
    //   std::cout << x;   // UB! Reading an uninitialised variable.

    // SAFE: always initialise
    int x{0}; // value-initialised to 0
    std::cout << "Initialised x = " << x << '\n';
    std::cout << "ALWAYS initialise your variables (use {} or = 0).\n";

    // ===================================================================
    // 4. Dereferencing a null pointer - UB
    // ===================================================================
    printSection("4. Null Pointer Dereference");

    // BAD (UB):
    //   int* ptr = nullptr;
    //   int val = *ptr;   // UB! Dereferencing null.

    // SAFE: check before dereferencing
    int *ptr = nullptr;
    if (ptr != nullptr)
    {
        std::cout << "*ptr = " << *ptr << '\n';
    }
    else
    {
        std::cout << "ptr is null - not dereferencing (avoided UB).\n";
    }

    // ===================================================================
    // 5. Omitting return from a non-void function - UB
    // ===================================================================
    printSection("5. Missing Return Statement");

    // BAD (UB):
    //   int getValue() {
    //       // no return statement - UB for non-void functions (except main)
    //   }

    // Note: main() is special - it implicitly returns 0 if you omit return.
    // All OTHER value-returning functions MUST have an explicit return.

    std::cout << "main() implicitly returns 0 if return is omitted.\n";
    std::cout << "All other non-void functions produce UB without return.\n";
    std::cout << "ALWAYS include an explicit return statement.\n";

    // ===================================================================
    // 6. Dangling reference / use-after-free - UB
    // ===================================================================
    printSection("6. Dangling References");

    // BAD (UB):
    //   int& getRef() {
    //       int local = 42;
    //       return local;   // UB! Returning reference to local variable.
    //   }

    // SAFE: return by value, or ensure the referenced object outlives the reference
    std::cout << "Never return a reference/pointer to a local variable.\n";
    std::cout << "The local is destroyed when the function returns.\n";

    // ===================================================================
    // Summary
    // ===================================================================
    printSection("Summary");
    std::cout << "Undefined behavior can appear to 'work' but is NEVER safe.\n";
    std::cout << "It can break with any compiler update, optimisation flag, or platform.\n";
    std::cout << "Common UB sources:\n";
    std::cout << "  - Signed overflow\n";
    std::cout << "  - Out-of-bounds access\n";
    std::cout << "  - Uninitialised variables\n";
    std::cout << "  - Null/dangling pointer dereference\n";
    std::cout << "  - Missing return in non-void functions\n";
    std::cout << "  - Use-after-free / dangling references\n";
    std::cout << "Prevention: initialise everything, check bounds, never assume.\n";

    return 0;
}
