/* Quiz questions for the 'iterators' topic. Loaded by 28-iterators-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.iterators = {
  id: 'iterators',
  questions: [
    { sec: 'invalidation', q: 'Which loop erases the even numbers correctly?',
      code: String.raw`
std::vector<int> v{1, 2, 3, 4};`,
      opts: ['`for (auto it = v.begin(); it != v.end(); ++it) if (*it % 2 == 0) v.erase(it);`', '`for (auto it = v.begin(); it != v.end(); ) { if (*it % 2 == 0) it = v.erase(it); else ++it; }`', '`for (int x : v) if (x % 2 == 0) v.erase(&x);`', '`v.erase(v.begin(), v.end(), 2);`'], a: 1,
      why: '`erase` invalidates the iterator and returns the next valid one. Using the return value (and not incrementing in that case) is the correct pattern. C++20 offers `std::erase_if(v, pred)`.' },

    { sec: 's6', q: 'Why does `std::sort(myList.begin(), myList.end())` fail to compile for a `std::list`?',
      opts: ['Lists cannot hold int elements, just class types such as strings', 'std::sort needs random-access iterators; list has only bidirectional ones', 'std::sort works just on built-in arrays and std::array', 'The list would have to be declared const before sorting'], a: 1,
      why: '`sort` jumps around by index arithmetic. Use the member function `myList.sort()` instead.' },

    { sec: 's6', q: 'What does `end()` return for a container?',
      opts: ['An iterator to the last element of the container', 'An iterator one past the last element, never dereferenced', 'A null pointer that marks the end of the container', 'An iterator to the first element of the container'], a: 1,
      why: 'Ranges are half-open `[begin, end)`. `end()` is a sentinel position; dereferencing it is undefined behavior, and an empty container has `begin() == end()`.' },

    { sec: 'adaptors', q: 'Why does `std::copy(src.begin(), src.end(), out.begin())` with an empty `out` break, and what fixes it?',
      opts: ['It is fine: copy grows the destination automatically as it goes', 'It writes past the end; std::back_inserter(out) makes writes push_back', 'It needs std::move to work on empty destination containers', 'It needs just a reserve call on out before the copy starts'], a: 1,
      why: 'Algorithms assign through the output iterator and do not grow the destination. An inserter turns assignments into insertions.' },

    { sec: 'views', q: 'Which function signature lets the caller pass a `std::vector<int>`, a C array `int[3]` or a slice of either, without a copy?',
      opts: ['`long sum(const std::vector<int>& xs)`', '`long sum(std::span<const int> xs)`', '`long sum(int* xs)`', '`long sum(std::vector<int> xs)`'], a: 1,
      why: 'A span is a pointer plus a length over any contiguous elements. It accepts a vector, an array, a `std::array` or `subspan` of them, remembers its size, and is passed by value (two words).' },

    { sec: 'views', q: 'What is wrong here?',
      code: String.raw`
std::vector<int> v{1, 2, 3};
std::span<int> s = v;
v.push_back(4);
std::cout << s[0];`,
      opts: ['The span follows the vector automatically when it grows, so it stays valid', 'push_back may reallocate, leaving s pointing at freed memory', 'A span cannot be created from a std::vector, only from arrays', 's[0] is bounds-checked and throws an exception on a bad index'], a: 1,
      why: 'A view does not own its data. `push_back` can move the elements to a new buffer, leaving the span dangling. Take views for parameters and short-lived use, and re-create them after modifying the container.' },

    { sec: 's6', q: 'What does `v.end()` give for a non-empty vector?',
      opts: ['An iterator one past the last element, never dereferenced', 'An iterator to the last element, which you may read and write', 'A null pointer that marks the end of the container', 'An iterator to a hidden sentinel element stored in the vector'], a: 0,
      why: 'end() marks the position after the last element. The range is [begin, end), so end() itself is never dereferenced.' },

    { sec: 's6', q: 'Which iterator category lets you write `it + 3`?',
      opts: ['Random access, as for vector and deque', 'Forward, as for forward_list and unordered containers', 'Bidirectional, as for list, map and set containers', 'Input, as for the iterators that read from streams'], a: 0,
      why: 'Only random-access iterators support jumps and subtraction. A list has bidirectional iterators: ++ and --, no +n.' },

    { sec: 's6', q: 'Why is `for (auto it = c.begin(); it != c.end(); ++it)` preferred to `it < c.end()`?',
      opts: ['`!=` works for every container; `<` does not', '`<` is slower than `!=` on every container type', '`<` is not allowed for pointers into an array', '`!=` also checks the bounds of the container for you'], a: 0,
      why: 'A list or map iterator has no operator<. The != test is the one every iterator category supports.' },

    { sec: 'adaptors', q: 'What does `std::back_inserter(out)` give you?',
      opts: ['An output iterator whose assignment calls push_back', 'A reverse iterator that walks the container backwards', 'An iterator that moves its elements instead of copying', 'A pointer to the last element currently stored in out'], a: 0,
      why: 'Each assignment through it becomes a push_back, so the target grows as the algorithm writes.' },

    { sec: 'invalidation', q: 'A `vector` has size 3 and capacity 3. What happens to `int* p = &v[0];` after `v.push_back(4)`?',
      opts: ['It may dangle, because the vector reallocated', 'It stays valid because the element did not move', 'It points to the new first element', 'It becomes null'], a: 0,
      why: 'A full vector allocates a bigger block, moves the elements and frees the old one. Pointers, references and iterators into it are invalid.' },

    { sec: 'views', q: 'What is the main risk of `std::string_view`?',
      opts: ['It does not own the text, so it can dangle', 'It copies the whole text on every function call', 'It cannot be passed to functions as an argument', 'It always allocates its characters on the heap'], a: 0,
      why: 'A view is a pointer and a length. The owner must outlive it.' }
  ]
};
