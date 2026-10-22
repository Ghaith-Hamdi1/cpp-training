// Exercise 6: count the words in a C string.
//
// A word is a run of characters that are not whitespace. Whitespace means ' ', '\t', '\n', '\r'.
//   countWords("  a   b  ") is 2        countWords("") is 0        countWords(nullptr) is 0
// Hint: count the places where a word STARTS (a non-space that follows a space or the start).
#include <cstddef>
#include "../check.h"

std::size_t countWords(const char* s)
{
    if (s == nullptr) return 0;
    auto isSpace = [](char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; };
    std::size_t words = 0;
    bool inWord = false;
    for (; *s != '\0'; ++s) {
        if (isSpace(*s)) inWord = false;
        else if (!inWord) { inWord = true; ++words; }   // a new word starts here
    }
    return words;
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
