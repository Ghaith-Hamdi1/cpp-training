/* Quiz questions for the 'weakptr' topic. Loaded by 32-weakptr-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.weakptr = {
  id: 'weakptr',
  questions: [
    { sec: 'weak', q: 'Two classes each hold a `std::shared_ptr` to the other. What happens when both go out of scope?',
      opts: ['Both are destroyed normally when they go out of scope', 'A reference cycle: counts never reach zero, so both leak', 'A compile error: shared_ptr cycles are rejected', 'Only one is destroyed; the other is kept alive'], a: 1,
      why: 'Each keeps the other\'s count at 1. Break the cycle by making one direction a `std::weak_ptr`.' },

    { sec: 'weak', q: 'What does `weak.lock()` return after the object has been destroyed?',
      opts: ['A dangling pointer to the freed object', 'An empty shared_ptr (null)', 'It throws std::bad_weak_ptr each time', 'A unique_ptr that owns a fresh object'], a: 1,
      why: '`lock()` returns a `shared_ptr` that is null when the object is gone, so test it before use. (`shared_ptr(weak)` is the version that throws.)' },

    { sec: 'weak', q: 'Why does a `weak_ptr` break a reference cycle?',
      opts: ['It deletes the object when the cycle is detected', 'It observes without adding to the strong count', 'It makes the shared_ptr unique by itself', 'It copies the object so there is no sharing'], a: 1,
      why: 'A `weak_ptr` does not own: it does not count toward the strong reference count, so the cycle of strong owners that kept both objects alive no longer exists.' },

    { sec: 'weak', q: 'How do you safely use the object a `weak_ptr` refers to?',
      opts: ['Dereference it directly with `*` as usual', 'Call `lock()` and check the result is not empty', 'Call `get()` on it and use the pointer', 'Convert it with a C-style cast to a pointer'], a: 1,
      why: '`lock()` returns a `shared_ptr` that keeps the object alive while you use it, or an empty one if the object is already gone.' },

    { sec: 'cycle', q: 'After this scope ends, how many `Node`s are destroyed? `auto a = make_shared<Node>(); auto b = make_shared<Node>(); a->next = b; b->next = a;`',
      opts: ['None: the cycle keeps both counts at 1', 'Both of them, one after the other', 'Only a, because it was created first', 'Only b, because it was created last'], a: 0,
      why: 'Each node is owned by the other\'s next pointer, so neither count reaches zero.' },

    { sec: 'cycle', q: 'Which of these is the usual symptom of a `shared_ptr` cycle?',
      opts: ['A leak', 'A crash with a segmentation fault', 'A compile error', 'A double delete'], a: 0,
      why: 'A cycle leaks silently. A leak checker or a missing destructor message reveals it.' },

    { sec: 'weak', q: 'What does `w.lock()` return when the object is gone?',
      opts: ['An empty `shared_ptr`', 'A dangling `shared_ptr`', 'It throws `bad_weak_ptr`', 'A raw null pointer of type T*'], a: 0,
      why: 'lock() never throws and never dangles: it returns an owner or an empty pointer. (Constructing a shared_ptr from an expired weak_ptr throws.)' },

    { sec: 'weak', q: 'Why is `if (!w.expired()) w.lock()->use();` a bug?',
      opts: ['The owner can vanish between the two calls', 'expired() is far too slow for this check', 'lock() cannot be called after expired() was used', 'It leaks the object that lock() returns'], a: 0,
      why: 'Call lock() once, test the result and use that owner.' },

    { sec: 'patterns', q: 'In a parent that owns its children, which link should be a `weak_ptr`?',
      opts: ['The child\'s pointer back to its parent', 'The parent\'s pointers to its children', 'Both of the links between them', 'Neither of the links between them'], a: 0,
      why: 'The owning direction stays strong; the back link observes only, which avoids the cycle.' },

    { sec: 'patterns', q: 'A cache stores `weak_ptr`s to its entries. What does that achieve?',
      opts: ['Entries in use are shared and unused ones can be freed', 'Entries are never freed while the cache exists', 'Entries are copied again on every single lookup', 'Entries automatically become thread safe objects'], a: 0,
      why: 'The cache does not own the entries, so it never keeps an unused one alive.' },

    { sec: 'cost', q: 'A `weak_ptr` is the last reference to an object made with `make_shared`. What is still allocated?',
      opts: ['The memory block holding the control block', 'Nothing at all, because the object was destroyed', 'A second copy of the object that was destroyed', 'Only the weak_ptr variable itself on the stack'], a: 0,
      why: 'The destructor ran, but object and control block share one allocation that is freed with the last weak reference.' },

    { sec: 'cost', q: 'What does a `weak_ptr` keep alive?',
      opts: ['Only the control block', 'The object it points to', 'All of the shared owners', 'Nothing at all, not even the counts'], a: 0,
      why: 'It must keep the counts so expired() can answer; it never keeps the object.' }
  ]
};
