// Chapter 5 - Project 08: std::string Basics
// ==============================================
// Topics:
//   - Creating and initializing std::string
//   - String operations: length(), empty(), concatenation
//   - Accessing characters with [] and at()
//   - std::string manages dynamic memory automatically
//   - Copying std::string is expensive
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <string> // Required for std::string

int main()
{
    // -------------------------------------------------------
    // 1. Creating std::string objects
    // -------------------------------------------------------
    std::cout << "=== Creating Strings ===\n";

    std::string empty{};                   // Empty string ""
    std::string greeting{"Hello, World!"}; // From C-style string literal
    std::string name{"Alice"};
    std::string copy{greeting}; // Copy of greeting (expensive!)

    std::cout << "empty:    \"" << empty << "\"\n";
    std::cout << "greeting: \"" << greeting << "\"\n";
    std::cout << "name:     \"" << name << "\"\n";
    std::cout << "copy:     \"" << copy << "\"\n";

    // -------------------------------------------------------
    // 2. String length and empty check
    // -------------------------------------------------------
    std::cout << "\n=== Length and Empty ===\n";

    // length() returns the number of characters (excluding null terminator)
    // The return type is std::string::size_type (an unsigned integer)
    std::cout << "greeting.length() = " << greeting.length() << '\n';
    std::cout << "empty.length()    = " << empty.length() << '\n';

    // empty() returns true if the string has no characters
    std::cout << "greeting.empty()  = " << std::boolalpha << greeting.empty() << '\n';
    std::cout << "empty.empty()     = " << std::boolalpha << empty.empty() << '\n';

    // -------------------------------------------------------
    // 3. String concatenation
    // -------------------------------------------------------
    std::cout << "\n=== Concatenation ===\n";

    std::string first{"Hello"};
    std::string second{" World"};
    std::string combined{first + second + "!"}; // operator+ concatenates

    std::cout << "first + second + \"!\" = \"" << combined << "\"\n";

    // You can also append with +=:
    first += ", ";
    first += name;
    std::cout << "After += : \"" << first << "\"\n";

    // NOTE: You cannot concatenate two C-style string literals:
    // std::string bad = "Hello" + " World";  // ERROR: can't add two const char*
    // Fix: make at least one operand a std::string
    std::string good = std::string{"Hello"} + " World";
    std::cout << "std::string{\"Hello\"} + \" World\" = \"" << good << "\"\n";

    // -------------------------------------------------------
    // 4. Accessing individual characters
    // -------------------------------------------------------
    std::cout << "\n=== Character Access ===\n";

    std::string word{"Copilot"};

    // operator[] - no bounds checking (undefined behavior if out of range)
    std::cout << "word[0] = '" << word[0] << "'\n";
    std::cout << "word[3] = '" << word[3] << "'\n";

    // at() - throws std::out_of_range if index is out of bounds
    std::cout << "word.at(6) = '" << word.at(6) << "'\n";

    // Modify a character:
    word[0] = 'c';
    std::cout << "After word[0]='c': \"" << word << "\"\n";

    // -------------------------------------------------------
    // 5. Copying is expensive
    // -------------------------------------------------------
    std::cout << "\n=== Copying is Expensive ===\n";
    std::cout << "std::string manages dynamic memory internally.\n";
    std::cout << "Copying a std::string allocates new memory and copies all characters.\n";
    std::cout << "Avoid unnecessary copies - pass by reference or use std::string_view.\n";

    // This creates a full copy:
    std::string original{"A long string with lots of characters"};
    std::string duplicate{original}; // Expensive: allocate + copy

    std::cout << "original:  \"" << original << "\"\n";
    std::cout << "duplicate: \"" << duplicate << "\"\n";

    return 0;
}
