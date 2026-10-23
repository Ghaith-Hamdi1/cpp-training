/* Quiz questions for the 'oop' topic. Loaded by 02-oop-quiz.html. */
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

    { sec: 's3', q: 'What goes wrong with this class when a copy is made?',
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

    { sec: 's3', q: 'The Rule of Three says that if a class needs a custom destructor, it probably also needs a custom...',
      opts: ['Default constructor and move constructor', 'Copy constructor and copy assignment operator', 'Virtual function table and a virtual destructor', 'Static member and a friend declaration'], a: 1,
      why: 'Destructor, copy constructor and copy assignment form the three. The Rule of Five adds the move constructor and move assignment. The Rule of Zero avoids all of them.' },

    { sec: 's6', q: 'What does this print?',
      code: String.raw`
struct Base { void f() { std::cout << "Base"; } };
struct Derived : Base { void f() { std::cout << "Derived"; } };
Base* p = new Derived;
p->f();`,
      opts: ['Derived', 'Base', 'Compile error', 'Undefined behavior'], a: 1,
      why: '`f` is not virtual, so the call is bound at compile time from the pointer\'s static type (`Base*`). Making `Base::f` virtual would print "Derived". (The `Derived` is also leaked here.)' },

    { sec: 's6', q: 'Why should the destructor of a polymorphic base class be virtual?',
      opts: ['So the class can be copied safely between objects of the same type', 'So delete through a base pointer also runs the derived destructor', 'So the class becomes abstract and can no longer be instantiated directly', 'So the class can take part in multiple inheritance without ambiguity'], a: 1,
      why: 'Without it, `delete basePtr` only runs the base destructor, which is undefined behavior and leaks whatever the derived part owns.' },

    { sec: 's5', q: 'What is object slicing?',
      code: String.raw`
Dog d;
Animal a = d;`,
      opts: ['Splitting a class definition across a header and a source file', 'Copying a derived object into a base value, losing the derived part', 'Deleting only part of a dynamically allocated array of objects', 'Casting a base pointer down to a derived pointer without a check'], a: 1,
      why: '`a` is a plain `Animal`, so only the base subobject is copied and virtual behaviour is lost. Use references or pointers for polymorphic objects.' },

    { sec: 's7', q: 'What happens here?',
      code: String.raw`
struct Shape { virtual double area() const = 0; };
Shape s;`,
      opts: ['It compiles; area() returns 0', 'It does not compile: Shape is abstract', 'It compiles but crashes when area() is called', 'It compiles with a warning'], a: 1,
      why: 'A class with a pure virtual function (`= 0`) is abstract and cannot be instantiated.' },

    { sec: 's6', q: 'What is the main benefit of the `override` keyword?',
      opts: ['It makes the call faster by skipping the vtable lookup at run time', 'The compiler checks that the function really overrides a base virtual', 'It turns an ordinary member function into a virtual one in the base', 'It prevents any further overriding of the function in derived classes'], a: 1,
      why: 'If you write `void area()` where the base has `area() const`, you create a new function silently. With `override` that is a compile error. (`final` is what prevents further overriding.)' },

    { sec: 's6', q: 'What does this print?',
      code: String.raw`
struct Base {
    Base() { init(); }
    virtual void init() { std::cout << "Base"; }
};
struct Derived : Base {
    void init() override { std::cout << "Derived"; }
};
Derived d;`,
      opts: ['Derived', 'Base', 'BaseDerived', 'Undefined behavior'], a: 1,
      why: 'While the `Base` constructor runs, the object\'s dynamic type is `Base`, so the virtual call resolves to `Base::init`. The derived part does not exist yet. Never rely on virtual calls in constructors or destructors.' },

    { sec: 's8', q: 'Why must `operator<<` for printing a class be a non-member function?',
      opts: ['Member operators cannot take references as parameters in C++', 'The left operand is std::ostream, which you cannot add members to', 'A member would be slower than a free function for stream output', 'Most operators in C++ must be declared as non-member functions'], a: 1,
      why: 'A member operator has `*this` (your class) as its left operand. For `std::cout << obj` the left operand is the stream, so the function must be a free function (often a friend).' },

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

    { sec: 's9', q: 'Which is the better design for a `Stack` class that needs a growable container?',
      opts: ['class Stack : public std::vector<int>, exposing every vector method', 'Hold a std::vector<int> as a private member (composition)', 'Derive publicly from std::stack<int> and add the extra methods you need', 'Use one global vector shared by every Stack object in the program'], a: 1,
      why: 'A Stack is not truly a vector (it should not expose `insert` or `[]`), so public inheritance violates is-a. Composition hides the implementation and exposes only stack operations.' },

    { sec: 's2', q: 'What does `explicit` do on this constructor?',
      code: String.raw`
struct Meters {
    explicit Meters(double v);
};
void walk(Meters m);
walk(5.0);`,
      opts: ['It only documents the intent and does not change behavior', 'walk(5.0) no longer compiles: no implicit conversion from double', 'It makes the constructor run faster by skipping a conversion step', 'It makes walk() a virtual function so derived classes can override it'], a: 1,
      why: '`explicit` forbids implicit conversions through that constructor. You must write `walk(Meters{5.0})`, which avoids accidental conversions.' },

    { sec: 's3', q: 'What does `NoCopy(const NoCopy&) = delete;` do?',
      opts: ['Deletes the object when it goes out of scope, instead of the destructor', 'Makes the class non-copyable: copying is a compile error', 'Calls the destructor on every copy attempt and then aborts the copy', 'Makes the class abstract so that it can no longer be created'], a: 1,
      why: '`= delete` removes the function. It is the modern way to forbid copying (for example for classes owning a unique resource).' },

    { sec: 's6', q: 'What is the difference between overloading and overriding?',
      opts: ['They are two names for the same mechanism, used in different languages', 'Overloading picks by parameters at compile time; overriding replaces a base virtual at run time', 'Overloading needs inheritance and virtual functions; overriding works on any free function', 'Overriding is chosen at compile time by the static type; overloading is chosen at run time'], a: 1,
      why: 'Overload resolution looks at argument types at compile time. Overriding relies on virtual dispatch using the dynamic type of the object.' },

    { sec: 's1', q: 'Which statement about `protected` members is correct?',
      opts: ['Accessible by any code that can see the object, like a public member', 'Accessible inside the class and its derived classes, not from outside', 'Accessible only inside the class itself and not in derived classes', 'Accessible only from friends of the class'], a: 1,
      why: '`protected` sits between public and private: derived classes can use the member, outside code cannot.' },

    { sec: 's3', q: 'What happens on the last line?',
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

    { sec: 's1', q: 'What is a class invariant?',
      opts: ['A data member that is declared const and set once in the constructor', 'A rule every valid object satisfies, kept true by constructors and members', 'A member function that cannot be overridden in derived classes', 'A static data member that all objects of the class share'], a: 1,
      why: 'For `BankAccount` it might be "the balance never goes negative". Hiding the representation and checking inputs in the public functions is how a class protects its invariant. If you cannot state one, the type is probably plain data and should be a `struct`.' },

    { sec: 's8', q: 'What does declaring `explicit operator bool() const` allow?',
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
      why: 'The by-value parameter is the copy. If the copy throws, nothing has changed; then a non-throwing swap commits.' }
  ]
};
