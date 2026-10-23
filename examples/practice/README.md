# Practice set: write it yourself

Seventeen "implement this function or class" exercises, short and focused, to be written without looking things up. Each folder has:

- `exercise.cpp`: the task in a comment at the top, a stub for you to fill in, and a set of tests in `main`.
- `solution.cpp`: a worked solution that passes the same tests. Look only after you have tried.

```bash
cd examples/practice/01-build-execution-id
g++ -std=c++17 -Wall -Wextra -pthread exercise.cpp -o ex && ./ex
```

The program prints which checks failed, and `all checks passed` when you are done. It exits with status 0 only when everything passes. Every solution here was compiled with no warnings and run; the exercises compile as given and fail until you write the code.

## How to practise (this is the part that matters)

1. **Set a timer.** 15 minutes for the string exercises, 25 for the classes and threads.
2. **Talk out loud while you write**, as if explaining to a colleague: what you allocate, why that size, what each line does. Silence reads as "no idea", even when you are thinking.
3. **Plan before typing.** For string functions: how long is each input, how many bytes do I need (do not forget the `'\0'`), who frees the result.
4. **A wrong but reasoned attempt scores better than a blank.** If you forget a library function, write the loop by hand.
5. After passing, **compare with the solution** and note anything you did differently.
6. Redo the ones you could not finish unaided, a day later, from a blank file.

## The exercises

| # | Exercise | Skills | Level |
|---|---|---|---|
| 01 | `buildExecutionId`: join two C strings into a new one | `new[]`, `strlen`, `memcpy`/`strcpy`/`strcat`, the terminating `'\0'`, ownership | a classic C-string exercise |
| 02 | `copyString`: your own `strdup` | allocate `len + 1`, independent copy | easy |
| 03 | `reversed`: reverse a C string into a new one | indexing, off-by-one | easy |
| 04 | `joinAll`: join many strings with a separator | two passes (measure, then copy), no repeated `strcat` | medium |
| 05 | `myStrlen`, `myStrcmp` | pointer walking, pointer subtraction, prefix rule | easy |
| 06 | `countWords` | state flag, edge cases (empty, only spaces) | easy |
| 07 | `parseUnsigned`: text to a number with overflow detection | digit math, error handling, no change on failure | medium |
| 08 | `trimmed`: strip whitespace at both ends | two pointers, `new[]` | medium |
| 09 | `maxOf`, `swapInts`, `reverseInPlace`, `countIf` | pointers, arrays, function pointers | easy |
| 10 | `MyString`: a string class that owns its memory | Rule of Five, deep copy, moves, self-assignment, `noexcept` | hard |
| 11 | Shapes: abstract base, virtual destructor | polymorphism, why the destructor must be virtual | medium |
| 12 | `Stack<T>`: a class template | templates, `std::move`, move-only types | medium |
| 13 | `SafeCounter` | `std::mutex`, `lock_guard`, `mutable` | easy |
| 14 | `BoundedQueue<T>` | condition variables, predicates, back-pressure | hard |
| 15 | `parsePort`, `parseValue`, `describe` | `optional`, `variant`, `std::visit`, `from_chars` (lesson 3, Vocabulary Types) | medium |
| 16 | `Summable` concept, `sumAll`, `kind` | `requires`, constrained templates, overloading by concept (lesson 13) | medium |
| 17 | `BucketTable`: an array indexed by key | O(1) updates, tracking the highest bucket, checking against `std::map` (lesson 20) | medium |

Suggested order if you have limited time: 01, 02, 03, 05, 06, 07, then 10, 11, 14. Exercises 15 to 17 compile with `-std=c++20`.

## Questions with model answers

Say these aloud until they come out fluently.

**1. "Implement `buildExecutionId(sender, sequence)` returning `sender-sequence` as a new C string."** Exercise 01. The plan to say: "I need a new buffer big enough for both strings, the dash and the terminator: `strlen(a) + 1 + strlen(b) + 1`. I allocate it with `new char[...]` because the caller frees with `delete[]`. I copy the first string, write the dash, copy the second string including its `'\0'`, and return the pointer."

**2. "Explain polymorphism and how `virtual` works in memory."**

> A class with virtual functions has a **vtable**: one table of function pointers per class, in static memory. Every object of that class carries a hidden **vptr**, set by the constructor, that points at its class's vtable. A call through a base pointer follows the object's vptr to the vtable, looks up the function's slot and jumps to it. So the real object's version runs, not the pointer type's. The cost is one extra pointer per object and one indirection per call, and the call usually cannot be inlined.

Follow-ups they may ask: a derived class gets its own vtable with overridden entries replaced; a constructor cannot be virtual (the vptr is not set yet); inside a base constructor a virtual call runs the base version; slicing loses the derived part and its vptr; a base class with virtual functions needs a virtual destructor. See the OOP lesson, "Polymorphism and virtual functions", and exercise 11.

**3. "If you call a function that is defined outside any class, does it compile?"** Yes. C++ is not purely object-oriented: free functions (at namespace or file scope) are normal, and `main` itself is one. The only requirement is that the function is declared before the call. Say so plainly, and mention the standard library's `std::sort` and `std::swap` as examples.
