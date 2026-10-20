# Chapter 10 Recap - Type Conversion, Type Aliases, and Type Deduction

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Conversions produce a temporary value of the target type; they never modify the original value
- **Numeric promotions** are always safe (value-preserving); **numeric conversions** may not be
- Prefer **brace initialization** (`{}`)-it catches narrowing conversions at compile time
- Use **`static_cast`** for explicit conversions; avoid C-style casts, `const_cast`, and `reinterpret_cast`
- When a narrowing conversion is intentional, wrap it in `static_cast` to document intent and suppress warnings
- Constexpr values get a special exemption from narrowing rules when brace-initializing (except float-to-int)
- Avoid mixing signed and unsigned types in arithmetic-the results may be counterintuitive
- Use **type aliases** to simplify complex types and improve readability, but don't overuse them

### 3 Tiny Examples

1.

```cpp
int i{ 3 };
double d{ i }; // implicit conversion: int → double (safe, value-preserving)
int j{ d };    // implicit narrowing: double → int (warning! drops .0)
```

2.

```cpp
float f{ 3.14f };
double d{ f };       // floating-point promotion (float → double)

char c{ 'A' };
int i{ c };          // integral promotion (char → int)
```

3.

```cpp
int x{ 3.5 };                       // error: narrowing in brace init
int y{ static_cast<int>(3.5) };     // OK: explicit intent
constexpr int z{ 5 }; double d{ z }; // OK: constexpr exemption
```

### 3 Common Mistakes

- Integer division surprise
- Signed/unsigned mixing
- Assuming all widenings are promotions

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Implicit type conversion (coercion)** - automatic conversion performed by the compiler when a different type is expected
- **Explicit type conversion (casting)** - programmer-requested conversion using cast operators
- **Numeric promotion** - value-preserving conversion of narrow types (e.g. `char`, `short`, `bool`, `float`) to wider types (`int` or `double`)
- **Numeric conversion** - any fundamental type conversion that isn't a promotion (may be unsafe)
- **Narrowing conversion** - a numeric conversion where the destination type may not hold all source values
- **Usual arithmetic conversions** - rules that determine how mismatched operand types are resolved in binary operators
- **`static_cast`** - the preferred named cast for explicit type conversions
- **Type alias (`using`)** - creates a new name for an existing type (not a new distinct type)
- **Typedef** - older syntax for type aliases; prefer `using` in modern C++
- **Type deduction (`auto`)** - lets the compiler deduce a variable's type from its initializer
- **Trailing return type** - alternative function syntax using `auto func() -> ReturnType`

### Section-by-Section Detail

### 10.1 - Implicit type conversion

- **Implicit conversions** (**coercions**) happen automatically when the compiler needs a different type - during initialization, assignment, return statements, binary operations, and function calls
- The C++ standard defines **standard conversions** grouped into numeric promotions, numeric conversions, qualification conversions, value transformations, and pointer conversions
- The compiler can **chain** multiple standard conversions in a single **implicit conversion sequence**
- If no valid conversion sequence exists, compilation fails with a **type mismatch error**
- Implicit conversions happen silently - the compiler typically won't warn unless the conversion is potentially **lossy**

```cpp
int i{ 3 };
double d{ i }; // implicit conversion: int → double (safe, value-preserving)
int j{ d };    // implicit narrowing: double → int (warning! drops .0)
```

→ _See [01_ImplicitTypeConversion](../solutions/Chapter_10_Type_Conversion_And_Deduction/01_ImplicitTypeConversion/)_

### 10.2 - Floating-point and integral promotion

- **Numeric promotions** convert narrow types to wider types (`int` or `double`) so the CPU can process them efficiently
- **Floating-point promotion** converts `float` to `double`; **integral promotion** converts `bool`, `char`, `short` to `int`
- Promotions are always **value-preserving** - no data is lost because the destination type can represent every source value
- Not all widening conversions are promotions: `int` → `long` and `int` → `double` are classified as **numeric conversions**, not promotions
- This distinction matters for **function overload resolution**, where promotions are preferred over conversions

```cpp
float f{ 3.14f };
double d{ f };       // floating-point promotion (float → double)

char c{ 'A' };
int i{ c };          // integral promotion (char → int)
```

→ _See [02_NumericPromotion](../solutions/Chapter_10_Type_Conversion_And_Deduction/02_NumericPromotion/)_

### 10.3 - Numeric conversions

- **Numeric conversions** cover all non-promotion conversions between fundamental types: integral-to-integral, float-to-float, float-to-integral (truncates), integral-to-float (may lose precision), and anything-to-`bool`
- Three **safety categories**: **value-preserving**, **reinterpretive** (bits preserved but value may differ, e.g., `signed` → `unsigned`), and **lossy** (data permanently lost)
- The compiler typically warns about **lossy conversions**, and **brace initialization** blocks them entirely at compile time
- Use **`static_cast`** to document intent when a **narrowing conversion** is deliberate

→ _See [03_NumericConversions](../solutions/Chapter_10_Type_Conversion_And_Deduction/03_NumericConversions/)_

**Numeric Conversion Safety Categories:**

| Category             | Definition                           | Example                                                   | Data Loss?                  |
| -------------------- | ------------------------------------ | --------------------------------------------------------- | --------------------------- |
| **Value-preserving** | Destination holds every source value | `int` → `long`                                            | No                          |
| **Reinterpretive**   | Bits preserved, but value may differ | `signed` → `unsigned`                                     | No bits lost, value changes |
| **Lossy**            | Data permanently lost                | `double` → `int` (truncates), `int` → `float` (precision) | Yes                         |

> **Rule of thumb:** Brace initialization (`{}`) blocks lossy conversions at compile time. Use `static_cast` when narrowing is intentional.

### 10.4 - Narrowing conversions, list initialization, and constexpr initializers

- A **narrowing conversion** is one where the destination type cannot represent all possible source values (e.g., `double` → `int`, `int` → `char`)
- **Brace initialization** (`{}`) disallows narrowing conversions and produces a compile error - one of the strongest reasons to prefer it
- **`constexpr` exemption**: if the source is a `constexpr` expression and its value provably fits in the destination type, the compiler allows it
- The **exception to the exemption**: `float`-to-`int` is always treated as narrowing regardless of the value
- When a narrowing conversion is intentional, use **`static_cast`** to make intent explicit

```cpp
int x{ 3.5 };                       // error: narrowing in brace init
int y{ static_cast<int>(3.5) };     // OK: explicit intent
constexpr int z{ 5 }; double d{ z }; // OK: constexpr exemption
```

→ _See [04_NarrowingConversions](../solutions/Chapter_10_Type_Conversion_And_Deduction/04_NarrowingConversions/)_

### 10.5 - Arithmetic conversions

- When a binary operator receives mismatched operand types, the **usual arithmetic conversions** implicitly convert the lower-ranked operand to the higher-ranked type
- Type ranking from low to high: `int` < `long` < `long long` < `float` < `double` < `long double`
- If one operand is **signed** and the other **unsigned** of the same rank, the signed operand is converted to unsigned - causing surprises like `5u - 10` wrapping
- The **return type** of the expression is the type both operands were converted to
- This **signed/unsigned mixing** problem is a primary reason to **avoid unsigned integers in arithmetic**

```cpp
int s{ -3 };
unsigned int u{ 5 };
auto result{ s + u }; // s promoted to unsigned - result is a huge number!
```

> **See also:** [Chapter 4 - Fundamental Data Types](Chapter%204%20-%20Fundamental%20Data%20Types.md) for unsigned wrapping behavior.

→ _See [05_ArithmeticConversions](../solutions/Chapter_10_Type_Conversion_And_Deduction/05_ArithmeticConversions/) · [11_SignedUnsignedMixing](../solutions/Chapter_10_Type_Conversion_And_Deduction/11_SignedUnsignedMixing/)_

**Usual Arithmetic Conversion Rules:**

| Situation                      | Rule                                                | Example                                  |
| ------------------------------ | --------------------------------------------------- | ---------------------------------------- |
| Both same type                 | No conversion needed                                | `int + int` → `int`                      |
| One is wider floating          | Narrow operand promoted to wider float              | `int + double` → `double`                |
| Both integral, same sign       | Narrow converted to wider                           | `short + int` → `int`                    |
| Signed vs unsigned (same rank) | **Signed → unsigned** (dangerous!)                  | `-3 + 5u` wraps to huge value            |
| Signed wider than unsigned     | Signed type used if it can hold all unsigned values | `long long + unsigned int` → `long long` |

> **Key danger:** When signed meets unsigned of the same rank, the signed value is converted to unsigned. This causes `-1 < 1u` to evaluate to `false` because `-1` wraps to `UINT_MAX`.

### 10.6 - Explicit type conversion (casting) and static_cast

- C++ provides five cast operators: **`static_cast`**, **`dynamic_cast`**, **`const_cast`**, **`reinterpret_cast`**, and **C-style casts**
- **`static_cast<Type>(value)`** is the preferred choice - performs **compile-time type checking**, clearly communicates intent, and is searchable
- **C-style casts** should be avoided because they can silently act as `static_cast`, `const_cast`, or `reinterpret_cast` with no way to tell which
- Use `static_cast` to make **narrowing conversions** explicit, convert between related types, and convert `void*` pointers back to their original type
- `dynamic_cast` is for safe **downcasting** in inheritance hierarchies; `const_cast` and `reinterpret_cast` are for rare, well-justified circumstances only

```cpp
double d{ 3.14 };
int i{ static_cast<int>(d) };  // explicit, compile-time checked
int j{ (int)d };               // C-style cast - AVOID (no compile-time safety)
```

→ _See [06_StaticCast](../solutions/Chapter_10_Type_Conversion_And_Deduction/06_StaticCast/) · [07_CStyleCastDangers](../solutions/Chapter_10_Type_Conversion_And_Deduction/07_CStyleCastDangers/)_

**C++ Cast Operators Comparison:**

| Cast                    | Purpose                         | Compile-time Check  | When to Use                           |
| ----------------------- | ------------------------------- | ------------------- | ------------------------------------- |
| `static_cast<T>()`      | General-purpose safe conversion | Yes                 | Default choice for conversions        |
| `dynamic_cast<T>()`     | Safe downcast in inheritance    | Yes + runtime check | Polymorphic hierarchies (Ch 25)       |
| `const_cast<T>()`       | Add/remove `const`              | Yes                 | Rare - interfacing with legacy C APIs |
| `reinterpret_cast<T>()` | Reinterpret bit pattern         | Minimal             | Extremely rare - low-level/hardware   |
| `(T)value` (C-style)    | May act as any of the above     | **No**              | **Never** - avoid in C++              |

> **Best practice:** Use `static_cast` for 99% of explicit conversions. Enable `-Wold-style-cast` to catch C-style casts.

### 10.7 - Typedefs and type aliases

- **Type aliases** (created with `using Name = Type;`) give a new name to an existing type - useful for **platform-independent coding**, simplifying complex types, and documenting value semantics
- Aliases are **not distinct types** - the compiler treats the alias and the original type as interchangeable, so they provide no **type safety**
- Prefer the modern **`using`** syntax over the older **`typedef`** syntax in new C++ code
- Name type aliases starting with a **capital letter** by convention

```cpp
using Distance = double;                              // preferred modern syntax
using StringPair = std::pair<std::string, std::string>; // simplify complex types
```

→ _See [08_TypeAliases](../solutions/Chapter_10_Type_Conversion_And_Deduction/08_TypeAliases/)_

### 10.8 - Type deduction for objects using the auto keyword

- The **`auto`** keyword lets the compiler **deduce** a variable's type from its initializer, reducing redundancy and ensuring the variable is always initialized
- Type deduction **drops top-level `const` and references** - write `const auto` (or `constexpr auto`) explicitly to preserve `const`
- **String literals** deduce to `const char*`, not `std::string` or `std::string_view` - use the **`s`** suffix for `std::string` or **`sv`** for `std::string_view`
- `auto` avoids unintended **implicit conversions** because the variable's type always matches the initializer exactly
- The tradeoff is reduced **readability** - when the initializer doesn't make the type obvious, `auto` can obscure the actual type

```cpp
auto x{ 5 };         // int
auto d{ 3.14 };      // double
const auto c{ x };   // const int - must re-apply const
auto s{ "hello"sv };  // std::string_view (not const char*)
```

→ _See [09_AutoTypeDeduction](../solutions/Chapter_10_Type_Conversion_And_Deduction/09_AutoTypeDeduction/)_

**auto Type Deduction Behavior:**

| Initializer                    | Deduced Type            | Notes                                               |
| ------------------------------ | ----------------------- | --------------------------------------------------- |
| `auto x{ 5 };`                 | `int`                   | Integer literal                                     |
| `auto d{ 3.14 };`              | `double`                | Floating-point literal                              |
| `auto f{ 3.14f };`             | `float`                 | `f` suffix preserved                                |
| `const int ci{5}; auto a{ci};` | `int` (not `const int`) | Top-level `const` dropped                           |
| `auto s{ "hello" };`           | `const char*`           | String literal - not `std::string`!                 |
| `auto s{ "hello"s };`          | `std::string`           | `s` suffix (`using namespace std::string_literals`) |
| `auto s{ "hello"sv };`         | `std::string_view`      | `sv` suffix                                         |
| `const auto x{ 5 };`           | `const int`             | Re-apply `const` explicitly                         |

### 10.9 - Type deduction for functions

- In C++14+, **`auto`** can be used as a function return type, letting the compiler deduce it from the `return` statements
- All `return` statements must return the **same type**, and the function must be **fully defined** before any call site
- The **trailing return syntax** (`auto func(params) -> ReturnType`) places the return type after the parameters - useful when the return type depends on parameter types
- For normal functions, **prefer explicit return types** over `auto` - they serve as documentation and allow **forward declarations**
- `auto` return types are most useful in **templates** and **lambdas** where the return type would be verbose

```cpp
auto add(int x, int y) -> int // trailing return type syntax
{
    return x + y;
}
```

→ _See [10_AutoReturnTypes](../solutions/Chapter_10_Type_Conversion_And_Deduction/10_AutoReturnTypes/) · [12_CommonPitfalls](../solutions/Chapter_10_Type_Conversion_And_Deduction/12_CommonPitfalls/)_

### Edge Cases and Caveats

- **Integer division surprise** - `10 / 4` gives `2`, not `2.5`.

  ❌ **Bad:** `static_cast<double>(10 / 4)` - still truncates first.
  ✅ **Good:** `static_cast<double>(10) / 4` - cast _before_ dividing.

- **Signed/unsigned mixing** - `5u - 10` wraps to a huge unsigned value.

  ❌ **Bad:** `-3 < 5u` - false (signed→unsigned conversion).
  ✅ **Good:** Avoid unsigned for arithmetic; use `-Wsign-conversion`.

- **Assuming all widenings are promotions** - `int`→`long` is a _conversion_, not a promotion.

  ❌ **Bad:** Expecting `print(long)` to win overload resolution via promotion.
  ✅ **Good:** Remember: promotions are only `bool`/`char`/`short`→`int`, `float`→`double`.

- **Forgetting `const` with `auto`** - `auto` drops `const`.

  ❌ **Bad:** `auto x{ constValue };` - x is non-const.
  ✅ **Good:** `const auto x{ constValue };`

- **String literal type with `auto`** - deduces `const char*`.

  ❌ **Bad:** `auto s{ "hello" };` - `const char*`, not `std::string`.
  ✅ **Good:** `auto s{ "hello"s };` or `auto s{ "hello"sv };`

- **Using C-style casts** - `(int)x` may silently perform `reinterpret_cast`.

  ❌ **Bad:** `(int)ptr`
  ✅ **Good:** `static_cast<int>(x)` - enable `-Wold-style-cast`.

- **Narrowing in brace init** - `int x{ 3.5 };` won't compile.

  ❌ **Bad:** Surprised by compile error.
  ✅ **Good:** If intentional: `int x{ static_cast<int>(3.5) };`

- **`auto` return with forward declarations** - can't forward-declare `auto` return functions.

  ❌ **Bad:** Forward declaring a function with `auto` return, then calling it.
  ✅ **Good:** Use explicit return types for functions needing forward declarations.

- **Thinking type aliases create new types** - `using Miles = long;` is interchangeable with `long`.

  ❌ **Bad:** Expecting `Miles` and `Speed` (both `long`) to be type-safe.
  ✅ **Good:** Use a wrapper struct for true type safety.

---

### Hands-On Code Projects

| #   | Project                                                                                                       | Concept                                        |
| --- | ------------------------------------------------------------------------------------------------------------- | ---------------------------------------------- |
| 01  | [01_ImplicitTypeConversion](../solutions/Chapter_10_Type_Conversion_And_Deduction/01_ImplicitTypeConversion/) | Automatic standard conversions                 |
| 02  | [02_NumericPromotion](../solutions/Chapter_10_Type_Conversion_And_Deduction/02_NumericPromotion/)             | `char`/`short`/`float` → `int`/`double`        |
| 03  | [03_NumericConversions](../solutions/Chapter_10_Type_Conversion_And_Deduction/03_NumericConversions/)         | Value-preserving, reinterpretive, lossy        |
| 04  | [04_NarrowingConversions](../solutions/Chapter_10_Type_Conversion_And_Deduction/04_NarrowingConversions/)     | Brace-init protection, `constexpr` exemption   |
| 05  | [05_ArithmeticConversions](../solutions/Chapter_10_Type_Conversion_And_Deduction/05_ArithmeticConversions/)   | Usual arithmetic conversions, type ranking     |
| 06  | [06_StaticCast](../solutions/Chapter_10_Type_Conversion_And_Deduction/06_StaticCast/)                         | Safe explicit casts with `static_cast`         |
| 07  | [07_CStyleCastDangers](../solutions/Chapter_10_Type_Conversion_And_Deduction/07_CStyleCastDangers/)           | Why C-style casts are dangerous                |
| 08  | [08_TypeAliases](../solutions/Chapter_10_Type_Conversion_And_Deduction/08_TypeAliases/)                       | `using` aliases, `typedef`, not distinct types |
| 09  | [09_AutoTypeDeduction](../solutions/Chapter_10_Type_Conversion_And_Deduction/09_AutoTypeDeduction/)           | `auto`, `const` dropping, string literal types |
| 10  | [10_AutoReturnTypes](../solutions/Chapter_10_Type_Conversion_And_Deduction/10_AutoReturnTypes/)               | `auto` return types, trailing return syntax    |
| 11  | [11_SignedUnsignedMixing](../solutions/Chapter_10_Type_Conversion_And_Deduction/11_SignedUnsignedMixing/)     | Signed/unsigned arithmetic surprises           |
| 12  | [12_CommonPitfalls](../solutions/Chapter_10_Type_Conversion_And_Deduction/12_CommonPitfalls/)                 | Integer division, narrowing, deduction gotchas |

### Quick Reference

### Type conversion hierarchy (low → high)

```
Promotion (always safe, value-preserving)
  bool/char/short → int          (integral promotion)
  float → double                  (floating-point promotion)

Numeric conversion (may lose data)
  int → long, int → double, double → int, signed ↔ unsigned
```

### Usual arithmetic conversion ranking (low → high)

```
int < long < long long < float < double < long double
```

The lower-ranked operand is converted to the higher-ranked type.

### static_cast

```cpp
double d{3.14};
int i{ static_cast<int>(d) };      // explicit narrowing - intent is clear

char c{'A'};
std::cout << static_cast<int>(c);  // prints 65, not 'A'

// Avoid: (int)d - C-style cast, unsafe
```

### Type alias

```cpp
using Distance = double;           // modern syntax (preferred)
typedef double Distance;           // legacy C syntax (avoid in new code)

using StringPair = std::pair<std::string, std::string>;  // simplify complex types
```

### auto deduction

```cpp
auto x{ 5 };                       // int
auto y{ 3.14 };                    // double
const auto z{ x };                 // const int - must re-apply const
constexpr auto w{ 42 };            // constexpr int

auto s1{ "hello" };                 // const char* - NOT std::string
auto s2{ "hello"s };               // std::string  (requires using namespace std::string_literals)
auto s3{ "hello"sv };              // std::string_view
```

### Trailing return type

```cpp
auto add(int x, int y) -> int      // equivalent to: int add(int x, int y)
{
    return x + y;
}
```

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is the difference between a **numeric promotion** and a **numeric conversion**?

<details>
<summary>Show answer</summary>

**Direct answer:** A numeric promotion widens a narrow type to `int` or `double` - the CPU's native operation size - and is always safe (no data loss). A numeric conversion is any other type change between fundamental types (e.g., `int` to `char`, `double` to `int`) and may be value-preserving, reinterpretive, or lossy.

**Detailed explanation:**
Promotions exist because most CPUs operate most efficiently on `int`-sized or `double`-sized values. Integral promotion converts `bool`, `char`, `short` (and their variants) to `int`. Floating-point promotion converts `float` to `double`. These always preserve the value. Conversions, on the other hand, may lose data - for example, `double` to `int` truncates the fractional part, and `int` to `char` silently drops high bits if the value doesn't fit.

</details>

2. Why does brace initialization disallow narrowing, and what is the `constexpr` exemption?

<details>
<summary>Show answer</summary>

**Direct answer:** Brace initialization (`{}`) produces a compile error on narrowing conversions to catch potential data loss at compile time - this is one of the strongest reasons to prefer it. The exemption: if the source is a `constexpr` expression and the value provably fits in the destination type, the compiler allows it because no data will actually be lost.

**Detailed explanation:**
A narrowing conversion is one where the destination can't represent all possible values of the source (e.g., `double` to `int`, `int` to `char`). With copy or direct initialization, these happen silently. Brace initialization catches them.

```cpp
int x{ 3.5 };             // ERROR: narrowing (double to int)
constexpr int y{ 5 };
char c{ y };               // OK: compiler knows 5 fits in char (constexpr exemption)
char d{ x };               // ERROR: x is not constexpr, might not fit
```

</details>

3. Name the five cast types in C++. Which one should you use for most explicit conversions?

<details>
<summary>Show answer</summary>

**Direct answer:** `static_cast`, `dynamic_cast`, `const_cast`, `reinterpret_cast`, and C-style casts (`(Type)value`). Use **`static_cast`** for most explicit conversions - it is checked at compile time, clearly communicates intent, and is searchable in code.

**Detailed explanation:**
C-style casts should be avoided because they silently pick the most permissive cast that works - they can act as `static_cast`, `const_cast`, or `reinterpret_cast` depending on context, with no way to tell which from the syntax. `dynamic_cast` is for safe downcasting in polymorphic hierarchies. `const_cast` adds or removes `const` (usually a design smell). `reinterpret_cast` reinterprets the bit pattern as a different type (dangerous, rarely needed).

```cpp
double d{ 3.14 };
int i{ static_cast<int>(d) };   // explicit, clear, safe - truncates to 3
int j{ (int)d };                 // C-style - avoid: which cast is it actually doing?
```

</details>

4. What are the **usual arithmetic conversions**, and what is the type ranking?

<details>
<summary>Show answer</summary>

**Direct answer:** When a binary operator receives operands of different types, the usual arithmetic conversions implicitly convert the lower-ranked operand to the higher-ranked type. Ranking (low to high): `int` < `long` < `long long` < `float` < `double` < `long double`.

**Detailed explanation:**
If one operand is signed and the other unsigned of the same rank, the signed operand is converted to unsigned - this can produce surprising results. For example, `5u - 10` wraps around to a very large unsigned value, and `-1 < 1u` evaluates to `false` because `-1` becomes a huge unsigned number.

```cpp
std::cout << 5u - 10;       // huge unsigned value (wrap-around)
std::cout << (-1 < 1u);     // prints 0 (false!) - -1 converted to unsigned
std::cout << (5.0 + 3);     // 8.0 - int 3 promoted to double
```

</details>

5. Why does `auto` drop `const`? How do you preserve it?

<details>
<summary>Show answer</summary>

**Direct answer:** `auto` performs type deduction using the same rules as template argument deduction, which drops top-level `const` and references. This is because you're creating a new independent variable - it shouldn't inherit constraints from the initializer. To preserve `const`, write `const auto` (or `constexpr auto`).

**Detailed explanation:**
Top-level `const` means the variable itself is const. Low-level `const` (e.g., `const int*`) is preserved because it describes what the pointer _points to_, not the pointer itself.

```cpp
const int x{ 5 };
auto y{ x };          // y is int (const dropped - y is a new copy)
const auto z{ x };    // z is const int (explicitly preserved)
auto& r{ x };         // r is const int& (reference to const - const preserved)
```

</details>

6. What does `auto s{ "hello" };` deduce to, and how do you get `std::string`?

<details>
<summary>Show answer</summary>

**Direct answer:** `auto s{ "hello" }` deduces to `const char*`, not `std::string` or `std::string_view`. To get `std::string`, use the `s` suffix: `auto s{ "hello"s }`. For `std::string_view`, use the `sv` suffix: `auto sv{ "hello"sv }`.

**Detailed explanation:**
String literals in C++ are `const char[]` arrays that decay to `const char*`. The `auto` keyword deduces the decayed type. The `s` and `sv` suffixes are user-defined literals from `<string>` and `<string_view>` respectively - you need `using namespace std::literals;` (or the specific literal namespace) to enable them.

```cpp
using namespace std::literals;
auto a{ "hello" };     // const char*
auto b{ "hello"s };    // std::string
auto c{ "hello"sv };   // std::string_view
```

</details>

7. What is a **trailing return type**, and when is it useful?

<details>
<summary>Show answer</summary>

**Direct answer:** A trailing return type uses the syntax `auto func(params) -> ReturnType` to place the return type after the parameter list instead of before the function name. It is useful in templates when the return type depends on the parameter types (which aren't yet visible in the leading position), and when the return type is complex.

**Detailed explanation:**
In C++14+, `auto` can also be used as a deduced return type (no trailing `-> Type`), where the compiler infers the type from `return` statements. However, deduced return types require the function to be fully defined before any call site - you can't forward-declare it. The trailing return syntax is an alternative that explicitly states the type while allowing it to reference parameter names.

```cpp
// Trailing return type - Type visible after params:
auto add(int a, double b) -> double
{
    return a + b;
}

// Deduced return type (C++14) - no trailing ->:
auto multiply(int a, int b)
{
    return a * b;  // compiler deduces int
}
```

</details>

8. Why are type aliases (`using`) not type-safe?

<details>
<summary>Show answer</summary>

**Direct answer:** A type alias creates a new _name_ for an existing type, but the compiler treats the alias and the original type as identical - they are freely interchangeable. A `Distance` alias for `double` can be mixed with any other `double` or `double` alias without any compiler warning.

**Detailed explanation:**
Type aliases improve readability and documentation (e.g., `using Miles = double; using Kilometers = double;`) but provide no compile-time safety. You can accidentally pass a `Miles` value to a function expecting `Kilometers` and the compiler won't complain. For true type safety, use a wrapper class (strong typedef). Prefer `using` over the older `typedef` syntax.

```cpp
using Miles = double;
using Kilometers = double;

Miles m{ 26.2 };
Kilometers k{ m };    // compiles fine - no type safety! Both are just double.
```

</details>

9. What is the difference between **implicit** and **explicit** type conversion?

<details>
<summary>Show answer</summary>

**Direct answer:** Implicit conversion (coercion) is performed automatically by the compiler when types don't match - e.g., passing an `int` to a function expecting `double`. Explicit conversion (casting) is requested by the programmer using a cast operator - e.g., `static_cast<int>(3.14)`. Implicit conversions happen silently and may be unsafe; explicit conversions document the programmer's intent.

**Detailed explanation:**
The compiler performs implicit conversions for promotions, conversions in arithmetic, function argument passing, and initialization. Explicit casts should be used when you intentionally want a conversion that would otherwise be disallowed or ambiguous. Brace initialization catches many dangerous implicit conversions by disallowing narrowing.

</details>

10. What happens when you mix signed and unsigned operands in a comparison?

<details>
<summary>Show answer</summary>

**Direct answer:** The signed operand is converted to unsigned. If the signed value is negative, it wraps around to a large positive value, making the comparison produce the wrong result. For example, `-1 < 1u` evaluates to `false` because `-1` becomes `4294967295u` (on 32-bit `unsigned`).

**Detailed explanation:**
This is one of the most common pitfalls with unsigned integers. Compilers typically warn about signed/unsigned comparison mismatches (`-Wsign-compare`). The fix is to avoid mixing signed and unsigned types - use `static_cast` to explicitly convert one operand, or use signed types consistently.

```cpp
int s{ -1 };
unsigned int u{ 1 };
if (s < u)  // FALSE! -1 converted to ~4 billion unsigned
    std::cout << "expected";  // never prints
```

</details>
