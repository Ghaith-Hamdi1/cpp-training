/* Quiz questions for the 'objmodel' topic. Loaded by 19-object-model-quiz.html. */
CT.quizData.objmodel = {
  id: 'objmodel',
  questions: [
    { sec: 'multiple', q: 'Why can `Reader*` and `Writer*` obtained from the same `File` object (which derives from both) hold different addresses?',
      opts: ['It is a compiler bug', 'Each base subobject sits at its own offset with its own vptr, and converting to the second base adjusts the pointer', 'Pointers to interfaces are always shifted', 'Because `File` is not polymorphic'], a: 1,
      why: 'The object is the bases laid out one after another. A conversion to the second base must point at that subobject, which is why C casts and `reinterpret_cast` are wrong for it.' },

    { sec: 'multiple', q: 'What is the sensible use of multiple inheritance in C++?',
      opts: ['Inheriting data from several concrete classes', 'Implementing several pure interfaces (abstract classes without data)', 'Avoiding virtual functions', 'Making a class final'], a: 1,
      why: 'Interfaces without data cause no duplicated members and no diamond problem.' },

    { sec: 'multiple', q: 'Two base classes both declare a member function `f`. What happens on `obj.f()`?',
      opts: ['The first base wins', 'It is ambiguous and does not compile; qualify it (`obj.A::f()`) or override `f` in the derived class', 'The last base wins', 'It calls both'], a: 1,
      why: 'Name lookup finds two candidates in different bases, which is ambiguous.' },

    { sec: 'diamond', q: 'What is the diamond problem?',
      opts: ['A class that inherits from two unrelated base classes', 'A class inherits the same base through two paths, so the base is duplicated and member access is ambiguous', 'A virtual function with two overriders', 'A circular include'], a: 1,
      why: '`Diamond` derives from `Left` and `Right`, each of which derives from `Base`. Without virtual inheritance `Diamond` contains two `Base` subobjects.' },

    { sec: 'diamond', q: 'How does virtual inheritance solve it, and who initializes the shared base?',
      opts: ['It copies the base twice; each middle class initializes it', 'All paths share one base subobject; the most derived class initializes it, before the other bases', 'It removes the base; nobody initializes it', 'It makes the base abstract'], a: 1,
      why: 'The middle classes declare `: virtual Base`. The most derived class constructs the single `Base` first (compiled order: VBase VLeft VRight VDiamond).' },

    { sec: 'diamond', q: 'What does virtual inheritance cost?',
      opts: ['Nothing', 'Extra pointers per object and indirect access to the shared base', 'It makes the class non-copyable', 'It disables virtual functions'], a: 1,
      why: 'The layout needs a way to find the shared base from each derived part, so objects get bigger and access slower (compiled: 24 bytes versus 8 for the two-int plain diamond).' },

    { sec: 'rtti', q: 'What does `dynamic_cast` require of the source type for a downcast?',
      opts: ['Nothing', 'A polymorphic class: at least one virtual function', 'A template parameter', 'A public destructor only'], a: 1,
      why: 'The run-time type information is stored with the vtable, so a class with no virtual function has none.' },

    { sec: 'rtti', q: 'What does `dynamic_cast<Cat&>(*animalPtr)` do when the object is not a `Cat`?',
      opts: ['Returns null', 'Throws `std::bad_cast`', 'Undefined behaviour', 'Returns the object unchanged'], a: 1,
      why: 'A reference cannot be null, so failure is reported with an exception. The pointer form returns `nullptr`.' },

    { sec: 'rtti', q: 'What does `typeid(*p) == typeid(Dog)` compare when `p` is an `Animal*` to a polymorphic object?',
      opts: ['The static type `Animal`', 'The dynamic type of the object `p` points to', 'The pointer values', 'Nothing: it does not compile'], a: 1,
      why: 'For a polymorphic type `typeid` applied to the dereferenced pointer reports the dynamic type. For a non-polymorphic type it is the static type.' },

    { sec: 'private', q: 'What does private inheritance mean?',
      opts: ['Is-a, but hidden from the compiler', 'Implemented-in-terms-of: the base is an implementation detail and a `Derived*` does not convert to `Base*` outside the class', 'The base cannot have virtual functions', 'The derived class cannot be copied'], a: 1,
      why: 'Compiled: `Car*` is not convertible to `Engine*` when `Car` inherits `Engine` privately.' },

    { sec: 'private', q: 'When should you prefer composition to private inheritance?',
      opts: ['Almost always: use private inheritance only to override a virtual, reach a protected member, or get the empty base optimisation', 'Never', 'Only for templates', 'Only for abstract classes'], a: 0,
      why: 'A member object is simpler and does not expose the base to accidental overriding.' },

    { sec: 'conversions', q: 'What does `explicit` on a single-argument constructor prevent?',
      opts: ['Copying the object', 'Implicit conversions from the argument type, such as `Feet f = 3.0;` or passing `3.0` where `Feet` is expected', 'Inheritance from the class', 'Use in templates'], a: 1,
      why: 'The conversion must be written out (`Feet(3.0)`). Mark single-argument constructors `explicit` by default.' },

    { sec: 'conversions', q: 'Why is `explicit operator bool()` better than a plain `operator bool()`?',
      opts: ['It is faster', 'It works in `if` and `while` but not silently in arithmetic or comparisons with other types', 'It allows more conversions', 'It avoids a vtable'], a: 1,
      why: 'A non-explicit `operator bool` converts to `int` and so lets `h + 1` or `h == 2` compile.' },

    { sec: 'conversions', q: 'What is the main benefit of copy-and-swap for `operator=`?',
      opts: ['It is the fastest possible implementation', 'The copy is made before `*this` is modified, so it gives the strong exception guarantee and safe self-assignment with one function', 'It avoids the copy constructor', 'It makes the class final'], a: 1,
      why: 'The by-value parameter is the copy. If the copy throws, nothing has changed; then a non-throwing swap commits.' }
  ]
};
