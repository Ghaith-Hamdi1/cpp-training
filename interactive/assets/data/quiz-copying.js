/* Quiz questions for the 'copying' topic. Loaded by 26-copying-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.copying = {
  id: 'copying',
  questions: [
    { sec: 'copy', q: 'What goes wrong with this class when a copy is made?',
      code: String.raw`
class Buffer {
    int* data_;
public:
    Buffer(int v) : data_(new int(v)) {}
    ~Buffer() { delete data_; }
};
Buffer a(1);
Buffer b = a;`,
      opts: ['The compiler-generated copy is correct for classes with pointers', 'It does not compile, because raw pointers cannot be copied by default', 'Both objects point at the same memory, so both destructors delete it', 'b becomes a reference to a, so changes to one show in the other'], a: 2,
      why: 'The compiler-generated copy constructor is a shallow copy. This is why the Rule of Three exists: define a deep-copy constructor and assignment, or use `std::unique_ptr` / `std::vector` (Rule of Zero).' },

    { sec: 'copy', q: 'The Rule of Three says that if a class needs a custom destructor, it probably also needs a custom...',
      opts: ['Default constructor and move constructor', 'Copy constructor and copy assignment operator', 'Virtual function table and a virtual destructor', 'Static member and a friend declaration'], a: 1,
      why: 'Destructor, copy constructor and copy assignment form the three. The Rule of Five adds the move constructor and move assignment. The Rule of Zero avoids all of them.' },

    { sec: 'operators', q: 'Why must `operator<<` for printing a class be a non-member function?',
      opts: ['Member operators cannot take references as parameters in C++', 'The left operand is std::ostream, which you cannot add members to', 'A member would be slower than a free function for stream output', 'Most operators in C++ must be declared as non-member functions'], a: 1,
      why: 'A member operator has `*this` (your class) as its left operand. For `std::cout << obj` the left operand is the stream, so the function must be a free function (often a friend).' },

    { sec: 'copy', q: 'What does `NoCopy(const NoCopy&) = delete;` do?',
      opts: ['Deletes the object when it goes out of scope, instead of the destructor', 'Makes the class non-copyable: copying is a compile error', 'Calls the destructor on every copy attempt and then aborts the copy', 'Makes the class abstract so that it can no longer be created'], a: 1,
      why: '`= delete` removes the function. It is the modern way to forbid copying (for example for classes owning a unique resource).' },

    { sec: 'copy', q: 'What happens on the last line?',
      code: String.raw`
class Widget {
public:
    ~Widget() { std::cout << "bye"; }
    // no other special member functions declared
};
Widget a;
Widget b = std::move(a);`,
      opts: ['It moves: the compiler generates a move constructor automatically', 'It copies: the declared destructor suppresses the move operations', 'It does not compile, because the move operations are deleted', 'Undefined behavior, because the source object is left empty'], a: 1,
      why: 'A user-declared destructor (or copy operation) stops the compiler generating move operations, and an rvalue then falls back to the copy constructor. It compiles and works, just more slowly. Ask for the defaults with `= default` if the class should stay movable.' },

    { sec: 'operators', q: 'What does declaring `explicit operator bool() const` allow?',
      opts: ['Conversion operators cannot be declared explicit in C++', 'Use in conditions like if (obj), but not int n = obj; or obj + 1', 'Implicit conversion to bool everywhere, arithmetic included', 'Converting a bool value into an object of the class type'], a: 1,
      why: 'An explicit conversion only applies where a bool is clearly wanted (if, while, !, &&, ||). Without explicit, a class convertible to bool also silently converts to int and takes part in arithmetic.' },

    { sec: 'conversions', q: 'What does `explicit` on a single-argument constructor prevent?',
      opts: ['Copying the object from another object of the same class type', 'Implicit conversions from the argument type, such as Feet f = 3.0;', 'Inheritance from the class by other, completely unrelated types', 'Use of the class as an argument of any class template'], a: 1,
      why: 'The conversion must be written out (`Feet(3.0)`). Mark single-argument constructors `explicit` by default.' },

    { sec: 'conversions', q: 'Why is `explicit operator bool()` better than a plain `operator bool()`?',
      opts: ['It is faster, because the conversion is resolved at compile time', 'It works in if and while but not in arithmetic or other comparisons', 'It allows more conversions than a plain operator bool does', 'It avoids creating a vtable for the class, saving some memory'], a: 1,
      why: 'A non-explicit `operator bool` converts to `int` and so lets `h + 1` or `h == 2` compile.' },

    { sec: 'conversions', q: 'What is the main benefit of copy-and-swap for `operator=`?',
      opts: ['It is the fastest possible implementation of copy assignment in C++', 'The copy happens before *this changes: strong guarantee, safe self-assignment', 'It avoids calling the copy constructor entirely when assigning', 'It makes the class final so it cannot be derived from later'], a: 1,
      why: 'The by-value parameter is the copy. If the copy throws, nothing has changed; then a non-throwing swap commits.' },

    { sec: 'copy', q: 'What does the compiler-generated copy constructor do with a raw `int*` member?',
      opts: ['Copies the pointer value, so both objects point to the same int', 'Allocates a new int and copies the value into it', 'Sets the pointer in the new object to nullptr', 'Does not compile until you write a copy constructor'], a: 0,
      why: 'The default copy is member-wise and shallow: the address is copied, not the thing it points to. Two destructors then free the same block.' },

    { sec: 'operators', q: 'Why can `operator<<` for printing a class not be a member function?',
      opts: ['Its left operand is the stream, not an object of your class', 'Member functions cannot take a reference parameter', 'Operators that return a reference must be free functions', 'The standard forbids member operators on templates'], a: 0,
      why: 'A member operator has `*this` as its left operand. For `os << v` the left operand is the `ostream`, so the function must be a non-member.' },

    { sec: 'copy', q: 'A class holds a `std::vector<int>` and a `std::string` and nothing else. How many of the five special member functions should you write?',
      opts: ['None: the Rule of Zero', 'Only the destructor', 'All five, to be safe', 'The copy pair, to make copies deep'], a: 0,
      why: 'Both members already copy and move correctly and free their memory, so the compiler-generated versions are right. Write nothing.' }
  ]
};
