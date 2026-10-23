// Chapter 13 - Project 12: Member Selection with Pointers and References
// Demonstrates: '.' with objects/references, '->' with pointers,
//               and why (*ptr).member should be avoided in favor of ptr->member.

#include <iostream>
#include <string>

struct Employee
{
    int id{};
    std::string name{};
    double salary{};
};

// Takes a pointer - uses -> to access members
void giveRaise(Employee *emp, double percent)
{
    if (emp) // always check for null when using pointers
    {
        emp->salary += emp->salary * (percent / 100.0);
    }
}

// Takes a reference - uses . to access members
void printEmployee(const Employee &emp)
{
    std::cout << emp.id << ": " << emp.name << " ($" << emp.salary << ")\n";
}

int main()
{
    Employee alice{1, "Alice", 60000.0};

    // ========================================================================
    // 1. Member access with '.' (objects and references)
    // ========================================================================
    std::cout << "=== Member Access with '.' ===\n";
    std::cout << "Name: " << alice.name << '\n';

    Employee &ref{alice};                               // reference to alice
    std::cout << "Via reference: " << ref.name << '\n'; // uses '.'

    // ========================================================================
    // 2. Member access with '->' (pointers)
    // ========================================================================
    std::cout << "\n=== Member Access with '->' ===\n";
    Employee *ptr{&alice};

    // PREFERRED: use -> for pointer member access
    std::cout << "Via ptr->name:    " << ptr->name << '\n';
    std::cout << "Via ptr->salary:  " << ptr->salary << '\n';

    // AVOID: (*ptr).member is equivalent but clunky
    std::cout << "Via (*ptr).name:  " << (*ptr).name << '\n';

    // ========================================================================
    // 3. Modifying through a pointer
    // ========================================================================
    std::cout << "\n=== Modify Through Pointer ===\n";
    ptr->salary = 65000.0;
    std::cout << "New salary: " << ptr->salary << '\n';

    giveRaise(ptr, 10.0); // 10% raise via pointer
    std::cout << "After 10% raise: " << ptr->salary << '\n';

    // ========================================================================
    // 4. Common pitfall: using '.' with a pointer won't compile
    // ========================================================================
    // ptr.name;   // ERROR: '.' cannot be used with pointers
    // Use ptr->name instead.

    // ========================================================================
    // 5. Dynamic allocation example
    // ========================================================================
    std::cout << "\n=== Dynamic Allocation ===\n";
    Employee *dynEmp{new Employee{99, "Dynamic Dan", 40000.0}};
    std::cout << "Dynamic: ";
    printEmployee(*dynEmp); // dereference to pass by reference
    std::cout << "Via ->: " << dynEmp->name << '\n';

    delete dynEmp; // always free dynamically allocated memory
    dynEmp = nullptr;

    return 0;
}
