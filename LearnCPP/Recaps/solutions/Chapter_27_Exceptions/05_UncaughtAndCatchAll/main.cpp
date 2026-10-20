// Chapter 27 - Project 05: Uncaught Exceptions and Catch-All Handlers
// ====================================================================
// If no matching catch handler is found for a thrown exception,
// std::terminate() is called and the program ends abruptly.
// The stack may or may NOT be unwound (implementation-defined).
//
// The catch-all handler: catch(...)
//   - Catches exceptions of ANY type
//   - Must be placed LAST among catch blocks
//   - Cannot access the exception object (type is unknown)
//
// Best practice: wrap main() in a try/catch-all for orderly shutdown.

#include <iostream>
#include <string>
#include <exception>

// A function that might throw various types
void riskyOperation(int code)
{
    switch (code)
    {
    case 1:
        throw 42; // int
    case 2:
        throw 3.14; // double
    case 3:
        throw std::string{"string error"}; // string
    case 4:
        throw std::runtime_error{"runtime error"}; // std::exception-derived
    case 5:
        throw 'X'; // char (unusual)
    default:
        break;
    }
}

int main()
{
    // --- Demonstrating the catch-all handler ---
    std::cout << "=== Catch-all handler catches any type ===\n";
    for (int code{1}; code <= 5; ++code)
    {
        try
        {
            riskyOperation(code);
        }
        catch (int value)
        {
            std::cout << "Caught int: " << value << '\n';
        }
        catch (double value)
        {
            std::cout << "Caught double: " << value << '\n';
        }
        catch (const std::exception &e)
        {
            // Catches std::runtime_error and all std::exception-derived types
            std::cout << "Caught std::exception: " << e.what() << '\n';
        }
        catch (...)
        {
            // Catch-all: catches anything not matched above (char, string, etc.)
            // We cannot access the exception value here.
            std::cout << "Caught unknown exception (catch-all)\n";
        }
    }

    // --- Pattern: wrapping main() in try/catch-all ---
    std::cout << "\n=== Wrapping main logic in try/catch-all ===\n";
    std::cout << "Best practice: ensures orderly shutdown on ANY exception.\n\n";

    try
    {
        // Simulate main application logic
        std::cout << "Application starting...\n";

        // Some deeply nested code throws an unexpected type
        throw 'Z'; // unexpected exception type

        std::cout << "Application finishing normally\n"; // never reached
    }
    catch (const std::exception &e)
    {
        std::cerr << "Standard exception: " << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        // Last resort - we don't know what was thrown, but we can
        // log a message and exit cleanly instead of crashing.
        std::cerr << "Unknown exception caught - shutting down safely.\n";
        return 1;
    }

    // NOTE: If catch(...) is placed BEFORE more specific handlers,
    // the compiler will warn (or error) because it would shadow them.
    // Always place catch(...) LAST.

    return 0;
}
