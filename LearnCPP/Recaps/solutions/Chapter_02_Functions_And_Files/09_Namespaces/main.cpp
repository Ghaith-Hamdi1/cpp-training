// Chapter 2 - Project 09: Namespaces and Naming Collisions
// Concept: Why namespaces exist, std::, scope resolution operator (::)
//
// A naming collision occurs when two identical identifiers are introduced
// in the same scope - the compiler (or linker) cannot tell them apart.
//
// Namespaces solve this by creating named scope regions that isolate
// identifiers.  Each name inside a namespace is qualified by the
// namespace name and the scope resolution operator (::).
//
// The C++ standard library lives in namespace `std`.
//
// Best practice: ALWAYS use the std:: prefix.
// NEVER use `using namespace std;` - it defeats the purpose of namespaces
// and can cause hard-to-diagnose collisions as your program or the
// standard library grows.
// -----------------------------------------------------------------------

#include <iostream>

// -----------------------------------------------------------------------
// User-defined namespaces to prevent naming collisions.
// Both namespaces contain a function named "getValue", but they are
// completely separate because they live in different namespaces.
// -----------------------------------------------------------------------

namespace moduleA
{
    int getValue()
    {
        return 10;
    }
}

namespace moduleB
{
    int getValue()
    {
        return 20;
    }
}

// A function in the global namespace (no namespace qualifier needed).
void greet()
{
    std::cout << "Hello from the global namespace!\n";
}

// -----------------------------------------------------------------------
// Demonstrating the scope resolution operator (::)
// -----------------------------------------------------------------------

namespace physics
{
    double gravity()
    {
        return 9.81; // m/s²
    }
}

namespace mars
{
    double gravity()
    {
        return 3.72; // m/s²
    }
}

int main()
{
    std::cout << "=== Project 09: Namespaces ===\n\n";

    // 1. std:: prefix - accessing the standard library
    std::cout << "--- Using std:: prefix ---\n";
    std::cout << "std::cout lives in namespace std.\n";
    // Without std::, the compiler wouldn't find 'cout'.

    // 2. Without namespaces, two functions named getValue would collide.
    //    With namespaces, we disambiguate using the :: operator.
    std::cout << "\n--- User-defined namespaces ---\n";
    std::cout << "moduleA::getValue() = " << moduleA::getValue() << '\n';
    std::cout << "moduleB::getValue() = " << moduleB::getValue() << '\n';
    // Just calling getValue() would be ambiguous (compile error).

    // 3. Global namespace - no prefix needed
    std::cout << "\n--- Global namespace ---\n";
    greet();

    // 4. Practical example: same function name, different contexts
    std::cout << "\n--- Namespace disambiguation ---\n";
    std::cout << "Earth gravity: " << physics::gravity() << " m/s^2\n";
    std::cout << "Mars gravity:  " << mars::gravity() << " m/s^2\n";

    // 5. Why NOT to use `using namespace std;`
    //    using namespace std;  // DON'T DO THIS!
    //    It dumps ALL of std's names into the global scope, risking
    //    collisions with your own identifiers (e.g., count, distance,
    //    size, min, max, ...).

    return 0;
}
