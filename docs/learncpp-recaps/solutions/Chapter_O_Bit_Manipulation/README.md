# Chapter O - Bit Manipulation

## Projects

| #   | Folder                         | Topic                                                                                         |
| --- | ------------------------------ | --------------------------------------------------------------------------------------------- |
| 1   | `01_BitFlagsWithBitset`        | Using `std::bitset` for individual bit manipulation (`test`, `set`, `reset`, `flip`, `count`) |
| 2   | `02_BitwiseOperators`          | The six bitwise operators: `<<`, `>>`, `~`, `&`, `\|`, `^` and their assignment variants      |
| 3   | `03_BitMasks`                  | Defining bit masks and the four essential mask operations (test, set, reset, flip)            |
| 4   | `04_BitFlagsRealWorld`         | Real-world use case: passing multiple options to a function via bit flags                     |
| 5   | `05_BinaryDecimalConversion`   | Converting between binary and decimal, and two's complement for signed integers               |
| 6   | `06_IntegralPromotionPitfalls` | How integral promotion affects `~` and `<<` on narrow types, and how to fix it                |
| 7   | `07_CommonPitfalls`            | Logical vs bitwise operators, signed operand issues, off-by-one bit positions, shift loss     |

## Build

Each subfolder contains a standalone `main.cpp` compilable with any C++20 compiler:

```bash
cd 01_BitFlagsWithBitset
g++ -std=c++20 -o main main.cpp && ./main
```
