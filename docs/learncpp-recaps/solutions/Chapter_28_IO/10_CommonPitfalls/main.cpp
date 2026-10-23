// Chapter 28 - Project 10: Common I/O Pitfalls
// ------------------------------------------------
// This project demonstrates the most frequent mistakes programmers
// make with C++ I/O and how to avoid them.

#include <fstream>
#include <iostream>
#include <limits> // numeric_limits
#include <sstream>
#include <string>

// -------------------------------------------------------
// Pitfall 1: Mixing >> and getline()
// >> leaves '\n' in the buffer; the next getline() reads an empty string.
// -------------------------------------------------------
void pitfall_mixing_extraction_and_getline()
{
    std::cout << "=== Pitfall 1: Mixing >> and getline() ===\n";

    std::istringstream input{"42\nHello World\n"};

    int number{};
    input >> number; // reads "42", leaves '\n' in buffer

    std::string line{};
    std::getline(input, line); // reads up to '\n' - gets EMPTY string!

    std::cout << "  [BUG]  number=" << number
              << ", line=\"" << line << "\" (empty!)\n";

    // ----- FIX: ignore the leftover newline after >> -----
    std::istringstream input2{"42\nHello World\n"};
    input2 >> number;
    input2.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard '\n'
    std::getline(input2, line);

    std::cout << "  [FIX]  number=" << number
              << ", line=\"" << line << "\"\n\n";
}

// -------------------------------------------------------
// Pitfall 2: Not clearing the stream after failed input
// All subsequent reads silently fail.
// -------------------------------------------------------
void pitfall_not_clearing_after_failure()
{
    std::cout << "=== Pitfall 2: Not clearing after failed input ===\n";

    std::istringstream input{"abc 123"};
    int a{};
    int b{};

    input >> a; // fails - "abc" is not an int → failbit set
    input >> b; // also fails - stream is still in error state!

    std::cout << "  [BUG]  a=" << a << ", b=" << b
              << " (both 0 - second read failed too!)\n";

    // ----- FIX: clear() then ignore() the bad chars -----
    std::istringstream input2{"abc 123"};
    input2 >> a; // fails

    input2.clear();                                                  // reset error flags
    input2.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // skip "abc "
    input2 >> b;                                                     // now reads 123

    std::cout << "  [FIX]  a=" << a << " (still failed), b=" << b
              << " (recovered!)\n\n";
}

// -------------------------------------------------------
// Pitfall 3: Assuming setw() is persistent
// -------------------------------------------------------
void pitfall_setw_persistent()
{
    std::cout << "=== Pitfall 3: Assuming setw() is persistent ===\n";

    std::ostringstream oss{};
    oss << std::setw(10) << "A" << "B" << "C";
    //       ^^^^^^^^^^    applies only to "A"

    std::cout << "  [BUG]  \"" << oss.str() << "\"  - only 'A' is padded\n";

    std::ostringstream oss2{};
    oss2 << std::setw(10) << "A"
         << std::setw(10) << "B"
         << std::setw(10) << "C";

    std::cout << "  [FIX]  \"" << oss2.str() << "\"  - all padded\n\n";
}

// -------------------------------------------------------
// Pitfall 4: get() leaves the newline in the stream
// -------------------------------------------------------
void pitfall_get_leaves_newline()
{
    std::cout << "=== Pitfall 4: get() leaves the newline ===\n";

    std::istringstream input{"A\nHello"};

    char ch{};
    input.get(ch); // reads 'A', leaves '\n' in stream

    char ch2{};
    input.get(ch2); // reads '\n', NOT 'H'!

    std::cout << "  [BUG]  ch='" << ch << "', ch2='"
              << (ch2 == '\n' ? "\\n" : std::string(1, ch2)) << "'\n";

    // ----- FIX: use getline() which consumes the delimiter -----
    std::istringstream input2{"A\nHello"};
    std::string first{};
    std::getline(input2, first); // reads "A", consumes '\n'

    std::string second{};
    std::getline(input2, second); // reads "Hello"

    std::cout << "  [FIX]  first=\"" << first
              << "\", second=\"" << second << "\"\n\n";
}

// -------------------------------------------------------
// Pitfall 5: Using endl excessively (performance hit)
// -------------------------------------------------------
void pitfall_endl_performance()
{
    std::cout << "=== Pitfall 5: endl vs '\\n' ===\n";

    // std::endl does TWO things:
    //   1. Inserts '\n'
    //   2. Flushes the stream buffer
    //
    // In a loop writing to a file, each flush is an expensive
    // system call.  Use '\n' instead for normal line breaks.

    std::cout << "  std::endl = '\\n' + flush  (slow in loops)\n";
    std::cout << "  '\\n'     = just a newline  (fast)\n";
    std::cout << "  Rule: use '\\n' by default; only use endl when\n";
    std::cout << "        you specifically need to flush.\n\n";

    // Demonstration: writing 1000 lines to a file
    {
        std::ofstream fast{"perf_newline.txt"};
        for (int i{0}; i < 1000; ++i)
            fast << "Line " << i << '\n'; // fast - no flush per line
    }
    {
        std::ofstream slow{"perf_endl.txt"};
        for (int i{0}; i < 1000; ++i)
            slow << "Line " << i << std::endl; // slow - flushes every line
    }
    std::cout << "  (Created perf_newline.txt and perf_endl.txt for comparison)\n\n";
}

// -------------------------------------------------------
// Pitfall 6: Not checking if a file opened successfully
// -------------------------------------------------------
void pitfall_not_checking_file_open()
{
    std::cout << "=== Pitfall 6: Not checking file open ===\n";

    // BUG: writing to a stream that failed to open → silent failure
    std::ifstream file{"nonexistent_file_12345.txt"};
    if (!file)
    {
        std::cout << "  [DEMO] File failed to open - detected with if(!file)\n";
        std::cout << "  Always check before reading/writing!\n\n";
    }
}

// -------------------------------------------------------
// Pitfall 7: Using setf() without specifying the group
// -------------------------------------------------------
void pitfall_setf_without_group()
{
    std::cout << "=== Pitfall 7: setf() without group ===\n";

    std::ostringstream oss{};

    // BUG: turning on hex without turning off dec
    // dec is set by default.  setf(hex) turns hex ON but leaves dec ON too.
    oss.setf(std::ios::hex); // WRONG - dec is still active
    oss << 255;
    std::cout << "  [BUG]  setf(hex) without group: \"" << oss.str() << "\"\n";

    // FIX: use the two-parameter form specifying the group
    std::ostringstream oss2{};
    oss2.setf(std::ios::hex, std::ios::basefield); // turns off dec, turns on hex
    oss2 << 255;
    std::cout << "  [FIX]  setf(hex, basefield): \"" << oss2.str() << "\"\n";

    // BEST: just use the manipulator - it handles the group automatically
    std::ostringstream oss3{};
    oss3 << std::hex << 255;
    std::cout << "  [BEST] std::hex manipulator: \"" << oss3.str() << "\"\n\n";
}

int main()
{
    std::cout << "Chapter 28 - Common I/O Pitfalls\n";
    std::cout << "=================================\n\n";

    pitfall_mixing_extraction_and_getline();
    pitfall_not_clearing_after_failure();
    pitfall_setw_persistent();
    pitfall_get_leaves_newline();
    pitfall_endl_performance();
    pitfall_not_checking_file_open();
    pitfall_setf_without_group();

    std::cout << "All pitfalls demonstrated. Review each [BUG]/[FIX] pair!\n";
    return 0;
}
