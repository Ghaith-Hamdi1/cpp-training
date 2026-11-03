/* Quiz questions for the 'condvars' topic. Loaded by 41-condvars-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.condvars = {
  id: 'condvars',
  questions: [
    { sec: 's7', q: 'Why must `condition_variable::wait` be used with a predicate (or in a loop)?',
      opts: ['It makes wait faster by skipping the lock on the first check', 'Wake-ups can be spurious, and the condition may change again', 'The operating system refuses to wait without a predicate', 'Without a predicate, wait never returns to the caller'], a: 1,
      why: '`cv.wait(lk, pred)` is shorthand for `while (!pred()) cv.wait(lk);`. A bare `wait` can return with the condition still false.' },

    { sec: 's7', q: 'Why does `condition_variable::wait` take a `std::unique_lock` rather than a `std::lock_guard`?',
      opts: ['unique_lock is faster than lock_guard in most situations', 'wait must unlock the mutex while sleeping, then relock on wake-up', 'lock_guard cannot lock a mutex, only adopt one', 'It is only a naming convention and either type would work'], a: 1,
      why: 'Unlocking while the thread sleeps is what lets the producer enter. `lock_guard` has no unlock operation.' },

    { sec: 's7', q: 'What is a "lost wakeup"?',
      opts: ['The operating system forgetting a waiting thread in its queue', 'A notification sent before the waiter slept, so it sleeps forever', 'A thread being woken up twice for one single event', 'A mutex being unlocked twice by mistake in the code'], a: 1,
      why: 'Changing the condition under the mutex makes "check, then sleep" atomic with respect to the update, which closes the window in which a notification can be missed.' },

    { sec: 's7', q: 'When is `notify_all()` needed instead of `notify_one()`?',
      opts: ['Never: notify_one is always enough', 'When several waiters can proceed, or at shutdown to wake everyone', 'Only when the waiting threads also use atomic variables for data', 'Only when the shared queue happens to be empty at that moment'], a: 1,
      why: '`notify_one` wakes just one thread. For broadcast conditions such as "stop requested", all waiters must be woken.' },

    { sec: 's11', q: 'Is initialization of a function-local `static` variable thread-safe in C++11 and later?',
      opts: ['No: you must always add a mutex yourself around the static variable', 'Yes: it runs exactly once even if several threads reach it together', 'Only for primitive types such as int and double, not for classes', 'Only if the static variable is declared const as well'], a: 1,
      why: 'This "magic statics" guarantee is why the Meyers Singleton needs no explicit locking for its construction.' },

    { sec: 's11', q: 'How can you detect data races in a C++ program?',
      opts: ['Add more print statements to the code and rerun it often', 'Compile with ThreadSanitizer', 'Use -O3 so the compiler reorders the accesses safely', 'Declare every shared variable volatile'], a: 1,
      why: 'ThreadSanitizer instruments memory accesses and reports conflicting unsynchronised accesses with stack traces. Helgrind and DRD help with lock-order issues.' },

    { sec: 's11', q: 'Why can several threads printing with `std::cout << a << b << \'\\n\'` produce garbled lines?',
      opts: ['cout cannot be used from several threads at the same time', 'Each << is a separate operation, so output from threads can interleave', 'cout is buffered, which reorders the lines between the threads', 'False sharing corrupts the internal output buffer of the stream'], a: 1,
      why: 'The stream itself does not crash, but the pieces of different lines mix. Build the full string first and write it once, or protect output with a mutex.' },

    { sec: 's7', q: 'Why does `cv.wait` take a `std::unique_lock`?',
      opts: ['It unlocks the mutex while the thread sleeps and relocks it', 'lock_guard is deprecated and no longer compiles', 'It needs two different mutexes at the same time', 'It stores a copy of the mutex inside the variable'], a: 0,
      why: 'wait must be able to release and reacquire the lock.' },

    { sec: 'predicate', q: 'A waiter is woken but the predicate is false. What should it do?',
      opts: ['Go back to waiting', 'Continue with the work anyway', 'Throw an exception to the caller', 'Call notify on the condition variable'], a: 0,
      why: 'A wakeup is only a hint: the predicate decides.' },

    { sec: 'predicate', q: 'Why must the condition be changed under the same mutex the waiter uses?',
      opts: ['A notification can be lost between the check and the sleep', 'It makes the notify call itself run faster', 'Because notify cannot be called without a lock', 'Because the condition is really a kind of mutex'], a: 0,
      why: 'The check-then-sleep must be atomic with respect to the update.' },

    { sec: 'rules', q: 'When is `notify_all` better than `notify_one`?',
      opts: ['When waiters wait', 'Always', 'Never', 'Only for producers'], a: 0,
      why: 'notify_one may wake a thread that cannot use the event.' },

    { sec: 'queue', q: 'In a thread-safe queue, where does the consumer wait?',
      opts: ['`cv.wait(lk, [&]{ return !q.empty(); })`', 'In a loop that calls sleep_for repeatedly', 'On the thread id of the producer thread', 'On a raw atomic flag that it polls hard'], a: 0,
      why: 'Sleep on the condition variable with a predicate.' },

    { sec: 'timeline', q: 'A notify is sent before the consumer starts waiting. What saves the consumer from sleeping forever?',
      opts: ['It checks the predicate first and sees the item', 'The notify is queued by the condition variable', 'wait always returns once', 'The producer retries'], a: 0,
      why: 'A condition variable does not remember notifications; the predicate does.' }
  ]
};
