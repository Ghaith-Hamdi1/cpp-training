# Chapter 12 - Compound Types: References and Pointers

This chapter covers lvalue references, pointers, const interactions, parameter passing strategies,
return by reference, type deduction, and `std::optional`.

## Projects

| #   | Folder                             | Topic                                                         |
| --- | ---------------------------------- | ------------------------------------------------------------- |
| 01  | `01_ValueCategories`               | Lvalues vs rvalues and implicit conversions                   |
| 02  | `02_LvalueReferences`              | Basic lvalue references - aliases for existing objects        |
| 03  | `03_ReferencesToConst`             | `const&` binding rules and lifetime extension of temporaries  |
| 04  | `04_PassByReference`               | Pass by non-const lvalue reference                            |
| 05  | `05_PassByConstReference`          | Pass by `const&` - the default for class types                |
| 06  | `06_PointersBasics`                | Pointers, address-of (`&`), and dereference (`*`)             |
| 07  | `07_NullPointers`                  | `nullptr`, null checks, and undefined behavior                |
| 08  | `08_PointersAndConst`              | Pointer to const, const pointer, and both                     |
| 09  | `09_PassByAddress`                 | Passing pointers to functions, null-checking                  |
| 10  | `10_ReturnByReference`             | Returning references safely, dangling reference pitfalls      |
| 11  | `11_DanglingReferencesAndPointers` | Identifying and avoiding dangling references and pointers     |
| 12  | `12_InOutParameters`               | In, out, and in-out parameter patterns                        |
| 13  | `13_TypeDeductionPointersRefs`     | `auto` behavior with pointers, references, and const          |
| 14  | `14_StdOptional`                   | `std::optional` as a modern alternative to sentinels and null |

## Build

Each subfolder contains a standalone `main.cpp`. Compile any project with:

```
cl /std:c++20 /EHsc /W4 main.cpp        # MSVC
g++ -std=c++20 -Wall -Wextra main.cpp    # GCC / MinGW
clang++ -std=c++20 -Wall -Wextra main.cpp # Clang
```
