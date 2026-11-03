/* Quiz questions for the 'memmodel' topic. Loaded by 43-memmodel-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.memmodel = {
  id: 'memmodel',
  questions: [
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
      opts: ['It may print 0 or 42, depending on how the threads are scheduled', 'It prints 42', 'It is a data race with undefined behavior on the shared data', 'It prints nothing because the consumer loop never ends'], a: 1,
      why: 'A release store paired with an acquire load that observes it creates a happens-before edge, so the write to `data` is visible. With relaxed ordering this would not be guaranteed.' },

    { sec: 'ordering', q: 'Which pair of orders publishes data written before a store to a thread that reads the stored value?',
      opts: ['Both operations use relaxed', 'A release store and an acquire load', 'An acquire store and a release load', 'Only volatile reads and writes'], a: 1,
      why: 'The release store and acquire load synchronize-with each other, so earlier writes happen-before the reader\'s later reads.' },

    { sec: 'ordering', q: 'A producer stores the flag with `release`, but the consumer loads it with `relaxed`. What is guaranteed about the data written before the store?',
      opts: ['It is visible, because the store was a release operation on the flag', 'Nothing: without an acquire on the reading side there is no ordering', 'It is guaranteed visible only if the data is declared volatile', 'The program does not compile when memory orders are mixed like this'], a: 1,
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
      opts: ['Pop needs more arguments than push does, so it is slower', 'Another thread may free the node you read', 'Pop cannot use atomic operations, so it must use a mutex', 'Push is not lock-free either in this design, only pop is'], a: 1,
      why: 'Push only links a node you own. Pop reads and frees nodes other threads may still be using, which needs hazard pointers, epochs or counted pointers.' },

    { sec: 'structures', q: 'What is the difference between lock-free and wait-free?',
      opts: ['There is no difference between the two terms, both mean lock-free', 'Lock-free: some thread always progresses; wait-free: all do, in bounded steps', 'Wait-free algorithms use mutexes to bound the waiting time for threads', 'Lock-free means that no atomic operations are used by the algorithm'], a: 1,
      why: 'Wait-free is the stronger guarantee: no thread can be starved indefinitely by others.' },

    { sec: 'reorder', q: 'Which of these can reorder memory operations between threads?',
      opts: ['The compiler, the CPU', 'Only the compiler', 'Only the CPU', 'Only the operating system'], a: 0,
      why: 'All three layers can change the order another thread observes.' },

    { sec: 'orders', q: 'Which memory order is the default for atomic operations?',
      opts: ['`memory_order_seq_cst`', '`memory_order_relaxed`', '`memory_order_acquire`', '`memory_order_release`'], a: 0,
      why: 'The default is the strongest and easiest to reason about.' },

    { sec: 'orders', q: 'Which order suits a statistics counter that nothing else depends on?',
      opts: ['`relaxed`', '`seq_cst`', '`release`', '`acq_rel`'], a: 0,
      why: 'Only atomicity of the total is needed.' },

    { sec: 'happens', q: 'Which of these creates a happens-before edge between threads?',
      opts: ['`join()` on the other thread', 'Reading a plain int twice', 'Calling `sleep_for`', 'Printing with `std::cout`'], a: 0,
      why: 'Joining synchronizes the end of the thread with the code after join.' },

    { sec: 'happens', q: 'Inside a single thread, what gives happens-before?',
      opts: ['Program order', 'The mutex', 'A memory fence only', 'Nothing'], a: 0,
      why: 'Within one thread each statement happens-before the next.' },

    { sec: 'dclp', q: 'What goes wrong in double-checked locking without release/acquire?',
      opts: ['Another thread can see the pointer before the object is built', 'The mutex deadlocks the first time it is taken', 'The pointer stays null forever for every thread', 'The call to new throws an exception each time'], a: 0,
      why: 'The constructor\'s writes may not be visible yet.' },

    { sec: 'structures', q: 'Why does a two-lock queue use a dummy node?',
      opts: ['Pushes touch only the tail', 'To store the size', 'To allow reverse iteration', 'To make the queue lock-free'], a: 0,
      why: 'The dummy node keeps head and tail from meeting on the same node.' }
  ]
};
