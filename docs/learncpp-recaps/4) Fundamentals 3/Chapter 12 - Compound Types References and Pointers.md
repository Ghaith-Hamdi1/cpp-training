# Chapter 12 Recap - Compound Types: References and Pointers

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Lvalue references are aliases, not objects. They must be initialized and cannot be reseated.
- `const&` is the universal binding type - it accepts lvalues, const lvalues, and rvalues.
- **Pass fundamental types by value; pass class types by `const&`.**
- Prefer references over pointers when null is not a valid state.
- Always value-initialize pointers and check for null before dereferencing.
- Never return a local variable by reference - it's immediately dangling.
- Lifetime extension of temporaries only works for local `const&` - **not** across function return boundaries.
- Remember: const before `*` = value is const; const after `*` = pointer is const.

### 3 Tiny Examples

1.

```cpp
int x{ 5 };
int& ref{ x };   // reference - alias for x
int* ptr{ &x };   // pointer - stores address of x
```

2.

```cpp
int x{ 5 };       // x is an lvalue
int y{ x + 1 };   // (x + 1) is an rvalue - temporary result
```

3.

```cpp
int x{ 5 };
int& ref{ x };  // ref is an alias for x
ref = 10;        // x is now 10
```

### 3 Common Mistakes

- Returning a local variable by reference
- Dereferencing a null pointer
- Non-const `&` binding to rvalues

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Compound data types** - types built from fundamental types (references, pointers, arrays, classes, enums, functions).
- **Value categories** - every expression is either an **lvalue** (identifies a persistent object with an address) or an **rvalue** (a temporary value that doesn't persist beyond the expression).
- **Lvalue reference (`&`)** - an alias for an existing lvalue; must be initialized, cannot be reseated, is not itself an object.
- **Lvalue reference to const (`const&`)** - can bind to modifiable lvalues, non-modifiable lvalues, _and_ rvalues; extends the lifetime of bound temporaries.
- **Pointer (`*`)** - an object that holds a memory address; can be reseated, can be null, has its own address.
- **Null pointer (`nullptr`)** - a pointer that points to nothing; dereferencing it is **undefined behavior**.
- **Dangling reference/pointer** - refers to a destroyed object; accessing it is undefined behavior.
- **Pass by value** - copies the argument; changes don't affect the original. Best for fundamental types.
- **Pass by reference** - the function operates on the original object via an alias. Use `const&` unless modification is needed.
- **Pass by address** - passes a pointer; requires null-checking and explicit `&`/`*` syntax. Prefer `const&` when possible.
- **Return by reference** - avoids copying the return value, but the object **must outlive the function call**.
- **`std::optional<T>`** - a wrapper that holds either a value or nothing; cleaner than sentinel values.
- **Top-level const** - const on the object itself (`int* const`); **low-level const** - const on what's pointed/referred to (`const int*`).
- **Type deduction (`auto`)** - drops references and top-level const by default; pointers are kept.

### Section-by-Section Detail

### 12.1 - Introduction to compound data types

- **Fundamental types** (`int`, `double`, `char`, `bool`) are limited to holding single values; **compound types** extend the language by combining or modifying them
- Compound types include functions, arrays, pointers, references, enumerations, structs, and classes
- This chapter focuses on **lvalue references** and **pointers**, the two primary tools for **indirection**
- Understanding references and pointers is essential because they underpin **parameter passing**, dynamic memory, **polymorphism**, and iterator-based algorithms

```cpp
int x{ 5 };
int& ref{ x };   // reference - alias for x
int* ptr{ &x };   // pointer - stores address of x
```

→ _See [01_ValueCategories](../solutions/Chapter_12_References_And_Pointers/01_ValueCategories) for code demonstrating lvalue/rvalue expressions._

### 12.2 - Value categories (lvalues and rvalues)

- Every expression has both a **type** and a **value category** describing whether the result is a persistent object or a temporary
- **Lvalues** evaluate to identifiable objects that persist beyond the expression - variables, references, and dereferenced pointers
- **Rvalues** evaluate to temporary values that exist only within the expression - literals like `5`, the result of `x + 1`"
- An lvalue **implicitly converts** to an rvalue when its value is needed, but an rvalue **cannot** convert to an lvalue
- Understanding value categories is critical for **reference binding**, **move semantics**, and function **overload resolution**

```cpp
int x{ 5 };       // x is an lvalue
int y{ x + 1 };   // (x + 1) is an rvalue - temporary result
```

→ _See [01_ValueCategories](../solutions/Chapter_12_References_And_Pointers/01_ValueCategories) for concrete examples._

### 12.3 - Lvalue references

- An **lvalue reference** (`int& ref{x}`) creates an **alias** for an existing object - they share the same memory
- A reference **must be initialized** at declaration and **cannot be reseated** to refer to a different object afterward
- References are **not objects** - they have no independent storage, no address of their own, and cannot be null
- Non-const lvalue references can only bind to **modifiable lvalues**: you cannot bind them to `const` variables, literals, or rvalues
- This restriction exists because modifying a temporary or `const` value would be semantically meaningless or dangerous

```cpp
int x{ 5 };
int& ref{ x };  // ref is an alias for x
ref = 10;        // x is now 10
```

→ _See [02_LvalueReferences](../solutions/Chapter_12_References_And_Pointers/02_LvalueReferences) for examples of reference creation and aliasing behavior._

### 12.4 - Lvalue references to const

- A `const int&` (**reference to const**) can bind to modifiable lvalues, `const` lvalues, **and** rvalues - the most flexible reference type
- When bound to an rvalue, the compiler creates a **temporary object** and extends its **lifetime** to match the reference's scope
- This **lifetime extension** is why `const&` is the universal parameter type for **read-only access**
- Favor `const&` over non-const `&` unless you specifically need to modify the argument

```cpp
const int& ref1{ x };   // binds to lvalue
const int& ref2{ 5 };   // binds to rvalue - lifetime extended
```

→ _See [03_ReferencesToConst](../solutions/Chapter_12_References_And_Pointers/03_ReferencesToConst) for binding rules and lifetime extension demos._

### 12.5 - Pass by lvalue reference

- Passing by **non-const lvalue reference** (`int& val`) avoids copying and lets the function **modify the original object**
- Useful for functions that update the caller's data, such as `std::swap`
- Non-const reference parameters only accept **modifiable lvalues** - you cannot pass literals, `const` variables, or temporaries
- If you don't need to modify the argument, use `const&` instead, which also accepts rvalues and const lvalues

```cpp
void increment(int& val) { ++val; }
int x{ 5 };
increment(x);  // x is now 6
```

→ _See [04_PassByReference](../solutions/Chapter_12_References_And_Pointers/04_PassByReference) for modification-through-reference examples._

### 12.6 - Pass by const lvalue reference

- Passing by `const&` avoids copies **and** accepts modifiable lvalues, `const` lvalues, and rvalues - the most versatile pass-by-reference form
- Rule of thumb: pass **fundamental types by value** (cheap to copy) and **class types by `const&`** (copying `std::string` is expensive)
- Exception: `std::string_view` should be passed **by value** rather than by `const&` because it's already a lightweight non-owning view
- Prefer `std::string_view` over `const std::string&` for **read-only string parameters**

```cpp
void print(const std::string& s) { std::cout << s; }  // no copy
print("hello");  // rvalue accepted via const&
```

→ _See [05_PassByConstReference](../solutions/Chapter_12_References_And_Pointers/05_PassByConstReference) for the recommended parameter-passing patterns._

**Parameter Passing Mechanism Comparison:**

| Mechanism            | Syntax                  | Copies?     | Modifies original? | Accepts rvalues?  | Best for                |
| -------------------- | ----------------------- | ----------- | ------------------ | ----------------- | ----------------------- |
| **By value**         | `f(int x)`              | Yes         | No                 | Yes               | Fundamental types       |
| **By const ref**     | `f(const T& x)`         | No          | No                 | Yes               | Class types (read-only) |
| **By non-const ref** | `f(T& x)`               | No          | Yes                | No (lvalues only) | In-out parameters       |
| **By address**       | `f(T* ptr)`             | Ptr copied  | Yes (via `*ptr`)   | No                | Nullable/optional args  |
| **By string_view**   | `f(std::string_view s)` | View copied | No                 | Yes               | Read-only strings       |

### 12.7 - Introduction to pointers

- A **pointer** stores a **memory address**; use `&obj` (address-of) to get an address and `*ptr` (dereference) to access the value at that address
- Pointers can be **reseated** (point to a different object) and can be **null** (point to nothing)
- The pointer type must match the pointed-to type (`int*` for `int`)
- Pointer **size** depends on the architecture (4 bytes on 32-bit, 8 bytes on 64-bit), not on the pointed-to type

```cpp
int x{ 5 };
int* ptr{ &x };           // ptr holds address of x
std::cout << *ptr;        // dereference: prints 5
int y{ 10 };
ptr = &y;                 // reseated to point to y
```

→ _See [06_PointersBasics](../solutions/Chapter_12_References_And_Pointers/06_PointersBasics) for address-of, dereference, and reseat examples._

**Lvalue Reference vs Pointer Comparison:**

| Feature                     | Lvalue Reference (`&`) | Pointer (`*`)               |
| --------------------------- | ---------------------- | --------------------------- |
| **Must be initialized**     | Yes                    | No (but should be)          |
| **Can be null**             | No                     | Yes (`nullptr`)             |
| **Can be reseated**         | No (bound for life)    | Yes                         |
| **Is an object**            | No (alias)             | Yes (has own address)       |
| **Access syntax**           | Direct use             | Dereference `*ptr`          |
| **Creation syntax**         | `int& ref{x}`          | `int* ptr{&x}`              |
| **Multi-level indirection** | No                     | Yes (`int**`)               |
| **Prefer when**             | Null not valid         | Null valid or reseat needed |

### 12.8 - Null pointers

- `nullptr` (C++11) represents a pointer that **points to nothing**; always value-initialize pointers and check for null before dereferencing
- Dereferencing `nullptr` is **undefined behavior** - it may crash, silently corrupt memory, or appear to work
- Use `nullptr` instead of `0` or `NULL` for type safety
- Favor **references over pointers** when null is not a valid state

```cpp
int* ptr{ nullptr };
if (ptr)                   // check before dereferencing
    std::cout << *ptr;
```

→ _See [07_NullPointers](../solutions/Chapter_12_References_And_Pointers/07_NullPointers) for null-checking patterns and UB demos._

### 12.9 - Pointers and const

- A **pointer to const** (`const int* ptr`) allows pointing at a `const` or non-const object but prevents modifying the value through the pointer
- A **const pointer** (`int* const ptr`) cannot be reseated but allows modifying the value it points to
- A **const pointer to const** (`const int* const ptr`) can do neither - most restrictive form
- Prefer **pointers to const** unless the function genuinely needs to modify the pointed-to value

```cpp
int x{ 5 };
const int* ptrToConst{ &x };  // can't modify *ptrToConst
int* const constPtr{ &x };    // can't repoint constPtr
```

→ _See [08_PointersAndConst](../solutions/Chapter_12_References_And_Pointers/08_PointersAndConst) for all four combinations demonstrated._

**Pointer → const Combinations:**

| Declaration            | Read as                            | Value modifiable? | Pointer resettable? |
| ---------------------- | ---------------------------------- | ----------------- | ------------------- |
| `int* ptr`             | pointer to int                     | Yes               | Yes                 |
| `const int* ptr`       | pointer to **const** int           | No                | Yes                 |
| `int* const ptr`       | **const** pointer to int           | Yes               | No                  |
| `const int* const ptr` | **const** pointer to **const** int | No                | No                  |

> **Memory aid:** Read right-to-left. `const` before `*` → can't change pointed-to value. `const` after `*` → can't change pointer itself.

### 12.10 - Pass by address

- **Pass by address** sends a pointer to a function so the function can access or modify the original object via `*ptr`
- Always **null-check** the pointer inside the function before dereferencing
- Pass by address lets you express **optional arguments** by passing `nullptr` when a value isn't available
- When only reading, use `const int* ptr` to prevent accidental modification
- Prefer **pass by reference** over pass by address unless null is a valid input

```cpp
void nullify(int* ptr) { if (ptr) *ptr = 0; }
int x{ 5 };
nullify(&x);  // x is now 0
```

→ _See [09_PassByAddress](../solutions/Chapter_12_References_And_Pointers/09_PassByAddress) for pass-by-address patterns with null-checking._

### 12.11 - Pass by address (part 2)

- **Pass by address** and **pass by reference** both provide indirect access, but references are **safer** (no null, no pointer arithmetic)
- Pass by `const&` is the default for **non-trivial read-only** parameters; **non-const `&`** for output parameters
- Use **pass by address** only when `nullptr` is a meaningful sentinel or when interfacing with C or legacy APIs
- `std::optional` often replaces pass-by-address for optional parameters with cleaner semantics

```cpp
void log(const std::string& msg, std::ostream* out = nullptr)
{
    if (out) *out << msg;  // only writes if caller provides a stream
}
```

### 12.12 - Return by reference and return by address

- **Return by reference** (`int& get()`) avoids a copy and returns an alias to an existing object - the object **must outlive** the reference
- **Never** return a reference or pointer to a **local variable**; its memory is freed when the function returns, causing **dangling**
- Return by reference is appropriate when the object lives in a higher scope, is `static`, or is a member of a persistent container
- Return by address (`int* get()`) follows the same lifetime rules; use it when returning `nullptr` is meaningful
- For **most functions**, return by **value** - the compiler applies **copy elision** (RVO/NRVO) to eliminate the copy

```cpp
const std::string& larger(const std::string& a, const std::string& b)
{
    return (a.size() >= b.size()) ? a : b;  // safe - params outlive call
}
```

→ _See [10_ReturnByReference](../solutions/Chapter_12_References_And_Pointers/10_ReturnByReference) and [11_DanglingReferencesAndPointers](../solutions/Chapter_12_References_And_Pointers/11_DanglingReferencesAndPointers) for safe vs. dangling examples._

### 12.13 - In and out parameters

- **In parameters** are read-only inputs (pass by value or `const&`); **out parameters** return results through a reference or pointer
- **In-out parameters** serve both roles - the function reads the current value and modifies it in place
- Out/in-out parameters use **non-const references or pointers** and are only needed when a function must return **multiple results** or modify the caller's object
- Prefer **return by value** over out parameters for single results; use `std::tuple` or a struct for multiple results
- Non-const reference out parameters hurt readability at the call site - the caller can't tell from the call syntax that the argument may be modified

```cpp
void getCenter(const Rectangle& r, int& outX, int& outY)  // out params
{
    outX = r.x + r.w / 2;
    outY = r.y + r.h / 2;
}
```

→ _See [12_InOutParameters](../solutions/Chapter_12_References_And_Pointers/12_InOutParameters) for in, out, and in-out patterns._

### 12.14 - Type deduction with pointers, references, and const

- `auto` deduces the type of a variable from its initializer, **dropping references and top-level `const`** by default
- `auto&` forces an lvalue reference; `const auto&` forces a reference to const - useful for avoiding copies
- `auto*` forces a pointer deduction; `const auto*` deduces a pointer to const
- `auto&&` deduces a **forwarding reference**, binding to both lvalues and rvalues - used in templates and perfect forwarding
- Rule of thumb: use plain `auto` for values, `const auto&` for read-only references, `auto&` when modification through the reference is intended

```cpp
int x{ 5 };
const int& cref{ x };
auto a{ cref };        // int  (drops ref + const)
const auto& b{ x };   // const int&
auto* p{ &x };         // int*
```

→ _See [13_TypeDeductionPointersRefs](../solutions/Chapter_12_References_And_Pointers/13_TypeDeductionPointersRefs) for auto-deduction behavior with pointers and refs._

**auto Deduction with References and Pointers:**

| Source type  | `auto x = src`         | `auto& x = src` | `const auto& x = src` |
| ------------ | ---------------------- | --------------- | --------------------- |
| `int`        | `int`                  | `int&`          | `const int&`          |
| `const int`  | `int` (drops const)    | `const int&`    | `const int&`          |
| `int&`       | `int` (drops ref)      | `int&`          | `const int&`          |
| `const int&` | `int` (drops both)     | `const int&`    | `const int&`          |
| `int*`       | `int*` (preserves ptr) | `int*&`         | `int* const&`         |

> **Key rule:** `auto` drops top-level `const` and references. `auto&` preserves them. `auto*` deduces to pointer and preserves low-level `const`.

### 12.15 - std::optional

- `std::optional<T>` (C++17, `<optional>`) holds either a value of type `T` **or nothing**, replacing the common `sentinel_value` / `bool` + out-parameter patterns
- Check if a value is present with `.has_value()` or an implicit `bool` conversion; access it via `.value()` (throws on empty) or `*opt` (UB on empty)
- `.value_or(default)` returns the stored value if present, otherwise the provided default - avoids branching
- Ideal for functions that may legitimately have **no result** (e.g., finding an element in a container, parsing an optional config field)
- `std::optional` adds a small overhead (stores a `bool` flag alongside the value), so avoid wrapping types that already have a natural null state (pointers, `std::string_view`)

```cpp
std::optional<int> findIndex(std::string_view name)
{
    if (name == "alice") return 0;
    return std::nullopt;  // not found
}
```

→ _See [14_StdOptional](../solutions/Chapter_12_References_And_Pointers/14_StdOptional) for optional usage and error-value replacement patterns._

### Edge Cases and Caveats

- **Returning a local variable by reference** - dangling reference.

  ❌ **Bad:**

  ```cpp
  const std::string& getName() { std::string s{"hi"}; return s; } // dangling!
  ```

  ✅ **Good:** Return by value; move semantics avoid the copy.

- **Dereferencing a null pointer** - undefined behavior.

  ❌ **Bad:** `int* p{ nullptr }; std::cout << *p;`
  ✅ **Good:** Always null-check before dereferencing.

- **Non-const `&` binding to rvalues** - won't compile.

  ❌ **Bad:** `int& r{ 5 };` - can't bind non-const ref to literal.
  ✅ **Good:** `const int& r{ 5 };` - ok, lifetime extended.

- **Confusing `const int*` with `int* const`** - different things.

  ❌ **Bad:** Thinking `const int*` means the pointer can't change.
  ✅ **Good:** `const int*` = pointer to const value. `int* const` = const pointer to mutable value.

- **Assuming pass-by-address modifies the caller's pointer** - pointer is copied.

  ❌ **Bad:** `void f(int* p) { p = &other; }` - caller’s pointer unchanged.
  ✅ **Good:** Pass `int*&` or `int**` to modify the caller's pointer.

- **Not null-checking a pointer parameter** -

  ❌ **Bad:** `void f(int* p) { std::cout << *p; }` - crashes if null.
  ✅ **Good:** `if (!p) return;` or assert non-null.

- **Expecting lifetime extension across returns** - only works locally.

  ❌ **Bad:** Returning `const&` to a temporary from a function.
  ✅ **Good:** Return by value for temporaries; extend only with local `const&`.

- **`auto` dropping `const` and `&`** -

  ❌ **Bad:** `auto x = constRef;` - mutable copy, not a reference.
  ✅ **Good:** `const auto& x = constRef;`

- **`std::optional::value()` without checking** - throws `std::bad_optional_access`.

  ❌ **Bad:** `opt.value()` on an empty optional.
  ✅ **Good:** `if (opt.has_value()) ... opt.value()` or `opt.value_or(default)`.

- **Dangling pointer after `delete`** -

  ❌ **Bad:** `delete ptr;` then using `ptr`.
  ✅ **Good:** `delete ptr; ptr = nullptr;`

---

### Hands-On Code Projects

Practice every concept with the hands-on projects in:

```
solutions/Chapter_12_References_And_Pointers/
```

| Project                                                                                                               | Concept                                                       |
| --------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------- |
| [01_ValueCategories](../solutions/Chapter_12_References_And_Pointers/01_ValueCategories)                             | Lvalues vs rvalues, implicit conversions between them         |
| [02_LvalueReferences](../solutions/Chapter_12_References_And_Pointers/02_LvalueReferences)                           | Basic lvalue references - aliases for existing objects        |
| [03_ReferencesToConst](../solutions/Chapter_12_References_And_Pointers/03_ReferencesToConst)                         | `const&` binding rules and lifetime extension of temporaries  |
| [04_PassByReference](../solutions/Chapter_12_References_And_Pointers/04_PassByReference)                             | Pass by non-const lvalue reference - modifying the original   |
| [05_PassByConstReference](../solutions/Chapter_12_References_And_Pointers/05_PassByConstReference)                   | Pass by `const&` - the default for class types                |
| [06_PointersBasics](../solutions/Chapter_12_References_And_Pointers/06_PointersBasics)                               | Pointers, address-of (`&`), dereference (`*`)                 |
| [07_NullPointers](../solutions/Chapter_12_References_And_Pointers/07_NullPointers)                                   | `nullptr`, null checks, and undefined behavior                |
| [08_PointersAndConst](../solutions/Chapter_12_References_And_Pointers/08_PointersAndConst)                           | Pointer to const, const pointer, and both                     |
| [09_PassByAddress](../solutions/Chapter_12_References_And_Pointers/09_PassByAddress)                                 | Passing pointers to functions, null-checking                  |
| [10_ReturnByReference](../solutions/Chapter_12_References_And_Pointers/10_ReturnByReference)                         | Returning references safely, dangling pitfalls                |
| [11_DanglingReferencesAndPointers](../solutions/Chapter_12_References_And_Pointers/11_DanglingReferencesAndPointers) | Identifying and avoiding dangling references and pointers     |
| [12_InOutParameters](../solutions/Chapter_12_References_And_Pointers/12_InOutParameters)                             | In, out, and in-out parameter patterns                        |
| [13_TypeDeductionPointersRefs](../solutions/Chapter_12_References_And_Pointers/13_TypeDeductionPointersRefs)         | `auto` behavior with pointers, references, and const          |
| [14_StdOptional](../solutions/Chapter_12_References_And_Pointers/14_StdOptional)                                     | `std::optional` as a modern alternative to sentinels and null |

### Quick Reference

| Feature              | Syntax                        | Notes                                   |
| -------------------- | ----------------------------- | --------------------------------------- |
| Lvalue reference     | `int& ref{x};`                | Alias; must init; can't reseat          |
| Const reference      | `const int& ref{x};`          | Binds to lvalues + rvalues              |
| Pointer              | `int* ptr{&x};`               | Stores address; can reseat; can be null |
| Null pointer         | `int* ptr{nullptr};`          | Points to nothing; never deref          |
| Pointer to const     | `const int* ptr{&x};`         | Value is read-only through ptr          |
| Const pointer        | `int* const ptr{&x};`         | Pointer can't be reseated               |
| Both const           | `const int* const ptr{&x};`   | Neither value nor pointer can change    |
| Address-of           | `&x`                          | Gets memory address of x                |
| Dereference          | `*ptr`                        | Gets value at address                   |
| Pass by value        | `void f(int x)`               | Copy - for fundamentals                 |
| Pass by const ref    | `void f(const int& x)`        | No copy - for class types               |
| Pass by address      | `void f(int* ptr)`            | Pointer - check for null                |
| Return by ref        | `int& f()`                    | Object must outlive function            |
| `std::optional`      | `std::optional<int> opt{42};` | Value or `std::nullopt`                 |
| Auto drops ref       | `auto x = ref;`               | x is a copy, not a reference            |
| Auto keeps ptr       | `auto p = &x;`                | p is `int*`                             |
| Auto drops top const | `auto x = cval;`              | x is non-const copy                     |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is the difference between an **lvalue** and an **rvalue**?

<details>
<summary>Show answer</summary>

**Direct answer:** An lvalue evaluates to an identifiable object that persists beyond the expression (e.g., variables, references, dereferenced pointers). An rvalue evaluates to a temporary value that exists only for the duration of the expression (e.g., literals like `5`, the result of `x + 1`, function return values by value). An lvalue can implicitly convert to an rvalue, but not vice versa.

**Detailed explanation:**
The key distinction: lvalues have a persistent memory address you can take with `&`. Rvalues don't - you can't write `&5` or `&(x + 1)`. This matters because non-const lvalue references can only bind to lvalues, while const lvalue references can bind to both lvalues and rvalues (via lifetime extension for rvalues).

```cpp
int x{ 5 };       // x is an lvalue
int y{ x + 1 };   // (x + 1) is an rvalue - temporary, no address
int& ref{ x };    // OK: lvalue reference binds to lvalue
// int& bad{ 5 }; // ERROR: non-const lvalue ref can't bind to rvalue
const int& ok{ 5 }; // OK: const ref binds to rvalue (lifetime extended)
```

</details>

2. When should you pass by `const&` vs `std::string_view`?

<details>
<summary>Show answer</summary>

**Direct answer:** Use `const&` as the default for any class type that is expensive to copy (e.g., `std::string`, `std::vector`). Use `std::string_view` (by value) specifically for read-only string parameters - it avoids creating a temporary `std::string` when a string literal or C-string is passed, and it's cheaper because it's just a pointer + length.

**Detailed explanation:**
Rule of thumb: pass fundamental types (`int`, `double`, `bool`) by value (cheap to copy), pass class types by `const&`, and use `std::string_view` as a special case for strings. Pass by non-const reference (`int&`) only when the function needs to modify the caller's data.

```cpp
void print(std::string_view sv);     // best for read-only strings
void process(const std::vector<int>& v); // const& for other class types
void update(int& count);              // non-const ref for output parameters
void square(int x);                   // by value for cheap types
```

</details>

3. What is the difference between `const int*` and `int* const`?

<details>
<summary>Show answer</summary>

**Direct answer:** `const int*` (pointer to const) means the pointed-to value cannot be modified through this pointer, but the pointer itself can be reseated to point elsewhere. `int* const` (const pointer) means the pointer cannot be reseated, but the pointed-to value can be modified. Read declarations right-to-left: "const pointer to int" vs. "pointer to const int."

**Detailed explanation:**

```cpp
int x{ 5 }, y{ 10 };

const int* p1{ &x };  // pointer to const - can't modify *p1
// *p1 = 20;          // ERROR
p1 = &y;              // OK: pointer can be reseated

int* const p2{ &x };  // const pointer - can't repoint
*p2 = 20;             // OK: can modify value
// p2 = &y;           // ERROR: pointer is const

const int* const p3{ &x };  // both const - can't modify or repoint
```

</details>

4. Why should you prefer references over pointers when null is not a valid state?

<details>
<summary>Show answer</summary>

**Direct answer:** References cannot be null - they must be bound to a valid object at initialization and cannot be reseated. This eliminates an entire class of bugs (null pointer dereference). If a function always needs a valid object, use a reference parameter to make it impossible to pass null, rather than a pointer with a null-check.

**Detailed explanation:**
Pointers should be used when null is a valid state (e.g., optional output parameters), when you need to reseat to a different object, or when working with arrays/dynamic memory. References communicate "this will always be valid" at the type level, which is both safer and more readable. Always initialize pointers - use `nullptr` for "points to nothing" - and check for null before dereferencing.

</details>

5. What is **lifetime extension**, and when does it NOT work?

<details>
<summary>Show answer</summary>

**Direct answer:** When a `const&` binds to an rvalue, the compiler creates a temporary object and extends its lifetime to match the lifetime of the reference. This does NOT work across function return boundaries - returning a `const&` to a local variable creates a dangling reference because the local is destroyed when the function exits, and lifetime extension doesn't apply to return values.

**Detailed explanation:**

```cpp
const int& ref{ 5 };  // lifetime extension - temporary lives as long as ref

const std::string& bad()
{
    std::string local{ "hello" };
    return local;  // DANGLING: local destroyed, no lifetime extension on return
}

// Safe: returning a reference to a caller-owned object
const std::string& safe(const std::string& s)
{
    return s;  // OK: s outlives this function call
}
```

</details>

6. What does `auto` do with `const` and `&`? How do you preserve them?

<details>
<summary>Show answer</summary>

**Direct answer:** `auto` drops references and top-level `const` but preserves pointers and low-level `const` (const on the pointed-to type). To preserve the reference, write `auto&` or `const auto&`. To preserve const, write `const auto`.

**Detailed explanation:**

```cpp
const int x{ 5 };
const int& cref{ x };

auto a{ cref };         // int (reference AND const dropped - a is a copy)
auto& b{ cref };        // const int& (reference kept, const preserved because it's low-level)
const auto c{ cref };   // const int (const explicitly reapplied)
auto* p{ &x };          // const int* (pointer preserved, low-level const preserved)
```

</details>

7. When is `std::optional` preferred over sentinel values like `-1`?

<details>
<summary>Show answer</summary>

**Direct answer:** Use `std::optional<T>` when a function may legitimately have no result to return, and there's no natural sentinel value - or when using a sentinel would reduce the valid range of return values. It's type-safe, self-documenting ("this may not produce a result"), and doesn't require the caller to know which magic value means "failure."

**Detailed explanation:**
Check via `has_value()` or boolean context (`if (opt)`). Access via `value()` (throws if empty) or `*opt` (undefined behavior if empty - faster but unsafe).

```cpp
std::optional<int> findIndex(const std::vector<int>& v, int target)
{
    for (int i{ 0 }; i < static_cast<int>(v.size()); ++i)
        if (v[i] == target)
            return i;
    return std::nullopt;  // clearly "not found"
}

auto result{ findIndex(vec, 42) };
if (result)
    std::cout << "Found at " << *result;
```

</details>

8. What is a **dangling reference**, and how do you avoid creating one?

<details>
<summary>Show answer</summary>

**Direct answer:** A dangling reference is a reference that refers to an object that has been destroyed. Accessing it is undefined behavior. The most common cause is returning a reference to a local variable from a function. Avoid it by never returning references to local variables - only return references to objects that outlive the function call (e.g., reference parameters, static variables, or class members).

**Detailed explanation:**
Dangling pointers are the pointer equivalent (pointing to freed memory). Both are among the most common and dangerous bugs in C++. The compiler may not warn about dangling references, so you must be disciplined about object lifetimes.

```cpp
const std::string& getName()
{
    std::string name{ "Alice" };
    return name;   // DANGLING - name destroyed at function exit
}
// Caller gets a reference to destroyed memory - undefined behavior
```

</details>

9. What does the **address-of** operator (`&`) return, and what is the **dereference** operator (`*`)?

<details>
<summary>Show answer</summary>

**Direct answer:** `&x` returns a pointer holding the memory address of `x`. `*ptr` (dereference) accesses the value at the address stored in the pointer. They are inverses: `*(&x)` gives back `x`.

**Detailed explanation:**

```cpp
int x{ 42 };
int* ptr{ &x };       // ptr holds address of x
std::cout << *ptr;     // prints 42 (dereference - access value at address)
*ptr = 100;            // modifies x through the pointer
std::cout << x;        // prints 100
```

</details>

10. Why should you pass by non-const reference only when the function needs to modify the argument?

<details>
<summary>Show answer</summary>

**Direct answer:** Non-const lvalue references only accept modifiable lvalue arguments - you can't pass literals, const variables, or temporaries. Using non-const `&` when you don't need to modify the argument unnecessarily restricts what callers can pass. Use `const&` instead for read-only access, which accepts lvalues, const lvalues, and rvalues.

**Detailed explanation:**
Non-const reference parameters also signal intent to callers: "this function will modify your variable." Using `const&` signals "this function will only read." Clear intent at the interface level prevents bugs and makes code self-documenting.

</details>
