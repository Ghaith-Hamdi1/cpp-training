// Chapter 5 - Project 03: Numeral Systems
// =========================================
// Topics:
//   - Decimal (base 10), octal (base 8), hexadecimal (base 16), binary (base 2)
//   - Literal prefixes: 0 (octal), 0x (hex), 0b (binary, C++14)
//   - Digit separator ' (C++14) for readability
//   - Accidental octal pitfall
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <bitset> // for binary output

int main()
{
    // -------------------------------------------------------
    // 1. Decimal (base 10) - the default
    // -------------------------------------------------------
    int decimal = 42;
    std::cout << "=== Numeral Systems ===\n";
    std::cout << "Decimal:     " << decimal << '\n';

    // -------------------------------------------------------
    // 2. Octal (base 8) - prefix with 0
    // -------------------------------------------------------
    int octal = 052; // 5*8 + 2 = 42 in decimal
    std::cout << "Octal 052:   " << octal << " (decimal)\n";

    // -------------------------------------------------------
    // 3. Hexadecimal (base 16) - prefix with 0x
    // -------------------------------------------------------
    int hex = 0x2A; // 2*16 + 10 = 42 in decimal
    std::cout << "Hex 0x2A:    " << hex << " (decimal)\n";

    // Hex is widely used for memory addresses and color codes:
    int color = 0xFF5733;
    std::cout << "Color code:  0x" << std::hex << color << std::dec << '\n';

    // -------------------------------------------------------
    // 4. Binary (base 2) - prefix with 0b (C++14)
    // -------------------------------------------------------
    int binary = 0b00101010; // 42 in decimal
    std::cout << "Binary 0b00101010: " << binary << " (decimal)\n";

    // -------------------------------------------------------
    // 5. Digit separator ' for readability (C++14)
    // -------------------------------------------------------
    // The single-quote ' can appear between digits to improve readability.
    // It is purely cosmetic - the compiler ignores it.
    int billion = 1'000'000'000;
    int hexGrouped = 0xFF'00'FF'00;
    int binGrouped = 0b1111'0000'1010'0101;

    std::cout << "\n=== Digit Separators ===\n";
    std::cout << "1'000'000'000     = " << billion << '\n';
    std::cout << "0xFF'00'FF'00     = " << hexGrouped << '\n';
    std::cout << "0b1111'0000'1010  = " << binGrouped << '\n';

    // -------------------------------------------------------
    // 6. Printing in different bases
    // -------------------------------------------------------
    int value = 255;
    std::cout << "\n=== Printing 255 in Different Bases ===\n";
    std::cout << "Decimal:     " << std::dec << value << '\n';
    std::cout << "Octal:       " << std::oct << value << '\n';
    std::cout << "Hexadecimal: " << std::hex << value << '\n';
    std::cout << "Binary:      " << std::bitset<8>(value) << '\n';

    // Reset to decimal for subsequent output
    std::cout << std::dec;

    // -------------------------------------------------------
    // 7. PITFALL: Accidental octal
    // -------------------------------------------------------
    // A leading 0 makes a literal octal - this is a common mistake!
    int notTwelve = 012; // This is octal 12 = decimal 10, NOT 12!
    std::cout << "\n=== Accidental Octal Pitfall ===\n";
    std::cout << "012 is NOT 12 - it is octal for " << notTwelve << "!\n";
    std::cout << "Lesson: Never prefix a decimal number with 0.\n";

    return 0;
}
