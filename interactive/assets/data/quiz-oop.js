/* Quiz questions for the 'oop' topic. Loaded by 02-oop-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.oop = {
  id: 'oop',
  questions: [
    { sec: 's1', q: 'What is the default access of members in a `struct` versus a `class`?',
      opts: ['Both private, because members default to private', 'Both public, because members default to public', 'struct is public by default, class is private', 'struct is private by default, class is public'], a: 2,
      why: 'That is the only difference between them (it also applies to the default inheritance access).' },

    { sec: 's2', q: 'What does this print?',
      code: String.raw`
struct A { A(){ std::cout << "A"; } ~A(){ std::cout << "~A"; } };
struct B : A { B(){ std::cout << "B"; } ~B(){ std::cout << "~B"; } };
int main() { B b; }`,
      opts: ['AB~B~A', 'BA~A~B', 'AB~A~B', 'B~BA~A'], a: 0,
      why: 'Construction goes base first, then derived. Destruction is the exact reverse: derived first, then base.' },

    { sec: 's2', q: 'In what order are the members of a class initialized?',
      code: String.raw`
class C {
    int a_;
    int b_;
public:
    C() : b_(1), a_(2) {}
};`,
      opts: ['In the order of the initializer list: b_ then a_', 'In declaration order: a_ then b_', 'Alphabetical order', 'Unspecified'], a: 1,
      why: 'Members are always initialized in the order they are declared in the class, whatever order the list is written in. Compilers warn with `-Wreorder`.' },

    { sec: 's2', q: 'Why is a member initializer list preferred over assigning in the constructor body?',
      opts: ['It is required for every member of every class', 'It initializes members directly, and const and reference members need it', 'It makes the constructor explicit, so no implicit conversions happen', 'It runs before the base class constructor, so the base sees valid members'], a: 1,
      why: 'Assigning in the body first default-constructs the member and then overwrites it. `const` and reference members cannot be assigned at all, so they must be in the list.' },

    { sec: 's4', q: 'What does a `const` member function promise?',
      code: String.raw`
class P {
    int x_;
public:
    int get() const { return x_; }
};`,
      opts: ['That it returns a constant value that callers cannot modify', 'That it does not modify the object, so const objects can call it', 'That it is evaluated at compile time, like a constexpr function', 'That derived classes are not allowed to override it later on'], a: 1,
      why: 'Inside a const member function `this` is a pointer to const, so members cannot be modified (unless marked `mutable`). Const objects can only call const member functions.' },

    { sec: 's4', q: 'What is a `static` data member?',
      opts: ['A member stored separately inside every object', 'A single member shared by all objects of the class', 'A member that can never be changed', 'A member that is always stored on the stack'], a: 1,
      why: 'There is exactly one copy for the whole class. It must be defined once outside the class (or declared `inline static` in C++17).' },

    { sec: 's2', q: 'What does `explicit` do on this constructor?',
      code: String.raw`
struct Meters {
    explicit Meters(double v);
};
void walk(Meters m);
walk(5.0);`,
      opts: ['It only documents the intent and does not change behavior', 'walk(5.0) no longer compiles: no implicit conversion from double', 'It makes the constructor run faster by skipping a conversion step', 'It makes walk() a virtual function so derived classes can override it'], a: 1,
      why: '`explicit` forbids implicit conversions through that constructor. You must write `walk(Meters{5.0})`, which avoids accidental conversions.' },

    { sec: 's1', q: 'Which statement about `protected` members is correct?',
      opts: ['Accessible by any code that can see the object, like a public member', 'Accessible inside the class and its derived classes, not from outside', 'Accessible only inside the class itself and not in derived classes', 'Accessible only from friends of the class'], a: 1,
      why: '`protected` sits between public and private: derived classes can use the member, outside code cannot.' },

    { sec: 's1', q: 'What is a class invariant?',
      opts: ['A data member that is declared const and set once in the constructor', 'A rule every valid object satisfies, kept true by constructors and members', 'A member function that cannot be overridden in derived classes', 'A static data member that all objects of the class share'], a: 1,
      why: 'For `BankAccount` it might be "the balance never goes negative". Hiding the representation and checking inputs in the public functions is how a class protects its invariant. If you cannot state one, the type is probably plain data and should be a `struct`.' },

    { sec: 's1', q: 'Where is the code of a member function stored when a program creates 1000 objects of the class?',
      opts: ['Once, shared by all the objects', 'Once in each object, next to its data', 'Once in each object, but only if it is virtual', 'On the heap, one copy per object'], a: 0,
      why: 'Objects carry only their data. A member function exists once; the hidden `this` pointer tells it which object to work on.' },

    { sec: 's1', q: 'What is `this` inside a member function?',
      opts: ['A pointer to the object the function was called on', 'A copy of the object that the function was called on', 'A reference to the class itself, not to an object', 'A pointer to the first data member of the class'], a: 0,
      why: '`this` is the address of the current object. In a `const` member function it has type `const T*`.' },

    { sec: 's4', q: 'What is shared by all objects of a class?',
      opts: ['A static data member, which exists once for the whole class', 'Every data member, because members belong to the class', 'Only the private data members of the class', 'Only the members that are declared const'], a: 0,
      why: 'A `static` member belongs to the class, not to an object, so there is a single copy no matter how many objects exist.' },

    { sec: 's2', q: 'When does the destructor of a local object run?',
      opts: ['At the closing brace of its scope, even if the scope is left by an exception', 'Only when you call delete on the object explicitly', 'When the program ends, after main has returned', 'When the object is last used, before the closing brace'], a: 0,
      why: 'Local objects are destroyed when their scope ends, whatever way it ends. That guarantee is what RAII builds on.' }
  ]
};
