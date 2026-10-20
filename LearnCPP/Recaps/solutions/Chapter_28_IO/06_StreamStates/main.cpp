// Chapter 28 - Project 06: Stream States
// ------------------------------------------
// Key concepts:
//   Four state flags on every stream:
//     goodbit  - no errors, extraction succeeded
//     badbit   - fatal/irrecoverable error (e.g. stream corrupted)
//     eofbit   - end-of-file reached
//     failbit  - extraction failed (e.g. expected int, got text)
//
//   Accessor functions:
//     good()  - returns true if goodbit is set (no error flags)
//     bad()   - returns true if badbit is set
//     eof()   - returns true if eofbit is set
//     fail()  - returns true if failbit OR badbit is set
//
//   Clearing errors: clear() resets all flags to goodbit
//
//   A stream in a boolean context (e.g. if(cin)) returns !fail()

#include <iostream>
#include <limits>  // std::numeric_limits
#include <sstream> // for safe demonstration without ruining cin

// Helper: print the state of a stream
void printStreamState(const std::istream &stream, const std::string &label)
{
    std::cout << label << ": ";
    std::cout << "good=" << stream.good()
              << " eof=" << stream.eof()
              << " fail=" << stream.fail()
              << " bad=" << stream.bad() << '\n';
}

int main()
{
    // ========================================================
    // 1. Normal extraction - goodbit
    // ========================================================
    std::cout << "=== 1. Successful extraction ===\n";
    std::istringstream iss1{"42"};
    int value{};
    iss1 >> value;
    printStreamState(iss1, "After reading 42");
    std::cout << "Value = " << value << "\n\n";

    // ========================================================
    // 2. Failed extraction - failbit
    // ========================================================
    std::cout << "=== 2. Failed extraction (type mismatch) ===\n";
    std::istringstream iss2{"hello"};
    int num{};
    iss2 >> num; // "hello" can't be parsed as int → failbit set
    printStreamState(iss2, "After reading 'hello' as int");
    std::cout << "num = " << num << " (unchanged - extraction failed)\n\n";

    // ========================================================
    // 3. End-of-file - eofbit
    // ========================================================
    std::cout << "=== 3. End-of-file ===\n";
    std::istringstream iss3{"99"};
    int eof_val{};
    iss3 >> eof_val; // reads 99, then hits end of stream
    printStreamState(iss3, "After reading 99 (at end)");
    // eofbit may be set here because the stream hit EOF during extraction.

    // Trying one more read should set failbit too
    int dummy{};
    iss3 >> dummy;
    printStreamState(iss3, "After attempting another read");
    std::cout << '\n';

    // ========================================================
    // 4. Using a stream in a boolean context
    // ========================================================
    std::cout << "=== 4. Boolean context ===\n";
    std::istringstream iss4{"10 20 abc"};
    int x{};
    while (iss4 >> x) // returns !fail() - loop exits on failbit
    {
        std::cout << "Read: " << x << '\n';
    }
    printStreamState(iss4, "After loop");
    std::cout << '\n';

    // ========================================================
    // 5. Clearing errors with clear()
    // ========================================================
    std::cout << "=== 5. Clearing errors ===\n";
    std::istringstream iss5{"abc 123"};
    int val{};
    iss5 >> val;
    printStreamState(iss5, "After failed read");

    iss5.clear(); // reset flags to goodbit
    printStreamState(iss5, "After clear()");

    // The bad characters ("abc") are still in the stream.
    // We must discard them before retrying.
    iss5.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    iss5 >> val;
    printStreamState(iss5, "After re-read");
    std::cout << "Value = " << val << "\n\n";

    // ========================================================
    // 6. Live demo with std::cin
    // ========================================================
    std::cout << "=== 6. Live: enter an integer (try typing text) ===\n";
    std::cout << "Enter an integer: ";
    int input{};
    std::cin >> input;

    if (std::cin.fail()) // same as: if (!std::cin)
    {
        std::cout << "Invalid input! Clearing error state...\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else
    {
        std::cout << "You entered: " << input << '\n';
    }

    std::cout << "\nDone!\n";
    return 0;
}
