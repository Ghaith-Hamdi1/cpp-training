# C++ in Motion #15: constexpr vs const - caption

const means "I won't change it". constexpr means "the compiler knows it".

```
const int a = std::rand();
constexpr int b = 5 * 2;
```

Both are read-only. Only one of them is known before the program runs. Swipe for the difference, why it matters for array sizes and templates, and constexpr functions.

Do you still use #define for constants?

#cpp #cplusplus #programming #learninpublic

## Files

- `cpp-in-motion-15-carousel.pdf` - 6 pages, 4:5, light mode. Upload this as the LinkedIn document.
- `index.html` - source.

## First comment (post it right after publishing)

Full lesson on constexpr, consteval and compile-time C++: <link to your repo>

## Checks done

Every claim was checked with `g++ -std=c++17 -Wall -Wextra -fsyntax-only`: `const int a = std::rand();` compiles and `constexpr int a = std::rand();` does not; `constexpr int n = 4;` works as an array size and template argument, `const int n = std::rand();` does not; a `const int` with a literal initializer also works as a template argument; a `constexpr` function works in `static_assert` and with a run-time argument, but cannot initialize a `constexpr` variable from a run-time argument.

## Source of the idea

Based on the topic of the Stack Overflow question "What's the difference between constexpr and const?" (https://stackoverflow.com/questions/14116003/whats-the-difference-between-constexpr-and-const). Wording and code are written from scratch.
