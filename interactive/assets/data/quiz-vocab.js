/* Quiz questions for the 'vocab' topic. Loaded by 21-vocabulary-types-quiz.html. */
CT.quizData.vocab = {
  id: 'vocab',
  questions: [
    { sec: 'why', q: 'What is the main point of a "vocabulary type" such as `std::optional`?',
      opts: ['It is faster than a pointer', 'It puts a contract (maybe absent, one of several, a value or an error) into the signature, so readers and the compiler can see it', 'It avoids all use of templates', 'It stores its value on the heap'], a: 1,
      why: 'These types replace magic values (`-1`), tagged unions and pointer-plus-count pairs. The meaning is in the type, not in a comment. They are ordinary value types: no heap allocation, no virtual functions.' },

    { sec: 'pairs', q: 'What do `lo` and `hi` hold?',
      code: String.raw`
std::pair<int, int> minmax(const std::vector<int>& v);   // {smallest, largest}
auto [lo, hi] = minmax({3, 9, 1, 7});`,
      opts: ['`lo` is 3 and `hi` is 7 (first and last)', '`lo` is 1 and `hi` is 9', 'It does not compile: a pair cannot be unpacked', '`lo` and `hi` are both pairs'], a: 1,
      why: 'A structured binding names the members of the returned pair in order: `.first` becomes `lo` (1) and `.second` becomes `hi` (9).' },

    { sec: 'pairs', q: '`auto [it, inserted] = m.insert({"a", 2});` where the map already holds the key "a" with value 1. What is `inserted`, and what does `it->second` read?',
      opts: ['`true`, and 2', '`false`, and 1', '`false`, and 2', '`true`, and 1'], a: 1,
      why: '`insert` never overwrites. It returns `pair<iterator, bool>`: the bool says whether a new element was added (`false` here), and the iterator points at the element that is in the map (still 1). Use `insert_or_assign` to overwrite.' },

    { sec: 'optional', q: 'What happens when you write `*opt` on an empty `std::optional<int>`?',
      opts: ['It throws `std::bad_optional_access`', 'It returns 0', 'Undefined behaviour: `*` does not check', 'It does not compile'], a: 2,
      why: '`operator*` and `operator->` are unchecked, like dereferencing a null pointer. `value()` is the checked version and throws `bad_optional_access`; `value_or(x)` supplies a default.' },

    { sec: 'optional', q: 'How big is `std::optional<int>` compared with `int` (typical 64-bit platform)?',
      opts: ['The same: the flag is stored elsewhere', 'Bigger: the value plus a "has value" flag, padded (8 bytes)', 'Pointer sized, because it allocates on the heap', 'It depends on the value'], a: 1,
      why: 'The int lives inside the optional next to a flag (compiled: 4 versus 8 bytes). There is no heap allocation, which is the main advantage over a pointer or `unique_ptr`.' },

    { sec: 'optional', q: 'A lookup function may legitimately find nothing, and the reason is obvious. What is the best return type?',
      opts: ['An `int` that returns -1', 'A raw pointer that is null when nothing is found, owned by the callee', '`std::optional<T>`', 'It throws an exception for every miss'], a: 2,
      why: '`optional<T>` makes "not found" part of the type, needs no allocation and cannot be mistaken for a real value. An exception is too heavy for an expected miss, and a magic value hides the contract.' },

    { sec: 'variant', q: 'What does this print?',
      code: String.raw`
std::variant<int, std::string> v;
std::cout << v.index();`,
      opts: ['0', '1', 'Nothing: it is empty and `index()` throws', 'It does not compile: there is no default constructor'], a: 0,
      why: 'A default-constructed variant holds a value-initialized first alternative, so `index()` is 0 (the int, value 0). To make "no alternative" the default, put `std::monostate` first.' },

    { sec: 'variant', q: 'What happens at `std::get<std::string>(v)` when `v` currently holds an `int`?',
      code: String.raw`
std::variant<int, std::string> v = 7;
auto s = std::get<std::string>(v);`,
      opts: ['Undefined behaviour, like a union', 'It throws `std::bad_variant_access`', 'It converts the int to a string', 'It returns an empty string'], a: 1,
      why: 'Unlike a raw union, a variant knows its active alternative, so a wrong `get` is detected and throws. `std::get_if<std::string>(&v)` returns a null pointer instead of throwing.' },

    { sec: 'variant', q: 'You add a third alternative to a `variant` and forget to handle it in one `std::visit` call that uses `overloaded{...}` lambdas. What happens?',
      opts: ['It silently does nothing for the new alternative', 'A compile error: the visitor must be callable with every alternative', 'A run-time exception when that alternative is active', 'The first lambda is used for it'], a: 1,
      why: '`std::visit` requires the callable to accept every alternative. A missing case is a compile-time error, which is the main safety advantage over a chain of `if` / `get_if` checks or a `switch` on a tag.' },

    { sec: 'variant', q: 'When is `std::variant` a better fit than a class hierarchy with virtual functions?',
      opts: ['When the set of types is open and others will add their own', 'When the set of types is closed and you keep adding operations over it', 'Never: virtual functions are always faster', 'Only for built-in types such as `int` and `double`'], a: 1,
      why: 'With a closed set of types (messages, tokens, syntax-tree nodes), a variant stores values inline with no allocation or virtual call, and each new operation is one new visitor that the compiler checks for completeness. Virtual functions fit an open set of types.' },

    { sec: 'expected', q: 'What does `std::expected<T, E>` offer that `std::optional<T>` does not?',
      opts: ['It stores the value on the heap', 'It carries the reason for the failure (an `E`) when there is no `T`', 'It is available in C++11', 'It never throws, even from `value()`'], a: 1,
      why: '`optional` says only "no value". `expected<T, E>` (C++23) holds either the value or an error object that explains what went wrong, without an exception. `value()` on an error still throws `bad_expected_access`.' },

    { sec: 'views', q: 'Which function signature lets the caller pass a `std::vector<int>`, a C array `int[3]` or a slice of either, without a copy?',
      opts: ['`long sum(const std::vector<int>& xs)`', '`long sum(std::span<const int> xs)`', '`long sum(int* xs)`', '`long sum(std::vector<int> xs)`'], a: 1,
      why: 'A span is a pointer plus a length over any contiguous elements. It accepts a vector, an array, a `std::array` or `subspan` of them, remembers its size, and is passed by value (two words).' },

    { sec: 'views', q: 'What is wrong here?',
      code: String.raw`
std::vector<int> v{1, 2, 3};
std::span<int> s = v;
v.push_back(4);
std::cout << s[0];`,
      opts: ['Nothing: `s` follows the vector', 'The `push_back` may reallocate, so `s` can point at freed memory (undefined behaviour)', 'A span cannot be created from a vector', '`s[0]` is checked and throws'], a: 1,
      why: 'A view does not own its data. `push_back` can move the elements to a new buffer, leaving the span dangling. Take views for parameters and short-lived use, and re-create them after modifying the container.' }
  ]
};
