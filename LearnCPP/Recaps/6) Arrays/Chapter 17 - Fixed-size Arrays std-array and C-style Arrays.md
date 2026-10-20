# Chapter 17 Recap - Fixed-size Arrays: std::array and C-style Arrays

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Use `std::array` for constexpr fixed-size arrays; `std::vector` for everything else.
- Always value-initialize arrays with `{}` to avoid uninitialized elements.
- Pass `std::array` by `const&`; use function templates to generalize over type and length.
- Prefer `std::get<N>()` for compile-time bounds checking when the index is constexpr.
- Avoid C-style arrays in new code - they decay, can't be assigned, and lose length info.
- `sizeof(decayedArray)` returns pointer size, not array size - a common trap.
- Favor `constexpr std::string_view` over C-style string symbolic constants.
- Use `static_assert` to validate array size matches enum count.

### 3 Tiny Examples

1.

```cpp
#include <array>
constexpr std::array<int, 4> a{ 10, 20, 30, 40 };
std::array b{ 1, 2, 3 }; // CTAD: array<int, 3>
```

2.

```cpp
std::array a{ 5, 10, 15 };
int x = a[0];               // no bounds check
int y = a.at(2);             // runtime bounds check
int z = std::get<1>(a);     // compile-time bounds check
```

3.

```cpp
template <typename T, std::size_t N>
void print(const std::array<T, N>& arr) {
    for (const auto& e : arr) std::cout << e << ' ';
}
```

### 3 Common Mistakes

- Skipping compiler warnings.
- Using chapter features without understanding prerequisites.
- Not testing edge cases.

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Fixed-size array** - length known at compile time and immutable; contrasts with dynamic arrays like `std::vector`.
- **`std::array<T, N>`** - standard library fixed-size array with `constexpr` support, bounds-checked access, and no decay.
- **C-style array** - built-in `int arr[N]`; decays to a pointer, no bounds checking, no assignment/comparison.
- **Aggregate** - `std::array` and C-style arrays are aggregates initialized with braced lists.
- **CTAD** - `std::array a{ 1, 2, 3 };` deduces `std::array<int, 3>` (C++17).
- **Array decay** - a C-style array implicitly converts to a pointer to its first element, **losing length info**.
- **Pointer arithmetic** - `ptr + n` moves by `n` objects (not bytes); `ptr[n]` ≡ `*(ptr + n)`.
- **`std::reference_wrapper<T>`** - allows creating arrays of reference-like objects (actual reference arrays are illegal).
- **Brace elision** - aggregate init rules that sometimes allow omitting inner braces; `std::array` of structs often needs double braces.
- **C-style string** - a `char` array terminated by `'\0'`; decays like any C-style array.
- **`std::mdspan`** (C++23) - a multidimensional view over a flat contiguous range.

### Section-by-Section Detail

### 17.1 - Introduction to std::array

- `std::array<int, 5> a{ 1, 2, 3, 4, 5 };` - requires `<array>`, needs both **type** and **compile-time length**
- Value-initialize with `{}` to zero all elements; supports **`constexpr`** fully
- **CTAD** (C++17): `std::array b{ 1, 2, 3 };` deduces `array<int, 3>` - no explicit template arguments needed
- Rule of thumb: use **`std::array`** for `constexpr` fixed-size arrays; **`std::vector`** for everything else

```cpp
#include <array>
constexpr std::array<int, 4> a{ 10, 20, 30, 40 };
std::array b{ 1, 2, 3 }; // CTAD: array<int, 3>
```

→ _See [01_StdArray_Basics](../solutions/Chapter_17_Fixed_Size_Arrays/01_StdArray_Basics/) for declaration and initialization._

**Array Type Comparison:**

| Feature              | `std::array`             | C-style array             | `std::vector`   |
| -------------------- | ------------------------ | ------------------------- | --------------- |
| **Size**             | Fixed, constexpr         | Fixed, constexpr          | Dynamic         |
| **Header**           | `<array>`                | Built-in                  | `<vector>`      |
| **Bounds check**     | `at()` / `std::get<>()`  | None                      | `at()`          |
| **Decay to pointer** | No                       | **Yes** (loses size info) | No              |
| **Assignment**       | Yes (`=`)                | **No**                    | Yes             |
| **`constexpr`**      | Yes (fully)              | Partial                   | No              |
| **Move semantics**   | No (copies all elements) | N/A                       | Yes (O(1) move) |
| **Pass to function** | Preserves size           | Loses size                | Preserves size  |

### 17.2 - std::array length and indexing

- `size()` / `std::size()` return `size_type` (**unsigned**, `constexpr`); `std::ssize()` (C++20) returns **signed**
- Three indexing methods: `operator[]` (no check), `at()` (runtime check, throws `std::out_of_range`), `std::get<N>()` (compile-time check)
- Prefer **`std::get<N>()`** when the index is a **constant expression** - catches out-of-bounds at compile time

```cpp
std::array a{ 5, 10, 15 };
int x = a[0];               // no bounds check
int y = a.at(2);             // runtime bounds check
int z = std::get<1>(a);     // compile-time bounds check
```

→ _See [02_StdArray_Length_And_Indexing](../solutions/Chapter_17_Fixed_Size_Arrays/02_StdArray_Length_And_Indexing/) for all three indexing approaches._

**Indexing Methods Comparison:**

| Method           | Bounds Check                     | Check Time   | Requires          |
| ---------------- | -------------------------------- | ------------ | ----------------- |
| `a[i]`           | None - UB if out-of-bounds       | -            | Any index         |
| `a.at(i)`        | Yes - throws `std::out_of_range` | Runtime      | Any index         |
| `std::get<N>(a)` | Yes - compile error if OOB       | Compile-time | `constexpr` index |

### 17.3 - Passing and returning std::array

- Pass `std::array` by **`const&`** - element type **and** length are part of the type (`std::array<int, 5>` - `std::array<int, 3>`)
- Write generic code with `template <typename T, std::size_t N>` to accept arrays of any type and size
- Returning by value **copies** all elements - unlike `std::vector`, `std::array` has no meaningful **move semantics**
- For large arrays, consider **out parameters** or switching to `std::vector`

```cpp
template <typename T, std::size_t N>
void print(const std::array<T, N>& arr) {
    for (const auto& e : arr) std::cout << e << ' ';
}
```

→ _See [03_Passing_And_Returning_StdArray](../solutions/Chapter_17_Fixed_Size_Arrays/03_Passing_And_Returning_StdArray/) for template-based passing._

### 17.4 - std::array of class types, and brace elision

- `std::array<Point, 3>{{ {1,2}, {3,4}, {5,6} }}` requires **double braces** - outer braces initialize the `std::array`, inner braces initialize the underlying C-style array
- For **scalar types**, **brace elision** lets you use a single set of braces (e.g., `std::array<int, 3>{ 1, 2, 3 }`)
- For arrays of **aggregate class types** (structs), brace elision doesn't always apply → may get compilation errors or incorrect initialization without the extra braces
- Safest approach: always use the **double-brace form** when initializing a `std::array` of structs

```cpp
struct Point { int x; int y; };
std::array<Point, 2> pts{{ {1, 2}, {3, 4} }}; // double braces needed
```

→ _See [04_StdArray_Of_Class_Types](../solutions/Chapter_17_Fixed_Size_Arrays/04_StdArray_Of_Class_Types/) for brace elision demos._

### 17.5 - Arrays of references via std::reference_wrapper

- Arrays of `int&` are **illegal** - C++ does not allow arrays of references
- **`std::reference_wrapper<int>`** wraps a reference - reseat-able and usable in containers; access/modify via `.get()`
- Convenience helpers: `std::ref(x)` creates `std::reference_wrapper<int>`, `std::cref(x)` creates a **const** version

```cpp
int a{ 1 }, b{ 2 };
std::array<std::reference_wrapper<int>, 2> refs{ std::ref(a), std::ref(b) };
refs[0].get() = 99; // modifies a
```

→ _See [05_Arrays_Of_References](../solutions/Chapter_17_Fixed_Size_Arrays/05_Arrays_Of_References/) for reference wrapper usage._

### 17.6 - std::array and enumerations

- A `constexpr std::array` indexed by **enum values** is a clean, efficient way to implement **enum-to-string conversion**
- Use **`static_assert(names.size() == max_colors)`** to catch mismatches at compile time - adding an enumerator without a matching string triggers a build error
- This pattern generalizes beyond strings → map enumerators to default values, function pointers, or configuration records
- C++20 **`consteval`** functions can enforce that the lookup is always performed at **compile time**
- Preferable to a `switch`-based converter - the array form is **data-driven** and easier to keep in sync with the enum

```cpp
enum Color { red, green, blue, max_colors };
constexpr std::array names{ "red", "green", "blue" };
static_assert(names.size() == max_colors);
```

→ _See [06_StdArray_And_Enumerations](../solutions/Chapter_17_Fixed_Size_Arrays/06_StdArray_And_Enumerations/) for enum/array mapping._

### 17.7 - Introduction to C-style arrays

- `int arr[5]{ 1, 2, 3, 4, 5 };` - length must be a **constant expression**; missing initializers are **zero-initialized**
- Accepts both **signed** and **unsigned** indices; omit the length when providing a full initializer list
- C-style arrays do **not** support assignment after declaration
- Use `std::size()` (C++17) or the `sizeof` trick to get the array length

```cpp
int arr[5]{ 1, 2, 3, 4, 5 };
std::cout << arr[2];           // 3
std::cout << std::size(arr);   // 5
```

→ _See [07_CStyle_Arrays_Intro](../solutions/Chapter_17_Fixed_Size_Arrays/07_CStyle_Arrays_Intro/) for C-style array basics._

### 17.8 - C-style array decay

- In most contexts a C-style array **decays** to a pointer to its first element → all **length information is lost**
- This is how they're passed to functions - by address, not by value
- `sizeof(decayedArr)` returns **pointer size** (4 or 8 bytes), not array size - a common source of bugs
- Prefer **`std::array`** or **`std::vector`** to avoid decay-related issues entirely

```cpp
int arr[5]{ 1, 2, 3, 4, 5 };
int* ptr = arr;                      // decay: arr → pointer to first element
std::cout << sizeof(arr);            // 20 (5 × 4 bytes)
std::cout << sizeof(ptr);            // 4 or 8 (pointer size - length lost!)
```

→ _See [08_Array_Decay](../solutions/Chapter_17_Fixed_Size_Arrays/08_Array_Decay/) for decay and sizeof pitfalls._

### 17.9 - Pointer arithmetic and subscripting

- `ptr[n]` is equivalent to `*(ptr + n)` - pointer addition moves by **whole objects**, not bytes
- Arrays are **zero-based** because `arr[0]` is equivalent to `*(arr + 0)` - no offset from the start
- **Iterator-based traversal** uses begin/end pointers; **range-based for loops** use iterators internally

```cpp
int arr[]{ 10, 20, 30 };
int* ptr = arr;
std::cout << *(ptr + 2); // 30 - same as ptr[2] or arr[2]
```

→ _See [09_Pointer_Arithmetic](../solutions/Chapter_17_Fixed_Size_Arrays/09_Pointer_Arithmetic/) for pointer math demos._

### 17.10 - C-style strings

- A **C-style string** is a `char[]` terminated by `'\\0'` - `std::cout` prints until the null terminator
- `std::strlen()` returns the length **excluding** the null terminator
- **Buffer overflow:** reading into a fixed-size `char` array without limiting input → can overwrite adjacent memory
- Avoid non-const C-style string objects - use **`std::string`** or **`std::string_view`** instead

```cpp
const char name[]{ "Alex" };        // null-terminated: 'A','l','e','x','\0'
std::cout << name;                   // prints "Alex"
std::cout << std::strlen(name);      // 4 (excludes '\0')
```

→ _See [10_CStyle_Strings](../solutions/Chapter_17_Fixed_Size_Arrays/10_CStyle_Strings/) for null termination and buffer overflow demos._

### 17.11 - C-style string symbolic constants

- `const char name[]{ "Alex" }` creates a **local array** that copies the string literal into stack memory
- `const char* const color{ "Orange" }` stores only a **pointer** to the literal in **read-only memory** - the compiler may consolidate identical literals (implementation-defined)
- Modifying a string literal through a non-const pointer is **undefined behavior** - always use `const char*` or `const char[]`
- In modern C++, favor **`constexpr std::string_view`** - it carries the length alongside the pointer, avoiding `strlen()` and enabling safe, bounds-aware operations

```cpp
const char name[]{ "Alex" };                  // copies literal into array
const char* const color{ "Orange" };          // points to read-only literal
constexpr std::string_view sv{ "Preferred" }; // modern alternative
```

### 17.12 - Multidimensional C-style Arrays

- `int grid[3][4]` - 3 rows x 4 columns; C++ uses **row-major** order in memory
- Initialize with **nested braces**; traverse with nested loops - outer loop over rows for **cache efficiency**
- Cartesian `{x, y}` maps to array index `[y][x]` - the y-coordinate selects the **row**, the x-coordinate selects the **column**

```cpp
int grid[2][3]{ {1, 2, 3}, {4, 5, 6} };
for (int row{ 0 }; row < 2; ++row)
    for (int col{ 0 }; col < 3; ++col)
        std::cout << grid[row][col] << ' ';
```

→ _See [11_Multidimensional_CStyle_Arrays](../solutions/Chapter_17_Fixed_Size_Arrays/11_Multidimensional_CStyle_Arrays/) for 2D array traversal._

### 17.13 - Multidimensional std::array

- 2D `std::array`: `std::array<std::array<int, 4>, 3>` - verbose and **dimensions appear reversed** (inner = cols, outer = rows)
- Simplify with an **alias template**: `template <typename T, std::size_t Row, std::size_t Col> using Array2d = ...`
- Alternative: **flatten** to 1D and compute indices manually (`row * cols + col`)
- **`std::mdspan`** (C++23) provides a standard multidimensional view over a flat contiguous range

```cpp
template <typename T, std::size_t R, std::size_t C>
using Array2d = std::array<std::array<T, C>, R>;
Array2d<int, 2, 3> grid{{ {1,2,3}, {4,5,6} }};
```

→ _See [12_Multidimensional_StdArray](../solutions/Chapter_17_Fixed_Size_Arrays/12_Multidimensional_StdArray/) for alias templates and flattening._

### Edge Cases and Caveats

❌ Forgetting `{}` initialization:

```cpp
std::array<int, 5> a; // ❌ elements are uninitialized (indeterminate)
```

✅ Always value-initialize:

```cpp
std::array<int, 5> a{}; // ✅ all elements zero-initialized
```

---

❌ `operator[]` with OOB index:

```cpp
std::array<int, 3> a{1, 2, 3};
int x = a[5]; // ❌ silent UB
```

✅ Use `at()` for bounds checking:

```cpp
int x = a.at(5); // ✅ throws std::out_of_range
```

---

❌ Double braces for `std::array` of structs:

```cpp
std::array<Point, 2> a{ {1,2}, {3,4} }; // ❌ may fail or be ambiguous
```

✅ Use double braces:

```cpp
std::array<Point, 2> a{{ {1,2}, {3,4} }}; // ✅
```

---

❌ `sizeof` on a decayed array:

```cpp
void foo(int arr[]) {
    std::cout << sizeof(arr); // ❌ prints pointer size (4 or 8), not array size
}
```

✅ Pass `std::array` or pass the size explicitly alongside the pointer.

---

❌ Trusting array length after passing to a function:

```cpp
void print(int arr[]) { /* length is unknown */ } // ❌ decayed to pointer
```

✅ Use `std::array` or `std::span` to preserve size:

```cpp
void print(std::span<int> s) { /* s.size() works */ } // ✅
```

---

❌ Returning large `std::array` by value:

```cpp
std::array<int, 10000> makeArr() { ... return a; } // ❌ always copies (no move)
```

✅ `std::array` has no move semantics - consider `std::vector` for large dynamic data.

---

❌ Non-constexpr array length:

```cpp
int n = 5;
std::array<int, n> a; // ❌ n must be constexpr
```

✅ Use a compile-time constant:

```cpp
constexpr int n = 5;
std::array<int, n> a; // ✅
```

---

❌ Cartesian vs. array indices:

```cpp
grid[x][y] = val; // ❌ if grid is row-major, this should be grid[y][x]
```

✅ Row-major: `grid[row][col]` - `{x, y}` maps to `[y][x]`.

---

❌ Buffer overflow with C-style string input:

```cpp
char name[10];
std::cin >> name; // ❌ no bounds check - buffer overflow if input > 9 chars
```

✅ Use `std::string` instead:

```cpp
std::string name;
std::cin >> name; // ✅ dynamic sizing
```

---

❌ C-style array assignment after declaration:

```cpp
int arr[3];
arr = { 1, 2, 3 }; // ❌ doesn't compile - arrays are not assignable
```

✅ Initialize at declaration or use `std::array`:

```cpp
int arr[3] = { 1, 2, 3 }; // ✅ initialization
```

---

### Hands-On Code Projects

Practice every concept with the hands-on projects in:

```
solutions/Chapter_17_Fixed_Size_Arrays/
```

| Project                                                                                                           | Concept                                                    |
| ----------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------- |
| [01_StdArray_Basics](../solutions/Chapter_17_Fixed_Size_Arrays/01_StdArray_Basics/)                               | Declaration, initialization, value-init, constexpr, CTAD   |
| [02_StdArray_Length_And_Indexing](../solutions/Chapter_17_Fixed_Size_Arrays/02_StdArray_Length_And_Indexing/)     | `size()`, `ssize()`, `operator[]`, `at()`, `std::get<>()`  |
| [03_Passing_And_Returning_StdArray](../solutions/Chapter_17_Fixed_Size_Arrays/03_Passing_And_Returning_StdArray/) | Pass by const ref, function templates, returning arrays    |
| [04_StdArray_Of_Class_Types](../solutions/Chapter_17_Fixed_Size_Arrays/04_StdArray_Of_Class_Types/)               | Brace elision, double-brace init with structs              |
| [05_Arrays_Of_References](../solutions/Chapter_17_Fixed_Size_Arrays/05_Arrays_Of_References/)                     | `std::reference_wrapper`, `std::ref()`, `std::cref()`      |
| [06_StdArray_And_Enumerations](../solutions/Chapter_17_Fixed_Size_Arrays/06_StdArray_And_Enumerations/)           | Enum-to-string mapping, `static_assert` validation         |
| [07_CStyle_Arrays_Intro](../solutions/Chapter_17_Fixed_Size_Arrays/07_CStyle_Arrays_Intro/)                       | C-style array declaration, initialization, limitations     |
| [08_Array_Decay](../solutions/Chapter_17_Fixed_Size_Arrays/08_Array_Decay/)                                       | Decay to pointer, `sizeof` pitfalls, lost length info      |
| [09_Pointer_Arithmetic](../solutions/Chapter_17_Fixed_Size_Arrays/09_Pointer_Arithmetic/)                         | `ptr[n]`, pointer iteration, zero-based indexing rationale |
| [10_CStyle_Strings](../solutions/Chapter_17_Fixed_Size_Arrays/10_CStyle_Strings/)                                 | Null termination, `std::strlen`, buffer overflow pitfalls  |
| [11_Multidimensional_CStyle_Arrays](../solutions/Chapter_17_Fixed_Size_Arrays/11_Multidimensional_CStyle_Arrays/) | 2D arrays, row-major order, Cartesian ↔ array mapping      |
| [12_Multidimensional_StdArray](../solutions/Chapter_17_Fixed_Size_Arrays/12_Multidimensional_StdArray/)           | 2D `std::array`, alias template, flattening alternative    |

### Quick Reference

| Feature       | Syntax                                | Notes                               |
| ------------- | ------------------------------------- | ----------------------------------- |
| std::array    | `std::array<int, 5> a{ 1,2,3,4,5 };`  | Fixed size, constexpr               |
| CTAD          | `std::array a{ 1,2,3 };`              | Deduces `array<int,3>`              |
| Value init    | `std::array<int, 5> a{};`             | All zeros                           |
| Indexing      | `a[i]` / `a.at(i)` / `std::get<i>(a)` | No check / runtime / compile-time   |
| Size          | `a.size()` / `std::ssize(a)`          | Unsigned / signed                   |
| C-style array | `int arr[5]{ 1,2,3,4,5 };`            | Decays to pointer                   |
| Array decay   | `int* p = arr;`                       | Loses length info                   |
| Pointer math  | `ptr[n]` ≡ `*(ptr + n)`               | Moves by objects, not bytes         |
| C string      | `const char s[]{ "hello" };`          | Null-terminated `char[]`            |
| ref wrapper   | `std::reference_wrapper<int> r{x};`   | Reseat-able reference in containers |
| `std::ref`    | `auto r = std::ref(x);`               | Creates reference_wrapper           |
| 2D C array    | `int grid[3][4];`                     | Row-major                           |
| 2D std::array | `std::array<std::array<int,4>,3>`     | Dims reversed                       |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What happens if you don't brace-initialize a `std::array`?

<details>
<summary>Show answer</summary>

**Direct answer:** If you default-initialize a `std::array` without braces (`std::array<int, 5> a;`), its elements are left uninitialized (containing garbage values) because `std::array` is an aggregate. Always value-initialize with `std::array<int, 5> a{};` to zero all elements.

**Detailed explanation:**

```cpp
std::array<int, 5> a;      // uninitialized - elements contain garbage!
std::array<int, 5> b{};    // value-initialized - all zeros
std::array<int, 5> c{ 1, 2, 3 };  // first 3 set, rest are 0

// CTAD (C++17): compiler deduces type and size
std::array d{ 1, 2, 3, 4, 5 };  // std::array<int, 5>
```

</details>

2. Why do you need double braces when initializing a `std::array` of structs?

<details>
<summary>Show answer</summary>

**Direct answer:** Internally, `std::array` is an aggregate wrapping a C-style array. The outer braces initialize the `std::array` and the inner braces initialize the underlying C array. For scalar types, brace elision lets you use a single set, but for arrays of aggregate class types, the extra braces are often required to avoid ambiguity.

**Detailed explanation:**

```cpp
struct Point { int x; int y; };

// Double braces needed for arrays of structs:
std::array<Point, 3> pts{{ {1,2}, {3,4}, {5,6} }};

// Single braces work for scalars (brace elision):
std::array<int, 3> nums{ 1, 2, 3 };  // OK
```

</details>

3. What does `sizeof` return for a C-style array that has decayed to a pointer?

<details>
<summary>Show answer</summary>

**Direct answer:** It returns the size of the pointer (typically 4 or 8 bytes), not the size of the array. Array decay loses all length information. This is one of the major reasons C-style arrays are error-prone - you can't determine the array length from the pointer alone.

**Detailed explanation:**

```cpp
int arr[10]{};

std::cout << sizeof(arr);   // 40 (10 * 4 bytes) - full array, no decay

void f(int* p)
{
    std::cout << sizeof(p); // 8 (pointer size on 64-bit) - length lost!
}
f(arr);  // arr decays to int*
```

`std::array` solves this: `sizeof(std::array<int, 10>)` always returns `40`, and `.size()` always returns `10`, regardless of context.

</details>

4. Why can't `std::array` be moved efficiently like `std::vector`?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::array` stores elements directly inside the object (on the stack), not on the heap via a pointer. Moving a `std::vector` swaps a pointer - $O(1)$. Moving a `std::array` must copy/move each element individually - $O(n)$ - because there's no heap pointer to transfer.

**Detailed explanation:**

```cpp
std::array<int, 1000> a{ /* ... */ };
auto b = std::move(a);  // still copies 1000 ints - O(n)!

std::vector<int> v(1000);
auto w = std::move(v);  // transfers pointer - O(1)
```

For large fixed-size arrays, consider `std::vector` with `reserve()` if move efficiency matters.

</details>

5. What is `std::span` and how does it solve the array decay problem?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::span` (C++20) is a lightweight, non-owning view over a contiguous sequence of elements. It stores a pointer and a size, so it works with `std::array`, `std::vector`, and C-style arrays without losing length information. Unlike C-style array decay (which loses length), a `std::span` preserves it.

**Detailed explanation:**

```cpp
#include <span>

void print(std::span<const int> s)  // accepts any contiguous container
{
    for (int x : s)
        std::cout << x << ' ';
}

std::array a{ 1, 2, 3 };
std::vector v{ 4, 5, 6 };
int c[]{ 7, 8, 9 };

print(a);  // OK: knows size is 3
print(v);  // OK: knows size is 3
print(c);  // OK: knows size is 3 - no decay!
```

`std::span` is non-owning - it does not manage the lifetime of the data it points to.

</details>

6. Why must the size of `std::array` be a constexpr value?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::array` is a fixed-size container allocated entirely on the stack. The compiler must know the size at compile-time to determine how much stack space to reserve. The size is part of the type - `std::array<int, 5>` and `std::array<int, 3>` are different types. Use `std::vector` when the size is only known at runtime.

**Detailed explanation:**

```cpp
constexpr int n{ 5 };
std::array<int, n> a{};     // OK: n is constexpr

int x{};
std::cin >> x;
// std::array<int, x> b{};  // ERROR: x is not constexpr - use std::vector
std::vector<int> b(x);      // OK: runtime size
```

</details>

7. How do Cartesian coordinates `{x, y}` map to row-major array indices?

<details>
<summary>Show answer</summary>

**Direct answer:** In C++'s row-major order, a 2D array `grid[rows][cols]` maps Cartesian `{x, y}` to `grid[y][x]` - the y-coordinate selects the row, the x-coordinate selects the column. Traversing with the outer loop over rows (first index) is cache-friendly.

**Detailed explanation:**

```cpp
constexpr int rows{ 3 };
constexpr int cols{ 4 };
int grid[rows][cols]{};

// Cartesian (x=2, y=1) → grid[1][2]
grid[1][2] = 42;

// Cache-friendly traversal (row-major):
for (int r{ 0 }; r < rows; ++r)        // outer = rows
    for (int c{ 0 }; c < cols; ++c)     // inner = columns
        std::cout << grid[r][c] << ' ';
```

</details>

8. Why is `std::array` preferred over C-style arrays in modern C++?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::array` doesn't decay to a pointer, knows its own size (`.size()`), supports iterators and range-based `for` loops, is an aggregate that can be passed/returned by value, and works with STL algorithms. C-style arrays decay to pointers (losing length), can't be assigned or returned by value, and require manual length tracking.

**Detailed explanation:**

```cpp
// C-style array problems:
int c[5]{ 1, 2, 3, 4, 5 };
// int c2[5] = c;           // ERROR: can't copy
// Can't return from function by value
// sizeof(c) is unreliable after decay

// std::array advantages:
std::array a{ 1, 2, 3, 4, 5 };
auto a2 = a;                  // OK: copy works
a.size();                     // always 5
std::sort(a.begin(), a.end()); // works with algorithms
```

Use `std::array` for constexpr fixed-size arrays; `std::vector` when the size varies at runtime.

</details>

9. What is the difference between `const char name[]` and `const char* name` for string literals?

<details>
<summary>Show answer</summary>

**Direct answer:** `const char name[]{ "Alex" }` creates a local array that copies the string literal into stack memory. `const char* name{ "Alex" }` stores only a pointer to the string literal, which resides in read-only memory. The array version owns the data; the pointer version does not. In modern C++, prefer `constexpr std::string_view` over both.

**Detailed explanation:**

```cpp
const char arr[]{ "hello" };  // 6 bytes on stack (copy of literal + '\0')
const char* ptr{ "hello" };   // pointer to read-only memory

// arr[0] = 'H';  // OK if not const - modifies the local copy
// ptr[0] = 'H';  // UB: modifying a string literal

// Modern C++:
constexpr std::string_view sv{ "hello" };  // pointer + length, no copies
```

</details>

10. How do you use enum values as array indices safely?

<details>
<summary>Show answer</summary>

**Direct answer:** Use unscoped enumerators (which implicitly convert to integers) as indices, with a trailing `count` enumerator for the array size. Use `static_assert` to verify the array size matches the count. For scoped enums, use `static_cast` or a helper `operator+`.

**Detailed explanation:**

```cpp
enum Color { red, green, blue, max_colors };

constexpr std::array colorNames{ "Red", "Green", "Blue" };
static_assert(colorNames.size() == max_colors);  // catches mismatches at compile-time

std::cout << colorNames[red];  // "Red" - self-documenting index

// Scoped enum requires explicit cast:
enum class Fruit { apple, banana, count };
constexpr std::array fruitNames{ "Apple", "Banana" };
static_assert(fruitNames.size() == static_cast<std::size_t>(Fruit::count));
```

</details>
