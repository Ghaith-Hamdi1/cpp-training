/* Quiz questions for the 'basics' topic. Loaded by 01-basics-quiz.html. */
CT.quizData.basics = {
  id: 'basics',
  questions: [
    { sec: 's3', q: 'What does `std::cout << 7 / 2 << " " << 7 / 2.0;` print?',
      opts: ['3 3', '3 3.5', '3.5 3.5', '4 3.5'], a: 1,
      why: 'Both operands are int in the first expression so integer division truncates to 3. In the second, a double operand makes it floating point: 3.5.' },

    { sec: 's4', q: 'What does this print?',
      code: String.raw`
void f(int n) { n = 10; }
int main() {
    int x = 1;
    f(x);
    std::cout << x;
}`,
      opts: ['10', '1', '0', 'Compile error'], a: 1,
      why: 'Arguments are passed by value by default, so `f` modified its own copy. Use `int& n` to modify the caller\'s variable.' },

    { sec: 's2', q: 'What does `std::cout << (-1 < 1u);` print?',
      opts: ['1 (true)', '0 (false)', 'Compile error', 'Undefined behavior'], a: 1,
      why: 'Comparing signed and unsigned converts the signed value to unsigned: -1 becomes 4294967295, which is not less than 1. Hence 0.' },

    { sec: 's1', q: 'The linker prints "undefined reference to `foo(int)`". What does that mean?',
      opts: ['A syntax error somewhere in the source file that stopped the build early', 'A function was declared and called, but no definition was linked in', 'The same function was defined twice, in two different object files, so the symbol clashes', 'A header file could not be found by the preprocessor, so the call has no declaration'], a: 1,
      why: 'Compile errors come from the compiler about one file. "Undefined reference" comes from the linker: it could not find the body of a declared function in any object file or library.' },

    { sec: 's2', q: 'Which line is rejected by the compiler?',
      code: String.raw`
int a{5};      // (1)
int b{3.7};    // (2)
int c = 3.7;   // (3)`,
      opts: ['Line (1), because braces need a type name before the value', 'Line (2): braces forbid narrowing a double to an int', 'Line (3): a double cannot initialise an int with =', 'None: all three compile, though (2) and (3) drop the .7'], a: 1,
      why: 'Brace initialization rejects narrowing (double to int). The `=` form silently truncates 3.7 to 3 (a common source of bugs, which is why braces are preferred).' },

    { sec: 's4', q: 'A function needs to read a run of ints. What is the safest way to pass it?',
      opts: ['A pointer and a separate count: `void f(const int* p, int n)`', 'A `std::span<const int>`, or a `const std::vector<int>&`', 'A pointer only, and the function finds the end itself', 'A global array'], a: 1,
      why: 'A pointer does not know how many elements it points to, and a (pointer, count) pair lets the two disagree. A span (C++20) or a container reference carries the size with the data and accepts arrays and vectors without copying.' },

    { sec: 's4', q: 'When should a function take a pointer parameter instead of a reference?',
      opts: ['When speed matters, since pointers are cheaper to pass than references', 'When nullptr is a valid argument, which the function must then test for', 'Whenever the object is large and copying it would be costly for the caller', 'When the object is const, since a const reference cannot be null'], a: 1,
      why: 'A reference must refer to a real object, so callers can rely on it. Use a pointer only when passing nothing is meaningful. Prefer a value for tiny types and a (const) reference otherwise.' },

    { sec: 's1', q: 'A program compiles without errors but the build stops with "undefined reference to `helper()`". Which stage failed?',
      opts: ['The preprocessor, which could not find a header', 'The compiler, which rejected the syntax of a line', 'The linker, which found no definition of `helper()`', 'The loader, which failed as the program started'], a: 2,
      why: 'Each .cpp file is compiled on its own. An "undefined reference" comes from the linker: it joined the object files and found a function that was declared but never defined.' },

    { sec: 's1', q: 'What does `#include <vector>` do?',
      opts: ['Links the standard vector library into the finished program', 'Pastes the header text into the file before it is compiled', 'Downloads the vector code from the internet when the program runs', 'Tells the linker which vector functions it should keep'], a: 1,
      why: '`#include` is handled by the preprocessor: it copies the text of the header into the file. Linking is a later and separate step.' },

    { sec: 's2', q: 'What does `int n;` hold when it is declared inside a function?',
      opts: ['Zero, because C++ always zero-initializes variables', 'An indeterminate value: reading it is undefined behavior', 'The value left by the previous variable, which is guaranteed to be valid', 'Nothing: the program does not compile until you initialize it'], a: 1,
      why: 'Local variables of built-in types are not initialized. Reading one before assigning it is undefined behavior; write `int n{};` or `int n = 0;`.' },

    { sec: 's3', q: 'What does `7 / 2` evaluate to when both operands are `int`?',
      opts: ['3.5', '3', '4', 'It does not compile'], a: 1,
      why: 'Division of two ints is integer division: the fractional part is dropped. Use `7.0 / 2` for 3.5.' },

    { sec: 's4', q: 'A function only reads a large `std::string` argument. How should it take the parameter?',
      opts: ['By value, so the caller cannot be affected', 'By `const` reference, which avoids the copy', 'By non-const reference, which is the fastest', 'By pointer, which is the only way to avoid a copy'], a: 1,
      why: 'A `const` reference avoids copying the string and promises not to modify it. A by-value parameter copies; a non-const reference allows changes the caller did not expect.' },

    { sec: 'tooling', q: 'Which tool reports an out-of-bounds write only when your test actually executes that line?',
      opts: ['clang-tidy, which analyzes the source without running it', 'AddressSanitizer, which instruments the running program', 'The preprocessor, which only expands macros and includes', 'The linker, which only resolves the names between files'], a: 1,
      why: 'A sanitizer checks the program while it runs, so it sees only the paths your tests take. A static analyzer reads the source without running it.' }
  ]
};
