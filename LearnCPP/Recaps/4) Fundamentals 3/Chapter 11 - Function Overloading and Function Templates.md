# Chapter 11 Recap - Function Overloading and Function Templates

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Use function overloading liberally to simplify your API - let the compiler pick the right function instead of making callers remember distinct names
- Return type is **never** used to differentiate overloads
- Numeric promotions are preferred over numeric conversions during overload resolution - be aware of this priority when designing overloads
- Use `= delete` to explicitly prevent undesired implicit conversions (e.g. `printInt(char) = delete`)
- Default arguments must be rightmost and should be declared in the forward declaration / header
- Prefer function templates over writing duplicate functions for different types
- Favor normal call syntax (`max(1, 2)`) over explicit template arguments (`max<int>(1, 2)`) unless you need to force a specific instantiation
- Template argument deduction does **not** perform type conversions - arguments must match template parameters exactly

### 3 Tiny Examples

1.

```cpp
int add(int x, int y) { return x + y; }
double add(double x, double y) { return x + y; }
// add(1, 2) calls int version; add(1.0, 2.0) calls double version
```

2.

```cpp
void print(int x);           // unique overload (int)
void print(double x);        // unique overload (double)
void print(int x, int y);    // unique overload (different count)
// int print(int x);          // NOT unique - return type doesn't differentiate
```

3.

```cpp
void print(int x);
void print(double x);
print('a');            // 'a' promoted to int → calls print(int)
// print(5L);          // ambiguous: long converts equally to int or double
print(static_cast<int>(5L));  // resolved: calls print(int)
```

### 3 Common Mistakes

- Differentiating overloads only by return type
- Type aliases creating distinct overloads
- `const` on value parameters

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Function overloading** - multiple functions sharing the same name, differentiated by parameter types or count
- **Overload resolution** - the compiler's process for matching a function call to the correct overload
- **Ambiguous match** - when the compiler finds two or more equally valid overloads and cannot choose
- **Deleted functions (`= delete`)** - explicitly forbidding certain overloads from being called
- **Default arguments** - default values for parameters that the caller can optionally omit
- **Function templates** - definitions using placeholder types that the compiler instantiates into real functions
- **Type template parameters** - placeholders (e.g. `T`) representing types to be determined later
- **Template argument deduction** - the compiler deducing template types from function call arguments
- **Non-type template parameters** - template parameters that hold constexpr values instead of types
- **Abbreviated function templates (C++20)** - using `auto` parameters to implicitly create templates
- **Name mangling** - the compiler's internal renaming of overloaded functions to give each a unique compiled name
- **Generic programming** - writing code in terms of template/generic types rather than specific types

### Section-by-Section Detail

### 11.1 - Introduction to function overloading

- **Function overloading** lets you define multiple functions with the **same name** that differ by the number or types of their parameters
- The compiler uses **overload resolution** to determine which overload to call based on the arguments at the call site
- Eliminates the need for distinct names like `addInt()`, `addDouble()` - just name them all `add()`
- Overloaded functions must differ in their **parameter list**; **return type alone** is not sufficient to differentiate overloads
- The compiler uses **name mangling** to give each overload a unique internal name encoding the parameter types

```cpp
int add(int x, int y) { return x + y; }
double add(double x, double y) { return x + y; }
// add(1, 2) calls int version; add(1.0, 2.0) calls double version
```

→ _See [01_IntroToFunctionOverloading](../solutions/Chapter_11_Function_Overloading_And_Templates/01_IntroToFunctionOverloading/)_

### 11.2 - Function overload differentiation

- Overloads are differentiated by the **number** and **type** of parameters, but **not** by return type alone
- **Type aliases** (e.g., `using Count = int;`) do not create distinct types, so a `Count` parameter and an `int` parameter are the **same overload**
- **Top-level `const`** on value parameters is ignored for differentiation because the caller doesn't care whether the function's local copy is `const`
- A function's **type signature** (name + parameter count + parameter types + function-level qualifiers) uniquely identifies each overload
- **Reference and pointer** parameters do differentiate overloads: `void f(int&)` and `void f(const int&)` are distinct

```cpp
void print(int x);           // unique overload (int)
void print(double x);        // unique overload (double)
void print(int x, int y);    // unique overload (different count)
// int print(int x);          // NOT unique - return type doesn't differentiate
```

→ _See [02_OverloadDifferentiation](../solutions/Chapter_11_Function_Overloading_And_Templates/02_OverloadDifferentiation/)_

**What Differentiates Overloads:**

| Factor                              | Differentiates? | Example                                          |
| ----------------------------------- | --------------- | ------------------------------------------------ |
| **Parameter types**                 | Yes             | `f(int)` vs `f(double)`                          |
| **Parameter count**                 | Yes             | `f(int)` vs `f(int, int)`                        |
| **Reference/pointer qualifiers**    | Yes             | `f(int&)` vs `f(const int&)`                     |
| **Return type alone**               | No              | `int f()` vs `double f()` - error                |
| **Type aliases**                    | No              | `f(int)` vs `f(Count)` where `using Count = int` |
| **Top-level const on value params** | No              | `f(int)` vs `f(const int)` - identical           |

### 11.3 - Function overload resolution and ambiguous matches

- The compiler resolves overloaded calls in a **prioritized sequence**: exact match → **numeric promotion** → **numeric conversion** → **user-defined conversion** → **ellipsis match**
- If multiple equally-good matches are found at the same step, the result is an **ambiguous match** (compile error)
- **Ambiguity** can be resolved by adding an exact-match overload, using `static_cast`, or using **literal suffixes**
- Trivial conversions (e.g., array-to-pointer) count as **exact matches** at the highest priority level

```cpp
void print(int x);
void print(double x);
print('a');            // 'a' promoted to int → calls print(int)
// print(5L);          // ambiguous: long converts equally to int or double
print(static_cast<int>(5L));  // resolved: calls print(int)
```

→ _See [03_OverloadResolution](../solutions/Chapter_11_Function_Overloading_And_Templates/03_OverloadResolution/) · [04_AmbiguousMatches](../solutions/Chapter_11_Function_Overloading_And_Templates/04_AmbiguousMatches/)_

**Overload Resolution Priority (highest to lowest):**

| Priority | Match Type                                  | Example                                           |
| -------- | ------------------------------------------- | ------------------------------------------------- |
| 1        | **Exact match** (incl. trivial conversions) | `print(5)` - `print(int)`                         |
| 2        | **Numeric promotion**                       | `print('a')` - `print(int)` via `char` - `int`    |
| 3        | **Numeric conversion**                      | `print(3.14)` - `print(int)` via `double` - `int` |
| 4        | **User-defined conversion**                 | Custom `operator int()`                           |
| 5        | **Ellipsis match**                          | `print(...)`                                      |

> **Ambiguity:** If two or more overloads match at the **same priority level**, the call is ambiguous and the compiler emits an error. Resolve by adding static_cast or a more specific overload.

### 11.4 - Deleting functions

- Using `= delete` on a function overload explicitly **forbids** calls that would match it, producing a **compile error** if invoked
- **Deleted functions** still **participate in overload resolution** - they mean "I explicitly forbid this call," not "this function doesn't exist"
- Useful for preventing **implicit conversions**: e.g., deleting `void printInt(char)` blocks silent `char` → `int` promotion
- You can delete a **function template** to block all non-exact-type matches, then provide specific non-template overloads for allowed types
- Deleted functions are part of the interface and should be **documented**

```cpp
void printInt(int x) { std::cout << x; }
void printInt(char) = delete;   // forbid char → int promotion
// printInt('a');                // compile error: use of deleted function
```

→ _See [05_DeletedFunctions](../solutions/Chapter_11_Function_Overloading_And_Templates/05_DeletedFunctions/)_

### 11.5 - Default arguments

- **Default arguments** provide fallback values for parameters the caller may omit
- They must be the **rightmost parameters** and cannot be redeclared in the same translation unit
- Defaults should be placed in the **forward declaration** (especially in header files), not in the definition
- Default arguments can cause **ambiguous matches** when combined with overloading
- C++ has no syntax to skip middle parameters - place most-commonly-omitted parameters **last**

```cpp
void greet(std::string_view name, std::string_view greeting = "Hello");
// greet("Alice");          // uses default: "Hello"
// greet("Alice", "Hi");   // overrides default with "Hi"
```

→ _See [06_DefaultArguments](../solutions/Chapter_11_Function_Overloading_And_Templates/06_DefaultArguments/)_

### 11.6 - Function templates

- A **function template** is a blueprint using **type template parameters** (e.g., `T`) as placeholders for types specified later
- The compiler generates (**instantiates**) concrete functions from a template as needed - e.g., `max(1, 2)` creates `max<int>`
- Templates are declared with `template <typename T>` (or `template <class T>`, which is equivalent) before the function definition
- Follows the **DRY principle** - write the logic once and let the compiler stamp out type-specific versions
- Template code that is **never instantiated** is never compiled, so unused specializations don't add to binary size

```cpp
template <typename T>
T max(T a, T b) { return (a < b) ? b : a; }
// max(1, 2) → max<int>  |  max(3.0, 4.0) → max<double>
```

> **See also:** [Chapter 26 - Templates and Classes](Chapter%2026%20-%20Templates%20and%20Classes.md) for class templates.

→ _See [07_FunctionTemplates](../solutions/Chapter_11_Function_Overloading_And_Templates/07_FunctionTemplates/)_

**Function Templates vs Function Overloading:**

| Aspect                  | Function Overloading           | Function Template                              |
| ----------------------- | ------------------------------ | ---------------------------------------------- |
| **Code duplication**    | One definition per type        | Single definition for all types                |
| **Type conversions**    | Implicit conversions allowed   | No implicit conversions during deduction       |
| **Definition location** | `.cpp` or header               | Must be in header (template definition needed) |
| **Binary output**       | Only written overloads exist   | One instantiation per used type                |
| **Per-type logic**      | Yes (custom body per overload) | Same logic for all types                       |
| **Maintenance**         | Update every overload          | Single point of change                         |

### 11.7 - Function template instantiation

- When a template is used, the compiler **instantiates** a concrete function by replacing template parameters with actual types
- **Template argument deduction** lets the compiler infer types from arguments, so `max(1, 2)` works instead of `max<int>(1, 2)`
- Normal call syntax prefers **non-template functions** over equally viable template instantiations
- Each instantiation with a **unique type set** produces a separate function (with its own static locals, etc.)
- You can explicitly specify template arguments with `max<double>(1, 2)` to **force** a specific instantiation

```cpp
template <typename T>
T add(T a, T b) { return a + b; }
// add(1, 2);         // deduced as add<int>(1, 2)
// add<double>(1, 2); // explicit: forces double instantiation
```

→ _See [08_TemplateInstantiationAndDeduction](../solutions/Chapter_11_Function_Overloading_And_Templates/08_TemplateInstantiationAndDeduction/)_

### 11.8 - Function templates with multiple template types

- A single template type `T` forces **all parameters** of type `T` to be the same actual type, so `max(2, 3.5)` fails deduction
- Use **multiple template parameters** (e.g., `T` and `U`) to support mixed types like `max(int, double)`
- Use `auto` **return type** to let the compiler deduce the correct return type from the expression
- **C++20 abbreviated function templates** (`auto max(auto x, auto y)`) provide a concise shorthand where each `auto` is an independent type parameter

```cpp
template <typename T, typename U>
auto max(T a, U b) { return (a < b) ? b : a; }
// max(2, 3.5);  // T=int, U=double, returns double
```

→ _See [09_MultipleTemplateTypes](../solutions/Chapter_11_Function_Overloading_And_Templates/09_MultipleTemplateTypes/) · [11_AbbreviatedFunctionTemplates](../solutions/Chapter_11_Function_Overloading_And_Templates/11_AbbreviatedFunctionTemplates/)_

### 11.9 - Non-type template parameters

- **Non-type template parameters (NTTPs)** hold `constexpr` values (e.g., `template <int N>`) rather than types, embedding compile-time constants into a template
- Useful for sizing `std::array`, performing `static_assert`, or unrolling loops - e.g., `std::bitset<8>` uses an NTTP
- NTTPs must be of a **structural type**: integral, enum, pointer, reference, and (since C++20) floating-point and literal class types
- C++17 introduced `auto` for NTTPs (`template <auto N>`), letting the compiler **deduce** the value's type
- The NTTP value is baked into the type at compile time, so `Foo<5>` and `Foo<10>` are **distinct types**

```cpp
template <int N>
void printN() { std::cout << N << '\n'; }
// printN<5>();  // N = 5 at compile time
```

→ _See [10_NonTypeTemplateParameters](../solutions/Chapter_11_Function_Overloading_And_Templates/10_NonTypeTemplateParameters/)_

### 11.10 - Using function templates in multiple files

- Template definitions must go in **header files** because the compiler needs the **full definition** to instantiate for a specific type
- Placing a template definition in a `.cpp` file causes **linker errors** - other translation units can't instantiate it from a declaration alone
- Templates (and their implicit instantiations) are **implicitly inline**, so the same template definition in multiple translation units does not violate the **ODR**
- This is different from normal functions, where declarations go in headers and definitions in `.cpp` files
- Templates can **increase compile times** since every translation unit that uses the template must compile its own instantiations

```cpp
// max.h - full template definition in header (required)
template <typename T>
T max(T a, T b) { return (a < b) ? b : a; }
```

> **See also:** [Chapter 2 - Functions and Files](Chapter%202%20-%20C++%20Basics%20Functions%20and%20Files.md) for the ODR and header files.

→ _See [12_CommonPitfalls](../solutions/Chapter_11_Function_Overloading_And_Templates/12_CommonPitfalls/)_

### Edge Cases and Caveats

- **Differentiating overloads only by return type** - compiler ignores return type.

  ❌ **Bad:** `int get();` and `double get();` - redefinition error.
  ✅ **Good:** Differ by parameter types, or use a template with `auto` return.

- **Type aliases creating distinct overloads** - `using Height = int;` is still `int`.

  ❌ **Bad:** `print(int)` and `print(Height)` - same overload.
  ✅ **Good:** Use a wrapper struct for true type distinction.

- **`const` on value parameters** - doesn't differentiate `void f(int)` from `void f(const int)`.

  ❌ **Bad:** Expecting these to be two different overloads.
  ✅ **Good:** `const` on value params only prevents internal modification.

- **Mismatched types in single-type template** - `T` can't be both `int` and `double`.

  ❌ **Bad:** `max(2, 3.5)` with `template <typename T> T max(T, T)` - deduction failure.
  ✅ **Good:** `max<double>(2, 3.5)` or use multiple template params.

- **Expecting conversions during deduction** - deduction requires exact matches.

  ❌ **Bad:** Passing `int` where `double` is needed in a template.
  ✅ **Good:** Use `static_cast` or explicit template arguments.

- **Template definitions in `.cpp` files** - linker can't find instantiations.

  ❌ **Bad:** Defining `template <typename T> T max(T,T)` in `max.cpp`.
  ✅ **Good:** Place full template definitions in header files.

- **Assuming deleted functions don't exist** - `= delete` still participates in resolution.

  ❌ **Bad:** `print(char) = delete;` then wondering why `print('a')` errors.
  ✅ **Good:** That's the intent - `= delete` means "forbidden."

- **Skipping default arguments from the left** - C++ has no `print(,,3)` syntax.

  ❌ **Bad:** Expecting to skip middle parameters.
  ✅ **Good:** Place most-commonly-omitted parameters last.

- **Redeclaring default arguments** - only once per translation unit.

  ❌ **Bad:** Defaults in both header declaration and `.cpp` definition.
  ✅ **Good:** Place defaults in the header (forward declaration) only.

---

### Hands-On Code Projects

| #   | Project                                                                                                                                  | Concept                                           |
| --- | ---------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------- |
| 01  | [01_IntroToFunctionOverloading](../solutions/Chapter_11_Function_Overloading_And_Templates/01_IntroToFunctionOverloading/)               | Multiple functions, same name, different params   |
| 02  | [02_OverloadDifferentiation](../solutions/Chapter_11_Function_Overloading_And_Templates/02_OverloadDifferentiation/)                     | What counts as a unique overload                  |
| 03  | [03_OverloadResolution](../solutions/Chapter_11_Function_Overloading_And_Templates/03_OverloadResolution/)                               | Matching priority: exact → promotion → conversion |
| 04  | [04_AmbiguousMatches](../solutions/Chapter_11_Function_Overloading_And_Templates/04_AmbiguousMatches/)                                   | Diagnosing and resolving ambiguity                |
| 05  | [05_DeletedFunctions](../solutions/Chapter_11_Function_Overloading_And_Templates/05_DeletedFunctions/)                                   | Forbidding overloads with `= delete`              |
| 06  | [06_DefaultArguments](../solutions/Chapter_11_Function_Overloading_And_Templates/06_DefaultArguments/)                                   | Default values, placement rules                   |
| 07  | [07_FunctionTemplates](../solutions/Chapter_11_Function_Overloading_And_Templates/07_FunctionTemplates/)                                 | `template <typename T>` basics                    |
| 08  | [08_TemplateInstantiationAndDeduction](../solutions/Chapter_11_Function_Overloading_And_Templates/08_TemplateInstantiationAndDeduction/) | Implicit instantiation, deduction                 |
| 09  | [09_MultipleTemplateTypes](../solutions/Chapter_11_Function_Overloading_And_Templates/09_MultipleTemplateTypes/)                         | Multi-type templates (`T`, `U`), `auto` return    |
| 10  | [10_NonTypeTemplateParameters](../solutions/Chapter_11_Function_Overloading_And_Templates/10_NonTypeTemplateParameters/)                 | Compile-time value parameters                     |
| 11  | [11_AbbreviatedFunctionTemplates](../solutions/Chapter_11_Function_Overloading_And_Templates/11_AbbreviatedFunctionTemplates/)           | C++20 `auto` parameters                           |
| 12  | [12_CommonPitfalls](../solutions/Chapter_11_Function_Overloading_And_Templates/12_CommonPitfalls/)                                       | Ambiguity, deduction failures, template placement |

### Quick Reference

### Function overloading

```cpp
void print(int x)       { std::cout << x << '\n'; }
void print(double x)    { std::cout << x << '\n'; }   // OK - different param type
void print(int x, int y){ std::cout << x+y << '\n'; } // OK - different param count
// void print(int x) -> double;  // ERROR - return type alone doesn't differentiate
```

### Overload resolution priority

| Priority | Match Type                        | Example                      |
| -------- | --------------------------------- | ---------------------------- |
| 1        | Exact match (trivial conversions) | `print(5)` → `print(int)`    |
| 2        | Numeric promotion                 | `print('a')` → `print(int)`  |
| 3        | Numeric conversion                | `print(3.14)` → `print(int)` |
| 4        | User-defined conversion           | Custom `operator int()`      |
| 5        | Ellipsis match                    | `print(...)`                 |

### Deleted functions

```cpp
void print(int x);              // allowed
void print(char) = delete;      // forbidden - compile error if called
void print(double) = delete;    // forbidden
```

### Default arguments

```cpp
void greet(std::string_view name, std::string_view greeting = "Hello"); // rightmost only
// greet("Alice");           // uses default greeting
// greet("Alice", "Hi");    // overrides default
```

### Function template

```cpp
template <typename T>
T max(T a, T b)
{
    return (a < b) ? b : a;
}
// max(1, 2);          // deduced: max<int>(1, 2)
// max<double>(1, 2);  // explicit: forces double
```

### Multiple template types

```cpp
template <typename T, typename U>
auto max(T a, U b)    // auto return deduced from expression
{
    return (a < b) ? b : a;
}
```

### Non-type template parameters

```cpp
template <int N>
void printN() { static_assert(N > 0); std::cout << N << '\n'; }
// printN<5>();   // N = 5 at compile time
```

### Abbreviated function templates (C++20)

```cpp
auto max(auto a, auto b)    // each auto = independent template type
{
    return (a < b) ? b : a;
}
```

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What makes two function overloads **distinct**? What does _not_ differentiate them?

<details>
<summary>Show answer</summary>

**Direct answer:** Overloads are differentiated by the number and/or types of their parameters. Return type alone does _not_ differentiate overloads - two functions with the same name and parameter list but different return types cause a compile error. Type aliases (e.g., `using Count = int;`) and top-level `const` on value parameters are also ignored for differentiation.

**Detailed explanation:**
The compiler uses name mangling internally to give each overload a unique symbol based on the function name and parameter types. This is why the linker can tell them apart. The return type is not encoded in the mangled name (in most ABIs) precisely because overload resolution happens before the return type is considered.

```cpp
void print(int x);
void print(double x);      // OK: different parameter type
void print(int x, int y);  // OK: different number of parameters
// int print(int x);       // ERROR: differs only in return type
```

</details>

2. List the overload resolution priority from best to worst match.

<details>
<summary>Show answer</summary>

**Direct answer:** (1) Exact match (including trivial conversions like array-to-pointer). (2) Numeric promotion (e.g., `char` → `int`, `float` → `double`). (3) Numeric conversion (e.g., `int` → `double`, `double` → `int`). (4) User-defined conversion (e.g., constructor or conversion operator). (5) Ellipsis match (`...`). If multiple overloads tie at the same step, the call is ambiguous (compile error).

**Detailed explanation:**
Ambiguity can be resolved by adding an exact-match overload, using `static_cast` on the argument, or using literal suffixes (e.g., `5.0f` for `float`). Non-template functions are preferred over equally viable template instantiations at the same match level.

</details>

3. What does `= delete` do, and why does it still participate in overload resolution?

<details>
<summary>Show answer</summary>

**Direct answer:** `= delete` explicitly forbids calls that match that overload, producing a compile error. Deleted functions still participate in overload resolution because their purpose is "I explicitly forbid this call," not "this function doesn't exist." If the deleted overload weren't considered, the call would silently fall through to another overload.

**Detailed explanation:**
This is useful for preventing implicit conversions. For example, if you have `void printInt(int)` and delete `void printInt(char) = delete`, calling `printInt('a')` produces a compile error instead of silently promoting `char` to `int`.

```cpp
void printInt(int x) { std::cout << x; }
void printInt(char) = delete;   // forbid char arguments

printInt(5);     // OK
// printInt('a'); // ERROR: use of deleted function
```

</details>

4. What is **template argument deduction**, and why don't implicit conversions apply?

<details>
<summary>Show answer</summary>

**Direct answer:** Template argument deduction lets the compiler infer template type parameters from the function arguments, so you can write `max(1, 2)` instead of `max<int>(1, 2)`. Implicit conversions don't apply during deduction because the compiler needs to determine the type from the arguments as-is - if `max(1, 2.0)` were allowed to convert `1` to `double`, the compiler couldn't know whether `T` should be `int` or `double`.

**Detailed explanation:**
If the deduced types conflict (e.g., `T` deduced as both `int` and `double` from different arguments), the call fails. Fixes: (1) explicitly specify the type: `max<double>(1, 2.0)`, (2) use `static_cast` on one argument, or (3) use multiple template parameters (`T` and `U`).

```cpp
template <typename T>
T max(T a, T b) { return (a > b) ? a : b; }

max(1, 2);       // OK: T = int
max(1.0, 2.0);   // OK: T = double
// max(1, 2.0);  // ERROR: T deduced as both int and double
max<double>(1, 2.0);  // OK: explicitly specify T = double
```

</details>

5. Why must template definitions be in **header files**?

<details>
<summary>Show answer</summary>

**Direct answer:** The compiler needs to see the full template definition to instantiate it for a specific type. If the definition is in a `.cpp` file, other translation units that only see the declaration can't instantiate it, resulting in linker errors. Placing template definitions in headers ensures every translation unit that uses the template can instantiate it.

**Detailed explanation:**
Templates are not real functions - they are blueprints. The compiler generates actual code only when the template is instantiated with specific types. Since compilation happens per-translation-unit, the template body must be visible everywhere it's used. `constexpr` and `inline` functions have the same requirement for the same reason.

</details>

6. How do C++20 **abbreviated function templates** differ from regular templates?

<details>
<summary>Show answer</summary>

**Direct answer:** Abbreviated function templates use `auto` parameters instead of an explicit `template <typename T>` declaration. Each `auto` parameter gets its own independent template type parameter, so `auto max(auto x, auto y)` allows `x` and `y` to be different types. With a regular template using a single `T`, both parameters must be the same type.

**Detailed explanation:**

```cpp
// Regular template - T and U are explicit:
template <typename T, typename U>
auto max(T x, U y) { return (x > y) ? x : y; }

// C++20 abbreviated - equivalent (each auto is independent):
auto max(auto x, auto y) { return (x > y) ? x : y; }

// Single T forces same type:
template <typename T>
T max(T x, T y) { return (x > y) ? x : y; }
// max(1, 2.0); // ERROR with single-T version
```

</details>

7. What is a **non-type template parameter**? Give an example.

<details>
<summary>Show answer</summary>

**Direct answer:** A non-type template parameter (NTTP) holds a `constexpr` value (not a type) that is baked into the template at compile time. Examples: `template <int N>` or `std::bitset<8>` (where `8` is an NTTP). NTTPs must be of a structural type: integral, enum, pointer, reference, or (C++20) floating-point and literal class types.

**Detailed explanation:**
NTTPs are useful when a compile-time constant needs to be embedded in the type or used for array sizing, `static_assert`, or loop unrolling. C++17 introduced `auto` for NTTPs: `template <auto N>` lets the compiler deduce the type.

```cpp
template <int N>
void printN() { std::cout << N << '\n'; }

printN<5>();   // prints 5 (N is embedded at compile time)

template <auto N>   // C++17: auto NTTP
void printAny() { std::cout << N << '\n'; }
printAny<42>();     // N deduced as int
```

</details>

8. What happens if you call `max(2, 3.5)` with `template <typename T> T max(T, T)`?

<details>
<summary>Show answer</summary>

**Direct answer:** It fails to compile. Template argument deduction deduces `T` as `int` from `2` and `double` from `3.5` - the deductions conflict. The compiler cannot decide which type to use and reports an ambiguity error. Fixes: `max<double>(2, 3.5)`, or `max(static_cast<double>(2), 3.5)`, or use two template parameters.

**Detailed explanation:**
Unlike regular function overload resolution, template argument deduction does not perform implicit conversions. The types must match exactly (or through trivial conversions like array-to-pointer). This is by design - if deduction allowed conversions, it would be ambiguous which direction to convert.

</details>

9. What is **name mangling**, and why does C++ need it?

<details>
<summary>Show answer</summary>

**Direct answer:** Name mangling is the process by which the compiler encodes a function's parameter types (and namespace/class scope) into its symbol name. This allows the linker to distinguish between overloaded functions that share the same name but have different parameter lists. C needs it because C++ supports function overloading, unlike C.

**Detailed explanation:**
For example, `void print(int)` might be mangled to `_Z5printi` and `void print(double)` to `_Z5printd`. Mangling schemes differ between compilers, which is why C++ libraries aren't directly ABI-compatible across compilers. `extern "C"` disables mangling for C-compatible linkage.

</details>

10. Why are non-template functions preferred over template instantiations in overload resolution?

<details>
<summary>Show answer</summary>

**Direct answer:** When a non-template function and a template instantiation are equally good matches, the compiler prefers the non-template function. This is because non-template functions are explicit specializations written by the programmer - they represent a deliberate, specific implementation for that type, which should take priority over a generic template.

**Detailed explanation:**
This rule lets you provide optimized or special-cased implementations for specific types while keeping the template as a fallback for all other types. If the template is a better match (e.g., exact match vs. conversion), the template still wins - the preference only applies at equal match quality.

</details>
