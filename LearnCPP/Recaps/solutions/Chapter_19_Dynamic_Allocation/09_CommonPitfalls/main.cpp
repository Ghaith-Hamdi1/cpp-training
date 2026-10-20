// ============================================================================
// Chapter 19 - Project 09: Common Pitfalls with Dynamic Allocation
// ============================================================================
// This project demonstrates the most common mistakes with new/delete and
// shows the CORRECT way to handle each situation.
//
// Pitfalls covered:
//   1. Mismatched new/delete vs new[]/delete[]
//   2. Double deletion
//   3. Forgetting to delete (memory leak)
//   4. Reassigning a pointer without freeing old memory
//   5. Multiple pointers and unclear ownership
//   6. Deleting in the wrong order (2D arrays)
// ============================================================================

#include <iostream>

int main()
{
    std::cout << "=== Common Dynamic Allocation Pitfalls ===\n";

    // =================================================================
    // Pitfall 1: Mismatched new / delete
    // =================================================================
    std::cout << "\n--- Pitfall 1: Mismatched new/delete ---\n";

    // WRONG (undefined behavior):
    //   int* arr = new int[10];
    //   delete arr;          // Should be delete[] arr!
    //
    //   int* single = new int{ 5 };
    //   delete[] single;     // Should be delete single!

    // CORRECT:
    int *arr{new int[10]{}};
    delete[] arr; // new[] → delete[]
    arr = nullptr;

    int *single{new int{5}};
    delete single; // new → delete
    single = nullptr;

    std::cout << "Rule: new pairs with delete, new[] pairs with delete[].\n";

    // =================================================================
    // Pitfall 2: Double deletion
    // =================================================================
    std::cout << "\n--- Pitfall 2: Double deletion ---\n";

    // WRONG (undefined behavior):
    //   int* p = new int{ 7 };
    //   delete p;
    //   delete p;    // CRASH or UB - deleting already-freed memory!

    // CORRECT: set to nullptr after delete
    int *p{new int{7}};
    std::cout << "Allocated: " << *p << '\n';
    delete p;
    p = nullptr; // now safe

    delete p; // safe: deleting nullptr is a no-op
    std::cout << "Double-delete avoided by setting ptr to nullptr.\n";

    // =================================================================
    // Pitfall 3: Forgetting to delete (memory leak)
    // =================================================================
    std::cout << "\n--- Pitfall 3: Forgetting to delete ---\n";

    // WRONG:
    //   void foo() {
    //       int* leak = new int{ 42 };
    //       // function returns without deleting - LEAK!
    //   }

    // CORRECT:
    int *data{new int{42}};
    std::cout << "Allocated: " << *data << '\n';
    delete data; // always free before losing access
    data = nullptr;
    std::cout << "Freed properly - no leak.\n";

    // =================================================================
    // Pitfall 4: Reassigning pointer without freeing old memory
    // =================================================================
    std::cout << "\n--- Pitfall 4: Reassigning without freeing ---\n";

    // WRONG:
    //   int* ptr = new int{ 10 };
    //   ptr = new int{ 20 };    // 10 is now LEAKED

    // CORRECT:
    int *ptr{new int{10}};
    std::cout << "First:  " << *ptr << '\n';
    delete ptr;        // free old memory first
    ptr = new int{20}; // then reassign
    std::cout << "Second: " << *ptr << '\n';
    delete ptr;
    ptr = nullptr;
    std::cout << "Both allocations freed.\n";

    // =================================================================
    // Pitfall 5: Multiple pointers - unclear ownership
    // =================================================================
    std::cout << "\n--- Pitfall 5: Multiple pointers, unclear ownership ---\n";

    // WRONG:
    //   int* a = new int{ 5 };
    //   int* b = a;         // both point to same memory
    //   delete a;           // memory freed
    //   *b = 10;            // UB! b is now dangling
    //   delete b;           // UB! double-delete

    // CORRECT: establish ONE owner
    int *owner{new int{5}};
    const int *reader{owner}; // const → reader doesn't own, doesn't delete
    std::cout << "Owner:  " << *owner << '\n';
    std::cout << "Reader: " << *reader << '\n';

    delete owner; // only owner deletes
    owner = nullptr;
    reader = nullptr; // reader must also be invalidated
    std::cout << "Single owner deleted - reader also set to nullptr.\n";

    // =================================================================
    // Pitfall 6: Wrong deallocation order for 2D arrays
    // =================================================================
    std::cout << "\n--- Pitfall 6: Wrong deallocation order (2D array) ---\n";

    constexpr int rows{2};
    constexpr int cols{3};

    int **matrix{new int *[rows]};
    for (int r{0}; r < rows; ++r)
        matrix[r] = new int[cols]{r * 10, r * 10 + 1, r * 10 + 2};

    // Print
    for (int r{0}; r < rows; ++r)
    {
        std::cout << "  Row " << r << ": ";
        for (int c{0}; c < cols; ++c)
            std::cout << matrix[r][c] << ' ';
        std::cout << '\n';
    }

    // WRONG order:
    //   delete[] matrix;        // frees pointer array FIRST - rows leak!
    //   for (...) delete[] matrix[r];  // accessing freed memory - UB

    // CORRECT: delete sub-arrays (rows) first, then the pointer array
    for (int r{0}; r < rows; ++r)
        delete[] matrix[r]; // free each row
    delete[] matrix;        // then free the pointer array
    matrix = nullptr;
    std::cout << "2D array freed in correct order.\n";

    std::cout << "\nAll pitfalls demonstrated and correctly handled.\n";
    return 0;
}
