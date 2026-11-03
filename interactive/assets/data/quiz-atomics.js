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

    { sec: 'cas', q: 'What does `compare_exchange_weak(expected, desired)` do when the current value is not equal to `expected`?',
      opts: ['Sets the value to desired anyway and returns true', 'Returns false and loads the current value into expected', 'Throws an exception to report the mismatch to the caller', 'Returns true and leaves expected completely unchanged'], a: 1,
      why: 'On failure it refreshes `expected` with the value it actually saw, so a retry loop can recompute from it.' },

    { sec: 'cas', q: 'Why is `compare_exchange_weak` normally used inside a loop?',
      opts: ['It is faster than a mutex, so it is preferred', 'It may fail spuriously even when the values match', 'It cannot be called more than once on the same atomic object', 'It blocks until the swap finally succeeds, like a lock does'], a: 1,
      why: '`weak` is allowed to fail spuriously (cheaper on some CPUs). `compare_exchange_strong` fails only on a real mismatch.' },

    { sec: 'aba', q: 'What is the ABA problem?',
      opts: ['A CAS succeeds because the value is A again, though it went through B', 'Two threads sharing the same atomic variable at the same moment', 'A deadlock between two mutexes locked in opposite orders', 'A compiler bug that is triggered by the volatile keyword'], a: 0,
      why: 'The value looks unchanged, so the CAS succeeds, but a node may have been freed and reused in between. Fix with a version counter or hazard pointers.' },

    { sec: 'spin', q: 'Which standard atomic type is guaranteed to be lock-free?',
      opts: ['`std::atomic<std::string>`', '`std::atomic_flag`', '`std::atomic<std::vector<int>>`', 'All of them'], a: 1,
      why: '`std::atomic_flag` is the only type the standard requires to be lock-free. Others depend on the type and platform (`is_lock_free()`).' },

    { sec: 'ops', q: 'What is the difference between `x++` on an int and on a `std::atomic<int>` shared by two threads?',
      opts: ['The atomic increment is one indivisible step', 'The atomic one is slower and still races as before', 'There is no difference, since both are the same', 'The plain int increment is atomic on x86 anyway'], a: 0,
      why: 'An atomic read-modify-write cannot be interleaved.' },

    { sec: 'cas', q: 'What does `compare_exchange` do on failure?',
      opts: ['Loads the current value into `expected`', 'Throws an exception that the caller must handle', 'Stores `desired` anyway, to force the update', 'Resets the variable to zero so it can start over'], a: 0,
      why: 'That is what makes the retry loop easy to write.' },

    { sec: 'spin', q: 'When is a spinlock a bad idea?',
      opts: ['When the lock holder can be descheduled', 'For very short critical sections of a few lines', 'On cores that are dedicated to the spinning threads', 'For protecting a single increment of a counter'], a: 0,
      why: 'Spinners burn CPU while the holder is not running.' },

    { sec: 'ops', q: 'What does `counter.exchange(9)` return?',
      opts: ['The previous value', '9', 'The new value of counter', 'Nothing'], a: 0,
      why: 'exchange writes and returns the old value in one step.' },

    { sec: 'ops', q: 'Which operation is NOT made safe by `std::atomic<int>` alone?',
      opts: ['Keeping two atomics consistent with each other', 'A single increment of one atomic integer variable', 'A load of one atomic integer variable', 'A store to one atomic integer variable'], a: 0,
      why: 'An atomic protects one variable; an invariant over several needs a mutex.' },

    { sec: 'cas', q: 'Why is the `expected` argument passed by reference to `compare_exchange`?',
      opts: ['A failed attempt can write the current value back into it', 'To avoid a copy of a large object on each call', 'So that the function can change the desired value', 'It is not passed by reference in the standard'], a: 0,
      why: 'The failure path updates expected so the loop can recompute.' },

    { sec: 'spin', q: 'What does `atomic_flag::test_and_set` return?',
      opts: ['The previous value of the flag', 'Whether the flag type is lock-free', 'The new value', 'Nothing'], a: 0,
      why: 'A spinlock loops until it sees that the flag was previously clear.' },

    { sec: 'practice', q: 'Which order is enough for `nextId.fetch_add(1)` used as a unique id generator?',
      opts: ['`relaxed`', '`release`', '`acquire`', 'None: atomics cannot do it'], a: 0,
      why: 'Only atomicity matters; no other data depends on the value.' }
  ]
};
