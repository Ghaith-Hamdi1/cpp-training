/* Quiz questions for the 'pools' topic. Loaded by 42-pools-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.pools = {
  id: 'pools',
  questions: [
    { sec: 'pool', q: 'In a thread pool worker loop, why is the task executed after releasing the queue mutex?',
      opts: ['It is only a style preference with no effect on the behavior', 'Otherwise the lock is held during the task, so only one task runs at a time', 'A mutex cannot be locked twice by the same worker thread in a row', 'Tasks must never use any locks of their own while they are running'], a: 1,
      why: 'Hold the lock only to pop the task. Running it outside the lock keeps workers parallel and avoids deadlocks if the task itself submits more work.' },

    { sec: 'pool', q: 'About how many worker threads should a pool for purely CPU-bound tasks have?',
      opts: ['One thread per queued task, however many there are', 'About std::thread::hardware_concurrency(), the core count', 'Exactly 100, as a round and reasonable number', 'Always exactly 1, so that tasks never overlap'], a: 1,
      why: 'More threads than cores only adds context switching (oversubscription). Threads that mostly wait on I/O can usefully outnumber the cores.' },

    { sec: 'pool', q: 'A pool task submits a subtask to the same pool and blocks waiting for it. With N workers all doing this, what can happen?',
      opts: ['Nothing: the OS adds threads when the pool needs more', 'Deadlock: all workers wait for subtasks no free worker can run', 'The pool grows automatically to make room for the subtasks', 'The subtasks run first, so everything finishes normally'], a: 1,
      why: 'Blocking a pool thread on work that needs the same pool can use up every worker. Avoid waiting inside pool tasks, or use a separate pool.' },

    { sec: 'stealing', q: 'How does work stealing reduce lock contention compared with one shared queue?',
      opts: ['It uses more threads than a single shared queue would', 'Each worker pops its own deque; only idle workers steal from others', 'It removes the need for any synchronization between workers', 'It sorts the tasks by size before running any of them'], a: 1,
      why: 'Owners and thieves work at opposite ends of per-worker deques. The common case touches only local data, and stealing balances the load.' },

    { sec: 'stealing', q: 'How many worker threads suit I/O-bound tasks compared with CPU-bound ones?',
      opts: ['The same number: hardware_concurrency() for every workload', 'More than the core count, because threads mostly wait', 'Always exactly one, since I/O is sequential anyway', 'Fewer than the core count, to save memory on stacks'], a: 1,
      why: 'A blocked thread does not use a core, so more threads keep the cores busy. For CPU-bound work extra threads only add context switches.' },

    { sec: 'coordination', q: 'What is the difference between `std::latch` and `std::barrier`?',
      opts: ['There is no difference between them, only the name', 'A latch counts down once; a barrier is reusable every phase', 'A barrier is one-shot, while a latch can be reused', 'A latch is for processes, while a barrier is for threads'], a: 1,
      why: 'Once a latch reaches zero it stays open. A barrier resets itself for the next phase.' },

    { sec: 'coordination', q: 'A `std::counting_semaphore` is created with 2 permits and six threads each `acquire()`, work and `release()`. What is the maximum number of threads working at once?',
      opts: ['1', '2', '6', 'Unspecified'], a: 1,
      why: 'The semaphore counts permits: two threads get through and the others wait until a permit is released.' },

    { sec: 'coordination', q: 'What is the right way to stop a running `std::jthread`?',
      opts: ['Call kill() on the thread object, as one would with a process', 'Request a stop; the thread checks its stop_token and returns', 'detach() it and let it keep running until the program ends', 'Call std::terminate from some other thread to stop just it'], a: 1,
      why: 'Stopping is cooperative. The destructor of a `jthread` calls `request_stop()` and then joins.' },

    { sec: 'parallel', q: 'Why must the operation given to `std::reduce` be associative?',
      opts: ['It does not have to be: reduce always keeps the original order', 'The library may regroup operands across threads', 'Only so that the call compiles when an execution policy is given', 'Because reduce always runs on a graphics card, never on a CPU'], a: 1,
      why: 'Unlike `std::accumulate`, `reduce` is free to combine partial results in any grouping. (For floating-point sums the result may differ slightly.)' },

    { sec: 'parallel', q: 'What must be true of the callback passed to `std::for_each(std::execution::par, ...)`?',
      opts: ['It must be written as a lambda expression', 'It must be safe to call from several threads at once', 'It must be both noexcept and constexpr to be accepted', 'Nothing: the library adds all the locking itself'], a: 1,
      why: 'The library runs it on several threads, so an unsynchronised write to shared state is a data race (undefined behaviour).' },

    { sec: 'pool', q: 'Why does a pool worker release the lock before running the task?',
      opts: ['Otherwise only one task could run at a time', 'To avoid a spurious wakeup of other workers', 'Because a task is never allowed to hold any lock', 'To make the queue itself take less memory'], a: 0,
      why: 'The lock protects only the queue.' },

    { sec: 'sizing', q: 'How many workers for a pool of CPU-bound tasks?',
      opts: ['About `hardware_concurrency()`', 'As many as there are tasks in the queue', 'Exactly one, so that tasks never conflict', 'Ten per core to keep every core busy'], a: 0,
      why: 'More workers than cores only adds switching.' },

    { sec: 'stealing', q: 'In work stealing, where does an idle worker take a task from?',
      opts: ['The back of another worker\'s deque', 'The front of one shared global queue', 'Its own deque, from the same end as before', 'A random thread\'s stack, chosen by the scheduler'], a: 0,
      why: 'Owners pop at one end and thieves take at the other, so they rarely collide.' },

    { sec: 'cancel', q: 'How do you safely stop a worker thread?',
      opts: ['Ask it to stop with a `stop_token`', 'Kill the thread from outside at any moment', 'Call detach on it so that it goes away', 'Destroy the mutex that the worker is using'], a: 0,
      why: 'There is no safe forced kill in standard C++.' }
  ]
};
