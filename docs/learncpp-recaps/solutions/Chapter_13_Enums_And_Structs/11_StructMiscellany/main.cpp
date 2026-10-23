// Chapter 13 - Project 11: Struct Miscellany
// Demonstrates: nested structs, struct ownership (std::string vs string_view),
//               padding/alignment, and member ordering for minimal size.

#include <cstdint> // fixed-width types
#include <iostream>
#include <string>

// ============================================================================
// 1. Nested structs (struct as a member of another struct)
// ============================================================================
struct Address
{
    std::string street{};
    std::string city{};
    std::string state{};
    int zip{};
};

struct Person
{
    std::string name{};
    int age{};
    Address address{}; // struct inside a struct
};

void printPerson(const Person &p)
{
    std::cout << p.name << " (age " << p.age << ")\n"
              << "  " << p.address.street << '\n'
              << "  " << p.address.city << ", " << p.address.state
              << ' ' << p.address.zip << '\n';
}

// ============================================================================
// 2. Ownership: use std::string, NOT std::string_view, for data members
// ============================================================================
// GOOD - owns its data:
struct SafeRecord
{
    int id{};
    std::string name{}; // std::string owns the characters
};

// BAD - does NOT own its data (dangling risk!):
// struct UnsafeRecord
// {
//     int              id{};
//     std::string_view name{}; // viewer only - source might be destroyed!
// };
// If the viewed string is destroyed, name becomes a dangling view.

// ============================================================================
// 3. Struct padding and alignment
// ============================================================================
// The compiler may insert padding bytes between members so each member
// is aligned to its natural alignment boundary.

struct Padded // poor ordering
{
    char a{}; // 1 byte  + 3 bytes padding (to align int)
    int b{};  // 4 bytes
    char c{}; // 1 byte  + 3 bytes padding (to align struct to 4)
};
// Total: likely 12 bytes (not 6!)

struct Packed // better ordering - largest to smallest
{
    int b{};  // 4 bytes
    char a{}; // 1 byte
    char c{}; // 1 byte  + 2 bytes padding (to align struct to 4)
};
// Total: likely 8 bytes - saved 4 bytes just by reordering!

// ============================================================================
// 4. Best practice: add new members at the BOTTOM
// ============================================================================
// Adding a member in the middle shifts all subsequent aggregate initializer
// values, causing hard-to-find bugs.
struct Version1
{
    int x{};
    int y{};
    // int z{};  // If added between x and y, existing { 1, 2 } init breaks!
};

int main()
{
    // --- Nested struct initialization ---
    std::cout << "=== Nested Structs ===\n";
    Person alice{
        "Alice",
        30,
        {"123 Main St", "Springfield", "IL", 62704} // nested init list
    };
    printPerson(alice);

    // Designated initializers make nesting even clearer:
    Person bob{
        .name = "Bob",
        .age = 45,
        .address = {.street = "456 Oak Ave", .city = "Shelbyville", .state = "IL", .zip = 62565},
    };
    std::cout << '\n';
    printPerson(bob);

    // --- Padding demonstration ---
    std::cout << "\n=== Struct Padding ===\n";
    std::cout << "sizeof(Padded): " << sizeof(Padded) << " bytes"
              << " (char, int, char - poor order)\n";
    std::cout << "sizeof(Packed): " << sizeof(Packed) << " bytes"
              << " (int, char, char - optimal order)\n";
    std::cout << "Savings: " << (sizeof(Padded) - sizeof(Packed)) << " bytes\n";

    // Best practice: order members from largest to smallest to minimize padding.

    // --- Ownership reminder ---
    std::cout << "\n=== Ownership ===\n";
    SafeRecord record{1, "Owned string"};
    std::cout << record.id << ": " << record.name << '\n';
    // std::string member owns its data - always safe.

    return 0;
}
