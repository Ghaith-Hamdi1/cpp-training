// Chapter 12 - Project 07: Null Pointers
// ========================================
// A null pointer points to nothing.
//   • Initialize with nullptr (C++11+)
//   • Dereferencing a null pointer is UNDEFINED BEHAVIOR (crash / corruption)
//   • Always check for null before dereferencing
//   • Use nullptr, NOT 0 or NULL (those can cause ambiguity with int overloads)
//   • Favor references over pointers when null is not needed

#include <iostream>

void printIfValid(int *ptr)
{
    if (ptr) // idiomatic null check - pointer converts to bool
    {
        std::cout << "Value: " << *ptr << '\n';
    }
    else
    {
        std::cout << "Pointer is null - nothing to print.\n";
    }
}

// Demonstrate why nullptr is better than 0 or NULL with overloads
void process(int value)
{
    std::cout << "process(int): " << value << '\n';
}

void process(int *ptr)
{
    if (ptr)
        std::cout << "process(int*): " << *ptr << '\n';
    else
        std::cout << "process(int*): null pointer\n";
}

int main()
{
    // ----- Value-initialize pointers to nullptr -----
    int *ptr{};         // value-initialized to nullptr
    int *ptr2{nullptr}; // explicit nullptr - preferred for clarity

    std::cout << "ptr  == nullptr? " << (ptr == nullptr ? "yes" : "no") << '\n';
    std::cout << "ptr2 == nullptr? " << (ptr2 == nullptr ? "yes" : "no") << '\n';

    // ----- Null check before dereferencing -----
    printIfValid(ptr); // "Pointer is null"

    int x{42};
    ptr = &x;
    printIfValid(ptr); // "Value: 42"

    // ----- Setting back to null -----
    ptr = nullptr;
    printIfValid(ptr); // "Pointer is null"

    // ----- Why nullptr over 0 or NULL -----
    // process(0);       // Calls process(int) - probably NOT what you wanted!
    process(nullptr); // Calls process(int*) - unambiguous
    int val{7};
    process(&val); // Calls process(int*)

    // ----- Conditional (ternary) with pointer -----
    int *maybe{&x};
    std::cout << "\nmaybe is " << (maybe ? "valid" : "null") << '\n';

    // DANGER: Dereferencing null is undefined behavior!
    // int* bad{ nullptr };
    // std::cout << *bad;   // UB: crash or worse

    return 0;
}
