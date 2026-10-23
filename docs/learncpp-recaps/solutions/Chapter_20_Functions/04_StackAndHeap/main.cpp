// Chapter 20 - Project 04: The Stack and the Heap
// ================================================
// Demonstrates: the difference between stack and heap allocation,
// stack frames, and what leads to stack overflow.
//
// Key points:
//   - The call stack stores stack frames (return address, parameters, locals)
//     for each active function call.  It is fast but limited in size.
//   - The heap is used for dynamic allocation (new/delete).  It is large
//     but slower than the stack.
//   - Allocating huge arrays on the stack causes stack overflow.
//   - Every function call pushes a new stack frame; deep recursion can
//     exhaust the stack.

#include <iostream>
#include <memory> // std::unique_ptr

// -------------------------------------------------------
// 1. Observing stack frame addresses
// -------------------------------------------------------
void funcC()
{
    int local_c{3};
    // Each function's local lives at a different stack address.
    std::cout << "  funcC - &local_c = " << &local_c << '\n';
}

void funcB()
{
    int local_b{2};
    std::cout << "  funcB - &local_b = " << &local_b << '\n';
    funcC();
}

void funcA()
{
    int local_a{1};
    std::cout << "  funcA - &local_a = " << &local_a << '\n';
    funcB();
}

// -------------------------------------------------------
// 2. Stack vs. heap allocation
// -------------------------------------------------------
void stackVsHeap()
{
    // Stack allocation - fast, automatic lifetime
    int stackArray[10]{};
    std::cout << "\nStack array address: " << stackArray << '\n';

    // Heap allocation - larger capacity, manual or smart-pointer lifetime
    auto heapArray = std::make_unique<int[]>(10);
    std::cout << "Heap  array address: " << heapArray.get() << '\n';

    // Note: heapArray is automatically freed when unique_ptr goes out of scope.
    // NEVER do:  int hugeStack[10'000'000]{};  // likely stack overflow!
}

// -------------------------------------------------------
// 3. Demonstrating (controlled) deep recursion
// -------------------------------------------------------
// This counts how many recursive calls we can make before the stack fills up.
// We limit it to avoid an actual crash.
void countFrames(int depth, int maxDepth)
{
    if (depth >= maxDepth)
    {
        std::cout << "\nReached " << depth << " recursive frames (stopped intentionally).\n";
        return;
    }
    countFrames(depth + 1, maxDepth);
}

int main()
{
    std::cout << "=== Stack frame addresses (notice descending order on most systems) ===\n";
    funcA();

    std::cout << "\n=== Stack vs. Heap allocation ===";
    stackVsHeap();

    std::cout << "\n=== Deep (but safe) recursion demo ===";
    // 500 frames is safe; a typical stack can handle ~10,000+ small frames.
    countFrames(0, 500);

    std::cout << "\nKey takeaway: don't allocate large arrays on the stack,\n"
              << "and always provide a base case for recursion.\n";

    return 0;
}
