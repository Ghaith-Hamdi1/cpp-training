/* Quiz questions for the 'assoc' topic. Loaded by 31-assoc-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.assoc = {
  id: 'assoc',
  questions: [
    { sec: 's4', q: 'What does this print?',
      code: String.raw`
std::map<std::string, int> m;
if (m["x"] == 0) { }
std::cout << m.size();`,
      opts: ['0', '1', 'It throws', 'Undefined behavior'], a: 1,
      why: '`operator[]` inserts a default-constructed value when the key is missing. Use `find`, `count` or `contains` to test for a key without inserting.' },

    { sec: 's4', q: 'How does iteration order differ between `std::map` and `std::unordered_map`?',
      opts: ['Both are sorted by key, so iteration order is the same', 'map is sorted by key; unordered_map has no defined order', 'unordered_map is sorted by key, while map is in insertion order', 'Both preserve the order in which elements were inserted'], a: 1,
      why: '`map` is a balanced tree, so in-order traversal is sorted. `unordered_map` is a hash table whose order is unspecified and can change after a rehash.' },

    { sec: 's4', q: 'What does `std::priority_queue<int> q;` return from `q.top()` by default?',
      opts: ['The smallest element', 'The largest element', 'The first inserted element', 'The last inserted element'], a: 1,
      why: 'It is a max-heap by default (it uses `std::less`). For a min-heap use `std::priority_queue<int, std::vector<int>, std::greater<int>>`.' },

    { sec: 's4', q: 'What is the worst-case cost of a lookup in `std::unordered_map`?',
      opts: ['O(1) always, because hashing guarantees constant lookup time', 'O(log n), as in a balanced tree with n entries', 'O(n), when many keys collide into one bucket', 'O(n log n), because the table sorts its keys during the lookup'], a: 2,
      why: 'Average O(1) relies on a good hash function and low load factor. Heavy collisions degrade a bucket toward a linear scan.' },

    { sec: 's4', q: 'In the code below, what is `counts["apple"]` after the loop?',
      code: String.raw`
std::unordered_map<std::string, int> counts;
for (const auto& w : {"apple", "pear", "apple"})
    counts[w]++;`,
      opts: ['1', '2', '0', 'The code does not compile'], a: 1,
      why: 'On the first "apple", `operator[]` inserts a value-initialised 0 which is then incremented. The second "apple" increments it again: 2.' },

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

    { sec: 'pairs', q: 'What do `lo` and `hi` hold?',
      code: String.raw`
std::pair<int, int> minmax(const std::vector<int>& v);   // {smallest, largest}
auto [lo, hi] = minmax({3, 9, 1, 7});`,
      opts: ['`lo` is 3 and `hi` is 7 (first and last)', '`lo` is 1 and `hi` is 9', 'It does not compile: a pair cannot be unpacked', '`lo` and `hi` are both pairs'], a: 1,
      why: 'A structured binding names the members of the returned pair in order: `.first` becomes `lo` (1) and `.second` becomes `hi` (9).' },

    { sec: 'pairs', q: '`auto [it, inserted] = m.insert({"a", 2});` where the map already holds the key "a" with value 1. What is `inserted`, and what does `it->second` read?',
      opts: ['`true`, and 2', '`false`, and 1', '`false`, and 2', '`true`, and 1'], a: 1,
      why: '`insert` never overwrites. It returns `pair<iterator, bool>`: the bool says whether a new element was added (`false` here), and the iterator points at the element that is in the map (still 1). Use `insert_or_assign` to overwrite.' }
  ]
};
