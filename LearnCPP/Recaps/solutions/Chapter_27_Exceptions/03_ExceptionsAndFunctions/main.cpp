// Chapter 27 - Project 03: Exceptions, Functions, and Stack Unwinding
// ====================================================================
// Exceptions thrown inside a function propagate UP the call stack until
// a matching catch handler is found. The function that throws does NOT
// have to handle the exception itself - the caller (or the caller's
// caller, etc.) can handle it instead.
//
// Stack unwinding: as the exception propagates, each function is popped
// off the call stack and its local variables are destroyed normally.

#include <iostream>
#include <string>

// A simple RAII class to visualize construction/destruction during unwinding
class Tracer
{
    std::string m_name;

public:
    Tracer(const std::string &name) : m_name{name}
    {
        std::cout << "  [Tracer] " << m_name << " constructed\n";
    }
    ~Tracer()
    {
        std::cout << "  [Tracer] " << m_name << " destroyed\n";
    }
};

// Level 3: this is where the exception originates
void level3()
{
    Tracer t{"level3_local"};
    std::cout << "level3(): about to throw\n";
    throw std::string{"Exception from level3"};
    // Code after throw is never reached
}

// Level 2: calls level3, does NOT catch
void level2()
{
    Tracer t{"level2_local"};
    std::cout << "level2(): calling level3()\n";
    level3(); // exception propagates through here
    std::cout << "level2(): this line is never reached\n";
}

// Level 1: calls level2, does NOT catch
void level1()
{
    Tracer t{"level1_local"};
    std::cout << "level1(): calling level2()\n";
    level2(); // exception propagates through here
    std::cout << "level1(): this line is never reached\n";
}

int main()
{
    // --- Stack unwinding demonstration ---
    std::cout << "=== Stack unwinding: exception propagates from level3 to main ===\n";
    try
    {
        level1();
    }
    catch (const std::string &error)
    {
        // The exception was thrown in level3, but caught here in main.
        // All local Tracer objects (level3, level2, level1) were destroyed
        // during stack unwinding - you'll see their destructors fire above.
        std::cout << "\nmain(): caught: " << error << '\n';
    }

    // --- Handling at different levels ---
    std::cout << "\n=== A function can choose to handle its own exception ===\n";
    auto safeDivide = [](int a, int b) -> int
    {
        if (b == 0)
            throw std::string{"division by zero"};
        return a / b;
    };

    // Caller 1 handles the exception
    try
    {
        std::cout << "10 / 0 = " << safeDivide(10, 0) << '\n';
    }
    catch (const std::string &msg)
    {
        std::cout << "Caller1 handled: " << msg << '\n';
    }

    // Caller 2 doesn't even need a try/catch if it knows the call is safe
    std::cout << "10 / 2 = " << safeDivide(10, 2) << '\n';

    std::cout << "\nProgram continues normally after exception handling.\n";

    return 0;
}
