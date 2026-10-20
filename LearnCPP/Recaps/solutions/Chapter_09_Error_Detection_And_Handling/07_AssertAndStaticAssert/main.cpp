// Project 07 - Assert and static_assert
// Chapter 9: Error Detection and Handling
//
// assert(condition) - runtime check from <cassert>
//   - If condition is false, prints a diagnostic and calls std::abort()
//   - Disabled in release builds when NDEBUG is defined
//   - Use it to catch PROGRAMMER ERRORS (bugs), not user errors
//   - Add descriptive messages via the && trick:
//       assert(ptr != nullptr && "pointer must not be null");
//
// static_assert(condition, message) - compile-time check (C++11)
//   - Evaluated entirely at compile time - zero runtime cost
//   - Causes a compiler error with 'message' if the condition is false
//   - Use it to enforce assumptions about types, sizes, and constants
//
// PITFALL: Never put side effects inside assert() - they disappear in
//          release builds when NDEBUG is defined!

#include <cassert> // assert
#include <cstdint> // std::int32_t, etc.
#include <iostream>

// ============================================================================
// static_assert examples (evaluated at compile time)
// ============================================================================

// Ensure int is at least 4 bytes on this platform.
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");

// Ensure we're compiling with C++17 or later.
static_assert(__cplusplus >= 201703L, "C++17 or later is required");

// Ensure a specific type has the expected size.
static_assert(sizeof(std::int32_t) == 4, "int32_t must be exactly 4 bytes");

// ============================================================================
// A function that uses assert for precondition checking
// ============================================================================

// Computes n! (n factorial).
// Precondition: n >= 0  (a negative factorial is a programmer bug)
long long factorial(int n)
{
    // This is a programmer error, not a user error - use assert
    assert(n >= 0 && "factorial: n must be non-negative");

    long long result{1};
    for (int i{2}; i <= n; ++i)
        result *= i;

    // Postcondition: result must be positive for valid input
    assert(result > 0 && "factorial: overflow detected");

    return result;
}

// ============================================================================
// Demonstrating the side-effect pitfall
// ============================================================================

void demo_sideEffectPitfall()
{
    std::cout << "--- Side-effect pitfall demo ---\n";

    int counter{0};

    // BAD: The increment is a side effect inside assert.
    // In release builds (NDEBUG defined), assert is compiled out,
    // so ++counter never executes and counter stays 0.
    //
    //   assert(++counter && "counter incremented");   // DON'T DO THIS
    //
    // GOOD: Perform the side effect outside the assert.
    ++counter;
    assert(counter > 0 && "counter must have been incremented");

    std::cout << "  counter = " << counter
              << "  (correct - side effect is outside assert)\n\n";
}

// ============================================================================
// Demonstrating assert with descriptive messages
// ============================================================================

void demo_assertMessages()
{
    std::cout << "--- Descriptive assert messages ---\n";

    int *ptr{nullptr};

    // The string literal after && makes the assert message more helpful.
    // If this fires, the output includes: "ptr != nullptr && \"pointer is null\""
    // assert(ptr != nullptr && "pointer is null");  // Would abort!

    // Safe version for the demo:
    ptr = new int{42};
    assert(ptr != nullptr && "pointer must not be null");
    std::cout << "  *ptr = " << *ptr << "  (assert passed)\n";
    delete ptr;

    std::cout << "  Tip: Use && \"message\" to add context to your asserts.\n\n";
}

// ============================================================================
// static_assert inside a function (C++17: message is optional)
// ============================================================================

template <typename T>
T doubleValue(T value)
{
    // Only allow arithmetic types (int, float, double, etc.)
    static_assert(std::is_arithmetic_v<T>,
                  "doubleValue requires an arithmetic type");
    return value * 2;
}

// ============================================================================
// Main
// ============================================================================

int main()
{
    std::cout << "=== Assert and static_assert Demo ===\n\n";

    // --- static_assert ---
    std::cout << "All static_asserts passed at compile time (you wouldn't see\n"
              << "this message if any had failed - the code wouldn't compile).\n\n";

    // --- assert in factorial ---
    std::cout << "Factorial calculations (assert checks preconditions):\n";
    for (int n : {0, 1, 5, 10})
        std::cout << "  " << n << "! = " << factorial(n) << '\n';
    // factorial(-1);   // Uncommenting this would trigger the assert
    std::cout << '\n';

    // --- Side-effect pitfall ---
    demo_sideEffectPitfall();

    // --- Descriptive messages ---
    demo_assertMessages();

    // --- static_assert in a template ---
    std::cout << "--- static_assert in a template ---\n";
    std::cout << "  doubleValue(21)   = " << doubleValue(21) << '\n';
    std::cout << "  doubleValue(3.14) = " << doubleValue(3.14) << '\n';
    // doubleValue("hello");  // Would cause a compile error via static_assert
    std::cout << '\n';

    std::cout << "Key takeaway: Use assert for bugs, static_assert for compile-time checks.\n";
    std::cout << "Never put side effects inside assert().\n";
    return 0;
}
