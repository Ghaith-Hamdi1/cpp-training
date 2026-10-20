// Chapter 3 - Project 06: Stepping Through Code
// ================================================
//
// KEY CONCEPT:
//   The debugger lets you execute code one statement at a time:
//
//   STEP INTO  (F11)       - Execute the next statement. If it is a function
//                            call, enter the function and pause at its first line.
//   STEP OVER  (F10)       - Execute the next statement. If it is a function
//                            call, run the entire function and pause after it returns.
//   STEP OUT   (Shift+F11) - Finish executing the current function, then pause
//                            at the statement after the call site in the caller.
//
//   IMPORTANT: You must compile with a DEBUG build configuration for the
//   debugger to work correctly. Release builds optimize code and remove
//   debug symbols, making stepping unreliable.
//
// HOW TO USE THIS PROGRAM:
//   1. Set a breakpoint on the first line of main().
//   2. Start debugging (F5).
//   3. Use Step Into to enter each function call.
//   4. Use Step Over to skip a function you don't need to inspect.
//   5. Use Step Out to finish a function early and return to the caller.
//
//   If you step too far, there is NO undo - restart the debug session.

#include <iostream>

// A simple function to practice Step Into
int square(int n)
{
    // When you Step Into the call to square(), you'll land here.
    // Try stepping over the return statement to see the result.
    return n * n;
}

// A function that calls another function - good for practicing Step Out
int sumOfSquares(int a, int b)
{
    // Step Into this function, then Step Into square(a).
    // After inspecting square(), use Step Out to return here.
    int sqA{square(a)};
    int sqB{square(b)}; // Try Step Over here to skip entering square()
    return sqA + sqB;
}

// A function with a loop - step through iterations one at a time
int sumRange(int start, int end)
{
    int total{0};
    // Step Over (F10) through each iteration to watch 'total' grow.
    // Check the value of 'total' in the watch window or by hovering.
    for (int i{start}; i <= end; ++i)
    {
        total += i;
    }
    return total;
}

int main()
{
    // SET A BREAKPOINT HERE (F9) then start debugging (F5).

    std::cout << "=== Stepping Through Code Demo ===\n\n";

    // Step Into this call to enter square():
    int result1{square(5)};
    std::cout << "square(5) = " << result1 << '\n';

    // Step Into this call, then Step Into/Out of nested square() calls:
    int result2{sumOfSquares(3, 4)};
    std::cout << "sumOfSquares(3, 4) = " << result2 << '\n';

    // Step Over through the loop iterations:
    int result3{sumRange(1, 10)};
    std::cout << "sumRange(1, 10) = " << result3 << '\n';

    // TIP: If you accidentally Step Into a standard library function
    // (like std::cout's operator<<), use Step Out immediately to
    // escape back to your code.

    return 0;
}
