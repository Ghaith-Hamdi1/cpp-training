/* Quiz questions for the 'writemoves' topic. Loaded by 34-writemoves-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.writemoves = {
  id: 'writemoves',
  questions: [
    { sec: 'ctor', q: 'Why mark a move constructor `noexcept`?',
      opts: ['It makes the move operation itself run faster than before', 'std::vector reallocates by moving only if the move cannot throw', 'The language requires it on every move constructor you write', 'It prevents the object from being copied by mistake'], a: 1,
      why: 'To keep the strong exception guarantee, `vector` uses `std::move_if_noexcept` during reallocation: a throwing move would leave elements in a half-moved state, so it copies instead.' },

    { sec: 'ctor', q: 'What is wrong with this move constructor?',
      code: String.raw`
Buffer(Buffer&& o) noexcept : data_(o.data_), n_(o.n_) {}`,
      opts: ['It is a correct and complete move constructor', 'The source still owns data_, so both free it (double delete)', 'noexcept is not allowed on move constructors in C++', 'It must take a const Buffer& to count as a move constructor'], a: 1,
      why: 'A move constructor must leave the source empty (`o.data_ = nullptr`), or use `std::exchange`. Otherwise both destructors release the same block.' },

    { sec: 'ctor', q: 'What does `std::exchange(o.data_, nullptr)` do?',
      opts: ['The old value of o.data_', 'nullptr, the new value it was given', 'A pointer to the object o itself', 'Nothing, because it returns void'], a: 1,
      why: 'It returns the previous value and stores the new one: the idiom for "steal the pointer and reset the source" in one expression.' },

    { sec: 'ctor', q: 'What does `std::exchange(o.data_, nullptr)` return?',
      opts: ['The old value of o.data_', 'nullptr', 'A pointer to o', 'Nothing'], a: 0,
      why: 'exchange stores the new value and returns the old one: the idiom for steal and reset.' },

    { sec: 'ctor', q: 'Why must a move constructor reset the source pointer to nullptr?',
      opts: ['So the source\'s destructor does not free the stolen buffer', 'So the source object can never be assigned to again', 'To make the stolen buffer smaller in memory', 'It does not need to reset the source at all'], a: 0,
      why: 'Otherwise both objects would free the same memory.' },

    { sec: 'assign', q: 'What does copy-and-swap assignment take as its parameter?',
      opts: ['The other object by value', 'The other object by const reference', 'The other object by rvalue reference', 'A raw pointer to the other object'], a: 0,
      why: 'By value, so an lvalue is copied and an rvalue is moved, then the contents are swapped in.' },

    { sec: 'noexcept', q: 'A `vector` of `T` grows. T\'s move constructor is not noexcept but T is copyable. What does the vector do?',
      opts: ['Copies the existing elements', 'Moves them anyway, ignoring the risk', 'Throws an exception to the caller', 'Keeps the old buffer and refuses to grow'], a: 0,
      why: 'To keep the strong guarantee, std::vector moves only if the move cannot throw.' },

    { sec: 'noexcept', q: 'When can you safely mark a move operation `noexcept`?',
      opts: ['When it only swaps or resets pointers', 'Always, because moves are trivially safe', 'Never, because moves can always throw', 'Only when the object is declared const'], a: 0,
      why: 'Moves that just transfer ownership of a pointer do not throw.' },

    { sec: 'zero', q: 'A class has members `std::string`, `std::vector<int>` and `std::unique_ptr<X>`. How many special member functions should you write?',
      opts: ['None: the Rule of Zero', 'Two of them, the copy pair', 'All five, to be on the safe side', 'Only the destructor of the class'], a: 0,
      why: 'Each member manages itself, so the compiler-generated operations are correct.' },

    { sec: 'zero', q: 'What does the Rule of Five add to the Rule of Three?',
      opts: ['Move constructor and move assignment', 'A second destructor for the move case', 'A swap function and a hash function', 'Constructors that allow implicit conversion'], a: 0,
      why: 'Destructor, copy constructor and copy assignment, plus the two move operations.' },

    { sec: 'testing', q: 'What does `static_assert(std::is_nothrow_move_constructible_v<Buffer>)` check?',
      opts: ['That the move constructor is noexcept, so vector will use it', 'That Buffer is trivially copyable', 'That Buffer has no destructor', 'That Buffer can be copied'], a: 0,
      why: 'It fails to compile if you forget noexcept on the move constructor.' }
  ]
};
