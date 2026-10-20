// Chapter 2 - Project 04: Parameters and Arguments
// Concept: Function parameters, arguments, pass by value
//
// • Parameters - variables declared in the function's header (definition).
// • Arguments  - the actual values supplied at the call site.
// • Pass by value - arguments are COPIED into parameters.  Modifying a
//   parameter inside the function does NOT affect the caller's variable.
//
// Key rules:
//   • The number and types of arguments must match the parameters.
//   • Parameters are effectively local variables initialized by their
//     matching arguments.
//   • Unreferenced parameters can be left unnamed to suppress warnings.
// -----------------------------------------------------------------------

#include <iostream>

// A function with one parameter.
void printDouble(int value)
{
    std::cout << value << " doubled is " << (value * 2) << '\n';
}

// A function with two parameters.
int add(int x, int y)
{
    return x + y;
}

// Demonstrates that pass-by-value creates a COPY.
// Changing the parameter inside the function has NO effect on the caller.
void tryToModify(int num)
{
    std::cout << "  Inside tryToModify: num starts as " << num << '\n';
    num = 999; // Modifies the LOCAL copy only!
    std::cout << "  Inside tryToModify: num changed to " << num << '\n';
}

// A function with multiple parameters of different types.
void displayInfo(std::string name, int age)
{
    std::cout << name << " is " << age << " years old.\n";
}

// Unreferenced parameter - left unnamed to suppress compiler warnings.
// This is valid C++ and communicates intent: we don't use this parameter.
void logMessage(std::string message, int /* severity */)
{
    std::cout << "[LOG] " << message << '\n';
    // 'severity' is intentionally unused in this simplified version.
}

int main()
{
    std::cout << "=== Project 04: Parameters and Arguments ===\n\n";

    // 1. Single parameter
    std::cout << "--- printDouble ---\n";
    printDouble(7); // 7 is the argument, copied into parameter 'value'

    // 2. Two parameters - order matters!
    std::cout << "\n--- add ---\n";
    std::cout << "add(3, 4) = " << add(3, 4) << '\n';
    std::cout << "add(10, 20) = " << add(10, 20) << '\n';

    // 3. Pass by value - the original variable is NOT modified
    std::cout << "\n--- Pass by value demonstration ---\n";
    int original{42};
    std::cout << "Before: original = " << original << '\n';
    tryToModify(original); // A copy of 'original' is passed
    std::cout << "After:  original = " << original << " (unchanged!)\n";

    // 4. Variables as arguments - the value is copied, not the variable itself
    std::cout << "\n--- Variables as arguments ---\n";
    int a{5};
    int b{3};
    std::cout << "add(a, b) = " << add(a, b) << '\n';

    // 5. Expressions as arguments - the expression is evaluated first
    std::cout << "add(a + 1, b * 2) = " << add(a + 1, b * 2) << '\n';

    // 6. Different parameter types
    std::cout << "\n--- displayInfo ---\n";
    displayInfo("Alice", 30);

    // 7. Unnamed (unreferenced) parameter
    std::cout << "\n--- logMessage (unused severity parameter) ---\n";
    logMessage("System started", 1);

    return 0;
}
