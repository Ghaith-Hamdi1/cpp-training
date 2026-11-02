# C++ in Motion #4: why virtual functions - caption

Call through a base pointer and C++ picks the function by the pointer's type. Unless it is virtual.

```
Animal* a = new Dog;
a->speak();    // which speak() runs?
```

Swipe for the answer without virtual, with virtual, how the call finds the right function, and the small print.

Do you mark every override with `override`? It is free.

#cpp #cplusplus #programming #learninpublic

## Files

- `cpp-in-motion-04-carousel.pdf` - 6 pages, 4:5, light mode. Upload this as the LinkedIn document.
- `index.html` - source.

## First comment (post it right after publishing)

Full OOP lesson (virtual functions, vtables, abstract classes): <link to your repo>

## Checks done

Compiled with `g++ -std=c++17 -Wall -Wextra` and run: without `virtual`, `a->speak()` through an `Animal*` to a `Dog` printed `...`; with `virtual` and `override` it printed `Woof`; a vector of `unique_ptr<Animal>` holding a `Dog` and a `Cat` printed `Woof` then `Meow`.

## Source of the idea

Based on the topic of the Stack Overflow question "Why do we need virtual functions in C++?" (https://stackoverflow.com/questions/2391679/why-do-we-need-virtual-functions-in-c). Wording, diagram and code are written from scratch.
