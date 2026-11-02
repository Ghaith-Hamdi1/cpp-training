# C++ in Motion #9: lambdas - caption

A lambda is a function you write right where you need it.

```
std::sort(v.begin(), v.end(),
          [](int a, int b) { return a > b; });
```

No separate function, no name, just the logic in place. Swipe for the three parts, the capture list, where lambdas shine, and the one trap to avoid.

Do you write [=] or list each capture?

#cpp #cplusplus #programming #learninpublic

## Files

- `cpp-in-motion-09-carousel.pdf` - 6 pages, 4:5, light mode. Upload this as the LinkedIn document.
- `index.html` - source.

## First comment (post it right after publishing)

Full lesson on lambdas and callables: <link to your repo>

## Checks done

Compiled with `g++ -std=c++17 -Wall -Wextra` and run: the descending sort gave 9 first and 1 last; `count_if` with `[limit]` (limit 3) counted 4 numbers above 3; a by-value capture kept its value (10) while a by-reference capture saw the later change (30); the by-value `make()` returned 5; the lambda was converted to a `std::function`. The dangling `[&n]` version is shown only as a bug.

## Source of the idea

Based on the topic of the Stack Overflow question "What is a lambda expression, and when should I use one?" (https://stackoverflow.com/questions/7627098/what-is-a-lambda-expression-and-when-should-i-use-one). Wording and code are written from scratch.
