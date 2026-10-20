// ============================================================================
// Chapter 0, Project 09 - Console Window Fix
// Concept: Keeping the console window open after program execution.
// ============================================================================
//
// KEY IDEAS (Section 0.8):
//   - On Windows, running a program outside an IDE may cause the console
//     window to close immediately after the program finishes.
//   - This happens because Windows closes the console when the process exits.
//   - FIX: Use std::cin.get() at the end of main() to wait for the user
//     to press Enter before the program exits.
//   - NOTE: If you're running inside an IDE (Visual Studio, VS Code terminal),
//     the console usually stays open automatically.
//   - std::cin.get() reads a single character - if you press Enter, the
//     program proceeds past that line and exits normally.
//
// BUILD:  g++ -std=c++20 -Wall -Wextra -Werror -o ConsoleWindowFix main.cpp
// ============================================================================

#include <iostream>

int main()
{
    std::cout << "=== Console Window Fix ===" << std::endl;
    std::cout << std::endl;

    std::cout << "THE PROBLEM:" << std::endl;
    std::cout << "  On Windows, double-clicking an .exe opens a console window." << std::endl;
    std::cout << "  When the program finishes, the window closes instantly." << std::endl;
    std::cout << "  You never get to see the output!" << std::endl;
    std::cout << std::endl;

    std::cout << "THE FIX:" << std::endl;
    std::cout << "  Add std::cin.get() before the return statement." << std::endl;
    std::cout << "  This pauses the program until you press Enter." << std::endl;
    std::cout << std::endl;

    std::cout << "WHEN TO USE THIS:" << std::endl;
    std::cout << "  - Running .exe by double-clicking in File Explorer." << std::endl;
    std::cout << "  - Any situation where the console closes too fast." << std::endl;
    std::cout << std::endl;

    std::cout << "WHEN YOU DON'T NEED IT:" << std::endl;
    std::cout << "  - Running inside Visual Studio (it pauses automatically)." << std::endl;
    std::cout << "  - Running from a terminal/command prompt (stays open)." << std::endl;
    std::cout << "  - Running in VS Code's integrated terminal." << std::endl;
    std::cout << std::endl;

    // This is the fix in action:
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get(); // Waits for the user to press Enter

    return 0;
}
