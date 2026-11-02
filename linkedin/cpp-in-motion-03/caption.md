# C++ in Motion #3: what && means — caption

In a type, && does not mean "and". It is a new kind of reference.

```
int&  a = x;
int&& b = 5;
```

The second one is an rvalue reference. It binds only to temporaries, and that is what lets a class steal the contents of a temporary instead of copying it.

Swipe for lvalues vs rvalues, why moving is cheap, what std::move really does, and how to write a move constructor.

Do you write move operations yourself or let the compiler do it?

#cpp #cplusplus #programming #learninpublic

## Files

- `cpp-in-motion-03-carousel.pdf` - 6 pages, 4:5, light mode. Upload this as the LinkedIn document.
- `index.html` - source (print it to PDF with a page size of 1080 x 1350 px to rebuild the carousel).

## First comment (post it right after publishing)

Full lesson on move semantics, smart pointers and the Rule of 5: <link to your repo>

## Checks done

- The overload example printed `1: lvalue ref` for a named string and `2: rvalue ref` for a temporary and for `std::move(s)`.
- `std::vector<int> b = std::move(a)` left `a` with size 0 and `b` with size 3.
- The `Numbers` move constructor compiled with `g++ -std=c++17 -Wall -Wextra`; the moved-from object held a null pointer and its destructor ran safely.

## Source of the idea

Based on the topic of the Stack Overflow question "What does T&& (double ampersand) mean in C++11?" (https://stackoverflow.com/questions/5481539/what-does-t-double-ampersand-mean-in-c11). The wording, examples and code are written from scratch; nothing is copied from the answers.
