# C++ in Motion #12: public, protected and private inheritance - caption

One keyword decides who can see the base class.

```
class A : public    Base {};
class B : protected Base {};
class C : private   Base {};
```

Same class, three very different relationships. Swipe for what the base's members become, and when to use each.

When did you last use private inheritance?

#cpp #cplusplus #programming #learninpublic

## Files

- `cpp-in-motion-12-carousel.pdf` - 6 pages, 4:5, light mode. Upload this as the LinkedIn document.
- `index.html` - source.

## First comment (post it right after publishing)

Full lesson on the object model, inheritance and composition: <link to your repo>

## Checks done

Every access claim was checked with `g++ -std=c++17 -fsyntax-only`: public members and base conversion work with public inheritance; with protected inheritance they fail outside the class but work in subclasses; with private inheritance they fail outside and in subclasses but work inside the class; the base's private members are never accessible; a class inheriting privately from `std::vector<int>` hides `push_back`; `class` defaults to private inheritance and `struct` to public.

## Source of the idea

Based on the topic of the Stack Overflow question "What is the difference between public, private, and protected inheritance in C++?" (https://stackoverflow.com/questions/860339/what-is-the-difference-between-public-private-and-protected-inheritance). Wording and code are written from scratch.
