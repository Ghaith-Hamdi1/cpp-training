/* Quiz questions for the 'oop' topic. Loaded by 02-oop-quiz.html. */
CT.quizData.oop = {
  id: 'oop',
  questions: [
    { q: 'What is the default access of members in a `struct` versus a `class`?',
      opts: ['Both private', 'Both public', '`struct` public, `class` private', '`struct` private, `class` public'], a: 2,
      why: 'That is the only difference between them (it also applies to the default inheritance access).' },

    { q: 'What does this print?',
      code: String.raw`
struct A { A(){ std::cout << "A"; } ~A(){ std::cout << "~A"; } };
struct B : A { B(){ std::cout << "B"; } ~B(){ std::cout << "~B"; } };
int main() { B b; }`,
      opts: ['AB~B~A', 'BA~A~B', 'AB~A~B', 'B~BA~A'], a: 0,
      why: 'Construction goes base first, then derived. Destruction is the exact reverse: derived first, then base.' },

    { q: 'In what order are the members of a class initialized?',
      code: String.raw`
class C {
    int a_;
    int b_;
public:
    C() : b_(1), a_(2) {}
};`,
      opts: ['In the order of the initializer list: b_ then a_', 'In declaration order: a_ then b_', 'Alphabetical order', 'Unspecified'], a: 1,
      why: 'Members are always initialized in the order they are declared in the class, whatever order the list is written in. Compilers warn with `-Wreorder`.' },

    { q: 'Why is a member initializer list preferred over assigning in the constructor body?',
      opts: ['It is required for all members', 'It initializes members directly (no default-construct-then-assign), and is the only way to set const and reference members', 'It makes the constructor `explicit`', 'It runs before the base class constructor'], a: 1,
      why: 'Assigning in the body first default-constructs the member and then overwrites it. `const` and reference members cannot be assigned at all, so they must be in the list.' },

    { q: 'What goes wrong with this class when a copy is made?',
      code: String.raw`
class Buffer {
    int* data_;
public:
    Buffer(int v) : data_(new int(v)) {}
    ~Buffer() { delete data_; }
};
Buffer a(1);
Buffer b = a;`,
      opts: ['Nothing, it works', 'It does not compile', 'The generated copy copies the pointer, so both destructors delete the same memory (double free)', 'b becomes a reference to a'], a: 2,
      why: 'The compiler-generated copy constructor is a shallow copy. This is why the Rule of Three exists: define a deep-copy constructor and assignment, or use `std::unique_ptr` / `std::vector` (Rule of Zero).' },

    { q: 'The Rule of Three says that if a class needs a custom destructor, it probably also needs a custom...',
      opts: ['Default constructor and move constructor', 'Copy constructor and copy assignment operator', 'Virtual function table', 'Static member'], a: 1,
      why: 'Destructor, copy constructor and copy assignment form the three. The Rule of Five adds the move constructor and move assignment. The Rule of Zero avoids all of them.' },

    { q: 'What does this print?',
      code: String.raw`
struct Base { void f() { std::cout << "Base"; } };
struct Derived : Base { void f() { std::cout << "Derived"; } };
Base* p = new Derived;
p->f();`,
      opts: ['Derived', 'Base', 'Compile error', 'Undefined behavior'], a: 1,
      why: '`f` is not virtual, so the call is bound at compile time from the pointer\'s static type (`Base*`). Making `Base::f` virtual would print "Derived". (The `Derived` is also leaked here.)' },

    { q: 'Why should the destructor of a polymorphic base class be virtual?',
      opts: ['So the class can be copied', 'So deleting a derived object through a base pointer runs the derived destructor', 'To make the class abstract', 'To allow multiple inheritance'], a: 1,
      why: 'Without it, `delete basePtr` only runs the base destructor, which is undefined behavior and leaks whatever the derived part owns.' },

    { q: 'What is object slicing?',
      code: String.raw`
Dog d;
Animal a = d;`,
      opts: ['Splitting a class into two files', 'Copying a derived object into a base value, losing the derived part', 'Deleting part of an array', 'Casting a base pointer to derived'], a: 1,
      why: '`a` is a plain `Animal`, so only the base subobject is copied and virtual behaviour is lost. Use references or pointers for polymorphic objects.' },

    { q: 'What happens here?',
      code: String.raw`
struct Shape { virtual double area() const = 0; };
Shape s;`,
      opts: ['It compiles; area() returns 0', 'It does not compile: Shape is abstract', 'It compiles but crashes when area() is called', 'It compiles with a warning'], a: 1,
      why: 'A class with a pure virtual function (`= 0`) is abstract and cannot be instantiated.' },

    { q: 'What is the main benefit of the `override` keyword?',
      opts: ['It makes the call faster', 'The compiler verifies the function really overrides a base virtual, catching signature typos', 'It makes the function virtual', 'It prevents further overriding'], a: 1,
      why: 'If you write `void area()` where the base has `area() const`, you create a new function silently. With `override` that is a compile error. (`final` is what prevents further overriding.)' },

    { q: 'What does this print?',
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

    { q: 'Why must `operator<<` for printing a class be a non-member function?',
      opts: ['Member operators cannot take references', 'The left operand is `std::ostream`, which you cannot add a member function to', 'It would be slower as a member', 'Non-members are required for every operator'], a: 1,
      why: 'A member operator has `*this` (your class) as its left operand. For `std::cout << obj` the left operand is the stream, so the function must be a free function (often a friend).' },

    { q: 'What does a `const` member function promise?',
      code: String.raw`
class P {
    int x_;
public:
    int get() const { return x_; }
};`,
      opts: ['That it returns a constant', 'That it will not modify the object, so it can be called on const objects', 'That it runs at compile time', 'That it cannot be overridden'], a: 1,
      why: 'Inside a const member function `this` is a pointer to const, so members cannot be modified (unless marked `mutable`). Const objects can only call const member functions.' },

    { q: 'What is a `static` data member?',
      opts: ['A member stored once per object', 'A single member shared by all objects of the class', 'A member that cannot change', 'A member stored on the stack'], a: 1,
      why: 'There is exactly one copy for the whole class. It must be defined once outside the class (or declared `inline static` in C++17).' },

    { q: 'Which is the better design for a `Stack` class that needs a growable container?',
      opts: ['`class Stack : public std::vector<int>`', 'Hold a `std::vector<int>` as a private member (composition)', 'Inherit privately from `int`', 'Use a global vector'], a: 1,
      why: 'A Stack is not truly a vector (it should not expose `insert` or `[]`), so public inheritance violates is-a. Composition hides the implementation and exposes only stack operations.' },

    { q: 'What does `explicit` do on this constructor?',
      code: String.raw`
struct Meters {
    explicit Meters(double v);
};
void walk(Meters m);
walk(5.0);`,
      opts: ['Nothing', 'It makes `walk(5.0)` a compile error: no implicit double-to-Meters conversion', 'It makes the constructor run faster', 'It makes `walk` virtual'], a: 1,
      why: '`explicit` forbids implicit conversions through that constructor. You must write `walk(Meters{5.0})`, which avoids accidental conversions.' },

    { q: 'What does `NoCopy(const NoCopy&) = delete;` do?',
      opts: ['Deletes the object', 'Makes the class non-copyable: any attempt to copy it is a compile error', 'Calls the destructor', 'Makes the class abstract'], a: 1,
      why: '`= delete` removes the function. It is the modern way to forbid copying (for example for classes owning a unique resource).' },

    { q: 'What is the difference between overloading and overriding?',
      opts: ['They are the same thing', 'Overloading: same name, different parameters, resolved at compile time. Overriding: derived class replaces a base virtual function, resolved at runtime', 'Overloading needs inheritance; overriding does not', 'Overriding is only for constructors'], a: 1,
      why: 'Overload resolution looks at argument types at compile time. Overriding relies on virtual dispatch using the dynamic type of the object.' },

    { q: 'Which statement about `protected` members is correct?',
      opts: ['Accessible by anyone', 'Accessible inside the class and its derived classes, but not from outside code', 'Accessible only inside the class', 'Accessible only from friends'], a: 1,
      why: '`protected` sits between public and private: derived classes can use the member, outside code cannot.' }
  ]
};
