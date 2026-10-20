# Chapter 23 - Object Relationships

This chapter explores how objects relate to one another in C++, covering four relationship types
(composition, aggregation, association, dependency), container classes, and `std::initializer_list`.

## Projects

| #   | Folder                                   | Concept                                                                                   |
| --- | ---------------------------------------- | ----------------------------------------------------------------------------------------- |
| 01  | `01_Composition`                         | Composition ("part-of") - whole owns and manages the lifetime of its parts                |
| 02  | `02_Aggregation`                         | Aggregation ("has-a") - parts can belong to multiple objects, lifetime managed externally |
| 03  | `03_ReferenceWrapper`                    | Using `std::reference_wrapper` to store references in standard containers                 |
| 04  | `04_UnidirectionalAssociation`           | Unidirectional association ("uses-a") between unrelated objects                           |
| 05  | `05_BidirectionalAssociation`            | Bidirectional association - both objects know about each other (Doctor ↔ Patient)         |
| 06  | `06_ReflexiveAssociation`                | Reflexive association - object relates to another object of the same type                 |
| 07  | `07_Dependency`                          | Dependency ("depends-on") - weakest relationship, temporary usage                         |
| 08  | `08_ContainerClass`                      | Building a container class (IntArray) with dynamic memory management                      |
| 09  | `09_InitializerList`                     | Using `std::initializer_list` for brace-enclosed initialization of custom classes         |
| 10  | `10_Pitfalls_ShallowCopy_BracesVsParens` | Common pitfalls: shallow copy, `{}` vs `()`, self-assignment checks                       |

## Build

Each subfolder contains a standalone `main.cpp`. Compile with any C++20 compiler:

```bash
cd 01_Composition
g++ -std=c++20 -o main main.cpp && ./main
```
