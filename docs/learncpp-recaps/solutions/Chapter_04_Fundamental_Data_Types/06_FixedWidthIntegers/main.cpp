// Chapter 4 - Project 06: Fixed-Width Integers and std::size_t
// =============================================================
// Key concept: Fixed-width integers from <cstdint> guarantee exact sizes.
// Examples: std::int8_t, std::int16_t, std::int32_t, std::int64_t
// and their unsigned counterparts.
//
// Pitfall: std::int8_t and std::uint8_t often behave like char,
// printing characters instead of numbers. Use static_cast<int>() to
// print their numeric values.
//
// std::size_t is an unsigned type used for object sizes (returned by sizeof).

#include <cstddef> // For std::size_t
#include <cstdint> // For fixed-width integer types
#include <iostream>

int main()
{
    std::cout << "=== Fixed-Width Integers ===\n\n";

    // Fixed-width signed integers
    std::int8_t i8{65};
    std::int16_t i16{30000};
    std::int32_t i32{2'000'000'000}; // Digit separator for readability
    std::int64_t i64{9'000'000'000'000'000'000};

    std::cout << "--- Fixed-width signed types ---\n";
    std::cout << "std::int8_t  sizeof: " << sizeof(std::int8_t) << " byte(s)\n";
    std::cout << "std::int16_t sizeof: " << sizeof(std::int16_t) << " byte(s)\n";
    std::cout << "std::int32_t sizeof: " << sizeof(std::int32_t) << " byte(s)\n";
    std::cout << "std::int64_t sizeof: " << sizeof(std::int64_t) << " byte(s)\n";
    std::cout << '\n';

    // Pitfall: int8_t often prints as a character!
    std::cout << "--- int8_t pitfall ---\n";
    std::cout << "i8 direct print:        " << i8 << " (prints as char 'A'!)\n";
    std::cout << "i8 with static_cast:    " << static_cast<int>(i8) << " (prints numeric value 65)\n";
    std::cout << '\n';

    // Other fixed-width types print correctly
    std::cout << "i16: " << i16 << '\n';
    std::cout << "i32: " << i32 << '\n';
    std::cout << "i64: " << i64 << '\n';
    std::cout << '\n';

    // Unsigned fixed-width integers
    std::uint8_t u8{255};
    std::uint32_t u32{4'000'000'000u};

    std::cout << "--- Fixed-width unsigned types ---\n";
    std::cout << "uint8_t  (255): " << static_cast<int>(u8) << " (need static_cast for numeric output)\n";
    std::cout << "uint32_t:       " << u32 << '\n';
    std::cout << '\n';

    // std::size_t - the type returned by sizeof
    std::cout << "--- std::size_t ---\n";
    std::size_t sizeOfInt{sizeof(int)};
    std::cout << "sizeof(int) = " << sizeOfInt << " bytes\n";
    std::cout << "sizeof(std::size_t) = " << sizeof(std::size_t) << " bytes\n";
    std::cout << "std::size_t is unsigned and typically 4 or 8 bytes.\n";
    std::cout << '\n';

    // Best practice
    std::cout << "--- Best Practice ---\n";
    std::cout << "Use int when size doesn't matter.\n";
    std::cout << "Use std::int32_t or std::int64_t when a guaranteed range is needed.\n";
    std::cout << "Avoid fast/least types (inconsistent behavior across platforms).\n";

    return 0;
}
