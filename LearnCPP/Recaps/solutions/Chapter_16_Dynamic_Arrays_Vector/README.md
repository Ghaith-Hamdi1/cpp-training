# Chapter 16 - Dynamic Arrays: std::vector

This chapter covers `std::vector`, the C++ standard library's dynamic array. Each subfolder contains a self-contained, compilable C++20 program demonstrating a key concept.

## Projects

| #   | Folder                          | Topic                                                        |
| --- | ------------------------------- | ------------------------------------------------------------ |
| 01  | `01_IntroToVector`              | Basic vector declaration, initialization, and CTAD           |
| 02  | `02_ListVsLengthConstructor`    | The `{n}` vs `(n)` initialization gotcha                     |
| 03  | `03_SubscriptAndBoundsChecking` | `operator[]` vs `at()` and bounds checking                   |
| 04  | `04_LengthAndCapacity`          | `size()`, `capacity()`, `ssize()`, and `size_type`           |
| 05  | `05_PassingVectors`             | Passing vectors by const reference and with templates        |
| 06  | `06_ReturningVectors`           | Returning vectors by value and move semantics                |
| 07  | `07_IndexBasedLoops`            | Traversal with index-based for loops and off-by-one pitfalls |
| 08  | `08_RangeBasedForLoops`         | Range-based for loops, `auto&`, `const auto&`, reverse       |
| 09  | `09_ResizingAndCapacity`        | `resize()`, `reserve()`, `shrink_to_fit()`, reallocation     |
| 10  | `10_StackBehavior`              | `push_back()`, `pop_back()`, `back()`, `emplace_back()`      |
| 11  | `11_EnumeratorIndices`          | Using enumerators as meaningful array indices                |
| 12  | `12_VectorBoolPitfall`          | Why `std::vector<bool>` is broken and what to use instead    |

## How to Compile

Each `main.cpp` compiles independently with any C++20 compiler:

```bash
# GCC / MinGW
g++ -std=c++20 -o main main.cpp

# MSVC (Developer Command Prompt)
cl /std:c++20 /EHsc main.cpp
```
