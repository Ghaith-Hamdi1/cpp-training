// Lesson 19: bit manipulation, struct layout and padding, endianness.
// Compile with -std=c++20 (uses <bit>). Expected values assume a typical 64-bit ABI (4-byte int, little-endian CPU).
#include <bit>
#include <cstddef>
#include <cstdint>
#include <iostream>

// ---- bit manipulation ----------------------------------------------------------------------------------------------
constexpr std::uint32_t setBit(std::uint32_t x, unsigned n)    { return x | (1u << n); }
constexpr std::uint32_t clearBit(std::uint32_t x, unsigned n)  { return x & ~(1u << n); }
constexpr std::uint32_t toggleBit(std::uint32_t x, unsigned n) { return x ^ (1u << n); }
constexpr bool testBit(std::uint32_t x, unsigned n)            { return (x >> n) & 1u; }
constexpr bool isPowerOfTwo(std::uint32_t x)                   { return x != 0 && (x & (x - 1)) == 0; }

int countBits(std::uint32_t x)                                 // Kernighan: each step clears the lowest set bit
{
    int n = 0;
    for (; x != 0; x &= x - 1) ++n;
    return n;
}

// a flags byte: bit 0 = ack, bit 1 = urgent, bits 2..4 = channel code (3 bits)
constexpr std::uint8_t kAck = 1u << 0;
constexpr std::uint8_t kUrgent = 1u << 1;
constexpr unsigned channelOf(std::uint8_t flags) { return (flags >> 2) & 0x7u; }   // shift down, then mask

// ---- struct layout --------------------------------------------------------------------------------------------------
struct Careless { char a; int b; char c; };                    // padding after a, and after c
struct Ordered  { int b; char a; char c; };                    // same members, largest first
#pragma pack(push, 1)
struct Packed   { char a; int b; char c; };                    // no padding: 6 bytes, but b may be unaligned
#pragma pack(pop)

static_assert(sizeof(Careless) == 12 && alignof(Careless) == 4);
static_assert(sizeof(Ordered) == 8);
static_assert(sizeof(Packed) == 6);
static_assert(offsetof(Careless, b) == 4 && offsetof(Careless, c) == 8);

// ---- endianness -----------------------------------------------------------------------------------------------------
constexpr std::uint32_t readBe32(const unsigned char* p)       // portable on ANY CPU: assemble the value with shifts
{
    return (std::uint32_t{p[0]} << 24) | (std::uint32_t{p[1]} << 16) | (std::uint32_t{p[2]} << 8) | std::uint32_t{p[3]};
}
constexpr std::uint32_t byteSwap32(std::uint32_t v)
{
    return (v >> 24) | ((v >> 8) & 0x0000FF00u) | ((v << 8) & 0x00FF0000u) | (v << 24);
}

int main()
{
    std::cout << std::boolalpha;
    std::uint32_t x = 0b0101;
    std::cout << "setBit(5,1)=" << setBit(x, 1) << " clearBit(5,0)=" << clearBit(x, 0)
              << " toggleBit(5,2)=" << toggleBit(x, 2) << " testBit(5,2)=" << testBit(x, 2) << '\n';
    std::cout << "isPowerOfTwo: 64 " << isPowerOfTwo(64) << ", 96 " << isPowerOfTwo(96) << ", 0 " << isPowerOfTwo(0) << '\n';
    std::cout << "countBits(0xF0F0)=" << countBits(0xF0F0) << " std::popcount=" << std::popcount(0xF0F0u) << '\n';

    std::uint8_t flags = kAck | kUrgent | (5u << 2);               // ack, urgent, channel 5
    std::cout << "flags=0x" << std::hex << int(flags) << std::dec << " ack=" << bool(flags & kAck)
              << " urgent=" << bool(flags & kUrgent) << " channel=" << channelOf(flags) << '\n';

    std::cout << "sizeof Careless=" << sizeof(Careless) << " Ordered=" << sizeof(Ordered) << " Packed=" << sizeof(Packed)
              << " alignof(int)=" << alignof(int) << '\n';
    std::cout << "offsets in Careless: a=" << offsetof(Careless, a) << " b=" << offsetof(Careless, b) << " c=" << offsetof(Careless, c) << '\n';

    std::uint32_t value = 0x12345678;
    const auto* bytes = reinterpret_cast<const unsigned char*>(&value);   // looking at an object as bytes is always allowed
    std::cout << "0x12345678 in memory: " << std::hex;
    for (int i = 0; i < 4; ++i) std::cout << int(bytes[i]) << (i < 3 ? " " : "");
    std::cout << std::dec << (std::endian::native == std::endian::little ? "   (little-endian CPU)" : "   (big-endian CPU)") << '\n';

    const unsigned char wire[] = {0x12, 0x34, 0x56, 0x78};      // network order = big-endian
    std::cout << "readBe32 gives 0x" << std::hex << readBe32(wire) << ", byteSwap32(0x12345678)=0x" << byteSwap32(0x12345678) << '\n';
}
