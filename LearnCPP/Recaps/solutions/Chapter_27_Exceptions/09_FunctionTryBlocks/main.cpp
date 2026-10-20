// Chapter 27 - Project 09: Function Try Blocks
// ================================================
// A function try block wraps the ENTIRE function body (including the
// member initializer list) in a try/catch. This is the only way to
// catch exceptions thrown by base-class or member-object constructors.
//
// Rules for constructor function try blocks:
//   - The catch block MUST throw or rethrow - it CANNOT swallow the exception
//     (the object failed to construct; there's nothing valid to return)
//   - If the catch block doesn't explicitly throw, the original exception
//     is automatically rethrown

#include <iostream>
#include <string>
#include <stdexcept>

// A member class that might throw during construction
class DatabaseHandle
{
    std::string m_connStr;

public:
    DatabaseHandle(const std::string &connStr)
        : m_connStr{connStr}
    {
        if (connStr.empty())
            throw std::runtime_error{"DatabaseHandle: empty connection string"};
        std::cout << "  DatabaseHandle connected: " << m_connStr << '\n';
    }

    ~DatabaseHandle()
    {
        std::cout << "  DatabaseHandle disconnected: " << m_connStr << '\n';
    }
};

// A base class that might throw
class Base
{
    int m_value;

public:
    Base(int value) : m_value{value}
    {
        if (value < 0)
            throw std::runtime_error{"Base: negative value not allowed"};
        std::cout << "  Base constructed with " << m_value << '\n';
    }

    ~Base()
    {
        std::cout << "  Base destroyed\n";
    }
};

// A derived class using a function try block to catch exceptions
// from the base class constructor and member initializers
class Application : public Base
{
    DatabaseHandle m_db;

public:
    // Function try block: the try wraps the initializer list AND the body
    Application(int baseValue, const std::string &dbConn)
    try
        : Base{baseValue} // might throw
          ,
          m_db{dbConn} // might throw
    {
        std::cout << "  Application body executed successfully\n";
    }
    catch (const std::runtime_error &e)
    {
        // We can log the error, but we MUST throw or rethrow.
        // If we don't explicitly throw, the original exception is rethrown anyway.
        std::cerr << "  Application constructor failed: " << e.what() << '\n';
        // Implicitly rethrows if we don't throw ourselves
        // throw; // optional - happens automatically
    }

    ~Application()
    {
        std::cout << "  Application destroyed\n";
    }
};

// Function try block on a regular (non-constructor) function
int safeDivide(int a, int b)
try
{
    if (b == 0)
        throw std::runtime_error{"division by zero"};
    return a / b;
}
catch (const std::runtime_error &e)
{
    std::cerr << "  safeDivide error: " << e.what() << '\n';
    return 0; // regular functions CAN return a value from the catch block
}

int main()
{
    // --- Successful construction ---
    std::cout << "=== Successful Application construction ===\n";
    try
    {
        Application app{42, "localhost:5432"};
        std::cout << "  App is alive and well\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "main caught: " << e.what() << '\n';
    }

    // --- Base class constructor throws ---
    std::cout << "\n=== Base class throws ===\n";
    try
    {
        Application app{-1, "localhost:5432"}; // Base throws
    }
    catch (const std::exception &e)
    {
        // The function try block in Application caught it, logged it,
        // and rethrew it - so we catch it here in main
        std::cerr << "main caught: " << e.what() << '\n';
    }

    // --- Member constructor throws ---
    std::cout << "\n=== Member (DatabaseHandle) throws ===\n";
    try
    {
        Application app{42, ""}; // DatabaseHandle throws
    }
    catch (const std::exception &e)
    {
        std::cerr << "main caught: " << e.what() << '\n';
    }

    // --- Function try block on a regular function ---
    std::cout << "\n=== Function try block on regular function ===\n";
    std::cout << "10 / 2 = " << safeDivide(10, 2) << '\n';
    std::cout << "10 / 0 = " << safeDivide(10, 0) << " (handled gracefully)\n";

    return 0;
}
