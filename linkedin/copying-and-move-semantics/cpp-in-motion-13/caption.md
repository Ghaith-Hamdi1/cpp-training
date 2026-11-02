# C++ in Motion #13: the Rule of Three — caption

These two lines compile. They still crash.

```
Numbers a(3);
Numbers b = a;
```

It compiles. It may even run. It is still a bug: the compiler copies the pointer, not the memory it points to, so a and b end up owning the same block, and the second destructor frees it again.

Swipe to see why, what the Rule of Three says, and how to avoid the whole problem.

Do you reach for the Rule of Zero or the Rule of Three?

#cpp #cplusplus #programming #learninpublic

## Files

- `cpp-in-motion-13-carousel.pdf` — 7 pages, 4:5, light mode. Upload this as the LinkedIn document.
- `index.html` — source (open it in a browser, or print it to PDF with a page size of 1080 x 1350 px to rebuild the carousel).

## First comment (post it right after publishing)

Code and the full OOP lesson (Rule of 3, 5 and 0): https://github.com/Ghaith-Hamdi1/cpp-training

## Checks done

- The simplified fixed `Numbers` (fixed size of 3, copy constructor, copy assignment, self-assignment) compiled with `g++ -std=c++17 -Wall -Wextra` and printed `7 9 7` (changing `b` leaves `a` alone).
- The `std::vector` (Rule of Zero) version compiled and printed `0 9 0`.
- The version with only a destructor compiled and then crashed with a heap-corruption error on the author's Windows machine (a double delete is undefined behaviour, so the exact symptom varies).

## Source of the idea

Based on the topic of the Stack Overflow question "What is The Rule of Three?" (https://stackoverflow.com/questions/4172722/what-is-the-rule-of-three). The wording, example and code here are written from scratch; nothing is copied from the answers.
