// Chapter O - Project 1: Bit Flags with std::bitset
//
// Key concept: std::bitset provides a convenient interface for manipulating
// individual bits by position. Member functions include test(), set(), reset(),
// flip(), count(), size(), any(), all(), and none().
//
// Note: std::bitset is optimized for speed, not memory. A std::bitset<8> will
// typically occupy 4 or 8 bytes (sizeof(size_t)), not 1 byte.

#include <bitset>
#include <iostream>

int main()
{
    // -----------------------------------------------------------------------
    // 1. Creating a std::bitset
    // -----------------------------------------------------------------------
    // Template parameter is the number of bits. The value can be initialized
    // from an integer or a binary string.
    std::bitset<8> flags{0b0000'0101}; // bits 0 and 2 are set
    std::cout << "Initial flags: " << flags << '\n';

    // -----------------------------------------------------------------------
    // 2. test() - query whether a specific bit is on
    // -----------------------------------------------------------------------
    // Bit positions are numbered right-to-left starting at 0.
    std::cout << "\ntest(0) = " << flags.test(0) << "  (bit 0 is on)\n";
    std::cout << "test(1) = " << flags.test(1) << "  (bit 1 is off)\n";
    std::cout << "test(2) = " << flags.test(2) << "  (bit 2 is on)\n";

    // -----------------------------------------------------------------------
    // 3. set() - turn a bit on (or set it to a specific value)
    // -----------------------------------------------------------------------
    flags.set(1); // turn on bit 1
    std::cout << "\nAfter set(1):   " << flags << '\n';

    flags.set(1, false); // set bit 1 to 0 (same as reset(1))
    std::cout << "After set(1,0): " << flags << '\n';

    // -----------------------------------------------------------------------
    // 4. reset() - turn a bit off
    // -----------------------------------------------------------------------
    flags.reset(0); // turn off bit 0
    std::cout << "\nAfter reset(0): " << flags << '\n';

    // -----------------------------------------------------------------------
    // 5. flip() - toggle a bit
    // -----------------------------------------------------------------------
    flags.flip(0); // was off → now on
    flags.flip(2); // was on  → now off
    std::cout << "After flip(0) and flip(2): " << flags << '\n';

    // -----------------------------------------------------------------------
    // 6. Aggregate queries: count(), size(), any(), all(), none()
    // -----------------------------------------------------------------------
    std::bitset<8> mixed{0b1010'0110};
    std::cout << "\nmixed = " << mixed << '\n';
    std::cout << "count() = " << mixed.count() << "  (number of 1-bits)\n";
    std::cout << "size()  = " << mixed.size() << "  (total bits)\n";
    std::cout << "any()   = " << mixed.any() << "  (at least one bit set?)\n";
    std::cout << "all()   = " << mixed.all() << "  (all bits set?)\n";
    std::cout << "none()  = " << mixed.none() << "  (no bits set?)\n";

    // -----------------------------------------------------------------------
    // 7. std::bitset does NOT save memory
    // -----------------------------------------------------------------------
    std::cout << "\nsizeof(std::bitset<1>)  = " << sizeof(std::bitset<1>) << " bytes\n";
    std::cout << "sizeof(std::bitset<8>)  = " << sizeof(std::bitset<8>) << " bytes\n";
    std::cout << "sizeof(std::bitset<32>) = " << sizeof(std::bitset<32>) << " bytes\n";
    std::cout << "sizeof(std::bitset<64>) = " << sizeof(std::bitset<64>) << " bytes\n";
    // Notice: even bitset<1> uses at least sizeof(size_t) bytes.

    return 0;
}
