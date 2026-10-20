// ============================================================================
// Chapter 19 - Project 03: Dangling Pointers
// ============================================================================
// A dangling pointer is a pointer that references memory that has already
// been freed. Dereferencing a dangling pointer is UNDEFINED BEHAVIOR.
//
// Key points:
//   - After 'delete', a pointer still holds the old address - it "dangles."
//   - Set pointers to nullptr after deleting to avoid accidental use.
//   - Multiple pointers to the same address make dangling easy.
//   - Always establish clear ownership of dynamically allocated memory.
// ============================================================================

#include <iostream>

int main()
{
    // -----------------------------------------------------------------
    // 1. Creating a dangling pointer (and fixing it)
    // -----------------------------------------------------------------
    int *ptr{new int{100}};
    std::cout << "Before delete: *ptr = " << *ptr << '\n';

    delete ptr;
    // ptr is now a dangling pointer - it still stores the old address
    // Dereferencing ptr here would be UNDEFINED BEHAVIOR:
    //   std::cout << *ptr;   // DON'T DO THIS!

    // Fix: set to nullptr after deleting
    ptr = nullptr;
    std::cout << "After delete:  ptr is " << (ptr ? "non-null" : "nullptr") << '\n';

    // Safe: we can check before dereferencing
    if (ptr)
        std::cout << *ptr << '\n'; // won't execute
    else
        std::cout << "ptr is nullptr - safe, not dangling.\n";

    // -----------------------------------------------------------------
    // 2. Multiple pointers to the same memory (aliasing danger)
    // -----------------------------------------------------------------
    int *original{new int{42}};
    int *alias{original}; // both point to the same int

    std::cout << "\nBefore delete: *original=" << *original
              << ", *alias=" << *alias << '\n';

    delete original;
    original = nullptr; // original is safe now

    // But 'alias' still holds the old address - it's dangling!
    // Accessing *alias here would be UNDEFINED BEHAVIOR.
    // This is the core problem with multiple pointers to the same memory.
    std::cout << "original is nullptr, but alias still dangles.\n";

    // To fix: also set alias to nullptr (or better - use clear ownership)
    alias = nullptr;

    // -----------------------------------------------------------------
    // 3. Best practice: clear ownership
    // -----------------------------------------------------------------
    // When only one pointer "owns" the memory, you always know who
    // is responsible for deleting it. Modern C++ uses std::unique_ptr
    // for automatic ownership (covered in a later chapter).

    int *owner{new int{7}};
    // Use owner throughout its lifetime...
    std::cout << "\nOwner value: " << *owner << '\n';

    // Only the owner deletes
    delete owner;
    owner = nullptr;

    // -----------------------------------------------------------------
    // 4. Dangling with dynamic arrays
    // -----------------------------------------------------------------
    int *arr{new int[3]{10, 20, 30}};
    std::cout << "\nArray before delete: "
              << arr[0] << ", " << arr[1] << ", " << arr[2] << '\n';

    delete[] arr;
    arr = nullptr;
    // arr[0] would be UB here - arr now dangles (but we set it to nullptr)
    std::cout << "Array pointer safely set to nullptr after delete[].\n";

    std::cout << "\nNo dangling pointers remain.\n";
    return 0;
}
