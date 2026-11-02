# C++ in Motion #17: forwarding references - caption

Sometimes T&& is not an rvalue reference. It binds to anything.

```
void f(std::string&& s);       // only temporaries

template <class T>
void g(T&& x);                 // anything
```

In a template, T&& with a deduced T is a forwarding reference. It keeps the information of whether the argument was an lvalue or an rvalue, and std::forward passes it on.

Swipe for when it applies, what T becomes, why a plain f(x) loses the information, and the make_unique pattern.

Which one do you mix up: std::move or std::forward?

#cpp #cplusplus #programming #learninpublic

## Files

- `cpp-in-motion-17-carousel.pdf` - 6 pages, 4:5, light mode. Upload this as the LinkedIn document.
- `index.html` - source (print it to PDF with a page size of 1080 x 1350 px to rebuild the carousel).

## First comment (post it right after publishing)

Full lesson on templates, move semantics and perfect forwarding: <link to your repo>

## Checks done

All compiled with `g++ -std=c++17 -Wall -Wextra` and run:

- `wrap` without `std::forward` called the lvalue overload for both a named string and a temporary; with `std::forward` the temporary reached the rvalue overload.
- `g(n)` deduced `T = int&` and `g(5)` deduced `T = int` (checked with `std::is_lvalue_reference_v`).
- The `make` function called the `const&` constructor for an lvalue and the `&&` constructor for a temporary.
- `auto&& r = n;` has type `int&` (static_assert).

## Source of the idea

Follow-up to carousel #15, based on the second half of the Stack Overflow question "What does T&& (double ampersand) mean in C++11?" (https://stackoverflow.com/questions/5481539/what-does-t-double-ampersand-mean-in-c11). Wording, examples and code are written from scratch.
