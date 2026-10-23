/* Quiz questions for the 'stl' topic. Loaded by 04-stl-quiz.html. */
CT.quizData.stl = {
  id: 'stl',
  questions: [
    { sec: 's1', q: 'Without special requirements, which container should you reach for first?',
      opts: ['std::list', 'std::vector', 'std::map', 'std::deque'], a: 1,
      why: 'Contiguous storage gives the best cache behaviour, so `vector` is the default for sequences. Switch only when measurement or a real requirement says otherwise.' },

    { sec: 's2', q: 'What is the cost of `push_back` on a `std::vector`?',
      opts: ['Always O(1)', 'Always O(n)', 'Amortised O(1): occasionally O(n) when it must reallocate', 'O(log n)'], a: 2,
      why: 'Most calls just write into spare capacity. When capacity runs out the vector grows geometrically and copies/moves all elements, but that is rare enough that the average stays constant.' },

    { sec: 's2', q: 'What is wrong with this code?',
      code: String.raw`
std::vector<int> v;
v.reserve(10);
v[5] = 1;`,
      opts: ['Nothing: capacity 10 means index 5 exists', 'Undefined behavior: reserve changes capacity, not size, so element 5 does not exist', 'It throws std::out_of_range', 'It does not compile'], a: 1,
      why: '`reserve` allocates space only. `resize(10)` would create the elements. `operator[]` does no bounds check, so this is silent undefined behavior (`at()` would throw).' },

    { sec: 's4', q: 'What does this print?',
      code: String.raw`
std::map<std::string, int> m;
if (m["x"] == 0) { }
std::cout << m.size();`,
      opts: ['0', '1', 'It throws', 'Undefined behavior'], a: 1,
      why: '`operator[]` inserts a default-constructed value when the key is missing. Use `find`, `count` or `contains` to test for a key without inserting.' },

    { sec: 's7', q: 'What does this print?',
      code: String.raw`
std::vector<int> v{1, 2, 3, 4, 5};
std::remove(v.begin(), v.end(), 3);
std::cout << v.size();`,
      opts: ['4', '5', '3', '0'], a: 1,
      why: 'Algorithms cannot change a container\'s size. `std::remove` only shifts elements and returns the new logical end. Combine it with `erase` (the erase-remove idiom) or use C++20 `std::erase`.' },

    { sec: 's2', q: 'A `std::vector` reallocates during `push_back`. What happens to existing iterators, pointers and references?',
      opts: ['They stay valid', 'Only end() is invalidated', 'All of them are invalidated', 'Only those after the insertion point'], a: 2,
      why: 'The elements moved to a new buffer, so anything pointing into the old one dangles. Reserve up front or avoid holding pointers across growth.' },

    { sec: 's6', q: 'Which loop erases the even numbers correctly?',
      code: String.raw`
std::vector<int> v{1, 2, 3, 4};`,
      opts: ['`for (auto it = v.begin(); it != v.end(); ++it) if (*it % 2 == 0) v.erase(it);`', '`for (auto it = v.begin(); it != v.end(); ) { if (*it % 2 == 0) it = v.erase(it); else ++it; }`', '`for (int x : v) if (x % 2 == 0) v.erase(&x);`', '`v.erase(v.begin(), v.end(), 2);`'], a: 1,
      why: '`erase` invalidates the iterator and returns the next valid one. Using the return value (and not incrementing in that case) is the correct pattern. C++20 offers `std::erase_if(v, pred)`.' },

    { sec: 's4', q: 'How does iteration order differ between `std::map` and `std::unordered_map`?',
      opts: ['Both are sorted', 'map is sorted by key; unordered_map has no specified order', 'unordered_map is sorted, map is insertion order', 'Both preserve insertion order'], a: 1,
      why: '`map` is a balanced tree, so in-order traversal is sorted. `unordered_map` is a hash table whose order is unspecified and can change after a rehash.' },

    { sec: 's6', q: 'Why does `std::sort(myList.begin(), myList.end())` fail to compile for a `std::list`?',
      opts: ['Lists cannot contain ints', 'std::sort requires random-access iterators and a list has only bidirectional ones', 'std::sort is only for arrays', 'The list must be const'], a: 1,
      why: '`sort` jumps around by index arithmetic. Use the member function `myList.sort()` instead.' },

    { sec: 's4', q: 'What does `std::priority_queue<int> q;` return from `q.top()` by default?',
      opts: ['The smallest element', 'The largest element', 'The first inserted element', 'The last inserted element'], a: 1,
      why: 'It is a max-heap by default (it uses `std::less`). For a min-heap use `std::priority_queue<int, std::vector<int>, std::greater<int>>`.' },

    { sec: 's9', q: 'What is the bug in this loop?',
      code: String.raw`
std::vector<int> v;   // empty
for (std::size_t i = 0; i < v.size() - 1; ++i) { /* ... */ }`,
      opts: ['None', '`v.size() - 1` wraps around to a huge number because size() is unsigned, so the loop runs far out of bounds', 'The loop never runs', 'i should be a signed int'], a: 1,
      why: 'Unsigned subtraction below zero wraps. Write `i + 1 < v.size()` or check `empty()` first.' },

    { sec: 's7', q: 'Why must a sort comparator use `<` and not `<=`?',
      opts: ['`<=` is slower', 'The comparator must be a strict weak ordering: returning true for equal elements is undefined behavior and can crash std::sort', 'It makes the sort unstable', 'It is only a style rule'], a: 1,
      why: 'Algorithms assume `comp(a, a)` is false. Violating that can cause out-of-bounds reads in `std::sort` and corrupt ordered containers.' },

    { sec: 's2', q: 'What is the difference between `push_back` and `emplace_back`?',
      opts: ['emplace_back inserts at the front', 'emplace_back constructs the element in place from the constructor arguments, avoiding a temporary', 'push_back is faster for all types', 'They are identical for every type'], a: 1,
      why: '`push_back(obj)` copies or moves an existing object. `emplace_back(args...)` builds it directly inside the container. For trivial types the two compile to the same thing.' },

    { sec: 's7', q: 'What must be true before calling `std::lower_bound` or `std::binary_search` on a range?',
      opts: ['It must contain unique elements', 'It must be sorted according to the same ordering', 'It must be a vector', 'It must be non-empty'], a: 1,
      why: 'Binary search only makes sense on sorted data. On unsorted data the result is meaningless (and the precondition violation is undefined behavior).' },

    { sec: 's4', q: 'What is the worst-case cost of a lookup in `std::unordered_map`?',
      opts: ['O(1)', 'O(log n)', 'O(n), when many keys collide into the same bucket', 'O(n log n)'], a: 2,
      why: 'Average O(1) relies on a good hash function and low load factor. Heavy collisions degrade a bucket toward a linear scan.' },

    { sec: 's6', q: 'What does `end()` return for a container?',
      opts: ['An iterator to the last element', 'An iterator one past the last element, which must not be dereferenced', 'nullptr', 'An iterator to the first element'], a: 1,
      why: 'Ranges are half-open `[begin, end)`. `end()` is a sentinel position; dereferencing it is undefined behavior, and an empty container has `begin() == end()`.' },

    { sec: 's4', q: 'In the code below, what is `counts["apple"]` after the loop?',
      code: String.raw`
std::unordered_map<std::string, int> counts;
for (const auto& w : {"apple", "pear", "apple"})
    counts[w]++;`,
      opts: ['1', '2', '0', 'The code does not compile'], a: 1,
      why: 'On the first "apple", `operator[]` inserts a value-initialised 0 which is then incremented. The second "apple" increments it again: 2.' },

    { sec: 's9', q: 'What does `auto x = v[0];` do when `v` is a `std::vector<BigObject>`?',
      opts: ['Binds a reference to the element', 'Makes a copy of the element', 'Moves the element out of the vector', 'Does not compile'], a: 1,
      why: '`auto` deduces a value type, dropping references and const. Use `const auto& x = v[0];` to avoid the copy.' },

    { sec: 's3', q: 'You need to add and remove at both ends of a sequence and still index into it. Which container fits best?',
      opts: ['std::vector', 'std::list', 'std::deque', 'std::forward_list'], a: 2,
      why: '`deque` gives O(1) push/pop at both ends plus random access. A vector is O(n) at the front; a list has no indexing.' },

    { sec: 's5', q: 'Why does a `std::vector` often beat a `std::list` even for insertions in the middle?',
      opts: ['Lists are always slower to insert', 'Contiguous memory is cache-friendly and a list allocates a node per element, so the O(n) shift of a vector is often cheaper in practice', 'Vectors never move elements', 'Lists cannot insert in the middle'], a: 1,
      why: 'Big-O hides constants. A vector\'s memmove-style shift is fast on modern CPUs, while pointer-chasing through scattered list nodes causes cache misses. Always measure.' },

    { sec: 's2', q: 'What is the difference between `std::vector<int> a(3, 7);` and `std::vector<int> b{3, 7};`?',
      opts: ['Both hold three elements equal to 7', '`a` holds {7, 7, 7}; `b` holds {3, 7}, because the initializer_list constructor wins for braces', '`a` does not compile', '`b` holds three elements'], a: 1,
      why: 'Parentheses call the (count, value) constructor. Braces prefer a constructor taking std::initializer_list whenever one can match, so the two numbers become the elements.' },

    { sec: 'keys', q: 'You use a struct as the key of `std::unordered_map`. What must you provide?',
      opts: ['`operator<` only', '`operator==` and a hash function (a hash functor or a `std::hash` specialisation)', '`operator()` and `operator[]`', 'Nothing: the compiler generates both'], a: 1,
      why: 'Hashing finds the bucket and equality finds the key inside it. Equal keys must produce equal hashes.' },

    { sec: 'keys', q: 'Why is `operator<=` not a valid comparator for `std::map`?',
      opts: ['It is slower', 'It breaks the strict weak ordering rules (an element is not less than itself), which is undefined behaviour', 'It does not compile', 'It reverses the order'], a: 1,
      why: 'Ordered containers need `comp(a, a) == false`. With `<=` equal keys compare as "less", so lookups and inserts misbehave.' },

    { sec: 'keys', q: 'What does a transparent comparator (`std::map<std::string, int, std::less<>>`) let you do?',
      opts: ['Make the map thread-safe', 'Look up with a `string_view` or `const char*` without constructing a temporary `std::string`', 'Sort in descending order', 'Store duplicate keys'], a: 1,
      why: '`std::less<>` accepts different but comparable types, so `find("abc")` does not allocate a `std::string`.' },

    { sec: 'keys', q: 'A map key object is modified while it is stored in the container. What is the consequence?',
      opts: ['Nothing', 'The key is in the wrong position (or bucket), so lookups and the container invariants break', 'The map re-sorts itself automatically', 'The program does not compile'], a: 1,
      why: 'That is why map and set keys are `const`. To change a key, remove the element and insert a new one.' },

    { sec: 's4', q: 'What does `try_emplace(key, std::move(value))` guarantee when the key already exists?',
      opts: ['It overwrites the old value', 'It does nothing and leaves `value` untouched', 'It throws', 'It moves `value` and discards it'], a: 1,
      why: 'Unlike `emplace` and `insert`, `try_emplace` does not touch its arguments when the key is present.' },

    { sec: 's4', q: 'What is the difference between `std::map` and `std::multimap`?',
      opts: ['`multimap` is hashed', '`multimap` allows several entries with the same key and has no `operator[]`', '`multimap` is faster', '`multimap` is unordered'], a: 1,
      why: 'Use `equal_range(key)` to get all entries for a key.' },

    { sec: 's6', q: 'Why does `std::copy(src.begin(), src.end(), out.begin())` with an empty `out` break, and what fixes it?',
      opts: ['It is fine', 'It writes past the end; use `std::back_inserter(out)` so each assignment becomes a `push_back`', 'It needs `std::move`', 'It needs `reserve` only'], a: 1,
      why: 'Algorithms assign through the output iterator and do not grow the destination. An inserter turns assignments into insertions.' },

    { sec: 'ranges', q: 'What does `v | std::views::filter(f) | std::views::transform(g)` do when it is created?',
      opts: ['It builds a new vector immediately', 'Nothing yet: it is a lazy view whose elements are computed when iterated', 'It sorts `v`', 'It copies `v`'], a: 1,
      why: 'Views are lazy and non-owning. Work happens during iteration, with no temporary containers.' },

    { sec: 'ranges', q: 'What is the practical difference between `std::sort(v.begin(), v.end())` and `std::ranges::sort(v)`?',
      opts: ['The ranges version is always faster', 'The ranges version takes the whole container (and supports projections) instead of an iterator pair', 'The ranges version works only on arrays', 'There is no difference in what you can write'], a: 1,
      why: 'The ranges algorithms accept a whole range, so you cannot mismatch begin and end of different containers, and they support projections such as `std::ranges::sort(people, {}, &Person::age)`. The sorting itself is the same.' },

    { sec: 'ranges', q: 'When can a view such as `v | std::views::filter(f)` become a dangling problem?',
      opts: ['Never: a view owns a copy of the data', 'When the container it looks at is destroyed or reallocated while the view is still used', 'Only when the filter returns false', 'Only with `transform`, never with `filter`'], a: 1,
      why: 'A view is non-owning, like `string_view`. If the vector dies, or reallocates after a `push_back`, the view points at stale memory.' },

    { sec: 'random', q: 'Two engines are created as `std::mt19937 a(42), b(42);` and used with the same distribution. What do they produce?',
      opts: ['Different sequences, because each engine is random', 'The same sequence: the same seed gives the same numbers', 'An error: the seed must come from std::random_device', 'Only zeros'], a: 1,
      why: 'An engine is deterministic: the same seed gives the same sequence (compiled: true). That is what you want in tests and simulations; use `std::random_device` to seed when you want different runs.' },

    { sec: 'random', q: 'Why is `rand() % 6 + 1` a poor way to roll a die in modern C++?',
      opts: ['It is too slow to matter', 'The low-quality generator and the modulo make it biased, and it uses hidden global state', 'It does not compile in C++', 'It can only produce 0'], a: 1,
      why: 'Use an engine plus a distribution (`std::mt19937` with `std::uniform_int_distribution<int>(1, 6)`): better quality, no modulo bias, and no global state.' }
  ]
};
