// Chapter 27 - Project 07: Inheritance and Catch-Block Order
// ============================================================
// Catch handlers are tested in ORDER - the FIRST matching handler wins.
//
// Because a base-class catch matches derived-class exceptions,
// you must list derived catch blocks BEFORE base catch blocks.
// Otherwise the derived handler is unreachable.
//
//   WRONG:  catch(Base&) before catch(Derived&)  → Derived is never caught
//   RIGHT:  catch(Derived&) before catch(Base&)  → works correctly

#include <iostream>
#include <stdexcept>
#include <string>

// Build a small exception hierarchy
class AppError : public std::runtime_error
{
public:
    AppError(const std::string &msg) : std::runtime_error{msg} {}
};

class IOError : public AppError
{
public:
    IOError(const std::string &msg) : AppError{msg} {}
};

class PermissionError : public IOError
{
public:
    PermissionError(const std::string &msg) : IOError{msg} {}
};

// Hierarchy:
//   std::exception
//     └── std::runtime_error
//           └── AppError
//                 └── IOError
//                       └── PermissionError

void throwPermission()
{
    throw PermissionError{"Access denied to /etc/shadow"};
}

void throwIO()
{
    throw IOError{"Disk read failure on sector 42"};
}

void throwApp()
{
    throw AppError{"Application configuration invalid"};
}

int main()
{
    // --- CORRECT order: most-derived first ---
    std::cout << "=== Correct catch order (derived before base) ===\n";

    auto handleCorrectly = [](auto thrower, const char *label)
    {
        try
        {
            thrower();
        }
        catch (const PermissionError &e) // most derived
        {
            std::cout << label << " → PermissionError: " << e.what() << '\n';
        }
        catch (const IOError &e) // less derived
        {
            std::cout << label << " → IOError: " << e.what() << '\n';
        }
        catch (const AppError &e) // least derived (of our hierarchy)
        {
            std::cout << label << " → AppError: " << e.what() << '\n';
        }
        catch (const std::exception &e) // standard base
        {
            std::cout << label << " → std::exception: " << e.what() << '\n';
        }
    };

    handleCorrectly(throwPermission, "Test 1"); // → PermissionError handler
    handleCorrectly(throwIO, "Test 2");         // → IOError handler
    handleCorrectly(throwApp, "Test 3");        // → AppError handler

    // --- WRONG order demonstration ---
    // If we put base before derived, the derived handler is unreachable.
    // (Most compilers will warn about this.)
    std::cout << "\n=== Wrong order: base catches everything ===\n";

    try
    {
        throwPermission(); // throws a PermissionError
    }
    catch (const AppError &e) // <-- base class listed first!
    {
        // This catches PermissionError because PermissionError IS-A AppError
        std::cout << "Caught by AppError handler (wrong order): " << e.what() << '\n';
    }
    // A PermissionError handler here would be unreachable
    // catch (const PermissionError& e) { ... } // UNREACHABLE

    // --- Catch by const reference to avoid slicing ---
    std::cout << "\n=== Always catch by const reference ===\n";
    try
    {
        throwPermission();
    }
    catch (const std::exception &e) // const reference - no slicing, no copy
    {
        // what() still returns the PermissionError message because
        // what() is virtual and we caught by reference (not by value).
        std::cout << "Caught by std::exception&: " << e.what() << '\n';
    }

    return 0;
}
