# Chapter 17 - Fixed-Size Arrays: std::array and C-style Arrays

This chapter covers the two fixed-size array types in C++: `std::array` and C-style arrays.  
Each subfolder contains a standalone, compilable C++20 program demonstrating a key concept.

## Projects

| #   | Folder                              | Concept                                                    |
| --- | ----------------------------------- | ---------------------------------------------------------- |
| 01  | `01_StdArray_Basics`                | Declaration, initialization, value-init, constexpr, CTAD   |
| 02  | `02_StdArray_Length_And_Indexing`   | `size()`, `ssize()`, `operator[]`, `at()`, `std::get<>()`  |
| 03  | `03_Passing_And_Returning_StdArray` | Pass by const ref, function templates, returning arrays    |
| 04  | `04_StdArray_Of_Class_Types`        | Brace elision, double-brace initialization with structs    |
| 05  | `05_Arrays_Of_References`           | `std::reference_wrapper`, `std::ref()`, `std::cref()`      |
| 06  | `06_StdArray_And_Enumerations`      | Enum-to-string mapping, `static_assert` validation         |
| 07  | `07_CStyle_Arrays_Intro`            | C-style array declaration, initialization, limitations     |
| 08  | `08_Array_Decay`                    | Decay to pointer, `sizeof` pitfalls, lost length info      |
| 09  | `09_Pointer_Arithmetic`             | `ptr[n]`, pointer iteration, zero-based indexing rationale |
| 10  | `10_CStyle_Strings`                 | Null termination, `std::strlen`, buffer overflow pitfalls  |
| 11  | `11_Multidimensional_CStyle_Arrays` | 2D arrays, row-major order, Cartesian ↔ array mapping      |
| 12  | `12_Multidimensional_StdArray`      | 2D `std::array`, alias template, flattening alternative    |

## Build

Each `main.cpp` is self-contained. Compile any project with:

```bash
# GCC / MinGW
g++ -std=c++20 -Wall -Wextra -o program main.cpp

# MSVC (Developer Command Prompt)
cl /std:c++20 /EHsc /W4 main.cpp
```
