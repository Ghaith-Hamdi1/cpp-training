# C++ in Motion #17: dereferencing a pointer - caption

*p means: go to the address stored in p. Then use what is there.

```
int x = 7;
int* p = &x;
int y = *p;   // 7
```

That is dereferencing. Swipe for what is in memory, reading and writing through a pointer, the arrow operator, and what goes wrong.

Where do you still need a raw *?

#cpp #cplusplus #programming #learninpublic

## Files

- `cpp-in-motion-17-carousel.pdf` - 6 pages, 4:5, light mode. Upload this as the LinkedIn document.
- `index.html` - source.

## First comment (post it right after publishing)

Full lesson on pointers, references and memory: <link to your repo>

## Checks done

Compiled with `g++ -std=c++17 -Wall -Wextra` and run: `int y = *p;` gave 7; after `*p = 9;` x was 9 and y stayed 7; `(*q).hp` and `q->hp` read the same member; `p == &x` was true; `&p` differs from `p`. The undefined-behaviour cases (null, uninitialized, dangling) are described, not run. The memory diagram uses made-up addresses.

## Source of the idea

Based on the topic of the Stack Overflow question "What does dereferencing a pointer mean in C/C++?" (https://stackoverflow.com/questions/4955198/what-does-dereferencing-a-pointer-mean-in-c-c). Wording, diagram and code are written from scratch.
