// Exercise 4: join many C strings with a separator (exercise 1, generalised).
//
// parts is an array of `count` C strings. Return a NEW string with all of them separated by sep.
//   {"a", "bb", "c"} with ',' gives "a,bb,c"
// count == 0 gives an empty string (still allocated with new[]).
// Hints: first loop over the parts to add up the total length, then allocate once,
//        then copy. Do not call strcat in a loop: it rescans the string every time.
#include <cstddef>
#include <cstring>
#include "../check.h"

char* joinAll(const char* const* parts, std::size_t count, char sep)
{
    std::size_t total = 0;
    for (std::size_t i = 0; i < count; ++i) total += std::strlen(parts[i]);
    if (count > 1) total += count - 1;                 // one separator between each pair
    char* out = new char[total + 1];
    char* p = out;
    for (std::size_t i = 0; i < count; ++i) {
        if (i > 0) *p++ = sep;
        const std::size_t n = std::strlen(parts[i]);
        std::memcpy(p, parts[i], n);
        p += n;
    }
    *p = '\0';
    return out;
}

int main()
{
    const char* abc[] = {"a", "bb", "c"};
    char* r = joinAll(abc, 3, ',');
    CHECK(r != nullptr && std::strcmp(r, "a,bb,c") == 0);
    delete[] r;

    const char* one[] = {"only"};
    r = joinAll(one, 1, ',');
    CHECK(r != nullptr && std::strcmp(r, "only") == 0);
    delete[] r;

    r = joinAll(nullptr, 0, ',');
    CHECK(r != nullptr && r[0] == '\0');
    delete[] r;

    const char* blanks[] = {"", "", ""};
    r = joinAll(blanks, 3, '-');
    CHECK(r != nullptr && std::strcmp(r, "--") == 0);
    delete[] r;

    const char* fix[] = {"8=FIX.4.2", "35=D", "49=XPAR"};
    r = joinAll(fix, 3, '|');
    CHECK(r != nullptr && std::strcmp(r, "8=FIX.4.2|35=D|49=XPAR") == 0);
    delete[] r;
    return finish("04 joinAll");
}
