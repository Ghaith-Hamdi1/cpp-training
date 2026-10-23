// Chapter 27 - Project 08: Rethrowing Exceptions
// =================================================
// When a catch block cannot fully handle an exception, it can rethrow it
// so a handler further up the call stack can finish the job.
//
// CORRECT:   throw;               - rethrows the ORIGINAL exception (no copy, no slicing)
// WRONG:     throw caughtVar;     - creates a COPY; slices derived types back to base
//
// Always use throw; (no operand) to rethrow.

#include <iostream>
#include <string>
#include <stdexcept>

class BaseError : public std::runtime_error
{
public:
    BaseError(const std::string &msg) : std::runtime_error{msg} {}
};

class DetailedError : public BaseError
{
    int m_code;

public:
    DetailedError(const std::string &msg, int code)
        : BaseError{msg}, m_code{code} {}

    int getCode() const { return m_code; }
};

// A function that partially handles the exception and rethrows
void processData(int value)
{
    try
    {
        if (value < 0)
            throw DetailedError{"Negative value", value};

        std::cout << "Processed: " << value << '\n';
    }
    catch (const BaseError &e)
    {
        // Log locally but can't fully handle - rethrow for the caller
        std::cout << "  processData() logged error: " << e.what() << '\n';
        throw; // CORRECT: rethrows the original DetailedError, not a sliced BaseError
    }
}

int main()
{
    // --- Correct rethrowing with throw; ---
    std::cout << "=== Correct rethrow with throw; ===\n";
    try
    {
        processData(-5);
    }
    catch (const DetailedError &e)
    {
        // We can still catch as DetailedError because throw; preserved the type
        std::cout << "  main() caught DetailedError: " << e.what()
                  << " (code: " << e.getCode() << ")\n";
    }

    // --- Demonstrating the WRONG way: throw caughtVar; causes slicing ---
    std::cout << "\n=== Wrong rethrow with throw caughtVar; (slicing!) ===\n";
    try
    {
        try
        {
            throw DetailedError{"Critical failure", 99};
        }
        catch (const BaseError &e)
        {
            std::cout << "  Inner catch: " << e.what() << '\n';

            // BAD: creates a COPY of BaseError, slicing away DetailedError data
            throw e; // This slices! The DetailedError becomes a BaseError copy
        }
    }
    catch (const DetailedError &e)
    {
        // This handler will NOT be reached because 'e' was sliced to BaseError
        std::cout << "  Outer caught DetailedError (this won't print)\n";
    }
    catch (const BaseError &e)
    {
        // This handler catches the sliced copy
        std::cout << "  Outer caught BaseError (sliced!): " << e.what() << '\n';
        std::cout << "  (DetailedError::getCode() is lost due to slicing)\n";
    }

    // --- Rethrow from a catch-all ---
    std::cout << "\n=== Rethrow from catch-all ===\n";
    try
    {
        try
        {
            throw 42; // throw an int
        }
        catch (...)
        {
            std::cout << "  catch-all: logging unknown exception, rethrowing...\n";
            throw; // rethrow the original int
        }
    }
    catch (int value)
    {
        std::cout << "  Outer caught int: " << value << '\n';
    }

    return 0;
}
