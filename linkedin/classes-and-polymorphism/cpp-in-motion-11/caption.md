# C++ in Motion #11: object slicing - caption

Copy a Derived into a Base and the Derived part is cut off. That is object slicing.

```
Derived d;
Base b = d;
```

It compiles without a single warning. Swipe for what gets lost, why the virtual call changes too, where it hides, and how to stop it.

Is there a vector<Base> hiding in your code?

#cpp #cplusplus #programming #learninpublic

## Files

- `cpp-in-motion-11-carousel.pdf` - 6 pages, 4:5, light mode. Upload this as the LinkedIn document.
- `index.html` - source.

## First comment (post it right after publishing)

Full OOP lesson (virtual functions, polymorphism, copying): https://github.com/Ghaith-Hamdi1/cpp-training

## Checks done

Compiled with `g++ -std=c++17 -Wall -Wextra` and run: `Base b = d;` then `b.print()` printed "Base"; passing by value, `vector<Base>::push_back` and `catch (Base e)` all sliced and printed "Base"; passing by reference and a `vector<unique_ptr<Base>>` printed "Derived"; with `Base(const Base&) = delete;` the slicing line failed to compile.

## Source of the idea

Based on the topic of the Stack Overflow question "What is object slicing?" (https://stackoverflow.com/questions/274626/what-is-object-slicing). Wording and code are written from scratch.
