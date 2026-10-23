# Chapter 21 - Operator Overloading

This chapter covers how to overload operators in C++ so they work with your own class types, including the three approaches (friend, normal, member), specific operator categories, shallow vs. deep copying, and how operator overloading interacts with function templates.

## Projects

| #   | Folder                           | Concept                                                                       |
| --- | -------------------------------- | ----------------------------------------------------------------------------- |
| 01  | `01_OperatorOverloadingBasics`   | Introduction to operator overloading - rules, restrictions, and first example |
| 02  | `02_FriendFunctionOverloading`   | Overloading arithmetic operators (+, -, \*, /) using friend functions         |
| 03  | `03_NormalFunctionOverloading`   | Overloading operators as normal (non-friend, non-member) functions            |
| 04  | `04_IOOperatorOverloading`       | Overloading `operator<<` and `operator>>` with transactional input            |
| 05  | `05_MemberFunctionOverloading`   | Overloading operators as member functions (+=, -=, etc.)                      |
| 06  | `06_UnaryOperatorOverloading`    | Overloading unary operators (+, -, !)                                         |
| 07  | `07_ComparisonOperators`         | Overloading ==, !=, <, >, <=, >= and C++20 spaceship operator                 |
| 08  | `08_IncrementDecrementOperators` | Prefix vs. postfix overloading of ++ and --                                   |
| 09  | `09_SubscriptOperator`           | Overloading operator[] with const/non-const versions                          |
| 10  | `10_FunctionCallOperator`        | Overloading operator() - functors and stateful callable objects               |
| 11  | `11_TypecastOverloading`         | User-defined type conversions and the `explicit` keyword                      |
| 12  | `12_CopyAssignmentOperator`      | Overloading operator= with self-assignment guard                              |
| 13  | `13_ShallowVsDeepCopy`           | Shallow vs. deep copying, Rule of Three, dangling pointer pitfalls            |
| 14  | `14_OperatorsAndTemplates`       | Enabling classes in function templates via operator overloads                 |

## Build Instructions

Each subfolder contains a single `main.cpp` that compiles independently with C++20:

```bash
cd 01_OperatorOverloadingBasics
g++ -std=c++20 -o main main.cpp && ./main
```

Or use MSVC:

```cmd
cl /std:c++20 /EHsc main.cpp
```
