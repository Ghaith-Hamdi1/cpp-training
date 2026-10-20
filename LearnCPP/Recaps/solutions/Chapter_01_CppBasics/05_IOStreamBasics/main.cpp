// Chapter 1 - Project 05: iostream Basics (cout, cin, endl)
// ===========================================================
//
// KEY CONCEPTS:
//   - #include <iostream> gives access to std::cout and std::cin.
//   - std::cout << value;   - outputs value to the console (insertion operator <<)
//   - std::cin  >> variable; - reads input from keyboard into variable (extraction >>)
//   - You can chain << or >> to output/input multiple values in one statement.
//   - '\n' outputs a newline character.
//   - std::endl outputs a newline AND flushes the buffer - prefer '\n' for performance.
//
// PITFALL:
//   - Using << with cin or >> with cout is a common mistake!
//     WRONG:  std::cin << x;     CORRECT: std::cin >> x;
//     WRONG:  std::cout >> x;    CORRECT: std::cout << x;
//   - Using '/n' (forward slash) instead of '\n' (backslash) prints a number, not a newline.

#include <iostream>

int main()
{
    // --- Basic output with std::cout ---
    std::cout << "Hello, World!\n"; // Outputs text followed by a newline

    // --- Chaining the insertion operator << ---
    int x{5};
    std::cout << "The value of x is: " << x << '\n'; // Multiple items in one statement

    // --- '\n' vs std::endl ---
    std::cout << "Line 1 with backslash-n\n";          // Preferred: just a newline
    std::cout << "Line 2 with std::endl" << std::endl; // Newline + buffer flush (slower)
    // Use '\n' in most cases. std::endl forces a flush which hurts performance.

    // --- Multiple outputs on the same line ---
    // Without '\n', successive cout statements print on the SAME line.
    std::cout << "Same ";
    std::cout << "line ";
    std::cout << "output.";
    std::cout << '\n'; // Now we move to the next line

    // --- Basic input with std::cin ---
    std::cout << "\nEnter a number: ";
    int userNumber{};
    std::cin >> userNumber; // Reads an integer from the keyboard
    std::cout << "You entered: " << userNumber << '\n';

    // --- Chaining the extraction operator >> ---
    std::cout << "Enter two numbers separated by a space: ";
    int a{};
    int b{};
    std::cin >> a >> b; // Reads two integers in one statement
    std::cout << "You entered: " << a << " and " << b << '\n';
    std::cout << "Their sum is: " << (a + b) << '\n';

    // --- PITFALL DEMO: '/n' vs '\n' ---
    // '\n' is the newline escape character (correct).
    // '/n' is the character '/' followed by 'n' - NOT a newline.
    std::cout << "\nCorrect newline: Hello\nWorld\n";
    // If you accidentally write '/n', you'd see something like: Hello/nWorld
    // (No actual newline - just the literal characters / and n)

    // --- Summary of operators ---
    std::cout << "\n--- Remember ---\n";
    std::cout << "std::cout << value;    (insertion: data goes INTO the stream)\n";
    std::cout << "std::cin  >> variable; (extraction: data comes OUT OF the stream)\n";
    std::cout << "Use '\\n' (backslash-n) for newlines, not std::endl.\n";

    return 0;
}
