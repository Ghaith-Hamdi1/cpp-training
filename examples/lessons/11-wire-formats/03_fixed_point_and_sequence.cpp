// Lesson 19: prices as scaled integers instead of double, and sequence-number gap detection with wraparound.
// Compile with -std=c++20.
#include <cstdint>
#include <iostream>
#include <optional>
#include <string_view>

// ---- fixed-point price: an integer count of ticks (1 tick = 0.0001) ---------------------------------------------------
class Price {
    std::int64_t ticks_;
    explicit constexpr Price(std::int64_t t) : ticks_(t) {}
public:
    static constexpr std::int64_t kScale = 10000;
    static constexpr Price fromTicks(std::int64_t t) { return Price(t); }
    static constexpr Price fromParts(std::int64_t whole, std::int64_t frac) { return Price(whole * kScale + frac); }

    static std::optional<Price> parse(std::string_view s)           // "101.2500" or "101.25" or "7"
    {
        std::int64_t whole = 0, frac = 0, fracDigits = 0;
        std::size_t i = 0;
        if (s.empty()) return std::nullopt;
        for (; i < s.size() && s[i] != '.'; ++i) {
            if (s[i] < '0' || s[i] > '9') return std::nullopt;
            whole = whole * 10 + (s[i] - '0');
        }
        if (i < s.size()) {
            for (++i; i < s.size(); ++i) {
                if (s[i] < '0' || s[i] > '9' || fracDigits == 4) return std::nullopt;   // more than 4 decimals: reject
                frac = frac * 10 + (s[i] - '0');
                ++fracDigits;
            }
        }
        while (fracDigits++ < 4) frac *= 10;                        // "25" means 2500 ticks
        return Price(whole * kScale + frac);
    }

    constexpr std::int64_t ticks() const { return ticks_; }
    constexpr Price operator+(Price o) const { return Price(ticks_ + o.ticks_); }
    constexpr Price operator-(Price o) const { return Price(ticks_ - o.ticks_); }
    constexpr bool operator==(const Price&) const = default;        // exact comparison: no epsilon needed
    constexpr auto operator<=>(const Price&) const = default;
};

void print(Price p)
{
    const auto t = p.ticks();
    std::cout << t / Price::kScale << '.';
    const auto f = t % Price::kScale;
    std::cout << (f < 1000 ? "0" : "") << (f < 100 ? "0" : "") << (f < 10 ? "0" : "") << f;
}

// ---- sequence numbers --------------------------------------------------------------------------------------------------
enum class SeqResult { InOrder, Duplicate, Gap };

SeqResult classify(std::uint32_t expected, std::uint32_t received)
{
    const std::int32_t diff = static_cast<std::int32_t>(received - expected);   // unsigned subtraction wraps; reinterpret as signed
    if (diff == 0) return SeqResult::InOrder;
    return diff < 0 ? SeqResult::Duplicate : SeqResult::Gap;
}

const char* name(SeqResult r) { return r == SeqResult::InOrder ? "in order" : r == SeqResult::Duplicate ? "duplicate/old" : "GAP"; }

int main()
{
    std::cout.precision(17);
    std::cout << "double: 0.1 + 0.2 = " << 0.1 + 0.2 << ", == 0.3 ? " << std::boolalpha << (0.1 + 0.2 == 0.3) << '\n';

    const Price a = *Price::parse("0.1"), b = *Price::parse("0.2"), c = *Price::parse("0.3");
    std::cout << "ticks: 0.1 + 0.2 = " << (a + b).ticks() << ", == 0.3 ? " << ((a + b) == c) << '\n';

    const auto bid = *Price::parse("101.2500"), ask = *Price::parse("101.27");
    std::cout << "bid ";
    print(bid);
    std::cout << "  ask ";
    print(ask);
    std::cout << "  spread ";
    print(ask - bid);
    std::cout << "  ask > bid ? " << (ask > bid) << '\n';
    std::cout << "5 decimals rejected: " << !Price::parse("1.23456").has_value()
              << ", letters rejected: " << !Price::parse("1.2x").has_value() << '\n';

    std::uint32_t expected = 100;
    for (std::uint32_t got : {100u, 101u, 103u, 102u, 103u}) {
        const SeqResult r = classify(expected, got);
        std::cout << "expected " << expected << " got " << got << ": " << name(r) << '\n';
        if (r == SeqResult::InOrder || r == SeqResult::Gap) expected = got + 1;
    }
    std::cout << "wraparound: expected 4294967295, got 0: " << name(classify(4294967295u, 0u))
              << "; expected 0, got 4294967295: " << name(classify(0u, 4294967295u)) << '\n';
}
