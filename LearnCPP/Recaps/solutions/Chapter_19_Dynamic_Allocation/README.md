# Chapter 19 - Dynamic Allocation

This chapter covers dynamic memory allocation in C++, including `new`/`delete`, dynamic arrays,
destructors, RAII, pointers to pointers, and void pointers.

> **Note:** This chapter is marked as under construction on learncpp.com.

## Projects

| #   | Folder                  | Concept                                                   |
| --- | ----------------------- | --------------------------------------------------------- |
| 01  | `01_NewAndDelete`       | Basic dynamic allocation with `new` and `delete`          |
| 02  | `02_DynamicArrays`      | Dynamically allocating arrays with `new[]` and `delete[]` |
| 03  | `03_DanglingPointers`   | Dangling pointers and how to avoid them                   |
| 04  | `04_MemoryLeaks`        | Common causes of memory leaks                             |
| 05  | `05_Destructors`        | Destructors and automatic cleanup                         |
| 06  | `06_RAII`               | Resource Acquisition Is Initialization pattern            |
| 07  | `07_PointersToPointers` | Pointer to pointer and dynamic 2D arrays                  |
| 08  | `08_VoidPointers`       | Void pointers, casting, and type safety                   |
| 09  | `09_CommonPitfalls`     | Mismatched delete, double delete, and other pitfalls      |

## Build

Each subfolder contains a standalone `main.cpp`. Compile with any C++20 compiler:

```bash
cd 01_NewAndDelete
g++ -std=c++20 -o main main.cpp && ./main
```
