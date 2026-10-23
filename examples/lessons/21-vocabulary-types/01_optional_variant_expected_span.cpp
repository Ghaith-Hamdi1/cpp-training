// Lesson 10: the vocabulary types: pair/tuple, optional, variant + visit, expected (C++23) and span.
// Build: g++ -std=c++23 -Wall -Wextra 21-vocabulary-types/01_optional_variant_expected_span.cpp -o vocab && ./vocab
#include <charconv>
#include <expected>
#include <iostream>
#include <map>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <tuple>
#include <variant>
#include <vector>

// --- pair, tuple, structured bindings -------------------------------------------------------------------------
std::pair<int, int> minmax(const std::vector<int>& v) {
    int lo = v[0], hi = v[0];
    for (int x : v) { if (x < lo) lo = x; if (x > hi) hi = x; }
    return {lo, hi};
}

// --- optional ---------------------------------------------------------------------------------------------------
std::optional<int> parseInt(std::string_view s) {
    int v = 0;
    auto r = std::from_chars(s.data(), s.data() + s.size(), v);
    if (r.ec != std::errc{} || r.ptr != s.data() + s.size()) return std::nullopt;
    return v;
}

// --- variant + visit ------------------------------------------------------------------------------------------------
template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

struct Circle { double r; };
struct Rect { double w, h; };
using Shape = std::variant<Circle, Rect>;

double area(const Shape& s) {
    return std::visit(overloaded{
        [](const Circle& c) { return 3.0 * c.r * c.r; },
        [](const Rect& r) { return r.w * r.h; }}, s);
}

// --- expected -------------------------------------------------------------------------------------------------------
enum class ParseError { Empty, NotANumber };
std::expected<int, ParseError> parse(std::string_view s) {
    if (s.empty()) return std::unexpected(ParseError::Empty);
    if (auto n = parseInt(s)) return *n;
    return std::unexpected(ParseError::NotANumber);
}

// --- span -----------------------------------------------------------------------------------------------------------
long sum(std::span<const int> xs) { long t = 0; for (int x : xs) t += x; return t; }

int main() {
    auto [lo, hi] = minmax({3, 9, 1, 7});
    std::cout << "minmax " << lo << ' ' << hi << '\n';
    auto t = std::make_tuple(1, 2.5, std::string("x"));
    std::cout << "tuple " << std::get<1>(t) << ' ' << std::get<std::string>(t) << '\n';
    std::map<std::string, int> m{{"a", 1}};
    auto [it, inserted] = m.insert({"a", 2});
    std::cout << "insert " << inserted << ' ' << it->second << '\n';

    std::cout << "optional " << parseInt("42").value_or(-1) << ' ' << parseInt("4x").value_or(-1) << ' ' << parseInt("").has_value() << '\n';
    try { std::optional<int> e; (void)e.value(); } catch (const std::bad_optional_access&) { std::cout << "value() on empty throws bad_optional_access\n"; }
    std::cout << "sizeof(int)=" << sizeof(int) << " sizeof(optional<int>)=" << sizeof(std::optional<int>) << '\n';

    std::vector<Shape> shapes{Circle{2}, Rect{3, 4}};
    double total = 0;
    for (const auto& s : shapes) total += area(s);
    std::cout << "variant total " << total << ", index of first " << shapes[0].index() << '\n';
    std::variant<int, std::string> v = 7;
    std::cout << "holds_alternative<int> " << std::holds_alternative<int>(v) << ", get_if<string> " << (std::get_if<std::string>(&v) == nullptr) << '\n';
    try { (void)std::get<std::string>(v); } catch (const std::bad_variant_access&) { std::cout << "get<wrong type> throws bad_variant_access\n"; }
    std::variant<int, std::string> d;
    std::cout << "default variant holds index " << d.index() << '\n';

    for (std::string_view s : {"12", "", "x1"}) {
        auto r = parse(s);
        if (r) std::cout << "expected value " << *r << '\n';
        else std::cout << "expected error " << static_cast<int>(r.error()) << '\n';
    }
    std::cout << "value_or " << parse("zz").value_or(0) << '\n';

    std::vector<int> vec{1, 2, 3, 4, 5};
    int arr[3] = {10, 20, 30};
    std::cout << "span " << sum(vec) << ' ' << sum(arr) << ' ' << sum(std::span(vec).subspan(1, 3)) << ' ' << sum(std::span(vec).first(2)) << '\n';
    std::cout << "sizeof(span)=" << sizeof(std::span<int>) << '\n';
}
