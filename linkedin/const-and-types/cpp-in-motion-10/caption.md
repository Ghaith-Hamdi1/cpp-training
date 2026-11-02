# C++ in Motion #10: the four casts - caption

A C-style cast quietly picks a cast for you. C++ makes you name it.

```
Derived* d = (Derived*)b;
```

Which cast did the compiler choose here? You cannot tell by reading it.

Swipe for what each of static_cast, dynamic_cast, const_cast and reinterpret_cast is for, and what goes wrong with each.

How many C-style casts are in your codebase?

#cpp #cplusplus #programming #learninpublic

## Files

- `cpp-in-motion-10-carousel.pdf` - 6 pages, 4:5, light mode. Upload this as the LinkedIn document.
- `index.html` - source (print it to PDF with a page size of 1080 x 1350 px to rebuild the carousel).

## First comment (post it right after publishing)

Full lesson on types, initialization and casts: https://github.com/Ghaith-Hamdi1/cpp-training

## Checks done

All compiled with `g++ -std=c++17 -Wall -Wextra` and run:

- `static_cast<int>(3.9)` gave 3, and the `Base*` to `Derived*` static downcast of a real `Derived` worked.
- `dynamic_cast<Derived*>` returned `nullptr` for an `Other` object and a valid pointer for a real `Derived`.
- `const_cast<char*>` on a string literal passed to a function that only reads it worked.
- `reinterpret_cast<const unsigned char*>(&x)` read the first byte of an `int` (4 on this little-endian machine).

## Source of the idea

Based on the topic of the Stack Overflow question "When should static_cast, dynamic_cast, const_cast and reinterpret_cast be used?" (https://stackoverflow.com/questions/332030/when-should-static-cast-dynamic-cast-const-cast-and-reinterpret-cast-be-used). Wording, examples and code are written from scratch.
