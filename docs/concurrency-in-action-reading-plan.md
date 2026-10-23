# Reading plan: *C++ Concurrency in Action* (2nd Edition)

An ordered plan for reading the sections that deepen the three concurrency lessons, in seven sessions. The book is a 592-page reference, so this plan reads about 95 pages of it. The reasons behind each pick are in the [reading guide](concurrency-in-action-reading-guide.md).

The book is `books/Cpp-Concurrency-in-Action-2nd-Edition-Williams.pdf`. **All page numbers are PDF viewer pages.** Do the lesson and its quiz for a topic first, then read the matching session.

## The plan at a glance

| # | Session | Book sections | PDF pages | Pages | Time |
|---|---|---|---|---|---|
| 1 | Why threads, and launching them | 1.1; 1.2.3; 2.1; 2.2 | 25 to 30; 32 to 33; 40 to 50 | 18 | 2 h |
| 2 | Sharing data and mutexes | 3.1; 3.2.1 to 3.2.3 | 60 to 74 | 13 | 2 h |
| 3 | Deadlock and locking | 3.2.4 to 3.2.8; 3.3.1 | 74 to 91 | 16 | 2 h |
| 4 | Waiting for events and results | 4.1; 4.2.1 to 4.2.4 | 96 to 113 | 16 | 2 h |
| 5 | How many threads, and a thread pool | 2.4; 9.1.1 | 54 to 57; 324 to 326 | 5 | 1 h |
| 6 | The memory model and data structures | 5.1; 5.3 overview; 6.1 to 6.2.2 | 148 to 151; 165 to 170; 197 to 206 | 17 | 2.5 h |
| 7 | Performance and bugs | 8.2; 11.1 to 11.2.1 | 283 to 289; 363 to 367 | 10 | 1.5 h |

About 95 pages and 13 hours at roughly 10 pages an hour plus the exercises.

## How to read each session

| Step | Do |
|---|---|
| 1. Read | Read the sections with the code closed. Note every claim that contradicts what you assumed. |
| 2. Run | Type in the book's key example and run it under `-fsanitize=thread` (`g++ -std=c++20 -Wall -Wextra -pthread`). |
| 3. Explain | Answer the checkpoint questions aloud. |
| 4. Reinforce | Do the "after" step. |

## Session 1: why threads, and launching them

Read 1.1 What is concurrency (25 to 30), 1.2.3 When not to use concurrency (32 to 33), 2.1 Basic thread management (40 to 47) and 2.2 Passing arguments (47 to 50).

1. What is the difference between concurrency and parallelism, and when is a thread not worth it?
2. Why must a `std::thread` be joined or detached on every path, including when an exception is thrown?
3. Why does `std::thread t(f, 3, buffer)` with a `char` array dangle?

After: Lesson 16, sections "Why threads" and "Your first thread".

## Session 2: sharing data and mutexes

Read 3.1 Problems with sharing data (60 to 63) and 3.2.1 to 3.2.3 Mutexes, structuring code to protect data, race conditions inherent in interfaces (64 to 74).

1. What is an invariant, and why does a race break it?
2. Why is a mutex in every member function not enough?
3. Why does `std::stack` split `top()` and `pop()`?

After: Lesson 16, "Shared data and data races", "Mutexes" and "Races hidden in interfaces".

## Session 3: deadlock and locking

Read 3.2.4 to 3.2.5 Deadlock (74 to 82), 3.2.6 to 3.2.8 `unique_lock`, transferring mutex ownership, locking granularity (82 to 87) and 3.3.1 `std::call_once` (88 to 91).

1. What are the four conditions for a deadlock, and which one does a fixed lock order remove?
2. When do you need `unique_lock` instead of `lock_guard`?
3. How does `call_once` differ from a hand-written double-checked lock?

After: Lesson 16, "Deadlock" and "Other mutex types and call_once".

## Session 4: waiting for events and results

Read 4.1 Condition variables and a thread-safe queue (96 to 104) and 4.2.1 to 4.2.4 `async`, `packaged_task`, `promise` and saving an exception (105 to 113).

1. Why must a condition-variable wait use a predicate?
2. What is the difference between a `promise`, a `packaged_task` and `async`?
3. How does an exception thrown in a task reach the caller?

After: Lesson 16, "Condition variables"; Lesson 17, "Futures and async" and "promise, shared_future and packaged_task".

## Session 5: how many threads, and a thread pool

Read 2.4 Choosing the number of threads at runtime (54 to 57) and 9.1.1 The simplest possible thread pool (324 to 326).

1. Why does adding threads beyond the core count slow CPU-bound work down?
2. In the simple pool, why must the task run outside the lock?

After: Lesson 17, "Thread pools and producer/consumer" and "Work stealing and sizing a pool".

## Session 6: the memory model and data structures

Read 5.1 Memory model basics (148 to 151), the 5.3 overview of synchronizing operations (165 to 170) and 6.1 to 6.2.2 Designing for concurrency, a thread-safe stack and queue (197 to 206).

1. What is a memory location, and what makes two accesses a data race?
2. What does a release store together with an acquire load guarantee?
3. How does the queue with a condition variable avoid the `top()` / `pop()` race?

After: Lesson 18 (Atomics), "Memory orders and happens-before" and "Thread-safe data structures".

## Session 7: performance and bugs

Read 8.2 Factors affecting the performance of concurrent code (283 to 289) and 11.1 to 11.2.1 Types of concurrency bugs and reviewing code (363 to 367).

1. What are cache ping-pong and false sharing, and how do you avoid them?
2. Which bugs does ThreadSanitizer find, and which does it miss?

After: Lesson 20 (Performance and Memory), "Threads, cores and busy-polling"; Lesson 16, "Debugging and common bugs".

## Skip

Chapter 7 (lock-free data structures), the rest of chapter 5 (fences, release sequences), reader-writer locks in 3.3.2 to 3.3.3 (the lesson covers `shared_mutex`), 4.2.5 and 4.3 to 4.4, 6.3, most of chapters 8 to 10, and the appendices. This is the 2nd edition (2019): interruptible threads, latches and barriers are now standard C++20 as `std::jthread` with `std::stop_token`, `std::latch` and `std::barrier`.
