// Chapter 13 - Project 06: Introduction to Structs, Members, and Member Selection
// Demonstrates: struct definition, data members, member selection operator (.),
//               and why structs are useful for grouping related data.

#include <iostream>
#include <string>

// ============================================================================
// 1. Defining a struct
// ============================================================================
// A struct bundles multiple data members (member variables) into one type.
// Convention: struct names start with a capital letter.
// Don't forget the semicolon after the closing brace!
struct Employee
{
    int id{};
    std::string name{};
    double salary{};
}; // <-- semicolon is required!

// ============================================================================
// 2. Why structs? - Compare with loose variables
// ============================================================================
// Without structs, you'd need separate variables for each employee field,
// and every function accepting employee data would need many parameters.

// With a struct, one parameter is enough:
void printEmployee(const Employee &emp) // pass by const reference
{
    std::cout << "ID:     " << emp.id << '\n';
    std::cout << "Name:   " << emp.name << '\n';
    std::cout << "Salary: " << emp.salary << '\n';
}

int main()
{
    // --- Creating and using struct objects ---
    std::cout << "=== Struct Basics ===\n";

    Employee joe{}; // value-initialized (all members zeroed/empty)
    joe.id = 101;   // member selection with '.'
    joe.name = "Joe Smith";
    joe.salary = 55000.0;

    printEmployee(joe);

    // --- Another object of the same type ---
    std::cout << "\n=== Another Employee ===\n";
    Employee jane{};
    jane.id = 102;
    jane.name = "Jane Doe";
    jane.salary = 62000.0;

    printEmployee(jane);

    // --- Direct initialization with brace-init (aggregate initialization) ---
    std::cout << "\n=== Aggregate Initialization ===\n";
    Employee bob{103, "Bob Lee", 48000.0};
    printEmployee(bob);

    // --- Member access in expressions ---
    std::cout << "\n=== Member Access in Expressions ===\n";
    double raise{bob.salary * 0.10};
    bob.salary += raise;
    std::cout << "Bob after 10% raise: " << bob.salary << '\n';

    return 0;
}
