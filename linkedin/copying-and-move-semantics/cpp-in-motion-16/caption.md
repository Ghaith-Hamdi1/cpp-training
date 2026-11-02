# C++ in Motion #16: value categories - caption

Every expression is an lvalue, an xvalue or a prvalue. Not just two kinds.

```
x                // lvalue
std::move(x)     // xvalue
x + 1            // prvalue
```

Since C++11 there are three basic categories. "lvalue" and "rvalue" are also names for groups of them (glvalue and rvalue). Swipe for the three, the two groups, how to ask the compiler, and why it matters.

Which of the three did you not know?

#cpp #cplusplus #programming #learninpublic

## Files

- `cpp-in-motion-16-carousel.pdf` - 6 pages, 4:5, light mode. Upload this as the LinkedIn document.
- `index.html` - source.

## First comment (post it right after publishing)

Full lesson on move semantics and value categories: https://github.com/Ghaith-Hamdi1/cpp-training

## Checks done

Compiled with `g++ -std=c++17 -Wall -Wextra`: `static_assert`s confirmed `decltype((x))`, `decltype((*p))` and `decltype((arr[0]))` are `int&` (lvalues), `decltype(std::move(x))` is `int&&` (xvalue), and `decltype(x + 1)`, `decltype(make())`, `decltype(5)` are non-references (prvalues). A parameter declared `std::string&&` is an lvalue expression inside the function.

## Source of the idea

Based on the topic of the Stack Overflow question "What are rvalues, lvalues, xvalues, glvalues, and prvalues?" (https://stackoverflow.com/questions/3601602/what-are-rvalues-lvalues-xvalues-glvalues-and-prvalues). Wording, diagram and code are written from scratch.
