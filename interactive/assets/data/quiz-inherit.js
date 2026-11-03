/* Quiz questions for the 'inherit' topic. Loaded by 27-inherit-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.inherit = {
  id: 'inherit',
  questions: [
    { sec: 'virtual', q: 'What does this print?',
      code: String.raw`
struct Base { void f() { std::cout << "Base"; } };
struct Derived : Base { void f() { std::cout << "Derived"; } };
Base* p = new Derived;
p->f();`,
      opts: ['Derived', 'Base', 'Compile error', 'Undefined behavior'], a: 1,
      why: '`f` is not virtual, so the call is bound at compile time from the pointer\'s static type (`Base*`). Making `Base::f` virtual would print "Derived". (The `Derived` is also leaked here.)' },

    { sec: 'virtual', q: 'Why should the destructor of a polymorphic base class be virtual?',
      opts: ['So the class can be copied safely between objects of the same type', 'So delete through a base pointer also runs the derived destructor', 'So the class becomes abstract and can no longer be instantiated directly', 'So the class can take part in multiple inheritance without ambiguity'], a: 1,
      why: 'Without it, `delete basePtr` only runs the base destructor, which is undefined behavior and leaks whatever the derived part owns.' },

    { sec: 'inheritance', q: 'What is object slicing?',
      code: String.raw`
Dog d;
Animal a = d;`,
      opts: ['Splitting a class definition across a header and a source file', 'Copying a derived object into a base value, losing the derived part', 'Deleting only part of a dynamically allocated array of objects', 'Casting a base pointer down to a derived pointer without a check'], a: 1,
      why: '`a` is a plain `Animal`, so only the base subobject is copied and virtual behaviour is lost. Use references or pointers for polymorphic objects.' },

    { sec: 'abstract', q: 'What happens here?',
      code: String.raw`
struct Shape { virtual double area() const = 0; };
Shape s;`,
      opts: ['It compiles; area() returns 0', 'It does not compile: Shape is abstract', 'It compiles but crashes when area() is called', 'It compiles with a warning'], a: 1,
      why: 'A class with a pure virtual function (`= 0`) is abstract and cannot be instantiated.' },

    { sec: 'virtual', q: 'What is the main benefit of the `override` keyword?',
      opts: ['It makes the call faster by skipping the vtable lookup at run time', 'The compiler checks that the function really overrides a base virtual', 'It turns an ordinary member function into a virtual one in the base', 'It prevents any further overriding of the function in derived classes'], a: 1,
      why: 'If you write `void area()` where the base has `area() const`, you create a new function silently. With `override` that is a compile error. (`final` is what prevents further overriding.)' },

    { sec: 'virtual', q: 'What does this print?',
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

    { sec: 'design', q: 'Which is the better design for a `Stack` class that needs a growable container?',
      opts: ['class Stack : public std::vector<int>, exposing every vector method', 'Hold a std::vector<int> as a private member (composition)', 'Derive publicly from std::stack<int> and add the extra methods you need', 'Use one global vector shared by every Stack object in the program'], a: 1,
      why: 'A Stack is not truly a vector (it should not expose `insert` or `[]`), so public inheritance violates is-a. Composition hides the implementation and exposes only stack operations.' },

    { sec: 'virtual', q: 'What is the difference between overloading and overriding?',
      opts: ['They are two names for the same mechanism, used in different languages', 'Overloading picks by parameters at compile time; overriding replaces a base virtual at run time', 'Overloading needs inheritance and virtual functions; overriding works on any free function', 'Overriding is chosen at compile time by the static type; overloading is chosen at run time'], a: 1,
      why: 'Overload resolution looks at argument types at compile time. Overriding relies on virtual dispatch using the dynamic type of the object.' },

    { sec: 'multiple', q: 'Why can `Reader*` and `Writer*` obtained from the same `File` object (which derives from both) hold different addresses?',
      opts: ['It is a compiler bug in how the second base class is handled by the optimizer', 'Each base sits at its own offset, so converting to the second base adjusts the pointer', 'Pointers to interfaces are always shifted by the size of a vptr', 'Because File is not polymorphic, so the addresses are arbitrary and unrelated'], a: 1,
      why: 'The object is the bases laid out one after another. A conversion to the second base must point at that subobject, which is why C casts and `reinterpret_cast` are wrong for it.' },

    { sec: 'multiple', q: 'What is the sensible use of multiple inheritance in C++?',
      opts: ['Inheriting data members from several concrete classes at once', 'Implementing several pure interfaces (abstract classes with no data)', 'Avoiding virtual functions by merging several base classes into one', 'Preventing other classes from deriving from yours in the future'], a: 1,
      why: 'Interfaces without data cause no duplicated members and no diamond problem.' },

    { sec: 'multiple', q: 'Two base classes both declare a member function `f`. What happens on `obj.f()`?',
      opts: ['The first base class listed wins and its f is called', 'It is ambiguous and does not compile; qualify it as obj.A::f()', 'The last base class listed wins and its f is called', 'It calls the function of both bases, in order of declaration'], a: 1,
      why: 'Name lookup finds two candidates in different bases, which is ambiguous.' },

    { sec: 'diamond', q: 'What is the diamond problem?',
      opts: ['A class that inherits from two unrelated base classes at once', 'One base reached through two paths: duplicated members, ambiguous access', 'A virtual function that has two different overriders in a hierarchy', 'Two header files that include each other in a circle'], a: 1,
      why: '`Diamond` derives from `Left` and `Right`, each of which derives from `Base`. Without virtual inheritance `Diamond` contains two `Base` subobjects.' },

    { sec: 'diamond', q: 'How does virtual inheritance solve it, and who initializes the shared base?',
      opts: ['It copies the base twice; each middle class initializes its own copy', 'All paths share one base; the most derived class initializes it first', 'It removes the base class, so nobody needs to initialize it', 'It makes the base abstract; derived classes provide the data'], a: 1,
      why: 'The middle classes declare `: virtual Base`. The most derived class constructs the single `Base` first (compiled order: VBase VLeft VRight VDiamond).' },

    { sec: 'diamond', q: 'What does virtual inheritance cost?',
      opts: ['It is free at run time, like ordinary inheritance', 'Extra pointers per object and indirect access to the shared base', 'It makes the derived class non-copyable and non-movable', 'It disables virtual functions in the whole hierarchy'], a: 1,
      why: 'The layout needs a way to find the shared base from each derived part, so objects get bigger and access slower (compiled: 24 bytes versus 8 for the two-int plain diamond).' },

    { sec: 'rtti', q: 'What does `dynamic_cast` require of the source type for a downcast?',
      opts: ['Any class type can be the source of the cast', 'A polymorphic class: at least one virtual function', 'A class template parameter on the source type', 'A public, non-virtual destructor and nothing else'], a: 1,
      why: 'The run-time type information is stored with the vtable, so a class with no virtual function has none.' },

    { sec: 'rtti', q: 'What does `dynamic_cast<Cat&>(*animalPtr)` do when the object is not a `Cat`?',
      opts: ['Returns null', 'Throws `std::bad_cast`', 'Undefined behaviour', 'Returns the object unchanged'], a: 1,
      why: 'A reference cannot be null, so failure is reported with an exception. The pointer form returns `nullptr`.' },

    { sec: 'rtti', q: 'What does `typeid(*p) == typeid(Dog)` compare when `p` is an `Animal*` to a polymorphic object?',
      opts: ['The static type Animal, known at compile time', 'The dynamic type of the object p points to', 'The pointer values stored in p and in a Dog*', 'The expression does not compile for a polymorphic class'], a: 1,
      why: 'For a polymorphic type `typeid` applied to the dereferenced pointer reports the dynamic type. For a non-polymorphic type it is the static type.' },

    { sec: 'private', q: 'What does private inheritance mean?',
      opts: ['Is-a, but hidden from the compiler\'s overload resolution rules', 'Implemented-in-terms-of: Derived* does not convert to Base* outside', 'The base class is not allowed to declare any virtual functions', 'The derived class cannot be copied or moved by other code'], a: 1,
      why: 'Compiled: `Car*` is not convertible to `Engine*` when `Car` inherits `Engine` privately.' },

    { sec: 'private', q: 'When should you prefer composition to private inheritance?',
      opts: ['Almost always: private inheritance is only for overriding a virtual or protected access', 'When reusing code: private inheritance is the better design for reuse', 'Inside class templates that need access to the protected members of the base', 'When the base class is abstract and has no data members of its own'], a: 0,
      why: 'A member object is simpler and does not expose the base to accidental overriding.' }
  ]
};
