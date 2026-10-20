// Chapter 27 - Project 01: The Need for Exceptions
// ===================================================
// Return codes are the traditional way to signal errors, but they have
// significant drawbacks:
//   1. They're cryptic (what does -1 mean?)
//   2. They can't coexist easily with a function's actual return value
//   3. They require constant checking that clutters control flow
//   4. They don't work with constructors or overloaded operators
//
// Exceptions solve all of these problems by decoupling error handling
// from normal control flow.

#include <iostream>
#include <string>
#include <cmath>

// ---- Approach 1: Return codes (problematic) ----

// Problem: the return value IS the result, so we can't also use it for errors.
// We're forced into awkward patterns like output parameters or sentinel values.
int divideReturnCode(int numerator, int denominator, bool &success)
{
    if (denominator == 0)
    {
        success = false;
        return 0; // meaningless sentinel value
    }
    success = true;
    return numerator / denominator;
}

// ---- Approach 2: Exceptions (clean) ----

// The function simply returns its result. Errors are signaled out-of-band.
int divideWithException(int numerator, int denominator)
{
    if (denominator == 0)
        throw std::string{"Division by zero"};

    return numerator / denominator;
}

// ---- Constructors: return codes are impossible ----

class DatabaseConnection
{
    std::string m_name;
    bool m_connected{};

public:
    // Constructors have no return value - exceptions are the only clean
    // way to signal that construction failed.
    DatabaseConnection(const std::string &name)
        : m_name{name}
    {
        // Simulate a connection failure
        if (name.empty())
            throw std::string{"Cannot connect: empty database name"};

        m_connected = true;
        std::cout << "Connected to " << m_name << '\n';
    }

    ~DatabaseConnection()
    {
        if (m_connected)
            std::cout << "Disconnected from " << m_name << '\n';
    }
};

int main()
{
    // --- Return-code approach: cluttered and error-prone ---
    std::cout << "=== Return-code approach ===\n";
    bool success{};
    int result{divideReturnCode(10, 0, success)};
    if (!success)
        std::cout << "Error: division by zero (return code)\n";
    else
        std::cout << "Result: " << result << '\n';

    // Every call site must check the flag - easy to forget.
    result = divideReturnCode(10, 2, success);
    if (success)
        std::cout << "10 / 2 = " << result << '\n';

    // --- Exception approach: clean and hard to ignore ---
    std::cout << "\n=== Exception approach ===\n";
    try
    {
        std::cout << "10 / 2 = " << divideWithException(10, 2) << '\n';
        std::cout << "10 / 0 = " << divideWithException(10, 0) << '\n'; // throws
        std::cout << "This line is never reached\n";
    }
    catch (const std::string &error)
    {
        std::cout << "Caught: " << error << '\n';
    }

    // --- Constructors: exceptions are essential ---
    std::cout << "\n=== Constructor exceptions ===\n";
    try
    {
        DatabaseConnection db1{"production_db"};
        DatabaseConnection db2{""}; // throws - no valid object is created
    }
    catch (const std::string &error)
    {
        std::cout << "Caught: " << error << '\n';
    }

    return 0;
}
