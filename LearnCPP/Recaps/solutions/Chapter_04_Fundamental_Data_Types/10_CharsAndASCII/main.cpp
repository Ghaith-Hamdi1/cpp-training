// Chapter 4 - Project 10: Chars and ASCII
// ==========================================
// Key concept: char holds a single ASCII character (1 byte).
// Character literals use single quotes: 'a'
// String literals use double quotes: "hello"
// Escape sequences: \n (newline), \t (tab), \\ (backslash), \' (quote)
//
// Pitfall: Confusing '5' (char, ASCII 53) with 5 (integer).
// Pitfall: Using /n instead of \n (forward slash is wrong).
// Pitfall: Avoiding multicharacter literals like 'ab'.
// Note: The signedness of char is implementation-defined.

#include <iostream>

int main()
{
    std::cout << "=== Chars and ASCII ===\n\n";

    // Basic char usage
    char letter{'A'};
    char digit{'7'};
    char symbol{'#'};

    std::cout << "--- Basic char values ---\n";
    std::cout << "letter: " << letter << '\n';
    std::cout << "digit:  " << digit << '\n';
    std::cout << "symbol: " << symbol << '\n';
    std::cout << '\n';

    // char is stored as an integer (ASCII value)
    std::cout << "--- char ↔ integer relationship ---\n";
    std::cout << "'A' as char:    " << letter << '\n';
    std::cout << "'A' as integer: " << static_cast<int>(letter) << " (ASCII 65)\n";
    std::cout << "'7' as char:    " << digit << '\n';
    std::cout << "'7' as integer: " << static_cast<int>(digit) << " (ASCII 55)\n";
    std::cout << '\n';

    // PITFALL: '5' vs 5
    std::cout << "--- Pitfall: '5' vs 5 ---\n";
    char charFive{'5'};
    int intFive{5};
    std::cout << "'5' (char) has ASCII value: " << static_cast<int>(charFive) << " (53)\n";
    std::cout << " 5  (int) has value:        " << intFive << '\n';
    std::cout << "These are COMPLETELY different values!\n";
    std::cout << '\n';

    // Escape sequences
    std::cout << "--- Escape sequences ---\n";
    std::cout << "Newline:    [line1\\nline2] -> [line1\nline2]\n";
    std::cout << "Tab:        [col1\\tcol2]   -> [col1\tcol2]\n";
    std::cout << "Backslash:  [\\\\]           -> [\\]\n";
    std::cout << "Single qt:  [\\']           -> [']\n";
    std::cout << "Double qt:  [\\\"]           -> [\"]\n";
    std::cout << '\n';

    // PITFALL: /n vs \n
    std::cout << "--- Pitfall: /n vs \\n ---\n";
    std::cout << "\\n creates a newline (correct)\n";
    std::cout << "/n does NOT create a newline - it's two characters '/' and 'n'\n";
    std::cout << '\n';

    // Printing a range of ASCII characters
    std::cout << "--- ASCII table excerpt (32-126: printable characters) ---\n";
    for (int i{32}; i <= 126; ++i)
    {
        std::cout << static_cast<char>(i);
        if ((i - 31) % 32 == 0) // New line every 32 characters
            std::cout << '\n';
    }
    std::cout << '\n';

    return 0;
}
