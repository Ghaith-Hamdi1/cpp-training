/* Quiz questions for the 'strings' topic. Loaded by 08-strings-regex-time-quiz.html. */
CT.quizData.strings = {
  id: 'strings',
  questions: [
    { sec: 's1', q: 'What is the key difference between `std::string` and `std::string_view`?',
      opts: ['string_view is faster because it uses vectorised instructions internally', 'string owns its characters; string_view only points at someone else\'s', 'string_view can modify the text in place, which string cannot do', 'They are the same type under two names; both own their text'], a: 1,
      why: 'A view is a pointer plus a length with no ownership. It never allocates, but it is only valid while the underlying characters are alive.' },

    { sec: 's1', q: 'What is wrong with this code?',
      code: String.raw`
std::string_view name = std::string("temporary");
std::cout << name;`,
      opts: ['It prints temporary without any problem', 'It does not compile because of the temporary string object', 'The view dangles: the temporary string dies after the first statement', 'string_view cannot be printed with cout, only std::string can'], a: 2,
      why: 'The temporary `std::string` dies at the semicolon, so `name` points at freed memory. Reading it is undefined behaviour.' },

    { sec: 's1', q: 'Which parameter type is best for a function that only reads text and should accept literals, std::string and substrings without copying?',
      opts: ['`std::string`', '`std::string&`', '`const std::string&`', '`std::string_view`'], a: 3,
      why: '`std::string_view` binds to all of them without allocating. `const std::string&` would build a temporary string for a literal.' },

    { sec: 's1', q: 'What does `std::string::find` return when the text is not found?',
      opts: ['-1', '0', '`std::string::npos`', 'It throws `std::out_of_range`'], a: 2,
      why: '`find` returns the constant `npos`, a very large unsigned value. Comparing the result to -1 through an `int` is a classic bug.' },

    { sec: 's1', q: 'Is it safe to pass `sv.data()` of a `std::string_view` to a C function expecting a null-terminated string?',
      opts: ['Yes: a view is null-terminated, just like a C string', 'No: a view is not guaranteed to be null-terminated', 'Yes, but only when the view refers to a string literal', 'No: a view has no data() member that could be passed on'], a: 1,
      why: 'A view of a substring does not end in `\\0`. Convert to `std::string` first if you need a C string.' },

    { sec: 's2', q: 'What does `std::regex_match("xabcx", std::regex("abc"))` return?',
      opts: ['true', 'false', 'It throws `std::regex_error`', 'It returns the position 1'], a: 1,
      why: '`regex_match` requires the pattern to match the **entire** string. The extra `x` characters make it fail; `regex_search` would return true.' },

    { sec: 's2', q: 'Which function finds a match anywhere inside a string and fills a `std::smatch` with the captures?',
      opts: ['`std::regex_match`', '`std::regex_search`', '`std::regex_replace`', '`std::regex_find`'], a: 1,
      why: '`regex_search` looks for the first match anywhere and stores the whole match and each group in the `smatch`. There is no `regex_find`.' },

    { sec: 's2', q: 'After a successful `regex_search(line, m, std::regex(R"((\\w+)=(\\d+))"))` on "x=42", what is `m[2]`?',
      opts: ['"x=42"', '"x"', '"42"', '"="'], a: 2,
      why: '`m[0]` is the whole match, `m[1]` is the first group (`x`) and `m[2]` is the second group (`42`).' },

    { sec: 's2', q: 'How do you visit every match in a string, not just the first?',
      opts: ['Call `regex_search` once; it returns all matches', 'Use `std::sregex_iterator`', 'Use `regex_match` in a loop', 'Use `std::regex_all`'], a: 1,
      why: 'A `std::sregex_iterator` constructed over the range walks all matches; compare it with a default-constructed iterator to detect the end.' },

    { sec: 's2', q: 'Why should you not construct a `std::regex` inside a hot loop?',
      opts: ['It is not thread safe, so concurrent loops corrupt its internal state', 'Construction compiles the pattern, which is expensive; build it once', 'It leaks memory each time one is constructed in a loop', 'The compiler forbids constructing regex objects inside loop bodies'], a: 1,
      why: 'Pattern compilation happens at construction. Create it once (for example as a `static const`) and reuse it.' },

    { sec: 's2', q: 'What does an invalid pattern such as `std::regex("(")` do?',
      opts: ['It silently matches no input and carries on', 'It throws std::regex_error when constructed', 'It is rejected by the compiler at compile time', 'It matches all strings, like an empty pattern'], a: 1,
      why: 'Patterns are parsed at run time, so an invalid one throws `std::regex_error` when the regex object is built.' },

    { sec: 's4', q: 'Which clock should you use to measure how long an operation took or to implement a timeout?',
      opts: ['`system_clock`, because it is the most accurate', '`steady_clock`, because it is monotonic', '`high_resolution_clock`, since it has the finest tick', 'The three clocks behave the same for this purpose'], a: 1,
      why: '`system_clock` can jump when the system time changes. `steady_clock` never goes backwards, which is what interval measurement needs.' },

    { sec: 's4', q: 'Which line does NOT compile?',
      code: String.raw`
using namespace std::chrono;
seconds s = 90s;
milliseconds ms = s;        // (A)
seconds back = ms;          // (B)`,
      opts: ['(A)', '(B)', 'Both', 'Neither'], a: 1,
      why: 'Converting seconds to milliseconds is lossless so it is implicit. Converting back could lose precision, so it needs an explicit `duration_cast<seconds>(ms)`.' },

    { sec: 's4', q: 'What does `std::chrono::duration_cast<std::chrono::minutes>(90s).count()` give?',
      opts: ['1', '1.5', '2', '90'], a: 0,
      why: 'Integer durations truncate when cast to a coarser unit, so 90 seconds becomes 1 minute.' },

    { sec: 's1', q: 'What does this statement do?',
      code: String.raw`
std::cout << s.find('z') == std::string::npos;`,
      opts: ['It prints 1 if z is absent, as the expression suggests', 'It prints 0 if z is absent, as the expression suggests', 'It does not compile as intended: << binds tighter than ==', 'It prints npos only when z is absent from the string'], a: 2,
      why: 'It parses as `(std::cout << s.find(\'z\')) == npos`, comparing a stream with a number. Parenthesise the comparison.' },

    { sec: 'sso', q: 'What is the small string optimisation (SSO)?',
      opts: ['Strings are compressed in memory to save space on the heap', 'Short strings live inside the string object, so no heap allocation', 'Strings are stored in read-only memory by the compiler', 'The compiler merges duplicate strings into a single shared copy'], a: 1,
      why: 'A `std::string` has room for a handful of characters (about 15 in libstdc++) inside the object. Longer text goes to the heap.' },

    { sec: 'sso', q: 'Why call `reserve(1000)` before appending 1000 characters one at a time?',
      opts: ['It makes the string read-only afterwards, which speeds up reads', 'It allocates once, so appending never reallocates', 'It removes the null terminator from the buffer to save one byte', 'It converts the string into a string_view over the same buffer'], a: 1,
      why: 'Without `reserve`, capacity grows geometrically and each growth copies the characters and invalidates pointers and iterators.' },

    { sec: 'sso', q: 'What happens to a pointer obtained from `s.c_str()` when you append to `s` and it reallocates?',
      opts: ['It stays valid, since the string owns the memory it points to', 'It dangles: reallocation moves the characters and invalidates it', 'It is updated automatically by the string whenever it reallocates', 'It becomes a null pointer, which is safe to test and ignore'], a: 1,
      why: 'Any operation that may reallocate invalidates pointers, references and iterators into the string.' },

    { sec: 'numbers', q: 'What does `std::from_chars` return for the input "12x4" when parsing an `int`?',
      opts: ['It throws invalid_argument for the bad input', 'It parses 12 with no error and leaves ptr at x4', 'It returns 0 together with an error code', 'It parses 124, skipping the stray character'], a: 1,
      why: 'It stops at the first character that cannot belong to the number and reports success. Compare `ptr` with the end of the input when the whole token must be numeric.' },

    { sec: 'numbers', q: 'Why is `std::from_chars` preferred over `std::stoi` on a hot path?',
      opts: ['It is the standard way to parse an int in C++', 'It does not throw, allocate or use the locale', 'It is faster because it uses vector instructions', 'It accepts leading whitespace and plus signs'], a: 1,
      why: '`from_chars` reports errors with a return value and works on a character range, so there are no exceptions, no temporary `string` and no locale lookup.' },

    { sec: 'format', q: 'What is a drawback of `std::cout << std::hex << 255;` compared with `std::format("{:x}", 255)`?',
      opts: ['It cannot print numbers in hexadecimal, only in decimal', 'The stream stays in hex mode, so later integers print in hex too', 'It allocates a temporary string each time it prints a number', 'It needs C++23 to compile, unlike std::format'], a: 1,
      why: 'Many stream manipulators are sticky. `std::format` is stateless: the format applies to that one replacement field only.' },

    { sec: 'streams', q: 'Which loop reads a file line by line correctly?',
      opts: ['`while (!f.eof()) { std::getline(f, line); use(line); }`', '`while (std::getline(f, line)) { use(line); }`', '`while (f) { f >> line; }` with no check afterwards', '`for (;;) { std::getline(f, line); }`'], a: 1,
      why: '`eof()` is true only after a read has already failed, so the first form processes a bogus last line. Testing the read itself is correct.' },

    { sec: 'streams', q: 'When is a `std::ofstream` closed if you never call `close()`?',
      opts: ['Only when you call close() yourself at some point', 'When its destructor runs at the end of its scope', 'When the whole program exits normally', 'When the last line is written to the file'], a: 1,
      why: 'File streams are RAII objects: the destructor flushes and closes the file.' }
  ]
};
