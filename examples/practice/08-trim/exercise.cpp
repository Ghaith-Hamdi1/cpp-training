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
    // TODO
    (void)s;
    return nullptr;
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
