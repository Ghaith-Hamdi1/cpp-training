/* Quiz questions for the 'core' topic. Loaded by 03-core-language-quiz.html. */
CT.quizData.core = {
  id: 'core',
  questions: [
    { sec: 's1', q: 'What does RAII stand for, and what is its core idea?',
      opts: ['Resource Allocation Is Immediate: allocate everything at program start', 'Resource Acquisition Is Initialization: tie a resource\'s lifetime to an object so the destructor always releases it', 'Run At Initialization Instantly: run code before main', 'Reference And Instance Isolation: separate objects from references'], a: 1,
      why: 'Acquire in the constructor, release in the destructor. Because destructors run on scope exit, even during exceptions, resources cannot leak.' },

    { sec: 's7', q: 'What is the output?',
      code: String.raw`
struct Guard {
    Guard()  { std::cout << "open "; }
    ~Guard() { std::cout << "close "; }
};
void f() {
    Guard g;
    throw std::runtime_error("x");
}
int main() {
    try { f(); } catch (const std::exception&) { std::cout << "caught"; }
}`,
      opts: ['open caught', 'open close caught', 'open caught close', 'caught'], a: 1,
      why: 'Stack unwinding destroys `g` (printing "close") while the exception propagates out of `f`, before the catch block runs.' },

    { sec: 's7', q: 'What happens if a destructor throws while the stack is already unwinding from another exception?',
      opts: ['The second exception is ignored', 'std::terminate is called and the program ends', 'Both exceptions are caught together', 'Nothing special'], a: 1,
      why: 'Two active exceptions cannot be handled, so C++ calls `std::terminate`. That is why destructors must not let exceptions escape.' },

    { sec: 's7', q: 'How should you catch exceptions?',
      opts: ['By value', 'By `const` reference', 'By pointer', 'By rvalue reference'], a: 1,
      why: 'Catching by value copies and slices derived exception types. `catch (const std::exception& e)` is the standard idiom.' },

    { sec: 'raii-types', q: 'Which of these is NOT an RAII type?',
      opts: ['`std::lock_guard`', '`std::fstream`', 'a raw `FILE*` returned by `fopen`', '`std::unique_ptr`'], a: 2,
      why: 'A raw `FILE*` must be closed by hand with `fclose`, so an early return or exception leaks it. The other three release their resource in a destructor.' },

    { sec: 'raii-types', q: 'A scope guard holds a rollback action. What does calling `release()` on it before the end of the scope do?',
      opts: ['Runs the rollback immediately', 'Cancels the rollback: the work is committed', 'Throws an exception', 'Runs the rollback twice'], a: 1,
      why: 'The guard\'s destructor only runs the cleanup while it is still active. `release()` deactivates it once the work has succeeded.' },

    { sec: 'raii-types', q: 'What does the Rule of Zero say?',
      opts: ['Never write any constructor', 'Keep resources in members that are already RAII types, so the class needs no user-written destructor, copy or move operations', 'Always delete the copy constructor', 'Classes must have zero data members'], a: 1,
      why: 'If every member manages itself (`vector`, `string`, `unique_ptr`), the compiler-generated special members are correct and you write none.' },

    { sec: 's7', q: 'Inside a `catch` block, what is the difference between `throw;` and `throw e;`?',
      opts: ['They are identical', '`throw;` rethrows the original exception object; `throw e;` throws a copy of `e`, which slices if `e` is a base-class reference', '`throw;` terminates the program', '`throw e;` rethrows without copying'], a: 1,
      why: 'Use a bare `throw;` to rethrow. Throwing the caught variable copies it and loses the derived part when the handler\'s type is a base.' },

    { sec: 's7', q: 'A constructor throws halfway through. Which destructors run?',
      opts: ['None at all', 'Those of the members and bases that were already fully constructed, but not the object\'s own destructor', 'The object\'s own destructor as well', 'Those of every member, including ones not yet constructed'], a: 1,
      why: 'The object never finished construction, so its own destructor does not run. Already-built subobjects are destroyed, which is why members should be RAII types.' },

    { sec: 's7', q: 'What is printed?',
      code: String.raw`
try { throw std::invalid_argument("x"); }
catch (const std::exception&)        { std::cout << "A"; }
catch (const std::invalid_argument&) { std::cout << "B"; }`,
      opts: ['A', 'B', 'AB', 'The code does not compile'], a: 0,
      why: 'Handlers are tried in order and the first match wins. `invalid_argument` derives from `exception`, so the first handler catches it and the second can never run. Put the more specific handler first.' },

    { sec: 'guarantees', q: 'Which guarantee does "if the operation throws, the object is exactly as before" describe?',
      opts: ['No-throw guarantee', 'Strong guarantee', 'Basic guarantee', 'No guarantee'], a: 1,
      why: 'Commit or rollback is the strong guarantee. The basic guarantee only promises no leaks and valid invariants; the no-throw guarantee means it never throws.' },

    { sec: 'guarantees', q: 'Why does this give the strong guarantee?',
      code: String.raw`
void Table::replaceAll(const std::vector<Row>& fresh) {
    std::vector<Row> copy(fresh);
    rows_.swap(copy);
}`,
      opts: ['The copy is made first and `swap` cannot throw, so `rows_` is untouched if the copy fails', '`swap` rolls back automatically if it throws', 'Because the parameter is `const`', 'Because `std::vector` is thread-safe'], a: 0,
      why: 'All the work that can fail (the copy) happens on a temporary. The commit is a non-throwing swap, so any exception leaves `*this` unchanged.' },

    { sec: 'guarantees', q: 'What happens when a function marked `noexcept` throws?',
      opts: ['`std::terminate` is called', 'The caller catches it as usual', 'The exception is silently ignored', 'It is undefined behaviour with no defined outcome'], a: 0,
      why: 'A `noexcept` function does not propagate exceptions: leaving it with one calls `std::terminate`. Only promise `noexcept` when it is true.' },

    { sec: 'guarantees', q: 'A class has a move constructor not marked `noexcept` (and a copy constructor). What does `std::vector` do when it grows?',
      opts: ['Moves the elements anyway', 'Copies the elements, to keep the strong guarantee', 'Terminates', 'Fails to compile'], a: 1,
      why: '`vector` uses `std::move_if_noexcept`: it only moves if the move cannot throw, otherwise it copies. Mark moves `noexcept` to avoid silent copies on every reallocation.' },

    { sec: 'guarantees', q: 'Which of these is `noexcept` by default?',
      opts: ['A destructor', 'A user-written move constructor', 'A user-written copy constructor', 'Every function that does not contain `throw`'], a: 0,
      why: 'Destructors are implicitly `noexcept`. Other functions, including your own move constructor, may throw unless you say otherwise.' },

    { sec: 'errors', q: 'Which failure is best reported with a return value (`std::optional` or an error code) rather than an exception?',
      opts: ['A parser rejecting a malformed message, which happens routinely', 'Running out of memory', 'A constructor that cannot acquire its resource', 'A broken class invariant'], a: 0,
      why: 'Expected, frequent failures belong in the return type, where the caller must look at them. Exceptions suit rare failures the local code cannot handle.' },

    { sec: 'errors', q: 'Why are exceptions avoided on a latency-critical hot path?',
      opts: ['They are forbidden since C++20', 'A throw is slow and its latency is unpredictable', 'They leak memory', 'They disable inlining of the whole program'], a: 1,
      why: 'The no-throw path is cheap, but actually throwing takes orders of magnitude longer than a return and varies from call to call. Hot paths report errors with return values.' }
  ]
};
