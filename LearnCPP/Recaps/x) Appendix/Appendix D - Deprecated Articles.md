# Appendix D Recap - Deprecated Articles

This appendix collects deprecated lessons from old Chapters 21 and 22, covering the C++ Standard Library (STL containers, iterators, and algorithms) and an in-depth walkthrough of `std::string` / `std::wstring`. These articles are marked for removal because the material has been superseded by updated lessons elsewhere in the tutorial; the author notes the string chapter in particular is "somewhat outdated." They remain available for reference and useful examples.

## Key Concepts

- **C++ Standard Library** - a collection of templated containers, algorithms, and iterators ready for reuse
- **STL container categories** - Sequence containers, Associative containers, and Container adapters
- **Iterators** - objects that traverse containers uniformly, regardless of internal implementation
- **STL algorithms** - generic functions (sort, find, min/max, reverse, etc.) that operate through iterators
- **`std::string` / `std::wstring`** - safe, feature-rich replacements for C-style strings, built on `basic_string<>`
- **String capacity vs. length** - capacity is pre-allocated memory; length is characters in use; reallocation is expensive
- **Converting between `std::string` and C-style strings** - `c_str()`, `data()`, and `copy()`
- **Number-to-string conversion** - `std::ostringstream` / `std::to_string()`; string-to-number via `std::istringstream`

## Section Summaries

### 21.1 - The Standard Library

- The **C++ Standard Library** is a large collection of templated **containers**, **algorithms**, and **iterators** ready for reuse
- Learn it **incrementally** - use what you need now and explore more as your projects demand it
- Containers store data, algorithms operate on data, and iterators provide the **glue** connecting them
- The library is **templated** - the same container/algorithm code works with any compatible type

```cpp
#include <vector>
#include <algorithm>
std::vector<int> v{3, 1, 4};
std::sort(v.begin(), v.end()); // STL algorithm + STL container
```

### 21.2 - STL Containers Overview

- STL containers fall into three categories - **Sequence** (maintain insertion order), **Associative** (auto-sort on insertion), and **Adapters** (wrap containers for specific access patterns)
- **Sequence containers** - `vector`, `deque`, `list`, `forward_list`, `array`, `basic_string`
- **Associative containers** - `set`, `multiset`, `map`, `multimap` - elements sorted by key automatically
- **Container adapters** - `stack` (LIFO), `queue` (FIFO), `priority_queue` (sorted priority) - built on top of sequence containers
- `std::vector` should be the **default choice** - contiguous memory, cache-friendly, O(1) random access

```cpp
std::vector<int> seq{1, 2, 3};        // sequence container
std::set<int> assoc{3, 1, 2};         // associative (auto-sorted)
std::stack<int> adapter;              // container adapter (LIFO)
```

> **Container Selection Guide**
>
> | I need…                                    | Use this             | Why                                |
> | ------------------------------------------ | -------------------- | ---------------------------------- |
> | Fast random access, cache-friendly         | `std::vector`        | Contiguous memory, O(1) index      |
> | Fast insert/remove at both ends            | `std::deque`         | O(1) front and back                |
> | Guaranteed O(1) insert/remove mid-sequence | `std::list`          | Node-based, no element movement    |
> | Unique sorted keys                         | `std::set`           | Auto-sorted, O(log n) lookup       |
> | Key-value pairs, sorted                    | `std::map`           | Sorted by key, O(log n)            |
> | Key-value pairs, fastest lookup            | `std::unordered_map` | Hash table, O(1) average           |
> | LIFO stack                                 | `std::stack`         | Adapter over `deque`/`vector`      |
> | FIFO queue                                 | `std::queue`         | Adapter over `deque`               |
> | Default choice                             | `std::vector`        | Almost always the right first pick |

### 21.3 - STL Iterators Overview

- **Iterators** are pointer-like objects providing a uniform interface (`*`, `++`, `==`) for traversing any container
- Nearly identical iteration code works across `vector`, `list`, `set`, and `map` - the container's internals are abstracted away
- `begin()`/`end()` return mutable iterators - `cbegin()`/`cend()` return **const iterators** that prevent modification
- Iterator categories form a hierarchy - **Input** → **Forward** → **Bidirectional** → **Random Access** → **Contiguous** (C++17)
- Some algorithms require specific iterator categories - e.g., `std::sort` requires **random-access** iterators

```cpp
std::vector<int> v{1, 2, 3};
for (auto it = v.cbegin(); it != v.cend(); ++it)
    std::cout << *it << ' ';
```

> **Iterator Category Hierarchy**
>
> | Category           | Operations                                  | Containers                    | Key Algorithm Compatibility     |
> | ------------------ | ------------------------------------------- | ----------------------------- | ------------------------------- |
> | Input              | `*`, `++`, `==` (single-pass read)          | `istream_iterator`            | `std::find`, `std::count`       |
> | Forward            | Input + multi-pass                          | `forward_list`, `unordered_*` | `std::replace`, `std::search`   |
> | Bidirectional      | Forward + `--`                              | `list`, `set`, `map`          | `std::reverse`, `std::prev`     |
> | Random Access      | Bidirectional + `+n`, `-n`, `[]`            | `vector`, `deque`, `array`    | `std::sort`, `std::nth_element` |
> | Contiguous (C++17) | Random Access + elements adjacent in memory | `vector`, `array`, `string`   | All algorithms + `std::span`    |
>
> `std::sort` requires random-access iterators. For `std::list`, use `list.sort()` (member function).

### 21.4 - STL Algorithms Overview

- Common algorithms from `<algorithm>` and `<numeric>` include `find`, `sort`, `reverse`, `min_element`, `max_element`, and `iota`
- Algorithms operate via **iterators** → they work generically across different container types
- Not all algorithm/container combinations perform well - `std::sort` doesn't work on `std::list` → use `list::sort()` instead
- C++20 **Ranges** algorithms accept entire containers and support **projections**, eliminating raw iterator-pair boilerplate

```cpp
std::vector<int> v{3, 1, 4};
auto it = std::find(v.begin(), v.end(), 1); // returns iterator to 1
std::sort(v.begin(), v.end());               // {1, 3, 4}
```

### 22.1 - std::string and std::wstring

- `std::string` eliminates the pitfalls of C-style strings - **no manual memory management**, no buffer overflows, no pointer-comparison bugs
- Supports intuitive **operators** for assignment (`=`), concatenation (`+=`), and comparison (`==`, `<`)
- Provides a full API - construction, element access, modification, comparison, searching, and iteration
- Prefer `std::string` (or `std::string_view` for read-only) over `char*` in all modern C++ code

```cpp
std::string s{"Hello"};
s += " World";  // simple concatenation
if (s == "Hello World") {} // intuitive comparison
```

### 22.2 - std::string Construction and Destruction

- String constructors include **default**, **copy**, **substring**, **from C-string**, **fill character**, and **iterator-range** variants
- Convert **numbers → strings** via `std::to_string()` or `std::ostringstream`
- Convert **strings → numbers** via `std::istringstream` (or C++17's `std::from_chars` for performance)
- `std::string` manages its own memory - construction and destruction are automatic through RAII

```cpp
std::string a{"Hello"};                // from C-string
std::string b(5, 'x');                 // fill: "xxxxx"
std::string num{ std::to_string(42) }; // number → string
```

### 22.3 - std::string Length and Capacity

- `length()`/`size()` return characters in use - `capacity()` returns pre-allocated buffer size - `capacity() >= size()` always
- Strings **over-allocate** to avoid frequent reallocations - when `size()` exceeds `capacity()`, a costly reallocation occurs (allocate + copy + invalidate iterators)
- Use `reserve()` to **pre-allocate** capacity when building large strings incrementally → avoids repeated reallocations
- `empty()` checks if the string has zero length - `max_size()` returns the theoretical maximum string length

```cpp
std::string s;
s.reserve(1000); // pre-allocate to avoid reallocations
for (int i{0}; i < 100; ++i) s += "x";
```

### 22.4 - std::string Character Access and Conversion to C-style Arrays

- `operator[]` is **fast** but performs no bounds checking - out-of-range access is **undefined behavior**
- `at()` is **bounds-checked** and throws `std::out_of_range` on invalid indices - use it for untrusted input
- `c_str()` and `data()` return a `const char*` pointing to the internal buffer - the pointer is **invalidated** by any non-const operation on the string
- `copy()` writes to a caller-managed buffer and does **not** append a null terminator - the caller must handle it

```cpp
std::string s{"Hello"};
char ch = s.at(1);           // 'e' (bounds-checked)
const char* cstr = s.c_str(); // null-terminated C-string
```

> **String Access Methods Compared**
>
> | Method        | Bounds Check                | Returns                        | Null-terminated?  | Notes                                       |
> | ------------- | --------------------------- | ------------------------------ | ----------------- | ------------------------------------------- |
> | `str[i]`      | No (UB if out of range)     | `char&`                        | N/A               | Fastest; use when index is known-valid      |
> | `str.at(i)`   | Yes (throws `out_of_range`) | `char&`                        | N/A               | Use for untrusted indices                   |
> | `str.c_str()` | N/A                         | `const char*`                  | Yes               | For C API interop; invalidated by mutations |
> | `str.data()`  | N/A                         | `const char*` (C++17: `char*`) | Yes (since C++11) | Same as `c_str()` since C++11               |

### 22.5 - std::string Assignment and Swapping

- `operator=` and the `assign()` family set the string's value - overloads accept strings, C-strings, substrings, and fill characters
- `swap()` exchanges two strings' contents in **O(1)** - it swaps internal pointers rather than copying characters
- Available as both a **member function** (`a.swap(b)`) and a **free function** (`std::swap(a, b)`)
- Swapping is more efficient than assignment when you need to exchange values and don't need the old contents

```cpp
std::string a{"Hello"}, b{"World"};
a.swap(b); // O(1) pointer swap
```

### 22.6 - std::string Appending

- `operator+=` is the simplest way to append content to the end of a string
- `append()` provides additional overloads - substrings, partial C-strings, repeated characters, and **iterator ranges**
- `push_back()` appends a **single character** - analogous to `std::vector::push_back()`
- All append operations may trigger **reallocation** if the current capacity is insufficient → use `reserve()` to avoid this

```cpp
std::string s{"Hello"};
s += " World";        // operator+=
s.append("!");        // append()
s.push_back('\n');    // push_back()
```

### 22.7 - std::string Inserting

- `insert()` places characters at an **arbitrary position** within the string - unlike append, which only adds to the end
- Overloads accept **strings**, **C-strings**, **substrings**, **repeated characters**, and **iterators**
- Insertion shifts existing characters to the right → may trigger **reallocation** if capacity is exceeded
- For frequent mid-string insertions, consider whether a different data structure (e.g., `std::deque`) is more appropriate

```cpp
std::string s{"Hello"};
s.insert(5, " World");       // "Hello World"
```

## Hands-On Code Projects

No companion code projects for this appendix - these articles are deprecated. Refer to the updated lessons in the main tutorial instead. For hands-on practice with the topics covered here:

- **STL containers & iterators** - See Chapter 16 (Dynamic Arrays / `std::vector`), Chapter 17 (Fixed-Size Arrays), and Chapter 18 (Iterators & Algorithms)
- **`std::string`** - See Chapter 5 (Constants and Strings) for modern string handling with `std::string` and `std::string_view`
- **Algorithms** - See Chapter 18 (Iterators & Algorithms) for STL algorithm usage

## Quick Reference

| Container Type | Examples                             | Access Pattern            |
| -------------- | ------------------------------------ | ------------------------- |
| Sequence       | `vector`, `deque`, `list`, `array`   | Maintains insertion order |
| Associative    | `set`, `map`, `multiset`, `multimap` | Auto-sorted by key        |
| Adapter        | `stack`, `queue`, `priority_queue`   | LIFO / FIFO / priority    |

| std::string Operation | Method                             | Notes                 |
| --------------------- | ---------------------------------- | --------------------- |
| Get C-string          | `str.c_str()`                      | Returns `const char*` |
| Bounds-checked access | `str.at(i)`                        | Throws `out_of_range` |
| Fast access           | `str[i]`                           | No bounds check       |
| Append                | `str += "text"` or `str.append(…)` | Multiple overloads    |
| Insert                | `str.insert(pos, "text")`          | At arbitrary position |
| Swap                  | `str.swap(other)`                  | O(1) - pointer swap   |
| Pre-allocate          | `str.reserve(n)`                   | Avoids reallocation   |

## Key Takeaways

- **Prefer STL containers over raw arrays** - they manage memory automatically and provide a rich interface
- **Use iterators for generic traversal** - the same loop logic works across vectors, lists, sets, and maps
- **STL algorithms + iterators = powerful combinations**, but verify that the algorithm is appropriate for your container type
- **Prefer `std::string` over C-style strings** - it eliminates manual memory management, buffer overflows, and subtle pointer-comparison bugs
- **Be aware of capacity vs. length** - use `reserve()` when building large strings incrementally to avoid repeated reallocations
- **Use `at()` over `operator[]` when index validity is uncertain** - it provides bounds checking via exceptions
- **Use `c_str()` to interface with C APIs** - but do not delete or modify the returned pointer
- **These articles are deprecated** - prefer the updated lessons in the main tutorial and authoritative references like cppreference for current API details

## Common Pitfalls

❌ Using deprecated STL APIs:

```cpp
std::auto_ptr<int> p; // ❌ deprecated C++11, removed C++17
```

✅ Cross-reference with [cppreference.com](https://en.cppreference.com). Use `std::ranges` algorithms (C++20) over raw iterator pairs.

---

❌ Manual iterator invalidation:

```cpp
std::vector<int> v{1, 2, 3};
v.push_back(4); // ❌ may invalidate all iterators if reallocation occurred
```

✅ Know each container's invalidation rules. Use `reserve()` to prevent reallocation.

---

❌ Using `operator[]` on `std::string` without bounds checking:

```cpp
std::string s = "hi";
char c = s[10]; // ❌ UB - no exception thrown
```

✅ Use `at()` when index validity is uncertain:

```cpp
char c = s.at(10); // ✅ throws std::out_of_range
```

---

❌ Forgetting that `c_str()` returns a pointer to internal data:

```cpp
const char* p = s.c_str();
s += " world"; // ❌ p is now invalidated
```

✅ Copy the result immediately if you need it to outlive the next string modification.

---

❌ Confusing `capacity()` with `size()`/`length()`:

```cpp
s.reserve(100);
// capacity() >= 100, but size() is still the original length ❌ don't confuse them
```

✅ `capacity()` = allocated buffer. `size()` = actual characters. Use `reserve()` to pre-allocate.

---

❌ Using `std::list` when `std::vector` would suffice:

```cpp
std::list<int> data; // ❌ poor cache locality, higher overhead
```

✅ Default to `std::vector`. Only use `std::list` for guaranteed O(1) splicing or iterator stability.

---

❌ Calling `std::sort` on `std::list`:

```cpp
std::sort(myList.begin(), myList.end()); // ❌ requires random-access iterators
```

✅ Use the member function:

```cpp
myList.sort(); // ✅ uses list's own sort
```

---

## Mastery Check

1. Why was `std::auto_ptr` deprecated and what replaced it?
2. What are iterator invalidation rules and why do they matter?
3. What is the difference between `operator[]` and `at()` for `std::string`?
4. Why is the `c_str()` pointer invalidated by non-const operations?
5. When is `std::list` actually the right choice over `std::vector`?
6. Why can't `std::sort` be used with `std::list`?
7. What is the difference between `size()` and `capacity()` for strings and vectors?
8. What are `std::ranges` algorithms and how do they improve on classic STL algorithms?
