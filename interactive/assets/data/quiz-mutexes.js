/* Quiz questions for the 'mutexes' topic. Loaded by 39-mutexes-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.mutexes = {
  id: 'mutexes',
  questions: [
    { sec: 's4', q: 'Which change makes that counter correct?',
      opts: ['Declare the counter as volatile int so that reads are fresh', 'Declare std::atomic<int> counter (or protect it with a mutex)', 'Declare the work function inline so the loop is optimized', 'Join the threads in the opposite order to avoid overlap'], a: 1,
      why: '`volatile` gives neither atomicity nor ordering. An atomic makes each increment indivisible; a mutex serialises the critical section.' },

    { sec: 's4', q: 'Why prefer `std::lock_guard` over calling `m.lock()` and `m.unlock()` yourself?',
      opts: ['It is faster than calling lock and unlock by hand each time', 'It unlocks automatically (RAII), even on early return or exception', 'It allows the same thread to lock the same mutex recursively', 'It avoids the need for a mutex object altogether'], a: 1,
      why: 'If code between `lock()` and `unlock()` throws or returns, a manual unlock is skipped and every other thread blocks forever.' },

    { sec: 'interface-races', q: 'Every member function of this shared stack locks a mutex internally. Why is the caller\'s code still racy?',
      code: String.raw`
SafeStack<int> s;                 // shared by several threads
if (!s.empty()) {
    int v = s.top();
    s.pop();
    use(v);
}`,
      opts: ['The mutex is not recursive, so the calls block each other here', 'Each call is atomic but the sequence is not', 'lock_guard cannot protect a std::stack from concurrent use', 'empty() must be called twice before the result can be trusted fully'], a: 1,
      why: 'This is a check-then-act race built into the interface. The cure is to change the interface, not to add more locking inside the individual calls.' },

    { sec: 'interface-races', q: 'What is the best fix for that stack?',
      opts: ['Declare every method of the stack volatile to publish changes', 'Provide one try_pop() that checks, reads and removes under one lock', 'Call empty() twice to be sure that the stack has elements', 'Call notify_all() after each pop to wake the other threads'], a: 1,
      why: 'Offer whole operations rather than steps, so callers never need to check and act separately. `empty()` may remain as a hint, but its answer can be stale the moment it returns.' },

    { sec: 'mutex-types', q: 'What happens if one thread locks a plain `std::mutex` a second time without unlocking it in between?',
      opts: ['The second lock is ignored and the thread continues', 'Undefined behaviour, in practice usually a deadlock', 'It always throws std::system_error from the second lock', 'It waits for a timeout and then continues running'], a: 1,
      why: 'A `std::mutex` is not re-lockable. Only `std::recursive_mutex` lets the owning thread lock again, which is usually a sign of a design problem.' },

    { sec: 'mutex-types', q: 'A public method `depositTwice()` locks a mutex and calls the public `deposit()`, which locks the same mutex. What is the cleaner fix than a `recursive_mutex`?',
      opts: ['Declare the shared data volatile so the changes become visible everywhere', 'Split into a locking public method and a private helper that assumes the lock', 'Make the mutex static so that it is shared by every call to the class', 'Unlock the mutex just before calling deposit() from depositTwice()'], a: 1,
      why: 'The locking public method calls a private `...Locked()` function that both public methods share. The lock is taken exactly once and the contract is explicit.' },

    { sec: 'mutex-types', q: 'When does a `std::shared_mutex` pay off compared with a plain `std::mutex`?',
      opts: ['Whenever there are two or more threads in the program', 'When many threads read for a while and writes are rare', 'When the critical section is a single increment of a counter', 'When threads must run in a fixed, predictable order'], a: 1,
      why: 'It costs more per lock than a `mutex`, so it only helps when readers dominate and each read holds the lock long enough to overlap with others.' },

    { sec: 'mutex-types', q: 'What does `std::call_once(flag, fn)` guarantee when eight threads call it at the same time?',
      opts: ['fn runs once for each calling thread, one after the other', 'fn runs exactly once; the other callers wait until it has finished', 'fn may run twice, but never more often than that in total', 'Nothing: you still need a mutex around the call as well'], a: 1,
      why: 'It is the standard thread-safe one-time initialization. The other threads block until the first call returns, then continue with the initialized state.' },

    { sec: 'raii', q: 'Why prefer `std::lock_guard` to calling `m.lock()` and `m.unlock()`?',
      opts: ['It unlocks on every path', 'It is faster', 'It allows recursive locking', 'It works without a mutex'], a: 0,
      why: 'RAII guarantees the unlock, even on early return or exception.' },

    { sec: 'granularity', q: 'What should NOT be done while holding a lock?',
      opts: ['Slow work such as file I/O or sleeping', 'Reading the shared data that the lock protects', 'Updating the shared data that the lock protects', 'Restoring the invariant before the lock is released'], a: 0,
      why: 'Everything under the lock blocks other threads, so keep it short.' },

    { sec: 'granularity', q: 'Which gives the shortest critical section?',
      opts: ['Compute outside, lock only', 'Lock for the whole function', 'Lock before computing', 'Lock for printing as well'], a: 0,
      why: 'Lock only the shared access.' },

    { sec: 'protect', q: 'A class locks a mutex inside each method. Is a sequence of two calls safe?',
      opts: ['No: the invariant between the two calls is unprotected', 'Yes: each individual method is locked, so the pair is too', 'Yes, as long as the methods are all declared const', 'Only on x86, which orders every memory operation'], a: 0,
      why: 'A caller\'s sequence is not atomic; offer whole operations.' },

    { sec: 'rw', q: 'When does a `std::shared_mutex` pay off?',
      opts: ['Many readers and rare writers', 'Many writers', 'Only one thread', 'Short critical sections of one line'], a: 0,
      why: 'Readers share the lock; writers are exclusive.' },

    { sec: 'recursive', q: 'Why is `std::recursive_mutex` often a design smell?',
      opts: ['It hides code that re-enters with a broken invariant', 'It is slower than every other kind of mutex', 'It cannot be unlocked once it has been locked', 'It does not exist at all before C++20'], a: 0,
      why: 'Re-locking is usually a sign of a design problem, not a fix.' },

    { sec: 'whole', q: 'Why is `if (!s.empty()) s.pop()` unsafe even if both calls lock?',
      opts: ['Another thread can empty it between the two calls', 'empty() is far too slow to call under a lock', 'pop() requires its own separate lock_guard object', 'It does not compile with a stack or a queue'], a: 0,
      why: 'Offer a single operation such as tryPop.' }
  ]
};
