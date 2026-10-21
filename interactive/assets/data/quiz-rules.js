/* Quiz questions for the 'rules' topic. Loaded by 10-coding-rules-quiz.html. */
CT.quizData.rules = {
  id: 'rules',
  questions: [
    { sec: 's2', q: 'What is the main goal of coding guidelines such as MISRA or AUTOSAR C++14?',
      opts: ['Make programs run faster', 'Restrict risky or unclear uses of the language so errors are avoided in safety-related code', 'Reduce the number of source files', 'Replace the need for testing'], a: 1,
      why: 'They remove legal-but-dangerous constructs (undefined behaviour, unclear conversions) from critical software. They complement testing; they do not replace it.' },

    { sec: 's2', q: 'AUTOSAR C++14 is based on which earlier standard?',
      opts: ['MISRA C++:2008', 'ISO C++98 only', 'The Linux kernel style guide', 'Google C++ Style Guide'], a: 0,
      why: 'AUTOSAR C++14 updates MISRA C++:2008 for C++14, taking in other leading standards and research.' },

    { sec: 's1', q: 'How do coding guidelines differ from code style?',
      opts: ['They are the same thing', 'Guidelines limit how language features are used to avoid errors; style fixes the form of code such as indentation, braces and naming', 'Style is mandatory, guidelines are optional', 'Guidelines only cover comments'], a: 1,
      why: 'Guidelines are about safety and clarity of language use. Style is about uniform appearance.' },

    { sec: 's4', q: 'How are coding rules usually enforced?',
      opts: ['By reading the code once a year', 'By static analysers (and formatters) run automatically, for example in CI', 'By the linker', 'They cannot be enforced'], a: 1,
      why: 'Tools such as cppcheck, clang-tidy, CodeSonar or Helix QAC check rules without running the program.' },

    { sec: 's3', q: 'What is the problem with this code?',
      code: String.raw`
int count;
if (ready) count = compute();
use(count);`,
      opts: ['count is declared in the wrong place', 'If ready is false, count is read uninitialised, which is undefined behaviour', 'compute must be constexpr', 'Nothing'], a: 1,
      why: 'Rule theme: initialise every object, for example `int count{};`.' },

    { sec: 's3', q: 'Why do safety guidelines discourage C-style casts like `(int)x`?',
      opts: ['They are slower', 'They can silently perform several different conversions, hiding the intent', 'They are not part of C++', 'They only work on pointers'], a: 1,
      why: 'A C-style cast may act as static, const or reinterpret cast. Named casts make the conversion explicit and easy to search for.' },

    { sec: 's3', q: 'Why is manual `new` and `delete` discouraged?',
      opts: ['They are removed from C++20', 'They leak on early returns and exceptions; RAII types such as `unique_ptr` and containers manage lifetime safely', 'They are slower than malloc', 'They cannot allocate arrays'], a: 1,
      why: 'Ownership should be tied to an object\'s lifetime so cleanup cannot be skipped.' },

    { sec: 's3', q: 'Why do many embedded standards forbid dynamic allocation after start-up?',
      opts: ['The heap does not exist on microcontrollers', 'Allocation time is unpredictable, the heap can fragment, and allocation can fail at run time', 'It is illegal in C++', 'It prevents use of classes'], a: 1,
      why: 'Deterministic timing and memory use matter in real-time systems, so memory is allocated once or taken from fixed pools.' },

    { sec: 's3', q: 'Why do safety standards commonly forbid recursion?',
      opts: ['Recursion is not allowed in C++', 'Stack depth depends on the data and cannot be bounded statically, so overflow is possible', 'Recursive functions cannot be inlined', 'Recursion is always slower than loops'], a: 1,
      why: 'Bounded loops can be analysed for worst-case stack and time; unbounded recursion cannot.' },

    { sec: 's3', q: 'What does brace initialisation help with here?',
      code: String.raw`
std::uint8_t level{300};`,
      opts: ['It wraps to 44 silently', 'The compiler rejects it as a narrowing conversion', 'It saturates to 255', 'It becomes a 16-bit value'], a: 1,
      why: 'List-initialisation forbids narrowing conversions, so a constant that does not fit is a compile error instead of a silent wrap.' },

    { sec: 's3', q: 'Why must you never write `using namespace std;` in a header?',
      opts: ['It increases compile time only', 'It forces that using-directive on every file that includes the header, polluting names and possibly changing overload resolution', 'It is a syntax error in headers', 'It prevents inlining'], a: 1,
      why: 'You cannot undo it from the includer\'s side. Qualify names in headers.' },

    { sec: 's3', q: 'What is the bug in this class?',
      code: String.raw`
class Buffer {
    char* data_;
public:
    Buffer(size_t n) : data_(new char[n]) {}
    ~Buffer() { delete[] data_; }
};`,
      opts: ['Missing virtual destructor', 'The implicit copy duplicates the pointer, so copies double-delete the same memory', 'delete[] is wrong here', 'The constructor must be explicit and constexpr'], a: 1,
      why: 'It owns a resource but follows neither the rule of five nor the rule of zero. Use `std::vector<char>` or define/delete all special members.' },

    { sec: 's4', q: 'A static analyser reports no violations. What can you conclude?',
      opts: ['The code is correct', 'No violations of the checked rules were found, but the analyser can miss issues and still needs tests and review', 'The code is certified', 'All run-time bugs are absent'], a: 1,
      why: 'Static analysis lowers risk but has false negatives and false positives; it does not prove correctness.' },

    { sec: 's2', q: 'What should you do when you genuinely must break a rule?',
      opts: ['Disable the whole analyser', 'Record a justified deviation through the project process, keep it narrow and have it reviewed', 'Rewrite the rule', 'Hide it in a macro'], a: 1,
      why: 'Standards such as MISRA explicitly allow documented deviations, which keeps exceptions visible and controlled.' }
  ]
};
