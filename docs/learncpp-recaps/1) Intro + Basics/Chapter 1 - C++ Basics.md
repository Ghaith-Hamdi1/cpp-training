# Chapter 1 Recap - C++ Basics

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Every C++ program must have a `main()` function - execution starts there. Without it, the linker will produce an error because the OS needs an entry point to call.
- Most statements end with a semicolon. Preprocessor directives (like `#include`) and function/class bodies enclosed in `{}` are notable exceptions.
- **Always initialize your variables** - prefer direct-list-initialization `int x{5};` or value-initialization `int x{};`. This eliminates an entire class of undefined-behavior bugs and costs nothing at runtime.
- List-initialization disallows narrowing conversions, making it safer than copy or direct initialization. For example, `int x{4.5};` is a compile error, catching data-loss bugs that `int x = 4.5;` would silently allow.
- Use `'\n'` over `std::endl` for better performance. `std::endl` flushes the buffer every time, which can be orders of magnitude slower in loops producing heavy output.
- `std::cin >> x` uses `>>` (extraction); `std::cout << x` uses `<<` (insertion) - don't mix them up. The arrows point in the direction data flows: `>>` from `cin` _into_ the variable, `<<` from the value _into_ `cout`.
- Using an uninitialized variable is **undefined behavior** - anything can happen. The compiler may optimize based on the assumption that UB never occurs, making bugs even harder to diagnose.
- Comment _what_ at the function level, _how_ inside functions, and _why_ at the statement level. Good comments explain intent, not mechanics - they should tell a reader something the code alone cannot.

### 3 Tiny Examples

1.

```cpp
int main()          // function definition - execution starts here
{
    int x{ 5 };    // declaration statement
    x = x + 1;     // expression statement (with side effect)
    return 0;       // return statement - 0 means success
}
```

2.

```cpp
int x;       // defines a variable named 'x' of type int
double d;    // defines a variable named 'd' of type double
```

3.

```cpp
int x{5};   // direct-list init (preferred) - disallows narrowing
int y{};    // value init - zero for fundamental types
int z = 5;  // copy init - OK but doesn't prevent narrowing
```

### 3 Common Mistakes

- Forgetting a semicolon
- Using `=` (assignment) instead of `==` (equality)
- Using `<<` with `std::cin`

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Statement** - the smallest independent unit of computation; most end with a semicolon
- **Function** - a named collection of statements that execute sequentially; every program needs `main()`
- **Identifier** - the name of a variable, function, type, etc.
- **Syntax** - the grammar rules of C++; violations cause syntax errors
- **Object** - a region of storage (RAM/register) that holds a value
- **Variable** - a named object
- **Data type** - tells the compiler how to interpret a value (e.g., `int`, `double`)
- **Literal** - a fixed value written directly in source code (e.g., `5`, `"Hello"`)
- **Operator** - a symbol denoting an operation (e.g., `+`, `=`, `<<`, `>>`)
- **Expression** - a combination of literals, variables, operators, and function calls that evaluates to a single value
- **Expression statement** - an expression followed by a semicolon
- **Undefined behavior (UB)** - the result of code the C++ standard doesn't define; can cause anything from crashes to silently wrong results

### Section-by-Section Detail

### 1.1 - Statements and the structure of a program

- A **statement** tells the program to perform an action; most end in a semicolon
- Statements are grouped into **functions**; every C++ program must have a `main()` function - execution starts there
- A **declaration statement** introduces a name (like a variable); an **expression statement** evaluates an expression and discards the result
- `main()` is called automatically by the OS, must return an `int`, and `0` signals success
- If you omit `return 0;` from `main()`, the compiler implicitly inserts it
- **Syntax errors** occur when you violate C++ grammar rules (e.g., missing semicolon or brace) - the compiler refuses to compile

```cpp
int main()          // function definition - execution starts here
{
    int x{ 5 };    // declaration statement
    x = x + 1;     // expression statement (with side effect)
    return 0;       // return statement - 0 means success
}
```

→ _See [01_StatementsAndStructure](../solutions/Chapter_01_CppBasics/01_StatementsAndStructure) for program structure basics._

### 1.2 - Comments

- C++ has **single-line comments** (`//`) and **multi-line comments** (`/* */`)
- Comment _what_ at the function/program level, _how_ inside functions, and _why_ at the statement level
- Multi-line comments cannot be nested - the first `*/` closes the comment, causing a compile error
- Code can be temporarily disabled by "commenting it out"
- Good comments explain intent, not what the code literally does (e.g., don't write `// add 1 to x` next to `x = x + 1`)
- Write comments as if the reader knows C++ but doesn't know what the code is supposed to do
- Keep comments up to date - a wrong comment is worse than no comment

→ _See [02_Comments](../solutions/Chapter_01_CppBasics/02_Comments) for comment styles and best practices._

### 1.3 - Introduction to objects and variables

- **Data** is information stored as sequences of bits in memory
- An **object** is a region of storage (RAM or CPU register) that holds a value with associated properties like a type
- A **variable** is a named object, created with a **definition statement** specifying a **data type** (e.g., `int x;`)
- The type must be known at compile time - it determines memory size and how stored bits are interpreted
- Multiple variables can be defined on one line (`int a, b;`), but this is discouraged for readability
- In C++, "object" is broader than in OOP - every variable is an object, but not every object is a variable (e.g., temporaries are unnamed objects)

```cpp
int x;       // defines a variable named 'x' of type int
double d;    // defines a variable named 'd' of type double
```

> **See also:** [Chapter 4 - Fundamental Data Types](<../2) Fundamentals 1/Chapter 4 - Fundamental Data Types.md>) for a deep dive into the built-in types.

→ _See [03_ObjectsAndVariables](../solutions/Chapter_01_CppBasics/03_ObjectsAndVariables) for object and variable definition demos._

### 1.4 - Variable assignment and initialization

- **Assignment** (`=`) gives an already-defined variable a new value via the **copy-assignment operator**
- **Initialization** provides a value at creation - more efficient than defining then assigning separately
- C++ initialization forms: **default** (`int x;` - indeterminate value), **copy** (`int x = 5;`), **direct** (`int x(5);`), **direct-list/brace** (`int x{5};`), and **value** (`int x{};` - zero-initializes)
- **Direct-list-initialization is preferred** - it disallows narrowing conversions (e.g., `int x{4.5};` is a compile error, while `int x = 4.5;` silently truncates to `4`)
- Copy initialization was inherited from C and is common in legacy code
- Value initialization (`int x{};`) is the best way to zero-initialize a variable
- The `[[maybe_unused]]` attribute (C++17) suppresses unused-variable warnings - useful during development

```cpp
int x{5};   // direct-list init (preferred) - disallows narrowing
int y{};    // value init - zero for fundamental types
int z = 5;  // copy init - OK but doesn't prevent narrowing
```

→ _See [04_InitializationForms](../solutions/Chapter_01_CppBasics/04_InitializationForms) for all initialization forms and narrowing conversion demos._

### 1.5 - Introduction to iostream: cout, cin, and endl

- `<iostream>` provides **`std::cout`** (output via `<<` insertion operator) and **`std::cin`** (input via `>>` extraction operator)
- Multiple `<<` or `>>` can be chained: `std::cout << "x = " << x << '\n';`
- Both `std::cout` and `std::cin` are **buffered** - data is collected and flushed in batches for performance
- Prefer `'\n'` over `std::endl` - `std::endl` forces a buffer flush on every call, which is slower
- `std::cin >> x` skips leading whitespace, reads until whitespace or invalid input, and stores the result in `x`
- If extraction fails (e.g., letter entered for `int`), `std::cin` enters a **fail state** - subsequent extractions fail until cleared

```cpp
std::cout << "Enter a number: ";
int x{};
std::cin >> x;
std::cout << "You entered: " << x << '\n';
```

→ _See [05_IOStreamBasics](../solutions/Chapter_01_CppBasics/05_IOStreamBasics) for `std::cout`, `std::cin`, and `'\n'` vs `std::endl`._

### 1.6 - Uninitialized variables and undefined behavior

- An **uninitialized** variable contains whatever bits were in memory - a "garbage" or "indeterminate" value
- Using it causes **undefined behavior (UB)** - the program may crash, give wrong results, appear to work, or vary between runs
- The compiler may assume UB never occurs, leading to unexpected optimizations
- Three categories of non-standard behavior: **implementation-defined** (compiler-specific, documented, e.g., size of `int`), **unspecified** (compiler-specific, _not_ documented, e.g., argument evaluation order), and **undefined** (anything goes)
- Always initialize variables to eliminate this class of bugs
- Enable high warning levels (`-Wall -Wextra` on GCC/Clang, `/W4` on MSVC) to catch some uninitialized-variable uses

```cpp
int x;              // uninitialized - contains garbage
std::cout << x;     // undefined behavior!
int y{};            // value-initialized to 0 - safe
```

> **See also:** [Chapter 9 - Error Detection and Handling](<../3) Fundamentals 2/Chapter 9 - Error Detection and Handling.md>) for systematic approaches to finding and handling errors.

→ _See [06_UninitializedAndUB](../solutions/Chapter_01_CppBasics/06_UninitializedAndUB) for UB demonstrations._

### 1.7 - Keywords and naming identifiers

- C++ reserves 92 **keywords** (as of C++23) - e.g., `int`, `return`, `if`, `while`, `class`, `void` - these cannot be used as identifiers
- Special identifiers like `override` and `final` have contextual meaning and should also be avoided as names
- Naming rules: no keywords, only letters/digits/underscores, must start with a letter or underscore (avoid leading `_` - reserved in many contexts), case-sensitive (`myVar` ≠ `myvar`)
- Best practices: lowercase start for variables/functions, uppercase for user-defined types, consistent `camelCase` or `snake_case`
- Choose descriptive names proportional to scope - short for small scopes, longer for larger ones
- Avoid abbreviations unless universally understood

→ _See [07_KeywordsAndIdentifiers](../solutions/Chapter_01_CppBasics/07_KeywordsAndIdentifiers) for naming rules and keyword examples._

### 1.8 - Whitespace and basic formatting

- **Whitespace** (spaces, tabs, newlines) separates language elements (e.g., `int x`) but is otherwise ignored by the compiler
- Whitespace is _not_ ignored inside quoted text - `"Hello World"` ≠ `"HelloWorld"`
- Statements can span multiple lines; the compiler ignores line breaks outside strings and single-line comments
- Indent with 4 spaces (or one tab) per nesting level; keep lines ≤ 80 characters
- Place opening braces on the same line or their own line - pick one style and be consistent
- Use your IDE's auto-format feature
- When breaking long statements, place operators at the beginning of continuation lines and align with the expression above

→ _See [08_WhitespaceAndFormatting](../solutions/Chapter_01_CppBasics/08_WhitespaceAndFormatting) for formatting style examples._

### 1.9 - Introduction to literals and operators

- **Literals** (aka **literal constants**) are fixed values in source code compiled into the executable - e.g., `5` (integer), `3.14` (floating-point), `'a'` (character), `"Hello"` (C-style string)
- **Operators** act on **operands** to produce a value; the operand count is the operator's **arity**: unary (`-x`), binary (`x + y`), ternary (`?:`), nullary (`throw` in some contexts)
- A **side effect** is any observable consequence beyond producing a return value - e.g., `=` changes a variable, `<<` writes to the console
- Return value and side effect are independent: `x = 5` _returns_ `5` (enabling chaining like `a = b = 5`) and has the side effect of changing `x`
- Arithmetic operators follow standard precedence (PEMDAS); use parentheses to override

```cpp
int x{ 5 };        // 5 is an integer literal
double pi{ 3.14 }; // 3.14 is a floating-point literal
char c{ 'a' };     // 'a' is a character literal

std::cout << x + 2;  // + is a binary operator (2 operands)
std::cout << -x;     // - is a unary operator (1 operand)
```

→ _See [09_LiteralsAndOperators](../solutions/Chapter_01_CppBasics/09_LiteralsAndOperators) for literal types, arity, and precedence demos._

### 1.10 - Introduction to expressions

- An **expression** is a combination of literals, variables, operators, and function calls that evaluates to a single value (the **result**)
- Every expression has both a result and a **type**, deduced from its elements
- A **subexpression** is an expression used as an operand in a larger expression (e.g., `2` and `3` in `2 + 3`)
- A **full expression** is one that is not itself a subexpression
- An **expression statement** is an expression followed by a semicolon - it evaluates the expression, discards the result, and executes side effects
- Wherever C++ expects a value, any value-producing expression can be used - this makes expressions composable
- Not every statement is an expression statement (e.g., declaration statements, `return` statements are not)

```cpp
int x{ 2 + 3 };        // 2 + 3 is an expression (evaluates to 5)
x = 4 * (x + 1);       // 4 * (x + 1) is an expression; x + 1 is a subexpression
std::cout << x << '\n'; // expression statement - evaluates and discards result
```

→ _See [10_Expressions](../solutions/Chapter_01_CppBasics/10_Expressions) for expression evaluation examples._

### 1.11 - Developing your first program

- Demonstrates **incremental development**: define the goal → break into subtasks → implement one at a time, compiling and testing after each
- Example goal: "take a number from the user and double it" → subtasks: get input, compute, output
- Prefer inline expressions (`std::cout << num * 2;`) over unnecessary intermediate variables - cleaner and avoids stale values
- If an expression is complex or reused, store it in a well-named variable
- Once working, clean up: remove dead code, add comments for non-obvious intent, ensure consistent formatting
- Avoid writing the entire program before compiling - bugs are far easier to find when only a few lines were added since the last successful build

```cpp
// Step-by-step: get input → compute → output
std::cout << "Enter a number: ";
int num{};
std::cin >> num;
std::cout << num << " doubled is " << num * 2 << '\n';
```

→ _See [11_IncrementalDevelopment](../solutions/Chapter_01_CppBasics/11_IncrementalDevelopment) for a step-by-step program build._

### Edge Cases and Caveats

- **Forgetting a semicolon** at the end of a statement - the error may point to the _next_ line.

  ❌ **Bad:**

  ```cpp
  int x{5}    // missing semicolon
  int y{10};  // compiler error points HERE
  ```

  ✅ **Good:**

  ```cpp
  int x{5};   // semicolon present
  int y{10};  // compiles fine
  ```

- **Using `=` (assignment) instead of `==` (equality)**

  ❌ **Bad:**

  ```cpp
  if (x = 5)  // assigns 5 to x, always "true" - not a comparison!
  ```

  ✅ **Good:**

  ```cpp
  if (x == 5) // compares x to 5
  ```

- **Using `<<` with `std::cin`** or `>>` with `std::cout`

  ❌ **Bad:**

  ```cpp
  std::cin << x;   // wrong direction
  std::cout >> x;   // wrong direction
  ```

  ✅ **Good:**

  ```cpp
  std::cin >> x;    // extraction: cin → variable
  std::cout << x;   // insertion: value → cout
  ```

- **Leaving variables uninitialized** - leads to garbage values and UB.

  ❌ **Bad:**

  ```cpp
  int x;          // indeterminate value
  std::cout << x; // undefined behavior
  ```

  ✅ **Good:**

  ```cpp
  int x{};        // value-initialized to 0
  std::cout << x; // safe: prints 0
  ```

- **Nesting multi-line comments** (`/* ... /* ... */ ... */`)

  ❌ **Bad:**

  ```cpp
  /* outer /* inner */ still outer */  // compile error!
  ```

  ✅ **Good:**

  ```cpp
  // /* inner */   // use // to comment out blocks with /* */
  // still outer
  ```

- **Defining multiple variables on one line** - initializer only applies to one.

  ❌ **Bad:**

  ```cpp
  int a, b = 5;  // only b is initialized; a is indeterminate!
  ```

  ✅ **Good:**

  ```cpp
  int a{0};
  int b{5};      // each variable on its own line with its own initializer
  ```

- **Using `'/n'` instead of `'\n'`** - forward slash vs backslash.

  ❌ **Bad:**

  ```cpp
  std::cout << '/n';  // multi-char literal, prints a number!
  ```

  ✅ **Good:**

  ```cpp
  std::cout << '\n';  // correct newline character
  ```

- **Assuming output appears on separate lines** without explicit newlines.

  ❌ **Bad:**

  ```cpp
  std::cout << "Hello";
  std::cout << "World";  // prints "HelloWorld" on one line
  ```

  ✅ **Good:**

  ```cpp
  std::cout << "Hello\n";
  std::cout << "World\n"; // prints on separate lines
  ```

- **Naming variables with keywords or starting with digits**

  ❌ **Bad:**

  ```cpp
  int return{5};  // 'return' is a keyword - compile error
  int 2nd{};      // can't start with a digit
  ```

  ✅ **Good:**

  ```cpp
  int result{5};
  int second{};   // descriptive, valid names
  ```

---

### Hands-On Code Projects

| #   | Project                                                                                     | Concept                                                    |
| --- | ------------------------------------------------------------------------------------------- | ---------------------------------------------------------- |
| 01  | [01_StatementsAndStructure](../solutions/Chapter_01_CppBasics/01_StatementsAndStructure)   | Statements, program structure, and `main()`                |
| 02  | [02_Comments](../solutions/Chapter_01_CppBasics/02_Comments)                               | Single-line, multi-line comments, commenting out code      |
| 03  | [03_ObjectsAndVariables](../solutions/Chapter_01_CppBasics/03_ObjectsAndVariables)         | Objects, variables, definitions, and data types            |
| 04  | [04_InitializationForms](../solutions/Chapter_01_CppBasics/04_InitializationForms)         | Copy, direct, list, and value initialization; narrowing    |
| 05  | [05_IOStreamBasics](../solutions/Chapter_01_CppBasics/05_IOStreamBasics)                   | `std::cout`, `std::cin`, `<<`, `>>`, `'\n'` vs `std::endl` |
| 06  | [06_UninitializedAndUB](../solutions/Chapter_01_CppBasics/06_UninitializedAndUB)           | Uninitialized variables and undefined behavior             |
| 07  | [07_KeywordsAndIdentifiers](../solutions/Chapter_01_CppBasics/07_KeywordsAndIdentifiers)   | Reserved keywords, naming rules, best practices            |
| 08  | [08_WhitespaceAndFormatting](../solutions/Chapter_01_CppBasics/08_WhitespaceAndFormatting) | Whitespace rules and formatting best practices             |
| 09  | [09_LiteralsAndOperators](../solutions/Chapter_01_CppBasics/09_LiteralsAndOperators)       | Literals, operator arity, side effects, precedence         |
| 10  | [10_Expressions](../solutions/Chapter_01_CppBasics/10_Expressions)                         | Expressions, subexpressions, expression statements         |
| 11  | [11_IncrementalDevelopment](../solutions/Chapter_01_CppBasics/11_IncrementalDevelopment)   | Building a program step-by-step                            |
| 12  | [12_CommonPitfalls](../solutions/Chapter_01_CppBasics/12_CommonPitfalls)                   | Semicolons, `=` vs `==`, `<<` vs `>>`, `'/n'` vs `'\n'`    |
| 13  | [13_MaybeUnusedAttribute](../solutions/Chapter_01_CppBasics/13_MaybeUnusedAttribute)       | `[[maybe_unused]]` to suppress unused-variable warnings    |

### Quick Reference

### Program skeleton

```cpp
#include <iostream>

int main()
{
    // your code here
    return 0;   // optional - compiler inserts if omitted
}
```

### Variable initialization (prefer brace init)

```cpp
int a;        // default init - indeterminate value (BAD for fundamental types)
int b = 5;    // copy init
int c(5);     // direct init
int d{5};     // direct-list init  ← PREFERRED (disallows narrowing)
int e{};      // value init (zero for fundamental types)
```

### Console I/O

```cpp
std::cout << "Hello" << '\n';        // output with newline
std::cin  >> x;                      // read into x (skips leading whitespace)
std::cout << a << ' ' << b << '\n';  // chain multiple values
```

### Comments

```cpp
// Single-line comment
/* Multi-line
   comment */
// /* Do NOT nest multi-line comments */
```

### Operator arity

| Arity   | Operands | Example        |
| ------- | -------- | -------------- |
| Unary   | 1        | `-x`, `!flag`  |
| Binary  | 2        | `x + y`, `a=b` |
| Ternary | 3        | `c ? x : y`    |

### Naming rules

- Letters, digits, underscores only; must start with a letter (avoid leading `_`)
- Case-sensitive (`myVar` ≠ `myvar`)
- Cannot be a keyword (`int`, `return`, `class`, …)
- Use `camelCase` or `snake_case` consistently; descriptive names proportional to scope

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What are the five forms of variable initialization in C++? Which one is preferred, and why?

<details>
<summary>Show answer</summary>

**Direct answer:** The five forms are: default initialization (`int x;`), copy initialization (`int x = 5;`), direct initialization (`int x(5);`), direct-list initialization (`int x{5};`), and value initialization (`int x{};`). Direct-list initialization is preferred because it disallows narrowing conversions - `int x{4.5};` is a compile error, whereas `int x = 4.5;` silently truncates to `4`.

**Detailed explanation:**

- **Default initialization** (`int x;`) - leaves fundamental types with an indeterminate (garbage) value. Using it is undefined behavior.
- **Copy initialization** (`int x = 5;`) - inherited from C. Works fine but does not prevent narrowing conversions.
- **Direct initialization** (`int x(5);`) - uses parentheses. Also does not prevent narrowing.
- **Direct-list initialization** (`int x{5};`) - the preferred modern form. Rejects narrowing conversions at compile time, catching data-loss bugs early.
- **Value initialization** (`int x{};`) - zero-initializes fundamental types. Best way to ensure a variable starts at zero.

```cpp
int a;        // default init - indeterminate value (BAD)
int b = 5;    // copy init
int c(5);     // direct init
int d{5};     // direct-list init ← PREFERRED
int e{};      // value init (zero)
```

</details>

2. What is **undefined behavior**? Give an example of code that causes it.

<details>
<summary>Show answer</summary>

**Direct answer:** Undefined behavior (UB) occurs when code does something the C++ standard does not define. The program may crash, produce wrong results, appear to work correctly, or behave differently on each run. A common example is using an uninitialized variable: `int x; std::cout << x;` - the value of `x` is indeterminate.

**Detailed explanation:**
The C++ standard imposes no requirements on what happens when UB occurs. The compiler is free to assume UB never happens, which can lead to surprising optimizations (e.g., removing code it considers unreachable based on UB assumptions). There are three categories of non-standard behavior:

- **Implementation-defined behavior** - compiler-specific but documented (e.g., the size of `int`).
- **Unspecified behavior** - compiler-specific and _not_ documented (e.g., evaluation order of function arguments).
- **Undefined behavior** - anything goes (e.g., using an uninitialized variable, signed integer overflow, dereferencing a null pointer).

```cpp
int x;              // uninitialized - contains garbage
std::cout << x;     // undefined behavior!
```

Always initialize your variables to prevent this entire class of bugs.

</details>

3. What is the difference between `'\n'` and `std::endl`? Which should you prefer?

<details>
<summary>Show answer</summary>

**Direct answer:** Both produce a newline, but `std::endl` also flushes the output buffer after every use, which is significantly slower. Prefer `'\n'` for normal output - the buffer will be flushed automatically when needed (e.g., when `std::cin` is called, when the program exits, or when the buffer is full).

**Detailed explanation:**
`std::cout` is buffered - output is collected in memory and written to the console in batches for performance. `'\n'` simply adds a newline character to the buffer. `std::endl` adds a newline _and_ forces the buffer to flush immediately, which involves a system call every time. In a loop producing thousands of lines of output, using `std::endl` can be orders of magnitude slower than `'\n'`. Use `std::endl` only when you specifically need an immediate flush (which is rare in practice).

```cpp
std::cout << "Fast\n";              // preferred - just a newline
std::cout << "Slow" << std::endl;   // newline + flush (usually unnecessary)
```

</details>

4. What is an **expression statement**? How does it differ from a declaration statement?

<details>
<summary>Show answer</summary>

**Direct answer:** An expression statement is an expression followed by a semicolon - it evaluates the expression, executes any side effects, and discards the result. A declaration statement introduces a new name (variable, function, type) into the program. For example, `x = 5;` is an expression statement (assigns 5 to x), while `int x{5};` is a declaration statement (creates variable x).

**Detailed explanation:**
An **expression** is a combination of literals, variables, operators, and function calls that evaluates to a single value with a specific type. When you put a semicolon after it, it becomes an **expression statement** - the expression is evaluated, any side effects (like assignment or output) are executed, and the result is discarded. A **declaration statement** creates a new identifier (like a variable) and optionally initializes it. Not every statement is an expression statement - `return 0;`, `int x{5};`, and `if (...)` are all statements but not expression statements.

```cpp
int x{ 5 };          // declaration statement - creates x
x = x + 1;           // expression statement - assigns, discards result (6)
std::cout << x;       // expression statement - outputs, discards result
```

</details>

5. Why should you define each variable on its own line with its own initializer?

<details>
<summary>Show answer</summary>

**Direct answer:** Defining multiple variables on one line can lead to accidental non-initialization. For example, `int a, b = 5;` only initializes `b` - `a` is left with an indeterminate value, which is easy to miss. Putting each variable on its own line with an explicit initializer makes it clear that every variable is properly initialized.

**Detailed explanation:**
When you write `int a, b = 5;`, it looks like both variables get the value 5, but only `b` is initialized. `a` has an indeterminate value, and using it is undefined behavior. By defining each variable on its own line (`int a{0}; int b{5};`), you make the initialization explicit and visible. This also makes code easier to read, debug, and modify - you can quickly see each variable's type and initial value.

```cpp
// BAD - only b is initialized
int a, b = 5;

// GOOD - each variable clearly initialized
int a{0};
int b{5};
```

</details>

6. What is **narrowing conversion**, and how does list-initialization protect against it?

<details>
<summary>Show answer</summary>

**Direct answer:** A narrowing conversion is an implicit type conversion that may lose data - for example, converting a `double` (4.5) to an `int` (4) silently drops the fractional part. List-initialization (brace initialization) makes narrowing conversions a compile error, catching the data loss at build time instead of at runtime.

**Detailed explanation:**
Copy initialization (`int x = 4.5;`) and direct initialization (`int x(4.5);`) silently truncate 4.5 to 4, which may not be what the programmer intended. Direct-list initialization (`int x{4.5};`) detects this at compile time and refuses to compile, forcing you to either fix the value or use an explicit cast. This is one of the main reasons brace initialization is the preferred form in modern C++.

```cpp
int x = 4.5;   // compiles - silently truncates to 4 (data loss!)
int y(4.5);    // compiles - silently truncates to 4
int z{4.5};    // compile ERROR - narrowing conversion detected
```

</details>

7. Explain the difference between **unspecified behavior**, **implementation-defined behavior**, and **undefined behavior**.

<details>
<summary>Show answer</summary>

**Direct answer:** **Implementation-defined behavior** is compiler-specific but the compiler must document its choice (e.g., the size of `int`). **Unspecified behavior** is compiler-specific but the compiler is _not_ required to document it (e.g., the order function arguments are evaluated). **Undefined behavior** has no requirements at all - anything can happen (e.g., using an uninitialized variable).

**Detailed explanation:**
These three categories represent decreasing levels of guarantee from the C++ standard:

1. **Implementation-defined** - the standard says there must be a specific behavior, and the compiler must document which one it chose. You can rely on it for a given compiler. Example: `sizeof(int)` is 4 on most modern platforms but could differ.
2. **Unspecified** - the standard allows multiple valid behaviors but doesn't require the compiler to document or even be consistent about which one it picks. Example: in `f(a(), b())`, either `a()` or `b()` may be called first.
3. **Undefined** - the standard imposes zero requirements. The compiler may do anything, including optimizing based on the assumption that UB never occurs, which can remove seemingly valid code. Example: `int x; std::cout << x;` (reading an uninitialized variable).

Avoid all three when possible, but undefined behavior is the most dangerous.

</details>

8. Why is **incremental development** (write a little, compile, test, repeat) preferable to writing an entire program before compiling?

<details>
<summary>Show answer</summary>

**Direct answer:** Incremental development catches bugs early, when you've only added a few lines since the last successful build, making them much easier to locate and fix. Writing an entire program before compiling can produce dozens of errors at once, making it hard to tell which error is real and which is a cascade from an earlier mistake.

**Detailed explanation:**
The incremental approach works as follows: (1) define the goal, (2) break it into subtasks, (3) implement one subtask at a time, compiling and testing after each step. If something breaks, you know the bug is in the few lines you just added. This keeps you productive and motivated by showing steady progress. In contrast, writing a large program all at once before compiling often leads to a wall of errors that are hard to untangle, especially since a single mistake early in the code can generate many cascading error messages.

</details>

9. What is a **literal** in C++? Name four types of literals and give an example of each.

<details>
<summary>Show answer</summary>

**Direct answer:** A literal (also called a literal constant) is a fixed value written directly in source code. Four types: integer literal (`5`), floating-point literal (`3.14`), character literal (`'a'`), and C-style string literal (`"Hello"`).

**Detailed explanation:**
Literals are compiled directly into the executable. They are distinct from variables because their values are fixed at compile time and cannot be modified. Each literal has a type determined by its form:

- `5` → `int`
- `3.14` → `double`
- `'a'` → `char`
- `"Hello"` → `const char[6]` (a C-style string literal, including the null terminator)

```cpp
int x{ 5 };        // 5 is an integer literal
double pi{ 3.14 }; // 3.14 is a floating-point literal
char c{ 'a' };     // 'a' is a character literal
std::cout << "Hi"; // "Hi" is a C-style string literal
```

</details>

10. What is the `[[maybe_unused]]` attribute, and when should you use it?

<details>
<summary>Show answer</summary>

**Direct answer:** `[[maybe_unused]]` is a C++17 attribute that tells the compiler not to warn about an unused variable or parameter. You should use it during development when you've declared a variable you plan to use later, to suppress the warning without disabling your high warning level.

**Detailed explanation:**
With high warning levels enabled (which you should always have), the compiler warns about declared variables that are never used. During early development, you sometimes define a variable before writing the code that uses it. Rather than lowering your warning level or commenting out the variable, you can annotate it with `[[maybe_unused]]`:

```cpp
[[maybe_unused]] int debugCounter{ 0 };  // no warning even if unused
```

Remove the attribute once the variable is actually used. This keeps your warning discipline intact while allowing work-in-progress code.

</details>
