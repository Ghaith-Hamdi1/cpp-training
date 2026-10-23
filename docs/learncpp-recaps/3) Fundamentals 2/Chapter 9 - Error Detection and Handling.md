# Chapter 9 Recap - Error Detection and Handling

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Write and test code in small units; don't write a whole program and test it all at the end
- Aim for 100% branch coverage and use the 0, 1, 2 test for loops
- Always plan for sad paths, not just the happy path
- When `std::cin` extraction fails, you must call `clear()` before `ignore()` - otherwise `ignore()` silently fails too
- Use `assert` to catch programmer errors during development; use error handling for issues that can occur in production
- Favor `static_assert` over `assert` when the condition can be evaluated at compile time
- Keep assert expressions free of side effects, since they are compiled out in release builds
- Use the bouncer pattern: check preconditions at the top of a function and return early on failure

### 3 Tiny Examples

1.

```cpp
int divide(int x, int y)
{
    if (y == 0)
    {
        std::cerr << "Error: division by zero\n"; // diagnostic output
        return 0; // sentinel value indicating error
    }
    return x / y;
}
```

2.

```cpp
if (std::cin.fail())   // extraction failed (e.g. user typed 'abc' for int)
{
    std::cin.clear();  // reset error flags
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
}
```

3.

```cpp
assert(ptr != nullptr && "ptr should never be null"); // runtime
static_assert(sizeof(int) >= 4, "int too small");     // compile-time
```

### 3 Common Mistakes

- Comparison mix-ups (`>=` vs `>`)
- Forgetting to increment a loop variable
- Unsigned countdown past zero

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Software testing / validation** - the process of determining whether software works as expected
- **Unit testing** - testing a small piece of code (usually a function) in isolation
- **Integration testing** - testing multiple units together after they've been individually verified
- **Code coverage** - how much of your source code is exercised during testing (statement, branch, and loop coverage)
- **Happy path vs. sad path** - the error-free execution path vs. paths where errors occur
- **Defensive programming** - anticipating and handling all the ways software can be misused
- **Input validation** - checking that user input conforms to what the program expects
- **Precondition / invariant / postcondition** - conditions that must be true before, during, or after code execution
- **Assertion** - an expression that should always be true unless there is a bug; triggers `std::abort` if false
- **`static_assert`** - a compile-time assertion that causes a compiler error if its condition is false
- **Sentinel value** - a special return value used to indicate an error condition

### Section-by-Section Detail

### 9.1 - Introduction to testing your code

- Testing every possible input combination is infeasible, so **test in small pieces as you write** rather than testing the whole program at the end
- **Unit tests** verify individual functions in isolation by passing known inputs and checking outputs against expected results
- Start with informal test calls in `main()`, then preserve them as dedicated test functions
- **Unit testing frameworks** (e.g., Google Test, Catch2) help organize, discover, and run large test suites at scale
- Aim to cover the **happy path** (normal inputs), the **sad path** (erroneous/boundary inputs), and any domain-specific **edge cases**

→ _See [01_UnitTesting](../solutions/Chapter_09_Error_Detection_And_Handling/01_UnitTesting)_

### 9.2 - Code coverage

- **Statement coverage** measures the percentage of code statements executed during testing
- **Branch coverage** checks whether both `true` and `false` paths of every conditional have been exercised - aim for **100%**
- **Loop coverage** (the **"0, 1, 2 test"**) verifies loops execute correctly with zero, one, and two or more iterations, catching **off-by-one errors**
- Beyond structural coverage, test different **input categories**: negatives, zero, positives, boundary values, empty containers, null pointers
- No single coverage metric guarantees bug-free code, but combining high **branch coverage** with thoughtful input categories catches the vast majority of issues

→ _See [02_CodeCoverage](../solutions/Chapter_09_Error_Detection_And_Handling/02_CodeCoverage)_

### 9.3 - Common semantic errors in C++

- **Semantic errors** (logic errors) compile and link cleanly but produce incorrect behavior at runtime
- Common types include **conditional logic errors** (wrong comparison), **infinite loops** (forgetting to update the loop variable), and **off-by-one errors** (`<` vs `<=`)
- **Operator precedence** mistakes cause subtle bugs - e.g., `x & 0xFF == 0` parses as `x & (0xFF == 0)`
- **Floating-point precision** issues cause `0.1 + 0.2 == 0.3` to be `false`; **integer division** (`7 / 2` → `3`) silently truncates
- Other frequent mistakes: **null statements** after `if`, missing braces, using `=` instead of `==`, and forgetting `()` when calling a function

→ _See [03_CommonSemanticErrors](../solutions/Chapter_09_Error_Detection_And_Handling/03_CommonSemanticErrors)_

> **Common Semantic Error Categories:**
>
> - **Conditional logic errors** - using >= instead of >, = instead of ==, wrong boolean logic
> - **Loop errors** - forgetting to increment loop variable (infinite loop), off-by-one (< vs <=)
> - **Operator precedence** - x & 0xFF == 0 parses as x & (0xFF == 0) because == binds tighter than &
> - **Floating-point precision** - 0.1 + 0.2 == 0.3 evaluates to false due to rounding
> - **Integer division truncation** - 7 / 2 yields 3, not 3.5; cast one operand to double
> - **Null statement** - if (cond); executes the null statement, not the next line
> - **Missing braces** - multi-statement blocks without {} only execute the first statement conditionally
> - **Missing parentheses** - if (getValue) evaluates the function pointer (always true), not the return value

### 9.4 - Detecting and handling errors

- Most bugs come from **faulty assumptions** about program state, not from misunderstanding language syntax
- Four **error-handling strategies**: (1) **handle within the function**, (2) **pass error to caller** via return codes, (3) **halt the program**, (4) **throw an exception**
- Use `std::cout` for normal output and `std::cerr` for diagnostic/error messages - `std::cerr` is **unbuffered**, so messages appear immediately
- For production applications, **log errors to a file** so issues can be diagnosed after the fact
- The **bouncer pattern** checks **preconditions** at the top of a function and returns early on failure

```cpp
int divide(int x, int y)
{
    if (y == 0)
    {
        std::cerr << "Error: division by zero\n"; // diagnostic output
        return 0; // sentinel value indicating error
    }
    return x / y;
}
```

> **See also:** [Chapter 27 - Exceptions](<../9) Advanced 2/Chapter 27 - Exceptions.md>) for throwing and catching exceptions.

→ _See [04_DetectingAndHandlingErrors](../solutions/Chapter_09_Error_Detection_And_Handling/04_DetectingAndHandlingErrors) · [05_BouncerPattern](../solutions/Chapter_09_Error_Detection_And_Handling/05_BouncerPattern)_

**Error Handling Strategies Comparison:**

| Strategy                   | When to Use                                                 | Pros                                        | Cons                                           |
| -------------------------- | ----------------------------------------------------------- | ------------------------------------------- | ---------------------------------------------- |
| **Handle within function** | Error has an obvious recovery (retry, default value)        | Caller doesn't need to know about the error | May hide problems silently                     |
| **Pass error to caller**   | Caller is better positioned to decide what to do            | Flexible - caller chooses response          | Caller may forget to check return code         |
| **Halt the program**       | Unrecoverable error, continuing would cause data corruption | Guarantees no further damage                | Abrupt - no cleanup, bad for servers           |
| **Throw an exception**     | Error detection and handling are in different scopes        | Clean separation of concerns                | Overhead; must be caught or program terminates |

> **Output streams for errors:**
>
> - std::cout - buffered, for normal output; may be lost on crash
> - std::cerr - unbuffered, for errors/diagnostics; appears immediately even on crash
> - **Log file** - persistent record for post-mortem analysis in production systems

### 9.5 - std::cin and handling invalid input

- Four categories of bad text input: (1) **meaningless but extractable**, (2) **extraneous characters** left in buffer, (3) **extraction failure** (puts `std::cin` in a fail state), (4) **numeric overflow**
- After extraction failure, `std::cin` sets **error flags** and all subsequent extractions silently fail - call `std::cin.clear()` to reset flags **before** `std::cin.ignore()`
- Use `std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\\n')` to discard everything up to and including the next newline
- The standard **robust input pattern** is a `while (true)` loop that prompts, attempts extraction, checks for failure, clears/ignores on failure, and breaks on success
- Order matters: calling `ignore()` without first calling `clear()` silently does nothing when the stream is in a **fail state**

```cpp
if (std::cin.fail())   // extraction failed (e.g. user typed 'abc' for int)
{
    std::cin.clear();  // reset error flags
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
}
```

→ _See [06_StdCinInvalidInput](../solutions/Chapter_09_Error_Detection_And_Handling/06_StdCinInvalidInput)_

**std::cin Input Error Categories:**

| Category                        | Example                    | Stream State               | Recovery                                   |
| ------------------------------- | -------------------------- | -------------------------- | ------------------------------------------ |
| **Meaningless but extractable** | User enters -1 for age     | Good - extraction succeeds | Application-level range validation         |
| **Extraneous characters**       | User types `42abc`         | Good - `42` extracted      | `std::cin.ignore()` to discard leftovers   |
| **Extraction failure**          | User types `abc` for `int` | Fail - error flags set     | `clear()` then `ignore()` (order matters!) |
| **Numeric overflow**            | Value exceeds type range   | Fail - error flags set     | `clear()` then `ignore()`                  |

> **Recovery order matters:** Always call `std::cin.clear()` **before** `std::cin.ignore()`. If `std::cin` is in a fail state, `ignore()` silently does nothing.

### 9.6 - Assert and static_assert

- `assert(condition)` (from `<cassert>`) enforces **programmer assumptions** at runtime - on failure it prints a diagnostic and calls `std::abort()`
- Asserts are for conditions that should **never** be false unless there is a bug - not for expected runtime errors
- When `NDEBUG` is defined (release builds), all `assert` calls are **compiled out** - so assert expressions must be **free of side effects**
- Add descriptive messages via the **`&&` trick**: `assert(x > 0 && "x must be positive")`
- **`static_assert(condition, message)`** checks a condition at **compile time**, producing a compiler error if false - use for type sizes, template parameters, and platform checks

```cpp
assert(ptr != nullptr && "ptr should never be null"); // runtime
static_assert(sizeof(int) >= 4, "int too small");     // compile-time
```

→ _See [07_AssertAndStaticAssert](../solutions/Chapter_09_Error_Detection_And_Handling/07_AssertAndStaticAssert) · [08_FloatingPointComparison](../solutions/Chapter_09_Error_Detection_And_Handling/08_FloatingPointComparison) · [09_LoopPitfalls](../solutions/Chapter_09_Error_Detection_And_Handling/09_LoopPitfalls)_

**assert vs static_assert Comparison:**

| Feature                | `assert`                                 | `static_assert`                                   |
| ---------------------- | ---------------------------------------- | ------------------------------------------------- |
| **When checked**       | Runtime                                  | Compile time                                      |
| **Header**             | `<cassert>`                              | Built-in (no header)                              |
| **On failure**         | Prints diagnostic + calls `std::abort()` | Compiler error                                    |
| **Disabled by NDEBUG** | Yes - compiled out in release            | No - always checked                               |
| **Side effects safe?** | No - expression removed in release       | N/A - constant expression required                |
| **Message**            | Via `&&` trick: `assert(x > 0 && "msg")` | Second parameter (optional C++17)                 |
| **Use case**           | Programmer assumptions at runtime        | Type sizes, template constraints, platform checks |

### Edge Cases and Caveats

- **Comparison mix-ups (`>=` vs `>`)** - compiles fine, wrong behavior.

  ❌ **Bad:** `if (age >= 18)` when you meant `if (age > 18)`.
  ✅ **Good:** Mentally trace boundary values; write unit tests for both sides.

- **Forgetting to increment a loop variable** - infinite loop.

  ❌ **Bad:** `while (i < 10) { /* forgot ++i */ }`
  ✅ **Good:** Use a `for` loop so the update is syntactically visible.

- **Unsigned countdown past zero** - wraps to `UINT_MAX`.

  ❌ **Bad:** `for (unsigned i{10}; i >= 0; --i)` - always true!
  ✅ **Good:** Use signed `int` for loop counters.

- **Null statement after `if`** - `if (cond);` does nothing.

  ❌ **Bad:** `if (x > 0); doSomething();`
  ✅ **Good:** `if (x > 0) { doSomething(); }`

- **`=` instead of `==`** in conditionals.

  ❌ **Bad:** `if (x = 5)` - assigns 5.
  ✅ **Good:** `if (x == 5)`

- **Calling `getValue` without `()`** - evaluates function pointer (always truthy).

  ❌ **Bad:** `if (getValue)` - always true.
  ✅ **Good:** `if (getValue())`

- **Not calling `std::cin.clear()` after fail** - all subsequent extractions fail.

  ❌ **Bad:** `std::cin.ignore(...)` without `clear()` first.
  ✅ **Good:** `std::cin.clear(); std::cin.ignore(...);`

- **Side effects in `assert()`** - removed in release builds.

  ❌ **Bad:** `assert(init());` - `init()` not called in release!
  ✅ **Good:** `bool ok = init(); assert(ok);`

- **Comparing floats with `==`** - rounding errors accumulate.

  ❌ **Bad:** `if (0.1 + 0.2 == 0.3)`
  ✅ **Good:** Use epsilon-based comparison.

---

### Hands-On Code Projects

| #   | Project                                                                                                              | Concept                                        |
| --- | -------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------- |
| 01  | [01_UnitTesting](../solutions/Chapter_09_Error_Detection_And_Handling/01_UnitTesting)                               | Writing and organizing unit tests              |
| 02  | [02_CodeCoverage](../solutions/Chapter_09_Error_Detection_And_Handling/02_CodeCoverage)                             | Statement, branch, and loop coverage           |
| 03  | [03_CommonSemanticErrors](../solutions/Chapter_09_Error_Detection_And_Handling/03_CommonSemanticErrors)             | Identifying logic errors that compile cleanly  |
| 04  | [04_DetectingAndHandlingErrors](../solutions/Chapter_09_Error_Detection_And_Handling/04_DetectingAndHandlingErrors) | Error return codes, sentinel values, halts     |
| 05  | [05_BouncerPattern](../solutions/Chapter_09_Error_Detection_And_Handling/05_BouncerPattern)                         | Precondition checks, early return              |
| 06  | [06_StdCinInvalidInput](../solutions/Chapter_09_Error_Detection_And_Handling/06_StdCinInvalidInput)                 | `std::cin` failure recovery                    |
| 07  | [07_AssertAndStaticAssert](../solutions/Chapter_09_Error_Detection_And_Handling/07_AssertAndStaticAssert)           | Runtime `assert`, compile-time `static_assert` |
| 08  | [08_FloatingPointComparison](../solutions/Chapter_09_Error_Detection_And_Handling/08_FloatingPointComparison)       | Epsilon and relative tolerance                 |
| 09  | [09_LoopPitfalls](../solutions/Chapter_09_Error_Detection_And_Handling/09_LoopPitfalls)                             | Off-by-one, unsigned wraparound                |

### Quick Reference

### assert / static_assert

```cpp
#include <cassert>

assert(ptr != nullptr);                          // runtime - aborts if false (disabled by NDEBUG)
assert(index < size && "index out of bounds");    // descriptive assert via && trick

static_assert(sizeof(int) >= 4, "int must be at least 32 bits"); // compile-time
static_assert(sizeof(int) >= 4);                  // C++17 - message optional
```

### std::cin error recovery

```cpp
#include <iostream>
#include <limits>

int getValidInt()
{
    while (true)
    {
        int x{};
        std::cout << "Enter an integer: ";
        std::cin >> x;

        if (std::cin.fail())                       // extraction failed
        {
            std::cin.clear();                      // restore stream state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
            std::cout << "Invalid input. Try again.\n";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard extraneous
            return x;
        }
    }
}
```

### Bouncer pattern

```cpp
void processAge(int age)
{
    if (age < 0 || age > 150)   // precondition check
        return;                 // reject bad input early

    // main logic only runs if preconditions are met
}
```

### Code coverage targets

| Coverage Type | What It Measures                 | Target    |
| ------------- | -------------------------------- | --------- |
| Statement     | % of statements executed         | > 70%     |
| Branch        | % of `if`/`else` branches taken  | 100%      |
| Loop (0/1/2)  | Loop executes 0, 1, and 2+ times | All three |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is the difference between **unit testing** and **integration testing**?

<details>
<summary>Show answer</summary>

**Direct answer:** Unit testing verifies individual functions or classes in isolation - you pass known inputs and check that the output matches expectations. Integration testing verifies that multiple components work correctly together. Always start with unit tests; they catch bugs earlier and are easier to debug because the scope is small.

**Detailed explanation:**
Start by testing each function with a range of inputs: normal cases, edge cases (boundary values, zero, negative), and error cases (invalid input). Preserve tests as dedicated test functions that automatically compare actual vs. expected results. As the codebase grows, integration tests verify that the tested units interact correctly. Testing in small pieces as you write is far more effective than writing the entire program first.

</details>

2. Name the three types of code coverage and their targets.

<details>
<summary>Show answer</summary>

**Direct answer:** (1) **Statement coverage** - the percentage of code statements executed. (2) **Branch coverage** - whether both `true` and `false` paths of every conditional have been exercised. (3) **Loop coverage** (the "0, 1, 2 test") - whether each loop has been tested with zero iterations, one iteration, and two or more iterations.

**Detailed explanation:**
Statement coverage is the weakest metric - 100% statement coverage doesn't mean you tested all branches. Branch coverage catches missed `else` paths and is the better goal. Loop coverage targets off-by-one errors that commonly occur at loop boundaries. Aim for 100% branch coverage and test all three loop counts for every loop.

</details>

3. What is the **bouncer pattern** and when should you use it?

<details>
<summary>Show answer</summary>

**Direct answer:** The bouncer pattern validates preconditions at the top of a function and returns early (or throws/asserts) if any check fails. This keeps the main logic un-indented and only runs if all preconditions are met, improving readability.

**Detailed explanation:**
Instead of wrapping the entire function body in nested `if` checks, you "bounce" invalid inputs at the door - like a nightclub bouncer. Each precondition check is a separate `if` that returns immediately on failure. The main logic follows at the base indentation level, making the happy path easy to read.

```cpp
bool processOrder(int quantity, double price)
{
    if (quantity <= 0)
        return false;      // bounced
    if (price < 0.0)
        return false;      // bounced

    // Main logic - only reached if preconditions pass
    double total{ quantity * price };
    // ...
    return true;
}
```

</details>

4. What are the four categories of bad `std::cin` input?

<details>
<summary>Show answer</summary>

**Direct answer:** (1) Meaningless but extractable input (e.g., `-1` for age - syntactically valid but semantically wrong). (2) Extraneous characters left in the buffer after a valid extraction (e.g., user types `"42abc"`). (3) Extraction failure - input can't be converted to the target type (e.g., typing letters when an `int` is expected), putting `std::cin` into a fail state. (4) Numeric overflow - the value is too large or small for the target type.

**Detailed explanation:**
Category 1 requires application-level validation (range checks). Category 2 requires `std::cin.ignore()` to discard extra characters. Categories 3 and 4 put `std::cin` into a fail state, requiring `std::cin.clear()` then `std::cin.ignore()` to recover. Always validate input in a loop to handle all four categories robustly.

</details>

5. Why must you call `std::cin.clear()` _before_ `std::cin.ignore()`?

<details>
<summary>Show answer</summary>

**Direct answer:** After an extraction failure, `std::cin` sets internal error flags that cause all subsequent operations (including `ignore()`) to silently fail. You must call `clear()` first to reset the error flags, then call `ignore()` to discard the bad characters from the input buffer.

**Detailed explanation:**
The typical recovery pattern is:

```cpp
if (!std::cin)  // extraction failed
{
    std::cin.clear();  // 1. reset error flags so cin works again
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 2. discard bad input
}
```

If you swap the order, `ignore()` does nothing because `std::cin` is still in a fail state, and the bad input stays in the buffer causing an infinite loop.

</details>

6. What happens to `assert()` in release builds, and why is that dangerous with side effects?

<details>
<summary>Show answer</summary>

**Direct answer:** When `NDEBUG` is defined (standard in release builds), all `assert()` calls are compiled out - the condition is never evaluated. If the assert expression contains side effects (like `assert(++counter > 0)`), those side effects disappear in release, causing different behavior between debug and release builds.

**Detailed explanation:**
Asserts are meant for conditions that should _never_ be false unless there is a programmer bug. They should not be used for expected runtime errors (like bad user input). Never put function calls, increments, or assignments inside `assert()` - separate the side effect from the assertion:

```cpp
// BAD - increment disappears in release:
assert(++count > 0);

// GOOD - separate the side effect:
++count;
assert(count > 0);
```

</details>

7. When should you prefer `static_assert` over `assert`?

<details>
<summary>Show answer</summary>

**Direct answer:** Use `static_assert` when the condition can be checked at compile time. It causes a compiler error (not a runtime crash) if the condition is false, catching problems before the program even runs. It is never compiled out - it runs during compilation regardless of `NDEBUG`.

**Detailed explanation:**
`static_assert` is ideal for verifying type sizes, template constraints, and platform assumptions. It takes a constant expression and an optional message string (the message is optional since C++17).

```cpp
static_assert(sizeof(int) >= 4, "int must be at least 32 bits");
static_assert(sizeof(long) >= sizeof(int));  // C++17 - message optional

// vs runtime assert:
assert(ptr != nullptr);  // only checked at runtime, removed in release
```

</details>

8. What is a **sentinel value**? Give an example.

<details>
<summary>Show answer</summary>

**Direct answer:** A sentinel value is a special return value that indicates an error or "not found" condition, using a value from the normal return type's range that has been reserved for this purpose. Example: `std::string::npos` (returned by `find()` when a substring is not found) and `-1` (commonly returned by C functions on failure).

**Detailed explanation:**
Sentinel values are simple but have downsides: the caller may forget to check for the sentinel and accidentally use it as a normal value, and they reduce the range of valid return values. Modern C++ alternatives include `std::optional` (returns an empty optional on failure) and exceptions. Always document what sentinel value a function returns on error.

```cpp
int findIndex(int arr[], int size, int target)
{
    for (int i{ 0 }; i < size; ++i)
        if (arr[i] == target)
            return i;
    return -1;  // sentinel: "not found"
}
```

</details>

9. What are **semantic errors**, and why are they harder to find than syntax errors?

<details>
<summary>Show answer</summary>

**Direct answer:** Semantic errors (logic errors) are mistakes where the code compiles and links without warnings but produces incorrect behavior at runtime. They are harder to find because the compiler can't detect them - the code is syntactically valid but logically wrong. Common types include using the wrong comparison operator, off-by-one errors in loops, and incorrect operator precedence.

**Detailed explanation:**
Examples: using `>` when you meant `>=`, iterating one too many or too few times (`<` vs. `<=`), writing `x & 0xFF == 0` which parses as `x & (0xFF == 0)` due to precedence. Floating-point precision issues also cause subtle semantic bugs (e.g., `0.1 + 0.2 == 0.3` evaluates to `false`). The best defense is thorough testing, code reviews, and using tools like assertions and sanitizers.

</details>

10. What is the difference between `std::cerr` and `std::cout` for error messages?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::cout` is buffered - output may be delayed until the buffer is flushed. `std::cerr` is unbuffered - output appears immediately. Use `std::cerr` for error and diagnostic messages so they are visible even if the program crashes before the buffer flushes. `std::cout` should be used for normal program output.

**Detailed explanation:**
If a program crashes, buffered `std::cout` output may be lost because the buffer was never flushed. `std::cerr` writes immediately, ensuring error messages are always visible. Additionally, `std::cerr` and `std::cout` can be redirected to different destinations (e.g., `./program > output.txt 2> errors.txt`), which is useful for separating normal output from diagnostics.

</details>
