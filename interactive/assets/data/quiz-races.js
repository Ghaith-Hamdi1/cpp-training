/* Quiz questions for the 'races' topic. Loaded by 38-races-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.races = {
  id: 'races',
  questions: [
    { sec: 's3', q: 'Two threads each execute the function below on the same global `counter`, then both are joined. What is true?',
      code: String.raw`
int counter = 0;
void work() { for (int i = 0; i < 1000; ++i) ++counter; }`,
      opts: ['counter is always 2000, since both loops run to completion', 'A data race (undefined behavior); the result may be below 2000', 'counter is always 1000, because only one thread wins', 'It does not compile, since counter is not atomic'], a: 1,
      why: '`++counter` is load, add, store. Interleavings lose updates, and the unsynchronised concurrent write is formally undefined behavior.' },

    { sec: 's3', q: 'Which of these is thread-safe without any extra synchronization?',
      opts: ['Two threads calling `push_back` on the same `std::vector`', 'Many threads only reading from the same const `std::vector`', 'One thread writing and another reading the same `int`', 'Two threads writing to the same `std::string`'], a: 1,
      why: 'Concurrent reads of data nobody modifies are safe. Any concurrent write plus access needs synchronization, including `push_back` on a standard container.' },

    { sec: 's3', q: 'Why can `++counter` lose an update when two threads run it?',
      opts: ['It is three steps', 'It is slower than a plain addition', 'Integers cannot be shared', 'The compiler removes it'], a: 0,
      why: 'If both threads load before either stores, one increment is lost.' },

    { sec: 's3', q: 'Which statement about a data race is correct?',
      opts: ['It is undefined behavior even if the output looks right', 'It only ever causes you to read a stale value', 'It needs three or more threads before it can occur', 'It cannot happen at all when there is only one core'], a: 0,
      why: 'The compiler assumes there are none, so the program has no defined meaning.' },

    { sec: 'invariants', q: 'What is an invariant?',
      opts: ['A condition on shared data that holds between operations', 'A variable that is declared once and never changes', 'A lock that a thread holds for its whole lifetime', 'A constant expression evaluated by the compiler'], a: 0,
      why: 'Updates break it briefly, and a reader in the middle sees a broken state.' },

    { sec: 'invariants', q: 'How does a race condition differ from a data race?',
      opts: ['It depends on timing', 'It is the same thing', 'It only involves deadlock', 'It needs a mutex'], a: 0,
      why: 'A data race is one specific kind of race condition: unsynchronized access.' },

    { sec: 'safe', q: 'Which is the best way to be safe with shared data when it is possible?',
      opts: ['Do not share', 'Use a global lock', 'Make everything volatile', 'Use more threads'], a: 0,
      why: 'No sharing means no races and no waiting.' },

    { sec: 'safe', q: 'Is it safe for many threads to read the same `const` object at the same time?',
      opts: ['Yes, as long as nobody modifies it', 'No, even read-only access is never safe', 'Only if every reader takes a mutex first', 'Only when the program runs on a single core'], a: 0,
      why: 'Read-only sharing has no conflicting writes.' },

    { sec: 's3', q: 'What does the thread simulator in this lesson show?',
      opts: ['That an interleaving of load, add', 'That mutexes are slow', 'That atomics are unsafe', 'That threads always finish in order'], a: 0,
      why: 'Stepping A and B alternately reproduces the lost increment.' },

    { sec: 's3', q: 'Why can a real race survive testing for a long time?',
      opts: ['The bad interleaving may occur once in thousands of runs', 'Races only exist in debug builds, never in release', 'The operating system prevents them while tests run', 'Tests always run on one core so races cannot happen'], a: 0,
      why: 'Timing-dependent bugs are rare and shift with load.' },

    { sec: 'strategies', q: 'Four threads each add into their own slot of `part[t]`. Why is that safe?',
      opts: ['No two threads write the same memory', 'The compiler adds a lock', 'Arrays are atomic', 'The slots are volatile'], a: 0,
      why: 'Disjoint writes are not a data race. Merge after join.' }
  ]
};
