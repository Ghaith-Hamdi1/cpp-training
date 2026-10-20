// Chapter 12 - Project 09: Pass by Address
// ===========================================
// Pass by address means passing a pointer to a function.
// The function can dereference the pointer to access/modify the original object.
//
// Key points:
//   • Always null-check pointer parameters
//   • Prefer pass by const& over pass by address unless pointer features are needed
//   • Pointers are passed BY VALUE - reassigning the pointer inside the function
//     does NOT affect the caller's pointer
//   • To modify the caller's pointer, pass a reference to a pointer (int*&)
//   • nullptr can serve as an "optional argument" sentinel

#include <iostream>
#include <string>

// Basic pass by address - modifies the original through the pointer
void doubleValue(int *ptr)
{
    if (ptr) // always null-check!
        *ptr *= 2;
}

// Pass by address for optional parameter (nullptr = "not provided")
void greet(const std::string &name, const std::string *title = nullptr)
{
    if (title)
        std::cout << "Hello, " << *title << ' ' << name << "!\n";
    else
        std::cout << "Hello, " << name << "!\n";
}

// Pointer is passed by value - this does NOT affect the caller's pointer
void tryReseat(int *ptr)
{
    [[maybe_unused]] static int local{999};
    ptr = &local;                                               // only changes the local copy of the pointer
    std::cout << "  Inside tryReseat: *ptr = " << *ptr << '\n'; // 999
}

// To actually reseat the caller's pointer, pass a reference to a pointer
void actualReseat(int *&ptr)
{
    static int local{777};
    ptr = &local; // modifies the caller's pointer!
}

int main()
{
    // ----- Basic pass by address -----
    int x{5};
    std::cout << "Before doubleValue: x = " << x << '\n';
    doubleValue(&x);
    std::cout << "After  doubleValue: x = " << x << '\n';

    // Passing null is safe because we null-check
    doubleValue(nullptr); // does nothing

    // ----- Optional parameter via nullptr -----
    std::cout << '\n';
    greet("Alice");
    std::string title{"Dr."};
    greet("Smith", &title);

    // ----- Pointer passed by value (reseat doesn't propagate) -----
    std::cout << '\n';
    int *ptr{&x};
    std::cout << "Before tryReseat: *ptr = " << *ptr << '\n';
    tryReseat(ptr);
    std::cout << "After  tryReseat: *ptr = " << *ptr << '\n'; // still points to x!

    // ----- Reference to pointer (reseat DOES propagate) -----
    std::cout << "\nBefore actualReseat: *ptr = " << *ptr << '\n';
    actualReseat(ptr);
    std::cout << "After  actualReseat: *ptr = " << *ptr << '\n'; // now 777

    return 0;
}
