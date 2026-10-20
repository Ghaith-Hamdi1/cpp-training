// Chapter 5 - Project 12: String View Operations
// =================================================
// Topics:
//   - remove_prefix() and remove_suffix() shrink the view
//   - These do NOT modify the underlying string
//   - constexpr std::string_view for string symbolic constants
//   - Comparison and searching with string_view
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <string>
#include <string_view>

int main()
{
    // -------------------------------------------------------
    // 1. remove_prefix() - shrink from the front
    // -------------------------------------------------------
    std::cout << "=== remove_prefix() ===\n";

    std::string_view sv{"Hello, World!"};
    std::cout << "Original:       \"" << sv << "\"\n";

    sv.remove_prefix(7);                                 // Remove first 7 characters ("Hello, ")
    std::cout << "remove_prefix(7): \"" << sv << "\"\n"; // "World!"

    // -------------------------------------------------------
    // 2. remove_suffix() - shrink from the back
    // -------------------------------------------------------
    std::cout << "\n=== remove_suffix() ===\n";

    std::string_view sv2{"Hello, World!"};
    std::cout << "Original:       \"" << sv2 << "\"\n";

    sv2.remove_suffix(1);                                 // Remove last character ("!")
    std::cout << "remove_suffix(1): \"" << sv2 << "\"\n"; // "Hello, World"

    // -------------------------------------------------------
    // 3. Combined remove_prefix + remove_suffix
    // -------------------------------------------------------
    std::cout << "\n=== Combined Trimming ===\n";

    std::string_view quoted{"\"Quoted Text\""};
    std::cout << "Original:    " << quoted << '\n';

    quoted.remove_prefix(1);                        // Remove opening quote
    quoted.remove_suffix(1);                        // Remove closing quote
    std::cout << "After trim:  " << quoted << '\n'; // Quoted Text

    // IMPORTANT: The original string is NOT modified.
    // remove_prefix/remove_suffix only adjust the view's pointer and length.

    // -------------------------------------------------------
    // 4. Searching within string_view
    // -------------------------------------------------------
    std::cout << "\n=== Searching ===\n";

    std::string_view text{"The quick brown fox jumps over the lazy dog"};

    // find() returns the position of the first occurrence, or npos if not found
    auto pos = text.find("fox");
    if (pos != std::string_view::npos)
        std::cout << "'fox' found at position " << pos << '\n';

    pos = text.find("cat");
    if (pos == std::string_view::npos)
        std::cout << "'cat' not found.\n";

    // starts_with() and ends_with() (C++20):
    std::cout << "starts_with('The'): " << std::boolalpha << text.starts_with("The") << '\n';
    std::cout << "ends_with('dog'):   " << text.ends_with("dog") << '\n';
    std::cout << "ends_with('cat'):   " << text.ends_with("cat") << '\n';

    // -------------------------------------------------------
    // 5. Comparison
    // -------------------------------------------------------
    std::cout << "\n=== Comparison ===\n";

    std::string_view a{"apple"};
    std::string_view b{"banana"};
    std::string_view c{"apple"};

    std::cout << "\"apple\" == \"banana\": " << (a == b) << '\n';
    std::cout << "\"apple\" == \"apple\":  " << (a == c) << '\n';
    std::cout << "\"apple\" < \"banana\":  " << (a < b) << '\n';

    // -------------------------------------------------------
    // 6. constexpr string_view for symbolic constants
    // -------------------------------------------------------
    std::cout << "\n=== constexpr string_view Constants ===\n";

    // This is the recommended way to define string constants in C++.
    // constexpr std::string is not well supported, but constexpr
    // std::string_view works perfectly.

    constexpr std::string_view appName{"LearnCPP"};
    constexpr std::string_view version{"2.0.1"};
    constexpr std::string_view author{"Amal Rajan"};

    std::cout << "App:     " << appName << '\n';
    std::cout << "Version: " << version << '\n';
    std::cout << "Author:  " << author << '\n';
    std::cout << "\nUse 'constexpr std::string_view' for all string constants.\n";

    // -------------------------------------------------------
    // 7. substr() creates a new string_view (no copy)
    // -------------------------------------------------------
    std::cout << "\n=== substr() ===\n";

    std::string_view path{"/home/user/documents/file.txt"};
    std::cout << "Full path:  " << path << '\n';

    // Find last '/' to extract the filename
    auto lastSlash = path.rfind('/');
    if (lastSlash != std::string_view::npos)
    {
        std::string_view filename = path.substr(lastSlash + 1);
        std::cout << "Filename:   " << filename << '\n';
    }

    return 0;
}
