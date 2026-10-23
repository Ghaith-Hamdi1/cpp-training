// Exercise 15: vocabulary types: optional, variant and visit. Worked solution.
// Build: g++ -std=c++20 -Wall -Wextra solution.cpp -o sol && ./sol
#include <charconv>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include "../check.h"

using Value = std::variant<int, double, std::string>;

std::optional<int> parsePort(std::string_view s)
{
    int v = 0;
    auto r = std::from_chars(s.data(), s.data() + s.size(), v);
    if (r.ec != std::errc{} || r.ptr != s.data() + s.size()) return std::nullopt;   // the WHOLE text must be a number
    if (v < 1 || v > 65535) return std::nullopt;
    return v;
}

Value parseValue(std::string_view s)
{
    int i = 0;
    auto ri = std::from_chars(s.data(), s.data() + s.size(), i);
    if (ri.ec == std::errc{} && ri.ptr == s.data() + s.size()) return i;
    double d = 0;
    auto rd = std::from_chars(s.data(), s.data() + s.size(), d);
    if (rd.ec == std::errc{} && rd.ptr == s.data() + s.size()) return d;
    return std::string(s);
}

std::string describe(const Value& v)
{
    return std::visit([](const auto& x) -> std::string {
        using T = std::decay_t<decltype(x)>;
        if constexpr (std::is_same_v<T, int>) return "int " + std::to_string(x);
        else if constexpr (std::is_same_v<T, double>) {
            std::string t = std::to_string(x);                       // "2.500000": trim the trailing zeros
            t.erase(t.find_last_not_of('0') + 1);
            if (t.back() == '.') t.push_back('0');
            return "double " + t;
        } else return "text " + x;
    }, v);
}

int main()
{
    CHECK(parsePort("8080") == 8080);
    CHECK(parsePort("1") == 1);
    CHECK(parsePort("65535") == 65535);
    CHECK(!parsePort("0"));
    CHECK(!parsePort("65536"));
    CHECK(!parsePort("80x"));
    CHECK(!parsePort(""));
    CHECK(!parsePort("-5"));
    CHECK(parsePort("443").value_or(-1) == 443);
    CHECK(parsePort("nope").value_or(-1) == -1);

    CHECK(describe(parseValue("42")) == "int 42");
    CHECK(describe(parseValue("-7")) == "int -7");
    CHECK(describe(parseValue("2.5")) == "double 2.5");
    CHECK(describe(parseValue("hello")) == "text hello");
    CHECK(describe(parseValue("12abc")) == "text 12abc");
    CHECK(describe(parseValue("")) == "text ");
    CHECK(parseValue("42").index() == 0 && parseValue("2.5").index() == 1 && parseValue("x").index() == 2);
    return finish("15 parse and describe");
}
