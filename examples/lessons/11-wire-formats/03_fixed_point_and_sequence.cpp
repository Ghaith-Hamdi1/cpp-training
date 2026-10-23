// Lesson 19: amounts as scaled integers instead of double, and sequence-number gap detection with wraparound.
// Compile with -std=c++23.
#include <cstdint>
#include <iostream>
#include <optional>
#include <string_view>

// ---- fixed-point amount: an integer count of units (1 unit = 0.0001) ---------------------------------------------------
class Money {
    std::int64_t units_;
    explicit constexpr Money(std::int64_t t) : units_(t) {}
public:
    static constexpr std::int64_t kScale = 10000;
    static constexpr Money fromTicks(std::int64_t t) { return Money(t); }
    static constexpr Money fromParts(std::int64_t whole, std::int64_t frac) { return Money(whole * kScale + frac); }

    static std::optional<Money> parse(std::string_view s)           // "101.2500" or "101.25" or "7"
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
        while (fracDigits++ < 4) frac *= 10;                        // "25" means 2500 units
        return Money(whole * kScale + frac);
    }

    constexpr std::int64_t units() const { return units_; }
    constexpr Money operator+(Money o) const { return Money(units_ + o.units_); }
    constexpr Money operator-(Money o) const { return Money(units_ - o.units_); }
    constexpr bool operator==(const Money&) const = default;        // exact comparison: no epsilon needed
    constexpr auto operator<=>(const Money&) const = default;
};

void print(Money p)
{
    const auto t = p.units();
    std::cout << t / Money::kScale << '.';
    const auto f = t % Money::kScale;
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

    const Money a = *Money::parse("0.1"), b = *Money::parse("0.2"), c = *Money::parse("0.3");
    std::cout << "units: 0.1 + 0.2 = " << (a + b).units() << ", == 0.3 ? " << ((a + b) == c) << '\n';

    const auto low = *Money::parse("101.2500"), high = *Money::parse("101.27");
    std::cout << "low ";
    print(low);
    std::cout << "  high ";
    print(high);
    std::cout << "  spread ";
    print(high - low);
    std::cout << "  high > low ? " << (high > low) << '\n';
    std::cout << "5 decimals rejected: " << !Money::parse("1.23456").has_value()
              << ", letters rejected: " << !Money::parse("1.2x").has_value() << '\n';

    std::uint32_t expected = 100;
    for (std::uint32_t got : {100u, 101u, 103u, 102u, 103u}) {
        const SeqResult r = classify(expected, got);
        std::cout << "expected " << expected << " got " << got << ": " << name(r) << '\n';
        if (r == SeqResult::InOrder || r == SeqResult::Gap) expected = got + 1;
    }
    std::cout << "wraparound: expected 4294967295, got 0: " << name(classify(4294967295u, 0u))
              << "; expected 0, got 4294967295: " << name(classify(0u, 4294967295u)) << '\n';
}
