// Chapter 1 - Project 01: Statements and the Structure of a Program
// ===================================================================
//
// KEY CONCEPTS:
//   - A **statement** is the smallest independent unit of computation in C++.
//     Most statements end with a semicolon (;).
//   - Statements are grouped inside **functions**.
//   - Every C++ program must contain a function called main().
//     Execution always begins at the first statement inside main().
//   - main() returns an int to the operating system (0 = success).
//   - A **syntax error** occurs when you violate the grammar rules of C++.

#include <iostream> // Needed for std::cout

// main() - the entry point of every C++ program.
// The operating system calls this function when the program starts.
int main()
{
    // Each line below is a separate statement.
    // Statements execute sequentially, top to bottom.

    std::cout << "Statement 1: Hello, World!\n"; // A simple output statement
    std::cout << "Statement 2: C++ is fun.\n";   // Another output statement

    int x{42};                                     // A definition statement - creates a variable named x
    std::cout << "Statement 3: x = " << x << '\n'; // Prints the value of x

    // An expression statement - evaluates an expression, discards the result.
    // Here the expression is (x + 1), and the side effect is the output.
    std::cout << "Statement 4: x + 1 = " << (x + 1) << '\n';

    // A compound statement (block) - a group of statements enclosed in { }.
    {
        std::cout << "Statement 5: Inside a block.\n";
        std::cout << "Statement 6: Still inside the block.\n";
    } // End of compound statement - no semicolon needed after the closing brace

    // The return statement ends main() and sends a status code to the OS.
    // Returning 0 means the program finished successfully.
    return 0;
}
