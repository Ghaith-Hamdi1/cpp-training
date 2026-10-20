# Chapter 5 Recap - Constants and Strings

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Make variables `const` or `constexpr` whenever possible - it prevents bugs, aids optimization, and reduces complexity.
- Use `constexpr` for any constant whose value is known at compile-time; use `const` for runtime constants.
- Prefer `const`/`constexpr` variables over `#define` macros for named constants.
- Replace magic numbers with named `constexpr` constants.
- Use the `f` suffix when initializing `float` variables with literals (e.g. `4.1f`) to avoid narrowing-conversion warnings.
- Prefer `std::string_view` over `std::string` for read-only function parameters.
- It is okay to return a local `std::string` by value (move semantics avoids the copy).
- Use `constexpr std::string_view` for string symbolic constants (`constexpr std::string` is not well supported).

### 3 Tiny Examples

1.

```cpp
// Prefer const/constexpr over #define
#define MAX 100       // Bad: no scope, no type
constexpr int max{100}; // Good: scoped, typed, debuggable
```

2.

```cpp
int i{ 5 };       // int literal
double d{ 3.14 }; // double literal
float f{ 4.1f };  // float literal (f suffix)
char c{ 'a' };    // char literal
auto s{ "hello" }; // C-style string literal (const char[])
```

3.

```cpp
int x{ 0xF };           // hexadecimal literal (15)
int y{ 0b1010 };        // binary literal (10, C++14)
int z{ 012 };           // octal literal (10)
int big{ 1'000'000 };   // digit separator for readability (C++14)
```

### 3 Common Mistakes

- Forgetting to initialize a `const` variable
- Using `#define` for constants
- Initializing a `float` with a `double` literal

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Constant variable** - a variable declared with `const` or `constexpr` whose value cannot change after initialization.
- **Literal** - a fixed value written directly in code (e.g. `5`, `3.14`, `"hello"`). All literals have a type.
- **Magic number** - a literal with unclear meaning or that may need changing; should be replaced with a named constant.
- **Constant expression** - an expression whose every part can be evaluated at compile-time.
- **`constexpr` variable** - must be initialized with a constant expression; guaranteed to be a compile-time constant.
- **Compile-time evaluation** - the compiler computing results during compilation instead of at runtime (constant folding, constant propagation, dead code elimination).
- **As-if rule** - the compiler may transform a program however it likes, as long as observable behavior is unchanged.
- **`std::string`** - a standard library class that manages a mutable, dynamically-allocated string. Expensive to copy.
- **`std::string_view`** - a lightweight, read-only, non-owning view into an existing string. Cheap to copy.
- **Dangling view** - a `std::string_view` whose underlying string has been destroyed or invalidated.

### Section-by-Section Detail

### 5.1 - Constant variables (named constants)

- Declare a variable with **`const`** before the type to make it immutable after initialization; it must be initialized at declaration
- Prefer **`const` variables** over **`#define` macros** - macros ignore scoping rules, are invisible to the debugger, and behave inconsistently
- **Runtime constants** are `const` variables whose initializers are not constant expressions - evaluated at runtime but still immutable
- Don't use `const` on **by-value parameters** or **by-value return types** (it adds no meaningful protection)
- Use `const` for any variable that should not change - it communicates intent to both the compiler and other programmers

```cpp
// Prefer const/constexpr over #define
#define MAX 100       // Bad: no scope, no type
constexpr int max{100}; // Good: scoped, typed, debuggable
```

→ _See [01_ConstVariables](../solutions/Chapter_05_Constants_And_Strings/01_ConstVariables/)_

### 5.2 - Literals

- Every **literal** has a default type: `5` → `int`, `3.4` → `double`, `'a'` → `char`; **suffixes** like `f`, `L`, `u` change a literal's type
- **C-style string literals** are null-terminated `const char` arrays with static lifetime (they exist for the entire program)
- Avoid **magic numbers** - replace unexplained literals with named constants for clarity and maintainability
- **Literal suffixes** are case-insensitive (`f` and `F` are equivalent), but avoid lowercase `l` because it resembles the digit `1` - prefer `L`
- **Adjacent string literals** (e.g., `"Hello " "world"`) are automatically concatenated at compile-time

```cpp
int i{ 5 };       // int literal
double d{ 3.14 }; // double literal
float f{ 4.1f };  // float literal (f suffix)
char c{ 'a' };    // char literal
auto s{ "hello" }; // C-style string literal (const char[])
```

→ _See [02_Literals](../solutions/Chapter_05_Constants_And_Strings/02_Literals/)_

### 5.3 - Numeral systems (decimal, binary, hexadecimal, and octal)

- C++ supports four numeral systems: **decimal** (no prefix), **octal** (`0` prefix), **hexadecimal** (`0x` prefix), and **binary** (`0b` prefix, C++14)
- **Hexadecimal** is commonly used to represent memory addresses and raw binary data compactly
- The **digit separator** `'` (C++14) improves readability of long literals (e.g., `1'000'000`)
- By default, `std::cout` outputs values in **decimal**; use `std::hex`, `std::oct`, or `std::dec` manipulators to change the output base
- These output-base manipulators are **sticky** - they persist until explicitly changed

```cpp
int x{ 0xF };           // hexadecimal literal (15)
int y{ 0b1010 };        // binary literal (10, C++14)
int z{ 012 };           // octal literal (10)
int big{ 1'000'000 };   // digit separator for readability (C++14)
```

→ _See [03_NumeralSystems](../solutions/Chapter_05_Constants_And_Strings/03_NumeralSystems/)_

### 5.4 - The as-if rule and compile-time optimization

- The **as-if rule** allows the compiler to modify or reorganize code in any way, as long as the program's **observable behavior** remains identical
- **Constant folding** evaluates literal expressions at compile time (e.g., `3 + 4` becomes `7`)
- **Constant propagation** replaces known-constant variables with their literal values throughout the code
- **Dead code elimination** removes code that can never execute or whose result is never used
- Making variables `const` or `constexpr` helps the compiler optimize more aggressively
- These optimizations are automatic (typically in **Release builds**); **Debug builds** may skip them

**Key optimization techniques:**

| Optimization              | What It Does                                                      | Example                                         |
| ------------------------- | ----------------------------------------------------------------- | ----------------------------------------------- |
| **Constant folding**      | Evaluates literal expressions at compile time                     | `3 + 4` becomes `7` in the binary               |
| **Constant propagation**  | Replaces known-constant variables with their literal values       | `const int x{5}; return x;` becomes `return 5;` |
| **Dead code elimination** | Removes code that can never execute or whose result is never used | Unreachable code after `return` is removed      |

Making variables `const` or `constexpr` helps the compiler optimize more aggressively because it can prove the value never changes. These optimizations are performed automatically (typically in Release builds) and require no manual effort. Debug builds may skip optimizations to preserve source-level debugging fidelity.

`cpp
// Before optimization (what you write):
const int x{ 3 + 4 }; // constant folding: 3+4 computed at compile time
const int y{ x \* 2 }; // constant propagation: x replaced by 7, then folded to 14
if (false) { doWork(); } // dead code elimination: entire if removed

// After optimization (what the compiler may generate):
// Equivalent to: const int y{ 14 };
`

→ _See [04_AsIfRuleAndOptimization](../solutions/Chapter_05_Constants_And_Strings/04_AsIfRuleAndOptimization/)_

### 5.5 - Constant expressions

- A **constant expression** is one that can be evaluated entirely at compile-time using only literals, `constexpr` variables, and certain operations
- **`const` integral** variables with constant expression initializers qualify as constant expressions, but **`const` non-integral** types (e.g., `const double`) do not
- The compiler is only _required_ to evaluate constant expressions at compile-time in **contexts that demand it** (e.g., `constexpr` initializers, array sizes, template arguments)
- A key distinction exists between expressions that _can_ be evaluated at compile-time versus those that _must_ be

```cpp
const int x{ 5 };           // constant expression (const + integral + literal init)
constexpr int y{ x + 1 };   // OK: x is a constant expression

int z{};
std::cin >> z;
const int w{ z };            // NOT a constant expression (runtime value)
// constexpr int v{ z };     // error: z is not a constant expression
```

→ _See [05_ConstantExpressions](../solutions/Chapter_05_Constants_And_Strings/05_ConstantExpressions/)_

### 5.6 - Constexpr variables

- **`constexpr`** guarantees a variable is a compile-time constant; the compiler will error if the initializer is not a **constant expression**
- Unlike `const`, `constexpr` works with **non-integral types** (e.g., `constexpr double`) and is implicitly `const`
- **Function parameters** cannot be declared `constexpr`
- Use `constexpr` for constants with compile-time initializers; use `const` for **runtime constants**
- Best practice: prefer `constexpr` over `const` even for integral types - it makes the **compile-time guarantee explicit**

```cpp
const double gravity{ 9.8 };     // runtime const (not constexpr-eligible)
constexpr double pi{ 3.14159 };  // compile-time constant ✓
```

> **See also:** [Chapter 7 - Sharing global constants](Chapter%207%20-%20Scope,%20Duration,%20and%20Linkage.md) for the `inline constexpr` header pattern.

→ _See [06_ConstexprVariables](../solutions/Chapter_05_Constants_And_Strings/06_ConstexprVariables/)_

**const vs constexpr at a glance:**

| Aspect                              | `const`                                        | `constexpr`                                        |
| ----------------------------------- | ---------------------------------------------- | -------------------------------------------------- |
| Initialized at                      | Runtime or compile time                        | Must be compile time                               |
| Compile-time guarantee              | No (only immutability)                         | Yes                                                |
| Works with non-literal types        | Yes (e.g., `const std::string`)                | No (only literal types)                            |
| Can be used in constant expressions | Only if initialized with a constant expression | Always                                             |
| Preferred for                       | Runtime-determined constants, function params  | Compile-time constants, array sizes, template args |

### 5.7 - Introduction to std::string

- **`std::string`** (from `<string>`) manages dynamically-sized, mutable strings safely
- Use `std::getline(std::cin >> std::ws, str)` to read a **full line** of input including spaces
- **`length()`** returns the string's size (excluding the null terminator) as an unsigned value
- Initializing and copying `std::string` is **expensive** - avoid passing it by value
- The `+` operator concatenates `std::string` objects and C-style literals, but **at least one operand** must be a `std::string`
- Using **`append()`** or `+=` is more efficient for repeated concatenation

```cpp
std::string name{};
std::cout << "Enter your full name: ";
std::getline(std::cin >> std::ws, name); // reads full line, skips leading whitespace
```

> **See also:** [Chapter 12 - References and Pointers](Chapter%2012%20-%20Compound%20Types%20References%20and%20Pointers.md) for passing strings by reference.

→ _See [08_StdStringBasics](../solutions/Chapter_05_Constants_And_Strings/08_StdStringBasics/) · [09_StringInput](../solutions/Chapter_05_Constants_And_Strings/09_StringInput/)_

### 5.8 - Introduction to std::string_view

- **`std::string_view`** (C++17, from `<string_view>`) provides **read-only** access to an existing string without copying
- It accepts **C-style strings**, `std::string`, or other `std::string_view` objects, and is the preferred type for **read-only function parameters**
- `std::string_view` will **not** implicitly convert to `std::string`; use explicit construction `std::string{ sv }` when needed
- **`constexpr std::string_view`** is fully supported, making it ideal for string symbolic constants
- Unlike `std::string`, it does **not guarantee null-termination** - do not pass it to functions expecting C-style strings

```cpp
void printSV(std::string_view sv)    // cheap to copy - no allocation
{
    std::cout << sv << '\n';
}

printSV("C-string literal");          // works
std::string s{ "std::string" };
printSV(s);                           // works
```

→ _See [10_StdStringView](../solutions/Chapter_05_Constants_And_Strings/10_StdStringView/)_

### 5.9 - std::string_view (part 2)

- **`std::string`** is an **owner** (makes its own copy); **`std::string_view`** is a **viewer** (depends on an external string)
- If the viewed string is destroyed or modified, the view becomes **dangling/invalidated** and using it is **undefined behavior**
- Safe to return a `std::string_view` of a **C-style string literal** or a `std::string_view` parameter, but **never** of a local `std::string`
- **`remove_prefix()`** and **`remove_suffix()`** shrink the view by adjusting internal pointers - they do not modify the underlying data
- When in doubt about the **lifetime** of the viewed string, prefer `std::string` to avoid dangling references

```cpp
std::string_view getDangling() {
    std::string s{ "hello" };
    return s; // dangling! s destroyed at end of function
}
```

→ _See [11_StringViewDangling](../solutions/Chapter_05_Constants_And_Strings/11_StringViewDangling/) · [12_StringViewOperations](../solutions/Chapter_05_Constants_And_Strings/12_StringViewOperations/)_

### Edge Cases and Caveats

- **Forgetting to initialize a `const` variable** - `const` variables _must_ be initialized at declaration.

  ❌ **Bad:**

  ```cpp
  const int x; // error: uninitialized const
  ```

  ✅ **Good:**

  ```cpp
  const int x{ 5 };
  ```

- **Using `#define` for constants** - macros bypass scoping and are invisible to debuggers.

  ❌ **Bad:** `#define MAX_SIZE 100`
  ✅ **Good:** `constexpr int maxSize{ 100 };`

- **Initializing a `float` with a `double` literal** - causes narrowing warning.

  ❌ **Bad:** `float f{ 4.1 };` - `4.1` is a `double`.
  ✅ **Good:** `float f{ 4.1f };`

- **Assuming `const double` is usable in constant expressions** - only `const` _integral_ types qualify.

  ❌ **Bad:** `const double d{ 3.14 }; constexpr double e{ d };` - error!
  ✅ **Good:** `constexpr double d{ 3.14 }; constexpr double e{ d };`

- **Passing `std::string` by value** - this makes an expensive copy.

  ❌ **Bad:** `void print(std::string s);`
  ✅ **Good:** `void print(std::string_view s);`

- **Using `std::cin >>` for multi-word input** - `operator>>` stops at whitespace.

  ❌ **Bad:** `std::cin >> name;` - only reads first word.
  ✅ **Good:** `std::getline(std::cin >> std::ws, name);`

- **Forgetting `std::ws` with `std::getline()`** - leftover `'\n'` causes an empty read.

  ❌ **Bad:** `std::getline(std::cin, name);` after a prior `>>`.
  ✅ **Good:** `std::getline(std::cin >> std::ws, name);`

- **Dangling `std::string_view`** - viewing a destroyed `std::string` is UB.

  ❌ **Bad:**

  ```cpp
  std::string_view sv{ std::string{"temp"} }; // dangling!
  ```

  ✅ **Good:**

  ```cpp
  std::string_view sv{ "temp" }; // C-style literal lives forever
  ```

- **Initializing `std::string_view` with a `std::string` literal (`"text"s`)** - temporary destroyed immediately.

  ❌ **Bad:** `std::string_view sv{ "text"s };`
  ✅ **Good:** `std::string_view sv{ "text" };`

- **Using an octal literal by accident** - a leading `0` makes a number octal.

  ❌ **Bad:** `int x{ 012 };` - this is decimal 10, not 12!
  ✅ **Good:** `int x{ 12 };`

---

### Hands-On Code Projects

| #   | Project                                                                                                 | Concept                                             |
| --- | ------------------------------------------------------------------------------------------------------- | --------------------------------------------------- |
| 01  | [01_ConstVariables](../solutions/Chapter_05_Constants_And_Strings/01_ConstVariables/)                   | `const` variables vs `#define` macros               |
| 02  | [02_Literals](../solutions/Chapter_05_Constants_And_Strings/02_Literals/)                               | Literal types, suffixes, C-style string literals    |
| 03  | [03_NumeralSystems](../solutions/Chapter_05_Constants_And_Strings/03_NumeralSystems/)                   | Decimal, octal, hex, binary literals                |
| 04  | [04_AsIfRuleAndOptimization](../solutions/Chapter_05_Constants_And_Strings/04_AsIfRuleAndOptimization/) | As-if rule, constant folding, dead code elimination |
| 05  | [05_ConstantExpressions](../solutions/Chapter_05_Constants_And_Strings/05_ConstantExpressions/)         | Compile-time vs runtime constant expressions        |
| 06  | [06_ConstexprVariables](../solutions/Chapter_05_Constants_And_Strings/06_ConstexprVariables/)           | `constexpr` guarantees, non-integral types          |
| 07  | [07_MagicNumbers](../solutions/Chapter_05_Constants_And_Strings/07_MagicNumbers/)                       | Replacing magic numbers with named constants        |
| 08  | [08_StdStringBasics](../solutions/Chapter_05_Constants_And_Strings/08_StdStringBasics/)                 | `std::string` creation, `length()`, concatenation   |
| 09  | [09_StringInput](../solutions/Chapter_05_Constants_And_Strings/09_StringInput/)                         | `std::getline()`, `std::ws`, leftover newline       |
| 10  | [10_StdStringView](../solutions/Chapter_05_Constants_And_Strings/10_StdStringView/)                     | `std::string_view` as read-only parameter           |
| 11  | [11_StringViewDangling](../solutions/Chapter_05_Constants_And_Strings/11_StringViewDangling/)           | Dangling views and undefined behavior               |
| 12  | [12_StringViewOperations](../solutions/Chapter_05_Constants_And_Strings/12_StringViewOperations/)       | `remove_prefix/suffix`, `constexpr` string_view     |
| 13  | [13_CommonPitfalls](../solutions/Chapter_05_Constants_And_Strings/13_CommonPitfalls/)                   | Float narrowing, accidental octal, `const` traps    |

### Quick Reference

| Topic                     | Details                                                                                                                                                                 |
| ------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `const` vs `constexpr`    | `const` prevents modification but may be runtime; `constexpr` guarantees compile-time evaluation. Prefer `constexpr` when the initializer is a constant expression.     |
| Literal suffixes          | `f`/`F` → `float`, `L` → `long` / `long double`, `u`/`U` → `unsigned`, `ll`/`LL` → `long long`. Suffixes are case-insensitive (avoid lowercase `l`).                    |
| Numeral systems           | Decimal (no prefix), Octal (`0`), Hexadecimal (`0x`/`0X`), Binary (`0b`/`0B`, C++14). Use `'` digit separator for readability.                                          |
| `std::string` basics      | Include `<string>`. Dynamically allocated, mutable, expensive to copy. Use `length()` for size. Concatenate with `+` (one operand must be `std::string`).               |
| `std::string_view` basics | Include `<string_view>` (C++17). Lightweight, read-only, non-owning view. Cheap to copy. Not null-terminated. Preferred for read-only parameters.                       |
| Magic numbers             | Unnamed literals with unclear meaning. Replace with `constexpr` named constants for readability and maintainability.                                                    |
| The as-if rule            | Compiler may reorganize/eliminate code as long as observable behavior is preserved. Enables constant folding, constant propagation, and dead code elimination.          |
| Constant expressions      | Expressions evaluable entirely at compile-time. `const` integral types with constant initializers qualify; `const` non-integral types do not - use `constexpr` instead. |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is the difference between `const` and `constexpr`? When should you use each?

<details>
<summary>Show answer</summary>

**Direct answer:** `const` means a variable cannot be modified after initialization, but its value may be determined at runtime. `constexpr` guarantees the variable is a compile-time constant - the compiler will error if the initializer is not a constant expression. Use `constexpr` when the value is known at compile time; use `const` for runtime constants whose values come from user input, function calls, etc.

**Detailed explanation:**
`constexpr` variables are implicitly `const`. The key advantage of `constexpr` is that the compiler is guaranteed to evaluate it at compile time, enabling optimizations and use in contexts that require constant expressions (like array sizes and template arguments). `const` variables initialized with constant expressions _may_ be evaluated at compile time but there's no guarantee. Best practice: any variable with a constant expression initializer should be `constexpr`, not just `const`. Function parameters cannot be `constexpr`.

```cpp
const int runtime{ getValue() };      // OK - runtime constant
constexpr int compileTime{ 5 + 3 };   // OK - compile-time constant
constexpr int bad{ getValue() };      // ERROR - not a constant expression
```

</details>

2. Why should you prefer named constants over magic numbers?

<details>
<summary>Show answer</summary>

**Direct answer:** Magic numbers are unexplained literal values in code (e.g., `3.14159`, `60`, `24`). Named constants give them descriptive names, making code self-documenting, easier to maintain (change value in one place), and less error-prone (the compiler checks the name for typos).

**Detailed explanation:**
A magic number like `60` could mean seconds per minute, items per page, or anything else - the intent is unclear. A named constant like `constexpr int secondsPerMinute{ 60 };` is immediately understandable. If the value ever needs to change, you update it in one place rather than hunting through every occurrence. Prefer `constexpr` variables over `#define` macros for named constants, because macros ignore scoping rules, are invisible to the debugger, and have no type safety.

</details>

3. What qualifies as a **constant expression**, and why does `const double` not qualify?

<details>
<summary>Show answer</summary>

**Direct answer:** A constant expression is one the compiler can evaluate entirely at compile time, using only literals, `constexpr` variables, and certain operations. `const double` does not qualify because only `const` _integral_ types (e.g., `const int`) with constant expression initializers are treated as constant expressions by the standard. `const` non-integral types (like `double`) are not, even if initialized with a literal.

**Detailed explanation:**
This is a historical quirk of C++. Before `constexpr` existed (pre-C++11), `const int` was the only way to create compile-time constants, so the standard gave `const` integral types special treatment. Non-integral types were not covered. The solution in modern C++ is simple: use `constexpr double` instead of `const double` when you need a compile-time constant. `constexpr` works with all types and provides explicit compile-time guarantees.

```cpp
const int ci{ 5 };         // constant expression (integral const with literal init)
const double cd{ 3.14 };   // NOT a constant expression (non-integral)
constexpr double ce{ 3.14 }; // IS a constant expression (constexpr)
```

</details>

4. What is the **as-if rule**, and name two optimizations the compiler can perform under it.

<details>
<summary>Show answer</summary>

**Direct answer:** The as-if rule states that the compiler may reorganize, optimize, or eliminate code as long as the program's observable behavior is preserved. Two common optimizations: **constant folding** (evaluating `3 + 4` at compile time instead of at runtime) and **dead code elimination** (removing code that can never be reached or whose result is never used).

**Detailed explanation:**
Another optimization under the as-if rule is **constant propagation** - replacing known-constant variables with their literal values throughout the code. Making variables `const`/`constexpr` helps the compiler optimize more aggressively because it knows their values won't change. These optimizations happen automatically (typically in release builds) and require no manual effort.

</details>

5. Why is `std::string_view` preferred over `const std::string&` for read-only parameters?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::string_view` can accept C-style strings, `std::string`, and other `std::string_view` objects without any copying or conversion overhead. A `const std::string&` parameter requires constructing a temporary `std::string` when passed a C-style string literal, which involves a heap allocation. `std::string_view` avoids this entirely because it only stores a pointer and a length.

**Detailed explanation:**
`std::string_view` (C++17, from `<string_view>`) provides read-only access to a string it doesn't own. It is lightweight (typically two pointers/pointer+length), copyable, and does not allocate memory. It will not implicitly convert to `std::string`, so you must explicitly construct one if needed: `std::string{ sv }`. `constexpr std::string_view` is fully supported, making it ideal for compile-time string constants. Note that `std::string_view` does not guarantee null-termination, so don't pass it to C APIs expecting null-terminated strings.

</details>

6. What makes a `std::string_view` **dangling**, and how do you avoid it?

<details>
<summary>Show answer</summary>

**Direct answer:** A `std::string_view` becomes dangling when the underlying string it refers to is destroyed or reallocated. This happens most commonly when returning a `std::string_view` that refers to a local `std::string` - the `std::string` is destroyed when the function returns, leaving the view pointing to freed memory. Using a dangling view is undefined behavior.

**Detailed explanation:**
`std::string` is an **owner** (manages its own memory), while `std::string_view` is a **viewer** (depends on external memory). It is safe to return a `std::string_view` of a C-style string literal (because literals have static lifetime) or of a `std::string_view` parameter (because the caller's string outlives the call). It is _not_ safe to return a view of a local `std::string`. `remove_prefix()` and `remove_suffix()` shrink the view by adjusting its internal pointers - they do not modify the underlying string. When in doubt about lifetime, prefer `std::string`.

</details>

7. How do you correctly read a full line of input after a prior `>>` extraction?

<details>
<summary>Show answer</summary>

**Direct answer:** Use `std::getline(std::cin >> std::ws, str)`. The `>> std::ws` manipulator is critical - it discards any leftover whitespace (including the newline character) left in the buffer by the prior `>>` extraction. Without it, `std::getline` would read an empty line.

**Detailed explanation:**
When `std::cin >> x` reads a value, it stops at whitespace but leaves the newline character `'\n'` in the input buffer. If you then call `std::getline(std::cin, str)` without clearing the buffer first, `getline` sees the leftover newline and returns an empty string immediately. The `std::ws` input manipulator extracts and discards all leading whitespace, ensuring `getline` waits for actual user input.

```cpp
int age{};
std::cin >> age;                            // leaves '\n' in buffer
std::string name{};
std::getline(std::cin >> std::ws, name);    // std::ws eats the leftover '\n'
```

</details>

8. What does the `0x` prefix signify, and what prefix creates a binary literal?

<details>
<summary>Show answer</summary>

**Direct answer:** The `0x` prefix denotes a hexadecimal (base-16) literal. The `0b` prefix (C++14) denotes a binary (base-2) literal. There is also the `0` prefix for octal (base-8), though it is rarely used and easy to trigger accidentally.

**Detailed explanation:**
C++ supports four numeral systems for integer literals: decimal (no prefix, the default), octal (`0` prefix), hexadecimal (`0x` prefix), and binary (`0b` prefix). Hexadecimal is commonly used for memory addresses and color values. The digit separator `'` (C++14) improves readability of long literals (e.g., `0b1010'0110'1110'1000`). By default, `std::cout` outputs in decimal; use `std::hex`, `std::oct`, or `std::dec` manipulators to change the output base (these are sticky until changed).

```cpp
int dec{ 42 };          // decimal
int oct{ 052 };         // octal (= 42)
int hex{ 0x2A };        // hexadecimal (= 42)
int bin{ 0b0010'1010 }; // binary with digit separator (= 42)
```

</details>

9. Why should you avoid `#define` macros for named constants?

<details>
<summary>Show answer</summary>

**Direct answer:** `#define` macros are processed by the preprocessor (pure text substitution) and have no understanding of C++ scope, types, or syntax. They ignore scoping rules, are invisible to the debugger (you can't inspect their values), and can cause unexpected behavior due to text substitution. Use `constexpr` variables instead, which are properly scoped, type-safe, and debugger-friendly.

**Detailed explanation:**
A `#define MAX 100` replaces every occurrence of `MAX` with `100` before the compiler sees the code. This means `MAX` doesn't exist as a named entity in the compiled program - you can't hover over it in a debugger, it doesn't respect namespace boundaries, and it can clash with identifiers in other scopes. `constexpr int max{ 100 };` is a real variable with a type, scope, and visibility in the debugger.

</details>

10. What is the difference between `std::string` and `std::string_view` in terms of ownership?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::string` is an **owner** - it allocates and manages its own copy of the string data. `std::string_view` is a **viewer** - it holds a pointer to string data owned by someone else. Copying a `std::string` duplicates the data (potentially expensive); copying a `std::string_view` just copies a pointer and a length (cheap).

**Detailed explanation:**
This ownership distinction is critical for understanding lifetimes. A `std::string` always contains valid data as long as the object exists. A `std::string_view` is only valid as long as the string it views remains alive and unmodified. Modifying or destroying the underlying string invalidates the view, making it dangling. Use `std::string` when you need ownership; use `std::string_view` for read-only access to strings you don't need to own.

</details>
