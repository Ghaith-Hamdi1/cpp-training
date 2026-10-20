// Chapter O - Project 7: Common Pitfalls in Bit Manipulation
//
// This project demonstrates the most frequent mistakes when working with
// bitwise operators, so you can recognize and avoid them.

#include <cstdint>
#include <iostream>
#include <bitset>

int main()
{
    // -----------------------------------------------------------------------
    // Pitfall 1: Confusing logical and bitwise operators
    // -----------------------------------------------------------------------
    // && / || are LOGICAL operators - they evaluate the overall truth of values.
    // &  / |  are BITWISE operators - they operate on individual bits.
    std::cout << "=== Pitfall 1: Logical vs Bitwise ===\n";

    std::uint8_t a{0b0000'0110}; // 6
    std::uint8_t b{0b0000'0011}; // 3

    // Bitwise AND: operates per-bit
    std::cout << "a & b  = " << std::bitset<8>(static_cast<std::uint8_t>(a & b))
              << " (" << (a & b) << ")\n";
    // Result: 0000'0010 = 2 (only bit 1 is 1 in both)

    // Logical AND: both are nonzero → true
    std::cout << "a && b = " << (a && b) << " (both nonzero → true)\n";

    // The dangerous case: using & when you meant &&
    std::uint8_t x{0b0000'0010}; // 2
    std::uint8_t y{0b0000'0100}; // 4
    std::cout << "\nx = " << +x << ", y = " << +y << '\n';
    std::cout << "x & y  = " << (x & y) << "  (bitwise: no bits in common → 0 → false!)\n";
    std::cout << "x && y = " << (x && y) << "  (logical: both nonzero → true)\n";
    std::cout << "BUG: 'if (x & y)' evaluates to false even though both are nonzero!\n";

    // -----------------------------------------------------------------------
    // Pitfall 2: Off-by-one with bit positions
    // -----------------------------------------------------------------------
    std::cout << "\n=== Pitfall 2: Off-by-One Bit Positions ===\n";

    // Bit positions start at 0 (rightmost), NOT 1.
    // 1 << 0 = bit position 0 = value 1
    // 1 << 1 = bit position 1 = value 2
    // 1 << 7 = bit position 7 = value 128

    std::cout << "1 << 0 = " << (1 << 0) << "  (bit 0, value 1)\n";
    std::cout << "1 << 1 = " << (1 << 1) << "  (bit 1, value 2)\n";
    std::cout << "1 << 7 = " << (1 << 7) << "  (bit 7, value 128)\n";

    // Common mistake: wanting to set bit 1 (the second bit) but writing:
    //   flags |= 1;        ← this sets bit 0, not bit 1!
    //   flags |= (1 << 1); ← this correctly sets bit 1

    // -----------------------------------------------------------------------
    // Pitfall 3: Shifting bits off the end (not rotation!)
    // -----------------------------------------------------------------------
    std::cout << "\n=== Pitfall 3: Shift Loss (Not Rotation) ===\n";

    std::uint8_t val{0b1100'0011}; // 195
    std::cout << "Original:  " << std::bitset<8>(val) << " (" << +val << ")\n";

    // Left shift by 4: the leftmost 4 bits (1100) are lost permanently
    std::uint8_t shifted{static_cast<std::uint8_t>(val << 4)};
    std::cout << "val << 4:  " << std::bitset<8>(shifted) << " (" << +shifted << ")\n";
    std::cout << "The top 4 bits are GONE - shifting is not rotation.\n";

    // Right shift by 4: the rightmost 4 bits (0011) are lost permanently
    std::uint8_t rshifted{static_cast<std::uint8_t>(val >> 4)};
    std::cout << "val >> 4:  " << std::bitset<8>(rshifted) << " (" << +rshifted << ")\n";

    // -----------------------------------------------------------------------
    // Pitfall 4: Forgetting ~ when clearing bits
    // -----------------------------------------------------------------------
    std::cout << "\n=== Pitfall 4: Forgetting ~ When Clearing ===\n";

    std::uint8_t flags{0b1111'1111};          // all bits set
    constexpr std::uint8_t mask{0b0000'0100}; // bit 2

    // WRONG: flags &= mask → clears everything EXCEPT bit 2
    std::uint8_t wrongResult{static_cast<std::uint8_t>(flags & mask)};
    std::cout << "flags & mask   = " << std::bitset<8>(wrongResult)
              << "  (WRONG - cleared everything except bit 2)\n";

    // RIGHT: flags &= ~mask → clears only bit 2
    std::uint8_t rightResult{static_cast<std::uint8_t>(flags & static_cast<std::uint8_t>(~mask))};
    std::cout << "flags & ~mask  = " << std::bitset<8>(rightResult)
              << "  (RIGHT - cleared only bit 2)\n";

    // -----------------------------------------------------------------------
    // Pitfall 5: Using bitwise operators on signed integers
    // -----------------------------------------------------------------------
    std::cout << "\n=== Pitfall 5: Signed Integer Bitwise Ops ===\n";

    // Right-shifting a negative signed integer is implementation-defined.
    // Some compilers do arithmetic shift (fill with 1s), others do logical
    // shift (fill with 0s). This is NOT portable!
    std::int8_t negative{-4}; // 1111'1100 in two's complement
    std::cout << "negative (-4)    = " << std::bitset<8>(static_cast<std::uint8_t>(negative)) << '\n';

    // Result of >> on signed negative is implementation-defined:
    std::int8_t negShifted{static_cast<std::int8_t>(negative >> 1)};
    std::cout << "negative >> 1    = " << std::bitset<8>(static_cast<std::uint8_t>(negShifted))
              << " (" << static_cast<int>(negShifted) << ")\n";
    std::cout << "Result may differ between compilers! Use unsigned types instead.\n";

    // -----------------------------------------------------------------------
    // Pitfall 6: De Morgan's law applies to bitwise ops too
    // -----------------------------------------------------------------------
    std::cout << "\n=== De Morgan's Law (Bitwise) ===\n";

    std::uint8_t p{0b1010'0110};
    std::uint8_t q{0b0110'1100};

    // ~(p | q)  ==  ~p & ~q
    std::uint8_t lhs{static_cast<std::uint8_t>(~(p | q))};
    std::uint8_t rhs{static_cast<std::uint8_t>(static_cast<std::uint8_t>(~p) & static_cast<std::uint8_t>(~q))};

    std::cout << "~(p | q)  = " << std::bitset<8>(lhs) << '\n';
    std::cout << "~p & ~q   = " << std::bitset<8>(rhs) << '\n';
    std::cout << "Equal?    " << (lhs == rhs ? "yes" : "no") << '\n';

    // ~(p & q)  ==  ~p | ~q
    std::uint8_t lhs2{static_cast<std::uint8_t>(~(p & q))};
    std::uint8_t rhs2{static_cast<std::uint8_t>(static_cast<std::uint8_t>(~p) | static_cast<std::uint8_t>(~q))};

    std::cout << "~(p & q)  = " << std::bitset<8>(lhs2) << '\n';
    std::cout << "~p | ~q   = " << std::bitset<8>(rhs2) << '\n';
    std::cout << "Equal?    " << (lhs2 == rhs2 ? "yes" : "no") << '\n';

    return 0;
}
