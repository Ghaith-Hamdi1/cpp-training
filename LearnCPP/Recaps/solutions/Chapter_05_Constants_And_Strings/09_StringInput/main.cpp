// Chapter 5 - Project 09: String Input
// ======================================
// Topics:
//   - std::cin >> reads only one word (stops at whitespace)
//   - std::getline() reads an entire line
//   - The leftover '\n' problem after std::cin >>
//   - std::ws to discard leading whitespace
//   - Best practice: std::getline(std::cin >> std::ws, str)
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <string>

int main()
{
    // -------------------------------------------------------
    // 1. std::cin >> stops at whitespace
    // -------------------------------------------------------
    std::cout << "=== std::cin >> (single word) ===\n";
    std::cout << "Enter your first name: ";

    std::string firstName{};
    std::cin >> firstName; // Reads until first whitespace character

    std::cout << "Hello, " << firstName << "!\n";
    std::cout << "(If you typed 'John Doe', only 'John' was captured.)\n";

    // -------------------------------------------------------
    // 2. std::getline() reads the full line
    // -------------------------------------------------------
    // But there's a problem! After std::cin >>, a '\n' is left
    // in the input buffer. std::getline() will read that '\n'
    // and return an empty string.

    // WRONG way (demonstrates the bug):
    std::cout << "\n=== The Leftover '\\n' Problem ===\n";
    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age; // Reads the number, leaves '\n' in buffer

    std::cout << "Enter your full name: ";
    std::string fullName{};
    std::getline(std::cin, fullName); // BUG: reads the leftover '\n' immediately!

    std::cout << "Age: " << age << '\n';
    std::cout << "Full name: \"" << fullName << "\" (likely empty due to the bug!)\n";

    // -------------------------------------------------------
    // 3. The fix: std::getline(std::cin >> std::ws, str)
    // -------------------------------------------------------
    // std::ws is an input manipulator that discards leading whitespace
    // (including the leftover '\n') before std::getline reads.

    std::cout << "\n=== The Fix: std::ws ===\n";
    std::cout << "Enter your age again: ";
    int age2{};
    std::cin >> age2;

    std::cout << "Enter your full name: ";
    std::string fullName2{};
    std::getline(std::cin >> std::ws, fullName2); // CORRECT: std::ws eats the '\n'

    std::cout << "Age: " << age2 << '\n';
    std::cout << "Full name: \"" << fullName2 << "\" (correct this time!)\n";

    // -------------------------------------------------------
    // 4. Best practice summary
    // -------------------------------------------------------
    std::cout << "\n=== Best Practice ===\n";
    std::cout << "ALWAYS use: std::getline(std::cin >> std::ws, str)\n";
    std::cout << "This ensures leftover whitespace is consumed first.\n";
    std::cout << "Works correctly whether or not there's a prior >> extraction.\n";

    // -------------------------------------------------------
    // 5. Multiple getline calls in a row
    // -------------------------------------------------------
    std::cout << "\n=== Multiple getline Calls ===\n";
    std::cout << "Enter your city: ";
    std::string city{};
    std::getline(std::cin >> std::ws, city);

    std::cout << "Enter your country: ";
    std::string country{};
    std::getline(std::cin >> std::ws, country);

    std::cout << "You live in " << city << ", " << country << ".\n";

    return 0;
}
