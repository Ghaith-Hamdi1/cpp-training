# C++ in Motion #8: const and pointers - caption

Three consts, three meanings. Read them right to left.

```
const int* a;
int* const b;
const int* const c;
```

They look almost the same. They are three different rules. Swipe for how to read them, what each one lets you change, and where you meet them.

Which do you write: const int* or int const*?

#cpp #cplusplus #programming #learninpublic

## Files

- `cpp-in-motion-08-carousel.pdf` - 6 pages, 4:5, light mode. Upload this as the LinkedIn document.
- `index.html` - source.

## First comment (post it right after publishing)

Full lesson on pointers and const-correctness: https://github.com/Ghaith-Hamdi1/cpp-training

## Checks done

Every row of the "what you can change" table was checked with `g++ -std=c++17 -fsyntax-only` (assigning to the pointer and to the value, for all three declarations), plus: `const int*` and `int const*` are interchangeable, `int*` converts to `const int*`, and `const int*` does not convert back to `int*`.

## Source of the idea

Based on the topic of the Stack Overflow question "What is the difference between const int*, const int * const, and int const *?" (https://stackoverflow.com/questions/1143262/what-is-the-difference-between-const-int-const-int-const-and-int-const). Wording and code are written from scratch.
