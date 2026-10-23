// Chapter 4 - Project 02: The Void Type
// =======================================
// Key concept: void means "no type." It is an incomplete type and cannot
// be instantiated. Its primary use is to indicate a function returns nothing.
//
// Pitfall: Using void in a parameter list - int f(void) - is deprecated
// in C++. Use int f() instead.

#include <iostream>

// void as a return type: this function returns nothing
void printGreeting()
{
    std::cout << "Hello from a void function!\n";
    // No return statement needed (though 'return;' is valid)
}

// void with no parameters: use empty parentheses, NOT void
// Good:  void doSomething()
// Bad:   void doSomething(void)   <-- deprecated in C++
void printSeparator()
{
    std::cout << "----------------------------\n";
}

// A function that uses early return (returns void early)
void printPositive(int x)
{
    if (x <= 0)
    {
        std::cout << x << " is not positive, skipping.\n";
        return; // Early return from a void function
    }

    std::cout << x << " is positive!\n";
}

int main()
{
    std::cout << "=== The Void Type ===\n\n";

    // Calling void functions
    printGreeting();
    printSeparator();

    // Demonstrating early return in void functions
    printPositive(5);
    printPositive(-3);
    printPositive(0);

    printSeparator();

    // You CANNOT create a void variable:
    // void v;           // Error: cannot declare variable of type void
    // void v{};         // Error: same reason - void is an incomplete type

    // You CANNOT use void as a function parameter type:
    // void func(void x); // Error: parameter cannot have void type

    std::cout << "\nvoid is useful only as a return type (and for void pointers,\n";
    std::cout << "which are covered in later chapters).\n";

    return 0;
}
