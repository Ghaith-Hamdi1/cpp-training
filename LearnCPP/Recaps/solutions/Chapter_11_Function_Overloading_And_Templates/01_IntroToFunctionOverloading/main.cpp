// Chapter 11 - Project 01: Introduction to Function Overloading
// ================================================================
// Function overloading lets you define multiple functions with the same name
// as long as they differ in their parameter types or count.
// The compiler uses "overload resolution" to pick the right one at each call site.

#include <iostream>
#include <string>

// --- Overload set for "add" ---
// Overload 1: two ints
int add(int x, int y)
{
    return x + y;
}

// Overload 2: three ints (different parameter count)
int add(int x, int y, int z)
{
    return x + y + z;
}

// Overload 3: two doubles (different parameter types)
double add(double x, double y)
{
    return x + y;
}

// --- Overload set for "print" ---
// Overload 1: print an int
void print(int value)
{
    std::cout << "int: " << value << '\n';
}

// Overload 2: print a double
void print(double value)
{
    std::cout << "double: " << value << '\n';
}

// Overload 3: print a string
void print(std::string_view value)
{
    std::cout << "string: " << value << '\n';
}

int main()
{
    // The compiler selects the correct overload based on arguments provided.

    std::cout << "=== add overloads ===\n";
    std::cout << "add(3, 4)       = " << add(3, 4) << '\n';     // calls add(int, int)
    std::cout << "add(1, 2, 3)    = " << add(1, 2, 3) << '\n';  // calls add(int, int, int)
    std::cout << "add(1.5, 2.5)   = " << add(1.5, 2.5) << '\n'; // calls add(double, double)

    std::cout << "\n=== print overloads ===\n";
    print(42);              // calls print(int)
    print(3.14);            // calls print(double)
    print("Hello, world!"); // calls print(std::string_view)

    // Key insight: the same function name is used for all variations.
    // The compiler figures out which version to call - callers don't need
    // to remember names like addInt, addDouble, addThreeInts, etc.

    return 0;
}
