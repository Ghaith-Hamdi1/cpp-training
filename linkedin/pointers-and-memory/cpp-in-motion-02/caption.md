# C++ in Motion #2: pointer or object? - caption

In C++, the object itself is the default. A pointer needs a reason.

```
Player a;                  // the default
Player* b = new Player;    // needs a reason
```

Coming from Java or C#, it feels backwards. Swipe for what a pointer costs, the four real reasons to use one, and what to use instead of a raw pointer.

How many raw `new` are in your code?

#cpp #cplusplus #programming #learninpublic

## Files

- `cpp-in-motion-02-carousel.pdf` - 6 pages, 4:5, light mode. Upload this as the LinkedIn document.
- `index.html` - source.

## First comment (post it right after publishing)

Full lesson on pointers, references and smart pointers: https://github.com/Ghaith-Hamdi1/cpp-training

## Checks done

Compiled with `g++ -std=c++17 -Wall -Wextra` and run: returning a `Player` by value, a `unique_ptr<Player>` holding a `Boss` calling the override, and `std::optional<Player>` with and without a value. The dangling `return &p;` version is shown only as a bug.

## Source of the idea

Based on the topic of the Stack Overflow question "Why should I use a pointer rather than the object itself?" (https://stackoverflow.com/questions/22146094/why-should-i-use-a-pointer-rather-than-the-object-itself). Wording and code are written from scratch.
