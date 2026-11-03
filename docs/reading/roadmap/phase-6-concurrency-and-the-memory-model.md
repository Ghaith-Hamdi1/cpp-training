# Phase 6: Concurrency and the memory model

[Roadmap](README.md) | Previous: [Phase 5: Modern C++ (C++11 to C++20)](phase-5-modern-cpp.md)

*Threads, mutexes, condition variables, futures and pools, atomics.*

**Time:** about **17.7 hours** (10.9 h reading, 5.9 h lessons and quizzes, 0.8 h exercises), plus 3.9 h if you also read the deepen list.

## Big topics

| Topic | What it covers |
|---|---|
| **Threads and data races** | Launching, joining, passing arguments, shared data, what a data race is. |
| **Mutexes and deadlock** | `lock_guard`, `unique_lock`, `scoped_lock`, interface races, deadlock and lock ordering. |
| **Condition variables and queues** | Waiting with a predicate, lost wakeups, a thread-safe queue. |
| **Tasks, futures and pools** | `async`, `promise`, `packaged_task`, thread pools, work stealing, `latch`/`barrier`/`jthread`. |
| **Atomics and the memory model** | `std::atomic`, compare-and-swap, memory orders, happens-before, lock-free structures. |

## Core reading (109 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| Concurrency in Action | Why threads and launching them: 1.1, 1.2.3, 2.1, 2.2 | 25 to 30; 32 to 33; 40 to 50 | 19 | The model and the basic API |
| Concurrency in Action | Sharing data and mutexes: 3.1, 3.2.1 to 3.2.3 | 60 to 74 | 15 | Invariants, race conditions inherent in interfaces |
| Concurrency in Action | Deadlock and locking: 3.2.4 to 3.2.8, 3.3.1 | 74 to 91 | 18 | Lock ordering, `unique_lock`, `call_once` |
| Concurrency in Action | Waiting for events and results: 4.1, 4.2.1 to 4.2.4 | 96 to 113 | 18 | Condition variables, futures, `promise` |
| Concurrency in Action | Thread counts and a pool: 2.4, 9.1.1 | 54 to 57; 324 to 326 | 7 | How many threads; the simplest pool |
| Concurrency in Action | The memory model and data structures: 5.1, 5.3 overview, 6.1 to 6.2.2 | 148 to 151; 165 to 170; 197 to 206 | 20 | Memory locations, orderings, a thread-safe stack and queue |
| Concurrency in Action | Performance and bugs: 8.2, 11.1 to 11.2.1 | 283 to 289; 363 to 367 | 12 | False sharing, oversubscription, kinds of concurrency bug |

## Deepen (optional, 39 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| EMC | Items 35 to 40: tasks, launch policies, joining, futures, one-shot events, `atomic` versus `volatile` | 259 to 297 | 39 | A compact second opinion on the same ground |

## Lessons and exercises

| Lesson | Time |
|---|---|
| [29. Threads: The Mental Model and Your First Thread](https://ghaith-hamdi1.github.io/cpp-training/07-multithreading.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/07-multithreading-quiz.html) | 30 min |
| [30. Shared Data and Data Races](https://ghaith-hamdi1.github.io/cpp-training/38-races.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/38-races-quiz.html) | 30 min |
| [31. Mutexes and Locking](https://ghaith-hamdi1.github.io/cpp-training/39-mutexes.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/39-mutexes-quiz.html) | 45 min |
| [32. Deadlock](https://ghaith-hamdi1.github.io/cpp-training/40-deadlock.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/40-deadlock-quiz.html) | 30 min |
| [33. Condition Variables and Debugging](https://ghaith-hamdi1.github.io/cpp-training/41-condvars.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/41-condvars-quiz.html) | 40 min |
| [34. Futures, async and Promises](https://ghaith-hamdi1.github.io/cpp-training/17-tasks-parallelism.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/17-tasks-parallelism-quiz.html) | 40 min |
| [35. Thread Pools, Coordination and Parallel Algorithms](https://ghaith-hamdi1.github.io/cpp-training/42-pools.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/42-pools-quiz.html) | 50 min |
| [36. Atomics and Compare-and-Swap](https://ghaith-hamdi1.github.io/cpp-training/18-atomics-memory-model.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/18-atomics-memory-model-quiz.html) | 35 min |
| [37. The Memory Model: Orders and Happens-Before](https://ghaith-hamdi1.github.io/cpp-training/43-memmodel.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/43-memmodel-quiz.html) | 55 min |

Exercises: 13 (`SafeCounter`) and 14 (`BoundedQueue<T>`).

> C++ Primer and Programming: Principles and Practice have no chapters on threads. Concurrency in Action is the main book; Effective Modern C++ items 35 to 40 are the short version.

**Recap check.** Explain: what a data race is and why it is undefined behavior, why a mutex per method is not enough, the four conditions for deadlock, why `wait` needs a predicate, what release and acquire guarantee, and what the ABA problem is.

**Notes templates.** [Reading notes for phase 6](../notes/phase-6-concurrency-and-the-memory-model/README.md).

---

[Roadmap](README.md) | Previous: [Phase 5: Modern C++ (C++11 to C++20)](phase-5-modern-cpp.md)
