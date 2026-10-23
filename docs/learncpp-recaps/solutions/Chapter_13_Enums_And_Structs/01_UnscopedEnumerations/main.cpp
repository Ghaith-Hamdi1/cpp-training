// Chapter 13 - Project 01: Unscoped Enumerations
// Demonstrates: enum definition, enumerator values, naming collisions,
//               and wrapping enums in namespaces to avoid them.

#include <iostream>

// ============================================================================
// 1. Basic unscoped enumeration
// ============================================================================
// Enumerators are implicitly assigned values starting from 0.
// red=0, green=1, blue=2
enum Color
{
    red,   // 0
    green, // 1
    blue,  // 2
};

// ============================================================================
// 2. Explicit enumerator values
// ============================================================================
// You can set values explicitly. Subsequent unset enumerators continue from
// the last explicit value + 1.
enum Priority
{
    low = 1,
    medium = 5,
    high = 10,
    urgent, // 11 (continues from 10)
};

// ============================================================================
// 3. Naming collision problem
// ============================================================================
// Two unscoped enums in the same scope CANNOT share enumerator names.
// Uncommenting this would cause a compile error because 'red' already exists:
//
// enum TrafficLight
// {
//     red,     // ERROR: 'red' already declared in this scope
//     yellow,
//     green,   // ERROR: 'green' already declared
// };

// ============================================================================
// 4. Solving naming collisions with namespaces
// ============================================================================
namespace Traffic
{
    enum Light
    {
        red,
        yellow,
        green,
    };
}

// ============================================================================
// 5. Each enum is a distinct type
// ============================================================================
enum Fruit
{
    apple,  // 0
    banana, // 1
    cherry, // 2
};

// You cannot assign a Fruit enumerator to a Color variable or compare them
// directly (though unscoped enums allow comparison via implicit int conversion
// - which is a pitfall, not a feature).

void printColor(Color c)
{
    switch (c)
    {
    case red:
        std::cout << "Red\n";
        break;
    case green:
        std::cout << "Green\n";
        break;
    case blue:
        std::cout << "Blue\n";
        break;
    }
}

int main()
{
    // --- Basic enum usage ---
    Color shirt{blue};
    std::cout << "=== Unscoped Enum Basics ===\n";
    std::cout << "shirt color: ";
    printColor(shirt);

    // --- Explicit values ---
    std::cout << "\n=== Explicit Enumerator Values ===\n";
    std::cout << "low    = " << low << '\n';
    std::cout << "medium = " << medium << '\n';
    std::cout << "high   = " << high << '\n';
    std::cout << "urgent = " << urgent << '\n'; // 11

    // --- Namespace-qualified enum ---
    std::cout << "\n=== Namespace-Qualified Enum ===\n";
    Traffic::Light signal{Traffic::red};
    // Traffic::Light enumerators don't collide with Color's red/green.
    std::cout << "Traffic light value: " << signal << '\n'; // prints 0

    // --- Distinct types ---
    std::cout << "\n=== Distinct Types ===\n";
    Fruit f{apple};
    // Color c2 = apple;  // ERROR: cannot convert Fruit to Color
    std::cout << "Fruit apple value: " << f << '\n'; // 0

    // WARNING: unscoped enums from different types CAN compare via implicit
    // int conversion - this compiles but is almost certainly a logic bug:
    // if (red == apple) { ... }  // Both are 0, so this is true!

    return 0;
}
