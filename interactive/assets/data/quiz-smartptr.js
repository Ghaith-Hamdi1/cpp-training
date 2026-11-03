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

    { sec: 'pitfalls', q: 'What happens when `shared_from_this()` is called on an object that no `shared_ptr` owns?',
      opts: ['It creates a new shared_ptr that takes ownership', 'It throws std::bad_weak_ptr', 'It returns a null shared_ptr', 'It leaks the object silently'], a: 1,
      why: '`enable_shared_from_this` only works if the object is already managed by a `shared_ptr`; otherwise it throws `std::bad_weak_ptr` (C++17).' },

    { sec: 'shared', q: 'What does `std::make_shared<T>()` do that `std::shared_ptr<T>(new T)` does not?',
      opts: ['It makes the object itself thread-safe', 'It allocates object and control block together', 'It avoids keeping a reference count at all', 'It creates a unique_ptr first and converts'], a: 1,
      why: '`make_shared` places the object and the control block in a single heap block, which is one allocation instead of two and keeps them close in memory.' },

    { sec: 'shared', q: 'What happens to the reference count when you copy a `shared_ptr`?',
      opts: ['Nothing: copies share the pointer without counting', 'The count is increased, atomically', 'The count is reset to one', 'The old owner loses its share'], a: 1,
      why: 'Each copy is another owner, so the strong count goes up (with an atomic increment, which is why copying a shared_ptr is not free). The object is freed when the count reaches zero.' },

    { sec: 'when', q: 'Several parts of a program each need an object to stay alive, and none knows which finishes last. Which pointer fits?',
      opts: ['`std::shared_ptr`, which counts the owners', '`std::unique_ptr`, which has one owner', 'A raw pointer that every part deletes', '`std::weak_ptr`, which owns nothing'], a: 0,
      why: 'Shared ownership is what shared_ptr is for: the last owner to leave deletes the object.' },

    { sec: 'when', q: 'What is the safest default when you are unsure about ownership?',
      opts: ['`unique_ptr`', '`shared_ptr`, to be safe', 'A raw pointer', 'A global variable'], a: 0,
      why: 'A unique_ptr states one owner clearly and costs nothing. Moving to shared ownership later is easy.' },

    { sec: 'make', q: 'What does `std::make_shared<Widget>()` do that `std::shared_ptr<Widget>(new Widget)` does not?',
      opts: ['Allocates the object and its control block together', 'Avoids the control block entirely', 'Makes the pointer thread safe', 'Calls the destructor earlier'], a: 0,
      why: 'make_shared uses one allocation; the other form allocates the object and then the control block.' },

    { sec: 'make', q: 'What does copying a `shared_ptr` cost?',
      opts: ['An atomic increment of the reference count', 'A copy of the whole object', 'A heap allocation', 'Nothing at all'], a: 0,
      why: 'Only the count changes; the object is shared. The increment is atomic, so it is not free.' },

    { sec: 'threads', q: 'Two threads each hold their own copy of a `shared_ptr` to one object and call a mutating member. What is true?',
      opts: ['The counts are safe but the object needs its own synchronization', 'Everything is safe because shared_ptr is thread safe', 'It is a race on the counts', 'The second thread\'s copy is a deep copy'], a: 0,
      why: 'The control block is atomic; the object is not protected.' },

    { sec: 'threads', q: 'Two threads assign to the same `shared_ptr` variable at the same time. What happens?',
      opts: ['A data race', 'The last assignment wins safely', 'The counts become inconsistent but the object is fine', 'It is safe because assignment is atomic'], a: 0,
      why: 'Copies of one pointer are independent, but the variable itself is an ordinary object.' }
  ]
};
