/* Quiz questions for the 'smartptr' topic. Loaded by 14-smart-pointers-quiz.html. */
CT.quizData.smartptr = {
  id: 'smartptr',
  questions: [
    { sec: 'shared', q: 'What does this print?',
      code: String.raw`
auto a = std::make_shared<int>(1);
auto b = a;
auto c = std::move(a);
std::cout << b.use_count();`,
      opts: ['1', '2', '3', '0'], a: 1,
      why: '`b` copied `a` (count 2). Moving `a` into `c` transfers its ownership without changing the count and leaves `a` null. So `b` and `c` share: 2.' },

    { sec: 'weak', q: 'Two classes each hold a `std::shared_ptr` to the other. What happens when both go out of scope?',
      opts: ['Both are destroyed normally when they go out of scope', 'A reference cycle: counts never reach zero, so both leak', 'A compile error: shared_ptr cycles are rejected', 'Only one is destroyed; the other is kept alive'], a: 1,
      why: 'Each keeps the other\'s count at 1. Break the cycle by making one direction a `std::weak_ptr`.' },

    { sec: 'pitfalls', q: 'What is wrong with this code?',
      code: String.raw`
auto raw = new Widget;
std::shared_ptr<Widget> a(raw);
std::shared_ptr<Widget> b(raw);`,
      opts: ['Both share ownership and the count is 2, as intended', 'Each shared_ptr makes its own control block: Widget is deleted twice', 'It does not compile: a raw pointer cannot be shared between pointers', 'b is left null after the second construction, so it cannot be used'], a: 1,
      why: 'Only copying an existing `shared_ptr` shares a control block. Build a second one from a raw pointer (or from `this`) and you get two independent reference counts. Use `enable_shared_from_this` when an object must hand out a `shared_ptr` to itself.' },

    { sec: 'shared', q: 'Which part of a `std::shared_ptr` is thread-safe?',
      opts: ['The reference count only: the object itself needs its own synchronization', 'The object it points to', 'Only the pointer\'s address', 'Everything, including assigning the same `shared_ptr` variable from two threads'], a: 0,
      why: 'The control block\'s counts are atomic, so separate `shared_ptr` copies can be made and destroyed on different threads. The pointed-to object and a shared variable still race.' },

    { sec: 'weak', q: 'What does `weak.lock()` return after the object has been destroyed?',
      opts: ['A dangling pointer to the freed object', 'An empty shared_ptr (null)', 'It throws std::bad_weak_ptr each time', 'A unique_ptr that owns a fresh object'], a: 1,
      why: '`lock()` returns a `shared_ptr` that is null when the object is gone, so test it before use. (`shared_ptr(weak)` is the version that throws.)' },

    { sec: 'pitfalls', q: 'What happens when `shared_from_this()` is called on an object that no `shared_ptr` owns?',
      opts: ['It creates a new shared_ptr that takes ownership', 'It throws std::bad_weak_ptr', 'It returns a null shared_ptr', 'It leaks the object silently'], a: 1,
      why: '`enable_shared_from_this` only works if the object is already managed by a `shared_ptr`; otherwise it throws `std::bad_weak_ptr` (C++17).' },

    { sec: 'shared', q: 'What does `std::make_shared<T>()` do that `std::shared_ptr<T>(new T)` does not?',
      opts: ['It makes the object itself thread-safe', 'It allocates object and control block together', 'It avoids keeping a reference count at all', 'It creates a unique_ptr first and converts'], a: 1,
      why: '`make_shared` places the object and the control block in a single heap block, which is one allocation instead of two and keeps them close in memory.' },

    { sec: 'shared', q: 'What happens to the reference count when you copy a `shared_ptr`?',
      opts: ['Nothing: copies share the pointer without counting', 'The count is increased, atomically', 'The count is reset to one', 'The old owner loses its share'], a: 1,
      why: 'Each copy is another owner, so the strong count goes up (with an atomic increment, which is why copying a shared_ptr is not free). The object is freed when the count reaches zero.' },

    { sec: 'weak', q: 'Why does a `weak_ptr` break a reference cycle?',
      opts: ['It deletes the object when the cycle is detected', 'It observes without adding to the strong count', 'It makes the shared_ptr unique by itself', 'It copies the object so there is no sharing'], a: 1,
      why: 'A `weak_ptr` does not own: it does not count toward the strong reference count, so the cycle of strong owners that kept both objects alive no longer exists.' },

    { sec: 'weak', q: 'How do you safely use the object a `weak_ptr` refers to?',
      opts: ['Dereference it directly with `*` as usual', 'Call `lock()` and check the result is not empty', 'Call `get()` on it and use the pointer', 'Convert it with a C-style cast to a pointer'], a: 1,
      why: '`lock()` returns a `shared_ptr` that keeps the object alive while you use it, or an empty one if the object is already gone.' }
  ]
};
