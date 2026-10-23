# Chapter 10 - Type Conversion, Type Aliases, and Type Deduction

This chapter covers how C++ converts values between types (implicitly and explicitly), type aliases, and type deduction with `auto`.

## Projects

| #   | Folder                      | Concept                                                            |
| --- | --------------------------- | ------------------------------------------------------------------ |
| 01  | `01_ImplicitTypeConversion` | Automatic conversions performed by the compiler                    |
| 02  | `02_NumericPromotion`       | Value-preserving widening of narrow types to `int`/`double`        |
| 03  | `03_NumericConversions`     | Non-promotion conversions: value-preserving, reinterpretive, lossy |
| 04  | `04_NarrowingConversions`   | Narrowing conversions and brace-init protection                    |
| 05  | `05_ArithmeticConversions`  | Usual arithmetic conversion rules for binary operators             |
| 06  | `06_StaticCast`             | `static_cast` for safe explicit type conversion                    |
| 07  | `07_CStyleCastDangers`      | Why C-style casts are dangerous compared to `static_cast`          |
| 08  | `08_TypeAliases`            | `using` aliases and `typedef`                                      |
| 09  | `09_AutoTypeDeduction`      | `auto` keyword for variable type deduction                         |
| 10  | `10_AutoReturnTypes`        | `auto` return types and trailing return syntax                     |
| 11  | `11_SignedUnsignedMixing`   | Pitfall: unexpected results mixing signed and unsigned             |
| 12  | `12_CommonPitfalls`         | Integer division, const dropping, string literal types             |

## Build

Each subfolder contains a standalone `main.cpp`. Compile with any C++20 compiler:

```bash
g++ -std=c++20 -Wall -Wextra -o program main.cpp
```
