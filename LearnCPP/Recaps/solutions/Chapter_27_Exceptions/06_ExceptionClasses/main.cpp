// Chapter 27 - Project 06: Exception Classes and std::exception
// ===============================================================
// Throwing primitive types (int, string) is fragile. Exception classes
// provide richer error context: messages, error codes, source info, etc.
//
// The standard library hierarchy:
//   std::exception              - base class, provides what()
//     ├── std::runtime_error    - for runtime errors (good to derive from)
//     ├── std::logic_error      - for logic/programming errors
//     ├── std::bad_alloc        - thrown by failed new
//     └── ...many others
//
// Best practice: catch by const reference to avoid copies and slicing.

#include <iostream>
#include <string>
#include <stdexcept>
#include <exception>

// --- Custom exception class (deriving from std::runtime_error) ---
class FileNotFoundError : public std::runtime_error
{
    std::string m_filename;

public:
    FileNotFoundError(const std::string &filename)
        : std::runtime_error{"File not found: " + filename}, m_filename{filename}
    {
    }

    const std::string &getFilename() const { return m_filename; }
};

// --- Another custom exception ---
class NetworkError : public std::runtime_error
{
    int m_errorCode;

public:
    NetworkError(const std::string &message, int code)
        : std::runtime_error{message}, m_errorCode{code}
    {
    }

    int getErrorCode() const { return m_errorCode; }
};

// --- A standalone custom exception class (from std::exception) ---
class DatabaseError : public std::exception
{
    std::string m_message;

public:
    DatabaseError(const std::string &msg) : m_message{msg} {}

    // Override what() to provide the error description
    const char *what() const noexcept override
    {
        return m_message.c_str();
    }
};

// Simulate operations that throw different exception types
void readFile(const std::string &filename)
{
    if (filename.empty())
        throw FileNotFoundError{"(empty filename)"};
    std::cout << "Reading file: " << filename << '\n';
}

void connectToServer(const std::string &host, int port)
{
    if (port < 0)
        throw NetworkError{"Invalid port for " + host, -1};
    std::cout << "Connected to " << host << ':' << port << '\n';
}

void queryDatabase(const std::string &query)
{
    if (query.empty())
        throw DatabaseError{"Empty SQL query"};
    std::cout << "Executed query: " << query << '\n';
}

int main()
{
    // --- Catching specific exception types ---
    std::cout << "=== Custom exception classes ===\n";
    try
    {
        readFile("");
    }
    catch (const FileNotFoundError &e)
    {
        std::cout << "FileNotFoundError: " << e.what() << '\n';
        std::cout << "  Filename was: " << e.getFilename() << '\n';
    }

    std::cout << '\n';
    try
    {
        connectToServer("example.com", -1);
    }
    catch (const NetworkError &e)
    {
        std::cout << "NetworkError: " << e.what()
                  << " (code " << e.getErrorCode() << ")\n";
    }

    std::cout << '\n';
    try
    {
        queryDatabase("");
    }
    catch (const DatabaseError &e)
    {
        std::cout << "DatabaseError: " << e.what() << '\n';
    }

    // --- Catching via the base class ---
    std::cout << "\n=== Catching via std::exception base ===\n";
    try
    {
        readFile(""); // throws FileNotFoundError
    }
    catch (const std::exception &e)
    {
        // Works because FileNotFoundError → std::runtime_error → std::exception
        std::cout << "Caught via std::exception: " << e.what() << '\n';
    }

    // --- Standard library exceptions ---
    std::cout << "\n=== Standard library exceptions ===\n";
    try
    {
        // std::stoi throws std::invalid_argument (derived from std::logic_error)
        int value = std::stoi("not_a_number");
        std::cout << value << '\n';
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "std::invalid_argument: " << e.what() << '\n';
    }

    try
    {
        // std::stoi throws std::out_of_range for values too large
        int value = std::stoi("99999999999999999999");
        std::cout << value << '\n';
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "std::out_of_range: " << e.what() << '\n';
    }

    return 0;
}
