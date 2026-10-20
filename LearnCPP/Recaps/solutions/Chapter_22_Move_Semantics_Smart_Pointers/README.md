# Chapter 22 - Move Semantics and Smart Pointers

This chapter covers smart pointers (RAII wrappers for dynamic memory) and move semantics (efficient resource transfer instead of copying).

## Projects

| #   | Folder                           | Concept                                                     |
| --- | -------------------------------- | ----------------------------------------------------------- |
| 01  | `01_SmartPointerMotivation`      | Why raw pointers leak and how RAII smart pointers fix it    |
| 02  | `02_RvalueReferences`            | R-value references (`&&`), binding rules, and overloading   |
| 03  | `03_MoveConstructor`             | Writing a move constructor that transfers ownership         |
| 04  | `04_MoveAssignment`              | Writing a move assignment operator                          |
| 05  | `05_StdMove`                     | Using `std::move` to invoke move semantics on l-values      |
| 06  | `06_RuleOfFive`                  | Defining all five special member functions correctly        |
| 07  | `07_UniquePtr`                   | `std::unique_ptr` - sole ownership smart pointer            |
| 08  | `08_SharedPtr`                   | `std::shared_ptr` - shared ownership via reference counting |
| 09  | `09_WeakPtr`                     | `std::weak_ptr` - non-owning observer, breaking cycles      |
| 10  | `10_CircularReferenceProblem`    | Demonstrating and solving circular `shared_ptr` references  |
| 11  | `11_MoveSemanticsWithContainers` | Move semantics with STL containers and `noexcept`           |
| 12  | `12_CommonPitfalls`              | Frequent mistakes: double-delete, moved-from access, etc.   |

## Build

Each project is a standalone `main.cpp`. Compile with any C++20 compiler:

```bash
cd 01_SmartPointerMotivation
g++ -std=c++20 -o main main.cpp && ./main
```
