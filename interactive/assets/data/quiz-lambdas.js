/* Quiz questions for the 'lambdas' topic. Loaded by 15-lambdas-quiz.html. */
CT.quizData.lambdas = {
  id: 'lambdas',
  questions: [
    { sec: 'captures', q: 'What does this print?',
      code: String.raw`
int x = 1;
auto byVal = [x]  { return x; };
auto byRef = [&x] { return x; };
x = 2;
std::cout << byVal() << byRef();`,
      opts: ['11', '12', '21', '22'], a: 1,
      why: 'The by-value capture is a snapshot taken when the lambda was created (1). The by-reference capture reads the live variable (2).' },

    { sec: 'advanced', q: 'How do you move a `std::unique_ptr` into a lambda (C++14)?',
      opts: ['`[p]`: capture by value', '`[p = std::move(p)]`: an init-capture', '`[&p]`: capture by reference', 'It is not possible: lambdas cannot hold move-only objects'], a: 1,
      why: 'A unique_ptr cannot be copied, so `[p]` does not compile. An init-capture creates the lambda\'s own member initialised with `std::move(p)`. A lambda that owns a unique_ptr is itself move-only.' },

    { sec: 'anatomy', q: 'What does the compiler generate for a lambda expression?',
      opts: ['A plain function pointer that points to the body', 'An unnamed class with a call operator and one member per capture', 'A std::function object that holds the body of the lambda', 'A preprocessor macro that is expanded at the call site'], a: 1,
      why: 'Every lambda has its own closure type: captures become members and the body becomes `operator()`. That is why calls can be inlined.' },

    { sec: 'anatomy', q: 'Which lambda converts to a plain function pointer?',
      opts: ['`[](int a) { return a * 2; }`', '`[factor](int a) { return a * factor; }`', '`[&](int a) { return a * k; }`', 'None: lambdas never convert'], a: 0,
      why: 'Only a lambda with no captures has a conversion to a function pointer, because it needs no state to call.' },

    { sec: 'captures', q: 'What is printed?',
      code: String.raw`
int n = 5;
auto f = [n]() mutable { return ++n; };
std::cout << f() << f() << n;`,
      opts: ['675', '677', '666', '565'], a: 0,
      why: '`f` has its own copy of `n`, so `++n` returns 6 then 7. The outer `n` is never touched and stays 5.' },

    { sec: 'lifetime', q: 'Which lambda is safe to return from a function that has a local `int x`?',
      opts: ['`[&x] { return x; }`', '`[x] { return x; }`', '`[&] { return x; }`', 'All of them'], a: 1,
      why: 'Capturing by value copies `x` into the lambda. The reference captures would dangle once the function returns.' },

    { sec: 'lifetime', q: 'In a member function, what does the capture `[=]` capture (and why is relying on it deprecated in C++20)?',
      opts: ['A copy of the whole object, so it is always safe to keep around later', 'The this pointer (not the object), so it dangles if the object dies', 'No members: [=] captures only local variables', 'A reference to a private copy of the whole object that it holds'], a: 1,
      why: '`[=]` implicitly captures `this` by pointer. C++20 deprecates that: write `[=, this]` to be explicit, or `[*this]` to copy the object.' },

    { sec: 'advanced', q: 'What does `mutable` allow on a lambda?',
      opts: ['Modifying variables that were captured by reference', 'Modifying the lambda\'s own by-value copies of captures', 'Capturing types that cannot be copied, such as unique_ptr', 'Calling the lambda from several threads safely at once'], a: 1,
      why: 'By-value captures are `const` inside the call operator unless the lambda is `mutable`. The changes affect the lambda\'s copy, not the original.' },

    { sec: 'advanced', q: 'What do three successive calls of `[n = 0]() mutable { return ++n; }` return (the same lambda object)?',
      opts: ['0 0 0', '1 2 3', '1 1 1', 'It does not compile'], a: 1,
      why: 'The init-capture creates a member `n` initialized to 0 once; `mutable` lets each call increment it, so the state persists between calls.' },

    { sec: 'advanced', q: 'What makes `[](const auto& a, const auto& b) { return a < b; }` a generic lambda?',
      opts: ['The const qualifiers on the parameters', 'The auto parameters make operator() a template', 'The empty capture list at the start', 'auto parameters are invalid in lambdas'], a: 1,
      why: 'A C++14 generic lambda has a templated call operator, so it works for any pair of types that support `<`.' },

    { sec: 'captures', q: 'What is the size of a lambda with no captures on a typical compiler?',
      opts: ['0 bytes', '1 byte', '8 bytes, like a function pointer', 'It depends on the size of its body'], a: 1,
      why: 'An empty class still has a size of at least 1 byte. A capture adds a member, so a lambda capturing one `int` is 4 bytes. The body is code, not data.' },

    { sec: 'lifetime', q: 'A lambda captures a local `x` by reference and is passed to a thread that runs after the function has returned. What is the problem?',
      opts: ['Nothing: a reference capture keeps x alive', 'The reference dangles: x was destroyed on return', 'The lambda is copied again for every call made', 'The thread cannot call a lambda with captures'], a: 1,
      why: 'A reference capture does not extend the lifetime of the variable. After the function returns, the lambda reads destroyed memory. Capture by value when a lambda outlives its scope.' },

    { sec: 'uses', q: 'Which call sorts the strings in `w` by length, shortest first?',
      opts: ['std::sort(w.begin(), w.end(), [](const std::string& a, const std::string& b) { return a.size() < b.size(); });', 'std::sort(w.begin(), w.end(), [](const std::string& a, const std::string& b) { return a.size() > b.size(); });', 'std::sort(w.begin(), w.end(), [](const std::string& a) { return a.size() < 3; });', 'std::sort(w.begin(), w.end(), [&w](const std::string& a, const std::string& b) { return a < w; });'], a: 0,
      why: 'A comparator returns true when its first argument goes before the second. `a.size() < b.size()` puts shorter strings first; `>` would put longer ones first.' }
  ]
};
