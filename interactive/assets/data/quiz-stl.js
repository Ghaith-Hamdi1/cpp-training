/* Quiz questions for the 'stl' topic. Loaded by 04-stl-quiz.html. */
CT.quizData.stl = {
  id: 'stl',
  questions: [
    { sec: 's1', q: 'Without special requirements, which container should you reach for first?',
      opts: ['std::list', 'std::vector', 'std::map', 'std::deque'], a: 1,
      why: 'Contiguous storage gives the best cache behaviour, so `vector` is the default for sequences. Switch only when measurement or a real requirement says otherwise.' },

    { sec: 's2', q: 'What is the cost of `push_back` on a `std::vector`?',
      opts: ['Always O(1), because it simply appends at the end of the array', 'Always O(n), since every push_back may copy the whole vector', 'Amortised O(1): occasionally O(n) when it reallocates', 'O(log n), as the vector keeps its elements balanced like a tree'], a: 2,
      why: 'Most calls just write into spare capacity. When capacity runs out the vector grows geometrically and copies/moves all elements, but that is rare enough that the average stays constant.' },

    { sec: 's2', q: 'What is wrong with this code?',
      code: String.raw`
std::vector<int> v;
v.reserve(10);
v[5] = 1;`,
      opts: ['Capacity 10 means index 5 already exists in the vector', 'Undefined behavior: reserve changes capacity, not size', 'It throws std::out_of_range when index 5 is accessed', 'It does not compile, because v is empty at that point'], a: 1,
      why: '`reserve` allocates space only. `resize(10)` would create the elements. `operator[]` does no bounds check, so this is silent undefined behavior (`at()` would throw).' },

    { sec: 's2', q: 'A `std::vector` reallocates during `push_back`. What happens to existing iterators, pointers and references?',
      opts: ['They stay valid', 'Just end() is invalidated', 'All of them are invalidated', 'Those after the insertion point'], a: 2,
      why: 'The elements moved to a new buffer, so anything pointing into the old one dangles. Reserve up front or avoid holding pointers across growth.' },

    { sec: 'pitfalls', q: 'What is the bug in this loop?',
      code: String.raw`
std::vector<int> v;   // empty
for (std::size_t i = 0; i < v.size() - 1; ++i) { /* ... */ }`,
      opts: ['The loop is correct and runs properly for all vectors', 'v.size() - 1 wraps to a huge value because size() is unsigned', 'The loop does not run, because the condition is false', 'i should be declared as a signed int, but the loop still works'], a: 1,
      why: 'Unsigned subtraction below zero wraps. Write `i + 1 < v.size()` or check `empty()` first.' },

    { sec: 's2', q: 'What is the difference between `push_back` and `emplace_back`?',
      opts: ['emplace_back inserts the new element at the front instead of the back', 'emplace_back constructs the element in place, avoiding a temporary', 'push_back is faster than emplace_back for most element types', 'They are identical for every type, including types with expensive constructors'], a: 1,
      why: '`push_back(obj)` copies or moves an existing object. `emplace_back(args...)` builds it directly inside the container. For trivial types the two compile to the same thing.' },

    { sec: 'pitfalls', q: 'What does `auto x = v[0];` do when `v` is a `std::vector<BigObject>`?',
      opts: ['Binds a reference to the element', 'Makes a copy of the element', 'Moves the element out of the vector', 'Does not compile'], a: 1,
      why: '`auto` deduces a value type, dropping references and const. Use `const auto& x = v[0];` to avoid the copy.' },

    { sec: 's3', q: 'You need to add and remove at both ends of a sequence and still index into it. Which container fits best?',
      opts: ['std::vector', 'std::list', 'std::deque', 'std::forward_list'], a: 2,
      why: '`deque` gives O(1) push/pop at both ends plus random access. A vector is O(n) at the front; a list has no indexing.' },

    { sec: 's5', q: 'Why does a `std::vector` often beat a `std::list` even for insertions in the middle?',
      opts: ['Lists are slower to insert into than other containers are', 'Contiguous memory is cache-friendly; a list allocates a node per element', 'Vectors do not need to move elements when inserting in the middle', 'Lists cannot insert elements in the middle of the sequence'], a: 1,
      why: 'Big-O hides constants. A vector\'s memmove-style shift is fast on modern CPUs, while pointer-chasing through scattered list nodes causes cache misses. Always measure.' },

    { sec: 's2', q: 'What is the difference between `std::vector<int> a(3, 7);` and `std::vector<int> b{3, 7};`?',
      opts: ['Both hold three elements equal to 7, written two ways', 'a holds {7, 7, 7}; b holds {3, 7}: braces prefer initializer_list', 'a does not compile, since 3 is not a valid size argument', 'b holds three elements, the same as a, written differently'], a: 1,
      why: 'Parentheses call the (count, value) constructor. Braces prefer a constructor taking std::initializer_list whenever one can match, so the two numbers become the elements.' },

    { sec: 's2', q: 'What is the difference between `size()` and `capacity()` of a vector?',
      opts: ['size is the elements in use; capacity is the slots allocated', 'size is in bytes; capacity is in elements', 'They are always equal after reserve', 'capacity counts only the elements that were erased'], a: 0,
      why: 'A vector keeps spare room so push_back is usually cheap. reserve changes capacity, resize changes size.' },

    { sec: 'adaptors', q: 'Which adaptor gives first-in first-out order?',
      opts: ['`std::queue`, which pops from the front', '`std::stack`, which pops the newest', '`std::priority_queue`, which pops the oldest', '`std::vector`, which pops the front cheaply'], a: 0,
      why: 'stack is last-in first-out; priority_queue pops the largest element; queue is FIFO.' },

    { sec: 's3', q: 'Which container has O(1) insertion at both ends and still supports `[i]`?',
      opts: ['`std::deque`, which stores blocks of arrays', '`std::vector`, which is contiguous', '`std::list`, which stores nodes', '`std::forward_list`, which links singly'], a: 0,
      why: 'A deque is a chain of blocks with an index, so both ends are cheap and indexing still works.' }
  ]
};
