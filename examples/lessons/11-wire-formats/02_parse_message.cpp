// Lesson 17: reading a binary message safely (memcpy, no casts of the buffer) and a zero-copy text parser
// (string_view + from_chars). Compile with -std=c++20.
#include <array>
#include <charconv>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <optional>
#include <string_view>

// ---- binary: a Trade message, all integers big-endian ---------------------------------------------------------------
// [type:1][length:2][seq:4][price:8, scaled by 10^4][qty:4]   = 19 bytes
struct Trade {
    std::uint32_t seq;
    std::int64_t  priceTicks;                     // price * 10000
    std::uint32_t qty;
};

template <typename T>
T loadBe(const unsigned char* p)                  // copy the bytes out, then assemble: no aliasing, no alignment problem
{
    T v = 0;
    for (std::size_t i = 0; i < sizeof(T); ++i) v = static_cast<T>((v << 8) | p[i]);
    return v;
}

template <typename T>
void storeBe(unsigned char* p, T v)
{
    for (std::size_t i = sizeof(T); i-- > 0; ) { p[i] = static_cast<unsigned char>(v & 0xFF); v = static_cast<T>(v >> 8); }
}

constexpr std::size_t kTradeSize = 19;

std::optional<Trade> parseTrade(const unsigned char* buf, std::size_t len)
{
    if (len < kTradeSize) return std::nullopt;                      // never read past the end
    if (buf[0] != 'T') return std::nullopt;                         // wrong message type
    if (loadBe<std::uint16_t>(buf + 1) != kTradeSize) return std::nullopt;   // length field must match
    Trade t;
    t.seq        = loadBe<std::uint32_t>(buf + 3);
    t.priceTicks = static_cast<std::int64_t>(loadBe<std::uint64_t>(buf + 7));
    t.qty        = loadBe<std::uint32_t>(buf + 15);
    return t;
}

// ---- text: "35=D|49=XPAR|34=12345|44=101.2500|" -----------------------------------------------------------------------
struct Field { int tag; std::string_view value; };

std::optional<Field> nextField(std::string_view& rest)             // returns a view INTO the buffer: no allocation
{
    const auto bar = rest.find('|');
    if (bar == std::string_view::npos) return std::nullopt;
    const std::string_view item = rest.substr(0, bar);
    rest.remove_prefix(bar + 1);                                    // advance the cursor
    const auto eq = item.find('=');
    if (eq == std::string_view::npos) return std::nullopt;
    Field f{};
    const auto r = std::from_chars(item.data(), item.data() + eq, f.tag);   // no locale, no allocation, no exceptions
    if (r.ec != std::errc{} || r.ptr != item.data() + eq) return std::nullopt;
    f.value = item.substr(eq + 1);
    return f;
}

int main()
{
    std::array<unsigned char, kTradeSize> buf{};
    buf[0] = 'T';
    storeBe<std::uint16_t>(buf.data() + 1, kTradeSize);
    storeBe<std::uint32_t>(buf.data() + 3, 12345);
    storeBe<std::int64_t>(buf.data() + 7, 1012500);                 // 101.2500 as ticks
    storeBe<std::uint32_t>(buf.data() + 15, 300);

    if (auto t = parseTrade(buf.data(), buf.size()))
        std::cout << "trade seq=" << t->seq << " price=" << t->priceTicks / 10000 << '.' << t->priceTicks % 10000
                  << " qty=" << t->qty << '\n';
    std::cout << "truncated: " << (parseTrade(buf.data(), 10) ? "parsed" : "rejected") << '\n';
    buf[1] = 0x7F;                                                  // corrupt the length field
    std::cout << "bad length: " << (parseTrade(buf.data(), buf.size()) ? "parsed" : "rejected") << '\n';

    std::string_view msg = "35=D|49=XPAR|34=12345|44=101.2500|";
    std::cout << "fields:";
    while (auto f = nextField(msg)) std::cout << ' ' << f->tag << "->[" << f->value << ']';
    std::cout << '\n';

    std::uint32_t seq = 0;
    std::string_view s = "12345";
    auto r = std::from_chars(s.data(), s.data() + s.size(), seq);
    std::cout << "from_chars: " << seq << (r.ec == std::errc{} ? " ok" : " error") << '\n';
    s = "12x";
    r = std::from_chars(s.data(), s.data() + s.size(), seq);
    std::cout << "stops at: '" << *r.ptr << "' (" << (r.ptr - s.data()) << " characters consumed)\n";
}
