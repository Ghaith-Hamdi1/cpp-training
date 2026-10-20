# Chapter 3 Recap - Debugging C++ Programs

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- The compiler catches syntax errors for you - semantic (logic) errors are the real challenge.
- Reproducing a bug reliably is the most important first step in debugging.
- Use `std::cerr` for debug output - it's unbuffered and prints immediately, unlike `std::cout`.
- Print-statement debugging works but is messy; prefer using an integrated debugger.
- Learn the core debugger commands: **step into**, **step over**, **step out**, **run to cursor**, **continue**, and **breakpoints**.
- Use the **watch window** to monitor variables as you step through code, rather than adding print statements.eer
- Use the **call stack** to understand how execution reached the current point.
- Always compile with a **debug build configuration** when using the debugger.

### 3 Tiny Examples

1.

```cpp
// Syntax error - caught by compiler:
// int x     // missing semicolon

// Semantic error - compiles but wrong result:
int area{ width - height }; // oops, should be * not -
```

2.

```cpp
std::cerr << "getValue() called\n";       // validate code flow
std::cerr << "x = " << x << '\n';         // print variable values
```

3.

```cpp
#ifdef ENABLE_DEBUG
std::cerr << "debug: x = " << x << '\n';
#endif
```

### 3 Common Mistakes

- Using `std::cout` for debug output
- Passing the wrong argument
- Assigning to the wrong variable

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Syntax error** - a statement that violates C++ grammar rules; caught by the compiler.
- **Semantic error (logic error)** - a statement that is syntactically valid but doesn't do what the programmer intended; may only appear at runtime.
- **Debugging** - the process of finding and removing errors from a program.
- **Reproduction steps** - clear steps to reliably trigger a bug so it can be studied.
- **Debugger** - a tool that lets you control program execution and inspect program state.
- **Integrated debugger** - a debugger built into the IDE (e.g. Visual Studio, Code::Blocks, VS Code).
- **Program state** - all tracked information at a point in time: variable values, call history, and current execution point.
- **Breakpoint** - a marker that tells the debugger to pause execution at a specific line.
- **Call stack** - a list of all active functions that have been called to reach the current point of execution.
- **Refactoring** - restructuring code without changing its behavior, to improve organization or readability.
- **Static analysis tool (linter)** - a program that analyzes source code for potential issues without executing it.
- **Defensive programming** - anticipating and handling ways software could be misused.
- **Unit testing** - testing small units of code in isolation to verify correctness.

---

### Section-by-Section Detail

### 3.1 - Syntax and Semantic Errors

| Error Type         | Detected By        | When Found   | Example                                  |
| ------------------ | ------------------ | ------------ | ---------------------------------------- |
| **Syntax error**   | Compiler           | Compile time | Missing semicolon, mismatched braces     |
| **Semantic error** | Programmer/testing | Runtime      | Using `-` instead of `*`, wrong variable |

- **Syntax errors** violate C++ grammar rules - the compiler catches them and refuses to compile.
- **Semantic errors** (logic errors) produce code that compiles and runs but gives wrong results - these are much harder to find because the compiler cannot detect them.
- The compiler's error message usually points to or near the problem for syntax errors, but for semantic errors you must reason about program behavior.

```cpp
// Syntax error - caught at compile time:
std::cout << "Hello"   // missing semicolon - compiler error

// Semantic error - compiles but wrong result:
int area{ width - height }; // oops, should be * not -
```

> **See also:** [Chapter 9 - Error Detection and Handling](Chapter%209%20-%20Error%20Detection%20and%20Handling.md) for systematic approaches to preventing and handling errors.

→ _See [01_SyntaxVsSemanticErrors](../solutions/Chapter_03_Debugging/01_SyntaxVsSemanticErrors/) for syntax vs. logic error examples._

### 3.2 - The Debugging Process

- **Debugging** follows a six-step process: find the root cause, understand why it happens, determine a fix, repair the issue, retest the fix, and retest the full program
- **Finding the root cause** is typically the hardest step - narrow down where the problem originates before attempting any changes
- **Understanding why** the bug occurs (step 2) is the most commonly skipped step - blindly changing code without understanding the cause often introduces new bugs
- After implementing a fix, **retest** both the specific scenario and the entire program, since a fix in one area can cause regressions elsewhere
- If you don't understand _why_ the bug occurs, your fix will likely **mask the symptom** rather than eliminate the root cause

1. **Find the root cause** - the hardest step; narrow down where the problem originates.
2. **Understand why it happens** - don't skip this! Blindly changing code introduces new bugs.
3. **Determine a fix** - plan the change before coding it.
4. **Repair the issue** - implement the fix.
5. **Retest the fix** - verify the original bug is resolved.
6. **Retest the full program** - check that the fix didn't break anything else.

> **Key insight:** Skipping step 2 is the most common debugging mistake. If you don't understand _why_ the bug occurs, your fix will often mask the symptom rather than eliminate the cause.

→ _See [02_DebuggingProcess](../solutions/Chapter_03_Debugging/02_DebuggingProcess/) for the six-step debugging process._

### 3.3 - A Strategy for Debugging

- Start with **code inspection** for simple bugs - read the code and think about what it does.
- For harder bugs, **run the program** and gather information.
- The critical first step is being able to **reproduce the problem** reliably.
- Use a **hi-lo (binary search) strategy** to narrow down the bug efficiently:

```
  Program Start
       |
  [checkpoint A]  - is the bug before or after here?
       |
  [checkpoint B]  - narrow further
       |
  Bug is isolated to a small section
```

This is far more efficient than checking line by line - each checkpoint eliminates half the remaining code.

→ _See [03_DebuggingWithCerr](../solutions/Chapter_03_Debugging/03_DebuggingWithCerr/) for the hi-lo debugging strategy._

### 3.4 - Basic Debugging Tactics

Three fundamental tactics for print-statement debugging:

- **Comment out code** - temporarily disable code sections to isolate whether they cause the bug.
- **Validate code flow** - print function names with `std::cerr` to confirm which functions are called and in what order.
- **Print variable values** - output key variables with `std::cerr` at critical points to verify they hold expected values.

> **Why `std::cerr` over `std::cout`?** `std::cout` is _buffered_ - if your program crashes before the buffer is flushed, the output is lost. `std::cerr` is _unbuffered_ and prints immediately, so debug messages always appear even on crash.

**Tip:** Number your debug statements (`std::cerr << 1`, `std::cerr << 2`, etc.) so you can see exactly which ones executed.

```cpp
std::cerr << "getValue() called\n";       // validate code flow
std::cerr << "x = " << x << '\n';         // print variable values
```

→ _See [04_ValidatingCodeFlow](../solutions/Chapter_03_Debugging/04_ValidatingCodeFlow/) for flow-tracing with `std::cerr`._

### 3.5 - More Debugging Tactics

- **Print-statement debugging** is useful but clutters code and requires manual cleanup afterward
- **`#ifdef ENABLE_DEBUG`** conditionally compiles debug statements via the preprocessor - zero overhead when disabled, but only binary on/off with no severity levels
- **Logger libraries** (e.g., plog, spdlog) write debug info to log files with **severity levels** and **timestamps**, offering more granular control
- Logger libraries require an **external dependency** and setup overhead, while `#ifdef` keeps debug statements in the source with no dependencies
- Define `ENABLE_DEBUG` to activate debug output; comment out or remove the `#define` to disable it at compile time

| Approach                          | How It Works                                                 | Pros                                                   | Cons                                |
| --------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------ | ----------------------------------- |
| **`#ifdef ENABLE_DEBUG`**         | Preprocessor conditionally compiles debug statements         | Zero overhead when disabled; statements stay in source | Binary on/off; no severity levels   |
| **Logger library** (plog, spdlog) | Writes debug info to a log file with severity and timestamps | Severity levels, timestamps, file output, reusable     | External dependency; setup overhead |

```cpp
#define ENABLE_DEBUG  // comment out to disable all debug output

#ifdef ENABLE_DEBUG
std::cerr << "debug: x = " << x << '\n';
#endif
```

→ _See [05_ConditionalDebugging](../solutions/Chapter_03_Debugging/05_ConditionalDebugging/) for toggling debug output with `#ifdef`._

### 3.6 - Using an Integrated Debugger: Stepping

- **Stepping** lets you execute code statement by statement while inspecting **program state** (variable values, execution point)
- **Step into** (`F11`) executes the next statement and _enters_ function calls - use it to debug your own functions
- **Step over** (`F10`) executes the next statement but runs function calls to completion without entering them - use for trusted or library functions
- **Step out** (`Shift+F11`) finishes the current function and pauses at the caller - useful when you entered a function you didn't need to debug
- Always compile with a **Debug build configuration** - optimizations in Release builds prevent the debugger from mapping instructions to source lines
- If you **step too far**, restart the debug session - there is no "step backward" command

| Command       | Shortcut  | Behavior                                                        | When to Use                               |
| ------------- | --------- | --------------------------------------------------------------- | ----------------------------------------- |
| **Step into** | F11       | Executes next statement; _enters_ function calls                | Debugging your own functions              |
| **Step over** | F10       | Executes next statement; _runs_ function calls without entering | Skipping trusted/library functions        |
| **Step out**  | Shift+F11 | Finishes current function; pauses at caller                     | You entered a function you didn't mean to |

- Always compile with a **Debug build configuration** - optimizations in Release builds prevent the debugger from mapping instructions to source lines.
- If you step too far, **restart** the debug session - there is no "step backward."

→ _See [06_SteppingThroughCode](../solutions/Chapter_03_Debugging/06_SteppingThroughCode/) for practicing step into/over/out._

### 3.7 - Using an Integrated Debugger: Running and Breakpoints

| Command                | Shortcut | Behavior                                                | Persists?         |
| ---------------------- | -------- | ------------------------------------------------------- | ----------------- |
| **Run to cursor**      | Ctrl+F10 | Runs to the line your cursor is on                      | No (one-shot)     |
| **Continue**           | F5       | Resumes until next breakpoint or program end            | -                 |
| **Breakpoint**         | F9       | Marks a line to pause execution every time it's reached | Yes (across runs) |
| **Set next statement** | -        | Jumps execution point forward/backward                  | -                 |

- **Breakpoints** are the backbone of efficient debugging - they let you skip directly to the suspicious area instead of stepping through hundreds of lines.
- **Set next statement** moves the instruction pointer but does **not** rewind program state - variables keep their current values.
- Combine breakpoints with continue to quickly test whether a particular line is reached.

→ _See [07_BreakpointsAndControl](../solutions/Chapter_03_Debugging/07_BreakpointsAndControl/) for breakpoint and run-control practice._

### 3.8 - Using an Integrated Debugger: Watching Variables

Inspecting variable values during execution without modifying source code:

- **Hover** over a variable in the editor to see its current value.
- **Watch window** - add variables for continuous monitoring as you step; can also evaluate expressions (e.g., `x + 2`, `x > 0`, `arr[i]`).
- **QuickWatch** - one-shot inspection of a variable or expression.
- **Locals window** - automatically shows all local variables currently in scope.
- **Data breakpoints** (watchpoints) - pause execution the moment a watched variable's value changes. Extremely powerful for finding which line caused an unexpected modification.

> **Tip:** Watch window expressions like `x == expected` (evaluates to 0 or 1) are a fast way to verify correctness at each step.

→ _See [08_WatchingVariables](../solutions/Chapter_03_Debugging/08_WatchingVariables/) for watch window and locals window demos._

### 3.9 - Using an Integrated Debugger: The Call Stack

The **call stack** shows all active functions from `main` down to the current function:

```
main()
  → processInput()
    → validateData()
      → <current breakpoint>   // you are here
```

- The **call stack window** displays this chain in the debugger.
- **Click any frame** to jump to that function and inspect its local variables - invaluable for tracing how incorrect values are passed between functions.
- Especially useful for understanding **recursive functions** and deeply nested code.
- The call stack reads bottom-to-top: the bottom frame is `main()`, the top frame is where execution is currently paused.

→ _See [09_CallStackDemo](../solutions/Chapter_03_Debugging/09_CallStackDemo/) for tracing execution through nested calls._

### 3.10 - Finding Issues Before They Become Problems

Prevention strategies (ordered by impact):

- **Keep functions short** - ideally under 10 lines; shorter functions are easier to debug, test, and understand.
- **Prefer the standard library** over hand-rolled solutions - it's tested, optimized, and well-documented.
- **Use defensive programming** - validate inputs, check preconditions, fail early with clear error messages.
- **Write unit tests** - verify individual functions produce correct output for known inputs.
- **Use static analysis tools** (clang-tidy, cppcheck, PVS-Studio) - automated code review that catches uninitialized variables, unused values, null pointer dereferences, and more.
- **Separate behavioral and structural changes** - if a bug appears after a combined change, you won't know which part caused it..
- **Don't code while fatigued** - tired programmers introduce more bugs than they fix.

→ _See [10_PreventionAndBestPractices](../solutions/Chapter_03_Debugging/10_PreventionAndBestPractices/) for prevention techniques._

---

### Edge Cases and Caveats

- **Using `std::cout` for debug output** - buffered output can be lost on crash.

  ❌ **Bad:**

  ```cpp
  std::cout << "reached here\n"; // may never appear if program crashes
  ```

  ✅ **Good:**

  ```cpp
  std::cerr << "reached here\n"; // unbuffered - prints immediately
  ```

- **Passing the wrong argument** - e.g., passing `5` instead of the variable `y`.

  ❌ **Bad:** `add(x, 5)` when you meant `add(x, y)`.
  ✅ **Good:** Double-check argument names match your intent.

- **Assigning to the wrong variable**

  ❌ **Bad:**

  ```cpp
  x = readNumber();
  x = readNumber(); // oops, overwrote x instead of assigning to y
  ```

  ✅ **Good:**

  ```cpp
  x = readNumber();
  y = readNumber();
  ```

- **Forgetting to remove debug changes** - leftover prints or commented-out code pollutes the source.

  ❌ **Bad:** Shipping code full of `std::cerr << "debug"` lines.
  ✅ **Good:** Use `#ifdef ENABLE_DEBUG` so debug output compiles away cleanly.

- **Debugging with a release build** - the debugger can't map optimized code to source lines.

  ❌ **Bad:** Building in Release mode then wondering why breakpoints don't work.
  ✅ **Good:** Always use the **Debug** build configuration when stepping through code.

- **Stepping too far in the debugger** - there's no undo.

  ❌ **Bad:** Hitting F10 one too many times and passing the bug.
  ✅ **Good:** Use breakpoints to jump close to the suspect area; restart if you overshoot.

- **Using set-next-statement without understanding it** - it moves the instruction pointer but doesn't rewind state.

  ❌ **Bad:** Jumping backward expecting variables to revert.
  ✅ **Good:** Restart the debug session if you need to re-execute code with fresh state.

- **Writing overly long functions** - harder to debug, understand, and test.

  ❌ **Bad:** A 200-line function doing multiple unrelated things.
  ✅ **Good:** Refactor into short, single-purpose functions (ideally < 10 lines).

---

### Hands-On Code Projects

| #   | Project                                                                                           | Concept                                             |
| --- | ------------------------------------------------------------------------------------------------- | --------------------------------------------------- |
| 01  | [01_SyntaxVsSemanticErrors](../solutions/Chapter_03_Debugging/01_SyntaxVsSemanticErrors/)         | Syntax errors vs. semantic/logic errors             |
| 02  | [02_DebuggingProcess](../solutions/Chapter_03_Debugging/02_DebuggingProcess/)                     | Six-step debugging process                          |
| 03  | [03_DebuggingWithCerr](../solutions/Chapter_03_Debugging/03_DebuggingWithCerr/)                   | `std::cerr` (unbuffered) vs `std::cout` (buffered)  |
| 04  | [04_ValidatingCodeFlow](../solutions/Chapter_03_Debugging/04_ValidatingCodeFlow/)                 | Tracing execution by printing function names        |
| 05  | [05_ConditionalDebugging](../solutions/Chapter_03_Debugging/05_ConditionalDebugging/)             | `#ifdef ENABLE_DEBUG` toggle for debug output       |
| 06  | [06_SteppingThroughCode](../solutions/Chapter_03_Debugging/06_SteppingThroughCode/)               | Step into (F11), step over (F10), step out          |
| 07  | [07_BreakpointsAndControl](../solutions/Chapter_03_Debugging/07_BreakpointsAndControl/)           | Breakpoints, continue, run-to-cursor                |
| 08  | [08_WatchingVariables](../solutions/Chapter_03_Debugging/08_WatchingVariables/)                   | Watch window, locals window, data breakpoints       |
| 09  | [09_CallStackDemo](../solutions/Chapter_03_Debugging/09_CallStackDemo/)                           | Call stack tracing through nested function calls    |
| 10  | [10_PreventionAndBestPractices](../solutions/Chapter_03_Debugging/10_PreventionAndBestPractices/) | Refactoring, defensive programming, static analysis |

---

### Quick Reference

| Topic                      | Details                                                                                                                |
| -------------------------- | ---------------------------------------------------------------------------------------------------------------------- |
| Syntax error               | Violates C++ grammar; caught by the compiler at compile time (e.g. missing `;`, mismatched `{}`)                       |
| Semantic error             | Code compiles but produces wrong results at runtime (e.g. using `-` instead of `+`)                                    |
| `std::cerr` vs `std::cout` | Use `std::cerr` for debug output - it's unbuffered and prints immediately, so output isn't lost if the program crashes |
| `#ifdef ENABLE_DEBUG`      | Wrap debug statements in `#ifdef` / `#endif` blocks; define `ENABLE_DEBUG` to activate, remove it to deactivate        |
| Step into (F11)            | Executes the next statement; enters function calls to debug inside them                                                |
| Step over (F10)            | Executes the next statement; runs function calls without entering them                                                 |
| Step out (Shift+F11)       | Finishes executing the current function and pauses at the caller                                                       |
| Continue (F5)              | Resumes execution until the next breakpoint is hit or the program ends                                                 |
| Run to cursor              | Runs the program to the line where your cursor is placed (one-shot, does not persist)                                  |
| Breakpoint (F9)            | Marks a line to pause execution every time it's reached; persists across runs                                          |
| Set next statement         | Moves the execution point forward or backward, but does **not** rewind program state                                   |
| Watch window               | Monitors variable values continuously as you step; can also evaluate expressions like `x + 2`                          |
| Locals window              | Automatically displays all local variables currently in scope                                                          |
| Data breakpoint            | Pauses execution when a watched variable's value changes (not all debuggers support this)                              |
| Call stack window          | Shows all active functions from `main` to the current function; click a frame to inspect its variables                 |
| Debug build config         | Disables optimizations and includes debug symbols; required for the debugger to work correctly                         |
| Static analysis tools      | Automated tools (e.g. clang-tidy, cppcheck) that analyze code for bugs without executing it                            |
| Refactoring                | Restructuring code without changing behavior; keep functions short (ideally < 10 lines)                                |

---

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is the difference between a **syntax error** and a **semantic error**? Which is harder to find, and why?

<details>
<summary>Show answer</summary>

**Direct answer:** A syntax error violates C++ grammar rules (e.g., missing semicolon, mismatched braces) and is caught at compile time. A semantic error is logically incorrect code that compiles successfully but produces wrong results at runtime (e.g., using `-` instead of `*`). Semantic errors are harder to find because the compiler cannot detect them - you must test and debug to discover them.

**Detailed explanation:**
The compiler is your first line of defense and will always catch syntax errors. Semantic errors require you to notice incorrect output, reproduce the bug, and trace it back to the faulty logic. A good habit is to compile frequently so syntax errors are caught close to when they're introduced, and to test your program's output against expected results to catch semantic errors early.

```cpp
// Syntax error - caught by compiler:
// int x     // missing semicolon

// Semantic error - compiles but wrong result:
int area{ width - height }; // oops, should be * not -
```

</details>

2. Name the six steps in the general debugging process.

<details>
<summary>Show answer</summary>

**Direct answer:** (1) Find the root cause, (2) understand why it happens, (3) determine a fix, (4) repair the issue, (5) retest the fix, and (6) retest for new problems (regressions).

**Detailed explanation:**
The hardest step is usually finding the root cause. Skipping the "understand" step is a common mistake - blindly changing code without understanding the root cause often introduces new bugs. Always retest the entire program after a fix, not just the specific scenario that was broken, because a fix in one area can inadvertently break something else.

</details>

3. Why should you use `std::cerr` instead of `std::cout` for debug output?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::cerr` is unbuffered, so output appears immediately even if the program crashes. `std::cout` is buffered, meaning output may be lost if the program crashes before the buffer is flushed - making it look like your debug print was never reached.

**Detailed explanation:**
When debugging a crash, you need to know which statements executed before the crash. If you use `std::cout`, its output sits in a buffer and may never be written to the console if the program terminates abnormally. `std::cerr` bypasses the buffer and writes directly, so you always see the output. Numbering your debug statements (e.g., `std::cerr << "checkpoint 1\n"`) makes it easy to see exactly which ones executed. For production code, use `#ifdef ENABLE_DEBUG` to conditionally compile debug output so it can be toggled without cluttering the code.

</details>

4. What is the difference between **step into**, **step over**, and **step out**?

<details>
<summary>Show answer</summary>

**Direct answer:** **Step into** (F11) executes the next statement and enters any function call. **Step over** (F10) executes the next statement but runs function calls to completion without entering them. **Step out** (Shift+F11) finishes executing the current function and pauses at the caller.

**Detailed explanation:**
Use **step over** for library/standard functions you trust (like `std::cout`), and **step into** only for your own functions where the bug might live. **Step out** is useful when you've stepped into a function and realized the bug isn't there - it runs the rest of the function and returns you to the caller. The debugger requires a **debug build configuration** (low optimization, full symbols) to work properly. If you step too far past the bug, you must restart the debug session.

</details>

5. What is a **breakpoint**, and how does it differ from **run to cursor**?

<details>
<summary>Show answer</summary>

**Direct answer:** A breakpoint (F9) is a persistent marker on a line that pauses execution every time that line is reached. Run to cursor is a one-shot command that runs the program until it reaches the line your cursor is on, then pauses once. Breakpoints persist across debug sessions; run to cursor does not.

**Detailed explanation:**
Use breakpoints when you need to pause at the same location repeatedly (e.g., inside a loop or a function called multiple times). Use run to cursor when you want to quickly jump to a specific line without setting a permanent breakpoint. **Continue** (F5) resumes execution from a pause and runs until the program ends or another breakpoint is hit. You can set multiple breakpoints simultaneously and toggle them on/off without deleting them.

</details>

6. What does the **call stack** show, and why is it useful during debugging?

<details>
<summary>Show answer</summary>

**Direct answer:** The call stack shows the chain of all active function calls from `main()` down to the currently executing function. It lets you see exactly how execution reached the current point, which is invaluable for tracing how incorrect values are being passed between functions.

**Detailed explanation:**
The call stack window in the debugger displays each active function as a "frame." You can click on any frame to jump to that function's code and inspect its local variables at that point in time. This is especially useful for understanding recursive calls, deeply nested code, and situations where a function is called from multiple places and you need to know which caller triggered the bug.

</details>

7. Why should you make behavioral and structural changes separately?

<details>
<summary>Show answer</summary>

**Direct answer:** A behavioral change modifies what the program does (its logic), while a structural change reorganizes code without changing behavior (refactoring). If you mix both in one step and something breaks, you can't tell whether the bug came from the new logic or the reorganization. Making them separately keeps each change testable in isolation.

**Detailed explanation:**
When refactoring (e.g., extracting a function, renaming variables), the program should behave identically before and after. If you simultaneously add new logic and restructure existing code, any bug could be in either change. By separating them, you compile and test after the structural change to confirm nothing broke, then make the behavioral change and test again. This discipline significantly reduces debugging time.

</details>

8. Name two **static analysis tools** for C++ and explain what they do.

<details>
<summary>Show answer</summary>

**Direct answer:** Two common static analysis tools are **clang-tidy** and **cppcheck**. They analyze your source code without executing it, detecting potential bugs, style issues, and undefined behavior that the compiler might miss.

**Detailed explanation:**
Static analysis tools examine code at compile time (or pre-compile time) and find issues like memory leaks, null pointer dereferences, unused variables, and coding standard violations. They complement compiler warnings by performing deeper analysis. Many IDEs integrate static analysis directly (e.g., Visual Studio has built-in code analysis, and clang-tidy integrates with VS Code). Using these tools regularly, together with high warning levels, catches bugs early and improves code quality.

</details>

9. What is the difference between the **watch window** and hovering over a variable in the debugger?

<details>
<summary>Show answer</summary>

**Direct answer:** Hovering over a variable shows its current value in a tooltip at that moment. The watch window persistently monitors one or more variables (or expressions) in a panel, updating their values as you step through code. The watch window is better for tracking how values change over time across multiple steps.

**Detailed explanation:**
The watch window can also evaluate simple expressions (e.g., `x + y` or `x > 0`), letting you compute derived values without adding them to your source code. QuickWatch (available on some IDEs) provides a dialog for one-time expression evaluation. Use the watch window for variables you need to track across multiple steps, and hovering or QuickWatch for quick spot checks.

</details>

10. What is **defensive programming**, and how does it help prevent bugs?

<details>
<summary>Show answer</summary>

**Direct answer:** Defensive programming means writing code that anticipates and handles misuse or unexpected input, rather than assuming everything will be used correctly. It helps prevent bugs by catching invalid states early before they propagate through the program.

**Detailed explanation:**
Techniques include validating function inputs, using assertions to enforce invariants, keeping functions short (ideally under 10 lines for easier reasoning), preferring well-tested standard library functions over hand-rolled implementations, and not coding while fatigued. The goal is to make bugs harder to introduce and easier to detect when they do occur.

</details>
