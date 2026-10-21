/* Quiz questions for the 'threads' topic. Loaded by 07-multithreading-quiz.html. */
CT.quizData.threads = {
  id: 'threads',
  questions: [
    { q: 'What do the threads of one process share, and what does each thread have of its own?',
      opts: ['They share nothing', 'They share the heap and globals; each has its own stack and registers', 'They share the stack; each has its own heap', 'They share registers only'], a: 1,
      why: 'Sharing the address space is what makes threads cheap to communicate but dangerous: any shared mutable data needs synchronization.' },

    { q: 'What happens when this program runs?',
      code: String.raw`
#include <thread>
int main() {
    std::thread t([] { /* work */ });
}   // main returns`,
      opts: ['It exits normally and the thread is cleaned up', 'std::terminate is called because the thread is still joinable when its object is destroyed', 'The thread is joined automatically', 'Compile error'], a: 1,
      why: 'A `std::thread` must be joined or detached before destruction. Otherwise the destructor calls `std::terminate`. (C++20 `std::jthread` joins automatically.)' },

    { q: 'Two threads each execute the function below on the same global `counter`, then both are joined. What is true?',
      code: String.raw`
int counter = 0;
void work() { for (int i = 0; i < 1000; ++i) ++counter; }`,
      opts: ['counter is always 2000', 'It is a data race (undefined behavior); the result may be less than 2000', 'counter is always 1000', 'It does not compile'], a: 1,
      why: '`++counter` is load, add, store. Interleavings lose updates, and the unsynchronised concurrent write is formally undefined behavior.' },

    { q: 'Which change makes that counter correct?',
      opts: ['Declare `volatile int counter`', 'Declare `std::atomic<int> counter` (or guard the increment with a mutex)', 'Make `work` inline', 'Join the threads in the opposite order'], a: 1,
      why: '`volatile` gives neither atomicity nor ordering. An atomic makes each increment indivisible; a mutex serialises the critical section.' },

    { q: 'Why prefer `std::lock_guard` over calling `m.lock()` and `m.unlock()` yourself?',
      opts: ['It is faster', 'It unlocks automatically (RAII), even on early return or exception, so the mutex cannot stay locked by accident', 'It allows recursive locking', 'It avoids the need for a mutex'], a: 1,
      why: 'If code between `lock()` and `unlock()` throws or returns, a manual unlock is skipped and every other thread blocks forever.' },

    { q: 'Thread A locks `m1` then `m2`. Thread B locks `m2` then `m1`. What can happen, and what is the best fix?',
      opts: ['Nothing: mutexes are fair', 'Deadlock; fix with a consistent lock order or `std::scoped_lock(m1, m2)`', 'A data race; fix with volatile', 'Starvation; fix by lowering thread priority'], a: 1,
      why: 'Each holds one lock and waits for the other: circular wait. Locking in the same order everywhere, or locking both at once with `scoped_lock`/`std::lock`, removes the cycle.' },

    { q: 'Which of these is NOT one of the four conditions required for a deadlock?',
      opts: ['Mutual exclusion', 'Hold and wait', 'Circular wait', 'All locks must be recursive'], a: 3,
      why: 'The four Coffman conditions are mutual exclusion, hold and wait, no preemption, and circular wait. Breaking any one of them prevents deadlock.' },

    { q: 'Why must `condition_variable::wait` be used with a predicate (or in a loop)?',
      opts: ['It makes wait faster', 'Threads can wake spuriously, and the condition may change again before the thread reacquires the lock, so it must be re-checked', 'The OS requires it', 'Otherwise wait never returns'], a: 1,
      why: '`cv.wait(lk, pred)` is shorthand for `while (!pred()) cv.wait(lk);`. A bare `wait` can return with the condition still false.' },

    { q: 'Why does `condition_variable::wait` take a `std::unique_lock` rather than a `std::lock_guard`?',
      opts: ['unique_lock is faster', 'wait must unlock the mutex while sleeping and relock it on wake-up, which lock_guard cannot do', 'lock_guard cannot lock a mutex', 'It is only a convention'], a: 1,
      why: 'Unlocking while the thread sleeps is what lets the producer enter. `lock_guard` has no unlock operation.' },

    { q: 'What is a "lost wakeup"?',
      opts: ['The OS forgetting a thread', 'A notification sent before the waiter began sleeping (because the shared state was changed without the mutex), so the waiter sleeps forever', 'A thread waking twice', 'A mutex being unlocked twice'], a: 1,
      why: 'Changing the condition under the mutex makes "check, then sleep" atomic with respect to the update, which closes the window in which a notification can be missed.' },

    { q: 'When is `notify_all()` needed instead of `notify_one()`?',
      opts: ['Never, notify_one is always enough', 'When several waiters may be able to proceed, waiters wait for different conditions, or at shutdown to wake everyone', 'Only when using atomics', 'When the queue is empty'], a: 1,
      why: '`notify_one` wakes just one thread. For broadcast conditions such as "stop requested", all waiters must be woken.' },

    { q: 'When is `std::atomic` NOT enough on its own?',
      opts: ['For a counter', 'For a stop flag', 'When an invariant spans several variables that must change together', 'For a pointer swap'], a: 2,
      why: 'Atomics make operations on one variable indivisible. Updating two related variables consistently needs a mutex (or a single atomic holding both).' },

    { q: 'Is `volatile` a valid way to share a flag between threads in C++?',
      opts: ['Yes, it guarantees visibility', 'No: it gives no atomicity or inter-thread ordering; use std::atomic', 'Yes, but only for bool', 'Yes, on x86 only'], a: 1,
      why: 'Concurrent access to a `volatile` variable is still a data race. `volatile` is for memory-mapped hardware, not thread synchronization.' },

    { q: 'What is the default memory order of `std::atomic` operations, and what does it mean?',
      opts: ['relaxed: no ordering', 'seq_cst: all threads agree on a single global order of atomic operations (strongest and simplest)', 'acquire for loads only', 'release for stores only'], a: 1,
      why: 'Sequential consistency is the default because it is the easiest to reason about. Weaker orders are an optimisation that needs justification.' },

    { q: 'What does this guarantee?',
      code: String.raw`
int data = 0;
std::atomic<bool> ready{false};

// thread 1
data = 42;
ready.store(true, std::memory_order_release);

// thread 2
while (!ready.load(std::memory_order_acquire)) {}
std::cout << data;`,
      opts: ['It may print 0 or 42', 'It prints 42: the release store publishes everything written before it to a thread whose acquire load sees true', 'It is a data race', 'It prints nothing'], a: 1,
      why: 'A release store paired with an acquire load that observes it creates a happens-before edge, so the write to `data` is visible. With relaxed ordering this would not be guaranteed.' },

    { q: 'What does this code do?',
      code: String.raw`
std::async(std::launch::async, slowTask);   // returned future is discarded
doOtherWork();`,
      opts: ['Runs slowTask in the background while doOtherWork runs', 'Effectively runs slowTask first: the temporary future\'s destructor blocks until the task finishes', 'Does not compile', 'Runs doOtherWork first'], a: 1,
      why: 'A future from `std::async` blocks in its destructor. Because the temporary is destroyed at the end of the statement, `doOtherWork` only starts after `slowTask` completes. Keep the future in a variable.' },

    { q: 'What happens if the function run by `std::async` throws, and you later call `future.get()`?',
      opts: ['The program terminates immediately', 'get() rethrows the exception in the calling thread', 'The exception is silently dropped', 'get() returns a default value'], a: 1,
      why: 'The exception is stored in the shared state and rethrown by `get()`. That makes futures the clean way to propagate errors out of worker threads.' },

    { q: 'What is the problem with this code?',
      code: String.raw`
void inc(int& n) { ++n; }
int x = 0;
std::thread t(inc, x);
t.join();`,
      opts: ['Nothing', 'It does not compile: thread arguments are copied, so you need std::ref(x) to pass a reference', 'x is incremented twice', 'It leaks the thread'], a: 1,
      why: '`std::thread` copies its arguments into internal storage and passes them as rvalues, which cannot bind to `int&`. Write `std::thread t(inc, std::ref(x));`.' },

    { q: 'What is the bug here?',
      code: String.raw`
void f() {
    int local = 0;
    std::thread t([&] { ++local; });
    t.detach();
}`,
      opts: ['None', 'The detached thread may use `local` after f() has returned and destroyed it (dangling reference)', 'detach is not allowed with lambdas', 'The thread never runs'], a: 1,
      why: 'Capturing by reference and detaching lets the thread outlive the variable. Capture by value, or join before returning.' },

    { q: 'What is false sharing?',
      opts: ['Two threads sharing one variable without a lock', 'Threads writing different variables that lie on the same cache line, causing the line to bounce between cores and slowing everything down', 'A mutex shared by unrelated objects', 'A shared_ptr copied between threads'], a: 1,
      why: 'Cores own memory in cache-line units (usually 64 bytes). Pad or align per-thread hot data (`alignas(64)`) so independent writers do not share a line.' },

    { q: 'In a thread pool worker loop, why is the task executed after releasing the queue mutex?',
      opts: ['It is only a style preference', 'Otherwise the lock would be held during the whole task, so only one task could run at a time and other workers could not take work', 'The mutex cannot be locked twice', 'Tasks must not use locks'], a: 1,
      why: 'Hold the lock only to pop the task. Running it outside the lock keeps workers parallel and avoids deadlocks if the task itself submits more work.' },

    { q: 'Which of these is thread-safe without any extra synchronization?',
      opts: ['Two threads calling `push_back` on the same `std::vector`', 'Many threads only reading from the same const `std::vector`', 'One thread writing and another reading the same `int`', 'Two threads writing to the same `std::string`'], a: 1,
      why: 'Concurrent reads of data nobody modifies are safe. Any concurrent write plus access needs synchronization, including `push_back` on a standard container.' },

    { q: 'Is initialization of a function-local `static` variable thread-safe in C++11 and later?',
      opts: ['No, you must add a mutex', 'Yes: it is performed exactly once even if several threads reach it concurrently', 'Only for primitive types', 'Only if it is const'], a: 1,
      why: 'This "magic statics" guarantee is why the Meyers Singleton needs no explicit locking for its construction.' },

    { q: 'How can you detect data races in a C++ program?',
      opts: ['Add more print statements', 'Compile with ThreadSanitizer (`-fsanitize=thread`) and run the tests', 'Use `-O3`', 'Use `volatile` on all variables'], a: 1,
      why: 'ThreadSanitizer instruments memory accesses and reports conflicting unsynchronised accesses with stack traces. Helgrind and DRD help with lock-order issues.' },

    { q: 'Why can several threads printing with `std::cout << a << b << \'\\n\'` produce garbled lines?',
      opts: ['cout is not usable from threads', 'Each `<<` is a separate operation, so output from different threads can interleave between them', 'cout is buffered', 'Because of false sharing'], a: 1,
      why: 'The stream itself does not crash, but the pieces of different lines mix. Build the full string first and write it once, or protect output with a mutex.' },

    { q: 'About how many worker threads should a pool for purely CPU-bound tasks have?',
      opts: ['One per task', 'About `std::thread::hardware_concurrency()`', 'Exactly 100', 'Always 1'], a: 1,
      why: 'More threads than cores only adds context switching (oversubscription). Threads that mostly wait on I/O can usefully outnumber the cores.' },

    { q: 'Why can a single-producer single-consumer ring buffer work without locks?',
      opts: ['Because it uses volatile', 'Each index is written by only one thread (head by the consumer, tail by the producer) and acquire/release atomics publish the data', 'Because the buffer never fills', 'Because the OS serialises threads'], a: 1,
      why: 'With exactly one writer per index, there are no conflicting writes. Release on the store and acquire on the load make the slot contents visible in the right order.' },

    { q: 'Every member function of this shared stack locks a mutex internally. Why is the caller\'s code still racy?',
      code: String.raw`
SafeStack<int> s;                 // shared by several threads
if (!s.empty()) {
    int v = s.top();
    s.pop();
    use(v);
}`,
      opts: ['The mutex is not recursive', 'Each call is atomic but the sequence of three calls is not: another thread can pop between the check and top(), so the check is stale', 'lock_guard cannot protect a std::stack', 'empty() must be called twice'], a: 1,
      why: 'This is a check-then-act race built into the interface. The cure is to change the interface, not to add more locking inside the individual calls.' },

    { q: 'What is the best fix for that stack?',
      opts: ['Make every method `volatile`', 'Provide one operation such as `std::optional<T> try_pop()` that checks, reads and removes under a single lock', 'Call `empty()` twice to be sure', 'Use `notify_all()` after each pop'], a: 1,
      why: 'Offer whole operations rather than steps, so callers never need to check and act separately. `empty()` may remain as a hint, but its answer can be stale the moment it returns.' },

    { q: 'Can two threads deadlock without any mutex being involved?',
      opts: ['No: deadlock requires a mutex', 'Yes: for example each thread calls join() on the other, or they wait in a cycle on futures or condition variables', 'Only with atomics', 'Only if one thread is detached'], a: 1,
      why: 'Deadlock is a cycle of waiting. The guideline is general: do not wait for another thread if there is a chance it is waiting for you.' },

    { q: 'What does a lock hierarchy (levels on mutexes) give you?',
      opts: ['Faster locking', 'A thread may only lock a mutex of lower level than any it holds, so cycles are impossible, and a violation is detected the first time the wrong order is attempted, even if no deadlock actually occurs', 'Automatic unlocking', 'Fair scheduling'], a: 1,
      why: 'Runtime-checked ordering turns a rare, timing-dependent deadlock into a deterministic error you can find in testing.' },

    { q: 'Why should you not call user-supplied code (a callback, a virtual function) while holding a lock?',
      opts: ['It is slower', 'It may take another lock (a hidden nested lock, risking deadlock) or keep a pointer or reference to the protected data and use it later without the lock', 'Callbacks cannot be called with a mutex held', 'The lock would be released early'], a: 1,
      why: 'You do not control what that code does. Never pass out references to protected data, and avoid holding a lock across calls to code you do not own.' },

    { q: 'What is the problem with this code?',
      code: String.raw`
void f(int i, const std::string& s);

void g() {
    char buffer[64] = "hi";
    std::thread t(f, 1, buffer);
    t.detach();
}`,
      opts: ['Nothing: arguments are converted on the calling thread', 'The char* is copied as is and converted to std::string inside the new thread, possibly after g() has returned: a dangling pointer', 'detach cannot be used with a free function', 'buffer is too large to copy'], a: 1,
      why: 'The thread constructor copies the arguments as given, and the conversion to the parameter type happens later, in the new thread. Convert first: `std::thread t(f, 1, std::string(buffer));`.' },

    { q: 'Why does the destructor of a joinable `std::thread` call `std::terminate` instead of joining or detaching for you?',
      opts: ['An implicit join can hide long waits and an implicit detach can leave the thread using destroyed locals, so the standard makes the mistake loud', 'Joining inside a destructor is impossible', 'detach is not allowed in destructors', 'It makes threads start faster'], a: 0,
      why: 'Both implicit options have worse failure modes (hard-to-find performance problems, or undefined behavior). Make the thread unjoinable on every path with an RAII guard, or use `std::jthread` in C++20.' }
  ]
};
