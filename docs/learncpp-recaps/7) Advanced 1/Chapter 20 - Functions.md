# Chapter 20 Recap - Functions

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Prefer `std::function` or `auto` over raw function pointer syntax for readability.
- Function pointers enable callbacks - pass behavior as a parameter.
- The stack is fast but small (~1-8 MB); don't allocate large arrays on it.
- Every recursive function **must** have a base case to avoid stack overflow.
- Favor iteration over recursion unless recursion is significantly cleaner.
- Command line arguments are always C-style strings - convert explicitly for numeric use.
- **Avoid ellipsis** - they bypass type safety entirely.
- Lambdas are ideal for short, inline functions used with algorithms.

### 3 Tiny Examples

1.

```cpp
int add(int a, int b) { return a + b; }
int (*fcnPtr)(int, int){ &add };
std::cout << fcnPtr(3, 4); // 7
```

2.

```cpp
int stackVar{5};            // allocated on the stack (automatic)
int* heapVar{new int{10}};  // allocated on the heap (dynamic)
delete heapVar;             // must free heap memory manually
```

3.

```cpp
int factorial(int n) {
    if (n <= 1) return 1;       // base case
    return n * factorial(n - 1); // recursive case
}
```

### 3 Common Mistakes

- Skipping compiler warnings.
- Using chapter features without understanding prerequisites.
- Not testing edge cases.

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Function pointer** - a variable storing the address of a function; enables indirect calls and callback patterns.
- **`std::function<R(Args...)>`** - a polymorphic function wrapper (from `<functional>`) that can hold any callable matching the signature.
- **Call stack** - a LIFO memory region storing stack frames (return address, parameters, locals) for each active function call.
- **Heap** - a large memory region for dynamic allocation (`new`/`delete`); slower than the stack but much larger.
- **Stack overflow** - occurs when the call stack is exhausted (too many nested calls or huge stack allocations).
- **Recursion** - a function calling itself; must have a **base case** (termination condition) to avoid infinite recursion.
- **Memoization** - caching previously computed results to avoid redundant recursive computation.
- **Command line arguments** - `int main(int argc, char* argv[])` - string inputs passed at launch.
- **Ellipsis (`...`)** - C-style variable-length argument lists; type-unsafe and dangerous.
- **Lambda expression** - `[captures](params) -> ret { body }` - an anonymous function object defined inline.
- **Capture clause** - gives a lambda access to outer-scope variables by value (default, const copies) or by reference (`&`).
- **`mutable` lambda** - allows modifying captured-by-value variables (the lambda's copies, not the originals).
- **Generic lambda** - uses `auto` parameters; the compiler generates separate instantiations per type.

### Section-by-Section Detail

### 20.1 - Function Pointers

- A **function pointer** `int (*fcnPtr)(int)` holds a function's address - call indirectly via `fcnPtr(arg)` or `(*fcnPtr)(arg)`
- Function names implicitly convert to function pointers → pass them directly where a pointer is expected
- Use type aliases (`using Callback = int(*)(int);`) or `std::function` for cleaner syntax
- Enable **callback patterns** - pass behavior as a parameter to customize algorithms at call time
- Default arguments work with function pointer parameters - callers can omit the callback for default behavior

```cpp
int add(int a, int b) { return a + b; }
int (*fcnPtr)(int, int){ &add };
std::cout << fcnPtr(3, 4); // 7
```

→ _See [01_FunctionPointers](../solutions/Chapter_20_Functions/01_FunctionPointers) and [03_CallbackPattern](../solutions/Chapter_20_Functions/03_CallbackPattern) for indirect calls and callbacks._

**Callable Types Comparison:**

| Callable Type        | Syntax                               | Captures State?      | Overhead            | Use Case                 |
| -------------------- | ------------------------------------ | -------------------- | ------------------- | ------------------------ |
| **Function pointer** | `int (*fp)(int)`                     | No                   | Zero (direct call)  | C APIs, simple callbacks |
| **`std::function`**  | `std::function<int(int)>`            | Yes (type-erased)    | Heap alloc possible | Storing any callable     |
| **Lambda**           | `[](int x){ return x; }`             | Yes (capture clause) | Zero (inlined)      | Inline with algorithms   |
| **Functor (class)**  | `struct F { int operator()(int); };` | Yes (member vars)    | Zero                | Stateful, reusable       |

### 20.2 - The Stack and the Heap

- Program memory is divided into segments - code, BSS, data, **heap**, and **call stack**
- The **stack** is fast (O(1) allocation) but limited (~1-8 MB) - each function call pushes a **stack frame** (return address, parameters, locals)
- The **heap** is large but slower - allocator must search for a free block; fragmentation possible over time
- Exceeding the stack causes a **stack overflow** - typically from deep/infinite recursion or large local arrays
- Prefer stack variables for small, short-lived data - reserve the heap for runtime-sized data or objects that must outlive the current scope

```cpp
int stackVar{5};            // allocated on the stack (automatic)
int* heapVar{new int{10}};  // allocated on the heap (dynamic)
delete heapVar;             // must free heap memory manually
```

→ _See [04_StackAndHeap](../solutions/Chapter_20_Functions/04_StackAndHeap) for allocation demos and overflow._

**Stack vs Heap:**

| Property             | Stack                         | Heap                                   |
| -------------------- | ----------------------------- | -------------------------------------- |
| **Allocation speed** | O(1) - pointer bump           | Slower - free-block search             |
| **Deallocation**     | Automatic (scope exit)        | Manual (`delete`) or smart pointer     |
| **Size limit**       | ~1-8 MB (platform-dependent)  | Limited by system RAM                  |
| **Fragmentation**    | None                          | Possible                               |
| **Use for**          | Small locals, function frames | Runtime-sized data, long-lived objects |
| **Failure mode**     | Stack overflow (crash)        | `std::bad_alloc` or `nullptr`          |

### 20.3 - Recursion

- A **recursive function** calls itself with progressively smaller input until it reaches a **base case** and returns
- Each call pushes a new stack frame - deep recursion without a reachable base case → stack overflow
- Classic examples - factorial, Fibonacci, Tower of Hanoi
- Naive Fibonacci is exponentially slow - **memoization** (caching results) reduces it to linear time
- Favor iteration over recursion unless the recursive formulation is significantly clearer (e.g., tree traversal, divide-and-conquer)

```cpp
int factorial(int n) {
    if (n <= 1) return 1;       // base case
    return n * factorial(n - 1); // recursive case
}
```

→ _See [05_Recursion](../solutions/Chapter_20_Functions/05_Recursion) for recursive algorithms and memoization._

### 20.4 - Command Line Arguments

- `int main(int argc, char* argv[])` - `argc` is the argument count (>= 1), `argv` is an array of C-style strings
- All arguments arrive as strings - convert with `std::stoi`, `std::stod`, or `std::stringstream` for numeric use
- Always check `argc` before accessing `argv[n]` to avoid out-of-bounds reads
- Useful for passing file paths, configuration flags, or run modes without recompiling
- On most systems, `argv[argc]` is guaranteed to be a null pointer - can serve as an alternative sentinel

```cpp
int main(int argc, char* argv[]) {
    if (argc > 1)
        std::cout << "First arg: " << argv[1] << '\n';
}
```

→ _See [06_CommandLineArguments](../solutions/Chapter_20_Functions/06_CommandLineArguments) for argument parsing._

### 20.5 - Ellipsis (and Why to Avoid Them)

- The `...` syntax with `va_list`/`va_start`/`va_arg`/`va_end` (from `<cstdarg>`) enables variable-argument functions like `printf`
- Type checking is **disabled** for ellipsis arguments - wrong types → garbage or UB with no compiler warning
- The caller must communicate argument count and types (e.g., format string) - no way to detect mismatches
- Modern alternatives - variadic templates, `std::initializer_list`, or containers - all preserve type safety
- Avoid ellipsis in new code - they exist primarily for C compatibility

```cpp
#include <cstdarg>
double avg(int count, ...) {
    va_list list;
    va_start(list, count);
    double sum{};
    for (int i{0}; i < count; ++i)
        sum += va_arg(list, int);
    va_end(list);
    return sum / count;
}
```

→ _See [07_Ellipsis](../solutions/Chapter_20_Functions/07_Ellipsis) for why ellipsis is dangerous._

### 20.6 - Introduction to Lambdas (Anonymous Functions)

- **Lambda** syntax - `[captures](params) -> returnType { body; }` - return type is usually deduced
- Store with `auto` (preferred), `std::function`, or a function pointer (captureless only)
- Ideal for short, one-off functions passed to algorithms like `std::sort` and `std::find_if`
- **Generic lambdas** use `auto` in the parameter list - implicitly `constexpr` (C++17+) when possible
- The standard library provides ready-made functors like `std::greater{}` in `<functional>`

```cpp
auto double_it = [](int x) { return x * 2; };
std::cout << double_it(5); // 10
std::sort(v.begin(), v.end(), std::greater{});
```

→ _See [08_LambdaBasics](../solutions/Chapter_20_Functions/08_LambdaBasics) and [11_GenericLambdas](../solutions/Chapter_20_Functions/11_GenericLambdas) for lambda syntax and generic lambdas._

### 20.7 - Lambda Captures

- The **capture clause** gives a lambda access to outer-scope variables
- **By value** (default) - lambda gets a const copy; add `mutable` to modify the copy
- **By reference** (`&var`) - lambda accesses the original; changes persist, but dangling possible if variable is destroyed
- Default captures - `[=]` (all by value), `[&]` (all by reference)
- Use `std::ref` to avoid unintended copies of mutable lambdas passed to `std::function`

```cpp
int x{10};
auto byVal = [x]()  { return x; };       // const copy of x
auto byRef = [&x]() { return ++x; };     // accesses original x
byRef();  // x is now 11
```

→ _See [09_LambdaCaptureByValue](../solutions/Chapter_20_Functions/09_LambdaCaptureByValue) and [10_LambdaCaptureByReference](../solutions/Chapter_20_Functions/10_LambdaCaptureByReference) for capture mechanics._

**Lambda Capture Modes:**

| Capture                  | Syntax          | Copies?              | Modifiable?   | Danger                         |
| ------------------------ | --------------- | -------------------- | ------------- | ------------------------------ |
| **By value**             | `[x]`           | Yes (const copy)     | No            | Stale data if original changes |
| **By value + mutable**   | `[x]() mutable` | Yes (non-const copy) | Copy only     | Original unchanged             |
| **By reference**         | `[&x]`          | No (reference)       | Original      | Dangling reference if `x` dies |
| **Default by value**     | `[=]`           | All used vars        | No            | Hidden copies                  |
| **Default by reference** | `[&]`           | None                 | All originals | Hard to audit; dangling risk   |

### Edge Cases and Caveats

❌ Writing `foo` instead of `foo()`:

```cpp
auto result = foo; // ❌ this is a function pointer, not the return value
```

✅ Call the function:

```cpp
auto result = foo(); // ✅ calls foo and stores the return value
```

---

❌ Mismatching function pointer types:

```cpp
int (*fp)(double) = &bar; // ❌ if bar takes int, types don't match
```

✅ Parameter and return types must exactly match the pointed-to function.

---

❌ Dereferencing a null function pointer:

```cpp
int (*fp)(int) = nullptr;
fp(5); // ❌ UB - calling through null
```

✅ Check before calling:

```cpp
if (fp) fp(5); // ✅
```

---

❌ Huge arrays on the stack:

```cpp
int arr[10'000'000]; // ❌ stack overflow
```

✅ Use dynamic allocation (`std::vector`) for large data.

---

❌ Missing base case in recursion:

```cpp
int factorial(int n) { return n * factorial(n - 1); } // ❌ infinite recursion
```

✅ Add a base case:

```cpp
int factorial(int n) {
    if (n <= 1) return 1; // ✅ base case
    return n * factorial(n - 1);
}
```

---

❌ `--variable` in recursive calls:

```cpp
foo(x, --x); // ❌ UB - x modified and read in the same expression
```

✅ Use `x - 1` as the argument instead.

---

❌ Accessing `argv[n]` without checking `argc`:

```cpp
std::cout << argv[2]; // ❌ OOB if fewer than 3 arguments
```

✅ Check `argc` first:

```cpp
if (argc > 2) std::cout << argv[2]; // ✅
```

---

❌ Expecting by-value capture to modify the original:

```cpp
int x = 5;
auto fn = [x]() mutable { ++x; }; // ❌ modifies lambda's copy, not original x
```

✅ Capture by reference to modify the original:

```cpp
auto fn = [&x]() { ++x; }; // ✅
```

---

❌ Dangling reference captures:

```cpp
auto makeLambda() {
    int x = 5;
    return [&x]() { return x; }; // ❌ x dies when function returns
}
```

✅ Capture by value if the lambda outlives the local.

---

❌ Unintended copies of mutable lambdas:

```cpp
std::function<void()> fn = myLambda; // ❌ copies the lambda; independent state
```

✅ Use `std::ref(myLambda)` to share state.

---

### Hands-On Code Projects

Practice every concept with the hands-on projects in:

```
solutions/Chapter_20_Functions/
```

| Project                                                                                         | Concept                                                              |
| ----------------------------------------------------------------------------------------------- | -------------------------------------------------------------------- |
| [01_FunctionPointers](../solutions/Chapter_20_Functions/01_FunctionPointers)                   | Function pointer syntax, assignment, and indirect calls              |
| [02_StdFunctionAndTypeAliases](../solutions/Chapter_20_Functions/02_StdFunctionAndTypeAliases) | Cleaner function pointer usage with `std::function` and type aliases |
| [03_CallbackPattern](../solutions/Chapter_20_Functions/03_CallbackPattern)                     | Callback patterns with function pointers and `std::function`         |
| [04_StackAndHeap](../solutions/Chapter_20_Functions/04_StackAndHeap)                           | Stack vs. heap allocation and stack overflow                         |
| [05_Recursion](../solutions/Chapter_20_Functions/05_Recursion)                                 | Recursive functions, base cases, and memoization                     |
| [06_CommandLineArguments](../solutions/Chapter_20_Functions/06_CommandLineArguments)           | Accessing and converting `argc` / `argv`                             |
| [07_Ellipsis](../solutions/Chapter_20_Functions/07_Ellipsis)                                   | C-style variadic functions and why to avoid them                     |
| [08_LambdaBasics](../solutions/Chapter_20_Functions/08_LambdaBasics)                           | Lambda syntax, `auto` storage, use with algorithms                   |
| [09_LambdaCaptureByValue](../solutions/Chapter_20_Functions/09_LambdaCaptureByValue)           | Capture by value semantics and the `mutable` keyword                 |
| [10_LambdaCaptureByReference](../solutions/Chapter_20_Functions/10_LambdaCaptureByReference)   | Capture by reference and dangling-reference pitfalls                 |
| [11_GenericLambdas](../solutions/Chapter_20_Functions/11_GenericLambdas)                       | `auto` parameters, constexpr lambdas, standard functors              |
| [12_CommonPitfalls](../solutions/Chapter_20_Functions/12_CommonPitfalls)                       | Frequent mistakes with function pointers, recursion, and lambdas     |

### Quick Reference

| Feature          | Syntax                              | Notes                         |
| ---------------- | ----------------------------------- | ----------------------------- |
| Function pointer | `int (*fp)(int) = &func;`           | Indirect call: `fp(5)`        |
| Type alias       | `using FP = int(*)(int);`           | Cleaner declarations          |
| `std::function`  | `std::function<int(int)> f = func;` | Polymorphic wrapper           |
| Lambda           | `[](int x) { return x * 2; }`       | Anonymous function object     |
| Capture by value | `[x]` or `[=]`                      | Const copy (unless `mutable`) |
| Capture by ref   | `[&x]` or `[&]`                     | Access original variable      |
| Mutable lambda   | `[x]() mutable { ++x; }`            | Modify the lambda's copy      |
| Generic lambda   | `[](auto x) { return x; }`          | One instantiation per type    |
| argc/argv        | `int main(int argc, char* argv[])`  | Always strings                |
| Recursion base   | `if (n <= 0) return 1;`             | Prevents infinite recursion   |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is the difference between `foo` and `foo()` in an expression?

<details>
<summary>Show answer</summary>

**Direct answer:** `foo` names the function itself (and often decays to a function pointer), while `foo()` actually calls the function and produces its return value.

**Detailed explanation:**
``cpp
int add(int a, int b) { return a + b; }

auto fnPtr = add; // foo function pointer (no call)
auto result = add(3, 4); // foo() calls the function, result = 7

// fnPtr can be used to call later:
std::cout << fnPtr(3, 4); // 7
``

</details>

2. How do you declare a function pointer for a function `int add(int, int)`?

<details>
<summary>Show answer</summary>

**Direct answer:** `int (*fcnPtr)(int, int){ &add };` the parentheses around `*fcnPtr` are required. You can call via `fcnPtr(3, 4)` or `(*fcnPtr)(3, 4)`. Use type aliases for readability: `using AddFn = int(*)(int, int);`.

**Detailed explanation:**
``cpp
int add(int a, int b) { return a + b; }

// Raw function pointer:
int (\*fcnPtr)(int, int){ &add };
std::cout << fcnPtr(3, 4); // 7

// Type alias (cleaner):
using BinaryOp = int(\*)(int, int);
BinaryOp op{ &add };

// std::function (most flexible, supports lambdas with captures):
std::function<int(int, int)> fn{ add };
``

</details>

3. What causes a stack overflow in recursive functions?

<details>
<summary>Show answer</summary>

**Direct answer:** Each recursive call pushes a new stack frame. If there's no reachable base case, or the recursion depth is too large, the stack runs out of space (typically 1-8 MB), causing a stack overflow (crash). Always ensure every recursive path eventually reaches a base case.

**Detailed explanation:**
``cpp
// Missing base case infinite recursion -> stack overflow:
int bad(int n) { return bad(n - 1); } // never stops

// Correct base case:
int factorial(int n)
{
if (n <= 1) return 1; // base case
return n \* factorial(n - 1); // recursive case
}
``

For deep recursion (thousands of levels), consider converting to iterative form. Memoization can also help avoid redundant recursive calls (e.g., Fibonacci).

</details>

4. What are `argc` and `argv` and how are they used?

<details>
<summary>Show answer</summary>

**Direct answer:** `argc` is the count of command-line arguments (always >= 1). `argv` is an array of C-style strings `argv[0]` is the program name, `argv[1]` through `argv[argc-1]` are the user-provided arguments. All arguments arrive as strings; convert with `std::stoi` or `std::stod` for numeric use.

**Detailed explanation:**
``cpp
// Run: ./program hello 42
int main(int argc, char\* argv[])
{
// argc = 3
// argv[0] = "./program"
// argv[1] = "hello"
// argv[2] = "42"

    if (argc > 1)
        std::cout << argv[1]; // "hello"
    if (argc > 2)
    {
        int num{ std::stoi(argv[2]) }; // 42
    }

}
``

Always check `argc` before accessing `argv[n]` to avoid out-of-bounds reads.

</details>

5. What is the difference between capture by value `[x]` and by reference `[&x]`?

<details>
<summary>Show answer</summary>

**Direct answer:** `[x]` captures a const copy of `x` at the point of lambda creation the lambda has its own independent copy. `[&x]` captures a reference to the original the lambda reads/writes the same variable. Danger: if `x` is destroyed before the lambda runs, `[&x]` dangles.

**Detailed explanation:**
``cpp
int x{ 10 };

auto byVal = [x]() { return x; }; // copy of x (10)
auto byRef = [&x]() { return x; }; // reference to x

x = 20;
std::cout << byVal(); // 10 (copy hasn't changed)
std::cout << byRef(); // 20 (sees current value of x)

// Default captures:
auto allVal = [=]() { return x; }; // all by value
auto allRef = [&]() { return x; }; // all by reference
``

</details>

6. Why might `mutable` be needed on a lambda with by-value captures?

<details>
<summary>Show answer</summary>

**Direct answer:** By-value captures are `const` inside the lambda by default you can't modify the copy. The `mutable` keyword removes this `const`, letting you modify the lambda's own copy (not the original). This is useful for lambdas that need internal state across calls.

**Detailed explanation:**
``cpp
int count{ 0 };
auto counter = [count]() mutable {
++count; // modifies the lambda's internal copy
return count;
};

std::cout << counter(); // 1
std::cout << counter(); // 2
std::cout << count; // 0 (original unchanged)
``

Without `mutable`, `++count` would be a compile error because `count` is const inside the lambda.

</details>

7. What is the danger of returning a lambda that captures locals by reference?

<details>
<summary>Show answer</summary>

**Direct answer:** The local variables die when the function returns, but the lambda still holds references to them they become dangling references. Using the lambda after the function returns is undefined behavior. Always capture by value (`[=]`) when returning lambdas.

**Detailed explanation:**
``cpp
auto makeLambda()
{
int local{ 42 };
return [&local]() { return local; }; // DANGER: local dies at return
}

auto fn = makeLambda();
// fn(); // UB: local no longer exists

// Safe: capture by value
auto makeSafe()
{
int local{ 42 };
return [local]() { return local; }; // OK: copy survives
}
``

</details>

8. How does `std::function` interact with mutable lambda state?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::function` stores a copy of the lambda internally. If you pass a mutable lambda to `std::function`, changes to the lambda's captured state happen inside `std::function`'s copy. Assigning the lambda to multiple `std::function` objects creates independent copies, each with their own state. Use `std::ref` to wrap the lambda if you want `std::function` to reference the original.

**Detailed explanation:**
``cpp
auto counter = [count = 0]() mutable { return ++count; };

std::function<int()> fn1{ counter }; // fn1 gets a COPY of counter
std::function<int()> fn2{ counter }; // fn2 gets another COPY

fn1(); fn1(); // fn1's state: 2
fn2(); // fn2's state: 1 (independent)

// To share state, use std::ref:
std::function<int()> fn3{ std::ref(counter) }; // references original
``

</details>

9. What is the difference between `std::function` and a raw function pointer?

<details>
<summary>Show answer</summary>

**Direct answer:** A raw function pointer (`int(*)(int)`) can only point to free functions or captureless lambdas. `std::function<int(int)>` can store any callable: free functions, lambdas with captures, functors, bound member functions. `std::function` has more overhead (heap allocation, type erasure) but is more versatile.

**Detailed explanation:**
``cpp
int square(int x) { return x \* x; }

// Function pointer: only free functions / captureless lambdas
int (\*fp)(int){ square };

// std::function: any callable
int factor{ 3 };
std::function<int(int)> fn{ [factor](int x) { return x * factor; } };
// int (*fp2)(int){ [factor](int x) { return x \* factor; } }; // ERROR: has capture
``

Prefer `auto` for lambda variables (zero overhead). Use `std::function` when you need to store callables in containers or pass them through interfaces that can't be templated.

</details>

10. Why should ellipsis (`...`) variadic functions be avoided in modern C++?

<details>
<summary>Show answer</summary>

**Direct answer:** Ellipsis functions (like `printf`) disable type checking for variadic arguments passing the wrong type yields garbage or UB with no compiler warning. There's no way to determine how many arguments were passed. Modern alternatives (variadic templates, `std::initializer_list`, parameter packs) preserve type safety.

**Detailed explanation:**
``cpp
// C-style: no type safety
int sum(int count, ...) // caller must pass correct count and types
{
va_list args;
va_start(args, count);
int total{ 0 };
for (int i{ 0 }; i < count; ++i)
total += va_arg(args, int); // wrong type = UB
va_end(args);
return total;
}

// Modern C++: type-safe variadic template
template <typename... Args>
auto sum(Args... args) { return (args + ...); } // fold expression
``

</details>
