// Chapter 13 - Project 07: Struct Aggregate Initialization
// Demonstrates: braced initializer lists, memberwise initialization order,
//               missing initializers, value-initialization, and copy-list init.

#include <iostream>
#include <string>

// ============================================================================
// A struct is an 'aggregate' - it can be initialized with a braced list.
// Members are initialized in the order they are DECLARED (not named).
// ============================================================================
struct Fraction
{
    int numerator{};    // default member initializer: 0
    int denominator{1}; // default member initializer: 1
};

struct Employee
{
    int id{};
    std::string name{};
    double wage{};
};

void printFraction(const Fraction &f)
{
    std::cout << f.numerator << '/' << f.denominator << '\n';
}

int main()
{
    // ========================================================================
    // 1. Full aggregate initialization (all members provided)
    // ========================================================================
    std::cout << "=== Full Aggregate Initialization ===\n";
    Fraction f1{3, 4}; // numerator=3, denominator=4
    printFraction(f1); // 3/4

    // ========================================================================
    // 2. Partial initialization - missing members use defaults
    // ========================================================================
    std::cout << "\n=== Partial Initialization ===\n";
    Fraction f2{5};    // numerator=5, denominator uses default (1)
    printFraction(f2); // 5/1

    // ========================================================================
    // 3. Empty braces - value initialization (all defaults used)
    // ========================================================================
    std::cout << "\n=== Value Initialization (Empty Braces) ===\n";
    Fraction f3{};     // numerator=0, denominator=1 (from defaults)
    printFraction(f3); // 0/1

    // ========================================================================
    // 4. Best practice: always use braces, even if empty
    // ========================================================================
    // Fraction f4;      // default initialization - members WITHOUT default
    //                    // member initializers would be UNINITIALIZED!
    // Fraction f4{};    // value initialization - safe, all members initialized.

    // ========================================================================
    // 5. Copy-list initialization (using = with braces)
    // ========================================================================
    std::cout << "\n=== Copy-List Initialization ===\n";
    Fraction f5 = {7, 8}; // equivalent to Fraction f5{ 7, 8 };
    printFraction(f5);    // 7/8

    // ========================================================================
    // 6. Aggregate init with a more complex struct
    // ========================================================================
    std::cout << "\n=== Employee Aggregate Init ===\n";
    Employee e1{42, "Alice", 75000.0};
    std::cout << e1.id << ": " << e1.name << " ($" << e1.wage << ")\n";

    // Partial - wage omitted, gets value-initialized to 0.0
    Employee e2{43, "Bob"};
    std::cout << e2.id << ": " << e2.name << " ($" << e2.wage << ")\n";

    // ========================================================================
    // 7. Assignment with braces (re-initialization)
    // ========================================================================
    std::cout << "\n=== Re-assignment with Braces ===\n";
    f1 = {9, 10};      // assigns a new Fraction to f1
    printFraction(f1); // 9/10

    return 0;
}
