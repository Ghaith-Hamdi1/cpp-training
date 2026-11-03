/* Quiz questions for the 'algorithms' topic. Loaded by 29-algorithms-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.algorithms = {
  id: 'algorithms',
  questions: [
    { sec: 's7', q: 'What does this print?',
      code: String.raw`
std::vector<int> v{1, 2, 3, 4, 5};
std::remove(v.begin(), v.end(), 3);
std::cout << v.size();`,
      opts: ['4', '5', '3', '0'], a: 1,
      why: 'Algorithms cannot change a container\'s size. `std::remove` only shifts elements and returns the new logical end. Combine it with `erase` (the erase-remove idiom) or use C++20 `std::erase`.' },

    { sec: 's7', q: 'Why must a sort comparator use `<` and not `<=`?',
      opts: ['<= is slower than < for large ranges because it does extra work', 'The comparator must be a strict weak ordering: <= can crash std::sort', '<= makes the sort unstable, so equal elements may be reordered', 'It is a style rule and has no effect on correctness'], a: 1,
      why: 'Algorithms assume `comp(a, a)` is false. Violating that can cause out-of-bounds reads in `std::sort` and corrupt ordered containers.' },

    { sec: 's7', q: 'What must be true before calling `std::lower_bound` or `std::binary_search` on a range?',
      opts: ['The range must contain no duplicate elements', 'The range must be sorted by the same ordering', 'The range must be stored in a std::vector', 'The range must not be empty before the call'], a: 1,
      why: 'Binary search only makes sense on sorted data. On unsorted data the result is meaningless (and the precondition violation is undefined behavior).' },

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
      why: 'Use an engine plus a distribution (`std::mt19937` with `std::uniform_int_distribution<int>(1, 6)`): better quality, no modulo bias, and no global state.' },

    { sec: 's7', q: 'What does `std::remove(v.begin(), v.end(), 3)` do to `v.size()`?',
      opts: ['Nothing: it only shifts kept elements forward', 'It shrinks the vector by the number of 3s it found', 'It throws an exception if there is no 3 in the range', 'It sets the removed slots to zero and keeps the size'], a: 0,
      why: 'Algorithms work through iterators and cannot change the size of a container. Erase the tail afterwards: erase-remove.' },

    { sec: 's7', q: 'What is wrong with `std::accumulate(v.begin(), v.end(), 0)` when `v` holds doubles?',
      opts: ['The int start value makes the sum an int', 'It does not compile when the range holds doubles', 'It sums only the first half of the range given to it', 'It needs a custom lambda to be able to add doubles'], a: 0,
      why: 'The type of the initial value decides the type of the sum. Write 0.0.' },

    { sec: 's7', q: 'How do you find a key in a `std::map` efficiently?',
      opts: ['Call the member `m.find(key)`, O(log n)', 'Call `std::find(m.begin(), m.end(), key)` on the map', 'Loop over the whole map and compare every key by hand', 'Sort the map first and then call lower_bound on it'], a: 0,
      why: 'std::find walks every element in O(n) and compares pairs. The member function uses the tree.' },

    { sec: 's7', q: 'Why does `std::transform` into an empty vector need `std::back_inserter`?',
      opts: ['It writes through the output iterator without growing', 'transform sorts the output container before writing', 'back_inserter makes the lambda run noticeably faster', 'An empty vector does not have a begin() iterator'], a: 0,
      why: 'Algorithms assign through iterators. An inserter turns each assignment into a push_back.' },

    { sec: 'ranges', q: 'What does the projection in `std::ranges::sort(people, {}, &Person::age)` do?',
      opts: ['It sorts by the age member, no comparator needed', 'It copies all the ages into a new temporary vector', 'It sorts the data members inside every Person object', 'It sorts the people in descending order of their age'], a: 0,
      why: 'A projection is applied to each element before the comparison. The empty braces select the default less.' },

    { sec: 'families', q: 'What does `std::unique` do to the vector {1, 2, 1, 2}?',
      opts: ['It removes nothing, because there are no neighbouring duplicates', 'It removes the second 1 and the second 2', 'It sorts the vector and then removes the duplicates', 'It removes the first element of each pair of duplicates'], a: 0,
      why: 'unique removes only equal neighbours. Sort first when you want every duplicate gone.' },

    { sec: 'families', q: 'Which algorithm puts the elements that satisfy a predicate in front and returns the split point?',
      opts: ['`std::partition`', '`std::sort`', '`std::find_if`', '`std::accumulate`'], a: 0,
      why: 'partition reorders the range so matches come first and returns an iterator to the first non-match.' },

    { sec: 'pitfalls', q: 'Why is `std::find(m.begin(), m.end(), key)` a poor way to look up a key in a `map`?',
      opts: ['It scans every element in O(n) and the member find uses the tree in O(log n)', 'It does not compile for maps at all', 'It returns the value instead of an iterator', 'It modifies the map when the key is missing'], a: 0,
      why: 'The generic algorithm knows nothing about the tree. The member find is the fast path.' }
  ]
};
