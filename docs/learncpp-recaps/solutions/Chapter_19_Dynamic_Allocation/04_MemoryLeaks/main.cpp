// ============================================================================
// Chapter 19 - Project 04: Memory Leaks
// ============================================================================
// A memory leak occurs when dynamically allocated memory can no longer be
// freed because its address has been lost.
//
// Key points:
//   - Pointer goes out of scope without delete → leak
//   - Pointer reassigned without deleting old memory → leak
//   - Always 'delete' before a pointer loses access to its allocated memory
//   - RAII and smart pointers (std::unique_ptr) prevent leaks automatically
// ============================================================================

#include <iostream>

// Demonstrates a LEAKED allocation (called to show the concept)
void leakExample_scopeLoss()
{
    // BAD: ptr goes out of scope at the end of this function
    // without deleting the allocated memory - LEAK!
    // int* ptr{ new int{ 999 } };
    // (function returns, ptr destroyed, memory leaked)

    // FIXED version:
    int *ptr{new int{999}};
    std::cout << "[Scope] Allocated: " << *ptr << '\n';
    delete ptr; // Free before the pointer goes out of scope
    ptr = nullptr;
    std::cout << "[Scope] Freed - no leak.\n";
}

void leakExample_reassignment()
{
    // BAD: reassigning the pointer without freeing the old memory
    // int* ptr{ new int{ 10 } };
    // ptr = new int{ 20 };       // old memory (10) is now LEAKED

    // FIXED version:
    int *ptr{new int{10}};
    std::cout << "\n[Reassign] First allocation: " << *ptr << '\n';

    delete ptr;        // Free old memory FIRST
    ptr = new int{20}; // Then allocate new memory
    std::cout << "[Reassign] Second allocation: " << *ptr << '\n';

    delete ptr;
    ptr = nullptr;
    std::cout << "[Reassign] Both freed - no leak.\n";
}

void leakExample_earlyReturn()
{
    int *data{new int{42}};

    // Imagine a condition that causes an early return:
    bool errorOccurred{false};

    if (errorOccurred)
    {
        // BAD if we just return here without deleting data
        // return;    // LEAK!

        // FIXED: delete before returning
        delete data;
        data = nullptr;
        std::cout << "\n[EarlyReturn] Error path - freed before return.\n";
        return;
    }

    std::cout << "\n[EarlyReturn] Normal path: " << *data << '\n';
    delete data;
    data = nullptr;
    std::cout << "[EarlyReturn] Freed - no leak.\n";
}

int main()
{
    std::cout << "=== Memory Leak Prevention Examples ===\n\n";

    // -----------------------------------------------------------------
    // Cause 1: Pointer goes out of scope without delete
    // -----------------------------------------------------------------
    leakExample_scopeLoss();

    // -----------------------------------------------------------------
    // Cause 2: Pointer reassigned without freeing old memory
    // -----------------------------------------------------------------
    leakExample_reassignment();

    // -----------------------------------------------------------------
    // Cause 3: Early return skips delete
    // -----------------------------------------------------------------
    leakExample_earlyReturn();

    // -----------------------------------------------------------------
    // Cause 4: Losing the only pointer in a loop
    // -----------------------------------------------------------------
    std::cout << "\n[Loop] Allocating and freeing in a loop:\n";
    for (int i{0}; i < 5; ++i)
    {
        int *temp{new int{i * 10}};
        std::cout << "  Iteration " << i << ": " << *temp << '\n';

        // If we didn't delete here, each iteration would leak the previous one
        delete temp;
        // temp goes out of scope anyway at end of loop body - but we
        // still must delete before that happens.
    }
    std::cout << "[Loop] All iterations freed.\n";

    std::cout << "\nAll examples completed with no memory leaks.\n";
    return 0;
}
