// Chapter 20 - Project 06: Command Line Arguments
// =================================================
// Demonstrates: accessing argc/argv, converting string arguments
// to numeric types, and safely checking bounds.
//
// Key points:
//   - int main(int argc, char* argv[])
//   - argc is always >= 1 (argv[0] is the program name).
//   - argv entries are C-style strings - you MUST convert them
//     to int/double/etc. explicitly (e.g., via std::stringstream).
//   - Pitfall: accessing argv[n] without checking argc first is
//     undefined behavior if n >= argc.
//
// Try running:
//   ./main 42 3.14 hello

#include <iostream>
#include <sstream> // std::stringstream
#include <string>

int main(int argc, char *argv[])
{
    // -------------------------------------------------------
    // 1. Print all raw arguments
    // -------------------------------------------------------
    std::cout << "=== Raw command-line arguments ===\n";
    std::cout << "argc = " << argc << '\n';
    for (int i{0}; i < argc; ++i)
        std::cout << "  argv[" << i << "] = \"" << argv[i] << "\"\n";

    // -------------------------------------------------------
    // 2. Safely access a specific argument
    // -------------------------------------------------------
    // Always check argc before accessing argv[n]!
    if (argc >= 2)
    {
        std::cout << "\nFirst user argument: " << argv[1] << '\n';
    }
    else
    {
        std::cout << "\nNo user arguments provided. "
                  << "Run with: " << argv[0] << " <number> [more args]\n";
    }

    // -------------------------------------------------------
    // 3. Converting a string argument to an integer
    // -------------------------------------------------------
    if (argc >= 2)
    {
        std::stringstream ss;
        ss << argv[1];

        int value{};
        if (ss >> value)
            std::cout << "argv[1] as int: " << value << " (doubled: " << value * 2 << ")\n";
        else
            std::cout << "argv[1] could not be converted to int.\n";
    }

    // -------------------------------------------------------
    // 4. Converting a string argument to a double
    // -------------------------------------------------------
    if (argc >= 3)
    {
        std::stringstream ss;
        ss << argv[2];

        double value{};
        if (ss >> value)
            std::cout << "argv[2] as double: " << value << " (squared: " << value * value << ")\n";
        else
            std::cout << "argv[2] could not be converted to double.\n";
    }

    // -------------------------------------------------------
    // 5. Pitfall demonstration (commented out - would be UB)
    // -------------------------------------------------------
    // NEVER do this without checking argc first:
    //   std::cout << argv[99];  // undefined behavior if argc < 100

    return 0;
}
