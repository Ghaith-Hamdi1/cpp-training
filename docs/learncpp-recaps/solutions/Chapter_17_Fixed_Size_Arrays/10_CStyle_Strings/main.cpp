// Chapter 17 - Project 10: C-style Strings
// Topics: null termination, strlen, symbolic constants, pitfalls
// Compile: g++ -std=c++20 -Wall -Wextra -o program main.cpp

#include <iostream>
#include <cstring>     // std::strlen, std::strcpy
#include <string>      // std::string
#include <string_view> // std::string_view
#include <iterator>    // std::size

int main()
{
    // -----------------------------------------------------------------------
    // 1. C-style strings are char arrays terminated by '\0' (null character)
    //    The null terminator marks the end of the string.
    // -----------------------------------------------------------------------
    std::cout << "--- 1. Null-terminated strings ---\n";

    char greeting[]{"Hello"};
    // This is actually: {'H','e','l','l','o','\0'}  - 6 chars total

    std::cout << "greeting: " << greeting << '\n';
    std::cout << "Array size (with null): " << std::size(greeting) << '\n';    // 6
    std::cout << "String length (no null): " << std::strlen(greeting) << '\n'; // 5

    // -----------------------------------------------------------------------
    // 2. std::cout prints until it hits '\0'
    // -----------------------------------------------------------------------
    std::cout << "\n--- 2. Printing stops at null ---\n";

    char manual[]{'A', 'B', 'C', '\0', 'D', 'E'};
    std::cout << "manual: " << manual << '\n';                // prints "ABC" only
    std::cout << "Array size: " << std::size(manual) << '\n'; // 6

    // -----------------------------------------------------------------------
    // 3. String literal types
    //    "Alex" has type const char[5] (4 chars + null)
    //    It lives in read-only memory.
    // -----------------------------------------------------------------------
    std::cout << "\n--- 3. String literals ---\n";

    // const char name[] - creates a COPY of the literal on the stack
    const char name[]{"Alex"};

    // const char* - points directly to the literal in read-only memory
    const char *color{"Orange"};

    std::cout << "name  (copy):    " << name << '\n';
    std::cout << "color (pointer): " << color << '\n';

    // -----------------------------------------------------------------------
    // 4. PITFALL: buffer overflow
    //    Reading into a fixed-size char array without limiting input length
    //    can write past the array bounds - undefined behavior!
    // -----------------------------------------------------------------------
    std::cout << "\n--- 4. Buffer overflow risk ---\n";

    char buffer[10]{};
    // std::cin >> buffer;  // DANGEROUS: no length limit!
    // Use std::cin.getline(buffer, std::size(buffer)) instead, or better:
    // Use std::string which manages its own memory.
    std::cout << "Fixed buffer size: " << std::size(buffer) << '\n';
    std::cout << "Prefer std::string to avoid buffer overflow!\n";

    // -----------------------------------------------------------------------
    // 5. strlen vs sizeof
    //    strlen counts characters until '\0' (O(n) walk)
    //    sizeof returns the total byte size of the array
    // -----------------------------------------------------------------------
    std::cout << "\n--- 5. strlen vs sizeof ---\n";

    char word[]{"Hello"};
    std::cout << "std::strlen(word) = " << std::strlen(word) << '\n'; // 5
    std::cout << "sizeof(word)      = " << sizeof(word) << '\n';      // 6

    // -----------------------------------------------------------------------
    // 6. BEST PRACTICE: prefer std::string and std::string_view
    // -----------------------------------------------------------------------
    std::cout << "\n--- 6. Modern alternatives ---\n";

    std::string str{"std::string manages memory"};
    constexpr std::string_view sv{"constexpr string_view - no copy, no alloc"};

    std::cout << str << '\n';
    std::cout << sv << '\n';

    // -----------------------------------------------------------------------
    // 7. C-style symbolic constants: array vs pointer
    // -----------------------------------------------------------------------
    std::cout << "\n--- 7. Symbolic constants ---\n";

    const char arrConst[]{"Array copy"};        // stack copy
    const char *ptrConst{"Pointer to literal"}; // points to read-only memory

    std::cout << "arrConst: " << arrConst << "  (sizeof=" << sizeof(arrConst) << ")\n";
    std::cout << "ptrConst: " << ptrConst << "  (sizeof=" << sizeof(ptrConst) << ")\n";

    // Prefer:
    constexpr std::string_view modern{"Use string_view instead"};
    std::cout << "modern:   " << modern << '\n';

    // -----------------------------------------------------------------------
    // KEY TAKEAWAY:
    //   C-style strings are null-terminated char arrays that decay like
    //   any other C-style array. Avoid non-const C-style string objects.
    //   Prefer std::string for mutable strings and std::string_view for
    //   read-only string references.
    // -----------------------------------------------------------------------

    return 0;
}
