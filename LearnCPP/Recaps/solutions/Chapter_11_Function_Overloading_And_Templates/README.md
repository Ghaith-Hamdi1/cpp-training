# Chapter 11 - Function Overloading and Function Templates

This chapter covers two major C++ features for writing flexible, reusable functions:
**function overloading** and **function templates**.

## Projects

| #   | Folder                                 | Concept                                                      |
| --- | -------------------------------------- | ------------------------------------------------------------ |
| 01  | `01_IntroToFunctionOverloading`        | Basic function overloading - same name, different parameters |
| 02  | `02_OverloadDifferentiation`           | What differentiates overloads (and what doesn't)             |
| 03  | `03_OverloadResolution`                | Compiler resolution priority: exact → promotion → conversion |
| 04  | `04_AmbiguousMatches`                  | Ambiguous matches and how to resolve them                    |
| 05  | `05_DeletedFunctions`                  | Using `= delete` to forbid specific overloads                |
| 06  | `06_DefaultArguments`                  | Default argument rules, placement, and pitfalls              |
| 07  | `07_FunctionTemplates`                 | Basic function templates with type parameters                |
| 08  | `08_TemplateInstantiationAndDeduction` | Implicit instantiation and template argument deduction       |
| 09  | `09_MultipleTemplateTypes`             | Multiple template type parameters and `auto` return          |
| 10  | `10_NonTypeTemplateParameters`         | Compile-time value parameters in templates                   |
| 11  | `11_AbbreviatedFunctionTemplates`      | C++20 abbreviated function templates (`auto` params)         |
| 12  | `12_CommonPitfalls`                    | Common mistakes and how to avoid them                        |

## Build

Each subfolder contains a standalone `main.cpp`.  
Compile any project with C++20:

```bash
g++ -std=c++20 -Wall -Wextra -o main main.cpp
```
