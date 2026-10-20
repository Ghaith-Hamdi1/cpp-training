# Chapter 27 Recap - Exceptions

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Use exceptions for truly exceptional/error conditions, not routine input validation
- Catch class-type exceptions by **const reference** to avoid copies and slicing
- Place catch blocks for **derived types before base types** - the first matching handler wins
- Use `throw;` (no operand) to rethrow - never `throw exceptionVariable;`
- Never throw exceptions from destructors
- Use RAII (smart pointers, stack-allocated objects) so resources are automatically cleaned up even when exceptions occur
- Always mark move constructors, move assignment, and swap as `noexcept`
- Consider wrapping `main()` in a try/catch-all for orderly shutdown on unexpected exceptions

### 3 Tiny Examples

1.

```cpp
int divide(int a, int b) {
    if (b == 0) throw std::invalid_argument("Division by zero");
    return a / b;
}
```

2.

```cpp
try {
    throw 42;
}
catch (int x)    { std::cout << "Caught int: " << x; }
catch (double d) { } // int won't match double
```

3.

```cpp
void foo() { throw std::runtime_error("error"); }
void bar() { foo(); } // exception propagates through
int main() {
    try { bar(); }
    catch (const std::exception& e) { std::cerr << e.what(); }
}
```

### 3 Common Mistakes

- Skipping compiler warnings.
- Using chapter features without understanding prerequisites.
- Not testing edge cases.

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **throw** - raises an exception of any data type
- **try block** - observes statements for thrown exceptions and routes them to catch blocks
- **catch block** - handles exceptions of a specific type (or all types via `catch(...)`)
- **Stack unwinding** - the process of popping functions off the call stack until a matching catch handler is found, destroying local variables along the way
- **Catch-all handler** - `catch(...)` catches exceptions of any type; must be placed last
- **Exception classes** - custom classes designed to be thrown as exceptions, providing richer error context than primitive types
- **std::exception** - base class for all standard library exceptions; provides the `what()` virtual function
- **Rethrowing** - using `throw;` (with no operand) inside a catch block to re-raise the exact same exception without slicing
- **Function try blocks** - wrap an entire function (including member initializer lists) in a try/catch
- **noexcept** - specifier that marks a function as non-throwing; violation calls `std::terminate`
- **Exception safety guarantees** - four levels: no guarantee, basic, strong, no-throw/no-fail
- **std::move_if_noexcept** - uses move semantics if the move constructor is `noexcept`, otherwise falls back to copy semantics

### Section-by-Section Detail

### 27.1 - The need for exceptions

- **Return codes** are cryptic, can't coexist easily with a function's actual return value, and don't work with constructors or operators.
- **Exceptions** decouple error handling from normal execution - error-free code stays clean and readable.
- `throw` transfers control directly to a matching `catch` block, even across multiple function boundaries, without manual error propagation.
- Exceptions are especially valuable in **deep call chains** where errors originate far from where they can be meaningfully handled.

```cpp
int divide(int a, int b) {
    if (b == 0) throw std::invalid_argument("Division by zero");
    return a / b;
}
```

→ _See [01_NeedForExceptions](../solutions/Chapter_27_Exceptions/01_NeedForExceptions/) for the motivation for exceptions over return codes._

### 27.2 - Basic exception handling

- Three keywords: `throw` raises an exception of any copyable type, `try` watches for exceptions, and `catch` handles a matching type.
- **No implicit type conversion** when matching - an `int` exception won't match a `double` handler; the type must match exactly (except base-to-derived).
- Once caught, execution resumes **after the last catch block** - not at the throw point.
- Multiple `catch` blocks can follow a single `try` block to handle different exception types.

```cpp
try {
    throw 42;
}
catch (int x)    { std::cout << "Caught int: " << x; }
catch (double d) { } // int won't match double
```

→ _See [02_BasicExceptionHandling](../solutions/Chapter_27_Exceptions/02_BasicExceptionHandling/) for `throw`, `try`, and `catch` fundamentals._

### 27.3 - Exceptions, functions, and stack unwinding

- Exceptions propagate up the call stack until a matching `catch` handler is found - this process is called **stack unwinding**.
- During unwinding, local variables in each unwound function are properly **destroyed via their destructors** - making RAII objects critical.
- A function that throws doesn't have to handle the exception itself → enables **modular error handling** across layers.
- Raw resources (e.g. `new`'d memory without a smart pointer) **will leak** if not wrapped in RAII during unwinding.

```cpp
void foo() { throw std::runtime_error("error"); }
void bar() { foo(); } // exception propagates through
int main() {
    try { bar(); }
    catch (const std::exception& e) { std::cerr << e.what(); }
}
```

→ _See [03_ExceptionsAndFunctions](../solutions/Chapter_27_Exceptions/03_ExceptionsAndFunctions/) for cross-function propagation · [04_StackUnwinding](../solutions/Chapter_27_Exceptions/04_StackUnwinding/) for destructor cleanup during unwinding._

### 27.4 - Uncaught exceptions and catch-all handlers

- If no matching `catch` handler is found, `std::terminate()` is called - the stack may or may not unwind (implementation-defined).
- The **catch-all handler** `catch(...)` catches any exception type and must be placed **last** among catch blocks.
- Wrapping `main()` in a try/catch-all is good practice for **orderly cleanup** on unexpected exceptions.
- In **debug builds**, consider omitting the catch-all so the debugger can break at the throw point.

```cpp
try { riskyFunc(); }
catch (const std::exception& e) { std::cerr << e.what(); }
catch (...) { std::cerr << "Unknown exception"; }
```

→ _See [05_UncaughtAndCatchAll](../solutions/Chapter_27_Exceptions/05_UncaughtAndCatchAll/) for uncaught exceptions and `catch(...)`._

### 27.5 - Exceptions, classes, and inheritance

- Exceptions are especially useful in **constructors and overloaded operators** where return codes aren't viable.
- If a constructor throws, the object's destructor is **not** called - but already-constructed members and base classes are destructed (→ use **RAII**).
- **Exception classes** inheriting from `std::exception` provide richer context via the `what()` virtual function.
- Catch handlers match derived-to-base → **derived catch blocks must be listed before base catch blocks**.

```cpp
class MyError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};
try { throw MyError("custom error"); }
catch (const std::exception& e) { std::cout << e.what(); }
```

→ _See [06_ExceptionClasses](../solutions/Chapter_27_Exceptions/06_ExceptionClasses/) for custom exception classes · [07_InheritanceAndCatchOrder](../solutions/Chapter_27_Exceptions/07_InheritanceAndCatchOrder/) for derived-before-base catch ordering._

### 27.6 - Rethrowing exceptions

- Use `throw;` (no operand) inside a catch block to **rethrow** the original exception - the dynamic type is preserved, no slicing occurs.
- Using `throw exception;` (with the caught variable) creates a **copy** and can **slice** derived types → always avoid this form.
- Rethrowing is useful for **logging** at one level while letting a higher level decide how to recover.
- The original exception object is reused - no new exception is constructed when using bare `throw;`.

```cpp
try { foo(); }
catch (const std::exception& e) {
    std::cerr << "Logging: " << e.what();
    throw; // rethrow original (no slicing)
}
```

→ _See [08_RethrowingExceptions](../solutions/Chapter_27_Exceptions/08_RethrowingExceptions/) for `throw;` vs `throw exception;` and the slicing problem._

> **Rethrow Cheat Sheet**
>
> | Syntax     | What happens                                | Original type preserved?                       | Use when                                    |
> | ---------- | ------------------------------------------- | ---------------------------------------------- | ------------------------------------------- |
> | `throw;`   | Re-raises the **original** exception object | Yes - no copy, no slicing                      | Always - this is the correct way to rethrow |
> | `throw e;` | Throws a **copy** of the caught variable    | No - derived part sliced if caught by base ref | Never use this form                         |

### 27.7 - Function try blocks

- **Function try blocks** wrap an entire function body - including the **member initializer list** - in a try/catch using special syntax.
- They are primarily used in derived class constructors to catch exceptions thrown by **base class or member constructors** - the only way to handle those.
- A constructor's function-level catch block **must** throw or rethrow - it cannot swallow the exception and let construction complete in an invalid state.
- For non-constructor functions, function try blocks offer **no advantage** over a normal try/catch inside the body.

```cpp
class Derived : public Base {
public:
    Derived(int x) try : Base{x} {
        // constructor body
    } catch (...) {
        std::cerr << "Base threw!";
        throw; // must rethrow
    }
};
```

→ _See [09_FunctionTryBlocks](../solutions/Chapter_27_Exceptions/09_FunctionTryBlocks/) for constructor try blocks._

### 27.8 - Exception dangers and downsides

- Exceptions can cause **resource leaks** if cleanup code (`delete`, `close()`) is skipped between a `throw` and `catch` - the solution is **RAII**.
- **Never throw from a destructor** during stack unwinding - two active exceptions simultaneously → `std::terminate` kills the program.
- Exceptions have a small performance cost under normal execution but a **significantly larger cost** when actually thrown due to the unwinding machinery.
- Reserve exceptions for **truly exceptional error conditions** - not routine control flow.

```cpp
auto ptr{ std::make_unique<int>(42) };
riskyFunc(); // if this throws, ptr cleans up automatically
// No manual delete needed - RAII handles it
```

→ _See [11_RAIIAndExceptionSafety](../solutions/Chapter_27_Exceptions/11_RAIIAndExceptionSafety/) for RAII-based resource cleanup during unwinding._

> **Exception Safety Guarantees**
>
> | Guarantee        | Promise                                                   | Example                                                                 | When to use                                             |
> | ---------------- | --------------------------------------------------------- | ----------------------------------------------------------------------- | ------------------------------------------------------- |
> | **No guarantee** | Anything can happen - leaks, corrupt state                | Raw `new` without RAII + throwing code                                  | Avoid - always aim for at least basic                   |
> | **Basic**        | Invariants preserved, no leaks, but state may be modified | `std::vector::push_back` (element inserted or not, but vector is valid) | Default target for most functions                       |
> | **Strong**       | Commit-or-rollback - on failure, state is unchanged       | Copy-and-swap idiom for `operator=`                                     | Critical operations where partial state is unacceptable |
> | **No-throw**     | Function never throws                                     | Destructors, `swap`, move operations                                    | Mark `noexcept`; required by STL for optimal perf       |

### 27.9 - Exception specifications and noexcept

- The `noexcept` specifier marks a function as **non-throwing** - if an exception escapes, `std::terminate` is called and the stack may not unwind.
- Always mark **move constructors**, **move assignment operators**, **swap functions**, and **destructors** as `noexcept`.
- The `noexcept` **operator** can check at compile time whether an expression could throw - usable in constant expressions.
- **Exception safety guarantees** range from no guarantee (anything can happen) to no-throw/no-fail (the function never throws).

```cpp
void swap(MyClass& a, MyClass& b) noexcept {
    std::swap(a.m_data, b.m_data); // guaranteed not to throw
}
```

→ _See [10_NoexceptSpecifier](../solutions/Chapter_27_Exceptions/10_NoexceptSpecifier/) for `noexcept`, `std::terminate`, and the `noexcept` operator._

> **Always mark `noexcept`:**
>
> - Move constructors and move assignment operators
> - `swap()` functions (member and free)
> - Destructors (implicitly `noexcept` since C++11, but be explicit in documentation)
> - Trivial getters/setters that cannot fail
> - `std::hash` specializations (required by unordered containers)
>
> **Never mark `noexcept`:**
>
> - Functions that allocate memory (`new` can throw `std::bad_alloc`)
> - Functions that call other potentially-throwing functions unless you catch internally
> - Virtual functions if derived classes might need to throw

### 27.10 - std::move_if_noexcept

- `std::move_if_noexcept` returns an **rvalue reference** (enabling move) if the move constructor is `noexcept` - otherwise returns a **const lvalue reference** (forcing copy).
- This preserves the **strong exception guarantee** - if a copy fails, the source object remains intact.
- The standard library (e.g. `std::vector::resize`, `push_back`) uses this to **automatically pick** the safest and fastest strategy.
- Making your move constructor `noexcept` is **critical** for optimal container performance.

```cpp
MyClass a;
auto ref = std::move_if_noexcept(a);
// If MyClass(MyClass&&) is noexcept → rvalue ref (move)
// Otherwise → const lvalue ref (copy)
```

→ _See [12_MoveIfNoexcept](../solutions/Chapter_27_Exceptions/12_MoveIfNoexcept/) for `std::move_if_noexcept` and the strong exception guarantee._

### Edge Cases and Caveats

❌ Forgetting to clean up resources:

```cpp
int* p = new int{5};
riskyFunction(); // ❌ if this throws, p is leaked
delete p;
```

✅ Use RAII (smart pointers):

```cpp
auto p = std::make_unique<int>(5);
riskyFunction(); // ✅ p is cleaned up even if exception thrown
```

---

❌ Catching base before derived:

```cpp
try { throw Derived{}; }
catch (const Base&) { /* catches Derived too */ } // ❌
catch (const Derived&) { /* unreachable */ }
```

✅ Catch derived types first:

```cpp
catch (const Derived&) { /* ... */ } // ✅ checked first
catch (const Base&) { /* ... */ }
```

---

❌ Rethrowing with `throw exception;` instead of `throw;`:

```cpp
catch (const Base& e) {
    throw e; // ❌ copies and potentially slices the exception
}
```

✅ Use bare `throw;`:

```cpp
catch (const Base& e) {
    throw; // ✅ rethrows the original exception object
}
```

---

❌ Throwing from destructors:

```cpp
~Foo() { throw std::runtime_error{"oops"}; } // ❌ if during stack unwinding → std::terminate
```

✅ Never throw from destructors. Log the error or swallow it.

---

❌ Expecting type conversions in catch matching:

```cpp
try { throw 42; }
catch (double d) {} // ❌ int doesn't match double - no implicit conversion
```

✅ Catch the exact type or use a base class reference.

---

❌ Variables declared inside try needed in catch:

```cpp
try { int x = compute(); }
catch (...) { std::cout << x; } // ❌ x is out of scope
```

✅ Declare before the try block:

```cpp
int x{};
try { x = compute(); }
catch (...) { std::cout << x; } // ✅
```

---

❌ Assuming `noexcept` prevents all problems:

```cpp
void foo() noexcept { throw 42; } // ❌ std::terminate called - stack may not unwind
```

✅ `noexcept` is a promise, not a safety net. Ensure the function truly cannot throw.

---

❌ Not making move constructors `noexcept`:

```cpp
Foo(Foo&& other) { /* might throw */ } // ❌ STL falls back to slower copies
```

✅ Mark moves `noexcept`:

```cpp
Foo(Foo&& other) noexcept { /* ... */ } // ✅ STL uses move optimization
```

---

### Hands-On Code Projects

| #   | Project                                                                                        | Concept                                                              |
| --- | ---------------------------------------------------------------------------------------------- | -------------------------------------------------------------------- |
| 01  | [01_NeedForExceptions](../solutions/Chapter_27_Exceptions/01_NeedForExceptions/)               | Why return codes fall short and how exceptions solve those problems  |
| 02  | [02_BasicExceptionHandling](../solutions/Chapter_27_Exceptions/02_BasicExceptionHandling/)     | Using `throw`, `try`, and `catch` - no implicit type conversion      |
| 03  | [03_ExceptionsAndFunctions](../solutions/Chapter_27_Exceptions/03_ExceptionsAndFunctions/)     | Exceptions propagating up through function calls                     |
| 04  | [04_StackUnwinding](../solutions/Chapter_27_Exceptions/04_StackUnwinding/)                     | How local variables are destroyed as the stack unwinds               |
| 05  | [05_UncaughtAndCatchAll](../solutions/Chapter_27_Exceptions/05_UncaughtAndCatchAll/)           | Uncaught exceptions, `std::terminate`, and `catch(...)`              |
| 06  | [06_ExceptionClasses](../solutions/Chapter_27_Exceptions/06_ExceptionClasses/)                 | Custom exception classes, `std::exception`, and `std::runtime_error` |
| 07  | [07_InheritanceAndCatchOrder](../solutions/Chapter_27_Exceptions/07_InheritanceAndCatchOrder/) | Catching derived before base - order matters                         |
| 08  | [08_RethrowingExceptions](../solutions/Chapter_27_Exceptions/08_RethrowingExceptions/)         | `throw;` vs `throw exception;` - avoiding slicing                    |
| 09  | [09_FunctionTryBlocks](../solutions/Chapter_27_Exceptions/09_FunctionTryBlocks/)               | Wrapping constructors (including initializer lists) in try/catch     |
| 10  | [10_NoexceptSpecifier](../solutions/Chapter_27_Exceptions/10_NoexceptSpecifier/)               | `noexcept`, `std::terminate`, and the `noexcept` operator            |
| 11  | [11_RAIIAndExceptionSafety](../solutions/Chapter_27_Exceptions/11_RAIIAndExceptionSafety/)     | Resource leaks, RAII, and why destructors must not throw             |
| 12  | [12_MoveIfNoexcept](../solutions/Chapter_27_Exceptions/12_MoveIfNoexcept/)                     | `std::move_if_noexcept` and the strong exception guarantee           |

> **Path:** `solutions/Chapter_27_Exceptions/01_NeedForExceptions/main.cpp` … `12_MoveIfNoexcept/main.cpp`

### Quick Reference

| Feature            | Syntax / Usage                                                                      | Notes                         |
| ------------------ | ----------------------------------------------------------------------------------- | ----------------------------- |
| Throw exception    | `throw std::runtime_error{"msg"};`                                                  | Any copyable type             |
| Try/catch          | `try { ... } catch (const T& e) { ... }`                                            | Catch by const ref            |
| Catch-all          | `catch(...) { ... }`                                                                | Must be last                  |
| Rethrow            | `throw;`                                                                            | Inside catch - preserves type |
| Function try block | `void f() try { ... } catch (...) { ... }`                                          | Wraps entire body             |
| noexcept specifier | `void f() noexcept;`                                                                | Calls terminate if violated   |
| noexcept operator  | `noexcept(expr)`                                                                    | Compile-time check            |
| move_if_noexcept   | `std::move_if_noexcept(obj)`                                                        | Move if safe, else copy       |
| Custom exception   | `class E : public std::runtime_error { using std::runtime_error::runtime_error; };` | Inherit `what()`              |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is RAII and how does it help with exception safety?

<details>
<summary>Show answer</summary>

**Direct answer:** RAII (Resource Acquisition Is Initialization) ties resource ownership to object lifetime the constructor acquires, the destructor releases. When an exception causes stack unwinding, destructors run automatically, ensuring resources are freed even if the normal cleanup code is skipped.

**Detailed explanation:**

```cpp
void risky()
{
    // Without RAII: leak if doWork() throws
    int* data = new int[100];
    doWork();            // throws!
    delete[] data;       // never reached  leak!

    // With RAII: no leak
    auto data2 = std::make_unique<int[]>(100);
    doWork();            // throws!
    // ~unique_ptr runs automatically during stack unwinding
}
```

Smart pointers, `std::lock_guard`, `std::fstream` all use RAII. Prefer them over raw `new/delete`.

</details>

2. Why should you catch derived exceptions before base exceptions?

<details>
<summary>Show answer</summary>

**Direct answer:** Catch blocks are checked top-to-bottom. A base-class catch matches all derived types too, so placing it first hides the more specific handlers below it they would never execute. Always order from most-derived (specific) to most-base (general).

**Detailed explanation:**

```cpp
class BaseException {};
class DerivedException : public BaseException {};

try { throw DerivedException{}; }

// WRONG order:
catch (const BaseException& e)   { /* catches everything, including Derived */ }
catch (const DerivedException& e) { /* never reached! */ }

// CORRECT order:
catch (const DerivedException& e) { /* handles Derived specifically */ }
catch (const BaseException& e)    { /* handles other Base-derived types */ }
catch (...)                        { /* catch-all fallback */ }
```

</details>

3. What is the difference between `throw;` and `throw e;` in a catch block?

<details>
<summary>Show answer</summary>

**Direct answer:** `throw;` rethrows the original exception object with its full dynamic type preserved. `throw e;` throws a copy of the local variable `e` if the original was a derived type caught by base reference, the copy is sliced to the base type. Always use `throw;` to rethrow.

**Detailed explanation:**

```cpp
class Base {};
class Derived : public Base {};

try { throw Derived{}; }
catch (const Base& e)
{
    throw;     // rethrows the Derived object  type preserved
    // throw e; // throws a NEW Base object  Derived part sliced off!
}
```

</details>

4. Why should destructors never throw exceptions?

<details>
<summary>Show answer</summary>

**Direct answer:** If a destructor throws during stack unwinding (caused by another exception), the program has two active exceptions C++ calls `std::terminate` and the program crashes. Destructors are implicitly `noexcept` in C++11+. Swallow or log errors in destructors, never throw.

**Detailed explanation:**

```cpp
class Bad
{
public:
    ~Bad()
    {
        // throw std::runtime_error("oops");  // NEVER DO THIS
        // If Bad is destroyed during stack unwinding  std::terminate!

        // Instead: log the error, swallow it
        try { cleanup(); }
        catch (...) { std::cerr << "cleanup failed\n"; }
    }
};
```

</details>

5. What does `noexcept` mean and what happens if an exception escapes a `noexcept` function?

<details>
<summary>Show answer</summary>

**Direct answer:** `noexcept` promises the function won't throw. If an exception does escape, `std::terminate` is called immediately the stack may not unwind, destructors may not run. It's a hard guarantee that allows the compiler and STL to optimize (e.g., `std::vector` uses move instead of copy if the move constructor is `noexcept`).

**Detailed explanation:**

```cpp
void safe() noexcept
{
    // If anything here throws  std::terminate
}

// Always mark these noexcept:
// - Move constructors and move assignment operators
// - Swap functions
// - Destructors (implicitly noexcept already)

// The noexcept operator checks at compile time:
static_assert(noexcept(safe()));            // true
// static_assert(noexcept(riskyFunc()));    // false if riskyFunc can throw
```

</details>

6. Why should move constructors be marked `noexcept`?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::vector` (and other containers) use `std::move_if_noexcept` during reallocation. If the move constructor is `noexcept`, elements are moved (fast). If not, they're copied (slow but safe preserves the strong exception guarantee). Without `noexcept`, your class gets silently copied instead of moved.

**Detailed explanation:**

```cpp
class Widget
{
    int* m_data{};
public:
    // With noexcept: vector moves elements during resize
    Widget(Widget&& src) noexcept
        : m_data{src.m_data}
    {
        src.m_data = nullptr;
    }

    // Without noexcept: vector copies elements during resize (slower!)
};

std::vector<Widget> v;
v.reserve(1);
v.push_back(Widget{});
v.push_back(Widget{});  // triggers reallocation  move or copy?
```

</details>

7. What are the three exception safety guarantees?

<details>
<summary>Show answer</summary>

**Direct answer:** (1) **Basic guarantee**: invariants preserved, no leaks, but state may be modified. (2) **Strong guarantee**: commit-or-rollback if the operation fails, state is unchanged (as if the call never happened). (3) **No-throw guarantee**: the operation never throws (e.g., destructors, swap). There's also "no guarantee" anything can happen on failure, which should be avoided.

**Detailed explanation:**

```cpp
// No-throw guarantee:
void swap(Widget& a, Widget& b) noexcept { /* ... */ }

// Strong guarantee (copy-and-swap):
Widget& operator=(Widget copy)  // copy may throw
{
    swap(*this, copy);           // swap is noexcept  if we reach here, commit
    return *this;
}   // old data destroyed when 'copy' goes out of scope

// Basic guarantee:
void addElement(int val)
{
    m_data[m_size] = val;  // if this throws, m_size is still valid
    ++m_size;              // but m_data[m_size] may have been partially modified
}
```

</details>

8. Why don't catch blocks perform implicit type conversions?

<details>
<summary>Show answer</summary>

**Direct answer:** Exception matching uses exact type matching (plus base-to-derived), not the implicit conversions that work for function arguments. An `int` exception won't match a `double` handler. This avoids ambiguity with conversions, it would be unclear which of multiple handlers should match.

**Detailed explanation:**

```cpp
try { throw 42; }          // throws int

catch (double d) { }       // does NOT catch int (no implicit conversion)
catch (int i)    { }       // catches int  exact match required

// Base/derived matching DOES work:
try { throw std::runtime_error{"oops"}; }
catch (const std::exception& e) { }  // matches  runtime_error derives from exception
```

Always catch by `const` reference to avoid slicing and unnecessary copies.

</details>

9. What is stack unwinding and how does it work?

<details>
<summary>Show answer</summary>

**Direct answer:** When an exception is thrown, the runtime searches the call stack upward for a matching catch handler. Each function it exits through has its local stack-allocated objects destroyed (destructors called). This process destroying locals as control moves up the stack is called stack unwinding. Raw `new`'d memory without RAII wrappers will leak.

**Detailed explanation:**

```cpp
void c() { throw std::runtime_error{"error"}; }  // throws
void b() { std::string s{"temp"}; c(); }           // s destroyed during unwinding
void a()
{
    try { b(); }
    catch (const std::exception& e)
    {
        std::cout << e.what();  // "error"
    }
    // execution continues here, not at throw site
}
```

This is why every resource should be managed by an RAII object the destructor will run during unwinding.

</details>

10. What is a function try block and when is it useful?

<details>
<summary>Show answer</summary>

**Direct answer:** A function try block wraps the entire function body (including the member initializer list) in a try/catch. It's primarily useful in constructors to catch exceptions thrown by base class or member constructors the only way to handle such exceptions, since the initializer list runs before the constructor body.

**Detailed explanation:**

```cpp
class Derived : public Base
{
    Widget m_widget;
public:
    Derived(int x)
    try                             // function try block
        : Base{x}                   // may throw
        , m_widget{x * 2}           // may throw
    {
        // constructor body
    }
    catch (const std::exception& e)
    {
        std::cerr << "Construction failed: " << e.what();
        // MUST throw or rethrow  can't swallow and complete construction
        throw;
    }
};
```

For non-constructor functions, a regular try/catch inside the body works just as well.

</details>
