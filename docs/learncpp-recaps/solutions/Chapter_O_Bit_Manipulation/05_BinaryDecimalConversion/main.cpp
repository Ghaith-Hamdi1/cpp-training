// Chapter O - Project 5: Binary ↔ Decimal Conversion and Two's Complement
//
// Key concepts:
//   - Binary is base-2; each digit is a power of 2 (1, 2, 4, 8, 16, …)
//   - Binary → decimal: sum each bit × its positional power of 2
//   - Decimal → binary: repeatedly divide by 2 and collect remainders
//   - Two's complement: invert all bits and add 1 to negate a signed integer
//   - The sign bit (leftmost) is 0 for positive, 1 for negative
//   - The type determines whether binary is interpreted as signed or unsigned

#include <cstdint>
#include <iostream>
#include <bitset>
#include <string>
#include <algorithm>

// -----------------------------------------------------------------------
// 1. Manual binary → decimal conversion
// -----------------------------------------------------------------------
// Sum each bit multiplied by its positional value (2^n).
unsigned int binaryToDecimal(const std::string &binary)
{
    unsigned int result{0};
    unsigned int power{1}; // 2^0 = 1

    // Process from right to left (least-significant bit first)
    for (auto it{binary.rbegin()}; it != binary.rend(); ++it)
    {
        if (*it == '1')
            result += power;
        power *= 2;
    }
    return result;
}

// -----------------------------------------------------------------------
// 2. Manual decimal → binary conversion (method 1: repeated division)
// -----------------------------------------------------------------------
// Repeatedly divide by 2; collect remainders in reverse order.
std::string decimalToBinary(unsigned int value)
{
    if (value == 0)
        return "0";

    std::string result;
    while (value > 0)
    {
        result += (value % 2 == 0) ? '0' : '1';
        value /= 2;
    }
    std::ranges::reverse(result);
    return result;
}

int main()
{
    // -----------------------------------------------------------------------
    // 3. Demonstrate binary → decimal
    // -----------------------------------------------------------------------
    std::cout << "=== Binary to Decimal ===\n";
    std::string bin1{"11010110"}; // 214
    std::cout << bin1 << " = " << binaryToDecimal(bin1) << '\n';

    std::string bin2{"00101001"}; // 41
    std::cout << bin2 << " = " << binaryToDecimal(bin2) << '\n';

    // -----------------------------------------------------------------------
    // 4. Demonstrate decimal → binary
    // -----------------------------------------------------------------------
    std::cout << "\n=== Decimal to Binary ===\n";
    unsigned int dec1{214};
    std::cout << dec1 << " = " << decimalToBinary(dec1) << '\n';

    unsigned int dec2{41};
    std::cout << dec2 << " = " << decimalToBinary(dec2) << '\n';

    unsigned int dec3{255};
    std::cout << dec3 << " = " << decimalToBinary(dec3) << '\n';

    // -----------------------------------------------------------------------
    // 5. Two's complement - how negative numbers are stored
    // -----------------------------------------------------------------------
    std::cout << "\n=== Two's Complement ===\n";
    // For an 8-bit signed integer, to represent -5:
    //   Step 1: Write +5 in binary:        0000 0101
    //   Step 2: Invert all bits (ones'):    1111 1010
    //   Step 3: Add 1:                      1111 1011  → this is -5

    std::int8_t positive5{5};
    std::int8_t negative5{-5};

    std::cout << " +5 in binary: " << std::bitset<8>(static_cast<std::uint8_t>(positive5)) << '\n';
    std::cout << " -5 in binary: " << std::bitset<8>(static_cast<std::uint8_t>(negative5)) << '\n';

    // Verify: invert +5 and add 1
    std::uint8_t inverted{static_cast<std::uint8_t>(~static_cast<std::uint8_t>(positive5))};
    std::uint8_t twosComp{static_cast<std::uint8_t>(inverted + 1)};
    std::cout << " ~5 + 1      : " << std::bitset<8>(twosComp) << " (should match -5)\n";

    // -----------------------------------------------------------------------
    // 6. Same binary pattern, different interpretation
    // -----------------------------------------------------------------------
    std::cout << "\n=== Signed vs Unsigned Interpretation ===\n";
    // The SAME bit pattern can mean different things depending on the type.
    std::uint8_t unsignedVal{0b1111'1011};                        // 251 as unsigned
    std::int8_t signedVal{static_cast<std::int8_t>(unsignedVal)}; // -5 as signed

    std::cout << "Bit pattern 11111011:\n";
    std::cout << "  As unsigned: " << static_cast<int>(unsignedVal) << '\n';
    std::cout << "  As signed:   " << static_cast<int>(signedVal) << '\n';

    // -----------------------------------------------------------------------
    // 7. Special property: only one zero in two's complement
    // -----------------------------------------------------------------------
    std::cout << "\n=== Two's Complement of Zero ===\n";
    std::int8_t zero{0};
    std::cout << " 0 in binary: " << std::bitset<8>(static_cast<std::uint8_t>(zero)) << '\n';
    // ~0 + 1 = 1111'1111 + 1 = 1'0000'0000 → overflows back to 0000'0000
    // So there's only ONE representation of zero (unlike one's complement).
    std::uint8_t negZero{static_cast<std::uint8_t>(~static_cast<std::uint8_t>(zero) + 1)};
    std::cout << "-0 in binary: " << std::bitset<8>(negZero) << " (same as +0)\n";

    return 0;
}
