/* Quiz questions for the 'threads' topic. Loaded by 07-multithreading-quiz.html. */
CT.quizData.threads = {
  id: 'threads',
  questions: [
    { sec: 's1', q: 'What do the threads of one process share, and what does each thread have of its own?',
      opts: ['They share nothing', 'They share the heap and globals; each has its own stack and registers', 'They share the stack; each has its own heap', 'They share registers only'], a: 1,
      why: 'Sharing the address space is what makes threads cheap to communicate but dangerous: any shared mutable data needs synchronization.' },

    { sec: 's2', q: 'What happens when this program runs?',
      code: String.raw`
#include <thread>
int main() {
    std::thread t([] { /* work */ });
}   // main returns`,
      opts: ['It exits normally and the thread is cleaned up', 'std::terminate is called because the thread is still joinable when its object is destroyed', 'The thread is joined automatically', 'Compile error'], a: 1,
      why: 'A `std::thread` must be joined or detached before destruction. Otherwise the destructor calls `std::terminate`. (C++20 `std::jthread` joins automatically.)' },

    { sec: 's3', q: 'Two threads each execute the function below on the same global `counter`, then both are joined. What is true?',
      code: String.raw`
int counter = 0;
void work() { for (int i = 0; i < 1000; ++i) ++counter; }`,
      opts: ['counter is always 2000', 'It is a data race (undefined behavior); the result may be less than 2000', 'counter is always 1000', 'It does not compile'], a: 1,
      why: '`++counter` is load, add, store. Interleavings lose updates, and the unsynchronised concurrent write is formally undefined behavior.' },

    { sec: 's4', q: 'Which change makes that counter correct?',
      opts: ['Declare `volatile int counter`', 'Declare `std::atomic<int> counter` (or guard the increment with a mutex)', 'Make `work` inline', 'Join the threads in the opposite order'], a: 1,
      why: '`volatile` gives neither atomicity nor ordering. An atomic makes each increment indivisible; a mutex serialises the critical section.' },

    { sec: 's4', q: 'Why prefer `std::lock_guard` over calling `m.lock()` and `m.unlock()` yourself?',
      opts: ['It is faster', 'It unlocks automatically (RAII), even on early return or exception, so the mutex cannot stay locked by accident', 'It allows recursive locking', 'It avoids the need for a mutex'], a: 1,
      why: 'If code between `lock()` and `unlock()` throws or returns, a manual unlock is skipped and every other thread blocks forever.' },

    { sec: 's5', q: 'Thread A locks `m1` then `m2`. Thread B locks `m2` then `m1`. What can happen, and what is the best fix?',
      opts: ['Nothing: mutexes are fair', 'Deadlock; fix with a consistent lock order or `std::scoped_lock(m1, m2)`', 'A data race; fix with volatile', 'Starvation; fix by lowering thread priority'], a: 1,
      why: 'Each holds one lock and waits for the other: circular wait. Locking in the same order everywhere, or locking both at once with `scoped_lock`/`std::lock`, removes the cycle.' },

    { sec: 's5', q: 'Which of these is NOT one of the four conditions required for a deadlock?',
      opts: ['Mutual exclusion', 'Hold and wait', 'Circular wait', 'All locks must be recursive'], a: 3,
      why: 'The four Coffman conditions are mutual exclusion, hold and wait, no preemption, and circular wait. Breaking any one of them prevents deadlock.' },

    { sec: 's7', q: 'Why must `condition_variable::wait` be used with a predicate (or in a loop)?',
      opts: ['It makes wait faster', 'Threads can wake spuriously, and the condition may change again before the thread reacquires the lock, so it must be re-checked', 'The OS requires it', 'Otherwise wait never returns'], a: 1,
      why: '`cv.wait(lk, pred)` is shorthand for `while (!pred()) cv.wait(lk);`. A bare `wait` can return with the condition still false.' },

    { sec: 's7', q: 'Why does `condition_variable::wait` take a `std::unique_lock` rather than a `std::lock_guard`?',
      opts: ['unique_lock is faster', 'wait must unlock the mutex while sleeping and relock it on wake-up, which lock_guard cannot do', 'lock_guard cannot lock a mutex', 'It is only a convention'], a: 1,
      why: 'Unlocking while the thread sleeps is what lets the producer enter. `lock_guard` has no unlock operation.' },

    { sec: 's7', q: 'What is a "lost wakeup"?',
      opts: ['The OS forgetting a thread', 'A notification sent before the waiter began sleeping (because the shared state was changed without the mutex), so the waiter sleeps forever', 'A thread waking twice', 'A mutex being unlocked twice'], a: 1,
      why: 'Changing the condition under the mutex makes "check, then sleep" atomic with respect to the update, which closes the window in which a notification can be missed.' },

    { sec: 's7', q: 'When is `notify_all()` needed instead of `notify_one()`?',
      opts: ['Never, notify_one is always enough', 'When several waiters may be able to proceed, waiters wait for different conditions, or at shutdown to wake everyone', 'Only when using atomics', 'When the queue is empty'], a: 1,
      why: '`notify_one` wakes just one thread. For broadcast conditions such as "stop requested", all waiters must be woken.' },

    { sec: 's2', q: 'What is the problem with this code?',
      code: String.raw`
void inc(int& n) { ++n; }
int x = 0;
std::thread t(inc, x);
t.join();`,
      opts: ['Nothing', 'It does not compile: thread arguments are copied, so you need std::ref(x) to pass a reference', 'x is incremented twice', 'It leaks the thread'], a: 1,
      why: '`std::thread` copies its arguments into internal storage and passes them as rvalues, which cannot bind to `int&`. Write `std::thread t(inc, std::ref(x));`.' },

    { sec: 's2', q: 'What is the bug here?',
      code: String.raw`
void f() {
    int local = 0;
    std::thread t([&] { ++local; });
    t.detach();
}`,
      opts: ['None', 'The detached thread may use `local` after f() has returned and destroyed it (dangling reference)', 'detach is not allowed with lambdas', 'The thread never runs'], a: 1,
      why: 'Capturing by reference and detaching lets the thread outlive the variable. Capture by value, or join before returning.' },

    { sec: 's3', q: 'Which of these is thread-safe without any extra synchronization?',
      opts: ['Two threads calling `push_back` on the same `std::vector`', 'Many threads only reading from the same const `std::vector`', 'One thread writing and another reading the same `int`', 'Two threads writing to the same `std::string`'], a: 1,
      why: 'Concurrent reads of data nobody modifies are safe. Any concurrent write plus access needs synchronization, including `push_back` on a standard container.' },

    { sec: 's11', q: 'Is initialization of a function-local `static` variable thread-safe in C++11 and later?',
      opts: ['No, you must add a mutex', 'Yes: it is performed exactly once even if several threads reach it concurrently', 'Only for primitive types', 'Only if it is const'], a: 1,
      why: 'This "magic statics" guarantee is why the Meyers Singleton needs no explicit locking for its construction.' },

    { sec: 's11', q: 'How can you detect data races in a C++ program?',
      opts: ['Add more print statements', 'Compile with ThreadSanitizer (`-fsanitize=thread`) and run the tests', 'Use `-O3`', 'Use `volatile` on all variables'], a: 1,
      why: 'ThreadSanitizer instruments memory accesses and reports conflicting unsynchronised accesses with stack traces. Helgrind and DRD help with lock-order issues.' },

    { sec: 's11', q: 'Why can several threads printing with `std::cout << a << b << \'\\n\'` produce garbled lines?',
      opts: ['cout is not usable from threads', 'Each `<<` is a separate operation, so output from different threads can interleave between them', 'cout is buffered', 'Because of false sharing'], a: 1,
      why: 'The stream itself does not crash, but the pieces of different lines mix. Build the full string first and write it once, or protect output with a mutex.' },

    { sec: 'interface-races', q: 'Every member function of this shared stack locks a mutex internally. Why is the caller\'s code still racy?',
      code: String.raw`
SafeStack<int> s;                 // shared by several threads
if (!s.empty()) {
    int v = s.top();
    s.pop();
    use(v);
}`,
      opts: ['The mutex is not recursive', 'Each call is atomic but the sequence of three calls is not: another thread can pop between the check and top(), so the check is stale', 'lock_guard cannot protect a std::stack', 'empty() must be called twice'], a: 1,
      why: 'This is a check-then-act race built into the interface. The cure is to change the interface, not to add more locking inside the individual calls.' },

    { sec: 'interface-races', q: 'What is the best fix for that stack?',
      opts: ['Make every method `volatile`', 'Provide one operation such as `std::optional<T> try_pop()` that checks, reads and removes under a single lock', 'Call `empty()` twice to be sure', 'Use `notify_all()` after each pop'], a: 1,
      why: 'Offer whole operations rather than steps, so callers never need to check and act separately. `empty()` may remain as a hint, but its answer can be stale the moment it returns.' },

    { sec: 's5', q: 'Can two threads deadlock without any mutex being involved?',
      opts: ['No: deadlock requires a mutex', 'Yes: for example each thread calls join() on the other, or they wait in a cycle on futures or condition variables', 'Only with atomics', 'Only if one thread is detached'], a: 1,
      why: 'Deadlock is a cycle of waiting. The guideline is general: do not wait for another thread if there is a chance it is waiting for you.' },

    { sec: 's5', q: 'What does a lock hierarchy (levels on mutexes) give you?',
      opts: ['Faster locking', 'A thread may only lock a mutex of lower level than any it holds, so cycles are impossible, and a violation is detected the first time the wrong order is attempted, even if no deadlock actually occurs', 'Automatic unlocking', 'Fair scheduling'], a: 1,
      why: 'Runtime-checked ordering turns a rare, timing-dependent deadlock into a deterministic error you can find in testing.' },

    { sec: 's5', q: 'Why should you not call user-supplied code (a callback, a virtual function) while holding a lock?',
      opts: ['It is slower', 'It may take another lock (a hidden nested lock, risking deadlock) or keep a pointer or reference to the protected data and use it later without the lock', 'Callbacks cannot be called with a mutex held', 'The lock would be released early'], a: 1,
      why: 'You do not control what that code does. Never pass out references to protected data, and avoid holding a lock across calls to code you do not own.' },

    { sec: 's2', q: 'What is the problem with this code?',
      code: String.raw`
void f(int i, const std::string& s);

void g() {
    char buffer[64] = "hi";
    std::thread t(f, 1, buffer);
    t.detach();
}`,
      opts: ['Nothing: arguments are converted on the calling thread', 'The char* is copied as is and converted to std::string inside the new thread, possibly after g() has returned: a dangling pointer', 'detach cannot be used with a free function', 'buffer is too large to copy'], a: 1,
      why: 'The thread constructor copies the arguments as given, and the conversion to the parameter type happens later, in the new thread. Convert first: `std::thread t(f, 1, std::string(buffer));`.' },

    { sec: 's2', q: 'Why does the destructor of a joinable `std::thread` call `std::terminate` instead of joining or detaching for you?',
      opts: ['An implicit join can hide long waits and an implicit detach can leave the thread using destroyed locals, so the standard makes the mistake loud', 'Joining inside a destructor is impossible', 'detach is not allowed in destructors', 'It makes threads start faster'], a: 0,
      why: 'Both implicit options have worse failure modes (hard-to-find performance problems, or undefined behavior). Make the thread unjoinable on every path with an RAII guard, or use `std::jthread` in C++20.' },

    { sec: 'mutex-types', q: 'What happens if one thread locks a plain `std::mutex` a second time without unlocking it in between?',
      opts: ['The second lock is ignored', 'Undefined behaviour, in practice usually a deadlock', 'It always throws `std::system_error`', 'It waits for a timeout and continues'], a: 1,
      why: 'A `std::mutex` is not re-lockable. Only `std::recursive_mutex` lets the owning thread lock again, which is usually a sign of a design problem.' },

    { sec: 'mutex-types', q: 'A public method `depositTwice()` locks a mutex and calls the public `deposit()`, which locks the same mutex. What is the cleaner fix than a `recursive_mutex`?',
      opts: ['Use `volatile`', 'Split into a public method that locks once and a private helper that assumes the lock is held', 'Make the mutex `static`', 'Unlock before calling `deposit()`'], a: 1,
      why: 'The locking public method calls a private `...Locked()` function that both public methods share. The lock is taken exactly once and the contract is explicit.' },

    { sec: 'mutex-types', q: 'When does a `std::shared_mutex` pay off compared with a plain `std::mutex`?',
      opts: ['Whenever there are two threads', 'When many threads read for a while and writes are rare', 'When the critical section is a single increment', 'When threads must run in a fixed order'], a: 1,
      why: 'It costs more per lock than a `mutex`, so it only helps when readers dominate and each read holds the lock long enough to overlap with others.' },

    { sec: 'mutex-types', q: 'What does `std::call_once(flag, fn)` guarantee when eight threads call it at the same time?',
      opts: ['`fn` runs once per thread', '`fn` runs exactly once; the other callers wait until it has finished', '`fn` may run twice but not more', 'Nothing: you still need a mutex'], a: 1,
      why: 'It is the standard thread-safe one-time initialization. The other threads block until the first call returns, then continue with the initialized state.' }
  ]
};
