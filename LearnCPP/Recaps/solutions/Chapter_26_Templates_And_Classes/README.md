# Chapter 26 - Templates and Classes

This chapter extends templates from functions to classes, covering generic container classes, non-type template parameters, full and partial specialization, and handling pointer types.

## Projects

| #   | Folder                              | Concept                                                                                    |
| --- | ----------------------------------- | ------------------------------------------------------------------------------------------ |
| 1   | `01_BasicClassTemplate`             | Defining a template class (`Array<T>`) with member functions inside the class body         |
| 2   | `02_MemberFunctionsOutsideClass`    | Correctly defining template member functions outside the class (common pitfalls)           |
| 3   | `03_NonTypeTemplateParameters`      | Using constexpr non-type template parameters (`StaticArray<T, int size>`)                  |
| 4   | `04_FunctionTemplateSpecialization` | Full function template specialization vs. non-template overloads                           |
| 5   | `05_MemberFunctionSpecialization`   | Specializing a single member function without rewriting the entire class                   |
| 6   | `06_ClassTemplateSpecialization`    | Full class template specialization (`Storage8<bool>` bit-packing example)                  |
| 7   | `07_PartialTemplateSpecialization`  | Partial template specialization for classes (fixing one parameter, keeping others generic) |
| 8   | `08_PartialSpecForPointers`         | Partial specialization for pointer types - avoiding dangling-pointer bugs                  |
| 9   | `09_StaticAssertTypeTraits`         | Using `static_assert` + `std::is_pointer_v` to prevent unwanted instantiations             |
| 10  | `10_BaseClassPatternPartialSpec`    | Base-class pattern to avoid code duplication when partially specializing                   |

## Build

Each subfolder contains a standalone `main.cpp`. Compile any project with:

```bash
g++ -std=c++20 -o main main.cpp
```
