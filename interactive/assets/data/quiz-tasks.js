/* Quiz questions for the 'tasks' topic. Loaded by 17-tasks-parallelism-quiz.html. */
CT.quizData.tasks = {
  id: 'tasks',
  questions: [
    { sec: 'futures', q: 'What does this code do?',
      code: String.raw`
std::async(std::launch::async, slowTask);   // returned future is discarded
doOtherWork();`,
      opts: ['Runs slowTask in the background while doOtherWork runs', 'Effectively runs slowTask first: the temporary future\'s destructor blocks until the task finishes', 'Does not compile', 'Runs doOtherWork first'], a: 1,
      why: 'A future from `std::async` blocks in its destructor. Because the temporary is destroyed at the end of the statement, `doOtherWork` only starts after `slowTask` completes. Keep the future in a variable.' },

    { sec: 'futures', q: 'What happens if the function run by `std::async` throws, and you later call `future.get()`?',
      opts: ['The program terminates immediately', 'get() rethrows the exception in the calling thread', 'The exception is silently dropped', 'get() returns a default value'], a: 1,
      why: 'The exception is stored in the shared state and rethrown by `get()`. That makes futures the clean way to propagate errors out of worker threads.' },

    { sec: 'pool', q: 'In a thread pool worker loop, why is the task executed after releasing the queue mutex?',
      opts: ['It is only a style preference', 'Otherwise the lock would be held during the whole task, so only one task could run at a time and other workers could not take work', 'The mutex cannot be locked twice', 'Tasks must not use locks'], a: 1,
      why: 'Hold the lock only to pop the task. Running it outside the lock keeps workers parallel and avoids deadlocks if the task itself submits more work.' },

    { sec: 'pool', q: 'About how many worker threads should a pool for purely CPU-bound tasks have?',
      opts: ['One per task', 'About `std::thread::hardware_concurrency()`', 'Exactly 100', 'Always 1'], a: 1,
      why: 'More threads than cores only adds context switching (oversubscription). Threads that mostly wait on I/O can usefully outnumber the cores.' },

    { sec: 'signals', q: 'A `std::promise<int>` is destroyed without `set_value` or `set_exception` ever being called. What does `get()` on its future do?',
      opts: ['Blocks forever', 'Throws `std::future_error` with `broken_promise`', 'Returns 0', 'Terminates the program'], a: 1,
      why: 'The promise breaks and the future is made ready with an error, so the waiting thread is not left hanging.' },

    { sec: 'signals', q: 'Which type lets several threads wait for the same result?',
      opts: ['`std::future`', '`std::shared_future`', '`std::packaged_task`', '`std::once_flag`'], a: 1,
      why: '`std::future` is move-only and can be read once. A `shared_future` is copyable, so every thread gets its own handle on the same result.' },

    { sec: 'signals', q: 'What does `std::packaged_task<int(int)>` do?',
      opts: ['Runs a function on a new thread', 'Wraps a callable and delivers its result (or exception) into a future, to be run later by anything', 'Caches a function\'s return value', 'Creates a thread pool'], a: 1,
      why: 'It is a callable plus a future. A pool queues the task, a worker runs it, and the caller reads the result from the future.' },

    { sec: 'pool', q: 'A pool task submits a subtask to the same pool and blocks waiting for it. With N workers all doing this, what can happen?',
      opts: ['Nothing: the OS adds threads', 'Deadlock: all workers wait for subtasks that no free worker can run', 'The pool grows automatically', 'The subtasks run first'], a: 1,
      why: 'Blocking a pool thread on work that needs the same pool can use up every worker. Avoid waiting inside pool tasks, or use a separate pool.' },

    { sec: 'stealing', q: 'How does work stealing reduce lock contention compared with one shared queue?',
      opts: ['It uses more threads', 'Each worker pops its own deque and only an idle worker takes from the opposite end of another deque, so threads rarely touch the same lock', 'It removes the need for synchronization', 'It sorts tasks by size'], a: 1,
      why: 'Owners and thieves work at opposite ends of per-worker deques. The common case touches only local data, and stealing balances the load.' },

    { sec: 'stealing', q: 'How many worker threads suit I/O-bound tasks compared with CPU-bound ones?',
      opts: ['The same: `hardware_concurrency()`', 'More than the core count, because the threads spend their time waiting', 'Always exactly one', 'Fewer, to save memory'], a: 1,
      why: 'A blocked thread does not use a core, so more threads keep the cores busy. For CPU-bound work extra threads only add context switches.' },

    { sec: 'coordination', q: 'What is the difference between `std::latch` and `std::barrier`?',
      opts: ['None', 'A latch is a one-shot countdown; a barrier is reusable and synchronizes a group of threads at the end of every phase', 'A barrier is one-shot; a latch is reusable', 'A latch is for processes, a barrier for threads'], a: 1,
      why: 'Once a latch reaches zero it stays open. A barrier resets itself for the next phase.' },

    { sec: 'coordination', q: 'A `std::counting_semaphore` is created with 2 permits and six threads each `acquire()`, work and `release()`. What is the maximum number of threads working at once?',
      opts: ['1', '2', '6', 'Unspecified'], a: 1,
      why: 'The semaphore counts permits: two threads get through and the others wait until a permit is released.' },

    { sec: 'coordination', q: 'What is the right way to stop a running `std::jthread`?',
      opts: ['Call `kill()` on it', 'Request a stop (or let its destructor do it) and have the thread check its `std::stop_token` and return', '`detach()` it', 'Call `std::terminate`'], a: 1,
      why: 'Stopping is cooperative. The destructor of a `jthread` calls `request_stop()` and then joins.' },

    { sec: 'parallel', q: 'Why must the operation given to `std::reduce` be associative?',
      opts: ['It does not have to be', 'The library may regroup the operands across threads, so the result must not depend on the grouping', 'To make it compile', 'Because it runs on a GPU'], a: 1,
      why: 'Unlike `std::accumulate`, `reduce` is free to combine partial results in any grouping. (For floating-point sums the result may differ slightly.)' },

    { sec: 'parallel', q: 'What must be true of the callback passed to `std::for_each(std::execution::par, ...)`?',
      opts: ['It must be a lambda', 'It must be safe to call from several threads at once: no unsynchronised writes to shared data', 'It must be `noexcept` and `constexpr`', 'Nothing'], a: 1,
      why: 'The library runs it on several threads, so an unsynchronised write to shared state is a data race (undefined behaviour).' }
  ]
};
