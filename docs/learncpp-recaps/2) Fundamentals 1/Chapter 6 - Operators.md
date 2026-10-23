# Chapter 6 Recap - Operators

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Use parentheses to clarify any non-trivial compound expression - don't rely on memorizing the precedence table
- Never depend on the evaluation order of operands or function arguments; it is unspecified
- Don't use a variable with a side effect (e.g., `++x`) more than once in the same statement
- Prefer prefix `++`/`--` over postfix unless you specifically need the old value
- Use `static_cast<double>()` when you need floating-point division from integer operands
- Dividing by integer `0` is undefined behavior - always guard against it
- Avoid `==` and `!=` on calculated floating-point values; use an epsilon-based comparison instead
- When comparing a remainder result, compare against `0` (not `1`) to handle negative numbers correctly

### 3 Tiny Examples

1.

```cpp
int x{ 2 + 3 * 4 };   // 14, not 20 (* has higher precedence)
int y{ (2 + 3) * 4 }; // 20 (parentheses override precedence)
```

2.

```cpp
int x{ 7 / 4 };                          // 1 (truncated)
double y{ static_cast<double>(7) / 4 };   // 1.75
```

3.

```cpp
std::cout << -7 % 4 << '\n';  // -3 (sign follows first operand)
std::cout << 7 % -4 << '\n';  //  3

#include <cmath>
double result{ std::pow(2.0, 10.0) }; // 1024.0
```

### 3 Common Mistakes

- Assuming evaluation order
- Using `x % 2 == 1` to check odd
- Integer division surprise

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Operator precedence** - determines which operators are grouped with operands first in a compound expression (higher precedence = grouped first)
- **Operator associativity** - determines grouping direction (left-to-right or right-to-left) when adjacent operators share the same precedence level
- **Integer vs. floating-point division** - integer division truncates the fraction; floating-point division preserves it
- **Remainder operator (`%`)** - returns the remainder of integer division; result takes the sign of the first operand
- **Prefix vs. postfix increment/decrement** - prefix modifies then returns the value; postfix copies, modifies, then returns the old copy
- **Side effects** - observable effects beyond producing a return value (e.g., modifying a variable, performing I/O)
- **Short-circuit evaluation** - `&&` and `||` skip evaluating the right operand when the result is already determined by the left operand
- **Conditional (ternary) operator (`?:`)** - a compact alternative to simple if-else, evaluated as an expression
- **Epsilon-based floating-point comparison** - using an absolute and/or relative epsilon to compare floats instead of `==`
- **De Morgan's laws** - `!(x && y)` ≡ `!x || !y`; `!(x || y)` ≡ `!x && !y`

### Section-by-Section Detail

### 6.1 - Operator precedence and associativity

- **Operator precedence** determines which operators are grouped with operands first in compound expressions (e.g., `*` before `+`)
- When adjacent operators share the same precedence, **associativity** (L→ R or R→ L) breaks the tie
- Precedence and associativity determine grouping, but **not** the order in which operands or function arguments are evaluated - that is mostly **unspecified**
- The C++ precedence table has **17 levels**; focus on knowing `*`/`/` bind tighter than `+`/`-`, and that assignment has very low precedence
- Use **parentheses** to make non-trivial compound expressions unambiguous - it costs nothing and prevents bugs

```cpp
int x{ 2 + 3 * 4 };   // 14, not 20 (* has higher precedence)
int y{ (2 + 3) * 4 }; // 20 (parentheses override precedence)
```

→ _See [01_PrecedenceAndAssociativity](../solutions/Chapter_06_Operators/01_PrecedenceAndAssociativity)_

**Key Precedence Levels (highest to lowest):**

| Level | Operators                                                               | Associativity | Example           |
| ----- | ----------------------------------------------------------------------- | ------------- | ----------------- | --- | --- | --- | --- |
| 1     | `::`                                                                    | L→R           | `std::cout`       |
| 2     | `()` `[]` `.` `->` `++`/`--` (postfix)                                  | L→R           | `arr[i]`, `obj.x` |
| 3     | `++`/`--` (prefix), `!`, `-` (unary), `*` (deref), `&` (addr), `sizeof` | R→L           | `!done`, `-x`     |
| 5     | `*` `/` `%`                                                             | L→R           | `a * b + c`       |
| 6     | `+` `-`                                                                 | L→R           | `x + y`           |
| 9     | `<` `<=` `>` `>=`                                                       | L→R           | `x < 10`          |
| 10    | `==` `!=`                                                               | L→R           | `x == y`          |
| 14    | `&&`                                                                    | L→R           | `a && b`          |
| 15    | `                                                                       |               | `                 | L→R | `a  |     | b`  |
| 16    | `?:` (ternary), `=`, `+=`, `-=` etc.                                    | R→L           | `x = y = 5`       |

> **Rule of thumb:** When in doubt, parenthesize. It costs nothing and prevents bugs.

### 6.2 - Arithmetic operators

- C++ provides **unary** `+`/`-` and **binary** `+`, `-`, `*`, `/`, `%` arithmetic operators
- **Integer division** truncates the fractional part; use `static_cast<double>()` on at least one operand to get floating-point division
- Dividing by integer `0` is **undefined behavior**
- **Arithmetic assignment operators** (`+=`, `-=`, `*=`, `/=`, `%=`) provide shorthand for modifying a variable
- The result type of an arithmetic operation on two same-type operands is that **same type** (e.g., `int / int` yields `int`)
- **Signed integer overflow** is undefined behavior - integer arithmetic can silently overflow

```cpp
int x{ 7 / 4 };                          // 1 (truncated)
double y{ static_cast<double>(7) / 4 };   // 1.75
```

→ _See [02_ArithmeticOperators](../solutions/Chapter_06_Operators/02_ArithmeticOperators) · [03_IntegerVsFloatingPointDivision](../solutions/Chapter_06_Operators/03_IntegerVsFloatingPointDivision)_

### 6.3 - Remainder and exponentiation

- The **`%` operator** returns the integer division remainder and only works on **integer** operands
- The result carries the **sign of the first operand**, so compare against `0` (not `1`) when checking divisibility
- C++ has **no exponent operator**; use `std::pow()` from `<cmath>` for floating-point exponentiation
- **`std::pow()`** returns a `double`, so converting back to an integer may lose precision for large values
- For **exact integer powers**, use a loop-based or `constexpr` approach to avoid floating-point rounding issues

```cpp
std::cout << -7 % 4 << '\n';  // -3 (sign follows first operand)
std::cout << 7 % -4 << '\n';  //  3

#include <cmath>
double result{ std::pow(2.0, 10.0) }; // 1024.0
```

→ _See [04_RemainderOperator](../solutions/Chapter_06_Operators/04_RemainderOperator) · [05_Exponentiation](../solutions/Chapter_06_Operators/05_Exponentiation)_

### 6.4 - Increment/decrement operators, and side effects

- **Prefix** `++x`/`--x` modifies the variable then returns the new value; **postfix** `x++`/`x--` copies the old value, modifies, then returns the old copy
- Prefer **prefix** for performance and clarity - postfix creates a temporary copy (significant for iterators and user-defined types)
- **Side effects** (like modifying a variable) can cause **undefined behavior** if a variable with a side effect is used more than once in the same statement
- **Evaluation order** between operands is unspecified, so never rely on when a side effect occurs relative to other operands
- Golden rule: do not use a variable that has a **side effect** applied more than once in a given statement

```cpp
int x{ 5 };
int y{ ++x }; // prefix: x=6, y=6
int z{ x++ }; // postfix: z=6 (old), x=7
```

→ _See [06_IncrementDecrementOperators](../solutions/Chapter_06_Operators/06_IncrementDecrementOperators) · [07_SideEffectsAndEvaluationOrder](../solutions/Chapter_06_Operators/07_SideEffectsAndEvaluationOrder)_

**Prefix vs. Postfix:**

| Form        | Syntax        | Returns                      | When Variable Changes              |
| ----------- | ------------- | ---------------------------- | ---------------------------------- |
| **Prefix**  | `++x` / `--x` | New value (after increment)  | Before the expression is evaluated |
| **Postfix** | `x++` / `x--` | Old value (before increment) | After the value is read            |

```cpp
int x{ 5 };
int a{ ++x }; // x becomes 6 first, then a = 6
int b{ x++ }; // b = 6 (old value), then x becomes 7
```

> **Best Practice:** Prefer prefix (`++x`) unless you specifically need the old value. Prefix is never slower and avoids creating an unnecessary temporary copy (matters for iterator types).

### 6.5 - The comma operator

- The **comma operator** evaluates the left operand, discards the result, then evaluates and returns the **right operand**
- It has the **lowest precedence** of all C++ operators
- It is rarely useful outside of **`for` loops** and is best avoided elsewhere because it hurts readability
- Do not confuse the **comma operator** with the comma used in function calls, variable declarations, or initializer lists - those are **syntactic commas**
- The comma operator can only appear where a **single expression** is expected

```cpp
for (int i{0}, j{10}; i < j; ++i, --j) // comma separates two side effects
    std::cout << i << ' ' << j << '\n';
```

→ _See [08_CommaOperator](../solutions/Chapter_06_Operators/08_CommaOperator)_

### 6.6 - The conditional operator

- The **ternary `?:` operator** (`condition ? exprTrue : exprFalse`) is a compact, expression-based alternative to simple if-else
- Most useful for **initialization**, **assignment**, or returning one of two values; also works in **`constexpr` contexts**
- Always **parenthesize** the entire conditional in compound expressions, and parenthesize the condition if it contains operators
- The types of the two result expressions must **match or be implicitly convertible**
- Avoid **nesting** ternary operators - deeply nested conditionals are unreadable; use an if-else chain instead

```cpp
constexpr int max{ (a > b) ? a : b };       // expression-based - works in constexpr
std::cout << ((x > 0) ? "positive" : "non-positive") << '\n';
```

→ _See [09_ConditionalOperator](../solutions/Chapter_06_Operators/09_ConditionalOperator)_

### 6.7 - Relational operators and floating-point comparisons

- The six **relational operators** (`>`, `<`, `>=`, `<=`, `==`, `!=`) return `bool`
- Avoid `==` and `!=` with **calculated floating-point values** - rounding errors make exact comparison unreliable
- For approximate equality, use an **epsilon-based approach** combining an absolute epsilon (for near-zero values) with a **relative epsilon** (Knuth's algorithm)
- The **relative epsilon** scales tolerance by operand magnitude: `std::abs(a - b) <= epsilon * std::max(std::abs(a), std::abs(b))`
- A common implementation defines an **`approximatelyEqual()`** function encapsulating this logic

```cpp
bool approximatelyEqual(double a, double b, double eps) {
    return std::abs(a - b) <= eps * std::max(std::abs(a), std::abs(b));
}
```

> **See also:** [Chapter 4 - Fundamental Data Types](Chapter%204%20-%20Fundamental%20Data%20Types.md) for floating-point precision limits.

→ _See [10_RelationalAndFloatingPointComparison](../solutions/Chapter_06_Operators/10_RelationalAndFloatingPointComparison)_

### 6.8 - Logical operators

- **`!`** (NOT), **`&&`** (AND), and **`||`** (OR) build compound conditions; `&&` has **higher precedence** than `||`, so parenthesize when mixing them
- **Short-circuit evaluation**: `&&` skips the right operand if the left is `false`; `||` skips it if the left is `true`
- Be cautious when short-circuited operands contain **side effects** (e.g., `++x` or function calls) - those effects may be skipped entirely
- Apply **De Morgan's laws** correctly: `!(a && b)` = `!a || !b`; `!(a || b)` = `!a && !b`
- C++ has no logical **XOR** operator, but `operator!=` on `bool` operands achieves the same effect
- **Logical operators** perform implicit boolean conversions - any non-zero integer or non-null pointer evaluates as `true`

```cpp
if (x > 0 && x < 100)       // AND: both must be true
    std::cout << "in range";

if (x == 0 || x == 1)       // OR: at least one must be true
    std::cout << "binary digit";

// Short-circuit: if x is 0, (y/x) is never evaluated
if (x != 0 && (y / x) > 2)  { /* safe */ }
```

→ _See [11_LogicalOperatorsAndShortCircuit](../solutions/Chapter_06_Operators/11_LogicalOperatorsAndShortCircuit) · [12_CommonPitfalls](../solutions/Chapter_06_Operators/12_CommonPitfalls)_

### Edge Cases and Caveats

- **Assuming evaluation order** - function argument order is unspecified.

  ❌ **Bad:**

  ```cpp
  printCalc(getValue(), getValue(), getValue()); // order unknown
  ```

  ✅ **Good:** Store results in named variables first.

- **Using `x % 2 == 1` to check odd** - fails for negative numbers.

  ❌ **Bad:** `if (x % 2 == 1)` - `-7 % 2` is `-1`, not `1`.
  ✅ **Good:** `if (x % 2 != 0)`

- **Integer division surprise** - both operands are `int`, fraction is dropped.

  ❌ **Bad:** `double d{ 7 / 4 };` - d is `1.0`, not `1.75`.
  ✅ **Good:** `double d{ static_cast<double>(7) / 4 };`

- **Dividing by zero** - integer division by `0` is undefined behavior.

  ❌ **Bad:** `int result{ x / y };` without checking y.
  ✅ **Good:** Guard with `if (y != 0)` before dividing.

- **Confusing `=` with `==`** - assignment in conditions.

  ❌ **Bad:** `if (x = 5)` - assigns, always true.
  ✅ **Good:** `if (x == 5)`

- **Misusing `!` precedence** - `!x > y` is `(!x) > y`.

  ❌ **Bad:** `!x > y`
  ✅ **Good:** `!(x > y)`

- **Forgetting to parenthesize `?:`** - `<<` has higher precedence.

  ❌ **Bad:** `std::cout << (x < 0) ? "neg" : "pos";`
  ✅ **Good:** `std::cout << ((x < 0) ? "neg" : "pos");`

- **Distributing `!` incorrectly** - De Morgan's law.

  ❌ **Bad:** `!(a && b)` ≠ `!a && !b`
  ✅ **Good:** `!(a && b)` ≡ `!a || !b`

- **Mixing `&&` and `||` without parentheses** - `&&` binds tighter.

  ❌ **Bad:** `a || b && c` → `a || (b && c)`
  ✅ **Good:** `(a || b) && c` if that's the intent.

- **Side effects in short-circuited expressions** - right operand may be skipped.

  ❌ **Bad:** `if (x == 1 && ++y == 2)` - `++y` skipped when `x != 1`.
  ✅ **Good:** Increment `y` on its own statement.

- **Comparing floats with `==`** - rounding errors accumulate.

  ❌ **Bad:** `if (0.1 + 0.2 == 0.3)`
  ✅ **Good:** Use `approximatelyEqual()` with an epsilon.

---

### Hands-On Code Projects

| #   | Project                                                                                                               | Concept                                         |
| --- | --------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------- |
| 01  | [01_PrecedenceAndAssociativity](../solutions/Chapter_06_Operators/01_PrecedenceAndAssociativity)                     | Precedence levels, associativity, parentheses   |
| 02  | [02_ArithmeticOperators](../solutions/Chapter_06_Operators/02_ArithmeticOperators)                                   | Unary/binary arithmetic, `+=` shorthand         |
| 03  | [03_IntegerVsFloatingPointDivision](../solutions/Chapter_06_Operators/03_IntegerVsFloatingPointDivision)             | Truncation vs fractional results, `static_cast` |
| 04  | [04_RemainderOperator](../solutions/Chapter_06_Operators/04_RemainderOperator)                                       | `%` sign behavior, divisibility checking        |
| 05  | [05_Exponentiation](../solutions/Chapter_06_Operators/05_Exponentiation)                                             | `std::pow()` vs custom integer power            |
| 06  | [06_IncrementDecrementOperators](../solutions/Chapter_06_Operators/06_IncrementDecrementOperators)                   | Prefix vs postfix, performance                  |
| 07  | [07_SideEffectsAndEvaluationOrder](../solutions/Chapter_06_Operators/07_SideEffectsAndEvaluationOrder)               | Unspecified evaluation order, UB                |
| 08  | [08_CommaOperator](../solutions/Chapter_06_Operators/08_CommaOperator)                                               | Comma operator in `for` loops                   |
| 09  | [09_ConditionalOperator](../solutions/Chapter_06_Operators/09_ConditionalOperator)                                   | Ternary `?:`, parenthesization                  |
| 10  | [10_RelationalAndFloatingPointComparison](../solutions/Chapter_06_Operators/10_RelationalAndFloatingPointComparison) | Relational ops, epsilon comparison              |
| 11  | [11_LogicalOperatorsAndShortCircuit](../solutions/Chapter_06_Operators/11_LogicalOperatorsAndShortCircuit)           | `!`, `&&`, `\|\|`, short-circuit, De Morgan's   |
| 12  | [12_CommonPitfalls](../solutions/Chapter_06_Operators/12_CommonPitfalls)                                             | `=` vs `==`, `!` precedence, `?:` grouping      |

### Quick Reference

| Topic                                   | Details                                                                                                                                                                                                           |
| --------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Operator Precedence (key levels)**    | Highest → lowest (selected): `()` → unary `+`/`-`/`!`/`++`/`--` → `*`/`/`/`%` → `+`/`-` → `<`/`<=`/`>`/`>=` → `==`/`!=` → `&&` → `\|\|` → `?:` → `=`/`+=`/`-=` → `,`                                              |
| **Arithmetic Operators**                | Unary: `+x`, `-x`. Binary: `x + y`, `x - y`, `x * y`, `x / y`, `x % y`. Assignment shorthand: `+=`, `-=`, `*=`, `/=`, `%=`                                                                                        |
| **Integer vs. Floating-Point Division** | `7 / 4` → `1` (truncated). `7.0 / 4` or `static_cast<double>(7) / 4` → `1.75`. At least one operand must be floating-point to get a fractional result                                                             |
| **Remainder Operator Rules**            | `%` works on integers only. Result sign matches the **first** operand: `-7 % 4` → `-3`, `7 % -4` → `3`. Check divisibility with `x % n == 0`, not `== 1`                                                          |
| **Increment / Decrement**               | Prefix `++x`: increments then returns new value. Postfix `x++`: copies old value, increments, returns old copy. Prefer prefix unless the old value is needed                                                      |
| **Conditional (Ternary) Operator**      | Syntax: `condition ? exprTrue : exprFalse`. Always parenthesize in compound expressions. Both result expressions must have compatible types                                                                       |
| **Logical Operators & Short-Circuit**   | `!` (NOT), `&&` (AND, higher prec.), `\|\|` (OR, lower prec.). `&&` short-circuits on `false`; `\|\|` short-circuits on `true`. De Morgan's: `!(a && b)` ≡ `!a \|\| !b`, `!(a \|\| b)` ≡ `!a && !b`               |
| **Floating-Point Comparison**           | Avoid `==`/`!=` on calculated floats. Use absolute epsilon for near-zero values: `std::abs(a - b) <= epsilon`. Use relative epsilon (Knuth): `std::abs(a - b) <= maxEpsilon * std::max(std::abs(a), std::abs(b))` |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is the difference between operator **precedence** and **associativity**?

<details>
<summary>Show answer</summary>

**Direct answer:** Precedence determines which operator is applied first when different operators appear in the same expression (e.g., `*` before `+`). Associativity determines the grouping order when adjacent operators have the _same_ precedence (e.g., `a - b - c` is left-to-right: `(a - b) - c`). Neither controls the order in which operands are _evaluated_ - that is mostly unspecified.

**Detailed explanation:**
The C++ precedence table has 17 levels. You don't need to memorize them all - know that multiplication/division bind tighter than addition/subtraction, and that assignment has very low precedence. When in doubt, use parentheses to make grouping explicit - it costs nothing and prevents bugs.

</details>

2. Why does `7 / 4` evaluate to `1`? How do you get `1.75`?

<details>
<summary>Show answer</summary>

**Direct answer:** `7 / 4` performs integer division because both operands are `int`. Integer division truncates the fractional part (drops it, does not round), producing `1`. To get `1.75`, cast at least one operand to `double`: `static_cast<double>(7) / 4` produces `1.75`.

**Detailed explanation:**
The result type of an arithmetic operation matches its operands. If both are `int`, the result is `int`. If either operand is `double`, the other is promoted to `double` and the result is `double`. Dividing by integer `0` is undefined behavior. You can also write `7.0 / 4` or `7 / 4.0` to make one operand a floating-point literal, but `static_cast` is more explicit and works with variables.

```cpp
std::cout << 7 / 4;                          // prints 1 (integer division)
std::cout << static_cast<double>(7) / 4;     // prints 1.75
```

</details>

3. What is the result of `-7 % 4`? Why does `x % 2 == 1` fail for negative odd numbers?

<details>
<summary>Show answer</summary>

**Direct answer:** `-7 % 4` evaluates to `-3`, because the remainder operator `%` carries the sign of the first (left) operand. `x % 2 == 1` fails for negative odd numbers because `-7 % 2` is `-1`, not `1`. The correct way to check for odd is `x % 2 != 0`.

**Detailed explanation:**
The `%` operator returns the integer division remainder and only works with integer operands. Since the sign follows the dividend (first operand), negative values produce negative remainders. Testing `x % 2 == 1` only catches positive odd numbers; negative odd numbers produce `-1`. Using `x % 2 != 0` correctly identifies all odd numbers regardless of sign.

```cpp
std::cout << -7 % 4;    // prints -3 (sign follows left operand)
std::cout << -7 % 2;    // prints -1 (not 1!)

// Correct odd check:
if (x % 2 != 0) { /* x is odd */ }
```

</details>

4. Explain the difference between **prefix** and **postfix** increment.

<details>
<summary>Show answer</summary>

**Direct answer:** Prefix `++x` increments the variable first, then returns the incremented value. Postfix `x++` copies the current value, increments the variable, then returns the _old_ (pre-increment) copy. Prefer prefix for clarity and performance (postfix creates a temporary copy, which matters for iterators and user-defined types).

**Detailed explanation:**
For built-in types, the performance difference is negligible. For user-defined iterators and objects, prefix avoids creating a temporary copy, which can be significant. The golden rule: do not use a variable that has a side effect (like `++`) applied more than once in a single statement - evaluation order between operands is unspecified, making the result undefined behavior.

```cpp
int x{ 5 };
int a{ ++x };   // x becomes 6, a is 6 (prefix - increment first)
int b{ x++ };   // b is 6 (old value), x becomes 7 (postfix - copy then increment)
```

</details>

5. What is **short-circuit evaluation**, and what risks does it create with side effects?

<details>
<summary>Show answer</summary>

**Direct answer:** Short-circuit evaluation means that `&&` and `||` skip evaluating the right operand if the left operand alone determines the result. For `&&`, if the left is `false`, the right is skipped. For `||`, if the left is `true`, the right is skipped. The risk is that if the right operand has side effects (like `++x` or a function call), those side effects may not execute, leading to unexpected behavior.

**Detailed explanation:**
Short-circuit evaluation is a feature, not a bug - it enables patterns like `ptr != nullptr && ptr->value > 0`, where the second check is only safe if the first succeeds. However, relying on side effects in the skipped operand is dangerous:

```cpp
int x{ 0 };
if (true || ++x)  // ++x is NEVER executed because true || anything is true
    std::cout << x; // prints 0, not 1!
```

</details>

6. Rewrite `!(a || b)` using De Morgan's law.

<details>
<summary>Show answer</summary>

**Direct answer:** `!(a || b)` is equivalent to `!a && !b`. De Morgan's laws state: `!(a || b)` = `!a && !b`, and `!(a && b)` = `!a || !b`. The negation swaps `&&`/`||` and negates each operand.

**Detailed explanation:**
De Morgan's laws are essential for simplifying complex boolean expressions and for understanding how negation distributes. A common mistake is to distribute `!` without flipping the operator - `!(a || b)` is _not_ `!a || !b`. The correct transformation always flips AND to OR and vice versa.

```cpp
// These are equivalent:
if (!(a || b)) { }
if (!a && !b) { }

// These are equivalent:
if (!(a && b)) { }
if (!a || !b) { }
```

</details>

7. Why should you parenthesize a `?:` expression used inside `<<`?

<details>
<summary>Show answer</summary>

**Direct answer:** The conditional operator `?:` has very low precedence - lower than `<<`. Without parentheses, `std::cout << x ? "yes" : "no"` is parsed as `(std::cout << x) ? "yes" : "no"`, which outputs `x`, then uses the resulting stream object as the condition. You must write `std::cout << (x ? "yes" : "no")` to get the intended behavior.

**Detailed explanation:**
The ternary operator is most useful for initialization, assignment, or returning one of two values. Always parenthesize the entire conditional expression in larger statements, and parenthesize the condition itself if it contains operators. Avoid nesting ternary operators - deeply nested conditionals are unreadable; use an if-else chain instead.

```cpp
// BAD - parsed as (std::cout << isHappy) ? "smile" : "frown"
std::cout << isHappy ? "smile" : "frown";

// GOOD - prints "smile" or "frown"
std::cout << (isHappy ? "smile" : "frown");
```

</details>

8. Describe the **Knuth epsilon** approach to floating-point comparison.

<details>
<summary>Show answer</summary>

**Direct answer:** The Knuth epsilon approach uses a _relative_ epsilon that scales with the magnitude of the values being compared. Two values `a` and `b` are approximately equal if their absolute difference is less than or equal to `epsilon * max(|a|, |b|)`. This handles both very large and very small values correctly, unlike a fixed absolute epsilon.

**Detailed explanation:**
A fixed absolute epsilon (e.g., `0.00001`) works for values near zero but fails for very large numbers. The Knuth approach scales the tolerance proportionally. A robust implementation combines both absolute and relative epsilon: use the absolute epsilon when values are near zero, and the relative epsilon otherwise. Avoid `==` and `!=` entirely with calculated floating-point values.

```cpp
bool approximatelyEqual(double a, double b, double relEpsilon)
{
    return std::abs(a - b) <= relEpsilon * std::max(std::abs(a), std::abs(b));
}
```

</details>

9. What are the arithmetic assignment operators, and why are they useful?

<details>
<summary>Show answer</summary>

**Direct answer:** Arithmetic assignment operators (`+=`, `-=`, `*=`, `/=`, `%=`) combine an arithmetic operation with assignment. `x += 5` is equivalent to `x = x + 5` but more concise and avoids evaluating `x` twice (which matters when `x` is a complex expression).

**Detailed explanation:**
These operators are shorthand that reduces typing and makes the intent clearer - "add 5 to x" vs. "set x to x plus 5." The same pattern exists for bitwise operators (`<<=`, `>>=`, `&=`, `|=`, `^=`). They are especially useful in loops and accumulation patterns.

</details>

10. What is a **side effect**, and why is using a variable with side effects more than once in a statement dangerous?

<details>
<summary>Show answer</summary>

**Direct answer:** A side effect is any observable consequence of an operator or function beyond producing a return value - e.g., `=` modifies a variable, `<<` writes to the console, `++x` modifies `x`. Using a variable with side effects more than once in the same statement is dangerous because the order of evaluation between operands is mostly unspecified - the result is undefined behavior.

**Detailed explanation:**
In `x = ++x + x++`, the compiler is free to evaluate the subexpressions in any order, producing different results on different compilers or even different optimization levels. The golden rule: do not use a variable that has a side effect applied to it more than once in a given statement.

```cpp
int x{ 5 };
int y{ ++x + ++x }; // undefined behavior - x modified twice in one expression
```

</details>
