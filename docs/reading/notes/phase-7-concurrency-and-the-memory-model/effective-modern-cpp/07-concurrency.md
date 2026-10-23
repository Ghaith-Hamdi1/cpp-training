# Session 7: Concurrency

*Effective Modern C++*, Scott Meyers.
Plan: [reading plan](../../../effective-modern-cpp-reading-plan.md). Previous: [session 6](../../phase-3-the-standard-library-and-generic-programming/effective-modern-cpp/06-lambdas.md). Next: none.

- [ ] Read
- [ ] Ran the key example and changed it
- [ ] Answered the checkpoint questions aloud
- [ ] Did the "after" step

Date started:
Date finished:

## What to read (PDF pages)

- Item 35, prefer tasks to threads (pp. 259 to 263)
- Item 36, specify `std::launch::async` if it matters (pp. 263 to 268)
- Item 37, make threads unjoinable on all paths (pp. 268 to 276)
- Item 38, thread handle destructor behaviour (pp. 276 to 280)
- Item 39, void futures for one-shot events (pp. 280 to 289)
- Item 40, `std::atomic` versus `volatile` (pp. 289 to 297)

## Checkpoint questions

Answer each in two sentences, in your own words.

1. **What does the default launch policy risk, and what does a future from `async` do in its destructor?**

   Answer:

2. **Why is a joinable `std::thread` destroyed a `std::terminate`?**

   Answer:

3. **What is `volatile` for, and why is it not a synchronization tool?**

   Answer:

## Notes

Write the key ideas here, in your own words.

-

## Code I wrote

```cpp

```

What surprised me when I ran it:

-

## What surprised me

-

## Still unclear

-

## After this session

Lessons 16 to 18 (Multithreading, Tasks, Atomics) and their quizzes
