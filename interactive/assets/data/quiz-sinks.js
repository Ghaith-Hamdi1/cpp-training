/* Quiz questions for the 'sinks' topic. Loaded by 36-sinks-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.sinks = {
  id: 'sinks',
  questions: [
    { sec: 'traps', q: 'What does the second line do?',
      code: String.raw`
const std::string a = "text";
std::string b = std::move(a);`,
      opts: ['Moves the contents of a into b, leaving a empty afterwards', 'Copies a: a const rvalue cannot bind to the move constructor', 'It does not compile, because a const object cannot be moved', 'Undefined behavior, because a is left in an empty state'], a: 1,
      why: '`std::move` only casts to an rvalue, and a `const` rvalue cannot bind to `string(string&&)`, so overload resolution silently picks the copy constructor. Never return `const` values by value for the same reason.' },

    { sec: 'traps', q: 'A constructor `Person(std::string n) : name_(std::move(n))` is called with an lvalue string. What does it cost?',
      opts: ['The string is only referenced, so there is no copy', 'One copy (into the parameter) and one move (into the member)', 'Two copies, one into the parameter and one into the member', 'One move only, because the constructor calls std::move'], a: 1,
      why: 'The lvalue is copied into the by-value parameter, then moved into the member. An rvalue argument costs just the move.' },

    { sec: 'traps', q: 'Which statement about `emplace_back` is true?',
      opts: ['It does not construct anything itself, it only inserts', 'It constructs the element in place from its arguments', 'It avoids reallocation of the underlying vector', 'It only works for built-in types such as int and double'], a: 1,
      why: '`emplace_back(args...)` forwards the arguments to the element\'s constructor inside the container\'s storage. Reallocation still happens when the capacity is exceeded.' },

    { sec: 'sink', q: 'A constructor takes `std::string n` by value and does `name_(std::move(n))`. How many copies and moves for a call with an lvalue?',
      opts: ['One copy and one move', 'Two copies of the string', 'Two moves and no copy at all', 'No copies and exactly one move'], a: 0,
      why: 'The lvalue is copied into the parameter, then moved into the member.' },

    { sec: 'sink', q: 'How many copies and moves does the same constructor make for a temporary argument?',
      opts: ['Two moves, no copy', 'One copy, one move', 'One move', 'Two copies'], a: 0,
      why: 'The temporary is moved into the parameter and then into the member.' },

    { sec: 'choose', q: 'Which design is fastest for storing an argument, at the price of two functions?',
      opts: ['Overloads `const T&` and `T&&`', 'By value and then move into the member', 'Only a `const T&` parameter', 'Only a raw pointer parameter'], a: 0,
      why: 'Overloads copy an lvalue once and move an rvalue once, with no extra move.' },

    { sec: 'choose', q: 'Why is a by-value parameter a poor choice for a setter?',
      opts: ['Assignment into the member could reuse storage', 'Setters are not allowed to take any values', 'A by-value parameter cannot be moved at all', 'It is always slower than passing a pointer'], a: 0,
      why: 'Constructing the parameter costs an allocation that an in-place assignment may avoid.' },

    { sec: 'emplace', q: 'Which call constructs the element directly inside the vector, with no temporary?',
      opts: ['`v.emplace_back(args...)`', '`v.push_back(T(args...))`', '`v.insert(v.end(), T(args...))`', '`v.assign(1, T(args...))`'], a: 0,
      why: 'emplace_back forwards the arguments to the element\'s constructor.' },

    { sec: 'emplace', q: 'What does `v.push_back(std::move(x))` do?',
      opts: ['Moves x into the vector', 'Copies x into the vector instead', 'Empties the vector it was called on', 'Constructs x in place inside the vector'], a: 0,
      why: 'The rvalue overload moves the object into the new element.' },

    { sec: 'traps', q: 'Which is NOT a way a move silently becomes a copy?',
      opts: ['Moving a vector that has a large capacity', 'Calling std::move on a const object', 'Declaring a destructor in the class', 'Using a type that has no move operations'], a: 0,
      why: 'Vectors move fine. The other three all select the copy operation.' },

    { sec: 'moveonly', q: 'How does a caller pass a `std::unique_ptr<int> p` to `void take(std::unique_ptr<int>)`?',
      opts: ['`take(std::move(p));`', '`take(p);`', '`take(&p);`', '`take(*p);`'], a: 0,
      why: 'A unique_ptr cannot be copied, so the caller moves it in.' }
  ]
};
