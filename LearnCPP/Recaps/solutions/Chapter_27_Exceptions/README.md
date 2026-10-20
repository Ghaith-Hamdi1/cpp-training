# Chapter 27 - Exceptions

This chapter covers C++ exception handling: the mechanism that decouples error handling from normal control flow using `throw`, `try`, and `catch`.

## Projects

| #   | Folder                        | Concept                                                              |
| --- | ----------------------------- | -------------------------------------------------------------------- |
| 01  | `01_NeedForExceptions`        | Why return codes fall short and how exceptions solve those problems  |
| 02  | `02_BasicExceptionHandling`   | Using `throw`, `try`, and `catch` - no implicit type conversion      |
| 03  | `03_ExceptionsAndFunctions`   | Exceptions propagating up through function calls                     |
| 04  | `04_StackUnwinding`           | How local variables are destroyed as the stack unwinds               |
| 05  | `05_UncaughtAndCatchAll`      | Uncaught exceptions, `std::terminate`, and `catch(...)`              |
| 06  | `06_ExceptionClasses`         | Custom exception classes, `std::exception`, and `std::runtime_error` |
| 07  | `07_InheritanceAndCatchOrder` | Catching derived before base - order matters                         |
| 08  | `08_RethrowingExceptions`     | `throw;` vs `throw exception;` - avoiding slicing                    |
| 09  | `09_FunctionTryBlocks`        | Wrapping constructors (including initializer lists) in try/catch     |
| 10  | `10_NoexceptSpecifier`        | `noexcept`, `std::terminate`, and the `noexcept` operator            |
| 11  | `11_RAIIAndExceptionSafety`   | Resource leaks, RAII, and why destructors must not throw             |
| 12  | `12_MoveIfNoexcept`           | `std::move_if_noexcept` and the strong exception guarantee           |

## Build

Each project is a standalone `main.cpp`. Compile with any C++20 compiler:

```bash
cd 01_NeedForExceptions
g++ -std=c++20 -o main main.cpp && ./main
```
