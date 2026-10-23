// Chapter 12 - Project 08: Pointers and Const
// ==============================================
// Const can be applied in two positions relative to the *.
//
//   const int* ptr     →  pointer to const   - value can't be changed through ptr, ptr can be reseated
//   int* const ptr     →  const pointer      - ptr can't be reseated, but value CAN be changed
//   const int* const   →  const pointer to const - neither can change
//
// Memory trick:  const BEFORE * → protects the value
//                const AFTER  * → protects the pointer

#include <iostream>

int main()
{
    int x{10};
    int y{20};

    // ==========================================================
    // 1. Pointer to const  (const int* ptr  OR  int const* ptr)
    // ==========================================================
    const int *ptrToConst{&x};

    std::cout << "--- Pointer to const ---\n";
    std::cout << "*ptrToConst = " << *ptrToConst << '\n'; // 10

    // *ptrToConst = 99;   // ERROR: can't modify value through pointer to const

    ptrToConst = &y;                                                    // OK: can reseat the pointer
    std::cout << "After reseat: *ptrToConst = " << *ptrToConst << '\n'; // 20

    // A pointer to const CAN point to a non-const variable
    // (it just promises not to modify through the pointer)
    x = 15; // direct modification is still fine
    ptrToConst = &x;
    std::cout << "x modified directly: *ptrToConst = " << *ptrToConst << '\n'; // 15

    // ==========================================================
    // 2. Const pointer  (int* const ptr)
    // ==========================================================
    int *const constPtr{&x};

    std::cout << "\n--- Const pointer ---\n";
    std::cout << "*constPtr = " << *constPtr << '\n'; // 15

    *constPtr = 50;                                         // OK: can modify the value
    std::cout << "After *constPtr = 50: x = " << x << '\n'; // 50

    // constPtr = &y;       // ERROR: can't reseat a const pointer

    // ==========================================================
    // 3. Const pointer to const  (const int* const ptr)
    // ==========================================================
    const int *const constPtrToConst{&x};

    std::cout << "\n--- Const pointer to const ---\n";
    std::cout << "*constPtrToConst = " << *constPtrToConst << '\n'; // 50

    // *constPtrToConst = 1;    // ERROR: can't modify value
    // constPtrToConst = &y;    // ERROR: can't reseat pointer

    // ==========================================================
    // 4. Top-level vs low-level const
    // ==========================================================
    // Top-level const: const on the pointer object itself  → int* const
    //   (Dropped by auto / value semantics)
    // Low-level const: const on what's pointed to          → const int*
    //   (NOT dropped - must be preserved)
    std::cout << "\n--- Summary table ---\n";
    std::cout << "const int*        → pointer to const   (value protected)\n";
    std::cout << "int* const        → const pointer      (pointer protected)\n";
    std::cout << "const int* const  → both protected\n";

    return 0;
}
