// Chapter 28 - Project 04: setw() Is NOT Persistent
// -----------------------------------------------------
// Key concept / Common pitfall:
//   Unlike most manipulators (boolalpha, hex, setfill, setprecision, etc.),
//   std::setw() is NON-PERSISTENT.  It only applies to the very next
//   insertion or extraction, then resets to 0.
//
// This catches beginners who expect it to behave like setfill() or
// setprecision().

#include <iomanip>
#include <iostream>
#include <string>

int main()
{
    // ========================================================
    // 1. Demonstrating non-persistence of setw()
    // ========================================================
    std::cout << "=== 1. setw() resets after one use ===\n";

    std::cout << std::setfill('-'); // persistent - stays on
    std::cout << std::setw(20);     // non-persistent

    std::cout << "Hello" << '\n'; // "Hello" is padded to width 20
    std::cout << "World" << '\n'; // "World" has NO padding (setw reset)

    //   Output:
    //   ---------------Hello
    //   World

    // ========================================================
    // 2. You must repeat setw() for each output
    // ========================================================
    std::cout << "\n=== 2. Repeating setw() for each item ===\n";

    std::cout << std::setfill(' ');
    std::cout << std::setw(10) << "Column A" // setw reapplied each time
              << std::setw(10) << "Column B"
              << std::setw(10) << "Column C" << '\n';
    std::cout << std::setw(10) << 100
              << std::setw(10) << 200
              << std::setw(10) << 300 << '\n';

    // ========================================================
    // 3. Contrast: setfill IS persistent
    // ========================================================
    std::cout << "\n=== 3. setfill() IS persistent ===\n";

    std::cout << std::setfill('*');          // set once
    std::cout << std::setw(10) << 1 << '\n'; // *********1
    std::cout << std::setw(10) << 2 << '\n'; // *********2  - fill char stuck
    std::cout << std::setw(10) << 3 << '\n'; // *********3

    // ========================================================
    // 4. Contrast: setprecision IS persistent
    // ========================================================
    std::cout << "\n=== 4. setprecision() IS persistent ===\n";
    std::cout << std::setfill(' ');

    double pi{3.141592653589793};
    std::cout << std::setprecision(3); // set once
    std::cout << pi << '\n';           // 3.14
    std::cout << pi * 2 << '\n';       // 6.28  - still 3 digits
    std::cout << pi * 100 << '\n';     // 314   - still 3 sig digits

    // Reset precision
    std::cout << std::setprecision(6);

    // ========================================================
    // 5. setw() with extraction (input)
    // ========================================================
    // setw() also works with >> to limit how many chars are read
    // into a C-style array, preventing buffer overflow.
    std::cout << "\n=== 5. setw() with extraction ===\n";
    std::cout << "Enter a word (only first 4 chars stored): ";

    char buf[5]{};                   // 4 chars + null
    std::cin >> std::setw(5) >> buf; // reads at most 4 chars + '\0'
    std::cout << "Buffer contains: \"" << buf << "\"\n";

    // Best practice: prefer std::string + std::getline() over
    // C-style arrays to avoid buffer overflow entirely.

    std::cout << "\nDone!\n";
    return 0;
}
