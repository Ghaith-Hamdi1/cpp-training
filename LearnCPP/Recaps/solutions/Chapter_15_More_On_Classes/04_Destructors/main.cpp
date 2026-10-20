// Chapter 15 - Project 04: Introduction to Destructors
// =====================================================
//
// A destructor (~ClassName) is called automatically when an object is
// destroyed (goes out of scope, is deleted, etc.).
//
// Rules:
//   - Takes no arguments, has no return type.
//   - A class can have only ONE destructor.
//   - If you don't declare one, the compiler generates an implicit
//     destructor with an empty body.
//   - Use destructors for cleanup: releasing memory, closing files,
//     flushing buffers, etc.
//
// PITFALL: std::exit() terminates the program WITHOUT calling destructors
// for local objects. Prefer normal returns for proper cleanup.

#include <iostream>
#include <string>
#include <cstdlib> // for std::exit

// -------------------------------------------------------
// A class that demonstrates destructor behaviour
// -------------------------------------------------------
class Logger
{
private:
    std::string m_name{};

public:
    Logger(const std::string &name)
        : m_name{name}
    {
        std::cout << "[Logger '" << m_name << "'] constructed\n";
    }

    // Destructor - called when the object is destroyed
    ~Logger()
    {
        std::cout << "[Logger '" << m_name << "'] DESTROYED - cleanup performed\n";
    }

    void log(const std::string &msg) const
    {
        std::cout << "[" << m_name << "] " << msg << '\n';
    }
};

// -------------------------------------------------------
// Demonstrate scope-based destruction
// -------------------------------------------------------
void demonstrateScope()
{
    std::cout << "\n--- demonstrateScope() ---\n";
    Logger outer{"outer"};
    outer.log("I'm in the function.");

    {
        Logger inner{"inner"};
        inner.log("I'm in a nested block.");
        // `inner` is destroyed here when the block ends
    }

    outer.log("inner is already destroyed.");
    // `outer` is destroyed here when the function returns
}

// -------------------------------------------------------
// Demonstrate the std::exit() pitfall
// -------------------------------------------------------
void demonstrateExitPitfall(bool useExit)
{
    std::cout << "\n--- demonstrateExitPitfall(useExit=" << std::boolalpha
              << useExit << ") ---\n";

    Logger obj{"exitTest"};
    obj.log("About to leave function...");

    if (useExit)
    {
        std::cout << "Calling std::exit()... destructor will NOT be called.\n";
        // WARNING: This would terminate the program immediately.
        // We'll just print a message instead of actually calling std::exit()
        // to keep the rest of the demo running.
        std::cout << "  (Skipping actual std::exit() call for demo purposes.)\n";
        std::cout << "  In real code, ~Logger() would never run for 'exitTest'.\n";
        return; // normal return so we can continue the demo
    }
    // Normal return - destructor WILL be called
}

// -------------------------------------------------------
// A class that manages a dynamic resource
// -------------------------------------------------------
class DynamicArray
{
private:
    int *m_data{};
    int m_size{};

public:
    DynamicArray(int size)
        : m_data{new int[size]{}}, m_size{size}
    {
        std::cout << "DynamicArray allocated " << m_size << " ints\n";
    }

    // Destructor releases the dynamic memory
    ~DynamicArray()
    {
        delete[] m_data; // Clean up!
        std::cout << "DynamicArray freed " << m_size << " ints\n";
    }

    void set(int index, int value)
    {
        if (index >= 0 && index < m_size)
            m_data[index] = value;
    }

    int get(int index) const
    {
        if (index >= 0 && index < m_size)
            return m_data[index];
        return -1;
    }
};

int main()
{
    // --- Scope-based destruction ---
    demonstrateScope();

    // --- The std::exit() pitfall ---
    demonstrateExitPitfall(false); // normal return - destructor runs
    demonstrateExitPitfall(true);  // simulated std::exit - destructor skipped

    // --- Resource management via destructor ---
    std::cout << "\n--- Dynamic resource cleanup ---\n";
    {
        DynamicArray arr{5};
        arr.set(0, 42);
        arr.set(4, 99);
        std::cout << "arr[0]=" << arr.get(0) << ", arr[4]=" << arr.get(4) << '\n';
        // Destructor frees memory at end of scope - no manual cleanup needed!
    }

    std::cout << "\nAll objects properly cleaned up.\n";
    return 0;
}
