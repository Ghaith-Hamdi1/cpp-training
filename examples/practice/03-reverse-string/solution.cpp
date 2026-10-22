// Exercise 3: reverse a C string.
//
// Return a NEW string with the characters of s in reverse order (allocate with new[]).
// The original must not change. Return nullptr if s is nullptr.
//   reversed("abc") returns "cba"
// Hints: allocate strlen(s) + 1, fill out[i] = s[n - 1 - i], and write the '\0' at out[n].
#include <cstddef>
#include <cstring>
#include "../check.h"

char* reversed(const char* s)
{
    if (s == nullptr) return nullptr;
    const std::size_t n = std::strlen(s);
    char* out = new char[n + 1];
    for (std::size_t i = 0; i < n; ++i) out[i] = s[n - 1 - i];
    out[n] = '\0';
    return out;
}

int main()
{
    char* r = reversed("abc");
    CHECK(r != nullptr && std::strcmp(r, "cba") == 0);
    delete[] r;
    r = reversed("hello world");
    CHECK(r != nullptr && std::strcmp(r, "dlrow olleh") == 0);
    delete[] r;
    r = reversed("a");
    CHECK(r != nullptr && std::strcmp(r, "a") == 0);
    delete[] r;
    r = reversed("");
    CHECK(r != nullptr && r[0] == '\0');
    delete[] r;
    char original[] = "xyz";
    r = reversed(original);
    CHECK(std::strcmp(original, "xyz") == 0);   // the input is not modified
    delete[] r;
    CHECK(reversed(nullptr) == nullptr);
    return finish("03 reversed");
}
