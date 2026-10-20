// ============================================================================
// Chapter 19 - Project 05: Destructors
// ============================================================================
// A destructor (~ClassName) is a special member function called automatically
// when an object is destroyed (goes out of scope or is explicitly deleted).
//
// Key points:
//   - Destructors have no parameters and no return type.
//   - They are called automatically - you never call them manually.
//   - Use destructors to release resources (dynamic memory, file handles, etc.).
//   - std::exit() does NOT call destructors - avoid it if objects own resources.
// ============================================================================

#include <iostream>
#include <cstring> // for strlen, strcpy_s / strncpy

class SimpleMessage
{
private:
    char *m_message{}; // dynamically allocated C-string

public:
    // Constructor - acquires the resource (dynamic memory)
    SimpleMessage(const char *msg)
    {
        std::size_t len{std::strlen(msg) + 1};
        m_message = new char[len];

        // Copy message safely
#ifdef _MSC_VER
        strcpy_s(m_message, len, msg); // MSVC
#else
        std::strncpy(m_message, msg, len); // GCC/Clang
#endif

        std::cout << "  [Constructor] Allocated and stored: \"" << m_message << "\"\n";
    }

    // Destructor - releases the resource
    ~SimpleMessage()
    {
        std::cout << "  [Destructor]  Freeing: \"" << m_message << "\"\n";
        delete[] m_message;
        m_message = nullptr;
    }

    void print() const
    {
        std::cout << "  Message: " << m_message << '\n';
    }

    // Prevent copying for simplicity (rule of three)
    SimpleMessage(const SimpleMessage &) = delete;
    SimpleMessage &operator=(const SimpleMessage &) = delete;
};

void demonstrateAutomaticDestruction()
{
    std::cout << "\n--- Automatic destruction (stack object) ---\n";
    SimpleMessage msg{"Hello from the stack!"};
    msg.print();
    // msg goes out of scope here - destructor is called automatically
}

void demonstrateDynamicDestruction()
{
    std::cout << "\n--- Dynamic destruction (heap object) ---\n";
    SimpleMessage *msgPtr{new SimpleMessage{"Hello from the heap!"}};
    msgPtr->print();

    // For heap objects, destructor is called when we 'delete' the pointer
    delete msgPtr;
    msgPtr = nullptr;
    std::cout << "  Heap object deleted.\n";
}

void demonstrateDestructionOrder()
{
    std::cout << "\n--- Destruction order (reverse of construction) ---\n";
    SimpleMessage first{"First"};
    SimpleMessage second{"Second"};
    SimpleMessage third{"Third"};
    // Destructors will fire in REVERSE order: Third, Second, First
    std::cout << "  About to leave scope...\n";
}

int main()
{
    std::cout << "=== Destructor Demonstration ===\n";

    demonstrateAutomaticDestruction();
    demonstrateDynamicDestruction();
    demonstrateDestructionOrder();

    // -----------------------------------------------------------------
    // Note about std::exit()
    // -----------------------------------------------------------------
    // std::exit() terminates the program WITHOUT calling destructors
    // for local objects. If any object manages resources (like our
    // SimpleMessage), those resources would leak.
    //
    // Example (DON'T do this if objects own resources):
    //   std::exit(0);   // destructors NOT called - memory leaked!
    //
    // Best practice: let main() return normally so all destructors run.

    std::cout << "\nAll destructors ran properly.\n";
    return 0;
}
