# C++ in Motion: posting order

The carousel numbers (`cpp-in-motion-NN`) rank the carousels from easiest to hardest. Each carousel lives in the folder of its topic. The posting order below differs slightly, so that every post only relies on ideas an earlier post already taught.

**Cadence:** Tuesday and Thursday, about 08:30 Tunisia time (UTC+1). Post the repo link as the first comment and reply to every comment in the first hour. 17 posts take about 9 weeks.

| Post | Date | Folder | Topic |
|---|---|---|---|
| 1 | Tue 3 Nov | `pointers-and-memory/cpp-in-motion-07` | `std::vector` on the stack and the heap |
| 2 | Thu 5 Nov | `pointers-and-memory/cpp-in-motion-01` | Dereferencing a pointer |
| 3 | Tue 10 Nov | `pointers-and-memory/cpp-in-motion-02` | Pointer or object? |
| 4 | Thu 12 Nov | `lambdas/cpp-in-motion-03` | Lambdas |
| 5 | Tue 17 Nov | `classes-and-polymorphism/cpp-in-motion-04` | Why virtual functions |
| 6 | Thu 19 Nov | `classes-and-polymorphism/cpp-in-motion-11` | Object slicing |
| 7 | Tue 24 Nov | `classes-and-polymorphism/cpp-in-motion-12` | Virtual destructors |
| 8 | Thu 26 Nov | `classes-and-polymorphism/cpp-in-motion-09` | Public, protected and private inheritance |
| 9 | Tue 1 Dec | `const-and-types/cpp-in-motion-08` | `const` and pointers |
| 10 | Thu 3 Dec | `const-and-types/cpp-in-motion-05` | `const` after a member function |
| 11 | Tue 8 Dec | `const-and-types/cpp-in-motion-06` | `constexpr` vs `const` |
| 12 | Thu 10 Dec | `const-and-types/cpp-in-motion-10` | The four casts |
| 13 | Tue 15 Dec | `copying-and-move-semantics/cpp-in-motion-13` | The Rule of Three |
| 14 | Thu 17 Dec | `copying-and-move-semantics/cpp-in-motion-15` | `T&&` (rvalue references) |
| 15 | Tue 22 Dec | `copying-and-move-semantics/cpp-in-motion-14` | When to use `std::move` |
| 16 | Thu 24 Dec | `copying-and-move-semantics/cpp-in-motion-16` | Value categories |
| 17 | Tue 29 Dec | `copying-and-move-semantics/cpp-in-motion-17` | Forwarding references |

## Why this order

- **Start with the vector post (07).** It is the most visual one and the one the series was built around. It teaches the stack and heap that the next posts rely on.
- **Pointers before objects with identity:** 01 and 02 come right after, then lambdas (03) as a lighter change of pace.
- **Virtual functions as a block (05, 06, 07):** slicing and virtual destructors both build on "why virtual", and inheritance access (08) follows once the base/derived idea is familiar.
- **`const` as a block (09, 10, 11):** `const` and pointers first, then `const` members, then `constexpr`.
- **Casts (12) after inheritance and virtual functions**, because `dynamic_cast` needs both.
- **Move semantics last and in dependency order:** the Rule of Three (13), then `T&&` (14), then when to use `std::move` (15), then value categories (16), and forwarding references (17) as the finale.

## Notes

- 22 and 24 December fall around the holidays. Swap or shift them if engagement drops.
- Carousels 14 and 15 (`std::move` and `T&&`) overlap, and so do 04 and 12 (virtual functions and virtual destructors). They could be merged, but I have not merged anything.
- Carousel 07 uses the older animated source (`index.html?flip` rebuilds its PDF); the others are static 6-slide pages (13 has 7).
