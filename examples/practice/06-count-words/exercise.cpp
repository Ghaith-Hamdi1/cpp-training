// Exercise 6: count the words in a C string.
//
// A word is a run of characters that are not whitespace. Whitespace means ' ', '\t', '\n', '\r'.
//   countWords("  a   b  ") is 2        countWords("") is 0        countWords(nullptr) is 0
// Hint: count the places where a word STARTS (a non-space that follows a space or the start).
#include <cstddef>
#include "../check.h"

std::size_t countWords(const char* s)
{
    // TODO
    (void)s;
    return 0;
}

int main()
{
    CHECK(countWords("hello world") == 2);
    CHECK(countWords("  a   b  ") == 2);
    CHECK(countWords("") == 0);
    CHECK(countWords("   ") == 0);
    CHECK(countWords("one") == 1);
    CHECK(countWords("a\tb\nc") == 3);
    CHECK(countWords("8=FIX.4.2 35=D") == 2);
    CHECK(countWords(nullptr) == 0);
    return finish("06 countWords");
}
