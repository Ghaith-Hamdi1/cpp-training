// ============================================================================
// Chapter 0, Project 01 - Hello, World!
// Concept: Your very first C++ program.
// ============================================================================
//
// KEY IDEAS (Section 0.7):
//   - Every C++ program needs a main() function - it's where execution begins.
//   - #include <iostream> gives us access to std::cout for output.
//   - std::cout << "text" sends text to the console (standard output).
//   - std::endl outputs a newline and flushes the stream.
//   - return 0 tells the operating system the program finished successfully.
//
// BUILD:  g++ -std=c++20 -Wall -Wextra -Werror -o HelloWorld main.cpp
// ============================================================================

#include <iostream> // for std::cout, std::endl

int main()
{
    // std::cout sends output to the console
    // << is the "insertion operator" - it inserts the text into the output stream
    std::cout << "Hello, world!" << std::endl;

    return 0; // 0 means success - the program ran without errors
}
