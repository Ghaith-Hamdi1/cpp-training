// Chapter 27 - Project 11: RAII and Exception Safety
// =====================================================
// Exceptions can cause resource leaks if cleanup code (delete, close, etc.)
// is skipped because a throw jumps over it.
//
// The solution: RAII (Resource Acquisition Is Initialization)
//   - Wrap resources in objects whose destructors release them
//   - Destructors always run during stack unwinding
//   - Use smart pointers (std::unique_ptr, std::shared_ptr) for heap memory
//
// CRITICAL: Never throw from a destructor during stack unwinding.
//   If a destructor throws while another exception is propagating,
//   std::terminate is called and the program dies.
//
// Exception safety guarantees (4 levels):
//   1. No guarantee         - anything can happen
//   2. Basic guarantee      - no leaks, objects in valid (but unspecified) state
//   3. Strong guarantee     - operation succeeds or has no effect (rollback)
//   4. No-throw / No-fail  - operation never throws (e.g., destructors, swap)

#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

// --- BAD EXAMPLE: manual resource management leaks on exception ---
void badExample()
{
    std::cout << "=== BAD: Manual new/delete leaks on exception ===\n";

    int *data = new int[1000];
    std::cout << "  Allocated data\n";

    // If this throws, the delete[] below is never reached → LEAK!
    bool errorOccurred{true}; // simulate an error
    if (errorOccurred)
    {
        // delete[] data; // We'd have to remember to clean up here too!
        // But what if there are multiple resources? It becomes unmanageable.
        std::cout << "  ERROR: exception would leak 'data' (skipping throw for demo)\n";
    }

    delete[] data;
    std::cout << "  Freed data (only reached if no exception)\n";
}

// --- GOOD EXAMPLE: RAII with smart pointers - leak-proof ---
void goodExample()
{
    std::cout << "\n=== GOOD: Smart pointer - automatic cleanup ===\n";

    auto data = std::make_unique<int[]>(1000);
    std::cout << "  Allocated data via unique_ptr\n";

    // Even if we throw here, unique_ptr's destructor releases the memory
    throw std::runtime_error{"Something went wrong"};

    // This line is never reached, but 'data' is still freed!
    std::cout << "  This line is never reached\n";
}

// --- RAII wrapper for a file-like resource ---
class FileHandle
{
    std::string m_filename;
    bool m_open{};

public:
    FileHandle(const std::string &filename)
        : m_filename{filename}, m_open{true}
    {
        std::cout << "  FileHandle: opened " << m_filename << '\n';
    }

    ~FileHandle()
    {
        // Destructor ensures the file is always closed
        // NEVER throw from a destructor!
        if (m_open)
        {
            m_open = false;
            std::cout << "  FileHandle: closed " << m_filename << '\n';
        }
    }

    void write(const std::string &content)
    {
        if (content.empty())
            throw std::runtime_error{"Cannot write empty content"};
        std::cout << "  FileHandle: wrote \"" << content << "\" to " << m_filename << '\n';
    }
};

void raiiFileExample()
{
    std::cout << "\n=== RAII file handle - always closed ===\n";

    FileHandle file{"output.txt"};
    file.write("Hello");
    file.write(""); // throws - but FileHandle destructor still closes the file
}

// --- Exception safety levels demonstration ---
class SafeContainer
{
    std::unique_ptr<int[]> m_data;
    std::size_t m_size{};

public:
    SafeContainer() = default;

    // Strong guarantee: if push fails, container is unchanged
    void push(int value)
    {
        // Create new storage first (might throw bad_alloc)
        auto newData = std::make_unique<int[]>(m_size + 1);

        // Copy old data (if this threw, newData would clean itself up)
        for (std::size_t i{0}; i < m_size; ++i)
            newData[i] = m_data[i];

        newData[m_size] = value;

        // Commit - swap is noexcept, so this can't fail
        m_data = std::move(newData);
        ++m_size;
    }

    // No-throw guarantee
    std::size_t size() const noexcept { return m_size; }

    void print() const
    {
        std::cout << "  [";
        for (std::size_t i{0}; i < m_size; ++i)
        {
            if (i > 0)
                std::cout << ", ";
            std::cout << m_data[i];
        }
        std::cout << "]\n";
    }
};

int main()
{
    // --- Bad: manual management ---
    badExample();

    // --- Good: smart pointers ---
    try
    {
        goodExample();
    }
    catch (const std::exception &e)
    {
        std::cout << "  Caught: " << e.what() << '\n';
        std::cout << "  (unique_ptr cleaned up automatically during unwinding)\n";
    }

    // --- RAII file handle ---
    try
    {
        raiiFileExample();
    }
    catch (const std::exception &e)
    {
        std::cout << "  Caught: " << e.what() << '\n';
        std::cout << "  (FileHandle was closed by its destructor)\n";
    }

    // --- Strong exception guarantee container ---
    std::cout << "\n=== Strong exception guarantee ===\n";
    SafeContainer sc;
    sc.push(10);
    sc.push(20);
    sc.push(30);
    std::cout << "  Container after 3 pushes: ";
    sc.print();

    // --- Key takeaway ---
    std::cout << "\n=== Summary ===\n";
    std::cout << "  - Use RAII (smart pointers, RAII wrappers) for all resources\n";
    std::cout << "  - Never throw from destructors\n";
    std::cout << "  - Aim for strong or no-throw exception safety guarantees\n";

    return 0;
}
