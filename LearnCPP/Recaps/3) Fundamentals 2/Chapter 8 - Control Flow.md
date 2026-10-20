# Chapter 8 Recap - Control Flow

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Use blocks (`{}`) with `if`/`else` to prevent dangling-else bugs and accidental unconditional execution
- Favor `if constexpr` when the condition is a constant expression
- Prefer `switch` over long `if-else` chains when testing one integral/enum expression for equality
- Always end each `switch` case with `break` or `return`; use `[[fallthrough]];` for intentional fallthrough
- Wrap variable declarations inside `switch` cases in their own block
- Avoid `goto`; use structured loops and conditionals instead
- Use `for` loops when a counter variable exists; use `while` loops when there is no obvious counter
- Favor `while(true)` for intentional infinite loops

### 3 Tiny Examples

1.

```cpp
if (x > 0)
{
    std::cout << "positive\n";
}
else
{
    std::cout << "non-positive\n";
}
```

2.

```cpp
if constexpr (sizeof(int) == 4)
    std::cout << "int is 4 bytes"; // dead branch discarded at compile time
```

3.

```cpp
switch (day)
{
    case 1: std::cout << "Monday";  break;
    case 2: std::cout << "Tuesday"; break;
    default: std::cout << "Other";  break;
}
```

### 3 Common Mistakes

- Forgetting blocks after `if`/`else`
- Null statement after `if`
- Using `=` instead of `==`

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Execution path** - the specific sequence of statements the CPU executes in a program
- **Branching** - when a control flow statement causes execution to jump to a non-sequential statement
- **Conditional statements** - `if`/`else` and `switch`/`case` for choosing which code to run
- **Dangling else** - ambiguity when an `else` could match more than one `if`; resolves to the last unmatched `if` in the same block
- **Null statement** - a lone semicolon (`;`) that does nothing; can cause subtle bugs after `if` or `while`
- **Fallthrough** - when execution in a `switch` flows from one `case` into the next without a `break`/`return`
- **Loop variable / counter** - a variable that tracks how many times a loop has iterated
- **Infinite loop** - a loop whose condition never becomes `false`
- **Off-by-one error** - iterating one too many or one too few times
- **PRNG (Pseudo-Random Number Generator)** - an algorithm that produces a deterministic but seemingly random sequence from a **seed**
- **Underseeding** - providing fewer seed bits than the PRNG's state size, reducing output quality

### Section-by-Section Detail

### 8.1 - Control flow introduction

- An **execution path** is the specific sequence of statements the CPU executes in a running program
- **Straight-line programs** always run the same statements in the same order, making them predictable but limited
- **Control flow statements** alter the execution path so programs can make decisions, repeat work, and respond to input
- C++ provides five control flow categories: **conditional** (`if`, `switch`), **jumps** (`goto`, `break`, `continue`), **loops** (`for`, `while`, `do-while`), **halts** (`std::exit`, `std::abort`), and **exceptions**
- Without control flow, programs could not validate input, iterate over data, or handle errors

### 8.2 - If statements and blocks

- `if`/`else` executes a branch based on a condition; only a **single statement** follows each branch unless you use a **block** (`{}`)
- Always use **explicit blocks** to avoid accidental unconditional execution of subsequent statements
- An **if-else chain** treats conditions as **mutually exclusive** (only one branch runs)
- Consecutive **independent `if` statements** treat each condition separately (multiple may run)
- **Implicit blocks** exist around single statements, but explicit `{}` is the best practice

```cpp
if (x > 0)
{
    std::cout << "positive\n";
}
else
{
    std::cout << "non-positive\n";
}
```

→ _See [01_IfStatementsAndBlocks](../solutions/Chapter_08_Control_Flow/01_IfStatementsAndBlocks/)_

### 8.3 - Common if statement problems

- The **dangling else** problem occurs when nested `if` statements lack braces - `else` pairs with the **last unmatched `if`** in the same block
- Fix dangling else by always using **explicit blocks** (`{}`) so pairing is unambiguous
- A **null statement** (`;` after `if (condition);`) silently terminates the conditional, causing the next line to execute **unconditionally**
- Using **`=` instead of `==`** in a condition assigns the value rather than comparing
- Flatten **deeply nested `if`** statements using `else if` chains or **logical operators** (`&&`, `||`)
- Enable high **warning levels** in your compiler to catch accidental assignment

→ _See [02_CommonIfProblems](../solutions/Chapter_08_Control_Flow/02_CommonIfProblems/) · [03_IfElseChains](../solutions/Chapter_08_Control_Flow/03_IfElseChains/)_

### 8.4 - Constexpr if statements

- `if constexpr` (C++17) evaluates the condition at **compile time** and **discards the untaken branch** entirely
- The discarded branch is not compiled, so it doesn't need to be valid code for the given **template instantiation**
- The condition must be a **constant expression** (e.g., `sizeof(T) == 4`, a `constexpr` variable, or a type trait)
- There is **zero runtime overhead** - no branch prediction, no dead code in the binary
- Unlike preprocessor `#if`, `if constexpr` respects **scoping**, works with templates, and is **type-safe**
- In non-template functions, both branches must still be **syntactically valid** since types are fully known

```cpp
if constexpr (sizeof(int) == 4)
    std::cout << "int is 4 bytes"; // dead branch discarded at compile time
```

> **See also:** [Chapter F - Constexpr Functions](Chapter%20F%20-%20Constexpr%20Functions.md) for compile-time evaluation.

→ _See [04_ConstexprIf](../solutions/Chapter_08_Control_Flow/04_ConstexprIf/)_

### 8.5 - Switch statement basics

- `switch` evaluates an **integral or enum expression** once and jumps to the matching `case` label
- It is **cleaner and often faster** than long `if-else` chains for equality tests on discrete values
- Each case should end with `break` or `return` to prevent **fallthrough**
- The `default` label handles **unmatched values** and is conventionally placed last
- The switch expression must be an **integral type** (including `char` and enums) - not floating-point or string

```cpp
switch (day)
{
    case 1: std::cout << "Monday";  break;
    case 2: std::cout << "Tuesday"; break;
    default: std::cout << "Other";  break;
}
```

→ _See [05_SwitchBasics](../solutions/Chapter_08_Control_Flow/05_SwitchBasics/)_

**`switch` vs `if-else` chain:**

| Aspect           | `switch`                                            | `if-else` chain                                       |
| ---------------- | --------------------------------------------------- | ----------------------------------------------------- |
| Tests            | Equality on single integral/enum value              | Any condition (ranges, complex logic, multiple types) |
| Clarity          | Cleaner for many discrete cases                     | More flexible for complex conditions                  |
| Fallthrough      | Requires explicit `break`; can skip unintentionally | Each `else if` is independent                         |
| Type restriction | Integral and enum types only                        | Any type with == or logical ops                       |
| Performance      | Often faster (compiler may use jump table)          | Sequential conditional branches                       |

### 8.6 - Switch fallthrough and scoping

- Without `break`/`return`, execution **falls through** from one `case` into the next
- Use `[[fallthrough]];` (C++17 attribute) to mark **intentional fallthrough** explicitly
- **Stacked case labels** sharing the same body are fine and are not considered fallthrough
- Variables declared inside a `switch` without a block may cause **jump-past-initialization** errors
- Wrap variable declarations in case bodies inside **explicit blocks** (`{}`) to create a proper scope

```cpp
case 1:
    doA();
    [[fallthrough]];  // intentional fallthrough (C++17)
case 2:
case 3:               // stacked labels - not fallthrough
{
    int x{ 5 };       // variables need their own block
    doB();
    break;
}
```

→ _See [06_SwitchFallthroughAndScoping](../solutions/Chapter_08_Control_Flow/06_SwitchFallthroughAndScoping/)_

### 8.7 - Goto statements

- `goto` performs an **unconditional jump** to a **statement label** (e.g., `end:`) within the same function
- Statement labels have **function scope** - you can jump forward or backward regardless of block nesting
- You **cannot jump over** the initialization of a variable; the compiler will error
- `goto` produces tangled **"spaghetti code"** - avoid it in favor of structured constructs
- The one accepted use is breaking out of **deeply nested loops**, though refactoring with `return` is cleaner

→ _See [07_GotoStatements](../solutions/Chapter_08_Control_Flow/07_GotoStatements/)_

### 8.8 - Introduction to loops and while statements

- `while` loops repeat a statement **as long as the condition is `true`**, checked **before each iteration**
- A `while` loop may execute **zero times** if the condition is initially `false`
- Use `while(true)` for **intentional infinite loops**; avoid accidental semicolons after `while`
- **Loop variables** should be **signed integers** to avoid unsigned wrap-around bugs
- Loops can be **nested**, with no limit on depth

```cpp
int count{ 5 };
while (count > 0)
{
    std::cout << count << ' ';
    --count;
} // prints: 5 4 3 2 1
```

→ _See [08_WhileLoops](../solutions/Chapter_08_Control_Flow/08_WhileLoops/)_

### 8.9 - Do while statements

- `do-while` guarantees the body executes **at least once** because the condition is checked **after** the body
- Ideal for **input-validation loops** where you must prompt and read before you can validate
- The syntax requires a **semicolon** after `while (condition);` - easy to forget
- **Prefer `while`** when either loop type works equally well, since the condition at the bottom obscures intent
- Reserve `do-while` for cases where executing the body first is **semantically necessary**

```cpp
int choice{};
do
{
    std::cout << "Enter 1, 2, or 3: ";
    std::cin >> choice;
} while (choice < 1 || choice > 3); // repeats until valid
```

→ _See [09_DoWhileLoops](../solutions/Chapter_08_Control_Flow/09_DoWhileLoops/)_

### 8.10 - For statements

- `for (init; condition; end-expression)` is preferred when the **number of iterations is known** or a counter is involved
- Declaring the loop variable in the **init-statement** (e.g., `int i{ 0 }`) limits its scope to the loop
- Prefer `<` over `!=` in the condition (e.g., `i < count`) to guard against **off-by-one errors**
- The **init-statement** runs once, the **condition** is checked before each iteration, and the **end-expression** runs after each body
- Any or all parts of the `for` header can be omitted (e.g., `for (;;)` creates an infinite loop)
- **For-each loops** (`for (auto x : container)`) are covered separately and preferred for iterating all elements

```cpp
for (int i{ 0 }; i < 5; ++i) // prefer < over !=
    std::cout << i << ' ';
```

→ _See [10_ForLoops](../solutions/Chapter_08_Control_Flow/10_ForLoops/)_

**Loop Comparison:**

| Feature                    | `for`                   | `while`                   | `do-while`               |
| -------------------------- | ----------------------- | ------------------------- | ------------------------ |
| **Iteration count known?** | Yes (preferred)         | No / conditional          | No / at least one        |
| **Condition check**        | Before each iteration   | Before each iteration     | After each iteration     |
| **Runs 0 times?**          | Possible                | Possible                  | Never (always runs once) |
| **Counter scope**          | Declared in loop header | Declared outside          | Declared outside         |
| **Best for**               | Counted iteration       | General conditional loops | Input validation         |

### 8.11 - Break and continue

- `break` exits the **innermost loop or `switch`**; `continue` skips to the **next iteration**
- In a `for` loop, `continue` still executes the **end-expression** before re-checking the condition
- Be careful with `continue` in `while`/`do-while` - it can **skip the counter update** and cause an infinite loop
- **Early returns** are the function-level equivalent of `break`
- Use `break` and `continue` judiciously to simplify loop logic without obscuring control flow

```cpp
for (int i{ 0 }; i < 10; ++i)
{
    if (i == 5) break;     // exits loop when i is 5
    if (i % 2 == 0) continue; // skips even numbers
    std::cout << i << ' ';  // prints: 1 3
}
```

→ _See [11_BreakAndContinue](../solutions/Chapter_08_Control_Flow/11_BreakAndContinue/)_

### 8.12 - Halts (exiting your program early)

- `std::exit()` terminates the program "normally" - calls `atexit` handlers, flushes I/O, but does **not** destroy local objects
- `std::atexit()` registers cleanup functions called during **normal termination** via `std::exit()`
- `std::abort()` terminates **abnormally** with **no cleanup** - no destructors, no handlers, no buffer flushing
- Prefer returning error codes to `main()` or using **exceptions** over halts, since those properly unwind the stack
- Halts should be a **last resort** in well-structured programs

> **See also:** [Chapter 27 - Exceptions](Chapter%2027%20-%20Exceptions.md) for structured error handling.

→ _See [12_Halts](../solutions/Chapter_08_Control_Flow/12_Halts/)_

### 8.13 - Introduction to random number generation

- A **PRNG** (Pseudo-Random Number Generator) is a deterministic algorithm that produces seemingly random numbers from an internal **state** set by a **seed**
- The same seed always produces the **same sequence**, which is useful for **reproducibility** in testing
- Key PRNG quality criteria: **uniform distribution**, long **period**, non-predictability, and efficiency
- **Mersenne Twister** (`std::mt19937` / `std::mt19937_64`) has a period of 2^19937 - 1 but is **not cryptographically secure**
- For cryptographic randomness, use a platform-specific **CSPRNG** or a dedicated library

→ _See [13_MersenneTwisterRandom](../solutions/Chapter_08_Control_Flow/13_MersenneTwisterRandom/)_

### 8.14 - Generating random numbers using Mersenne Twister

- Pair `std::mt19937` with `std::uniform_int_distribution` (or `std::uniform_real_distribution`) to generate numbers in a **desired range**
- Seed the PRNG **exactly once** at startup using `std::random_device{}()` (OS entropy pool) - reseeding inside loops produces correlated output
- Mersenne Twister's state is **624 x 32-bit integers** (19937 bits), but a single `std::random_device` call provides only **32 bits** - this is **underseeding**
- Use `std::seed_seq` initialized with **8+ `std::random_device` values** to mitigate underseeding
- Do **not** use `std::rand()` and `srand()` - they have a small period, poor distribution, and global state

```cpp
#include <random>
std::mt19937 mt{ std::random_device{}() };
std::uniform_int_distribution die{ 1, 6 };
std::cout << die(mt) << '\n'; // random number in [1, 6]
```

→ _See [13_MersenneTwisterRandom](../solutions/Chapter_08_Control_Flow/13_MersenneTwisterRandom/) · [14_GlobalRandomHeader](../solutions/Chapter_08_Control_Flow/14_GlobalRandomHeader/)_

### 8.15 - Global random numbers (Random.h)

- A header-only `Random` namespace wraps a global **`inline std::mt19937`** that self-seeds via `std::seed_seq` on first use
- Making the PRNG `inline` (C++17) ensures **exactly one instance** across all translation units
- The convenience function `Random::get(min, max)` lets any file generate random numbers **without setup**
- This design **centralizes seeding**, avoids global-state issues of `std::rand()`/`srand()`, and keeps calling code clean
- The header is a reusable utility for **consistent random generation** across projects

→ _See [14_GlobalRandomHeader](../solutions/Chapter_08_Control_Flow/14_GlobalRandomHeader/)_

### Edge Cases and Caveats

- **Forgetting blocks after `if`/`else`** - only the first statement is conditional.

  ❌ **Bad:**

  ```cpp
  if (x > 0)
      std::cout << "positive";
      doSomething(); // always runs!
  ```

  ✅ **Good:** Always wrap in `{ }`.

- **Null statement after `if`** - `if (cond);` does nothing.

  ❌ **Bad:** `if (x > 0); doSomething();` - always executes.
  ✅ **Good:** `if (x > 0) doSomething();`

- **Using `=` instead of `==`** in a condition.

  ❌ **Bad:** `if (x = 5)` - assigns 5, always true.
  ✅ **Good:** `if (x == 5)`

- **Missing `break` in `switch` cases** - causes unintended fallthrough.

  ❌ **Bad:**

  ```cpp
  case 1: doA(); // falls through to case 2!
  case 2: doB(); break;
  ```

  ✅ **Good:** End each `case` with `break`; use `[[fallthrough]];` if intentional.

- **Initializing variables inside `switch` without a block** - jump past init.

  ❌ **Bad:** `case 1: int y{0}; break;`
  ✅ **Good:** `case 1: { int y{0}; break; }`

- **Unsigned loop variables** - decrementing past zero wraps to `UINT_MAX`.

  ❌ **Bad:** `for (unsigned int i{10}; i >= 0; --i)` - infinite loop!
  ✅ **Good:** `for (int i{10}; i >= 0; --i)`

- **Using `!=` instead of `<` in for-loop conditions** - may miss the target.

  ❌ **Bad:** `for (int i{0}; i != 10; i += 3)` - never terminates (3,6,9,12…).
  ✅ **Good:** `for (int i{0}; i < 10; i += 3)`

- **`continue` in `while` skipping counter update** - infinite loop.

  ❌ **Bad:**

  ```cpp
  while (i < 10) { if (skip) continue; ++i; } // i never increments
  ```

  ✅ **Good:** Use a `for` loop, or increment before `continue`.

- **Re-seeding the PRNG every call** - poor randomness.

  ❌ **Bad:** Creating `std::mt19937` inside a loop.
  ✅ **Good:** Create and seed once (`static` local or global `inline`).

- **Dangling else** - `else` pairs with last unmatched `if`.

  ❌ **Bad:**

  ```cpp
  if (a) if (b) doX(); else doY(); // else belongs to inner if!
  ```

  ✅ **Good:** Use explicit `{ }` to clarify intent.

---

### Hands-On Code Projects

| #   | Project                                                                                                | Concept                                        |
| --- | ------------------------------------------------------------------------------------------------------ | ---------------------------------------------- |
| 01  | [01_IfStatementsAndBlocks](../solutions/Chapter_08_Control_Flow/01_IfStatementsAndBlocks/)             | `if`/`else` with explicit blocks               |
| 02  | [02_CommonIfProblems](../solutions/Chapter_08_Control_Flow/02_CommonIfProblems/)                       | Dangling else, null statements, `=` vs `==`    |
| 03  | [03_IfElseChains](../solutions/Chapter_08_Control_Flow/03_IfElseChains/)                               | Flattening nested conditionals                 |
| 04  | [04_ConstexprIf](../solutions/Chapter_08_Control_Flow/04_ConstexprIf/)                                 | Compile-time branching (C++17)                 |
| 05  | [05_SwitchBasics](../solutions/Chapter_08_Control_Flow/05_SwitchBasics/)                               | `switch`/`case`/`default`                      |
| 06  | [06_SwitchFallthroughAndScoping](../solutions/Chapter_08_Control_Flow/06_SwitchFallthroughAndScoping/) | `[[fallthrough]]`, variable scoping            |
| 07  | [07_GotoStatements](../solutions/Chapter_08_Control_Flow/07_GotoStatements/)                           | `goto`, statement labels                       |
| 08  | [08_WhileLoops](../solutions/Chapter_08_Control_Flow/08_WhileLoops/)                                   | `while`, infinite loops, nested loops          |
| 09  | [09_DoWhileLoops](../solutions/Chapter_08_Control_Flow/09_DoWhileLoops/)                               | `do-while` for input validation                |
| 10  | [10_ForLoops](../solutions/Chapter_08_Control_Flow/10_ForLoops/)                                       | `for` loop syntax, off-by-one guards           |
| 11  | [11_BreakAndContinue](../solutions/Chapter_08_Control_Flow/11_BreakAndContinue/)                       | `break`, `continue`, early returns             |
| 12  | [12_Halts](../solutions/Chapter_08_Control_Flow/12_Halts/)                                             | `std::exit()`, `std::atexit()`, `std::abort()` |
| 13  | [13_MersenneTwisterRandom](../solutions/Chapter_08_Control_Flow/13_MersenneTwisterRandom/)             | `std::mt19937`, seeding, distributions         |
| 14  | [14_GlobalRandomHeader](../solutions/Chapter_08_Control_Flow/14_GlobalRandomHeader/)                   | Reusable `Random.h` header                     |

### Quick Reference

### if / else

```cpp
if (condition)          // single statement - prefer blocks instead
    statement;

if (condition)
{
    // block - always preferred
}
else if (otherCondition)
{
    // chained condition
}
else
{
    // fallback
}

// C++17 - dead branch discarded at compile time
if constexpr (constexprCondition) { /* ... */ }
```

### switch

```cpp
switch (integralOrEnumExpr)
{
    case value1:
        // ...
        break;
    case value2:
    case value3:       // stacked labels - not fallthrough
        // ...
        [[fallthrough]];  // intentional fallthrough (C++17 attribute)
    case value4:
        // ...
        break;
    default:
        // ...
        break;
}
```

### Loops

```cpp
while (condition) { /* pre-check */ }

do { /* post-check - at least once */ } while (condition);

for (int i{0}; i < n; ++i) { /* counted */ }

while (true) { /* intentional infinite loop - preferred form */ }
```

### break / continue / goto

```cpp
break;               // exits innermost loop or switch
continue;            // skips to next iteration (for-loop end-expr still runs)
goto label;          // unconditional jump within function (avoid)
label: statement;    // target of goto - function scope
```

### Random numbers (Mersenne Twister)

```cpp
#include <random>

// Basic setup
std::mt19937 mt{ std::random_device{}() };
std::uniform_int_distribution dist{ 1, 6 };  // range [1, 6]
int roll{ dist(mt) };

// Better seeding via seed_seq (reduces underseeding)
std::random_device rd;
std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
std::mt19937 mt2{ ss };
```

### Halts

| Function          | Behavior                                                              |
| ----------------- | --------------------------------------------------------------------- |
| `std::exit(code)` | Normal termination; calls `atexit` handlers; **no** local destructors |
| `std::atexit(fn)` | Registers cleanup function called on `exit()`                         |
| `std::abort()`    | Abnormal termination; **no** cleanup at all                           |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is a **dangling else**, and how do you prevent it?

<details>
<summary>Show answer</summary>

**Direct answer:** A dangling else occurs when nested `if` statements lack braces - the `else` always pairs with the closest unmatched `if`, which may not be the one the programmer intended. Prevent it by always using explicit braces `{}` on all `if`/`else` bodies.

**Detailed explanation:**
Without braces, the pairing is purely syntactic - the compiler doesn't care about indentation. This bug is subtle because the code _looks_ correct based on whitespace. Using braces on every `if`/`else` body eliminates all ambiguity.

```cpp
// BUG - else pairs with inner if, not outer:
if (x > 0)
    if (y > 0)
        std::cout << "both positive";
else                      // paired with "if (y > 0)", not "if (x > 0)"!
    std::cout << "x not positive";

// FIX - braces make intent clear:
if (x > 0)
{
    if (y > 0)
        std::cout << "both positive";
}
else
{
    std::cout << "x not positive";
}
```

</details>

2. When should you use `if constexpr` instead of a regular `if`?

<details>
<summary>Show answer</summary>

**Direct answer:** Use `if constexpr` (C++17) when the condition can be evaluated at compile time and you want the untaken branch to be discarded entirely - not compiled at all. This is especially useful in templates where different branches may contain code that is invalid for certain type instantiations.

**Detailed explanation:**
A regular `if` requires both branches to compile for every type. `if constexpr` only compiles the taken branch, so the discarded branch doesn't even need to be valid code for the current type. The condition must be a constant expression (e.g., `sizeof(T) == 4`, `std::is_integral_v<T>`, or a `constexpr` variable).

```cpp
template <typename T>
void process(T value)
{
    if constexpr (std::is_integral_v<T>)
        std::cout << value % 2;       // only compiled for integral types
    else
        std::cout << std::fixed << value; // only compiled for non-integral types
}
```

</details>

3. What happens if you omit `break` at the end of a `switch` case?

<details>
<summary>Show answer</summary>

**Direct answer:** Execution "falls through" to the next case and continues executing its statements, regardless of whether the next case's label matches. This is almost always a bug. If intentional, use the `[[fallthrough]]` attribute to signal your intent and suppress compiler warnings.

**Detailed explanation:**
`switch` jumps to the matching label, but labels are not barriers - once execution enters a case, it continues sequentially through all subsequent cases unless stopped by `break`, `return`, or `goto`. Intentional fallthrough is rare; the most common legitimate use is stacking multiple case labels that share the same code.

```cpp
switch (x)
{
case 1:
    std::cout << "one";
    // BUG: missing break - falls through to case 2!
case 2:
    std::cout << "two";
    break;
case 3:
case 4:                        // intentional: 3 and 4 share code
    std::cout << "three or four";
    break;
case 5:
    std::cout << "five";
    [[fallthrough]];           // intentional fallthrough - attribute documents it
case 6:
    std::cout << "five or six";
    break;
}
```

</details>

4. Why should loop counter variables be **signed** integers?

<details>
<summary>Show answer</summary>

**Direct answer:** Unsigned integers wrap around to a very large value when decremented past zero, creating subtle bugs - especially in loops that count down or compare against zero. Signed integers underflow predictably (undefined behavior, but easily caught by sanitizers). Using `int` as a loop counter avoids wrap-around surprises.

**Detailed explanation:**
A common bug: `for (unsigned int i = 10; i >= 0; --i)` is an infinite loop because `i` can never be less than zero - when it wraps from 0, it becomes `UINT_MAX`. With `int i`, the condition `i >= 0` works as expected. The C++ Core Guidelines recommend signed integers for loop counters and sizes for this reason.

```cpp
// BUG - infinite loop (unsigned can never be < 0):
for (unsigned int i{ 10 }; i >= 0; --i) { }

// CORRECT - signed counter:
for (int i{ 10 }; i >= 0; --i) { }
```

</details>

5. What is the difference between `break` and `continue` inside a `for` loop?

<details>
<summary>Show answer</summary>

**Direct answer:** `break` exits the loop entirely - execution jumps to the first statement after the loop body. `continue` skips the rest of the current iteration and jumps to the loop's end-expression (e.g., `++i`), then re-evaluates the condition for the next iteration.

**Detailed explanation:**
`break` is used when you've found what you're looking for or hit a terminating condition. `continue` is used to skip certain iterations while continuing the loop. Use both sparingly - they can make loop logic harder to follow. In nested loops, `break` and `continue` only affect the innermost loop they appear in.

```cpp
for (int i{ 0 }; i < 10; ++i)
{
    if (i == 5)
        break;       // exits loop - prints 0 1 2 3 4
    if (i % 2 == 0)
        continue;    // skips even numbers - but break at 5 dominates here
    std::cout << i << ' ';
}
// Without break: continue alone would print 1 3 5 7 9
```

</details>

6. Why should you seed a PRNG only once, and what is **underseeding**?

<details>
<summary>Show answer</summary>

**Direct answer:** A PRNG should be seeded exactly once at program startup because re-seeding resets its internal state, which can produce repeated or correlated sequences. Underseeding occurs when you provide fewer bits of seed data than the PRNG's state requires - `std::mt19937` has 624 × 32 bits of state but `std::random_device{}()` provides only 32 bits, so most possible sequences can never be generated.

**Detailed explanation:**
Use `std::seed_seq` initialized with multiple calls to `std::random_device` to provide more seed entropy and reduce underseeding. Never seed inside a loop. A common pattern is a `Random` namespace with an `inline` static `std::mt19937` that self-seeds once on first use, providing a convenient `Random::get(min, max)` function.

```cpp
// GOOD - seed once, use many times:
std::mt19937 mt{ std::random_device{}() };
std::uniform_int_distribution die{ 1, 6 };
for (int i{ 0 }; i < 10; ++i)
    std::cout << die(mt) << ' ';
```

</details>

7. Name three control flow categories and give an example statement for each.

<details>
<summary>Show answer</summary>

**Direct answer:** (1) **Conditional/selection statements** - `if`, `switch`, `?:`. (2) **Iteration/loop statements** - `for`, `while`, `do-while`. (3) **Jump statements** - `break`, `continue`, `return`, `goto`. Other categories include halts (`std::exit`, `std::abort`) and exception handling (`throw`, `try`/`catch`).

**Detailed explanation:**
Control flow statements alter the execution path so programs can make decisions, repeat work, and handle errors. Selection statements choose between paths, loops repeat work, and jumps transfer execution unconditionally. Each category serves a different need, and modern C++ provides enough tools that `goto` is almost never necessary.

</details>

8. Why is `goto` discouraged, and what is its one acceptable use case?

<details>
<summary>Show answer</summary>

**Direct answer:** `goto` is discouraged because it creates unstructured "spaghetti code" that is hard to read, maintain, and reason about. Any `goto` usage can be replaced with structured constructs (`if`, `for`, `while`, `break`, `return`). The one acceptable use case is jumping forward to a cleanup section at the end of a function - but even this is better handled with RAII or exceptions in C++.

**Detailed explanation:**
`goto` labels have function scope, meaning you can jump to any label in the function, including backward (creating implicit loops) and across blocks. However, you cannot jump over a variable initialization. C-style codebases sometimes use `goto` for error cleanup in functions with multiple resource allocations, but C++ destructors (RAII) handle this automatically.

</details>

9. What is a `do-while` loop, and when is it preferred over `while`?

<details>
<summary>Show answer</summary>

**Direct answer:** A `do-while` loop executes the body first, then checks the condition - guaranteeing at least one iteration. It is preferred for input-validation loops where you must prompt and read input before you can check whether it's valid.

**Detailed explanation:**
The syntax is `do { body } while (condition);` - note the required semicolon after the closing parenthesis. The key difference from `while` is that `while` checks the condition before the first iteration (and may run zero times), while `do-while` always runs the body at least once.

```cpp
int input{};
do
{
    std::cout << "Enter a positive number: ";
    std::cin >> input;
} while (input <= 0);  // repeat until valid
```

</details>

10. What is the difference between `std::exit()` and `std::abort()`?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::exit()` performs a clean shutdown - it calls destructors of static objects, flushes I/O buffers, and invokes `atexit` handlers. `std::abort()` terminates immediately with no cleanup, no destructors, and no handlers. Use `std::exit()` for controlled program termination and `std::abort()` for unrecoverable errors where cleanup may be unsafe (or for `assert` failures).

**Detailed explanation:**
Neither `std::exit()` nor `std::abort()` calls destructors of local variables. For this reason, both should be used sparingly in C++ - prefer returning from `main()` for normal termination, as this unwinds the stack and calls all destructors. `std::abort()` may generate a core dump on Unix systems, which is useful for post-mortem debugging.

</details>
