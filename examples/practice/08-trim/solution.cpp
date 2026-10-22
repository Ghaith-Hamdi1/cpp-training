// Exercise 8: trim whitespace from both ends of a C string.
//
// Return a NEW string (allocate with new[]) without leading or trailing whitespace
// (' ', '\t', '\n', '\r'). Spaces inside the text stay. Return nullptr if s is nullptr.
//   trimmed("  hi there  ") returns "hi there"       trimmed("   ") returns ""
// Hint: find the first non-space and the last non-space, then copy that range.
#include <cstddef>
#include <cstring>
#include "../check.h"

char* trimmed(const char* s)
{
    if (s == nullptr) return nullptr;
    auto isSpace = [](char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; };
    const char* begin = s;
    while (*begin != '\0' && isSpace(*begin)) ++begin;
    const char* end = begin + std::strlen(begin);
    while (end > begin && isSpace(*(end - 1))) --end;
    const std::size_t n = static_cast<std::size_t>(end - begin);
    char* out = new char[n + 1];
    std::memcpy(out, begin, n);
    out[n] = '\0';
    return out;
}

int main()
{
    char* r = trimmed("  hi there  ");
    CHECK(r != nullptr && std::strcmp(r, "hi there") == 0);
    delete[] r;
    r = trimmed("hi");
    CHECK(r != nullptr && std::strcmp(r, "hi") == 0);
    delete[] r;
    r = trimmed("   ");
    CHECK(r != nullptr && r[0] == '\0');
    delete[] r;
    r = trimmed("");
    CHECK(r != nullptr && r[0] == '\0');
    delete[] r;
    r = trimmed("\t a b \n");
    CHECK(r != nullptr && std::strcmp(r, "a b") == 0);
    delete[] r;
    CHECK(trimmed(nullptr) == nullptr);
    return finish("08 trimmed");
}
