# Chapter 7 Recap - Scope, Duration, and Linkage

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- **Scope:** Define variables in the smallest/most limited scope possible.
- **Duration:** Local = automatic; global & `static` locals = static; `new`/`delete` = dynamic.
- **Linkage defaults:** Functions and non-const globals → external. `const`/`constexpr` globals → internal.
- Use `static` to make globals/functions internal. Use `extern` to forward-declare external variables.
- **Avoid non-const global variables.** They are the source of countless bugs and maintenance headaches.
- For global constants in C++17+, prefer **`inline constexpr`** variables in a header file.
- Use the `g_` prefix for globals and `s_` for static locals to signal their nature.
- Keep block nesting ≤ 3 levels; refactor deeply nested code into separate functions.

### 3 Tiny Examples

1.

```cpp
{ // block start
    int x{ 5 }; // x created here
    // x is accessible here
} // block end - x destroyed
// x is NOT accessible here
```

2.

```cpp
namespace Foo {
    int doSomething() { return 1; }
}
int x{ Foo::doSomething() }; // :: scope resolution
```

3.

```cpp
void foo(int param) // param: local variable with block scope, automatic duration
{
    int x{ 10 };    // local: created here, destroyed at }
} // param and x both destroyed here
```

### 3 Common Mistakes

- Forgetting braces on multi-statement `if` bodies
- Accidentally shadowing variables
- Using non-const global variables

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Block (compound statement)** - A group of statements enclosed in `{ }`, treated as a single statement.
- **Scope** - Determines where an identifier can be accessed - either _block scope_ (local) or _global/file scope_.
- **Storage duration** - Rules for when a variable is created/destroyed - _automatic_, _static_, or _dynamic_.
- **Lifetime** - The actual time between a variable's creation and destruction.
- **Linkage** - Whether multiple declarations of the same name refer to the same entity - _no linkage_, _internal_, or _external_.
- **Namespace** - A named region that groups identifiers to prevent naming collisions.
- **Scope resolution operator (`::`)** - Used to specify which namespace an identifier belongs to.
- **Shadowing (name hiding)** - When a variable in an inner scope hides one with the same name in an outer scope.
- **Inline expansion** - Compiler optimization that replaces a function call with the function body.
- **Inline variables/functions (modern meaning)** - Allowed to have multiple identical definitions across translation units.
- **Using declarations vs. using directives** - Two mechanisms for accessing namespaced names without full qualification.

---

### Section-by-Section Detail

### 7.1 - Compound statements (blocks)

- **Blocks** (compound statements) are groups of statements enclosed in `{ }` that act as a single statement
- Blocks enable multiple statements where only one is allowed, such as in `if` bodies
- Blocks can be **nested**, but keep nesting to **3 levels or fewer** for readability
- Variables declared inside a block go **out of scope** at the closing `}`, limiting their lifetime
- **Empty blocks** are legal but serve no practical purpose

```cpp
{ // block start
    int x{ 5 }; // x created here
    // x is accessible here
} // block end - x destroyed
// x is NOT accessible here
```

→ _See [01_CompoundStatements](../solutions/Chapter_07_Scope_Duration_Linkage/01_CompoundStatements)_

### 7.2 - User-defined namespaces and the scope resolution operator

- **Namespaces** prevent naming collisions by grouping identifiers into named regions
- Use the **scope resolution operator** `::` to access members, e.g., `Foo::doSomething()`
- Namespaces can be **nested** (e.g., `Foo::Goo::add()`), **aliased**, and split across multiple blocks/files
- **Namespace aliases** (`namespace Baz = Foo::Goo;`) provide shorthand for deeply nested namespaces
- Declarations from the same namespace can be **split across multiple files**, letting related code share a namespace

```cpp
namespace Foo {
    int doSomething() { return 1; }
}
int x{ Foo::doSomething() }; // :: scope resolution
```

→ _See [02_UserDefinedNamespaces](../solutions/Chapter_07_Scope_Duration_Linkage/02_UserDefinedNamespaces)_

### 7.3 - Local variables

- **Local variables** have **block scope** and **automatic storage duration** - they exist from definition to the end of their enclosing block
- Local variables have **no linkage**, meaning each declaration is an independent entity
- **Function parameters** are also local variables with block scope and automatic duration
- Define variables in the **most limited scope** possible and as close to their first use as practical
- Minimizing a variable's **live range** improves readability and reduces potential for errors

```cpp
void foo(int param) // param: local variable with block scope, automatic duration
{
    int x{ 10 };    // local: created here, destroyed at }
} // param and x both destroyed here
```

→ _See [03_LocalVariables](../solutions/Chapter_07_Scope_Duration_Linkage/03_LocalVariables)_

### 7.4 - Introduction to global variables

- Variables declared outside functions are **global**, with **file scope** and **static duration** (created at program start, destroyed at end)
- **Non-const** globals have **external linkage** by default; `const`/`constexpr` globals have **internal linkage** by default
- Use the `g_` prefix for global variables to signal their nature
- Globals are **zero-initialized** by default before any other initialization takes place
- Avoid **non-const** globals; prefer `const` or `constexpr` for values that must be globally accessible

```cpp
int g_value{ 42 };          // non-const global - external linkage by default
const int g_max{ 100 };     // const global - internal linkage by default
```

> **See also:** [Chapter 5 - Constants and Strings](Chapter%205%20-%20Constants%20and%20Strings.md) for `const` vs `constexpr` rules.

→ _See [04_GlobalVariables](../solutions/Chapter_07_Scope_Duration_Linkage/04_GlobalVariables)_

**Global Variable Defaults:**

| Declaration                      | Default Linkage         | Duration | How to Change Linkage     |
| -------------------------------- | ----------------------- | -------- | ------------------------- |
| `int g_x;`                       | External                | Static   | Add `static` for internal |
| `const int g_x{ 5 };`            | Internal                | Static   | Add `extern` for external |
| `constexpr int g_x{ 5 };`        | Internal                | Static   | Add `extern` (rare)       |
| `static int g_x;`                | Internal (forced)       | Static   | Cannot make external      |
| `extern int g_x;`                | External (forward decl) | Static   | -                         |
| `inline constexpr int g_x{ 5 };` | External                | Static   | Best for shared constants |

### 7.5 - Variable shadowing (name hiding)

- A variable in an **inner block** can **shadow** (hide) a same-named variable in an outer block
- The **inner variable** takes precedence within its scope, making the outer one inaccessible by name
- **Global variables** shadowed by locals can still be accessed via `::` (the scope resolution operator)
- Enable compiler warnings (e.g., `-Wshadow` in GCC/Clang) to detect **variable shadowing**
- Avoid shadowing entirely - it causes **subtle bugs** and reduces code clarity

```cpp
int x{ 5 };          // global x
int main()
{
    int x{ 10 };     // local x shadows global x
    std::cout << x;   // 10 (local)
    std::cout << ::x; // 5 (global, via ::)
}
```

→ _See [05_VariableShadowing](../solutions/Chapter_07_Scope_Duration_Linkage/05_VariableShadowing)_

### 7.6 - Internal linkage

- Identifiers with **internal linkage** are only visible within their **translation unit**
- Use the `static` keyword on a global variable or function to give it **internal linkage**
- `const` and `constexpr` globals have **internal linkage** by default
- **Unnamed namespaces** are the modern alternative to `static` for achieving internal linkage
- Each translation unit with an internally-linked variable gets its own **independent copy**

```cpp
// internal.cpp
static int g_internal{ 42 }; // internal linkage - invisible outside this file
```

→ _See [06_InternalLinkage](../solutions/Chapter_07_Scope_Duration_Linkage/06_InternalLinkage)_

### 7.7 - External linkage and variable forward declarations

- Identifiers with **external linkage** are visible across **translation units**
- **Functions** and **non-const globals** have external linkage by default
- Use `extern` without an initializer to **forward-declare** variables defined in other files
- `extern` with an initializer is a **definition**, not a forward declaration
- `constexpr` variables **cannot** be forward-declared as `constexpr` - use `inline constexpr` in a header instead

```cpp
// global.cpp
int g_x{ 42 };              // definition (external linkage by default)

// main.cpp
extern int g_x;              // forward declaration - no initializer
std::cout << g_x;           // 42
```

> **See also:** [Chapter 2 - Functions and Files](<../1) Intro + Basics/Chapter 2 - C++ Basics Functions and Files.md>) for forward declarations of functions.

→ _See [07_ExternalLinkage](../solutions/Chapter_07_Scope_Duration_Linkage/07_ExternalLinkage)_

### 7.8 - Why (non-const) global variables are evil

- **Non-const global variables** make program state unpredictable since any function can modify them
- They reduce **modularity**, make **debugging** harder, and introduce the **static initialization order fiasco**
- The static initialization order fiasco means **init order of globals across files is undefined**
- Prefer **local variables** and **function parameters** over global state
- If global access is necessary, encapsulate it behind a function returning a `static` local reference ("construct on first use" idiom)

→ _See [08_WhyGlobalsAreEvil](../solutions/Chapter_07_Scope_Duration_Linkage/08_WhyGlobalsAreEvil)_

### 7.9 - Inline functions and variables

- **Inline expansion** replaces function calls with the function body for performance, but the compiler decides when to do this
- In modern C++, the `inline` keyword means **"multiple definitions are allowed"** - the linker deduplicates them
- This enables functions and variables to be **defined in header files** without ODR violations
- `inline` variables (C++17) follow the same **multiple-definition rules** and are ideal for `constexpr` globals in headers
- Do **not** use `inline` as an optimization hint - the compiler ignores it and makes its own inlining decisions

```cpp
// utils.h - safe to include in multiple .cpp files
inline int square(int x) { return x * x; } // multiple definitions OK
```

→ _See [09_InlineFunctionsAndVariables](../solutions/Chapter_07_Scope_Duration_Linkage/09_InlineFunctionsAndVariables)_

### 7.10 - Sharing global constants across multiple files

- **Three approaches** for sharing global constants: (1) `constexpr` in headers (pre-C++17, duplicates per TU), (2) `extern const` in a `.cpp` (single copy, not `constexpr` elsewhere), (3) `inline constexpr` in a header (C++17, best)
- The **`inline constexpr`** approach provides a single definition, compile-time evaluation everywhere, and no linker complications
- Pre-C++17 `constexpr` in headers causes **N copies** (one per translation unit), wasting memory
- The `extern const` approach provides a single copy but loses **compile-time constexpr** availability in other files
- For pre-C++17 codebases, `extern const` remains a **viable alternative**

```cpp
// constants.h - C++17 best practice
#ifndef CONSTANTS_H
#define CONSTANTS_H
inline constexpr double gravity{ 9.8 }; // single copy, compile-time everywhere
#endif
```

→ _See [10_SharingGlobalConstants](../solutions/Chapter_07_Scope_Duration_Linkage/10_SharingGlobalConstants)_

**Three Approaches Compared:**

| Approach                                | Mechanism                                        | Copies   | Constexpr?        | Recommended?       |
| --------------------------------------- | ------------------------------------------------ | -------- | ----------------- | ------------------ |
| `constexpr` in header (pre-C++17)       | Each `.cpp` gets its own copy (internal linkage) | N copies | Yes               | No (wastes memory) |
| `extern const` in `.cpp` + forward decl | Single definition, other files use `extern`      | 1 copy   | No (runtime-only) | Acceptable         |
| `inline constexpr` in header (C++17+)   | ODR-exempt, compiler deduplicates                | 1 copy   | Yes               | **Best**           |

### 7.11 - Static local variables

- Applying `static` to a local variable gives it **static duration** - it persists for the entire program but retains **block scope**
- Static locals are **initialized once** (the first time execution reaches their declaration), not at program start
- They **retain their value** between function calls, making them useful for stateful operations like ID generators
- Use the `s_` prefix to indicate a **static local** variable
- Avoid using static locals to alter **control flow**, as it hurts reusability and introduces hidden side effects

```cpp
int generateID()
{
    static int s_id{ 0 }; // created once, persists for entire program
    return ++s_id;         // returns 1, 2, 3, ... on each call
}
```

→ _See [11_StaticLocalVariables](../solutions/Chapter_07_Scope_Duration_Linkage/11_StaticLocalVariables)_

### 7.12 - Scope, duration, and linkage summary

- **Local variables** have block scope, automatic duration, and no linkage
- **Global variables** have file scope and static duration, with internal or external linkage depending on qualifiers
- `static` and `extern` are **storage class specifiers** that control duration and linkage
- Other storage class specifiers include `thread_local` (one instance per thread) and `mutable` (allows modification in `const` objects)
- This section's **summary table** serves as a quick reference for determining which specifiers apply

### 7.13 - Using declarations and using directives

- `using std::cout;` (**using declaration**) aliases a single name into the current scope
- `using namespace std;` (**using directive**) imports all names from a namespace - **avoid this** due to collision risk
- Never place `using` statements in **headers** or before `#include` directives
- **Using declarations** are safer than using directives because they import only one name
- In modern C++, **explicit `::` qualification** (e.g., `std::cout`) is generally preferred over any form of `using`

```cpp
using std::cout;          // using declaration: imports only cout
cout << "Hello\n";        // OK - cout is now accessible without std::

// using namespace std;   // using directive - AVOID (imports everything)
```

→ _See [12_UsingDeclarationsDirectives](../solutions/Chapter_07_Scope_Duration_Linkage/12_UsingDeclarationsDirectives)_

### 7.14 - Unnamed and inline namespaces

- **Unnamed namespaces** give all their content **internal linkage**, keeping identifiers file-local
- **Inline namespaces** make their content accessible as part of the **parent namespace**, useful for API versioning
- Unnamed namespaces are the preferred modern alternative to `static` for internal linkage of free functions and globals
- Inline namespaces enable **transparent version swapping** by changing which namespace is marked `inline`
- They can be **combined** for internal-linkage versioned content

```cpp
namespace { // unnamed namespace - internal linkage
    void helper() { }    // only visible in this file
}

namespace MyLib {
    inline namespace V2 { // inline: V2 members accessible as MyLib::
        void doWork() { }
    }
}
MyLib::doWork(); // calls V2::doWork transparently
```

→ _See [13_UnnamedAndInlineNamespaces](../solutions/Chapter_07_Scope_Duration_Linkage/13_UnnamedAndInlineNamespaces)_

---

### Edge Cases and Caveats

- **Forgetting braces on multi-statement `if` bodies** - only the first statement is conditional.

  ❌ **Bad:**

  ```cpp
  if (x > 0)
      std::cout << "positive";
      doSomething(); // always runs!
  ```

  ✅ **Good:** Wrap in `{ }`.

- **Accidentally shadowing variables** - a local hides an outer variable.

  ❌ **Bad:**

  ```cpp
  int x{ 5 };
  { int x{ 10 }; } // shadows outer x
  ```

  ✅ **Good:** Use distinct names; enable `-Wshadow`.

- **Using non-const global variables** - leads to unpredictable state.

  ❌ **Bad:** `int g_count{ 0 };` modified from anywhere.
  ✅ **Good:** Pass values via function parameters.

- **Confusing `extern` declaration vs definition** -

  ❌ **Bad:** `extern int g_x{ 1 };` in a header - this is a definition, causes ODR violations.
  ✅ **Good:** `extern int g_x;` (declaration only) in header; define in one `.cpp`.

- **Forward declaring `constexpr` variables** - not allowed.

  ❌ **Bad:** `extern constexpr int x;` - won't compile.
  ✅ **Good:** Use `inline constexpr` in a header (C++17).

- **Placing `using namespace` in headers** - pollutes every file that includes it.

  ❌ **Bad:** `using namespace std;` in a `.h` file.
  ✅ **Good:** Use explicit `std::` qualification.

- **Relying on initialization order of globals across files** - static initialization order fiasco.

  ❌ **Bad:** Global in file A initialized from global in file B - order undefined.
  ✅ **Good:** Use a function returning a `static` local ("construct on first use" idiom).

- **Using `static` locals to change function behavior** - makes function non-reusable.

  ❌ **Bad:** Function returns different results on repeated calls via hidden state.
  ✅ **Good:** Pass state as a parameter.

- **Deeply nesting blocks** - reduces readability past 3 levels.

  ❌ **Bad:** 5+ levels of nested `if`/`for`.
  ✅ **Good:** Extract inner logic into helper functions.

---

### Hands-On Code Projects

| #   | Project                                                                                                          | Concept                                     |
| --- | ---------------------------------------------------------------------------------------------------------------- | ------------------------------------------- |
| 01  | [01_CompoundStatements](../solutions/Chapter_07_Scope_Duration_Linkage/01_CompoundStatements)                   | `{ }` blocks, nesting, scope                |
| 02  | [02_UserDefinedNamespaces](../solutions/Chapter_07_Scope_Duration_Linkage/02_UserDefinedNamespaces)             | Namespaces, `::`, aliases                   |
| 03  | [03_LocalVariables](../solutions/Chapter_07_Scope_Duration_Linkage/03_LocalVariables)                           | Block scope, automatic duration             |
| 04  | [04_GlobalVariables](../solutions/Chapter_07_Scope_Duration_Linkage/04_GlobalVariables)                         | File scope, static duration, `g_` prefix    |
| 05  | [05_VariableShadowing](../solutions/Chapter_07_Scope_Duration_Linkage/05_VariableShadowing)                     | Name hiding, `::` to access globals         |
| 06  | [06_InternalLinkage](../solutions/Chapter_07_Scope_Duration_Linkage/06_InternalLinkage)                         | `static`, unnamed namespaces                |
| 07  | [07_ExternalLinkage](../solutions/Chapter_07_Scope_Duration_Linkage/07_ExternalLinkage)                         | `extern` forward declarations               |
| 08  | [08_WhyGlobalsAreEvil](../solutions/Chapter_07_Scope_Duration_Linkage/08_WhyGlobalsAreEvil)                     | Non-const global dangers, alternatives      |
| 09  | [09_InlineFunctionsAndVariables](../solutions/Chapter_07_Scope_Duration_Linkage/09_InlineFunctionsAndVariables) | `inline` ODR relaxation, header definitions |
| 10  | [10_SharingGlobalConstants](../solutions/Chapter_07_Scope_Duration_Linkage/10_SharingGlobalConstants)           | Three approaches, `inline constexpr`        |
| 11  | [11_StaticLocalVariables](../solutions/Chapter_07_Scope_Duration_Linkage/11_StaticLocalVariables)               | `static` locals, `s_` prefix, ID generators |
| 12  | [12_UsingDeclarationsDirectives](../solutions/Chapter_07_Scope_Duration_Linkage/12_UsingDeclarationsDirectives) | `using` declaration vs directive            |
| 13  | [13_UnnamedAndInlineNamespaces](../solutions/Chapter_07_Scope_Duration_Linkage/13_UnnamedAndInlineNamespaces)   | Internal linkage, API versioning            |

---

### Quick Reference

| Topic                          | Details                                                                                                                                              |
| ------------------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Block scope**                | Variable is accessible only within the `{ }` block where it is defined; destroyed at the closing `}`.                                                |
| **File scope (global scope)**  | Variable is accessible from its declaration to the end of the file. Applies to global variables.                                                     |
| **Global scope (`::`)**        | The global namespace; use `::name` to explicitly access a global identifier.                                                                         |
| **Automatic duration**         | Variable is created at the point of definition and destroyed at the end of its block. Default for local variables.                                   |
| **Static duration**            | Variable is created at program start and destroyed at program end. Applies to globals and `static` locals.                                           |
| **Dynamic duration**           | Variable is created and destroyed by the programmer via `new` and `delete`.                                                                          |
| **No linkage**                 | Each declaration refers to a unique entity. Default for local variables and type definitions.                                                        |
| **Internal linkage**           | Identifier visible only within its translation unit. Apply with `static` or an unnamed namespace. Default for `const`/`constexpr` globals.           |
| **External linkage**           | Identifier visible across translation units. Default for functions and non-const globals. Forward-declare with `extern`.                             |
| **`static` keyword**           | On globals/functions → internal linkage. On locals → static duration (persists across calls). Prefix `s_` for static locals.                         |
| **`extern` keyword**           | Without initializer → forward declaration of an external variable. With initializer → definition. Cannot forward-declare `constexpr` as `constexpr`. |
| **Inline functions**           | Modern meaning: multiple identical definitions allowed across TUs (linker deduplicates). Does _not_ guarantee inlining.                              |
| **Inline variables (C++17)**   | Same ODR-relaxation as inline functions. Enables defining variables in headers without linker errors.                                                |
| **Namespace syntax**           | `namespace Name { /* declarations */ }` - access via `Name::identifier`. Nesting: `namespace A::B { }` (C++17).                                      |
| **`using` declaration**        | `using std::cout;` - imports a single name into the current scope. Safer than a directive.                                                           |
| **`using` directive**          | `using namespace std;` - imports all names from a namespace. Avoid - risks naming collisions. Never in headers.                                      |
| **`inline constexpr` globals** | Best C++17 pattern for shared constants: `inline constexpr int val { 42 };` in a header. Single copy, compile-time available everywhere.             |
| **Unnamed namespaces**         | `namespace { }` - all content gets internal linkage. Modern replacement for `static` on globals/functions.                                           |
| **Inline namespaces**          | `inline namespace V2 { }` - content accessible as if in the parent namespace. Useful for API versioning.                                             |

---

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What are the three properties of an identifier? Define each briefly.

<details>
<summary>Show answer</summary>

**Direct answer:** Every identifier in C++ has three properties: **scope** (where the identifier can be seen/used), **storage duration** (when the variable's memory is created and destroyed), and **linkage** (whether the identifier can be referenced from other translation units).

**Detailed explanation:**
Scope determines _visibility_ - a local variable has block scope (visible from its definition to the end of the block), while a global has file/namespace scope. Storage duration determines _lifetime_ - automatic duration means the object is created and destroyed with its enclosing block; static duration means it lives for the entire program. Linkage determines _sharing_ - no linkage means the name is local to its scope; internal linkage means it's visible only within its translation unit; external linkage means it can be accessed from other translation units via forward declarations.

</details>

2. What is the difference between **automatic** and **static** storage duration?

<details>
<summary>Show answer</summary>

**Direct answer:** Variables with automatic storage duration are created at their point of definition and destroyed at the end of their enclosing block (e.g., local variables). Variables with static storage duration are created once (at program start or first use) and destroyed at program exit (e.g., global variables and `static` local variables).

**Detailed explanation:**
Local variables have automatic duration by default. Adding the `static` keyword to a local variable gives it static duration - it retains its value across function calls and is initialized only once. Global variables always have static duration regardless of whether they're `const`, `extern`, or `static`. Function parameters have automatic duration, just like other local variables.

```cpp
void counter()
{
    static int count{ 0 };  // static duration - initialized once, persists across calls
    ++count;
    std::cout << count << '\n';
}
// counter() prints 1, 2, 3, ... on successive calls
```

</details>

3. How do `static` and unnamed namespaces achieve **internal linkage**?

<details>
<summary>Show answer</summary>

**Direct answer:** The `static` keyword on a global variable or free function gives it internal linkage, restricting visibility to the current translation unit. An unnamed namespace (`namespace { ... }`) does the same - everything declared inside it has internal linkage. Unnamed namespaces are the preferred modern approach.

**Detailed explanation:**
Internal linkage means each translation unit gets its own independent copy of the identifier. `const` and `constexpr` global variables have internal linkage by default. For non-const globals and free functions, you must explicitly use `static` or place them in an unnamed namespace. The unnamed namespace approach is preferred because it works for types, templates, and variables uniformly, while `static` only applies to variables and functions.

```cpp
// file.cpp
static int s_value{ 42 };       // internal linkage via static

namespace
{
    int anotherValue{ 10 };      // internal linkage via unnamed namespace (preferred)
}
```

</details>

4. Why can't you forward-declare a `constexpr` variable as `constexpr`?

<details>
<summary>Show answer</summary>

**Direct answer:** `constexpr` variables must be initialized at their point of declaration with a compile-time constant expression. A forward declaration provides no initializer, so the compiler cannot evaluate the value at compile time. You can forward-declare a `constexpr` variable as `extern const` instead, but it won't be usable in constant expressions in the forwarding file.

**Detailed explanation:**
The whole point of `constexpr` is that the compiler knows the value at compile time. A forward declaration says "this exists somewhere else" - the compiler doesn't see the value, so it can't treat it as a compile-time constant. This is why the `inline constexpr` pattern (C++17) is preferred for sharing constants: you define the constant directly in a header, and `inline` ensures only one copy exists across translation units. No forward declaration needed.

```cpp
// constants.h
inline constexpr int maxSize{ 100 };  // C++17: defined in header, single copy

// old approach - cannot use in constant expressions in other files:
// constants.cpp: extern constexpr int maxSize{ 100 };
// constants.h:  extern const int maxSize;  // forward declaration (not constexpr)
```

</details>

5. Explain the **static initialization order fiasco** and how to avoid it.

<details>
<summary>Show answer</summary>

**Direct answer:** The static initialization order fiasco occurs when a global variable in one translation unit depends on a global variable in another, but the initialization order of globals across translation units is undefined. The dependent variable may read an uninitialized value. Avoid it by using function-local static variables (the "construct on first use" idiom) or by avoiding mutable global state entirely.

**Detailed explanation:**
Within a single translation unit, globals are initialized in order of definition. But across translation units, there is no guaranteed order. If global `A` in file1.cpp depends on global `B` in file2.cpp, `A` might be initialized before `B`, reading garbage. The fix: wrap the global in a function that returns a reference to a local static variable - C++ guarantees local statics are initialized on first use.

```cpp
// Instead of: extern int g_value;
int& getValue()
{
    static int value{ computeValue() };  // initialized on first call, guaranteed
    return value;
}
```

</details>

6. What does the `inline` keyword mean in modern C++? (Not the optimization hint.)

<details>
<summary>Show answer</summary>

**Direct answer:** In modern C++, `inline` means "multiple identical definitions of this function or variable are allowed across translation units, and the linker will deduplicate them." This lets you define functions and variables in header files without violating the One Definition Rule.

**Detailed explanation:**
The original meaning of `inline` was a hint to the compiler to expand a function call in-place. Modern compilers ignore this hint and make their own inlining decisions. The modern meaning is purely about the ODR: `inline` tells the linker that if it sees the same definition in multiple object files, they are intentionally identical and only one should be kept. `inline` variables (C++17) follow the same rule and are especially useful for `constexpr` globals in headers.

```cpp
// myheader.h - safe to include in multiple .cpp files
inline int square(int x) { return x * x; }       // inline function
inline constexpr double pi{ 3.14159 };             // inline variable (C++17)
```

</details>

7. What is the preferred C++17 pattern for sharing global constants across files?

<details>
<summary>Show answer</summary>

**Direct answer:** Define constants as `inline constexpr` in a header file. This gives you a single copy of each constant (not duplicated per translation unit), usable in constant expressions everywhere, with no forward declarations or `.cpp` file needed.

**Detailed explanation:**
Three approaches exist: (1) Pre-C++17: put `constexpr` in a header - each translation unit gets its own copy (wasteful). (2) `extern const` in a `.cpp` with forward declarations - single copy, but not usable in constant expressions in other files. (3) **`inline constexpr` in a header (C++17)** - best of both worlds: single copy, compile-time evaluation everywhere, and simple.

```cpp
// constants.h (C++17 - preferred)
#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants
{
    inline constexpr double pi{ 3.14159265358979 };
    inline constexpr double gravity{ 9.8 };
}

#endif
```

</details>

8. Why is `using namespace std;` dangerous in header files?

<details>
<summary>Show answer</summary>

**Direct answer:** A `using namespace std;` in a header silently imports the entire `std` namespace into every file that includes that header. This pollutes the global namespace for all those files, creating potential name collisions that the including files have no control over and may not even be aware of.

**Detailed explanation:**
Unlike a `.cpp` file (where `using namespace` only affects that one translation unit), a header is included in potentially many files. The `using` directive in the header propagates to all of them, pulling hundreds of names from `std` into the global scope. If any user-defined name collides with a `std` name, you get ambiguity errors - or worse, silent selection of the wrong overload. Always use explicit `std::` prefixes in headers. In `.cpp` files, `using namespace std;` is less harmful but still discouraged.

</details>

9. What is a **block** (compound statement), and why should nesting depth be limited?

<details>
<summary>Show answer</summary>

**Direct answer:** A block is a group of statements enclosed in `{ }` that acts as a single statement. Variables declared inside a block go out of scope at the closing `}`. Nesting should be limited to 3 levels or fewer because deeply nested code is harder to read, test, and debug.

**Detailed explanation:**
Blocks are essential for if/else bodies, loops, and function bodies. Each nested block creates a new scope, and variables in inner blocks can shadow variables in outer blocks (which should be avoided). If you find yourself nesting deeply, consider extracting the inner logic into a separate function to flatten the structure.

</details>

10. What is a **using declaration** vs. a **using directive**, and which is safer?

<details>
<summary>Show answer</summary>

**Direct answer:** A using declaration (`using std::cout;`) imports a single specific name into the current scope. A using directive (`using namespace std;`) imports _all_ names from a namespace. Using declarations are safer because they only introduce the specific names you need, minimizing the risk of name collisions.

**Detailed explanation:**
Using declarations are generally acceptable even in header files (though scoped to a block is safest). Using directives should never appear in headers and should be used sparingly in `.cpp` files. The safest approach overall is to use explicit namespace prefixes (`std::cout`, `std::string`) everywhere, making the code maximally clear about where each name comes from.

```cpp
using std::cout;         // using declaration - imports only 'cout'
using namespace std;     // using directive - imports everything from std (risky)
std::cout << "safest";   // explicit prefix (best practice)
```

</details>
