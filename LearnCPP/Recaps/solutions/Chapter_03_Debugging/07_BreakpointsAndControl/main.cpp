// Chapter 3 - Project 07: Breakpoints and Execution Control
// ===========================================================
//
// KEY CONCEPT:
//   BREAKPOINT (F9):
//     A persistent marker on a line. Every time execution reaches that
//     line, the debugger pauses. Unlike run-to-cursor, breakpoints stay
//     set across runs until you remove them.
//
//   CONTINUE (F5):
//     Resumes execution from a paused state. The program runs until it
//     hits the next breakpoint or finishes.
//
//   RUN TO CURSOR:
//     A one-shot "temporary breakpoint" - execution runs until it reaches
//     the line your cursor is on, then pauses. After that, the marker
//     is gone.
//
//   SET NEXT STATEMENT:
//     Moves the execution point to a different line. WARNING: this does
//     NOT rewind variable values or undo side effects. It simply changes
//     which line executes next. Use with extreme caution.
//
// HOW TO USE THIS PROGRAM:
//   1. Set breakpoints on several lines inside the loop (e.g., the
//      std::cout line and the if-statement).
//   2. Start debugging (F5). The program pauses at the first breakpoint.
//   3. Press Continue (F5) to jump to the next breakpoint hit.
//   4. Remove a breakpoint (F9 on the same line) and Continue again -
//      notice it no longer pauses there.

#include <iostream>

bool isEven(int n)
{
    return (n % 2) == 0;
}

int main()
{
    std::cout << "=== Breakpoints and Execution Control Demo ===\n\n";

    // TIP: Set a breakpoint on the std::cout line inside the loop.
    //       Then press Continue (F5) repeatedly to see it pause on
    //       each iteration.

    for (int i{1}; i <= 10; ++i)
    {
        // BREAKPOINT CANDIDATE: Set a breakpoint here (F9).
        // Each iteration, the debugger will pause and you can
        // inspect 'i' in the watch window or by hovering.
        std::cout << "i = " << i;

        if (isEven(i))
        {
            // BREAKPOINT CANDIDATE: Set a breakpoint here to pause
            // only when i is even.
            std::cout << " (even)";
        }
        else
        {
            std::cout << " (odd)";
        }

        std::cout << '\n';
    }

    // --- Set Next Statement Warning ---
    // If you use "Set Next Statement" to jump backward in the loop,
    // the variable 'i' keeps its CURRENT value - it does not reset.
    // Example: If i=7 and you jump back to the loop header, i is
    // still 7 and gets incremented to 8 on the next iteration.
    // The loop does NOT restart from i=1.

    std::cout << "\nLoop complete.\n";

    // CONDITIONAL BREAKPOINT TIP:
    // In Visual Studio, you can right-click a breakpoint and add a
    // condition like: i == 5
    // The breakpoint will only trigger when i equals 5, letting you
    // skip uninteresting iterations automatically.

    return 0;
}
