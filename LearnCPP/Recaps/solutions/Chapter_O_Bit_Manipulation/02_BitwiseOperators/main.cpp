// Chapter O - Project 2: Bitwise Operators
//
// C++ provides six bitwise operators that work on individual bits:
//   <<  left shift      >>  right shift
//   ~   bitwise NOT     &   bitwise AND
//   |   bitwise OR      ^   bitwise XOR
//
// Each also has a compound-assignment variant: <<=, >>=, &=, |=, ^=
//
// IMPORTANT: Always use unsigned integers when doing bitwise operations.
// Using signed operands can produce implementation-defined behavior.

#include <cstdint>
#include <iostream>
#include <bitset>

// Helper to print a value in both decimal and binary
void print(const char *label, std::uint8_t value)
{
    std::cout << label << "  dec=" << static_cast<int>(value)
              << "  bin=" << std::bitset<8>(value) << '\n';
}

int main()
{
    std::uint8_t a{0b0110'1100}; // 108
    std::uint8_t b{0b0011'1010}; //  58

    std::cout << "--- Operands ---\n";
    print("a", a);
    print("b", b);

    // -----------------------------------------------------------------------
    // 1. Left shift (<<) - shifts bits toward the most-significant end
    // -----------------------------------------------------------------------
    // Bits shifted off the left end are lost. New bits on the right are 0.
    std::cout << "\n--- Left Shift ---\n";
    print("a << 1", static_cast<std::uint8_t>(a << 1));
    print("a << 2", static_cast<std::uint8_t>(a << 2));
    // Note: a << 1 doubles the value (if no bits are lost).

    // -----------------------------------------------------------------------
    // 2. Right shift (>>) - shifts bits toward the least-significant end
    // -----------------------------------------------------------------------
    // Bits shifted off the right end are lost. New bits on the left are 0
    // (for unsigned types).
    std::cout << "\n--- Right Shift ---\n";
    print("a >> 1", static_cast<std::uint8_t>(a >> 1));
    print("a >> 2", static_cast<std::uint8_t>(a >> 2));
    // Note: a >> 1 halves the value (integer division).

    // -----------------------------------------------------------------------
    // 3. Bitwise NOT (~) - flips every bit
    // -----------------------------------------------------------------------
    std::cout << "\n--- Bitwise NOT ---\n";
    // We cast back to uint8_t because ~ promotes to int.
    print("~a", static_cast<std::uint8_t>(~a));
    print("~b", static_cast<std::uint8_t>(~b));

    // -----------------------------------------------------------------------
    // 4. Bitwise AND (&) - result is 1 only where BOTH bits are 1
    // -----------------------------------------------------------------------
    std::cout << "\n--- Bitwise AND ---\n";
    print("a & b", static_cast<std::uint8_t>(a & b));
    //   0110 1100
    // & 0011 1010
    // = 0010 1000  (40)

    // -----------------------------------------------------------------------
    // 5. Bitwise OR (|) - result is 1 where EITHER bit is 1
    // -----------------------------------------------------------------------
    std::cout << "\n--- Bitwise OR ---\n";
    print("a | b", static_cast<std::uint8_t>(a | b));
    //   0110 1100
    // | 0011 1010
    // = 0111 1110  (126)

    // -----------------------------------------------------------------------
    // 6. Bitwise XOR (^) - result is 1 where bits DIFFER
    // -----------------------------------------------------------------------
    std::cout << "\n--- Bitwise XOR ---\n";
    print("a ^ b", static_cast<std::uint8_t>(a ^ b));
    //   0110 1100
    // ^ 0011 1010
    // = 0101 0110  (86)

    // -----------------------------------------------------------------------
    // 7. Compound assignment operators
    // -----------------------------------------------------------------------
    std::cout << "\n--- Compound Assignment ---\n";
    std::uint8_t x{a};
    x <<= 1;
    print("a <<= 1", x);
    x = a;
    x >>= 1;
    print("a >>= 1", x);
    x = a;
    x &= b;
    print("a &= b ", x);
    x = a;
    x |= b;
    print("a |= b ", x);
    x = a;
    x ^= b;
    print("a ^= b ", x);

    // -----------------------------------------------------------------------
    // 8. XOR swap trick (classic interview question)
    // -----------------------------------------------------------------------
    std::cout << "\n--- XOR Swap ---\n";
    std::uint8_t p{25}, q{42};
    std::cout << "Before: p=" << +p << ", q=" << +q << '\n';
    p ^= q;
    q ^= p;
    p ^= q;
    std::cout << "After:  p=" << +p << ", q=" << +q << '\n';

    return 0;
}
