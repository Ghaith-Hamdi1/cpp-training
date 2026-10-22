/* Quiz questions for the 'atomics' topic. Loaded by 18-atomics-memory-model-quiz.html. */
CT.quizData.atomics = {
  id: 'atomics',
  questions: [
    { sec: 'ops', q: 'When is `std::atomic` NOT enough on its own?',
      opts: ['For a counter', 'For a stop flag', 'When an invariant spans several variables that must change together', 'For a pointer swap'], a: 2,
      why: 'Atomics make operations on one variable indivisible. Updating two related variables consistently needs a mutex (or a single atomic holding both).' },

    { sec: 'ops', q: 'Is `volatile` a valid way to share a flag between threads in C++?',
      opts: ['Yes, it guarantees visibility', 'No: it gives no atomicity or inter-thread ordering; use std::atomic', 'Yes, but only for bool', 'Yes, on x86 only'], a: 1,
      why: 'Concurrent access to a `volatile` variable is still a data race. `volatile` is for memory-mapped hardware, not thread synchronization.' },

    { sec: 'ordering', q: 'What is the default memory order of `std::atomic` operations, and what does it mean?',
      opts: ['relaxed: no ordering', 'seq_cst: all threads agree on a single global order of atomic operations (strongest and simplest)', 'acquire for loads only', 'release for stores only'], a: 1,
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
      opts: ['It may print 0 or 42', 'It prints 42: the release store publishes everything written before it to a thread whose acquire load sees true', 'It is a data race', 'It prints nothing'], a: 1,
      why: 'A release store paired with an acquire load that observes it creates a happens-before edge, so the write to `data` is visible. With relaxed ordering this would not be guaranteed.' },

    { sec: 'ops', q: 'What does `compare_exchange_weak(expected, desired)` do when the current value is not equal to `expected`?',
      opts: ['Sets the value to `desired` anyway', 'Returns false and loads the current value into `expected`', 'Throws', 'Returns true'], a: 1,
      why: 'On failure it refreshes `expected` with the value it actually saw, so a retry loop can recompute from it.' },

    { sec: 'ops', q: 'Why is `compare_exchange_weak` normally used inside a loop?',
      opts: ['It is faster than a mutex', 'It may fail spuriously even when the values match', 'It cannot be called twice', 'It blocks until it succeeds'], a: 1,
      why: '`weak` is allowed to fail spuriously (cheaper on some CPUs). `compare_exchange_strong` fails only on a real mismatch.' },

    { sec: 'ops', q: 'What is the ABA problem?',
      opts: ['A CAS succeeds because the value is A again, although it changed to B and back, and the structure around it has changed', 'Two threads using the same atomic', 'A deadlock between two mutexes', 'A compiler bug with `volatile`'], a: 0,
      why: 'The value looks unchanged, so the CAS succeeds, but a node may have been freed and reused in between. Fix with a version counter or hazard pointers.' },

    { sec: 'ops', q: 'Which standard atomic type is guaranteed to be lock-free?',
      opts: ['`std::atomic<std::string>`', '`std::atomic_flag`', '`std::atomic<std::vector<int>>`', 'All of them'], a: 1,
      why: '`std::atomic_flag` is the only type the standard requires to be lock-free. Others depend on the type and platform (`is_lock_free()`).' },

    { sec: 'ordering', q: 'Which pair of orders publishes data written before a store to a thread that reads the stored value?',
      opts: ['Both `relaxed`', 'A `release` store and an `acquire` load', 'An `acquire` store and a `release` load', 'Only `volatile` works'], a: 1,
      why: 'The release store and acquire load synchronize-with each other, so earlier writes happen-before the reader\'s later reads.' },

    { sec: 'ordering', q: 'A producer stores the flag with `release`, but the consumer loads it with `relaxed`. What is guaranteed about the data written before the store?',
      opts: ['It is visible', 'Nothing: without an acquire on the reading side no happens-before edge exists', 'It is visible only on x86', 'The program does not compile'], a: 1,
      why: 'Both sides must take part. A relaxed load does not synchronize, so reading the data afterwards can be a data race.' },

    { sec: 'ordering', q: 'What does "A happens-before B" mean?',
      opts: ['A starts earlier in wall-clock time', 'A\'s effects are guaranteed to be visible to B', 'A and B run on the same core', 'A is faster than B'], a: 1,
      why: 'It is the memory model\'s visibility relation: program order within a thread, plus the edges created by synchronization (atomics, mutexes, join, futures).' },

    { sec: 'ordering', q: 'Why can code with a wrong memory order seem to work on x86 and fail on ARM?',
      opts: ['x86 has no caches', 'x86 already orders ordinary loads and stores like release/acquire, while ARM reorders much more', 'ARM does not support atomics', 'Compilers only optimise for ARM'], a: 1,
      why: 'The C++ memory model, not the machine you test on, defines correctness. x86 hides some missing orderings.' },

    { sec: 'patterns', q: 'Which orders suit the decrement of a reference count where the thread that drops it to zero deletes the object?',
      opts: ['`relaxed`', '`acq_rel` (so it sees every other thread\'s writes before deleting)', '`release` only on the load', 'No atomic is needed'], a: 1,
      why: 'Increments can be relaxed, but the decrement must acquire what the other owners released before the object is destroyed.' },

    { sec: 'patterns', q: 'Which memory order is normally enough for a statistics counter that nothing else depends on?',
      opts: ['`seq_cst`', '`relaxed`', '`acquire`', '`release`'], a: 1,
      why: 'Only atomicity is needed: the final total is right and no other data is published through the counter.' },

    { sec: 'structures', q: 'Why does the two-lock queue keep a dummy node?',
      opts: ['To save memory', 'So a push only touches the tail and a pop only the head, and producers and consumers do not block each other', 'To make it lock-free', 'To sort the elements'], a: 1,
      why: 'With a permanent dummy node, head and tail never point at the same real node, so each end can have its own mutex.' },

    { sec: 'structures', q: 'Why is a lock-free pop much harder to write than a lock-free push?',
      opts: ['Pop needs more arguments', 'Another thread may free the node you are reading (memory reclamation), and ABA can corrupt the list', 'Pop cannot use atomics', 'Push is not lock-free'], a: 1,
      why: 'Push only links a node you own. Pop reads and frees nodes other threads may still be using, which needs hazard pointers, epochs or counted pointers.' },

    { sec: 'structures', q: 'What is the difference between lock-free and wait-free?',
      opts: ['None', 'Lock-free: some thread always makes progress; wait-free: every thread finishes in a bounded number of steps', 'Wait-free uses mutexes', 'Lock-free means no atomics'], a: 1,
      why: 'Wait-free is the stronger guarantee: no thread can be starved indefinitely by others.' }
  ]
};
