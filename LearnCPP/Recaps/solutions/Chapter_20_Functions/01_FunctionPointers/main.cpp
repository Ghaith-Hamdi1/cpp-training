// Chapter 20 - Project 01: Function Pointers
// =============================================
// Demonstrates: declaring, assigning, and calling through function pointers.
//
// Key points:
//   - A function pointer stores the address of a function.
//   - The pointer's type must exactly match the target function's signature.
//   - Writing 'foo' (without parentheses) yields the function's address, not its return value.
//   - You can call through a pointer with explicit dereference (*fcnPtr)(args)
//     or via implicit dereference fcnPtr(args).

#include <iostream>

// Two simple functions with the same signature: int(int, int)
int add(int a, int b)
{
    return a + b;
}

int multiply(int a, int b)
{
    return a * b;
}

int main()
{
    // -------------------------------------------------------
    // 1. Declaring a function pointer and assigning it
    // -------------------------------------------------------
    // Syntax: returnType (*pointerName)(paramTypes...)
    int (*operation)(int, int){&add}; // points to 'add'

    // Calling through the pointer (implicit dereference - preferred style)
    std::cout << "add(3, 4) via pointer:      " << operation(3, 4) << '\n';

    // Calling through the pointer (explicit dereference - also valid)
    std::cout << "add(3, 4) explicit deref:   " << (*operation)(3, 4) << '\n';

    // -------------------------------------------------------
    // 2. Reassigning the pointer to a different function
    // -------------------------------------------------------
    operation = &multiply; // now points to 'multiply'
    std::cout << "multiply(3, 4) via pointer: " << operation(3, 4) << '\n';

    // -------------------------------------------------------
    // 3. Null function pointers
    // -------------------------------------------------------
    int (*nullPtr)(int, int){nullptr};

    // Always check before calling - dereferencing null is undefined behavior
    if (nullPtr)
        std::cout << "nullPtr result: " << nullPtr(1, 2) << '\n';
    else
        std::cout << "nullPtr is null - cannot call\n";

    // -------------------------------------------------------
    // 4. Common pitfall: forgetting parentheses
    // -------------------------------------------------------
    // 'add' without () gives you a function pointer (the address), NOT the return value.
    // The compiler may warn about an unused value here.
    // Example (do NOT do this when you want the result):
    //   int result = add;   // ERROR: tries to assign a function pointer to an int

    std::cout << "\nAddress of add():      " << reinterpret_cast<void *>(&add) << '\n';
    std::cout << "Address of multiply(): " << reinterpret_cast<void *>(&multiply) << '\n';

    return 0;
}
