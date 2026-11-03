/* Quiz questions for the 'deadlock' topic. Loaded by 40-deadlock-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.deadlock = {
  id: 'deadlock',
  questions: [
    { sec: 's5', q: 'Thread A locks `m1` then `m2`. Thread B locks `m2` then `m1`. What can happen, and what is the best fix?',
      opts: ['Nothing: mutexes are fair, so the threads simply take turns', 'Deadlock; fix with a fixed lock order or std::scoped_lock(m1, m2)', 'A data race; fix by declaring the protected data volatile', 'Starvation; fix by lowering one thread\'s priority a little'], a: 1,
      why: 'Each holds one lock and waits for the other: circular wait. Locking in the same order everywhere, or locking both at once with `scoped_lock`/`std::lock`, removes the cycle.' },

    { sec: 's5', q: 'Which of these is NOT one of the four conditions required for a deadlock?',
      opts: ['Mutual exclusion: only one thread may hold the resource', 'Hold and wait: a thread holds one lock while requesting another', 'Circular wait: a cycle of threads each waiting for the next', 'All locks must be recursive so a thread can re-enter them'], a: 3,
      why: 'The four Coffman conditions are mutual exclusion, hold and wait, no preemption, and circular wait. Breaking any one of them prevents deadlock.' },

    { sec: 's5', q: 'Can two threads deadlock without any mutex being involved?',
      opts: ['No: deadlock always needs at least one mutex to be involved somewhere', 'Yes: for example each thread joins the other, or waits in a future cycle', 'Only with atomics, when two threads spin waiting on each other', 'Only if one of the two threads has been detached earlier'], a: 1,
      why: 'Deadlock is a cycle of waiting. The guideline is general: do not wait for another thread if there is a chance it is waiting for you.' },

    { sec: 's5', q: 'What does a lock hierarchy (levels on mutexes) give you?',
      opts: ['Faster locking than a plain mutex, thanks to cached lock levels', 'A thread may lock only lower levels than it holds, so cycles cannot form', 'Automatic unlocking at the end of the enclosing scope, like RAII', 'Fair scheduling between the threads that wait for the same lock'], a: 1,
      why: 'Runtime-checked ordering turns a rare, timing-dependent deadlock into a deterministic error you can find in testing.' },

    { sec: 's5', q: 'Why should you not call user-supplied code (a callback, a virtual function) while holding a lock?',
      opts: ['It may take another lock or keep a pointer to the data', 'It is always slower than calling your own code', 'It cannot be copied into the critical section', 'It must always be declared noexcept to be called'], a: 1,
      why: 'You do not control what that code does. Never pass out references to protected data, and avoid holding a lock across calls to code you do not own.' },

    { sec: 's5', q: 'Which is NOT one of the four conditions for a deadlock?',
      opts: ['Priority inversion', 'Mutual exclusion', 'Hold and wait', 'Circular wait'], a: 0,
      why: 'The four are mutual exclusion, hold and wait, no preemption and circular wait.' },

    { sec: 's5', q: 'What does a cycle in the wait-for graph mean?',
      opts: ['A deadlock', 'A livelock', 'A race', 'A spurious wakeup'], a: 0,
      why: 'Each thread in the cycle waits for the next one forever.' },

    { sec: 'order', q: 'How does a global lock order prevent deadlock?',
      opts: ['It removes the circular wait', 'It removes mutual exclusion', 'It makes locks faster', 'It allows preemption'], a: 0,
      why: 'If everyone takes a before b, no cycle can form.' },

    { sec: 'order', q: 'What does `std::scoped_lock lk(a, b)` do?',
      opts: ['Locks both mutexes with a deadlock-avoidance algorithm', 'Locks a first and b second strictly in that order', 'Locks only the first mutex and ignores the second', 'Detaches the threads that are waiting for the locks'], a: 0,
      why: 'The argument order does not matter.' },

    { sec: 'guidelines', q: 'Why should you not call user-supplied code under a lock?',
      opts: ['It may take another lock or keep a pointer to the protected data', 'It is slower', 'It cannot be copied', 'It must be noexcept'], a: 0,
      why: 'A callback can create new lock orders or leak references.' },

    { sec: 'related', q: 'Threads keep reacting to each other and use 100% CPU but make no progress. What is it?',
      opts: ['Livelock', 'Deadlock', 'A data race', 'Starvation'], a: 0,
      why: 'A deadlock is idle; a livelock is busy.' },

    { sec: 'related', q: 'How is livelock usually cured?',
      opts: ['Randomize the retry delay or impose an order', 'Add more threads so that somebody makes progress', 'Switch the mutexes to recursive mutexes everywhere', 'Declare the shared variables volatile instead'], a: 0,
      why: 'Breaking the symmetry lets one thread win.' },

    { sec: 'debug', q: 'In a hung program all threads are blocked inside `lock()` and the CPU is at 0%. What is the likely problem?',
      opts: ['A deadlock', 'A livelock', 'A data race', 'A busy wait'], a: 0,
      why: 'Idle CPU with every thread waiting points to a deadlock or a lost wakeup.' }
  ]
};
