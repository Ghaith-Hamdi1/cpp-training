# Chapter 19 Recap - Dynamic Allocation

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Every `new` must pair with `delete`; every `new[]` with `delete[]` - mismatching is UB.
- Set deleted pointers to `nullptr` unless they immediately go out of scope.
- `delete nullptr` is safe - no need to check before deleting.
- Memory leaks happen when you lose the address (pointer reassigned, went out of scope, exception thrown).
- Use **RAII** (constructors + destructors) to automate resource management.
- Prefer `std::vector` over manual `new[]`/`delete[]` dynamic arrays.
- Prefer templates/overloading over `void*` for type-safe generic code.
- `std::exit()` skips local destructors - don't rely on it if objects manage resources.

### 3 Tiny Examples

1.

```cpp
int* ptr{ new int{5} };
std::cout << *ptr;  // 5
delete ptr;
ptr = nullptr;
```

2.

```cpp
int size{5};
int* arr{ new int[size]{1, 2, 3, 4, 5} };
std::cout << arr[2]; // 3
delete[] arr;
```

3.

```cpp
class Resource {
    int* m_data{};
public:
    Resource(int val) : m_data{ new int{val} } {}
    ~Resource() { delete m_data; } // automatic cleanup
};
```

### 3 Common Mistakes

- Skipping compiler warnings.
- Using chapter features without understanding prerequisites.
- Not testing edge cases.

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Three allocation types** - static (global/static lifetime), automatic (stack, scope-based), and dynamic (heap, programmer-managed).
- **`new` / `delete`** - allocate/free a single dynamically allocated object on the heap.
- **`new[]` / `delete[]`** - allocate/free a dynamically allocated array.
- **Heap** - a large pool of OS-managed memory; persists until explicitly freed or the program exits.
- **Dangling pointer** - a pointer to memory that has been `delete`d; dereferencing is UB.
- **Memory leak** - allocated memory whose address is lost (pointer reassigned, goes out of scope, etc.).
- **Destructor (`~ClassName()`)** - automatically called when an object is destroyed; used for cleanup.
- **RAII (Resource Acquisition Is Initialization)** - acquire resources in the constructor, release in the destructor, guaranteeing cleanup.
- **Pointer to pointer (`int**`)\*\* - stores the address of another pointer; used for dynamic 2D arrays.
- **Void pointer (`void*`)** - can point to any type but cannot be dereferenced without `static_cast`.

### Section-by-Section Detail

### 19.1 - Dynamic memory allocation with new and delete

- C++ has three memory regions - static storage (globals/statics), the **stack** (locals, limited size), and the **heap** (large, dynamic)
- `int* ptr{ new int{5} };` allocates an `int` on the heap and returns its address; `delete ptr;` frees it
- Failing to `delete` causes a **memory leak**; using `ptr` after `delete` creates a **dangling pointer** → UB
- Set deleted pointers to `nullptr` to avoid accidental dangling dereferences
- Use `new (std::nothrow)` to get `nullptr` on failure instead of an exception

```cpp
int* ptr{ new int{5} };
std::cout << *ptr;  // 5
delete ptr;
ptr = nullptr;
```

→ _See [01_NewAndDelete](../solutions/Chapter_19_Dynamic_Allocation/01_NewAndDelete) for allocation and deallocation basics._

**Memory Region Comparison:**

| Property          | Stack                   | Heap                         | Static/Global         |
| ----------------- | ----------------------- | ---------------------------- | --------------------- |
| **Lifetime**      | Scope-based (automatic) | Until `delete` (manual)      | Entire program        |
| **Size**          | Small (~1-8 MB)         | Large (system RAM)           | Fixed at compile time |
| **Speed**         | O(1) pointer bump       | Slower (allocator search)    | N/A (startup)         |
| **Fragmentation** | None                    | Possible over time           | None                  |
| **Managed by**    | Compiler (RAII)         | Programmer or smart pointers | Compiler/linker       |

### 19.2 - Dynamically allocating arrays

- `int* arr{ new int[size]{} };` allocates an array whose size can be a **runtime** value
- Free with `delete[] arr;` - using plain `delete` is UB
- Dynamic arrays behave like decayed C-style arrays - no built-in size tracking
- Can be initialized with initializer lists since C++11
- C++ has no built-in array resizing - prefer `std::vector` over manual `new[]`/`delete[]`

```cpp
int size{5};
int* arr{ new int[size]{1, 2, 3, 4, 5} };
std::cout << arr[2]; // 3
delete[] arr;
```

→ _See [02_DynamicArrays](../solutions/Chapter_19_Dynamic_Allocation/02_DynamicArrays) for dynamic array creation and cleanup._

### 19.3 - Destructors

- A **destructor** `~ClassName()` is called automatically when an object is destroyed - leaves scope, `delete`d, etc.
- Takes no arguments, no return type, and only one per class
- Used for releasing resources - memory, files, locks
- **RAII** pairs resource acquisition in the constructor with release in the destructor → cleanup guaranteed even during exceptions
- `std::exit()` does **not** call local destructors - avoid relying on it if objects manage resources

```cpp
class Resource {
    int* m_data{};
public:
    Resource(int val) : m_data{ new int{val} } {}
    ~Resource() { delete m_data; } // automatic cleanup
};
```

→ _See [05_Destructors](../solutions/Chapter_19_Dynamic_Allocation/05_Destructors) and [06_RAII](../solutions/Chapter_19_Dynamic_Allocation/06_RAII) for automatic cleanup patterns._

**Resource Management Approaches:**

| Aspect                    | Raw `new`/`delete` | RAII (destructor) | Smart Pointer (`unique_ptr`) |
| ------------------------- | ------------------ | ----------------- | ---------------------------- |
| **Leak on early return?** | Yes                | No                | No                           |
| **Leak on exception?**    | Yes                | No                | No                           |
| **Manual delete needed?** | Yes                | No (destructor)   | No (automatic)               |
| **Ownership clarity**     | Ambiguous          | Class-scoped      | Type-enforced                |
| **Recommendation**        | Avoid              | Good for classes  | Preferred default            |

### 19.4 - Pointers to pointers and dynamic multidimensional arrays

- `int** ptrptr{ &ptr };` stores the address of a pointer - dereference twice (`**ptrptr`) to get the value
- Used for dynamic 2D arrays - allocate an `int**` of row pointers, then `new int[]` for each row
- Deallocate in **reverse order** - free each row first, then the pointer array; mismatched order → UB
- Flatten to a 1D array with `row * cols + col` indexing for simpler, more **cache-friendly** access
- In modern C++, prefer `std::vector<std::vector<int>>` or a flat `std::vector` over raw `int**` arrays

```cpp
int val{42};
int* ptr{&val};
int** ptrptr{&ptr};
std::cout << **ptrptr; // 42
```

→ _See [07_PointersToPointers](../solutions/Chapter_19_Dynamic_Allocation/07_PointersToPointers) for dynamic 2D array creation._

**Dynamic 2D Array Approaches:**

| Approach              | Syntax                             | Cache-Friendly?  | Jagged Rows? | Cleanup                         |
| --------------------- | ---------------------------------- | ---------------- | ------------ | ------------------------------- |
| `int**` (ptr-to-ptr)  | `new int*[rows]` + per-row `new`   | No (scattered)   | Yes          | High (reverse-order `delete[]`) |
| Flat 1D + index math  | `new int[rows*cols]`, `[r*cols+c]` | Yes (contiguous) | No           | Low (single `delete[]`)         |
| `vector<vector<int>>` | Nested vectors                     | No (scattered)   | Yes          | None (automatic)                |
| Flat `vector`         | `vector<int>(rows*cols)`           | Yes (contiguous) | No           | None (automatic)                |

### 19.5 - Void pointers

- `void*` can point to any type but cannot be dereferenced, used in pointer arithmetic, or `delete`d directly
- Must `static_cast` back to the **exact original type** before use - casting to the wrong type → UB
- Sacrifices type safety entirely - mainly a C holdover for legacy APIs and `malloc`/`free` patterns
- In modern C++, prefer function overloading, templates, or `std::variant`/`std::any` for type-generic code

```cpp
int x{5};
void* vp{&x};               // OK: any type
int* ip{static_cast<int*>(vp)};  // must cast back to use
std::cout << *ip;            // 5
```

→ _See [08_VoidPointers](../solutions/Chapter_19_Dynamic_Allocation/08_VoidPointers) for void pointer casting demos._

### Edge Cases and Caveats

❌ `delete` instead of `delete[]` on a dynamic array:

```cpp
int* arr = new int[10];
delete arr; // ❌ UB - must use delete[]
```

✅ Match `new[]` with `delete[]`:

```cpp
delete[] arr; // ✅
```

---

❌ Dereferencing a dangling pointer:

```cpp
int* p = new int{5};
delete p;
std::cout << *p; // ❌ dangling → UB
```

✅ Set to `nullptr` after delete:

```cpp
delete p;
p = nullptr; // ✅ safe to check before use
```

---

❌ Forgetting to `delete`:

```cpp
void leak() {
    int* p = new int{42}; // ❌ memory leak - never freed
}
```

✅ Always pair `new` with `delete`, or use smart pointers.

---

❌ Reassigning a pointer without deleting first:

```cpp
int* p = new int{1};
p = new int{2}; // ❌ first allocation leaked
```

✅ Delete before reassigning:

```cpp
delete p;
p = new int{2}; // ✅
```

---

❌ Double deletion:

```cpp
delete p;
delete p; // ❌ UB - double free
```

✅ Set to `nullptr` after deletion:

```cpp
delete p;
p = nullptr; // ✅ deleting nullptr is safe (no-op)
```

---

❌ Multiple pointers to the same allocation without clear ownership:

```cpp
int* a = new int{5};
int* b = a;
delete a;
std::cout << *b; // ❌ b is dangling
```

✅ Use smart pointers (`std::shared_ptr`) for shared ownership.

---

❌ Not checking `new (std::nothrow)` for `nullptr`:

```cpp
int* p = new (std::nothrow) int;
*p = 5; // ❌ p could be nullptr
```

✅ Check before use:

```cpp
if (p) *p = 5; // ✅
```

---

❌ Wrong deallocation order for 2D arrays:

```cpp
delete[] arr; // ❌ deletes outer array, leaks sub-arrays
```

✅ Delete sub-arrays first:

```cpp
for (int i = 0; i < rows; ++i) delete[] arr[i]; // ✅ sub-arrays first
delete[] arr; // ✅ then the outer array
```

---

❌ Casting `void*` to the wrong type:

```cpp
void* p = new double{3.14};
int* ip = static_cast<int*>(p); // ❌ wrong type → UB
```

✅ Always cast back to the original type.

---

### Hands-On Code Projects

Practice every concept with the hands-on projects in:

```
solutions/Chapter_19_Dynamic_Allocation/
```

| Project                                                                                    | Concept                                              |
| ------------------------------------------------------------------------------------------ | ---------------------------------------------------- |
| [01_NewAndDelete](../solutions/Chapter_19_Dynamic_Allocation/01_NewAndDelete)             | Basic dynamic allocation with `new` and `delete`     |
| [02_DynamicArrays](../solutions/Chapter_19_Dynamic_Allocation/02_DynamicArrays)           | Allocating arrays with `new[]` and `delete[]`        |
| [03_DanglingPointers](../solutions/Chapter_19_Dynamic_Allocation/03_DanglingPointers)     | Dangling pointers and how to avoid them              |
| [04_MemoryLeaks](../solutions/Chapter_19_Dynamic_Allocation/04_MemoryLeaks)               | Common causes of memory leaks                        |
| [05_Destructors](../solutions/Chapter_19_Dynamic_Allocation/05_Destructors)               | Destructors and automatic cleanup                    |
| [06_RAII](../solutions/Chapter_19_Dynamic_Allocation/06_RAII)                             | Resource Acquisition Is Initialization pattern       |
| [07_PointersToPointers](../solutions/Chapter_19_Dynamic_Allocation/07_PointersToPointers) | `int**` and dynamic 2D arrays                        |
| [08_VoidPointers](../solutions/Chapter_19_Dynamic_Allocation/08_VoidPointers)             | Void pointers, casting, and type safety              |
| [09_CommonPitfalls](../solutions/Chapter_19_Dynamic_Allocation/09_CommonPitfalls)         | Mismatched delete, double delete, and other pitfalls |

### Quick Reference

| Feature         | Syntax                              | Notes                           |
| --------------- | ----------------------------------- | ------------------------------- |
| Allocate object | `int* p{ new int{5} };`             | Returns address on heap         |
| Delete object   | `delete p;`                         | Free memory; p becomes dangling |
| Allocate array  | `int* a{ new int[n]{} };`           | Runtime size; value-init        |
| Delete array    | `delete[] a;`                       | Must match `new[]`              |
| nothrow         | `int* p{ new (std::nothrow) int };` | Returns nullptr on failure      |
| Destructor      | `~MyClass() { delete ptr; }`        | Auto-called on destroy          |
| Pointer to ptr  | `int** pp{ &p };`                   | Double dereference: `**pp`      |
| Void pointer    | `void* vp{ &x };`                   | Can't deref directly            |
| Cast void ptr   | `static_cast<int*>(vp)`             | Must know original type         |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is the difference between `delete` and `delete[]`?

<details>
<summary>Show answer</summary>

**Direct answer:** `delete` frees a single dynamically allocated object (`new int`). `delete[]` frees a dynamically allocated array (`new int[n]`). Using `delete` on an array allocation or `delete[]` on a single allocation is undefined behavior - the compiler tracks the element count differently for each.

**Detailed explanation:**

```cpp
int* ptr{ new int{ 42 } };        // single allocation
delete ptr;                         // correct: delete single

int* arr{ new int[100]{} };        // array allocation
delete[] arr;                       // correct: delete array

// delete arr;    // UB: wrong form for array
// delete[] ptr;  // UB: wrong form for single
```

</details>

2. What is a dangling pointer and how do you prevent it?

<details>
<summary>Show answer</summary>

**Direct answer:** A dangling pointer points to memory that has been freed or to a local variable that has gone out of scope. Dereferencing it is undefined behavior. Prevent it by setting pointers to `nullptr` after deleting, avoiding returning addresses of local variables, and using smart pointers (which handle deallocation automatically).

**Detailed explanation:**

```cpp
int* ptr{ new int{ 5 } };
delete ptr;            // memory freed
// *ptr;               // UB: dangling pointer!
ptr = nullptr;         // safe: accessing nullptr is well-defined (crash, not UB)

// Also dangling:
int* dangerous()
{
    int local{ 42 };
    return &local;     // local dies at function exit - returned pointer dangles
}
```

</details>

3. Why should you set a pointer to `nullptr` after deleting it?

<details>
<summary>Show answer</summary>

**Direct answer:** After `delete`, the pointer still holds the old address (now invalid). Accidentally dereferencing it is UB that may silently corrupt data. Setting it to `nullptr` makes accidental dereference a deterministic crash (null pointer dereference) and allows safe conditional checks like `if (ptr)`.

**Detailed explanation:**

```cpp
int* ptr{ new int{ 5 } };
delete ptr;
ptr = nullptr;  // safe sentinel value

if (ptr)           // false - won't accidentally use freed memory
    *ptr = 10;

delete ptr;        // deleting nullptr is safe (no-op)
```

</details>

4. What does `new (std::nothrow)` do differently from regular `new`?

<details>
<summary>Show answer</summary>

**Direct answer:** Regular `new` throws `std::bad_alloc` if allocation fails. `new (std::nothrow)` returns `nullptr` instead of throwing, allowing you to check for failure with a simple `if` statement. In practice, allocation failure is rare on modern systems, and the throwing version is generally preferred because exceptions propagate automatically.

**Detailed explanation:**

```cpp
int* ptr{ new (std::nothrow) int{ 42 } };
if (!ptr)
{
    std::cerr << "Allocation failed!\n";
    return;
}
// use ptr...
delete ptr;
```

</details>

5. How do you properly deallocate a dynamically allocated 2D array?

<details>
<summary>Show answer</summary>

**Direct answer:** Deallocate in reverse order of allocation: first `delete[]` each row, then `delete[]` the array of row pointers. Mismatched order or missing a step causes memory leaks or undefined behavior.

**Detailed explanation:**

```cpp
int rows{ 3 }, cols{ 4 };

// Allocate:
int** grid{ new int*[rows] };
for (int r{ 0 }; r < rows; ++r)
    grid[r] = new int[cols]{};

// Deallocate (reverse order):
for (int r{ 0 }; r < rows; ++r)
    delete[] grid[r];      // free each row first
delete[] grid;              // then free the row pointer array

// Modern alternative - no manual deallocation:
std::vector<std::vector<int>> grid2(rows, std::vector<int>(cols));
```

</details>

6. What is a memory leak and when does the OS reclaim the memory?

<details>
<summary>Show answer</summary>

**Direct answer:** A memory leak occurs when dynamically allocated memory is never freed because all pointers to it are lost (overwritten, out of scope). The leaked memory remains allocated for the program's lifetime. The OS reclaims all of a process's memory when the program terminates, but long-running programs (servers, games) with leaks gradually consume more and more RAM.

**Detailed explanation:**

```cpp
void leak()
{
    int* ptr{ new int{ 42 } };
    // ptr goes out of scope - no delete - memory leaked!
}

void doubleLeak()
{
    int* ptr{ new int{ 1 } };
    ptr = new int{ 2 };    // first allocation leaked - no pointer to it remains
    delete ptr;             // only frees the second allocation
}
```

RAII and smart pointers prevent leaks by tying deallocation to object lifetime.

</details>

7. Why are smart pointers preferred over raw `new`/`delete`?

<details>
<summary>Show answer</summary>

**Direct answer:** Smart pointers (`std::unique_ptr`, `std::shared_ptr`) implement RAII - they automatically call `delete` in their destructor when they go out of scope. This eliminates manual deallocation, prevents memory leaks even during exceptions, and makes ownership semantics explicit in the type system.

**Detailed explanation:**

```cpp
// Raw pointer: easy to leak
void risky()
{
    int* ptr{ new int{ 42 } };
    if (someCondition()) return;  // leak if this returns early!
    delete ptr;
}

// Smart pointer: always cleaned up
void safe()
{
    auto ptr{ std::make_unique<int>(42) };
    if (someCondition()) return;  // ptr's destructor frees memory automatically
}
// No delete needed - ever
```

Rule: never use raw `new`/`delete` in modern C++. Use `std::make_unique` and `std::make_shared`.

</details>

8. What is the danger of having multiple raw pointers to the same allocation?

<details>
<summary>Show answer</summary>

**Direct answer:** Without clear ownership, any pointer might `delete` the memory, leaving the other pointers dangling. Double-delete is also a risk - deleting memory that's already been freed is undefined behavior. Smart pointers solve this: `std::unique_ptr` enforces single ownership, `std::shared_ptr` uses reference counting for shared ownership.

**Detailed explanation:**

```cpp
int* p1{ new int{ 42 } };
int* p2{ p1 };              // p2 also points to the same allocation

delete p1;                   // memory freed
p1 = nullptr;
// *p2 = 10;                // UB: p2 is now dangling!
// delete p2;               // UB: double-delete!
```

</details>

9. What are the three memory regions in C++ and their characteristics?

<details>
<summary>Show answer</summary>

**Direct answer:** **Static storage** holds global/static variables (lifetime = entire program). The **stack** holds local variables and function call frames (fast, limited size ~1-8 MB, LIFO allocation). The **heap** (free store) is for dynamic allocation via `new`/`delete` (large, slower due to allocation overhead, manual or smart-pointer-managed lifetime).

**Detailed explanation:**

```cpp
int g_val{ 10 };                  // static storage - lives until program ends

void foo()
{
    int local{ 20 };              // stack - dies when foo() returns
    int* heap{ new int{ 30 } };   // heap - lives until delete is called
    delete heap;
}
// Stack overflow: too many stack frames (deep recursion) or large local arrays
```

</details>

10. What is `void*` and why should you avoid it in modern C++?

<details>
<summary>Show answer</summary>

**Direct answer:** `void*` is a pointer that can point to any type but cannot be dereferenced, used in arithmetic, or deleted directly - the compiler has no type information. You must `static_cast` back to the exact original type (wrong cast = UB). In modern C++, prefer templates, `std::variant`, `std::any`, or function overloading instead of erasing type information.

**Detailed explanation:**

```cpp
int x{ 42 };
void* vp{ &x };

// *vp;                    // ERROR: can't dereference void*
int* ip{ static_cast<int*>(vp) };  // must cast back to exact type
std::cout << *ip;          // 42

// Modern alternatives:
std::variant<int, double, std::string> v{ 42 };  // type-safe union
std::any a{ 42 };                                  // type-erased value
```

</details>
