# Appendix B - C++ Updates

## Summary

This appendix provides a hands-on tour of the major C++ standard revisions from C++11 through C++23. Each project demonstrates the key features introduced in that standard version, with detailed comments explaining **what** each feature does, **why** it was added, and **what it replaced**. The code is designed to compile and run, producing clear output that shows each feature in action.

C++ evolves on a 3-year cycle. The major themes of each release:

- **C++11** - The "modern C++" revolution: move semantics, lambdas, auto, smart pointers
- **C++14** - Polish and convenience: generic lambdas, digit separators, return type deduction
- **C++17** - Practical improvements: optional, string_view, structured bindings, constexpr if
- **C++20** - The next big leap: concepts, ranges, coroutines, modules, spaceship operator
- **C++23** - Refinement: std::print, deducing this, constexpr expansion, multidimensional operator[]

## Projects

| #   | Project                 | Standard | Demonstrates                                                                                                                                                              |
| --- | ----------------------- | -------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 01  | `01_Cpp11_KeyFeatures`  | C++11    | `auto`, range-based `for`, `nullptr`, scoped enums (`enum class`), uniform initialization, lambda expressions, move semantics, smart pointers                             |
| 02  | `02_Cpp14_Improvements` | C++14    | Binary literals (`0b`), digit separators (`'`), generic lambdas (`auto` params), return type deduction, generalized lambda captures, `[[deprecated]]`, `std::make_unique` |
| 03  | `03_Cpp17_Features`     | C++17    | `std::string_view`, `std::optional`, structured bindings, `constexpr if`, CTAD, inline variables, if-with-initializer                                                     |
| 04  | `04_Cpp20_Features`     | C++20    | Concepts, designated initializers, spaceship operator (`<=>`), `consteval`, `std::span`                                                                                   |
| 05  | `05_Cpp23_Features`     | C++23    | `std::print`, `std::to_underlying`, constexpr math, `if consteval`, deducing this, multidimensional `operator[]`                                                          |

## Build Instructions

Open `Appendix_B_CppUpdates.sln` in Visual Studio 2022.

- Projects 01–04 are configured for **C++20** (`/std:c++20`).
- Project 05 is configured for **C++ Latest** (`/std:c++latest`) to enable C++23 features.
- All projects target **v143** (Visual Studio 2022 toolset).

Set any project as the startup project and press **F5** (or **Ctrl+F5** to run without debugging).

## Notes

- Project 05 uses `#if` preprocessor checks to gracefully handle C++23 features that may not be available on your compiler version. If a feature isn't supported, the program prints a description of what it does instead.
- For the best C++23 experience, use Visual Studio 2022 version 17.7 or later.
- Each `main.cpp` is fully self-contained - no dependencies between projects.
