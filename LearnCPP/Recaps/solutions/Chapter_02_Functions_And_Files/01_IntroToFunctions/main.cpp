// Chapter 2 - Project 01: Introduction to Functions
// Concept: Basic function definition, calling, and execution flow
//
// A function is a reusable, named block of statements designed to do a
// particular job.  When the CPU encounters a function call it "bookmarks"
// its current location (the caller), jumps to the start of the called
// function (the callee), executes it, and then returns to the caller.
//
// Key rules:
//   • Programs begin execution at the top of main().
//   • Functions must be defined before they are called (or forward-declared).
//   • C++ does NOT allow nested function definitions (defining a function
//     inside another function).
// -----------------------------------------------------------------------

#include <iostream>

// A simple user-defined function that prints a greeting.
// It takes no parameters and returns nothing (implied void here, but we
// will cover void explicitly in Project 03).
void printGreeting()
{
    std::cout << "Hello from printGreeting()!\n";
}

// Another small function to demonstrate sequencing.
void printFarewell()
{
    std::cout << "Goodbye from printFarewell()!\n";
}

// A function that calls other functions, showing the call/return flow.
void demonstrateCallFlow()
{
    std::cout << "[demonstrateCallFlow] Before calling printGreeting()\n";
    printGreeting(); // CPU jumps to printGreeting, executes it, then returns here
    std::cout << "[demonstrateCallFlow] After printGreeting(), before printFarewell()\n";
    printFarewell(); // Same flow: jump, execute, return
    std::cout << "[demonstrateCallFlow] After printFarewell()\n";
}

int main()
{
    std::cout << "=== Project 01: Introduction to Functions ===\n\n";

    // 1. Calling a simple function
    std::cout << "--- Calling printGreeting() directly from main ---\n";
    printGreeting();

    // 2. A function calling other functions
    std::cout << "\n--- Calling demonstrateCallFlow() from main ---\n";
    demonstrateCallFlow();

    // 3. Functions can be called more than once - reusability!
    std::cout << "\n--- Calling printGreeting() again to show reusability ---\n";
    printGreeting();

    // Execution continues in main after all calls return.
    std::cout << "\nBack in main(). Program ends.\n";

    return 0; // Return 0 to indicate success
}
