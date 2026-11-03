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

    { sec: 'models', q: 'What is the difference between concurrency and parallelism?',
      opts: ['Parallel tasks run at the same instant; concurrent ones may take turns', 'They are two names for exactly the same thing', 'Concurrency needs several cores, but parallelism does not need them', 'Parallelism is only possible when you use separate processes'], a: 0,
      why: 'Concurrency is about tasks being in progress together. Parallelism is about running at the same instant.' },

    { sec: 'models', q: 'For a CPU-bound job, about how many threads make sense?',
      opts: ['About one per hardware thread', 'As many threads as there are tasks to do', 'Always exactly one thread, whatever the machine', 'Ten times the number of cores on the machine'], a: 0,
      why: 'More threads than cores only adds context switches. Waiting-bound work can use more.' },

    { sec: 'rules', q: 'What happens if a joinable `std::thread` is destroyed?',
      opts: ['`std::terminate` is called', 'It is joined automatically', 'It is detached automatically', 'Nothing: the thread just stops'], a: 0,
      why: 'The standard chose termination over a silent join or detach.' },

    { sec: 'rules', q: 'How do you pass a variable by reference to a `std::thread` function?',
      opts: ['Wrap it in `std::ref`', 'Pass it normally', 'Use a pointer to a pointer', 'Declare it volatile'], a: 0,
      why: 'Arguments are copied into the thread; std::ref passes a reference.' },

    { sec: 'join', q: 'What does a ThreadGuard-style RAII class guarantee?',
      opts: ['The thread is joined however the scope is left', 'The thread never gets the chance to start running', 'The thread is detached as soon as it is created', 'The thread runs faster than an unguarded thread'], a: 0,
      why: 'The destructor joins on every path.' },

    { sec: 'rules', q: 'What is the danger of detaching a thread that captured a local by reference?',
      opts: ['The thread may use the local after it is destroyed', 'The thread cannot start because of the reference capture', 'The local variable is copied twice by the lambda', 'The thread is joined twice when the scope ends'], a: 0,
      why: 'A detached thread can outlive the function and write to a dead variable.' }
  ]
};
