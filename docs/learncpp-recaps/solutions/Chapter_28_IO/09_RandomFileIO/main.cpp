// Chapter 28 - Project 09: Random File I/O
// --------------------------------------------
// Key concepts:
//   - seekg(offset, origin) - set the GET (read)  pointer position
//   - seekp(offset, origin) - set the PUT (write) pointer position
//   - tellg()               - query the current GET pointer position
//   - tellp()               - query the current PUT pointer position
//   - Origins: ios::beg, ios::cur, ios::end
//   - With fstream, you MUST seek when switching between read and write
//   - Use binary mode for reliable seeking (text mode has newline issues)
//
// Common pitfalls:
//   - Seeking in text-mode files - newline encoding differs by OS,
//     so seek positions may be unreliable.  Use ios::binary.
//   - Never write raw pointer addresses to files - they are meaningless
//     when read back by a different process or on a different run.

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    const std::string filename{"random_io_demo.dat"};

    // ========================================================
    // 1. Create a binary file with known content
    // ========================================================
    std::cout << "=== 1. Creating binary file ===\n";
    {
        std::ofstream outFile{filename, std::ios::binary};
        if (!outFile)
        {
            std::cerr << "Error: could not create file.\n";
            return 1;
        }

        // Write 10 integers (0..9) as raw binary
        for (std::int32_t i{0}; i < 10; ++i)
        {
            outFile.write(reinterpret_cast<const char *>(&i), sizeof(i));
        }
        std::cout << "Wrote 10 integers (0-9) to '" << filename << "'.\n";
    }

    // ========================================================
    // 2. Reading sequentially
    // ========================================================
    std::cout << "\n=== 2. Sequential read ===\n";
    {
        std::ifstream inFile{filename, std::ios::binary};
        if (!inFile)
        {
            std::cerr << "Error: could not open file.\n";
            return 1;
        }

        std::int32_t value{};
        while (inFile.read(reinterpret_cast<char *>(&value), sizeof(value)))
        {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }

    // ========================================================
    // 3. Random read with seekg()
    // ========================================================
    std::cout << "\n=== 3. Random read - seekg() ===\n";
    {
        std::ifstream inFile{filename, std::ios::binary};
        if (!inFile)
        {
            std::cerr << "Error: could not open file.\n";
            return 1;
        }

        // Read the 5th integer (index 4) - offset = 4 * sizeof(int32_t)
        std::int32_t value{};
        inFile.seekg(4 * static_cast<std::streamoff>(sizeof(std::int32_t)), std::ios::beg);
        inFile.read(reinterpret_cast<char *>(&value), sizeof(value));
        std::cout << "Element at index 4: " << value << '\n';

        // Read the last integer - seek from end
        inFile.seekg(-static_cast<std::streamoff>(sizeof(std::int32_t)), std::ios::end);
        inFile.read(reinterpret_cast<char *>(&value), sizeof(value));
        std::cout << "Last element:       " << value << '\n';

        // tellg() - current position
        std::cout << "Current get position: " << inFile.tellg() << " bytes\n";
    }

    // ========================================================
    // 4. Random write with seekp()
    // ========================================================
    std::cout << "\n=== 4. Random write - seekp() ===\n";
    {
        // Open for both read and write (fstream), binary mode
        std::fstream file{filename, std::ios::in | std::ios::out | std::ios::binary};
        if (!file)
        {
            std::cerr << "Error: could not open file.\n";
            return 1;
        }

        // Overwrite the 3rd element (index 2) with value 999
        std::int32_t newValue{999};
        file.seekp(2 * static_cast<std::streamoff>(sizeof(std::int32_t)), std::ios::beg);
        file.write(reinterpret_cast<const char *>(&newValue), sizeof(newValue));
        std::cout << "Overwrote index 2 with " << newValue << ".\n";

        // NOW READ BACK - must seek before switching from write to read
        file.seekg(0, std::ios::beg); // <-- required seek!

        std::int32_t value{};
        std::cout << "File contents: ";
        while (file.read(reinterpret_cast<char *>(&value), sizeof(value)))
        {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }

    // ========================================================
    // 5. seekg() origins: beg, cur, end
    // ========================================================
    std::cout << "\n=== 5. Seek origins ===\n";
    {
        std::ifstream inFile{filename, std::ios::binary};
        if (!inFile)
        {
            std::cerr << "Error: could not open file.\n";
            return 1;
        }

        std::int32_t value{};

        // From beginning: index 1
        inFile.seekg(1 * static_cast<std::streamoff>(sizeof(std::int32_t)), std::ios::beg);
        inFile.read(reinterpret_cast<char *>(&value), sizeof(value));
        std::cout << "beg + 1*4: " << value << '\n';

        // From current position: skip one, read next
        inFile.seekg(1 * static_cast<std::streamoff>(sizeof(std::int32_t)), std::ios::cur);
        inFile.read(reinterpret_cast<char *>(&value), sizeof(value));
        std::cout << "cur + 1*4: " << value << " (skipped one after previous read)\n";

        // From end: second-to-last
        inFile.seekg(-2 * static_cast<std::streamoff>(sizeof(std::int32_t)), std::ios::end);
        inFile.read(reinterpret_cast<char *>(&value), sizeof(value));
        std::cout << "end - 2*4: " << value << '\n';
    }

    // ========================================================
    // 6. Pitfall reminder
    // ========================================================
    std::cout << "\n=== 6. Pitfall reminders ===\n";
    std::cout << "  - Use binary mode for reliable seeking\n";
    std::cout << "  - Never write raw pointers to files\n";
    std::cout << "  - With fstream, seek before switching read <-> write\n";

    std::cout << "\nDone! (File 'random_io_demo.dat' created)\n";
    return 0;
}
