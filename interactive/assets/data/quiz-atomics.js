/* Quiz questions for the 'atomics' topic. Loaded by 18-atomics-memory-model-quiz.html. */
CT.quizData.atomics = {
  id: 'atomics',
  questions: [
    { sec: 'ops', q: 'When is `std::atomic` NOT enough on its own?',
      opts: ['Incrementing a single shared counter from many threads', 'A flag that tells a worker thread to stop', 'An invariant over several variables that must change together', 'Publishing a pointer to data that is already finished'], a: 2,
      why: 'Atomics make operations on one variable indivisible. Updating two related variables consistently needs a mutex (or a single atomic holding both).' },

    { sec: 'ops', q: 'Is `volatile` a valid way to share a flag between threads in C++?',
      opts: ['Yes: it guarantees that other threads will see the new value at once', 'No: it gives no atomicity or ordering between threads; use std::atomic', 'Yes, but only for variables of type bool or char on most targets', 'Yes, but only on x86 processors with their strong memory ordering'], a: 1,
      why: 'Concurrent access to a `volatile` variable is still a data race. `volatile` is for memory-mapped hardware, not thread synchronization.' },

    { sec: 'ordering', q: 'What is the default memory order of `std::atomic` operations, and what does it mean?',
      opts: ['relaxed: there is no ordering between the threads', 'seq_cst: one global order for all threads (strongest, simplest)', 'acquire, which is applied to loads only by default in C++', 'release, which is applied to stores only by default in C++'], a: 1,
      why: 'Sequential consistency is the default because it is the easiest to reason about. Weaker orders are an optimisation that needs justification.' },

    { sec: 'ordering', q: 'What does this guarantee?',
      code: String.raw`
int data = 0;
std::atomic<bool> ready{false};

// thread 1
data = 42;
ready.store(true, std::memory_order_release);

// thread 2
while (!ready.load(std::memory_order_acquire)) {}
std::cout << data;`,
      opts: ['It may print 0 or 42, depending on how the threads are scheduled', 'It prints 42: the release store publishes earlier writes to the acquire load', 'It is a data race with undefined behavior on the shared data', 'It prints nothing because the consumer loop never ends'], a: 1,
      why: 'A release store paired with an acquire load that observes it creates a happens-before edge, so the write to `data` is visible. With relaxed ordering this would not be guaranteed.' },

    { sec: 'ops', q: 'What does `compare_exchange_weak(expected, desired)` do when the current value is not equal to `expected`?',
      opts: ['Sets the value to desired anyway and returns true', 'Returns false and loads the current value into expected', 'Throws an exception to report the mismatch to the caller', 'Returns true and leaves expected completely unchanged'], a: 1,
      why: 'On failure it refreshes `expected` with the value it actually saw, so a retry loop can recompute from it.' },

    { sec: 'ops', q: 'Why is `compare_exchange_weak` normally used inside a loop?',
      opts: ['It is faster than a mutex, so it is preferred', 'It may fail spuriously even when the values match', 'It cannot be called more than once on the same atomic object', 'It blocks until the swap finally succeeds, like a lock does'], a: 1,
      why: '`weak` is allowed to fail spuriously (cheaper on some CPUs). `compare_exchange_strong` fails only on a real mismatch.' },

    { sec: 'ops', q: 'What is the ABA problem?',
      opts: ['A CAS succeeds because the value is A again, though it went through B', 'Two threads sharing the same atomic variable at the same moment', 'A deadlock between two mutexes locked in opposite orders', 'A compiler bug that is triggered by the volatile keyword'], a: 0,
      why: 'The value looks unchanged, so the CAS succeeds, but a node may have been freed and reused in between. Fix with a version counter or hazard pointers.' },

    { sec: 'ops', q: 'Which standard atomic type is guaranteed to be lock-free?',
      opts: ['`std::atomic<std::string>`', '`std::atomic_flag`', '`std::atomic<std::vector<int>>`', 'All of them'], a: 1,
      why: '`std::atomic_flag` is the only type the standard requires to be lock-free. Others depend on the type and platform (`is_lock_free()`).' },

    { sec: 'ordering', q: 'Which pair of orders publishes data written before a store to a thread that reads the stored value?',
      opts: ['Both operations use relaxed', 'A release store and an acquire load', 'An acquire store and a release load', 'Only volatile reads and writes'], a: 1,
      why: 'The release store and acquire load synchronize-with each other, so earlier writes happen-before the reader\'s later reads.' },

    { sec: 'ordering', q: 'A producer stores the flag with `release`, but the consumer loads it with `relaxed`. What is guaranteed about the data written before the store?',
      opts: ['It is visible, because the store was a release operation on the flag', 'Nothing: without an acquire on the reading side there is no ordering', 'It is visible on x86 only, not on weaker architectures such as ARM', 'The program does not compile when memory orders are mixed like this'], a: 1,
      why: 'Both sides must take part. A relaxed load does not synchronize, so reading the data afterwards can be a data race.' },

    { sec: 'ordering', q: 'What does "A happens-before B" mean?',
      opts: ['A starts earlier than B in wall-clock time', 'A\'s effects are guaranteed to be visible to B', 'A and B run on the same processor core', 'A runs faster than B on the same machine'], a: 1,
      why: 'It is the memory model\'s visibility relation: program order within a thread, plus the edges created by synchronization (atomics, mutexes, join, futures).' },

    { sec: 'ordering', q: 'Why can code with a wrong memory order seem to work on x86 and fail on ARM?',
      opts: ['x86 has no caches that could reorder the memory accesses', 'x86 already gives release/acquire ordering; ARM reorders more', 'ARM does not support atomic operations', 'Compilers only optimise code aggressively for ARM targets'], a: 1,
      why: 'The C++ memory model, not the machine you test on, defines correctness. x86 hides some missing orderings.' },

    { sec: 'patterns', q: 'Which orders suit the decrement of a reference count where the thread that drops it to zero deletes the object?',
      opts: ['relaxed on both the increment and the decrement of the count', 'acq_rel, so the last thread sees all other writes before deleting', 'release only, applied to the load of the counter value', 'No atomic is needed for a reference count in C++'], a: 1,
      why: 'Increments can be relaxed, but the decrement must acquire what the other owners released before the object is destroyed.' },

    { sec: 'patterns', q: 'Which memory order is normally enough for a statistics counter that nothing else depends on?',
      opts: ['`seq_cst`', '`relaxed`', '`acquire`', '`release`'], a: 1,
      why: 'Only atomicity is needed: the final total is right and no other data is published through the counter.' },

    { sec: 'structures', q: 'Why does the two-lock queue keep a dummy node?',
      opts: ['To save memory when the queue is empty most of the time', 'A push touches only the tail and a pop only the head', 'To make the queue lock-free without any other change', 'To keep the elements stored in the queue sorted'], a: 1,
      why: 'With a permanent dummy node, head and tail never point at the same real node, so each end can have its own mutex.' },

    { sec: 'structures', q: 'Why is a lock-free pop much harder to write than a lock-free push?',
      opts: ['Pop needs more arguments than push does, so it is slower', 'Another thread may free the node you read, and ABA can corrupt the list', 'Pop cannot use atomic operations, so it must use a mutex', 'Push is not lock-free either in this design, only pop is'], a: 1,
      why: 'Push only links a node you own. Pop reads and frees nodes other threads may still be using, which needs hazard pointers, epochs or counted pointers.' },

    { sec: 'structures', q: 'What is the difference between lock-free and wait-free?',
      opts: ['There is no difference between the two terms, both mean lock-free', 'Lock-free: some thread always progresses; wait-free: all do, in bounded steps', 'Wait-free algorithms use mutexes to bound the waiting time for threads', 'Lock-free means that no atomic operations are used by the algorithm'], a: 1,
      why: 'Wait-free is the stronger guarantee: no thread can be starved indefinitely by others.' }
  ]
};
