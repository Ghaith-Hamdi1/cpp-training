// Exercise 5: implement strlen and strcmp yourself, with pointers.
//
// myStrlen: the number of characters before the terminating '\0'.
// myStrcmp: return a negative number if a < b, 0 if equal, a positive number if a > b
//           (compare character by character; a shorter string that is a prefix is smaller).
// You may NOT call any function from <cstring>. Walk the strings with a pointer.
#include <cstddef>
#include "../check.h"

std::size_t myStrlen(const char* s)
{
    const char* p = s;
    while (*p != '\0') ++p;
    return static_cast<std::size_t>(p - s);       // pointer difference = number of characters
}

int myStrcmp(const char* a, const char* b)
{
    while (*a != '\0' && *a == *b) { ++a; ++b; }
    return static_cast<unsigned char>(*a) - static_cast<unsigned char>(*b);
}

int main()
{
    CHECK(myStrlen("") == 0);
    CHECK(myStrlen("a") == 1);
    CHECK(myStrlen("hello") == 5);
    char buf[] = {'h', 'i', '\0', 'x', '\0'};
    CHECK(myStrlen(buf) == 2);                     // stops at the first '\0'

    CHECK(myStrcmp("abc", "abc") == 0);
    CHECK(myStrcmp("", "") == 0);
    CHECK(myStrcmp("a", "b") < 0);
    CHECK(myStrcmp("b", "a") > 0);
    CHECK(myStrcmp("ab", "abc") < 0);              // prefix is smaller
    CHECK(myStrcmp("abc", "ab") > 0);
    CHECK(myStrcmp("", "a") < 0);
    return finish("05 myStrlen / myStrcmp");
}
