/* Quiz questions for the 'strings' topic. Loaded by 08-strings-regex-time-quiz.html. */
CT.quizData.strings = {
  id: 'strings',
  questions: [
    { q: 'What is the key difference between `std::string` and `std::string_view`?',
      opts: ['string_view is faster because it uses SIMD', '`std::string` owns its characters, `string_view` only points at someone else\'s', 'string_view can modify the text, string cannot', 'There is no difference apart from the name'], a: 1,
      why: 'A view is a pointer plus a length with no ownership. It never allocates, but it is only valid while the underlying characters are alive.' },

    { q: 'What is wrong with this code?',
      code: String.raw`
std::string_view name = std::string("temporary");
std::cout << name;`,
      opts: ['Nothing, it prints temporary', 'It does not compile', 'The view dangles: the temporary string is destroyed at the end of the first statement', 'string_view cannot be printed'], a: 2,
      why: 'The temporary `std::string` dies at the semicolon, so `name` points at freed memory. Reading it is undefined behaviour.' },

    { q: 'Which parameter type is best for a function that only reads text and should accept literals, std::string and substrings without copying?',
      opts: ['`std::string`', '`std::string&`', '`const std::string&`', '`std::string_view`'], a: 3,
      why: '`std::string_view` binds to all of them without allocating. `const std::string&` would build a temporary string for a literal.' },

    { q: 'What does `std::string::find` return when the text is not found?',
      opts: ['-1', '0', '`std::string::npos`', 'It throws `std::out_of_range`'], a: 2,
      why: '`find` returns the constant `npos`, a very large unsigned value. Comparing the result to -1 through an `int` is a classic bug.' },

    { q: 'Is it safe to pass `sv.data()` of a `std::string_view` to a C function expecting a null-terminated string?',
      opts: ['Yes, it is always null-terminated', 'No, a view is not guaranteed to be null-terminated', 'Yes, but only for literals', 'No, `data()` does not exist for views'], a: 1,
      why: 'A view of a substring does not end in `\\0`. Convert to `std::string` first if you need a C string.' },

    { q: 'What does `std::regex_match("xabcx", std::regex("abc"))` return?',
      opts: ['true', 'false', 'It throws `std::regex_error`', 'It returns the position 1'], a: 1,
      why: '`regex_match` requires the pattern to match the **entire** string. The extra `x` characters make it fail; `regex_search` would return true.' },

    { q: 'Which function finds a match anywhere inside a string and fills a `std::smatch` with the captures?',
      opts: ['`std::regex_match`', '`std::regex_search`', '`std::regex_replace`', '`std::regex_find`'], a: 1,
      why: '`regex_search` looks for the first match anywhere and stores the whole match and each group in the `smatch`. There is no `regex_find`.' },

    { q: 'After a successful `regex_search(line, m, std::regex(R"((\\w+)=(\\d+))"))` on "x=42", what is `m[2]`?',
      opts: ['"x=42"', '"x"', '"42"', '"="'], a: 2,
      why: '`m[0]` is the whole match, `m[1]` is the first group (`x`) and `m[2]` is the second group (`42`).' },

    { q: 'How do you visit every match in a string, not just the first?',
      opts: ['Call `regex_search` once; it returns all matches', 'Use `std::sregex_iterator`', 'Use `regex_match` in a loop', 'Use `std::regex_all`'], a: 1,
      why: 'A `std::sregex_iterator` constructed over the range walks all matches; compare it with a default-constructed iterator to detect the end.' },

    { q: 'Why should you not construct a `std::regex` inside a hot loop?',
      opts: ['It is not thread safe', 'Constructing compiles the pattern, which is expensive; build it once and reuse it', 'It leaks memory', 'The compiler forbids it'], a: 1,
      why: 'Pattern compilation happens at construction. Create it once (for example as a `static const`) and reuse it.' },

    { q: 'What does an invalid pattern such as `std::regex("(")` do?',
      opts: ['Silently matches nothing', 'Throws `std::regex_error` at construction', 'Causes a compile error', 'Matches everything'], a: 1,
      why: 'Patterns are parsed at run time, so an invalid one throws `std::regex_error` when the regex object is built.' },

    { q: 'Which clock should you use to measure how long an operation took or to implement a timeout?',
      opts: ['`system_clock`, because it is the most accurate', '`steady_clock`, because it is monotonic', '`high_resolution_clock`, always', 'Any of them behaves the same'], a: 1,
      why: '`system_clock` can jump when the system time changes. `steady_clock` never goes backwards, which is what interval measurement needs.' },

    { q: 'Which line does NOT compile?',
      code: String.raw`
using namespace std::chrono;
seconds s = 90s;
milliseconds ms = s;        // (A)
seconds back = ms;          // (B)`,
      opts: ['(A)', '(B)', 'Both', 'Neither'], a: 1,
      why: 'Converting seconds to milliseconds is lossless so it is implicit. Converting back could lose precision, so it needs an explicit `duration_cast<seconds>(ms)`.' },

    { q: 'What does `std::chrono::duration_cast<std::chrono::minutes>(90s).count()` give?',
      opts: ['1', '1.5', '2', '90'], a: 0,
      why: 'Integer durations truncate when cast to a coarser unit, so 90 seconds becomes 1 minute.' },

    { q: 'What does this statement do?',
      code: String.raw`
std::cout << s.find('z') == std::string::npos;`,
      opts: ['Prints 1 if z is absent', 'Prints 0 if z is absent', 'Does not compile as intended, because << binds tighter than ==', 'Always prints npos'], a: 2,
      why: 'It parses as `(std::cout << s.find(\'z\')) == npos`, comparing a stream with a number. Parenthesise the comparison.' }
  ]
};
