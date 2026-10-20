# Chapter 2 Recap - C++ Basics: Functions and Files

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Every executable program needs a `main()` function; it should return `0` on success.
- A value-returning function **must** return a value in all code paths, or you get undefined behavior.
- Do not put a `return;` at the end of a void function - it is redundant.
- Use **pass by value** for now: arguments are _copied_ into parameters, so modifying a parameter inside a function does not affect the caller's variable.
- Variables in different functions are completely independent, even if they share the same name (**functional separation**).
- Define local variables close to their first use.
- Use a function parameter when the caller supplies the value; use a local variable otherwise.
- Follow DRY - extract repeated code into functions.

### 3 Tiny Examples

1.

```cpp
void greet()               // function definition
{
    std::cout << "Hello!\n";
}

int main()
{
    greet();               // function call - CPU jumps to greet(), then returns
    return 0;
}
```

2.

```cpp
int add(int x, int y) { return x + y; }
int main() { std::cout << add(3, 4) << '\n'; } // prints 7
```

3.

```cpp
void printHi()                // void = returns nothing
{
    std::cout << "Hi!\n";
    // no return needed
}
```

### 3 Common Mistakes

- Forgetting parentheses on a function call
- Forgetting to return a value
- Trying to use a void function's "return value"

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Function** - a reusable sequence of statements designed to do a particular job
- **Function call** - tells the CPU to interrupt the current function and execute another; the initiator is the **caller**, the target is the **callee**
- **Return type & return value** - the type a function promises to return, and the actual value copied back to the caller (**return by value**)
- **Void function** - a function with return type `void` that does not return a value
- **Parameters vs. arguments** - parameters are variables declared in the function header; arguments are the values passed by the caller (copied via **pass by value**)
- **Local variables & scope** - variables defined inside a function (including parameters) are local; they exist only within their enclosing braces (scope is compile-time, lifetime is runtime)
- **Forward declaration** - telling the compiler an identifier exists before defining it; done via a **function prototype** (header + semicolon, no body)
- **One Definition Rule (ODR)** - each function/variable may have only one definition per file and per program (with some exceptions for types, templates, and inline entities)
- **Namespace** - a scope region that isolates identifiers to prevent naming collisions; the standard library lives in `std`
- **Preprocessor & directives** - a pre-compilation phase that processes `#include`, `#define`, `#ifdef`/`#ifndef`/`#endif`, etc.
- **Header file (.h)** - a file containing forward declarations that can be `#include`d into multiple source files
- **Header guard** - `#ifndef` / `#define` / `#endif` (or `#pragma once`) to prevent a header's contents from being included more than once in the same translation unit
- **DRY (Don't Repeat Yourself)** - principle of minimizing redundant code by using functions and variables

### Section-by-Section Detail

### 2.1 - Introduction to functions

- A **function** is a named, reusable block of code
- When called, the CPU "bookmarks" the caller, executes the **callee**, then returns to the caller
- Functions must be **defined** (or **forward-declared**) before they are called
- C++ does **not** allow nested function definitions
- The compiler processes top-to-bottom in a **single pass** - it must know about a function before encountering a call to it

```cpp
void greet()               // function definition
{
    std::cout << "Hello!\n";
}

int main()
{
    greet();               // function call - CPU jumps to greet(), then returns
    return 0;
}
```

→ _See [01_IntroToFunctions](../solutions/Chapter_02_Functions_And_Files/01_IntroToFunctions/) for basic function definition and calling._

### 2.2 - Function return values (value-returning functions)

- A **value-returning function** specifies a non-void return type and uses `return` to send a value back
- `main()` returns a **status code** (`0` = success); the OS uses it to judge whether the program succeeded
- Omitting `return` from a non-void function causes **undefined behavior** (except `main`, which implicitly returns `0`)
- The return value is **copied** back to the caller (**return by value**) - the caller gets its own independent copy

```cpp
int add(int x, int y) { return x + y; }
int main() { std::cout << add(3, 4) << '\n'; } // prints 7
```

→ _See [02_ReturnValues](../solutions/Chapter_02_Functions_And_Files/02_ReturnValues/) for return-by-value and status code examples._

### 2.3 - Void functions (non-value returning functions)

- **Void functions** (return type `void`) perform an action but return nothing
- They do **not** need a `return` statement; an empty `return;` at the end is redundant
- A void function **cannot** be used where a value is required (e.g., `std::cout << voidFunc()`)
- Typically used for **side effects** - printing output, modifying external state
- Early `return;` is acceptable for control flow, but not at the very end of the body

```cpp
void printHi()                // void = returns nothing
{
    std::cout << "Hi!\n";
    // no return needed
}
```

→ _See [03_VoidFunctions](../solutions/Chapter_02_Functions_And_Files/03_VoidFunctions/) for void function patterns._

### 2.4 - Introduction to function parameters and arguments

- **Parameters** are the variables declared in the function header; **arguments** are the values supplied at the call site
- Arguments are **copied** into parameters (**pass by value**)
- The number and types of arguments must **match** the parameters
- **Unreferenced parameters** can be left unnamed to suppress compiler warnings
- Changes to a parameter inside the function **never affect** the caller's original variable

```cpp
int multiply(int x, int y)    // x and y are parameters
{
    return x * y;
}

int result{ multiply(3, 4) }; // 3 and 4 are arguments, copied into x and y
```

→ _See [04_ParametersAndArguments](../solutions/Chapter_02_Functions_And_Files/04_ParametersAndArguments/) for pass-by-value demonstrations._

### 2.5 - Introduction to local scope

- **Local variables** (including parameters) are created at definition and destroyed at the end of their enclosing block
- **Scope** (compile-time) = where a name is visible; **lifetime** (runtime) = how long the object exists
- Variables in different functions are **independent**, even with the same name
- Define local variables **close to their first use**
- A name going out of scope doesn't always mean the object is destroyed (though for locals it does)
- This distinction becomes critical with **references** and **dynamic memory** later

```cpp
int main()
{
    int x{ 5 };       // x created here
    {
        int y{ 10 };  // y created here - inner scope
        std::cout << x + y; // both visible
    }                  // y destroyed here
    // std::cout << y; // error: y not in scope
    return 0;
}                      // x destroyed here
```

> **See also:** [Chapter 7 - Scope, Duration, and Linkage](Chapter%207%20-%20Scope,%20Duration,%20and%20Linkage.md) for a deep dive into scope, lifetime, and linkage rules.

→ _See [05_LocalScope](../solutions/Chapter_02_Functions_And_Files/05_LocalScope/) for scope vs. lifetime demos._

### 2.6 - Why functions are useful, and how to use them effectively

- Functions aid **organization**, **reusability**, **testing**, **extensibility**, and **abstraction**
- Each function should ideally perform **one task**; separate calculation from output
- Code that appears more than once or does a well-defined job is a good candidate for extraction
- **Abstraction** lets callers use a function without knowing _how_ it works - only _what_ it does
- Implementation changes don't affect callers as long as the **interface stays the same** (DRY)

→ _See [06_EffectiveFunctions](../solutions/Chapter_02_Functions_And_Files/06_EffectiveFunctions/) for DRY refactoring examples._

### 2.7 - Forward declarations and definitions

- A **forward declaration** (function prototype) tells the compiler a function exists before its definition appears
- A **definition** implements/instantiates; a **declaration** merely announces existence
- The **ODR** (One Definition Rule): each identifier may have only one definition per scope/file/program (with exceptions)
- Without forward declarations, mutual recursion or calling functions defined later would be **impossible** (single-pass compilation)

```cpp
int add(int x, int y); // forward declaration (prototype)
int main() { std::cout << add(3, 4); }
int add(int x, int y) { return x + y; } // definition
```

→ _See [07_ForwardDeclarations](../solutions/Chapter_02_Functions_And_Files/07_ForwardDeclarations/) for prototypes and ODR demos._

### 2.8 - Programs with multiple code files

- Larger programs split code across multiple `.cpp` files, each compiled **independently**
- The compiler does **not** remember other files - forward declarations or headers bridge the gap
- The **linker** connects everything together by resolving cross-file references
- Each `.cpp` file plus its included headers forms a **translation unit** - the independent unit the compiler processes

→ _See [08_MultiFilePrograms](../solutions/Chapter_02_Functions_And_Files/08_MultiFilePrograms/) for multi-file compilation and linking._

### 2.9 - Naming collisions and an introduction to namespaces

- Identical identifiers in the same scope cause **naming collisions** (compiler or linker errors)
- **Namespaces** isolate names to avoid conflicts; the standard library lives in `std`
- Use the `std::` prefix (**scope resolution operator**) to access standard library members
- Avoid `using namespace std;` - it defeats the purpose of namespaces
- `::identifier` (empty left side) explicitly accesses the **global namespace**
- Namespaces can be **nested**, and you can create your own to organize large projects

```cpp
namespace myLib {
    int getValue() { return 42; }
}

int main()
{
    std::cout << myLib::getValue();  // :: = scope resolution operator
}
```

> **See also:** [Chapter 7 - Scope, Duration, and Linkage](Chapter%207%20-%20Scope,%20Duration,%20and%20Linkage.md) for user-defined namespaces and the scope resolution operator.

→ _See [09_Namespaces](../solutions/Chapter_02_Functions_And_Files/09_Namespaces/) for namespace collision demos._

### 2.10 - Introduction to the preprocessor

- The **preprocessor** runs before compilation, processing directives like `#include`, `#define`, `#ifdef`/`#ifndef`/`#endif`, `#if 0`
- `#include` **pastes** a file's contents in place; `#define` creates **macros** (prefer alternatives in modern C++)
- **Conditional compilation** (`#ifdef`, `#if 0`, etc.) includes/excludes code at preprocessing time
- Directives are **file-scoped** and resolved top-to-bottom
- The preprocessor does **pure text substitution** - no understanding of C++ syntax or types
- Modern C++ prefers `constexpr` variables and `inline` functions over `#define` macros

```cpp
#include <iostream>   // pastes iostream contents here

#define MAX_SIZE 100  // text substitution macro (prefer constexpr)

#if 0
    // this code is "commented out" by the preprocessor
#endif
```

→ _See [10_Preprocessor](../solutions/Chapter_02_Functions_And_Files/10_Preprocessor/) for `#include`, `#define`, and conditional compilation._

### 2.11 - Header files

- **Header files** (`.h`) hold forward declarations shared across source files via `#include`
- Use `< >` for **system/library** headers; `" "` for **your own** headers
- Source files should `#include` their **paired header**
- Do **not** put function/variable definitions in headers (for now); do **not** `#include` `.cpp` files
- `< >` searches system include directories first; `" "` searches the project directory first, then falls back to system

```cpp
// add.h - header with forward declaration
#pragma once
int add(int x, int y);

// main.cpp
#include "add.h"          // user header: double quotes
#include <iostream>        // system header: angle brackets
```

→ _See [11_HeaderFiles](../solutions/Chapter_02_Functions_And_Files/11_HeaderFiles/) for paired headers and include conventions._

### 2.12 - Header guards

- **Header guards** (`#ifndef` / `#define` / `#endif`) prevent a header from being copied into the same translation unit more than once
- `#pragma once` is a widely-supported **shorthand alternative**
- Guards do **not** prevent inclusion in multiple different `.cpp` files (that's by design)
- They work by wrapping contents in a conditional - if the guard macro is already defined, the preprocessor **skips** the contents
- The macro state **resets** for each translation unit, so the same header can (and should) appear in multiple source files

```cpp
// myheader.h
#ifndef MYHEADER_H
#define MYHEADER_H
int add(int x, int y);  // forward declaration
#endif
```

→ _See [12_HeaderGuards](../solutions/Chapter_02_Functions_And_Files/12_HeaderGuards/) for header guard and `#pragma once` patterns._

### 2.13 - How to design your first programs

- Follow a **top-down process**: define the goal → define requirements → choose tools → break into sub-problems (functions) → determine sequence → implement
- Keep programs **simple at first**; add features over time
- **Test each piece** as you go - incremental development catches bugs early
- Resist writing the entire program at once; write a little, test a little

→ _See [13_ProgramDesign](../solutions/Chapter_02_Functions_And_Files/13_ProgramDesign/) for a top-down design walkthrough._

### Edge Cases and Caveats

- **Forgetting parentheses on a function call**

  ❌ **Bad:**

  ```cpp
  doPrint;   // evaluates to a function pointer - does NOT call the function
  ```

  ✅ **Good:**

  ```cpp
  doPrint();  // actually calls the function
  ```

- **Forgetting to return a value** from a non-void function - causes undefined behavior.

  ❌ **Bad:**

  ```cpp
  int getValue() { /* no return! */ } // UB
  ```

  ✅ **Good:**

  ```cpp
  int getValue() { return 42; }       // always return a value
  ```

- **Trying to use a void function's "return value"**

  ❌ **Bad:**

  ```cpp
  void printHi() { std::cout << "Hi"; }
  std::cout << printHi(); // error: void used as a value
  ```

  ✅ **Good:**

  ```cpp
  printHi(); // call it as a statement, don't use as an expression
  ```

- **Calling a function before it is declared or defined**

  ❌ **Bad:**

  ```cpp
  int main() { foo(); } // error: 'foo' not declared
  void foo() { }
  ```

  ✅ **Good:**

  ```cpp
  void foo();            // forward declaration
  int main() { foo(); }  // OK
  void foo() { }
  ```

- **Mismatched forward declaration and definition**

  ❌ **Bad:**

  ```cpp
  int add(int x, int y);          // declares 2 params
  int add(int x, int y, int z) {} // defines 3 params - linker error
  ```

  ✅ **Good:** Ensure the signature (return type, parameters) matches exactly.

- **Defining functions inside other functions** - not allowed in C++.

  ❌ **Bad:**

  ```cpp
  int main() {
      int add(int x, int y) { return x + y; } // error: nested function
  }
  ```

  ✅ **Good:** Define all functions at file/namespace scope.

- **Putting function definitions in headers** - leads to ODR violations.

  ❌ **Bad:** `int add(int x, int y) { return x + y; }` in a `.h` included by multiple `.cpp` files.
  ✅ **Good:** Put only declarations in headers; definitions in `.cpp` files.

- **Forgetting header guards** - causes duplicate-definition errors.

  ❌ **Bad:** A `.h` file without `#ifndef`/`#define`/`#endif` included twice in the same TU.
  ✅ **Good:** Always use `#pragma once` or `#ifndef` / `#define` / `#endif` guards.

- **Using `using namespace std;`** - risks naming collisions.

  ❌ **Bad:**

  ```cpp
  using namespace std;  // imports ALL of std into scope
  ```

  ✅ **Good:**

  ```cpp
  std::cout << "explicit prefix"; // no collision risk
  ```

- **Forgetting to add a `.cpp` file to your build** - causes "unresolved external" linker errors.

  ❌ **Bad:** Defining `add()` in `math.cpp` but not adding `math.cpp` to the project.
  ✅ **Good:** Add every `.cpp` file to your project/build system.

- **Using `#include "file.cpp"`** instead of adding the file to the build.

  ❌ **Bad:** `#include "math.cpp"` - fragile and error-prone.
  ✅ **Good:** Compile `.cpp` files separately; `#include` only `.h` headers.

- **Assuming a parameter change affects the caller**

  ❌ **Bad:**

  ```cpp
  void increment(int x) { x++; } // only modifies the local copy
  ```

  ✅ **Good:** Pass by value means changes are local; return the result or use references (Ch 12).

---

### Hands-On Code Projects

| #   | Project                                                                                             | Concept                                                 |
| --- | --------------------------------------------------------------------------------------------------- | ------------------------------------------------------- |
| 01  | [01_IntroToFunctions](../solutions/Chapter_02_Functions_And_Files/01_IntroToFunctions/)             | Function definition, calling, execution flow            |
| 02  | [02_ReturnValues](../solutions/Chapter_02_Functions_And_Files/02_ReturnValues/)                     | Return by value, status codes from `main()`             |
| 03  | [03_VoidFunctions](../solutions/Chapter_02_Functions_And_Files/03_VoidFunctions/)                   | Void functions, side effects, early returns             |
| 04  | [04_ParametersAndArguments](../solutions/Chapter_02_Functions_And_Files/04_ParametersAndArguments/) | Parameters vs arguments, pass by value                  |
| 05  | [05_LocalScope](../solutions/Chapter_02_Functions_And_Files/05_LocalScope/)                         | Block scope, variable lifetime, independence            |
| 06  | [06_EffectiveFunctions](../solutions/Chapter_02_Functions_And_Files/06_EffectiveFunctions/)         | DRY principle, single-task functions, separation of I/O |
| 07  | [07_ForwardDeclarations](../solutions/Chapter_02_Functions_And_Files/07_ForwardDeclarations/)       | Function prototypes, ODR, forward declarations          |
| 08  | [08_MultiFilePrograms](../solutions/Chapter_02_Functions_And_Files/08_MultiFilePrograms/)           | Translation units, independent compilation, linker      |
| 09  | [09_Namespaces](../solutions/Chapter_02_Functions_And_Files/09_Namespaces/)                         | Naming collisions, `std::` prefix, `::` operator        |
| 10  | [10_Preprocessor](../solutions/Chapter_02_Functions_And_Files/10_Preprocessor/)                     | `#include`, `#define`, `#ifdef`, `#if 0`                |
| 11  | [11_HeaderFiles](../solutions/Chapter_02_Functions_And_Files/11_HeaderFiles/)                       | Header files, paired headers, `< >` vs `" "`            |
| 12  | [12_HeaderGuards](../solutions/Chapter_02_Functions_And_Files/12_HeaderGuards/)                     | `#ifndef`/`#define`/`#endif`, `#pragma once`            |
| 13  | [13_ProgramDesign](../solutions/Chapter_02_Functions_And_Files/13_ProgramDesign/)                   | Top-down design, incremental implementation             |
| 14  | [14_CommonPitfalls](../solutions/Chapter_02_Functions_And_Files/14_CommonPitfalls/)                 | Common function and header mistakes                     |

### Quick Reference

| Topic                        | Details                                                                                                        |
| ---------------------------- | -------------------------------------------------------------------------------------------------------------- |
| **Function definition**      | `returnType functionName(parameters) { body }`                                                                 |
| **Function call**            | `functionName(arguments);` - parentheses required even with no arguments                                       |
| **Return statement**         | `return expression;` - copies the value back to the caller (return by value)                                   |
| **Void function**            | `void functionName() { }` - no return value; do not use where a value is expected                              |
| **Parameters vs. arguments** | Parameters: variables in the declaration; Arguments: values passed at the call site (copied via pass by value) |
| **Forward declaration**      | `returnType functionName(parameters);` - prototype with semicolon, no body                                     |
| **One Definition Rule**      | One definition per function/variable per file and per program (exceptions: types, templates, inline)           |
| **Multi-file compilation**   | Each `.cpp` → translation unit → compiled independently → linker resolves references                           |
| **Namespace access**         | `std::cout`, `myNamespace::myFunc()` - use `::` scope resolution operator                                      |
| **Global namespace access**  | `::identifier` - explicitly accesses the global scope                                                          |
| **`#include` (system)**      | `#include <header>` - searches system/library include directories first                                        |
| **`#include` (user)**        | `#include "header.h"` - searches project directory first, then system directories                              |
| **`#define` macro**          | `#define NAME value` - text substitution; prefer `constexpr`/`inline` in modern C++                            |
| **Conditional compilation**  | `#ifdef` / `#ifndef` / `#endif` - include/exclude code blocks at preprocessing time                            |
| **Comment-out block**        | `#if 0` ... `#endif` - preprocessor skips the enclosed code                                                    |
| **Header guard pattern**     | `#ifndef HEADER_H` ⟶ `#define HEADER_H` ⟶ _contents_ ⟶ `#endif`                                                |
| **Pragma once**              | `#pragma once` - non-standard but widely supported shorthand for header guards                                 |
| **Paired header rule**       | A `.cpp` file should `#include` its own `.h` header first to catch declaration mismatches                      |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is the difference between a **parameter** and an **argument**?

<details>
<summary>Show answer</summary>

**Direct answer:** A parameter is a variable declared in a function's header that receives data. An argument is the actual value passed by the caller at the call site. Arguments are copied into parameters (pass by value), so modifying a parameter inside the function does not affect the caller's original variable.

**Detailed explanation:**
Parameters act as local variables within the function, initialized with copies of the arguments. The number and types of arguments must match the function's parameters. Because C++ uses pass by value by default, the function works with independent copies - any changes to a parameter are invisible to the caller.

```cpp
int multiply(int x, int y)    // x and y are parameters
{
    return x * y;
}

int result{ multiply(3, 4) }; // 3 and 4 are arguments, copied into x and y
```

</details>

2. What happens if a non-void function doesn't have a `return` statement?

<details>
<summary>Show answer</summary>

**Direct answer:** It causes undefined behavior. The caller expects a return value, but none is provided, so the program may crash, return garbage, or appear to work by accident. The one exception is `main()`, which implicitly returns `0` if no `return` statement is present.

**Detailed explanation:**
A value-returning function specifies a non-void return type and promises to send a value back to the caller. If the function reaches the end of its body without hitting a `return` statement, the behavior is undefined - the caller receives whatever happens to be on the stack or in the return register. The compiler may warn about this (`-Wall` catches it), but it is not guaranteed to be an error on all compilers. Always ensure every code path in a non-void function returns a value.

```cpp
int getValue() { /* no return! */ } // undefined behavior
int main() { std::cout << getValue(); } // could print anything
```

</details>

3. Why can't you define a function inside another function in C++?

<details>
<summary>Show answer</summary>

**Direct answer:** C++ does not support nested function definitions - the language grammar simply does not allow it. All functions must be defined at file scope (or namespace scope). This is a deliberate design decision that keeps the compilation model simpler and maintains clear separation between functions.

**Detailed explanation:**
Unlike some languages (Python, JavaScript), C++ requires every function to be defined at the top level of a file or within a namespace - not inside another function's body. If you try to define a function inside `main()` or any other function, you'll get a compile error. This design choice simplifies name lookup, linkage, and the one-pass compilation model. If you need function-like behavior inside a function, C++11 introduced **lambdas** as a workaround.

```cpp
// BAD - compile error: nested function
int main() {
    int add(int x, int y) { return x + y; }
}

// GOOD - define at file scope
int add(int x, int y) { return x + y; }
int main() { std::cout << add(3, 4); }
```

</details>

4. What is the **One Definition Rule (ODR)**? Name one exception to it.

<details>
<summary>Show answer</summary>

**Direct answer:** The ODR states that each function or variable may have only one definition within any given file (translation unit) and only one definition across the entire program. Exceptions include type definitions (classes/structs), template definitions, and inline functions/variables - these may be defined identically in multiple translation units.

**Detailed explanation:**
The ODR is fundamental to how C++ compiles and links programs. If you define the same function in two `.cpp` files, the linker will report a "multiple definition" error. Forward declarations are pure declarations (not definitions) and can appear multiple times without violating the ODR. The exceptions exist because types, templates, and inline entities _must_ be available in every translation unit that uses them, so the standard allows identical definitions in multiple files as long as they are truly identical.

</details>

5. What is the difference between a **forward declaration** and a **definition**?

<details>
<summary>Show answer</summary>

**Direct answer:** A forward declaration (function prototype) tells the compiler that an identifier exists and what its type is, without providing its implementation. A definition actually implements the function or allocates storage for a variable. You can declare something many times, but you can only define it once (per the ODR).

**Detailed explanation:**
Forward declarations are necessary because C++ compiles files top-to-bottom in a single pass. If function `main()` calls `add()` but `add()` is defined later in the file (or in another file), the compiler won't know about it unless you provide a forward declaration first. A forward declaration is just the function header followed by a semicolon (no body):

```cpp
int add(int x, int y); // forward declaration (prototype) - no body
int main() { std::cout << add(3, 4); } // OK - compiler knows about add()
int add(int x, int y) { return x + y; } // definition - has body
```

</details>

6. Why should you use `#include "myheader.h"` (double quotes) for your own headers, but `#include <iostream>` (angle brackets) for library headers?

<details>
<summary>Show answer</summary>

**Direct answer:** Double quotes (`"header.h"`) tell the preprocessor to search the project's own directory first before falling back to system directories. Angle brackets (`<header>`) search only the system/library include directories. Using the correct form ensures the compiler finds the right file and makes the intent clear to other programmers.

**Detailed explanation:**
When you write `#include "myheader.h"`, the preprocessor looks in the same directory as the source file (and other project-configured directories) first, then falls back to system include paths. When you write `#include <iostream>`, it searches only the system/standard library include directories. Using double quotes for your own headers and angle brackets for library headers is a widely followed convention that prevents accidental name collisions and clearly communicates the origin of each header.

```cpp
#include <iostream>        // system header - angle brackets
#include "add.h"           // project header - double quotes
```

</details>

7. What is the purpose of **header guards**, and why don't they prevent a header from being included in multiple `.cpp` files?

<details>
<summary>Show answer</summary>

**Direct answer:** Header guards prevent the same header from being pasted into a single translation unit more than once (which would cause duplicate-definition errors). They don't prevent inclusion across different `.cpp` files because each `.cpp` file is an independent translation unit with its own preprocessor state - the guard macro is undefined at the start of each new translation unit.

**Detailed explanation:**
Header guards work by wrapping the entire header in a conditional: `#ifndef MYHEADER_H` / `#define MYHEADER_H` / `#endif`. The first time the header is `#include`d in a translation unit, the macro is not yet defined, so the contents are included and the macro is defined. If the same header is `#include`d again (e.g., indirectly through another header), the macro is already defined, so the preprocessor skips the contents. However, each `.cpp` file starts its preprocessing from scratch, so the macro is undefined again - meaning the header _will_ be included once per `.cpp` file, which is by design.

```cpp
// myheader.h
#ifndef MYHEADER_H
#define MYHEADER_H
int add(int x, int y);  // forward declaration
#endif

// Alternative (widely supported but non-standard):
#pragma once
```

</details>

8. Why should each function perform a single task?

<details>
<summary>Show answer</summary>

**Direct answer:** Single-task functions are easier to understand, test, reuse, and maintain. If a function does multiple things, changing one part risks breaking the other, and the function becomes harder to name, test in isolation, and reuse in different contexts.

**Detailed explanation:**
Functions provide **organization**, **reusability**, **testing**, **extensibility**, and **abstraction**. A function that performs exactly one well-defined task can be tested independently, reused in different parts of the program, and understood at a glance from its name. Separating calculation from output is a key example: a function that both computes a result and prints it cannot be reused in a context where you need the result but don't want it printed. The DRY (Don't Repeat Yourself) principle naturally leads to single-task functions - if you find yourself writing the same code in multiple places, extract it into a function.

</details>

9. What is a **translation unit**, and how does it relate to multi-file compilation?

<details>
<summary>Show answer</summary>

**Direct answer:** A translation unit is a single `.cpp` source file plus all of the headers it `#include`s (after preprocessing). Each translation unit is compiled independently into an object file, and the linker combines all object files into the final executable.

**Detailed explanation:**
The compiler processes each `.cpp` file in isolation - it has no knowledge of other `.cpp` files in your project. This is why you need forward declarations or headers: so the compiler knows about functions defined in other translation units. The linker's job is to resolve all cross-file references after compilation. If the linker can't find a definition for a declared function, you get an "unresolved external symbol" error.

</details>

10. Why should you avoid `using namespace std;`?

<details>
<summary>Show answer</summary>

**Direct answer:** `using namespace std;` imports every name from the `std` namespace into the current scope, defeating the purpose of namespaces by risking naming collisions. If you define a function or variable with the same name as something in `std`, the compiler may pick the wrong one or report an ambiguity error. Use the `std::` prefix explicitly instead.

**Detailed explanation:**
Namespaces exist specifically to prevent naming collisions. The `std` namespace contains thousands of identifiers (`count`, `find`, `max`, `min`, `size`, etc.). If you write `using namespace std;` and then define your own `count` variable, you'll get a hard-to-diagnose conflict. The `std::` prefix is explicit, unambiguous, and actually makes code more readable because it's immediately clear that `std::cout` comes from the standard library.

```cpp
// BAD - risks naming collisions
using namespace std;
int count = 5; // conflicts with std::count!

// GOOD - explicit and safe
std::cout << "No collision risk\n";
```

</details>

11. What is the difference between **scope** and **lifetime** for local variables?

<details>
<summary>Show answer</summary>

**Direct answer:** Scope is a compile-time property that determines where in the source code a variable's name is visible. Lifetime is a runtime property that determines how long the variable's storage exists in memory. For local variables, both end at the closing brace of the enclosing block, but for other entities (like references and dynamic memory) they can differ.

**Detailed explanation:**
A local variable's scope extends from its point of definition to the end of the enclosing block. Its lifetime also begins at its definition and ends when the block exits. Variables in different functions are completely independent even if they share the same name - each function has its own scope. This distinction becomes critical in later chapters when you learn about references (whose lifetime may extend beyond the referred-to object's scope) and dynamic memory (whose lifetime is controlled by the programmer, not by scope).

```cpp
int main()
{
    int x{ 5 };       // x scope + lifetime begin
    {
        int y{ 10 };  // y scope + lifetime begin
    }                  // y scope + lifetime end
    // y is not accessible here
    return 0;
}                      // x scope + lifetime end
```

</details>
