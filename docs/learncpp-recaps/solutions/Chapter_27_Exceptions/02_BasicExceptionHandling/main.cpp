// Chapter 27 - Project 02: Basic Exception Handling
// ===================================================
// The three keywords:
//   throw  - raises an exception of any copyable type
//   try    - defines a block that watches for thrown exceptions
//   catch  - handles exceptions of a matching type
//
// Key rules:
//   - No implicit type conversion when matching exceptions to catch blocks
//     (an int throw won't match a double catch)
//   - Once caught, execution resumes AFTER the last catch block
//   - Exceptions can be of any copyable type: int, double, string, etc.

#include <iostream>
#include <string>

int main()
{
    // --- Example 1: Throwing and catching an int ---
    std::cout << "=== Throwing an int ===\n";
    try
    {
        throw 42; // throw an integer exception
    }
    catch (int value)
    {
        std::cout << "Caught int: " << value << '\n';
    }
    // Execution resumes here after the catch block
    std::cout << "Execution continues after catch\n\n";

    // --- Example 2: Throwing a string ---
    std::cout << "=== Throwing a std::string ===\n";
    try
    {
        throw std::string{"Something went wrong"};
    }
    catch (const std::string &msg)
    {
        std::cout << "Caught string: " << msg << '\n';
    }

    // --- Example 3: No implicit type conversion ---
    // An int exception does NOT match a double catch block.
    std::cout << "\n=== No implicit conversion (int vs double) ===\n";
    try
    {
        throw 42; // int
    }
    catch (double value)
    {
        // This will NOT catch the int - no implicit conversion
        std::cout << "Caught double: " << value << '\n';
    }
    catch (int value)
    {
        // This one matches
        std::cout << "Caught int (not double): " << value << '\n';
    }

    // --- Example 4: Multiple catch blocks ---
    std::cout << "\n=== Multiple catch blocks ===\n";
    for (int i{0}; i < 3; ++i)
    {
        try
        {
            if (i == 0)
                throw 100; // int
            else if (i == 1)
                throw 3.14; // double
            else
                throw std::string{"error string"}; // string
        }
        catch (int value)
        {
            std::cout << "Caught int: " << value << '\n';
        }
        catch (double value)
        {
            std::cout << "Caught double: " << value << '\n';
        }
        catch (const std::string &msg)
        {
            std::cout << "Caught string: " << msg << '\n';
        }
    }

    // --- Example 5: Code after a throw is not executed ---
    std::cout << "\n=== Code after throw is skipped ===\n";
    try
    {
        std::cout << "Before throw\n";
        throw -1;
        std::cout << "After throw (NEVER PRINTED)\n"; // unreachable
    }
    catch (int value)
    {
        std::cout << "Caught: " << value << '\n';
    }

    return 0;
}
