// Chapter 3 - Project 09: The Call Stack
// ========================================
//
// KEY CONCEPT:
//   The CALL STACK is a list of all active functions from main() down to
//   the current point of execution. Each entry is called a STACK FRAME
//   and records: the function name, source file, line number, and local
//   variable values.
//
//   When function A calls function B, B is "pushed" onto the stack.
//   When B returns, it is "popped" off. The stack always shows the
//   chain of calls that led to the current statement.
//
//   The CALL STACK WINDOW in the debugger shows this. You can click on
//   any frame to see that function's local variables and the line where
//   it called the next function.
//
// HOW TO USE THIS PROGRAM:
//   1. Set a breakpoint inside the deepest function: doWork().
//   2. Start debugging (F5).
//   3. When paused, open the Call Stack window (Debug > Windows > Call Stack
//      in Visual Studio, or the Call Stack panel in VS Code).
//   4. You should see:
//        doWork()          <-- current location
//        processItem()     <-- called doWork()
//        processAll()      <-- called processItem()
//        main()            <-- called processAll()
//   5. Click each frame to see its local variables and where it paused.

#include <iostream>
#include <string>

// Deepest function - set a breakpoint here to see the full call stack.
void doWork(const std::string &item, int step)
{
    // When paused here, the call stack shows all callers above.
    std::cout << "  [doWork] Processing \"" << item
              << "\", step " << step << '\n';
}

void processItem(const std::string &item)
{
    std::cout << " [processItem] Starting item: \"" << item << "\"\n";

    // Call doWork multiple times - each call shows in the stack.
    for (int step{1}; step <= 3; ++step)
    {
        doWork(item, step); // Step Into here to see the growing stack
    }

    std::cout << " [processItem] Finished item: \"" << item << "\"\n";
}

void processAll()
{
    std::cout << "[processAll] Starting batch processing\n";

    // Each call to processItem() adds a frame to the stack.
    processItem("Alpha");
    processItem("Beta");

    std::cout << "[processAll] Batch processing complete\n";
}

int main()
{
    std::cout << "=== Call Stack Demo ===\n\n";

    // When debugging: set a breakpoint inside doWork(), then start
    // debugging. The call stack will look like:
    //
    //   doWork         main.cpp  line ~29
    //   processItem    main.cpp  line ~40
    //   processAll     main.cpp  line ~51
    //   main           main.cpp  line ~62
    //
    // This is invaluable for understanding HOW the program reached
    // a specific point, especially in large codebases.

    processAll();

    // TIP: The call stack is most useful with breakpoints.
    // When your program crashes or produces wrong output, set a
    // breakpoint near the problem. The call stack tells you the
    // entire chain of function calls that led there - helping you
    // trace the bug back to its ROOT CAUSE.

    return 0;
}
