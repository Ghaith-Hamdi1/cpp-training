# Constants, typedef and alias

- A constant is a value that may not be changed
  - Constant variable: `const` keyword
  - Constant function (should be on a class member function)
  - Constant return: `return const variable`
  - Constant expression: all values must be known at compile time

## Compile time constants

- Allow the compiler to make more and more optimisations

## Runtime constants

- `constexpr` keyword: not necessarily a compile time constant

## Constexpr functions

- Can be evaluated either at runtime or compile time
- Must satisfy many conditions to be evaluated at compile time: refer to documentation

## Inline functions

- Used to try to indicate to the compiler that this is an inline function
- Compiler can accept inlining or refuse inlining and process it as a simple function
- Should have a condition to accept inlining the function
- If inline is accepted, the function will not be called as a function but the code will be replaced
  - => gain of execution time
- Inline conditions: see link (external reference in the original slide)
- A function declared `constexpr` is implicitly an inline function.

## Typedef

- Old way to define new types (kept for compatibility)
  - Define a new type
  - Function pointer type
- The use of `typedef` is deprecated; use `alias` instead

## Alias

- Keyword `using`: creates an alias for an existing type
- Can be declared at any location in the code
- Aliases are not type safe
  - The compiler processes both types the same (e.g. both as `double`), it does not make a difference between the original type and its alias (types can be mixed)
- Why use alias in source code?
  - Make complex types easier
  - Make code easier to read
  - Make code maintenance easier

Reference example, `examples/01-cpp-basics/10-constants-typedef-and-alias/09_constants.cpp`:

```cpp
// Trimmed excerpt — full runnable example: examples/01-cpp-basics/10-constants-typedef-and-alias/09_constants.cpp
#include <iostream>

constexpr int greater(int x, int y)
{
    return (x > y ? x : y); // here's our expression
}

constexpr int factorial(int n)
{
    return n <= 1 ? 1 : (n * factorial(n - 1));
}

int main(){
    const int ki { 5 * 3 };
    constexpr int kExpr { ki };
    int i { kExpr };
    // ki = i; not allowed

    constexpr int x{ 5 };
    constexpr int y{ 6 };
    constexpr int g { greater(x, y) }; // will be evaluated at compile-time
    //constexpr int g { greater(i, y) }; // compile error, i not constant

    int g1 { greater(x, y) }; // Constexpr functions can also be evaluated at runtime

    int h { greater(ki, i) };

    std::cout << "g= " << g << " h= " << h << std::endl;

    const long int fac_10 = factorial(10); // constexpr function called at runtime here

    return 0;
}
```

---

