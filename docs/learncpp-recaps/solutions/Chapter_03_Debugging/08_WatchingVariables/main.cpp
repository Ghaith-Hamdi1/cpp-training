// Chapter 3 - Project 08: Watching Variables
// =============================================
//
// KEY CONCEPT:
//   Instead of adding print statements to inspect variables, use
//   the debugger's WATCH features:
//
//   HOVER:        Pause at a breakpoint, then hover your mouse over
//                 any variable to see its current value in a tooltip.
//
//   WATCH WINDOW: Add variables or expressions (e.g., "x + y", "arr[i]")
//                 to the watch window. Their values update automatically
//                 as you step through code.
//
//   LOCALS WINDOW: Automatically shows ALL local variables currently
//                  in scope - no setup needed.
//
//   QUICKWATCH:   In Visual Studio, highlight an expression and press
//                 Shift+F9 to evaluate it in a dialog.
//
// HOW TO USE THIS PROGRAM:
//   1. Set a breakpoint at the top of the loop in main().
//   2. Start debugging (F5).
//   3. Add these to the Watch window:
//        total
//        i
//        values[i]
//        total / (i + 1)    <-- watch expressions can include math!
//   4. Step through the loop and observe the values change.

#include <iostream>
#include <array>

double computeAverage(const std::array<int, 6> &values, int count)
{
    // Set a breakpoint here and watch 'sum' grow as you step through.
    double sum{0.0};

    for (int i{0}; i < count; ++i)
    {
        sum += values[static_cast<std::size_t>(i)];

        // WATCH SUGGESTIONS while paused here:
        //   sum            - running total so far
        //   values[i]      - current element being added
        //   sum / (i + 1)  - running average
        //   i < count      - evaluates to true/false (loop condition)
    }

    return sum / count;
}

int main()
{
    std::cout << "=== Watching Variables Demo ===\n\n";

    // These values are good for watching because the running average
    // changes noticeably with each iteration.
    std::array<int, 6> values{10, 25, 7, 42, 15, 31};

    std::cout << "Values: ";
    for (int v : values)
    {
        std::cout << v << ' ';
    }
    std::cout << '\n';

    // Set a breakpoint on the next line, then Step Into computeAverage().
    // In the Locals window, you'll see 'values' and 'count'.
    // Expand 'values' to see all array elements.
    double avg{computeAverage(values, static_cast<int>(values.size()))};

    std::cout << "Average: " << avg << '\n';

    // BONUS: Watch window can detect changes.
    // Some debuggers highlight variables in red when their value changes
    // between steps, making it easy to spot unexpected mutations.

    // PITFALL: Watching variables only works when the program is PAUSED.
    // You cannot inspect values while the program is running.
    // Use breakpoints or stepping to pause at the right moment.

    return 0;
}
