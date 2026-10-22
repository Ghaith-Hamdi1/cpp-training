// Exercise 7: parse a sequence number from text (feed handlers do this all day).
//
// Convert the decimal digits in s to a number and store it in out.
// Return true on success. Return false, and leave out unchanged, when:
//   - s is nullptr or empty
//   - s contains anything other than the digits '0'..'9' (no sign, no spaces)
//   - the value does not fit in a 64-bit unsigned integer (overflow)
//   parseUnsigned("12345", n) returns true and n == 12345
// Hint: value = value * 10 + digit. Check for overflow BEFORE multiplying: the multiplication
//       is safe only if value <= (UINT64_MAX - digit) / 10.
#include <cstdint>
#include "../check.h"

bool parseUnsigned(const char* s, std::uint64_t& out)
{
    // TODO
    (void)s;
    (void)out;
    return false;
}

int main()
{
    std::uint64_t n = 7;
    CHECK(parseUnsigned("12345", n) && n == 12345);
    CHECK(parseUnsigned("0", n) && n == 0);
    CHECK(parseUnsigned("007", n) && n == 7);

    n = 99;
    CHECK(!parseUnsigned("", n));
    CHECK(!parseUnsigned("12a", n));
    CHECK(!parseUnsigned("-1", n));
    CHECK(!parseUnsigned(" 1", n));
    CHECK(!parseUnsigned(nullptr, n));
    CHECK(n == 99);                                   // out untouched on every failure

    CHECK(parseUnsigned("18446744073709551615", n) && n == UINT64_MAX);   // the largest value
    n = 5;
    CHECK(!parseUnsigned("18446744073709551616", n));                     // one more: overflow
    CHECK(!parseUnsigned("99999999999999999999999", n));
    CHECK(n == 5);
    return finish("07 parseUnsigned");
}
