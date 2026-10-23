// ============================================================================
// Chapter 19 - Project 06: RAII (Resource Acquisition Is Initialization)
// ============================================================================
// RAII ties resource lifetime to object lifetime:
//   - Constructor acquires the resource
//   - Destructor releases the resource
// This ensures resources are always cleaned up, even if exceptions occur
// or functions return early.
//
// Key points:
//   - If the constructor succeeds, the destructor is guaranteed to run.
//   - Eliminates manual new/delete pairing - no leaks possible.
//   - Standard library types (std::string, std::vector, std::unique_ptr)
//     all follow RAII.
// ============================================================================

#include <iostream>
#include <cstddef> // for std::size_t

// An RAII wrapper around a dynamic int array
class IntArray
{
private:
    int *m_data{};
    std::size_t m_size{};

public:
    // Constructor: acquires the resource
    explicit IntArray(std::size_t size)
        : m_data{new int[size]{}} // allocate and zero-initialize
          ,
          m_size{size}
    {
        std::cout << "[IntArray] Allocated " << m_size << " ints on the heap.\n";
    }

    // Destructor: releases the resource
    ~IntArray()
    {
        std::cout << "[IntArray] Freeing " << m_size << " ints.\n";
        delete[] m_data;
        // No need to set m_data = nullptr - the object is being destroyed
    }

    // Element access (with bounds checking)
    int &operator[](std::size_t index)
    {
        if (index >= m_size)
        {
            std::cerr << "Index " << index << " out of bounds (size " << m_size << ")!\n";
            // In real code you'd throw; here we just clamp to last element.
            index = m_size - 1;
        }
        return m_data[index];
    }

    const int &operator[](std::size_t index) const
    {
        if (index >= m_size)
        {
            std::cerr << "Index " << index << " out of bounds (size " << m_size << ")!\n";
            index = m_size - 1;
        }
        return m_data[index];
    }

    std::size_t size() const { return m_size; }

    // Prevent copying (we don't implement deep copy here)
    IntArray(const IntArray &) = delete;
    IntArray &operator=(const IntArray &) = delete;
};

void processData()
{
    // Create an RAII-managed array
    IntArray arr{5};

    // Fill it
    for (std::size_t i{0}; i < arr.size(); ++i)
        arr[i] = static_cast<int>(i * i);

    // Print it
    std::cout << "Array contents: ";
    for (std::size_t i{0}; i < arr.size(); ++i)
        std::cout << arr[i] << ' ';
    std::cout << '\n';

    // Simulate an early return - the destructor STILL runs!
    bool earlyExit{true};
    if (earlyExit)
    {
        std::cout << "Returning early - RAII guarantees cleanup.\n";
        return; // ~IntArray runs here automatically
    }

    // (Code after an early return is unreachable in this demo)
    std::cout << "This line won't execute.\n";
}

int main()
{
    std::cout << "=== RAII Demonstration ===\n\n";

    // -----------------------------------------------------------------
    // 1. RAII in action - no manual delete needed
    // -----------------------------------------------------------------
    processData();

    // -----------------------------------------------------------------
    // 2. RAII with scoped blocks
    // -----------------------------------------------------------------
    std::cout << "\n--- Scoped RAII block ---\n";
    {
        IntArray temp{3};
        temp[0] = 10;
        temp[1] = 20;
        temp[2] = 30;
        std::cout << "Inside scope: " << temp[0] << ", " << temp[1] << ", " << temp[2] << '\n';
    }
    // temp is destroyed here - memory freed automatically
    std::cout << "Outside scope - IntArray already freed.\n";

    // -----------------------------------------------------------------
    // 3. Contrast: raw new/delete (fragile)
    // -----------------------------------------------------------------
    std::cout << "\n--- Raw new/delete (fragile, avoid) ---\n";
    int *raw{new int[3]{100, 200, 300}};
    std::cout << "Raw: " << raw[0] << ", " << raw[1] << ", " << raw[2] << '\n';
    delete[] raw; // Must remember this - RAII does it for you!
    raw = nullptr;
    std::cout << "Manually freed raw array.\n";

    std::cout << "\nAll resources cleaned up via RAII.\n";
    return 0;
}
