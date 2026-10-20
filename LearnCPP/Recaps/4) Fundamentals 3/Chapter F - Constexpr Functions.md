# Chapter F Recap - Constexpr Functions

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- `constexpr` on a function means "can be used in a constant expression," **not** "will always evaluate at compile-time"
- Compile-time evaluation is **guaranteed** only when the constexpr call appears where a constant expression is _required_ (e.g., initializing a `constexpr` variable)
- In non-required contexts, the compiler _may_ evaluate at compile-time but is not obligated to
- Use `consteval` (C++20) when a function **must** evaluate at compile-time; any runtime call is a compile error
- Function parameters of constexpr/consteval functions are **not** constexpr; you cannot use them to initialize `constexpr` variables inside the function
- Constexpr functions are **implicitly inline**. Define them in headers when shared across translation units
- A function that _can_ be part of a constant expression (especially a pure function) **should** be `constexpr` - even if you only call it at runtime today
- Don't `constexpr` a function that genuinely cannot be evaluated at compile-time (e.g., it does I/O)

### 3 Tiny Examples

1.

```cpp
constexpr int square(int x) { return x * x; }
constexpr int val{ square(5) };  // compile-time: val == 25
int n{ 3 };
int rt{ square(n) };             // runtime: n is not constexpr
```

2.

```cpp
constexpr int add(int a, int b) { return a + b; }
constexpr int sum{ add(3, 4) };  // guaranteed compile-time
int x{ add(3, 4) };              // may or may not be compile-time
```

3.

```cpp
consteval int cube(int x) { return x * x * x; }
constexpr int val{ cube(3) };  // OK: compile-time → 27
// int n{3}; cube(n);          // error: n is not a constant expression
```

### 3 Common Mistakes

- Skipping compiler warnings.
- Using chapter features without understanding prerequisites.
- Not testing edge cases.

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Constexpr function** - a function marked `constexpr` that is _allowed_ to be called in a constant expression. It can evaluate at compile-time or runtime depending on context.
- **Consteval function (C++20)** - a function marked `consteval` (an _immediate function_) that _must_ evaluate at compile-time; passing non-constant arguments is a compile error.
- **Constant-evaluated context** - a context where a constant expression is _required_ (e.g., initializing a `constexpr` variable). Constexpr function calls here are guaranteed to evaluate at compile-time.
- **Implicitly inline** - constexpr/consteval functions are implicitly inline to satisfy ODR when included in multiple translation units.
- **Pure function** - a function with no side effects that always returns the same result for the same arguments. Pure functions are prime candidates for `constexpr`.
- **`std::is_constant_evaluated()` / `if consteval` (C++23)** - utilities that check whether the function is executing in a _required_ constant context (not simply "at compile-time").

### Section-by-Section Detail

### F.1 - Constexpr functions

- A **constexpr function** can be evaluated at **compile time** when called with constant arguments, or at **runtime** otherwise
- Declare with `constexpr` before the return type; the body must contain only constructs the compiler can evaluate at compile time
- Results used in a **constant expression** context (e.g., `constexpr int x = func();`) are guaranteed to be computed at compile time
- `constexpr` functions are **implicitly inline**, so they should be defined in header files

```cpp
constexpr int square(int x) { return x * x; }
constexpr int val{ square(5) };  // compile-time: val == 25
int n{ 3 };
int rt{ square(n) };             // runtime: n is not constexpr
```

→ _See [01_Constexpr_Function_Basics](../solutions/Chapter_F_Constexpr_Functions/01_Constexpr_Function_Basics/) for basic constexpr functions used in both contexts._

### F.2 - Constexpr functions (part 2)

- **`consteval`** (C++20) forces a function to be evaluated at **compile time only** - a runtime call is a compiler error
- Use `consteval` when the result is **always** needed at compile time (e.g., generating lookup tables, compile-time hashing)
- `consteval` functions are implicitly inline, just like `constexpr` functions
- Prefer `constexpr` for flexibility unless you must **enforce** compile-time evaluation

```cpp
constexpr int add(int a, int b) { return a + b; }
constexpr int sum{ add(3, 4) };  // guaranteed compile-time
int x{ add(3, 4) };              // may or may not be compile-time
```

→ _See [02_Compile_Time_Guarantee](../solutions/Chapter_F_Constexpr_Functions/02_Compile_Time_Guarantee/) for when evaluation is guaranteed vs optional · [05_Parameters_Are_Not_Constexpr](../solutions/Chapter_F_Constexpr_Functions/05_Parameters_Are_Not_Constexpr/) for the parameter-not-constexpr rule._

**Compile-Time Evaluation Guarantee Contexts:**

| Context                     | Compile-time guaranteed?  | Example                     |
| --------------------------- | ------------------------- | --------------------------- |
| `constexpr` variable init   | Yes                       | `constexpr int x{ f(5) };`  |
| Template argument           | Yes                       | `std::array<int, f(5)>`     |
| `static_assert`             | Yes                       | `static_assert(f(5) == 25)` |
| C-array size                | Yes                       | `int arr[f(5)]`             |
| Non-constexpr variable init | Maybe (compiler's choice) | `int x{ f(5) };`            |
| Function argument           | Maybe (compiler's choice) | `g(f(5))`                   |

> **Key insight:** To guarantee compile-time evaluation, store the result in a `constexpr` variable or use it in a context that requires a constant expression.

### F.3 - Constexpr functions (part 3) and consteval

- **`if constexpr`** (C++17) evaluates the condition at compile time and **discards** the false branch from codegen entirely
- Essential in templates to select code paths based on type traits without triggering compilation errors in the discarded branch
- The condition must be a **constant expression** - variables, function calls, or type traits that resolve at compile time
- Replaces SFINAE and `std::enable_if` for many template branching use cases

```cpp
consteval int cube(int x) { return x * x * x; }
constexpr int val{ cube(3) };  // OK: compile-time → 27
// int n{3}; cube(n);          // error: n is not a constant expression
```

→ _See [03_Consteval_Immediate_Functions](../solutions/Chapter_F_Constexpr_Functions/03_Consteval_Immediate_Functions/) for `consteval` · [04_Constexpr_vs_Consteval](../solutions/Chapter_F_Constexpr_Functions/04_Constexpr_vs_Consteval/) for a side-by-side comparison · [08_Is_Constant_Evaluated](../solutions/Chapter_F_Constexpr_Functions/08_Is_Constant_Evaluated/) for `std::is_constant_evaluated()` and `if consteval`._

**constexpr vs consteval Comparison:**

| Feature                     | `constexpr`                          | `consteval` (C++20)          |
| --------------------------- | ------------------------------------ | ---------------------------- |
| **Compile-time evaluation** | Allowed, not guaranteed              | **Always** required          |
| **Runtime fallback**        | Yes - evaluates at runtime if needed | No - compile error           |
| **Parameters constexpr?**   | No (parameters are never constexpr)  | No                           |
| **Implicitly inline?**      | Yes                                  | Yes                          |
| **Non-constant arguments**  | Evaluated at runtime                 | Compile error                |
| **Use case**                | Dual-use (compile + runtime)         | Compile-time only guarantees |

### F.4 - Constexpr functions (part 4)

- `constexpr` / `consteval` functions can use `if constexpr`, loops, local variables, and (C++20) `std::vector` / `std::string` in limited ways
- **Compile-time limitations**: no `goto`, no `try`/`catch`, no `reinterpret_cast`, no calls to non-`constexpr` functions
- C++20 expanded constexpr to allow **dynamic allocation** during constant evaluation, provided memory is freed before evaluation ends
- Use `std::is_constant_evaluated()` (C++20) or `if consteval` (C++23) to branch between compile-time and runtime logic inside the same function

```cpp
constexpr int sumTo(int n) {
    int total{ 0 };           // non-const local - fine in constexpr
    for (int i{ 1 }; i <= n; ++i)
        total += i;
    return total;
}
constexpr int result{ sumTo(10) };  // 55, computed at compile-time
```

→ _See [06_Constexpr_Locals_And_Mutation](../solutions/Chapter_F_Constexpr_Functions/06_Constexpr_Locals_And_Mutation/) for local mutation and when to apply `constexpr`._

> **When to Use constexpr / consteval:**
>
> - Pure function (no side effects, deterministic) - mark `constexpr`
> - Must always evaluate at compile-time - mark `consteval`
> - Function does I/O (`cout`, `cin`, file) - **cannot** be constexpr
> - Heap allocation (pre-C++20) - **cannot** be constexpr
> - Only called at runtime today - still mark `constexpr` for future flexibility

### F.X - Chapter F summary and quiz

- Constexpr functions bridge **compile-time** and **runtime** computation - one definition, two execution contexts
- `consteval` enforces compile-time-only evaluation; `constexpr` allows both
- `if constexpr` enables **zero-cost branching** in templates by discarding unused code paths at compile time
- Moving computation to compile time reduces runtime cost but increases build time and binary size if overused

```cpp
// Quiz pattern: identify what can be constexpr
constexpr int double_it(int x) { return x * 2; }  // pure → constexpr
void print(int x) { std::cout << x; }             // I/O → cannot be constexpr
```

→ _See [07_Testing_In_Constant_Context](../solutions/Chapter_F_Constexpr_Functions/07_Testing_In_Constant_Context/) for the quiz solution._

### Edge Cases and Caveats

❌ Assuming constexpr means "always compile-time":

```cpp
constexpr int square(int x) { return x * x; }
int n = 5;
int result = square(n); // ❌ evaluated at runtime - n is not constexpr
```

✅ Only guaranteed at compile-time in contexts that _require_ constant expressions:

```cpp
constexpr int result = square(5); // ✅ forced compile-time
```

---

❌ Trying to declare function parameters as `constexpr`:

```cpp
constexpr int square(constexpr int x) { return x * x; } // ❌ illegal
```

✅ Parameters are never constexpr. Use `consteval` if the function must always be compile-time.

---

❌ Using a constexpr function parameter to initialize a `constexpr` local:

```cpp
constexpr int foo(int x) {
    constexpr int y = x; // ❌ x is not a constant expression inside the body
    return y;
}
```

✅ Use a non-constexpr local, or use `if consteval` for branching.

---

❌ Never testing a constexpr function in a constant context:

```cpp
constexpr int compute(int x) { /* complex logic */ }
int result = compute(5); // ❌ works at runtime but may fail at compile-time
```

✅ Test with `static_assert` or `constexpr` variable:

```cpp
static_assert(compute(5) == 25); // ✅ forces compile-time evaluation
```

---

❌ Forgetting that constexpr functions need full definitions:

```cpp
// header.h
constexpr int square(int x); // ❌ forward declaration only - can't evaluate
```

✅ Put the full definition in the header.

---

❌ Marking I/O functions as constexpr:

```cpp
constexpr void print(int x) { std::cout << x; } // ❌ can't do I/O at compile-time
```

✅ Don't mark functions with I/O as constexpr.

---

❌ Confusing `std::is_constant_evaluated()`:

```cpp
constexpr int foo() {
    if (std::is_constant_evaluated()) return 1;
    return 2;
}
int x = foo(); // ❌ may return 1 OR 2 depending on context
```

✅ It returns `true` only in _required_ constant contexts. Prefer `if consteval` (C++23).

---

### Hands-On Code Projects

| #   | Project                            | Concept                                                              |
| --- | ---------------------------------- | -------------------------------------------------------------------- |
| 01  | `01_Constexpr_Function_Basics`     | Basic constexpr functions - compile-time and runtime usage           |
| 02  | `02_Compile_Time_Guarantee`        | When compile-time evaluation is guaranteed vs optional               |
| 03  | `03_Consteval_Immediate_Functions` | `consteval` (C++20) - functions that _must_ evaluate at compile-time |
| 04  | `04_Constexpr_vs_Consteval`        | Side-by-side comparison of `constexpr` and `consteval`               |
| 05  | `05_Parameters_Are_Not_Constexpr`  | Why function parameters are never constexpr (common pitfall)         |
| 06  | `06_Constexpr_Locals_And_Mutation` | Constexpr functions can declare and mutate non-const local variables |
| 07  | `07_Testing_In_Constant_Context`   | Always test constexpr functions in a compile-time context            |
| 08  | `08_Is_Constant_Evaluated`         | `std::is_constant_evaluated()` and `if consteval` (C++23)            |

> **Path:** `solutions/Chapter_F_Constexpr_Functions/01_Constexpr_Function_Basics/main.cpp` … `08_Is_Constant_Evaluated/main.cpp`

### Quick Reference

| Feature               | Syntax / Usage                                    | Notes                              |
| --------------------- | ------------------------------------------------- | ---------------------------------- |
| constexpr function    | `constexpr int f(int x) { return x * 2; }`        | Compile-time or runtime            |
| consteval function    | `consteval int f(int x) { return x * 2; }`        | Compile-time only (C++20)          |
| Force compile-time    | `constexpr int val = f(5);`                       | Required constant context          |
| Check context         | `if consteval { ... }`                            | C++23 - is this required constant? |
| Check context (C++20) | `std::is_constant_evaluated()`                    | Returns bool                       |
| Local mutation        | `constexpr int f() { int x = 0; ++x; return x; }` | Legal - locals can be mutated      |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. When is a constexpr function guaranteed to evaluate at compile-time?

<details>
<summary>Show answer</summary>

**Direct answer:** A constexpr function is guaranteed to evaluate at compile-time only when its result is used in a context that requires a constant expression - such as initializing a `constexpr` variable, providing a template argument, or specifying an array size. In all other contexts, the compiler may choose runtime or compile-time evaluation at its discretion.

**Detailed explanation:**
The `constexpr` keyword on a function means "eligible for compile-time evaluation," not "always evaluated at compile-time." The same function can run at runtime with non-constant arguments.

```cpp
constexpr int square(int n) { return n * n; }

constexpr int a{ square(5) };  // GUARANTEED compile-time (constexpr variable)
int b{ square(5) };            // MAY be compile-time (compiler's choice)

int x{};
std::cin >> x;
int c{ square(x) };            // MUST be runtime (x is not constexpr)
```

</details>

2. What is the difference between `constexpr` and `consteval`?

<details>
<summary>Show answer</summary>

**Direct answer:** A `constexpr` function _can_ be evaluated at compile-time or runtime. A `consteval` function (C++20) _must_ be evaluated at compile-time - passing a non-constant argument is a compile error. Use `consteval` when you need the guarantee that runtime evaluation can never happen.

**Detailed explanation:**

```cpp
constexpr int square(int n) { return n * n; }  // can be compile-time OR runtime
consteval int cube(int n) { return n * n * n; } // MUST be compile-time

int a{ square(5) };  // OK: may be runtime
int b{ cube(5) };    // OK: always compile-time

int x{};
std::cin >> x;
int c{ square(x) };  // OK: runtime fallback
// int d{ cube(x) }; // ERROR: x is not a constant expression
```

</details>

3. Why can't function parameters be `constexpr`?

<details>
<summary>Show answer</summary>

**Direct answer:** Function parameters are never constexpr because they receive their values from arguments at the call site, and the compiler must generate a single function body that works with both constant and non-constant arguments. Even inside a `consteval` function, parameters are runtime values - you cannot use them to initialize `constexpr` local variables or as template arguments.

**Detailed explanation:**

```cpp
constexpr int process(int n)   // n is NOT constexpr
{
    // constexpr int x{ n };   // ERROR: n is not a constant expression
    return n * 2;
}

constexpr int result{ process(5) };  // 5 is constant, but inside process(), n is still not constexpr
```

The compiler resolves the entire call chain at compile-time when the outermost call is in a required constant context, but it does so through constant evaluation of the expression tree, not by marking parameters as constexpr.

</details>

4. How can you verify that a constexpr function works at compile-time?

<details>
<summary>Show answer</summary>

**Direct answer:** Assign the result to a `constexpr` variable: `constexpr int x{ f(args) };`. If the function cannot be evaluated at compile-time with those arguments, the compiler will produce an error. This is the standard technique for testing constexpr correctness.

**Detailed explanation:**
A constexpr function might compile and run perfectly at runtime yet fail at compile-time (e.g., a branch that divides by zero with certain inputs). Always test in a required-constant context:

```cpp
constexpr int divide(int a, int b) { return a / b; }

constexpr int ok{ divide(10, 2) };   // OK: compiles, compile-time evaluation
// constexpr int bad{ divide(10, 0) }; // ERROR: division by zero at compile-time
int runtime{ divide(10, 0) };         // UB at runtime, but compiles!
```

You can also use `static_assert` with the result for compile-time verification:

```cpp
static_assert(divide(10, 2) == 5);  // compile-time check
```

</details>

5. Why must constexpr function definitions be in headers?

<details>
<summary>Show answer</summary>

**Direct answer:** To evaluate a constexpr function at compile-time, the compiler must see the full function definition (not just a declaration) at the point of call. Since each translation unit is compiled independently, the definition must be in a header that gets `#include`d wherever the function is used. constexpr functions are implicitly inline, so multiple definitions across translation units don't violate the ODR.

**Detailed explanation:**

```cpp
// math.h
#ifndef MATH_H
#define MATH_H

constexpr int square(int n) { return n * n; }  // definition in header - OK
// constexpr implies inline, so no ODR violation

#endif
```

If you put the definition in a `.cpp` file and only a forward declaration in the header, calling files can only use it at runtime (the compiler can't see the body to evaluate it at compile-time).

</details>

6. What does `std::is_constant_evaluated()` return and when?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::is_constant_evaluated()` (C++20, from `<type_traits>`) returns `true` if the function is currently being evaluated in a constant expression context, and `false` if at runtime. This lets a constexpr function choose different code paths for compile-time vs. runtime execution.

**Detailed explanation:**

```cpp
#include <type_traits>

constexpr double power(double base, int exp)
{
    if (std::is_constant_evaluated())
    {
        // compile-time safe path (no std::pow available)
        double result{ 1.0 };
        for (int i{ 0 }; i < exp; ++i)
            result *= base;
        return result;
    }
    else
    {
        // runtime path - can use optimized library function
        return std::pow(base, exp);
    }
}
```

Caution: do _not_ use it in an `if constexpr` - that always evaluates the condition at compile-time, so `std::is_constant_evaluated()` would always return `true`.

</details>

7. Can a constexpr function contain an `if` statement? Since which C++ standard?

<details>
<summary>Show answer</summary>

**Direct answer:** Yes. Since C++14, constexpr functions can contain `if` statements, loops, local variables, and multiple `return` statements. C++11 constexpr functions were restricted to a single `return` statement with no local variables or branches. C++14 relaxed these restrictions significantly.

**Detailed explanation:**

```cpp
// C++11: only a single return statement allowed
constexpr int abs11(int n) { return (n < 0) ? -n : n; }

// C++14+: if statements, loops, local variables all OK
constexpr int factorial(int n)
{
    int result{ 1 };
    for (int i{ 2 }; i <= n; ++i)
        result *= i;
    return result;
}

static_assert(factorial(5) == 120);
```

The restriction is on _side effects_ (I/O, modifying global state, non-constexpr heap allocation), not on control flow or local mutation.

</details>

8. What is `if consteval` and how does it improve on `std::is_constant_evaluated()`?

<details>
<summary>Show answer</summary>

**Direct answer:** `if consteval` (C++23) is a language-level replacement for `std::is_constant_evaluated()`. It detects whether the function is being evaluated at compile-time, but because it's a language construct (not a library function), it avoids the pitfalls of `std::is_constant_evaluated()` - notably, it works correctly even outside a function body and doesn't accidentally always-return-true when used inside `if constexpr`.

**Detailed explanation:**

```cpp
constexpr double power(double base, int exp)
{
    if consteval  // C++23 - no parentheses, no condition
    {
        // compile-time path
        double result{ 1.0 };
        for (int i{ 0 }; i < exp; ++i)
            result *= base;
        return result;
    }
    else
    {
        // runtime path - consteval functions callable here too
        return std::pow(base, exp);
    }
}
```

Inside the `if consteval` branch, you can call `consteval` functions (which would normally fail at runtime). In the `else` branch, you can use runtime-only features.

</details>

9. What kinds of operations are **not allowed** inside a constexpr function?

<details>
<summary>Show answer</summary>

**Direct answer:** A constexpr function cannot perform I/O (e.g., `std::cout`), call non-constexpr functions, use `goto`, modify global/static variables, or (before C++20) allocate heap memory. The restriction is on side effects and non-deterministic operations - local variable mutation, loops, and branches are all fine (since C++14).

**Detailed explanation:**

```cpp
constexpr int good(int n)
{
    int sum{ 0 };           // OK: local variable
    for (int i{ 0 }; i < n; ++i)
        sum += i;           // OK: local mutation
    return sum;
}

constexpr int bad(int n)
{
    std::cout << n;         // ERROR: I/O not allowed in constexpr
    return n;
}
```

Pure functions (same inputs → same outputs, no side effects) are the ideal candidates for `constexpr`. Don't blindly mark every function constexpr - only those that genuinely benefit from compile-time evaluation.

</details>

10. When should you prefer `constexpr` over `consteval`, and vice versa?

<details>
<summary>Show answer</summary>

**Direct answer:** Use `constexpr` when you want a function usable at both compile-time and runtime (the common case - e.g., utility math functions). Use `consteval` when the function _must never_ run at runtime - e.g., functions that generate lookup tables, compute hash values for string literals, or encode compile-time configuration. If accidental runtime evaluation would be a bug, use `consteval`.

**Detailed explanation:**

```cpp
// constexpr: usable everywhere
constexpr int max(int a, int b) { return (a > b) ? a : b; }

int x{};
std::cin >> x;
int m{ max(x, 10) };       // OK at runtime
constexpr int n{ max(3, 7) }; // OK at compile-time

// consteval: compile-time only guarantee
consteval unsigned long long operator""_hash(const char* str, std::size_t len)
{
    unsigned long long hash{ 0 };
    for (std::size_t i{ 0 }; i < len; ++i)
        hash = hash * 31 + str[i];
    return hash;
}

constexpr auto h{ "hello"_hash };  // OK: compile-time
// Runtime string hashing won't compile - that's the point
```

</details>
