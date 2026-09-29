# Multi-threading and threads synchronization

(Slides 61–79)

- Threads management and concurrency support:
  - Create and manage threads
  - Atomic operations
  - Mutual exclusion
  - Condition variables
  - Futures and promises

## How these five topics fit together

- **Threads** (`std::thread`): the unit of concurrent execution, runs independently until its entry function returns, joined or detached
- Two threads touching the same memory → potential **race condition** (result depends on timing); if at least one access is a write with no synchronization → **data race** = undefined behavior in C++, not just "probably fine"
- Three complementary tools, each suited to a different job:
  - **Mutual exclusion** (`std::mutex` and friends) — run a whole critical section on one thread at a time
  - **Atomic variables** (`std::atomic<T>`) — make one read/write/read-modify-write on a single variable indivisible, no full lock needed; cheaper for simple counters/flags, easy to misuse for anything more complex
  - **Condition variables** and **futures/promises** — let one thread *wait* for another to reach a state or produce a result, without a polling loop
- Rule of thumb: mutexes/atomics answer "how do I touch shared data safely?"; condition variables/futures answer "how do I wait for something to happen?"

## Further reading

The explanations in this section have been deepened with concepts, terminology and best practices drawn from *C++ Concurrency in Action*, 2nd edition, by Anthony Williams (Manning, 2019) — a widely recommended, in-depth reference for the C++ Thread Library and memory model. It goes considerably further than this training deck (lock-free data structures, thread pools, the full memory-ordering model, parallel algorithms) for anyone who wants to go deeper after this module.

