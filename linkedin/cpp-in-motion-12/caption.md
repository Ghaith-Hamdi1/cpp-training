# C++ in Motion #12: virtual destructors - caption

Deleting through a base pointer is undefined behaviour, unless the base destructor is virtual.

```
Base* p = new Derived;
delete p;
```

It compiles without a warning and it usually runs. In my test only ~Base ran, so everything Derived owned leaked.

Swipe for what happens, the one-keyword fix, when you need it, and what it costs.

Is -Wnon-virtual-dtor on in your build?

#cpp #cplusplus #programming #learninpublic

## Files

- `cpp-in-motion-12-carousel.pdf` - 6 pages, 4:5, light mode. Upload this as the LinkedIn document.
- `index.html` - source (print it to PDF with a page size of 1080 x 1350 px to rebuild the carousel).

## First comment (post it right after publishing)

Full OOP lesson (virtual functions, vtables, Rule of 0/3/5): <link to your repo>

## Checks done

Compiled with `g++ -std=c++17 -Wall -Wextra` and run:

- Without `virtual`: only `~Base` was printed (the standard calls this undefined behaviour; this is what the compiler did).
- With `virtual`: `~Derived` then `~Base`.
- `sizeof` of an `int`-only struct is 4, with a virtual destructor it is 16 (64-bit build).

## Source of the idea

Based on the topic of the Stack Overflow question "When to use virtual destructors?" (https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors). Wording, examples and code are written from scratch.
