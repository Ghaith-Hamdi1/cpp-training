// Exercise 1: build an ID by joining two C strings (a classic C-string exercise).
//
// Return a newly allocated C string containing senderCompId + "-" + sequenceNumber.
//   buildExecutionId("XPAR", "12345") returns "XPAR-12345"
// Rules:
//   - the caller frees the result with delete[], so allocate with new[]
//   - return nullptr if either argument is nullptr
// Hints: strlen does not count the terminating '\0'. The result needs
//        len(a) + 1 (the dash) + len(b) + 1 (the '\0') bytes.
//        strcpy/strcat or memcpy both work. Never return a pointer to a local array.
#include <cstddef>
#include <cstring>
#include "../check.h"

char* buildExecutionId(const char* senderCompId, const char* sequenceNumber)
{
    // TODO
    (void)senderCompId;
    (void)sequenceNumber;
    return nullptr;
}

int main()
{
    char* r = buildExecutionId("XPAR", "12345");
    CHECK(r != nullptr && std::strcmp(r, "XPAR-12345") == 0);
    delete[] r;
    r = buildExecutionId("", "");
    CHECK(r != nullptr && std::strcmp(r, "-") == 0);
    delete[] r;
    r = buildExecutionId("A", "1");
    CHECK(r != nullptr && std::strcmp(r, "A-1") == 0 && std::strlen(r) == 3);
    delete[] r;
    CHECK(buildExecutionId(nullptr, "1") == nullptr);
    CHECK(buildExecutionId("A", nullptr) == nullptr);
    return finish("01 buildExecutionId");
}
