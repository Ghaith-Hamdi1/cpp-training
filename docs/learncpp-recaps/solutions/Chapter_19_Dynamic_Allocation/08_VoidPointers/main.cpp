// ============================================================================
// Chapter 19 - Project 08: Void Pointers
// ============================================================================
// A void pointer (void*) can point to any data type, but gives up type
// safety in exchange for generality.
//
// Key points:
//   - void* can hold the address of any type (int, double, struct, etc.)
//   - Cannot be dereferenced directly - must cast to the correct type first
//   - Pointer arithmetic on void* is not allowed
//   - delete on void* is undefined behavior - always cast back first
//   - Modern C++ prefers templates or function overloading over void*
// ============================================================================

#include <iostream>

// A function that accepts any pointer type via void*
// The caller must tell us the type via the 'type' parameter.
// This is the OLD C-style approach - prefer templates in modern C++.
void printValue(const void *ptr, char type)
{
    switch (type)
    {
    case 'i':
        std::cout << "int:    " << *static_cast<const int *>(ptr) << '\n';
        break;
    case 'd':
        std::cout << "double: " << *static_cast<const double *>(ptr) << '\n';
        break;
    case 'c':
        std::cout << "char:   " << *static_cast<const char *>(ptr) << '\n';
        break;
    default:
        std::cout << "Unknown type!\n";
        break;
    }
}

// Modern alternative: a function template (type-safe, no void* needed)
template <typename T>
void printValueModern(const T &value)
{
    std::cout << "value:  " << value << '\n';
}

int main()
{
    std::cout << "=== Void Pointer Demonstration ===\n\n";

    // -----------------------------------------------------------------
    // 1. void* can point to any type
    // -----------------------------------------------------------------
    int iVal{42};
    double dVal{3.14};
    char cVal{'A'};

    void *voidPtr{};

    // Point to an int
    voidPtr = &iVal;
    std::cout << "void* pointing to int:\n  ";
    printValue(voidPtr, 'i');

    // Point to a double (same pointer variable)
    voidPtr = &dVal;
    std::cout << "void* pointing to double:\n  ";
    printValue(voidPtr, 'd');

    // Point to a char
    voidPtr = &cVal;
    std::cout << "void* pointing to char:\n  ";
    printValue(voidPtr, 'c');

    // -----------------------------------------------------------------
    // 2. Casting void* to access the value
    // -----------------------------------------------------------------
    std::cout << "\n--- Casting void* ---\n";

    voidPtr = &iVal;

    // WRONG: cannot dereference void* directly
    //   std::cout << *voidPtr;   // ERROR: "void*" is not a pointer-to-object

    // RIGHT: cast to the correct type, then dereference
    int *intPtr{static_cast<int *>(voidPtr)};
    std::cout << "Casted back to int*:  " << *intPtr << '\n';

    // DANGER: casting to the wrong type is undefined behavior
    // double* wrongPtr{ static_cast<double*>(voidPtr) };
    // std::cout << *wrongPtr;   // UB - voidPtr actually points to an int!

    // -----------------------------------------------------------------
    // 3. Pointer arithmetic is NOT allowed on void*
    // -----------------------------------------------------------------
    // void* has no type information, so the compiler doesn't know the
    // element size. This won't compile:
    //   voidPtr++;           // ERROR
    //   voidPtr + 1;         // ERROR

    // You must cast first:
    int arr[]{10, 20, 30};
    voidPtr = arr;
    int *arrPtr{static_cast<int *>(voidPtr)};
    std::cout << "\nArray via casted void*: "
              << arrPtr[0] << ", " << arrPtr[1] << ", " << arrPtr[2] << '\n';

    // -----------------------------------------------------------------
    // 4. Modern alternative: templates (type-safe)
    // -----------------------------------------------------------------
    std::cout << "\n--- Modern template alternative ---\n";
    std::cout << "  ";
    printValueModern(42); // deduces int
    std::cout << "  ";
    printValueModern(3.14); // deduces double
    std::cout << "  ";
    printValueModern('A'); // deduces char

    // -----------------------------------------------------------------
    // 5. NEVER delete through a void pointer
    // -----------------------------------------------------------------
    // Deleting a void* is undefined behavior because the compiler
    // doesn't know which destructor to call or how much memory to free.
    //
    //   void* vp = new int{ 5 };
    //   delete vp;    // UB! Must cast back to int* first.
    //
    // Correct:
    //   delete static_cast<int*>(vp);

    std::cout << "\nVoid pointer demo complete. Prefer templates over void*!\n";
    return 0;
}
