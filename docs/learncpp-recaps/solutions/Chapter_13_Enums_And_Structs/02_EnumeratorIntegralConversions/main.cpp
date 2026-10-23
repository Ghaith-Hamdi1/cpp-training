// Chapter 13 - Project 02: Unscoped Enumerator Integral Conversions
// Demonstrates: implicit conversion to int, no implicit int-to-enum,
//               static_cast, and making value 0 a sensible default.

#include <iostream>

// Best practice: make the enumerator with value 0 a sensible default
// or add an "unknown" / "invalid" sentinel.
enum Animal
{
    unknown = 0, // sensible default for value 0
    cat = 1,
    dog = 2,
    pig = 3,
    whale = 4,
};

enum SortOrder
{
    ascending,  // 0
    descending, // 1
};

int main()
{
    // ========================================================================
    // 1. Implicit conversion: enum -> int (allowed for unscoped enums)
    // ========================================================================
    std::cout << "=== Enum to Int (Implicit) ===\n";

    Animal a{dog};
    std::cout << "dog as int: " << a << '\n'; // prints 2

    // You can use enumerators in arithmetic/comparison with ints:
    if (a == 2)
        std::cout << "a == 2 is true (dog's underlying value)\n";

    // ========================================================================
    // 2. Int -> Enum: NOT implicit - use static_cast
    // ========================================================================
    std::cout << "\n=== Int to Enum (static_cast) ===\n";

    // Animal b{ 3 };           // ERROR in C++17+: cannot narrow int to enum
    // Animal b = 3;            // ERROR: no implicit conversion
    Animal b{static_cast<Animal>(3)};                      // OK: explicitly cast int to Animal
    std::cout << "static_cast<Animal>(3) = " << b << '\n'; // 3 (pig)

    // ========================================================================
    // 3. Using enumerators in switch statements
    // ========================================================================
    std::cout << "\n=== Switch on Enum ===\n";
    Animal pet{cat};
    switch (pet)
    {
    case cat:
        std::cout << "Meow!\n";
        break;
    case dog:
        std::cout << "Woof!\n";
        break;
    case pig:
        std::cout << "Oink!\n";
        break;
    case whale:
        std::cout << "Splash!\n";
        break;
    case unknown:
        std::cout << "Unknown animal\n";
        break;
    }

    // ========================================================================
    // 4. Default-initialized enum gets value 0
    // ========================================================================
    std::cout << "\n=== Value-Initialized Enum ===\n";
    Animal defaultAnimal{};                                         // value-initialized to 0 -> unknown
    std::cout << "Default animal value: " << defaultAnimal << '\n'; // 0

    // ========================================================================
    // 5. Storing enum in an int variable
    // ========================================================================
    std::cout << "\n=== Storing Enum in int ===\n";
    int sortVal{ascending};                               // implicit conversion
    std::cout << "ascending as int: " << sortVal << '\n'; // 0

    return 0;
}
