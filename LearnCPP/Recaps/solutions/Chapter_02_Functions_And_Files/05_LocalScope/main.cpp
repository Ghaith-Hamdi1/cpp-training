// Chapter 2 - Project 05: Local Scope
// Concept: Local variables, scope vs. lifetime, functional separation
//
// • Local variables (including parameters) are created when their
//   definition is reached and destroyed at the end of their enclosing
//   block (the closing brace '}').
// • Scope (compile-time) - where a name is visible / accessible.
// • Lifetime (runtime) - how long the object actually exists in memory.
// • Variables in different functions are completely independent, even if
//   they share the same name.
// • Best practice: define variables as close to their first use as
//   reasonable.
// -----------------------------------------------------------------------

#include <iostream>

void functionA()
{
    // 'x' is local to functionA - it has nothing to do with any 'x' elsewhere.
    int x{10};
    std::cout << "[functionA] x = " << x << '\n';
    // 'x' is destroyed here when functionA returns.
}

void functionB()
{
    // This 'x' is a completely independent variable from functionA's 'x'.
    int x{20};
    std::cout << "[functionB] x = " << x << '\n';
}

// Parameters are local variables too - created on function entry,
// destroyed on function exit.
void showParameter(int value)
{
    std::cout << "[showParameter] value = " << value << '\n';
    // 'value' is destroyed when this function returns.
}

// Demonstrates nested blocks and their own scope.
void nestedScopes()
{
    int outer{1};
    std::cout << "[nestedScopes] outer = " << outer << '\n';

    { // Inner block - its own scope
        int inner{2};
        std::cout << "[nestedScopes]   inner = " << inner << '\n';
        std::cout << "[nestedScopes]   outer = " << outer << " (still accessible)\n";
        // Both 'outer' and 'inner' are accessible here.
    } // 'inner' is destroyed here

    // std::cout << inner;  // ERROR: 'inner' is out of scope here
    std::cout << "[nestedScopes] outer = " << outer << " (still alive)\n";
}

// Demonstrates that modifying a local variable does not affect anything
// outside the function (functional separation).
void modifyLocal()
{
    int count{0};
    count = 100;
    std::cout << "[modifyLocal] count = " << count << '\n';
    // 'count' is destroyed here - no effect on the outside world.
}

int main()
{
    std::cout << "=== Project 05: Local Scope ===\n\n";

    // 1. Same-named variables in different functions are independent
    std::cout << "--- Independent variables across functions ---\n";
    functionA(); // x = 10
    functionB(); // x = 20 (completely separate!)

    // 2. Parameters are local variables
    std::cout << "\n--- Parameters are local ---\n";
    showParameter(55);
    // 'value' no longer exists here

    // 3. Nested scopes
    std::cout << "\n--- Nested block scopes ---\n";
    nestedScopes();

    // 4. Functional separation
    std::cout << "\n--- Functional separation ---\n";
    modifyLocal();

    // 5. Best practice: define close to first use
    std::cout << "\n--- Define close to first use ---\n";
    // BAD:  int result;  (defined far from use)
    //       ... lots of code ...
    //       result = someComputation();

    // GOOD: define where you need it
    int result{7 * 6};
    std::cout << "result = " << result << '\n';

    return 0;
}
