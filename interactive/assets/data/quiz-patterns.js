/* Quiz questions for the 'patterns' topic. Loaded by 06-design-patterns-quiz.html. */
CT.quizData.patterns = {
  id: 'patterns',
  questions: [
    { sec: 's2', q: 'What is the intent of the Singleton pattern?',
      opts: ['Create objects without naming their concrete class', 'Guarantee exactly one instance, with global access to it', 'Notify many objects when one object changes', 'Swap algorithms at run time without touching the client'], a: 1,
      why: 'Singleton restricts instantiation to one object (private constructor, deleted copies) and offers a single access point.' },

    { sec: 's2', q: 'What does this print?',
      code: String.raw`
class Logger {
public:
    static Logger& instance() { static Logger inst; return inst; }
    Logger(const Logger&) = delete;
private:
    Logger() = default;
};
Logger& a = Logger::instance();
Logger& b = Logger::instance();
std::cout << (&a == &b);`,
      opts: ['0', '1', 'Compile error', 'Undefined behavior'], a: 1,
      why: 'Both calls return a reference to the same function-local static, so the addresses are equal and the program prints 1.' },

    { sec: 's2', q: 'Why is the Meyers Singleton (function-local static) safe when several threads call `instance()` at the same time?',
      opts: ['It is not safe: you must wrap instance() in your own mutex each time', 'Since C++11 a function-local static is initialised exactly once, thread-safely', 'Because the constructor is private, no other thread can reach the object', 'Because references are atomic in C++, so the returned reference is safe'], a: 1,
      why: 'The standard requires "magic statics": other threads wait until initialization completes. Using the object afterwards still needs its own synchronization if it has mutable shared state.' },

    { sec: 's2', q: 'Which is a genuine criticism of the Singleton pattern?',
      opts: ['It is too slow for real programs, because of the global lookup', 'It is global state that hides dependencies and makes tests hard', 'It cannot be used from several threads, even with a mutex', 'It requires virtual functions in the class to work'], a: 1,
      why: 'Any code can reach a Singleton, so dependencies are invisible, and tests cannot easily substitute a fake. Passing a reference (dependency injection) avoids both problems.' },

    { sec: 's2', q: 'Why does a Singleton delete its copy constructor and copy assignment operator?',
      opts: ['To save memory on each instance of the class', 'So no second instance can be created by copying the first', 'To make the single instance thread-safe on its own', 'Because singletons cannot be moved in C++'], a: 1,
      why: 'Otherwise `Logger c = Logger::instance();` would silently create a second object and break the "exactly one" guarantee.' },

    { sec: 's3', q: 'What is a good return type for a Factory function that creates polymorphic objects?',
      opts: ['A raw owning pointer `Shape*`', '`std::unique_ptr<Shape>`', 'A `Shape` by value', 'A `void*`'], a: 1,
      why: '`unique_ptr` makes ownership explicit, prevents leaks, and avoids slicing (returning by value would slice). It can be converted to `shared_ptr` if needed.' },

    { sec: 's3', q: 'What must the abstract base class of objects created by a factory have?',
      opts: ['A static member that holds the number of instances created so far', 'A virtual destructor, since objects are deleted through base pointers', 'A public copy constructor so that objects can be cloned easily', 'No data members, only pure virtual functions in the class'], a: 1,
      why: 'Without a virtual destructor, deleting a derived object through a base pointer is undefined behavior.' },

    { sec: 's4', q: 'What is the Strategy pattern for?',
      opts: ['Guaranteeing that one instance of a class exists at run time', 'Interchangeable algorithms chosen at run time without changing the user', 'Observing and reacting to state changes in other objects automatically', 'Hiding the implementation of a class behind a pointer to a private type'], a: 1,
      why: 'The client holds a strategy through an interface (or a callable) and delegates the varying part to it, e.g. sorting order or pricing rules.' },

    { sec: 's4', q: 'In modern C++, what can often replace a whole Strategy class hierarchy?',
      opts: ['A preprocessor macro that is defined once for each algorithm', 'A std::function or lambda (or a template parameter)', 'A global variable that selects which algorithm is used', 'A union that holds all the algorithm types at once'], a: 1,
      why: 'A strategy is just "a callable with a signature". `std::function<double(double)>` gives runtime flexibility; a template parameter gives zero overhead at compile time.' },

    { sec: 's4', q: 'What is the key difference between Strategy and State?',
      opts: ['They are the same pattern with two names, used in different books', 'Strategy: the client picks the algorithm. State: the object switches itself', 'State uses templates while Strategy does not, which is the whole difference', 'Strategy is a behavioural pattern, while State is a creational pattern'], a: 1,
      why: 'Both delegate to a swappable object. The intent differs: external choice of algorithm versus internal, self-driven behaviour changes.' },

    { sec: 's5', q: 'What problem does the Observer pattern solve?',
      opts: ['Creating objects of several different types from one place', 'Notifying dependents of a change without the subject knowing them', 'Adapting one interface so that it matches another interface', 'Controlling access to an object through a stand-in proxy object'], a: 1,
      why: 'It decouples the subject from its observers: the subject only knows the `Observer` interface and a list of subscribers.' },

    { sec: 's5', q: 'An observer is destroyed but the subject still holds a raw pointer to it. What happens on the next notification?',
      opts: ['The notification is skipped safely and the loop carries on', 'Undefined behavior: the subject calls a method on a destroyed object', 'The subject removes the observer from its list automatically', 'A compile error is reported at the notification call'], a: 1,
      why: 'This is the classic dangling-observer bug. Detach in the observer\'s destructor (RAII), or store `std::weak_ptr<Observer>` and skip expired ones.' },

    { sec: 's5', q: 'Why does `Subject::set` iterate over a copy of the observer list when notifying?',
      opts: ['Copying the list is faster than iterating over the original list', 'An observer may detach or attach during update(), invalidating iterators', 'The list is const while notifying, so it must be copied first', 'To keep the notification order sorted by observer address'], a: 1,
      why: 'Modifying a `std::vector` while looping over it invalidates iterators. A copy makes the loop safe against re-entrant attach/detach.' },

    { sec: 's6', q: 'What problem does the State pattern remove?',
      opts: ['Memory leaks that are caused by shared mutable state between objects', 'Long if/switch chains on a state variable, repeated in every method', 'Slow compile times in large projects with many header files included', 'Thread contention on shared objects in concurrent code that runs in parallel'], a: 1,
      why: 'Putting each state\'s behaviour behind its own type (or table entry) makes transitions explicit and keeps methods free of state checks.' },

    { sec: 's7', q: '`std::stack` is implemented on top of `std::deque` by default, exposing only push/pop/top. Which pattern is this?',
      opts: ['Singleton', 'Adapter', 'Observer', 'Factory'], a: 1,
      why: 'An adapter wraps one interface (deque) to present the interface clients expect (a stack). `queue` and `priority_queue` work the same way.' },

    { sec: 's7', q: 'How do Adapter and Decorator differ?',
      opts: ['They are the same pattern under two different names in books', 'Adapter changes the interface; Decorator keeps it and adds behaviour', 'Decorator is a creational pattern, while Adapter is structural', 'Adapter is available when you use class templates'], a: 1,
      why: 'Adapter converts interfaces; Decorator wraps an object with the same interface to add responsibilities (for example buffering or logging).' },

    { sec: 's7', q: 'What does CRTP (`struct Circle : Shape<Circle>`) provide?',
      opts: ['Run-time polymorphism through a vtable and virtual calls', 'Compile-time polymorphism with no virtual call overhead', 'Multiple inheritance of several unrelated base classes', 'Automatic memory management for the derived types'], a: 1,
      why: 'The base class template knows the derived type and can call its functions through `static_cast`, so the dispatch is resolved at compile time and can be inlined.' },

    { sec: 's7', q: 'Which C++ feature is the modern way to implement the Visitor pattern for a closed set of types?',
      opts: ['std::thread with a worker per type', 'std::variant together with std::visit', 'std::shared_ptr to a base class', 'Preprocessor macros per type'], a: 1,
      why: '`std::visit` applies a visitor to whichever alternative the variant currently holds, and the compiler checks that every alternative is handled.' },

    { sec: 's8', q: 'What does the Open/Closed Principle say?',
      opts: ['Classes must be published as open source before they are used', 'Code should be open for extension but closed for modification', 'All functions must be declared inline when they are small', 'Objects must be closed after use, in the same way as files'], a: 1,
      why: 'You should add new behaviour (a new strategy, a new registered shape) without editing existing, tested code. Strategy, Decorator and factory registries support this.' },

    { sec: 's8', q: 'The "D" in SOLID, Dependency Inversion, recommends that...',
      opts: ['High-level code depends on abstractions and gets its dependencies injected', 'Each class has one global instance that others reach', 'Derived classes must override all virtual functions they inherit', 'Dependencies are copied into the class by value'], a: 0,
      why: 'Code should depend on interfaces, with concrete implementations supplied from outside (constructor injection). It is the usual alternative to reaching for a Singleton.' }
  ]
};
