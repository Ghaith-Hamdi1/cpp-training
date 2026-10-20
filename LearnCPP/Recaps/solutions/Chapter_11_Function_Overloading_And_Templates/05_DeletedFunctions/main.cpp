// Chapter 11 - Project 05: Deleting Functions (`= delete`)
// ================================================================
// Using `= delete` on a function overload explicitly FORBIDS calls that
// would match it.  A deleted function still participates in overload
// resolution - it means "I forbid this," not "this doesn't exist."
//
// Common use: prevent undesired implicit conversions.

#include <iostream>

// ---------------------------------------------------------------
// Example 1: Prevent implicit conversions to int
// ---------------------------------------------------------------
// We want printInt to ONLY accept int - not char, bool, double, etc.
void printInt(int x)
{
    std::cout << "printInt(int): " << x << '\n';
}

// Delete specific overloads to block implicit conversions:
void printInt(char) = delete;   // forbid char → int
void printInt(bool) = delete;   // forbid bool → int
void printInt(double) = delete; // forbid double → int

// Now printInt('A') is a compile error - the deleted overload is an
// exact match for char, and calling a deleted function is forbidden.

// ---------------------------------------------------------------
// Example 2: Delete all non-int overloads using a template
// ---------------------------------------------------------------
// This is a broader approach: accept int, forbid everything else.
void onlyInt(int x)
{
    std::cout << "onlyInt(int): " << x << '\n';
}

// A function template matches any type besides int.
// By deleting it, we prevent ALL other types at once.
template <typename T>
void onlyInt(T) = delete;

// ---------------------------------------------------------------
// Example 3: Deleted functions still participate in resolution
// ---------------------------------------------------------------
void process(int x)
{
    std::cout << "process(int): " << x << '\n';
}

void process(double) = delete; // forbidden, but still visible to resolution

// If we call process(3.14), the compiler sees process(double) as the
// best match → but it's deleted → compile error (not "no match found").

int main()
{
    std::cout << "=== Example 1: selective deletion ===\n";
    printInt(42); // OK - exact match for int

    // Uncommenting any of these would cause a compile error:
    // printInt('A');    // ERROR: printInt(char) is deleted
    // printInt(true);   // ERROR: printInt(bool) is deleted
    // printInt(3.14);   // ERROR: printInt(double) is deleted

    std::cout << "\n=== Example 2: template-based deletion ===\n";
    onlyInt(100); // OK - matches onlyInt(int)

    // Uncommenting any of these would cause a compile error:
    // onlyInt('B');     // ERROR: matches deleted template
    // onlyInt(3.14);    // ERROR: matches deleted template
    // onlyInt(true);    // ERROR: matches deleted template

    std::cout << "\n=== Example 3: deleted function still participates ===\n";
    process(7); // OK - matches process(int)

    // process(3.14);   // ERROR: process(double) is deleted
    // Note: the error message says "use of deleted function," NOT "no matching function."
    // The deleted overload IS found - it's just forbidden.

    return 0;
}
