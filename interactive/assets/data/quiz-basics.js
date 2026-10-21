/* Quiz questions for the 'basics' topic. Loaded by 01-basics-quiz.html. */
CT.quizData.basics = {
  id: 'basics',
  questions: [
    { q: 'What is the value of `x` after this code runs?',
      code: String.raw`
int x = 5;
int* p = &x;
*p = 9;`,
      opts: ['5', '9', 'The address of x', 'Undefined behavior'], a: 1,
      why: '`p` holds the address of `x`, so `*p = 9` writes 9 into `x` itself.' },

    { q: 'What does the expression `&x` give you?',
      opts: ['The value stored in x', 'The address of x', 'A reference to the type of x', 'A copy of x'], a: 1,
      why: 'Unary `&` is the address-of operator. Do not confuse it with `int&`, where `&` is part of a reference type.' },

    { q: 'Which statement does NOT compile?',
      code: String.raw`
int a = 1, b = 2;
const int* p = &a;
// (1)  p = &b;
// (2)  *p = 3;
// (3)  int c = *p;`,
      opts: ['(1) p = &b;', '(2) *p = 3;', '(3) int c = *p;', 'All three compile'], a: 1,
      why: '`const int*` is a pointer to const int: the data cannot be modified through it, but the pointer itself can be re-pointed and the data can be read.' },

    { q: 'What does this print?',
      code: String.raw`
int a = 1, b = 2;
int& r = a;
r = b;
std::cout << a;`,
      opts: ['1', '2', 'It does not compile', 'Undefined behavior'], a: 1,
      why: 'A reference can never be re-bound. `r = b` assigns the value of `b` into the variable `r` aliases, so `a` becomes 2.' },

    { q: 'Which of these is true of a C++ reference but NOT of a pointer?',
      opts: ['It can be re-seated to another object', 'It can be null', 'It must be initialized when declared and cannot be null', 'It always lives on the heap'], a: 2,
      why: 'References are permanent aliases that must be bound to a real object at declaration. Pointers can be null, uninitialized, or re-pointed.' },

    { q: 'In `int* p = new int(5);` where do `p` and the int it points to live?',
      code: String.raw`
void f() {
    int* p = new int(5);
}`,
      opts: ['Both on the stack', 'Both on the heap', '`p` on the stack, the int on the heap', '`p` on the heap, the int on the stack'], a: 2,
      why: '`p` is an ordinary local variable (stack). `new` allocates the int on the heap. When `f` returns, `p` disappears but the heap int leaks unless you `delete` it first.' },

    { q: 'What is wrong with this code?',
      code: String.raw`
int* a = new int[10];
delete a;`,
      opts: ['Nothing, it is correct', 'It should be `delete[] a;` (mismatched new[]/delete is undefined behavior)', 'It leaks because delete does not free arrays', 'new cannot allocate arrays'], a: 1,
      why: 'Memory from `new[]` must be released with `delete[]`. Using plain `delete` is undefined behavior.' },

    { q: 'What happens on the last line?',
      code: String.raw`
int* p = new int(1);
delete p;
std::cout << *p;`,
      opts: ['Prints 1 reliably', 'Prints 0', 'Compile error', 'Undefined behavior: p is a dangling pointer'], a: 3,
      why: 'After `delete p`, the pointer still holds the old address but the memory is no longer yours. Reading it is use-after-free: undefined behavior.' },

    { q: 'What does `std::cout << 7 / 2 << " " << 7 / 2.0;` print?',
      opts: ['3 3', '3 3.5', '3.5 3.5', '4 3.5'], a: 1,
      why: 'Both operands are int in the first expression so integer division truncates to 3. In the second, a double operand makes it floating point: 3.5.' },

    { q: 'What does this print?',
      code: String.raw`
void f(int n) { n = 10; }
int main() {
    int x = 1;
    f(x);
    std::cout << x;
}`,
      opts: ['10', '1', '0', 'Compile error'], a: 1,
      why: 'Arguments are passed by value by default, so `f` modified its own copy. Use `int& n` to modify the caller\'s variable.' },

    { q: 'What does `std::cout << (-1 < 1u);` print?',
      opts: ['1 (true)', '0 (false)', 'Compile error', 'Undefined behavior'], a: 1,
      why: 'Comparing signed and unsigned converts the signed value to unsigned: -1 becomes 4294967295, which is not less than 1. Hence 0.' },

    { q: 'What does this print?',
      code: String.raw`
int a[3] = {10, 20, 30};
int* p = a;
std::cout << *(p + 2);`,
      opts: ['10', '20', '30', 'The address of the third element'], a: 2,
      why: 'Pointer arithmetic moves in whole elements. `p + 2` points at `a[2]`, which holds 30. `*(p + 2)` is the same as `p[2]`.' },

    { q: 'Inside this function, what does `sizeof(arr)` give?',
      code: String.raw`
void f(int arr[10]) {
    std::cout << sizeof(arr);
}`,
      opts: ['40 (10 ints)', '10', 'The size of a pointer (for example 8)', 'Compile error'], a: 2,
      why: 'A C array parameter silently decays to a pointer, so the size information is lost. This is a key reason to prefer `std::array` and `std::vector`.' },

    { q: 'Which function is safe?',
      code: String.raw`
int& f() { int v = 1; return v; }
int  g() { int v = 1; return v; }
int* h() { int v = 1; return &v; }`,
      opts: ['Only f', 'Only g', 'f and h', 'All of them'], a: 1,
      why: '`f` returns a reference and `h` a pointer to a local that is destroyed when the function returns (dangling). `g` returns a copy of the value, which is fine.' },

    { q: 'Why is `nullptr` preferred over `NULL`?',
      opts: ['It is faster', 'It has its own pointer type, so it cannot be mistaken for the integer 0 in overload resolution', 'NULL does not exist in C++', 'nullptr can be dereferenced safely'], a: 1,
      why: '`NULL` is just 0, so `f(NULL)` may pick `f(int)` over `f(char*)`. `nullptr` converts only to pointer types. Dereferencing either is undefined behavior.' },

    { q: 'The linker prints "undefined reference to `foo(int)`". What does that mean?',
      opts: ['A syntax error in your file', 'A function was declared and used but no definition was linked in', 'A header file is missing', 'The stack overflowed'], a: 1,
      why: 'Compile errors come from the compiler about one file. "Undefined reference" comes from the linker: it could not find the body of a declared function in any object file or library.' },

    { q: 'Which line is rejected by the compiler?',
      code: String.raw`
int a{5};      // (1)
int b{3.7};    // (2)
int c = 3.7;   // (3)`,
      opts: ['(1)', '(2) because braces forbid narrowing conversions', '(3) because 3.7 is not an int', 'None'], a: 1,
      why: 'Brace initialization rejects narrowing (double to int). The `=` form silently truncates 3.7 to 3 (a common source of bugs, which is why braces are preferred).' },

    { q: 'What best describes `int* const p = &x;`?',
      opts: ['A pointer to a const int', 'A const pointer to an int: the pointer cannot move, the int can change', 'A const pointer to a const int', 'A reference to x'], a: 1,
      why: 'Read right to left: "p is a const pointer to int". The star separates the pointer (right side) from the data (left side).' },

    { q: 'In modern C++, what is the preferred way to hold a dynamically sized array of ints?',
      opts: ['`int* a = new int[n];`', '`int a[n];` on the stack', '`std::vector<int>`', '`malloc(n * sizeof(int))`'], a: 2,
      why: '`std::vector` owns its memory, frees it automatically, grows on demand and offers bounds-checked access via `.at()`. Raw `new[]` and `malloc` leave all that to you.' },

    { q: 'Besides allocating memory, what does `new` do that `malloc` does not?',
      opts: ['Nothing, they are identical', 'It calls the constructor and returns a correctly typed pointer', 'It zero-fills the memory', 'It allocates on the stack'], a: 1,
      why: '`new` allocates, then constructs the object, and throws `std::bad_alloc` on failure. `malloc` returns raw uninitialized bytes (`void*`) and returns null on failure.' }
  ]
};
