// Chapter 5 - Project 10: std::string_view
// ==========================================
// Topics:
//   - std::string_view provides read-only, non-owning access to a string
//   - Cheap to copy (just a pointer + length)
//   - Accepts C-style strings, std::string, or other string_views
//   - Preferred type for read-only string function parameters
//   - std::string_view will NOT implicitly convert to std::string
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <string>
#include <string_view>

// -------------------------------------------------------
// Function taking std::string_view - preferred for read-only strings
// -------------------------------------------------------
// This accepts C-style strings, std::string, and std::string_view
// without any copying.
void printGreeting(std::string_view name)
{
    // string_view is cheap to copy (it's just a pointer + length).
    // No dynamic memory allocation happens here.
    std::cout << "Hello, " << name << "!\n";
}

// For comparison - this function COPIES the entire string:
void printGreetingExpensive(std::string name) // Expensive copy!
{
    std::cout << "Hello, " << name << "! (copied)\n";
}

int main()
{
    // -------------------------------------------------------
    // 1. Creating std::string_view
    // -------------------------------------------------------
    std::cout << "=== Creating string_view ===\n";

    std::string_view sv1{"Hello"}; // From C-style string literal
    std::string str{"World"};
    std::string_view sv2{str}; // From std::string
    std::string_view sv3{sv1}; // From another string_view

    std::cout << "sv1 (from literal):      " << sv1 << '\n';
    std::cout << "sv2 (from std::string):  " << sv2 << '\n';
    std::cout << "sv3 (from string_view):  " << sv3 << '\n';

    // -------------------------------------------------------
    // 2. string_view as function parameter
    // -------------------------------------------------------
    std::cout << "\n=== As Function Parameter ===\n";

    // All of these work with a string_view parameter - no copies made:
    printGreeting("Alice"); // C-style string literal
    printGreeting(str);     // std::string
    printGreeting(sv1);     // std::string_view

    // -------------------------------------------------------
    // 3. string_view operations
    // -------------------------------------------------------
    std::cout << "\n=== Operations ===\n";

    std::string_view sentence{"The quick brown fox"};

    std::cout << "sentence:          \"" << sentence << "\"\n";
    std::cout << "length():          " << sentence.length() << '\n';
    std::cout << "empty():           " << std::boolalpha << sentence.empty() << '\n';
    std::cout << "sentence[0]:       '" << sentence[0] << "'\n";
    std::cout << "sentence.at(4):    '" << sentence.at(4) << "'\n";
    std::cout << "front():           '" << sentence.front() << "'\n";
    std::cout << "back():            '" << sentence.back() << "'\n";
    std::cout << "substr(4, 5):      \"" << sentence.substr(4, 5) << "\"\n";

    // -------------------------------------------------------
    // 4. string_view does NOT implicitly convert to std::string
    // -------------------------------------------------------
    std::cout << "\n=== No Implicit Conversion to std::string ===\n";

    std::string_view sv{"Hello"};
    // std::string s = sv;           // ERROR: no implicit conversion
    std::string s = std::string{sv}; // OK: explicit conversion

    std::cout << "std::string{ sv } = \"" << s << "\" (explicit conversion required)\n";

    // -------------------------------------------------------
    // 5. constexpr std::string_view
    // -------------------------------------------------------
    // string_view is fully constexpr-compatible, making it ideal
    // for string symbolic constants.

    std::cout << "\n=== constexpr string_view ===\n";

    constexpr std::string_view appName{"MyApp"};
    constexpr std::string_view version{"1.0.0"};

    std::cout << appName << " v" << version << '\n';
    std::cout << "constexpr std::string_view is the best way to define string constants.\n";

    return 0;
}
