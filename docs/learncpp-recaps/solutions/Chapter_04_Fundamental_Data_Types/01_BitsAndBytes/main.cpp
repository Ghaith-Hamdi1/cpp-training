// Chapter 4 - Project 01: Bits and Bytes
// ========================================
// Key concept: A bit is the smallest unit of memory (0 or 1).
// A byte is 8 bits and the smallest addressable unit.
// An object with n bits can hold 2^n unique values.
// Data types tell the compiler how to interpret the bits in memory.

#include <bitset>
#include <cmath>
#include <iostream>

int main()
{
    // A byte is 8 bits. With 8 bits, we can represent 2^8 = 256 unique values.
    std::cout << "=== Bits and Bytes ===\n\n";

    std::cout << "1 byte  = 8 bits  -> 2^8  = " << static_cast<int>(std::pow(2, 8)) << " unique values\n";
    std::cout << "2 bytes = 16 bits -> 2^16 = " << static_cast<int>(std::pow(2, 16)) << " unique values\n";
    std::cout << "4 bytes = 32 bits -> 2^32 = " << static_cast<unsigned long long>(std::pow(2, 32)) << " unique values\n";
    std::cout << "8 bytes = 64 bits -> 2^64 = ~1.8 * 10^19 unique values\n\n";

    // The same bits can mean different things depending on the data type.
    // Let's show how a single byte value looks in binary vs as an int vs as a char.
    unsigned char value{65}; // 65 in decimal

    std::cout << "=== Same bits, different interpretation ===\n";
    std::cout << "Value stored: 65\n";
    std::cout << "As binary:    " << std::bitset<8>(value) << '\n';
    std::cout << "As integer:   " << static_cast<int>(value) << '\n';
    std::cout << "As character: " << static_cast<char>(value) << " (ASCII 65 = 'A')\n\n";

    // Another example: the value 48
    unsigned char value2{48};
    std::cout << "Value stored: 48\n";
    std::cout << "As binary:    " << std::bitset<8>(value2) << '\n';
    std::cout << "As integer:   " << static_cast<int>(value2) << '\n';
    std::cout << "As character: " << static_cast<char>(value2) << " (ASCII 48 = '0')\n\n";

    // Key takeaway: The data type determines HOW the bits are interpreted.
    // The bits themselves don't change - only our interpretation of them does.

    return 0;
}
