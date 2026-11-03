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

    { sec: 'signals', q: 'A `std::promise<int>` is destroyed without `set_value` or `set_exception` ever being called. What does `get()` on its future do?',
      opts: ['It blocks forever, waiting for a value that never comes', 'It throws std::future_error with broken_promise', 'It returns 0, the default value of the int', 'It terminates the program through std::terminate'], a: 1,
      why: 'The promise breaks and the future is made ready with an error, so the waiting thread is not left hanging.' },

    { sec: 'signals', q: 'Which type lets several threads wait for the same result?',
      opts: ['`std::future`', '`std::shared_future`', '`std::packaged_task`', '`std::once_flag`'], a: 1,
      why: '`std::future` is move-only and can be read once. A `shared_future` is copyable, so every thread gets its own handle on the same result.' },

    { sec: 'signals', q: 'What does `std::packaged_task<int(int)>` do?',
      opts: ['Runs a function on a new thread immediately when it is created', 'Wraps a callable and delivers its result into a future, to run later', 'Caches the return value of a function for repeated calls to it', 'Creates a whole thread pool around the given function object'], a: 1,
      why: 'It is a callable plus a future. A pool queues the task, a worker runs it, and the caller reads the result from the future.' },

    { sec: 'why', q: 'What happens to an exception thrown inside a plain `std::thread` function that escapes?',
      opts: ['`std::terminate` is called', 'It is rethrown in main automatically', 'It is silently ignored by the library', 'It is stored so that you can read it later'], a: 0,
      why: 'A task with a future is the way to carry it back.' },

    { sec: 'futures', q: 'Which launch policy guarantees that `std::async` runs on a new thread?',
      opts: ['`std::launch::async`', '`std::launch::deferred`', 'The default policy', '`std::launch::lazy`'], a: 0,
      why: 'The default may defer the call until get().' },

    { sec: 'futures', q: 'What does `future::get()` do?',
      opts: ['Waits for the result and returns it, once', 'Starts the task if it has not started yet', 'Returns at once with a copy of the value', 'Cancels the task and discards its result'], a: 0,
      why: 'get() blocks until ready and can be called only once.' },

    { sec: 'destructor', q: 'What happens at the end of the statement `std::async(std::launch::async, work);` with the result discarded?',
      opts: ['The temporary future blocks until work() finishes', 'work() is cancelled before it has finished', 'The program terminates with an error message', 'work() keeps running quietly in the background'], a: 0,
      why: 'The future from async waits in its destructor.' },

    { sec: 'exceptions', q: 'Where is an exception thrown inside an `async` task rethrown?',
      opts: ['From `future::get()`', 'From the `async` call', 'In the worker thread again', 'Nowhere'], a: 0,
      why: 'The exception is stored in the shared state and rethrown by get().' },

    { sec: 'promise', q: 'What does a `std::promise` give you?',
      opts: ['The writing end of a one-shot channel to a future', 'A second thread that runs your function for you', 'A mutex that protects the shared result value', 'A repeating signal that you can send many times'], a: 0,
      why: 'set_value or set_exception once.' },

    { sec: 'promise', q: 'What does the future see if the promise is destroyed without a value?',
      opts: ['A `broken_promise` exception', 'A default constructed value of the type', 'It waits forever without ever returning', 'A null pointer that the caller must check'], a: 0,
      why: 'The library reports the broken promise instead of waiting forever.' },

    { sec: 'timeouts', q: 'What does `wait_for` return when the task has not finished within the time?',
      opts: ['`future_status::timeout`', '`future_status::ready`, as if it had finished', 'It throws an exception to the caller', 'It cancels the task and returns the status'], a: 0,
      why: 'timeout means not ready yet; ask again or do other work.' }
  ]
};
