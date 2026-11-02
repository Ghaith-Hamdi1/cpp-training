# C++ in Motion #13: when to use std::move - caption

std::move is for the last time you use a variable. Not for returns.

```
std::string s = read();
names.push_back(std::move(s));
// s is finished
```

Knowing when to write it matters more than knowing what it is. Swipe for where it helps, the return mistake, what a moved-from object is, and why moving a const copies.

Have you ever written `return std::move(x);`? Be honest.

#cpp #cplusplus #programming #learninpublic

## Files

- `cpp-in-motion-13-carousel.pdf` - 6 pages, 4:5, light mode. Upload this as the LinkedIn document.
- `index.html` - source.

## First comment (post it right after publishing)

Full lesson on move semantics (Rule of 5, noexcept, returns table): <link to your repo>

## Checks done

Compiled with `g++ -std=c++17 -Wall -Wextra` and run, using a type that prints "copy" and "move": `return std::move(x);` produced a move and a `-Wpessimizing-move` warning, while `return x;` produced no output at all (copy elided); moving from a `const` object printed "copy", moving from a non-const one printed "move"; after `push_back(std::move(s))` on a long string, `s.size()` was 0 on this implementation; the `Person` constructor with `std::move(n)` worked.

## Source of the idea

Based on the topic of the Stack Overflow question "What is std::move(), and when should it be used?" (https://stackoverflow.com/questions/3413470/what-is-stdmove-and-when-should-it-be-used). Wording and code are written from scratch. Related to carousels #3 and #10 (rvalue references and value categories).
