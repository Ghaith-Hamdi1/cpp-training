// Chapter 28 - Project 03: Output Formatting with ostream
// ----------------------------------------------------------
// Key concepts:
//   - Manipulators vs. raw flag manipulation (prefer manipulators)
//   - Boolean display:      std::boolalpha / std::noboolalpha
//   - Sign display:         std::showpos   / std::noshowpos
//   - Number base:          std::dec, std::hex, std::oct, std::showbase
//   - Floating-point:       std::fixed, std::scientific, std::setprecision
//   - Field width/fill:     std::setw, std::setfill, std::left, std::right, std::internal
//   - Important: setw() is NOT persistent - most other manipulators ARE persistent

#include <iomanip> // setw, setfill, setprecision, etc.
#include <iostream>

int main()
{
    // ========================================================
    // 1. Boolean formatting - boolalpha
    // ========================================================
    std::cout << "=== 1. Boolean formatting ===\n";
    std::cout << "Default:   " << true << " / " << false << '\n';
    std::cout << std::boolalpha; // persistent - stays on until turned off
    std::cout << "boolalpha: " << true << " / " << false << '\n';
    std::cout << std::noboolalpha; // restore default

    // ========================================================
    // 2. Sign display - showpos
    // ========================================================
    std::cout << "\n=== 2. Sign display ===\n";
    std::cout << std::showpos; // show '+' for positive numbers
    std::cout << "showpos:   " << 42 << " / " << -7 << " / " << 0 << '\n';
    std::cout << std::noshowpos;

    // ========================================================
    // 3. Number base - dec, hex, oct, showbase
    // ========================================================
    std::cout << "\n=== 3. Number base ===\n";
    int n{255};
    std::cout << "Decimal:     " << std::dec << n << '\n';
    std::cout << "Hexadecimal: " << std::hex << n << '\n';
    std::cout << "Octal:       " << std::oct << n << '\n';

    // showbase adds the prefix (0x for hex, 0 for octal)
    std::cout << std::showbase;
    std::cout << "Hex (base):  " << std::hex << n << '\n';
    std::cout << "Oct (base):  " << std::oct << n << '\n';
    std::cout << std::noshowbase << std::dec; // restore

    // Note: dec, hex, oct are in the "basefield" group - they are
    // mutually exclusive.  Using the manipulator automatically
    // unsets the others.  With raw setf() you must pass the group:
    //   cout.setf(std::ios::hex, std::ios::basefield);

    // ========================================================
    // 4. Floating-point precision and notation
    // ========================================================
    std::cout << "\n=== 4. Floating-point formatting ===\n";
    double pi{3.141592653589793};

    std::cout << "Default:     " << pi << '\n'; // 6 significant digits
    std::cout << std::setprecision(10);         // persistent!
    std::cout << "Precision 10:" << pi << '\n';

    std::cout << std::fixed; // fixed notation
    std::cout << "Fixed:       " << pi << '\n';

    std::cout << std::scientific; // scientific notation
    std::cout << "Scientific:  " << pi << '\n';

    // Reset to default notation
    std::cout.unsetf(std::ios::floatfield);
    std::cout << std::setprecision(6); // default precision

    // ========================================================
    // 5. Field width and fill - setw, setfill, left, right, internal
    // ========================================================
    std::cout << "\n=== 5. Field width and justification ===\n";

    // setw() sets the minimum field width for the NEXT output only
    std::cout << std::setfill('.'); // persistent fill character
    std::cout << std::right;        // right-justify (default)
    std::cout << std::setw(15) << "Name"
              << std::setw(10) << "Score" << '\n';
    std::cout << std::setw(15) << "Alice"
              << std::setw(10) << 95 << '\n';
    std::cout << std::setw(15) << "Bob"
              << std::setw(10) << 87 << '\n';

    // Left-justified
    std::cout << '\n'
              << std::left;
    std::cout << std::setw(15) << "Name"
              << std::setw(10) << "Score" << '\n';
    std::cout << std::setw(15) << "Alice"
              << std::setw(10) << 95 << '\n';

    // Internal justification - sign on left, digits on right
    std::cout << "\n=== Internal justification ===\n";
    std::cout << std::internal << std::showpos << std::setfill('0');
    std::cout << std::setw(10) << 42 << '\n';  // +000000042
    std::cout << std::setw(10) << -42 << '\n'; // -000000042
    std::cout << std::noshowpos << std::setfill(' ') << std::right;

    std::cout << "\nDone!\n";
    return 0;
}
