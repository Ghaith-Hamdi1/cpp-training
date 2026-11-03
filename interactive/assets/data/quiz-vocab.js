/* Quiz questions for the 'vocab' topic. Loaded by 21-vocabulary-types-quiz.html. */
CT.quizData.vocab = {
  id: 'vocab',
  questions: [
    { sec: 'why', q: 'What is the main point of a "vocabulary type" such as `std::optional`?',
      opts: ['It is usually faster than a raw pointer, because it never allocates', 'It puts the contract (absent, one of several, value or error) in the signature', 'It removes the need for templates in generic code, replacing them with variants', 'It stores its value on the heap so that several owners can share it'], a: 1,
      why: 'These types replace magic values (`-1`), tagged unions and pointer-plus-count pairs. The meaning is in the type, not in a comment. They are ordinary value types: no heap allocation, no virtual functions.' },

    { sec: 'optional', q: 'What happens when you write `*opt` on an empty `std::optional<int>`?',
      opts: ['It throws std::bad_optional_access, like value()', 'It returns a default-constructed int, which is 0', 'Undefined behaviour: operator* does not check', 'It does not compile for an empty optional'], a: 2,
      why: '`operator*` and `operator->` are unchecked, like dereferencing a null pointer. `value()` is the checked version and throws `bad_optional_access`; `value_or(x)` supplies a default.' },

    { sec: 'optional', q: 'How big is `std::optional<int>` compared with `int` (typical 64-bit platform)?',
      opts: ['The same size: the flag is stored somewhere else', 'Bigger: the value plus a flag, padded (8 bytes)', 'Pointer sized, because the value lives on the heap', 'It depends on the value stored inside'], a: 1,
      why: 'The int lives inside the optional next to a flag (compiled: 4 versus 8 bytes). There is no heap allocation, which is the main advantage over a pointer or `unique_ptr`.' },

    { sec: 'optional', q: 'A lookup function may legitimately find nothing, and the reason is obvious. What is the best return type?',
      opts: ['An `int` that returns -1', 'A raw pointer that is null when nothing is found, owned by the callee', '`std::optional<T>`', 'It throws an exception on each miss'], a: 2,
      why: '`optional<T>` makes "not found" part of the type, needs no allocation and cannot be mistaken for a real value. An exception is too heavy for an expected miss, and a magic value hides the contract.' },

    { sec: 'variant', q: 'What does this print?',
      code: String.raw`
std::variant<int, std::string> v;
std::cout << v.index();`,
      opts: ['0', '1', 'It is valueless, so index() throws an exception', 'It does not compile: there is no default constructor'], a: 0,
      why: 'A default-constructed variant holds a value-initialized first alternative, so `index()` is 0 (the int, value 0). To make "no alternative" the default, put `std::monostate` first.' },

    { sec: 'variant', q: 'What happens at `std::get<std::string>(v)` when `v` currently holds an `int`?',
      code: String.raw`
std::variant<int, std::string> v = 7;
auto s = std::get<std::string>(v);`,
      opts: ['Undefined behaviour, like a union', 'It throws `std::bad_variant_access`', 'It converts the int to a string', 'It returns an empty string'], a: 1,
      why: 'Unlike a raw union, a variant knows its active alternative, so a wrong `get` is detected and throws. `std::get_if<std::string>(&v)` returns a null pointer instead of throwing.' },

    { sec: 'variant', q: 'You add a third alternative to a `variant` and forget to handle it in one `std::visit` call that uses `overloaded{...}` lambdas. What happens?',
      opts: ['It silently skips the new alternative at run time', 'A compile error: the visitor must accept every alternative', 'A run-time exception when that alternative is active', 'The first lambda is called for it by default'], a: 1,
      why: '`std::visit` requires the callable to accept every alternative. A missing case is a compile-time error, which is the main safety advantage over a chain of `if` / `get_if` checks or a `switch` on a tag.' },

    { sec: 'variant', q: 'When is `std::variant` a better fit than a class hierarchy with virtual functions?',
      opts: ['When the set of types is open and others will add their own', 'When the set of types is closed and operations keep being added', 'When speed matters: virtual functions are faster than variants', 'Only for built-in types such as int and double'], a: 1,
      why: 'With a closed set of types (messages, tokens, syntax-tree nodes), a variant stores values inline with no allocation or virtual call, and each new operation is one new visitor that the compiler checks for completeness. Virtual functions fit an open set of types.' },

    { sec: 'expected', q: 'What does `std::expected<T, E>` offer that `std::optional<T>` does not?',
      opts: ['It stores its value on the heap, not inline, so it can be moved cheaply', 'It carries the reason for a failure (an E) when there is no T', 'It has been in the standard library since C++11, in <utility>', 'It cannot throw, even from value(), so it is noexcept'], a: 1,
      why: '`optional` says only "no value". `expected<T, E>` (C++23) holds either the value or an error object that explains what went wrong, without an exception. `value()` on an error still throws `bad_expected_access`.' }
  ]
};
