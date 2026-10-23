/* Quiz questions for the 'moves' topic. Loaded by 13-move-semantics-quiz.html. */
CT.quizData.moves = {
  id: 'moves',
  questions: [
    { sec: 'copy-move', q: 'What does `std::move(x)` do?',
      opts: ['Moves x\'s data to a new memory location and clears the old one for good', 'Casts x to an rvalue reference so a move can be chosen; it moves nothing', 'Deletes x so that it can no longer be used by the rest of the program', 'Copies x into a temporary and then clears the original object afterwards'], a: 1,
      why: '`std::move` is just `static_cast<T&&>(x)`. The actual transfer happens in whichever move constructor or move assignment operator is then selected.' },

    { sec: 'copy-move', q: 'After `std::vector<int> b = std::move(a);`, what may you safely do with `a`?',
      opts: ['Read a[0]', 'Call a.size() and trust it equals the old size', 'Destroy it or assign a new value to it', 'Not even destroy it, since the program is undefined'], a: 2,
      why: 'A moved-from object is valid but unspecified: it is safe to destroy or assign to, but you should not rely on its contents.' },

    { sec: 'returning', q: 'Why is `return std::move(local);` usually a mistake?',
      opts: ['It does not compile for local variables of class type', 'It prevents copy elision (RVO), so it can be slower', 'It makes the returned result const, which blocks later moves', 'It causes a memory leak of the local variable\'s storage'], a: 1,
      why: 'Returning a local by value already lets the compiler elide the copy or implicitly move it. Wrapping it in `std::move` changes the expression type and blocks elision.' },

    { sec: 'writing', q: 'Why mark a move constructor `noexcept`?',
      opts: ['It makes the move operation itself run faster than before', 'std::vector reallocates by moving only if the move cannot throw', 'The language requires it on every move constructor you write', 'It prevents the object from being copied by mistake'], a: 1,
      why: 'To keep the strong exception guarantee, `vector` uses `std::move_if_noexcept` during reallocation: a throwing move would leave elements in a half-moved state, so it copies instead.' },

    { sec: 'traps', q: 'What does the second line do?',
      code: String.raw`
const std::string a = "text";
std::string b = std::move(a);`,
      opts: ['Moves the contents of a into b, leaving a empty afterwards', 'Copies a: a const rvalue cannot bind to the move constructor', 'It does not compile, because a const object cannot be moved', 'Undefined behavior, because a is left in an empty state'], a: 1,
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
      opts: ['h(const std::string&), because s is an lvalue inside g', 'h(std::string&&), because s has an rvalue reference type', 'Neither: the call is ambiguous between the two', 'The code does not compile'], a: 0,
      why: 'A name is always an lvalue, whatever its declared type. To pass it on as an rvalue you need `std::move(s)`.' },

    { sec: 'values', q: 'What can bind to an rvalue reference parameter `T&&`?',
      opts: ['Any lvalue of type T', 'Only rvalues: temporaries and std::move(x)', 'Only const objects of type T', 'Anything, including lvalues, just like const T&'], a: 1,
      why: 'An rvalue reference binds to rvalues, which is how overload resolution sends temporaries to move operations. An lvalue needs `std::move` first.' },

    { sec: 'writing', q: 'What is wrong with this move constructor?',
      code: String.raw`
Buffer(Buffer&& o) noexcept : data_(o.data_), n_(o.n_) {}`,
      opts: ['It is a correct and complete move constructor', 'The source still owns data_, so both free it (double delete)', 'noexcept is not allowed on move constructors in C++', 'It must take a const Buffer& to count as a move constructor'], a: 1,
      why: 'A move constructor must leave the source empty (`o.data_ = nullptr`), or use `std::exchange`. Otherwise both destructors release the same block.' },

    { sec: 'writing', q: 'What does `std::exchange(o.data_, nullptr)` do?',
      opts: ['Returns nullptr and leaves o.data_ unchanged', 'Returns the old o.data_ and sets it to nullptr', 'Swaps o.data_ with a null pointer permanently', 'Deletes the object o.data_ points to'], a: 1,
      why: 'It returns the previous value and stores the new one: the idiom for "steal the pointer and reset the source" in one expression.' },

    { sec: 'returning', q: 'What happens in `Counter get() { return member_; }` when `member_` is a data member?',
      opts: ['It is moved automatically, since the function ends', 'It is copied: a member is never moved implicitly', 'It is elided, like a returned local', 'It does not compile, because member_ is not a local'], a: 1,
      why: 'Implicit move and elision only apply to local variables and parameters. A member must be moved explicitly with `std::move`, if the object is meant to give it up.' },

    { sec: 'returning', q: 'In C++17, how many copies or moves does `Counter c = Counter();` perform?',
      opts: ['One copy, then the temporary is destroyed', 'One move, then the temporary is destroyed', 'None: guaranteed copy elision builds it in place', 'It depends on the optimization level you compile with'], a: 2,
      why: 'Since C++17, initializing from a prvalue of the same type constructs the object directly in its final location. No copy or move constructor is even needed.' },

    { sec: 'traps', q: 'A constructor `Person(std::string n) : name_(std::move(n))` is called with an lvalue string. What does it cost?',
      opts: ['The string is only referenced, so there is no copy', 'One copy (into the parameter) and one move (into the member)', 'Two copies, one into the parameter and one into the member', 'One move only, because the constructor calls std::move'], a: 1,
      why: 'The lvalue is copied into the by-value parameter, then moved into the member. An rvalue argument costs just the move.' },

    { sec: 'traps', q: 'Which statement about `emplace_back` is true?',
      opts: ['It does not construct anything itself, it only inserts', 'It constructs the element in place from its arguments', 'It avoids reallocation of the underlying vector', 'It only works for built-in types such as int and double'], a: 1,
      why: '`emplace_back(args...)` forwards the arguments to the element\'s constructor inside the container\'s storage. Reallocation still happens when the capacity is exceeded.' }
  ]
};
