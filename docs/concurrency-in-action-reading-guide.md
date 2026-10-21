# Reading guide: *C++ Concurrency in Action* (2nd Edition)

A short reading plan for `thread.pdf` in the repo root (Anthony Williams, 592 pages). The book is a reference that goes far beyond what an interview tests, so do **not** read it cover to cover. Use the [interactive multithreading lesson](../interactive/07-multithreading.html) and its quiz first, then read the book sections below for the topics where you need more depth.

**Page numbers.** The tables give *PDF viewer* page numbers, the number shown in your PDF reader.

The sections were chosen from the book's table of contents and from reading samples of the chapters.

---

## Tier 1: read these for a solid grasp of the basics (about 47 pages)

| Book section | PDF pages | Matching lesson section |
|---|---|---|
| 1.1 What is concurrency? | 25 to 30 | 1. Why threads? The mental model |
| 1.2.3 When not to use concurrency | 32 to 33 | 1. Why threads? The mental model |
| 2.1 Basic thread management (launching, joining, detaching, waiting in exceptional circumstances, running in the background) | 40 to 47 | 2. Your first thread |
| 2.2 Passing arguments to a thread function | 47 to 50 | 2. Your first thread |
| 3.1 Problems with sharing data between threads (invariants, race conditions) | 60 to 63 | 3. Shared data and data races |
| 3.2.1 to 3.2.3 Mutexes in C++, structuring code to protect data, race conditions inherent in interfaces | 64 to 74 | 4. Mutexes, 5. Races hidden in interfaces |
| 3.2.4 to 3.2.5 Deadlock: the problem, the solution and further guidelines | 74 to 82 | 6. Deadlock |
| 4.1 Waiting for an event: condition variables and a thread-safe queue | 96 to 104 | 8. Condition variables |

## Tier 2: read next if you have time (about 55 pages)

| Book section | PDF pages | Matching lesson section |
|---|---|---|
| 2.4 Choosing the number of threads at runtime | 54 to 57 | 10. Thread pools |
| 3.2.6 to 3.2.8 `std::unique_lock`, transferring mutex ownership, locking granularity | 82 to 87 | 4. Mutexes |
| 3.3.1 Protecting shared data during initialization (`std::call_once`) | 88 to 91 | 12. Debugging and common bugs (vocabulary) |
| 4.2.1 to 4.2.4 Futures: `std::async`, `std::packaged_task`, `std::promise`, saving an exception | 105 to 113 | 9. Futures and async |
| 5.1 Memory model basics, and 5.3 Synchronizing operations through the memory ordering overview | 148 to 151 and 165 to 170 | 7. Atomics |
| 6.1 to 6.2.2 Designing for concurrency, a thread-safe stack and a queue with condition variables | 197 to 206 | 5. Races hidden in interfaces, 8. Condition variables |
| 8.2 Factors affecting the performance of concurrent code (cache ping-pong, false sharing, oversubscription) | 283 to 289 | 11. Performance and real-time concerns |
| 9.1.1 The simplest possible thread pool | 324 to 326 | 10. Thread pools and producer/consumer |
| 11.1 Types of concurrency-related bugs, and 11.2.1 reviewing code to locate them | 363 to 367 | 12. Debugging and common bugs |

## Skip for interview preparation

- Chapter 7, lock-free data structures.
- The rest of chapter 5: fences, release sequences and the remaining orderings.
- 3.3.2 and 3.3.3: reader-writer locks and recursive locking (the lesson covers `shared_mutex` briefly).
- 4.2.5 and 4.3 to 4.4: shared futures, timeouts and the Concurrency TS.
- 6.3, most of chapters 8 to 10, and the appendices, which are lookup material (appendix D is a reference, not reading).

## How to use this guide

1. Work through the multithreading lesson and its quiz.
2. Read the Tier 1 sections that match the lesson sections where you missed questions.
3. Read Tier 2 for any remaining weak spots.

## A note on the edition

This is the 2nd edition (2019), so some features appear under experimental names. Interruptible threads and latches/barriers are now standard in C++20 as `std::jthread` with `std::stop_token`, `std::latch` and `std::barrier`. The Tier 1 and Tier 2 sections above avoid those parts.
