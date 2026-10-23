/* Quiz questions for the 'threads' topic. Loaded by 07-multithreading-quiz.html. */
CT.quizData.threads = {
  id: 'threads',
  questions: [
    { sec: 's1', q: 'What do the threads of one process share, and what does each thread have of its own?',
      opts: ['They share nothing and communicate only through operating-system pipes', 'They share the heap and globals; each has its own stack and registers', 'They share the stack; each thread has its own private heap', 'They share registers; each has its own heap and its own globals'], a: 1,
      why: 'Sharing the address space is what makes threads cheap to communicate but dangerous: any shared mutable data needs synchronization.' },

    { sec: 's2', q: 'What happens when this program runs?',
      code: String.raw`
#include <thread>
int main() {
    std::thread t([] { /* work */ });
}   // main returns`,
      opts: ['It exits normally and the thread is cleaned up by the runtime', 'std::terminate is called: the thread is still joinable when destroyed', 'The thread is joined automatically by the thread destructor', 'It fails to compile because the thread object is never joined'], a: 1,
      why: 'A `std::thread` must be joined or detached before destruction. Otherwise the destructor calls `std::terminate`. (C++20 `std::jthread` joins automatically.)' },

    { sec: 's3', q: 'Two threads each execute the function below on the same global `counter`, then both are joined. What is true?',
      code: String.raw`
int counter = 0;
void work() { for (int i = 0; i < 1000; ++i) ++counter; }`,
      opts: ['counter is always 2000, since both loops run to completion', 'A data race (undefined behavior); the result may be below 2000', 'counter is always 1000, because only one thread wins', 'It does not compile, since counter is not atomic'], a: 1,
      why: '`++counter` is load, add, store. Interleavings lose updates, and the unsynchronised concurrent write is formally undefined behavior.' },

    { sec: 's4', q: 'Which change makes that counter correct?',
      opts: ['Declare the counter as volatile int so that reads are fresh', 'Declare std::atomic<int> counter (or protect it with a mutex)', 'Declare the work function inline so the loop is optimized', 'Join the threads in the opposite order to avoid overlap'], a: 1,
      why: '`volatile` gives neither atomicity nor ordering. An atomic makes each increment indivisible; a mutex serialises the critical section.' },

    { sec: 's4', q: 'Why prefer `std::lock_guard` over calling `m.lock()` and `m.unlock()` yourself?',
      opts: ['It is faster than calling lock and unlock by hand each time', 'It unlocks automatically (RAII), even on early return or exception', 'It allows the same thread to lock the same mutex recursively', 'It avoids the need for a mutex object altogether'], a: 1,
      why: 'If code between `lock()` and `unlock()` throws or returns, a manual unlock is skipped and every other thread blocks forever.' },

    { sec: 's5', q: 'Thread A locks `m1` then `m2`. Thread B locks `m2` then `m1`. What can happen, and what is the best fix?',
      opts: ['Nothing: mutexes are fair, so the threads simply take turns', 'Deadlock; fix with a fixed lock order or std::scoped_lock(m1, m2)', 'A data race; fix by declaring the protected data volatile', 'Starvation; fix by lowering one thread\'s priority a little'], a: 1,
      why: 'Each holds one lock and waits for the other: circular wait. Locking in the same order everywhere, or locking both at once with `scoped_lock`/`std::lock`, removes the cycle.' },

    { sec: 's5', q: 'Which of these is NOT one of the four conditions required for a deadlock?',
      opts: ['Mutual exclusion: only one thread may hold the resource', 'Hold and wait: a thread holds one lock while requesting another', 'Circular wait: a cycle of threads each waiting for the next', 'All locks must be recursive so a thread can re-enter them'], a: 3,
      why: 'The four Coffman conditions are mutual exclusion, hold and wait, no preemption, and circular wait. Breaking any one of them prevents deadlock.' },

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

    { sec: 's2', q: 'What is the problem with this code?',
      code: String.raw`
void inc(int& n) { ++n; }
int x = 0;
std::thread t(inc, x);
t.join();`,
      opts: ['Nothing is wrong: x is passed to the thread by reference', 'It does not compile: arguments are copied, so pass std::ref(x)', 'x is incremented twice by the thread before it ends', 'It leaks the thread object when the function returns'], a: 1,
      why: '`std::thread` copies its arguments into internal storage and passes them as rvalues, which cannot bind to `int&`. Write `std::thread t(inc, std::ref(x));`.' },

    { sec: 's2', q: 'What is the bug here?',
      code: String.raw`
void f() {
    int local = 0;
    std::thread t([&] { ++local; });
    t.detach();
}`,
      opts: ['There is no bug in this code; the thread finishes first', 'The detached thread may use local after f() returns and destroys it', 'detach is not allowed with lambda expressions as thread bodies', 'The thread never starts running because it was detached'], a: 1,
      why: 'Capturing by reference and detaching lets the thread outlive the variable. Capture by value, or join before returning.' },

    { sec: 's3', q: 'Which of these is thread-safe without any extra synchronization?',
      opts: ['Two threads calling `push_back` on the same `std::vector`', 'Many threads only reading from the same const `std::vector`', 'One thread writing and another reading the same `int`', 'Two threads writing to the same `std::string`'], a: 1,
      why: 'Concurrent reads of data nobody modifies are safe. Any concurrent write plus access needs synchronization, including `push_back` on a standard container.' },

    { sec: 's11', q: 'Is initialization of a function-local `static` variable thread-safe in C++11 and later?',
      opts: ['No: you must always add a mutex yourself around the static variable', 'Yes: it runs exactly once even if several threads reach it together', 'Only for primitive types such as int and double, not for classes', 'Only if the static variable is declared const as well'], a: 1,
      why: 'This "magic statics" guarantee is why the Meyers Singleton needs no explicit locking for its construction.' },

    { sec: 's11', q: 'How can you detect data races in a C++ program?',
      opts: ['Add more print statements to the code and rerun it often', 'Compile with ThreadSanitizer (-fsanitize=thread) and run the tests', 'Use -O3 so the compiler reorders the accesses safely', 'Declare every shared variable volatile'], a: 1,
      why: 'ThreadSanitizer instruments memory accesses and reports conflicting unsynchronised accesses with stack traces. Helgrind and DRD help with lock-order issues.' },

    { sec: 's11', q: 'Why can several threads printing with `std::cout << a << b << \'\\n\'` produce garbled lines?',
      opts: ['cout cannot be used from several threads at the same time', 'Each << is a separate operation, so output from threads can interleave', 'cout is buffered, which reorders the lines between the threads', 'False sharing corrupts the internal output buffer of the stream'], a: 1,
      why: 'The stream itself does not crash, but the pieces of different lines mix. Build the full string first and write it once, or protect output with a mutex.' },

    { sec: 'interface-races', q: 'Every member function of this shared stack locks a mutex internally. Why is the caller\'s code still racy?',
      code: String.raw`
SafeStack<int> s;                 // shared by several threads
if (!s.empty()) {
    int v = s.top();
    s.pop();
    use(v);
}`,
      opts: ['The mutex is not recursive, so the calls block each other here', 'Each call is atomic but the sequence is not: another thread can pop in between', 'lock_guard cannot protect a std::stack from concurrent use', 'empty() must be called twice before the result can be trusted fully'], a: 1,
      why: 'This is a check-then-act race built into the interface. The cure is to change the interface, not to add more locking inside the individual calls.' },

    { sec: 'interface-races', q: 'What is the best fix for that stack?',
      opts: ['Declare every method of the stack volatile to publish changes', 'Provide one try_pop() that checks, reads and removes under one lock', 'Call empty() twice to be sure that the stack has elements', 'Call notify_all() after each pop to wake the other threads'], a: 1,
      why: 'Offer whole operations rather than steps, so callers never need to check and act separately. `empty()` may remain as a hint, but its answer can be stale the moment it returns.' },

    { sec: 's5', q: 'Can two threads deadlock without any mutex being involved?',
      opts: ['No: deadlock always needs at least one mutex to be involved somewhere', 'Yes: for example each thread joins the other, or waits in a future cycle', 'Only with atomics, when two threads spin waiting on each other', 'Only if one of the two threads has been detached earlier'], a: 1,
      why: 'Deadlock is a cycle of waiting. The guideline is general: do not wait for another thread if there is a chance it is waiting for you.' },

    { sec: 's5', q: 'What does a lock hierarchy (levels on mutexes) give you?',
      opts: ['Faster locking than a plain mutex, thanks to cached lock levels', 'A thread may lock only lower levels than it holds, so cycles cannot form', 'Automatic unlocking at the end of the enclosing scope, like RAII', 'Fair scheduling between the threads that wait for the same lock'], a: 1,
      why: 'Runtime-checked ordering turns a rare, timing-dependent deadlock into a deterministic error you can find in testing.' },

    { sec: 's5', q: 'Why should you not call user-supplied code (a callback, a virtual function) while holding a lock?',
      opts: ['It is slower than calling the callback after releasing the lock', 'It may take another lock, or keep a reference to the protected data', 'Callbacks cannot be called while a mutex is held', 'The lock would be released early by the callback call'], a: 1,
      why: 'You do not control what that code does. Never pass out references to protected data, and avoid holding a lock across calls to code you do not own.' },

    { sec: 's2', q: 'What is the problem with this code?',
      code: String.raw`
void f(int i, const std::string& s);

void g() {
    char buffer[64] = "hi";
    std::thread t(f, 1, buffer);
    t.detach();
}`,
      opts: ['Nothing: arguments are converted on the calling thread first, so it is safe', 'The char* is copied and converted to std::string in the new thread, too late', 'detach cannot be used with a free function as the thread body', 'buffer is far too large to be copied into a new thread safely'], a: 1,
      why: 'The thread constructor copies the arguments as given, and the conversion to the parameter type happens later, in the new thread. Convert first: `std::thread t(f, 1, std::string(buffer));`.' },

    { sec: 's2', q: 'Why does the destructor of a joinable `std::thread` call `std::terminate` instead of joining or detaching for you?',
      opts: ['Implicit join hides long waits, implicit detach leaves a thread using dead locals', 'Joining inside a destructor is not possible in standard C++, so it was left out', 'Calling detach in a destructor is forbidden by the C++ standard, so it terminates', 'It lets the runtime start threads a little faster than it otherwise could'], a: 0,
      why: 'Both implicit options have worse failure modes (hard-to-find performance problems, or undefined behavior). Make the thread unjoinable on every path with an RAII guard, or use `std::jthread` in C++20.' },

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
      why: 'It is the standard thread-safe one-time initialization. The other threads block until the first call returns, then continue with the initialized state.' }
  ]
};
