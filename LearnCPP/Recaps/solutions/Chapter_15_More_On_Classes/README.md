# Chapter 15 - More on Classes

This chapter explores deeper class mechanics in C++: the hidden `this` pointer, method chaining,
nested types, destructors, class templates with member functions, static members, friend access,
ref qualifiers, and composition.

## Projects

| #   | Folder                         | Topic                                                                            |
| --- | ------------------------------ | -------------------------------------------------------------------------------- |
| 01  | `01_ThisPointer`               | The hidden `this` pointer - implicit parameter, explicit usage, disambiguation   |
| 02  | `02_MethodChaining`            | Returning `*this` by reference to enable fluent-style method chaining            |
| 03  | `03_NestedTypes`               | Nested enums, type aliases, and classes defined inside a class                   |
| 04  | `04_Destructors`               | Destructor basics, automatic cleanup, and the `std::exit()` pitfall              |
| 05  | `05_ClassTemplatesWithMembers` | Class templates with member functions, external definitions, injected class name |
| 06  | `06_StaticMemberVariables`     | `static`, `static inline`, and `static constexpr` member variables               |
| 07  | `07_StaticMemberFunctions`     | Static member functions, no `this` pointer, pure static classes                  |
| 08  | `08_FriendFunctions`           | `friend` non-member functions granted private access                             |
| 09  | `09_FriendClasses`             | Friend classes and friend member functions; non-reciprocal, non-transitive       |
| 10  | `10_RefQualifiers`             | Overloading member functions for lvalue (`&`) vs rvalue (`&&`) objects           |
| 11  | `11_Composition`               | Classes containing classes - modeling "has-a" relationships                      |
| 12  | `12_CommonPitfalls`            | Comprehensive demo of frequent mistakes and their fixes                          |

## Build Instructions

Each subfolder contains a standalone `main.cpp`.  
Compile any project with a C++20-capable compiler:

```bash
# GCC / MinGW
g++ -std=c++20 -Wall -Wextra -o main main.cpp

# MSVC (Developer Command Prompt)
cl /std:c++20 /EHsc /W4 main.cpp
```
