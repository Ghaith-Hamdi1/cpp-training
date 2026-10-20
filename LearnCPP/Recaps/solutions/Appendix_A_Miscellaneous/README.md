# Appendix A - Miscellaneous Subjects: Solutions

This folder contains standalone C++20 projects illustrating the key concepts, pitfalls, and best practices from **Appendix A** of _learncpp.com_.

| #   | Folder                        | Concept                                                   |
| --- | ----------------------------- | --------------------------------------------------------- |
| 1   | `01_StaticVsDynamicLibraries` | Static libraries, dynamic libraries, and import libraries |
| 2   | `02_TransitiveIncludes`       | Why relying on transitive includes is dangerous           |
| 3   | `03_UsingDirectivePitfalls`   | Why `using namespace std;` causes problems                |
| 4   | `04_CTAD`                     | Class Template Argument Deduction (C++17/20)              |
| 5   | `05_UndefinedBehavior`        | Undefined behavior examples and why it's never safe       |
| 6   | `06_ConstexprBestPractices`   | Using `constexpr` proactively for compile-time evaluation |
| 7   | `07_OperandEvaluationOrder`   | Unspecified operand evaluation order pitfalls             |
| 8   | `08_CommonMistakes`           | Paired headers, const by-value, omitting return, and more |

## How to Build

Each subfolder contains a single `main.cpp`. Compile with any C++20 compiler:

```bash
# GCC / MinGW
g++ -std=c++20 -o main main.cpp

# MSVC (Developer Command Prompt)
cl /std:c++20 /EHsc main.cpp
```
