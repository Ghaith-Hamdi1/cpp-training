# Chapter 18 Recap - Iterators and Algorithms

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- **Prefer `std::sort`** over hand-written sorts - it's pre-tested, optimized, and often 100×+ faster.
- Use iterators (`begin()` / `end()`) for container-agnostic traversal.
- Compare iterators with `!=`, not `<` - not all iterator types support relational comparison.
- **Do not modify a container while iterating** - this invalidates iterators and causes UB.
- Revalidate iterators by assigning the return value of modifying operations (e.g., `it = v.erase(it)`).
- Use `std::for_each` when you want guaranteed sequential access and want to avoid range-for mistakes.
- C++20 ranges simplify algorithm calls - `std::ranges::sort(v)` instead of `std::sort(v.begin(), v.end())`.
- Always benchmark in **release mode** with at least 3 measurements.

### 3 Tiny Examples

1.

```cpp
int arr[] {5, 3, 1, 4, 2};
std::sort(std::begin(arr), std::end(arr));
// arr is now {1, 2, 3, 4, 5}
```

2.

```cpp
std::vector v{1, 2, 3};
for (auto it = v.begin(); it != v.end(); ++it)
    std::cout << *it << ' '; // 1 2 3
```

3.

```cpp
std::vector v{3, 1, 4, 1, 5};
auto it = std::find(v.begin(), v.end(), 4);
int count = std::count_if(v.begin(), v.end(), [](int x){ return x > 2; });
```

### 3 Common Mistakes

- Skipping compiler warnings.
- Using chapter features without understanding prerequisites.
- Not testing edge cases.

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Selection sort** - O(n²); scans unsorted portion for the smallest, swaps it into position.
- **Bubble sort** - O(n²); adjacent swaps, large values "bubble" to the end; early-termination if no swaps.
- **`std::sort`** - highly optimized sort in `<algorithm>`; introsort (quicksort + heapsort + insertion sort).
- **Iterator** - an object abstracting container traversal via `operator*` (dereference) and `operator++` (advance).
- **`begin()` / `end()`** - return iterators to the first element and one-past-the-last element.
- **Iterator invalidation** - modifying a container (add/remove) can make existing iterators dangling.
- **`std::find` / `std::find_if`** - search by value or by predicate; return `end()` if not found.
- **`std::count` / `std::count_if`** - count elements matching a value or predicate.
- **`std::for_each`** - apply a callable to every element; guaranteed sequential, single-pass.
- **Ranges (C++20)** - pass containers directly to algorithms: `std::ranges::sort(v)`.
- **`std::chrono`** - timing library; `std::chrono::steady_clock` for reliable benchmarking.

### Section-by-Section Detail

### 18.1 - Sorting an array using selection sort

- Sorting enables efficient searching and organized output
- **Selection sort** uses a nested loop - outer marks sorted position, inner finds smallest remaining element, `std::swap` places it
- Complexity is **O(n^2)** - fine for small arrays, terrible for large datasets
- **Bubble sort** compares adjacent elements and supports early termination when no swaps occur (nearly-sorted optimization)
- Both are vastly outperformed by `std::sort` - always prefer it for production code

```cpp
int arr[] {5, 3, 1, 4, 2};
std::sort(std::begin(arr), std::end(arr));
// arr is now {1, 2, 3, 4, 5}
```

→ _See [01_SelectionSort](../solutions/Chapter_18_Iterators_And_Algorithms/01_SelectionSort) and [02_BubbleSort](../solutions/Chapter_18_Iterators_And_Algorithms/02_BubbleSort) for both algorithms._

**Sorting Algorithm Comparison:**

| Algorithm                   | Complexity | Stable? | Early-Exit?         | Use Case                         |
| --------------------------- | ---------- | ------- | ------------------- | -------------------------------- |
| **Selection sort**          | O(n^2)     | No      | No                  | Educational only                 |
| **Bubble sort**             | O(n^2)     | Yes     | Yes (no-swap check) | Educational; nearly-sorted data  |
| **`std::sort`** (introsort) | O(n log n) | No      | N/A                 | All production sorting           |
| **`std::stable_sort`**      | O(n log n) | Yes     | N/A                 | When equal-element order matters |

### 18.2 - Introduction to iterators

- An **iterator** abstracts traversal - `operator++` advances, `operator*` accesses the current element
- Pointers are the simplest iterators
- `begin()` returns an iterator to the first element; `end()` returns a sentinel one-past-the-last
- Range-based for loops use iterators internally - any type with `begin()`/`end()` is iterable
- **Iterator invalidation** occurs when the container is modified (add/remove) while iterating → existing iterators become dangling

```cpp
std::vector v{1, 2, 3};
for (auto it = v.begin(); it != v.end(); ++it)
    std::cout << *it << ' '; // 1 2 3
```

→ _See [04_Iterators](../solutions/Chapter_18_Iterators_And_Algorithms/04_Iterators) and [05_IteratorInvalidation](../solutions/Chapter_18_Iterators_And_Algorithms/05_IteratorInvalidation)._

**Iterator Category Capabilities:**

| Capability              | Forward        | Bidirectional        | Random-Access              |
| ----------------------- | -------------- | -------------------- | -------------------------- |
| `++it` (advance)        | Yes            | Yes                  | Yes                        |
| `--it` (retreat)        | No             | Yes                  | Yes                        |
| `it + n` (jump)         | No             | No                   | Yes                        |
| `it[n]` (subscript)     | No             | No                   | Yes                        |
| `it < it2` (relational) | No             | No                   | Yes                        |
| `==` / `!=`             | Yes            | Yes                  | Yes                        |
| **Example container**   | `forward_list` | `list`, `set`, `map` | `vector`, `array`, `deque` |

### 18.3 - Introduction to standard library algorithms

- `<algorithm>` provides three categories - **inspectors** (`find`, `count`), **mutators** (`sort`, `reverse`), and **facilitators** (`for_each`, `transform`)
- `std::find` returns an iterator to the first match or `end()`; `std::find_if` uses a predicate
- `std::sort` accepts a custom comparator - e.g., `std::greater{}` for descending order
- `std::for_each` guarantees sequential access and avoids common range-for mistakes
- C++20 **ranges** eliminate `begin()`/`end()` boilerplate → `std::ranges::sort(v)`

```cpp
std::vector v{3, 1, 4, 1, 5};
auto it = std::find(v.begin(), v.end(), 4);
int count = std::count_if(v.begin(), v.end(), [](int x){ return x > 2; });
```

→ _See [06_FindAndCount](../solutions/Chapter_18_Iterators_And_Algorithms/06_FindAndCount), [07_ForEach](../solutions/Chapter_18_Iterators_And_Algorithms/07_ForEach), and [08_RangesCpp20](../solutions/Chapter_18_Iterators_And_Algorithms/08_RangesCpp20)._

**Standard Algorithm Categories:**

| Category         | Purpose                          | Examples                                 |
| ---------------- | -------------------------------- | ---------------------------------------- |
| **Inspectors**   | Query without modifying          | `find`, `count`, `min_element`, `any_of` |
| **Mutators**     | Modify element order/values      | `sort`, `reverse`, `fill`, `remove`      |
| **Facilitators** | Apply operations to each element | `for_each`, `transform`, `accumulate`    |

### 18.4 - Timing your code

- Wrap `std::chrono::steady_clock` in a **Timer** class - record a time point on construction, expose an `elapsed()` method returning seconds
- `std::sort` can be **orders of magnitude** faster than selection/bubble sort on the same data set
- Always benchmark with **release builds** - debug mode disables optimizations and can be 30x+ slower
- Minimize background processes, use the same random seed, and run at least 3 measurements to account for variance
- Compare **relative** performance between variants on the same machine - hardware differences make raw numbers non-portable

```cpp
auto start = std::chrono::steady_clock::now();
std::sort(v.begin(), v.end());
auto end = std::chrono::steady_clock::now();
std::chrono::duration<double> elapsed = end - start;
std::cout << "Elapsed: " << elapsed.count() << "s\n";
```

→ _See [09_TimingCode](../solutions/Chapter_18_Iterators_And_Algorithms/09_TimingCode) for a Timer class implementation and benchmark examples._

### Edge Cases and Caveats

❌ Modifying a container during iteration:

```cpp
for (auto& e : v)
    if (e == 3) v.push_back(99); // ❌ invalidates iterators → UB
```

✅ Collect changes and apply after the loop, or use erase-remove idiom.

---

❌ Using `operator<` with iterators:

```cpp
for (auto it = c.begin(); it < c.end(); ++it) // ❌ not all iterators support <
```

✅ Always compare with `!=`:

```cpp
for (auto it = c.begin(); it != c.end(); ++it) // ✅ works for all iterator categories
```

---

❌ Off-by-one in sort loops:

```cpp
// selection sort: outer goes to size instead of size-1
for (int i = 0; i < size; ++i) // ❌ last pass is wasted or OOB
```

✅ Outer loop stops one before the end; inner loop handles the rest.

---

❌ Benchmarking in debug mode:

```cpp
// Debug build: optimizations disabled → 30×+ slower
```

✅ Always benchmark in Release/optimized mode for meaningful results.

---

❌ Forgetting `&` in range-for:

```cpp
for (auto e : v) e *= 2; // ❌ modifies a copy, original unchanged
```

✅ Use a reference:

```cpp
for (auto& e : v) e *= 2; // ✅ modifies the original
```

---

❌ Accessing `arr[size()]`:

```cpp
int x = arr[arr.size()]; // ❌ one-past-the-end → UB
```

✅ Last valid index is `size() - 1`. Use `arr.data() + size()` only as an end pointer.

---

❌ Assuming all algorithms preserve order:

```cpp
// std::for_each and std::copy are sequential
// std::sort, std::partition may reorder ❌ don't assume order is preserved
```

✅ Check algorithm documentation for ordering guarantees.

---

### Hands-On Code Projects

Practice every concept with the hands-on projects in:

```
solutions/Chapter_18_Iterators_And_Algorithms/
```

| Project                                                                                              | Concept                                                     |
| ---------------------------------------------------------------------------------------------------- | ----------------------------------------------------------- |
| [01_SelectionSort](../solutions/Chapter_18_Iterators_And_Algorithms/01_SelectionSort)               | Selection sort - O(n²) by finding smallest unsorted element |
| [02_BubbleSort](../solutions/Chapter_18_Iterators_And_Algorithms/02_BubbleSort)                     | Bubble sort with early-termination optimization             |
| [03_StdSort](../solutions/Chapter_18_Iterators_And_Algorithms/03_StdSort)                           | `std::sort` with default and custom comparators             |
| [04_Iterators](../solutions/Chapter_18_Iterators_And_Algorithms/04_Iterators)                       | Iterators - `begin()`, `end()`, dereferencing, advancing    |
| [05_IteratorInvalidation](../solutions/Chapter_18_Iterators_And_Algorithms/05_IteratorInvalidation) | Modifying containers during iteration - UB and revalidation |
| [06_FindAndCount](../solutions/Chapter_18_Iterators_And_Algorithms/06_FindAndCount)                 | `std::find`, `std::find_if`, `std::count`, `std::count_if`  |
| [07_ForEach](../solutions/Chapter_18_Iterators_And_Algorithms/07_ForEach)                           | `std::for_each` - guaranteed sequential access              |
| [08_RangesCpp20](../solutions/Chapter_18_Iterators_And_Algorithms/08_RangesCpp20)                   | C++20 ranges - pass containers directly to algorithms       |
| [09_TimingCode](../solutions/Chapter_18_Iterators_And_Algorithms/09_TimingCode)                     | `std::chrono` Timer class for benchmarking                  |
| [10_CommonPitfalls](../solutions/Chapter_18_Iterators_And_Algorithms/10_CommonPitfalls)             | Off-by-one, debug benchmarking, missing `&`, past-the-end   |

### Quick Reference

| Feature         | Syntax                             | Notes                        |
| --------------- | ---------------------------------- | ---------------------------- |
| Selection sort  | Nested loops + `std::swap`         | O(n²)                        |
| `std::sort`     | `std::sort(v.begin(), v.end());`   | Introsort, O(n log n)        |
| Sort descending | `std::sort(b, e, std::greater{});` | Custom comparator            |
| Ranges sort     | `std::ranges::sort(v);` (C++20)    | No begin/end needed          |
| Find            | `auto it = std::find(b, e, val);`  | Returns `end()` if not found |
| Find if         | `std::find_if(b, e, pred);`        | Predicate version            |
| Count           | `std::count(b, e, val);`           | Number of matches            |
| Count if        | `std::count_if(b, e, pred);`       | Predicate version            |
| For each        | `std::for_each(b, e, func);`       | Sequential, single-pass      |
| Begin/end       | `v.begin()` / `v.end()`            | Member or free function      |
| Timer           | `std::chrono::steady_clock::now()` | For benchmarking             |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What happens if you call `push_back()` on a vector during a range-based for loop?

<details>
<summary>Show answer</summary>

**Direct answer:** It causes iterator invalidation. The range-based `for` loop holds iterators internally. If `push_back()` triggers a reallocation, those iterators become dangling, leading to undefined behavior. Never modify a container's size while iterating over it with range-based `for` or iterators.

**Detailed explanation:**

```cpp
std::vector v{ 1, 2, 3 };

for (auto x : v)
    v.push_back(x * 2);  // UB: push_back may reallocate, invalidating iterators

// Safe alternative: collect changes, apply after the loop
std::vector<int> toAdd;
for (auto x : v)
    toAdd.push_back(x * 2);
v.insert(v.end(), toAdd.begin(), toAdd.end());
```

</details>

2. Why should you use `!=` instead of `<` when comparing iterators?

<details>
<summary>Show answer</summary>

**Direct answer:** Not all iterator types support `<`. Only random-access iterators (like those from `std::vector` and `std::array`) support relational operators (`<`, `>`, `<=`, `>=`). Forward and bidirectional iterators (like those from `std::list`, `std::set`) only support `==` and `!=`. Using `!=` works with all iterator categories, making code more generic.

**Detailed explanation:**

```cpp
// Works with ANY iterator type:
for (auto it{ v.begin() }; it != v.end(); ++it)
    std::cout << *it << ' ';

// Only works with random-access iterators:
for (auto it{ v.begin() }; it < v.end(); ++it)  // won't compile for std::list
    std::cout << *it << ' ';
```

</details>

3. What is the difference between a forward iterator and a random-access iterator?

<details>
<summary>Show answer</summary>

**Direct answer:** A forward iterator can only move forward one step at a time (`++it`). A random-access iterator supports arbitrary jumps (`it + n`, `it - n`, `it[n]`), relational comparisons (`<`, `>`), and iterator arithmetic. `std::vector` and `std::array` provide random-access iterators; `std::forward_list` provides forward iterators; `std::list` provides bidirectional iterators (forward and backward, but no jumps).

**Detailed explanation:**

```cpp
std::vector<int> v{ 10, 20, 30, 40, 50 };
auto it{ v.begin() };

// Random-access operations:
it += 3;          // jump to 4th element (40)
auto d = it - v.begin();  // distance = 3
auto val = it[1]; // 50

// std::sort requires random-access iterators - won't work with std::list
std::sort(v.begin(), v.end());  // OK: vector has random-access iterators
```

</details>

4. Why is benchmarking in debug mode misleading?

<details>
<summary>Show answer</summary>

**Direct answer:** Debug mode disables compiler optimizations and adds extra checks (bounds checking, iterator validation, memory guards). This can make code 10-30x slower than release mode, distorting relative performance comparisons. Always benchmark in release/optimized builds to get meaningful results.

**Detailed explanation:**
Best practices for benchmarking:

- Build in release mode (`-O2` or `-O3`)
- Use `std::chrono::steady_clock` (not `system_clock`) for timing
- Run at least 3 measurements and consider the median
- Use the same random seed for reproducibility
- Minimize background processes

```cpp
auto start{ std::chrono::steady_clock::now() };
// ... code to benchmark ...
auto end{ std::chrono::steady_clock::now() };
std::chrono::duration<double> elapsed{ end - start };
std::cout << "Elapsed: " << elapsed.count() << " s\n";
```

</details>

5. What does `auto& e` vs `auto e` mean in a range-based for loop?

<details>
<summary>Show answer</summary>

**Direct answer:** `auto e` copies each element - modifications affect only the copy. `auto& e` creates a reference to each element - modifications affect the original container. Use `const auto& e` for read-only access to avoid copies (especially for expensive-to-copy types like `std::string`).

**Detailed explanation:**

```cpp
std::vector v{ 1, 2, 3 };

for (auto e : v)     e *= 2;   // copies - v is unchanged: {1, 2, 3}
for (auto& e : v)    e *= 2;   // references - v is now: {2, 4, 6}
for (const auto& e : v)        // read-only reference - efficient, no copy
    std::cout << e << ' ';
```

</details>

6. Name two STL algorithms and explain what they do.

<details>
<summary>Show answer</summary>

**Direct answer:** `std::find` searches for a value and returns an iterator to the first match (or `end()` if not found). `std::sort` sorts a range in ascending order (by default) using an introsort-like algorithm with $O(n \log n)$ complexity. Both are in `<algorithm>`.

**Detailed explanation:**

```cpp
#include <algorithm>
std::vector v{ 5, 3, 1, 4, 2 };

// std::find: search for a value
auto it{ std::find(v.begin(), v.end(), 4) };
if (it != v.end())
    std::cout << "Found: " << *it;  // 4

// std::sort: sort in ascending order
std::sort(v.begin(), v.end());     // {1, 2, 3, 4, 5}

// std::sort with custom comparator (descending):
std::sort(v.begin(), v.end(), std::greater{});  // {5, 4, 3, 2, 1}

// C++20 ranges version:
std::ranges::sort(v);  // no begin()/end() needed
```

</details>

7. What is the erase-remove idiom and when is it useful?

<details>
<summary>Show answer</summary>

**Direct answer:** It's a two-step pattern for efficiently removing elements from a vector: `std::remove` (or `std::remove_if`) shifts non-removed elements to the front and returns an iterator to the new logical end, then `erase()` actually shrinks the container. In C++20, `std::erase(v, val)` and `std::erase_if(v, pred)` combine both steps.

**Detailed explanation:**

```cpp
std::vector v{ 1, 2, 3, 2, 4, 2, 5 };

// Pre-C++20: erase-remove idiom
v.erase(std::remove(v.begin(), v.end(), 2), v.end());
// v is now {1, 3, 4, 5}

// C++20: simplified
std::vector w{ 1, 2, 3, 2, 4, 2, 5 };
std::erase(w, 2);           // remove all 2s
std::erase_if(w, [](int x) { return x > 3; });  // remove if > 3
```

Without `erase()`, `std::remove` alone just shifts elements and leaves the container with the same `size()` - the "removed" elements are still physically present at the end.

</details>

8. Why is `arr[arr.size()]` undefined behavior?

<details>
<summary>Show answer</summary>

**Direct answer:** Valid indices range from `0` to `size() - 1`. `arr[size()]` accesses one past the last element, which is out of bounds. Only a pointer/iterator to one-past-the-end is valid (as a sentinel) - dereferencing it or using it as an index is UB.

**Detailed explanation:**

```cpp
std::vector v{ 10, 20, 30 };
// v[0], v[1], v[2] are valid
// v[3] == v[v.size()] - UB: out of bounds

// One-past-the-end POINTER is valid for comparisons, not dereferencing:
auto end{ v.data() + v.size() };  // OK as sentinel
// *end;  // UB: dereferencing one-past-the-end
```

</details>

9. What is the time complexity of selection sort vs. `std::sort`?

<details>
<summary>Show answer</summary>

**Direct answer:** Selection sort is $O(n^2)$ - it uses a nested loop to find the minimum element for each position. `std::sort` is $O(n \log n)$ - it typically uses introsort (a hybrid of quicksort, heapsort, and insertion sort). For large datasets, `std::sort` is vastly faster. Always prefer `std::sort` over hand-written sorting.

**Detailed explanation:**

```cpp
// Selection sort (O(n²)) - educational only
for (std::size_t i{ 0 }; i < v.size(); ++i)
{
    auto minIdx{ i };
    for (std::size_t j{ i + 1 }; j < v.size(); ++j)
        if (v[j] < v[minIdx])
            minIdx = j;
    std::swap(v[i], v[minIdx]);
}

// std::sort (O(n log n)) - always use this
std::sort(v.begin(), v.end());
```

</details>

10. How do C++20 ranges simplify algorithm usage?

<details>
<summary>Show answer</summary>

**Direct answer:** C++20 ranges allow you to pass the container directly instead of `begin()`/`end()` iterator pairs. `std::ranges::sort(v)` replaces `std::sort(v.begin(), v.end())`. Ranges also support composable views (lazy transformations) via the pipe (`|`) operator.

**Detailed explanation:**

```cpp
#include <algorithm>
#include <ranges>

std::vector v{ 5, 3, 1, 4, 2 };

// Traditional:
std::sort(v.begin(), v.end());
auto it = std::find(v.begin(), v.end(), 3);

// C++20 ranges:
std::ranges::sort(v);
auto it2 = std::ranges::find(v, 3);

// Range views (lazy, composable):
for (int x : v | std::views::filter([](int x) { return x > 2; })
                | std::views::transform([](int x) { return x * 10; }))
    std::cout << x << ' ';  // 30 40 50
```

</details>
