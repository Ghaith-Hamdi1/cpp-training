/* Quiz questions for the 'elision' topic. Loaded by 35-elision-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.elision = {
  id: 'elision',
  questions: [
    { sec: 'whenmove', q: 'Why is `return std::move(local);` usually a mistake?',
      opts: ['It blocks NRVO and forces a move', 'It copies the object once more than needed', 'It does not compile with local variables', 'It returns a dangling reference to the local'], a: 1,
      why: 'Returning a local by value already lets the compiler elide the copy or implicitly move it. Wrapping it in `std::move` changes the expression type and blocks elision.' },

    { sec: 'whenmove', q: 'What happens in `Counter get() { return member_; }` when `member_` is a data member?',
      opts: ['It is moved automatically, since the function ends', 'It is copied: a member is never moved implicitly', 'It is elided, like a returned local', 'It does not compile, because member_ is not a local'], a: 1,
      why: 'Implicit move and elision only apply to local variables and parameters. A member must be moved explicitly with `std::move`, if the object is meant to give it up.' },

    { sec: 'whenmove', q: 'In C++17, how many copies or moves does `Counter c = Counter();` perform?',
      opts: ['One copy, then the temporary is destroyed', 'One move, then the temporary is destroyed', 'None: guaranteed copy elision builds it in place', 'It depends on the optimization level you compile with'], a: 2,
      why: 'Since C++17, initializing from a prvalue of the same type constructs the object directly in its final location. No copy or move constructor is even needed.' },

    { sec: 'rvo', q: 'How many copies and moves does `Buffer b = make();` perform when make is `return Buffer(1000);`?',
      opts: ['None: built in place', 'Exactly one move into the variable b', 'Exactly one copy into the variable b', 'One copy followed by one more move'], a: 0,
      why: 'Since C++17 returning a prvalue constructs the object directly in the caller.' },

    { sec: 'rvo', q: 'What is NRVO?',
      opts: ['Elision of a returned named local, which is optional', 'A required optimization that applies to temporaries', 'A special way of returning references from functions', 'A compiler warning about expensive return statements'], a: 0,
      why: 'Named return value optimization is optional but done by all major compilers in simple cases.' },

    { sec: 'guaranteed', q: 'In C++17, which type can be returned by value as `return T();`?',
      opts: ['One with deleted copy and move', 'Only a type that has a move constructor', 'Only a type that can be copied', 'Only a trivial type with no members'], a: 0,
      why: 'Guaranteed elision means no copy or move constructor is needed for a prvalue.' },

    { sec: 'whenmove', q: 'Why is `return std::move(local);` worse than `return local;`?',
      opts: ['It blocks NRVO and forces a move', 'It copies the object', 'It does not compile', 'It returns a dangling reference'], a: 0,
      why: 'The returned expression is no longer the plain local name, so elision is not allowed.' },

    { sec: 'whenmove', q: 'When is `return std::move(obj.member);` correct?',
      opts: ['When obj outlives the call and you take its member', 'Never, because a return never needs std::move', 'When the member happens to be declared const', 'Only inside constructors and destructors'], a: 0,
      why: 'A member is never moved implicitly, so the explicit move avoids a copy.' },

    { sec: 'whenmove', q: 'What does the compiler do when a by-value parameter is returned by name?',
      opts: ['Moves it', 'Elides it', 'Copies it', 'Rejects it'], a: 0,
      why: 'Returning a parameter by name moves it automatically but does not elide it.' },

    { sec: 'rvo', q: 'Which warning flags `return std::move(local);`?',
      opts: ['`-Wpessimizing-move`', '`-Wunused-variable`', '`-Wshadow-all-names`', '`-Wconversion-extra`'], a: 0,
      why: 'It is part of -Wall in GCC and Clang.' },

    { sec: 'limits', q: 'A function has `C x, y; if (b) return x; return y;`. What happens to the returned object?',
      opts: ['It is moved, not copied', 'It is always elided', 'It is copied', 'It does not compile'], a: 0,
      why: 'With two candidates NRVO usually does not apply, but a returned local is moved.' }
  ]
};
