// Appendix B - C++ Updates: Project 02 - C++14 Improvements
// C++14 was a smaller "bugfix" release that polished C++11.
// It focused on usability improvements and filling gaps.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>

// ============================================================================
// HELPER: Generic function using C++14 return type deduction
// ============================================================================

// Before C++14: You had to specify the return type explicitly, or use
//   trailing return types with decltype:
//     auto add(int a, int b) -> decltype(a + b) { return a + b; }
// Now: The compiler deduces the return type from the return statement.

auto add(int a, int b)
{
    return a + b; // Return type deduced as int
}

auto makeGreeting(const std::string &name)
{
    return "Hello, " + name + "!"; // Return type deduced as std::string
}

// Multiple return statements are fine as long as they all return the same type
auto absoluteValue(int x)
{
    if (x < 0)
        return -x; // int
    return x;      // int - same type, OK
}

// ============================================================================
// HELPER: Demonstrating deprecated [[deprecated]] attribute
// ============================================================================

// C++14 added the [[deprecated]] attribute to mark functions/types that
// should no longer be used. The compiler emits a warning when they're called.
// (We comment out the usage to avoid build warnings in our demo.)

[[deprecated("Use newFunction() instead")]]
int oldFunction()
{
    return 42;
}

int newFunction() { return 100; }

int main()
{
    std::cout << "=== Appendix B: C++14 Improvements ===\n\n";

    // ========================================================================
    // 1. BINARY LITERALS
    // ========================================================================
    // Before C++14: No standard way to write binary numbers in source code.
    //   You had to use hex (0xFF) or decimal and mentally convert.
    // Now: Prefix 0b or 0B lets you write binary directly.
    std::cout << "--- 1. Binary literals ---\n";

    auto byte1 = 0b11111111;  // 255 in binary
    auto byte2 = 0b00001010;  // 10 in binary
    auto flags = 0b1010'0101; // With digit separator (see below)

    std::cout << "  0b11111111 = " << byte1 << '\n';
    std::cout << "  0b00001010 = " << byte2 << '\n';
    std::cout << "  0b1010'0101 = " << flags << " (165 in decimal)\n\n";

    // ========================================================================
    // 2. DIGIT SEPARATORS (apostrophe)
    // ========================================================================
    // Before C++14: Large numeric literals were hard to read:
    //   long bigNum = 1000000000;  // How many zeros?
    // Now: Single quotes (') can separate digit groups for readability.
    // They have no effect on the value - purely visual.
    std::cout << "--- 2. Digit separators ---\n";

    auto billion = 1'000'000'000;            // Much clearer than 1000000000
    auto hexColor = 0xFF'A5'00;              // Orange in RGB (hex)
    auto binPattern = 0b1111'0000'1010'0101; // Binary with separators
    auto piDigits = 3.141'592'653'589'793;   // Works for floating point too

    std::cout << "  1'000'000'000  = " << billion << '\n';
    std::cout << "  0xFF'A5'00     = " << hexColor << " (decimal)\n";
    std::cout << "  binary pattern = " << binPattern << '\n';
    std::cout << "  pi             = " << piDigits << '\n';
    std::cout << '\n';

    // ========================================================================
    // 3. GENERIC LAMBDAS
    // ========================================================================
    // Before C++14: Lambda parameters had to be concrete types.
    //   auto add = [](int a, int b) { return a + b; };
    //   // Can't reuse this for doubles or strings!
    // Now: Using 'auto' in lambda parameters makes them generic (templated).
    std::cout << "--- 3. Generic lambdas ---\n";

    // This single lambda works with int, double, string, or any type with operator+
    auto genericAdd = [](auto a, auto b)
    {
        return a + b;
    };

    std::cout << "  genericAdd(3, 4)         = " << genericAdd(3, 4) << '\n';
    std::cout << "  genericAdd(1.5, 2.7)     = " << genericAdd(1.5, 2.7) << '\n';
    std::cout << "  genericAdd(\"Hi \", \"C++\") = " << genericAdd(std::string{"Hi "}, std::string{"C++"}) << '\n';

    // Generic lambda for printing any container
    auto printContainer = [](const auto &container, const std::string &label)
    {
        std::cout << "  " << label << ": { ";
        for (const auto &elem : container)
            std::cout << elem << ' ';
        std::cout << "}\n";
    };

    std::vector<int> ints{1, 2, 3};
    std::vector<double> doubles{1.1, 2.2, 3.3};
    std::vector<std::string> words{"hello", "generic", "lambda"};

    printContainer(ints, "ints");
    printContainer(doubles, "doubles");
    printContainer(words, "words");
    std::cout << '\n';

    // ========================================================================
    // 4. RETURN TYPE DEDUCTION
    // ========================================================================
    // Demonstrated by the helper functions at the top of the file.
    std::cout << "--- 4. Return type deduction ---\n";

    std::cout << "  add(10, 20)            = " << add(10, 20) << '\n';
    std::cout << "  makeGreeting(\"C++14\")  = " << makeGreeting("C++14") << '\n';
    std::cout << "  absoluteValue(-42)     = " << absoluteValue(-42) << '\n';
    std::cout << '\n';

    // ========================================================================
    // 5. GENERALIZED LAMBDA CAPTURES (init captures)
    // ========================================================================
    // Before C++14: Lambdas could only capture existing variables by copy or ref.
    // Now: You can create new variables in the capture clause itself.
    // This is essential for moving objects into lambdas and renaming captures.
    std::cout << "--- 5. Generalized lambda captures ---\n";

    // Create a new variable 'offset' in the capture, initialized to 100
    auto addOffset = [offset = 100](int x)
    {
        return x + offset;
    };
    std::cout << "  addOffset(42) = " << addOffset(42) << '\n';

    // Move a string into a lambda (can't do this with C++11 captures)
    auto greeting = std::string{"Captured by move!"};
    auto showGreeting = [msg = std::move(greeting)]()
    {
        std::cout << "  " << msg << '\n';
    };
    showGreeting();
    std::cout << "  Original string after move: \"" << greeting << "\" (empty)\n";

    // Computed init capture
    int base = 5;
    auto computedCapture = [squared = base * base](int x)
    {
        return x + squared;
    };
    std::cout << "  base=5, computedCapture(10) = " << computedCapture(10)
              << " (10 + 25)\n";
    std::cout << '\n';

    // ========================================================================
    // 6. [[deprecated]] ATTRIBUTE
    // ========================================================================
    std::cout << "--- 6. [[deprecated]] attribute ---\n";
    std::cout << "  newFunction() = " << newFunction() << '\n';
    std::cout << "  oldFunction() is marked [[deprecated(\"Use newFunction() instead\")]]\n";
    std::cout << "  Calling it would produce a compiler warning.\n";
    // int old = oldFunction(); // Uncomment to see the deprecation warning
    std::cout << '\n';

    // ========================================================================
    // 7. std::make_unique (moved here from C++11 where it was missing)
    // ========================================================================
    // In C++11, we had std::unique_ptr but no std::make_unique.
    // You had to write: std::unique_ptr<int> p(new int(42));
    // C++14 added make_unique for consistency with make_shared and safety.
    std::cout << "--- 7. std::make_unique ---\n";

    auto ptr = std::make_unique<int>(42);
    std::cout << "  make_unique<int>(42) = " << *ptr << '\n';

    // Safe: no raw 'new' needed, exception-safe
    auto arr = std::make_unique<int[]>(5); // Array version
    for (int i = 0; i < 5; ++i)
        arr[i] = i * 10;
    std::cout << "  make_unique<int[]>(5): ";
    for (int i = 0; i < 5; ++i)
        std::cout << arr[i] << ' ';
    std::cout << '\n';

    std::cout << "\n=== C++14 demo complete ===\n";

    return 0;
}
