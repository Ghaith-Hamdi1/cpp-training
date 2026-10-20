// Chapter 3 - Project 03: Debugging with std::cerr
// ===================================================
//
// KEY CONCEPT:
//   When adding temporary print statements for debugging, use std::cerr
//   instead of std::cout.
//
//   std::cout is BUFFERED - output is collected in a buffer and flushed later.
//   If the program crashes before the buffer is flushed, you may never see
//   the debug message, making it impossible to tell how far execution got.
//
//   std::cerr is UNBUFFERED - every output is written immediately. Even if
//   the program crashes on the very next line, the debug message will have
//   already appeared on screen.
//
// This program shows how std::cerr prints immediately while std::cout may
// delay its output. In a crash scenario, std::cerr is far more reliable.

#include <iostream>

int getUserInput()
{
    // Debug output with std::cerr - prints immediately, crash-safe
    std::cerr << "[DEBUG] getUserInput() called\n";

    std::cout << "Enter a number: ";
    int value{};
    std::cin >> value;

    std::cerr << "[DEBUG] getUserInput() returning " << value << '\n';
    return value;
}

int multiply(int x, int y)
{
    std::cerr << "[DEBUG] multiply(" << x << ", " << y << ") called\n";
    return x * y;
}

int main()
{
    std::cerr << "[DEBUG] main() started\n";

    std::cout << "=== std::cerr Debugging Demo ===\n\n";

    // Why std::cerr?
    // 1. It is unbuffered - output appears instantly.
    // 2. It writes to stderr, separate from normal program output (stdout).
    // 3. You can redirect stderr to a file while keeping stdout on screen:
    //       program.exe 2> debug.log
    //    This sends cerr output to debug.log and cout output to the console.

    int a{getUserInput()};
    int b{getUserInput()};

    int result{multiply(a, b)};

    std::cout << "\n"
              << a << " * " << b << " = " << result << '\n';

    // PITFALL: If you used std::cout for debug messages, and the program
    // crashed after multiply() but before the buffer was flushed, you might
    // never see the debug output. std::cerr avoids this entirely.

    std::cerr << "[DEBUG] main() finished successfully\n";

    return 0;
}
