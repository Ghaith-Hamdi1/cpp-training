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
      opts: ['They stay valid', 'Just end() is invalidated', 'All of them are invalidated', 'Those after the insertion point'], a: 2,
      why: 'The elements moved to a new buffer, so anything pointing into the old one dangles. Reserve up front or avoid holding pointers across growth.' },

    { sec: 's6', q: 'Which loop erases the even numbers correctly?',
      code: String.raw`
std::vector<int> v{1, 2, 3, 4};`,
      opts: ['`for (auto it = v.begin(); it != v.end(); ++it) if (*it % 2 == 0) v.erase(it);`', '`for (auto it = v.begin(); it != v.end(); ) { if (*it % 2 == 0) it = v.erase(it); else ++it; }`', '`for (int x : v) if (x % 2 == 0) v.erase(&x);`', '`v.erase(v.begin(), v.end(), 2);`'], a: 1,
      why: '`erase` invalidates the iterator and returns the next valid one. Using the return value (and not incrementing in that case) is the correct pattern. C++20 offers `std::erase_if(v, pred)`.' },

    { sec: 's4', q: 'How does iteration order differ between `std::map` and `std::unordered_map`?',
      opts: ['Both are sorted by key, so iteration order is the same', 'map is sorted by key; unordered_map has no defined order', 'unordered_map is sorted by key, while map is in insertion order', 'Both preserve the order in which elements were inserted'], a: 1,
      why: '`map` is a balanced tree, so in-order traversal is sorted. `unordered_map` is a hash table whose order is unspecified and can change after a rehash.' },

    { sec: 's6', q: 'Why does `std::sort(myList.begin(), myList.end())` fail to compile for a `std::list`?',
      opts: ['Lists cannot hold int elements, just class types such as strings', 'std::sort needs random-access iterators; list has only bidirectional ones', 'std::sort works just on built-in arrays and std::array', 'The list would have to be declared const before sorting'], a: 1,
      why: '`sort` jumps around by index arithmetic. Use the member function `myList.sort()` instead.' },

    { sec: 's4', q: 'What does `std::priority_queue<int> q;` return from `q.top()` by default?',
      opts: ['The smallest element', 'The largest element', 'The first inserted element', 'The last inserted element'], a: 1,
      why: 'It is a max-heap by default (it uses `std::less`). For a min-heap use `std::priority_queue<int, std::vector<int>, std::greater<int>>`.' },

    { sec: 's9', q: 'What is the bug in this loop?',
      code: String.raw`
std::vector<int> v;   // empty
for (std::size_t i = 0; i < v.size() - 1; ++i) { /* ... */ }`,
      opts: ['The loop is correct and runs properly for all vectors', 'v.size() - 1 wraps to a huge value because size() is unsigned', 'The loop does not run, because the condition is false', 'i should be declared as a signed int, but the loop still works'], a: 1,
      why: 'Unsigned subtraction below zero wraps. Write `i + 1 < v.size()` or check `empty()` first.' },

    { sec: 's7', q: 'Why must a sort comparator use `<` and not `<=`?',
      opts: ['<= is slower than < for large ranges because it does extra work', 'The comparator must be a strict weak ordering: <= can crash std::sort', '<= makes the sort unstable, so equal elements may be reordered', 'It is a style rule and has no effect on correctness'], a: 1,
      why: 'Algorithms assume `comp(a, a)` is false. Violating that can cause out-of-bounds reads in `std::sort` and corrupt ordered containers.' },

    { sec: 's2', q: 'What is the difference between `push_back` and `emplace_back`?',
      opts: ['emplace_back inserts the new element at the front instead of the back', 'emplace_back constructs the element in place, avoiding a temporary', 'push_back is faster than emplace_back for most element types', 'They behave the same for most types, so the choice is style'], a: 1,
      why: '`push_back(obj)` copies or moves an existing object. `emplace_back(args...)` builds it directly inside the container. For trivial types the two compile to the same thing.' },

    { sec: 's7', q: 'What must be true before calling `std::lower_bound` or `std::binary_search` on a range?',
      opts: ['The range must contain no duplicate elements', 'The range must be sorted by the same ordering', 'The range must be stored in a std::vector', 'The range must not be empty before the call'], a: 1,
      why: 'Binary search only makes sense on sorted data. On unsorted data the result is meaningless (and the precondition violation is undefined behavior).' },

    { sec: 's4', q: 'What is the worst-case cost of a lookup in `std::unordered_map`?',
      opts: ['O(1) always, because hashing guarantees constant lookup time', 'O(log n), as in a balanced tree with n entries', 'O(n), when many keys collide into one bucket', 'O(n log n), because the table sorts its keys during the lookup'], a: 2,
      why: 'Average O(1) relies on a good hash function and low load factor. Heavy collisions degrade a bucket toward a linear scan.' },

    { sec: 's6', q: 'What does `end()` return for a container?',
      opts: ['An iterator to the last element of the container', 'An iterator one past the last element, never dereferenced', 'A null pointer that marks the end of the container', 'An iterator to the first element of the container'], a: 1,
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
      opts: ['Lists are slower to insert into than other containers are', 'Contiguous memory is cache-friendly; a list allocates a node per element', 'Vectors do not need to move elements when inserting in the middle', 'Lists cannot insert elements in the middle of the sequence'], a: 1,
      why: 'Big-O hides constants. A vector\'s memmove-style shift is fast on modern CPUs, while pointer-chasing through scattered list nodes causes cache misses. Always measure.' },

    { sec: 's2', q: 'What is the difference between `std::vector<int> a(3, 7);` and `std::vector<int> b{3, 7};`?',
      opts: ['Both hold three elements equal to 7, written two ways', 'a holds {7, 7, 7}; b holds {3, 7}: braces prefer initializer_list', 'a does not compile, since 3 is not a valid size argument', 'b holds three elements, the same as a, written differently'], a: 1,
      why: 'Parentheses call the (count, value) constructor. Braces prefer a constructor taking std::initializer_list whenever one can match, so the two numbers become the elements.' },

    { sec: 'keys', q: 'You use a struct as the key of `std::unordered_map`. What must you provide?',
      opts: ['operator< alone, because the container orders its keys like std::map', 'operator== and a hash function (functor or std::hash specialisation)', 'operator() and operator[] defined on the key type itself', 'The compiler generates both for a struct automatically'], a: 1,
      why: 'Hashing finds the bucket and equality finds the key inside it. Equal keys must produce equal hashes.' },

    { sec: 'keys', q: 'Why is `operator<=` not a valid comparator for `std::map`?',
      opts: ['It is slower than operator< because it has to compare twice', 'It breaks strict weak ordering: an element is not less than itself', 'It does not compile when it is used with std::map', 'It reverses the order of the keys in the container for lookups'], a: 1,
      why: 'Ordered containers need `comp(a, a) == false`. With `<=` equal keys compare as "less", so lookups and inserts misbehave.' },

    { sec: 'keys', q: 'What does a transparent comparator (`std::map<std::string, int, std::less<>>`) let you do?',
      opts: ['Make the map thread-safe for concurrent readers and writers alike', 'Look up with a string_view or const char* without a temporary std::string', 'Sort the keys in descending order instead of ascending order', 'Store duplicate keys in the same map without reporting an error'], a: 1,
      why: '`std::less<>` accepts different but comparable types, so `find("abc")` does not allocate a `std::string`.' },

    { sec: 'keys', q: 'A map key object is modified while it is stored in the container. What is the consequence?',
      opts: ['The map copes with changed keys by itself', 'The key sits in the wrong position or bucket, so lookups break', 'The map re-sorts itself automatically afterwards', 'The program no longer compiles after the key is modified'], a: 1,
      why: 'That is why map and set keys are `const`. To change a key, remove the element and insert a new one.' },

    { sec: 's4', q: 'What does `try_emplace(key, std::move(value))` guarantee when the key already exists?',
      opts: ['It overwrites the old value in the map', 'It does nothing and leaves value untouched', 'It throws an exception for the duplicate key', 'It moves value in and then discards it'], a: 1,
      why: 'Unlike `emplace` and `insert`, `try_emplace` does not touch its arguments when the key is present.' },

    { sec: 's4', q: 'What is the difference between `std::map` and `std::multimap`?',
      opts: ['multimap is hashed instead of tree-based, like unordered_map', 'multimap allows several entries per key and has no operator[]', 'multimap is faster for most kinds of lookup', 'multimap is unordered, like unordered_map, but allows duplicates'], a: 1,
      why: 'Use `equal_range(key)` to get all entries for a key.' },

    { sec: 's6', q: 'Why does `std::copy(src.begin(), src.end(), out.begin())` with an empty `out` break, and what fixes it?',
      opts: ['It is fine: copy grows the destination automatically as it goes', 'It writes past the end; std::back_inserter(out) makes writes push_back', 'It needs std::move to work on empty destination containers', 'It needs just a reserve call on out before the copy starts'], a: 1,
      why: 'Algorithms assign through the output iterator and do not grow the destination. An inserter turns assignments into insertions.' },

    { sec: 'ranges', q: 'What does `v | std::views::filter(f) | std::views::transform(g)` do when it is created?',
      opts: ['It builds a new vector right away from the filtered values', 'Nothing yet: it is a lazy view, evaluated when iterated', 'It sorts v in place before elements are read', 'It copies every element of v into a temporary vector'], a: 1,
      why: 'Views are lazy and non-owning. Work happens during iteration, with no temporary containers.' },

    { sec: 'ranges', q: 'What is the practical difference between `std::sort(v.begin(), v.end())` and `std::ranges::sort(v)`?',
      opts: ['The ranges version is faster than the iterator version of sort', 'The ranges version takes the whole container (and supports projections)', 'The ranges version works on built-in arrays, not on vectors', 'You can write the same things with both, in code'], a: 1,
      why: 'The ranges algorithms accept a whole range, so you cannot mismatch begin and end of different containers, and they support projections such as `std::ranges::sort(people, {}, &Person::age)`. The sorting itself is the same.' },

    { sec: 'ranges', q: 'When can a view such as `v | std::views::filter(f)` become a dangling problem?',
      opts: ['Not a problem: a view owns a private copy of the data it shows', 'When the container dies or reallocates while the view is still used', 'When the filter function returns false for all elements', 'With transform, not with filter, since filter is lazy'], a: 1,
      why: 'A view is non-owning, like `string_view`. If the vector dies, or reallocates after a `push_back`, the view points at stale memory.' },

    { sec: 'random', q: 'Two engines are created as `std::mt19937 a(42), b(42);` and used with the same distribution. What do they produce?',
      opts: ['Different sequences, because each engine is random', 'The same sequence: same seed, same numbers', 'An error: the seed must come from std::random_device', 'Zeros, since the seeds are equal'], a: 1,
      why: 'An engine is deterministic: the same seed gives the same sequence (compiled: true). That is what you want in tests and simulations; use `std::random_device` to seed when you want different runs.' },

    { sec: 'random', q: 'Why is `rand() % 6 + 1` a poor way to roll a die in modern C++?',
      opts: ['It is too slow to matter in everyday modern code', 'A weak generator, modulo bias and hidden global state', 'It does not compile when used with modern C++ headers', 'It produces the value 0 on most platforms'], a: 1,
      why: 'Use an engine plus a distribution (`std::mt19937` with `std::uniform_int_distribution<int>(1, 6)`): better quality, no modulo bias, and no global state.' }
  ]
};
