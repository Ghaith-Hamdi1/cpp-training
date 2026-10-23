// ============================================================================
// Chapter 19 - Project 01: Dynamic Allocation with new and delete
// ============================================================================
// Demonstrates the three memory allocation types (static, automatic, dynamic)
// and shows how to use 'new' and 'delete' for single-variable heap allocation.
//
// Key points:
//   - 'new' allocates memory on the heap and returns a pointer to it.
//   - 'delete' frees that memory - every 'new' must have a matching 'delete'.
//   - Deleting a nullptr is safe (does nothing).
//   - std::nothrow lets you handle allocation failure gracefully.
// ============================================================================

#include <iostream>
#include <new> // for std::nothrow

int main()
{
    // -----------------------------------------------------------------
    // 1. Static vs. Automatic vs. Dynamic allocation
    // -----------------------------------------------------------------
    // static:    lives for the entire program     (keyword 'static')
    // automatic: lives within its scope/block     (local variables)
    // dynamic:   controlled by the programmer     (new / delete)

    static int staticVar{10}; // static storage duration
    int autoVar{20};          // automatic storage duration

    // Dynamic allocation - allocated on the heap
    int *dynPtr{new int{30}}; // allocate an int, initialize to 30
    std::cout << "Static:    " << staticVar << '\n';
    std::cout << "Automatic: " << autoVar << '\n';
    std::cout << "Dynamic:   " << *dynPtr << '\n';

    // -----------------------------------------------------------------
    // 2. Modifying dynamically allocated memory
    // -----------------------------------------------------------------
    *dynPtr = 42;
    std::cout << "Modified:  " << *dynPtr << '\n';

    // -----------------------------------------------------------------
    // 3. Freeing memory with delete
    // -----------------------------------------------------------------
    // The pointer still exists after delete, but the memory it pointed to
    // is returned to the OS. Using *dynPtr after this is UNDEFINED BEHAVIOR.
    delete dynPtr;

    // Best practice: set the pointer to nullptr after deleting
    dynPtr = nullptr;

    // -----------------------------------------------------------------
    // 4. Deleting nullptr is safe
    // -----------------------------------------------------------------
    // This is a no-op - no need to check "if (dynPtr)" before deleting.
    delete dynPtr; // safe: dynPtr is nullptr
    std::cout << "Deleting nullptr succeeded (no crash).\n";

    // -----------------------------------------------------------------
    // 5. Handling allocation failure with std::nothrow
    // -----------------------------------------------------------------
    // By default, 'new' throws std::bad_alloc on failure.
    // 'new (std::nothrow)' returns nullptr instead, letting you check.
    int *safePtr{new (std::nothrow) int{99}};
    if (!safePtr)
    {
        std::cerr << "Memory allocation failed!\n";
        return 1;
    }

    std::cout << "nothrow allocation: " << *safePtr << '\n';
    delete safePtr;
    safePtr = nullptr;

    // -----------------------------------------------------------------
    // 6. Value initialization with new
    // -----------------------------------------------------------------
    int *zeroInit{new int{}};                                    // value-initialized to 0
    std::cout << "Value-initialized int: " << *zeroInit << '\n'; // prints 0
    delete zeroInit;
    zeroInit = nullptr;

    std::cout << "\nAll dynamic memory properly freed. No leaks!\n";
    return 0;
}
