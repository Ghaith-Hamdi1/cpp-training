/* Quiz questions for the 'copymove' topic. Loaded by 33-copymove-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.copymove = {
  id: 'copymove',
  questions: [
    { sec: 'stdmove', q: 'What does `std::move(x)` do?',
      opts: ['Moves x\'s data to a new memory location and clears the old one for good', 'Casts x to an rvalue reference so a move can be chosen; it moves nothing', 'Deletes x so that it can no longer be used by the rest of the program', 'Copies x into a temporary and then clears the original object afterwards'], a: 1,
      why: '`std::move` is just `static_cast<T&&>(x)`. The actual transfer happens in whichever move constructor or move assignment operator is then selected.' },

    { sec: 'stdmove', q: 'After `std::vector<int> b = std::move(a);`, what may you safely do with `a`?',
      opts: ['Read a[0]', 'Call a.size() and trust it equals the old size', 'Destroy it or assign a new value to it', 'Not even destroy it, since the program is undefined'], a: 2,
      why: 'A moved-from object is valid but unspecified: it is safe to destroy or assign to, but you should not rely on its contents.' },

    { sec: 'cost', q: 'What does copying a `std::vector<int>` of a million elements do?',
      opts: ['Allocates a new buffer and copies every element', 'Copies only the pointer and the size to the new vector', 'Shares the buffer until one of the vectors is modified', 'Moves the buffer and leaves the source vector empty'], a: 0,
      why: 'A vector copy is deep. A move is the operation that copies only the internals.' },

    { sec: 'cost', q: 'For which type is a move noticeably cheaper than a copy?',
      opts: ['`std::string` holding a long text', '`int`, the plain built-in integer type', 'A struct made of two plain double values', '`bool`, the smallest built-in value type'], a: 0,
      why: 'Types that own memory or other resources gain from a move. For plain data a move is a copy.' },

    { sec: 'stdmove', q: 'What does `std::move(x)` do at run time?',
      opts: ['Nothing', 'Moves the contents of x into a temporary', 'Empties x', 'Calls the move constructor'], a: 0,
      why: 'It only changes the expression\'s category. The move constructor chosen afterwards does the work.' },

    { sec: 'stdmove', q: 'After `std::string t = std::move(s);` what may you do with `s`?',
      opts: ['Destroy it or assign a new value to it', 'Read its old text to check what was moved', 'Rely on its length being 0 afterwards', 'Use it as a key in a map without assigning'], a: 0,
      why: 'A moved-from object is valid but unspecified. Assignment and destruction are always allowed.' },

    { sec: 'movedfrom', q: 'Why is moving inside a loop usually a bug?',
      opts: ['The next iteration sees a moved-from object', 'A move operation can only be performed one time', 'Moves are always slower when they run inside loops', 'It leaks the memory of the container being moved'], a: 0,
      why: 'After the first iteration the variable is moved-from. Move only at the last use.' },

    { sec: 'constmove', q: 'What does `std::string y = std::move(cs);` do when `cs` is `const std::string`?',
      opts: ['Copies', 'Moves, because std::move always moves', 'Does not compile', 'Throws'], a: 0,
      why: 'const T&& cannot bind to T&&, so the copy constructor is selected.' },

    { sec: 'constmove', q: 'Which class suppresses its implicit move operations?',
      opts: ['One with a user-declared destructor', 'One with only std::string members', 'One with a defaulted constructor', 'One that is a template'], a: 0,
      why: 'Declaring a destructor, copy operation or move operation stops the compiler generating moves, so a move becomes a copy.' },

    { sec: 'stdtypes', q: 'What does `auto a2 = std::move(a);` do for a `std::array<Counted, 3> a`?',
      opts: ['Moves each of the three elements one by one', 'Moves nothing: it copies the pointer', 'Copies the array', 'Does not compile'], a: 0,
      why: 'The elements are stored inline, so there is no pointer to steal.' }
  ]
};
