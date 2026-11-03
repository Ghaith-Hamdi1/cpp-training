/* Quiz questions for the 'uniqueptr' topic. Loaded by 24-uniqueptr-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.uniqueptr = {
  id: 'uniqueptr',
  questions: [
    { sec: 'move', q: 'Which line fails to compile?',
      code: String.raw`
auto p = std::make_unique<int>(5);   // (1)
auto q = p;                          // (2)
auto r = std::move(p);               // (3)`,
      opts: ['(1)', '(2) because unique_ptr cannot be copied', '(3) because you cannot move a unique_ptr', 'None: all three lines compile'], a: 1,
      why: '`unique_ptr` has exclusive ownership, so its copy constructor is deleted. It is move-only, which is what (3) does.' },

    { sec: 'basics', q: 'Why prefer `std::make_unique<T>(...)` over `std::unique_ptr<T>(new T(...))`?',
      opts: ['It is the only way to create a unique_ptr', 'No naked new, shorter, and the type is written once', 'It allocates the object on the stack for speed', 'It makes the pointer shareable like a shared_ptr'], a: 1,
      why: 'It avoids raw `new`, names the type only once, and before C++17 also prevented a leak when another argument in the same call threw. (`make_shared` additionally saves an allocation.)' },

    { sec: 'pass', q: 'A function only needs to read a `Widget`. What should its parameter be?',
      opts: ['`std::unique_ptr<Widget>` by value', '`const Widget&`', '`std::shared_ptr<Widget>` by value', '`Widget*&`'], a: 1,
      why: 'A function that merely uses an object should not care how it is owned: take a reference (or a raw pointer if it may be null).' },

    { sec: 'pass', q: 'Which parameter type says "I take over ownership of this object"?',
      opts: ['Widget* by value, because a raw pointer owns what it points to', 'const Widget&, which keeps the object alive for the call', 'std::unique_ptr<Widget> by value', 'std::weak_ptr<Widget> by value, which keeps the object alive'], a: 2,
      why: 'A `unique_ptr` by value can only be passed with `std::move`, so the transfer is visible at the call site.' },

    { sec: 'details', q: 'With the default deleter, how does `sizeof(std::unique_ptr<int>)` compare with `sizeof(int*)`?',
      opts: ['They are the same: no overhead', 'The `unique_ptr` is twice as big', 'It adds a control block', 'It depends on the compiler, always larger'], a: 0,
      why: 'The deleter is part of the type and an empty default deleter takes no space, so a `unique_ptr` is exactly one pointer. A function-pointer deleter would double it.' },

    { sec: 'details', q: 'Which `unique_ptr` member returns the raw pointer AND gives up ownership?',
      opts: ['`get()`', '`release()`', '`reset()`', '`operator*`'], a: 1,
      why: '`release()` hands the pointer to you and stops managing it: you must delete it. `get()` only peeks, and `reset()` destroys the object.' },

    { sec: 'owner', q: 'In a function that only reads a `Widget`, which parameter says "I do not own this"?',
      opts: ['std::unique_ptr<Widget>', 'std::shared_ptr<Widget>', 'const Widget&', 'Widget*&&'], a: 2,
      why: 'A reference (or a raw pointer) means the function only uses the object. A smart pointer parameter would tell the reader that ownership is involved.' },

    { sec: 'basics', q: 'When is the object held by a local `std::unique_ptr` deleted?',
      opts: ['When you call delete on it', 'When the unique_ptr goes out of scope', 'At the end of the program', 'When the next unique_ptr is created'], a: 1,
      why: 'The destructor of the `unique_ptr` deletes the object, so it happens automatically at the end of the scope, even if the function returns early or throws.' },

    { sec: 'move', q: 'After `auto b = std::move(a);` where `a` is a `unique_ptr`, what is `a`?',
      opts: ['Still the owner, b has a copy', 'Null: b is the owner now', 'Dangling: it points at freed memory', 'Undefined: you may not touch it'], a: 1,
      why: 'Moving a `unique_ptr` transfers ownership and leaves the source null. It is valid to test or assign to it.' },

    { sec: 'move', q: 'Why can a `unique_ptr` be stored in a `std::vector` but not copied into it?',
      opts: ['vector never makes copies of its elements', 'push_back can move it in, and moving is allowed', 'vector converts it to a shared_ptr first', 'unique_ptr is copied but the original is deleted'], a: 1,
      why: 'Copying is deleted, but moving is allowed: `v.push_back(std::move(p))` or `v.push_back(std::make_unique<T>())` hands the ownership to the vector.' },

    { sec: 'pass', q: 'Which function signature takes over ownership of a `Widget`?',
      opts: ['void f(Widget& w)', 'void f(const Widget& w)', 'void f(std::unique_ptr<Widget> w)', 'void f(Widget* w)'], a: 2,
      why: 'A `unique_ptr` taken by value means the function becomes the owner; the caller must write `f(std::move(p))`.' },

    { sec: 'pass', q: 'A factory function should return which type to hand sole ownership to the caller?',
      opts: ['Widget*', 'std::unique_ptr<Widget>', 'Widget&', 'std::shared_ptr<Widget>&'], a: 1,
      why: 'Returning a `unique_ptr` by value moves ownership out of the function and says clearly who must free the object. Callers can still convert it to a shared_ptr if they need to.' },

    { sec: 'details', q: 'How can a `unique_ptr<Base>` correctly own a `Derived` object?',
      opts: ['Base needs a virtual destructor', 'Derived needs a copy constructor', 'unique_ptr cannot own derived objects', 'Base must have no virtual functions'], a: 0,
      why: 'The `unique_ptr` deletes through a `Base*`, so `Base` needs a virtual destructor, exactly as with any `delete` through a base pointer.' },

    { sec: 'details', q: 'What does `p.release()` do?',
      opts: ['Destroys the object it points to right now', 'Gives up ownership and returns the raw pointer', 'Makes a copy of the object it points to', 'Sets the pointer to point at a new object'], a: 1,
      why: '`release()` only gives up ownership; it does not delete anything. Forgetting to delete the returned pointer leaks the object.' },

    { sec: 'mistakes', q: 'What is wrong with `Widget* raw = new Widget; std::unique_ptr<Widget> a(raw), b(raw);`?',
      opts: ['Nothing: unique_ptr detects the sharing', 'Both own the Widget, so it is deleted twice', 'It does not compile', 'b becomes empty because a came first'], a: 1,
      why: 'Neither `unique_ptr` knows about the other, so each deletes the object when it is destroyed: a double delete, which is undefined behavior.' },

    { sec: 'mistakes', q: 'Why is `delete p.get();` a bug when `p` is a `unique_ptr`?',
      opts: ['get() returns a null pointer when asked', 'The unique_ptr deletes the object a second time', 'get() throws an exception in that case', 'It deletes the unique_ptr and not the object'], a: 1,
      why: '`get()` only lends you the address; `p` still owns the object and will delete it when it is destroyed, so the object is deleted twice.' }
  ]
};
