/* Quiz questions for the 'moves' topic. Loaded by 13-move-semantics-quiz.html. */
CT.quizData.moves = {
  id: 'moves',
  questions: [
    { sec: 'copy-move', q: 'What does `std::move(x)` do?',
      opts: ['Moves x\'s data to a new memory location', 'Casts x to an rvalue reference so a move constructor/assignment can be used; it moves nothing by itself', 'Deletes x', 'Copies x and clears the original'], a: 1,
      why: '`std::move` is just `static_cast<T&&>(x)`. The actual transfer happens in whichever move constructor or move assignment operator is then selected.' },

    { sec: 'copy-move', q: 'After `std::vector<int> b = std::move(a);`, what may you safely do with `a`?',
      opts: ['Read a[0]', 'Call a.size() and trust it equals the old size', 'Destroy it or assign a new value to it', 'Nothing, the program is undefined'], a: 2,
      why: 'A moved-from object is valid but unspecified: it is safe to destroy or assign to, but you should not rely on its contents.' },

    { sec: 'returning', q: 'Why is `return std::move(local);` usually a mistake?',
      opts: ['It does not compile', 'It prevents copy elision (RVO), so it can be slower', 'It makes the result const', 'It causes a memory leak'], a: 1,
      why: 'Returning a local by value already lets the compiler elide the copy or implicitly move it. Wrapping it in `std::move` changes the expression type and blocks elision.' },

    { sec: 'writing', q: 'Why mark a move constructor `noexcept`?',
      opts: ['It makes it faster by itself', 'std::vector only uses a move (instead of a copy) when reallocating if the move cannot throw', 'It is required by the language', 'It prevents the object being copied'], a: 1,
      why: 'To keep the strong exception guarantee, `vector` uses `std::move_if_noexcept` during reallocation: a throwing move would leave elements in a half-moved state, so it copies instead.' },

    { sec: 'traps', q: 'What does the second line do?',
      code: String.raw`
const std::string a = "text";
std::string b = std::move(a);`,
      opts: ['Moves the contents of a into b', 'Copies a into b: a const rvalue cannot bind to the move constructor', 'It does not compile', 'Undefined behavior'], a: 1,
      why: '`std::move` only casts to an rvalue, and a `const` rvalue cannot bind to `string(string&&)`, so overload resolution silently picks the copy constructor. Never return `const` values by value for the same reason.' },

    { sec: 'values', q: 'What is the value category of the expression `std::move(x)`?',
      opts: ['lvalue', 'prvalue', 'xvalue', 'It is not an expression'], a: 2,
      why: 'An xvalue is an object marked as movable, and `std::move` produces one. A prvalue is an unnamed temporary like `5` or `a + b`. "Rvalue" means a prvalue or an xvalue.' },

    { sec: 'values', q: 'Which expression is a prvalue?',
      opts: ['`x` (a named variable)', '`std::move(x)`', '`x + 1`', '`v[0]`'], a: 2,
      why: '`x + 1` is an unnamed temporary: a prvalue. `x` and `v[0]` are lvalues; `std::move(x)` is an xvalue.' },

    { sec: 'values', q: 'Which overload is called?',
      code: String.raw`
void h(const std::string&);
void h(std::string&&);
void g(std::string&& s) { h(s); }`,
      opts: ['`h(const std::string&)`, because `s` is an lvalue inside `g`', '`h(std::string&&)`, because `s` has an rvalue reference type', 'Neither: the call is ambiguous', 'The code does not compile'], a: 0,
      why: 'A name is always an lvalue, whatever its declared type. To pass it on as an rvalue you need `std::move(s)`.' },

    { sec: 'values', q: 'What can bind to an rvalue reference parameter `T&&`?',
      opts: ['Any lvalue of type `T`', 'Rvalues only: temporaries and `std::move(x)`', 'Only `const` objects', 'Anything'], a: 1,
      why: 'An rvalue reference binds to rvalues, which is how overload resolution sends temporaries to move operations. An lvalue needs `std::move` first.' },

    { sec: 'writing', q: 'What is wrong with this move constructor?',
      code: String.raw`
Buffer(Buffer&& o) noexcept : data_(o.data_), n_(o.n_) {}`,
      opts: ['Nothing', 'The source still owns `data_`, so both objects free it: a double delete', '`noexcept` is not allowed on move constructors', 'It must take a `const Buffer&`'], a: 1,
      why: 'A move constructor must leave the source empty (`o.data_ = nullptr`), or use `std::exchange`. Otherwise both destructors release the same block.' },

    { sec: 'writing', q: 'What does `std::exchange(o.data_, nullptr)` do?',
      opts: ['Returns `nullptr` and leaves `o.data_` alone', 'Returns the old value of `o.data_` and sets it to `nullptr`', 'Swaps `o.data_` with a null pointer permanently', 'Deletes `o.data_`'], a: 1,
      why: 'It returns the previous value and stores the new one: the idiom for "steal the pointer and reset the source" in one expression.' },

    { sec: 'returning', q: 'What happens in `Counter get() { return member_; }` when `member_` is a data member?',
      opts: ['It is moved automatically', 'It is copied: a member is never moved implicitly', 'It is elided', 'It does not compile'], a: 1,
      why: 'Implicit move and elision only apply to local variables and parameters. A member must be moved explicitly with `std::move`, if the object is meant to give it up.' },

    { sec: 'returning', q: 'In C++17, how many copies or moves does `Counter c = Counter();` perform?',
      opts: ['One copy', 'One move', 'None: guaranteed copy elision constructs it in place', 'It depends on compiler flags'], a: 2,
      why: 'Since C++17, initializing from a prvalue of the same type constructs the object directly in its final location. No copy or move constructor is even needed.' },

    { sec: 'traps', q: 'A constructor `Person(std::string n) : name_(std::move(n))` is called with an lvalue string. What does it cost?',
      opts: ['Nothing', 'One copy (into the parameter) and one move (into the member)', 'Two copies', 'One move only'], a: 1,
      why: 'The lvalue is copied into the by-value parameter, then moved into the member. An rvalue argument costs just the move.' },

    { sec: 'traps', q: 'Which statement about `emplace_back` is true?',
      opts: ['It never constructs anything', 'It constructs the element in place from its arguments, saving a temporary', 'It always avoids reallocation', 'It only works for `int`'], a: 1,
      why: '`emplace_back(args...)` forwards the arguments to the element\'s constructor inside the container\'s storage. Reallocation still happens when the capacity is exceeded.' }
  ]
};
