// Chapter 13 - Project 04: Overloading I/O Operators for Enums
// Demonstrates: operator<< for printing enums with std::cout,
//               operator>> for reading enums from std::cin,
//               and stream chaining.

#include <iostream>
#include <string>
#include <string_view>

enum Pet
{
    cat,
    dog,
    fish,
    bird,
};

// ============================================================================
// 1. Overload operator<< so std::cout knows how to print Pet
// ============================================================================
// The first parameter is std::ostream& (left side of <<).
// The second parameter is our enum type.
// Returns std::ostream& to allow chaining (e.g., std::cout << p1 << p2).
std::ostream &operator<<(std::ostream &out, Pet pet)
{
    switch (pet)
    {
    case cat:
        out << "cat";
        break;
    case dog:
        out << "dog";
        break;
    case fish:
        out << "fish";
        break;
    case bird:
        out << "bird";
        break;
    default:
        out << "unknown";
        break;
    }
    return out; // return stream to enable chaining
}

// ============================================================================
// 2. Overload operator>> so std::cin can read a Pet
// ============================================================================
// Reads a string from the user and maps it to the corresponding enumerator.
// If the input is invalid, sets the stream's failbit.
std::istream &operator>>(std::istream &in, Pet &pet)
{
    std::string input{};
    in >> input;

    if (input == "cat")
        pet = cat;
    else if (input == "dog")
        pet = dog;
    else if (input == "fish")
        pet = fish;
    else if (input == "bird")
        pet = bird;
    else
        in.setstate(std::ios_base::failbit); // signal invalid input

    return in;
}

int main()
{
    // --- Using operator<< ---
    std::cout << "=== operator<< for Pet ===\n";
    Pet p1{cat};
    Pet p2{fish};

    // Now we can print Pet values directly - no helper function needed.
    std::cout << "p1 is " << p1 << '\n'; // "p1 is cat"
    std::cout << "p2 is " << p2 << '\n'; // "p2 is fish"

    // Chaining works because we return std::ostream&:
    std::cout << "Pets: " << p1 << ", " << p2 << '\n';

    // --- Using operator>> ---
    std::cout << "\n=== operator>> for Pet ===\n";
    std::cout << "Enter a pet (cat, dog, fish, bird): ";

    Pet userPet{};
    if (std::cin >> userPet)
        std::cout << "You chose: " << userPet << '\n';
    else
        std::cout << "Invalid pet entered.\n";

    return 0;
}
