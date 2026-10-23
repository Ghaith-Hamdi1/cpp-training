// Chapter O - Project 6: Integral Promotion Pitfalls
//
// Key pitfall: Bitwise operators promote operands smaller than int to int
// (or unsigned int). This means ~ and << on a uint8_t produce a 32-bit
// result, which can cause surprising values if you're not careful.
//
// Fix: Always static_cast the result back to the narrow type.

#include <cstdint>
#include <iostream>
#include <bitset>

int main()
{
    // -----------------------------------------------------------------------
    // 1. The problem with ~ and narrow types
    // -----------------------------------------------------------------------
    std::cout << "=== Bitwise NOT (~) Promotion ===\n";

    std::uint8_t byte{0b0000'0101}; // 5
    std::cout << "byte        = " << std::bitset<8>(byte) << " (uint8_t)\n";

    // When we apply ~, 'byte' is promoted to int (32 bits) BEFORE the NOT.
    // So ~byte is NOT 1111'1010 (the 8-bit result we might expect).
    // Instead it's 1111'1111'1111'1111'1111'1111'1111'1010 (a 32-bit result).
    auto notByte{~byte}; // type is int, not uint8_t!
    std::cout << "~byte       = " << std::bitset<32>(notByte) << " (int - 32 bits!)\n";
    std::cout << "~byte value = " << notByte << " (large negative number, not 250)\n";

    // Fix: cast back to uint8_t to get the 8-bit result:
    std::uint8_t notByteFixed{static_cast<std::uint8_t>(~byte)};
    std::cout << "cast ~byte  = " << std::bitset<8>(notByteFixed)
              << " (uint8_t - correct!)\n";
    std::cout << "value       = " << static_cast<int>(notByteFixed) << " (250)\n";

    // -----------------------------------------------------------------------
    // 2. The problem with << and narrow types
    // -----------------------------------------------------------------------
    std::cout << "\n=== Left Shift (<<) Promotion ===\n";

    std::uint8_t val{0b1000'0000}; // 128 - highest bit set
    std::cout << "val         = " << std::bitset<8>(val) << " (128)\n";

    // val << 1 promotes val to int first, then shifts.
    // Result is 256 (0x100), which doesn't fit in uint8_t.
    auto shifted{val << 1}; // type is int!
    std::cout << "val << 1    = " << shifted << " (256 - overflows uint8_t)\n";
    std::cout << "as 32-bit   = " << std::bitset<32>(shifted) << '\n';

    // If you expected the bit to "wrap around" or be lost, cast back:
    std::uint8_t shiftedFixed{static_cast<std::uint8_t>(val << 1)};
    std::cout << "cast val<<1 = " << std::bitset<8>(shiftedFixed)
              << " (0 - the bit was shifted off)\n";

    // -----------------------------------------------------------------------
    // 3. Real-world consequence: mask clearing fails without cast
    // -----------------------------------------------------------------------
    std::cout << "\n=== Mask Clearing Pitfall ===\n";

    std::uint8_t flags{0b1111'1111}; // all bits set
    std::uint8_t mask{0b0000'0100};  // bit 2

    // Correct way to clear bit 2:
    // flags &= ~mask;
    // But ~mask is promoted to int: ~0x04 = 0xFFFF'FFFB (32-bit).
    // After &= with an 8-bit flags, the result is truncated back to 8 bits,
    // which happens to give the correct answer here. BUT if you store ~mask
    // in an intermediate variable, the type matters:

    auto badMask{~mask}; // int, not uint8_t
    std::cout << "~mask (int) = " << std::bitset<32>(badMask) << '\n';

    std::uint8_t goodMask{static_cast<std::uint8_t>(~mask)};
    std::cout << "~mask (u8)  = " << std::bitset<8>(goodMask) << '\n';

    // Both work for &=, but being explicit is safer and clearer:
    flags &= static_cast<std::uint8_t>(~mask);
    std::cout << "flags       = " << std::bitset<8>(flags) << " (bit 2 cleared)\n";

    // -----------------------------------------------------------------------
    // 4. Summary of best practices
    // -----------------------------------------------------------------------
    std::cout << "\n=== Rules of Thumb ===\n";
    std::cout << "1. After ~ on a narrow type, static_cast back immediately.\n";
    std::cout << "2. After << on a narrow type, static_cast if storing result.\n";
    std::cout << "3. Use auto cautiously - it captures the promoted int type.\n";
    std::cout << "4. Prefer std::uint32_t or std::uint64_t to avoid promotion.\n";

    return 0;
}
