# Chapter 4 Recap - Fundamental Data Types

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Prefer `int` when the exact size doesn't matter; use fixed-width types (`std::int32_t`, etc.) when a guaranteed range is needed.
- Favor `double` over `float` - floats lack precision and lead to rounding errors more quickly.
- **Favor signed over unsigned** for quantities and math. Avoid mixing signed and unsigned in expressions.
- Never compare floating-point numbers directly for equality - rounding errors make this unreliable.
- **Integer division truncates** (drops the fractional part); it does not round.
- **Signed integer overflow is undefined behavior**; unsigned overflow wraps around via modulo.
- Use `static_cast` for explicit conversions instead of relying on implicit conversions that may lose data.
- Brace initialization (`{}`) prevents narrowing conversions and should be preferred.

### 3 Tiny Examples

1.

```cpp
bool b{ true };       // boolean
int i{ 42 };          // integer
double d{ 3.14 };     // floating point
char c{ 'A' };        // character
```

2.

```cpp
void printHello()     // void return = no value returned
{
    std::cout << "Hello\n";
    // no return statement needed
}

// void v;            // error: cannot declare a void variable
```

3.

```cpp
std::cout << sizeof(int) << '\n';   // e.g. 4 (bytes)
std::cout << sizeof(double) << '\n'; // e.g. 8
```

### 3 Common Mistakes

- Signed integer overflow
- Mixing signed and unsigned
- Assuming `int` is always 32 bits

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Bit and byte** - A bit is the smallest unit of memory (0 or 1). A byte is 8 bits and is the smallest addressable unit of memory.
- **Data type** - Tells the compiler how to interpret a sequence of bits in memory.
- **Fundamental data types** - The built-in primitive types - integers, floating point, bool, char, void, and `std::nullptr_t`.
- **Signed vs. unsigned integers** - Signed integers can hold negative and positive values; unsigned integers hold only non-negative values.
- **Fixed-width integers** (`std::int32_t`, etc.) - Integers with guaranteed sizes, defined in `<cstdint>`.
- **`std::size_t`** - An unsigned type used to represent object sizes; returned by `sizeof`.
- **Scientific notation / significant digits** - A way to express numbers as _significand × 10^exponent_; the number of significant digits determines precision.
- **Floating-point precision and rounding errors** - Floats/doubles can only store a limited number of significant digits; values like `0.1` cannot be represented exactly in binary.
- **Boolean type (`bool`)** - Stores `true` (1) or `false` (0).
- **`char` and ASCII** - `char` stores a single character as an integer mapped via the ASCII table.
- **Type conversion** - Converting a value from one type to another - either implicitly (by the compiler) or explicitly (via `static_cast`).
- **`sizeof` operator** - Returns the size of a type or variable in bytes.

---

### Section-by-Section Detail

### 4.1 - Introduction to fundamental data types

- **Memory** is organized into **bytes** (8 bits each); every byte has a unique address
- A **data type** tells the compiler how to interpret stored bits in memory
- C++ provides **fundamental types** (integers, floats, bools, chars, void) and **compound types**
- The `_t` suffix is a convention indicating a type name (e.g., `size_t`, `int32_t`)
- The C++ standard defines **minimum sizes** for each fundamental type, but the actual size is **implementation-defined** and may be larger
- Choosing the right data type affects both **correctness** and **performance**

```cpp
bool b{ true };       // boolean
int i{ 42 };          // integer
double d{ 3.14 };     // floating point
char c{ 'A' };        // character
```

→ _See [01_BitsAndBytes](../solutions/Chapter_04_Fundamental_Data_Types/01_BitsAndBytes/) for bit/byte storage demos._

### 4.2 - Void

- `void` means "no type" - it is an **incomplete type** that cannot be instantiated
- Its primary use is to indicate a function **returns no value**
- Using `void` in a parameter list (e.g., `int f(void)`) is **deprecated** in C++ - use empty parentheses instead
- **Void pointers** (`void*`) can point to objects of any type but must be cast before dereferencing

```cpp
void printHello()     // void return = no value returned
{
    std::cout << "Hello\n";
    // no return statement needed
}

// void v;            // error: cannot declare a void variable
```

→ _See [02_Void](../solutions/Chapter_04_Fundamental_Data_Types/02_Void/) for void type usage._

### 4.3 - Object sizes and the sizeof operator

- Objects may use **1, 2, 4, 8, or more bytes**; an object with _n_ bits can hold **2^n unique values**
- The C++ standard only guarantees **minimum sizes** for types (e.g., `int` is at least 16 bits)
- Use `sizeof` to determine the **actual size** of a type or variable on your machine
- `sizeof` is a **compile-time operator** - it does not evaluate its operand
- It can be applied to both **types** and **variables**, and always returns a value of type `std::size_t`

```cpp
std::cout << sizeof(int) << '\n';   // e.g. 4 (bytes)
std::cout << sizeof(double) << '\n'; // e.g. 8
```

→ _See [03_SizeofOperator](../solutions/Chapter_04_Fundamental_Data_Types/03_SizeofOperator/) for `sizeof` on all fundamental types._

### 4.4 - Signed integers

- C++ has four **signed integer types**: `short` (≥16 bits), `int` (≥16 bits), `long` (≥32 bits), and `long long` (≥64 bits)
- **Signed integer overflow** is **undefined behavior** - not a predictable wrap
- **Integer division truncates** the fractional part (drops it, does not round)
- Prefer `int` for general-purpose integer arithmetic unless a specific size is needed
- Signed integers use **two's complement** on virtually all modern systems, guaranteed since **C++20**

```cpp
short s{ 32767 };                          // at least 16 bits
int i{ 2'147'483'647 };                    // digit separators for readability
long long ll{ 9'000'000'000'000'000'000 }; // at least 64 bits

std::cout << 7 / 4;  // 1 (truncated, not 1.75)
```

→ _See [04_SignedIntegers](../solutions/Chapter_04_Fundamental_Data_Types/04_SignedIntegers/) for ranges and overflow demos._

### 4.5 - Unsigned integers, and why to avoid them

- **Unsigned integers** hold only non-negative values and use **modulo wrapping** on overflow
- Mixing **signed and unsigned** in expressions implicitly converts the signed value to unsigned, causing **subtle bugs**
- Example: `2u - 3u` wraps to a very large positive number rather than producing `-1`
- **Favor signed types** for quantities and math
- The only recommended uses of unsigned types are **bit manipulation** and cases where wrap-around behavior is intentional

```cpp
unsigned int u{ 2 };
std::cout << u - 3; // wraps to a huge number, not -1!
```

→ _See [05_UnsignedIntegers](../solutions/Chapter_04_Fundamental_Data_Types/05_UnsignedIntegers/) for unsigned wrapping pitfalls._

### 4.6 - Fixed-width integers and size_t

- **Fixed-width integers** (e.g., `std::int32_t`) from `<cstdint>` guarantee **exact sizes**
- The **8-bit types** (`std::int8_t`) often behave like `char`, causing unexpected output
- **Fast/least types** exist but should be avoided due to inconsistent behavior across platforms
- `std::size_t` is an **unsigned type** for object sizes; include `<cstddef>` to use it
- Prefer `std::int32_t` or `std::int64_t` when a **guaranteed size** is required (e.g., serialization, hardware interfacing)
- `std::size_t` is typically **4 bytes** on 32-bit systems and **8 bytes** on 64-bit systems

```cpp
#include <cstdint>
std::int32_t x{ 100 };         // exactly 32 bits
std::int8_t  y{ 65 };          // may print as 'A' (treated as char)

#include <cstddef>
std::size_t sz{ sizeof(int) }; // unsigned, platform-dependent size
```

→ _See [06_FixedWidthIntegers](../solutions/Chapter_04_Fundamental_Data_Types/06_FixedWidthIntegers/) for `std::int32_t` and `std::size_t` usage._

### 4.7 - Introduction to scientific notation

- **Scientific notation** expresses numbers as _significand x 10^exponent_ (e.g., `5.9722e24`)
- The digits in the significand are the **significant digits** and determine precision
- **Trailing zeros** after a decimal point are significant; trailing zeros in a whole number are not by default
- In C++, scientific notation uses the `e` character (e.g., `3.14e2` means `314.0`)
- Understanding significant digits is crucial for knowing the limits of **floating-point precision**

```cpp
double avogadro{ 6.02e23 };  // 6.02 × 10^23
double small{ 5e-3 };         // 0.005
double charge{ 1.6e-19 };    // 0.00000000000000000016
```

→ _See [07_FloatingPointBasics](../solutions/Chapter_04_Fundamental_Data_Types/07_FloatingPointBasics/) for scientific notation and precision._

### 4.8 - Floating point numbers

- C++ has `float` (4 bytes, **~7 digits**), `double` (8 bytes, **~16 digits**), and `long double`
- Floating-point literals default to `double`; use the `f` suffix for `float` literals
- **Rounding errors** are inherent in floating-point and accumulate with operations - never compare floats with `==`
- **IEEE 754** defines special values: `Inf`, `-Inf`, `NaN`, and signed zero; `NaN != NaN` is `true`
- Use `std::setprecision(n)` from `<iomanip>` to control significant digits output (default is **6**)

```cpp
#include <iomanip>
std::cout << std::setprecision(17);
std::cout << 0.1 + 0.2 << '\n'; // 0.30000000000000004 (rounding error!)

float  f{ 3.14f };  // f suffix required for float literals
double d{ 3.14 };   // double by default - prefer this
```

→ _See [08_FloatingPointPitfalls](../solutions/Chapter_04_Fundamental_Data_Types/08_FloatingPointPitfalls/) for rounding error and equality comparison demos._

### 4.9 - Boolean values

- `bool` stores **`true`** or **`false`** (internally 1 or 0)
- `std::cout` prints bools as `0`/`1` by default; use **`std::boolalpha`** to print `true`/`false`
- `std::cin` only accepts `0`/`1` for bools by default; enable `std::boolalpha` on `std::cin` for text input
- Any **non-zero integer** converts to `true`; zero converts to `false`
- **Logical operators** (`&&`, `||`, `!`) operate on and return `bool` values

```cpp
bool b{ true };
std::cout << b << '\n';                   // 1
std::cout << std::boolalpha << b << '\n'; // true

if (4)  // non-zero converts to true
    std::cout << "this prints\n";
```

→ _See [09_Booleans](../solutions/Chapter_04_Fundamental_Data_Types/09_Booleans/) for boolean I/O and `std::boolalpha`._

### 4.10 - Introduction to if statements

- **`if` statements** execute code conditionally based on a **boolean expression**
- Use `else` for the alternative branch and chain **`else if`** for multiple conditions
- Non-boolean conditionals are converted: **non-zero -> `true`**, **zero -> `false`**
- **Early returns** allow exiting a function before its end
- Always use **blocks (`{}`)** with `if`/`else`, even for single statements, to prevent errors when adding code later
- Prefer flattened `else if` chains over deeply **nested `if`** statements for readability

```cpp
if (x > 0)
{
    std::cout << "positive\n";
}
else if (x < 0)
{
    std::cout << "negative\n";
}
else
{
    std::cout << "zero\n";
}
```

> **See also:** [Chapter 8 - Control Flow](Chapter%208%20-%20Control%20Flow.md) for complete coverage of `if`, `switch`, loops, and other control flow structures.

### 4.11 - Chars

- `char` holds a single **ASCII character** (1 byte); character literals use **single quotes** (`'a'`)
- **String literals** use double quotes (`"hello"`) - do not confuse with character literals
- **Escape sequences** like `'\n'` and `'\t'` represent special characters
- Avoid **multicharacter literals** (e.g., `'ab'`); the default **signedness** of `char` is implementation-defined
- Characters are stored as **integer values** mapped via the ASCII table (e.g., `'A'` = 65, `'0'` = 48)
- You can perform **arithmetic on `char`** values - e.g., `'A' + 1` yields `'B'`

```cpp
char c{ 'A' };
std::cout << c << '\n';                    // A
std::cout << static_cast<int>(c) << '\n';  // 65 (ASCII code)
std::cout << c + 1 << '\n';                // 66 (printed as int)
```

→ _See [10_CharsAndASCII](../solutions/Chapter_04_Fundamental_Data_Types/10_CharsAndASCII/) for char/ASCII and escape sequence demos._

### 4.12 - Introduction to type conversion and static_cast

- **Implicit type conversion** happens automatically when types don't match (e.g., `int` to `double`)
- **Unsafe conversions** (e.g., `double` to `int`) generate warnings and drop fractional parts
- Use **`static_cast<new_type>(expression)`** for explicit, warning-free conversions
- **Brace initialization** (`{}`) prevents narrowing conversions at compile time
- The compiler follows the **usual arithmetic conversions**, generally promoting smaller types to larger ones
- `static_cast` is preferred over **C-style casts** (`(int)x`) because it is checked at compile time and clearly communicates intent

```cpp
double d{ 4.5 };
int i{ static_cast<int>(d) }; // explicit: i = 4, no warning
```

> **See also:** [Chapter 10 - Type Conversion, Type Aliases, and Type Deduction](Chapter%2010%20-%20Type%20Conversion,%20Type%20Aliases,%20and%20Type%20Deduction.md) for the full type conversion story.

→ _See [11_TypeConversion](../solutions/Chapter_04_Fundamental_Data_Types/11_TypeConversion/) for implicit/explicit conversion examples._

---

### Edge Cases and Caveats

- **Signed integer overflow** - undefined behavior, not a predictable wrap.

  ❌ **Bad:**

  ```cpp
  int x{ 2'147'483'647 };
  std::cout << x + 1; // UB! not guaranteed to wrap
  ```

  ✅ **Good:** Use a larger type (`long long`) or check before arithmetic.

- **Mixing signed and unsigned** - signed is implicitly converted to unsigned.

  ❌ **Bad:**

  ```cpp
  std::cout << (2u - 3u); // wraps to 4294967295, not -1
  ```

  ✅ **Good:** Stick to signed types for math; avoid mixing.

- **Assuming `int` is always 32 bits** - the standard only guarantees ≥16 bits.

  ❌ **Bad:** Relying on `int` being 4 bytes without checking.
  ✅ **Good:** Use `std::int32_t` when a guaranteed 32-bit size is required.

- **Comparing floats with `==`** - rounding errors make exact comparison unreliable.

  ❌ **Bad:**

  ```cpp
  if (0.1 + 0.2 == 0.3) // false on most systems!
  ```

  ✅ **Good:** Compare with an epsilon: `std::abs(a - b) < 1e-9`.

- **Using `float` instead of `double`** - ~7 digits of precision is easily exceeded.

  ❌ **Bad:** `float pi{ 3.14159265f };` - precision lost after 7th digit.
  ✅ **Good:** `double pi{ 3.14159265 };` - ~16 digits of precision.

- **Confusing `'5'` (char, ASCII 53) with `5` (integer)**

  ❌ **Bad:** `char c{'5'}; if (c == 5) ...` - always false!
  ✅ **Good:** `if (c == '5') ...` or use `static_cast<int>(c)` for the numeric value.

- **Using `/n` instead of `\n`** - forward slash creates a multicharacter literal.

  ❌ **Bad:** `std::cout << '/n';` prints a number.
  ✅ **Good:** `std::cout << '\n';` prints a newline.

- **Expecting `std::int8_t` to print as a number** - it often acts like `char`.

  ❌ **Bad:** `std::int8_t x{65}; std::cout << x;` - prints `A`.
  ✅ **Good:** `std::cout << static_cast<int>(x);` - prints `65`.

- **Forgetting the `f` suffix on float literals** - `5.0` is `double`, not `float`.

  ❌ **Bad:** `float f{ 5.0 };` - narrowing from `double`.
  ✅ **Good:** `float f{ 5.0f };`

---

### Hands-On Code Projects

| #   | Project                                                                                              | Concept                                                     |
| --- | ---------------------------------------------------------------------------------------------------- | ----------------------------------------------------------- |
| 01  | [01_BitsAndBytes](../solutions/Chapter_04_Fundamental_Data_Types/01_BitsAndBytes/)                   | Bits, bytes, and memory storage                             |
| 02  | [02_Void](../solutions/Chapter_04_Fundamental_Data_Types/02_Void/)                                   | Void type usage and limitations                             |
| 03  | [03_SizeofOperator](../solutions/Chapter_04_Fundamental_Data_Types/03_SizeofOperator/)               | `sizeof` on fundamental types                               |
| 04  | [04_SignedIntegers](../solutions/Chapter_04_Fundamental_Data_Types/04_SignedIntegers/)               | Signed integer types, ranges, overflow (UB)                 |
| 05  | [05_UnsignedIntegers](../solutions/Chapter_04_Fundamental_Data_Types/05_UnsignedIntegers/)           | Unsigned wrapping and signed/unsigned mixing                |
| 06  | [06_FixedWidthIntegers](../solutions/Chapter_04_Fundamental_Data_Types/06_FixedWidthIntegers/)       | `std::int32_t`, `std::size_t` from `<cstdint>`              |
| 07  | [07_FloatingPointBasics](../solutions/Chapter_04_Fundamental_Data_Types/07_FloatingPointBasics/)     | `float`, `double`, scientific notation, `std::setprecision` |
| 08  | [08_FloatingPointPitfalls](../solutions/Chapter_04_Fundamental_Data_Types/08_FloatingPointPitfalls/) | Rounding errors, equality comparison issues                 |
| 09  | [09_Booleans](../solutions/Chapter_04_Fundamental_Data_Types/09_Booleans/)                           | `bool`, `std::boolalpha`, integer-to-bool conversion        |
| 10  | [10_CharsAndASCII](../solutions/Chapter_04_Fundamental_Data_Types/10_CharsAndASCII/)                 | `char`, ASCII codes, escape sequences                       |
| 11  | [11_TypeConversion](../solutions/Chapter_04_Fundamental_Data_Types/11_TypeConversion/)               | Implicit/explicit conversions, `static_cast`                |
| 12  | [12_IntegerDivision](../solutions/Chapter_04_Fundamental_Data_Types/12_IntegerDivision/)             | Truncation in integer division, casting for fractions       |
| 13  | [13_BraceInitialization](../solutions/Chapter_04_Fundamental_Data_Types/13_BraceInitialization/)     | Brace init prevents narrowing conversions                   |

---

### Quick Reference

| Topic                     | Details                                                                                                             |
| ------------------------- | ------------------------------------------------------------------------------------------------------------------- |
| **Signed Integer Sizes**  | `short` ≥ 16 bits, `int` ≥ 16 bits (usually 32), `long` ≥ 32 bits, `long long` ≥ 64 bits                            |
| **Signed Integer Ranges** | 16-bit: −32,768 to 32,767 · 32-bit: −2,147,483,648 to 2,147,483,647 · 64-bit: −9.2×10¹⁸ to 9.2×10¹⁸                 |
| **Unsigned Integers**     | Same sizes as signed but range is 0 to 2ⁿ−1 (e.g., 32-bit: 0 to 4,294,967,295). Overflow wraps around.              |
| **Fixed-Width Types**     | `std::int8_t`, `std::int16_t`, `std::int32_t`, `std::int64_t` (and unsigned `std::uint_` variants) from `<cstdint>` |
| **`std::size_t`**         | Unsigned type for object sizes; 4 bytes on 32-bit, 8 bytes on 64-bit systems. Include `<cstddef>`.                  |
| **`float`**               | 4 bytes, ~7 significant digits of precision, suffix `f` (e.g., `3.14f`)                                             |
| **`double`**              | 8 bytes, ~15–16 significant digits of precision (default for floating-point literals)                               |
| **`long double`**         | ≥ 8 bytes (often 8, 12, or 16 depending on platform), extended precision                                            |
| **`bool`**                | 1 byte, stores `true` (1) or `false` (0). Non-zero integers convert to `true`.                                      |
| **`char`**                | 1 byte, stores ASCII character (e.g., `'A'` = 65, `'0'` = 48). Signedness is implementation-defined.                |
| **`sizeof` Operator**     | Compile-time operator returning size in bytes as `std::size_t`. Works on types and expressions.                     |
| **Initialization Forms**  | Copy: `int x = 5;` · Direct: `int x(5);` · Brace (preferred): `int x{5};` - brace prevents narrowing                |
| **Implicit Conversion**   | Compiler auto-converts types (e.g., `int` → `double`). May lose data (e.g., `double` → `int` drops fraction).       |
| **`static_cast`**         | `static_cast<int>(4.5)` - explicit, checked cast. Preferred over C-style `(int)4.5`.                                |
| **Scientific Notation**   | `3.14e2` = 314.0, `5e-3` = 0.005. Literals use `e`/`E` for the exponent.                                            |
| **IEEE 754 Specials**     | `Inf` (overflow), `-Inf`, `NaN` (invalid operations). `NaN != NaN` is `true`.                                       |

---

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. How many unique values can an object with _n_ bits store?

<details>
<summary>Show answer</summary>

**Direct answer:** An object with _n_ bits can store $2^n$ unique values. For example, an 8-bit (1 byte) object can store $2^8 = 256$ unique values, and a 32-bit integer can store $2^{32} \approx 4.3$ billion unique values.

**Detailed explanation:**
Each bit can be either 0 or 1, so _n_ bits give $2^n$ possible combinations. The C++ standard only guarantees minimum sizes for types (e.g., `int` is at least 16 bits), so the actual number of values depends on the platform. Use `sizeof(type)` to determine the actual size in bytes on your machine. `sizeof` is a compile-time operator that returns a value of type `std::size_t`.

</details>

2. What is the difference between **signed** and **unsigned** integer overflow behavior?

<details>
<summary>Show answer</summary>

**Direct answer:** Signed integer overflow is **undefined behavior** - anything can happen. Unsigned integer overflow is well-defined: it wraps around using modulo arithmetic (e.g., for a `uint16_t`, 65535 + 1 wraps to 0). This is why mixing signed and unsigned types is dangerous - the signed value gets implicitly converted to unsigned, and unexpected wrapping can occur.

**Detailed explanation:**
Signed integers use two's complement on virtually all modern systems (guaranteed since C++20). When a signed value exceeds its range, the result is undefined behavior - the compiler may assume it never happens and optimize accordingly, leading to bugs that are very hard to diagnose. Unsigned integers use modulo $2^n$ wrapping, which is predictable but can still cause logic errors (e.g., `2u - 3u` wraps to a very large positive number instead of `-1`). The recommended practice is to favor signed types for general arithmetic and only use unsigned types for bit manipulation or when wrap-around behavior is intentional.

</details>

3. Why should you prefer `double` over `float` for most floating-point work?

<details>
<summary>Show answer</summary>

**Direct answer:** `double` has roughly twice the precision of `float` (~16 significant digits vs. ~7) and is the default type for floating-point literals in C++. The performance difference between `float` and `double` is negligible on modern hardware, so `double` gives you better accuracy at virtually no cost.

**Detailed explanation:**
`float` occupies 4 bytes with ~7 digits of precision, while `double` occupies 8 bytes with ~16 digits. When you write `3.14`, the compiler treats it as a `double` - you need the `f` suffix (`3.14f`) to make it a `float`. Rounding errors are inherent in all floating-point types but accumulate faster with `float` due to lower precision. `long double` offers even more precision but is not worth the extra cost in most cases (and its actual size varies by platform).

```cpp
float f{ 3.14f };  // f suffix required for float literals
double d{ 3.14 };  // double by default - prefer this
```

</details>

4. What does `static_cast<int>(4.7)` evaluate to? Why is it preferred over `(int)4.7`?

<details>
<summary>Show answer</summary>

**Direct answer:** `static_cast<int>(4.7)` evaluates to `4` (the fractional part is truncated, not rounded). It is preferred over the C-style cast `(int)4.7` because `static_cast` is checked at compile time, clearly communicates intent, and is easy to search for in code. C-style casts are more permissive and can accidentally perform dangerous conversions that `static_cast` would reject.

**Detailed explanation:**
Implicit type conversion (e.g., assigning a `double` to an `int`) happens automatically but generates compiler warnings for potentially unsafe conversions. `static_cast<new_type>(expression)` performs the same conversion explicitly, suppressing the warning and making your intent clear. Brace initialization rejects narrowing conversions entirely (`int x{4.7};` is a compile error), so `static_cast` is the correct tool when you know you want to truncate.

```cpp
double d{ 4.7 };
int x{ static_cast<int>(d) }; // x = 4 - explicit, safe, no warning
int y = (int)d;                // x = 4 - works but less safe, harder to find
```

</details>

5. What is the difference between `'5'` and `5` in C++?

<details>
<summary>Show answer</summary>

**Direct answer:** `'5'` is a `char` literal representing the ASCII character '5' (stored as integer value 53). `5` is an `int` literal representing the integer value five. They are completely different types with different values in memory.

**Detailed explanation:**
Characters are stored as integer values mapped through the ASCII table. The character `'0'` has ASCII value 48, `'1'` is 49, etc. So `'5'` is stored as 53. The integer `5` is stored as the binary representation of the number five. You can convert between them: `'5' - '0'` evaluates to `5` (the integer), and `static_cast<char>(53)` gives you `'5'`. Character literals use single quotes and string literals use double quotes - `'a'` is a `char`, while `"a"` is a `const char[2]` (C-style string with null terminator).

</details>

6. Why should you avoid mixing signed and unsigned integers in expressions?

<details>
<summary>Show answer</summary>

**Direct answer:** When you mix signed and unsigned integers in an expression, the signed value is implicitly converted to unsigned. If the signed value is negative, this conversion wraps it to a very large positive number, producing incorrect results. For example, `-1 < 1u` evaluates to `false` because `-1` is converted to an unsigned value near the maximum.

**Detailed explanation:**
The compiler follows "usual arithmetic conversions" that promote both operands to a common type. When one operand is unsigned and the other is signed, the signed value is converted to unsigned. This can cause subtle bugs in comparisons, arithmetic, and loop conditions. The fix is to favor signed types for general arithmetic and use `static_cast` when you must convert between signed and unsigned types.

```cpp
unsigned int u{ 1 };
int s{ -1 };
if (s < u)  // WRONG - s is converted to a huge unsigned value
    std::cout << "-1 is less than 1";  // this does NOT print!
```

</details>

7. What does `sizeof` return, and what type is its result?

<details>
<summary>Show answer</summary>

**Direct answer:** `sizeof` returns the size of a type or object in bytes. Its result type is `std::size_t`, which is an unsigned integral type large enough to represent the size of any object. `sizeof` is a compile-time operator - it does not evaluate its operand at runtime.

**Detailed explanation:**
You can use `sizeof` with a type (`sizeof(int)`) or with a variable (`sizeof x`). The C++ standard only guarantees minimum sizes for fundamental types, so the actual sizes are platform-dependent. For example, `sizeof(int)` is typically 4 bytes on modern platforms but is only guaranteed to be at least 2 bytes. `sizeof(char)` is always exactly 1 byte by definition.

</details>

8. Why can't you compare floating-point numbers with `==` reliably?

<details>
<summary>Show answer</summary>

**Direct answer:** Floating-point numbers have limited precision and cannot represent all real numbers exactly. Arithmetic operations introduce tiny rounding errors that accumulate, so two values that should be mathematically equal may differ by a small amount. Comparing with `==` checks for exact bit-for-bit equality, which fails when rounding errors are present.

**Detailed explanation:**
For example, `0.1 + 0.2` does not equal `0.3` exactly in floating-point - the result is something like `0.30000000000000004`. Instead of `==`, use an epsilon-based comparison that checks whether two values are "close enough." A robust approach combines an absolute epsilon (for values near zero) with a relative epsilon (Knuth's algorithm) that scales with the magnitude of the operands. IEEE 754 also defines special values: `Inf` (infinity from division by zero), `NaN` (not a number, from invalid operations like `sqrt(-1)`), and signed zero. `NaN` is unique in that `NaN != NaN` is `true`.

</details>

9. What is `void` used for in C++?

<details>
<summary>Show answer</summary>

**Direct answer:** `void` means "no type." It is primarily used to indicate that a function returns no value (`void myFunc()`). `void` is an incomplete type - you cannot create a variable of type `void`. Void pointers (`void*`) can point to objects of any type but must be cast to another pointer type before dereferencing.

**Detailed explanation:**
Using `void` in a parameter list to indicate no parameters (e.g., `int main(void)`) is valid but deprecated in C++ - use empty parentheses instead (`int main()`). `void*` is useful in C-style APIs for generic pointers, but in modern C++ you should prefer templates or `std::any` for type-generic programming.

</details>

10. What are the fixed-width integer types, and why should you use them?

<details>
<summary>Show answer</summary>

**Direct answer:** Fixed-width integer types (e.g., `int8_t`, `int16_t`, `int32_t`, `int64_t` and their unsigned counterparts from `<cstdint>`) have guaranteed sizes on all platforms. You should use them when you need a specific number of bits (e.g., for file formats, network protocols, or hardware interfaces) rather than relying on the platform-dependent sizes of `int`, `short`, etc.

**Detailed explanation:**
The standard types (`int`, `long`, etc.) only have guaranteed minimum sizes, which can differ across platforms and cause portability bugs. The `<cstdint>` header provides types with exact widths. However, for general-purpose code where exact size doesn't matter, `int` remains the preferred choice because it is typically the most efficient type for the platform. The "fast" variants (`int_fast16_t`, etc.) give the fastest type with at least the specified width, and the "least" variants (`int_least16_t`, etc.) give the smallest type with at least the specified width.

</details>
