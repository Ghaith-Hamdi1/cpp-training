/* Quiz questions for the 'smartptr' topic. Loaded by 14-smart-pointers-quiz.html. */
CT.quizData.smartptr = {
  id: 'smartptr',
  questions: [
    { sec: 'unique', q: 'Which line fails to compile?',
      code: String.raw`
auto p = std::make_unique<int>(5);   // (1)
auto q = p;                          // (2)
auto r = std::move(p);               // (3)`,
      opts: ['(1)', '(2) because unique_ptr cannot be copied', '(3) because you cannot move a unique_ptr', 'None'], a: 1,
      why: '`unique_ptr` has exclusive ownership, so its copy constructor is deleted. It is move-only, which is what (3) does.' },

    { sec: 'shared', q: 'What does this print?',
      code: String.raw`
auto a = std::make_shared<int>(1);
auto b = a;
auto c = std::move(a);
std::cout << b.use_count();`,
      opts: ['1', '2', '3', '0'], a: 1,
      why: '`b` copied `a` (count 2). Moving `a` into `c` transfers its ownership without changing the count and leaves `a` null. So `b` and `c` share: 2.' },

    { sec: 'weak', q: 'Two classes each hold a `std::shared_ptr` to the other. What happens when both go out of scope?',
      opts: ['Both are destroyed normally', 'A reference cycle: counts never reach zero, so both leak', 'Compile error', 'Only one is destroyed'], a: 1,
      why: 'Each keeps the other\'s count at 1. Break the cycle by making one direction a `std::weak_ptr`.' },

    { sec: 'unique', q: 'Why prefer `std::make_unique<T>(...)` over `std::unique_ptr<T>(new T(...))`?',
      opts: ['It is the only way to create a unique_ptr', 'No naked `new`, shorter, and the type is written once', 'It allocates on the stack', 'It makes the pointer shareable'], a: 1,
      why: 'It avoids raw `new`, names the type only once, and before C++17 also prevented a leak when another argument in the same call threw. (`make_shared` additionally saves an allocation.)' },

    { sec: 'pitfalls', q: 'What is wrong with this code?',
      code: String.raw`
auto raw = new Widget;
std::shared_ptr<Widget> a(raw);
std::shared_ptr<Widget> b(raw);`,
      opts: ['Nothing: both share ownership and the count is 2', 'Each shared_ptr creates its own control block, so the Widget is deleted twice (undefined behavior)', 'It does not compile', 'b is left null'], a: 1,
      why: 'Only copying an existing `shared_ptr` shares a control block. Build a second one from a raw pointer (or from `this`) and you get two independent reference counts. Use `enable_shared_from_this` when an object must hand out a `shared_ptr` to itself.' },

    { sec: 'ownership', q: 'A function only needs to read a `Widget`. What should its parameter be?',
      opts: ['`std::unique_ptr<Widget>` by value', '`const Widget&`', '`std::shared_ptr<Widget>` by value', '`Widget*&`'], a: 1,
      why: 'A function that merely uses an object should not care how it is owned: take a reference (or a raw pointer if it may be null).' },

    { sec: 'ownership', q: 'Which parameter type says "I take over ownership of this object"?',
      opts: ['`Widget*`', '`const Widget&`', '`std::unique_ptr<Widget>` by value', '`std::weak_ptr<Widget>`'], a: 2,
      why: 'A `unique_ptr` by value can only be passed with `std::move`, so the transfer is visible at the call site.' },

    { sec: 'unique', q: 'With the default deleter, how does `sizeof(std::unique_ptr<int>)` compare with `sizeof(int*)`?',
      opts: ['They are the same: no overhead', 'The `unique_ptr` is twice as big', 'It adds a control block', 'It depends on the compiler, always larger'], a: 0,
      why: 'The deleter is part of the type and an empty default deleter takes no space, so a `unique_ptr` is exactly one pointer. A function-pointer deleter would double it.' },

    { sec: 'unique', q: 'Which `unique_ptr` member returns the raw pointer AND gives up ownership?',
      opts: ['`get()`', '`release()`', '`reset()`', '`operator*`'], a: 1,
      why: '`release()` hands the pointer to you and stops managing it: you must delete it. `get()` only peeks, and `reset()` destroys the object.' },

    { sec: 'shared', q: 'Which part of a `std::shared_ptr` is thread-safe?',
      opts: ['The reference count only: the object itself needs its own synchronization', 'The object it points to', 'Nothing', 'Everything, including assigning the same `shared_ptr` variable from two threads'], a: 0,
      why: 'The control block\'s counts are atomic, so separate `shared_ptr` copies can be made and destroyed on different threads. The pointed-to object and a shared variable still race.' },

    { sec: 'weak', q: 'What does `weak.lock()` return after the object has been destroyed?',
      opts: ['A dangling pointer', 'An empty `shared_ptr` (null)', 'It throws `bad_weak_ptr`', 'A `unique_ptr`'], a: 1,
      why: '`lock()` returns a `shared_ptr` that is null when the object is gone, so test it before use. (`shared_ptr(weak)` is the version that throws.)' },

    { sec: 'pitfalls', q: 'What happens when `shared_from_this()` is called on an object that no `shared_ptr` owns?',
      opts: ['It creates a new `shared_ptr`', 'It throws `std::bad_weak_ptr`', 'It returns null', 'It leaks the object'], a: 1,
      why: '`enable_shared_from_this` only works if the object is already managed by a `shared_ptr`; otherwise it throws `std::bad_weak_ptr` (C++17).' }
  ]
};
