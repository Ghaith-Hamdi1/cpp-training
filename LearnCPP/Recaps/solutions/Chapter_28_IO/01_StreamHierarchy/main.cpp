// Chapter 28 - Project 01: The iostream Class Hierarchy
// -------------------------------------------------------
// Key concept: C++ I/O is built on a hierarchy of stream classes.
//
//   ios_base          - format flags, state flags, open-mode constants
//     └─ ios          - ties streams together, locale support
//         ├─ istream  - input  (extraction operator >>)
//         │    └─ ifstream / istringstream
//         └─ ostream  - output (insertion  operator <<)
//              └─ ofstream / ostringstream
//         (iostream inherits both istream and ostream → fstream / stringstream)
//
// Four predefined standard stream objects:
//   std::cin  - standard input  (istream, usually keyboard)
//   std::cout - standard output (ostream, usually console, buffered)
//   std::cerr - standard error  (ostream, unbuffered - good for errors)
//   std::clog - standard log    (ostream, buffered   - good for logging)

#include <iostream>

int main()
{
    // ----- std::cout - buffered standard output -----
    std::cout << "=== Standard Streams Demo ===\n\n";
    std::cout << "std::cout is the standard output stream (buffered).\n";
    std::cout << "It is an object of type std::ostream.\n\n";

    // ----- std::cerr - unbuffered error output -----
    // Because cerr is unbuffered, output appears immediately - useful
    // for error messages that must not be lost if the program crashes.
    std::cerr << "std::cerr is the standard error stream (unbuffered).\n";
    std::cerr << "Use it for error messages that need immediate display.\n\n";

    // ----- std::clog - buffered log output -----
    // clog writes to stderr like cerr, but is buffered for performance.
    std::clog << "std::clog is the buffered log stream.\n";
    std::clog << "Use it for diagnostic/logging messages.\n\n";

    // ----- std::cin - standard input -----
    // cin is an istream tied to cout by default, meaning cout is flushed
    // before cin blocks for input.  We demonstrate with a simple read.
    std::cout << "std::cin is the standard input stream.\n";
    std::cout << "Enter a number: "; // cout is flushed automatically
                                     // because cin is tied to cout
    int value{};
    std::cin >> value;
    std::cout << "You entered: " << value << "\n\n";

    // ----- Demonstrating insertion (<<) and extraction (>>) -----
    // The << operator inserts data INTO an ostream.
    // The >> operator extracts data FROM an istream.
    std::cout << "The insertion operator (<<) sends data to an output stream.\n";
    std::cout << "The extraction operator (>>) reads data from an input stream.\n\n";

    // ----- Stream chaining -----
    // Both << and >> return a reference to the stream, enabling chaining.
    std::cout << "Chaining: " << 42 << " + " << 58 << " = " << (42 + 58) << '\n';

    return 0;
}
