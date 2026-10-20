# Chapter 3 - Debugging C++ Programs

This chapter covers how to find and fix errors (bugs) in C++ programs. It introduces syntax vs. semantic errors, walks through a systematic debugging process, explores debugging tactics like `std::cerr` and conditional compilation, and teaches use of an integrated debugger with stepping, breakpoints, watches, and the call stack.

## Projects

| #   | Project                       | Concept                                                                                                     |
| --- | ----------------------------- | ----------------------------------------------------------------------------------------------------------- |
| 01  | 01_SyntaxVsSemanticErrors     | Difference between syntax errors (caught by compiler) and semantic/logic errors (wrong behavior at runtime) |
| 02  | 02_DebuggingProcess           | The six-step debugging process: find, understand, determine fix, repair, retest, check for regressions      |
| 03  | 03_DebuggingWithCerr          | Using `std::cerr` (unbuffered) instead of `std::cout` (buffered) for debug output                           |
| 04  | 04_ValidatingCodeFlow         | Tracing execution flow by printing function names to `std::cerr`                                            |
| 05  | 05_ConditionalDebugging       | Using `#ifdef ENABLE_DEBUG` to toggle debug output without modifying code                                   |
| 06  | 06_SteppingThroughCode        | Demonstrating code suitable for practicing step into, step over, and step out                               |
| 07  | 07_BreakpointsAndControl      | Breakpoints, continue, run-to-cursor, and set-next-statement concepts                                       |
| 08  | 08_WatchingVariables          | Inspecting and watching variable values during a debug session                                              |
| 09  | 09_CallStackDemo              | Understanding the call stack through nested function calls                                                  |
| 10  | 10_PreventionAndBestPractices | Refactoring, defensive programming, short functions, and static analysis tips                               |
