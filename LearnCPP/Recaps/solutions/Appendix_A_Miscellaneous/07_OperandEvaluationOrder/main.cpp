// Project 07: Operand Evaluation Order
// ======================================
// Appendix A.4 - Unspecified operand evaluation order
//
// In C++, the order in which operands of most operators are evaluated
// is UNSPECIFIED.  This means the compiler can evaluate them in any
// order it wants, and that order can change between builds.
//
// This is NOT undefined behavior - the individual evaluations are
// well-defined, but the ORDER is left to the compiler.  However,
// if operands have side effects (like reading input or modifying a
// variable), the result becomes non-deterministic.
//
// The most common pitfall:
//   std::cout << getInput() << getInput();
// You don't know which getInput() runs first!
//
// Best practice:
//   Don't call the same side-effecting function multiple times in
//   one expression.  Separate them into individual statements.

#include <iostream>
#include <string>
#include <sstream>

// -----------------------------------------------------------------------
// Simulated input function with side effects
// Each call returns the next value from a predefined sequence.
// -----------------------------------------------------------------------
class InputSimulator
{
    int m_callCount{0};
    int m_values[4]{10, 20, 30, 40};

public:
    int getNext()
    {
        int index = m_callCount % 4;
        ++m_callCount;
        return m_values[index];
    }

    int getCallCount() const { return m_callCount; }
};

// -----------------------------------------------------------------------
// Functions with observable side effects
// -----------------------------------------------------------------------
int addAndPrint(int a, int b)
{
    int result = a + b;
    std::cout << "  [addAndPrint called: " << a << " + " << b
              << " = " << result << "]\n";
    return result;
}

int multiplyAndPrint(int a, int b)
{
    int result = a * b;
    std::cout << "  [multiplyAndPrint called: " << a << " * " << b
              << " = " << result << "]\n";
    return result;
}

int main()
{
    std::cout << "=== Operand Evaluation Order ===\n\n";

    // ===================================================================
    // 1. PROBLEM: Multiple side-effecting calls in one expression
    // ===================================================================
    std::cout << "--- Problem: Multiple calls in one expression ---\n";
    {
        InputSimulator sim;

        // BAD: Both calls have side effects (advancing the counter).
        // We don't know which getNext() is called first!
        //
        //   int result = sim.getNext() + sim.getNext();
        //
        // If left-to-right:  result = 10 + 20 = 30
        // If right-to-left:  result = 20 + 10 = 30 (same sum, but...)
        //
        // With subtraction it matters:
        //   int result = sim.getNext() - sim.getNext();
        //   Left-to-right: 10 - 20 = -10
        //   Right-to-left: 20 - 10 =  10
        //
        // The result is non-deterministic!

        // SAFE: separate into individual statements
        int first = sim.getNext();  // 10
        int second = sim.getNext(); // 20
        int result = first - second;

        std::cout << "first  = " << first << '\n';
        std::cout << "second = " << second << '\n';
        std::cout << "first - second = " << result << "  (deterministic!)\n";
    }

    // ===================================================================
    // 2. PROBLEM: Function arguments - order unspecified
    // ===================================================================
    std::cout << "\n--- Problem: Function argument evaluation order ---\n";
    {
        // BAD:
        //   someFunc(getA(), getB());
        // getA() might be called before or after getB().

        // SAFE: evaluate arguments in separate statements
        int a = addAndPrint(3, 4);      // always runs first
        int b = multiplyAndPrint(5, 6); // always runs second
        int total = a + b;
        std::cout << "total = " << a << " + " << b << " = " << total << '\n';
    }

    // ===================================================================
    // 3. PROBLEM: Chained << with side effects
    // ===================================================================
    std::cout << "\n--- Problem: Chained << with side-effecting calls ---\n";
    {
        InputSimulator sim;

        // BAD:
        //   std::cout << sim.getNext() << " " << sim.getNext();
        // Output could be "10 20" or "20 10" depending on evaluation order!

        // SAFE: call separately
        int val1 = sim.getNext();
        int val2 = sim.getNext();
        std::cout << "val1 = " << val1 << ", val2 = " << val2
                  << "  (order guaranteed by separate statements)\n";
    }

    // ===================================================================
    // 4. What IS guaranteed
    // ===================================================================
    std::cout << "\n--- What IS guaranteed ---\n";
    std::cout << "- && and || short-circuit: left operand first.\n";
    std::cout << "- Comma operator: left operand first.\n";
    std::cout << "- Ternary (?:): condition first.\n";
    std::cout << "- Function call: all args evaluated before the call.\n";
    std::cout << "  (But the ORDER of arg evaluation is unspecified.)\n";

    // Demonstration: short-circuit is safe
    int *ptr = nullptr;
    if (ptr != nullptr && *ptr == 42)
    {
        // Safe: if ptr is null, *ptr is never evaluated
        std::cout << "Pointer value: " << *ptr << '\n';
    }
    else
    {
        std::cout << "Short-circuit: *ptr was NOT evaluated (ptr is null).\n";
    }

    // ===================================================================
    // Summary
    // ===================================================================
    std::cout << "\n--- Summary ---\n";
    std::cout << "1. Operand evaluation order is unspecified for most operators.\n";
    std::cout << "2. Never put multiple side-effecting calls in one expression.\n";
    std::cout << "3. Separate side-effecting calls into individual statements.\n";
    std::cout << "4. Short-circuit operators (&&, ||) DO guarantee left-first.\n";

    return 0;
}
