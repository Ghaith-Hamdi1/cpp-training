// Chapter 7 - Project 11: Static Local Variables
// =================================================
// Adding 'static' to a local variable gives it STATIC DURATION:
//   - Created once (at first encounter), destroyed at program end
//   - Retains its value between function calls
//   - Still has BLOCK SCOPE - only accessible within its function
//
// Use the s_ prefix for static locals to signal their persistent nature.
//
// Best practice: Use static locals for values that must survive across calls
// (e.g., ID generators). Avoid using them to alter control flow.

#include <iostream>

// -------------------------------------------------
// 1. Classic use case: unique ID generator
// -------------------------------------------------
int generateID()
{
    static int s_nextID{0}; // Initialized ONCE, persists across calls
    return ++s_nextID;      // Returns 1, 2, 3, ... on successive calls
}

// -------------------------------------------------
// 2. Call counter - tracks how many times a function is called
// -------------------------------------------------
void trackCalls()
{
    static int s_callCount{0}; // Only initialized once
    ++s_callCount;
    std::cout << "  trackCalls() has been called " << s_callCount << " time(s)\n";
}

// -------------------------------------------------
// 3. Expensive initialization - compute once, reuse forever
// -------------------------------------------------
const int &getExpensiveValue()
{
    // Simulates a costly computation that only runs once
    static const int s_result{[]()
                              {
                                  std::cout << "  (Computing expensive value...)\n";
                                  int sum{0};
                                  for (int i{1}; i <= 100; ++i)
                                      sum += i;
                                  return sum;
                              }()}; // Immediately-invoked lambda, runs only on first call

    return s_result;
}

// -------------------------------------------------
// 4. PITFALL: Using static locals to change behavior between calls
// -------------------------------------------------
// This function behaves differently on the first call vs. subsequent calls.
// This is BAD because it makes the function unpredictable and non-reusable.
void badExample()
{
    static bool s_firstCall{true};

    if (s_firstCall)
    {
        std::cout << "  First time - doing initialization...\n";
        s_firstCall = false;
    }
    else
    {
        std::cout << "  Not first time - doing something else...\n";
    }
    // PROBLEM: Can't "reset" this function. Can't reuse it in another context.
    // If you need initialization, use a proper initialization pattern instead.
}

// -------------------------------------------------
// 5. Contrast with non-static local
// -------------------------------------------------
void noStatic()
{
    int counter{0}; // Re-initialized EVERY call (automatic duration)
    ++counter;
    std::cout << "  Non-static counter = " << counter << '\n'; // Always 1
}

int main()
{
    // 1. ID generator - static local persists across calls
    std::cout << "1. ID Generator (static local):\n";
    std::cout << "  ID: " << generateID() << '\n'; // 1
    std::cout << "  ID: " << generateID() << '\n'; // 2
    std::cout << "  ID: " << generateID() << '\n'; // 3

    // 2. Call counter
    std::cout << "\n2. Call Counter:\n";
    trackCalls(); // 1
    trackCalls(); // 2
    trackCalls(); // 3

    // 3. Expensive initialization - only computed once
    std::cout << "\n3. Expensive Initialization:\n";
    std::cout << "  Value: " << getExpensiveValue() << '\n'; // Computes
    std::cout << "  Value: " << getExpensiveValue() << '\n'; // Reuses (no recompute)
    std::cout << "  Value: " << getExpensiveValue() << '\n'; // Reuses

    // 4. Pitfall - behavior changes between calls
    std::cout << "\n4. PITFALL - Behavior depends on call history:\n";
    badExample(); // "First time"
    badExample(); // "Not first time"
    badExample(); // "Not first time"
    std::cout << "  (This pattern is hard to test and reuse - avoid it!)\n";

    // 5. Non-static contrast - resets every call
    std::cout << "\n5. Non-static local (resets every call):\n";
    noStatic(); // 1
    noStatic(); // 1
    noStatic(); // 1

    // -------------------------------------------------
    // Summary
    // -------------------------------------------------
    std::cout << "\n--- Static Local Summary ---\n";
    std::cout << "  static int s_x{0};  -> created once, persists until program end\n";
    std::cout << "  Still has block scope -> only accessible in its function\n";
    std::cout << "  Use s_ prefix       -> signals static duration\n";
    std::cout << "  Good for: ID generators, caches, one-time initialization\n";
    std::cout << "  Avoid:    changing function behavior between calls\n";

    return 0;
}
