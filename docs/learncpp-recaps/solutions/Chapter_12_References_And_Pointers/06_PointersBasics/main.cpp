// Chapter 12 - Project 06: Pointers Basics
// ==========================================
// A pointer is an object that holds a memory address.
//   • Declare with:  int* ptr;
//   • Address-of:    &variable   - gives the memory address of a variable
//   • Dereference:   *ptr        - accesses the value at the stored address
//   • Pointer type must match the pointed-to type
//   • Pointers can be reseated (pointed at different objects)
//   • Pointer size depends on architecture (4 bytes on 32-bit, 8 bytes on 64-bit)

#include <iostream>

int main()
{
    int x{5};
    int *ptr{&x}; // ptr holds the address of x

    std::cout << "x          = " << x << '\n';    // 5
    std::cout << "&x         = " << &x << '\n';   // address of x
    std::cout << "ptr        = " << ptr << '\n';  // same address
    std::cout << "*ptr       = " << *ptr << '\n'; // 5 - dereferencing

    // ----- Modify through the pointer -----
    *ptr = 10;
    std::cout << "\nAfter *ptr = 10:\n";
    std::cout << "  x    = " << x << '\n';    // 10
    std::cout << "  *ptr = " << *ptr << '\n'; // 10

    // ----- Reseating: make the pointer point to a different object -----
    int y{99};
    ptr = &y; // now ptr points to y
    std::cout << "\nAfter reseating ptr to &y:\n";
    std::cout << "  *ptr = " << *ptr << '\n'; // 99
    std::cout << "  x    = " << x << '\n';    // 10 (unchanged)

    // ----- Pointer size is architecture-dependent -----
    std::cout << "\nsizeof(int*)    = " << sizeof(int *) << " bytes\n";
    std::cout << "sizeof(double*) = " << sizeof(double *) << " bytes\n";
    std::cout << "sizeof(char*)   = " << sizeof(char *) << " bytes\n";
    // All pointer types have the same size on a given platform

    // ----- Multiple pointers can point to the same object -----
    int *ptr2{&x};
    int *ptr3{&x};
    std::cout << "\nptr2 and ptr3 both point to x:\n";
    std::cout << "  *ptr2 = " << *ptr2 << ", *ptr3 = " << *ptr3 << '\n';

    return 0;
}
