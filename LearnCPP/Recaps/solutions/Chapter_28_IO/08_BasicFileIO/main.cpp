// Chapter 28 - Project 08: Basic File I/O
// -------------------------------------------
// Key concepts:
//   - std::ofstream - write to a file    (output file stream)
//   - std::ifstream - read from a file   (input file stream)
//   - std::fstream  - read and write     (file stream)
//   - File modes: ios::app, ios::trunc, ios::binary, ios::in, ios::out
//   - RAII: file is automatically closed when the stream goes out of scope
//   - Always check if the file opened successfully before using it
//
// Best practices:
//   - Use '\n' instead of std::endl for performance (endl forces a flush)
//   - Don't call exit() in the middle of your program - destructors won't
//     run and buffered data may be lost
//   - Use ios::app to append instead of overwrite

#include <fstream> // ifstream, ofstream, fstream
#include <iostream>
#include <string>

int main()
{
    const std::string filename{"demo_output.txt"};

    // ========================================================
    // 1. Writing to a file with ofstream
    // ========================================================
    std::cout << "=== 1. Writing to a file ===\n";
    {
        // ofstream opens in ios::out | ios::trunc by default
        // (creates the file if it doesn't exist, truncates if it does)
        std::ofstream outFile{filename};

        // Always check if the file opened successfully
        if (!outFile)
        {
            std::cerr << "Error: could not open '" << filename << "' for writing.\n";
            return 1;
        }

        // Write data - use '\n' not std::endl for performance
        outFile << "Line 1: Hello, file I/O!\n";
        outFile << "Line 2: The answer is " << 42 << '\n';
        outFile << "Line 3: Pi is approximately " << 3.14159 << '\n';

        std::cout << "Wrote 3 lines to '" << filename << "'.\n";

        // File is automatically closed when outFile goes out of scope (RAII)
    }

    // ========================================================
    // 2. Reading from a file with ifstream
    // ========================================================
    std::cout << "\n=== 2. Reading from a file ===\n";
    {
        std::ifstream inFile{filename};

        if (!inFile)
        {
            std::cerr << "Error: could not open '" << filename << "' for reading.\n";
            return 1;
        }

        // Read line by line using std::getline
        std::string line{};
        while (std::getline(inFile, line))
        {
            std::cout << "  Read: " << line << '\n';
        }

        // inFile closes automatically here
    }

    // ========================================================
    // 3. Appending to a file with ios::app
    // ========================================================
    std::cout << "\n=== 3. Appending to a file ===\n";
    {
        // ios::app - all writes go to the end; existing content preserved
        std::ofstream appendFile{filename, std::ios::app};

        if (!appendFile)
        {
            std::cerr << "Error: could not open '" << filename << "' for appending.\n";
            return 1;
        }

        appendFile << "Line 4: This line was appended.\n";
        appendFile << "Line 5: Append mode preserves existing content.\n";
        std::cout << "Appended 2 more lines.\n";
    }

    // ========================================================
    // 4. Verify the append worked
    // ========================================================
    std::cout << "\n=== 4. File contents after append ===\n";
    {
        std::ifstream inFile{filename};
        if (!inFile)
        {
            std::cerr << "Error: could not open file.\n";
            return 1;
        }

        std::string line{};
        while (std::getline(inFile, line))
        {
            std::cout << "  " << line << '\n';
        }
    }

    // ========================================================
    // 5. Using open() and close() explicitly
    // ========================================================
    std::cout << "\n=== 5. Explicit open() / close() ===\n";
    {
        std::ofstream outFile{};           // not yet connected to a file
        outFile.open("explicit_demo.txt"); // open explicitly

        if (!outFile)
        {
            std::cerr << "Error: could not open file.\n";
            return 1;
        }

        outFile << "Written with explicit open().\n";
        outFile.close(); // close explicitly

        // Verify
        std::ifstream inFile{"explicit_demo.txt"};
        std::string content{};
        std::getline(inFile, content);
        std::cout << "  Read: " << content << '\n';
    }

    // ========================================================
    // 6. File modes summary
    // ========================================================
    std::cout << "\n=== 6. File modes reference ===\n";
    std::cout << "  ios::in     - open for reading\n";
    std::cout << "  ios::out    - open for writing\n";
    std::cout << "  ios::app    - append (all writes go to end)\n";
    std::cout << "  ios::trunc  - truncate file on open (default with out)\n";
    std::cout << "  ios::ate    - seek to end after opening\n";
    std::cout << "  ios::binary - open in binary mode (no newline translation)\n";

    std::cout << "\nDone! (Files 'demo_output.txt' and 'explicit_demo.txt' created)\n";
    return 0;
}
