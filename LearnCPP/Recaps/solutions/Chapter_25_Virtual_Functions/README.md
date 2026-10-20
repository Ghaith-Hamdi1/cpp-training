# Chapter 25 - Virtual Functions

This chapter covers virtual functions and runtime polymorphism in C++: how base class pointers/references resolve to derived class overrides at runtime, virtual tables, object slicing, and safe downcasting.

## Projects

| #   | Folder                            | Concept                                                                        |
| --- | --------------------------------- | ------------------------------------------------------------------------------ |
| 01  | `01_PointersReferencesToBase`     | Base pointers/references to derived objects - motivation for virtual functions |
| 02  | `02_VirtualFunctionsPolymorphism` | `virtual` keyword, runtime dispatch through pointers/references                |
| 03  | `03_OverrideAndFinal`             | `override` specifier, `final` specifier, catching signature mismatches         |
| 04  | `04_CovariantReturnTypes`         | Returning a more-derived pointer/reference from an override                    |
| 05  | `05_VirtualDestructors`           | Why base classes need virtual destructors, undefined behavior without them     |
| 06  | `06_EarlyAndLateBinding`          | Compile-time vs. runtime function resolution, function pointers                |
| 07  | `07_VirtualTable`                 | How the vtable and `__vptr` enable dynamic dispatch                            |
| 08  | `08_PureVirtualAbstractClasses`   | Pure virtual functions (`= 0`), abstract base classes                          |
| 09  | `09_InterfaceClasses`             | Classes with only pure virtual functions - defining contracts                  |
| 10  | `10_VirtualBaseClasses`           | Diamond inheritance, `virtual` inheritance, shared base                        |
| 11  | `11_ObjectSlicing`                | Slicing by value, Frankenobjects, prevention techniques                        |
| 12  | `12_DynamicCast`                  | `dynamic_cast` for safe downcasting, `nullptr` checks, `std::bad_cast`         |

## Build

Each subfolder contains a standalone `main.cpp`.  
Compile any project with a C++20 compiler:

```bash
cd 01_PointersReferencesToBase
g++ -std=c++20 -o main main.cpp && ./main
```
