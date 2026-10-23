# Chapter 16 Recap - Dynamic Arrays: std::vector

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- `{ n }` invokes the **list constructor** (one element); `( n )` invokes the **length constructor** (n zeros).
- Pass `std::vector` by `const&`; return by value - move semantics makes this efficient.
- `operator[]` does **no bounds checking** - prefer range-based for loops or `at()`.
- Favor **range-based for loops** over index-based when you don't need the index.
- `reserve()` pre-allocates capacity without creating elements; `resize()` changes length.
- Reallocation is expensive - minimize it by reserving capacity when the approximate size is known.
- Use `std::ssize()` (C++20) or `static_cast` for signed sizes when needed.
- `std::vector` is not `constexpr` - use `std::array` for compile-time arrays.

### 3 Tiny Examples

1.

```cpp
#include <vector>
std::vector<int> scores{ 90, 85, 72 }; // dynamic array of 3 ints
std::cout << scores[1]; // 85
```

2.

```cpp
std::vector<int> list{ 5 };  // 1 element with value 5
std::vector<int> five( 5 );  // 5 elements, all zero
std::vector v{ 1, 2, 3 };    // CTAD: vector<int>
```

3.

```cpp
std::vector v{ 10, 20, 30 };
auto len = std::ssize(v);  // signed size (C++20)
int x = v.at(5);           // throws std::out_of_range
```

### 3 Common Mistakes

- Skipping compiler warnings.
- Using chapter features without understanding prerequisites.
- Not testing edge cases.

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Container** - a data type that stores a collection of unnamed elements (e.g., `std::string`, `std::vector`).
- **Array** - a container that stores elements **contiguously** in memory, enabling fast random access via indices.
- **`std::vector<T>`** - a dynamic (resizable) array defined in `<vector>` as a class template.
- **List constructor** - `std::vector<int> v{ 1, 2, 3 }` - initializes from a `std::initializer_list`.
- **Length constructor** - `std::vector<int> v( n )` - creates `n` value-initialized elements.
- **CTAD** - Class Template Argument Deduction (C++17) lets the compiler deduce element type from initializers.
- **`size_type`** - a nested unsigned typedef (usually `std::size_t`) for lengths and indices.
- **`std::ssize()`** (C++20) - returns a **signed** size, avoiding signed/unsigned mismatch.
- **Length vs. capacity** - length is elements in use; capacity is total allocated storage.
- **Reallocation** - acquiring new, larger memory when capacity is exceeded (copies all elements - expensive).
- **Move semantics** - transferring ownership of internal memory instead of copying; makes return-by-value cheap.
- **Range-based for loop** - `for (auto& e : arr)` traverses without explicit indexing.
- **Stack operations** - `push_back()`, `pop_back()`, `back()` - LIFO behavior on a vector.
- **`std::vector<bool>`** - a bit-packed specialization that is **not** a true container; avoid it.

### Section-by-Section Detail

### 16.1 - Introduction to containers and arrays

- Individual variables don't scale - managing many values requires **containers** that store collections of unnamed elements
- **Arrays** store elements **contiguously** in memory, enabling fast O(1) random access by index
- C++ provides three array types: **C-style arrays** (built-in, unsafe), **`std::array`** (fixed-size, `constexpr`), and **`std::vector`** (dynamic, resizable)

```cpp
#include <vector>
std::vector<int> scores{ 90, 85, 72 }; // dynamic array of 3 ints
std::cout << scores[1]; // 85
```

→ _See [01_IntroToVector](../solutions/Chapter_16_Dynamic_Arrays_Vector/01_IntroToVector) for basic vector creation._

### 16.2 - Introduction to std::vector and list constructors

- Declare with `std::vector<int> v{ 1, 2, 3 };` (**list constructor**) or `std::vector<int> v( 5 );` (**length constructor** - five zeros)
- **Critical gotcha:** `{ 5 }` creates a 1-element vector containing 5; `( 5 )` creates a 5-element vector of zeros
- **CTAD** (C++17): `std::vector v{ 1, 2, 3 };` deduces `vector<int>` - no explicit template argument needed
- Access elements with `operator[]` - zero-based indexing, **no bounds check**

```cpp
std::vector<int> list{ 5 };  // 1 element with value 5
std::vector<int> five( 5 );  // 5 elements, all zero
std::vector v{ 1, 2, 3 };    // CTAD: vector<int>
```

→ _See [01_IntroToVector](../solutions/Chapter_16_Dynamic_Arrays_Vector/01_IntroToVector) and [02_ListVsLengthConstructor](../solutions/Chapter_16_Dynamic_Arrays_Vector/02_ListVsLengthConstructor) for the initialization distinction._

### 16.3 - std::vector and the unsigned length and subscript problem

- `size()` returns `size_type` (**unsigned**); `std::ssize()` (C++20) returns a **signed** type - avoids signed/unsigned mismatch
- `operator[]` performs **no bounds checking** - out-of-bounds access is **undefined behavior**
- `at()` performs **runtime bounds checking** and throws `std::out_of_range` on invalid indices
- Workarounds for signed/unsigned indexing warnings include `static_cast`, `constexpr` indices, `data()` pointer, and **range-based for loops**

```cpp
std::vector v{ 10, 20, 30 };
auto len = std::ssize(v);  // signed size (C++20)
int x = v.at(5);           // throws std::out_of_range
```

→ _See [03_SubscriptAndBoundsChecking](../solutions/Chapter_16_Dynamic_Arrays_Vector/03_SubscriptAndBoundsChecking) and [04_LengthAndCapacity](../solutions/Chapter_16_Dynamic_Arrays_Vector/04_LengthAndCapacity)._

### 16.4 - Passing std::vector

- Pass `std::vector` by **`const&`** to avoid expensive O(n) copies - vectors can hold thousands of elements
- For generic code, use a **function template**: `template <typename T> void f(const std::vector<T>& v)`
- C++20 **abbreviated function templates** (`void f(const auto& v)`) are shorter but accept any type - less type-safe
- Pass by **non-const reference** (`std::vector<T>&`) only when the function needs to modify the vector

```cpp
template <typename T>
void print(const std::vector<T>& v) {
    for (const auto& e : v) std::cout << e << ' ';
}
```

→ _See [05_PassingVectors](../solutions/Chapter_16_Dynamic_Arrays_Vector/05_PassingVectors) for pass-by-reference patterns._

### 16.5 - Returning std::vector, and an introduction to move semantics

- Returning `std::vector` by value is efficient - **move semantics** transfers internal memory ownership (pointer, size, capacity) instead of copying all elements
- A move is essentially three pointer-sized assignments → O(1) regardless of vector size
- The move happens automatically when the source is an **rvalue** (temporary or named local in a `return` statement) and the type has a **move constructor**
- After a move, the source vector is left in a **valid-but-unspecified state** (typically empty)
- General rule: **pass by `const&`**, **return by value** - avoids copies on input, leverages move semantics on output

```cpp
std::vector<int> generate() {
    std::vector<int> v{ 1, 2, 3 };
    return v; // move semantics - no expensive copy
}
```

→ _See [06_ReturningVectors](../solutions/Chapter_16_Dynamic_Arrays_Vector/06_ReturningVectors) for move semantics in action._

### 16.6 - Arrays and loops

- Index-based `for` loops traverse arrays: `for (std::size_t i{0}; i < v.size(); ++i)`
- **Templates + arrays + loops** enable scalable, type-generic code for aggregates, searches, and transforms
- **Watch for off-by-one:** use `< size()`, not `<= size()` - the latter causes out-of-bounds access on the last iteration

```cpp
std::vector v{ 3, 7, 1, 9 };
for (std::size_t i{ 0 }; i < v.size(); ++i)
    std::cout << v[i] << ' ';
```

→ _See [07_IndexBasedLoops](../solutions/Chapter_16_Dynamic_Arrays_Vector/07_IndexBasedLoops) for traversal patterns and pitfalls._

### 16.7 - Arrays, loops, and sign challenge solutions

- The core tension: `std::vector::size()` returns **unsigned** `std::size_t`, but **signed** integers are preferred for general arithmetic
- Workarounds include: `std::size_t` indices directly, signed indices with `static_cast`, `std::ssize()` (C++20), or `data()` with signed `int`
- Each approach trades off between **verbosity**, **safety**, and **language version requirements**
- Best solution in most cases - **avoid manual indexing entirely** by using **range-based for loops** or **iterator-based algorithms**, which sidestep the signed/unsigned issue completely

```cpp
std::vector v{ 10, 20, 30 };
for (const auto& e : v)       // no index - no sign issues
    std::cout << e << ' ';
```

### 16.8 - Range-based for loops (for-each)

- `for (auto e : arr)` **copies** each element; `for (auto& e : arr)` gives a **modifiable reference**; `for (const auto& e : arr)` gives a **read-only reference**
- Works with any type that has `begin()`/`end()` - no index variable needed → cleaner and safer
- Reverse traversal: `for (auto& e : arr | std::views::reverse)` (C++20)

```cpp
std::vector v{ 1, 2, 3 };
for (const auto& e : v) std::cout << e << ' '; // read-only
for (auto& e : v) e *= 2;                       // modify each
```

→ _See [08_RangeBasedForLoops](../solutions/Chapter_16_Dynamic_Arrays_Vector/08_RangeBasedForLoops) for all loop variants._

### 16.9 - Array indexing and length using enumerators

- **Unscoped enumerators** serve as meaningful array indices - `scores[Students::alice]` is self-documenting compared to `scores[0]`
- A trailing **count enumerator** (e.g., `max_students`) automatically equals the number of preceding values → perfect for array sizing
- Use **`static_assert`** to validate that array size matches the count enumerator - catches mismatches at **compile time**
- **Scoped enums** (`enum class`) don't implicitly convert to integers → need `static_cast` or a custom `operator+` overload
- Common use cases: **lookup tables**, configuration arrays, and any situation where each array slot has a domain-specific meaning

```cpp
enum Students { alice, bob, max_students };
std::vector<int> scores(max_students);
scores[alice] = 95;
scores[bob]   = 88;
```

→ _See [11_EnumeratorIndices](../solutions/Chapter_16_Dynamic_Arrays_Vector/11_EnumeratorIndices) for enumerator-indexed arrays._

### 16.10 - std::vector resizing and capacity

- `resize(n)` changes **length** (and capacity if `n > capacity`); `reserve(n)` changes only **capacity** - no element creation
- **Reallocation** copies all elements → expensive; use `reserve()` to pre-allocate when approximate size is known
- `shrink_to_fit()` requests capacity reduction - **non-binding** (implementation may ignore it)
- Valid indices are `[0, length)`, **not** `[0, capacity)` - accessing reserved-but-uninitialized slots is UB

```cpp
std::vector<int> v;
v.reserve(100);              // capacity >= 100, length still 0
v.resize(10);                // length = 10, elements value-initialized
v.shrink_to_fit();           // request capacity = length
```

→ _See [09_ResizingAndCapacity](../solutions/Chapter_16_Dynamic_Arrays_Vector/09_ResizingAndCapacity) for resize vs. reserve demos._

**Capacity Management Operations:**

| Operation         | Changes Length? | Changes Capacity?        | Creates/Destroys Elements?          | Use Case                        |
| ----------------- | --------------- | ------------------------ | ----------------------------------- | ------------------------------- |
| `resize(n)`       | Yes             | Only if n > capacity     | Yes - value-initializes or destroys | Set exact element count         |
| `reserve(n)`      | No              | Yes (at least n)         | No                                  | Pre-allocate before `push_back` |
| `shrink_to_fit()` | No              | May reduce (non-binding) | No                                  | Release excess memory           |

### 16.11 - std::vector and stack behavior

- `push_back(val)` appends and grows if needed; `emplace_back(args...)` constructs in-place - prefer for complex objects
- `pop_back()` removes the last element - **UB on empty vector**; `back()` accesses the last element
- Use `reserve()` (**not** `resize()`) before stack operations to minimize reallocations without creating unwanted elements

```cpp
std::vector<int> stack;
stack.reserve(10);
stack.push_back(1);          // [1]
stack.push_back(2);          // [1, 2]
int top = stack.back();      // 2
stack.pop_back();             // [1]
```

→ _See [10_StackBehavior](../solutions/Chapter_16_Dynamic_Arrays_Vector/10_StackBehavior) for push/pop/emplace patterns._

**std::vector Stack Operations:**

| Operation               | Effect                      | Returns                | UB if empty? |
| ----------------------- | --------------------------- | ---------------------- | ------------ |
| `push_back(val)`        | Appends copy of val         | `void`                 | No           |
| `emplace_back(args...)` | Constructs element in-place | ref to element (C++17) | No           |
| `pop_back()`            | Removes last element        | `void`                 | **Yes**      |
| `back()`                | Accesses last element       | reference              | **Yes**      |

### 16.12 - std::vector<bool>

- `std::vector<bool>` is a specialization that **bit-packs** booleans (1 bit per element) - but this optimization has significant drawbacks
- `operator[]` returns a **proxy object** instead of an actual `bool&` → `auto& b = v[0]` fails to compile
- Many standard library **algorithms** that rely on contiguous memory or real references don't work correctly with it
- Prefer **`std::bitset`** for fixed-size bit collections, **`std::vector<char>`** for dynamic boolean arrays, or a third-party dynamic bitset when bit-packing is needed

```cpp
// std::vector<bool> v{true, false}; // avoid - returns proxy, not bool&
std::vector<char> flags{ 1, 0, 1 };  // safe dynamic bool alternative
std::bitset<8> bits{ 0b1010'0110 };   // fixed-size alternative
```

→ _See [12_VectorBoolPitfall](../solutions/Chapter_16_Dynamic_Arrays_Vector/12_VectorBoolPitfall) for why `vector<bool>` breaks._

### Edge Cases and Caveats

❌ Confusing `{ n }` with `( n )`:

```cpp
std::vector<int> v1{ 5 }; // ❌ 1 element with value 5
std::vector<int> v2( 5 );  // 5 elements, all zero
```

✅ Be explicit about intent - use `()` for count, `{}` for values.

---

❌ Off-by-one errors:

```cpp
for (std::size_t i = 0; i <= v.size(); ++i) // ❌ UB on last iteration
```

✅ Use `<` not `<=`:

```cpp
for (std::size_t i = 0; i < v.size(); ++i) // ✅
```

---

❌ `operator[]` with out-of-bounds index:

```cpp
std::vector<int> v{1, 2, 3};
int x = v[5]; // ❌ silent UB - no exception
```

✅ Use `at()` for bounds-checked access:

```cpp
int x = v.at(5); // ✅ throws std::out_of_range
```

---

❌ Unsigned index wrap-around:

```cpp
for (std::size_t i = v.size() - 1; i >= 0; --i) // ❌ wraps to huge value
```

✅ Use a signed type or range-based for:

```cpp
for (auto it = v.rbegin(); it != v.rend(); ++it) // ✅ reverse iterate safely
```

---

❌ Using `resize()` before `push_back()`:

```cpp
v.resize(10);
v.push_back(42); // ❌ now 11 elements - 10 zeroes + 42
```

✅ Use `reserve()` to pre-allocate without adding elements:

```cpp
v.reserve(10);
v.push_back(42); // ✅ 1 element, capacity ≥ 10
```

---

❌ Passing `std::vector` by value:

```cpp
void process(std::vector<int> v) {} // ❌ full copy every call
```

✅ Pass by const reference:

```cpp
void process(const std::vector<int>& v) {} // ✅ no copy
```

---

❌ `std::vector<const int>`:

```cpp
std::vector<const int> v; // ❌ illegal - elements must be assignable
```

✅ Make the vector const instead:

```cpp
const std::vector<int> v{1, 2, 3}; // ✅
```

---

❌ Confusing capacity with length:

```cpp
v.reserve(100);
int x = v[50]; // ❌ UB - length is still 0, only capacity is 100
```

✅ Valid indices are `[0, size())`, not `[0, capacity())`.

---

❌ Signed/unsigned mismatch warnings:

```cpp
for (int i = 0; i < v.size(); ++i) // ❌ mismatch: int vs size_type
```

✅ Use range-based for or matching types:

```cpp
for (auto& elem : v) { /* ... */ } // ✅ no index needed
```

---

❌ `pop_back()` on empty vector:

```cpp
std::vector<int> v;
v.pop_back(); // ❌ UB
```

✅ Check first:

```cpp
if (!v.empty()) v.pop_back(); // ✅
```

---

### Hands-On Code Projects

Practice every concept with the hands-on projects in:

```
solutions/Chapter_16_Dynamic_Arrays_Vector/
```

| Project                                                                                                       | Concept                                                   |
| ------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------- |
| [01_IntroToVector](../solutions/Chapter_16_Dynamic_Arrays_Vector/01_IntroToVector)                           | Basic vector declaration, initialization, and CTAD        |
| [02_ListVsLengthConstructor](../solutions/Chapter_16_Dynamic_Arrays_Vector/02_ListVsLengthConstructor)       | The `{n}` vs `(n)` initialization gotcha                  |
| [03_SubscriptAndBoundsChecking](../solutions/Chapter_16_Dynamic_Arrays_Vector/03_SubscriptAndBoundsChecking) | `operator[]` vs `at()` - bounds checking tradeoffs        |
| [04_LengthAndCapacity](../solutions/Chapter_16_Dynamic_Arrays_Vector/04_LengthAndCapacity)                   | `size()`, `capacity()`, `ssize()`, and `size_type`        |
| [05_PassingVectors](../solutions/Chapter_16_Dynamic_Arrays_Vector/05_PassingVectors)                         | Passing vectors by const reference and with templates     |
| [06_ReturningVectors](../solutions/Chapter_16_Dynamic_Arrays_Vector/06_ReturningVectors)                     | Returning vectors by value - move semantics in action     |
| [07_IndexBasedLoops](../solutions/Chapter_16_Dynamic_Arrays_Vector/07_IndexBasedLoops)                       | Index-based traversal and off-by-one pitfalls             |
| [08_RangeBasedForLoops](../solutions/Chapter_16_Dynamic_Arrays_Vector/08_RangeBasedForLoops)                 | Range-based for loops, `auto&`, `const auto&`, reverse    |
| [09_ResizingAndCapacity](../solutions/Chapter_16_Dynamic_Arrays_Vector/09_ResizingAndCapacity)               | `resize()`, `reserve()`, `shrink_to_fit()`, reallocation  |
| [10_StackBehavior](../solutions/Chapter_16_Dynamic_Arrays_Vector/10_StackBehavior)                           | `push_back()`, `pop_back()`, `back()`, `emplace_back()`   |
| [11_EnumeratorIndices](../solutions/Chapter_16_Dynamic_Arrays_Vector/11_EnumeratorIndices)                   | Using enumerators as meaningful array indices             |
| [12_VectorBoolPitfall](../solutions/Chapter_16_Dynamic_Arrays_Vector/12_VectorBoolPitfall)                   | Why `std::vector<bool>` is broken and what to use instead |

### Quick Reference

| Feature     | Syntax                               | Notes                      |
| ----------- | ------------------------------------ | -------------------------- |
| Declare     | `std::vector<int> v;`                | Empty vector               |
| List init   | `std::vector<int> v{ 1, 2, 3 };`     | 3 elements                 |
| Length init | `std::vector<int> v( 5 );`           | 5 zeros - **not** `{ 5 }`  |
| CTAD        | `std::vector v{ 1, 2, 3 };`          | Deduces `vector<int>`      |
| Access      | `v[i]` / `v.at(i)`                   | No check / throws on OOB   |
| Size        | `v.size()` / `std::ssize(v)`         | Unsigned / signed (C++20)  |
| Pass        | `void f(const std::vector<int>& v)`  | By const reference         |
| Return      | `std::vector<int> f() { return v; }` | Move semantics - cheap     |
| Range for   | `for (const auto& e : v)`            | No index needed            |
| Reserve     | `v.reserve(100);`                    | Pre-allocate capacity      |
| Resize      | `v.resize(10);`                      | Change length (+ capacity) |
| Push back   | `v.push_back(42);`                   | Append element             |
| Emplace     | `v.emplace_back(args...);`           | Construct in-place         |
| Pop back    | `v.pop_back();`                      | Remove last (UB if empty)  |
| Back        | `v.back();`                          | Last element               |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is the difference between `std::vector<int> v(5)` and `std::vector<int> v{5}`?

<details>
<summary>Show answer</summary>

**Direct answer:** `v(5)` uses the length constructor - it creates a vector of 5 elements, all zero-initialized. `v{5}` uses the list constructor - it creates a vector with one element whose value is `5`. This is one of the most common `std::vector` gotchas.

**Detailed explanation:**

```cpp
std::vector<int> a(5);   // [0, 0, 0, 0, 0] - 5 elements
std::vector<int> b{5};   // [5]             - 1 element

std::vector<int> c(3, 7); // [7, 7, 7]      - 3 elements, all 7
std::vector<int> d{3, 7}; // [3, 7]         - 2 elements

// CTAD works with list init:
std::vector e{ 1, 2, 3 };  // deduces vector<int>
```

</details>

2. Why does `operator[]` not throw on out-of-bounds access?

<details>
<summary>Show answer</summary>

**Direct answer:** `operator[]` is designed for performance - bounds checking on every access would add overhead. Out-of-bounds access via `operator[]` is undefined behavior. Use `at()` when you need runtime bounds checking; it throws `std::out_of_range` on invalid indices.

**Detailed explanation:**

```cpp
std::vector v{ 10, 20, 30 };

v[1];   // OK: returns 20 (no bounds check)
v[99];  // UB: no exception, unpredictable behavior

v.at(1);   // OK: returns 20 (bounds checked)
v.at(99);  // throws std::out_of_range
```

For most code, range-based `for` loops eliminate the need for indexing entirely. When indexing is required, ensure the index is valid before using `operator[]`.

</details>

3. What is the difference between `size()` and `capacity()`?

<details>
<summary>Show answer</summary>

**Direct answer:** `size()` is the number of elements currently stored in the vector. `capacity()` is the number of elements the vector has allocated memory for. `capacity() >= size()` always. When `size()` reaches `capacity()`, the next `push_back()` triggers a reallocation (typically doubling capacity), which copies/moves all existing elements.

**Detailed explanation:**

```cpp
std::vector<int> v;
v.reserve(100);          // capacity=100, size=0 - no elements created
v.push_back(42);         // capacity=100, size=1

v.resize(50);            // capacity=100, size=50 - 50 elements exist (49 zeros + 42)
v.shrink_to_fit();       // capacity may reduce to 50 (non-binding request)
```

</details>

4. Why should you use `reserve()` instead of `resize()` when pre-allocating?

<details>
<summary>Show answer</summary>

**Direct answer:** `reserve(n)` allocates memory for `n` elements without creating them - `size()` stays the same. `resize(n)` both allocates and creates elements (default-initialized), changing `size()`. Use `reserve()` when you know how many elements you'll `push_back()` - it prevents expensive reallocations without producing unnecessary default-constructed elements.

**Detailed explanation:**

```cpp
std::vector<int> v;
v.reserve(1000);        // capacity=1000, size=0 - ready for push_back
for (int i{ 0 }; i < 1000; ++i)
    v.push_back(i);     // no reallocations - memory already allocated

// vs.
std::vector<int> w;
w.resize(1000);         // capacity=1000, size=1000 - 1000 zeros exist
// Now push_back adds element 1001, which may reallocate
```

</details>

5. Why is `std::vector<const int>` illegal?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::vector` requires its element type to be assignable and movable so it can rearrange elements during reallocation, insertion, and erasure. `const int` cannot be assigned to, so it fails to satisfy the container's requirements. Use `const std::vector<int>` instead to make the entire vector immutable.

**Detailed explanation:**

```cpp
// std::vector<const int> v{ 1, 2, 3 };  // ERROR: const int is not assignable

const std::vector<int> v{ 1, 2, 3 };     // OK: vector itself is const
// v.push_back(4);                        // ERROR: can't modify const vector
// v[0] = 99;                             // ERROR: can't modify elements
int x = v[0];                             // OK: can read
```

</details>

6. How can you safely iterate a vector in reverse without unsigned wrap-around?

<details>
<summary>Show answer</summary>

**Direct answer:** Use reverse iterators: `for (auto it = v.rbegin(); it != v.rend(); ++it)`. Alternatively, use a signed index with `std::ssize()` (C++20): `for (auto i = std::ssize(v) - 1; i >= 0; --i)`. Do not decrement an unsigned index below 0 - it wraps to a huge value, causing UB or an infinite loop.

**Detailed explanation:**

```cpp
std::vector v{ 10, 20, 30, 40 };

// Option 1: reverse iterators (safest)
for (auto it{ v.rbegin() }; it != v.rend(); ++it)
    std::cout << *it << ' ';  // 40 30 20 10

// Option 2: signed index with std::ssize (C++20)
for (auto i{ std::ssize(v) - 1 }; i >= 0; --i)
    std::cout << v[static_cast<std::size_t>(i)] << ' ';

// DANGEROUS: unsigned wrap-around
// for (std::size_t i = v.size() - 1; i >= 0; --i)  // infinite loop!
```

</details>

7. What happens if you call `pop_back()` on an empty vector?

<details>
<summary>Show answer</summary>

**Direct answer:** It's undefined behavior. `pop_back()` does not check whether the vector is empty. Always check `!v.empty()` before calling `pop_back()`.

**Detailed explanation:**

```cpp
std::vector<int> v;

// v.pop_back();  // UB: vector is empty

if (!v.empty())
    v.pop_back();  // safe - only called when elements exist
```

Similarly, `front()` and `back()` on an empty vector are also UB. Always verify `!empty()` or check `size() > 0` before accessing.

</details>

8. Why should vectors generally be passed by `const&`?

<details>
<summary>Show answer</summary>

**Direct answer:** Vectors can hold thousands of elements, so passing by value copies every element - $O(n)$. Passing by `const&` avoids the copy while preventing modification. Pass by non-const reference (`std::vector<T>&`) when the function needs to modify the vector. Return by value (move semantics make this $O(1)$).

**Detailed explanation:**

```cpp
void print(const std::vector<int>& v)    // const&: no copy, read-only
{
    for (int x : v) std::cout << x << ' ';
}

void sort(std::vector<int>& v)            // non-const&: modifies in-place
{
    std::sort(v.begin(), v.end());
}

std::vector<int> generate()               // return by value: move semantics
{
    std::vector<int> result{ 1, 2, 3 };
    return result;  // moved, not copied
}
```

</details>

9. What is the problem with `std::vector<bool>` and why should you avoid it?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::vector<bool>` is a special-case template that bit-packs booleans (1 bit per element instead of 1 byte). `operator[]` returns a proxy object instead of a real `bool&`, which breaks `auto&` references, algorithms expecting contiguous memory, and code using pointers to elements. Use `std::vector<char>` or `std::bitset` instead.

**Detailed explanation:**

```cpp
std::vector<bool> flags{ true, false, true };

// auto& f = flags[0];    // ERROR: operator[] returns a proxy, not bool&
auto f = flags[0];         // OK: copies the proxy (converts to bool)

// Prefer alternatives:
std::vector<char> flags2{ 1, 0, 1 };  // 1 byte each, but real references
std::bitset<3> flags3{ 0b101 };       // fixed-size bit container
```

</details>

10. How does move semantics make returning `std::vector` by value efficient?

<details>
<summary>Show answer</summary>

**Direct answer:** Moving a vector transfers ownership of its internal heap allocation (a pointer, size, and capacity) from the source to the destination - three pointer-sized assignments, $O(1)$ regardless of element count. No elements are copied. The source is left in a valid-but-empty state. The compiler performs this move automatically when returning a local vector from a function.

**Detailed explanation:**

```cpp
std::vector<int> generate(int n)
{
    std::vector<int> result;
    result.reserve(n);
    for (int i{ 0 }; i < n; ++i)
        result.push_back(i);
    return result;  // MOVED to caller (or NRVO'd) - no copy
}

auto v = generate(1'000'000);  // 1M elements, but return is O(1)
```

Rule of thumb: pass by `const&`, return by value.

</details>
