// Chapter O - Project 3: Bit Masks
//
// A bit mask is a value with specific bits set to 1, used to select which
// bits a bitwise operation should affect. The four essential mask operations:
//
//   TEST  a bit:  flags & mask        → nonzero if the bit is set
//   SET   a bit:  flags |= mask       → turns the bit on
//   RESET a bit:  flags &= ~mask      → turns the bit off
//   FLIP  a bit:  flags ^= mask       → toggles the bit
//
// Masks can be defined using:
//   - Binary literals:  constexpr std::uint8_t mask{ 0b0000'0100 };
//   - Hex literals:     constexpr std::uint8_t mask{ 0x04 };
//   - Left shift:       constexpr std::uint8_t mask{ 1 << 2 };

#include <cstdint>
#include <iostream>
#include <bitset>

int main()
{
    // -----------------------------------------------------------------------
    // 1. Define meaningful bit masks using the left-shift operator
    // -----------------------------------------------------------------------
    // Best practice: give masks descriptive names, not "mask0", "mask1"
    constexpr std::uint8_t mask_isAlive{1 << 0};     // bit 0 - 0000'0001
    constexpr std::uint8_t mask_hasPoison{1 << 1};   // bit 1 - 0000'0010
    constexpr std::uint8_t mask_hasShield{1 << 2};   // bit 2 - 0000'0100
    constexpr std::uint8_t mask_isBoss{1 << 3};      // bit 3 - 0000'1000
    constexpr std::uint8_t mask_isFlying{1 << 4};    // bit 4 - 0001'0000
    constexpr std::uint8_t mask_isInvisible{1 << 5}; // bit 5 - 0010'0000
    // bits 6-7 unused

    std::uint8_t entityFlags{0};

    // -----------------------------------------------------------------------
    // 2. SET bits - turn flags on with |=
    // -----------------------------------------------------------------------
    entityFlags |= mask_isAlive;   // entity is alive
    entityFlags |= mask_hasShield; // entity has a shield
    entityFlags |= mask_isFlying;  // entity can fly

    std::cout << "After setting alive, shield, flying:\n";
    std::cout << "  flags = " << std::bitset<8>(entityFlags) << '\n';

    // You can set multiple bits at once by OR-ing masks together:
    entityFlags |= (mask_hasPoison | mask_isBoss);
    std::cout << "After also setting poison and boss:\n";
    std::cout << "  flags = " << std::bitset<8>(entityFlags) << '\n';

    // -----------------------------------------------------------------------
    // 3. TEST bits - check if a flag is on with &
    // -----------------------------------------------------------------------
    std::cout << "\nTesting individual flags:\n";
    std::cout << "  isAlive?     " << ((entityFlags & mask_isAlive) ? "yes" : "no") << '\n';
    std::cout << "  hasPoison?   " << ((entityFlags & mask_hasPoison) ? "yes" : "no") << '\n';
    std::cout << "  hasShield?   " << ((entityFlags & mask_hasShield) ? "yes" : "no") << '\n';
    std::cout << "  isBoss?      " << ((entityFlags & mask_isBoss) ? "yes" : "no") << '\n';
    std::cout << "  isFlying?    " << ((entityFlags & mask_isFlying) ? "yes" : "no") << '\n';
    std::cout << "  isInvisible? " << ((entityFlags & mask_isInvisible) ? "yes" : "no") << '\n';

    // -----------------------------------------------------------------------
    // 4. RESET bits - turn flags off with &= ~mask
    // -----------------------------------------------------------------------
    // Common pitfall: using &= mask instead of &= ~mask clears everything
    // EXCEPT the masked bit - the opposite of what you want!
    entityFlags &= ~mask_hasPoison; // cure poison
    entityFlags &= ~mask_isFlying;  // ground the entity

    std::cout << "\nAfter resetting poison and flying:\n";
    std::cout << "  flags = " << std::bitset<8>(entityFlags) << '\n';
    std::cout << "  hasPoison?   " << ((entityFlags & mask_hasPoison) ? "yes" : "no") << '\n';
    std::cout << "  isFlying?    " << ((entityFlags & mask_isFlying) ? "yes" : "no") << '\n';

    // -----------------------------------------------------------------------
    // 5. FLIP bits - toggle flags with ^=
    // -----------------------------------------------------------------------
    entityFlags ^= mask_isInvisible; // toggle invisibility on
    std::cout << "\nAfter flipping invisibility:\n";
    std::cout << "  flags = " << std::bitset<8>(entityFlags) << '\n';
    std::cout << "  isInvisible? " << ((entityFlags & mask_isInvisible) ? "yes" : "no") << '\n';

    entityFlags ^= mask_isInvisible; // toggle invisibility off
    std::cout << "After flipping invisibility again:\n";
    std::cout << "  isInvisible? " << ((entityFlags & mask_isInvisible) ? "yes" : "no") << '\n';

    // -----------------------------------------------------------------------
    // 6. Testing multiple bits at once
    // -----------------------------------------------------------------------
    std::uint8_t requiredFlags{static_cast<std::uint8_t>(mask_isAlive | mask_hasShield)};

    // Check if ALL required flags are set:
    if ((entityFlags & requiredFlags) == requiredFlags)
        std::cout << "\nEntity is alive AND has a shield.\n";

    // Check if ANY of the required flags are set:
    if (entityFlags & requiredFlags)
        std::cout << "Entity has at least one of: alive, shield.\n";

    return 0;
}
