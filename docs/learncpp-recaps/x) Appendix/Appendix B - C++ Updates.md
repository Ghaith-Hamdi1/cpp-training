# Appendix B Recap - C++ Updates

This appendix surveys every major C++ standard revision from C++11 through C++23. For each version it explains the design goals, lists the headline language and library features, and points to the relevant learncpp.com lessons. Understanding this timeline helps you know which features are available at each standard level and why they were introduced.

## Key Concepts

- **ISO C++ Standards** - The C++ language is updated through formal ISO standards (C++11, C++14, C++17, C++20, C++23), each adding new features while maintaining backward compatibility.
- **Backward Compatibility** - A core design principle: code that compiled under an older standard should generally still compile under a newer one.
- **Core Language vs. Standard Library** - Updates come in two flavours: changes to the language syntax/semantics (core) and new/improved classes and functions in the standard library.
- **Feature Adoption Ladder** - C++11 was a massive overhaul; C++14 was a small polish pass; C++17 added moderate content; C++20 was the next big leap; C++23 continued incremental improvements.

## Section Summaries

### B.1 - Introduction to C++11

- **C++11** was the largest update since C++'s inception - it established the **`modern C++`** baseline all later standards build on
- Key language additions - `auto`, **range-based for**, **lambdas**, **move semantics**, `nullptr`, `constexpr`, **scoped enums**, **uniform initialization**
- Key library additions - **smart pointers** (`std::unique_ptr`), improved **multithreading** support, better **random-number** generation, `std::tuple`
- Design goals - build on C++'s strengths, improve **type safety**, increase **performance**, and make the language easier to learn

```cpp
auto ptr{ std::make_unique<int>(42) };  // smart pointer
for (int x : {1, 2, 3}) {}             // range-based for
auto fn = [](int x) { return x * 2; }; // lambda
```

→ _See [01_Cpp11_KeyFeatures](../solutions/Appendix_B_CppUpdates/01_Cpp11_KeyFeatures)_

### B.2 - Introduction to C++14

- **C++14** was a minor refinement release that polished C++11 rather than adding major new features
- Key additions - **binary literals** (`0b`), **digit separators** (`'`), **generic lambdas** (`auto` parameters), **relaxed** `constexpr` functions (loops/local variables allowed)
- Added **return-type deduction** for functions and `std::make_unique` - filling gaps C++11 left behind
- Think of C++14 as a **quality-of-life** update - most of its features are things C++11 should have included from the start

```cpp
auto x = 0b1010;                     // binary literal
auto y = 1'000'000;                  // digit separators
auto add = [](auto a, auto b) { return a + b; }; // generic lambda
```

→ _See [02_Cpp14_Improvements](../solutions/Appendix_B_CppUpdates/02_Cpp14_Improvements)_

### B.3 - Introduction to C++17

- **C++17** bridged the gap between C++11's revolution and C++20's next major overhaul with practical everyday improvements
- Key library additions - `std::string_view` (non-owning string refs), `std::optional` (nullable values), `std::filesystem` (portable file ops)
- Key language features - **CTAD**, **inline variables**, `constexpr if`, **nested namespace definitions**, **fold expressions**, **mandatory copy elision**
- Removed long-deprecated items like `std::auto_ptr` and **trigraphs**
- Added **structured bindings** (`auto [x, y] = ...`) for convenient multi-value unpacking

```cpp
std::optional<int> maybe{42};        // optional
std::string_view sv{"hello"};         // string_view
auto [x, y] = std::pair{1, 2};       // structured bindings
```

→ _See [03_Cpp17_Features](../solutions/Appendix_B_CppUpdates/03_Cpp17_Features)_

> **C++17 vs C++20 at a Glance**
>
> | Dimension              | C++17 (Practical)                | C++20 (Transformative)                |
> | ---------------------- | -------------------------------- | ------------------------------------- |
> | Template constraints   | SFINAE + `enable_if` workarounds | Concepts (clean, readable)            |
> | Algorithm style        | Iterator-pair (`begin`/`end`)    | Ranges (pass container directly)      |
> | Compile-time branching | `if constexpr` (local)           | `consteval` (forced compile-time)     |
> | String handling        | `std::string_view` (non-owning)  | `std::span` (generic non-owning view) |
> | Comparison boilerplate | Write all 6 operators manually   | `<=>` spaceship generates them        |

### B.4 - Introduction to C++20

- **C++20** is the second `major` standard after C++11 - it fundamentally improves templates, algorithms, and large-scale code organization
- **Concepts** replace SFINAE hacks with clean, readable constraints on template parameters
- **Ranges** enable composable algorithm pipelines via views and adaptors - pass containers directly instead of iterator pairs
- **Modules** replace `#include` with a modern system that improves build times and encapsulation
- Other notable additions - **spaceship operator** (`<=>`), `consteval`, `constinit`, **designated initializers**, `std::span`, **coroutines**

```cpp
template<std::integral T>             // C++20 concept
T add(T a, T b) { return a + b; }
auto v = std::views::iota(1, 10);    // C++20 ranges
```

→ _See [04_Cpp20_Features](../solutions/Appendix_B_CppUpdates/04_Cpp20_Features)_

### B.5 - Introduction to C++23

- **C++23** focuses on polish and usability rather than sweeping changes - continues incremental improvement
- `std::print` / `std::println` provide modern, **type-safe formatted output** as an alternative to `std::cout`
- `std::expected` offers a better alternative to exceptions for **expected failure paths** - `std::mdspan` adds **multidimensional array views**
- New literal suffix `uz`/`zu` for `std::size_t` - `std::to_underlying` converts enums to their underlying integer type
- `constexpr` support expands further to `<cmath>` functions and `std::unique_ptr` - **standard library modules** (`import std;`) promise dramatic build-time improvements

```cpp
std::println("Hello, {}!", "world");  // C++23 formatted output
auto sz = 42uz;                       // C++23 size_t literal suffix
```

→ _See [05_Cpp23_Features](../solutions/Appendix_B_CppUpdates/05_Cpp23_Features)_

> **"Which Standard Do I Need?" - Feature Decision Table**
>
> | I want to use…                                                           | Minimum Standard |
> | ------------------------------------------------------------------------ | ---------------- |
> | `auto`, lambdas, `nullptr`, move semantics, smart pointers               | C++11            |
> | Generic lambdas, `std::make_unique`, digit separators                    | C++14            |
> | `std::string_view`, `std::optional`, structured bindings, `if constexpr` | C++17            |
> | Concepts, Ranges, `<=>` spaceship operator, `consteval`, `std::span`     | C++20            |
> | `std::print`, `std::expected`, deducing this, `constexpr <cmath>`        | C++23            |

## Hands-On Code Projects

| #   | Project                                                                            | Standard | Concept                                                                                                             |
| --- | ---------------------------------------------------------------------------------- | -------- | ------------------------------------------------------------------------------------------------------------------- |
| 01  | [01_Cpp11_KeyFeatures](../solutions/Appendix_B_CppUpdates/01_Cpp11_KeyFeatures)   | C++11    | `auto`, range-based `for`, `nullptr`, scoped enums, uniform initialization, lambdas, move semantics, smart pointers |
| 02  | [02_Cpp14_Improvements](../solutions/Appendix_B_CppUpdates/02_Cpp14_Improvements) | C++14    | Binary literals, digit separators, generic lambdas, return type deduction, `std::make_unique`                       |
| 03  | [03_Cpp17_Features](../solutions/Appendix_B_CppUpdates/03_Cpp17_Features)         | C++17    | `std::string_view`, `std::optional`, structured bindings, `constexpr if`, CTAD, inline variables                    |
| 04  | [04_Cpp20_Features](../solutions/Appendix_B_CppUpdates/04_Cpp20_Features)         | C++20    | Concepts, designated initializers, spaceship operator (`<=>`), `consteval`, `std::span`                             |
| 05  | [05_Cpp23_Features](../solutions/Appendix_B_CppUpdates/05_Cpp23_Features)         | C++23    | `std::print`, `std::to_underlying`, constexpr math, `if consteval`, deducing this                                   |

> **Path:** `solutions/Appendix_B_CppUpdates/01_Cpp11_KeyFeatures/main.cpp` … `05_Cpp23_Features/main.cpp`

## Quick Reference

| Standard | Year | Theme                  | Key Features                                                             |
| -------- | ---- | ---------------------- | ------------------------------------------------------------------------ |
| C++11    | 2011 | Modern C++ revolution  | `auto`, lambdas, move semantics, smart pointers, `nullptr`, scoped enums |
| C++14    | 2014 | Polish                 | Generic lambdas, binary literals, digit separators, `std::make_unique`   |
| C++17    | 2017 | Practical improvements | `string_view`, `optional`, CTAD, `constexpr if`, structured bindings     |
| C++20    | 2020 | Next big leap          | Concepts, Ranges, Coroutines, Modules, `consteval`, `<=>`                |
| C++23    | 2023 | Refinement             | `std::print`, `std::expected`, constexpr math, deducing this             |

## Key Takeaways

- **Set your compiler to at least C++17** (preferably C++20 or later) to access the most useful modern features
- **Prefer modern idioms**: use `auto` for type deduction, `nullptr` instead of `NULL`/`0`, scoped enums over unscoped, `std::string_view` for read-only string parameters, and smart pointers over raw `new`/`delete`
- **Each standard is cumulative** - every feature from an older standard is still available (unless explicitly removed, like `std::auto_ptr`)
- **Not all compilers support every feature immediately** - always check your compiler's support table for the standard you target
- **`constexpr` has grown with every release** - from basic constant variables in C++11 to `consteval` in C++20 and `constexpr <cmath>` in C++23
- **C++11 and C++20 are the "big leap" standards**; C++14 and C++23 are incremental polishes. Prioritise learning C++11/C++20 features first

## Common Pitfalls

❌ Using a language standard that's too old:

```cpp
// Compiling with -std=c++14 when the code uses C++17 features ❌ confusing errors
```

✅ Use at least C++17 for modern tutorials and libraries.

---

❌ Confusing feature availability across standards:

```cpp
std::optional<int> x; // ❌ doesn't exist in C++14 - it's C++17
auto concept = ...; // ❌ Concepts are C++20
```

✅ Check [cppreference.com](https://en.cppreference.com) for which standard introduced each feature.

---

❌ Ignoring compiler extensions:

```cpp
// Code compiles with GCC extensions but fails on strict-conforming mode ❌
```

✅ Disable extensions (`-pedantic`) and target a specific standard.

---

❌ Still using deprecated features:

```cpp
std::auto_ptr<int> p; // ❌ deprecated C++11, removed C++17
```

✅ Use modern alternatives:

```cpp
std::unique_ptr<int> p; // ✅
```

---

❌ Assuming all C++20/23 features are fully supported:

```cpp
import std; // ❌ Modules have partial/experimental support in many compilers
```

✅ Verify compiler support before relying on cutting-edge features.

---

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What are the major C++ standards and their key features?

<details>
<summary>Show answer</summary>

**Direct answer:** C++11 (auto, lambdas, move semantics, smart pointers, range-for, constexpr, nullptr), C++14 (generic lambdas, relaxed constexpr, variable templates), C++17 (structured bindings, if/switch initializers, std::optional/variant/any, nested namespaces, CTAD), C++20 (concepts, ranges, coroutines, modules, three-way comparison `<=>`), C++23 (std::print, deducing this, std::expected, multidimensional subscript operator).

**Detailed explanation:**
Each standard builds on the previous. C++11 was the largest single update, modernizing the language. C++14 and C++17 were refinements. C++20 was another major release comparable in scope to C++11. C++23 continues incremental improvements.

</details>

2. How do you check which C++ standard your compiler supports?

<details>
<summary>Show answer</summary>

**Direct answer:** Check the `__cplusplus` predefined macro. It returns a long integer: `199711L` (C++98/03), `201103L` (C++11), `201402L` (C++14), `201703L` (C++17), `202002L` (C++20), `202302L` (C++23). MSVC requires `/Zc:__cplusplus` to report the correct value.

**Detailed explanation:**

```cpp
#include <iostream>

int main()
{
    std::cout << "C++ standard: " << __cplusplus << '\n';
    // Prints 202002L if compiled with -std=c++20
}
```

```bash
# MSVC needs the /Zc:__cplusplus flag:
cl /std:c++20 /Zc:__cplusplus main.cpp
```

</details>

3. What is `std::auto_ptr` and why was it deprecated?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::auto_ptr` was C++98's smart pointer that transferred ownership on copy the source pointer was silently set to null. This made it incompatible with STL containers and violated value semantics expectations. It was deprecated in C++11 and removed in C++17. `std::unique_ptr` replaced it with explicit move semantics.

**Detailed explanation:**

```cpp
// auto_ptr (dangerous  copy transfers ownership):
std::auto_ptr<int> a(new int{42});
std::auto_ptr<int> b = a;  // a is now null! (silent ownership transfer)

// unique_ptr (safe  must explicitly move):
std::unique_ptr<int> a = std::make_unique<int>(42);
// std::unique_ptr<int> b = a;           // compile error  can't copy
std::unique_ptr<int> b = std::move(a);   // explicit move  clear intent
```

</details>

4. What are compiler extensions and why should you disable them for portable code?

<details>
<summary>Show answer</summary>

**Direct answer:** Compiler extensions are non-standard features added by specific compilers (GCC, Clang, MSVC) that go beyond the C++ standard. Code using extensions won't compile on other compilers or may behave differently. Disable them with `-pedantic-errors` (GCC/Clang) or `/permissive-` (MSVC) to ensure your code is standard-conformant and portable.

**Detailed explanation:**

```bash
# GCC/Clang: disable extensions
g++ -std=c++20 -pedantic-errors main.cpp

# MSVC: conformance mode (default since VS 2019 16.11)
cl /std:c++20 /permissive- main.cpp
```

Examples of extensions: GCC's variable-length arrays (VLAs) in C++, MSVC's non-standard `for` loop variable scoping, Clang's `__attribute__` keywords.

</details>

5. Name three features introduced in C++17 and three in C++20.

<details>
<summary>Show answer</summary>

**Direct answer:** C++17: (1) structured bindings (`auto [x, y] = pair;`), (2) `if constexpr` for compile-time branching, (3) `std::optional` / `std::variant` / `std::any` vocabulary types. C++20: (1) concepts for constraining templates, (2) ranges library for composable algorithms, (3) the three-way comparison operator `<=>` (spaceship operator).

**Detailed explanation:**

```cpp
// C++17: structured bindings
auto [name, age] = std::pair{"Alice", 30};

// C++17: if constexpr
template <typename T>
void process(T t)
{
    if constexpr (std::is_integral_v<T>)
        std::cout << t * 2;
    else
        std::cout << t;
}

// C++20: concepts
template <std::integral T>
T add(T a, T b) { return a + b; }

// C++20: spaceship operator
auto result = (5 <=> 10);  // std::strong_ordering::less
```

</details>

6. What is the status of C++ Modules support across major compilers?

<details>
<summary>Show answer</summary>

**Direct answer:** As of 2024, modules support is partial across all major compilers. MSVC has the most complete implementation (usable in production). GCC and Clang have experimental support but lack full build-system integration. CMake added initial modules support in 3.28. The standard library module (`import std;`) is available in MSVC and partially in Clang.

**Detailed explanation:**

```cpp
// Module interface unit (modern replacement for headers):
export module math;

export int add(int a, int b) { return a + b; }

// Consumer:
import math;
int result = add(3, 4);  // no #include needed
```

Modules eliminate header inclusion overhead and macro leakage, but adoption is slow due to build-system tooling gaps.

</details>

7. How do you enable a specific C++ standard in GCC, Clang, and MSVC?

<details>
<summary>Show answer</summary>

**Direct answer:** GCC/Clang: `-std=c++17`, `-std=c++20`, `-std=c++23`. MSVC: `/std:c++17`, `/std:c++20`, `/std:c++latest`. CMake: `set(CMAKE_CXX_STANDARD 20)` with `CMAKE_CXX_STANDARD_REQUIRED ON` and `CMAKE_CXX_EXTENSIONS OFF`.

**Detailed explanation:**

```bash
# GCC:
g++ -std=c++20 -Wall -Wextra -Werror -pedantic-errors main.cpp

# Clang:
clang++ -std=c++20 -Wall -Wextra -Werror -pedantic-errors main.cpp

# MSVC:
cl /std:c++20 /W4 /WX /permissive- main.cpp
```

Use `-std=c++2b` (GCC/Clang) or `/std:c++latest` (MSVC) for bleeding-edge features not yet finalized.

</details>

8. What does `-pedantic` do and why is it useful?

<details>
<summary>Show answer</summary>

**Direct answer:** `-pedantic` (GCC/Clang) issues warnings for code that uses compiler extensions or violates the C++ standard. `-pedantic-errors` turns those warnings into hard errors. It's useful because it ensures your code is portable and standards-conformant, catching non-standard constructs that might compile on your system but fail elsewhere.

**Detailed explanation:**

```cpp
// This compiles with GCC by default (VLA is a GCC extension):
int n = 10;
int arr[n];   // variable-length array  not standard C++

// With -pedantic-errors:
// error: ISO C++ forbids variable length array 'arr'
```

```bash
g++ -std=c++20 -pedantic-errors main.cpp
# Now VLAs, zero-length arrays, and other extensions cause errors
```

</details>
