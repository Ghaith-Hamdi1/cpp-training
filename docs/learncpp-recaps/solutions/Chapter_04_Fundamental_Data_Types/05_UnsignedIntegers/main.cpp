// Chapter 4 - Project 05: Unsigned Integers and Why to Avoid Them
// ================================================================
// Key concept: Unsigned integers can only hold non-negative values.
// On overflow, they wrap around (modulo 2^n), which is defined behavior
// but still leads to bugs.
//
// CRITICAL PITFALL: Mixing signed and unsigned in expressions causes
// the signed value to be implicitly converted to unsigned, producing
// surprising results.
//
// Best practice: Favor signed types for quantities and math.

#include <iostream>
#include <climits>

int main()
{
    std::cout << "=== Unsigned Integers ===\n\n";

    // Basic unsigned integer
    unsigned int u{5};
    std::cout << "unsigned int u = " << u << '\n';

    // Range of unsigned int
    std::cout << "Range: 0 to " << UINT_MAX << '\n';
    std::cout << '\n';

    // --- Unsigned wrapping (modulo arithmetic) ---
    std::cout << "--- Unsigned wrapping ---\n";

    unsigned int big{UINT_MAX};
    std::cout << "UINT_MAX     = " << big << '\n';
    std::cout << "UINT_MAX + 1 = " << big + 1 << " (wraps to 0)\n";

    unsigned int zero{0};
    std::cout << "0u - 1       = " << zero - 1 << " (wraps to UINT_MAX!)\n";
    std::cout << '\n';

    // --- The danger of mixing signed and unsigned ---
    std::cout << "--- Mixing signed and unsigned (DANGER!) ---\n";

    unsigned int a{3};
    unsigned int b{5};

    // Subtracting a larger unsigned from a smaller one wraps around
    std::cout << "3u - 5u = " << (a - b) << " (expected -2, got a huge number!)\n";
    std::cout << '\n';

    // Comparing signed and unsigned
    int signedVal{-1};
    unsigned int unsignedVal{1};

    // The signed -1 gets converted to unsigned, becoming a huge number
    if (signedVal < unsignedVal)
        std::cout << "-1 < 1u: true (mathematically correct, but...\n";
    else
        std::cout << "-1 < 1u: false! (-1 converted to unsigned becomes " << static_cast<unsigned int>(-1) << ")\n";

    std::cout << '\n';

    // Best practice summary
    std::cout << "--- Best Practice ---\n";
    std::cout << "1. Use signed int for general quantities and math.\n";
    std::cout << "2. Unsigned is acceptable for bit manipulation and specific APIs.\n";
    std::cout << "3. NEVER mix signed and unsigned in expressions.\n";
    std::cout << "4. Be careful with subtraction on unsigned types.\n";

    return 0;
}
