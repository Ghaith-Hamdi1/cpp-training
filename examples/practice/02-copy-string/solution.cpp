// Exercise 2: write your own strdup.
//
// Return a newly allocated copy of the C string s (allocate with new[]).
// Return nullptr if s is nullptr.
// Hints: allocate strlen(s) + 1 bytes, the +1 is for the '\0'. The copy must be independent
//        of the original: changing one must not change the other.
#include <cstddef>
#include <cstring>
#include "../check.h"

char* copyString(const char* s)
{
    if (s == nullptr) return nullptr;
    const std::size_t n = std::strlen(s);
    char* out = new char[n + 1];
    std::memcpy(out, s, n + 1);
    return out;
}

int main()
{
    char original[] = "hello";
    char* c = copyString(original);
    CHECK(c != nullptr && std::strcmp(c, "hello") == 0);
    CHECK(c != original);                      // a different block of memory
    if (c) c[0] = 'J';
    CHECK(std::strcmp(original, "hello") == 0); // the original is untouched
    delete[] c;

    c = copyString("");
    CHECK(c != nullptr && c[0] == '\0');
    delete[] c;

    CHECK(copyString(nullptr) == nullptr);
    return finish("02 copyString");
}
