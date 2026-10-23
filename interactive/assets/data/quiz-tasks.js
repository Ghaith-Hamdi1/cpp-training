/* Quiz questions for the 'tasks' topic. Loaded by 17-tasks-parallelism-quiz.html. */
CT.quizData.tasks = {
  id: 'tasks',
  questions: [
    { sec: 'futures', q: 'What does this code do?',
      code: String.raw`
std::async(std::launch::async, slowTask);   // returned future is discarded
doOtherWork();`,
      opts: ['Runs slowTask in the background while doOtherWork runs at the same time', 'Effectively runs slowTask first: the temporary future waits in its destructor', 'It does not compile because the returned future is simply discarded', 'Runs doOtherWork first and slowTask only afterwards, one after the other'], a: 1,
      why: 'A future from `std::async` blocks in its destructor. Because the temporary is destroyed at the end of the statement, `doOtherWork` only starts after `slowTask` completes. Keep the future in a variable.' },

    { sec: 'futures', q: 'What happens if the function run by `std::async` throws, and you later call `future.get()`?',
      opts: ['The program terminates immediately', 'get() rethrows the exception in the calling thread', 'The exception is silently dropped by the future', 'get() returns a default-constructed value'], a: 1,
      why: 'The exception is stored in the shared state and rethrown by `get()`. That makes futures the clean way to propagate errors out of worker threads.' },

    { sec: 'pool', q: 'In a thread pool worker loop, why is the task executed after releasing the queue mutex?',
      opts: ['It is only a style preference with no effect on the behavior', 'Otherwise the lock is held during the task, so only one task runs at a time', 'A mutex cannot be locked twice by the same worker thread in a row', 'Tasks must never use any locks of their own while they are running'], a: 1,
      why: 'Hold the lock only to pop the task. Running it outside the lock keeps workers parallel and avoids deadlocks if the task itself submits more work.' },

    { sec: 'pool', q: 'About how many worker threads should a pool for purely CPU-bound tasks have?',
      opts: ['One thread per queued task, however many there are', 'About std::thread::hardware_concurrency(), the core count', 'Exactly 100, as a round and reasonable number', 'Always exactly 1, so that tasks never overlap'], a: 1,
      why: 'More threads than cores only adds context switching (oversubscription). Threads that mostly wait on I/O can usefully outnumber the cores.' },

    { sec: 'signals', q: 'A `std::promise<int>` is destroyed without `set_value` or `set_exception` ever being called. What does `get()` on its future do?',
      opts: ['It blocks forever, waiting for a value that never comes', 'It throws std::future_error with broken_promise', 'It returns 0, the default value of the int', 'It terminates the program through std::terminate'], a: 1,
      why: 'The promise breaks and the future is made ready with an error, so the waiting thread is not left hanging.' },

    { sec: 'signals', q: 'Which type lets several threads wait for the same result?',
      opts: ['`std::future`', '`std::shared_future`', '`std::packaged_task`', '`std::once_flag`'], a: 1,
      why: '`std::future` is move-only and can be read once. A `shared_future` is copyable, so every thread gets its own handle on the same result.' },

    { sec: 'signals', q: 'What does `std::packaged_task<int(int)>` do?',
      opts: ['Runs a function on a new thread immediately when it is created', 'Wraps a callable and delivers its result into a future, to run later', 'Caches the return value of a function for repeated calls to it', 'Creates a whole thread pool around the given function object'], a: 1,
      why: 'It is a callable plus a future. A pool queues the task, a worker runs it, and the caller reads the result from the future.' },

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
      opts: ['It does not have to be: reduce always keeps the original order', 'The library may regroup operands across threads, so grouping must not matter', 'Only so that the call compiles when an execution policy is given', 'Because reduce always runs on a graphics card, never on a CPU'], a: 1,
      why: 'Unlike `std::accumulate`, `reduce` is free to combine partial results in any grouping. (For floating-point sums the result may differ slightly.)' },

    { sec: 'parallel', q: 'What must be true of the callback passed to `std::for_each(std::execution::par, ...)`?',
      opts: ['It must be written as a lambda expression', 'It must be safe to call from several threads at once', 'It must be both noexcept and constexpr to be accepted', 'Nothing: the library adds all the locking itself'], a: 1,
      why: 'The library runs it on several threads, so an unsynchronised write to shared state is a data race (undefined behaviour).' }
  ]
};
