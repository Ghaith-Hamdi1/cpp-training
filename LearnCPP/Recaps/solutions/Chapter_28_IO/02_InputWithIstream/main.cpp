// Chapter 28 - Project 02: Input with istream
// -----------------------------------------------
// Key concepts:
//   - Extraction operator (>>) skips leading whitespace by default
//   - get()     - reads one character including whitespace, does NOT consume '\n'
//   - getline() (member) - reads into a char array, DOES consume the delimiter
//   - std::getline() (free function) - reads a full line into std::string
//   - ignore()  - discards characters from the stream
//   - peek()    - looks at the next character without extracting it
//   - unget()   - puts the last-read character back into the stream
//   - setw()    - limits extraction length to prevent buffer overflow (C-style)

#include <iomanip> // std::setw
#include <iostream>
#include <limits> // std::numeric_limits
#include <string>

int main()
{
    // ========================================================
    // 1. Extraction operator >> (skips whitespace)
    // ========================================================
    std::cout << "=== 1. Extraction operator >> ===\n";
    std::cout << "Enter two words (space-separated): ";
    std::string word1{};
    std::string word2{};
    std::cin >> word1 >> word2; // stops at whitespace
    std::cout << "Word 1: " << word1 << '\n';
    std::cout << "Word 2: " << word2 << '\n';

    // Discard the leftover '\n' from the previous >> extraction
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // ========================================================
    // 2. std::getline() - reads a full line into std::string
    // ========================================================
    // Preferred over the member getline() because it works with
    // std::string and avoids buffer-overflow risks.
    std::cout << "\n=== 2. std::getline() ===\n";
    std::cout << "Enter a full sentence: ";
    std::string sentence{};
    std::getline(std::cin, sentence); // reads until '\n', discards it
    std::cout << "You said: \"" << sentence << "\"\n";

    // ========================================================
    // 3. get() - reads one char, does NOT consume '\n'
    // ========================================================
    std::cout << "\n=== 3. get() ===\n";
    std::cout << "Enter a single character: ";
    char ch{};
    std::cin.get(ch); // reads one char (including space)
    std::cout << "get() read: '" << ch << "'\n";

    // The newline from pressing Enter is still in the stream.
    // We must clear it, or the next read would see it immediately.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // ========================================================
    // 4. peek() - look without extracting
    // ========================================================
    std::cout << "\n=== 4. peek() ===\n";
    std::cout << "Enter something: ";
    char peeked = static_cast<char>(std::cin.peek()); // look at next char
    std::cout << "peek() saw: '" << peeked << "' (still in the stream)\n";

    // Now actually extract the rest so the buffer is clean
    std::string rest{};
    std::getline(std::cin, rest);
    std::cout << "Full line extracted: \"" << rest << "\"\n";

    // ========================================================
    // 5. Member getline() - reads into a C-style char array
    // ========================================================
    // The member version is useful when you must use a fixed-size buffer.
    // Use setw() to prevent buffer overflows.
    std::cout << "\n=== 5. Member getline() with char array ===\n";
    std::cout << "Enter up to 9 characters: ";
    char buf[10]{};            // 9 chars + null terminator
    std::cin.getline(buf, 10); // reads up to 9 chars + '\0'
    std::cout << "Buffer contains: \"" << buf << "\"\n";

    // ========================================================
    // 6. ignore() - discard characters
    // ========================================================
    std::cout << "\n=== 6. ignore() ===\n";
    std::cout << "Enter text (first 5 chars will be discarded): ";
    std::cin.ignore(5); // skip 5 characters
    std::string remaining{};
    std::getline(std::cin, remaining);
    std::cout << "After ignoring 5 chars: \"" << remaining << "\"\n";

    // ========================================================
    // 7. unget() - put a character back
    // ========================================================
    std::cout << "\n=== 7. unget() ===\n";
    std::cout << "Enter a character: ";
    char c{};
    std::cin.get(c);
    std::cout << "Read: '" << c << "'\n";
    std::cin.unget(); // put it back
    char c2{};
    std::cin.get(c2);
    std::cout << "Read again after unget(): '" << c2 << "'\n";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\nDone!\n";
    return 0;
}
