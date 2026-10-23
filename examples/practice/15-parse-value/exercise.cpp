// Exercise 15: vocabulary types: optional, variant and visit.
//
//   std::optional<int> parsePort(std::string_view s)
//       the whole text must be a number from 1 to 65535, otherwise return std::nullopt
//       (hint: std::from_chars, and check that it consumed everything)
//   Value parseValue(std::string_view s)
//       Value is std::variant<int, double, std::string>.
//       Return an int if the whole text is an integer, else a double if the whole text is a
//       decimal number, else the text itself as a std::string.
//   std::string describe(const Value& v)
//       "int 42", "double 2.5" or "text hi", using std::visit (no if chains, no std::get).
// Build: g++ -std=c++20 -Wall -Wextra exercise.cpp -o ex && ./ex
#include <charconv>
#include <optional>
#include <string>
#include <string_view>
#include <variant>
#include "../check.h"

using Value = std::variant<int, double, std::string>;

std::optional<int> parsePort(std::string_view s) { (void)s; return std::nullopt; }   // TODO
Value parseValue(std::string_view s) { (void)s; return std::string(); }              // TODO
std::string describe(const Value& v) { (void)v; return ""; }                         // TODO

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
