// Chapter 22 - Project 01: Smart Pointer Motivation
// Why raw pointers are dangerous and how RAII smart pointers fix memory leaks.
//
// Key idea: If a function allocates with `new` and exits early (return,
// exception, etc.) before `delete`, the memory leaks.  A smart-pointer
// class wraps the raw pointer and calls `delete` in its destructor,
// guaranteeing cleanup no matter how the scope exits.

#include <iostream>
#include <stdexcept>

// -----------------------------------------------------------------------
// 1. The problem: raw pointers can easily leak
// -----------------------------------------------------------------------
void riskyFunction()
{
    int *ptr = new int(42);

    // Imagine some logic that may throw or return early:
    bool earlyReturn = true;
    if (earlyReturn)
    {
        std::cout << "[RAW]  Returning early - memory at " << ptr << " is LEAKED!\n";
        // We forgot to delete ptr here!
        return; // <-- LEAK: ptr is never freed
    }

    delete ptr; // This line is never reached
}

// -----------------------------------------------------------------------
// 2. A minimal RAII smart pointer (educational, NOT production code)
// -----------------------------------------------------------------------
template <typename T>
class SmartPtr
{
    T *m_ptr{};

public:
    explicit SmartPtr(T *ptr = nullptr) : m_ptr{ptr}
    {
        std::cout << "[SmartPtr] Acquired resource at " << m_ptr << '\n';
    }

    // Destructor: automatically frees the resource
    ~SmartPtr()
    {
        std::cout << "[SmartPtr] Destroying resource at " << m_ptr << '\n';
        delete m_ptr;
    }

    // Dereference operators so it behaves like a pointer
    T &operator*() const { return *m_ptr; }
    T *operator->() const { return m_ptr; }

    // Disable copy to avoid double-delete (we'll handle move later)
    SmartPtr(const SmartPtr &) = delete;
    SmartPtr &operator=(const SmartPtr &) = delete;
};

// -----------------------------------------------------------------------
// 3. Safe function: uses our SmartPtr - no leak possible
// -----------------------------------------------------------------------
void safeFunction()
{
    SmartPtr<int> ptr(new int(42));

    bool earlyReturn = true;
    if (earlyReturn)
    {
        std::cout << "[SAFE] Returning early - SmartPtr destructor will clean up!\n";
        return; // SmartPtr destructor runs, memory freed automatically
    }

    // Even if we never reach here, no leak.
}

// -----------------------------------------------------------------------
// 4. Exception safety: smart pointer still cleans up on throw
// -----------------------------------------------------------------------
void throwingFunction()
{
    SmartPtr<int> ptr(new int(99));

    std::cout << "[THROW] About to throw an exception...\n";
    throw std::runtime_error("Oops!");

    // ptr's destructor is still called during stack unwinding
}

// -----------------------------------------------------------------------
int main()
{
    std::cout << "=== 1. Raw pointer leak demo ===\n";
    riskyFunction();

    std::cout << "\n=== 2. SmartPtr prevents leak ===\n";
    safeFunction();

    std::cout << "\n=== 3. SmartPtr + exception safety ===\n";
    try
    {
        throwingFunction();
    }
    catch (const std::exception &e)
    {
        std::cout << "[CATCH] Exception caught: " << e.what() << '\n';
        std::cout << "        Resource was still cleaned up by SmartPtr.\n";
    }

    std::cout << "\nDone.\n";
    return 0;
}
