// Chapter 7 - Project 02: User-Defined Namespaces
// =================================================
// Namespaces prevent naming collisions by grouping identifiers.
// Use the scope resolution operator (::) to access members.
// Namespaces can be nested, aliased, and split across blocks/files.

#include <iostream>

// -------------------------------------------------
// 1. Basic namespace - avoids name collisions
// -------------------------------------------------
namespace Math
{
    int add(int a, int b)
    {
        return a + b;
    }

    int subtract(int a, int b)
    {
        return a - b;
    }
}

namespace Physics
{
    // A different 'add' function - no collision with Math::add
    double add(double force1, double force2)
    {
        return force1 + force2;
    }
}

// -------------------------------------------------
// 2. Nested namespaces
// -------------------------------------------------
namespace Company
{
    namespace Department
    {
        void greet()
        {
            std::cout << "Hello from Company::Department!\n";
        }
    }
}

// C++17 nested namespace shorthand (equivalent to the above pattern)
namespace Game::Engine
{
    void init()
    {
        std::cout << "Game::Engine initialized.\n";
    }
}

// -------------------------------------------------
// 3. Namespace aliases - shorter names for deeply nested namespaces
// -------------------------------------------------
namespace GE = Game::Engine;

// -------------------------------------------------
// 4. Namespaces can be split across multiple blocks
//    (the compiler merges them)
// -------------------------------------------------
namespace Utils
{
    int square(int x) { return x * x; }
}

namespace Utils // Same namespace - adds to the one above
{
    int cube(int x) { return x * x * x; }
}

// -------------------------------------------------
// 5. The global namespace (no prefix)
// -------------------------------------------------
void globalFunction()
{
    std::cout << "I live in the global namespace.\n";
}

int main()
{
    // Accessing namespace members with :: (scope resolution operator)
    std::cout << "Math::add(3, 4)      = " << Math::add(3, 4) << '\n';
    std::cout << "Math::subtract(10,3) = " << Math::subtract(10, 3) << '\n';
    std::cout << "Physics::add(1.5,2.5)= " << Physics::add(1.5, 2.5) << '\n';

    // Nested namespaces
    Company::Department::greet();
    Game::Engine::init();

    // Using the alias
    GE::init(); // Same as Game::Engine::init()

    // Split namespace - both functions are in Utils
    std::cout << "\nUtils::square(5) = " << Utils::square(5) << '\n';
    std::cout << "Utils::cube(3)   = " << Utils::cube(3) << '\n';

    // Global namespace - can be accessed with :: prefix (or without)
    ::globalFunction(); // Explicit global namespace access
    globalFunction();   // Also works (implicit)

    return 0;
}
