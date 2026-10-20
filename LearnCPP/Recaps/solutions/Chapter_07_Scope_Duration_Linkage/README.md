# Chapter 7 - Scope, Duration, and Linkage

This chapter explores the three fundamental properties of identifiers in C++: **scope** (where a name is accessible), **duration** (when a variable is created/destroyed), and **linkage** (whether declarations across scopes refer to the same entity).

## Projects

| #   | Folder                           | Concept                          | Key Topics                                                              |
| --- | -------------------------------- | -------------------------------- | ----------------------------------------------------------------------- |
| 01  | `01_CompoundStatements`          | Compound Statements (Blocks)     | `{ }` blocks, nesting levels, block as single statement                 |
| 02  | `02_UserDefinedNamespaces`       | User-Defined Namespaces          | Namespace creation, `::` operator, nested namespaces, namespace aliases |
| 03  | `03_LocalVariables`              | Local Variables                  | Block scope, automatic duration, no linkage, limited scope              |
| 04  | `04_GlobalVariables`             | Global Variables                 | File scope, static duration, `g_` prefix, const/constexpr defaults      |
| 05  | `05_VariableShadowing`           | Variable Shadowing (Name Hiding) | Inner hides outer, accessing shadowed globals via `::`                  |
| 06  | `06_InternalLinkage`             | Internal Linkage                 | `static` keyword, `const`/`constexpr` defaults, unnamed namespaces      |
| 07  | `07_ExternalLinkage`             | External Linkage                 | `extern` keyword, forward declarations across files                     |
| 08  | `08_WhyGlobalsAreEvil`           | Why Non-Const Globals Are Evil   | Unpredictable state, debugging difficulty, alternatives                 |
| 09  | `09_InlineFunctionsAndVariables` | Inline Functions & Variables     | Modern `inline` meaning, ODR, header definitions                        |
| 10  | `10_SharingGlobalConstants`      | Sharing Global Constants         | `inline constexpr` in headers (C++17), three approaches compared        |
| 11  | `11_StaticLocalVariables`        | Static Local Variables           | `static` locals, `s_` prefix, ID generators, persistence                |
| 12  | `12_UsingDeclarationsDirectives` | Using Declarations & Directives  | `using` declaration vs directive, pitfalls in headers                   |
| 13  | `13_UnnamedAndInlineNamespaces`  | Unnamed & Inline Namespaces      | Internal linkage via unnamed ns, API versioning via inline ns           |

## Build Notes

- All projects target **C++20** (`/std:c++20` in MSVC, `-std=c++20` in GCC/Clang).
- Projects 06, 07, 09, and 10 contain multiple source/header files - compile all `.cpp` files together.
- Single-file projects: `cl /std:c++20 /EHsc main.cpp` (MSVC) or `g++ -std=c++20 main.cpp` (GCC).
- Multi-file projects: `cl /std:c++20 /EHsc *.cpp` (MSVC) or `g++ -std=c++20 *.cpp` (GCC).
