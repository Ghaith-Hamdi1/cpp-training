# Chapter 14 - Introduction to Classes

This chapter covers the core building blocks of object-oriented programming in C++: classes, access control, constructors, encapsulation, and related concepts.

## Projects

| #   | Folder                                 | Concept                                                                          |
| --- | -------------------------------------- | -------------------------------------------------------------------------------- |
| 01  | `01_ClassVsStruct`                     | Difference between `class` and `struct`, default access levels                   |
| 02  | `02_MemberFunctions`                   | Defining and calling member functions, implicit object                           |
| 03  | `03_ConstObjectsAndMemberFunctions`    | Const objects, const member functions                                            |
| 04  | `04_AccessSpecifiers`                  | `public`, `private`, `protected` access specifiers                               |
| 05  | `05_EncapsulationAndDataHiding`        | Encapsulation, getters, setters, data hiding benefits                            |
| 06  | `06_ReturningReferencesToMembers`      | Returning const/non-const references to data members, dangling reference pitfall |
| 07  | `07_ConstructorsBasics`                | Introduction to constructors, initialization semantics                           |
| 08  | `08_MemberInitializerList`             | Member initializer lists, initialization order pitfall                           |
| 09  | `09_DefaultConstructors`               | Default constructors, `= default`, implicit generation                           |
| 10  | `10_DelegatingConstructors`            | Delegating constructors, reducing redundancy                                     |
| 11  | `11_CopyConstructors`                  | Copy constructors, implicit copy, `= delete` to prevent copies                   |
| 12  | `12_CopyElision`                       | Copy elision, mandatory elision since C++17                                      |
| 13  | `13_TemporaryObjects`                  | Temporary (unnamed) class objects                                                |
| 14  | `14_ConvertingConstructorsAndExplicit` | Converting constructors, `explicit` keyword                                      |
| 15  | `15_ConstexprClasses`                  | Constexpr constructors and member functions, compile-time objects                |

## How to Build

Each subfolder contains a single `main.cpp`. Compile with any C++20 compiler:

```bash
# MSVC
cl /std:c++20 /EHsc main.cpp

# GCC / MinGW
g++ -std=c++20 -o main main.cpp

# Clang
clang++ -std=c++20 -o main main.cpp
```
