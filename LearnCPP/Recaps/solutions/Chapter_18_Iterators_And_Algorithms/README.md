# Chapter 18 - Iterators and Algorithms

## Projects

| #   | Folder                  | Concept                                                                                            |
| --- | ----------------------- | -------------------------------------------------------------------------------------------------- |
| 1   | 01_SelectionSort        | Selection sort algorithm - O(n²) sort by repeatedly finding the smallest unsorted element          |
| 2   | 02_BubbleSort           | Bubble sort with early-termination optimization                                                    |
| 3   | 03_StdSort              | `std::sort` with default and custom comparators (`std::greater`)                                   |
| 4   | 04_Iterators            | Introduction to iterators - `begin()`, `end()`, pointer iterators, range-based for internals       |
| 5   | 05_IteratorInvalidation | Pitfall: modifying a container while iterating causes UB; how to revalidate with `erase()`         |
| 6   | 06_FindAndCount         | `std::find`, `std::find_if`, `std::count`, `std::count_if`                                         |
| 7   | 07_ForEach              | `std::for_each` - guaranteed sequential access and common loop pitfalls it avoids                  |
| 8   | 08_RangesCpp20          | C++20 ranges - pass containers directly to algorithms without `begin()`/`end()`                    |
| 9   | 09_TimingCode           | `std::chrono` - building a Timer class to benchmark sorting algorithms                             |
| 10  | 10_CommonPitfalls       | All major pitfalls: off-by-one, debug benchmarking, missing `&`, past-the-end access, iterator `<` |

All projects compile independently with C++20 (`/std:c++20` on MSVC, `-std=c++20` on GCC/Clang).
