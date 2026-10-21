/* Quiz questions for the 'patterns' topic. Loaded by 06-design-patterns-quiz.html. */
CT.quizData.patterns = {
  id: 'patterns',
  questions: [
    { sec: 's2', q: 'What is the intent of the Singleton pattern?',
      opts: ['Create objects without naming their class', 'Guarantee a class has exactly one instance and provide global access to it', 'Notify many objects of a change', 'Swap algorithms at runtime'], a: 1,
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
      opts: ['It is not safe', 'Since C++11, initialization of a function-local static is guaranteed to happen exactly once, even under concurrent calls', 'Because the constructor is private', 'Because references are atomic'], a: 1,
      why: 'The standard requires "magic statics": other threads wait until initialization completes. Using the object afterwards still needs its own synchronization if it has mutable shared state.' },

    { sec: 's2', q: 'Which is a genuine criticism of the Singleton pattern?',
      opts: ['It is slow', 'It is global state that hides dependencies and makes unit testing hard', 'It cannot be used with threads', 'It requires virtual functions'], a: 1,
      why: 'Any code can reach a Singleton, so dependencies are invisible, and tests cannot easily substitute a fake. Passing a reference (dependency injection) avoids both problems.' },

    { sec: 's2', q: 'Why does a Singleton delete its copy constructor and copy assignment operator?',
      opts: ['To save memory', 'So no second instance can be created by copying', 'To make it thread-safe', 'Because singletons cannot be moved'], a: 1,
      why: 'Otherwise `Logger c = Logger::instance();` would silently create a second object and break the "exactly one" guarantee.' },

    { sec: 's3', q: 'What is a good return type for a Factory function that creates polymorphic objects?',
      opts: ['A raw owning pointer `Shape*`', '`std::unique_ptr<Shape>`', 'A `Shape` by value', 'A `void*`'], a: 1,
      why: '`unique_ptr` makes ownership explicit, prevents leaks, and avoids slicing (returning by value would slice). It can be converted to `shared_ptr` if needed.' },

    { sec: 's3', q: 'What must the abstract base class of objects created by a factory have?',
      opts: ['A static member', 'A virtual destructor, because objects are deleted through base pointers', 'A copy constructor', 'No data members'], a: 1,
      why: 'Without a virtual destructor, deleting a derived object through a base pointer is undefined behavior.' },

    { sec: 's4', q: 'What is the Strategy pattern for?',
      opts: ['Guaranteeing one instance', 'Defining interchangeable algorithms that can be selected at runtime without changing the code that uses them', 'Observing state changes', 'Hiding implementation in a pointer'], a: 1,
      why: 'The client holds a strategy through an interface (or a callable) and delegates the varying part to it, e.g. sorting order or pricing rules.' },

    { sec: 's4', q: 'In modern C++, what can often replace a whole Strategy class hierarchy?',
      opts: ['A macro', 'A `std::function` or lambda (or a template parameter)', 'A global variable', 'A union'], a: 1,
      why: 'A strategy is just "a callable with a signature". `std::function<double(double)>` gives runtime flexibility; a template parameter gives zero overhead at compile time.' },

    { sec: 's4', q: 'What is the key difference between Strategy and State?',
      opts: ['There is none', 'With Strategy the client picks the algorithm; with State the object changes its own behaviour as its internal state changes, and transitions are driven by the states', 'State uses templates, Strategy does not', 'Strategy is behavioural, State is creational'], a: 1,
      why: 'Both delegate to a swappable object. The intent differs: external choice of algorithm versus internal, self-driven behaviour changes.' },

    { sec: 's5', q: 'What problem does the Observer pattern solve?',
      opts: ['Creating objects of different types', 'Automatically notifying dependents when a subject changes without the subject knowing who they are', 'Adapting an interface', 'Controlling access to an object'], a: 1,
      why: 'It decouples the subject from its observers: the subject only knows the `Observer` interface and a list of subscribers.' },

    { sec: 's5', q: 'An observer is destroyed but the subject still holds a raw pointer to it. What happens on the next notification?',
      opts: ['The notification is skipped safely', 'Undefined behavior: the subject calls a method on a destroyed object', 'The subject removes it automatically', 'A compile error'], a: 1,
      why: 'This is the classic dangling-observer bug. Detach in the observer\'s destructor (RAII), or store `std::weak_ptr<Observer>` and skip expired ones.' },

    { sec: 's5', q: 'Why does `Subject::set` iterate over a copy of the observer list when notifying?',
      opts: ['It is faster', 'An observer may detach itself (or attach another) during `update()`, which would invalidate iterators of the original vector', 'The list is const', 'To keep the notification order sorted'], a: 1,
      why: 'Modifying a `std::vector` while looping over it invalidates iterators. A copy makes the loop safe against re-entrant attach/detach.' },

    { sec: 's6', q: 'What problem does the State pattern remove?',
      opts: ['Memory leaks', 'Large if/switch chains on a state variable repeated across every method', 'Slow compile times', 'Thread contention'], a: 1,
      why: 'Putting each state\'s behaviour behind its own type (or table entry) makes transitions explicit and keeps methods free of state checks.' },

    { sec: 's7', q: '`std::stack` is implemented on top of `std::deque` by default, exposing only push/pop/top. Which pattern is this?',
      opts: ['Singleton', 'Adapter', 'Observer', 'Factory'], a: 1,
      why: 'An adapter wraps one interface (deque) to present the interface clients expect (a stack). `queue` and `priority_queue` work the same way.' },

    { sec: 's7', q: 'How do Adapter and Decorator differ?',
      opts: ['They are the same pattern', 'Adapter changes an object\'s interface to match another; Decorator keeps the interface and adds behaviour', 'Decorator is creational', 'Adapter is only for templates'], a: 1,
      why: 'Adapter converts interfaces; Decorator wraps an object with the same interface to add responsibilities (for example buffering or logging).' },

    { sec: 's7', q: 'What does CRTP (`struct Circle : Shape<Circle>`) provide?',
      opts: ['Runtime polymorphism through a vtable', 'Compile-time (static) polymorphism with no virtual call overhead', 'Multiple inheritance', 'Automatic memory management'], a: 1,
      why: 'The base class template knows the derived type and can call its functions through `static_cast`, so the dispatch is resolved at compile time and can be inlined.' },

    { sec: 's7', q: 'Which C++ feature is the modern way to implement the Visitor pattern for a closed set of types?',
      opts: ['`std::thread`', '`std::variant` together with `std::visit`', '`std::shared_ptr`', 'Macros'], a: 1,
      why: '`std::visit` applies a visitor to whichever alternative the variant currently holds, and the compiler checks that every alternative is handled.' },

    { sec: 's8', q: 'What does the Open/Closed Principle say?',
      opts: ['Classes must be open source', 'Code should be open for extension but closed for modification', 'All functions must be inline', 'Objects must be closed after use'], a: 1,
      why: 'You should add new behaviour (a new strategy, a new registered shape) without editing existing, tested code. Strategy, Decorator and factory registries support this.' },

    { sec: 's8', q: 'The "D" in SOLID, Dependency Inversion, recommends that...',
      opts: ['High-level code depends on abstractions and dependencies are injected, instead of high-level code depending on concrete classes', 'Every class has a global instance', 'Derived classes must override all functions', 'Dependencies are always copied'], a: 0,
      why: 'Code should depend on interfaces, with concrete implementations supplied from outside (constructor injection). It is the usual alternative to reaching for a Singleton.' }
  ]
};
