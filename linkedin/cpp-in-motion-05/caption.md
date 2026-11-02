# C++ in Motion #5: const after a member function - caption

The const after a member function's parentheses is a promise: it will not change the object.

```
int size() const;
```

Easy to forget, and it breaks code that has nothing to do with it. Swipe for what it means, who can call it, overloading on const, and mutable.

How many of your getters are missing const?

#cpp #cplusplus #programming #learninpublic

## Files

- `cpp-in-motion-05-carousel.pdf` - 6 pages, 4:5, light mode. Upload this as the LinkedIn document.
- `index.html` - source.

## First comment (post it right after publishing)

Full OOP lesson (classes, const-correctness, member functions): <link to your repo>

## Checks done

Checked with `g++ -std=c++17 -Wall -Wextra -fsyntax-only`: modifying a member in a const function fails, reading works; a const object can call const functions and cannot call non-const ones; a non-const getter cannot be called through `const&`; a `mutable` counter and a `mutable std::mutex` compile in a const function while a non-mutable mutex does not. The `at()` overload pair was compiled and run: the non-const object picked the non-const version and the const object picked the const version.

## Source of the idea

Based on the topic of the Stack Overflow question "What is the meaning of 'const' at the end of a member function declaration?" (https://stackoverflow.com/questions/751681/what-is-the-meaning-of-const-at-the-end-of-a-member-function-declaration). Wording and code are written from scratch.
