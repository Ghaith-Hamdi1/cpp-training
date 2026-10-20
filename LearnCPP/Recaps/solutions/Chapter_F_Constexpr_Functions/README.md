# Chapter F - Constexpr Functions

Solutions and examples for Chapter F of _Learn C++_.

This chapter covers **constexpr** and **consteval** functions - functions that can
(or must) be evaluated at compile-time rather than runtime.

## Projects

| #   | Folder                             | Concept                                                              |
| --- | ---------------------------------- | -------------------------------------------------------------------- |
| 1   | `01_Constexpr_Function_Basics`     | Basic constexpr functions - compile-time and runtime usage           |
| 2   | `02_Compile_Time_Guarantee`        | When compile-time evaluation is guaranteed vs optional               |
| 3   | `03_Consteval_Immediate_Functions` | `consteval` (C++20) - functions that _must_ evaluate at compile-time |
| 4   | `04_Constexpr_vs_Consteval`        | Side-by-side comparison of `constexpr` and `consteval`               |
| 5   | `05_Parameters_Are_Not_Constexpr`  | Why function parameters are never constexpr (common pitfall)         |
| 6   | `06_Constexpr_Locals_And_Mutation` | Constexpr functions can declare and mutate non-const local variables |
| 7   | `07_Testing_In_Constant_Context`   | Always test constexpr functions in a compile-time context            |
| 8   | `08_Is_Constant_Evaluated`         | `std::is_constant_evaluated()` and `if consteval` (C++23)            |

## Build

Each subfolder contains a standalone `main.cpp`.  
Compile any project with a C++20 (or C++23 for project 8) compiler:

```bash
g++ -std=c++20 -o main main.cpp
```
