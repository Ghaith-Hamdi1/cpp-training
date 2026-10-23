/* Quiz questions for the 'basics' topic. Loaded by 01-basics-quiz.html. */
CT.quizData.basics = {
  id: 'basics',
  questions: [
    { sec: 's6', q: 'What is the value of `x` after this code runs?',
      code: String.raw`
int x = 5;
int* p = &x;
*p = 9;`,
      opts: ['5', '9', 'The address of x', 'Undefined behavior'], a: 1,
      why: '`p` holds the address of `x`, so `*p = 9` writes 9 into `x` itself.' },

    { sec: 's6', q: 'What does the expression `&x` give you?',
      opts: ['The value stored in x', 'The address of x', 'A reference to the type of x', 'A copy of x'], a: 1,
      why: 'Unary `&` is the address-of operator. Do not confuse it with `int&`, where `&` is part of a reference type.' },

    { sec: 's8', q: 'Which statement does NOT compile?',
      code: String.raw`
int a = 1, b = 2;
const int* p = &a;
// (1)  p = &b;
// (2)  *p = 3;
// (3)  int c = *p;`,
      opts: ['(1) p = &b;', '(2) *p = 3;', '(3) int c = *p;', 'All three compile'], a: 1,
      why: '`const int*` is a pointer to const int: the data cannot be modified through it, but the pointer itself can be re-pointed and the data can be read.' },

    { sec: 's7', q: 'What does this print?',
      code: String.raw`
int a = 1, b = 2;
int& r = a;
r = b;
std::cout << a;`,
      opts: ['1', '2', 'It does not compile', 'Undefined behavior'], a: 1,
      why: 'A reference can never be re-bound. `r = b` assigns the value of `b` into the variable `r` aliases, so `a` becomes 2.' },

    { sec: 's7', q: 'Which of these is true of a C++ reference but NOT of a pointer?',
      opts: ['It can be re-seated to another object after it is created', 'It can be left uninitialized and assigned later', 'It must be bound when declared and can never be null', 'It can only refer to objects that live on the stack'], a: 2,
      why: 'References are permanent aliases that must be bound to a real object at declaration. Pointers can be null, uninitialized, or re-pointed.' },

    { sec: 's5', q: 'In `int* p = new int(5);` where do `p` and the int it points to live?',
      code: String.raw`
void f() {
    int* p = new int(5);
}`,
      opts: ['Both live on the stack, because the declaration is inside a function', 'Both live on the heap, because new was used', 'p is on the stack; the int it points to is on the heap', 'p is on the heap; the int is on the stack, since it is a small value'], a: 2,
      why: '`p` is an ordinary local variable (stack). `new` allocates the int on the heap. When `f` returns, `p` disappears but the heap int leaks unless you `delete` it first.' },

    { sec: 's9', q: 'What is wrong with this code?',
      code: String.raw`
int* a = new int[10];
delete a;`,
      opts: ['It is fine: delete frees arrays too, though element destructors may not run', 'It needs delete[] a: new[] and delete must match (undefined behavior)', 'It leaks only the first element, but the program is otherwise valid', 'new int[10] is invalid: arrays cannot be heap-allocated'], a: 1,
      why: 'Memory from `new[]` must be released with `delete[]`. Using plain `delete` is undefined behavior.' },

    { sec: 's9', q: 'What happens on the last line?',
      code: String.raw`
int* p = new int(1);
delete p;
std::cout << *p;`,
      opts: ['Prints the old value 1, because the memory is still intact', 'Prints 0, because delete zeroes the memory it frees', 'A compile error, because p is used after the delete', 'Undefined behavior: p dangles after the delete'], a: 3,
      why: 'After `delete p`, the pointer still holds the old address but the memory is no longer yours. Reading it is use-after-free: undefined behavior.' },

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

    { sec: 's6', q: 'What does this print?',
      code: String.raw`
int a[3] = {10, 20, 30};
int* p = a;
std::cout << *(p + 2);`,
      opts: ['10', '20', '30', 'The address of the third element'], a: 2,
      why: 'Pointer arithmetic moves in whole elements. `p + 2` points at `a[2]`, which holds 30. `*(p + 2)` is the same as `p[2]`.' },

    { sec: 's10', q: 'Inside this function, what does `sizeof(arr)` give?',
      code: String.raw`
void f(int arr[10]) {
    std::cout << sizeof(arr);
}`,
      opts: ['40, the size of the whole array of 10 ints', '10, the number of elements declared in the parameter', '8 on a 64-bit machine: the parameter is really a pointer', 'A compile error, because sizeof cannot take a parameter'], a: 2,
      why: 'A C array parameter silently decays to a pointer, so the size information is lost. This is a key reason to prefer `std::array` and `std::vector`.' },

    { sec: 's11', q: 'Which function is safe?',
      code: String.raw`
int& f() { int v = 1; return v; }
int  g() { int v = 1; return v; }
int* h() { int v = 1; return &v; }`,
      opts: ['Only f', 'Only g', 'f and h', 'All of them'], a: 1,
      why: '`f` returns a reference and `h` a pointer to a local that is destroyed when the function returns (dangling). `g` returns a copy of the value, which is fine.' },

    { sec: 's6', q: 'Why is `nullptr` preferred over `NULL`?',
      opts: ['It runs faster at run time, because it avoids a comparison with zero in conditions', 'It has its own type, so it is never taken for the integer 0 in overloads', 'NULL was removed from the language in C++11, so old code no longer compiles', 'It can be dereferenced safely, which is why NULL should be avoided in new code'], a: 1,
      why: '`NULL` is just 0, so `f(NULL)` may pick `f(int)` over `f(char*)`. `nullptr` converts only to pointer types. Dereferencing either is undefined behavior.' },

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

    { sec: 's8', q: 'What best describes `int* const p = &x;`?',
      opts: ['A pointer to a const int: the int is fixed, but the pointer itself can move on', 'A const pointer to an int: the pointer is fixed, the int can change', 'A const pointer to a const int: neither the pointer nor the int can change', 'A reference to x, written with pointer syntax and bound to x for life'], a: 1,
      why: 'Read right to left: "p is a const pointer to int". The star separates the pointer (right side) from the data (left side).' },

    { sec: 's9', q: 'In modern C++, what is the preferred way to hold a dynamically sized array of ints?',
      opts: ['`int* a = new int[n];`', '`int a[n];` on the stack', '`std::vector<int>`', '`malloc(n * sizeof(int))`'], a: 2,
      why: '`std::vector` owns its memory, frees it automatically, grows on demand and offers bounds-checked access via `.at()`. Raw `new[]` and `malloc` leave all that to you.' },

    { sec: 's9', q: 'Besides allocating memory, what does `new` do that `malloc` does not?',
      opts: ['It is just a type-safe spelling of malloc with a cast hidden inside', 'It calls the constructor and returns a typed pointer', 'It zero-fills the memory before returning it', 'It places the object on the stack for faster access'], a: 1,
      why: '`new` allocates, then constructs the object, and throws `std::bad_alloc` on failure. `malloc` returns raw uninitialized bytes (`void*`) and returns null on failure.' },
    { sec: 's4', q: 'A function needs to read a run of ints. What is the safest way to pass it?',
      opts: ['A pointer and a separate count: `void f(const int* p, int n)`', 'A `std::span<const int>`, or a `const std::vector<int>&`', 'A pointer only, and the function finds the end itself', 'A global array'], a: 1,
      why: 'A pointer does not know how many elements it points to, and a (pointer, count) pair lets the two disagree. A span (C++20) or a container reference carries the size with the data and accepts arrays and vectors without copying.' },

    { sec: 's4', q: 'When should a function take a pointer parameter instead of a reference?',
      opts: ['When speed matters, since pointers are cheaper to pass than references', 'When nullptr is a valid argument, which the function must then test for', 'Whenever the object is large and copying it would be costly for the caller', 'When the object is const, since a const reference cannot be null'], a: 1,
      why: 'A reference must refer to a real object, so callers can rely on it. Use a pointer only when passing nothing is meaningful. Prefer a value for tiny types and a (const) reference otherwise.' }
  ]
};
