/* Quiz questions for the 'pointers' topic. Loaded by 22-pointers-quiz.html.
 * Each question: { sec: '<section id of the lesson>', q, opts: [4 options], a: <index of the right one>, why }.
 * Write 12 to 20 questions; keep the right answer from being the longest one (tools/check-quiz-balance.mjs). */
CT.quizData.pointers = {
  id: 'pointers',
  questions: [
    { sec: 'pointers', q: 'What is the value of `x` after this code runs?',
      code: String.raw`
int x = 5;
int* p = &x;
*p = 9;`,
      opts: ['5', '9', 'The address of x', 'Undefined behavior'], a: 1,
      why: '`p` holds the address of `x`, so `*p = 9` writes 9 into `x` itself.' },

    { sec: 'pointers', q: 'What does the expression `&x` give you?',
      opts: ['The value stored in x', 'The address of x', 'A reference to the type of x', 'A copy of x'], a: 1,
      why: 'Unary `&` is the address-of operator. Do not confuse it with `int&`, where `&` is part of a reference type.' },

    { sec: 'constptr', q: 'Which statement does NOT compile?',
      code: String.raw`
int a = 1, b = 2;
const int* p = &a;
// (1)  p = &b;
// (2)  *p = 3;
// (3)  int c = *p;`,
      opts: ['(1) p = &b;', '(2) *p = 3;', '(3) int c = *p;', 'All three compile'], a: 1,
      why: '`const int*` is a pointer to const int: the data cannot be modified through it, but the pointer itself can be re-pointed and the data can be read.' },

    { sec: 'references', q: 'What does this print?',
      code: String.raw`
int a = 1, b = 2;
int& r = a;
r = b;
std::cout << a;`,
      opts: ['1', '2', 'It does not compile', 'Undefined behavior'], a: 1,
      why: 'A reference can never be re-bound. `r = b` assigns the value of `b` into the variable `r` aliases, so `a` becomes 2.' },

    { sec: 'references', q: 'Which of these is true of a C++ reference but NOT of a pointer?',
      opts: ['It can be re-seated to another object after it is created', 'It can be left uninitialized and assigned later', 'It must be bound when declared and can never be null', 'It can only refer to objects that live on the stack'], a: 2,
      why: 'References are permanent aliases that must be bound to a real object at declaration. Pointers can be null, uninitialized, or re-pointed.' },

    { sec: 'regions', q: 'In `int* p = new int(5);` where do `p` and the int it points to live?',
      code: String.raw`
void f() {
    int* p = new int(5);
}`,
      opts: ['Both live on the stack, because the declaration is inside a function', 'Both live on the heap, because new was used', 'p is on the stack; the int it points to is on the heap', 'p is on the heap; the int is on the stack, since it is a small value'], a: 2,
      why: '`p` is an ordinary local variable (stack). `new` allocates the int on the heap. When `f` returns, `p` disappears but the heap int leaks unless you `delete` it first.' },

    { sec: 'dynamic', q: 'What is wrong with this code?',
      code: String.raw`
int* a = new int[10];
delete a;`,
      opts: ['It is fine: delete frees arrays too, though element destructors may not run', 'It needs delete[] a: new[] and delete must match (undefined behavior)', 'It leaks only the first element, but the program is otherwise valid', 'new int[10] is invalid: arrays cannot be heap-allocated'], a: 1,
      why: 'Memory from `new[]` must be released with `delete[]`. Using plain `delete` is undefined behavior.' },

    { sec: 'dynamic', q: 'What happens on the last line?',
      code: String.raw`
int* p = new int(1);
delete p;
std::cout << *p;`,
      opts: ['Prints the old value 1, because the memory is still intact', 'Prints 0, because delete zeroes the memory it frees', 'A compile error, because p is used after the delete', 'Undefined behavior: p dangles after the delete'], a: 3,
      why: 'After `delete p`, the pointer still holds the old address but the memory is no longer yours. Reading it is use-after-free: undefined behavior.' },

    { sec: 'pointers', q: 'What does this print?',
      code: String.raw`
int a[3] = {10, 20, 30};
int* p = a;
std::cout << *(p + 2);`,
      opts: ['10', '20', '30', 'The address of the third element'], a: 2,
      why: 'Pointer arithmetic moves in whole elements. `p + 2` points at `a[2]`, which holds 30. `*(p + 2)` is the same as `p[2]`.' },

    { sec: 'arrays', q: 'Inside this function, what does `sizeof(arr)` give?',
      code: String.raw`
void f(int arr[10]) {
    std::cout << sizeof(arr);
}`,
      opts: ['40, the size of the whole array of 10 ints', '10, the number of elements declared in the parameter', '8 on a 64-bit machine: the parameter is really a pointer', 'A compile error, because sizeof cannot take a parameter'], a: 2,
      why: 'A C array parameter silently decays to a pointer, so the size information is lost. This is a key reason to prefer `std::array` and `std::vector`.' },

    { sec: 'bugs', q: 'Which function is safe?',
      code: String.raw`
int& f() { int v = 1; return v; }
int  g() { int v = 1; return v; }
int* h() { int v = 1; return &v; }`,
      opts: ['Only f', 'Only g', 'f and h', 'All of them'], a: 1,
      why: '`f` returns a reference and `h` a pointer to a local that is destroyed when the function returns (dangling). `g` returns a copy of the value, which is fine.' },

    { sec: 'pointers', q: 'Why is `nullptr` preferred over `NULL`?',
      opts: ['It runs faster at run time, because it avoids a comparison with zero in conditions', 'It has its own type, so it is never taken for the integer 0 in overloads', 'NULL was removed from the language in C++11, so old code no longer compiles', 'It can be dereferenced safely, which is why NULL should be avoided in new code'], a: 1,
      why: '`NULL` is just 0, so `f(NULL)` may pick `f(int)` over `f(char*)`. `nullptr` converts only to pointer types. Dereferencing either is undefined behavior.' },

    { sec: 'constptr', q: 'What best describes `int* const p = &x;`?',
      opts: ['A pointer to a const int: the int is fixed, but the pointer itself can move on', 'A const pointer to an int: the pointer is fixed, the int can change', 'A const pointer to a const int: neither the pointer nor the int can change', 'A reference to x, written with pointer syntax and bound to x for life'], a: 1,
      why: 'Read right to left: "p is a const pointer to int". The star separates the pointer (right side) from the data (left side).' },

    { sec: 'dynamic', q: 'In modern C++, what is the preferred way to hold a dynamically sized array of ints?',
      opts: ['`int* a = new int[n];`', '`int a[n];` on the stack', '`std::vector<int>`', '`malloc(n * sizeof(int))`'], a: 2,
      why: '`std::vector` owns its memory, frees it automatically, grows on demand and offers bounds-checked access via `.at()`. Raw `new[]` and `malloc` leave all that to you.' },

    { sec: 'dynamic', q: 'Besides allocating memory, what does `new` do that `malloc` does not?',
      opts: ['It is just a type-safe spelling of malloc with a cast hidden inside', 'It calls the constructor and returns a typed pointer', 'It zero-fills the memory before returning it', 'It places the object on the stack for faster access'], a: 1,
      why: '`new` allocates, then constructs the object, and throws `std::bad_alloc` on failure. `malloc` returns raw uninitialized bytes (`void*`) and returns null on failure.' },

    { sec: 'memory', q: 'What is the address of a variable?',
      opts: ['The value that is stored in the variable right now', 'The number of the memory box where the variable starts', 'The number of bytes that the variable uses in memory', 'The name that the compiler gives to the variable'], a: 1,
      why: 'Memory is a row of numbered boxes (bytes). A variable\'s address is the number of the first box it occupies; `&x` gives it.' },

    { sec: 'arrays', q: 'With `int* p = a;` pointing at the first element of an int array, how many bytes does `p + 1` move on a typical machine?',
      opts: ['1 byte', '4 bytes: one int', '8 bytes: one pointer', 'It depends on the address of p'], a: 1,
      why: 'Pointer arithmetic moves by whole elements, so adding 1 to an `int*` adds `sizeof(int)`, which is 4 bytes on most machines.' },

    { sec: 'bugs', q: 'What does this code do? `int* p = new int(1); p = new int(2); delete p;`',
      opts: ['Frees both ints', 'Leaks the first int and frees the second', 'Frees the first int and leaks the second', 'Causes a double delete'], a: 1,
      why: 'The second `new` overwrites the only pointer to the first block, so it can never be freed. `delete p` frees the second block.' }
  ]
};
