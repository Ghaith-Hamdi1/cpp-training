// Chapter 15 - Project 01: The Hidden "this" Pointer
// ====================================================
//
// Every non-static member function receives a hidden parameter called `this`.
// It is a const pointer to the object the function was called on.
//
// The compiler rewrites member accesses like `m_id` to `this->m_id`.
// You rarely need to use it explicitly, but there are three common cases:
//   1. Disambiguating when a parameter shadows a member name.
//   2. Passing the current object to an external function.
//   3. Returning *this for method chaining (see Project 02).
//
// Key rule: `this` is a POINTER, so use `this->member`, not `this.member`.

#include <iostream>
#include <string>

class Employee
{
private:
    std::string m_name{};
    int m_id{};

public:
    // Constructor - parameter `name` shadows m_name.
    // We use `this->` to disambiguate.
    Employee(const std::string &name, int id)
    {
        this->m_name = name; // `this->m_name` refers to the member
        this->m_id = id;     // `name` and `id` refer to the parameters
    }

    // Normally you don't need `this->` if names don't collide.
    void print() const
    {
        // The compiler implicitly rewrites m_name as this->m_name.
        std::cout << "Employee{ name=" << m_name
                  << ", id=" << m_id << " }\n";
    }

    // Passing `this` (address of current object) to an external function.
    void printAddress() const
    {
        std::cout << "Address of this Employee object: " << this << '\n';
    }

    // Reset the object to its default-constructed state using *this = {}.
    void reset()
    {
        *this = {}; // Assigns a default-constructed Employee to *this
        std::cout << "(Employee has been reset to defaults)\n";
    }
};

// A free function that takes an Employee by pointer - demonstrates passing `this`.
void describeEmployee(const Employee *emp)
{
    std::cout << "describeEmployee received object at address: " << emp << '\n';
    emp->print();
}

int main()
{
    Employee alice{"Alice", 101};
    Employee bob{"Bob", 202};

    // --- Basic usage ---
    alice.print(); // Internally: Employee::print(&alice)
    bob.print();   // Internally: Employee::print(&bob)

    // --- Show the hidden pointer value ---
    alice.printAddress();
    bob.printAddress();

    // --- Passing `this` to a free function ---
    // Inside printAddress, `this` points to alice.
    describeEmployee(&alice);

    // --- Resetting an object via *this = {} ---
    std::cout << "\nBefore reset:\n";
    alice.print();
    alice.reset();
    std::cout << "After reset:\n";
    alice.print();

    return 0;
}
